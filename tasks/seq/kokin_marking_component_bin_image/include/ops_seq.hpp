// Copyright 2024 Kokin Ivan
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

class imageMarkingSeq : public ppc::core::Task {
 public:
  explicit imageMarkingSeq(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  uint32_t ht{}, wh{};
  std::vector<std::vector<uint32_t>> src = {};
  std::vector<std::vector<uint32_t>> dest = {};
  void imageMark();
};
