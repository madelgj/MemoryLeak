#include "MemberLoginInfo.hpp"

std::string MemberLoginInfo::getPassword() const
{
    return _password;
}

void MemberLoginInfo::setEmail(const std::string &email)
{
    _email = email;
}

void MemberLoginInfo::setPassword(const std::string &password)
{
    _password = password;
}

std::string MemberLoginInfo::getEmail() const
{
    return _email;
}

MemberLoginInfo::MemberLoginInfo(std::string email, std::string password)
{
    _email = email;
    _password = password;
}

MemberLoginInfo::MemberLoginInfo()
{

}
