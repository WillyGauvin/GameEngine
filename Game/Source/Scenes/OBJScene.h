#include "Framework.h"
#include "DataTypes.h"

class OBJScene : public fw::Scene
{
public:

	OBJScene(fw::GameCore* pGameCore);
	virtual ~OBJScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void PlaceTrees();

protected:
	fw::GameObject* m_pPlane = nullptr;
	fw::GameObject* m_pIsland = nullptr;
	fw::GameObject* m_pTestDice = nullptr;
	std::vector<fw::GameObject*> m_pTrees;
};