#include "Question.hpp"
#include "Question.hpp"

Question::Question(int id,unsigned long int time,MemberProfileInfo* author,string title,string description,vector <string> tags)
{
    _id=id;
    _time=time;
    _author=author;
    _title=title;
    _description=description;
    _tags=tags;
    _votes=0;
    _closed=false;
}

Question::~Question()
{
    _interactions.clear();
    _tags.clear();
    _author=NULL;
}

void Question::incrementVotes()
{
    _votes++;
}

void Question::decrementVotes()
{
    _votes--;
}

void Question::addInteraction(Interaction* interaction)
{
    _interactions.push_back(interaction);
}

Interaction* Question::removeInteraction(const int &id)
{
  Interaction* removed;
  //auto it = find_if(_interactions.begin(),_interactions.end(),[&id](const Interaction& obj) {return obj.getId() == id;})
    for (unsigned long i=0;i<_interactions.size();i++){
        if(_interactions[i]->getId() == id){
            removed = _interactions[i];
            _interactions.erase(_interactions.begin() + i);
            return removed;
        }
    }
    return nullptr;
}

string Question::show()
{
    stringstream ss;
    ss << _id << " - " << _title << endl;
    ss << "-------" << endl;
    ss << "by " << _author << " on " << _time << endl;
    ss << " Tags: " << _tags[0];
    for (unsigned long i=1; i<_tags.size();i++){
        ss << " / " << _tags[i];
    }
    ss << endl;
    if (_closed == true){ // a lo mejor solo deberia aparecer true y false y no esto
        ss << "closed - ";
    } else{
        ss << "open - ";
    }
    ss << _votes << " votes" << endl;
    ss << "-------" << endl;
    ss << _description << endl;
    ss << "-------" << endl;
    if (_interactions[0] != nullptr){
        ss << _interactions[0]->show() << endl;
        for (unsigned long i=1; i<_interactions.size();i++){
            ss << "-" << endl;
            ss << _interactions[i]->show() << endl;
        }
        ss << "-------" << endl;
    }
    return ss.str();

}

int Question::getId()
{
    return _id;
}

void Question::setId(int id)
{
    _id=id;
}

string Question::getTitle()
{
    return _title;
}

void Question::setTitle(string title)
{
    _title=title;
}

string Question::getDescription()
{
    return _description;
}

void Question::setDescription(string description)
{
    _description=description;
}

vector <string> Question::getTags()
{
    return _tags;
}

void Question::setTags(vector <string> tags)
{
    _tags=tags;
}

unsigned long int Question::getTime()
{
    return _time;
}

void Question::setTime(unsigned long int time)
{
    _time=time;
}

MemberProfileInfo* Question::getAuthor()
{
    return _author;
}

void Question::setAuthor(MemberProfileInfo* author)
{
    _author=author;
}

bool Question::getClosed()
{
    return _closed;
}

void Question::setClosed(bool closed)
{
    _closed=closed;
}
