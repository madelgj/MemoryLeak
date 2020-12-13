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
    _questions.clear();
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
    delete _members.at(_currentMember);
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
    //map --> vector de pares
    //funcion q devuelva un vector de id de todas las question o answer o comments
    // setMasterId para meter id de la pregunta/respuesta a la q corresponda

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
        if(!_questions[questionIndex]->getClosed()){
            unsigned long time = 10;
            _id++;
            _questions[questionIndex]->addInteraction(new Answer(_id,time,(MemberProfileInfo*)getCurrentMember(),answerText));
            return true;
        }
    }
    return false;
}

bool Application::comment(const int &idQA, const string &commentText)
{
    if (!isLogged()){
        return false;
    }
    unsigned long time = 10;
    int questionIndex = questionExists(idQA);
    // the id corresponds to a question
    if (questionIndex != -1){
        _id++;
        _questions[questionIndex]->addInteraction(new Comment(_id,time,(MemberProfileInfo*)getCurrentMember(),commentText));
        return true;
    }

    Interaction* answerToComment = interactionExists(idQA);
    if(answerToComment!=nullptr){

        if(dynamic_cast <Answer*> (answerToComment) != nullptr){
            Answer* targetAnswer = dynamic_cast<Answer*>(answerToComment);
            _id++;
            targetAnswer->addComment(new Comment(_id,time,(MemberProfileInfo*)getCurrentMember(),commentText));
            return true;
        }
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
        // we check if it's the author
        if(_questions[questionIndex]->getAuthor()->getUsername()==_members[_currentMember]->getUsername()){
            _questions[questionIndex]->setClosed(true);
            return true;
        }
    }
    return false;
}

bool Application::acceptAnswer(const int &idAnswer)
{
    if (!isLogged()){
        return false;
    }
    // we check if the id corresponds to any interaction
    Interaction* answerToClose = interactionExists(idAnswer);
    if(answerToClose!= nullptr && answerToClose->getTyp()=="Answer"){
        int index = interactionIndex(idAnswer);
        // check if is the question's author
        if (_questions[index]->getAuthor()->getUsername()==_members[_currentMember]->getUsername()){
            Answer* targetAnswer = (Answer*) answerToClose;
            answerToClose->getAuthor()->increaseReputation();
            targetAnswer->setRightAnswer(true);
            return true;
        }
    }
    return false;
}

vector<Question *> Application::getQuestions()
{
    return _questions;
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
    // we check if the user has already upvoted this question
    if(_members[_currentMember]->hasUpvoted(idAnswer)){
        return false;
    }

    Interaction* answerToVote = interactionExists(idAnswer);
    if (answerToVote != nullptr && answerToVote->getTyp()=="Answer"){
        Answer* targetAnswer = (Answer*) answerToVote;
        if(_members[_currentMember]->hasDownvoted(idAnswer)){
            _members[_currentMember]->removeDownvoted(idAnswer);
            targetAnswer->incrementVotes();
        }
        targetAnswer->incrementVotes();
        targetAnswer->getAuthor()->increaseReputation();
        _members[_currentMember]->setUpvoted(idAnswer);

        return true;
    }
    return false;
}

bool Application::downvoteAnswer(const int &idAnswer)
{
    if (!isLogged()){
        return false;
    }
    if(_members[_currentMember]->hasDownvoted(idAnswer)){
        return false;
    }

    Interaction* answerToVote = interactionExists(idAnswer);
    // we check if the answer exists
    if (answerToVote != nullptr && answerToVote->getTyp()=="Answer"){
        Answer* targetAnswer = (Answer*) answerToVote;
        if(_members[_currentMember]->hasUpvoted(idAnswer)){
            _members[_currentMember]->removeUpvoted(idAnswer);
            targetAnswer->decrementVotes();
        }
        targetAnswer->decrementVotes();
        targetAnswer->getAuthor()->decreaseReputation();
        _members[_currentMember]->setDownvoted(idAnswer);
        return true;
    }
    return false;

}

