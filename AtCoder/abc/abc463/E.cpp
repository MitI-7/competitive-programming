#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define LEN(x) int(x.size())
#define FOR(i, a, n) for (int i = (a); i < (n); ++i)
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
template <class T, class U> void print(const std::pair<T, U>& p) { std::cout << p.first << " " << p.second << '\n'; }
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

    Edge() : from(-1), to(-1), w(T{}), no(-1) {}

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

    void add_directed_edge(const int u, const int v, const T &w, const int no) {
        this->no_edge[no] = {u, this->graph[u].size()};
        this->graph[u].emplace_back(Edge(u, v, w, no));
        ++this->num_edges;
    }

    void add_directed_edge(const int u, const int v, const T &w = T{1}) {
        const int no = num_edges;
        this->add_directed_edge(u, v, w, no);
    }

    Edge<T> &get_edge(const int no) {
        const auto [u, i] = this->no_edge.at(no);
        return this->graph[u][i];
    }

    std::vector<Edge<T>> &operator[](const int u) {
        return this->graph[u];
    }
};


/**
 * s からすべての頂点への最短距離と，各頂点に接続する最短距離となる辺を求める
 * O(|E| log |V|)
 * 到達できない場合は infinity を格納する
 * 負辺はないものとする
 */
template<typename T>
std::pair<std::vector<T>, std::vector<Edge<T>>> dijkstra(const int s, const Graph<T> &graph, const T infinity = std::numeric_limits<T>::max() / 3) {

    // [(最短距離, node番号)]のque (距離が近い順にとりだす)
    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<>> que;
    que.push({0, s});

    std::vector<Edge<T>> prev_edge(graph.num_nodes);       // 経路復元用
    std::vector<bool> seen(graph.num_nodes);
    std::vector<T> distance(graph.num_nodes, infinity);   // startからの距離
    distance[s] = 0;

    while (not que.empty()) {
        const auto [now_dist, u] = que.top();
        que.pop();
        if (seen[u]) {
            continue;
        }
        seen[u] = true;

        for (const auto& edge: graph.graph[u]) {
            const auto new_dist = now_dist + edge.w;
            if (new_dist < distance[edge.to]) {
                prev_edge[edge.to] = edge;
                distance[edge.to] = new_dist;
                que.push({new_dist, edge.to});
            }
        }
    }

    return {distance, prev_edge};
}

using namespace std;


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, M, Y;
    cin >> N >> M >> Y;

    Graph<LL> g(N + 2);
    FOR(i, 0, M) {
        int U, V, T;
        cin >> U >> V >> T;
        U--;
        V--;
        g.add_directed_edge(U, V, T);
        g.add_directed_edge(V, U, T);
    }

    const int gate1 = N;
    const int gate2 = N + 1;
    g.add_directed_edge(gate1, gate2, Y);

    FOR(i, 0, N) {
        int X;
        cin >> X;
        g.add_directed_edge(i, gate1, X);
        g.add_directed_edge(gate2, i, X);
    }

    auto [ans, _] = dijkstra(0, g, LINF);
    ans.erase(ans.begin());
    ans.pop_back();
    ans.pop_back();
    print(ans);

    return 0;
}
