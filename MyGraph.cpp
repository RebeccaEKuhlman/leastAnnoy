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
        MyGraph::vertexes = n + 1;
        adjMatrix.resize(vertexes);
        for (int i = 1; i < vertexes; i++) {
            adjMatrix[i].resize(n);
            for(int j = 1; j < vertexes; j++)
                adjMatrix[i][j] = 0;
        }
    }
    MyGraph::MyGraph(const MyGraph& oldMatrix){
        MyGraph::vertexes = oldMatrix.MyGraph::vertexes;
        float newMatrix [MyGraph::vertexes][MyGraph::vertexes];
        for(int row = 1; row < MyGraph::vertexes; row++){
            for(int col = 1; col < MyGraph::vertexes; col++){
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
        for(int row = 1; row < MyGraph::vertexes; row++){
            for(int col = 1; col < MyGraph::vertexes; col++){
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
        for (int i = 1; i < vertexes; i++) {
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
        for(int i = 1; i < vertexes; i++){
            visited[i] = false;
        }
        vector<int> temp;
        dfs(s, visited, t, -1, (temp));
        float weightRecord = canMax;
        return std::pair<std::vector<int>, float>(candidate, weightRecord);
    }

    std::pair<std::vector<int>, float> MyGraph::HW2Prog(int s, int t){
        if(!mstRan)
            getMST();
        pathFound = false;
        path.clear();
        vector<bool> visited(vertexes);
        for(int i = 1; i < vertexes; i++){
            visited[i] = false;
        }
        maxEdge = -1;
        pathFind(s, t, visited);
        return std::pair<std::vector<int>, float>(path, maxEdge);
    }


    void MyGraph::getMST(){
        mst.clear();
        vector<bool> visited(vertexes);
        sets.resize(vertexes);
        mst.resize(vertexes);
        mst[0].resize(1);
        vector<int> setKey(vertexes);
        for(int i = 1; i < vertexes; i++){
            visited[i] = false;
            mst[i].resize(vertexes);
            sets[i].push_back(i);
            setKey[i] = i;
        }
        quicksort(edgeList, 0, edgeList.size() - 1);
 /**       mst[edgeList[0].second.first][edgeList[0].second.second] = edgeList[0].first;
        mst[edgeList[0].second.second][edgeList[0].second.first] = edgeList[0].first;
        visited[edgeList[0].second.first] = true;
        visited[edgeList[0].second.second] = true;
        sets[edgeList[0].second.second].pop_back();
        sets[edgeList[0].second.first].push_back(edgeList[0].second.second);
        setKey[edgeList[0].second.second] = edgeList[0].second.first;*/
        for(int index = 0; index < edgeList.size(); index++){
            int a = edgeList[index].second.first;
            int b = edgeList[index].second.second;
            if(!visited[a] || !visited[b]){
                mst[a][b] = edgeList[index].first;
                mst[b][a] = edgeList[index].first;
                visited[a] = true;
                visited[b] = true;
                int indA = setKey[a];
                int indB = setKey[b];
                if(sets[indA].size() >= sets[indB].size()){
                    mergeVectors(indA, indB, b, setKey);
                }
                else
                    mergeVectors(indB, indA, a, setKey);
                mstEdges++;
            }
            else if(setKey[a] != setKey[b]){
                int indA = setKey[a];
                int indB = setKey[b];
                if(sets[indA].size() >= sets[indB].size()){
                    mergeVectors(indA, indB, b, setKey);
                }
                else
                    mergeVectors(indB, indA, a, setKey);
                mst[a][b] = edgeList[index].first;
                mst[b][a] = edgeList[index].first;
                mstEdges++;
            }
        }
        mstRan = true;
    }

    void MyGraph::mergeVectors(int indA, int indB, int b, vector<int>& setKey){
        for(int index = sets[indB].size() - 1; index >= 0; index--){
            sets[indA].push_back(sets[indB][index]);
            setKey[sets[indB][index]] = indA;
            sets[indB].pop_back();
        }
    }

    void MyGraph::pathFind(int start, int t, vector<bool> visited){
        path.push_back(start);
        if(start == t){
            pathFound = true;
            return;
        }
        vector<int> newpath;
        visited[start] = true;
        for(int i = 1; i < vertexes; i++){
            if(pathFound)
                return;
            if(!visited[i] && mst[start][i] != 0){
                pathFind(i, t, visited);
                if(pathFound){
                    if(maxEdge < mst[start][i])
                        maxEdge = mst[start][i];
                    return;
                }
            }
        }
        path.pop_back();
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

