#include <iostream>
#include <string>
#include <vector>

using namespace std;


void merge(vector<pair<int, string>> &v, pair<int, string> *answer, int left, int right) {

    int mid = (left + right) / 2;
    int first_idx, second_idx, idx, l;
    first_idx = left;
    second_idx = mid + 1;
    idx = left;

    // sort
    while (first_idx <= mid && second_idx <= right) {
        if (v[first_idx].first >= v[second_idx].first) {
            answer[idx] = v[first_idx];
            idx++;
            first_idx++;
        } else {
            answer[idx] = v[second_idx];
            idx++;
            second_idx++;
        }
    }

    // handle remains
    if (first_idx > mid) {
        for (l = second_idx; l <= right; l++) {
            answer[idx] = v[l];
            idx++;
        }
    } else {
        for (l = first_idx; l <= mid; l++) {
            answer[idx] = v[l];
            idx++;
        }
    }

    // copy vector
    for (l = left; l <= right; l++) {
        v[l] = answer[l];
    }
}

void mergesort(vector<pair<int, string> > &v, pair<int, string> *answer, int p, int r) {
    if (p < r) {
        int mid = (p + r) / 2;
        mergesort(v, answer, p, mid);
        mergesort(v, answer, mid + 1, r);
        merge(v, answer, p, r);
    }
}

void merge_sort(vector<pair<int, string> > &v, int p, int r) {
    pair<int, string> answer[v.size()];
    mergesort(v, answer, p, r);
}


int main() {
    int n;
    vector<pair<int, string> > v;

    cin >> n;
    // input data
    for (int i = 0; i < n; i++) {
        int d;
        string s;
        cin >> d >> s;
        v.emplace_back(d, s);
    }

    // merge sort
    merge_sort(v, 0, v.size() - 1);

    for (int i = 0; i < n; i++) {
        cout << v[i].first << ' ' << v[i].second << endl;
    }

    return 0;
}