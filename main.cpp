#include <iostream>
#include <fstream>
#include <vector>
#include <forward_list>
#include <queue>


using namespace std;

class Vertex{
public:
    queue<int> edges;
    int inDegree;
    int outDegree;
    Vertex(){
        this->inDegree = 0;
        this->outDegree = 0;
    }
};

int main(int argc, char const *argv[]) {
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    int numOfVertices = 0;
    infile >> numOfVertices;
    vector<Vertex> listOfVertices(numOfVertices);
    int numOfEdges = 0;
    //reading the input from the txt file, and recording the indegrees, outdegrees and adjacent adges of all the vertices
    for(int i = 0; i < numOfVertices; i++){
        int id = 0, outDegree = 0;
        infile >> id >> outDegree;
        Vertex& v =listOfVertices[id];
        v.outDegree = outDegree;
        numOfEdges += outDegree;
        for(int i = 0; i < outDegree; i++){
            int edge = 0;
            infile >> edge;
            listOfVertices[edge].inDegree++;
            v.edges.push(edge);
//            if(listOfVertices[edge].outDegree != 0 && listOfVertices[edge].inDegree > listOfVertices[edge].outDegree){
//                outfile << "no path";
//                return 0;
//            }
        }
    }
    //checking if the the graph is eulerian
    for (int i = 0; i < listOfVertices.size(); ++i)
    {
        if(listOfVertices[i].inDegree != listOfVertices[i].outDegree){
            outfile << "no path";
            return 0;
        }
    }

    int startingVertex = 0;
    infile >> startingVertex;
    //creating a singly linked list circuit 
    forward_list<int> circuit;
    circuit.push_front(startingVertex);
    int length = 1;

    forward_list<int>::iterator itr = circuit.begin();
    int vertCurrent = startingVertex;
    int iterationNum = 1;
    //implementation of the Hierholzer's algortihm
    while(length <= numOfEdges){
        vector<int> tour;
        while(!listOfVertices[vertCurrent].edges.empty()){
            int edg = listOfVertices[vertCurrent].edges.front();
            listOfVertices[vertCurrent].edges.pop();
            vertCurrent = edg;
            tour.emplace_back(vertCurrent);
        }
        circuit.insert_after(itr, tour.begin(),tour.end());
        length += tour.size();
        itr = circuit.begin();
        advance(itr, iterationNum);
        for( ; itr != circuit.end(); itr++){
            if(!listOfVertices[*itr].edges.empty()){
                vertCurrent = *itr;
                break;
            }
        }
        iterationNum++;

    }

    listOfVertices.clear();
    vector<Vertex>().swap(listOfVertices);

    //printing the circuit to the given txt file
    for(forward_list<int>::iterator it = circuit.begin(); it!=circuit.end(); it++){
        outfile << *it << " ";
    }
    
    return 0;
}