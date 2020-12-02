#ifndef MEMBER_HPP
#define MEMBER_HPP
#include <iostream>
#include <vector>
#include "MemberLoginInfo.hpp"
#include "MemberProfileInfo.hpp"


class Member : public MemberProfileInfo, public MemberLoginInfo
{
public:
    Member(std::string username,std::string bio, std::string email, std::string password);
    ~Member();

    bool hasUpvoted(const int &id) ;
    void setUpvoted(const int &upvoted);
    void removeUpvoted(const int &upvoted);

    bool hasDownvoted(const int &id);
    void setDownvoted(const int &downvoted);
    void removeDownvoted(const int &downvoted);

private:
    std::vector<int> _upvoted;
    std::vector<int> _downvoted;
};

#endif // MEMBER_HPP
