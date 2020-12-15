#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <iostream>
#include <vector>
#include "Member.hpp"
#include "Question.hpp"
#include "Comment.hpp"
#include "Answer.hpp"
#include <fstream>
#include <sstream>
#include <unordered_map>


using namespace std;

class Application
{
public:
    Application();
    ~Application();

// methods regarding the user
    bool createMember(string username, string bio, string email, string password);
    bool login(string email, string password);
    bool isLogged();
    Member* getCurrentMember();
    bool eraseCurrentMember();
    bool logout();
    vector <MemberProfileInfo*> showMembers();
    MemberProfileInfo* showMember(string user);
    bool editEmail(string const email);
    bool editPassword(string const password);
    bool editUsername(string const username);
    bool editBio(string const bio);
    bool checkPassword(string &password);

// methods regarding the interactions

    // methods to create posts
    bool createQuestion(const string &title, const string &description, vector<string> tags);
    bool answerQuestion(const int &idQuestion, const string &answerText);
    bool comment(const int &idQA, const string &commentText);

    // methods to close posts
    bool closeQuestion(const int &idQuestion);
    bool acceptAnswer(const int &idAnswer);

    // methods to publicly access to questions
    vector<Question *> getQuestions();
    vector<Question *> getQuestionsByTag(const string &tag);

    // methods for voting
    bool upvoteAnswer(const int &idAnswer);
    bool downvoteAnswer(const int &idAnswer);
    bool upvoteQuestion(const int &idQuestion);
    bool downvoteQuestion(const int &idQuestion);

    // methods to delete posts
    bool deleteQuestion(const int &idQuestion);
    bool deleteInteraction(const int &idInteraction);

    // methods to modify posts
    bool modifyQuestion(const int &idQuestion,const string &newDescription);
    bool modifyInteraction(const int &idInteraction, const string &newText);

    // methods to find posts
    int questionExists(const int &idQuestion);
    Interaction* interactionExists(const int &idInteraction);
    int interactionIndex(const int &idInteraction);

    // methods to interact with the outside
    bool saveToFile(const string &filename);
    bool loadFromFile(const string &filename);

    void ClearScreen();


private:
    vector<Member*> _members;
    int _id;
    int _currentMember;
    vector<Question*> _questions;
    time_t _timer;
};

#endif // APPLICATION_HPP
