#include <gtest/gtest.h>
#include <time.h>
#include "../Member.hpp"
#include "../Application.hpp"
#include "../Question.hpp"
#include "../Interaction.hpp"
#include "../Comment.hpp"
#include "../Answer.hpp"

::testing::AssertionResult IsQuestionInVector(std::string title, std::vector<Question *> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
        if (v[i]->getTitle() == title)
            found = true;
        i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Question with title: " << title << " not in questions vector.";
}

// The fixture for testing class Foo.
class TestMemoryLeakInteractionIntegration : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TestMemoryLeakInteractionIntegration() {
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
    title2 = "How to do a recursive function";
    tags2 = {"programming"};

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

  ~TestMemoryLeakInteractionIntegration() override {
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
  std::string title2;
  std::string description1, description2, description3;
  std::vector<std::string> tags1, tags2;
  std::string question_text, question_with_comment_text, question_with_answer_text;
  std::string answer_text, answer_with_comment_text, comment_text;
  std::string email1, password1, name1, bio1;
  std::string email2, password2, name2, bio2;
  Member * member, *member2;
  MemberProfileInfo * pmember, *pmember2;

};

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanCreateQuestions)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_FALSE(manager.createQuestion(title1, description1, tags1)); //-- Cannot create publications if not logged in
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    ASSERT_TRUE(manager.createQuestion(title2, description2, tags2));

    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(2, questions.size());
    ASSERT_TRUE(IsQuestionInVector(title1, questions));
    ASSERT_TRUE(IsQuestionInVector(title2, questions));
    ASSERT_FALSE(IsQuestionInVector(text2, questions));
    ASSERT_NE(questions[0]->getId(), questions[1]->getId()); //-- Two questiosn cannot have the same id
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanFilterQuestionsByTag)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    ASSERT_TRUE(manager.createQuestion(title2, description2, tags2));

    std::vector<Question *> questions = manager.getQuestionsByTag("programming");
    ASSERT_EQ(2, questions.size());
    ASSERT_TRUE(IsQuestionInVector(title1, questions));
    ASSERT_TRUE(IsQuestionInVector(title2, questions));

    questions = manager.getQuestionsByTag("general");
    ASSERT_EQ(1, questions.size());
    ASSERT_TRUE(IsQuestionInVector(title1, questions));
    ASSERT_FALSE(IsQuestionInVector(title2, questions));

    questions = manager.getQuestionsByTag("cooking");
    ASSERT_EQ(0, questions.size());
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanVoteQuestions)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();

    ASSERT_TRUE(manager.logout());
    ASSERT_FALSE(manager.upvoteQuestion(question_id));  //-- Voting requires login first
    ASSERT_FALSE(manager.downvoteQuestion(question_id));  //-- Voting requires login first

    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.upvoteQuestion(question_id));  //-- Voting requires login first
    ASSERT_EQ(1, questions[0]->getVotes());
    Member * member = manager.getCurrentMember();
    ASSERT_EQ(1, member->getReputation());

    ASSERT_FALSE(manager.upvoteQuestion(question_id));  //-- Cannot vote twice the same question
    ASSERT_EQ(1, questions[0]->getVotes());
    ASSERT_EQ(1, member->getReputation());

    ASSERT_TRUE(manager.downvoteQuestion(question_id));  //-- But you can downvote it
    ASSERT_EQ(-1, questions[0]->getVotes());
    ASSERT_EQ(0, member->getReputation());  //-- Reputation is always >= 0
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanAnswerQuestions)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();

    ASSERT_TRUE(manager.logout());
    ASSERT_FALSE(manager.answerQuestion(question_id, text2));  //-- Answer requires login first

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));

    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    EXPECT_EQ(name1, answer->getAuthor()->getUsername());
    EXPECT_EQ(text2, answer->getText());
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanVoteAnswers)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));
    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    int answer_id = answer->getId();


    ASSERT_TRUE(manager.logout());
    ASSERT_FALSE(manager.upvoteAnswer(answer_id));  //-- Voting requires login first
    ASSERT_FALSE(manager.downvoteAnswer(answer_id));  //-- Voting requires login first

    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.upvoteAnswer(answer_id));  //-- Voting requires login first
    ASSERT_EQ(1, answer->getVotes());
    Member * member = manager.getCurrentMember();
    ASSERT_EQ(1, member->getReputation());

    ASSERT_FALSE(manager.upvoteAnswer(answer_id));  //-- Cannot vote twice the same answer
    ASSERT_EQ(1, answer->getVotes());
    ASSERT_EQ(1, member->getReputation());

    ASSERT_TRUE(manager.downvoteAnswer(answer_id));  //-- But you can downvote it
    ASSERT_EQ(-1, answer->getVotes());
    ASSERT_EQ(0, member->getReputation());  //-- Reputation is always >= 0
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanCloseQuestions)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();

    ASSERT_TRUE(manager.logout());
    ASSERT_FALSE(manager.closeQuestion(question_id)); //-- Cannot close questions if not logged in

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_FALSE(manager.closeQuestion(question_id)); //-- Cannot close questions if you are not the owner
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.closeQuestion(question_id)); //-- Cannot close questions if not logged in
    ASSERT_TRUE(questions[0]->getClosed());
    ASSERT_FALSE(manager.answerQuestion(question_id, text2)); //-- Closed questions do not accept answers
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanAcceptAnswers)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));
    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    int answer_id = answer->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_FALSE(manager.acceptAnswer(answer_id));  //-- Accept answer requires login first

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_FALSE(manager.acceptAnswer(answer_id));  //-- Only question owner can accept the answer
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.acceptAnswer(answer_id));
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(answer->getRightAnswer());
    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_EQ(1, manager.getCurrentMember()->getReputation());  //-- An accepted answer increases author's reputation by 1
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanCommentQuestions)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();

    ASSERT_TRUE(manager.logout());
    ASSERT_FALSE(manager.comment(question_id, text3));  //-- Comment requires login first

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.comment(question_id, text3));

    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Comment* comment = dynamic_cast<Comment*>(interactions[0]);
    ASSERT_TRUE(comment);
    EXPECT_EQ(name1, comment->getAuthor()->getUsername());
    EXPECT_EQ(text3, comment->getText());
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCannotCommentComments)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();

    ASSERT_TRUE(manager.comment(question_id, text3));

    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Comment* comment = dynamic_cast<Comment*>(interactions[0]);
    ASSERT_TRUE(comment);
    ASSERT_FALSE(manager.comment(comment->getId(), text2)); //-- Comments cannot be commented
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanCommentAnswers)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.login(email1, password1));

    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));

    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    int answer_id = interactions[0]->getId();

    ASSERT_TRUE(manager.logout());
    ASSERT_FALSE(manager.comment(answer_id, text3));  //-- Comment requires login first

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.comment(answer_id, text3));

    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    std::vector<Comment*> comments = answer->getComments();
    ASSERT_EQ(1, comments.size());
    EXPECT_EQ(name1, comments[0]->getAuthor()->getUsername());
    EXPECT_EQ(text3, comments[0]->getText());
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanRemoveQuestions)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();
    Question* q = questions[0];
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.createQuestion(title2, description2, tags2));
    questions = manager.getQuestions();
    ASSERT_EQ(2, questions.size());
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));
    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    int answer_id = answer->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_FALSE(manager.deleteQuestion(question_id));  //-- Deleting questions requires login first

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_FALSE(manager.deleteQuestion(question_id));  //-- Deleting can only be done by author
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.deleteQuestion(question_id));

    questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    ASSERT_NE(q, questions[0]);
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanModifyQuestions)
{
    std::string new_description="This is the new description.";
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();
    Question* q = questions[0];
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.createQuestion(title2, description2, tags2));
    questions = manager.getQuestions();
    ASSERT_EQ(2, questions.size());
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));
    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    int answer_id = answer->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_FALSE(manager.modifyQuestion(question_id, new_description));  //-- Modifying questions requires login first

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_FALSE(manager.modifyQuestion(question_id, new_description));  //-- Only author can modify a question
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.modifyQuestion(question_id, new_description));
    ASSERT_EQ(new_description, q->getDescription());
}

TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanRemoveInteractions)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.createQuestion(title2, description2, tags2));
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));
    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    int answer_id = answer->getId();
    ASSERT_TRUE(manager.comment(question_id, text3));
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.comment(answer_id, text3));
    Comment* c1 = dynamic_cast<Comment*>(answer->getComments()[0]);
    ASSERT_TRUE(c1);
    int comment_id = c1->getId();
    ASSERT_TRUE(manager.logout());


    ASSERT_FALSE(manager.deleteInteraction(comment_id));  //-- Deleting interactions requires login first

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_FALSE(manager.deleteInteraction(comment_id));  //-- Deleting can only be done by author
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.deleteInteraction(comment_id));
    ASSERT_EQ(0, answer->getComments().size());
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.deleteInteraction(answer_id));
    interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    ASSERT_NE(answer, interactions[0]);
    ASSERT_TRUE(manager.logout());
}


TEST_F(TestMemoryLeakInteractionIntegration, ApplicationCanModifyInteractions)
{
    std::string new_text1="This is the new text for answers";
    std::string new_text2="This is the new text for comments";

    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int question_id = questions[0]->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.createQuestion(title2, description2, tags2));
    ASSERT_TRUE(manager.answerQuestion(question_id, text2));
    std::vector<Interaction*> interactions = questions[0]->getInteractions();
    ASSERT_EQ(1, interactions.size());
    Answer* answer = dynamic_cast<Answer*>(interactions[0]);
    ASSERT_TRUE(answer);
    int answer_id = answer->getId();
    ASSERT_TRUE(manager.comment(question_id, text3));
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.comment(answer_id, text3));
    Comment* c1 = dynamic_cast<Comment*>(answer->getComments()[0]);
    ASSERT_TRUE(c1);
    int comment_id = c1->getId();
    ASSERT_TRUE(manager.logout());


    ASSERT_FALSE(manager.modifyInteraction(comment_id, new_text2));  //-- Modifying interactions requires login first

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_FALSE(manager.modifyInteraction(comment_id, new_text2));  //-- Modifying can only be done by author
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.modifyInteraction(comment_id, new_text2));
    ASSERT_EQ(new_text2, c1->getText());
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.modifyInteraction(answer_id, new_text1));
    ASSERT_EQ(new_text1, answer->getText());
    ASSERT_TRUE(manager.logout());
}
