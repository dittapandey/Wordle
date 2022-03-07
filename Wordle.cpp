#include<bits/stdc++.h>
using namespace std;
#define all(x) x.begin(),x.end()
#define tr(a,i) for(auto i : a)
#define f(i,n) for(int i=0;i<n;i++)
int n,m=15000;
vector<string> possible_words, searchable_words,possible_words_backup, searchable_words_backup;
string answer_file = "answers_original.txt";
string search_words_file = "allowed_words.txt";
vector<int> attempts;
string first_guess;
priority_queue<pair<int,string> > scores;
void filter_data(string str, string res)    //perfect
{
    for(int k=0;k<searchable_words.size();k++)
    if(str==searchable_words[k])
    searchable_words.erase(searchable_words.begin()+k);
    for(int k=0;k<possible_words.size();k++)
    if(str==possible_words[k])
    possible_words.erase( possible_words.begin()+k );
    // possible_words[k]="______";

    f(i,5) 
    if(res[i]=='b')
    {
    for(int k=0;k<possible_words.size();k++)
    if(count(all(possible_words[k]),str[i])!=0)
    possible_words[k]="______";
    }
    else if (res[i]=='y')
    {
    for(int k=0;k<possible_words.size();k++)
    if(count(all(possible_words[k]),str[i])==0)
    possible_words[k]="______";
    }
    else if(res[i]=='g')
    {
    for(int k=0;k<possible_words.size();k++)
    if(possible_words[k][i]!=str[i])
    possible_words[k]="______";
    }
    vector<string> temp_list;
    for(int k=0;k<possible_words.size();k++)
    if(possible_words[k][0]!='_')
    temp_list.push_back(possible_words[k]);
    possible_words=temp_list;
}

int calculate_score(string s)
{
    vector<int> x(243);

    int score=0;
    int coeff[5];
    tr(possible_words,t)
    {
        score=0;
        f(i,5)
        {
            if(s[i]==t[i])
            coeff[i]=0;
            else if(count(all(s),s[i])==count(all(t),s[i]))
            coeff[i]=1;
            else coeff[i]=2;
        }
        coeff[1]*=3;
        coeff[2]*=9;
        coeff[3]*=27;
        coeff[4]*=81;
        score=coeff[0]+coeff[1]+coeff[2]+coeff[3]+coeff[4];
        x[score]++;
    }
    int ans=0;
    // f(i,243) cout<<x[i]<<endl;

    // f(i,243) score+=x[i];
    // cout<<score;
    f(i,243) ans+=x[i]*x[i];
    return ans;
}
string next_suggestion()
{
    while(!scores.empty()) scores.pop();
    if(possible_words.size()==1 ||possible_words.size()==2)
    return possible_words[0];
    if(possible_words.size()==0)
    {
        cout<<"Invalid word ";
        exit(0);
    }
    //return searchable_words[rand()%searchable_words.size()];
    
    int score=1e9,current_score;
    string ans="No such word";
    tr(searchable_words,s)
    {
    
    current_score=calculate_score(s);
    // cout<<s<<" "<<current_score<<'\n';

    if(current_score<score)
    {
        ans=s;
        score=current_score;
    }
    }
    // cout<<"Suggested "<<ans<<" with score "<<score<<endl;
    return ans;
}


int autoplay(string s)   //perfect
{
    int size=possible_words_backup.size();
    possible_words=possible_words_backup;
    searchable_words=searchable_words_backup;
    string suggestion=first_guess;
    int turns=0;
    while(++turns)
    {
    if(suggestion==s)
    return turns;
    searchable_words.erase(find(all(searchable_words),suggestion));
    possible_words.erase(find(all(possible_words),suggestion));
    for(int k=0;k<size;k++)
    f(i,5)
    {
    if(suggestion[i]==s[i])
    {
    if(possible_words[k][i]!=s[i])
    possible_words[k]="______";
    }
    else if( count(all(s),suggestion[i]) )
    {
    if(count(all(possible_words[k]),suggestion[i])==0)
    possible_words[k]="______";
    }
    else
    if(count(all(possible_words[k]),suggestion[i]))
    possible_words[k]="______";
    }
    vector<string> temp_list;
    for(int k=0;k<size;k++)
    if(possible_words[k][0]!='_')
    temp_list.push_back(possible_words[k]);
    possible_words=temp_list;
    size=possible_words.size();
    // filter_data(suggestion,result);
    suggestion = next_suggestion();
    }
    return turns;
}
void play()
{
    cout<<"Hello !"<<endl;
    string suggestion=first_guess;
    int k=0;string res;
    while(++k)
    {
        cout<<"Suggested "<<suggestion<<endl;
        cout<<"Result is ";
        cin>>res;
        if(res=="ggggg") break;
        filter_data(suggestion,res);
        suggestion=next_suggestion();
    }
}
int play(string s)   //perfect
{
    possible_words=possible_words_backup;
    searchable_words=searchable_words_backup;
    cout<<"Playing for "<<s<<endl;
    string suggestion=first_guess;
    cout<<"Trying "<<suggestion<<endl;
    string result;
    int k=0;
    while(++k)
    {
    result = "bbbbb";
    f(i,5)
    if(count(all(s),suggestion[i]))
    result[i]='y';
    f(i,5)
    if(suggestion[i]==s[i])
    result[i]='g';
    cout<<"Result "<<result<<endl;
    if(result =="ggggg")
    break;
    filter_data(suggestion,result);
    cout<<"Filtered list, "<<possible_words.size()<<" words remain."<<endl;
    suggestion = next_suggestion();
    cout<<"Trying "<<suggestion<<endl;
    }
    cout<<"Got it in "<<k<<endl;
    return k;
    // autoplay(s,k+1);
}
void play(int t)
{
    double score = 0.0;
    for(int i=0;i<t;i++)
    {    
    score+=autoplay(possible_words_backup[i]);
    cout<<i+1<<" "<<score/(i+1)<<endl;
    }
}
void play_random(int k)
{
    double score = 0.0;
    for(int i=0;i<k;i++)
    {    
    score+=autoplay(possible_words_backup[(rand()*rand())%possible_words_backup.size()]);
    // string s = possible_words_backup[rand()%possible_words_backup.size()];
    cout<<i+1<<" "<<score/(i+1)<<endl;
    }
}

void input(bool full_mode=0)
{
string s;
ifstream file;
file.open(search_words_file);
while(file>>s)
searchable_words.push_back(s);
n=searchable_words.size();
file.close();
if(full_mode)
possible_words=searchable_words;
else
{
file.open(answer_file);
f(i,m)
if(file>>s)
possible_words.push_back(s);
file.close();
}
m=possible_words.size();
possible_words_backup=possible_words;
searchable_words_backup=searchable_words;

}

int main()
{
input();

cout<<n<<" words recognised, "<<m<<" possible answers."<<endl;

// first_guess = "tares"; 
// first_guess = next_suggestion(); 

// cout<<"First guess is "<<first_guess<<endl;

// play(n);

return 0;
}

