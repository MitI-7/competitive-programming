#include <algorithm>
#include <array>
#include <assert.h>
#include <bitset>
#include <climits>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define LEN(x) int(x.size())
#define FOR(i, a, n) for (int i = (a); i < (n); ++i)
#define FOE(i, a) for (auto i: a)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SUM(x) std::accumulate(ALL(x), 0LL)
#define MIN(v) *std::min_element(v.begin(), v.end())
#define MAX(v) *std::max_element(v.begin(), v.end())
#define EXIST(v, x) (std::find(v.begin(), v.end(), x) != v.end())
#define IS_BIT_ON(bit, i) (bit & (1 << i))
#define BIT_ON(bit, i) (bit |= (1 << i))
#define BIT_OFF(bit, i) (bit &= ~(1 << i))
#define BIT_COUNT(bit) (__builtin_popcount(bit))

// clang-format off
// @formatter:off
typedef long long LL;
typedef __int128_t LLL;
template<typename T> std::vector<T> make_v(size_t a){return std::vector<T>(a);}
template<typename T,typename... Ts> auto make_v(size_t a, Ts... ts){ return std::vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));}    // C++14
template<typename T,typename V> typename std::enable_if<std::is_class<T>::value==0>::type fill_v(T &t,const V &v){t=v;}
template<typename T,typename V> typename std::enable_if<std::is_class<T>::value!=0>::type fill_v(T &t,const V &v){for(auto &e:t) fill_v(e,v);}
template<class T> inline T ceil(T a, T b) { return (a + b - 1) / b; }
void print() { std::cout << std::endl; }
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) { std::cout << head; if (sizeof...(tail) != 0) {std::cout << " ";} print(std::forward<Tail>(tail)...); }
template <class T> void print(std::vector<T> &v) {for (auto& a : v) { std::cout << a; if (&a != &v.back()) {std::cout << " ";} }std::cout << std::endl;}
template <class T> void print(std::pair<T, T> &p) { std::cout << p.first << " " << p.second << std::endl; }
void debug() { std::cerr << std::endl; }
template <class Head, class... Tail> void debug(Head&& head, Tail&&... tail) { std::cerr << head; if (sizeof...(tail) != 0) {std::cerr << " ";} debug(std::forward<Tail>(tail)...); }
template <class T> void debug(std::vector<T> &v) {for (auto& a : v) { std::cerr << a; if (&a != &v.back()) {std::cerr << " ";} }std::cerr << std::endl;}
template <class T> void debug(std::pair<T, T> &p) { std::cerr << p.first << " " << p.second << std::endl; }
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= y and y < H and 0 <= x and x < W; }
template<class T> inline double euclidean_distance(T y1, T x1, T y2, T x2) { return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); }
template<class T> inline T euclidean_distance2(T y1, T x1, T y2, T x2) { return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); }
template<class T> inline T manhattan_distance(T y1, T x1, T y2, T x2) { return abs(x1 - x2) + abs(y1 - y2); }
template<typename T> T &chmin(T &a, const T &b) { return a = std::min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = std::max(a, b); }
bool is_bit_on(const unsigned long long bit, const unsigned int i) { return (bit >> i) & 1u; }
unsigned long long get_bit_set(const unsigned long long bit, const unsigned int i, const unsigned int b) { assert(b == 0 or b == 1); if (b == 0) { return bit & ~(1ull << i); } else {return bit | (1ull << i);}}

const int INF = 1u << 30u;  // 1,073,741,824
const long long LINF = 1ull << 60u;
const double EPS = 1e-9;
const long double PI = acos(-1.0);
// 2次元配列上での移動．右，下，左，上，右上，右下，左下，左上
const std::vector<int> dy8 = {0, 1, 0, -1, -1, 1, 1, -1}, dx8 = {1, 0, -1, 0, 1, 1, -1, -1};
// @formatter:on
// clang-format on

template<typename T>
class Edge {
public:
    int from;
    int to;
    T w;
    int no;

    Edge() : from(-1), to(-1), w(-1), no(-1) {}

