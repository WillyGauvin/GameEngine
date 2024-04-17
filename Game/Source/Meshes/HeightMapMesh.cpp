#include "Framework.h"

#include "HeightMapMesh.h"

HeightMapMesh::HeightMapMesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize, vec2 size, ivec2 vertCount, std::vector<VertexFormat_Pos3NormalUV> vert) :
    fw::Mesh(vertexFormat, verts, vertsSize, indices, indicesSize),
    m_Size(size),
    m_VertCount(vertCount),
    m_Verts(vert)
{
}
HeightMapMesh::~HeightMapMesh()
{
}
void HeightMapMesh::Create(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize)
{
    Super::Create(vertexFormat, verts, vertsSize, indices, indicesSize);
}
void HeightMapMesh::Draw(bgfx::ViewId viewID, const fw::Uniforms* pUniforms, const fw::Material* pMaterial)
{
    Super::Draw(viewID, pUniforms, pMaterial);
}

float HeightMapMesh::GetHeightAtXZ(float x, float z)
{
    float height = 0;

    // Convert x,z to heightmap indices.
    float xPercent = x / m_Size.x;
    float zPercent = z / m_Size.y;

    vec2 tileSize = vec2(m_Size.x / m_VertCount.x, m_Size.y / m_VertCount.y);

    float fxIndex = (int)(x - fmodf(x, tileSize.x)) / tileSize.x;
    int xIndex = (int)fxIndex;

    float fzIndex = (int)(z - fmodf(z, tileSize.y)) / tileSize.y;
    int zIndex = (int)fzIndex;

    // Get the 4 vertices that make up the quad.
    int stride = m_VertCount.x;
    int index = zIndex * stride + xIndex;
    vec3 bottomLeft = m_Verts[index].pos;
    vec3 bottomRight = m_Verts[index + 1].pos;
    vec3 topLeft = m_Verts[index + stride].pos;
    vec3 topRight = m_Verts[index + stride + 1].pos;

    // Get the x,z percent within the quad.
    float xPercentInQuad = xPercent * (m_VertCount.x) - xIndex;
    float zPercentInQuad = zPercent * (m_VertCount.y) - zIndex;
  
    // Get the height at x,z.
    vec3 p1, p2, p3;
    if (xPercentInQuad < zPercentInQuad)
    {
        // Top left triangle.
        p1 = vec3(0, bottomLeft.y, 0);
        p2 = vec3(0, topLeft.y, 1);
        p3 = vec3(1, topRight.y, 1);
    }
    else
    {
        // Bottom right triangle.
        p1 = vec3(0, bottomLeft.y, 0);
        p2 = vec3(1, topRight.y, 1);
        p3 = vec3(1, bottomRight.y, 0);
    }

    // Barycentric interpolation.
    {
        vec2 p0 = vec2(xPercentInQuad, zPercentInQuad);

        // Calculate Vectors.
        vec2 p10 = p0 - p1.XZ();
        vec2 p12 = p2.XZ() - p1.XZ();
        vec2 p13 = p3.XZ() - p1.XZ();

        // Cross products.
        float a123 = (p12.x * p13.y - p12.y * p13.x);
        float a3 = (p12.x * p10.y - p12.y * p10.x);
        float a2 = (p10.x * p13.y - p10.y * p13.x);

        // Weights.
        float w3 = a3 / a123;
        float w2 = a2 / a123;
        float w1 = 1.0f - w2 - w3;

        // Apply weights.
        height = (w1 * p1.y) + (w2 * p2.y) + (w3 * p3.y);
    }

    return height;
}

std::vector<vec3> HeightMapMesh::GetVerts()
{
    std::vector<vec3> verts;

    for (int i = 0; i < m_Verts.size(); i++)
    {
        verts.push_back(m_Verts[i].pos);
    }
    return verts;
}
