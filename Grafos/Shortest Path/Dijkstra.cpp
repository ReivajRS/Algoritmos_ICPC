// Time complexity O(E log V)

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int INF=1e9;

vector<vii> adj;

vi dijkstra(int start, int V){
    priority_queue<ii, vii, greater<ii>> pq;    pq.push({0,start});
    vi dist(V, INF);    dist[start]=0;

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto &[v, w] : adj[u]){
            if(dist[u]+w >= dist[v])  continue;
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }

    return dist;
}