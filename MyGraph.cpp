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
        adjMatrix.resize(n);
        for (int i = 0; i < vertexes; i++) {
            adjMatrix[i].resize(n);
            for(int j = 0; j < vertexes; j++)
                adjMatrix[i][j] = 0;
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
        if(adjMatrix[a][b] != 0)
            return false;
        adjMatrix[a][b] = weight;
        adjMatrix[b][a] = weight;
        edgeList.push_back(pair<float, pair<int, int>>(weight, pair<int, int>(a, b)));
        mstRan = false;
        return true;
    }
    void MyGraph::Output(std::ostream& os){
        os << "Vertexes: " << MyGraph::vertexes << std::endl;
        for(int row = 0; row < MyGraph::vertexes; row++){
            for(int col = 0; col < MyGraph::vertexes; col++){
                os << row << "-" << adjMatrix[row][col] << "-" << col << std::endl;
            }
        }

    }

void MyGraph::dfs(int start, vector<bool> visited, const int t, float canCount, vector<int> temp)
{
    temp.push_back(start);
    if(start == t){
        if(canMax > canCount || canMax == -1){
            canMax = canCount;
            candidate = temp;
        }
    }
    else{
        visited[start] = true;
        for (int i = 0; i < vertexes; i++) {
            float num = adjMatrix[start][i];
            if (num != 0 && (!visited[i])) {
                if(num > canCount)
                    dfs(i, visited, t, num, temp);
                else
                    dfs(i, visited, t, canCount, temp);
            }
        }
    }
}

    std::pair<std::vector<int>, float> MyGraph::HW2ProgV1(int s, int t){
        vector<bool> visited(vertexes);
        canMax = -1;
        candidate.empty();
        for(int i = 0; i < vertexes; i++){
            visited[i] = false;
        }
        vector<int> temp;
        dfs(s, visited, t, -1, (temp));
        float weightRecord = canMax;
        return std::pair<std::vector<int>, float>(candidate, weightRecord);
    }

    std::pair<std::vector<int>, float> MyGraph::HW2Prog(int s, int t){
        if(!pathFound)
            getMST();
        pathFound = false;
        vector<bool> visited(vertexes);
        for(int i = 0; i < vertexes; i++){
            visited[i] = false;
        }
        maxEdge = -1;
        pathFind(s, t, visited);
        return std::pair<std::vector<int>, float>(path, maxEdge);
    }


    void MyGraph::getMST(){
        vector<int>edgeOrder(vertexes);
        vector<bool> visited(vertexes);
        mst.resize(vertexes);
<<<<<<< HEAD
        vector<float> key(vertexes);
=======
>>>>>>> parent of e887614 (Before prim switch)
        for(int i = 0; i < vertexes; i++){
            visited[i] = false;
            mst[i].resize(vertexes);
        }
<<<<<<< HEAD
        key[0] = 0;
        edgeOrder[0] = -1;
        for(int index = 0; index < vertexes - 1; index++){
            int minyEdge = minEdge(key, visited);
            visited[minyEdge] = true;
            for(int j = 0; j < vertexes; j++){
                if(adjMatrix[minyEdge][j] != 0 && !visited[j] && adjMatrix[minyEdge][j] < key[j])
                    edgeOrder[j] = minyEdge;
                    key[j] = adjMatrix[minyEdge][j];
=======
        mstEdges = 0;
        quicksort(edgeList, 0, edgeList.size() - 1);
        mst[edgeList[0].second.first][edgeList[0].second.second] = edgeList[0].first;
        mst[edgeList[0].second.second][edgeList[0].second.first] = edgeList[0].first;
        visited[edgeList[0].second.first] = true;
        visited[edgeList[0].second.second] = true;
        for(int index = 1; mstEdges != (vertexes - 1) && index < edgeList.size(); index++){
            int a = edgeList[index].second.first;
            int b = edgeList[index].second.second;
            if(!visited[a]){
                mst[a][b] = edgeList[index].first;
                mst[b][a] = edgeList[index].first;
                visited[a] = true;
                visited[b] = true;
                mstEdges++;
            }
            else if(!visited[b]){
                mst[a][b] = edgeList[index].first;
                mst[b][a] = edgeList[index].first;
                visited[b] = true;
                mstEdges++;
>>>>>>> parent of e887614 (Before prim switch)
            }
        }
        mstRan = true;
        for (int a = 1; a < vertexes; a++){
            int b = edgeOrder[a];
            float weight = adjMatrix[a][b];
            mst[b][a] = weight;
            mst[a][b] = weight;
        }
    }

<<<<<<< HEAD
    int MyGraph::minEdge(vector<float> key, vector<bool> visited)
    {
        int min = INT_MAX, min_index;
        for (int index = 0; index < vertexes; index++)
            if (!visited[index] && key[index] < min)
                min = key[index], min_index = index;
        return min_index;
    }


    bool MyGraph::findEndpoint(int a, int b, int num){
        if(num == b)
            return false;
        else if(num == a)
            return true;
        for(int i; i < vertexes; i++){
            float check = mst[num][i];
            bool ifComplete = false;
            if(check != 0 && i != b){
                ifComplete = findEndpoint(a, b, i);
            }
            if(ifComplete)
                return true;
        }
        return true;
    }

    void MyGraph::pathFind(int start, int t, vector<bool> visited){
=======
    vector<int> MyGraph::pathFind(int start, int t, vector<int> path, vector<bool> visited){
>>>>>>> parent of e887614 (Before prim switch)
        path.push_back(start);
        if(start == t){
            pathFound = true;
            vector<int> returner;
            for(int index = 0; index < path.size(); index++){
                returner.push_back(path[index]);
            }
            return returner;
        }
        vector<int> newpath;
        visited[start] = true;
        for(int i = 0; i < vertexes; i++){
            if(pathFound){
                if(maxEdge < mst[start][i])
                    maxEdge = mst[start][i];
                return newpath;
            }
            if(!visited[i] && mst[start][i] != 0){
                 newpath = pathFind(i, t, path, visited);
            }
        }
        return newpath;
    }


int MyGraph::Partition(vector<pair<float, pair<int, int>>> &v, int start, int end){

    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(v[i].first < v[pivot].first){
            swap(v[i],v[j]);
            ++j;
        }
    }
    swap(v[j],v[pivot]);
    return j;

}

void MyGraph::quicksort(vector<pair<float, pair<int, int>>> &v, int start, int end){

    if(start<end){
        int p = Partition(v,start,end);
        quicksort(v,start,p-1);
        quicksort(v,p+1,end);
    }

}

