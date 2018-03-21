#pragma once

// フレームワーク
#include <framework\entity.h>

namespace Scene
{
	class Title : public Entity
	{
	public:
		Title(Entity * parent) : Entity(parent)
		{

		}
	};
}