bool Application::upvoteQuestion(const int &idQuestion)
{
    if (!isLogged()){
        return false;
    }

    int questionIndex = questionExists(idQuestion);
    if (questionIndex == -1){
        return false;
    }

    if(_members[_currentMember]->hasUpvoted(idQuestion)){
        return false;
    }

    if(_members[_currentMember]->hasDownvoted(idQuestion)){
        _members[_currentMember]->removeDownvoted(idQuestion);
        _questions[questionIndex]->incrementVotes();

    }

    _members[_currentMember]->setUpvoted(idQuestion);
    _questions[questionIndex]->incrementVotes();
    _questions[questionIndex]->getAuthor()->increaseReputation();
    return true;
}

bool Application::downvoteQuestion(const int &idQuestion)
{
    if (!isLogged()){
        return false;
    }

    int questionIndex = questionExists(idQuestion);
    if (questionIndex == -1){
        return false;
    }

    if(_members[_currentMember]->hasDownvoted(idQuestion)){
        return false;
    }

    if(_members[_currentMember]->hasUpvoted(idQuestion)){
        _members[_currentMember]->removeUpvoted(idQuestion);
        _questions[questionIndex]->decrementVotes();
    }

    _questions[questionIndex]->decrementVotes();
    _members[_currentMember]->setDownvoted(idQuestion);
    _questions[questionIndex]->getAuthor()->decreaseReputation();
    return true;
}

bool Application::deleteQuestion(const int &idQuestion)
{
    if (!isLogged()){
        return false;
    }
    int questionIndex = questionExists(idQuestion);
    if (questionIndex != -1){
        // we check if it's the question's author
        if(_questions[questionIndex]->getAuthor()->getUsername()==_members[_currentMember]->getUsername()){
            delete _questions[questionIndex];
            _questions.erase(_questions.begin() + questionIndex);
            return true;
        }
    }
    return false;
}

