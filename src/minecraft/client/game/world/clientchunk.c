#include "clientchunk.h"
#include <string.h>


#define DEFAULT_CHUNK_VERTEXBUFFER_SIZE (sizeof(BlockMesh) * CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT)
#define DEFAULT_CHUNK_INDEXBUFFER_SIZE (sizeof(int)  * 24 * CHUNK_X_LIMIT * CHUNK_Y_LIMIT * CHUNK_Z_LIMIT)

ChunkMesh ChunkMesh_create(Chunk *chunk)
{   
    ChunkMesh chunkMesh;
    memset(&chunkMesh, 0, sizeof(ChunkMesh));
    if(!chunk) return chunkMesh;
    
    MeshData meshData;
    meshData.format = POS3f_NORM3f_UV2f;
    meshData.type = DYNAMIC;
    meshData.vertexData = (BufferData){.buffer=NULL, .size=DEFAULT_CHUNK_VERTEXBUFFER_SIZE};
    meshData.indexData = (BufferData){.buffer=NULL, .size=DEFAULT_CHUNK_INDEXBUFFER_SIZE};

    chunkMesh.mesh = Mesh_create(meshData);
    chunkMesh.chunk = chunk;

    return chunkMesh;
}


void ChunkMesh_build(ChunkMesh *mesh)
{
    if(!mesh) return;

    
}


// void ChunkMesh_addBlock(ChunkMesh *chunkMesh, BlockMesh blockMesh, int xOffset, int yOffset, int zOffset)
// {
//     if(!chunkMesh || xOffset < 0 || yOffset < 0 || zOffset < 0) return;
    
    
//     VertexBuffer_write(&chunkMesh->mesh.vbo, );
// }
