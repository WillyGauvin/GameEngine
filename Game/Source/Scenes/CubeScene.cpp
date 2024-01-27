#include "CubeScene.h"
#include "Objects/VirtualController.h"
#include "Events/GameEvents.h"
#include "Game.h"
#include "Objects/Player.h"


CubeScene::CubeScene(fw::GameCore* pGameCore)
	: fw::Scene(pGameCore)
{
    //Register for Events
    GetEventManager()->RegisterListener(RemoveFromGameEvent::GetStaticEventType(), this);
    GetEventManager()->RegisterListener(fw::CharEvent::GetStaticEventType(), this);

    Game* game = static_cast<Game*>(m_pGameCore);

#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_pRotatingDice = new fw::GameObject(this, "Dice", vec3(0, 0, 0), getMesh("Cube"), getMaterial("Dice"));
    m_Objects.push_back(m_pRotatingDice);
    m_Objects.push_back(new fw::GameObject(this, "Dice2", vec3(5, 5, 20), getMesh("Cube"), getMaterial("Dice")));
    m_Objects.push_back(new fw::GameObject(this, "Dice3", vec3(-4, -2, -15), getMesh("Cube"), getMaterial("Dice")));
    m_Objects.push_back(new fw::GameObject(this, "Dice2", vec3(0, 5, 30), getMesh("WideXCube"), getMaterial("Dice")));
    m_Objects[m_Objects.size() - 1]->SetRotation(vec3(0,45,0));
    m_Objects.push_back(new fw::GameObject(this, "Dice2", vec3(5, 0, 25), getMesh("WideYCube"), getMaterial("Dice")));
    m_Objects[m_Objects.size() - 1]->SetRotation(vec3(45, 0, 0));
    m_Objects.push_back(new fw::GameObject(this, "Dice2", vec3(5, -5, -8), getMesh("WideZCube"), getMaterial("Dice")));
    m_Objects[m_Objects.size() - 1]->SetRotation(vec3(0, 0, 0));





}

CubeScene::~CubeScene()
{
}

void CubeScene::ExecuteEvent(fw::Event* pEvent)
{
    // Pass "WM_CHAR" events to imgui to handle text input.
    if (pEvent->GetType() == fw::CharEvent::GetStaticEventType())
    {
        int character = static_cast<fw::CharEvent*>(pEvent)->GetValue();
        Game* pGame = static_cast<Game*>(m_pGameCore);
        pGame->GetGuiManager()->AddInputCharacter(character);
    }
}

void CubeScene::StartFrame(float deltaTime)
{
    m_pEventManager->ProcessEvents();
}

void CubeScene::Update(float deltaTime)
{
    m_rotation += vec3(0, 0.3, 0.3);
    if (m_rotation.y > 359)
    {
        m_rotation = vec3(45, 0, 0);
    }
    m_pRotatingDice->SetRotation(m_rotation);
    m_pCamera->Update(deltaTime);
}

void CubeScene::Draw()
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
