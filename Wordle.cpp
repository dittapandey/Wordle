#include<bits/stdc++.h>
#include<chrono>
#include <ctime>
using namespace std;
#define all(x) x.begin(),x.end()
#define tr(a,i) for(auto i : a)
#define f(i,n) for(int i=0;i<n;i++)
int n=15000,m=15000;
vector<string> possible_words, searchable_words,possible_words_backup, searchable_words_backup;
string answer_file = "answers_original.txt";
string search_words_file = "allowed_words.txt";
int coeff[5];
int x[243];
vector<int> attempts;
string first_guess;

double calculate_score(string s) //buggy, non ideal
{
    f(i,243)
    x[i]=0;
    int j;
    double ans=0;

    tr(possible_words,t)
    {
        
        f(i,5)
        if(s[i]==t[i])
        {
            coeff[i]=2;
            t[i]=' ';
        }
        else 
        {
        coeff[i]=0;
        j=-1;
        while(++j<5)
        if(t[j]==s[i])
        {
            coeff[i]=1;
            t[j]=' ';
            break;
        }

        }
        
        x[coeff[0]+3*coeff[1]+9*coeff[2]+27*coeff[3]+81*coeff[4]]++;
    }
    int sum=0;
    f(i,243)
    sum+=x[i];
    if(sum!=possible_words.size())
    exit(0);
    double t=possible_words.size();
    f(i,243) if(x[i]) ans+=x[i]*log2(t/x[i])/t;
    return ans;
}

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
void input(bool full_mode=0)
{
string s;
ifstream file;
file.open(search_words_file);
f(i,n)
if(file>>s)
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
cout<<n<<" words recognised\n"<<m<<" possible answers\n"<<endl;

}
void show_scores(int k=10)
{
    auto scores = suggestions();
    f(i,k)
    {
        cout<<scores.top().second<<" "<<
        scores.top().first<<endl;
        scores.pop();
    }
}

int main()
{
clock_t begin = clock();
// n=500;
input(0);

first_guess = "lares";
// first_guess = next_suggestion();
// play("abbes");
// calculate_score("lares");
show_scores();


clock_t end = clock();
cout<<"Time taken :"<<double(end - begin) / CLOCKS_PER_SEC;

return 0;
}

