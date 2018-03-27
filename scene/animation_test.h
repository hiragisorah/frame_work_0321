#pragma once

// フレームワーク
#include <framework\entity.h>

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// ゲームオブジェクト
#include <game_object\primitive3d.h>
#include <game_object\bone.h>

// コンポーネント
#include <component\test_animation.h>

namespace Scene
{
	class AnimationTest : public Entity
	{
	public:
		AnimationTest(Entity * parent) : Entity(parent)
		{
			Game::GetSystem<System::Loader::Shader>()->Load<Data::Shader::Specular>();
			Game::GetSystem<System::Loader::Mesh>()->Load<Data::Mesh::Cube>();
			auto a = this->AddChild<GameObject::Primitive3D>();
			a->AddComponent<Component::TestAnimation>();
		}
	};
}