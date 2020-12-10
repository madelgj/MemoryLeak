#include "Interaction.hpp"

Interaction::Interaction(const int &id, const string &text, MemberProfileInfo* author,unsigned long time){
    _id = id;
    _text = text;
    _author = author;
    _time = time;
    _type = "Interaction";
}

Interaction::~Interaction()
{}

unsigned long Interaction::getTime() const
{
    return _time;
}

void Interaction::setTime(unsigned long time)
{
    _time = time;
}

string Interaction::getText() const
{
    return _text;
}

void Interaction::setText(const string &text)
{
    _text = text;
}

MemberProfileInfo *Interaction::getAuthor() const
{
    return _author;
}

void Interaction::setAuthor(MemberProfileInfo *author)
{
    _author = author;
}

string Interaction::getTyp()
{
    return _type;
}

int Interaction::getId() const
{
    cout << "the id is: " << _id << endl << flush;
    return _id;
}

void Interaction::setId(const int &id)
{
    _id = id;
}
