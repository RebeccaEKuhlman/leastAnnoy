//
// Created by rekuh on 10/10/2022.
//
/**
 *  MyGraph. It represents an undirected graph with weights on each edge. You must implement the following methods:
 *  Methods:
 *  • Constructors:  o MyGraph(int n): Create a graph with n vertices. 
 *      The vertices are labelled 1..n o MyGraph(const MyGraph& g): Construct a new graph that is a copy of g
 *  • Methods
 *      o bool AddEdge(int a, int b, float w): Add an edge between vertex a and b, with weight w.
 *          If the edge already exists or a vertex is not on the graph, do nothing and return false.
 *          Otherwise (addition is successful) return true.
 *      o void Output(ostream& os):
 *          Output the graph to the ostream& specified. Your output should have the following format:
 *  ▪ The first line print the number of vertices. ▪ Each subsequent line prints an edge.
 *      It should print three numbers: the two vertices associated with the edge
 *      (print the vertex with the smaller number first), and the weight of the edge.
 *      You should have one space character between the numbers, and no space at the end.
 *      You can order the edges whatever way you want.
 *      o pair<vector<int>, float> HW2Prog(int s, int t):
 *      This is the main function that you have to implement for this homework.
 *  ▪ The function will find a least annoying path from s to t.
 *      The return will be a pair. The first item of the pair (vector) denotes the path from s to t.
 *      The first item of the vector should be s and the last one should be t,
 *      and the vector is the order of the vertices on the path from s to t.
 *      The second item (float) denote the actual annoyance (i.e. the weight of the edge that has maximum weight on the path). .
 */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
using namespace std;

#ifndef LEASTANNOY_MYGRAPH_H
#define LEASTANNOY_MYGRAPH_H

class MyGraph{

    int vertexes;
    vector<vector<float>> adjMatrix;
    public:
        MyGraph(int);
        MyGraph(const MyGraph&);
        bool AddEdge(int, int, float);
        void Output(std::ostream& os);
        std::pair<std::vector<int>, float> HW2Prog(int, int);
        void dfs(int start, vector<bool> visited,const int t, float canCount, vector<int> temp);
    private:
        vector<int> candidate;
        float canMax = -1;
        bool mstRan = false;
        vector<vector<float>> mst;
        int mstEdges;

};

#endif //LEASTANNOY_MYGRAPH_H

