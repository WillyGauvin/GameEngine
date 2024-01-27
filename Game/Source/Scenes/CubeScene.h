#pragma once

#include "Framework.h"
#include "DataTypes.h"

class VirtualController;
class Player;

class CubeScene : public fw::Scene
{
public:
	CubeScene(fw::GameCore* pGameCore);
	virtual ~CubeScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	fw::GameObject* m_pRotatingDice = nullptr;
	vec3 m_rotation = vec3 (45,0,0);
};