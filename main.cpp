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
    manager.loadFromFile("..\dataFile.txt");
    int ps=0; //present state of machine
    while (ps!=-1) {
        switch (ps) {
        case 0:
            cout<<"Press the following for:\n\n";
            cout<<"\t 1)Log in\n\t 2)Sign up\n\t 3)Search questions by tag\n\t 4)See all questions\n";
            cin>>ps;
            if (ps==4){ps=5;}
            break;

        case 1: //Initial page
        {
            string email, password;
            cout<<"Please enter your email:\n";
            cin>>email;
            cout<<"Please enter your password:\n";
            cin>>password;
            if(manager.login(email,password)==1){
                cout<<"Hello!, welcome back" << manager.getCurrentMember()->getUsername() << "\n\n";
                ps=4;
            }
            else{
                cout << "/a/a/a/a/a/a/a/a/a/a/a";
                cout<<"Incorrect user or password!!\n\n";
                ps=1;
            }
            break;
        }

        case 2: //Sign in page
        {
            string user, password, email;
            cout<<"Please enter your desired username:\n\n";
            cin>>user;
            cout<<"Please enter your email:\n\n";
            cin>>email;
            cout<<"Please enter your desired password:\n\n";
            cin>>password;
            if(manager.createMember(user,"Empty field",email,password) == 1){
                cout<<"Congrats, your ccount has been successfully created!!\n";
                cout<<"Please remember to complete your bio in settings once you log in\n\n";
                ps=0;
            }
            else{
                cout << "/a/a/a/a/a/a/a/a/a/a/a";
                cout<<"Username already exist! \n\n";
                ps=2;
            }
            break;
        }

       case 3: // Show questions by tag
       {
           string tags;
           vector<Question*> QuestionSorted;
           int id,index;
           cout << "please introduce the tag of the questions you want to see\n\n";
           cin >> tags;
           QuestionSorted = manager.getQuestionsByTag(tags);

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
               cout << "/a/a/a/a/a/a/a/a/a/a/a";
               cout<<"ID does not match\n\n";
           }

           break;

        }
       case 4:  //Welcome page
        {
            manager.ClearScreen();
            cout<<"Press the following for:\n\n";
            cout<<"\t 1)Newly added questions\n\t 2)Ask a question\n\t 3)Account settings\n\t 4)My Questions\n\n\t 5)Logout\n\n\t 6)Restore/Create security copy";
            cin>>ps;
            ps+=3;
            break;
        }

        case 5: //Feed page
        {
            int id,index=-1;

            cout<<"Question feed:\n";
            cout<<" -- Type question id to interact with -- \n\n";
            vector <Question*> printQ = manager.getQuestions();
            for (unsigned long  a = 0;  a < printQ.size(); a++) {
                cout<<"\tID: "<<printQ[a]->getId();
                cout<<"\tTitle: "<<printQ[a]->getTitle();
            }
            cout<<"\n\n";
            cin>>id;

            for (unsigned long  a = 0;  a < printQ.size(); a++) {
                if(id==printQ[a]->getId()){
                    index=a;
                    a=printQ.size();
                }
            }

            if(index!=-1){
                printQ[index]->show();
            }

            else{
                cout<<"ID does not match\n\n";
            }

            break;
        }

       case 6:  //Add question page
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
            ps = 4;
            break;
        }

        case 7: //Edit account page
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
                 cout<<"Enter your new password\n";
                 cin>>password;
                 manager.getCurrentMember()->setPassword(password);
                 break;
             case 4:
                 cout<<"Enter your new bio\n";
                 cin>>bio;
                 manager.getCurrentMember()->setBio(bio);
                 break;
             case 5:
                 ps=4;
                 break;
             }
             break;
         }
         case 8:
        {
            manager.logout();
            manager.saveToFile("..\dataFile.txt");
            break;
        }
        case 9:
        {
            string adminPass;
            int option;
            cout << "You have to be an admin to do this. Please, enter the admin password\n\n";
            cin >> adminPass;
            if(adminPass == "Inform4tic4Uc3M!"){
                cout << "Welcome, admin " << manager.getCurrentMember()->getUsername() << "What do you want to do?\n\n\t 1)Create security copy\n\n\t 2)Restore security copy\n\n\t -1)Exit";
                switch (option) {
                case 1:
                {
                    if( manager.saveToFile("..\CopiadeSeguridad1.txt")){
                        cout << "Security copy successfully made\n";
                    } else {
                        cout << "/a/a/a/a/a/a/a/a/a/a/a";
                        cout << "File cannot be created\n";
                    }
                    ps=4;
                    break;
                }
                case 2:{
                    string filename;
                    cout << "Please enter the name of the file you want to restore.Please,be aware you will be logged out";
                    manager.logout();
                    if(!manager.loadFromFile(filename)){
                        cout << "/a/a/a/a/a/a/a/a/a/a/a";
                        cout << "copy cannot be restored";
                        ps = 4;
                    }else{
                        ps=0;
                    }

                    break;
                }
                case -1:{
                    ps=4;
                    break;
                }

                default:
                    break;
                }
            }

        }


        default:
            cout << "/a/a/a/a/a/a/a/a/a/a/a";
            cout << "No valid option, please enter again\n\n";
            ps=0;
        }
    }

    return 0;
}
