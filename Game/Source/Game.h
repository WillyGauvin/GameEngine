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

class JimmyScene;

class CubeScene;

class PhysicsScene;

class TestScene;

class VirtualController;

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

protected:

    // Resources.
    fw::ResourceManager* m_pResources = nullptr;

    JimmyScene* m_pJimmyScene = nullptr;
    CubeScene* m_pCubeScene = nullptr;
    PhysicsScene* m_pPhysicsScene = nullptr;
    TestScene* m_pTestScene = nullptr;

    fw::ImGuiManager* m_pImGuiManager = nullptr;
};
