#include "project.h"
#include "3DVertex.h"
#include "2DVertex.h"

struct vertex2D projectVertex(struct vertex3D vertex3D){//maybe useful later
    return (struct vertex2D){vertex3D.x/vertex3D.z, vertex3D.y/vertex3D.z};
}

void projectVertices(){//projecting only from a dedicated buffer to another dedicated buffer may be unextensible but i dont care
    for (int i = 0; i < vertex3DCount; i++){
        vertex2DList[i] = projectVertex(vertex3DList[i]);
        vertex2DCount = vertex3DCount;
    }
}