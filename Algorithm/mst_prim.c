#include "stdio.h"
#include "limits.h"

int get_min(int num_node, int *key, int *mst_set) {
    int min = INT_MAX;
    int min_idx;

    for (int i = 0; i < num_node; ++i) {
        if (mst_set[i] == 0 && key[i] < min) {
            min = key[i];
            min_idx = i;
        }
    }
    return min_idx;
}

int mst_prim(int num_node, int graph[][num_node]) {
    int parent[num_node];
    int key[num_node];
    int visited[num_node];
    int ret = 0;
    // Source Init
    for (int i = 0; i < num_node; ++i) {
        key[i] = INT_MAX;
        visited[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < num_node - 1; ++i) {
        int u = get_min(num_node, key, visited);
        visited[u] = 1;
        for (int j = 0; j < num_node; ++j) {
            if (graph[u][j] != 0 && visited[j] == 0 && graph[u][j] < key[j]) {
                parent[j] = u;
                key[j] = graph[u][j];
            }
        }
    }

    for (int i = 1; i < num_node; ++i) {
        ret += graph[i][parent[i]];
    }
    return ret;
}

int main() {
    int num_case, num_node, node_num, num_adj, adj_node_num, weight;
    scanf("%d", &num_case);
    for (int i = 0; i < num_case; ++i) {
        scanf("%d", &num_node);

        // init graph
        int arr[num_node][num_node];
        for (int j = 0; j < num_node; ++j) {
            for (int k = 0; k < num_node; ++k) {
                arr[j][k] = 0;
            }
        }

        // build graph
        for (int j = 0; j < num_node; ++j) {
            scanf("%d", &node_num);
            scanf("%d", &num_adj);
            for (int j = 0; j < num_adj; ++j) {
                scanf("%d", &adj_node_num);
                scanf("%d", &weight);
                arr[node_num - 1][adj_node_num - 1] = weight;
            }
        }
        printf("%d\n", mst_prim(num_node, arr));
    }
    return 0;
}
