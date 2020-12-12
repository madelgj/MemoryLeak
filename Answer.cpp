#include "Answer.hpp"

Answer::Answer(const int &id,unsigned long time,MemberProfileInfo* author,const string &text): Interaction(id,text,author,time)
{
    _votes = 0;
    right_answer = false;
    _type = "Answer"; // each interaction has an attribute to specify the type of interaction it is
}

Answer::~Answer()
{
    _comments.clear();
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
    for (unsigned long i=0;i<_comments.size();i++){ // we check if the id matches any comment
        if(_comments[i]->getId() == id){
            removed = _comments[i];
            _comments.erase(_comments.begin() + i);
            return removed;
        }
    }
    return nullptr;
}

vector<Comment*>Answer::getComments()
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
    ss << '\t' << "Answer:" << '\n';
    ss << '\t' << _id << " - " << _time << " - " << _author->getUsername() << ":";
    if(right_answer){
        ss << "\naccepted";
    }
    else{
        ss << '\n';
    }
    ss <<" - " << _votes << " votes" << '\n';
    ss << '\t' << _text << '\n';
    ss << "\t--";
    for (unsigned long i=0; i<_comments.size();i++){
            ss << "\n\t" << _comments[i]->show() << "\n\t-";
        }
    return ss.str();

}

int Answer::getVotes() const
{
    return _votes;
}

