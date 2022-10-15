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
 *      You can order the edges whatever way you want.  o pair<vector<int>, float> HW2Prog(int s, int t):
 *      This is the main function that you have to implement for this homework.
 *  ▪ The function will find a least annoying path from s to t.
 *      The return will be a pair. The first item of the pair (vector) denotes the path from s to t.
 *      The first item of the vector should be s and the last one should be t,
 *      and the vector is the order of the vertices on the path from s to t.
 *      The second item (float) denote the actual annoyance (i.e. the weight of the edge that has maximum weight on the path). .
 */
#include "MyGraph.h"


    //Create a graph with n vertices.
    MyGraph::MyGraph(int n){
        MyGraph::vertexes = n;

        // Create a dynamic array of pointers
        adjMatrix = new float*[vertexes];

        // Create a row for every pointer
        for (int i = 0; i < vertexes; i++) {
            adjMatrix[i] = new float[vertexes];
        }
    }
    MyGraph::MyGraph(const MyGraph& oldMatrix){
        MyGraph::vertexes = oldMatrix.MyGraph::vertexes;
        float newMatrix [MyGraph::vertexes][MyGraph::vertexes];
        for(int row = 0; row < MyGraph::vertexes; row++){
            for(int col = 0; col < MyGraph::vertexes; col++){
                newMatrix[row][col] = oldMatrix.adjMatrix[row][col];
            }
        }
    }
    bool MyGraph::AddEdge(int a, int b, float weight){
        if(a > MyGraph::vertexes || b > MyGraph::vertexes || weight < 0)
            return false;
        if((MyGraph::adjMatrix[a][b]) != 0)
            return false;
        MyGraph::adjMatrix[a][b] = weight;
        return true;
    }
    void MyGraph::Output(std::ostream& os){
        os << "Vertexes: " << MyGraph::vertexes << std::endl;
        for(int row = 0; row < MyGraph::vertexes; row++){
            for(int col = 0; col < MyGraph::vertexes; col++){
                os << row << "-" << MyGraph::adjMatrix[row][col] << "-" << col << std::endl;
            }
        }

    }
    std::pair<std::vector<int>, float> MyGraph::HW2Prog(int s, int t){
        std::vector<int> candidate;
        candidate.push_back(s);
        float canMax = -1;
        int visited[vertexes];
        visited[s] = true;
        int vertex = s;
        std::vector<int> temp;
        int canCount = -1;
        do{
            for(int index = 0; index < vertexes; index++) {
                if (index != vertex && !visited[index] && adjMatrix[vertex][index] != 0) {
                    temp.push_back(index);
                    int edgeNum = adjMatrix[vertex][index];
                    if (canMax > edgeNum || canCount == -1)
                        canCount = edgeNum;
                    visited[index] = true;
                    if(index == t) {
                        if(canMax > canCount || canMax == -1){
                            canMax = canCount;
                            candidate = std::vector<int>(temp);
                        }
                        //Might need some editing
                        temp.pop_back();
                    }
                    else //Might need some editing
                        vertex = index;
                        break;
                }
            }
        }while(vertex != s);
        return std::pair<std::vector<int>, float>(candidate, canMax);
    }