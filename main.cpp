#include <iostream>
#include <unordered_set>
#include <fstream>

int* computeMwis(int* w, int n) {
    int* A = new int[n+1];
    A[0] = 0;
    A[1] = w[1];
    for (int i = 2; i <= n; i++) {
        A[i] = std::max(A[i-1], A[i-2] + w[i]);
    }

    return A;
}

std::unordered_set<int>* getNodesInMwis(int* A, int* w, int n) {
    auto* s = new std::unordered_set<int>;

    int i = n;
    while(i >= 2) {
        if (A[i-1] >= A[i-2] + w[i]) {
            i--;
        } else {
            s->insert(i);
            i-=2;
        }
    }

    if (i == 1) {
        s->insert(i);
    }

    return s;
}

int hasV(std::unordered_set<int>* s, int v) {
    if (s->find(v) != s->end()) {
        return 1;
    }
    else {
        return 0;
    }
}

struct Data {
    int n;
    int* w;
};

Data* readData() {
    std::ifstream infile("input.txt");

    int n;
    infile >> n;
    int* w = new int[n+1];

    int q;
    int i = 1;
    while (infile >> q) {
        w[i] = q;
        i++;
    }

    Data* d = new Data;
    d->n = n;
    d->w = w;

    return d;
}

int main() {
//    int w[] = {0,3, 2, 1, 6, 4, 5};
//    int n = 6;
    Data* d = readData();
    int n = d->n;
    int* w = d->w;

    int* A = computeMwis(w, n);
    std::unordered_set<int>* s = getNodesInMwis(A, w, n);

    std::cout << hasV(s, 1) << hasV(s, 2) << hasV(s, 3) << hasV(s, 4) << hasV(s, 17)
    << hasV(s, 117) << hasV(s,517) << hasV(s,997) << std::endl;
    return 0;
}
