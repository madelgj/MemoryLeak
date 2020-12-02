#include "Member.hpp"

Member::Member(std::string username, std::string bio, std::string email, std::string password): MemberProfileInfo (username,bio), MemberLoginInfo (email,password)
{

}

Member::~Member()
{
    _upvoted.clear();
    _downvoted.clear();
}

bool Member::hasUpvoted(const int &id)
{
    for (unsigned long i=0;i<_upvoted.size();i++){
        if(_upvoted[i] == id){
            return true;
        }
    }
    return false;
}

void Member::setUpvoted(const int &upvoted)
{
    _upvoted.push_back(upvoted);
}

void Member::removeUpvoted(const int &upvoted)
{
    for(unsigned long i=0;i<_upvoted.size();i++){
        if(_upvoted[i] == upvoted){
            _upvoted.erase(_upvoted.begin() + i);
        }
    }
}

bool Member::hasDownvoted(const int &id)
{
    for (unsigned long i=0;i<_downvoted.size();i++){
        if(_downvoted[i] == id){
            return true;
        }
    }
    return false;
}
void Member::setDownvoted(const int &downvoted)
{
    _downvoted.push_back(downvoted);
}

void Member::removeDownvoted(const int &downvoted)
{
    for(unsigned long i=0;i<_downvoted.size();i++){
        if(_downvoted[i] == downvoted){
            _downvoted.erase(_downvoted.begin() + i);
        }
    }
}
