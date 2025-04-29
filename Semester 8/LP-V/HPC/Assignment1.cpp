#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected
    }

    void sequentialBFS(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void parallelBFS(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int size = q.size();
            vector<int> currentLevel;
            for (int i = 0; i < size; ++i)
            {
                int node = q.front();
                q.pop();
                currentLevel.push_back(node);
            }

#pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); ++i)
            {
                int node = currentLevel[i];
                for (int neighbor : adj[node])
                {
                    if (!visited[neighbor])
                    {
#pragma omp critical
                        {
                            if (!visited[neighbor])
                            {
                                visited[neighbor] = true;
                                q.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }

    void sequentialDFS(int start)
    {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);

        while (!s.empty())
        {
            int node = s.top();
            s.pop();
            if (!visited[node])
            {
                visited[node] = true;
                for (int neighbor : adj[node])
                {
                    if (!visited[neighbor])
                    {
                        s.push(neighbor);
                    }
                }
            }
        }
    }

    void parallelDFS(int start)
    {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);

        while (!s.empty())
        {
            int node = s.top();
            s.pop();
            if (!visited[node])
            {
                visited[node] = true;
#pragma omp parallel for
                for (int i = 0; i < adj[node].size(); ++i)
                {
                    int neighbor = adj[node][i];
                    if (!visited[neighbor])
                    {
#pragma omp critical
                        s.push(neighbor);
                    }
                }
            }
        }
    }
};

int main()
{
    int V = 100000;
    Graph g(V);

    // Add edges to make a sparse graph (or adjust for density)
    for (int i = 0; i < V - 1; ++i)
    {
        g.addEdge(i, i + 1);
        if (i % 100 == 0 && i + 100 < V)
        {
            g.addEdge(i, i + 100);
        }
    }

    auto start = high_resolution_clock::now();
    g.sequentialBFS(0);
    auto end = high_resolution_clock::now();
    cout << "Sequential BFS Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    g.parallelBFS(0);
    end = high_resolution_clock::now();
    cout << "Parallel BFS Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    g.sequentialDFS(0);
    end = high_resolution_clock::now();
    cout << "Sequential DFS Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    g.parallelDFS(0);
    end = high_resolution_clock::now();
    cout << "Parallel DFS Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}
