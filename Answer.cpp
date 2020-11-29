#include "Answer.hpp"

Answer::Answer(const int &id, const int &date, MemberProfileInfo* author, const string &text)
{
    _id = id;
    _time = date;
    _author = author;
    _text = text;
    _votes = 0;
    right_answer = false;
}

void Answer::incrementVotes()
{

}

void Answer::decrementVotes()
{

}

void Answer::addComment(Comment *NewCom)
{

}

Comment *Answer::removeComment(const int &id)
{

}

Comment *Answer::getComments() const
{
    return _comments;
}

bool Answer::getRight_answer() const
{
    return right_answer;
}

void Answer::setRight_answer(bool value)
{
    right_answer = value;
}

void Answer::show()
{
    stringstream ss;
    ss << '\t' << "Answer:" << endl;
    ss << '\t' << _id << " - " << _time << " - " << _author << ":" << endl;
    if (_id == 3) {
        // accept answer
        ss << "accepted";
    }
    ss << " - " << _votes << "votes" << endl;
    ss << '\t' << _text << endl;
    ss << '\t' << "----------------------";
    if (_comments[0] != nullptr){
        ss << _comments[0]->show() << endl;
        for (unsigned long i=1; i<_comments.size();i++){
            ss << "-" << endl;
            ss << _comments[i]->show() << endl;
        }
        ss << "-------" << endl;
    }

    return ss.str();

}
