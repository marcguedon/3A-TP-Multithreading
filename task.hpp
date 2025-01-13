#pragma once

#include <Eigen/Dense>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Task {
private:
  int identifier;
  int size;
  Eigen::MatrixXd a;
  Eigen::VectorXd b;
  Eigen::VectorXd x;
  double time;

public:
  Task(int identifier = 0, int size = 0,
       const Eigen::MatrixXd &a = Eigen::MatrixXd(),
       const Eigen::VectorXd &b = Eigen::VectorXd(),
       const Eigen::VectorXd &x = Eigen::VectorXd(), double time = 0.0);
  Task(const json &file);

  void work();
  const Eigen::VectorXd &get_x() const;
  std::string to_json() const;

  bool operator==(const Task &other) const;
};
