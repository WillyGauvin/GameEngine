//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "bgfx/platform.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "ResourceManager.h"

namespace fw {

    class Material;
    class ShaderProgram;
    class Uniforms;

    class Mesh : public Resource
    {
    public:
        Mesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize);
        Mesh(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize, std::vector<vec3> vertexes, std::vector<std::vector<int>> triangles);

        virtual ~Mesh();

        static ResourceCategoryIDType GetResourceCategoryID() { return "Mesh"; }

        virtual void Create(const bgfx::VertexLayout& vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize);

        virtual void Draw(bgfx::ViewId viewID, const Uniforms* pUniforms, const Material* pMaterial);

        std::vector<vec3> GetVerts() { return m_Verts; }

        std::vector<std::vector<int>> GetTriangles() { return m_Triangles; }


    protected:
        
        std::vector<vec3> m_Verts;

        std::vector<std::vector<int>> m_Triangles;
        bgfx::VertexBufferHandle m_VBO;
        bgfx::IndexBufferHandle m_IBO;

    };

} // namespace fw
