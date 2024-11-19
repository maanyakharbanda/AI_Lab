#include<bits/stdc++.h>
#include<vector>
# define inf 1e9 // used for representing the graph elements infinity 
using namespace std;
class Graph
{
  int n;
  public:
  vector<vector<int>>adj_matrix;
  Graph(int vertices)
  {
    n=vertices;
    adj_matrix.resize(n);
    for(auto &i:adj_matrix)
      i.resize(n,0);
    for(int i=0;i<n;i++)
      adj_matrix[i][i]=inf;
  }
  void enterGraph()
  {
    cout<<"Enter matrix: ";
    for(int i = 0;i<n;i++)
    {
      for(int j=0 ; j<n ; j++){
        cin >> adj_matrix[i][j] ;
        if(i==j) {
          adj_matrix[i][j]=inf ;
        }
      }
    }
  }
};
vector<int>BFS_level_constant(Graph g1,int width)
{
  int n=g1.adj_matrix.size();
  queue<int>q;
  vector<int>bfs_traverse, vis(n, 0);
  int start_pt; 
  cout<<"Enter the start point : ";
  cin>>start_pt;
  q.push(start_pt);
  vis[start_pt] = 1;
  while (!q.empty())
  {
    int vertex = q.front();
    q.pop();
    bfs_traverse.push_back(vertex);
    for (int i = 0; i < n && q.size() < width; i++)
    {
      if (!vis[i] && g1.adj_matrix[vertex][i] == 1)
      {
        q.push(i);
        vis[i] = 1;
      }
    }
  }
  return bfs_traverse;
}
vector<int> BFS_node_constant(Graph g1, int width){
  int n = g1.adj_matrix.size();
  queue<int>q;
  vector<int>bfs_traverse,vis(n, 0);
  int start_pt;
  cout << "Enter the start point : ";
  cin >> start_pt;
  q.push(start_pt);
  vis[start_pt] = 1;
  while (!q.empty())
  {
    int vertex = q.front();
    q.pop();
    bfs_traverse.push_back(vertex);
    int cnt = 0 ;
    for (int i = 0; i < n && cnt < width; i++)
    {
      if (!vis[i] && g1.adj_matrix[vertex][i] == 1)
      {
        q.push(i);
        vis[i] = 1;
        cnt++ ;
      }
    }
  }
  return bfs_traverse;
}
int main()
{
  int n;
  cout << "Enter number of vertices present in graph : ";
  cin >> n;
  Graph g1(n);
  g1.enterGraph();
  while(1)
  {
    cout<<" Choose option :- \n";
    cout<<" 1. Constant width at level,\n";
    cout<<" 2. Constant width at node\n";
    cout<<" 3. Press any key to exit\n"<<endl;
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:
    {
      cout<<"\n\n CONSTANT WIDTH AT LEVEL \n\n";
      cout<<"Enter width for level :- " ;
      int width ;
      cin>>width ;
      vector<int>bfs=BFS_level_constant(g1,width);
      cout<<"\n\n";
      for(auto i : bfs)
        cout<<i<<"\t";
      cout<<endl<<endl<<endl ;
      break;
    }
    case 2:
    {
      cout<<"\n\n CONSTANT WIDTH AT NODE \n\n";
      cout<<"Enter width for node :- " ;
      int width ;
      cin>>width ;
      vector<int>bfs_node = BFS_node_constant(g1,width);
      cout<< "\n\n" ;
      for(auto i : bfs_node)
        cout<<i<<"\t";
      cout<<endl<<endl<<endl ;
      break;
    }
    default:
      exit(1); 
    }
  }
}


/*

0 1 1 0 0 1 0 0 0 0
1 0 1 1 0 0 0 0 0 0
1 1 0 0 1 0 0 1 0 0
0 1 0 0 1 0 1 0 1 0
0 0 1 1 0 1 1 0 0 0
1 0 0 0 1 0 0 0 0 1
0 0 0 1 1 0 0 1 0 0
0 0 1 0 0 0 1 0 0 0
0 0 0 1 0 0 0 0 0 1
0 0 0 0 0 1 0 0 1 0


*/

/* 
0 1 0 0 0 0 1 1 1 0 0 0 
1 0 1 1 1 0 0 0 0 0 0 0 
0 1 0 0 0 1 0 0 0 1 0 0 
0 1 0 0 1 0 0 0 0 0 0 0 
0 1 0 1 0 1 0 0 0 0 0 0 
0 0 1 0 1 0 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 1 0 
1 0 0 0 0 0 0 0 0 1 0 1 
0 0 1 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 1 0 0 0 1 
0 0 0 0 0 0 0 0 1 0 1 0

*/