//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

namespace fw {

    class Event;
    class FWCore;
    class Uniforms;
    class EventManager;

    class GameCore
    {
    public:
        GameCore(FWCore& fwCore) : m_FWCore( fwCore ) {}
        virtual ~GameCore() = 0 {}

        virtual void StartFrame(float deltaTime) = 0;
        virtual void OnEvent(Event* pEvent) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() = 0;

        // Getters.
        FWCore* GetFramework() { return &m_FWCore; }
        Uniforms* GetUniforms() { return m_pUniforms; }
        EventManager* GetEventManager() { return m_pEventManager; }

    protected:
        FWCore& m_FWCore;

        EventManager* m_pEventManager = nullptr;
        // Resources.
        Uniforms* m_pUniforms = nullptr;
    };

} // namespace fw
