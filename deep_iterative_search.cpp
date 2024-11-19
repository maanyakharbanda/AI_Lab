#include <bits/stdc++.h>
using namespace std;
#define inf 1e9
class Graph
{
  int n, m;
  public:
  vector<vector<int>> matrix;
  Graph(int vertices, int edges)
  {
    n = vertices;
    m = edges;
    matrix.resize(n);
    for (auto &i : matrix)
      i.resize(n, 0);
    for (int i = 0; i < n; i++)
      matrix[i][i] = inf;
  }
  void enterGraph()
  {
    cout << "Enter edges : ";
    for (int i = 0; i < m; i++)
    {
      int a, b;
      cin >> a >> b;
      // undirected graph
      matrix[a][b] = 1;
      matrix[b][a] = 1;
    }
  }
};
void dfs_func(int i, vector<int> &visited, Graph &g1, vector<int> &dfs_traverse, int n,int depth)
{
  visited[i] = 1; // i is the starting node
  dfs_traverse.push_back(i);
  if(depth==0) return ;
  for (int neighbours = 0; neighbours < n; neighbours++)
  {
    if (!visited[neighbours] && g1.matrix[i][neighbours] == 1)
      dfs_func(neighbours, visited, g1, dfs_traverse, n,depth-1);
  }
}
vector<int> DFS(Graph &g1,int depth)
{
  int n = g1.matrix.size();
  vector<int> dfs_traverse, vis(n, 0);
  int start_pt;
  cout << "Enter the start point : ";
  cin >> start_pt;
  if (start_pt >= n)
  {
    cout << "INVALID START POINT.\n";
    return {};
  }
  dfs_func(start_pt, vis, g1, dfs_traverse, n,depth);
  return dfs_traverse;
}
int main()
{
  int n, m;
  cout << "Enter number of vertices present in graph : ";
  cin >> n;
  cout << "Enter number of edges present in graph : ";
  cin >> m;
  Graph g1(n, m);
  g1.enterGraph();
  for (int depth = 1; depth <= 4; depth++)
  {
    cout << "\n\n DEPTH= "<< depth << " \n\n";
    vector<int> dfs = DFS(g1,depth);
    if(dfs.size()==0)
      continue ;

    cout << "\n\n";
    for (auto i : dfs)
      cout << i << "\t";
    cout << "\n\n" ;
  }
}

/* ips
21 24 1 2 1 3 2 4 2 5 5 4 5 6 5 7 3 9 9 10 9 11 7 12 10 13 11 12 12 14 14 19 13 17 17 18 18 19 18 20 20 15 15 16 16 8 1 0 0 3
*/