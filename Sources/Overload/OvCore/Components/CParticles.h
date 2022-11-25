#pragma once

#include "OvCore/ECS/Components/AComponent.h"

#include <OvMaths/FTransform.h>
#include <OvMaths/FVector3.h>
#include <OvMaths/FQuaternion.h>

#include "../../OvCore/include/OvCore/ECS/Components/AComponent.h"
#include <OvUI/Widgets/Texts/Text.h>
#include <OvUI/Widgets/Drags/DragFloat.h>
#include <OvUI/Widgets/Selection/ColorEdit.h>
#include <OvUI/Widgets/Buttons/Button.h>
#include <OvUI/Widgets/Layout/Group.h>

#include "OvCore/ECS/Actor.h"

#include "OvCore/ECS/Components/CPointLight.h"

namespace OvCore::ECS { class Actor; }

namespace OvCore::ECS::Components
{
	class CParticles : public AComponent
	{
	public:
		CParticles(ECS::Actor& p_owner);
		std::string GetName() override;

	public:
		float ParticlesSpeed;
		float DestroyTime;
		float InstanceTime;
		OvMaths::FVector3 Direction = OvMaths::FVector3(0, 0, 0);

	private:
		virtual void OnEnable() override;
		virtual void OnDisable() override;


	public:
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
		virtual void OnInspector(OvUI::Internal::WidgetContainer& p_root) override;

		//FUNCTIONS VOID
		void Update();
		void SetParticlesSpeed (float NewSpeed);
		void SetDestroyTime(float DestroyTime);
		void SetDirection(OvMaths::FVector3 Dir);
		void SetInstanceTime(float p_Time);
	};
}