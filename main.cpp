#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int TOTAL_CYLINDERS = 5000;

int runFCFS(int head, vector<int> reqs) {
    int total = 0;
    for (int r : reqs) {
        total += abs(r - head);
        head = r;
    }
    return total;
}

int runSSTF(int head, vector<int> reqs) {
    int total = 0;
    while (!reqs.empty()) {
        int closest_idx = 0;
        int min_dist = abs(reqs[0] - head);
        for (size_t i = 1; i < reqs.size(); ++i) {
            int dist = abs(reqs[i] - head);
            if (dist < min_dist) {
                min_dist = dist;
                closest_idx = i;
            }
        }
        total += min_dist;
        head = reqs[closest_idx];
        reqs.erase(reqs.begin() + closest_idx);
    }
    return total;
}

int runSCAN(int head, vector<int> reqs) {
    int total = 0;
    vector<int> left, right;
    for (int r : reqs) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) {
        total += abs(r - head);
        head = r;
    }
    
    if (!right.empty() || head < TOTAL_CYLINDERS - 1) {
        total += abs((TOTAL_CYLINDERS - 1) - head);
        head = TOTAL_CYLINDERS - 1;
    }

    for (int i = left.size() - 1; i >= 0; --i) {
        total += abs(left[i] - head);
        head = left[i];
    }
    return total;
}

int runLOOK(int head, vector<int> reqs) {
    int total = 0;
    vector<int> left, right;
    for (int r : reqs) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) {
        total += abs(r - head);
        head = r;
    }

    for (int i = left.size() - 1; i >= 0; --i) {
        total += abs(left[i] - head);
        head = left[i];
    }
    return total;
}

int runCSCAN(int head, vector<int> reqs) {
    int total = 0;
    vector<int> left, right;
    for (int r : reqs) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) {
        total += abs(r - head);
        head = r;
    }

    if (!right.empty() || head < TOTAL_CYLINDERS - 1) {
        total += abs((TOTAL_CYLINDERS - 1) - head);
        head = TOTAL_CYLINDERS - 1;
    }

    total += abs((TOTAL_CYLINDERS - 1) - 0);
    head = 0;

    for (int r : left) {
        total += abs(r - head);
        head = r;
    }
    return total;
}

int runCLOOK(int head, vector<int> reqs) {
    int total = 0;
    vector<int> left, right;
    for (int r : reqs) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) {
        total += abs(r - head);
        head = r;
    }

    if (!left.empty()) {
        total += abs(left[0] - head);
        head = left[0];
        for (size_t i = 1; i < left.size(); ++i) {
            total += abs(left[i] - head);
            head = left[i];
        }
    }
    return total;
}

int main() {
    int initial_head = 2150;
    vector<int> requests = {2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681};

    cout << "Initial Head Position: " << initial_head << endl << endl;

    cout << "a. FCFS:   " << runFCFS(initial_head, requests) << " cylinders" << endl;
    cout << "b. SSTF:   " << runSSTF(initial_head, requests) << " cylinders" << endl;
    cout << "c. SCAN:   " << runSCAN(initial_head, requests) << " cylinders" << endl;
    cout << "d. LOOK:   " << runLOOK(initial_head, requests) << " cylinders" << endl;
    cout << "e. C-SCAN: " << runCSCAN(initial_head, requests) << " cylinders" << endl;
    cout << "f. C-LOOK: " << runCLOOK(initial_head, requests) << " cylinders" << endl;

    return 0;
}