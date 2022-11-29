/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvCore/Scripting/LuaActorBinder.h"

#include "OvCore/ECS/Actor.h"

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
#include "../Components/CParticles.h"

void OvCore::Scripting::LuaActorBinder::BindActor(sol::state & p_luaState)
{
	using namespace OvCore::ECS;
	using namespace OvCore::ECS::Components;


	//mira copias ctrl + F y ya con eso dale yo me voy loko cuidate dale bro
	//que te parecen los nombres vro
	p_luaState.new_usertype<Actor>("Actor",
		/* Methods */
		"ObtenerNombre", &Actor::GetName,
		"EstablecerNombre", &Actor::SetName,
		"ObtenerTag", &Actor::GetTag,
		"ObtenerHijo", &Actor::GetChildren,
		"EstablecerTag", &Actor::SetTag,
		"ObtenerID", &Actor::GetID,
		"ObtenerPadre", &Actor::GetParent,
		"EstablecerPadre", &Actor::SetParent,
		"SepararPadre", &Actor::DetachFromParent,
		"Destruir", &Actor::MarkAsDestroy,
		"ObjetoActivo", &Actor::IsSelfActive, // TODO: Add to doc
		"EsActivo", &Actor::IsActive,
		"EstablecerActivo", &Actor::SetActive,


		/* Components Getters */
		"ObtenerTransformador", &Actor::GetComponent<CTransform>,
		"ObtenerObjetoFisico", &Actor::GetComponent<CPhysicalObject>,
		"ObtenerCajaFisica", &Actor::GetComponent<CPhysicalBox>,
		"ObtenerEsferaFisica", &Actor::GetComponent<CPhysicalSphere>,
		"ObtenerCapsulaFisica", &Actor::GetComponent<CPhysicalCapsule>,
		"ObtenerCamara", &Actor::GetComponent<CCamera>,
		"ObtenerLuz", &Actor::GetComponent<CLight>,
		"ObtenerPuntoDeLuz", &Actor::GetComponent<CPointLight>,
		"ObtenerLugarDeLuz", &Actor::GetComponent<CSpotLight>,
		"ObtenerLuzDireccional", &Actor::GetComponent<CDirectionalLight>,
		"ObtenerCajaAmbientalDeLuz", &Actor::GetComponent<CAmbientBoxLight>,
		"ObtenerEsferaAmbientalDeLuz", &Actor::GetComponent<CAmbientSphereLight>,
		"ObtenerRenderDeModelo", &Actor::GetComponent<CModelRenderer>,
		"ObtenerRenderDeMaterial", &Actor::GetComponent<CMaterialRenderer>,
		"ObtenerRecursoDeAudio", &Actor::GetComponent<CAudioSource>,
		"ObtenerAudioOyente", &Actor::GetComponent<CAudioListener>,
		"ObtenerParticulas", & Actor::GetComponent<CParticles>,

		/* Behaviours relatives */
		"GetBehaviour", [](Actor& p_this, const std::string& p_name) -> sol::table
		{
			auto behaviour = p_this.GetBehaviour(p_name);
			if (behaviour)
				return behaviour->GetTable();
			else
				return sol::nil;
		},

		/* Components Creators */
		"AgregarTransform", &Actor::AddComponent<CTransform>,
		"AgregarModeloDeRender", &Actor::AddComponent<CModelRenderer>,
		"AgregarCajaFisica", &Actor::AddComponent<CPhysicalBox>,
		"AgregarEsferaFisica", &Actor::AddComponent<CPhysicalSphere>,
		"AgregarCapsulaFisica", &Actor::AddComponent<CPhysicalCapsule>,
		"AgregarCamara", &Actor::AddComponent<CCamera>,
		"AgregarPuntoDeLuz", &Actor::AddComponent<CPointLight>,
		"AgregarLugarDeLuz", &Actor::AddComponent<CSpotLight>,
		"AgregarLuzDireccional", &Actor::AddComponent<CDirectionalLight>,
		"AgregarCajaAmbientalDeLuz", &Actor::AddComponent<CAmbientBoxLight>,
		"AgregarEsferaAmbientalDeLuz", &Actor::AddComponent<CAmbientSphereLight>,
		"AgregarRenderDeMaterial", &Actor::AddComponent<CMaterialRenderer>,
		"AgregarRecursoDeAudio", &Actor::AddComponent<CAudioSource>,
		"AgregarAudioOyente", &Actor::AddComponent<CAudioListener>,
		"AgregarParticulas", & Actor::AddComponent<CParticles>,

		/* Components Destructors */
		"RemoverRenderDeModelo", &Actor::RemoveComponent<CModelRenderer>,
		"RemoverCajaFisica", &Actor::RemoveComponent<CPhysicalBox>,
		"RemoverEsferaFisica", &Actor::RemoveComponent<CPhysicalSphere>,
		"RemoverCapsulaFisica", &Actor::RemoveComponent<CPhysicalCapsule>,
		"RemoverCamara", &Actor::RemoveComponent<CCamera>,
		"RemoverPuntoDeLuz", &Actor::RemoveComponent<CPointLight>,
		"RemoverLugarDeLuz", &Actor::RemoveComponent<CSpotLight>,
		"RemoverLuzDireccional", &Actor::RemoveComponent<CDirectionalLight>,
		"RemoverCajaAmbientalDeLuz", &Actor::RemoveComponent<CAmbientBoxLight>,
		"RemoverEsferaAmbientalDeLuz", &Actor::RemoveComponent<CAmbientSphereLight>,
		"RemoverRenderDeMaterial", &Actor::RemoveComponent<CMaterialRenderer>,
		"RemoverRecursoDeAudio", &Actor::RemoveComponent<CAudioSource>,
		"RemoverAudioOyente", &Actor::RemoveComponent<CAudioListener>,
		"RemoverParticulas", & Actor::RemoveComponent<CParticles>,

		/* Behaviour management */
		"AgregarBehaviour", &Actor::AddBehaviour,
		"RemoverBehaviour", sol::overload
		(
			sol::resolve<bool(Behaviour&)>(&Actor::RemoveBehaviour),
			sol::resolve<bool(const std::string&)>(&Actor::RemoveBehaviour)
		)
	);
}
