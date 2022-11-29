/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvCore/Scripting/LuaComponentBinder.h"

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

void OvCore::Scripting::LuaComponentBinder::BindComponent(sol::state & p_luaState)
{
	using namespace OvMaths;
	using namespace OvCore::ECS;
	using namespace OvCore::ECS::Components;

	p_luaState.new_usertype<AComponent>("Componente",
		"ObtenerLIDER", [](AComponent& p_component) -> Actor& { return p_component.owner; }
	);

	p_luaState.new_usertype<CTransform>("Transformador",
		sol::base_classes, sol::bases<AComponent>(),
		/* Methods */
		"SeleccionarPosicion", &CTransform::SetLocalPosition,
		"SeleccionarRotacion", &CTransform::SetLocalRotation,
		"SeleccionarEscala", &CTransform::SetLocalScale,
		"SeleccionarPosicionLocal", &CTransform::SetLocalPosition,
		"SeleccionarRotacionLocal", &CTransform::SetLocalRotation,
		"SeleccionarEscalaLocal", &CTransform::SetLocalScale,
		"SeleccionarPosicionDeMundo", &CTransform::SetWorldPosition,
		"SeleccionarRotacionDeMundo", &CTransform::SetWorldRotation,
		"SeleccionarEscalaDeMundo", &CTransform::SetWorldScale,
		"ObtenerPosicion", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldPosition(); },
		"ObtenerRotacion", [](CTransform& p_this) -> FQuaternion { return p_this.GetWorldRotation(); },
		"ObtenerEscala", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldScale(); },
		"ObtenerPosicionLocal", [](CTransform& p_this) -> FVector3 { return p_this.GetLocalPosition(); },
		"ObtenerRotacionLocal", [](CTransform& p_this) -> FQuaternion { return p_this.GetLocalRotation(); },
		"ObtenerEscalaLocal", [](CTransform& p_this) -> FVector3 { return p_this.GetLocalScale(); },
		"ObtenerPosicionDeMundo", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldPosition(); },
		"ObtenerRotacionDeMundo", [](CTransform& p_this) -> FQuaternion { return p_this.GetWorldRotation(); },
		"ObtenerEscalaDeMundo", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldScale(); },
		"ObtenerAvance", &CTransform::GetWorldForward,
		"ObtenerLevanto", &CTransform::GetWorldUp,
		"ObtenerDerecha", &CTransform::GetWorldRight,
		"ObtenerAvanceLocal", &CTransform::GetLocalForward,
		"ObtenerLevantoLocal", &CTransform::GetLocalUp,
		"ObtenerDerechaLocal", &CTransform::GetLocalRight,
		"MundoAvanza", &CTransform::GetWorldForward,
		"SubeMundo", &CTransform::GetWorldUp,
		"MundoAlaDerecha", &CTransform::GetWorldRight
		);

    
    p_luaState.new_enum<OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour>("FrustumBehaviour",
        {
            {"DISABLED",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::DISABLED},
            {"CULL_MODEL",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_MODEL},
            {"CULL_MESHES",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_MESHES},
            {"CULL_CUSTOM",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_CUSTOM}
        });

	p_luaState.new_usertype<CModelRenderer>("ModeloDeRender",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerModelo", &CModelRenderer::GetModel,
		"SeleccionarModelo", &CModelRenderer::SetModel,
		"ObtenerComportamientoDeFrustum", &CModelRenderer::GetFrustumBehaviour,
		"SeleccionarComportamientoDeFrustum", &CModelRenderer::SetFrustumBehaviour
	);

	p_luaState.new_usertype<CMaterialRenderer>("MaterialDeRender",
		sol::base_classes, sol::bases<AComponent>(),
		"SeleccionarMaterial", &CMaterialRenderer::SetMaterialAtIndex,
		"SeleccionarMatrizDeElementosDeUsuario", &CMaterialRenderer::SetUserMatrixElement,
		"ObtenerMatrizDeElementosDeUsurario", &CMaterialRenderer::GetUserMatrixElement
	);

	p_luaState.new_enum<OvPhysics::Entities::PhysicalObject::ECollisionDetectionMode>("ModoDetectorDeColisiones",
		{
			{"DISCRETO",		OvPhysics::Entities::PhysicalObject::ECollisionDetectionMode::DISCRETE},
			{"CONTINUO",		OvPhysics::Entities::PhysicalObject::ECollisionDetectionMode::CONTINUOUS}
		});

	p_luaState.new_usertype<CPhysicalObject>("FisicasObjetos",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerMasa", &CPhysicalObject::GetMass,
		"SeleccionarMasa", &CPhysicalObject::SetMass,
		"ObtenerFriccion", &CPhysicalObject::GetFriction,
		"SeleccionarFriccion", &CPhysicalObject::SetFriction,
		"ObtenerRebote", &CPhysicalObject::GetBounciness,
		"SeleccionarRebote", &CPhysicalObject::SetBounciness,
		"SeleccionarVelocidadLineal", &CPhysicalObject::SetLinearVelocity,
		"SeleccionarVelocidadAngular", &CPhysicalObject::SetAngularVelocity,
		"ObtenerVelocidadLineal", &CPhysicalObject::GetLinearVelocity,
		"ObtenerVelocidadAngular", &CPhysicalObject::GetAngularVelocity,
		"SeleccionarFactorLineal", &CPhysicalObject::SetLinearFactor,
		"SeleccionarFactorAngular", &CPhysicalObject::SetAngularFactor,
		"ObtenerFactorLineal", &CPhysicalObject::GetLinearFactor,
		"ObtenerFactorAngular", &CPhysicalObject::GetAngularFactor,
		"EsColisionador", &CPhysicalObject::IsTrigger,
		"SeleccionarColisionador", &CPhysicalObject::SetTrigger,
		"AgregarFuerza", &CPhysicalObject::AddForce,
		"AgregarImpulso", &CPhysicalObject::AddImpulse,
		"EliminarFuerzas", &CPhysicalObject::ClearForces,
		"SeleccionarDectorDeColisiones", &CPhysicalObject::SetCollisionDetectionMode,
		"ObtenerModoDeColision", &CPhysicalObject::GetCollisionDetectionMode,
		"SeleccionarKinematic", &CPhysicalObject::SetKinematic
		);

	p_luaState.new_usertype<CPhysicalBox>("PhysicalBox",
		sol::base_classes, sol::bases<CPhysicalObject>(),
		"ObtenerSize", &CPhysicalBox::GetSize,
		"SeleccionarSize", &CPhysicalBox::SetSize
		);

	p_luaState.new_usertype<CPhysicalSphere>("PhysicalSphere",
		sol::base_classes, sol::bases<CPhysicalObject>(),
		"ObtenerRadio", &CPhysicalSphere::GetRadius,
		"SeleccionarRadio", &CPhysicalSphere::SetRadius
		);

	p_luaState.new_usertype<CPhysicalCapsule>("PhysicalCapsule",
		sol::base_classes, sol::bases<CPhysicalObject>(),
		"ObtenerRadio", &CPhysicalCapsule::GetRadius,
		"SeleccionarRadio", &CPhysicalCapsule::SetRadius,
		"ObtenerAlto", &CPhysicalCapsule::GetHeight,
		"SeleccionarAlto", &CPhysicalCapsule::SetHeight
		);

    p_luaState.new_enum<OvRendering::Settings::EProjectionMode>("ProjectionMode",
    {
        {"ORTHOGRAPHIC",	OvRendering::Settings::EProjectionMode::ORTHOGRAPHIC},
        {"PERSPECTIVE",		OvRendering::Settings::EProjectionMode::PERSPECTIVE}
    });

	p_luaState.new_usertype<CCamera>("Camera",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerFov", &CCamera::GetFov,
		"ObtenerSize", &CCamera::GetSize,
		"ObtenerCerca", &CCamera::GetNear,
		"ObtenerLejos", &CCamera::GetFar,
		"ObtenerColorDespejado", &CCamera::GetClearColor,
		"SeleccionarFov", &CCamera::SetFov,
		"SeleccionarSize", &CCamera::SetSize,
		"SeleccionarCerca", &CCamera::SetNear,
		"SeleccionarLejos", &CCamera::SetFar,
		"SeleccionarColorDespejado", &CCamera::SetClearColor,
        "HasFrustumGeometryCulling", &CCamera::HasFrustumGeometryCulling,
        "HasFrustumLightCulling", &CCamera::HasFrustumLightCulling,
        "ObtenerModoProyeccion", &CCamera::GetProjectionMode,
        "SetFrustumGeometryCulling", &CCamera::SetFrustumGeometryCulling,
        "SetFrustumLightCulling", &CCamera::SetFrustumLightCulling,
        "SeleccionarModoProyeccion", &CCamera::SetProjectionMode
		);

	p_luaState.new_usertype<CLight>("Luz",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerColor", &CPointLight::GetColor,
		"ObtenerIntensidad", &CPointLight::GetIntensity,
		"SeleccionarColor", &CPointLight::SetColor,
		"SeleccionarIntensidad", &CPointLight::SetIntensity
		);

	p_luaState.new_usertype<CPointLight>("PuntoDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerConstante", &CPointLight::GetConstant,
		"ObtenerLineal", &CPointLight::GetLinear,
		"ObtenerCuadratica", &CPointLight::GetQuadratic,
		"SeleccionarConstante", &CPointLight::SetConstant,
		"SeleccionarLineal", &CPointLight::SetLinear,
		"SeleccionarCuadratica", &CPointLight::SetQuadratic
		);

	p_luaState.new_usertype<CSpotLight>("LugarDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerConstante", &CSpotLight::GetConstant,
		"ObtenerLineal", &CSpotLight::GetLinear,
		"ObtenerCuadratica", &CSpotLight::GetQuadratic,
		"ObtenerCorte", &CSpotLight::GetCutoff,
		"ObtenerCorteExterno", &CSpotLight::GetOuterCutoff,
		"SeleccionarConstante", &CSpotLight::SetConstant,
		"SeleccionarLineal", &CSpotLight::SetLinear,
		"SeleccionarCuadratica", &CSpotLight::SetQuadratic,
		"SeleccionarCorte", &CSpotLight::SetCutoff,
		"SeleccionarCorteExterno", &CSpotLight::SetOuterCutoff
		);

	p_luaState.new_usertype<CAmbientBoxLight>("CajaAmbientalDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerSize", &CAmbientBoxLight::GetSize,
		"SeleccionarSize", &CAmbientBoxLight::SetSize
		);

	p_luaState.new_usertype<CAmbientSphereLight>("EsferaAmbientalDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerRadio", &CAmbientSphereLight::GetRadius,
		"SeleccionarRadio", &CAmbientSphereLight::SetRadius
		);

	p_luaState.new_usertype<CDirectionalLight>("LuzDireccional",
		sol::base_classes, sol::bases<CLight>()
		);

	p_luaState.new_usertype<CAudioSource>("RecursoDeAudio",
		sol::base_classes, sol::bases<AComponent>(),
		"Empezar", &CAudioSource::Play,
		"Detener", &CAudioSource::Stop,
		"Pausa", &CAudioSource::Pause,
		"Reanudar", &CAudioSource::Resume,
		"ObtenerSonido", &CAudioSource::GetSound,
		"ObtenerVolumen", &CAudioSource::GetVolume,
		"ObtenerPan", &CAudioSource::GetPan,
		"EsLooped", &CAudioSource::IsLooped,
		"ObtenerPitch", &CAudioSource::GetPitch,
		"EstaTerminado", &CAudioSource::IsFinished,
		"EsEspacial", &CAudioSource::IsSpatial,
		"ObtenerUmbralDeAtenuacion", &CAudioSource::GetAttenuationThreshold,
		"SeleccionarSonido", &CAudioSource::SetSound,
		"SeleccionarVolumen", &CAudioSource::SetVolume,
		"SeleccionarPan", &CAudioSource::SetPan,
		"SeleccionarLooped", &CAudioSource::SetLooped,
		"SeleccionarPitch", &CAudioSource::SetPitch,
		"SeleccionarEspacial", &CAudioSource::SetSpatial,
		"SeleccionarUmbralDeAtenuacion", &CAudioSource::SetAttenuationThreshold
		);

	p_luaState.new_usertype<CAudioListener>("AudioListener",
		sol::base_classes, sol::bases<AComponent>()
		);
}
