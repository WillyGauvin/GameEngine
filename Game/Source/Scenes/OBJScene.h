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

protected:
	fw::GameObject* m_pPlane = nullptr;
	fw::GameObject* m_pOtherPlane = nullptr;

};