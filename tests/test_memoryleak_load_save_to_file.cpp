#include <gtest/gtest.h>
#include <time.h>
#include "../Member.hpp"
#include "../Application.hpp"
#include "../Question.hpp"
#include "../Interaction.hpp"
#include "../Comment.hpp"
#include "../Answer.hpp"
#include <fstream>
#include <sstream>

::testing::AssertionResult IsMemberInFile(Member m, std::string filename)
{
    //-- Open file
    std::ifstream f(filename);
    if (!f.is_open() || !f.good())
        return ::testing::AssertionFailure() << "Could not open file: " << filename;

    bool flag = false;
    while (!flag && !f.eof())
    {
        std::string l;
        std::getline(f, l);
        if (l == "Member:")
        {
            //-- Read data
            std::string n, b, e, p;
            int r = -1;
            std::getline(f, n);
            std::getline(f, b);
            std::getline(f, e);
            std::getline(f, p);
            f >> r;

            //-- Check data
            if (e == m.getEmail() &&
                p == m.getPassword() &&
                n == m.getUsername() &&
                b == m.getBio() &&
                r == m.getReputation())
            {
                flag = true;
            }
        }
    }

    f.close();
    if (flag)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Member: " << m.getUsername() << " not in file.";
}

::testing::AssertionResult IsQuestionInFile(Question question, std::string filename)
{
    //-- Open file
    std::ifstream file(filename);
    if (!file.is_open() || !file.good())
        return ::testing::AssertionFailure() << "Could not open file: " << filename;

    //-- Look for correct keyword
    bool found = false;
    while (!found && !file.eof())
    {
        std::string line;
        std::getline(file, line);
        if (line == "Question:")
        {
            //-- Read data
            int id, votes, closed;
            unsigned long time = -1;
            std::string title, description, username;
            std::string tagsline;
            std::stringstream ss;

            std::getline(file, line);
            ss << line;
            ss >> id;
            ss.clear();
            std::getline(file, title);
            std::getline(file, description);
            std::getline(file, tagsline);
            std::getline(file, line);
            ss << line;
            ss >> time;
            ss.clear();
            std::getline(file, username);
            std::getline(file, line);
            ss << line;
            ss >> votes;
            ss.clear();
            std::getline(file, line);
            ss << line;
            ss >> closed;
            ss.clear();

            //-- Check data
            if (id == question.getId() &&
                //time == question.getTime() &&  //-- This should be uncommented
                username == question.getAuthor()->getUsername() &&
                title == question.getTitle() &&
                description == question.getDescription() &&
                votes == question.getVotes() &&
                closed == question.getClosed())
            {
                std::stringstream ss2(tagsline);
                std::vector<std::string> v;
                std::vector<std::string> tags = question.getTags();

                std::string s;
                while (std::getline(ss2, s, ',')) {
                    v.push_back(s);
                }

                bool found2 = true;
                if (v.size() == tags.size())
                {
                   for (int i=0; i<v.size(); i++)
                       if (v[i] != tags[i])
                       {
                           found2 = false;
                           break;
                       }
                }
                else
                    found2=false;

                found = found2;
            }

            //-- Check interactions
            std::vector<Interaction*> interactions = question.getInteractions();
            for (int i=0; i<interactions.size(); i++)
            {
                //-- Answers
                Answer* aux_ans = dynamic_cast<Answer*>(interactions[i]);
                if (aux_ans != nullptr)
                {
                    std::string line;
                    std::getline(file, line);
                    if (line == "Answer:")
                    {
                        //-- Read data
                        int id, votes, accepted;
                        unsigned long time = -1;
                        std::string text, username;
                        std::stringstream ss;

                        std::getline(file, line);
                        ss << line;
                        ss >> id;
                        ss.clear();
                        std::getline(file, line);
                        ss << line;
                        ss >> time;
                        ss.clear();
                        std::getline(file, username);
                        std::getline(file, line);
                        ss << line;
                        ss >> votes;
                        ss.clear();
                        std::getline(file, line);
                        ss << line;
                        ss >> accepted;
                        ss.clear();
                        std::getline(file, text);

                        //-- Check data
                        if (id == aux_ans->getId() &&
                            //time == aux_ans->getTime() &&  //-- This should be uncommented
                            username == aux_ans->getAuthor()->getUsername() &&
                            text == aux_ans->getText() &&
                            votes == aux_ans->getVotes() &&
                            accepted == aux_ans->getRightAnswer())
                        {
                            found = true;
                        }

                    }
                    else{
                        found=false;
                        break;
                    }

                    //-- Check comments in answer
                    std::vector<Comment*> comments = aux_ans->getComments();
                    for (int j=0; j<comments.size(); j++)
                    {
                        std::string line;
                        std::getline(file, line);
                        if (line == "AnsComment:")
                        {
                            //-- Read data
                            int id;
                            unsigned long time = -1;
                            std::string text, username;
                            std::stringstream ss;

                            std::getline(file, line);
                            ss << line;
                            ss >> id;
                            ss.clear();
                            std::getline(file, line);
                            ss << line;
                            ss >> time;
                            ss.clear();
                            std::getline(file, username);
                            std::getline(file, text);

                            //-- Check data
                            if (id == comments[j]->getId() &&
                                //time == comments[j]->getTime() &&  //-- This should be uncommented
                                username == comments[j]->getAuthor()->getUsername() &&
                                text == comments[j]->getText())
                            {
                                found = true;
                            }

                        }
                        else{
                            found=false;
                            break;
                        }
                    }

                }

                //-- Comments
                Comment* aux_comment = dynamic_cast<Comment*>(interactions[i]);
                if (aux_comment != nullptr)
                {
                    std::string line;
                    std::getline(file, line);
                    if (line == "Comment:")
                    {
                        //-- Read data
                        int id;
                        unsigned long time = -1;
                        std::string text, username;
                        std::stringstream ss;

                        std::getline(file, line);
                        ss << line;
                        ss >> id;
                        ss.clear();
                        std::getline(file, line);
                        ss << line;
                        ss >> time;
                        ss.clear();
                        std::getline(file, username);
                        std::getline(file, text);

                        //-- Check data
                        if (id == aux_comment->getId() &&
                            //time == aux_comment->getTime() &&  //-- This should be uncommented
                            username == aux_comment->getAuthor()->getUsername() &&
                            text == aux_comment->getText())
                        {
                            found = true;
                        }

                    }
                    else{
                        found=false;
                        break;
                    }
                }
            }


        }
    }

    file.close();
    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Question with id: " << question.getId() << " not in file.";

}

