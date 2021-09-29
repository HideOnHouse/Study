#include <utility>

#include "vector"
#include "iostream"

using namespace std;


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void max_heapify(vector<int> &a, int idx, int k) {
    int left = idx * 2 + 1;
    int right = idx * 2 + 2;
    int largest;
    if (left < k and a[left] > a[idx]) {
        largest = left;
    } else {
        largest = idx;
    }
    if (right < k and a[right] > a[largest]) {
        largest = right;
    }
    if (largest != idx) {
        swap(a[idx], a[largest]);
        max_heapify(a, largest, k);
    }
}


void build_max_heap(vector<int> &a, int k) {
    for (int i = k / 2 - 1; i >= 0; --i) {
        max_heapify(a, i, k);
    }
}


void heap_sort(vector<int> &a, int k) {
    int length = static_cast<int>(a.size());
    int _size = length;
    build_max_heap(a, _size);
    for (int i = length - 1; i >= k; --i) {
        swap(a[0], a[i]);
        _size--;
        max_heapify(a, 0, _size);
    }
}


vector<int> solution(vector<int> a, int k) {
    vector<int> answer(std::move(a));
    heap_sort(answer, k);
    return answer;
}

int main() {
    vector<int> v;
    v.reserve(100);
    for (int i = 0; i < 100; ++i) {
        v.emplace_back(99 - i);
    }
    for (const auto &item: v) {
        cout << item << " ";
    }
    cout << endl;
    v = solution(v, 0);
    for (const auto &item: v) {
        cout << item << " ";
    }
    cout << endl;
}