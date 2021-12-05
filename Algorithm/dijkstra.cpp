#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    // Start Build Bidirectional Graph
    unordered_map<int, unordered_map<int, int>> graph;
    for (const auto &item : road) {
        int u = item[0];
        int v = item[1];
        int w = item[2];
        if (graph[u].find(v) != graph[u].end()) {
            graph[u][v] = graph[u][v] > w ? w : graph[u][v];
        } else {
            graph[u][v] = w;
        }
        if (graph[v].find(u) != graph[v].end()) {
            graph[v][u] = graph[v][u] > w ? w : graph[v][u];
        } else {
            graph[v][u] = w;
        }
    } // End Build Bidirectional Graph

    // Start Single Source Initialization
    unordered_map<int, int> distances;
    for (int i = 1; i <= N; ++i) {
        distances[i] = INT_MAX;
    }
    distances[1] = 0;
    // End Single Source Initialization

    vector<pair<int, int>> queue; // Priority Queue (Dense)
    queue.emplace_back(make_pair(1, 0));
    // Start Dijkstra Algorithm
    while (!queue.empty()) {
        // Start Extract Min (Dense)
        int cur_pi = queue.back().first, cur_dist = queue.back().second;
        queue.pop_back();
        // End Extract Min
        if (distances[cur_pi] >= cur_dist) { // Greedy Algorithm
            // Start for vertex in G.Adj[u]
            for (const auto &item: graph[cur_pi]) {
                // Start Relax
                int pi = item.first, dist = item.second;
                int new_dist = cur_dist + dist;
                if (distances[pi] > new_dist) {
                    distances[pi] = new_dist;
                    queue.emplace_back(make_pair(pi, new_dist));
                } // End Relax
            } // End for vertex in G.Adj[u]
        }
    } // End Dijkstra Algorithm

    for (const auto &item: distances) {
        if (item.second <= K) {
            ++answer;
        }
    }
    return answer;
}