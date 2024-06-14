// Copyright 2024 Smirnova Daria
#pragma once

#include <complex>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

namespace smirnova_stl {

struct crs_matrix {
  int n_rows{};
  int n_cols{};
  std::vector<std::complex<double>> non_zero_values{};
  std::vector<int> pointer{};
  std::vector<int> col_indexes{};
};

class StlTestComplexMatrixCrsSeq : public ppc::core::Task {
 public:
  explicit StlTestComplexMatrixCrsSeq(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  crs_matrix *A_M{}, *B_M{}, *Result{};
};

class StlTestComplexMatrixCrsPar : public ppc::core::Task {
 public:
  explicit StlTestComplexMatrixCrsPar(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  crs_matrix *A_M{}, *B_M{}, *Result{};
};

crs_matrix T(const crs_matrix& M);
bool is_crs(const crs_matrix& M);
}  // namespace smirnova_stl
