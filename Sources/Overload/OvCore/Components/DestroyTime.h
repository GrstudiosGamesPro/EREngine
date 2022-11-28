#pragma once
#include <OvUI/Widgets/Texts/Text.h>
#include <OvUI/Widgets/Drags/DragMultipleFloats.h>
#include "../../OvCore/include/OvCore/ECS/Components/AComponent.h"
#include <OvUI/Widgets/Texts/Text.h>
#include <OvUI/Widgets/Drags/DragFloat.h>
#include <OvUI/Widgets/Selection/ColorEdit.h>
#include <OvUI/Widgets/Buttons/Button.h>
#include <OvUI/Widgets/Layout/Group.h>
#include "OvCore/ECS/Actor.h"
#include "OvCore/Global/ServiceLocator.h"
#include "OvCore/SceneSystem/SceneManager.h"
#include "OvCore/SceneSystem/Scene.h"

#include <OvUI/Widgets/Plots/PlotLines.h>
#include <OvUI/Widgets/Drags/DragFloat.h>
#include "OvCore/ECS/Actor.h"
#include <OvCore/Global/ServiceLocator.h>
#include <OvTools/Filesystem/IniFile.h>
#include <OvTools/Utils/PathParser.h>


#include "OvCore/ECS/Components/CTransform.h"
#include "OvCore/ECS/Components/CCamera.h"
#include "OvCore/ECS/Components/CPhysicalBox.h"
#include "OvCore/ECS/Components/CPhysicalSphere.h"
#include "OvCore/ECS/Components/CPhysicalCapsule.h"
#include "OvCore/ECS/Components/CDirectionalLight.h"
#include "OvCore/ECS/Components/CPointLight.h"
#include "OvCore/ECS/Components/CSpotLight.h"
#include "OvCore/ECS/Components/CAmbientBoxLight.h"
#include "OvCore/ECS/Components/CAmbientSphereLight.h"
#include "OvCore/ECS/Components/CModelRenderer.h"
#include "OvCore/ECS/Components/CMaterialRenderer.h"
#include "OvCore/ECS/Components/CAudioSource.h"
#include "OvCore/ECS/Components/CAudioListener.h"


#include <filesystem>
#include <iostream>
#include <fstream>

#include <OvDebug/Logger.h>

#include <OvCore/ECS/Components/CPhysicalBox.h>
#include <OvCore/ECS/Components/CPhysicalSphere.h>
#include <OvCore/ECS/Components/CPhysicalCapsule.h>
#include <OvCore/ECS/Components/CModelRenderer.h>
#include <OvCore/ECS/Components/CMaterialRenderer.h>
#include <OvCore/ECS/Components/CAudioSource.h>

#include <OvWindowing/Dialogs/OpenFileDialog.h>
#include <OvWindowing/Dialogs/SaveFileDialog.h>
#include <OvWindowing/Dialogs/MessageBox.h>

#include <OvTools/Utils/PathParser.h>
#include <OvTools/Utils/String.h>
#include <OvTools/Utils/SystemCalls.h>
#include <OvDebug/Logger.h>


using namespace std;
using namespace OvCore::Helpers;
using namespace OvCore::ECS::Components;
using namespace OvMaths;
using namespace OvUI::Internal;
using namespace OvCore::ECS;
using namespace OvCore::Global;
using namespace OvCore::SceneSystem;
using namespace OvRendering::Resources;


namespace OvCore::ECS { class Actor; }

namespace OvCore::ECS::Components
{
	class DestroyTime : public AComponent
	{
	public:
		DestroyTime(ECS::Actor& p_owner);
		std::string GetName() override;
		float Time;

	private:
		virtual void OnEnable() override;
		virtual void OnDisable() override;

	public:
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
		virtual void OnInspector(OvUI::Internal::WidgetContainer& p_root) override;
		virtual void OnFixedUpdate(float p_deltaTime) override;
		void SetTime (float time);
	};
}