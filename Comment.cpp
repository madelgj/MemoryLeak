#include "Comment.hpp"

Comment::Comment(const int &id, const string &text, MemberProfileInfo* author, const unsigned long &time)
{
    _id = id;
    _text = text;
    _time = time;
    _author = author;
}

string Comment::show()
{
    stringstream ss;
    ss << '\t' << "Comment:" << endl;
    ss << '\t' << _id << " - " << _time << " - " << _author << endl;
    ss << '\t' << _text << endl;

    return ss.str();
}
