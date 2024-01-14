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
#include "Events/GameEvents.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"

Game::Game(fw::FWCore& fwCore)
    : GameCore( fwCore )
{
    // General renderer settings.
    int viewID = 0;
    bgfx::setViewClear( viewID, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0 );
    bgfx::setViewRect( viewID, 0, 0, m_FWCore.GetWindowClientWidth(), m_FWCore.GetWindowClientHeight() );

    // Create some manager objects.
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore, 1 );
    m_pResources = new fw::ResourceManager();
    m_pEventManager = new fw::EventManager(this);

    //Register for Events
    GetEventManager()->RegisterListener(RemoveFromGameEvent::GetStaticEventType(), this);

    // Create uniforms.
    CreateUniforms();

    // Create vertex formats.
    InitVertexFormats();

    // Load Resources.
    LoadResources( m_pResources );

    // Create some GameObjects.
    m_pCamera = new fw::Camera( this, vec3(5,5,0) );

#define getMesh m_pResources->Get<fw::Mesh>
#define getMaterial m_pResources->Get<fw::Material>

    m_pPlayer = new Player( this, "Player", vec3(6,5,0), getMesh("Sprite"), getMaterial("MegaMan") );
    m_Objects.push_back( m_pPlayer );

    m_Objects.push_back( new fw::GameObject( this, "Object 1", vec3(0,0,0), getMesh("Triangle"), getMaterial("VertexColor") ) );
    m_Objects.push_back( new fw::GameObject( this, "Object 2", vec3(10,10,0), getMesh("Triangle"), getMaterial("Blue") ) );
    m_Objects.push_back( new fw::GameObject( this, "Object 3", vec3(5,5,0), getMesh("Square"), getMaterial("VertexColor") ) );
    m_Objects.push_back( new fw::GameObject( this, "Object 4", vec3(1,1,0), getMesh("Square"), getMaterial("VertexColor") ) );
    m_Objects.push_back( new fw::GameObject( this, "Object 5", vec3(1,9,0), getMesh("Square"), getMaterial("Blue") ) );
}

Game::~Game()
{
    for( fw::GameObject* pObject : m_Objects )
    {
        delete pObject;
    }
    
    delete m_pCamera;

    delete m_pResources;
    delete m_pUniforms;

    delete m_pImGuiManager;

    delete m_pEventManager;
}

void Game::CreateUniforms()
{
    assert( m_pUniforms == nullptr );

    m_pUniforms = new fw::Uniforms();
    m_pUniforms->CreateUniform( "u_Position", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_Rotation", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_Scale", bgfx::UniformType::Vec4 );

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
    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find(m_Objects.begin(), m_Objects.end(), pObject);
        m_Objects.erase(it);

        delete pObject;
    }
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    m_pEventManager->ProcessEvents();
}

void Game::OnEvent(fw::Event* pEvent)
{
    // Process events.

    // Remove object from GameObject list and delete it.
    /*if( pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType() )
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>( pEvent );
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find( m_Objects.begin(), m_Objects.end(), pObject );
        m_Objects.erase( it );

        delete pObject;
    }*/

    // Set the new aspect ratio in the camera.
    /*if( pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType() )
    {
        int width = m_FWCore.GetWindowClientWidth();
        int height = m_FWCore.GetWindowClientHeight();

        m_pCamera->SetAspectRatio( (float)width/height );
    }*/

    // Pass "WM_CHAR" events to imgui to handle text input.
    /*if( pEvent->GetType() == fw::CharEvent::GetStaticEventType() )
    {
        int character = static_cast<fw::CharEvent*>(pEvent)->GetValue();
        m_pImGuiManager->AddInputCharacter( character );
    }*/
}

void Game::Update(float deltaTime)
{
    if( m_FWCore.IsKeyDown('X') )
    {
        if( m_Objects.size() > 1 )
        {
            RemoveFromGameEvent* pEvent = new RemoveFromGameEvent(m_Objects[1]);
            m_pEventManager->AddEvent(pEvent);
        }
    }

    for( fw::GameObject* pObject : m_Objects )
    {
        pObject->Update( deltaTime );
    }

    m_pCamera->Update( deltaTime );

    Editor_DisplayObjectList();
    Editor_DisplayResources();
}

void Game::Draw()
{
    int viewID = 0;

    // Setup time uniforms.
    float time = (float)fw::GetSystemTimeSinceGameStart();
    bgfx::setUniform( m_pUniforms->GetUniform("u_Time"), &time );

    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable( viewID );

    // Draw all objects.
    for( fw::GameObject* pObject : m_Objects )
    {
        pObject->Draw( m_pCamera );
    }

    m_pImGuiManager->EndFrame();
}

void Game::Editor_DisplayObjectList()
{
    ImGui::Begin( "Object List" );

    for( fw::GameObject* pObject : m_Objects )
    {
        ImGui::Text( "%s", pObject->GetName().c_str() );
    }

    // Testing character input, get rid of this once you confirm its working.
    int i = 50;
    ImGui::InputInt( "Test", &i );

    ImGui::End(); // "Object List"
}

void Game::Editor_DisplayResources()
{
    ImGui::Begin("Resources");

    m_pResources->Editor_DisplayResourceLists();

    ImGui::End(); // "Resources"
}