bool Application::deleteInteraction(const int &idInteraction)
{
    if (!isLogged()){
        return false;
    }
    for(unsigned long a=0; a<_questions.size();a++){ //we check in all questions
        vector <Interaction*> delInt = _questions[a]->getInteractions();//we get all interactions in each question
        for(unsigned long b=0;b<delInt.size();b++){ // we check if the id corresponds to any interaction
            if (delInt[b]->getId()==idInteraction && delInt[b]->getAuthor()==_members[_currentMember]){
                _questions[a]->removeInteraction(idInteraction);
                return true;
            }
            if(delInt[b]->getTyp()=="Answer"){//if the interaction is an answer, we check for all comments inside
                vector <Comment*> delCom = dynamic_cast <Answer*> (delInt[b])->getComments();
                for (int c = 0; c < delCom.size(); c++){
                    if((delCom[c]->getId() == idInteraction) && (delCom[c]->getAuthor() == _members[_currentMember])){
                        dynamic_cast<Answer*>(_questions[a]->getInteractions().at(b))->removeComment(idInteraction);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Application::modifyQuestion(const int &idQuestion, const string &newDescription)
{ //only author can modify
    if (!isLogged()){
        return false;
    }

    int questionIndex = questionExists(idQuestion);
    if (questionIndex != -1){
        // we see if the person trying to modify it is the author
        if(_questions[questionIndex]->getAuthor()->getUsername() == _members[_currentMember]->getUsername() ){
            _questions[questionIndex]->setDescription(newDescription);
            return true;
        } else {
            return false;
        }
    } else{
        return false;
    }
}

bool Application::modifyInteraction(const int &idInteraction, const string &newText)
{
    if (!isLogged()){
        return false;
    }
    Interaction* interactionToChange = interactionExists(idInteraction);
    if(interactionToChange->getAuthor()->getUsername()==_members[_currentMember]->getUsername()){
        if(interactionToChange != nullptr){
            interactionToChange -> setText(newText);
            return true;
        }
    }
    return false;

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

Interaction* Application::interactionExists(const int &idInteraction){
    Interaction* answerToClose;
    for (unsigned long i=0;i<_questions.size();i++){     // the id corresponds to an interaction
        answerToClose = _questions[i]->exists(idInteraction);
        if (answerToClose != nullptr){
            return answerToClose;
        }
    }
    return answerToClose;
}

int Application::interactionIndex(const int &idInteraction){
    Interaction* answerToClose;
    for (unsigned long i=0;i<_questions.size();i++){     // the id corresponds to an interaction
        answerToClose = _questions[i]->exists(idInteraction);
        if (answerToClose != nullptr){
            return i;
        }
    }
    return -1;
}

bool Application::saveToFile(const string &filename)
{
    ofstream dataFile;
    vector<Interaction*> interacciones;
    vector<Comment*> comments;
    vector<string> tagsToSave;
    Comment* commentToSave;
    Answer* AnswerToSave;
    dataFile.open(filename);

    if(dataFile.is_open()){

        // we save the info of all members
        for(unsigned long i=0;i<_members.size();i++){
            dataFile << "Member:\n";
            dataFile << _members[i]->getUsername() << '\n';
            dataFile << _members[i]->getBio() << '\n';
            dataFile << _members[i]->getEmail() << '\n';
            dataFile << _members[i]->getPassword() << '\n';
            dataFile << _members[i]->getReputation() << '\n';
        }
        // we save the info of all questions
        for (unsigned long i=0;i<_questions.size();i++){
            dataFile << "Question:\n";
            dataFile << _questions[i]->getId() << '\n';
            dataFile << _questions[i]->getTitle() << '\n';
            dataFile << _questions[i]->getDescription() << '\n';
            tagsToSave =  _questions[i]->getTags();
          //  dataFile << tagsToSave[0];
            dataFile << _questions[i]->getTags()[0];
//            for (unsigned long j=1;j<tagsToSave.size();j++){
//                dataFile << "," << tagsToSave[j];
//            }
            for(unsigned long j=1;j<_questions[i]->getTags().size();j++){
                dataFile << ","<< _questions[i]->getTags()[j];
            }
            dataFile << '\n';
            dataFile << _questions[i]->getTime() << '\n';
            dataFile << _questions[i]->getAuthor()->getUsername() << '\n';
            dataFile << _questions[i]->getVotes() << '\n';
            if (_questions[i]->getClosed()){
                dataFile << "1\n";
            } else{
                dataFile << "0\n";
            }
            // we save the info of all interactions within the questions
            interacciones = _questions[i]->getInteractions();
            for(unsigned long k=0;k<_questions[i]->getInteractions().size();k++){
                AnswerToSave = dynamic_cast<Answer*>(interacciones[k]);
                if(AnswerToSave != nullptr){
                    dataFile << "Answer:" << '\n';
                    dataFile << AnswerToSave->getId() << '\n';
                    dataFile << AnswerToSave->getTime() << '\n';
                    dataFile << AnswerToSave->getAuthor()->getUsername() << '\n';
                    dataFile << AnswerToSave->getVotes() << '\n';
                    if(AnswerToSave->getRightAnswer()){
                        dataFile << "1" << '\n';
                    }else{
                        dataFile << "0" << '\n';
                    }
                    dataFile << AnswerToSave->getText() << '\n';
                    comments = AnswerToSave->getComments();

                    // we save the info of all comments within an answer
                    for(unsigned long l=0;l<comments.size();l++){
                        dataFile << "AnsComment:" << '\n';
                        dataFile << comments[l]->getId() << '\n';
                        dataFile << comments[l]->getTime() << '\n';
                        dataFile << comments[l]->getAuthor()->getUsername() << '\n';
                        dataFile << comments[l]->getText() << '\n';
                    }

                }else{

                    commentToSave = dynamic_cast<Comment*>(interacciones[k]);
                    if(commentToSave!= nullptr){
                        dataFile << "Comment:" << '\n';
                        dataFile << commentToSave->getId() << '\n';
                        dataFile << commentToSave->getTime() << '\n';
                        dataFile << commentToSave->getAuthor()->getUsername() << '\n';
                        dataFile << commentToSave->getText() << '\n';
                    }
                }
            }
        }
    }
    return true;
}

bool Application::loadFromFile(const string &filename)
{
    ifstream dataFile(filename);
    string currentLine;
    string username,bio,email,password,title,text,tag,description,id,reputation,votes,closed,rightAnswer,time;
    vector<string> tags;
    unordered_map<int, bool> questions_closed;

    if(dataFile.is_open()){

        while(getline(dataFile,currentLine)){
            if(currentLine == "Member:"){
                getline(dataFile,username);
                getline(dataFile,bio);
                getline(dataFile,email);
                getline(dataFile,password);
                getline(dataFile,reputation);
                createMember(username,bio,email,password);
                for(int i=0;i<stoi(reputation);i++){
                    _members.back()->increaseReputation();
                }
            }

            if(currentLine == "Question:"){
                cout << "Creating a question: " <<  endl;
                tags.clear();
                getline(dataFile,id);
                cout << "question id: "<< id << endl;
                getline(dataFile,title);
                getline(dataFile,description);
                getline(dataFile,tag);
                getline(dataFile,time);
                getline(dataFile,username);
                getline(dataFile,votes);
                getline(dataFile,closed);

                string parseTags;
                for(unsigned long i=0;i<tag.size();i++){
                    if (tag[i] != ','){
                        parseTags+=tag[i];
                    } else{
                        tags.push_back(parseTags);
                        parseTags.clear();
                    }
                }
                tags.push_back(parseTags);
                parseTags.clear();

                for(unsigned long j=0;j<_members.size();j++){
                    if(_members[j]->getUsername()==username){
                        login(_members[j]->getEmail(),_members[j]->getPassword());
                    }
                }
                createQuestion(title,description,tags);
                _questions.back()->setId(stoi(id));
                _questions.back()->setTime(stoul(time));
                _questions.back()->setClosed(false);
                if(closed=="0"){ // the question is still open
                    questions_closed[stoi(id)] = false;
                }else{
                    questions_closed[stoi(id)] = true;

                }
                if (stoi(votes)>0){
                   for(int i=0;i<stoi(votes);i++){
                        _questions.back()->incrementVotes();
                    }
                } else {
                    for(int i=0;i>stoi(votes);i--){
                         _questions.back()->decrementVotes();
                     }
                }
                logout();

            }
            if(currentLine == "Answer:"){
                getline(dataFile,id);
                getline(dataFile,time);
                getline(dataFile,username);
                getline(dataFile,votes);
                getline(dataFile,rightAnswer);
                getline(dataFile,text);
                for(unsigned long j=0;j<_members.size();j++){
                    if(_members[j]->getUsername()==username){
                        login(_members[j]->getEmail(),_members[j]->getPassword());
                    }
                }
                answerQuestion(_questions.back()->getId(),text);
                dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->setId(stoi(id));
                dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->setTime(stoul(time));

                //dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->getAuthor()->setUsername(username);
                if(rightAnswer == "0"){
                    dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->setRightAnswer(false);
                } else{
                    dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->setRightAnswer(true);
                }
                if (stoi(votes)>0){
                   for(int i=0;i<stoi(votes);i++){
                        dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->incrementVotes();
                   }
                } else {
                    for(int i=0;i>stoi(votes);i--){
                        dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->decrementVotes();
                     }
                }

                logout();
                cout << "answer created"<<  endl;

            }


            if(currentLine == "Comment:"){
                cout << "ccreating comment"<< endl;
                getline(dataFile,id);
                getline(dataFile,time);
                getline(dataFile,username);
                getline(dataFile,text);
                for(unsigned long j=0;j<_members.size();j++){
                    if(_members[j]->getUsername()==username){
                        login(_members[j]->getEmail(),_members[j]->getPassword());
                    }
                }
                comment(_questions.back()->getId(),text);
                dynamic_cast<Comment*>(_questions.back()->getInteractions().back())->setTime(stoul(time));
                dynamic_cast<Comment*>(_questions.back()->getInteractions().back())->setId(stoi(id));
                dynamic_cast<Comment*>(_questions.back()->getInteractions().back())->getAuthor()->setUsername(username);
                logout();
                cout << "comment created"<<endl;
            }

            if(currentLine == "AnsComment:"){
                cout << "creating answcoment"<< endl;
                getline(dataFile,id);
                getline(dataFile,time);
                getline(dataFile,username);
                getline(dataFile,text);
                for(int i=0;i<_members.size();i++){
                    if(_members[i]->getUsername()==username){
                        login(_members[i]->getEmail(),_members[i]->getPassword());
                        dynamic_cast<Answer*>(_questions.back()->getInteractions().back())->addComment(new Comment(stoi(id),stoul(time),(MemberProfileInfo*)_members[i],text));
                    }
                }

                logout();
                cout << "answcomment created" << endl;
            }

         }
        for (unsigned long i=0;i<_questions.size();i++){
           int questionId = _questions[i]->getId();
           if (questions_closed[questionId]){
               _questions[i]->setClosed(true);
           }
        }
        dataFile.close();
    }
    return true;
}

void Application::ClearScreen()
{
    cout << string( 100, '\n' );
}


