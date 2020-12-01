#ifndef ANSWER_HPP
#define ANSWER_HPP
#include <iostream>
#include <sstream>
#include <vector>
#include "Comment.hpp"

using namespace std;

class Answer : public Interaction
{
public:
    Answer(const int &id,unsigned long time,MemberProfileInfo* author,const string &text);

    void incrementVotes();
    void decrementVotes();

    void addComment(Comment* NewCom);
    Comment* removeComment(const int &id);
    vector<Comment*> getComments() const;

    bool getRightAnswer() const;
    void setRightAnswer(bool value);

    string show();

    int getVotes() const;

private:
    vector<Comment*> _comments;
    int _votes;
    bool right_answer;
};

#endif // ANSWER_HPP
