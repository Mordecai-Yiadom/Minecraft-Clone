#include "mesh.h"

Mesh3D Mesh3D_create(VertexArray vao)
{
    Mesh3D mesh;
    memset(&mesh, 0, sizeof(Mesh3D));

    mesh.vao = vao;
    return mesh;
}


Mesh2D Mesh2D_create(VertexArray vao)
{
    Mesh2D mesh;
    memset(&mesh, 0, sizeof(Mesh2D));

    mesh.vao = vao;
    return mesh;  
}
