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
    BlockFace chunkMeshBuffer[DEFAULT_CHUNK_VERTEXBUFFER_SIZE];
    memset(chunkMeshBuffer, 0, sizeof(chunkMeshBuffer));
    if(!mesh) return;
    int i = 0;
    for(int x = 0; x < CHUNK_X_LIMIT; x++)
    {
        for(int y = 0; y < CHUNK_Y_LIMIT; y++)
        {
            for(int z = 0; y < CHUNK_Z_LIMIT; z++)
            {   
                chunkMeshBuffer[i++] = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_NORTH);
                chunkMeshBuffer[i++] = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_SOUTH);
                chunkMeshBuffer[i++] = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_EAST);
                chunkMeshBuffer[i++] = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_WEST);
                chunkMeshBuffer[i++] = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_TOP);
                chunkMeshBuffer[i++] = BlockMesh_getFace(mesh->chunk->blocks[x][y][z], BLOCKFACE_BOTTOM);     
            }
        }
    }
    BufferData data = {.buffer=chunkMeshBuffer, .size=VertexBuffer_getSize(&mesh->mesh.vbo)};
    VertexBuffer_write(&mesh->mesh.vbo, data, 0);
}


// void ChunkMesh_addBlock(ChunkMesh *chunkMesh, BlockMesh blockMesh, int xOffset, int yOffset, int zOffset)
// {
//     if(!chunkMesh || xOffset < 0 || yOffset < 0 || zOffset < 0) return;
    
    
//     VertexBuffer_write(&chunkMesh->mesh.vbo, );
// }
