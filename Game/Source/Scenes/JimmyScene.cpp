#include "JimmyScene.h"

#include "Objects/Player.h"
#include "Objects/VirtualController.h"
#include "Game.h"
#include "Events/GameEvents.h"


JimmyScene::JimmyScene(fw::GameCore* pGameCore) 
	: fw::Scene(pGameCore)
{
    m_pController = new VirtualController(m_pEventManager);

    m_pCamera->SetPosition(vec3(5, 5, 0));
    //Register for Events
    GetEventManager()->RegisterListener(RemoveFromGameEvent::GetStaticEventType(), this);
    GetEventManager()->RegisterListener(fw::CharEvent::GetStaticEventType(), this);

    Game* game = static_cast<Game*>(m_pGameCore);

    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_pPlayer = new Player(this, "Player", vec3(6, 5, 0), getMesh("Sprite"), getMaterial("MegaMan"));
    m_Objects.push_back(m_pPlayer);

    m_Objects.push_back(new fw::GameObject(this, "Object 1", vec3(0, 0, 0), getMesh("Triangle"), getMaterial("VertexColor")));
    m_Objects.push_back(new fw::GameObject(this, "Object 2", vec3(10, 10, 0), getMesh("Triangle"), getMaterial("Blue")));
    m_Objects.push_back(new fw::GameObject(this, "Object 3", vec3(5, 5, 0), getMesh("Square"), getMaterial("VertexColor")));
    m_Objects.push_back(new fw::GameObject(this, "Object 4", vec3(1, 1, 0), getMesh("Square"), getMaterial("VertexColor")));
    m_Objects.push_back(new fw::GameObject(this, "Object 5", vec3(1, 9, 0), getMesh("Square"), getMaterial("Blue")));
    m_Objects.push_back(new fw::GameObject(this, "Object 6", vec3(7, 2, 0), getMesh("Circle"), getMaterial("Blue")));

    m_pPlayer->SetController(m_pController);
}

JimmyScene::~JimmyScene()
{
    delete m_pController;
}

void JimmyScene::ExecuteEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find(m_Objects.begin(), m_Objects.end(), pObject);
        m_Objects.erase(it);

        delete pObject;
    }

    // Pass "WM_CHAR" events to imgui to handle text input.
    if (pEvent->GetType() == fw::CharEvent::GetStaticEventType())
    {
        int character = static_cast<fw::CharEvent*>(pEvent)->GetValue();
        Game* pGame = static_cast<Game*>(m_pGameCore);
        pGame->GetGuiManager()->AddInputCharacter(character);
    }
}

void JimmyScene::StartFrame(float deltaTime)
{
    m_pController->StartFrame();
    m_pEventManager->ProcessEvents();
}

void JimmyScene::Update(float deltaTime)
{
    Editor_DisplayObjectList();
    Editor_DisplayResources();

    if (m_pGameCore->GetFramework()->IsKeyDown('X'))
    {
        if (m_Objects.size() > 1)
        {
            RemoveFromGameEvent* pEvent = new RemoveFromGameEvent(m_Objects[1]);
            m_pEventManager->AddEvent(pEvent);
        }
    }

    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Update(deltaTime);
    }

    m_pCamera->Update(deltaTime);
}

void JimmyScene::Draw()
{
    int viewID = 0;

    // Setup time uniforms.
    float time = (float)fw::GetSystemTimeSinceGameStart();
    bgfx::setUniform(m_pGameCore->GetUniforms()->GetUniform("u_Time"), &time);
 
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(viewID);

    // Draw all objects.
    for (fw::GameObject* pObject : m_Objects)
    {
        pObject->Draw(m_pCamera);
    }
}

void JimmyScene::Editor_DisplayObjectList()
{
    ImGui::Begin("Object List");

    for (fw::GameObject* pObject : m_Objects)
    {
        ImGui::Text("%s", pObject->GetName().c_str());
    }

    // Testing character input, get rid of this once you confirm its working.
    int i = 50;
    ImGui::InputInt("Test", &i);

    ImGui::End(); // "Object List"
}

void JimmyScene::Editor_DisplayResources()
{
    ImGui::Begin("Resources");

    static_cast<Game*>(m_pGameCore)->GetResourceManager()->Editor_DisplayResourceLists();

    ImGui::End(); // "Resources"
}

//void JimmyScene::Editor_DisableEnable()
//{
//    if (ImGui::Button("Enable"))
//    {
//        for (fw::GameObject* pObject : m_Objects)
//        {
//            pObject->Enable();
//        }
//    }
//    if (ImGui::Button("Disable"))
//    {
//        for (fw::GameObject* pObject : m_Objects)
//        {
//            pObject->Disable();
//        }
//    }
//
//}
