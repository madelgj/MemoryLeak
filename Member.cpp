#include "Member.hpp"

Member::Member(std::string username, std::string bio, std::string email, std::string password): MemberProfileInfo (username,bio), MemberLoginInfo (email,password)
{

}
