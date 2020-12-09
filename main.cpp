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

        We help you get answers to your toughest coding questions, and find your next dream job.

)";

//    Application manager;
//    int ps=0; //present state of machine
//    int ns;//next state of machine
//    string user, password;

//    while (ps!=-1) {
//        switch (ps) {
//        case 0:
//            cout<<"Press the following for:\n\n";
//            cout<<"\t 1)Log in\n\t 2)Sign up\n\n";
//            cin>>ns;
//            break;

//        case 1:
//            cout<<"Please enter your username:\n";
//            cin>>user;
//            cout<<"Please enter your password:\n";
//            cin>>password;
//            if(manager.login(user,password)==1){
//                cout<<"Hello!, welcome back\n\n" << manager.getCurrentMember()->getUsername() << "\n\n";
//                ns=3;
//            }
//            else{
//                cout<<"Incorrect user or password!!\n";
//                ns=1;
//            }
//            break;

//        case 2:
//            cout<<"Please enter your desired username:\n\n";
//            cin>>user;
//            cout<<"Please enter your desired password:\n\n";
//            cin>>password;
//            if(manager.createMember(user,"","",password) == 1){
//                cout<<"Congrats, your ccount has been successfully created!!\n";
//                cout<<"Please remember to complete your account info in settings once you log in\n\n";
//                ns=1;
//            }
//            else{
//                cout<<"Username already exist! \n\n";
//                ns=2;
//            }
//            break;

//        default:
//            cout<<"No valid option, please enter again\n\n";
//            ns=ps;
//        }
//     ps=ns;
//    }

    return 0;
}
