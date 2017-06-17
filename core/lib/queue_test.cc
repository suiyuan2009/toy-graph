#include <thread>
#include <vector>

#include "core/lib/queue.h"
#include "gtest/gtest.h"

class QueueTest : public testing::Test {
protected:

  virtual void SetUp() {
    q = new lib::FixedSizeQueue<int>(100000);
  }

  virtual void TearDown() {
  }

  void producer(int size) {
    for (int i = 0; i < size; i++) {
      int x = i;
      q->push(x);
    }
  }

  void consumer(int size) {
    for (int i = 0; i < size; i++) {
      result.push_back(q->pop());
    }
  }

  void Test(int size) {
    std::thread p(&QueueTest::producer, this, size);
    std::thread c(&QueueTest::consumer, this, size);
    p.join();
    c.join();
    EXPECT_EQ(size, result.size());
    for (int i = 0; i < size; i++) {
      EXPECT_EQ(i, result[i]);
    }
  }

  std::vector<int>result;
  lib::QueueInterface<int>* q;
};


TEST_F(QueueTest, JustATest) {
  Test(1000000);
}
