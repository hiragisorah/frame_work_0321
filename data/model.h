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

	protected:
		ID3D11Buffer * vertex_buffer_ = nullptr;
		unsigned int vtx_num_ = 0;
		unsigned int stride_ = 0;
		unsigned int offset_ = 0;
		ID3D11Buffer * index_buffer_ = nullptr;
		unsigned int index_num_ = 0;
	};
}