#include "Comment.hpp"

Comment::Comment(const int &id, const string &text, MemberProfileInfo* author,unsigned long time) : Interaction(id,text,author,time)
{}

string Comment::show()
{
    stringstream ss;
    ss << '\t' << "Comment:" << endl;
    ss << '\t' << _id << " - " << _time << " - " << _author << endl;
    ss << '\t' << _text << endl;

    return ss.str();
}
