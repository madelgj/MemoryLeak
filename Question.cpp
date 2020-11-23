#include "Question.hpp"

Question::Question(int id,unsigned long int time,string author,string title,string description,vector <string> tags)
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

Interaction* Question::removeInteraction(int id)
{

}

string Question::show()
{

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
