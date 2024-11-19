#include <bits/stdc++.h>
using namespace std;
class Node {
public:
    int id;        // The unique identifier for the node, typically its index in the graph.
    int parent;    // The id of the parent node from which this node was reached.
    double f;      // The total cost function value (f = g + h).
    double g;      // The cost from the start node to this node.
    double h;      // The estimated cost from this node to the goal (heuristic value).

    // Constructor to initialize a node.
    Node(int id, int parent = -1, double g = 0.0, double h = 0.0)
        : id(id), parent(parent), g(g), h(h) {
        f = g + h;  // Calculate the total cost function.
    }

    // Operator overloading to compare nodes in a priority queue.
    bool operator<(const Node& other) const {
        return f > other.f; // Nodes with a lower f value have higher priority.
    }
};
class graph {
    int n;
public:
    vector<vector<int>> adj_matrix;
    vector<double> heuristic;
    graph(int nodes){
        n=nodes;
        adj_matrix.resize(n);
        for(auto &i:adj_matrix){
            i.resize(n,0);
        }
        heuristic.resize(n, 0.0); 
    }
    void display_adj_matrix() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adj_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    // dfs
    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << static_cast<char>('A' + node) << " ";
        for (int i = 0; i < n; i++) {
            if (adj_matrix[node][i] > 0 && !visited[i]) {
                dfs(i, visited);
            }
        }
    }
    // best first search
    void best_first(int starting_node){
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        vector<bool>visited(n,false);
        pq.push({0,starting_node}); // cost and node
        visited[starting_node]=true;
        while(!pq.empty()){
            int current_node=pq.top().second;
            pq.pop();
            cout << static_cast<char>('A' + current_node) << " ";
            for (int i = 0; i < n; i++) {
        if (!visited[i] && adj_matrix[current_node][i] > 0 ) {
          pq.push({adj_matrix[current_node][i], i});
          visited[i] = 1;
        }
      }
    }
  }
  // breadth first search
  void bfs(int starting_node){
      queue<int>q;
      vector<bool>visited(n,false);
      q.push(starting_node);
      visited[starting_node]=true;
      while(!q.empty()){
          int current_node=q.front();
          q.pop();
          cout<<static_cast<char>('A'+current_node)<<" ";
          for(int neighbours=0;neighbours<n;neighbours++){
              if(!visited[neighbours] && adj_matrix[current_node][neighbours] > 0 ){
                  q.push(neighbours);
                  visited[neighbours]=true;
              }
          }
      }
  }
  // iterative deepening
  void idfs(int node,int depth,vector<bool>&visited){
      visited[node]=true;
      cout<<static_cast<char>('A'+ node)<<" ";
      if(depth>0){
          for(int neighbours=0;neighbours<n;neighbours++){
              if(adj_matrix[node][neighbours]>0 && !visited[neighbours]){
                  idfs(neighbours,depth-1,visited);
          }
      }
  }
}
  void idfs_main(int start_node,int max_depth){
      for(int d=1;d<=max_depth;d++){
          vector<bool>visited(n,false);
          cout<<"Exploring depth level: "<<d<<endl;
          idfs(start_node,d,visited);
          cout<<endl;
      }
  }
  // beam search
 void beam_search(int starting_node, int width) {
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize the priority queue with the starting node
    pq.push({0, starting_node});
    visited[starting_node] = true;

    while (!pq.empty()) {
        // Collect nodes at the current level
        vector<pair<int, int>> current_level;
        while (!pq.empty()) {
            current_level.push_back(pq.top());
            pq.pop();
        }

        // Sort the collected nodes based on their priority (i.e., cost)
        sort(current_level.begin(), current_level.end());

        // Keep only the top 'width' nodes
        if (current_level.size() > width) {
            current_level.resize(width);
        }

        // Process each node in the current level
        for (const auto& node : current_level) {
            int current_node = node.second;
            cout << static_cast<char>('A' + current_node) << " ";
            visited[current_node] = true;

            // Expand the current node and push its neighbors to the priority queue
            for (int i = 0; i < n; i++) {
                if (!visited[i] && adj_matrix[current_node][i] > 0) {
                    pq.push({adj_matrix[current_node][i], i});
                    visited[i] = true;
                }
            }
        }
    }
}
void reconstructPath(const vector<int>& parents, int goal) {
        vector<int> path;
        for (int current = goal; current != -1; current = parents[current]) {
            path.push_back(current);
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (int node : path) {
            cout << static_cast<char>('A' + node) << " ";
        }
        cout << endl;
    }
// A* algorithm
void a_star(int start, int goal) {
    vector<bool> closedList(n, false);        // Tracks nodes that have been fully explored.
    vector<int> parents(n, -1);               // Keeps track of the parent nodes for path reconstruction.
    priority_queue<Node> openList;            // Priority queue (min-heap) for nodes to be explored.

    // Start with the initial node, pushing it to the open list.
    openList.push(Node(start, -1, 0, heuristic[start]));

    while (!openList.empty()) {
        Node current = openList.top();        // Get the node with the lowest f value.
        openList.pop();

        // If the goal is reached, reconstruct the path.
        if (current.id == goal) {
            reconstructPath(parents, goal);
            return;
        }

        closedList[current.id] = true;        // Mark this node as fully explored.

        // Explore each neighbor of the current node.
        for (int i = 0; i < n; ++i) {
            if (adj_matrix[current.id][i] != 0 && !closedList[i]) {
                double g = current.g + adj_matrix[current.id][i]; // g value for the neighbor.
                double h = heuristic[i];                          // h value for the neighbor.
                Node successor(i, current.id, g, h);              // Create the neighbor node.

                bool skip = false;

                // Check if a node with a lower f value is already in the open list.
                priority_queue<Node> tempList = openList;
                while (!tempList.empty()) {
                    Node n = tempList.top();
                    tempList.pop();
                    if (n.id == i && n.f <= successor.f) {
                        skip = true;
                        break;
                    }
                }

                // If the node isn't in the open list or is better, add it to the open list.
                if (!skip) {
                    openList.push(successor);
                    parents[successor.id] = current.id; // Update parent.
                }
            }
        }
    }

    cout << "No path found." << endl; // If the open list is empty and goal not reached, no path exists.
}
};
int main() {
    int n;
    cout << "Enter the number of nodes in the graph: " << endl;
    cin >> n;
    graph g1(n);
    cout << "Enter the adjacency matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g1.adj_matrix[i][j];
        }
    }
    cout << "Adjacency Matrix:" << endl;
    g1.display_adj_matrix();
    while(true){
    cout<<"Enter the option:"<<endl;
    cout<<" 1. Depth First Search without considering any cost."<<endl;
    cout<<" 2. Best First Search considering only g value."<<endl;
    cout<<" 3. Iterative Deepening by exploring best node first."<<endl;
    cout<<" 4. Breadth First Search without considering any cost."<<endl;
    cout<<" 5. Beam Search (Width=2) by giving preference to best node."<<endl;
    cout<<" 6. A* algorithm by considering both g and h'."<<endl;
    cout<<" 7. Exit"<<endl;
    int option;
    cin>>option;
    if(option==7){
        cout<<"Exit"<<endl;
        break;
    }
    vector<bool> visited(n, false);
    char start_node;
    cout << "Enter the starting node: (A-" << char('A' + n - 1) << "): " << endl;
    cin >> start_node;
    if (start_node < 'A' || start_node >= 'A' + n) {
        cout << "Invalid starting node." << endl;
        return 1;
    }
    switch(option){
        case 1:
        cout<<"Depth First Search: "<<endl;
        cout << "DFS Traversal: ";
        g1.dfs(start_node - 'A', visited);
        cout << endl;
        break;
        case 2:
        cout<<"BEST FIRST SEARCH TRAVERSAL: "<<endl;
        g1.best_first(start_node - 'A');
        cout << endl;
        break;
        case 3:
        cout<<"Iterative Deepening Search: "<<endl;
        int depth;
        cout<<"Enter depth: "<<endl;
        cin>>depth;
        g1.idfs_main(start_node-'A',depth);
        break;
        case 4:
        cout<<"Breadth First Search: "<<endl;
        g1.bfs(start_node-'A');
        cout<<endl;
        break;
        case 5:
        cout<<"Beam  First Search: "<<endl;
        int width;
        cout<<"Enter the value of beam width: "<<endl;
        cin>>width;
        g1.beam_search(start_node-'A',width);
        break;
        case 6:
        cout << "A* Algorithm: " << endl;
        char goal_node;
            cout << "Enter the goal node: (A-" << char('A' + n - 1) << "): " << endl;
            cin >> goal_node;
            if (goal_node < 'A' || goal_node >= 'A' + n) {
                cout << "Invalid goal node." << endl;
                return 1;
            }
            g1.a_star(start_node - 'A', goal_node - 'A');
            break;
        default:
        cout<<"Invalid Entry: "<<endl;
    }
    }
    return 0;
}