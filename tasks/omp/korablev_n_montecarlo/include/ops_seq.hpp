// Copyright 2024 Korablev Nikita
#pragma once

#include <string>
#include <vector>

#include "core/task/include/task.hpp"
#include "omp/korablev_n_montecarlo/include/my_funcs.hpp"

class KorablevSequentialMonteCarlo : public ppc::core::Task {
 public:
  explicit KorablevSequentialMonteCarlo(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  func function{};
  double Int1[2]{}, Int2[2]{};

  int N{};
  double res{};
};
