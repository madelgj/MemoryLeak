#include "MemberProfileInfo.hpp"

MemberProfileInfo::~MemberProfileInfo()
{

}

int MemberProfileInfo::getReputation() const
{
    return _reputation;
}

std::string MemberProfileInfo::getUsername() const
{
    return _username;
}

std::string MemberProfileInfo::getBio() const
{
    return _bio;
}

void MemberProfileInfo::setUsername(const std::string &username)
{
    _username = username;
}

void MemberProfileInfo::setBio(const std::string &bio)
{
    _bio = bio;
}

void MemberProfileInfo::decreaseReputation()
{
    if (_reputation > 0){
        _reputation -= 1;
    }
}

void MemberProfileInfo::increaseReputation()
{
    _reputation ++;
}

MemberProfileInfo::MemberProfileInfo()
{

}

MemberProfileInfo::MemberProfileInfo(const std::string &username, const std::string &bio)
{
    _username = username;
    _bio = bio;
    _reputation = 0;
}

