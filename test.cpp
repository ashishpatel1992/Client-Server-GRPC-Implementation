#include<bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    // string s = "5 10";
    // uint32_t a,b;
    // istringstream istringname(s);
    // istringname >> a>>b;
    // cout<<a<<" "<<b;
    // return 0;
     cout << "You have entered " << argc 
         << " arguments:" << "\n"; 
    string s = argv[1];
    string args;
    cout<<s<<"\n";
    for (int i = 2; i < argc; ++i){
        if(s == "add"){
            args = args+argv[i]+" ";
            // cout << argv[i] << "\n"; 
        }else break;
    } 
    cout<<"\n"<<args<<"\n";
        
}
