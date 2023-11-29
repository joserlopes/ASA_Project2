/* 2º Projeto de ASA - 2022/2023
 Realizado por :
 José António Lopes - nº103938
 Rodrigo Friães - nº104139
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; 

int *parent;
int *ranks;

typedef struct Edge {
    int cost; 
    pair<int, int> edge_pair;
} edge;

vector<edge> graph;

void MakeSet(int x) {
    parent[x] = x;
    ranks[x] = 0;
}

int FindSet(int x) {
    if (x != parent[x])
        parent[x] = FindSet(parent[x]);
    return parent[x];
}


void Union(int x, int y) {
    if (ranks[x] > ranks[y]) 
        parent[y] = x;
    else 
        parent[x] = y;
    if (ranks[x] == ranks[y])
        ranks[y] = ranks[y] + 1;
}

bool compareCost(edge e1, edge e2) {return e1.cost > e2.cost;}

int main() {
    ios::sync_with_stdio(false);

    int vertices, edges, cost, i, u, v, M = 0;

    cin >> vertices;
    cin >> edges;

    parent = new int[vertices + 1];
    ranks = new int[vertices + 1];

    for (i = 1; i <= vertices; i++)
        MakeSet(i);

    for (i = 0; i < edges; i++) {
        cin >> u; 
        cin >> v;
        cin >> cost;
        graph.push_back(edge());
        graph[i].cost = cost;
        graph[i].edge_pair.first = u;
        graph[i].edge_pair.second = v;
    }

    sort(graph.begin(), graph.end(), compareCost);

    for (i = 0; i < edges; i++) {
        u = graph[i].edge_pair.first;
        v = graph[i].edge_pair.second;
        if (FindSet(u) != FindSet(v)) {
            M += graph[i].cost;
            Union(FindSet(u), FindSet(v));
        }               
    }

    cout << M << endl;

    return 0;
}