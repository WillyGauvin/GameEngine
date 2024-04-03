#include "DataTypes.h"
#include "VertexFormats.h"


class HeightMapMesh : public fw::Mesh
{
	using Super = fw::Mesh;
public:
	HeightMapMesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize, vec2 size, ivec2 vertCount, std::vector<VertexFormat_Pos3NormalUV> vert);
	~HeightMapMesh();

	static fw::ResourceCategoryIDType GetResourceCategoryID() { return "HeightMesh"; }

	virtual void Create(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize) override;

	virtual void Draw(bgfx::ViewId viewID, const fw::Uniforms* pUniforms, const fw::Material* pMaterial) override;

	float GetHeightAtXZ(float x, float z);


	std::vector<vec3> GetVerts();
protected:
	vec2 m_Size;
	ivec2 m_VertCount;
	std::vector<VertexFormat_Pos3NormalUV> m_Verts;
};