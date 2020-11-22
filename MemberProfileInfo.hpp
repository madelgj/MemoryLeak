#ifndef MEMBERPROFILEINFO_HPP
#define MEMBERPROFILEINFO_HPP
#include <iostream>


class MemberProfileInfo
{
public:
    ~MemberProfileInfo();
    //getters & setters
    int getReputation() const;
    std::string getUsername() const;
    std::string getBio() const;
    void setUsername(const std::string &username);
    void setBio(const std::string &bio);

    //methods
    void decreaseReputation();
    void increaseReputation();

private:
    MemberProfileInfo();

protected:
   MemberProfileInfo(const std::string &username, const std::string &bio);
   std::string _username;
   std::string _bio;
   int _reputation;
};

#endif // MEMBERPROFILEINFO_HPP
