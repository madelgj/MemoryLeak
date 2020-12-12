#ifndef QUESTION_HPP
#define QUESTION_HPP
#include <iostream>
#include <vector>
#include "Member.hpp"
#include "Interaction.hpp"
#include "Answer.hpp"
#include "Comment.hpp"
#include <sstream>

using namespace std;

class Question
{
public:
    Question(int id,unsigned long int time,MemberProfileInfo* author,string title,string description,vector <string> tags);
    ~Question();

    // getters and setters
    int getId();
    void setId(const int &id);

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

    int getVotes() const;
    void incrementVotes();
    void decrementVotes();

    // methods regarding interactions
    Interaction* exists(const int &id);
    vector<Interaction *> getInteractions();
    void addInteraction(Interaction* interaction);
    Interaction* removeInteraction(const int &id);

    // other methods
    string show();
    bool questionHasTag(const string &tag);

private:

    int _id;
    int _votes;
    bool _closed;
    unsigned long int _time;
    MemberProfileInfo *_author;
    string _title;
    string _description;
    vector <string> _tags;
    vector <Interaction*> _interactions;

};

#endif // QUESTION_HPP
