#include "Answer.hpp"

Answer::Answer(const int &id, const string &text, MemberProfileInfo* author,unsigned long time): Interaction(id,text,author,time)
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

bool Answer::getRight_answer() const
{
    return right_answer;
}

void Answer::setRight_answer(bool value)
{
    right_answer = value;
}

string Answer::show()
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

int Answer::getVotes() const
{
    return _votes;
}
