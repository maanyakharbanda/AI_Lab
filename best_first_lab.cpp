#include<bits/stdc++.h>
using namespace std;
class graph{
    int n;
    public:
    vector<vector<int>>matrix;
    graph(){
        n=28; // given in question
        matrix.resize(n);
        for(auto &i:matrix){
            i.resize(n,0);
        }
    }
    int get_index(char ch){
        if(ch=='.'){
            return 26;
        }
        else if(ch==' '){
            return 27;
        }
        else{
            return ch-'a';
        }
    }
    char get_char(int i){
        if(i>=0 && i<=25){
            return 'a'+i;
        }
        else if(i==26){
            return '.';
        }
        else{
            return ' ';
        }
    }
    void graph_create(string s){
        int string_length=s.length();
        int prev=get_index(s[0]);
        int i=1;
        while(i<string_length){
            char ch=s[i];
            int curr_index=get_index(ch);
            matrix[prev][curr_index]++;
            prev=curr_index;
            i++;
        }
    }
    void display(){
        int width=5;
        cout<<"Adjacency Matrix: \n\n"<<endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cout<<setw(width)<<matrix[i][j];
              cout<<endl;
        }
        cout<<"\n\n";
    }
};
string refine_input(string input){
    string s="";
    for(auto i:input){
        if(i=='.' || i==' '||('a'<= i && i<='z')){
            string temp(1,i); // s.append(i) would not work directly because s.append expects a string or a character array, not a single char. The i variable is a char, so s.append(i) would result in a compilation error.
            s.append(temp);
        }
        else if('A'<=i && i<='Z'){
            i=tolower(i);
            string temp(1,i);
            s.append(temp);
        }
    }
    return s;
};
string best_first(graph &g1){
    int n=g1.matrix.size();
    queue<int>q;
    vector<int>vis(n,0);
    string output="";
    char start_char;
    cout<<"Enter the starting character: "<<endl;
    cin>>start_char;
    if(!(start_char== ' '|| start_char == '.' || ('a'<=start_char && start_char<='z'))){
        cout<<"INVALID STARTING CHARACTER"<<endl;
        return output;
    }
    
    int start_index=g1.get_index(start_char);
    q.push(start_index);
    vis[start_index]=1;
    while(!q.empty()){
        int vertex=q.front();
        q.pop();
        char ch=g1.get_char(vertex);
        string temp(1,ch);
        output.append(temp);
        int maximum_freq = -1e9;
        int index_no = -1;
        for (int i = 0; i < n; i++) { 
            if (!vis[i] && g1.matrix[vertex][i] != 0) { 
                if (maximum_freq < g1.matrix[vertex][i]) {
                    maximum_freq = g1.matrix[vertex][i]; 
                    index_no = i; 
                }
             } 
        }
        if (index_no != -1) { 
            q.push(index_no); 
            vis[index_no] = 1; 
            } 
        } 
        return output; 
}
int main(){
    string input_str;
    cout<<"Enter the string: "<<endl;
    getline(cin,input_str);
    string s=refine_input(input_str);
    graph g1;
    g1.graph_create(s);
    g1.display();
    string output=best_first(g1);
    cout<<"\n\n"<<output<<"\n\n"<<endl;
}