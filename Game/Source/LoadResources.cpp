//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "DataTypes.h"
#include "Game.h"
#include "Objects/Player.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"

#define getMesh pResources->Get<fw::Mesh>
#define getShader pResources->Get<fw::ShaderProgram>
#define getTexture pResources->Get<fw::Texture>
#define getMaterial pResources->Get<fw::Material>

void LoadResources(fw::ResourceManager* pResources)
{
    // Create some meshes.
    pResources->Add<fw::Mesh>( "Triangle", CreateTriangleMesh() );
    pResources->Add<fw::Mesh>( "Square", CreateSquareMesh() );
    pResources->Add<fw::Mesh>( "Sprite", CreateSpriteMesh() );
    pResources->Add<fw::Mesh>("Circle", CreateCircleMesh());
    pResources->Add<fw::Mesh>("Cube", CreateCubeMesh(vec3(1, 1, 1)));
    pResources->Add<fw::Mesh>("WideXCube", CreateCubeMesh(vec3(5, 1, 1)));
    pResources->Add<fw::Mesh>("WideYCube", CreateCubeMesh(vec3(1, 5, 1)));
    pResources->Add<fw::Mesh>("WideZCube", CreateCubeMesh(vec3(1, 1, 5)));



    // Load some shaders.
    pResources->Add<fw::ShaderProgram>( "SolidColor", new fw::ShaderProgram( "Data/Shaders/", "SolidColor.vert.bin", "SolidColor.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "VertexColor", new fw::ShaderProgram( "Data/Shaders/", "VertexColor.vert.bin", "VertexColor.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "Texture", new fw::ShaderProgram( "Data/Shaders/", "Texture.vert.bin", "Texture.frag.bin" ) );

    // Load some textures.
    pResources->Add<fw::Texture>( "MegaMan", new fw::Texture( "Data/Textures/MegaMan.png" ) );
    pResources->Add<fw::Texture>("Dice", new fw::Texture("Data/Textures/dice.png"));
    pResources->Add<fw::Texture>("ShipOff", new fw::Texture("Data/Textures/LunarLanding/Off.png"));
    pResources->Add<fw::Texture>("ShipLeft", new fw::Texture("Data/Textures/LunarLanding/Left.png"));
    pResources->Add<fw::Texture>("ShipRight", new fw::Texture("Data/Textures/LunarLanding/Right.png"));
    pResources->Add<fw::Texture>("ShipBoth", new fw::Texture("Data/Textures/LunarLanding/Both.png"));
    pResources->Add<fw::Texture>("ShipCrash", new fw::Texture("Data/Textures/LunarLanding/Crash.png"));



    // Create some materials.
    pResources->Add<fw::Material>( "Red", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Red(), false ) );
    pResources->Add<fw::Material>( "Blue", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Blue(), false ) );
    pResources->Add<fw::Material>( "Green", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Green(), false ) );
    pResources->Add<fw::Material>("Orange", new fw::Material(getShader("SolidColor"), nullptr, fw::color4f::Orange(), false));
    pResources->Add<fw::Material>("Yellow", new fw::Material(getShader("SolidColor"), nullptr, fw::color4f::Yellow(), false));
    pResources->Add<fw::Material>( "VertexColor", new fw::Material( getShader("VertexColor"), nullptr, fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "MegaMan", new fw::Material( getShader("Texture"), getTexture("MegaMan"), fw::color4f::White(), true ) );
    pResources->Add<fw::Material>("Dice", new fw::Material(getShader("Texture"), getTexture("Dice"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("ShipOff", new fw::Material(getShader("Texture"), getTexture("ShipOff"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("ShipLeft", new fw::Material(getShader("Texture"), getTexture("ShipLeft"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("ShipRight", new fw::Material(getShader("Texture"), getTexture("ShipRight"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("ShipBoth", new fw::Material(getShader("Texture"), getTexture("ShipBoth"), fw::color4f::White(), true));
    pResources->Add<fw::Material>("ShipCrash", new fw::Material(getShader("Texture"), getTexture("ShipCrash"), fw::color4f::White(), true));




}
