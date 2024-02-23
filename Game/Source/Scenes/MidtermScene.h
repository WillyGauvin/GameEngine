#pragma once

#include "Framework.h"
#include "DataTypes.h"

class MidtermScene : public fw::Scene
{
public:

	MidtermScene(fw::GameCore* pGameCore);
	virtual ~MidtermScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:

};