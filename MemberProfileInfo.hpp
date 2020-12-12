#ifndef MEMBERPROFILEINFO_HPP
#define MEMBERPROFILEINFO_HPP
#include <iostream>

using namespace std;
class MemberProfileInfo
{
public:
    ~MemberProfileInfo();
    //getters & setters
    int getReputation() const;
    string getUsername() const;
    string getBio() const;
    void setUsername(const string &username);
    void setBio(const string &bio);

    //methods
    void decreaseReputation();
    void increaseReputation();

private:
    MemberProfileInfo();

protected:
   MemberProfileInfo(const string &username, const string &bio);
   string _username;
   string _bio;
   int _reputation;
};

#endif // MEMBERPROFILEINFO_HPP
