#include <iostream>
#include <vector>
#include "Application.hpp"



using namespace std;

int main()
{
    cout<< R"(
           /$$      /$$                                                             /$$                           /$$
           | $$$    /$$$                                                            | $$                          | $$
           | $$$$  /$$$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$   /$$$$$$  /$$   /$$      | $$        /$$$$$$   /$$$$$$ | $$   /$$
           | $$ $$/$$ $$ /$$__  $$| $$_  $$_  $$ /$$__  $$ /$$__  $$| $$  | $$      | $$       /$$__  $$ |____  $$| $$  /$$/
           | $$  $$$| $$| $$$$$$$$| $$ \ $$ \ $$| $$  \ $$| $$  \__/| $$  | $$      | $$      | $$$$$$$$  /$$$$$$$| $$$$$$/
           | $$\  $ | $$| $$_____/| $$ | $$ | $$| $$  | $$| $$      | $$  | $$      | $$      | $$_____/ /$$__  $$| $$_  $$
           | $$ \/  | $$|  $$$$$$$| $$ | $$ | $$|  $$$$$$/| $$      |  $$$$$$$      | $$$$$$$$|  $$$$$$$|  $$$$$$$| $$ \  $$
           |__/     |__/ \_______/|__/ |__/ |__/ \______/ |__/       \____  $$      |________/ \_______/ \_______/|__/  \__/
                                                                     /$$  | $$
                                                                    |  $$$$$$/
                                                                     \______/

           ------------------------------------------------------------------------------------------------------------------

           We help you get answers to your toughest coding questions, and find your next dream job!.

           )";

    Application manager;
    manager.createMember("admin","admin","admin","admin");
    manager.loadFromFile("../dataFile.txt");
    int ps=0; //present state of machine
    int selectedQuestion;

    enum States
    {
        initial,
        logIn,
        signIn,
        showTag,
        welcome,
        feed,
        addQuestion,
        editAccount,
        logOut,
        backUp,
        myQuestions,
        feedID,

    };

    while (ps!=-2) {
        switch (ps)
        {

        case initial: //Initial page
            cout<<"Press the following for:\n\n";
            cout<<"\t 1)Log in\n\t 2)Sign up\n\t 3)Search questions by tag\n\t 4)See all questions\n";
            cin>>ps;

            switch(ps){
            case 1:
                ps=logIn;
                break;
            case 2:
                ps=signIn;
                break;
            case 3:
                ps=showTag;
                break;
            case 4:
                ps=feed;
                break;
            default:
                ps=initial;
                cout<<"No valid option, please enter again\n\n";
            }

            break;

        case logIn: //Log in
        {
            string email, password;
            int exit;
            cout<<"Please enter your email:\n";
            cin>>email;
            cout<<"Please enter your password:\n";
            cin>>password;
            if(manager.login(email,password)==1){
                cout<<"Hello!, welcome back " << manager.getCurrentMember()->getUsername() << "\n\n";
                ps=welcome;
            }
            else{
                cout<<"Incorrect user or password!!\n\n\t Enter -1 to exit.";
                cin  >> exit;
                if(exit == -1){
                    ps=initial;
                }else {
                    ps=logIn;
                }
            }
            break;
        }

        case signIn: //Sign in page
        {
            string user, password, email;
            int exit;
            cout<<"Please enter your desired username:\n\n";
            cin>>user;
            cout<<"Please enter your email:\n\n";
            cin>>email;
            cout<<"Please enter your desired password, it must contain at least a capital letter, a number and a special character:\n\n";
            cin>>password;
            if(manager.createMember(user,"Empty field",email,password) == 1 && manager.checkPassword(password)==1){
                cout<<"Congrats, your account has been successfully created!!\n";
                cout<<"Please remember to complete your bio in settings once you log in\n\n";
                ps=initial;
            }
            else{
                cout<<"Username already exist or password is incomplete! Please try again or enter -1 to exit\n\n";
                cin>>exit;
                if(exit==-1){
                    ps=initial;
                } else{
                    ps=signIn;
                }
            }
            break;
        }

        case showTag: // Show questions by tag
        {
            string tags;
            vector<Question*> QuestionSorted;
            int id,index;
            cout << "please introduce the tag of the questions you want to see\n\n";
            cin >> tags;
            QuestionSorted = manager.getQuestionsByTag(tags);
            if (!QuestionSorted.empty()){
                cout<<"Question feed:\n";
                cout<<" -- Type question id to interact with -- \n\n";
                for (int  a = 0;  a < QuestionSorted.size(); a++) {
                    cout<<"\tID: "<<QuestionSorted[a]->getId();
                    cout<<"\tTitle: "<<QuestionSorted[a]->getTitle();
                }
                cout<<"\n\n";
                cin>>id;

                for (unsigned long  a = 0;  a < QuestionSorted.size(); a++) {
                    if(id==QuestionSorted[a]->getId()){
                        index=a;
                        a=QuestionSorted.size();
                    }
                }

                if(index!=-1){
                    QuestionSorted[index]->show();
                }

                else{
                    cout<<"ID does not match\n\n";
                }

            } else {
                cout << "Sorry, we have no question with that tag at the moment, but you might create one yourself!\n\n";
                ps = initial;
            }

            break;

        }

        case welcome:  //Welcome page
        {
            cout<<"Press the following for:\n\n";
            cout<<"\t 1)Newly added questions\n\t 2)Ask a question\n\t 3)Account settings\n\t 4)My Questions\n\t 5)Logout\n";
            if(manager.getCurrentMember()->getUsername()=="admin"){
                cout<<"\t 6)Backup settings\n";
            }
            cin>>ps;
            switch(ps){
            case 1:
                ps=feed;
                break;
            case 2:
                ps=addQuestion;
                break;
            case 3:
                ps=editAccount;
                break;
            case 4:
                ps=myQuestions;
                break;
            case 5:
                ps=logOut;
                break;
            case 6:
                if(manager.getCurrentMember()->getUsername()=="admin"){
                    ps=backUp;
                    break;
                }
            default:
                ps=welcome;
                cout<<"No valid option, please enter again\n\n";
            }
            break;
        }

        case feed: //Feed page
        {
            int id,option,index=-1;
            if(!manager.getQuestions().empty()){
                cout<<"Question feed:\n";
                vector <Question*> printQ = manager.getQuestions();
                for (unsigned long  a = 0;  a < printQ.size(); a++) {
                    cout<<"\tID: "<<printQ[a]->getId();
                    cout<<"\tTitle: "<<printQ[a]->getTitle();
                }
                cout<<"\n\n";
                if(manager.isLogged()==true){
                    cout<<" -- Type question id to interact with -- \n\n";
                    cin>>id;
                    for (unsigned long  a = 0;  a < printQ.size(); a++) {
                        if(id==printQ[a]->getId()){
                            selectedQuestion=a;
                            a=printQ.size();
                            ps=feed;
                        }
                        else{
                            cout<<"ID does not match\n\n";
                        }
                    }
                }
                cout<<"Type -1 to return";
                cin>>option;
                if(option=-1){
                    ps=initial;
                    break;
                }
                break;
            } else {
                cout << "We have no questions at the moment!Please be the first one to create one\n\n";
                ps=initial;
                break;
            }
        }

        case addQuestion:  //Add question page
        {
            string title, description, tag;
            vector <string> tags;
            cout << "Please enter your question title\n";
            cin >> title;
            cout << "Please enter your question description\n";
            cin >> description;
            cout << "Please enter your question tags, enter * to indicate you are done\n";
            cin >> tag;
            tags.push_back(tag);
            while(tag != "*"){
                cout << "Please enter another tag: \n";
                cin >> tag;
                if(tag!="*"){ tags.push_back(tag); }
            }
            cout<<"\n";
            manager.createQuestion(title,description,tags);
            ps = welcome;
            break;
        }

        case editAccount: //Edit account page
        {
            int edit;
            string username,email,password,bio;
            cout<<"Press the following to edit:\n\n";
            cout<<"\t1)Username: "<<manager.getCurrentMember()->getUsername()<<"\n";
            cout<<"\t2)Email: "<<manager.getCurrentMember()->getEmail()<<"\n";
            cout<<"\t3)Password "<<manager.getCurrentMember()->getPassword()<<"\n";
            cout<<"\t4)Bio: "<<manager.getCurrentMember()->getBio()<<"\n";
            cout<<"\t5)Go back to main menu\n\n";
            cin>>edit;
            switch(edit){
            case 1:
                cout<<"Enter your new username\n";
                cin>>username;
                manager.getCurrentMember()->setUsername(username);
                break;
            case 2:
                cout<<"Enter your new email\n";
                cin>>email;
                manager.getCurrentMember()->setEmail(email);
                break;
            case 3:
                cout<<"Please enter your new password, it must contain at least a capital letter, a number and a special character:\n\n";
                cin>>password;
                if(manager.checkPassword(password)!=1){
                    cout<<"The entered password does not contain all the required fields\n\n";
                    ps=editAccount;
                    break;
                }
                manager.getCurrentMember()->setPassword(password);
                break;
            case 4:
                cout<<"Enter your new bio\n";
                cin>>bio;
                manager.getCurrentMember()->setBio(bio);
                break;
            case 5:
                ps=welcome;
                break;
            }
            break;
        }

        case myQuestions: //My questions page, we didn have time to implement this page
        {

        }

        case logOut:    //Logout
        {
            manager.logout();
            manager.saveToFile("../dataFile.txt");
            ps=initial;
            break;
        }

        case backUp: //Backup page
        {
            int option;
            cout<<"What do you want to do?\n\n\t 1)Create security copy\n\n\t 2)Restore security copy\n\n\t -1)Exit\n\n";
            cin>>option;
            switch (option) {
            case 1:
            {
                if( manager.saveToFile("../CopiadeSeguridad1.txt")){
                    cout << "Security copy successfully made\n";
                } else {
                    cout << "File cannot be created\n";
                }
                ps=4;
                break;
            }
            case 2:{
                string filename;
                cout << "Please enter the name of the file you want to restore. Please,be aware you will be logged out\n";
                manager.logout();
                if(!manager.loadFromFile(filename)){
                    cout << "copy cannot be restored";
                    ps = welcome;
                }
                else{
                    ps = initial;
                }

                break;
            }
            case -1:{
                ps = welcome;
                break;
            }

            default:
                break;
            }
        }

        case feedID:
        {
            int option;
            vector <Question*> printQ = manager.getQuestions();
            printQ[selectedQuestion]->show();
            cout<<"Press the following for:\n\n";
            cout<<"\t 1)Upvote Question|Answer\n\t 2)Downvote Question|Answer\n\t 3)Comment Question|Answer\n";
            if(manager.getCurrentMember()->getUsername()==printQ[selectedQuestion]->getAuthor()->getUsername()){
                cout<<"\t 4)Close question\n";
            }
            cin>>option;

            switch(option){
            case 1:
            {
                int id;
                cout<<"Enter Question|Answer ID";
                cin>>id;
                vector <Interaction*> interactions = printQ[selectedQuestion]->getInteractions();
                if (printQ[selectedQuestion]->getId() == id){
                    printQ[selectedQuestion]->incrementVotes();
                    ps=feedID;
                    break;
                }

                for(int a=0; a<interactions.size(); a++){
                    if(dynamic_cast <Answer*> (interactions[a])!= NULL && interactions[a]->getId()==id){
                        dynamic_cast <Answer*> (interactions[a])->incrementVotes();
                        ps=feedID;
                        break;
                    }
                }
                cout<<"ID does not match any answer or question\n\n";
                break;
            }
            case 2:
            {
                int id;
                cout<<"Enter Question|Answer ID";
                cin>>id;
                vector <Interaction*> interactions = printQ[selectedQuestion]->getInteractions();
                if (printQ[selectedQuestion]->getId() == id){
                    printQ[selectedQuestion]->decrementVotes();
                    ps=feedID;
                    break;
                }

                for(int a=0; a<interactions.size(); a++){
                    if(dynamic_cast <Answer*> (interactions[a])!= NULL && interactions[a]->getId()==id){
                        dynamic_cast <Answer*> (interactions[a])->decrementVotes();
                        ps=feedID;
                        break;
                    }
                }
                cout<<"ID does not match any answer or question\n\n";
                break;
            }
            case 3:
            {
                int id;
                cout<<"Enter Question|Answer ID";
                cin>>id;
                vector <Interaction*> interactions = printQ[selectedQuestion]->getInteractions();
                if (printQ[selectedQuestion]->getId() == id){
                    string comment;
                    cout<<"Please enter text to comment\n\n";
                    cin>>comment;
                    manager.comment(id,comment);
                    ps=feedID;
                    break;
                }

                for(int a=0; a<interactions.size(); a++){
                    if(dynamic_cast <Answer*> (interactions[a])!= NULL && interactions[a]->getId()==id){
                        string comment;
                        cout<<"Please enter text to comment\n\n";
                        cin>>comment;
                        manager.comment(id,comment);
                        ps=feedID;
                        break;
                    }
                }
                cout<<"ID does not match any answer or question\n\n";
                break;
            }
            case 4:
            {
                int id;
                cout<<"Enter Question|Answer ID";
                cin>>id;
                vector <Interaction*> interactions = printQ[selectedQuestion]->getInteractions();

                for(int a=0; a<interactions.size(); a++){
                    if(dynamic_cast <Answer*> (interactions[a])!= NULL && interactions[a]->getId()==id){
                        dynamic_cast <Answer*> (interactions[a])->setRightAnswer(true);
                        printQ[selectedQuestion]->setClosed(true);
                        break;
                    }
                }
                cout<<"ID does not match any answer or question\n\n";
                break;
            }
          }
        }

        default:
            cout << "Error 404, redirecting to home page\n\n";
            ps=initial;
        }
    }
    return 0;
}
