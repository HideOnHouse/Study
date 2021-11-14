#include <vector>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef struct vertex {
    int distance;
    vertex *pi;
} vertex;

void relex(vertex &u, vertex &v, int weight) {
    int temp = u.distance + weight;
    if (v.distance > temp) {
        v.distance = temp;
        v.pi = &u;
    }
}

int main() {
    
    return 0;
}