#include "Context/Components/TransformComponent.h"

#include "Context/GameFramework/Actor.h"

namespace Nocturn
{
	void NTransformComponent::Initialize()
	{
		NActorComponent::Initialize();
	}

	void NTransformComponent::OnComponenentActivated(NActor* OwnedActor)
	{
		NActorComponent::OnComponenentActivated(OwnedActor);
	}

	void NTransformComponent::OnComponenentDeactivated()
	{
		NActorComponent::OnComponenentDeactivated();
	}

	void NTransformComponent::Update(const double DeltaTime)
	{
		NActorComponent::Update(DeltaTime);

		Transform->Direction.x = cos( glm::radians( Transform->Rotation.x ) ) * cos( glm::radians( Transform->Rotation.y ) );
		Transform->Direction.y = sin( glm::radians( Transform->Rotation.y ) );
		Transform->Direction.z = sin( glm::radians( Transform->Rotation.x ) ) * cos( glm::radians( Transform->Rotation.y ) );

		Transform->Forward	= glm::normalize( Transform->Direction );
		Transform->Right	= glm::normalize( glm::cross( Transform->Forward, glm::vec3( 0, 1, 0 ) ) );
		Transform->Up		= glm::normalize( glm::cross( Transform->Right, Transform->Forward ) );
	}

	void NTransformComponent::SetLocation(const vec3& NewLocation) noexcept
	{
		Position = NewLocation;
	}

	void NTransformComponent::SetScale(const vec3& NewScale) noexcept
	{
		Scale = NewScale;
	}

	void NTransformComponent::SetRotation(const vec3& NewRotation) noexcept
	{
		Rotation = NewRotation;
	}

	void NTransformComponent::SetTransform(const FTransform& NewTransform) noexcept
	{
		Transform = NewTransform;
	}

	vec3& NTransformComponent::GetLocation() noexcept
	{
		return Position;
	}

	vec3& NTransformComponent::GetScale() noexcept
	{
		return Scale;
	}

	vec3& NTransformComponent::GetRotation() noexcept
	{
		return Rotation;
	}

	FTransform& NTransformComponent::GetTransform() noexcept
	{
		return &Transform;
	}
}
