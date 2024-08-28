#include <bits/stdc++.h>
using namespace std;
struct FringeOpposedSubset {
  deque<int> left, right;
  FringeOpposedSubset() = default;
  FringeOpposedSubset(int h) : left{h}, right() {}
};
template<typename T>
void extend(T& a, T& b, bool rev = false) {
  rev ? a.insert(a.begin(), b.rbegin(), b.rend())
      : a.insert(a.end(), b.begin(), b.end());
}
struct Fringe {
  deque<FringeOpposedSubset> FOPs;
  Fringe(int h) : FOPs{{h}} {}
  bool operator<(const Fringe& o) const {
    return std::tie(FOPs.back().left.back(), FOPs.front().left.front()) <
        std::tie(o.FOPs.back().left.back(), o.FOPs.front().left.front());
  }
  void merge(Fringe& o) {
    o.merge_t_alike_edges();
    merge_t_opposite_edges_into(o);
    if (FOPs.front().right.empty())
      o.align_duplicates(FOPs.back().left.front());
    else
      make_onion_structure(o);
    if (o.FOPs.front().left.size()) FOPs.push_front(o.FOPs.front());
  }
  void merge_t_alike_edges() {
    FringeOpposedSubset ans;
    for (auto& FOP : FOPs) {
      if (!FOP.right.empty()) throw runtime_error("Exception");
      extend(ans.left, FOP.left);
    }
    FOPs = {ans};
  }
  void merge_t_opposite_edges_into(Fringe& o) {
    while (FOPs.front().right.empty() &&
           FOPs.front().left.front() > o.FOPs.front().left.back()) {
      extend(o.FOPs.front().right, FOPs.front().left);
      FOPs.pop_front();
    }
  }
  void align_duplicates(int dfs_h) {
    if (FOPs.front().left.back() == dfs_h) {
      FOPs.front().left.pop_back();
      swap_side();
    }
  }
  void swap_side() {
    if (FOPs.front().left.empty() ||
        (!FOPs.front().right.empty() &&
         FOPs.front().left.back() > FOPs.front().right.back())) {
      swap(FOPs.front().left, FOPs.front().right);
    }
  }
  void make_onion_structure(Fringe& o) {
    auto low = &FOPs.front().left, high = &FOPs.front().right;
    if (FOPs.front().left.front() >= FOPs.front().right.front())
      swap(low, high);
    if (o.FOPs.front().left.back() < low->front())
      throw runtime_error("Exception");
    if (o.FOPs.front().left.back() < high->front()) {
      extend(*low, o.FOPs.front().left, true);
      extend(*high, o.FOPs.front().right, true);
      o.FOPs.front().left.clear();
      o.FOPs.front().right.clear();
    }
  }
  auto lr_condition(int deep) const {
    bool L = !FOPs.front().left.empty() && FOPs.front().left.front() >= deep;
    bool R = !FOPs.front().right.empty() && FOPs.front().right.front() >= deep;
    return make_pair(L, R);
  }
  void prune(int deep) {
    auto [left, right] = lr_condition(deep);
    while (!FOPs.empty() && (left || right)) {
      if (left) FOPs.front().left.pop_front();
      if (right) FOPs.front().right.pop_front();
      if (FOPs.front().left.empty() && FOPs.front().right.empty())
        FOPs.pop_front();
      else swap_side();
      if (!FOPs.empty()) tie(left, right) = lr_condition(deep);
    }
  }
};
unique_ptr<Fringe> get_merged_fringe(deque<unique_ptr<Fringe>>& upper) {
  if (upper.empty()) return nullptr;
  sort(upper.begin(), upper.end(), [](auto& a, auto& b) { return *a < *b; });
  for (auto it = next(upper.begin()); it != upper.end(); ++it)
    upper.front()->merge(**it);
  return move(upper.front());
}
void merge_fringes(vector<deque<unique_ptr<Fringe>>>& fringes, int deep) {
  auto mf = get_merged_fringe(fringes.back());
  fringes.pop_back();
  if (mf) {
    mf->prune(deep);
    if (mf->FOPs.size()) fringes.back().push_back(move(mf));
  }
}
struct Edge {
  int from, to;
  Edge(int from, int to) : from(from), to(to) {}
  bool operator==(const Edge& o) const {
    return from == o.from && to == o.to;
  }
};
struct Graph {
  int n = 0;
  vector<vector<int>> neighbor;
  vector<Edge> edges;
  void add_edge(int from, int to) {
    if (from == to) return;
    edges.emplace_back(from, to);
    edges.emplace_back(to, from);
  }
  void build() {
    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
      return a.from < b.from || (a.from == b.from && a.to < b.to);
    });
    edges.erase(unique(edges.begin(), edges.end()), edges.end());
    n = 0;
    for (auto& e : edges) n = max(n, max(e.from, e.to) + 1);
    neighbor.resize(n);
    for (auto& e : edges) neighbor[e.from].push_back(e.to);
  }
};
Graph g;
vector<int> Deeps;
vector<deque<unique_ptr<Fringe>>> fringes;
bool dfs(int x, int parent = -1) {
  for (int y : g.neighbor[x]) {
    if (y == parent) continue;
    if (Deeps[y] < 0) {  // tree edge
      fringes.push_back({});
      Deeps[y] = Deeps[x] + 1;
      if (!dfs(y, x)) return false;
    } else if (Deeps[x] > Deeps[y]) {  // back edge
      fringes.back().push_back(make_unique<Fringe>(Deeps[y]));
    }
  }
  try {
    if (fringes.size() > 1) merge_fringes(fringes, Deeps[parent]);
  } catch (const exception& e) {
    return false;
  }
  return true;
}
bool is_planar() {
  Deeps.assign(g.n, -1);
  for (int i = 0; i < g.n; ++i) {
    if (Deeps[i] >= 0) continue;
    fringes.clear();
    Deeps[i] = 0;
    if (!dfs(i)) return false;
  }
  return true;
}
int main() {
  int n, m, u, v;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> u >> v;
    g.add_edge(u, v);
  }
  g.build();
  cout << (is_planar() ? "YES" : "NO") << endl;
  return 0;
}