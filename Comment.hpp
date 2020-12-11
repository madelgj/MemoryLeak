#ifndef COMMENT_HPP
#define COMMENT_HPP
#include "Interaction.hpp"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Comment : public Interaction
{
public:
    Comment(const int &id, unsigned long time, MemberProfileInfo* author, const string &text);
    ~Comment();
    string show();
    bool is();
};

#endif // COMMENT_HPP
