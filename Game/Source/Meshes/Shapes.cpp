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
#include "stb/stb_image.h"
#include "HeightMapMesh.h"


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

    VertexFormat_Pos3NormalUV g_CubeVerts[] =
    {
        //Front
        {vec3(-0.5,-0.5,-0.5) * Objscale, vec3(0,0,-1), scale * vec2(0,1)}, //0
        {vec3(-0.5,0.5,-0.5) * Objscale, vec3(0,0,-1), scale * vec2(0,2)},  //1
        {vec3(0.5,0.5,-0.5) * Objscale, vec3(0,0,-1), scale * vec2(1,2)},   //2
        {vec3(0.5,-0.5,-0.5) * Objscale, vec3(0,0,-1), scale * vec2(1,1)},  //3

        //Right                             
        {vec3(0.5,-0.5,-0.5) * Objscale, vec3(1,0,0), scale * vec2(1,1)},  //4
        {vec3(0.5,0.5,-0.5) * Objscale, vec3(1,0,0), scale * vec2(1,2)},   //5
        {vec3(0.5,0.5,0.5) * Objscale, vec3(1,0,0), scale * vec2(2,2)},    //6
        {vec3(0.5,-0.5,0.5) * Objscale, vec3(1,0,0), scale * vec2(2,1)},   //7

        //Left                              
        {vec3(-0.5,-0.5,0.5) * Objscale, vec3(-1,0,0), scale * vec2(3,1)},  //8
        {vec3(-0.5,0.5,0.5) * Objscale, vec3(-1,0,0), scale * vec2(3,2)},   //9
        {vec3(-0.5,0.5,-0.5) * Objscale, vec3(-1,0,0), scale * vec2(4,2)},  //10
        {vec3(-0.5,-0.5,-0.5) * Objscale, vec3(-1,0,0), scale * vec2(4,1)}, //11

        //Back                              
        {vec3(0.5,-0.5,0.5) * Objscale, vec3(0,0,1), scale * vec2(2,1)},   //12
        {vec3(0.5,0.5,0.5) * Objscale, vec3(0,0,1), scale * vec2(2,2)},    //13
        {vec3(-0.5,0.5,0.5) * Objscale, vec3(0,0,1), scale * vec2(3,2)},   //14
        {vec3(-0.5,-0.5,0.5) * Objscale, vec3(0,0,1), scale * vec2(3,1)},  //15

        //Top                              
        {vec3(-0.5,0.5,-0.5) * Objscale, vec3(0,1,0), scale * vec2(3,3)},  //16
        {vec3(-0.5,0.5,0.5) * Objscale, vec3(0,1,0), scale * vec2(3,2)},   //17
        {vec3(0.5,0.5,0.5) * Objscale, vec3(0,1,0), scale * vec2(2,2)},    //18
        {vec3(0.5,0.5,-0.5) * Objscale, vec3(0,1,0), scale * vec2(2,3)},   //19

        //Bottom                            
        {vec3(0.5,-0.5,-0.5) * Objscale, vec3(0,-1, 0), scale * vec2(2,0)},  //20
        {vec3(0.5,-0.5,0.5) * Objscale, vec3(0,-1,0), scale * vec2(2,1)},   //21
        {vec3(-0.5,-0.5,0.5) * Objscale, vec3(0,-1,0), scale * vec2(3,1)},  //22
        {vec3(-0.5,-0.5,-0.5) * Objscale, vec3(0,-1,0), scale * vec2(3,0)}, //23


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
   
    return new fw::Mesh(VertexFormat_Pos3NormalUV::format, g_CubeVerts, sizeof(g_CubeVerts), g_CubeIndices, sizeof(g_CubeIndices));
}

fw::Mesh* CreatePlaneMesh(ivec2 size, vec2 scale)
{
    int numPoints = size.x * size.y;

    std::vector<VertexFormat_Pos3NormalUV> verts;
    std::vector<uint16> indices;

    for (int i = 0; i < numPoints; i++)
    {
        int x = i % size.x;
        int y = (i - x) / size.x;
        vec2 point = vec2((float)x, (float)y);

        vec3 pos = vec3(point.x * (scale.x / (size.x - 1)),0 , point.y * (scale.y / (size.y - 1)));

        vec3 normal = vec3(0, 1, 0);

        vec2 UV = point;

        verts.push_back({ pos, normal, UV });
    }

    for (int y = 0; y < size.y - 1; y++)
    {
        for (int x = 0; x < size.x - 1; x++)
        {
            indices.push_back((x + 1) + ((y + 1) * size.x));
            indices.push_back(x + (y * size.x));
            indices.push_back(x  + ((y + 1)* size.x) );

            indices.push_back((x + 1) + ((y + 1) * size.x));
            indices.push_back((x + 1) + (y * size.x));
            indices.push_back(x + (y * size.x));
        }
    }

    int vertBytes = sizeof(VertexFormat_Pos3NormalUV) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    return new fw::Mesh(VertexFormat_Pos3NormalUV::format, verts.data(), vertBytes, indices.data(), indicesBytes);
}

