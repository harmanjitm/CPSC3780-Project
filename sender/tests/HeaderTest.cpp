#include "Header.cpp"
#include "gtest/gtest.h"

#include <ctime>

class HeaderTest : public testing::Test {
  protected:
    void SetUp() {
      
    }

    void TearDown() {
      
    }
};

TEST(HeaderTest, setType_One) {
  Header h;
  h.setType(1);
  ASSERT_TRUE(h.getType() == 1);
}

TEST(HeaderTest, setType_Two) {
  Header h;
  h.setType(2);
  ASSERT_TRUE(h.getType() == 2);
}

TEST(HeaderTest, setType_Three) {
  Header h;
  h.setType(3);
  ASSERT_TRUE(h.getType() == 3);
}

TEST(HeaderTest, getTypeDefault) {
  Header h;
  ASSERT_TRUE(h.getType() == 0);
}

TEST(HeaderTest, getType_One) {
  Header h;
  h.setType(1);
  ASSERT_TRUE(h.getType() == 1);
}

TEST(HeaderTest, getType_Two) {
  Header h;
  h.setType(2);
  ASSERT_TRUE(h.getType() == 2);
}

TEST(HeaderTest, getType_Three) {
  Header h;
  h.setType(3);
  ASSERT_TRUE(h.getType() == 3);
}

TEST(HeaderTest, getTR_Zero) {
  Header h;
  ASSERT_TRUE(h.getTR() == 0);
}

TEST(HeaderTest, setTR_Zero) {
  Header h;
  h.setTR(0);
  ASSERT_TRUE(h.getTR() == 0);
}

TEST(HeaderTest, getTR_One) {
  Header h;
  h.setTR(1);
  ASSERT_TRUE(h.getTR() == 1);
}

TEST(HeaderTest, setTR_One) {
  Header h;
  h.setTR(1);
  ASSERT_TRUE(h.getTR() == 1);
}

TEST(HeaderTest, getWindow) {
  Header h;
  ASSERT_TRUE(h.getWindow() == 0);
}

TEST(HeaderTest, setWindow) {
  Header h;
  h.setWindow(31);
  ASSERT_TRUE(h.getWindow() == 31);
}

TEST(HeaderTest, getSequenceNum_Zero) {
  Header h;
  ASSERT_TRUE(h.getSequenceNum() == 0);
}

TEST(HeaderTest, setSequenceNum_Zero) {
  Header h;
  h.setSequenceNum(1);
  h.setSequenceNum(0);
  ASSERT_TRUE(h.getSequenceNum() == 0);
}

TEST(HeaderTest, getSequenceNum_Max) {
  Header h;
  ASSERT_TRUE(h.getSequenceNum() != 255);
}

TEST(HeaderTest, setSequenceNum_Max) {
  Header h;
  h.setSequenceNum(255);
  ASSERT_TRUE(h.getSequenceNum());
}

TEST(HeaderTest, getLength_Default) {
  Header h;
  ASSERT_TRUE(h.getLength() == 512);
}

TEST(HeaderTest, setLength_Default) {
  Header h;
  h.setLength(512);
  ASSERT_TRUE(h.getLength() == 512);
}

TEST(HeaderTest, getLength_Custom) {
  Header h;
  h.setLength(256);
  ASSERT_TRUE(h.getLength() == 256);
}

TEST(HeaderTest, setLength_Custom) {
  Header h;
  h.setLength(256);
  ASSERT_TRUE(h.getLength() == 256);
}

TEST(HeaderTest, getTimestamp) {
  Header h;
  h.getTimestamp();
  ASSERT_TRUE(true);
}

TEST(HeaderTest, getCRC1) {
  Header h;
  ASSERT_TRUE(h.getCRC1() == 0);
}

TEST(HeaderTest, setCRC1) {
  Header h;
  h.setCRC1(2);
  ASSERT_TRUE(h.getCRC1() == 2);
}

TEST(HeaderTest, getCRC2) {
  Header h;
  ASSERT_TRUE(h.getCRC2() == 0);
}

TEST(HeaderTest, setCRC2) {
  Header h;
  h.setCRC2(2);
  ASSERT_TRUE(h.getCRC2() == 2);
}

TEST(HeaderTest, getPayload) {
  Header h;
  h.setPayload("Test");
  ASSERT_TRUE(h.getPayload() == "Test");
}

TEST(HeaderTest, setPayload) {
  Header h;
  h.setPayload("SetPayload");
  ASSERT_TRUE(h.getPayload() == "SetPayload");
}

/**
 * getTR_Zero
 * getTR_One
 * setTR_Zero
 * setTR_One
 */