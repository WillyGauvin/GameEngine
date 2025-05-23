//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "FWCore.h"
#include "ImGuiManager.h"
#include "../Libraries/imgui/imgui.h"
#include "imgui_impl_bgfx.h"

// Relies on imgui_impl_bgfx
//    https://gist.github.com/pr0g/aff79b71bf9804ddb03f39ca7c0c3bbb
// Forked from
//    https://gist.github.com/RichardGale/6e2b74bc42b3005e08397236e4be0fd0
// Along with these shaders from the bgfx examples:
//    fs_ocornut_imgui.bin.h
//    vs_ocornut_imgui.bin.h

namespace fw {

    ImGuiManager* g_pImGuiManager = nullptr;

    ImGuiManager::ImGuiManager(FWCore* pFramework, int viewID)
    {
        m_pFramework = pFramework;
        Init( viewID );

        //Register For Events
        //pFramework->GetEventManager()->RegisterListener(WindowResizeEvent::GetStaticEventType(), this);

    }

    void ImGuiManager::ExecuteEvent(Event* pEvent)
    {
        if (pEvent->GetType() == fw::CharEvent::GetStaticEventType())
        {
            int character = static_cast<fw::CharEvent*>(pEvent)->GetValue();
            AddInputCharacter(character);
        }
    }

    ImGuiManager::~ImGuiManager()
    {
        Shutdown();
    }

    void ImGuiManager::Init(int viewID)
    {
        ImGui::CreateContext();

        CreateDeviceObjects();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = (float)m_pFramework->GetWindowClientWidth();
        io.DisplaySize.y = (float)m_pFramework->GetWindowClientHeight();
        io.IniFilename = "imgui.ini";
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // Keyboard mapping.  ImGui will use those indices to peek into the io.KeyDown[] array.
        io.KeyMap[ImGuiKey_Tab] = VK_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
        io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
        io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
        io.KeyMap[ImGuiKey_Home] = VK_HOME;
        io.KeyMap[ImGuiKey_End] = VK_END;
        io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
        io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
        io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
        io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
        io.KeyMap[ImGuiKey_A] = 'A';
        io.KeyMap[ImGuiKey_C] = 'C';
        io.KeyMap[ImGuiKey_V] = 'V';
        io.KeyMap[ImGuiKey_X] = 'X';
        io.KeyMap[ImGuiKey_Y] = 'Y';
        io.KeyMap[ImGuiKey_Z] = 'Z';

        ImGui_Implbgfx_Init( viewID );
    }

    void ImGuiManager::Shutdown()
    {
        ImGui_Implbgfx_Shutdown();

        ImGui::DestroyContext();
    }

    void ImGuiManager::AddInputCharacter(unsigned int value)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter( value );
    }

    void ImGuiManager::ClearInput()
    {
        ImGuiIO& io = ImGui::GetIO();

        for( int i=0; i<5; i++ )
        {
            io.MouseDown[i] = false;
        }

        io.MouseWheel = 0;

        for( int i=0; i<512; i++ )
        {
            io.KeysDown[i] = false;
        }

        io.KeyCtrl = false;
        io.KeyShift = false;
        io.KeyAlt = false;
        io.KeySuper = false;
    }

    void ImGuiManager::OnFocusLost()
    {
        ClearInput();
    }

    void ImGuiManager::StartFrame(float deltaTime)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = deltaTime;
        io.DisplaySize.x = (float)m_pFramework->GetWindowClientWidth();
        io.DisplaySize.y = (float)m_pFramework->GetWindowClientHeight();

        io.KeyCtrl = io.KeysDown[VK_CONTROL] || io.KeysDown[VK_LCONTROL] || io.KeysDown[VK_RCONTROL];
        io.KeyShift = io.KeysDown[VK_SHIFT] || io.KeysDown[VK_LSHIFT] || io.KeysDown[VK_RSHIFT];
        io.KeyAlt = io.KeysDown[VK_MENU] || io.KeysDown[VK_LMENU] || io.KeysDown[VK_RMENU];
        io.KeySuper = io.KeysDown[VK_LWIN] || io.KeysDown[VK_RWIN];

        int mx, my;
        m_pFramework->GetMouseCoordinates( &mx, &my );
        io.MousePos.x = (float)mx;
        io.MousePos.y = (float)my;
        io.MouseDown[0] = m_pFramework->IsMouseButtonDown( 0 );
        io.MouseDown[1] = m_pFramework->IsMouseButtonDown( 1 );
        io.MouseDown[2] = m_pFramework->IsMouseButtonDown( 2 );
        io.MouseWheel = m_pFramework->GetMouseWheel();

        for( int i=0; i<256; i++ )
        {
            io.KeysDown[i] = m_pFramework->IsKeyDown( i );
        }

        ImGui_Implbgfx_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiManager::EndFrame()
    {
        ImGui::Render();
        ImDrawData* data = ImGui::GetDrawData();
        RenderDrawLists( data );
    }

    // This is the main rendering function
    // If text or lines are blurry when integrating ImGui in your engine:
    // - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
    void ImGuiManager::RenderDrawLists(ImDrawData* draw_data)
    {
        ImGui_Implbgfx_RenderDrawLists( draw_data );
    }

    bool ImGuiManager::CreateDeviceObjects()
    {
        return ImGui_Implbgfx_CreateDeviceObjects();
    }

    void ImGuiManager::InvalidateDeviceObjects()
    {
        ImGui_Implbgfx_InvalidateDeviceObjects();
    }

} // namespace fw
