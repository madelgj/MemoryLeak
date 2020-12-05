#include "Comment.hpp"

Comment::Comment(const int &id, unsigned long time, MemberProfileInfo* author, const string &text) : Interaction(id,text,author,time)
{
    _type = "Comment";
}

string Comment::show()
{
    stringstream ss;
    ss << '\t' << "Comment:" << endl;
    ss << '\t' << _id << " - " << _time << " - " << _author->getUsername() << ":" << endl;
    ss << '\t' << _text;

    return ss.str();
}

bool Comment::is(){
    return false;
}
