#include <bits/stdc++.h>
using namespace std;

// Function to solve 0-1 Knapsack problem using dynamic programming
int knapsackDP(int capacity, vector<int>& weights, vector<int>& values, int n) {
    // Creating a DP table to store the maximum values
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build table dp[][] in bottom-up manner
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                // Maximize value by including or excluding the current item
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                // If item can't be included, carry forward the previous value
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    // Return the maximum value that can be achieved with given capacity
    return dp[n][capacity];
}

int main() {
    int n; // Number of items
    int capacity; // Maximum weight capacity of knapsack

    cout << "Enter the number of items: ";
    cin >> n;
    
    vector<int> weights(n), values(n);
    
    cout << "Enter the weight and value of each item:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << endl;
        cout<<"Weight: ";
        cin >> weights[i];
        cout << "Value: ";
        cin >> values[i];
    }

    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> capacity;

    int maxValue = knapsackDP(capacity, weights, values, n);

    cout << "Maximum value in knapsack: " << maxValue << endl;

    return 0;
}