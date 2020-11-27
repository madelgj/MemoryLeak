#ifndef QUESTION_HPP
#define QUESTION_HPP
#include <iostream>
#include <vector>
#include "Member.hpp"
#include "Interaction.hpp"
#include <sstream>

using namespace std;

class Question
{
public:
    Question(int id,unsigned long int time,MemberProfileInfo* author,string title,string description,vector <string> tags);
    ~Question();
    void incrementVotes();
    void decrementVotes();
    void addInteraction(Interaction* interaction);

    Interaction* removeInteraction(const int &id);

    string show();

    int getId();
    void setId(int id);
    string getTitle();
    void setTitle(string title);
    string getDescription();
    void setDescription(string description);
    vector <string> getTags();
    void setTags(vector <string> tags);
    unsigned long int getTime();
    void setTime(unsigned long int time);
    MemberProfileInfo* getAuthor();
    void setAuthor(MemberProfileInfo* author);
    bool getClosed();
    void setClosed(bool closed);

private:
    int _id;
    string _title;
    string _description;
    vector <string> _tags;
    unsigned long int _time;
    vector <Interaction*> _interactions;
    MemberProfileInfo *_author;
    int _votes;
    bool _closed;
};

#endif // QUESTION_HPP
