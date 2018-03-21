#pragma once

namespace Data
{
	class IModel
	{
	public:
		virtual ~IModel(void) {}

	public:
		virtual void Rendering(void) = 0;
	};
}