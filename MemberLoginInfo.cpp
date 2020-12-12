#include "MemberLoginInfo.hpp"

string MemberLoginInfo::getPassword() const
{
    return _password;
}

void MemberLoginInfo::setEmail(const string &email)
{
    _email = email;
}

void MemberLoginInfo::setPassword(const string &password)
{
    _password = password;
}

string MemberLoginInfo::getEmail() const
{
    return _email;
}

MemberLoginInfo::MemberLoginInfo(const string &email, const string &password)
{
    _email = email;
    _password = password;
}

MemberLoginInfo::MemberLoginInfo()
{

}
