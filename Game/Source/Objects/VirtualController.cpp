#include "Framework.h"

#include "DataTypes.h"

#include "VirtualController.h"

VirtualController::VirtualController(fw::EventManager* pEventManager)
{
	pEventManager->RegisterListener(fw::InputEvent::GetStaticEventType(), this);
}

VirtualController::~VirtualController()
{
}

void VirtualController::ExecuteEvent(fw::Event* pEvent)
{
	// Code to set controls based on events.
	if (pEvent->GetType() == fw::InputEvent::GetStaticEventType())
	{
		fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>(pEvent);

		if (pInputEvent->GetDeviceType() == fw::InputEvent::DeviceType::Keyboard)
		{
			if (pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
			{
				switch (pInputEvent->GetKeyCode())
				{

				case 'W': case VK_UP: { m_Actions = m_Actions | Actions::Up; } break;
				case 'A': case VK_LEFT: { m_Actions = m_Actions | Actions::Left; } break;
				case 'S': case VK_DOWN:  { m_Actions = m_Actions | Actions::Down; }	break;
				case 'D': case VK_RIGHT: { m_Actions = m_Actions | Actions::Right; } break;
				case 'Z': { m_Actions = m_Actions | Actions::Teleport; } break;
				case 'R': { m_Actions = m_Actions | Actions::Reset; } break;


				}
			}

			if (pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released)
			{
				switch (pInputEvent->GetKeyCode())
				{

				case 'W': case VK_UP: { m_Actions = m_Actions & ~Actions::Up; } break;
				case 'A': case VK_LEFT: { m_Actions = m_Actions & ~Actions::Left; } break;
				case 'S': case VK_DOWN: { m_Actions = m_Actions & ~Actions::Down; }	break;
				case 'D': case VK_RIGHT: { m_Actions = m_Actions & ~Actions::Right; } break;
				case 'Z': { m_Actions = m_Actions & ~Actions::Teleport; } break;
				case 'R': { m_Actions = m_Actions & ~Actions::Reset; } break;

				}
			}
		}
	}
}

void VirtualController::StartFrame()
{
	m_OldActions = m_Actions;
}

bool VirtualController::isActionHeld(Actions action)
{
	return (m_Actions & action);
}

bool VirtualController::WasActionPressed(Actions action)
{
	return (~m_OldActions & action && m_Actions & action);
}

bool VirtualController::WasActionReleased(Actions action)
{
	return (m_OldActions & action && ~m_Actions & action);
}

