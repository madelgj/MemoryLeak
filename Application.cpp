#include "Application.hpp"
using namespace std;

Application::Application()
{
    _currentMember = -1;
    _id = 0;
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

bool Application::createQuestion(const string &title, const string &description, vector<string> tags)
{
    if (!isLogged()){
        return false;
    }
    _id++;

    unsigned long time = 10; //how to set time? I think we can set a random value
    _questions.push_back(new Question(_id,time,(MemberProfileInfo*)getCurrentMember(),title,description,tags));
    return true;
}

bool Application::answerQuestion(const int &idQuestion, const string &answerText)
{
    if (!isLogged()){
        return false;
    }
    int questionIndex = questionExists(idQuestion);
    // we check if the id provided corresponds to any question
    if (questionIndex == -1){
        return false;
    } else {
        unsigned long time = 10;
        _id++;
        _questions[questionIndex]->addInteraction(new Answer(_id,answerText,(MemberProfileInfo*)getCurrentMember(),time));
        return true;
    }
}

bool Application::comment(const int &idQA, const string &commentText)
{
    if (!isLogged()){
        return false;
    }
    int questionIndex = questionExists(idQA);
    // the id corresponds to a question
    if (questionIndex != -1){
        unsigned long time = 10;
        _id++;
        _questions[questionIndex]->addInteraction(new Comment(_id,commentText,(MemberProfileInfo*)getCurrentMember(),time));
        return true;
    }
    Interaction* answerToComment = interactionExists(idQA);
    //the id corresponds to an interaction
    if(answerToComment != nullptr){
        _id++;
        //how to use polimorfism?
        answerToComment->addComment(new Comment(_id,commentText,(MemberProfileInfo*)getCurrentMember(),time));
        return true;
    }
    return false;

}

bool Application::closeQuestion(const int &idQuestion)
{
    if (!isLogged()){
        return false;
    }
    int questionIndex = questionExists(idQuestion);
    if (questionIndex == -1){
        return false;
    } else{
        _questions[questionIndex]->setClosed(true);
        return true;
    }

}

bool Application::acceptAnswer(const int &idAnswer)
{
    if (!isLogged()){
        return false;
    }
    // we check if the id corresponds to any interaction
        // the id corresponds to an interaction --> how to know if its comment or answer?
    Interaction* answerToClose = interactionExists(idAnswer);
    if(answerToClose!= nullptr){
       answerToClose->getAuthor()->increaseReputation();
       return true;
    }
    return false;
}

vector<Question *> Application::getQuestions()
{
    return _questioidQAns;
}

vector<Question *> Application::getQuestionsByTag(const string &tag)
{
    vector<Question *> questionsWithTag;
    for(unsigned long i=0; i<_questions.size(); i++){
        if(_questions[i]->questionHasTag(tag)){
            questionsWithTag.push_back(_questions[i]);
        }
    }
    return questionsWithTag;
}

bool Application::upvoteAnswer(const int &idAnswer)
{
    if (!isLogged()){
        return false;
    }
    Interaction* answerToVote = interactionExists(idAnswer);
    if(answerToVote != nullptr){
        //polimorfism?
        *answerToVote->incrementVotes();
        return true;
    } else{
        return false;
    }

}

bool Application::downvoteAnswer(const int &idAnswer)
{
    if (!isLogged()){
        return false;
    }
    Interaction* answerToVote = interactionExists(idAnswer);
    if(answerToVote != nullptr){
        //polimorfism?
        *answerToVote->decrementVotes();
        return true;
    } else{
        return false;
    }

}

bool Application::upvoteQuestion(const int &idQuestion)
{
    if (!isLogged()){
        return false;
    }
    int questionIndex = questionExists(idQuestion);
    if (questionIndex == -1){
        return false;
    } else {
        _questions[questionIndex]->incrementVotes();
        return true;
    }


}

bool Application::downvoteQuestion(const int &idQuestion)
{
    if (!isLogged()){
        return false;
    }
    int questionIndex = questionExists(idQuestion);
    if (questionIndex == -1){
        return false;
    } else {
        _questions[questionIndex]->decrementVotes();
        return true;
    }

}

void Application::deleteQuestion(const int &idQuestion)
{
    int questionIndex = questionExists(idQuestion);
    if (questionIndex != -1){
        _questions.erase(_questions.begin() + questionIndex);
    }
}

void Application::deleteInteraction(const int &idInteraction)
{
    int interactionToDelete = interactionIndex(idInteraction);
    if(interactionToDelete != -1){
        _questions[interactionToDelete]->removeInteraction(idInteraction);
        //why remove interaction returns a pointer?
    }
}

void Application::modifyQuestion(const int &idQuestion, const string &newDescription)
{
    int questionIndex = questionExists(idQuestion);
    if (questionIndex != -1){
        _questions[questionIndex]->setDescription(newDescription);
    }
}

void Application::modifyInteraction(const int &idInteraction, const string &newText)
{
    Interaction* interactionToChange = interactionExists(idInteraction);
    if(interactionToChange != nullptr){
        interactionToChange -> setText(newText);
    }
}

int Application::questionExists(const int &idQuestion)
{
    for (unsigned long i=0;i<_questions.size();i++){
        if(idQuestion == _questions[i]->getId()){
            return i;
        }
    }

    return -1;
}

Interaction *Application::interactionExists(const int &idInteraction){
    Interaction* answerToClose;
    for (unsigned long i=0;i<_questions.size();i++){     // the id corresponds to an interaction --> how to know if its comment or answer?
        answerToClose = _questions[i]->exists(idInteraction);
    }
    return answerToClose;

}
int Application::interactionIndex(const int &idInteraction){
    Interaction* answerToClose;
    for (unsigned long i=0;i<_questions.size();i++){     // the id corresponds to an interaction --> how to know if its comment or answer?
        answerToClose = _questions[i]->exists(idInteraction);
        if (answerToClose != nullptr){
            return i;
        }

    }
    return -1;
}
