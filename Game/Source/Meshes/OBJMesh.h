#include "DataTypes.h"
#include "VertexFormats.h"


class OBJMesh : public fw::Mesh
{
	using Super = fw::Mesh;
public:
	OBJMesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize, std::vector<VertexFormat_Pos3NormalUV> vert);
	~OBJMesh();

	static fw::ResourceCategoryIDType GetResourceCategoryID() { return "HeightMesh"; }

	virtual void Create(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize) override;

	virtual void Draw(bgfx::ViewId viewID, const fw::Uniforms* pUniforms, const fw::Material* pMaterial) override;

	std::vector<vec3> GetVerts();
protected:
	std::vector<VertexFormat_Pos3NormalUV> m_Verts;
};