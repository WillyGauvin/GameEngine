#pragma once

#include "Framework.h"
#include "DataTypes.h"

class JoltScene : public fw::Scene
{
public:

	JoltScene(fw::GameCore* pGameCore);
	virtual ~JoltScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	
protected:
	fw::JoltWorldBundle* m_pWorldBundle = nullptr;
	JPH::Body* m_pBody = nullptr;
};