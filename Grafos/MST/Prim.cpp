// Time complexity O(E log E)
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vector<vii> AL;
vi taken;
priority_queue<ii, vector<ii>, greater<ii>> pq;
int mst_cost = 0, num_taken = 0;

void process(int u){
    taken[u] = 1;
    for (auto &[v, w] : AL[u])
        if (!taken[v])
            pq.push({w, v});
}

void prim(vector<vii> AL, int src, int V){
    taken.assign(V+1, 0);
    process(src);
    while (!pq.empty()){
        auto [w, u] = pq.top();
        pq.pop();
        if (taken[u])
            continue;
        mst_cost += w;
        process(u);
        ++num_taken;
        if (num_taken == V - 1)
            break;
    }
}

int main(){
    int V, E;
    cin>>V>>E;
    AL.assign(V+1, vii());
    for (int i = 0; i < E; ++i){
        int u, v, w;
        cin>>u>>v>>w;
        AL[u].push_back({v,w});
        AL[v].push_back({u,w});
    }
    prim(AL,1,V);
    cout<<"MST cost= "<<mst_cost;
    return 0;
}