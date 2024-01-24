#include "CubeScene.h"
#include "Objects/VirtualController.h"
#include "Events/GameEvents.h"
#include "Game.h"
#include "Objects/Player.h"


CubeScene::CubeScene(fw::GameCore* pGameCore)
	: fw::Scene(pGameCore)
{
    m_pEventManager = new fw::EventManager(m_pGameCore);

    m_pImGuiManager = new fw::ImGuiManager(m_pGameCore->GetFramework(), 1);

    m_pCamera = new fw::Camera(this, vec3(5, 5, 0));

    m_pController = new VirtualController(m_pEventManager);

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

CubeScene::~CubeScene()
{
}

void CubeScene::ExecuteEvent(fw::Event* pEvent)
{
}

void CubeScene::StartFrame(float deltaTime)
{
}

void CubeScene::Update(float deltaTime)
{
}

void CubeScene::Draw()
{
}

void CubeScene::Editor_DisplayObjectList()
{
}

void CubeScene::Editor_DisplayResources()
{
}

void CubeScene::Editor_DisableEnable()
{
}
