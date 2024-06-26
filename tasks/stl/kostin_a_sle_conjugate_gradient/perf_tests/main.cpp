// Copyright 2024 Kostin Artem
#include <gtest/gtest.h>

#include <vector>

#include "core/perf/include/perf.hpp"
#include "stl/kostin_a_sle_conjugate_gradient/include/ops_stl.hpp"

using namespace KostinArtemSTL;

TEST(kostin_a_sle_conjugate_gradient_stl, test_pipeline_run) {
  int size = 360;

  // Create data
  std::vector<double> in_A = generateSPDMatrix(size, 100);
  std::vector<double> in_b = generatePDVector(size, 100);
  std::vector<double> out(size, 0.0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSTL = std::make_shared<ppc::core::TaskData>();
  taskDataSTL->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSTL->inputs_count.emplace_back(in_A.size());
  taskDataSTL->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_b.data()));
  taskDataSTL->inputs_count.emplace_back(in_b.size());
  taskDataSTL->inputs.emplace_back(reinterpret_cast<uint8_t *>(&size));
  taskDataSTL->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSTL->outputs_count.emplace_back(out.size());

  // Create Task
  auto testTaskSTL = std::make_shared<ConjugateGradientMethodSTL>(taskDataSTL);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSTL);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_TRUE(check_solution(in_A, size, in_b, out, 1e-6));
}

TEST(kostin_a_sle_conjugate_gradient_stl, test_task_run) {
  int size = 360;

  // Create data
  std::vector<double> in_A = generateSPDMatrix(size, 100);
  std::vector<double> in_b = generatePDVector(size, 100);
  std::vector<double> out(size, 0.0);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSTL = std::make_shared<ppc::core::TaskData>();
  taskDataSTL->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSTL->inputs_count.emplace_back(in_A.size());
  taskDataSTL->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_b.data()));
  taskDataSTL->inputs_count.emplace_back(in_b.size());
  taskDataSTL->inputs.emplace_back(reinterpret_cast<uint8_t *>(&size));
  taskDataSTL->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSTL->outputs_count.emplace_back(out.size());

  // Create Task
  auto testTaskSTL = std::make_shared<ConjugateGradientMethodSTL>(taskDataSTL);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSTL);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_TRUE(check_solution(in_A, size, in_b, out, 1e-6));
}
