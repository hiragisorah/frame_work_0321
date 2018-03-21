#pragma once

// フレームワーク
#include <framework\entity.h>

// システム
#include <system\direct3d11.h>

// ゲームオブジェクト
#include <game_object\point3d.h>
#include <game_object\point2d.h>
#include <game_object\line2d.h>
#include <game_object\line3d.h>
#include <game_object\triangle2d.h>
#include <game_object\triangle3d.h>
#include <game_object\square2d.h>
#include <game_object\square3d.h>

namespace Scene
{
	class Title : public Entity
	{
	public:
		Title(Entity * parent) : Entity(parent)
		{
			this->AddChild<GameObject::Point3d>();
		}
	};
}