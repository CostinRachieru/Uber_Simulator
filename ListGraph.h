// Copyright 2019 Rachieru Costin Tudor <<costinrch46@gmail.com>>

#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_

#include <queue>
#include <vector>
#include <string>


template <typename T> struct Node {
    std::vector<T> neighbors;
    std::string name;
    Node() {
        name = "name";
    }
};


template <typename T> class ListGraph {
 public:
    std::vector<Node<T>> nodes;
    int size;

    // Constructor
    explicit ListGraph(int size) {
        this->size = size;
        for (int i = 0; i < size; i++) {
            nodes.push_back(Node<T>());
        }
    }

    // Destructor
    ~ListGraph() {}

    // Adds an edge between two existing nodes.
    void addEdge(T src, T dst) {
        nodes[src].neighbors.push_back(dst);
    }

    // Adds a name to a node.
    void addName(T node, std::string name) {
        nodes[node].name = name;
    }

    // Removes an existing edge from the graph.
    void removeEdge(T src, T dst) {
        for (int i = 0; i < (int)nodes[src].neighbors.size(); i++) {
            if (nodes[src].neighbors[i] == dst) {
                nodes[src].neighbors.erase(nodes[src].neighbors.begin()+i);
            }
        }
    }

    // Checks if there is an edge between two existing nodes.
    bool hasEdge(T src, T dst) {
        for (unsigned int i = 0; i < nodes[src].neighbors.size(); i++) {
            if (nodes[src].neighbors[i] == dst) {
                return true;
            }
        }
        return false;
    }

    // Checks if there is a path between two nodes.
    bool isPath(T src, T dst) {
        if (src == dst) {
            return true;
        }
        int *color = new int[size];
        std::queue<int> Q;
        int i, j, aux, auxx, white = 0, grey = 1, black = 2;
        for (i = 0; i < size; i++) {
            color[i] = white;
        }
        color[src] = grey;
        Q.push(src);

        while (!Q.empty()) {
            aux = Q.front();
            Q.pop();
            for (j = 0; j < (int)nodes[aux].neighbors.size(); j++) {
                auxx = nodes[aux].neighbors[j];
                if (auxx == dst) {
                    delete[] color;
                    return true;
                }
                if (color[auxx] == white) {
                    color[auxx] = grey;
                    Q.push(auxx);
                }
            }
            color[aux] = black;
        }
        delete[] color;
        return false;
    }

    // Computes the distance between two nodes.
    int Distance(T src, T dst) {
        if (src == dst) {
            return 0;
        }
        int *color = new int[size];
        int *d = new int[size];
        std::queue<int> Q;
        int i, j, dist, aux, auxx, white = 0, grey = 1, black = 2;
        for (i = 0; i < size; i++) {
            color[i] = white;
            d[i] = size + 1;
        }
        color[src] = grey;
        d[src] = 0;
        Q.push(src);

        while (!Q.empty()) {
            aux = Q.front();
            Q.pop();
            for (j = 0; j < (int)nodes[aux].neighbors.size(); j++) {
                auxx = nodes[aux].neighbors[j];
                if (color[auxx] == white) {
                    color[auxx] = grey;
                    d[auxx] = d[aux] + 1;
                    Q.push(auxx);
                }
                if (auxx == dst) {
                    delete[] color;
                    dist = d[auxx];
                    delete[] d;
                    return dist;
                }
            }
            color[aux] = black;
        }
        delete[] color;
        delete[] d;
        return -1;
    }

    // Gets the graph size.
    int getSize() {
        return size;
    }
};

#endif  // LISTGRAPH_H_
