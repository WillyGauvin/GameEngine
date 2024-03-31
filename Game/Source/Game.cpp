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
#include "Scenes/JoltScene.h"
#include "Scenes/MidtermScene.h"
#include "Scenes/LandingScene.h"
#include "Scenes/OBJScene.h"
#include "Scenes/LightScene.h"
#include "Scenes/OrbitCameraScene.h"
#include "Scenes/DynamicLightScene.h"
#include "Component/ComponentManager.h"
#include <winsock.h>

Game::Game(fw::FWCore& fwCore)
    : GameCore( fwCore )
{
    WSAData wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData);

    srand((unsigned int)time(NULL));
    // This is a hard-coded 4096x4096 texture, bigger than we should need.
// In a complete engine this texture would need to be destroyed
//     and regenerated if we needed a bigger version.
    m_Game_FBOTexture = bgfx::createTexture2D(4096, 4096, false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT);
    m_Game_FBODepth = bgfx::createTexture2D(4096, 4096, false, 1, bgfx::TextureFormat::D32, BGFX_TEXTURE_RT);


    // Create the framebuffer with the texture and depth buffers.
    bgfx::TextureHandle gameTextures[2] = { m_Game_FBOTexture, m_Game_FBODepth };
    m_Game_FBO = bgfx::createFrameBuffer(2, gameTextures, true);

    bgfx::setViewFrameBuffer(EditorView_Game, m_Game_FBO);

    bgfx::setViewClear(EditorView_Game, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0);

    bgfx::setViewClear(EditorView_ImGui, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x001000ff, 1.0f, 0);

    bgfx::setViewFrameBuffer(EditorView_Game, m_Game_FBO);
    bgfx::setViewRect(EditorView_ImGui, 0, 0, m_FWCore.GetWindowClientWidth(), m_FWCore.GetWindowClientHeight());

    // General renderer settings.
    bgfx::setViewClear( EditorView_Game, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0 );
    bgfx::setViewRect( EditorView_Game, 0, 0, m_FWCore.GetWindowClientWidth(), m_FWCore.GetWindowClientHeight() );

    // Create some manager objects.
    m_pResources = new fw::ResourceManager();
    m_pImGuiManager = new fw::ImGuiManager(GetFramework(), EditorView_ImGui);

    // Create uniforms.
    CreateUniforms();

    // Create vertex formats.
    InitVertexFormats();

    // Load Resources.
    LoadResources( m_pResources );

    //Create some Scenes
    m_pJoltScene = new JoltScene(this);
    m_pMidtermScene = new MidtermScene(this);
    m_pLandingScene = new LandingScene(this);
    m_pOBJScene = new OBJScene(this);
    m_pLightScene = new LightScene(this);
    m_pOrbitCameraScene = new OrbitCameraScene(this);
    m_pDynamicLightScene = new DynamicLightScene(this);
    m_pCurrentScene = m_pDynamicLightScene;

}

Game::~Game()
{
    delete m_pResources;
    delete m_pImGuiManager;
    delete m_pUniforms;
    delete m_pJoltScene;
    delete m_pMidtermScene;
    delete m_pLandingScene;
    delete m_pOBJScene;
    delete m_pOrbitCameraScene;
    delete m_pDynamicLightScene;
}

void Game::CreateUniforms()
{
    assert( m_pUniforms == nullptr );

    m_pUniforms = new fw::Uniforms();

    m_pUniforms->CreateUniform("u_MatWorld", bgfx::UniformType::Mat4);
    m_pUniforms->CreateUniform("u_MatWorldRotation", bgfx::UniformType::Mat4);
    m_pUniforms->CreateUniform("u_MatView", bgfx::UniformType::Mat4);
    m_pUniforms->CreateUniform("u_MatProj", bgfx::UniformType::Mat4);


    m_pUniforms->CreateUniform( "u_CameraPosition", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_ProjectionScale", bgfx::UniformType::Vec4 );

    m_pUniforms->CreateUniform( "u_DiffuseColor", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_TextureColor", bgfx::UniformType::Sampler );
    m_pUniforms->CreateUniform( "u_UVScale", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_UVOffset", bgfx::UniformType::Vec4 );

    m_pUniforms->CreateUniform( "u_Time", bgfx::UniformType::Vec4 );
 
    //light pos vec3
    m_pUniforms->CreateUniform("u_LightPosition", bgfx::UniformType::Vec4);
    //light color vec4
    m_pUniforms->CreateUniform("u_LightColor", bgfx::UniformType::Vec4);

    //light range float
    m_pUniforms->CreateUniform("u_LightRange", bgfx::UniformType::Vec4);
    //ambient percentage float
    m_pUniforms->CreateUniform("u_AmbientPercentage", bgfx::UniformType::Vec4);
    //falloff exponent float
    m_pUniforms->CreateUniform("u_FalloffExponent", bgfx::UniformType::Vec4);
    //specular exponent float
    m_pUniforms->CreateUniform("u_SpecularExponent", bgfx::UniformType::Vec4);

    
}

void Game::ExecuteEvent(fw::Event* pEvent)
{
    m_pCurrentScene->ExecuteEvent(pEvent);

    if (pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType())
    {
        bgfx::setViewFrameBuffer(EditorView_Game, m_Game_FBO);
    }
}

void Game::StartFrame(float deltaTime)
{
    m_pCurrentScene->StartFrame(deltaTime);
    m_pImGuiManager->StartFrame(deltaTime);
    Editor_CreateMainFrame();
}

void Game::Update(float deltaTime)
{
    Editor_SelectScene();
    m_pCurrentScene->Update(deltaTime);
}

void Game::Draw()
{
    if (ImGui::Begin("Game view"))
    {
        ImVec2 minSize = ImGui::GetWindowContentRegionMin();
        ImVec2 size = ImGui::GetWindowContentRegionMax();
        ImTextureID imText = fw::imguiTexture(m_Game_FBOTexture);
        ImVec2 UVMin = ImVec2(0, 1);
        ImVec2 UVMax = ImVec2(m_FWCore.GetWindowClientWidth() / 4096.0f, 1 - m_FWCore.GetWindowClientHeight() / 4096.0f);
        ImGui::Image(imText, size - minSize, UVMin, UVMax);
    }



    ImGui::End();

    float time = (float)fw::GetSystemTimeSinceGameStart();
    bgfx::setUniform(m_pUniforms->GetUniform("u_Time"), &time);

    m_pCurrentScene->Draw();
    m_pImGuiManager->EndFrame();
}

void Game::Editor_SelectScene()
{
    ImGui::Begin("SceneSelector");

    if (ImGui::Button("Jolt"))
    {
        m_pCurrentScene = m_pJoltScene;
    }
    if (ImGui::Button("Midterm"))
    {
        m_pCurrentScene = m_pMidtermScene;
    }
    if (ImGui::Button("Landing"))
    {
        m_pCurrentScene = m_pLandingScene;
    }
    if (ImGui::Button("OBJ"))
    {
        m_pCurrentScene = m_pOBJScene;
    }
    if (ImGui::Button("Light"))
    {
        m_pCurrentScene = m_pLightScene;
    }
    if (ImGui::Button("DynamicLight"))
    {
        m_pCurrentScene = m_pDynamicLightScene;
    }
    ImGui::End();
}

void Game::Editor_CreateMainFrame()
{
    // Setup a main window with no frame and a dockspace that covers the entire viewport.
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    if (ImGui::Begin("Main Dock", nullptr, flags))
    {
        ImGuiID dockspaceID = ImGui::GetID("My Dockspace");
        ImGui::DockSpace(dockspaceID);
    }
    ImGui::End();
}

