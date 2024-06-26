// Copyright 2024 Kistrimova Ekaterina
#include <gtest/gtest.h>

#include <vector>

#include "stl/kistrimova_e_graham_alg_stl/include/ops_stl.hpp"

TEST(kistrimova_e_graham_alg_seq, known_result) {
  // Create data
  std::vector<point> in{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {0, 3}, {3, 0}};
  std::vector<point> res{{0, 0}, {3, 0}, {3, 3}, {0, 3}};
  std::vector<point> out(res.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  GrahamAlgTask testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  ASSERT_EQ(out.size(), res.size());
  for (size_t i = 0; i < res.size(); i++) {
    ASSERT_EQ(out[i], res[i]);
  }
}

TEST(kistrimova_e_graham_alg_seq, min_data) {
  // Create data
  std::vector<point> in{{0, 0}, {2, 0}, {1, 2}};
  std::vector<point> res{{0, 0}, {2, 0}, {1, 2}};
  std::vector<point> out(res.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  GrahamAlgTask testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  ASSERT_EQ(out.size(), res.size());
  for (size_t i = 0; i < res.size(); i++) {
    ASSERT_EQ(out[i], res[i]);
  }
}

TEST(kistrimova_e_graham_alg_seq, five_points) {
  // Create data
  std::vector<point> in{{0, 4}, {1, 4}, {0, 5}, {3, 3}, {5, 2}};
  std::vector<point> res{{0, 4}, {5, 2}, {0, 5}};
  std::vector<point> out(res.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  GrahamAlgTask testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  ASSERT_EQ(out.size(), res.size());
  for (size_t i = 0; i < res.size(); i++) {
    ASSERT_EQ(out[i], res[i]);
  }
}

TEST(kistrimova_e_graham_alg_seq, inside_square) {
  // Create data
  std::vector<point> in{{1, 1}, {6, 1}, {1, 6}, {2, 4}, {5, 3}, {6, 6}};
  std::vector<point> res{{1, 1}, {6, 1}, {6, 6}, {1, 6}};
  std::vector<point> out(res.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  GrahamAlgTask testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  ASSERT_EQ(out.size(), res.size());
  for (size_t i = 0; i < res.size(); i++) {
    ASSERT_EQ(out[i], res[i]);
  }
}

TEST(kistrimova_e_graham_alg_seq, simple_square) {
  // Create data
  std::vector<point> in{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {0, 3}, {3, 0}};
  std::vector<point> res{{0, 0}, {3, 0}, {3, 3}, {0, 3}};
  std::vector<point> out(res.size());

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataOmp = std::make_shared<ppc::core::TaskData>();
  taskDataOmp->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataOmp->inputs_count.emplace_back(in.size());
  taskDataOmp->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataOmp->outputs_count.emplace_back(out.size());

  // Creative Task
  GrahamAlgTask testTaskOmp(taskDataOmp);
  ASSERT_EQ(testTaskOmp.validation(), true);
  testTaskOmp.pre_processing();
  testTaskOmp.run();
  testTaskOmp.post_processing();

  ASSERT_EQ(out.size(), res.size());
  for (size_t i = 0; i < res.size(); i++) {
    ASSERT_EQ(out[i], res[i]);
  }
}
