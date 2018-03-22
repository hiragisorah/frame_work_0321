#pragma once

// フレームワーク
#include <framework\entity.h>

// システム
#include <system\direct3d11.h>
#include <system\camera.h>

// ゲームオブジェクト
#include <game_object\sprite.h>

namespace Scene
{
	class Title : public Entity
	{
	public:
		Title(Entity * parent) : Entity(parent)
		{
			this->AddChild<GameObject::Sprite>();
		}
	};
}