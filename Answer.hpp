#ifndef ANSWER_HPP
#define ANSWER_HPP
#include <iostream>
#include "Interaction.hpp"
#include "Comment.hpp"
#include <sstream>
#include <vector>

using namespace std;

class Answer : public Interaction
{
public:
    Answer(const int &id, const int &date, MemberProfileInfo* author, const string &text);

    void incrementVotes();
    void decrementVotes();

    void addComment(Comment* NewCom);
    Comment* removeComment(const int &id);
    Comment *getComments() const;

    bool getRight_answer() const;
    void setRight_answer(bool value);

    void show();

private:
    vector<Comment*> _comments;
    int _votes;
    bool right_answer;
};

#endif // ANSWER_HPP
