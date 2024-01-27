//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "VertexFormats.h"
#include "Shapes.h"

//=======================
// Triangle
//=======================
static const VertexFormat_PosColor g_TriangleVerts[] =
{
    { vec3( 0.0f, 0.5f, 0), 255, 0, 0, 255 }, // Top
    { vec3(-0.5f,-0.5f, 0), 0, 255, 0, 255 }, // Bottom-left
    { vec3( 0.5f,-0.5f, 0), 0, 0, 255, 255 }, // Bottom-right
};
static const uint16 g_TriangleIndices[] =
{
    0, 2, 1,
};
fw::Mesh* CreateTriangleMesh()
{
    return new fw::Mesh( VertexFormat_PosColor::format, g_TriangleVerts, sizeof(g_TriangleVerts), g_TriangleIndices, sizeof(g_TriangleIndices) );
}

//=======================
// Square
//=======================
static const VertexFormat_PosColor g_SquareVerts[] =
{
    { vec3(-0.5f, 0.5f, 0), 0, 255, 0, 255 }, // Top-left
    { vec3(-0.5f,-0.5f, 0), 0,   0, 0, 255 }, // Bottom-left
    { vec3( 0.5f,-0.5f, 0), 0,   0, 0, 255 }, // Bottom-right
    { vec3( 0.5f, 0.5f, 0), 0, 255, 0, 255 }, // Top-right
};
static const uint16 g_SquareIndices[] =
{
    0,2,1, 0,3,2
};
fw::Mesh* CreateSquareMesh()
{
    return new fw::Mesh( VertexFormat_PosColor::format, g_SquareVerts, sizeof(g_SquareVerts), g_SquareIndices, sizeof(g_SquareIndices) );
}

//=======================
// Sprite
//=======================
static const VertexFormat_PosUV g_SpriteVerts[] =
{
    { vec3(-0.5f, 0.5f, 0), vec2(0,1) }, // Top-left
    { vec3(-0.5f,-0.5f, 0), vec2(0,0) }, // Bottom-left
    { vec3( 0.5f,-0.5f, 0), vec2(1,0) }, // Bottom-right
    { vec3( 0.5f, 0.5f, 0), vec2(1,1) }, // Top-right
};
static const uint16 g_SpriteIndices[] =
{
    0,2,1, 0,3,2
};
fw::Mesh* CreateSpriteMesh()
{
    return new fw::Mesh( VertexFormat_PosUV::format, g_SpriteVerts, sizeof(g_SpriteVerts), g_SpriteIndices, sizeof(g_SpriteIndices) );
}

fw::Mesh* CreateCircleMesh()
{
    int numPoints = 32;

    std::vector<VertexFormat_PosColor> verts;
    std::vector<uint16> indices;

    float angleInc = 2 * PI / numPoints;
    float radius = 2.0f;

    for (int i = 0; i < numPoints; i++)
    {
        float angle = angleInc * i;
        vec3 pos = vec3(cos(angle), sin(angle), 0) * radius;
        verts.push_back({ pos, 0, 255, 0, 255 });
    }

    for (int i = 1; i < numPoints - 1; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i);
    }

    int vertBytes = sizeof(VertexFormat_PosColor) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    return new fw::Mesh(VertexFormat_PosColor::format,
        verts.data(), vertBytes,
        indices.data(), indicesBytes);
}


fw::Mesh* CreateCubeMesh(vec3 Objscale)
{
    vec2 texSize = vec2(800, 800);
    vec2 faceSize = vec2(200, 200);
    vec2 scale = faceSize / texSize;

    VertexFormat_PosUV g_CubeVerts[] =
    {
        //Front
        {vec3(-1,-1,-1) * Objscale,scale * vec2(0,1)}, //0
        {vec3(-1,1,-1) * Objscale,scale * vec2(0,2)},  //1
        {vec3(1,1,-1) * Objscale,scale * vec2(1,2)},   //2
        {vec3(1,-1,-1) * Objscale,scale * vec2(1,1)},  //3

        //Right                             
        {vec3(1,-1,-1) * Objscale,scale * vec2(1,1)},  //4
        {vec3(1,1,-1) * Objscale,scale * vec2(1,2)},   //5
        {vec3(1,1,1) * Objscale,scale * vec2(2,2)},    //6
        {vec3(1,-1,1) * Objscale,scale * vec2(2,1)},   //7

        //Left                              
        {vec3(-1,-1,1) * Objscale,scale * vec2(3,1)},  //8
        {vec3(-1,1,1) * Objscale,scale * vec2(3,2)},   //9
        {vec3(-1,1,-1) * Objscale,scale * vec2(4,2)},  //10
        {vec3(-1,-1,-1) * Objscale,scale * vec2(4,1)}, //11

        //Back                              
        {vec3(1,-1,1) * Objscale,scale * vec2(2,1)},   //12
        {vec3(1,1,1) * Objscale,scale * vec2(2,2)},    //13
        {vec3(-1,1,1) * Objscale,scale * vec2(3,2)},   //14
        {vec3(-1,-1,1) * Objscale,scale * vec2(3,1)},  //15

        //Top                               
        {vec3(-1,1,-1) * Objscale,scale * vec2(3,3)},  //16
        {vec3(-1,1,1) * Objscale,scale * vec2(3,2)},   //17
        {vec3(1,1,1) * Objscale,scale * vec2(2,2)},    //18
        {vec3(1,1,-1) * Objscale,scale * vec2(2,3)},   //19

        //Bottom                            
        {vec3(1,-1,-1) * Objscale,scale * vec2(2,0)},  //20
        {vec3(1,-1,1) * Objscale,scale * vec2(2,1)},   //21
        {vec3(-1,-1,1) * Objscale,scale * vec2(3,1)},  //22
        {vec3(-1,-1,-1) * Objscale,scale * vec2(3,0)}, //23


    };

    uint16 g_CubeIndices[] =
    {
        //Front
        3,1,2,
        3,0,1,
        //Right
        7,5,6,
        7,4,5,
        //Left
        11,9,10,
        11,8,9,
        //Back
        15,13,14,
        15,12,13,
        //Top
        19,17,18,
        19,16,17,
        //Bottom
        21,23,20,
        21,22,23
    };
   
    return new fw::Mesh(VertexFormat_PosUV::format, g_CubeVerts, sizeof(g_CubeVerts), g_CubeIndices, sizeof(g_CubeIndices));
}
