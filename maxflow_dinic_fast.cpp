#include <bits/stdc++.h>

using namespace std;

const int vy[] = {-1, -1, -1, 0, 1, 1, 1, 0}, vx[] = {-1, 0, 1, 1, 1, 0, -1, -1};


#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

const long long INF = (1ll << 50);

struct graph {
  typedef long long flow_type;
  struct edge {
    int src, dst;
    flow_type capacity, flow;
    size_t rev;
  };
  int n;
  vector< vector< edge>> adj;

  graph(int n) : n(n), adj(n) {}

  void add_edge(int src, int dst, flow_type capacity) {
    adj[src].push_back({src, dst, capacity, 0, adj[dst].size()});
    adj[dst].push_back({dst, src, 0, 0, adj[src].size() - 1});
  }

  flow_type max_flow(int s, int t) {
    vector< int > level(n), iter(n);
    function< int(void) > levelize = [&]() { // foward levelize
      level.assign(n, -1);
      level[s] = 0;
      queue< int > Q;
      Q.push(s);
      while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if(u == t) break;
        for(auto &e: adj[u]) {
          if(e.capacity > e.flow && level[e.dst] < 0) {
            Q.push(e.dst);
            level[e.dst] = level[u] + 1;
          }
        }
      }
      return level[t];
    };
    function< flow_type(int, flow_type) > augment = [&](int u, flow_type cur) {
      if(u == t) return cur;
      for(int &i = iter[u]; i < adj[u].size(); ++i) {
        edge &e = adj[u][i], &r = adj[e.dst][e.rev];
        if(e.capacity > e.flow && level[u] < level[e.dst]) {
          flow_type f = augment(e.dst, min(cur, e.capacity - e.flow));
          if(f > 0) {
            e.flow += f;
            r.flow -= f;
            return f;
          }
        }
      }
      return flow_type(0);
    };
    for(int u = 0; u < n; ++u) // initialize
      for(auto &e: adj[u]) e.flow = 0;

    flow_type flow = 0;
    while(levelize() >= 0) {
      fill(all(iter), 0);
      for(flow_type f; (f = augment(s, INF)) > 0;)
        flow += f;
    }
    return flow;
  }
};


using int64 = long long;

int H, W, SX, SY;
int S[150][150];

bool isover(int y, int x) {
  return (y < 0 || y >= H || x < 0 || x >= W);
}

int get(int y, int x, bool in = false) {
  if(in) return (H * W + y * W + x);
  return (y * W + x);
}

int main() {
  cin >> H >> W >> SY >> SX;
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      cin >> S[i][j];
    }
  }

  graph flow(H * W * 2 + 2);

  for(int i = 0; i < H; i++) {
    flow.add_edge(get(i, 0, false), H * W * 2, INF);
    flow.add_edge(get(i, W - 1, false), H * W * 2, INF);
  }
  for(int i = 0; i < W; i++) {
    flow.add_edge(get(0, i, false), H * W * 2, INF);
    flow.add_edge(get(H - 1, i, false), H * W * 2, INF);
  }

  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      if(S[i][j] == -1) {
        flow.add_edge(H * W * 2 + 1, get(i, j, false), INF);
      }
    }
  }

  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      flow.add_edge(get(i, j, true), get(i, j, false), S[i][j] == -1 ? INF : S[i][j]);
      for(int k = 0; k < 8; k++) {
        int ni = i + vy[k], nj = j + vx[k];
        if(isover(ni, nj)) continue;
        flow.add_edge(get(i, j, false), get(ni, nj, true), INF);
      }
    }
  }

  cout << flow.max_flow(H * W * 2 + 1, H * W * 2) << endl;
}
