// Time complexity O(V + E)
// Source: Own work
typedef vector<int> vi;

// DFS
vector<vi> adj;
vector<bool> visited;

void dfs(int u){
    if(visited[u]) return;
    visited[u]=true;
    //process node
    for(auto &v : adj[u])
        dfs(v);
}

// BFS
const int MAXN = 1e6;

void bfs(int src){
    queue<int> q; q.push(src);
    vector<bool> visited(MAXN, false); visited[src] = true;

    while(!q.empty()){
        int u = q.front(); q.pop();
        // Process node
        for(auto &v : adj[u]){
            if(visited[v])  continue;
            visited[v] = true;
            q.push(v);
        }
    }
}

// Bipartite graph check
bool bfs(int src){
    queue<int> q; q.push(src);
    vi color(MAXN, -1); color[src] = 0;
    
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto &v : adj[u]){
            if(color[v] == -1){
                color[v] = color[u] ^ 1;
                q.push(v);
            }
            else if(color[v] == color[u])
                return false;
        }
    }
    
    return true;
}