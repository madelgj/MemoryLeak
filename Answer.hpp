#ifndef ANSWER_HPP
#define ANSWER_HPP
#include <iostream>
#include "Interaction.hpp"
#include <sstream>
#include <vector>
#include "Comment.hpp"

using namespace std;

class Answer : public Interaction
{
public:
    Answer(const int &id, const string &text, MemberProfileInfo* author,unsigned long time);

    void incrementVotes();
    void decrementVotes();

    void addComment(Comment* NewCom);
    Comment* removeComment(const int &id);
    vector<Comment *> getComments() const;

    bool getRight_answer() const;
    void setRight_answer(bool value);

    string show();

    int getVotes() const;

private:
    vector<Comment*> _comments;
    int _votes;
    bool right_answer;
};

#endif // ANSWER_HPP
