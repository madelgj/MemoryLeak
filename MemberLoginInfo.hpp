#ifndef MEMBERLOGININFO_HPP
#define MEMBERLOGININFO_HPP
#include<iostream>

using namespace std;
class MemberLoginInfo
{
public:

    //getters & setters
    string getPassword() const;
    void setEmail(const string &email);
    void setPassword(const string &password);
    string getEmail() const;

protected:
    string _email;
    string _password;
    MemberLoginInfo(const string &email, const string &password);

private:
    MemberLoginInfo();
};

#endif // MEMBERLOGININFO_HPP