::testing::AssertionResult IsQuestionInVector(Question q, std::vector<Question*> v)
{
    bool found = false;
    int i = 0;
    while (!found && i < v.size() )
    {
      if ( v[i]->getId() == q.getId() &&
           v[i]->getTitle() == q.getTitle() &&
           v[i]->getDescription() == q.getDescription() &&
           v[i]->getVotes() == q.getVotes() &&
           v[i]->getClosed() == q.getClosed() &&
           //v[i]->getTime() == q.getTime() &&
           v[i]->getAuthor()->getUsername() == q.getAuthor()->getUsername())
      {
          bool found2 = true;
          std::vector<std::string> q_tags = q.getTags();
          std::vector<std::string> v_tags = v[i]->getTags();
          if (v_tags.size() == q_tags.size())
          {
             for (int j=0; j<v_tags.size(); j++)
                 if (v_tags[j] != q_tags[j])
                 {
                     found2 = false;
                     break;
                 }
          }
          else
              found2=false;

          found = found2;

          //-- Check interactions
          bool found3 = true;
          std::vector<Interaction*> q_interactions = q.getInteractions();
          std::vector<Interaction*> v_interactions = v[i]->getInteractions();
          if (q_interactions.size() == v_interactions.size())
              for (int j = 0; j < q_interactions.size(); j++)
              {
                  Answer* q_ans = dynamic_cast<Answer*>(q_interactions[j]);
                  Answer* v_ans = dynamic_cast<Answer*>(v_interactions[j]);
                  if (q_ans != nullptr && v_ans != nullptr)
                  {
                      if (q_ans->getId() == v_ans->getId() &&
                          //q_ans->getTime() == v_ans->getTime() &&  //-- This should be uncommented
                          q_ans->getAuthor()->getUsername() == v_ans->getAuthor()->getUsername() &&
                          q_ans->getText() == v_ans->getText() &&
                          q_ans->getVotes() == v_ans->getVotes() &&
                          q_ans->getRightAnswer() == v_ans->getRightAnswer())
                      {
                          //-- Check anscomments
                          bool found4 = true;
                          std::vector<Comment*> q_comments = q_ans->getComments();
                          std::vector<Comment*> v_comments = v_ans->getComments();
                          if (q_comments.size() == v_comments.size())
                          {
                              for(int k=0; k < q_comments.size(); k++)
                                  if (q_comments[k]->getId() == v_comments[k]->getId() &&
                                      //q_comments[k]->getTime() == v_comments[k]->getTime() &&  //-- This should be uncommented
                                      q_comments[k]->getAuthor()->getUsername() == v_comments[k]->getAuthor()->getUsername() &&
                                      q_comments[k]->getText() == v_comments[k]->getText())
                                  {
                                      found4 = true;
                                  }
                                  else
                                  {
                                      found4 = false;
                                      break;
                                  }

                              found3 = found4;
                              if (!found3)
                                  break;
                            }
                            else
                            {
                              found3 = false;
                              break;
                            }
                      }
                      else
                      {
                          found3 = false;
                          break;
                      }


                  }
                  else
                  {
                      Comment* q_comment = dynamic_cast<Comment*>(q_interactions[j]);
                      Comment* v_comment = dynamic_cast<Comment*>(v_interactions[j]);
                      if (q_comment != nullptr && v_comment != nullptr)
                      {
                          if (q_comment->getId() == v_comment->getId() &&
                              //q_comment->getTime() == v_comment->getTime() &&  //-- This should be uncommented
                              q_comment->getAuthor()->getUsername() == v_comment->getAuthor()->getUsername() &&
                              q_comment->getText() == v_comment->getText())
                          {
                              found3 = true;
                          }
                          else
                          {
                              found3 = false;
                              break;
                          }
                      }
                      else
                      {
                          found3 = false;
                          break;
                      }
                  }


              }
          else
              found3=false;

          found = found && found3;

      }
      i++;
    }

    if (found)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Question with id: " << q.getId() << " not in questions vector.";
}


