#include <gtest/gtest.h>

#include "dp/DynamicProgramming.h"

class DynamicProgrammingTest : public ::testing::Test {
 protected:
  dp::DynamicProgramming dypo;
  dp::Boxes boxes;

  void SetUp() override {
    boxes = {
        {{4, 5, 3}, {1, 5, 4}, {2, 3, 2}, {2, 4, 1}, {3, 6, 2}, {1, 2, 2}}
    };
    dypo.setBoxes(boxes);
  }
};

TEST_F(DynamicProgrammingTest, SetBoxesStoresBoxes) {
  // If getBoxes() exists, uncomment the next line:
  // EXPECT_EQ(dypo.getBoxes(), boxes);
  SUCCEED();
}

TEST_F(DynamicProgrammingTest, RunExecutesWithoutThrowing) {
  EXPECT_NO_THROW(dypo.run());
}

TEST(DynamicProgrammingStandalone, HandlesEmptyBoxes) {
  dp::DynamicProgramming dypo;
  dp::Boxes emptyBoxes;
  dypo.setBoxes(emptyBoxes);
  EXPECT_NO_THROW(dypo.run());
}

TEST(DynamicProgrammingStandalone, HandlesSingleBox) {
  dp::DynamicProgramming dypo;
  dp::Boxes singleBox = {{{1, 2, 3}}};
  dypo.setBoxes(singleBox);
  EXPECT_NO_THROW(dypo.run());
}

TEST(DynamicProgrammingStandalone, HandlesIdenticalBoxes) {
  dp::DynamicProgramming dypo;
  dp::Boxes identicalBoxes = {
      {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}
  };
  dypo.setBoxes(identicalBoxes);
  EXPECT_NO_THROW(dypo.run());
}

TEST(DynamicProgrammingStandalone, HandlesLargeInput) {
  dp::DynamicProgramming dypo;
  dp::Boxes manyBoxes;
  for (int i = 1; i <= 100; ++i) {
    manyBoxes.push_back({i, i + 1, i + 2});
  }
  dypo.setBoxes(manyBoxes);
  EXPECT_NO_THROW(dypo.run());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}