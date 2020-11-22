#ifndef MEMBERLOGININFO_HPP
#define MEMBERLOGININFO_HPP
#include<iostream>

class MemberLoginInfo
{
public:

    //getters & setters publicos o protected?
    std::string getPassword() const;
    void setEmail(const std::string &email);
    void setPassword(const std::string &password);
    std::string getEmail() const;

protected:
    std::string _email;
    std::string _password;

    MemberLoginInfo(std::string email, std::string password);

private:
    MemberLoginInfo();
};

#endif // MEMBERLOGININFO_HPP
