// Time complexity O(V + E log V)
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int INF = 1e9;

vector<vii> adj;

vi dijkstra(int source, int V){
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, source});
    vi dist(V, INF);
    dist[source] = 0;

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto &[v, w] : adj[u]){
            if(d+w >= dist[v])  continue;
            dist[v] = d+w;
            pq.push({dist[v], v});
        }
    }

    return dist;
}
