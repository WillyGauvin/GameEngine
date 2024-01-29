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
#include "LoadResources.h"
#include "Objects/Player.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"
#include "Objects/VirtualController.h"
#include "Scenes/JimmyScene.h"
#include "Scenes/CubeScene.h"
#include "Scenes/PhysicsScene.h"

Game::Game(fw::FWCore& fwCore)
    : GameCore( fwCore )
{
    // General renderer settings.
    int viewID = 0;
    bgfx::setViewClear( viewID, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0 );
    bgfx::setViewRect( viewID, 0, 0, m_FWCore.GetWindowClientWidth(), m_FWCore.GetWindowClientHeight() );

    // Create some manager objects.
    m_pResources = new fw::ResourceManager();
    m_pImGuiManager = new fw::ImGuiManager(GetFramework(), 1);

    // Create uniforms.
    CreateUniforms();

    // Create vertex formats.
    InitVertexFormats();

    // Load Resources.
    LoadResources( m_pResources );

    //Create some Scenes
    m_pCubeScene = new CubeScene(this);
    m_pJimmyScene = new JimmyScene(this);
    m_pPhysicsScene = new PhysicsScene(this);
    m_pCurrentScene = m_pPhysicsScene;
}

Game::~Game()
{
    delete m_pResources;
    delete m_pImGuiManager;
    delete m_pUniforms;

    delete m_pJimmyScene;
    delete m_pCubeScene;
}

void Game::CreateUniforms()
{
    assert( m_pUniforms == nullptr );

    m_pUniforms = new fw::Uniforms();

    m_pUniforms->CreateUniform("u_MatWorld", bgfx::UniformType::Mat4);
    m_pUniforms->CreateUniform("u_MatView", bgfx::UniformType::Mat4);
    m_pUniforms->CreateUniform("u_MatProj", bgfx::UniformType::Mat4);


    m_pUniforms->CreateUniform( "u_CameraPosition", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_ProjectionScale", bgfx::UniformType::Vec4 );

    m_pUniforms->CreateUniform( "u_DiffuseColor", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_TextureColor", bgfx::UniformType::Sampler );
    m_pUniforms->CreateUniform( "u_UVScale", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_UVOffset", bgfx::UniformType::Vec4 );

    m_pUniforms->CreateUniform( "u_Time", bgfx::UniformType::Vec4 );
 
    
}

void Game::ExecuteEvent(fw::Event* pEvent)
{
    m_pCurrentScene->ExecuteEvent(pEvent);
}

void Game::StartFrame(float deltaTime)
{
    m_pCurrentScene->StartFrame(deltaTime);
    m_pImGuiManager->StartFrame(deltaTime);
}

void Game::Update(float deltaTime)
{
    Editor_SelectScene();
    m_pCurrentScene->Update(deltaTime);
}

void Game::Draw()
{
    m_pCurrentScene->Draw();
    m_pImGuiManager->EndFrame();
}

void Game::Editor_SelectScene()
{
    ImGui::Begin("SceneSelector");
    if (ImGui::Button("Default"))
    {
        m_pCurrentScene = m_pJimmyScene;
    }
    if (ImGui::Button("Cube"))
    {
        m_pCurrentScene = m_pCubeScene;
    }
    if (ImGui::Button("Physics"))
    {
        m_pCurrentScene = m_pPhysicsScene;
    }
    ImGui::End();
}

