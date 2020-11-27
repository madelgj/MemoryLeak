#include <gtest/gtest.h>
#include <time.h>
#include "../Member.hpp"
#include "../Question.hpp"
#include "../Interaction.hpp"
//#include "../Answer.hpp"
//#include "../Comment.hpp"


// The fixture for testing class Foo.
class TestMemoryLeakInteractions : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestMemoryLeakInteractions() {
     // You can do set-up work for each test here.

    //-- Test data
    id1 = 0;
    id2 = 1;
    id3 = 2;

    /*time(&t1);
    time(&t2);
    time(&t3);*/
    t1 = 1;
    t2 = 20;
    t3 = 300;

    title1 = "How do I use this app?";
    description1 = "I'm new and I don't know how to use this. Please help.";
    tags1 = {"programming", "newbie", "general"};
    text2 = "You just kind of did use it.";
    text3 = "I should have used StackOverflow...";

    //-- Define test members
    email1 = "email@domain.com";
    password1 = "1234";
    name1 = "illuminator42";
    bio1 = "Guardian of the answer to life and everything else";
    member = new Member(name1, bio1, email1, password1);
    pmember = (MemberProfileInfo *)member;

    email2 = "otheremail@domain.com";
    password2 = "member2pass";
    name2 = "noobie";
    bio2 = "I signed up thinking this was Barker";
    member2 = new Member(name2, bio2, email2, password2);
    pmember2 = (MemberProfileInfo *)member2;

    //-- Define expected output texts
    // comment format -> "\tComment:\n\t{id} - {time} - {username}:\n\t{text}"
    comment_text = "\tComment:\n\t2 - 300 - noobie:\n\tI should have used StackOverflow...";

    // answer format -> "\tAnswer:\n\t{id} - {time} - {username}\n{accepted/''} - {votes} votes\n\t{text}\n\t--\n\t{comment}\n\t-\t{comment}\n\t-"
    answer_text = "\tAnswer:\n\t1 - 20 - noobie:\naccepted - 1 votes\n\tYou just kind of did use it.\n\t--";
    answer_with_comment_text = "\tAnswer:\n\t1 - 20 - illuminator42:\n - 0 votes\n\tYou just kind of did use it.\n\t--\n\t"+comment_text+"\n\t-";

    // question format -> "{id} - {title}\n -------\nby {username} on {time}\nTags: {tag1/tag2/tag3}\n{open/closed} - {votes} votes\n---\n{description}\n---\n{interaction}\n-\n{interaction}\n---"
    question_text = "0 - How do I use this app?\n -------\nby illuminator42 on 1\nTags: programming/newbie/general\nopen - 1 votes\n---\nI'm new and I don't know how to use this. Please help.\n---";
    question_with_comment_text = "0 - How do I use this app?\n -------\nby illuminator42 on 1\nTags: programming/newbie/general\nopen - 0 votes\n---\nI'm new and I don't know how to use this. Please help.\n---\n" + comment_text + "\n---";
    question_with_answer_text = "0 - How do I use this app?\n -------\nby illuminator42 on 1\nTags: programming/newbie/general\nopen - 0 votes\n---\nI'm new and I don't know how to use this. Please help.\n---\n" + answer_text +"\n---";

  }

  ~TestMemoryLeakInteractions() override {
     // You can do clean-up work that doesn't throw exceptions here.
      delete member;
      member = nullptr;

      delete member2;
      member2 = nullptr;

  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).

  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  int id1, id2, id3;
  time_t t1, t2, t3;
  std::string title1, text2, text3;
  std::string description1, description2, description3;
  std::vector<std::string> tags1;
  std::string question_text, question_with_comment_text, question_with_answer_text;
  std::string answer_text, answer_with_comment_text, comment_text;
  std::string email1, password1, name1, bio1;
  std::string email2, password2, name2, bio2;
  Member * member, *member2;
  MemberProfileInfo * pmember, *pmember2;

};


TEST_F(TestMemoryLeakInteractions, CanCreateComment)
{
    Comment comment(id3, t3, pmember2, text3);
    EXPECT_EQ(id3, comment.getId());
    EXPECT_EQ(t3, comment.getTime());
    EXPECT_EQ(pmember2, comment.getAuthor());
    EXPECT_EQ(text3, comment.getText());

    Interaction* interaction = (Interaction*)&comment;
    EXPECT_EQ(id3, interaction->getId());
    EXPECT_EQ(t3, interaction->getTime());
    EXPECT_EQ(pmember2, interaction->getAuthor());
    EXPECT_EQ(comment_text, interaction->show());
}


