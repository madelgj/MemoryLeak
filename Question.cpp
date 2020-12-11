#include "Question.hpp"

Question::Question(int id,unsigned long int time,MemberProfileInfo* author,string title,string description,vector <string> tags)
{
    _id=id;
    _time=time;
    _author=author;
    _title=title;
    _description=description;
    _tags=tags;
    _votes=0;
    _closed=false;
}

Question::~Question()
{
    _interactions.clear();
    _tags.clear();
    _author=NULL;
}

void Question::incrementVotes()
{
    _votes++;
}

void Question::decrementVotes()
{
    _votes--;
}

void Question::addInteraction(Interaction* interaction)
{
    if (!_closed){
        _interactions.push_back(interaction);
    }
}

Interaction* Question::removeInteraction(const int &id)
{
    Interaction* removed;
    Answer* commented_ans;
    vector<Comment*> comments;
    for (unsigned long i=0;i<_interactions.size();i++){
        if(_interactions[i]->getId() == id){ // the interaction to remove is an answer/comment of a question
            removed = _interactions[i];
            _interactions.erase(_interactions.begin() + i);
            return removed;
        } else {
            if (commented_ans = dynamic_cast<Answer*>(_interactions[i])){
                comments = commented_ans->getComments();
                for (unsigned long i=0;i<comments.size();i++){
                    if (comments[i]->getId() == id){ // the id corresponds to a comment of an answer
                        removed = comments[i];
                        comments.erase(comments.begin()+i);
                        return removed;
                    }
                }
            }
        }
    }
    return nullptr;
}

string Question::show()
{
    stringstream ss;
    ss << _id << " - " << _title << endl;
    ss << " -------" << endl;
    ss << "by " << _author->getUsername() << " on " << _time << endl;
    ss << "Tags: ";
    for (unsigned long i=0; i<_tags.size();i++){
        if (i!=0){ ss << "/"; }
        ss << _tags[i];
    }
    ss << endl;
    if (_closed == true){
        ss << "closed - ";
    } else{
        ss << "open - ";
    }
    ss << _votes << " votes" << endl;
    ss << "---" << endl;
    ss << _description << endl;
    for (unsigned long i=0; i<_interactions.size();i++){
        ss << "---" << endl;
        ss << _interactions[i]->show() << endl;
    }
    ss << "---";
    return ss.str();

}

int Question::getId()
{
    return _id;
}

void Question::setId(const int &id)
{
    _id=id;
}

string Question::getTitle()
{
    return _title;
}

void Question::setTitle(string title)
{
    _title=title;
}

string Question::getDescription()
{
    return _description;
}

void Question::setDescription(string description)
{
    _description=description;
}

vector <string> Question::getTags()
{
    return _tags;
}

void Question::setTags(vector <string> tags)
{
    _tags=tags;
}

unsigned long int Question::getTime()
{
    return _time;
}

void Question::setTime(unsigned long int time)
{
    _time=time;
}

MemberProfileInfo* Question::getAuthor()
{
    if (_author != nullptr) {
        cout << "hola2" << endl << flush;
    }
    return _author;
}

void Question::setAuthor(MemberProfileInfo* author)
{
    _author=author;
}

bool Question::getClosed()
{
    return _closed;
}

void Question::setClosed(bool closed)
{
    _closed=closed;
}

int Question::getVotes() const
{
    return _votes;
}

Interaction *Question::exists(const int &id)
{
    vector <Comment*> comments;
    Answer* commented_ans;
    for (unsigned long i=0; i<_interactions.size(); i++){
//        cout << "the id we are checking is: " << id << endl << flush;
//        cout << "the actual id is: " << _interactions[i]->getId()<< endl << flush;
        if (_interactions[i]->getId() == id){ // the id corresponds to an answer/comment of a question
            return _interactions[i];
        } else {
            if (commented_ans = dynamic_cast<Answer*>(_interactions[i])){
                comments = commented_ans->getComments();
                for (unsigned long i=0;i<comments.size();i++){
                    if (comments[i]->getId() == id){ // the id corresponds to a comment of an answer
                        return comments[i];
                    }
                }
            }
        }
    }
    return nullptr;
}

vector<Interaction *> Question::getInteractions() const
{
    return _interactions;
}

bool Question::questionHasTag(const string &tag)
{
    for (unsigned long i=0; i<_tags.size(); i++){
        if(_tags[i] == tag){
            return true;
        }
    }
    return false;
}
