#include "edges.h"
#include <stdlib.h>

struct edge *edgeList;
int edgeCount;

void initEdgeList(){
    edgeList = (struct edge *)calloc(MAX_EDGE_COUNT, sizeof(struct edge));
}

void appendEdge(int index1, int index2){
    edgeList[edgeCount] = (struct edge){index1, index2};
    edgeCount++;
}

void cleanEdgeList(){
    free(edgeList);
}

