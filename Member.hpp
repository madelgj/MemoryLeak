#ifndef MEMBER_HPP
#define MEMBER_HPP
#include <iostream>
#include <vector>
#include "MemberLoginInfo.hpp"
#include "MemberProfileInfo.hpp"

using namespace std;
class Member : public MemberProfileInfo, public MemberLoginInfo
{
public:
    Member(string username,string bio,string email,string password);
    ~Member();

    bool hasUpvoted(const int &id) ;
    void setUpvoted(const int &upvoted);
    void removeUpvoted(const int &upvoted);

    bool hasDownvoted(const int &id);
    void setDownvoted(const int &downvoted);
    void removeDownvoted(const int &downvoted);

private:
    vector<int> _upvoted;
    vector<int> _downvoted;
};

#endif // MEMBER_HPP
