#pragma once

#include "Framework.h"
#include "DataTypes.h"

class VirtualController;
class Player;

class JimmyScene : public fw::Scene
{
public:
	JimmyScene(fw::GameCore* pGameCore);
	virtual ~JimmyScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:

	fw::Camera* m_pCamera = nullptr;
	Player* m_pPlayer = nullptr;
	std::vector<fw::GameObject*> m_Objects;
	VirtualController* m_pController = nullptr;

	void Editor_DisplayObjectList();
	void Editor_DisplayResources();
	void Editor_DisableEnable();
};