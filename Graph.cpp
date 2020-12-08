#include "Graph.h"
#include <algorithm> //std::sort
#include <queue>
#include <fstream>
#include "DisjointSet.h"
// Implimentation for the Graph class
// by Drew Huniak
Graph::Graph()
{
    vertices = 0;
    edges = 0;
}

bool Graph::readGraph(string filename)
{
    // matrix.erase(matrix.begin(), matrix.end());
    // vertexNames.erase(vertexNames.begin(), vertexNames.end());
   
    matrix.clear();
    vertexNames.clear();

    ifstream stream(filename);
    if(!stream.is_open())
    {
        return false;
    }
    else
    {
        stream>>vertices;
        
        string names = "";

        for(int i = 0; i < vertices; i++)
        {
            stream >> names;
            vertexNames.push_back(names);
        }
        stream >> edges;

        //Copy the remaining edge data
        string first;
        string second;
        int x, y;
        int weight;
        matrix.resize(vertices, vector<int> (vertices));

        for(int i = 0; i < edges; i++)
        {
            stream >> first;
            stream >> second;
            stream >> weight;
    
            x = nameToIndex(first);
            y = nameToIndex(second);

            matrix[x][y] = weight;
        }
        stream.close();
        return true;
    }
}

void Graph::printGraph()
{
    cout<<vertices<<endl;
    for(int i = 0; i < vertexNames.size(); i++)
    {
        cout<<vertexNames[i]<<endl;
    }
    cout<<edges<<endl;
    for(int i = 0; i < vertices; i++)
    {
        for(int j = 0; j < vertices; j++)
        {
            if(matrix[i][j] > 0)
            {
                cout<<vertexNames[i]<<" "<<vertexNames[j]<<" "<<matrix[i][j]<<endl;
            }
        }
    }
}

void Graph::computeTopologicalSort()
{
   
    queue<int> que;
    vector<int> indegree(vertices); 
    vector<int> sort;
    //Initalizing the indegree vector
    for(int i = 0; i < vertices; i++)
    {
        for(int j = 0; j < vertices; j++)
        {
            if(matrix[j][i] > 0)
            {
                indegree[i] = indegree[i] + 1;
            }
        }
    }

    //Enqueuing nodes that do not have any nodes pointing to them
    int counter = 0;
    for(int i = 0; i < indegree.size(); i++)
    {
        if(indegree[i] == 0)
        {
            que.push(i);
        }
    }

    //removing those nodes from the queue adding them to a sorted vector and updating the indegree
    while(!que.empty())
    {
        int index = que.front();
        que.pop();
        sort.push_back(index);
        counter++;

        for(int i = 0; i < vertices;i++)
        {
            if(matrix[index][i] > 0)
            {
                if(--indegree[i] == 0)
                {
                    que.push(i);
                }
            }
        }
    }


    //Check to see if topological sort was possible
    if(counter != vertices)
    {
        cout<<"This graph cannot be topologically sorted."<<endl;
    }
    else
    {
        cout<<"Topological Sort:"<<endl;
        for(int i = 0; i < vertices; i++)
        {

            cout<<vertexNames[sort[i]];
            if(i != vertices-1)
            {
                cout<<" --> ";
            }
        }
        cout<<endl;
    }
}

void Graph::computeShortestPaths(string nodeName)
{
    cout<<"Shortest paths from "<<nodeName<<":"<<endl;
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> que;
    
    //Assign baseNode to an int
    int baseNode = nameToIndex(nodeName);

    if(baseNode == -1)
    {
        cout<<nodeName<<" is not in the graph, please select a value in the graph."<<endl;
        return;
    }
    
    vector<bool> found(vertices, false);
    vector<int> distance(vertices);
    vector<int> parent(vertices, -1);

    distance[baseNode] = 0; 
    found[baseNode] = true;

    //Initialize the first value of the que
    Vertex temp;
    temp.prev = baseNode;
    temp.cost = distance[baseNode];
    que.push(temp);

    
    while(!que.empty())
    {
        Vertex temp = que.top();
        que.pop();
        for(int i = 0; i < vertices; i++)
        {
            if(matrix[temp.prev][i] > 0)    // Search to see where the adjacent nodes are
            {
                if(!found[i] || distance[i] > distance[temp.prev] + matrix[temp.prev][i])
                {
                    found[i] = true;
                    distance[i] = distance[temp.prev] + matrix[temp.prev][i];
                    Vertex next;
                    next.prev = i;
                    next.cost = distance[i];
                    
                    parent[i] = temp.prev;
                    que.push(next);
                }
            }
        }
    }

    //Print the Shortest Path
    for(int i = 0; i < vertices; i++)
    {
        if(!found[i])
        {
            cout<<"No path from "<<vertexNames[baseNode]<<" to "<<vertexNames[i]<<" found."<<endl;
        }
        else if(i != baseNode)
        {   
            cout<<vertexNames[baseNode];
            printShortestPath(parent, i);
            cout<<" || Weight: "<<distance[i]<<endl;
        } 
    }
}

void Graph::computeMinimumSpanningTree()
{
    cout<<"Minimum Spanning Tree:"<<endl;
    DisjointSet set(vertices);
    vector<Vertex> mst;
    vector<Vertex> vect;

    for(int i = 0; i < vertices; i++)
    {
        for(int j = 0; j < vertices; j++)
        {
            if(matrix[i][j] > 0)
            {
                Vertex temp;
                temp.cost = matrix[i][j];
                temp.prev = i;
                temp.next = j;
                vect.push_back(temp);
            }
        }
    }
    //Sort the vector 
    sort(vect.begin(), vect.end());

    int first;
    int second;
    int counter = 0;
    while(mst.size() != vertices -1)
    {
        Vertex temp = vect[counter++];

        first = set.find(temp.prev);
        second = set.find(temp.next);

        if(first != second)
        {
            mst.push_back(temp);
            set.doUnion(first, second);
        }
    }
    
    int cost = 0;
    //Print the Tree
    for(int i = 0; i < mst.size(); i++)
    {
        cout<<vertexNames[mst[i].prev]<<" -- "<<vertexNames[mst[i].next]<<" || Weight: "<<mst[i].cost<<endl;
        cost += mst[i].cost;
    }
    cout<<"Total Cost: "<<cost<<endl;


}

void Graph::printShortestPath(vector<int> &parent, int i)
{
    if(parent[i] == -1)
    {
        return;
    }
    printShortestPath(parent, parent[i]);
    cout<<" --> "<<vertexNames[i];
}

int Graph::nameToIndex(string name)
{
    for(int i = 0; i < vertices; i++)
    {
        if(vertexNames[i] == name)
        {
            return i;
        }
    }
    return -1;
}