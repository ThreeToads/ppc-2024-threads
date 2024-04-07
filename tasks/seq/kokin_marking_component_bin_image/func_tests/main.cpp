// Copyright 2024 Kokin Ivan
#include <gtest/gtest.h>

#include <vector>

#include "seq/kokin_marking_component_bin_image/include/ops_seq.hpp"

TEST(kokin_marking_component_bin_image_test, test_1) {
  uint32_t ht = 8;
  uint32_t wh = 8;
  std::vector<uint32_t> size = {ht, wh};
  std::vector<uint8_t> in(ht * wh, 1);
  std::vector<uint8_t> out(ht * wh, 0);
  std::vector<uint8_t> cmpt(ht * wh, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(size.data()));
  taskDataSeq->inputs_count.emplace_back(size.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  imageMarkingSeq testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_EQ(out, cmpt);
}

TEST(kokin_marking_component_bin_image_test, test_2) {
  uint32_t ht = 8;
  uint32_t wh = 8;
  std::vector<uint32_t> size = {ht, wh};
  std::vector<uint8_t> in(ht * wh, 0);
  std::vector<uint8_t> out(ht * wh, 0);
  std::vector<uint8_t> cmpt(ht * wh, 1);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(size.data()));
  taskDataSeq->inputs_count.emplace_back(size.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  imageMarkingSeq testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_EQ(out, cmpt);
}

TEST(kokin_marking_component_bin_image_test, test_3) {
  uint32_t ht = 5;
  uint32_t wh = 5;
  std::vector<uint32_t> size = {ht, wh};
  std::vector<uint8_t> in = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1};
  std::vector<uint8_t> cmpt = {1, 1, 0, 0, 2, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 4, 0, 0, 0, 5, 6, 0, 0, 0};

  std::vector<uint8_t> out(ht * wh, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(size.data()));
  taskDataSeq->inputs_count.emplace_back(size.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  imageMarkingSeq testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_EQ(out, cmpt);
}

TEST(kokin_marking_component_bin_image_test, test_4) {
  uint32_t ht = 3;
  uint32_t wh = 3;
  std::vector<uint32_t> size = {ht, wh};
  std::vector<uint8_t> in = {0, 0, 1, 1, 0, 0, 0, 1, 1};
  std::vector<uint8_t> cmpt = {1, 1, 0, 0, 2, 1, 2, 0, 0};

  std::vector<uint8_t> out(ht * wh, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(size.data()));
  taskDataSeq->inputs_count.emplace_back(size.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  imageMarkingSeq testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_EQ(out, cmpt);
}

TEST(kokin_marking_component_bin_image_test, test_5) {
  uint32_t ht = 7;
  uint32_t wh = 7;
  std::vector<uint32_t> size = {ht, wh};
  std::vector<uint8_t> in = {0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
  std::vector<uint8_t> cmpt = {1, 1, 0, 0, 2, 1, 2, 1, 1, 0, 0, 2, 1, 2, 1, 1, 0, 0, 2, 1, 2, 1, 1, 0, 0, 2, 1, 2, 1, 1, 0, 0, 2, 1, 2, 1, 1, 0, 0, 2, 1, 2, 1, 1, 0, 0, 2, 1, 2};

  std::vector<uint8_t> out(ht * wh, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(size.data()));
  taskDataSeq->inputs_count.emplace_back(size.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  imageMarkingSeq testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_EQ(out, cmpt);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
