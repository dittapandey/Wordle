#include "Wordle.cpp"
using namespace std;
priority_queue<pair<double,string> > suggestions()  //perfect
{
    if(possible_words.size()==0)
    {
        cout<<"Invalid word ";
        exit(0);
    }
    priority_queue<pair<double,string> > scores;
    if(possible_words.size()<=2)
    {
        scores.push({1e9,possible_words[0]});
        if(possible_words.size()==2)
        scores.push({1e9,possible_words[1]});
        return scores;
    }

    tr(searchable_words,s)
        scores.push({calculate_score(s),s});

    return scores;
}
string next_suggestion()    //perfect
{
    return suggestions().top().second;
}