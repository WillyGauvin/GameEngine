#pragma once

#include "CoreHeaders.h"
#include "Objects/GameObject.h"

namespace fw
{

	using ComponentType = const char*;

	class Component
	{
	public:
		Component(GameObject* pGameObject) { m_pGameObject = pGameObject; }
		virtual ~Component() = 0 {};

		virtual ComponentType GetType() = 0;

		GameObject* m_pGameObject;
	};
}