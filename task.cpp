#include "task.hpp"
#include <nlohmann/json.hpp>
#include <random>
#include <stdexcept>

using json = nlohmann::json;

Task::Task(int identifier, int size, const Eigen::MatrixXd &a,
           const Eigen::VectorXd &b)
    : identifier(identifier), size(size), a(a), b(b),
      x(Eigen::VectorXd::Zero(size)) {
  if (size > 0 && (a.rows() != size || a.cols() != size || b.size() != size)) {
    throw std::invalid_argument(
        "Matrix and vector dimensions do not match the specified size.");
  }

  if (size == 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sizeDist(300, 3000);
    size = sizeDist(gen);

    a = Eigen::MatrixXd::Random(size, size);
    b = Eigen::VectorXd::Random(size);
    x = Eigen::VectorXd::Zero(size);
  }
}

void Task::work() {
  auto start = std::chrono::high_resolution_clock::now();
  x = a.colPivHouseholderQr().solve(b);
  auto end = std::chrono::high_resolution_clock::now();
  time = std::chrono::duration<double>(end - start).count();
}

const Eigen::VectorXd &Task::get_x() const { return x; }

std::string Task::to_json() const {
  json j;
  j["identifier"] = identifier;
  j["size"] = size;
  j["a"] =
      std::vector<std::vector<double>>(a.rows(), std::vector<double>(a.cols()));
  for (int i = 0; i < a.rows(); ++i) {
    for (int j = 0; j < a.cols(); ++j) {
      j["a"][i][j] = a(i, j);
    }
  }
  j["b"] = std::vector<double>(b.data(), b.data() + b.size());
  j["time"] = time;
  return j.dump();
}

Task Task::from_json(const std::string &jsonString) {
  json j = json::parse(jsonString);

  int identifier = j["identifier"];
  int size = j["size"];

  Eigen::MatrixXd a(size, size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      a(i, j) = j["a"][i][j];
    }
  }

  Eigen::VectorXd b(size);
  for (int i = 0; i < size; ++i) {
    b[i] = j["b"][i];
  }

  return Task(identifier, size, a, b);
}

bool Task::operator==(const Task &other) const {
  return identifier == other.identifier && size == other.size &&
         a.isApprox(other.a, 1e-8) && b.isApprox(other.b, 1e-8) &&
         std::abs(time - other.time) < 1e-8;
}
