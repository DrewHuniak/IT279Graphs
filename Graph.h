#ifndef GRAPH_H
#define GRAPH_H

// Graph Class that does multiple operators such as - Minimum Spanning Tree - Topological Sort - Shortest Path. 
// by Drew Huniak

#include <iostream>
#include <string>
#include "vector"


using namespace std;

/* A Struct for handling values for the shortest path algorithm and Minimum spanning tree*/
struct Vertex
{
    int prev;
    int next;  //Used for the minimum spanning tree
    int cost; 
    //Used for the priority que
    bool operator>(const Vertex &vert) const 
    {
        return cost > vert.cost;   
    }
    //Used for the sort
    bool operator<(const Vertex &vert) const  
    {
        return cost < vert.cost;
    }

};

class Graph
{
    private:
        vector<vector<int>> matrix;
        int vertices;
        int edges;
        vector<string> vertexNames;
    public:
        /* Default Constructor */
        Graph();

        /* Takes in a filename and reads the data into the graph matrix. */
        bool readGraph(string fileName);
        
        /* Prints the original graph given in file format. */
        void printGraph();

        /* Performs and prints a topological sort on the graph using a queue */
        void computeTopologicalSort();

        /* Performs and prints the shortest path given a nodeName using Dijkstra's algorithm. */
        void computeShortestPaths(string nodeName);

        // Precondition: Graph must be connected
        // Finds the minimum spanning tree assuming that the graph is not directed using Kruskal's algorithm.
        void computeMinimumSpanningTree();

    private:

        /* A recursive function that helps the computeShortestPath() function print each path */
        void printShortestPath(vector<int> &parent, int i);

        /* Returns the index of a vertex given its name. */
        int nameToIndex(string name);

};

#endif