#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// ------------------ BUBBLE SORT ------------------

void sequentialBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; ++i)
    {
        if (i % 2 == 0)
        {
#pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2)
            {
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
            }
        }
        else
        {
#pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2)
            {
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ------------------ MERGE SORT ------------------

void merge(vector<int> &arr, int l, int m, int r)
{
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < left.size())
        arr[k++] = left[i++];
    while (j < right.size())
        arr[k++] = right[j++];
}

void sequentialMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void parallelMergeSort(vector<int> &arr, int l, int r, int depth = 0)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        if (depth <= 3)
        {
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(arr, l, m, depth + 1);
#pragma omp section
                parallelMergeSort(arr, m + 1, r, depth + 1);
            }
        }
        else
        {
            sequentialMergeSort(arr, l, m);
            sequentialMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

// ------------------ PRINT FUNCTION ------------------

void printArray(vector<int> &arr, const string &label, int limit = 100)
{
    cout << label << " (first " << limit << " elements): ";
    for (int i = 0; i < min((int)arr.size(), limit); ++i)
        cout << arr[i] << " ";
    cout << "\n\n";
}

// ------------------ MAIN ------------------

int main()
{
    int size = 100000;
    vector<int> arr(size), temp;

    // Fill array in reverse order for worst-case sorting
    for (int i = 0; i < size; ++i)
        arr[i] = size - i;

    temp = arr;
    auto start = high_resolution_clock::now();
    sequentialBubbleSort(temp);
    auto end = high_resolution_clock::now();
    cout << "Sequential Bubble Sort: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
    printArray(temp, "Sorted Array (Sequential Bubble Sort)");

    temp = arr;
    start = high_resolution_clock::now();
    parallelBubbleSort(temp);
    end = high_resolution_clock::now();
    cout << "Parallel Bubble Sort:   " << duration_cast<milliseconds>(end - start).count() << " ms\n";
    printArray(temp, "Sorted Array (Parallel Bubble Sort)");

    temp = arr;
    start = high_resolution_clock::now();
    sequentialMergeSort(temp, 0, temp.size() - 1);
    end = high_resolution_clock::now();
    cout << "Sequential Merge Sort:  " << duration_cast<milliseconds>(end - start).count() << " ms\n";
    printArray(temp, "Sorted Array (Sequential Merge Sort)");

    temp = arr;
    start = high_resolution_clock::now();
    parallelMergeSort(temp, 0, temp.size() - 1);
    end = high_resolution_clock::now();
    cout << "Parallel Merge Sort:    " << duration_cast<milliseconds>(end - start).count() << " ms\n";
    printArray(temp, "Sorted Array (Parallel Merge Sort)");

    return 0;
}
