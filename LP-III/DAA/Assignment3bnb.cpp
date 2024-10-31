#include <bits/stdc++.h>
using namespace std;

// Structure to represent items with weight and value
struct Item {
    int weight;
    int value;
};

// Function to calculate the upper bound for a node
int bound(int currentValue, int currentWeight, int index, int capacity, vector<Item>& items) {
    if (currentWeight >= capacity) return 0; // No bound if capacity exceeded
    int boundValue = currentValue;
    int totalWeight = currentWeight;

    for (int i = index; i < items.size(); ++i) {
        if (totalWeight + items[i].weight <= capacity) {
            totalWeight += items[i].weight;
            boundValue += items[i].value;
        } else {
            boundValue += items[i].value * (capacity - totalWeight) / items[i].weight;
            break;
        }
    }
    return boundValue;
}

// Recursive Branch and Bound function
int knapsackBB(int index, int currentWeight, int currentValue, int capacity, vector<Item>& items, int& maxValue) {
    // Base case: end of items
    if (index == items.size()) return currentValue;

    // Check if the current solution is better
    if (currentValue > maxValue) maxValue = currentValue;

    // Calculate bound to decide whether to explore this branch
    int upperBound = bound(currentValue, currentWeight, index + 1, capacity, items);
    if (upperBound <= maxValue) return maxValue; // Prune if bound is not promising

    // Recursive calls
    if (currentWeight + items[index].weight <= capacity) {
        // Choose the current item
        knapsackBB(index + 1, currentWeight + items[index].weight, currentValue + items[index].value, capacity, items, maxValue);
    }
    // Do not choose the current item
    knapsackBB(index + 1, currentWeight, currentValue, capacity, items, maxValue);

    return maxValue;
}

int main() {
    int n, capacity;
    cout << "Enter the number of items: ";
    cin >> n;
    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter weight and value of item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }
    cout << "Enter the knapsack capacity: ";
    cin >> capacity;

    int maxValue = 0;
    knapsackBB(0, 0, 0, capacity, items, maxValue);

    cout << "Maximum value in the knapsack = " << maxValue << endl;
    return 0;
}