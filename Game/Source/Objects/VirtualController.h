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

	};
public:
	VirtualController(fw::EventManager* pEventManager);
	virtual ~VirtualController();

	virtual void ExecuteEvent(fw::Event* pEvent) override;

	void StartFrame();
	bool isActionHeld(Actions action) { return (m_Actions & action); }
	bool WasActionPressed(Actions action) { return !(m_OldActions & action); }
	bool WasActionReleased(Actions action) { return (m_OldActions & ~m_Actions); }

	//Math doesn't work
protected:
	uint32 m_Actions = 0;
	uint32 m_OldActions = 0;

};