#include <gtest/gtest.h>
#include <string>

#include "../Member.hpp"
#include "../Application.hpp"

// The fixture for testing class Foo.
class TestMemoryLeakApplicationBasic : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestMemoryLeakApplicationBasic() {
     // You can do set-up work for each test here.
      member = nullptr;
      email1 = "email@domain.com";
      password1 = "1234";
      name1 = "illuminator42";
      bio1 = "Guardian of the answer to life and everything elsee";

      member2 = nullptr;
      email2 = "otheremail@domain.com";
      password2 = "member2pass";
      name2 = "totalNoob";
      bio2 = "It's my first day here";

      member3 = nullptr;
      email3 = "fakeemail@domain.com";
      password3 = "member3pass";
      name3 = "theThird";
      bio3 = "I'm here just to test stuff";
  }

  ~TestMemoryLeakApplicationBasic() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     member = new Member(name1, bio1, email1, password1);
     member2 = new Member(name2, bio2, email2, password2);
     member3 = new Member(name3, bio3, email3, password3);
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
      delete member;
      member = nullptr;

      delete member2;
      member2 = nullptr;

      delete member3;
      member3 = nullptr;
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
  std::string email1, email2, email3;
  std::string password1, password2, password3;
  std::string name1, name2, name3;
  std::string bio1, bio2, bio3;
  Member* member, *member2, *member3;
};


TEST_F(TestMemoryLeakApplicationBasic, ApplicationCanCreateAndShowAllMembers)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    std::vector<MemberProfileInfo*> members = manager.showMembers();
    ASSERT_EQ(1, members.size());
    EXPECT_EQ(name1, members[0]->getUsername());
    EXPECT_EQ(bio1, members[0]->getBio());
    //EXPECT_EQ(0, members[0]->getFollowers());
    //EXPECT_EQ(0, members[0]->getFollowing().size());

    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    members = manager.showMembers();
    ASSERT_EQ(2, members.size());
    EXPECT_EQ(name2, members[1]->getUsername());
    EXPECT_EQ(bio2, members[1]->getBio());
    //EXPECT_EQ(0, members[1]->getFollowers());
    //EXPECT_EQ(0, members[1]->getFollowing().size());
}

TEST_F(TestMemoryLeakApplicationBasic, ApplicationCanShowSingleMember)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    ASSERT_TRUE(manager.createMember(name3, bio3, email3, password3));

    MemberProfileInfo* member = manager.showMember(name2);

    ASSERT_NE(nullptr, member);
    EXPECT_EQ(name2, member->getUsername());
    EXPECT_EQ(bio2, member->getBio());
    //EXPECT_EQ(0, member->getFollowers());
    //EXPECT_EQ(0, member->getFollowing().size());

    member = manager.showMember(name3);

    ASSERT_NE(nullptr, member);
    EXPECT_EQ(name3, member->getUsername());
    EXPECT_EQ(bio3, member->getBio());
    //EXPECT_EQ(0, member->getFollowers());
    //EXPECT_EQ(0, member->getFollowing().size());

    member = manager.showMember(name1);

    ASSERT_NE(nullptr, member);
    EXPECT_EQ(name1, member->getUsername());
    EXPECT_EQ(bio1, member->getBio());
    //EXPECT_EQ(0, member->getFollowers());
    //EXPECT_EQ(0, member->getFollowing().size());
}

TEST_F(TestMemoryLeakApplicationBasic, ApplicationCannotDuplicateMember)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    std::vector<MemberProfileInfo*> members = manager.showMembers();
    ASSERT_EQ(1, members.size());
    EXPECT_EQ(name1, members[0]->getUsername());
    EXPECT_EQ(bio1, members[0]->getBio());
    //EXPECT_EQ(0, members[0]->getFollowers());
    //EXPECT_EQ(0, members[0]->getFollowing().size());

    ASSERT_FALSE(manager.createMember(name1, bio1, email1, password1));
    members = manager.showMembers();
    ASSERT_EQ(1, members.size());
}


TEST_F(TestMemoryLeakApplicationBasic, ApplicationCanLoginMember)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    std::vector<MemberProfileInfo*> members = manager.showMembers();
    ASSERT_EQ(1, members.size());
    EXPECT_EQ(name1, members[0]->getUsername());
    EXPECT_EQ(bio1, members[0]->getBio());
    //EXPECT_EQ(0, members[0]->getFollowers());
    //EXPECT_EQ(0, members[0]->getFollowing().size());

    EXPECT_TRUE(manager.login(email1, password1));
    EXPECT_TRUE(manager.isLogged());
    Member *logged_member = manager.getCurrentMember();
    ASSERT_NE(nullptr, logged_member);
    EXPECT_EQ(email1, logged_member->getEmail());
    EXPECT_EQ(password1, logged_member->getPassword());
    EXPECT_EQ(name1, logged_member->getUsername());
    EXPECT_EQ(bio1, logged_member->getBio());

    //EXPECT_EQ(0, logged_member->getFollowers());
    //EXPECT_EQ(0, logged_member->getFollowing().size());
}