    Edge(const int from, const int to, const T w = 1, const int no = -1) : from(from), to(to), w(w), no(no) {}
};

template<typename T = int>
class Graph {
public:
    const int num_nodes;
    int num_edges;
    std::vector<std::vector<Edge<T>>> graph;
    std::unordered_map<int, std::pair<int, int>> no_edge;

    explicit Graph(const int num_nodes) : num_nodes(num_nodes), num_edges(0) {
        this->graph.resize(num_nodes);
    }

    void add_directed_edge(const int u, const int v, const T w = 1, const int no = -1) {
        this->no_edge[no] = {u, this->graph[u].size()};
        this->graph[u].emplace_back(Edge(u, v, w, no));
        ++this->num_edges;
    }

    Edge<T> &get_edge(const int no) {
        const auto [u, i] = this->no_edge[no];
        return this->graph[u][i];
    }

    std::vector<Edge<T>> &operator[](const int u) {
        return this->graph[u];
    }
};

template<typename T>
bool find_cycle_dfs(const int u, const Edge<T> &prev, std::vector<int> &state, std::vector<Edge<T>> &edges, const Graph<T> &graph) {
    state[u] = 1;
    for (const auto e: graph.graph[u]) {
        if (e.no == prev.no) {
            continue;
        }

        // 探索済み
        if (state[e.to] == 2) {
            continue;
        }

        edges.emplace_back(e);
        // find cycle
        if (state[e.to] == 1 or find_cycle_dfs(e.to, e, state, edges, graph)) {
            return true;
        }
        edges.pop_back();
    }

    state[u] = 2;
    return false;
}

// 有効/無向グラフのサイクルをひとつ見つける
// 単純グラフでなくてもいい
// O(N + M)
// 辺番号をいれておくこと
template<typename T>
std::vector<Edge<T>> find_cycle(const Graph<T> &graph) {
    std::vector<Edge<T>> edges;
    std::vector<int> state(graph.num_nodes, 0); // 0: 未探索， 1: 探索中，2: 探索済み

    // u を始点とし，閉路を探索
    std::vector<Edge<T>> cycle;
    for (int u = 0; u < graph.num_nodes; ++u) {
        if (state[u] != 0) {
            continue;
        }
        if (find_cycle_dfs(u, Edge(-1, -1, 0, -1), state, edges, graph)) {
            auto cycle_start = edges.back().to;
            bool in_cycle = false;
            for (auto e: edges) {
                // cycle の開始ノードを見つけた
                if (e.from == cycle_start) {
                    in_cycle = true;
                }
                if (in_cycle) {
                    cycle.emplace_back(e);
                }
            }
            break;
        }
    }

    return cycle;
}

using namespace std;

bool solve() {
    int N, M;
    cin >> N >> M;

    Graph city_graph(N);
    FOR(i, 0, N) {
        city_graph.add_directed_edge(i, i);
    }
    FOR(_, 0, M) {
        int U, V;
        cin >> U >> V;
        U--;
        V--;
        city_graph.add_directed_edge(U, V);
        city_graph.add_directed_edge(V, U);
    }

    int W;
    cin >> W;
    vector<string> state(N);
    FOR(i, 0, N) {
        string S;
        cin >> S;
        state[i] = S;
    }

    Graph graph(N * W);
    int edge_no = 0;
    FOR(t1, 0, N) {
        FOR(d1, 0, W) {
            if (state[t1][d1] == 'x') {
                continue;
            }

            const int no1 = t1 * W + d1;
            const int d2 = (d1 + 1) % W;

            FOE(e, city_graph[t1]) {
                const int t2 = e.to;
                const int no2 = t2 * W + d2;
                if (state[t2][d2] == 'o') {
                    graph.add_directed_edge(no1, no2, 0, edge_no++);
                }
            }
        }
    }

    return not find_cycle(graph).empty();
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    FOR(_, 0, T) {
        if (solve()) {
            print("Yes");
        } else {
            print("No");
        }
    }

    return 0;
}
