//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Framework.h"
#include "DataTypes.h"

class Player;

class PhysicsScene;

class JoltScene;

class MidtermScene;

class LandingScene;

class OBJScene;

class VirtualController;

class LightScene;

class OrbitCameraScene;

class DynamicLightScene;

class MiniPuttScene;

enum EditorViews
{
    EditorView_Game,
    EditorView_ImGui,
};

class Game : public fw::GameCore, fw::EventListener
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game() override;

    void CreateUniforms();

    virtual void ExecuteEvent(fw::Event* pEvent) override;
    virtual void StartFrame(float deltaTime) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    fw::ResourceManager* GetResourceManager() { return m_pResources; }
    fw::ImGuiManager* GetGuiManager() { return m_pImGuiManager; }

    void Editor_SelectScene();

    void Editor_CreateMainFrame();

protected:

    // Resources.
    fw::ResourceManager* m_pResources = nullptr;

    PhysicsScene* m_pPhysicsScene = nullptr;

    JoltScene* m_pJoltScene = nullptr;

    MidtermScene* m_pMidtermScene = nullptr;

    LandingScene* m_pLandingScene = nullptr;

    OBJScene* m_pOBJScene = nullptr;

    LightScene* m_pLightScene = nullptr;

    OrbitCameraScene* m_pOrbitCameraScene = nullptr;

    DynamicLightScene* m_pDynamicLightScene = nullptr;

    MiniPuttScene* m_pMiniPuttScene = nullptr;

    fw::ImGuiManager* m_pImGuiManager = nullptr;

    bgfx::TextureHandle m_Game_FBOTexture;
    bgfx::TextureHandle m_Game_FBODepth;

    bgfx::FrameBufferHandle m_Game_FBO;

    uint16 m_maxLights = 10;
};
