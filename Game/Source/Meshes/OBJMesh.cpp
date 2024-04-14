#include "Framework.h"

#include "OBJMesh.h"

OBJMesh::OBJMesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize, std::vector<VertexFormat_Pos3NormalUV> vert) :
    fw::Mesh(vertexFormat, verts, vertsSize, indices, indicesSize),
    m_Verts(vert)
{
}
OBJMesh::~OBJMesh()
{
}
void OBJMesh::Create(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize)
{
    Super::Create(vertexFormat, verts, vertsSize, indices, indicesSize);
}
void OBJMesh::Draw(bgfx::ViewId viewID, const fw::Uniforms* pUniforms, const fw::Material* pMaterial)
{
    Super::Draw(viewID, pUniforms, pMaterial);
}

std::vector<vec3> OBJMesh::GetVerts()
{
    std::vector<vec3> verts;

    for (int i = 0; i < m_Verts.size(); i++)
    {
        verts.push_back(m_Verts[i].pos);
    }
    return verts;
}
