// Copyright 2024 Mukhin Ivan
#include <gtest/gtest.h>
#include <oneapi/tbb.h>

#include <vector>

#include "core/perf/include/perf.hpp"
#include "tbb/mukhin_a_gaussian_filter/include/gaussian_filter.hpp"

TEST(mukhin_i_a_gaussian_filter_block_tbb, test_pipeline_run) {
  // Create data
  uint32_t width = 3200;
  uint32_t height = 3200;
  PixelMap in(width, height);
  PixelMap out(width, height);
  PixelMap expected(width, height);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Create Task
  auto testTaskTBB = std::make_shared<mukhin_i_tbb::GaussianFilterTBB>(taskDataSeq);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = oneapi::tbb::tick_count::now();
  perfAttr->current_timer = [&] { return (oneapi::tbb::tick_count::now() - t0).seconds(); };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskTBB);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_EQ(out, expected);
}

TEST(mukhin_i_a_gaussian_filter_block_tbb, test_task_run) {
  // Create data
  uint32_t width = 3200;
  uint32_t height = 3200;
  PixelMap in(width, height);
  PixelMap out(width, height);
  PixelMap expected(width, height);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data.data()));
  taskDataSeq->inputs_count.emplace_back(width);
  taskDataSeq->inputs_count.emplace_back(height);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data.data()));
  taskDataSeq->outputs_count.emplace_back(width);
  taskDataSeq->outputs_count.emplace_back(height);

  // Create Task
  auto testTaskTBB = std::make_shared<mukhin_i_tbb::GaussianFilterTBB>(taskDataSeq);

  // Create Perf attributes
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = oneapi::tbb::tick_count::now();
  perfAttr->current_timer = [&] { return (oneapi::tbb::tick_count::now() - t0).seconds(); };

  // Create and init perf results
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskTBB);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_EQ(out, expected);
}