#ifndef EDGES_H
#define EDGES_H
    #define MAX_EDGE_COUNT 32

    struct edge{
        int index1;
        int index2;
    };

    void initEdgeList();
    void appendEdge(int index1, int index2);
    void cleanEdgeList();

    extern struct edge *edgeList;
    extern int edgeCount;
#endif