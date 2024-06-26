// Copyright 2024 Volodin Evgeniy
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"

class SobelTaskOMP : public ppc::core::Task {
 public:
  explicit SobelTaskOMP(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool validation() override;
  bool pre_processing() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::vector<int> kernel_x = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

  std::vector<int> kernel_y = {1, 2, 1, 0, 0, 0, -1, -2, -1};

  std::vector<int> sourceImage;
  std::vector<int> resultImage;

  int width_;
  int height_;

  static int clamp(int value, int min, int max);
};
