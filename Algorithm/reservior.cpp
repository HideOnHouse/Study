#include <iostream>
#include <random>

using namespace std;

class Reservior {
private:
    unsigned int seed;
public:
    int k;
    int *sampled;
    int count;
    mt19937 gen;

    explicit Reservior(int k) {
        this->k = k;
        this->count = 0;
        this->sampled = new int[k];

        static random_device rd;
        this->seed = rd();
        this->gen.seed(this->seed);
    }

    void put(int item) {
        if (this->count < this->k) {
            this->sampled[count] = item;
        } else {
            uniform_int_distribution<int> dist(0, this->count);
            int r = dist(this->gen);
            if (r < this->k) {
                this->sampled[r] = item;
            }
        }
        ++(this->count);
    }

    friend ostream &operator<<(ostream &out, const Reservior &r) {
        for (int i = 0; i < r.count; ++i) {
            out << r.sampled[i] << ',';
        }
        return out;
    }

    ~Reservior() {
        delete[]this->sampled;
    }
};

class SWR {
private:
    unsigned int seed;
public:
    int k;
    int *sampled;
    int count;
    mt19937 gen;

    explicit SWR(int k) {
        this->k = k;
        this->count = 0;
        this->sampled = new int[k];

        static random_device rd;
        this->seed = rd();
        this->gen.seed(this->seed);
    }

    void put(int item) {
        uniform_int_distribution<int> dist(0, this->count);
        for (int i = 0; i < this->k; ++i) {
            int r = dist(this->gen);
            if (r < 1) {
                this->sampled[i] = item;
            }
        }
        ++(this->count);
    }

    friend ostream &operator<<(ostream &out, const SWR &s) {
        for (int i = 0; i < s.count; ++i) {
            out << s.sampled[i] << ',';
        }
        return out;
    }

    ~SWR() {
        delete[]this->sampled;
    }
};

void plot_counter(const int *counter, int counter_size, int bins, int unit = 100) {
    float interval = (float) (counter_size) / (float) (bins);
    float idx = 0.0;

    while (true) {
        int temp = 0;
        int start = (int) idx;
        int end = (int) (idx + interval);
        if (end >= counter_size) {
            break;
        }
        printf("%4d~%-4d: ", start, end);
        for (int i = start; i <= end; ++i) {
            temp += counter[i];
        }
        for (int i = 0; i < temp / unit; ++i) {
            cout << '*';
        }
        cout << " (" << temp << ')' << endl;
        idx += interval;
    }
}

int main() {
    // Reservoir with replacement
    int counter[1000]{};
    for (int _ = 0; _ < 1000; ++_) {
        Reservior r(100);
        for (int i = 0; i < 1000; ++i) {
            r.put(i);
        }
        for (int i = 0; i < 100; ++i) {
            ++counter[r.sampled[i]];
        }
    }
    cout << "Reservoir with replacement result" << endl;
    plot_counter(counter, 1000, 30);

    // Reservoir Without Replacement
    for (auto &item: counter) {
        item = 0;
    }
    for (int _ = 0; _ < 1000; ++_) {
        SWR r(100);
        for (int i = 0; i < 1000; ++i) {
            r.put(i);
        }
        for (int i = 0; i < r.k; ++i) {
            ++counter[r.sampled[i]];
        }
    }
    cout << "Reservoir without replacement result" << endl;
    plot_counter(counter, 1000, 30);
    return 0;
}
