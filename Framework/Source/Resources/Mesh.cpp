//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "bgfx/platform.h"

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Math/Matrix.h"
#include "Resources/Material.h"
#include "Utility/Utility.h"

namespace fw {

    Mesh::Mesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize)
    {
        Create( vertexFormat, verts, vertsSize, indices, indicesSize );
        void* m = new char[vertsSize];
        memcpy(m, verts, vertsSize);
    }

    Mesh::Mesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize, std::vector<vec3> vertexes, std::vector<std::vector<int>> triangles)
        : m_Verts(vertexes),
        m_Triangles(triangles)
    {
        Create(vertexFormat, verts, vertsSize, indices, indicesSize);
        void* m = new char[vertsSize];
        memcpy(m, verts, vertsSize);
    }

    Mesh::~Mesh()
    {
        bgfx::destroy( m_VBO );
        bgfx::destroy( m_IBO );
    }

    void Mesh::Create(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize)
    {
        m_VBO = bgfx::createVertexBuffer( bgfx::copy(verts, vertsSize), vertexFormat );
        m_IBO = bgfx::createIndexBuffer( bgfx::copy(indices, indicesSize) );
    }

    void Mesh::Draw(bgfx::ViewId viewID, const Uniforms* pUniforms, const Material* pMaterial)
    {
        // Set vertex and index buffer.
        bgfx::setVertexBuffer( 0, m_VBO );
        bgfx::setIndexBuffer( m_IBO );

        // Setup the material's uniforms.
        pMaterial->Enable( pUniforms );

        // Set render states.
        uint64_t state = pMaterial->GetBGFXRenderState() | BGFX_STATE_MSAA;
        bgfx::setState( state );

        // Submit primitive for rendering to the selected view.
        bgfx::submit( viewID, pMaterial->GetShader()->GetProgram() );
    }

} // namespace fw
