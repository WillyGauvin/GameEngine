#include "Framework.h"
#include "DataTypes.h"

class VirtualController;
class OrbitCamera;
class Player;

class FinalExamScene : public fw::Scene
{
	using Super = fw::Scene;

public:

	FinalExamScene(fw::GameCore* pGameCore);
	virtual ~FinalExamScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual fw::Camera* GetCamera() override;

protected:
	VirtualController* m_pController = nullptr;
	Player* m_pPlayer = nullptr;
	OrbitCamera* m_pOrbitCamera;
	fw::GameObject* m_pPlane = nullptr;
	fw::GameObject* m_pIsland = nullptr;
	fw::GameObject* m_pLight = nullptr;


};