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

#include <OvWindowing/Dialogs/OpenFileDialog.h>
#include <OvWindowing/Dialogs/SaveFileDialog.h>
#include <OvWindowing/Dialogs/MessageBox.h>

#include <OvTools/Utils/PathParser.h>
#include <OvTools/Utils/String.h>
#include <OvTools/Utils/SystemCalls.h>

namespace OvCore::ECS { class Actor; }

namespace OvCore::ECS::Components
{
	class CParticles : public AComponent
	{
	public:
		CParticles(ECS::Actor& p_owner);
		std::string GetName() override;

	public:
		float ParticlesSpeed = 1;
		float DestroyTime = 3;
		float InstanceTime = 1;
		float OpenAngle = 15;

		OvMaths::FVector3 Direction = OvMaths::FVector3(0, 0, 0);

	private:
		virtual void OnEnable() override;
		virtual void OnDisable() override;


	public:
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
		virtual void OnInspector(OvUI::Internal::WidgetContainer& p_root) override;
		virtual void OnFixedUpdate(float p_deltaTime) override;

		//FUNCTIONS VOID
		void Update();
		void SetParticlesSpeed (float NewSpeed);
		void SetDestroyTime(float DestroyTime);
		void SetDirection(OvMaths::FVector3 Dir);
		void SetInstanceTime(float p_Time);
		void SetOpenAngle(float p_Angle);
		float RandomFloatGenerate (float p_RangeMin, float p_RangeMax);
	};
}