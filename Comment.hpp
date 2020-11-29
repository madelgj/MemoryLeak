#ifndef COMMENT_HPP
#define COMMENT_HPP
#include "Interaction.hpp"
#include "Answer.hpp"
#include "Application.hpp"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Comment : public Interaction
{
public:
    Comment(const int &id, const string &text, MemberProfileInfo *author, unsigned long time);
    string show();
};

#endif // COMMENT_HPP