TEST_F(TestMemoryLeakInteractions, CanCreateAnswer)
{
    Answer answer(id2, t2, pmember2, text2);
    EXPECT_EQ(id2, answer.getId());
    EXPECT_EQ(t2, answer.getTime());
    EXPECT_EQ(pmember2, answer.getAuthor());
    EXPECT_EQ(text2, answer.getText());
    EXPECT_EQ(0, answer.getVotes());
    answer.incrementVotes();
    EXPECT_EQ(1, answer.getVotes());
    answer.incrementVotes();
    EXPECT_EQ(2, answer.getVotes());
    answer.decrementVotes();
    EXPECT_EQ(1, answer.getVotes());
    EXPECT_FALSE(answer.getRightAnswer());
    answer.setRightAnswer(true);
    EXPECT_TRUE(answer.getRightAnswer());

    Interaction* interaction = (Interaction*)&answer;
    EXPECT_EQ(id2, interaction->getId());
    EXPECT_EQ(t2, interaction->getTime());
    EXPECT_EQ(pmember2, interaction->getAuthor());
    EXPECT_EQ(answer_text, interaction->show());
}


TEST_F(TestMemoryLeakInteractions, CanCommentAnswer)
{
    Comment comment(id3, t3, pmember2, text3);
    Answer answer(id2, t2, pmember, text2);

    answer.addComment(&comment);
    std::vector<Comment *> comments = answer.getComments();
    ASSERT_EQ(1, comments.size());
    EXPECT_EQ(id3, comments[0]->getId());
    EXPECT_EQ(pmember2, comments[0]->getAuthor());
    EXPECT_EQ(answer_with_comment_text, answer.show());

    Comment* removed_comment = answer.removeComment(id3);
    ASSERT_EQ(&comment, removed_comment);
    comments = answer.getComments();
    ASSERT_EQ(0, comments.size());
}


TEST_F(TestMemoryLeakInteractions, CanCreateQuestion)
{
    Question question(id1, t1, pmember, title1, description1, tags1);
    EXPECT_EQ(id1, question.getId());
    EXPECT_EQ(t1, question.getTime());
    EXPECT_EQ(pmember, question.getAuthor());
    EXPECT_EQ(title1, question.getTitle());
    EXPECT_EQ(description1, question.getDescription());

    std::vector<std::string> stored_tags = question.getTags();
    ASSERT_EQ(tags1.size(), stored_tags.size());
    for (int i=0; i<tags1.size(); i++)
        EXPECT_EQ(tags1[i], stored_tags[i]);

    EXPECT_EQ(0, question.getVotes());
    question.incrementVotes();
    EXPECT_EQ(1, question.getVotes());
    question.incrementVotes();
    EXPECT_EQ(2, question.getVotes());
    question.decrementVotes();
    EXPECT_EQ(1, question.getVotes());

    EXPECT_FALSE(question.getClosed());
    EXPECT_EQ(question_text, question.show());

}


TEST_F(TestMemoryLeakInteractions, CanAnswerQuestion)
{
    Question question(id1, t1, pmember, title1, description1, tags1);
    Answer answer(id2, t2, pmember2, text2);
    answer.setRightAnswer(true);
    answer.incrementVotes();

    question.addInteraction(&answer);
    std::vector<Interaction *> interactions = question.getInteractions();
    ASSERT_EQ(1, interactions.size());
    EXPECT_EQ(id2, interactions[0]->getId());
    EXPECT_EQ(pmember2, interactions[0]->getAuthor());
    EXPECT_EQ(question_with_answer_text, question.show());

    Interaction* removed_interaction = question.removeInteraction(id2);
    ASSERT_EQ(&answer, (Answer*)removed_interaction);
    interactions = question.getInteractions();
    ASSERT_EQ(0, interactions.size());
}

TEST_F(TestMemoryLeakInteractions, CanCommentQuestion)
{
    Question question(id1, t1, pmember, title1, description1, tags1);
    Comment comment(id3, t3, pmember2, text3);

    question.addInteraction(&comment);
    std::vector<Interaction *> interactions = question.getInteractions();
    ASSERT_EQ(1, interactions.size());
    EXPECT_EQ(id3, interactions[0]->getId());
    EXPECT_EQ(pmember2, interactions[0]->getAuthor());
    EXPECT_EQ(question_with_comment_text, question.show());

    Interaction* removed_interaction = question.removeInteraction(id3);
    ASSERT_EQ(&comment, (Comment*)removed_interaction);
    interactions = question.getInteractions();
    ASSERT_EQ(0, interactions.size());
}

