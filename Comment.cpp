#include "Comment.hpp"

Comment::Comment(const int &id, unsigned long time, MemberProfileInfo* author, const string &text) : Interaction(id,text,author,time)
{
    _type = "Comment";
}

Comment::~Comment()
{}

string Comment::show()
{
    stringstream ss;
    ss << '\t' << "Comment:" << '\n';
    ss << '\t' << _id << " - " << _time << " - " << _author->getUsername() << ":" << '\n';
    ss << '\t' << _text;

    return ss.str();
}


