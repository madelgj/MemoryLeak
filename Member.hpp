#ifndef MEMBER_HPP
#define MEMBER_HPP
#include <iostream>
#include "MemberLoginInfo.hpp"
#include "MemberProfileInfo.hpp"


class Member : public MemberProfileInfo, public MemberLoginInfo
{
public:
    Member(std::string username,std::string bio, std::string email, std::string password);
};

#endif // MEMBER_HPP