class TestMemoryLeakLoadSaveToFile : public ::testing::Test {
 protected:

  TestMemoryLeakLoadSaveToFile()
  {
    //-- Some text for the app contents
    title1 = "How do I use this app?";
    description1 = "I'm new and I don't know how to use this. Please help.";
    tags1 = {"programming", "newbie", "general"};
    title2 = "How to do a recursive function";
    description2 = "I really need to know this or I will fail.";
    tags2 = {"programming"};
    title3 = "How can I install QtCreator?";
    description3 = "I'm trying to install it but it keeps asking for my email.";
    tags3 = {"programming", "IDEs"};

    answer1_text = "You just kind of did use it.";
    answer2_text = "You add questions and other people answers them.";
    answer3_text = "You can do it from the command line in Linux";
    comment1_text = "How to do a recursive function";
    comment2_text = "I should have used StackOverflow...";


    //-- Define test members
    email1 = "email@domain.com";
    password1 = "1234";
    name1 = "illuminator42";
    bio1 = "Guardian of the answer to life and everything elsee";

    email2 = "otheremail@domain.com";
    password2 = "member2pass";
    name2 = "totalNoob";
    bio2 = "It's my first day here";

    email3 = "fakeemail@domain.com";
    password3 = "member3pass";
    name3 = "theThird";
    bio3 = "I'm here just to test stuff";
  }


  int id1, id2, id3;
  time_t t1, t2, t3;
  std::string title1, title2, title3;
  std::string description1, description2, description3;
  std::vector<std::string> tags1, tags2, tags3;
  std::string answer1_text, answer2_text, answer3_text;
  std::string comment1_text, comment2_text;
  std::string email1, password1, name1, bio1;
  std::string email2, password2, name2, bio2;
  std::string email3, password3, name3, bio3;
};

TEST_F(TestMemoryLeakLoadSaveToFile, ApplicationCanSaveState)
{
    Application manager;
    ASSERT_TRUE(manager.createMember(name1, bio1, email1, password1));
    ASSERT_TRUE(manager.createMember(name2, bio2, email2, password2));
    ASSERT_TRUE(manager.createMember(name3, bio3, email3, password3));

    //-- Add questions
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.createQuestion(title1, description1, tags1));
    std::vector<Question *> questions = manager.getQuestions();
    ASSERT_EQ(1, questions.size());
    int q1_id = questions[0]->getId();
    Question* q1 = questions[0];
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.createQuestion(title2, description2, tags2));
    questions = manager.getQuestions();
    ASSERT_EQ(2, questions.size());
    int q2_id = questions[1]->getId();
    ASSERT_NE(q1_id, q2_id);
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email3, password3));
    ASSERT_TRUE(manager.createQuestion(title3, description3, tags3));
    questions = manager.getQuestions();
    ASSERT_EQ(3, questions.size());
    int q3_id = questions[2]->getId();
    Question* q3 = questions[2];
    ASSERT_NE(q1_id, q3_id);
    ASSERT_NE(q2_id, q3_id);
    ASSERT_TRUE(manager.logout());


    //-- Add interactions
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.comment(q2_id, comment1_text));
    ASSERT_TRUE(manager.answerQuestion(q3_id, answer3_text));
    std::vector<Interaction *> interactions = q3->getInteractions();
    ASSERT_EQ(1, interactions.size());
    int a3_id = interactions[0]->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email3, password3));
    ASSERT_TRUE(manager.answerQuestion(q1_id, answer1_text));
    interactions = q1->getInteractions();
    ASSERT_EQ(1, interactions.size());
    int a1_id = interactions[0]->getId();
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(manager.answerQuestion(q1_id, answer2_text));
    ASSERT_TRUE(manager.comment(a3_id, comment2_text));
    ASSERT_TRUE(manager.logout());

    //-- Do a little more
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(manager.upvoteAnswer(a3_id));
    ASSERT_TRUE(manager.upvoteQuestion(q3_id));
    ASSERT_TRUE(manager.downvoteQuestion(q2_id));
    ASSERT_TRUE(manager.downvoteAnswer(a1_id));
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email3, password3));
    ASSERT_TRUE(manager.acceptAnswer(a3_id));
    ASSERT_TRUE(manager.closeQuestion(q3_id));
    ASSERT_TRUE(manager.logout());

    manager.saveToFile("test_file.txt");

    //-- Is member in file?
    ASSERT_TRUE(manager.login(email1, password1));
    ASSERT_TRUE(IsMemberInFile(*manager.getCurrentMember(), "test_file.txt"));
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    ASSERT_TRUE(IsMemberInFile(*manager.getCurrentMember(), "test_file.txt"));
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email3, password3));
    ASSERT_TRUE(IsMemberInFile(*manager.getCurrentMember(), "test_file.txt"));
    ASSERT_TRUE(manager.logout());

    //-- Is question in file?
    questions = manager.getQuestions();
    for (int i=0; i<questions.size(); i++)
    {
        ASSERT_TRUE(IsQuestionInFile(*questions[i], "test_file.txt"));
    }
}