TEST_F(TestMemoryLeakApplicationBasic, ApplicationWrongMemberCannotLogin)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    EXPECT_FALSE(manager.login(email1, password2));
    EXPECT_FALSE(manager.isLogged());
    EXPECT_EQ(nullptr, manager.getCurrentMember());
    EXPECT_FALSE(manager.login(email2, password2));
    EXPECT_FALSE(manager.isLogged());
    EXPECT_EQ(nullptr, manager.getCurrentMember());
}

TEST_F(TestMemoryLeakApplicationBasic, ApplicationCannotLoginMemberTwice)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.isLogged());
    EXPECT_FALSE(manager.login(email1, password1));
    EXPECT_FALSE(manager.login(email2, password2));
}

TEST_F(TestMemoryLeakApplicationBasic, ApplicationCanLogoutMember)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    EXPECT_FALSE(manager.logout());  //-- No member logged in yet
    ASSERT_TRUE(manager.login(email1, password1));
    EXPECT_TRUE(manager.logout());
    EXPECT_EQ(nullptr, manager.getCurrentMember());
}


TEST_F(TestMemoryLeakApplicationBasic, ApplicationCanEraseLoggedMember)
{
    Application manager;
    ASSERT_FALSE(manager.eraseCurrentMember()); //-- Error if not logged in
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.eraseCurrentMember());
    EXPECT_EQ(nullptr, manager.getCurrentMember());
    std::vector<MemberProfileInfo*> members = manager.showMembers();
    ASSERT_EQ(1, members.size());
    EXPECT_EQ(name2, members[0]->getUsername());
}

TEST_F(TestMemoryLeakApplicationBasic, ApplicationLoggedMemberCanEditProfile)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    EXPECT_FALSE(manager.editEmail(email3)); //-- Cannot edit profile if not logged in
    EXPECT_FALSE(manager.editPassword(password3)); //-- Cannot edit profile if not logged in
    EXPECT_FALSE(manager.editUsername(name3)); //-- Cannot edit profile if not logged in
    EXPECT_FALSE(manager.editBio(bio3)); //-- Cannot edit profile if not logged in
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_EQ(email1, manager.getCurrentMember()->getEmail());
    ASSERT_EQ(password1, manager.getCurrentMember()->getPassword());
    ASSERT_EQ(name1, manager.getCurrentMember()->getUsername());
    ASSERT_EQ(bio1, manager.getCurrentMember()->getBio());

    EXPECT_TRUE(manager.editEmail(email3));
    EXPECT_EQ(email3, manager.getCurrentMember()->getEmail());
    EXPECT_EQ(password1, manager.getCurrentMember()->getPassword());
    EXPECT_EQ(name1, manager.getCurrentMember()->getUsername());
    EXPECT_EQ(bio1, manager.getCurrentMember()->getBio());

    ASSERT_TRUE(manager.editPassword(password3));
    EXPECT_EQ(email3, manager.getCurrentMember()->getEmail());
    EXPECT_EQ(password3, manager.getCurrentMember()->getPassword());
    EXPECT_EQ(name1, manager.getCurrentMember()->getUsername());
    EXPECT_EQ(bio1, manager.getCurrentMember()->getBio());

    ASSERT_TRUE(manager.editUsername(name3));
    EXPECT_EQ(email3, manager.getCurrentMember()->getEmail());
    EXPECT_EQ(password3, manager.getCurrentMember()->getPassword());
    EXPECT_EQ(name3, manager.getCurrentMember()->getUsername());
    EXPECT_EQ(bio1, manager.getCurrentMember()->getBio());

    ASSERT_TRUE(manager.editBio(bio3));
    EXPECT_EQ(email3, manager.getCurrentMember()->getEmail());
    EXPECT_EQ(password3, manager.getCurrentMember()->getPassword());
    EXPECT_EQ(name3, manager.getCurrentMember()->getUsername());
    EXPECT_EQ(bio3, manager.getCurrentMember()->getBio());

    ASSERT_FALSE(manager.editEmail(email2)); //-- cannot duplicate an existing email
    EXPECT_EQ(email3, manager.getCurrentMember()->getEmail());
    ASSERT_FALSE(manager.editUsername(name2)); //-- cannot duplicate an existing membername
    EXPECT_EQ(name3, manager.getCurrentMember()->getUsername());
}
