#pragma once

// システム
#include <system\direct3d11.h>

// SDK
#include <D3DX11.h>

namespace Data
{
	class IMesh
	{
	public:
		ID3D11Buffer * vertex_buffer_ = nullptr;
		unsigned int vtx_num_ = 0;
		unsigned int stride_ = 0;
		unsigned int offset_ = 0;
		ID3D11Buffer * index_buffer_ = nullptr;
		unsigned int index_num_ = 0;
		D3D11_PRIMITIVE_TOPOLOGY topology_ = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;

	public:
		template<class _Type>
		void CreateVertexBuffer(std::vector<_Type> * vertices, D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			this->topology_ = topology;

			auto d3d = Game::GetSystem<System::Direct3D11>();

			this->vtx_num_ = vertices->size();
			this->stride_ = sizeof(_Type);
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = this->stride_ * this->vtx_num_;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA init_data;
			init_data.pSysMem = vertices->data();

			if (FAILED(d3d->device_->CreateBuffer(&bd, &init_data, &this->vertex_buffer_)))
				Utils::EndMsg("頂点バッファーの生成に失敗しました。");
		}

	public:
		template<class _Type>
		void CreateIndexBuffer(std::vector<_Type> * indices)
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			this->index_num_ = indices->size();

			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(_Type) * this->index_num_;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA init_data;
			init_data.pSysMem = indices->data();

			if (FAILED(d3d->device_->CreateBuffer(&bd, &init_data, &this->index_buffer_)))
				Utils::EndMsg("インデックスバッファーの生成に失敗しました。");
		}
	};
}