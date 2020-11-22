#include <gtest/gtest.h>
#include <string>

#include "../Member.hpp"

// The fixture for testing class Foo.
class TestMemoryLeakMember : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestMemoryLeakMember() {
     // You can do set-up work for each test here.
      member = nullptr;
      email = "email@domain.com";
      password = "1234";
      name = "illuminator42";
      bio = "Guardian of the answer to life and everything else";
  }

  ~TestMemoryLeakMember() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     member = new Member(name, bio, email, password);
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
      delete member;
      member = nullptr;
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
  std::string email;
  std::string password;
  std::string name;
  std::string bio;
  Member* member;
};

TEST_F(TestMemoryLeakMember, MemberHasCorrectAttributes)
{
    EXPECT_EQ(email, member->getEmail());
    EXPECT_EQ(password, member->getPassword());
    EXPECT_EQ(name, member->getUsername());
    EXPECT_EQ(bio, member->getBio());
    EXPECT_EQ(0, member->getReputation());
}

TEST_F(TestMemoryLeakMember, MemberCanBeModified)
{
    std::string new_email = "newmail@domain.com";
    std::string new_password = "securepassword";
    std::string new_name = "coolerGuy98";
    std::string new_bio = "I'm back with more cool facts!";

    member->setEmail(new_email);
    member->setPassword(new_password);
    member->setUsername(new_name);
    member->setBio(new_bio);

    EXPECT_EQ(new_email, member->getEmail());
    EXPECT_EQ(new_password, member->getPassword());
    EXPECT_EQ(new_name, member->getUsername());
    EXPECT_EQ(new_bio, member->getBio());
    EXPECT_EQ(0, member->getReputation());
}

//-- Increment / decrement reputation count
TEST_F(TestMemoryLeakMember, MemberReputationIncreases)
{
    member->increaseReputation();
    EXPECT_EQ(1, member->getReputation());

    member->increaseReputation();
    member->increaseReputation();
    EXPECT_EQ(3, member->getReputation());
}

TEST_F(TestMemoryLeakMember, MemberReputationDecreases)
{
    member->increaseReputation();
    member->increaseReputation();
    member->increaseReputation();
    member->increaseReputation();
    ASSERT_EQ(4, member->getReputation());

    member->decreaseReputation();
    EXPECT_EQ(3, member->getReputation());

    member->decreaseReputation();
    member->decreaseReputation();
    EXPECT_EQ(1, member->getReputation());
}

TEST_F(TestMemoryLeakMember, MemberReputationCannotBeNegative)
{
    member->decreaseReputation();
    EXPECT_EQ(0, member->getReputation());
}
