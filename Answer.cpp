#include "Answer.hpp"

Answer::Answer(const int &id,unsigned long time,MemberProfileInfo* author,const string &text): Interaction(id,text,author,time)
{
    _votes = 0;
    right_answer = false;
}

void Answer::incrementVotes()
{
    _votes++;
}

void Answer::decrementVotes()
{
    _votes--;
}

void Answer::addComment(Comment *NewCom)
{
    _comments.push_back(NewCom);
}

Comment *Answer::removeComment(const int &id)
{
    Comment* removed;
    for (unsigned long i=0;i<_comments.size();i++){
        if(_comments[i]->getId() == id){
            removed = _comments[i];
            _comments.erase(_comments.begin() + i);
            return removed;
        }
    }
    return nullptr;
}

vector<Comment *>Answer::getComments() const
{
    return _comments;
}

bool Answer::getRightAnswer() const
{
    return right_answer;
}

void Answer::setRightAnswer(bool value)
{
    right_answer = value;
}

string Answer::show()
{
    stringstream ss;
    ss << '\t' << "Answer:" << endl;
    ss << '\t' << _id << " - " << _time << " - " << _author->getUsername() << ":" << endl;
    ss << "accepted" << " - " << _votes << " votes" << endl;
    ss << '\t' << _text << endl;
    ss << '\t' << "--";
    for (unsigned long i=0; i<_comments.size();i++){
        if(i!=0){ ss << "-" << endl; }
            ss << _comments[i]->show() << endl;
        }
    return ss.str();
}

int Answer::getVotes() const
{
    return _votes;
}