fw::Mesh* LoadObj(char* objFileName)
{
    uint32 length = 0;
    char* buffer = fw::LoadCompleteFile(objFileName, &length);
    if (buffer == 0 || length == 0)
    {
        delete[] buffer;
        assert(false);
    }

    // Split the string at line endings
    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);

    std::vector<vec2> UVCoordinates;
    std::vector<vec3> VertexNormals;
    std::vector<vec3> VertexPositions;
    std::vector<VertexFormat_Pos3NormalUV> Faces;
    // Keep looping as long as there are lines:
    while (line)
    {
        // Print out the line to see if it's working.
        fw::OutputMessage("%s\n", line);

        // TODO: Process the line.
        int length = (int)strlen(line);
        if (line[0] == 'v')
        {
            //Line is 'vt' : UV Coordinates
            if (line[1] == 't')
            {
                float x;
                float y;
                sscanf_s(line, "vt %f %f", &x, &y);
                UVCoordinates.push_back(vec2(x, y));

            }
            //Line is 'vn' : Vertex Normal
            else if (line[1] == 'n')
            {
                float x;
                float y;
                float z;
                sscanf_s(line, "vn %f %f %f", &x, &y, &z);
                VertexNormals.push_back(vec3(x, y, z));
            }
            //Line is just 'v' : Vertex Position
            else
            {
                float x;
                float y;
                float z;
                sscanf_s(line, "v %f %f %f", &x, &y, &z);
                VertexPositions.push_back(vec3(x, y, z));
            }
        }
        //Face
        else if (line[0] == 'f')
        {
            float posIndex1;
            float UVIndex1;
            float normIndex1;
            
            float posIndex2;
            float UVIndex2;
            float normIndex2;
            
            float posIndex3;
            float UVIndex3;
            float normIndex3;

            sscanf_s(line, "f %f/%f/%f %f/%f/%f %f/%f/%f", &posIndex1, &UVIndex1, &normIndex1, &posIndex2, &UVIndex2, &normIndex2, &posIndex3, &UVIndex3, &normIndex3);

            Faces.push_back({ VertexPositions[(int)posIndex1 - 1], VertexNormals[(int)normIndex1 - 1], UVCoordinates[(int)UVIndex1 - 1] });
            Faces.push_back({ VertexPositions[(int)posIndex2 - 1], VertexNormals[(int)normIndex2 - 1], UVCoordinates[(int)UVIndex2 - 1] });
            Faces.push_back({ VertexPositions[(int)posIndex3 - 1], VertexNormals[(int)normIndex3 - 1], UVCoordinates[(int)UVIndex3 - 1] });

            int i = 0;
        }

        // Go to the next line
        line = strtok_s(0, "\n", &next_token);
    }
    int vertBytes = sizeof(VertexFormat_Pos3NormalUV) * (int)Faces.size();

    std::vector<uint16> indices;
    for (int i = 0; i < (int)Faces.size(); i++)
    {
        indices.push_back(i);
    }

    int indicesBytes = sizeof(uint16) * (int)indices.size();

    return new fw::Mesh(VertexFormat_Pos3NormalUV::format, Faces.data(), vertBytes, indices.data(), indicesBytes);
}

fw::Mesh* CreateHeightMap(char* filename, vec2 size)
{
    uint32 length;
    char* fileContents = fw::LoadCompleteFile(filename, &length);


    int width;
    int height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load_from_memory((unsigned char*)fileContents, length, &width, &height, &channels, 4);
    assert(pixels != nullptr);

    ivec2 VertCount = ivec2(width, height);
    std::vector<VertexFormat_Pos3NormalUV> verts;
    std::vector<uint16> indices;
    std::vector<vec3> vertexs;
  
  
    for (int i = 0; i < width * height; i++)
    {
        int x = i % width;
        int y = (i - x) / width;
        vec2 point = vec2((float)x, (float)y);

        float Mapheight;

        Mapheight = (pixels[4 * i] * 5.0f) / 255.0f;
        vec3 pos = vec3((point.x * size.x) / width, Mapheight, (point.y * size.y) / height);
      
       
        vec3 normal = vec3(0.0f, 1.0f, 0.0f);

        
        vertexs.push_back(pos);

        vec2 UV = point;

        verts.push_back({ pos, normal, UV });
    }

    for (int i = 0; i < width * height; i++)
    {
        int x = i % width;
        int y = (i - x) / width;

        vec3 up;
        vec3 down;
        vec3 left;
        vec3 right;

        int Iup;
        int Idown;
        int Ileft;
        int Iright;

        if (x == 0)
        {
            Ileft = (y * width) + x;
        }
        else
        {
            Ileft = (y * width) + x - 1;
        }

        if (x == width - 1)
        {
            Iright = (y * width) + x;
        }
        else
        {
            Iright = (y * width) + x + 1;
        }

        if (y == 0)
        {
            Idown = (y * width) + x;
        }
        else
        {
            Idown = ((y - 1)* width) + x;
        }

        if (y == height - 1)
        {
            Iup = (y * width) + x;
        }
        else
        {
            Iup = ((y + 1) * width) + x;
        }

        //Get the vertex positions from verts and calculate the normal and assign it.
        up = verts[Iup].pos;
        down = verts[Idown].pos;
        left = verts[Ileft].pos;
        right = verts[Iright].pos;

        vec3 rightLeft = right - left;
        vec3 upDown = up - down;

        vec3 newNormal = upDown.Cross(rightLeft);

        newNormal.Normalize();

        verts[i].normal = newNormal;

    }
    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < width - 1; x++)
        {
            indices.push_back((x + 1) + ((y + 1) * width));
            indices.push_back(x + (y * width));
            indices.push_back(x + ((y + 1) * width));

            indices.push_back((x + 1) + ((y + 1) * width));
            indices.push_back((x + 1) + (y * width));
            indices.push_back(x + (y * width));
        }
    }
    
    int vertBytes = sizeof(VertexFormat_Pos3NormalUV) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    HeightMapMesh* heightMap = new HeightMapMesh(VertexFormat_Pos3NormalUV::format, verts.data(), vertBytes, indices.data(), indicesBytes, size, VertCount, verts);

    return heightMap;
}
