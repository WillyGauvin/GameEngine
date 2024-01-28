#include "TestScene.h"

TestScene::TestScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{
}

TestScene::~TestScene()
{
}

void TestScene::ExecuteEvent(fw::Event* pEvent)
{
}

void TestScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void TestScene::Update(float deltaTime)
{
	m_pCamera->Update(deltaTime);
}

void TestScene::Draw()
{
    int viewID = 0;

    // Setup time uniforms.
    float time = (float)fw::GetSystemTimeSinceGameStart();
    bgfx::setUniform(m_pGameCore->GetUniforms()->GetUniform("u_Time"), &time);

    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(viewID);


}
