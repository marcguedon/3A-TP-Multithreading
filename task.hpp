#pragma once

#include <Eigen/Dense>
#include <string>

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
       const Eigen::VectorXd &b = Eigen::VectorXd());

  void work();
  const Eigen::VectorXd &get_x() const;

  std::string to_json() const;
  static Task from_json(const std::string &jsonString);

  bool operator==(const Task &other) const;
};
