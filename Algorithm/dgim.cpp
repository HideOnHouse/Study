#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Bucket {
public:
    int start;
    int end;
    Bucket(int start, int end) {
        this->start = start;
        this->end = end;
    }

    friend ostream &operator<<(ostream &out, Bucket bucket) {
        out << '(' << bucket.start << ", " << bucket.end << ')';
        return out;
    }
};

class DGIM {
private:
    vector<vector<Bucket>> bucket_tower;
    int ts;
public:
    DGIM() {
        this->ts = 0;
        bucket_tower.emplace_back(vector<Bucket>());
    }

    void put(int bit) {
        if (bit == 1) {
            Bucket b(this->ts, this->ts);
            this->bucket_tower[0].insert(this->bucket_tower[0].begin(), b);

            int level = 0;
            while (this->bucket_tower[level].size() > 2) {
                if (this->bucket_tower.size() <= level + 1) {
                    this->bucket_tower.push_back(vector<Bucket>());
                }
                Bucket b1 = this->bucket_tower[level].back();
                this->bucket_tower[level].pop_back();
                Bucket b2 = this->bucket_tower[level].back();
                this->bucket_tower[level].pop_back();
                b1.end = b2.end;
                this->bucket_tower[level + 1].insert(this->bucket_tower[level + 1].begin(), b1);
            }
        }
        ++this->ts;
    }

    int count(int k) {
        int s = this->ts - k;
        int ret = 0;
        for (int level = 0; level < this->bucket_tower.size(); ++level) {
            auto buckets = this->bucket_tower[level];
            for (const auto &bucket: buckets) {
                if (s <= bucket.start) {
                    ret += (1 << level);
                } else if (s <= bucket.end) {
                    ret += (1 << level) * (bucket.end - s + 1) / (bucket.end - bucket.start + 1);
                } else {
                    return ret;
                }
            }
        }
        return ret;
    }
};


int main() {
    int stream[100000];
    DGIM d = DGIM();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);
    for (int & i : stream) {
        int bit = distribution(gen);
        i = bit;
        d.put(bit);
    }

    int actual = 0;
    for (int i = 1; i <= 5000; ++i) {
        if (stream[10000 - i] == 1) {
            ++actual;
        }
    }
    printf("actual: %d, estimated: %d", actual, d.count(5000));
    return 0;
}