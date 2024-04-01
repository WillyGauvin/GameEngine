#pragma once

#include "DataTypes.h"

class EventListener;

class EventManager;

class VirtualController : public fw::EventListener
{
public:
	enum Actions
	{
		Teleport = 1 << 0,
		Up		 = 1 << 1,
		Down	 = 1 << 2,
		Left	 = 1 << 3,
		Right	 = 1 << 4,
		Reset	 = 1 << 5,
		OrbitUp  = 1 << 6,
		OrbitDown = 1 << 7,
		OrbitLeft  = 1 << 8,
		OrbitRight  = 1 << 9,
		ZoomIn	 = 1 << 10,
		ZoomOut  = 1 << 11,
	};
public:
	VirtualController(fw::EventManager* pEventManager);
	virtual ~VirtualController();

	virtual void ExecuteEvent(fw::Event* pEvent) override;

	void StartFrame();
	bool isActionHeld(Actions action);
	bool WasActionPressed(Actions action);
	bool WasActionReleased(Actions action);

	void SetControlledObject(fw::GameObject* pawn) { controlledPawn = pawn; }

protected:
	fw::GameObject* controlledPawn = nullptr;
	uint32 m_Actions = 0;
	uint32 m_OldActions = 0;

};