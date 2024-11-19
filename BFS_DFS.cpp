#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
class graph{
public:
void add_Edge(vector<vector<int>>&list,int u,int v){
  list[u].push_back(v);
}
vector<int> Bfs(vector<vector<int>>&list,int starting_node){
  vector<int>ans;
  queue<int>q;
  unordered_map<int,bool>visited;
  q.push(starting_node);
  visited[starting_node]=true;
  while(!q.empty()){
    int current_node=q.front();
    q.pop();
    ans.push_back(current_node);
    for (int neighbour : list[current_node]) {  
        if (!visited[neighbour]) {
            visited[neighbour] = true;
            q.push(neighbour);
        }
    }
  }
  return ans;
}
void Dfs_recur(int node,vector<vector<int>>&list,unordered_map<int,bool>&visited,vector<int>&ans){
    visited[node]=true;
    ans.push_back(node);
    for (int neighbour : list[node]) {
            if (!visited[neighbour]) {
                Dfs_recur(neighbour, list, visited, ans);
            }
        }
}
vector<int> Dfs(vector<vector<int>>&list,int starting_node){
    vector<int>ans;
    unordered_map<int,bool>visited;
    Dfs_recur(starting_node,list,visited,ans);
    return ans;
}
};
int main(){
  int vertices;
  cout<<"Enter the number of vertices: "<<endl;
  cin>>vertices; 
  graph g;
  vector<vector<int>> list(vertices);
  g.add_Edge(list,0,1);
  g.add_Edge(list,1,3);
  g.add_Edge(list,0,2);
  g.add_Edge(list,2,6);
  g.add_Edge(list,3,4);
  g.add_Edge(list,4,5);
  g.add_Edge(list,6,7);
  g.add_Edge(list,7,8);
  g.add_Edge(list,5,9);
  g.add_Edge(list,8,10);
  g.add_Edge(list,9,10);
  int starting_node;
  cout<<"Enter the starting node: "<<endl;
  cin>>starting_node;
  int choice;
  cout<<"Enter your choice whether you want to implement BFS or DFS:\n 1.BFS 2.DFS "<<endl;
  cin>>choice;
  if (choice == 1) {
        vector<int> bfs_result = g.Bfs(list, starting_node);
        cout << "BFS traversal: ";
        for (int node : bfs_result) {
            cout << node << " ";
        }
        cout << endl;
    } else if (choice == 2) {
        vector<int> dfs_result = g.Dfs(list, starting_node);
        cout << "DFS traversal: ";
        for (int node : dfs_result) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Wrong Input" << endl;
    }

    return 0;
}