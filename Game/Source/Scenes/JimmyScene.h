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
	Player* m_pPlayer = nullptr;
	VirtualController* m_pController = nullptr;

	void Editor_DisplayObjectList();
	void Editor_DisplayResources();
};