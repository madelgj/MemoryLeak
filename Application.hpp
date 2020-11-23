#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <iostream>
#include <vector>
#include "Member.hpp"

using namespace std;

class Application
{
public:
    Application();
    ~Application();
    bool createMember(string username, string bio, string email, string password);
    bool login(string email, string password);
    bool isLogged();
    Member* getCurrentMember();
    bool eraseCurrentMember();
    bool logout();
    vector <MemberProfileInfo*> showMembers();
    MemberProfileInfo* showMember(string user);
    bool editEmail(string const email);
    bool editPassword(string const password);
    bool editUsername(string const username);
    bool editBio(string const bio);
private:
    vector<Member*> _members;
    int _currentMember;    //default no member is logged
};

#endif // APPLICATION_HPP
