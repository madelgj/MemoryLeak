#ifndef INTERACTION_HPP
#define INTERACTION_HPP
#include<iostream>
#include "Member.hpp"

using namespace std;

class Interaction
{
public:
    Interaction(const int &id, const string &text, MemberProfileInfo* author,unsigned long time);
    virtual ~Interaction();

    int getId() const;
    void setId(const int &id);

    unsigned long getTime() const;
    void setTime(unsigned long time);

    string getText() const;
    void setText(const string &text);

    MemberProfileInfo *getAuthor() const;
    void setAuthor(MemberProfileInfo *author);

    virtual string show()=0;
    string getTyp();


protected:
    int _id;
    string _type;
    unsigned long int _time;
    string _text;
    MemberProfileInfo* _author;
};




#endif // INTERACTION_HPP
