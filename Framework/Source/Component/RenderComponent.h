#pragma once

#include "CoreHeaders.h"

#include "Component/Component.h"


namespace fw
{
	class Mesh;
	class Material;

	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* pGameObject, Mesh* pMesh, Material* pMaterial);
		virtual ~RenderComponent();

		static const char* GetStaticType() { return "RenderComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }

		void Render();
		
	public:
		Mesh* m_pMesh = nullptr;
		Material* m_pMaterial = nullptr;

	};
}