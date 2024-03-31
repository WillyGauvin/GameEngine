#include "Framework.h"
#include "DataTypes.h"

class VirtualController;
class OrbitCamera;
class Player;

class DynamicLightScene : public fw::Scene
{
	using Super = fw::Scene;

public:

	DynamicLightScene(fw::GameCore* pGameCore);
	virtual ~DynamicLightScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void PlaceTrees();

protected:
	VirtualController* m_pController = nullptr;
	Player* m_pPlayer = nullptr;
	OrbitCamera* m_pOrbitCamera;
	fw::GameObject* m_pPlane = nullptr;
	fw::GameObject* m_pIsland = nullptr;
	fw::GameObject* m_pLight = nullptr;

	std::vector<fw::GameObject*> m_pTrees;
};