// Time complexity O(V + E)
typedef vector<int> vi;

// vi a[] es una lista de adyacencia y v[] el arreglo de nodos visitados
void dfs(vi a[],int node, bool v[]){
    if(v[node]){
        return;
    }
    v[node]=true;
    //process node
    //cout<<node<<" ";
    for(auto u : a[node]){
        dfs(a,u,v);
    }
}

void bfs(vi a[],int n){
    queue<int> q;
    bool v[n];
    //int dist[n];
    for(int i=0;i<n;i++)
        v[i]=false;
    //start=0
    v[0]=true;
    q.push(0);
    while(!q.empty()){
        int node=q.front();
        q.pop();
        //proccess node
        cout<<node<<" ";
        for(auto u:a[node]){
            if(v[u])
                continue;
            v[u]=true;
            //dist[u]=dist[node]+1;
            q.push(u);
        }
    }
}