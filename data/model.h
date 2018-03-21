#pragma once

// SDK
#include <D3DX11.h>

namespace System { class Direct3D11; }

namespace Data
{
	class IModel
	{
		friend System::Direct3D11;

	public:
		virtual ~IModel(void) {}

	private:
		virtual void Rendering(void) = 0;
	};
}