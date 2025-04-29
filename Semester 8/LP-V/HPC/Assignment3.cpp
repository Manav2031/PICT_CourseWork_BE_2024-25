#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

void fillArray(vector<int> &arr)
{
    int size = arr.size();
#pragma omp parallel for
    for (int i = 0; i < size; ++i)
        arr[i] = size - i; // Reverse order
}

void sequentialOps(const vector<int> &arr, int &min_val, int &max_val, long long &sum_val, double &avg_val)
{
    min_val = INT_MAX;
    max_val = INT_MIN;
    sum_val = 0;

    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i] < min_val)
            min_val = arr[i];
        if (arr[i] > max_val)
            max_val = arr[i];
        sum_val += arr[i];
    }
    avg_val = (double)sum_val / arr.size();
}

void parallelOps(const vector<int> &arr, int &min_val, int &max_val, long long &sum_val, double &avg_val)
{
    min_val = INT_MAX;
    max_val = INT_MIN;
    sum_val = 0;

#pragma omp parallel for reduction(min : min_val)
    for (int i = 0; i < arr.size(); ++i)
        if (arr[i] < min_val)
            min_val = arr[i];

#pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < arr.size(); ++i)
        if (arr[i] > max_val)
            max_val = arr[i];

#pragma omp parallel for reduction(+ : sum_val)
    for (int i = 0; i < arr.size(); ++i)
        sum_val += arr[i];

    avg_val = (double)sum_val / arr.size();
}

int main()
{
    const int size = 100000000;
    vector<int> arr(size);
    fillArray(arr);

    int min_val, max_val;
    long long sum_val;
    double avg_val;

    // Sequential
    auto start = high_resolution_clock::now();
    sequentialOps(arr, min_val, max_val, sum_val, avg_val);
    auto end = high_resolution_clock::now();
    cout << "Sequential:\nMin: " << min_val << ", Max: " << max_val
         << ", Sum: " << sum_val << ", Average: " << avg_val
         << "\nTime: " << duration_cast<milliseconds>(end - start).count() << " ms\n\n";

    // Parallel
    start = high_resolution_clock::now();
    parallelOps(arr, min_val, max_val, sum_val, avg_val);
    end = high_resolution_clock::now();
    cout << "Parallel:\nMin: " << min_val << ", Max: " << max_val
         << ", Sum: " << sum_val << ", Average: " << avg_val
         << "\nTime: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}