TEST_F(TestMemoryLeakLoadSaveToFile, ApplicationCanLoadState)
{
    Application manager;
    ASSERT_TRUE(manager.loadFromFile("test_data.dat"));

    //-- Check members
    ASSERT_TRUE(manager.login(email1, password1));
    Member* current = manager.getCurrentMember();
    EXPECT_EQ(email1, current->getEmail());
    EXPECT_EQ(password1, current->getPassword());
    EXPECT_EQ(name1, current->getUsername());
    EXPECT_EQ(bio1, current->getBio());
    EXPECT_EQ(1, current->getReputation());
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email2, password2));
    current = manager.getCurrentMember();
    EXPECT_EQ(email2, current->getEmail());
    EXPECT_EQ(password2, current->getPassword());
    EXPECT_EQ(name2, current->getUsername());
    EXPECT_EQ(bio2, current->getBio());
    EXPECT_EQ(0, current->getReputation());
    ASSERT_TRUE(manager.logout());

    ASSERT_TRUE(manager.login(email3, password3));
    current = manager.getCurrentMember();
    EXPECT_EQ(email3, current->getEmail());
    EXPECT_EQ(password3, current->getPassword());
    EXPECT_EQ(name3, current->getUsername());
    EXPECT_EQ(bio3, current->getBio());
    EXPECT_EQ(0, current->getReputation());
    ASSERT_TRUE(manager.logout());

    //-- Assemble data by hand:
    Member test_member1(name1, bio1, email1, password1);
    test_member1.increaseReputation();
    Member test_member2(name2, bio2, email2, password2);
    Member test_member3(name3, bio3, email3, password3);

    //-- Check questions
    Question q1(0, 0, (MemberProfileInfo*)&test_member1, title1, description1, tags1);    
    Question q2(1, 0, (MemberProfileInfo*)&test_member2, title2, description2, tags2);
    q2.decrementVotes();
    Question q3(2, 0, (MemberProfileInfo*)&test_member3, title3, description3, tags3);
    q3.incrementVotes();
    q3.setClosed(true);

    Answer a1(5, 0, (MemberProfileInfo*)&test_member3, answer1_text);
    a1.decrementVotes();
    Answer a2(6, 0, (MemberProfileInfo*)&test_member2, answer2_text);
    Answer a3(4, 0, (MemberProfileInfo*)&test_member1, answer3_text);
    a3.incrementVotes();
    a3.setRightAnswer(true);

    Comment c1(3, 0, (MemberProfileInfo*)&test_member1, comment1_text);
    Comment c2(7, 0, (MemberProfileInfo*)&test_member2, comment2_text);

    q2.addInteraction(&c1);
    a3.addComment(&c2); //-- Not yet tested
    q1.addInteraction(&a1);
    q1.addInteraction(&a2);
    q3.addInteraction(&a3);

    std::vector<Question*> questions = manager.getQuestions();
    ASSERT_TRUE(IsQuestionInVector(q1, questions));
    ASSERT_TRUE(IsQuestionInVector(q2, questions));
    ASSERT_TRUE(IsQuestionInVector(q3, questions));
}
