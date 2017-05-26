#include<bits/stdc++.h>
using namespace std;
#define MAX 500006

struct Weight_struct
{
    int Weight_age;
    int Weight_pincode;
    int Weight_job;
    int Weight_interests;
}Weight;

struct Profile
{
    string Name,Gender,City,Job;
    int Age,Id;
    long long Pincode;
    string Interest;
};

vector<Profile> Database[MAX];
set<pair<double,int> >Score;

Profile User,User1,Show_Profile[MAX];

double max_score;
int k,cmp,flag;

void Display_Info(int id)
{
    cout<<endl<<Show_Profile[id].Name;
    cout<<endl<<Show_Profile[id].Gender;
    cout<<endl<<Show_Profile[id].Age;
    cout<<endl<<Show_Profile[id].City;
    cout<<endl<<Show_Profile[id].Pincode;
    cout<<endl<<Show_Profile[id].Job;
    cout<<endl<<Show_Profile[id].Interest;
    cout<<endl;
}

void Get_Database()
{
    int n=20;
    while(n--)
    {
        cin>>User1.Id;
        getchar();
        getline(cin,User1.Name);
        cin>>User1.Gender;
        cin>>User1.Age;
        getchar();
        getline(cin,User1.City);
        cin>>User1.Pincode;
        getchar();
        getline(cin,User1.Job);
        cin>>User1.Interest;
        Database[User1.Pincode].push_back(User1);
        Show_Profile[User1.Id]=User1;
    }
}

double Get_Score(Profile & p)
{

    double ans=(abs(User.Age-p.Age))*Weight.Weight_age;
    ans+= (abs(User.Pincode-p.Pincode))*Weight.Weight_pincode;
    if(User.Job==p.Job)
    {
        ans+= Weight.Weight_job;
    }
    int mis=0;

    for(int i=0;i<User.Interest.size();i++)
    {
        mis+=(User.Interest[i]-'0')^(p.Interest[i]-'0');
    }
    ans+=mis*Weight.Weight_interests;
    return ans;
}

void init()
{
    flag=0;
    k=100;
    cmp=500;
    max_score=500;
    Weight.Weight_age=30;
    Weight.Weight_pincode=50;
    Weight.Weight_job=5;
    Weight.Weight_interests=10;
}

void get_User_Profile()
{
    cout<<"ENTER YOUR PROFILE INFORMATION\n\n";
    cout<<"Name: ";
    getline(cin,User.Name);
    cout<<"Gender: ";
    cin>>User.Gender;
    cout<<"Age: ";
    cin>>User.Age;
    cout<<"City: ";
    getchar();
    getline(cin,User.City);
    cout<<"Pincode: ";
    cin>>User.Pincode;
    cout<<"Job: ";
    getchar();
    getline(cin,User.Job);
    cout<<"Interests(Dancing, Singing, Swimming, Coding, Sports)(Enter a String of ones with Interests being 0) : ";
    cin>>User.Interest;
}

int main()
{
    init();
    get_User_Profile();

    if(User.Gender=="M" || User.Gender=="m" || User.Gender=="Male")
    {
        freopen("female_input.txt","r",stdin);
        Get_Database();
    }
    else
    {
        freopen("male_input.txt","r",stdin);
        Get_Database();
    }

    int start=User.Pincode-k;

    for(int i=0;i<2*k;i++)
    {
        for(int j=0;j<Database[start+i].size();j++)
        {
            double sc=Get_Score(Database[start+i][j]);
            if(sc<max_score)
            {
                Score.insert({sc,Database[start+i][j].Id});
            }
            if(Score.size()>cmp)
            {
                flag=1;
                break;
            }
        }
        if(flag)
            break;
    }

    for(auto i=Score.begin();i!=Score.end();i++)
    {
        cout<<"\n--------------------------\n";
        cout<<"\nCompatibility Score: "<<(*i).first<<endl;
        Display_Info((*i).second);
        cout<<"\n--------------------------\n";
    }
    if(Score.size()==0)
        cout<<"\n\nSorry, we could not find a match for you right now\n\n";

    return 0;
}
