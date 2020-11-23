#include "Application.hpp"
using namespace std;

Application::Application()
{
    _currentMember = -1;
}

Application::~Application()
{
    _currentMember = -1;
    _members.clear();
}

bool Application::createMember(string username, string bio, string email, string password)
{
    for(unsigned long a=0; a<_members.size(); a++){
        if(_members[a]->getEmail()==email){
            return false;
        }
    }
    for(unsigned long a=0; a<_members.size(); a++){
        if(_members[a]->getUsername()==username){
            return false;
        }
    }
    _members.push_back(new Member(username,bio,email,password));
    return true;
}

bool Application::login(string email, string password)
{
    for(int a=0; a<_members.size(); a++){
        if (_members[a]->getEmail()==email && _currentMember==-1){
            if(_members[a]->getPassword()==password){
                _currentMember=a;
                return true;
            }
        }
    }
    return false;
}

bool Application::isLogged()
{
    if(_currentMember==-1){
        return false;
    }
    return true;
}

bool Application::logout()
{
    if(_currentMember==-1){
        return false;
    }
    _currentMember=-1;
    return true;
}

Member* Application::getCurrentMember()
{
    if(_currentMember==-1){
        return NULL;
    }
    return _members[_currentMember];
}

bool Application::eraseCurrentMember()
{
    if(_currentMember==-1){
        return false;
    }
    _members.erase(_members.begin()+_currentMember);
    _currentMember=-1;
    return true;
}

vector <MemberProfileInfo*> Application::showMembers()
{
    vector<MemberProfileInfo*> users;    //vector que guarda los datos que queremos obtener

    for (unsigned long i = 0; i < _members.size(); i++) {
        users.push_back((MemberProfileInfo*) _members[i]);
    }
    return users;
}

MemberProfileInfo* Application::showMember(string user)
{
    MemberProfileInfo* profile;
    profile=NULL;
    for (unsigned long a = 0; a < _members.size(); a++) {
        if(_members[a]->getUsername()==user){
            profile=(MemberProfileInfo*)_members[a];
        }
    }
    return profile;
}

bool Application::editEmail(string const email)
{
    for(unsigned long a=0; a<_members.size(); a++){
        if(_members[a]->getEmail()==email){
            return false;
        }
    }
    if(_currentMember==-1){
        return false;
    }
    _members[_currentMember]->setEmail(email);
    return true;
}

bool Application::editPassword(string const password)
{
    if(_currentMember==-1){
        return false;
    }
    _members[_currentMember]->setPassword(password);
    return true;
}

bool Application::editUsername(string const username)
{
    for(unsigned long a=0; a<_members.size(); a++){
        if(_members[a]->getUsername()==username){
            return false;
        }
    }
    if(_currentMember==-1){
        return false;
    }
    _members[_currentMember]->setUsername(username);
    return true;
}

bool Application::editBio(string const bio)
{
    if(_currentMember==-1){
        return false;
    }
    _members[_currentMember]->setBio(bio);
    return true;
}
