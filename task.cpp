#include "task.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <random>
#include <stdexcept>

using json = nlohmann::json;

Task::Task(int identifier, int size, const Eigen::MatrixXd &a,
           const Eigen::VectorXd &b, const Eigen::VectorXd &x, double time)
    : identifier(identifier), size(size), a(a), b(b), x(x), time(time) {
  if (size > 0 && (a.rows() != size || a.cols() != size || b.size() != size ||
                   x.size() != size)) {
    throw std::invalid_argument(
        "Les dimensions de la matrice et des vecteurs doivent être égales à la "
        "taille de la matrice.");
  }

  if (size == 0) {
    throw std::invalid_argument(
        "La taille de la matrice doit être strictement positive.");
  }
}

Task::Task(const json &file) {
  identifier = file["identifier"];
  size = file["size"];

  a.resize(size, size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      a(i, j) = file["a"][i][j];
    }
  }

  b.resize(size);
  for (int i = 0; i < size; ++i) {
    b[i] = file["b"][i];
  }

  x.resize(size);
  if (file.contains("x")) {
    for (int i = 0; i < size; ++i) {
      x[i] = file["x"][i];
    }
  }

  double time = file["time"];
}

void Task::work() {
  auto start = std::chrono::high_resolution_clock::now();
  x = a.colPivHouseholderQr().solve(b);
  auto end = std::chrono::high_resolution_clock::now();
  time = std::chrono::duration<double>(end - start).count();
}

const Eigen::VectorXd &Task::get_x() const { return x; }

std::string Task::to_json() const {
  json file;
  file["identifier"] = identifier;
  file["size"] = size;

  file["a"] =
      std::vector<std::vector<double>>(a.rows(), std::vector<double>(a.cols()));
  for (int i = 0; i < a.rows(); ++i) {
    for (int j = 0; j < a.cols(); ++j) {
      file["a"][i][j] = a(i, j);
    }
  }

  file["b"] = std::vector<double>(b.data(), b.data() + b.size());
  for (int i = 0; i < b.size(); ++i) {
    file["b"][i] = b[i];
  }

  file["x"] = std::vector<double>(x.data(), x.data() + x.size());
  for (int i = 0; i < x.size(); ++i) {
    file["x"][i] = x[i];
  }

  file["time"] = time;

  return file.dump();
}

bool Task::operator==(const Task &other) const {
  return identifier == other.identifier && size == other.size &&
         a.isApprox(other.a, 1e-8) && b.isApprox(other.b, 1e-8) &&
         x.isApprox(other.x, 1e-8) && std::abs(time - other.time) < 1e-8;
}
