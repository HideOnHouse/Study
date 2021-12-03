#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int src;
    int dst;
    int weight;
} edge;

int find_root(int v[], int x) {
    while (x != v[x]) {
        x = v[x];
    }
    return v[x];
}

void do_union(int v[], int a, int b) {
    int x = find_root(v, a);
    int y = find_root(v, b);
    if (x > y) {
        v[x] = y;
    } else {
        v[y] = x;
    }
}

int cmp(const void *a, const void *b) {
    int w1 = ((edge *) a)->weight;
    int w2 = ((edge *) b)->weight;
    if (w1 > w2) {
        return 1;
    } else if (w1 == w2) {
        return 0;
    } else {
        return -1;
    }
}


int main() {
    int num_case, num_node, node_num, ret, v, num_edge, num_adj, adj_node_num, weight;
    scanf("%d", &num_case);
    for (int _ = 0; _ < num_case; ++_) {
        scanf("%d", &num_node);

        // init
        ret = 0;
        v = 0;
        num_edge = 0;
        edge edges[(num_node + 1) * (num_node + 1)];
        int connected[num_node + 1];
        for (int i = 1; i <= num_node; i++) {
            connected[i] = i;
        }

        // build
        for (int i = 0; i < num_node; ++i) {
            scanf("%d %d", &node_num, &num_adj);
            for (int k = 0; k < num_adj; ++k) {
                scanf("%d %d", &adj_node_num, &weight);
                if (adj_node_num > node_num) {
                    edges[num_edge].src = node_num;
                    edges[num_edge].dst = adj_node_num;
                    edges[num_edge].weight = weight;
                    ++num_edge;
                }
            }
        }

        // Kruskal
        qsort(edges, num_edge, sizeof(edge), cmp);
        for (int i = 0; i < num_edge; i++) {
            if (find_root(connected, edges[i].src) != find_root(connected, edges[i].dst)) {
                ret += edges[i].weight;
                do_union(connected, edges[i].src, edges[i].dst);
                ++v;
            }
            if (v == num_node - 1) {
                break;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
