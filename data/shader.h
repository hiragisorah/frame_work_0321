#pragma once

// システム
#include <system\direct3d11.h>

// Utils
#include <utils\process.h>

// データ
#include <data\texture.h>

// ローダー
#include <system\loader\texture.h>

// SDK
#include <D3DX10.h>
#include <D3DX11.h>

namespace Data
{
	class Shader
	{
	private:
		ID3D11VertexShader * vs_ = nullptr;
		ID3D11GeometryShader * gs_ = nullptr;
		ID3D11PixelShader * ps_ = nullptr;
		ID3D11InputLayout * layout_ = nullptr;
		ID3D11Buffer * cbuffers_[10] = {};
		ID3D11SamplerState * samplers_[10] = {};
		ID3D11ShaderResourceView * resources_[10] = {};

	public:
		Shader(std::string hlsl, D3D11_INPUT_ELEMENT_DESC * desc, int desc_num)
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			ID3DBlob * compiled_shader = nullptr;
			ID3DBlob * errors = nullptr;

			{// バーテックシェーダー作成
				if (FAILED(D3DX11CompileFromFileA(hlsl.c_str(), nullptr, nullptr, "VS", "vs_5_0",
					D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, &compiled_shader, &errors, nullptr)))
				{
					errors ? Utils::EndMsg((char*)errors->GetBufferPointer()) : Utils::EndMsg("VSシェーダファイルが見つかりませんでした");
					return;
				}
				else
				{
					if (FAILED(d3d->device_->CreateVertexShader(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), nullptr, &this->vs_)))
						Utils::EndMsg("VSの生成に失敗しました");
				}
				Utils::Memory::SafeRelease(errors);
			}

			{// インプットレイアウト作成
				if (FAILED(d3d->device_->CreateInputLayout(desc, desc_num, compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), &this->layout_)))
					Utils::EndMsg("インプットレイアウトの生成に失敗しました。");

				Utils::Memory::SafeRelease(compiled_shader);
			}

			{// ジオメトリシェーダー作成
				if (SUCCEEDED(D3DX11CompileFromFileA(hlsl.c_str(), nullptr, nullptr, "GS", "gs_5_0",
					D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, &compiled_shader, &errors, nullptr)))
					if (FAILED(d3d->device_->CreateGeometryShader(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), nullptr, &this->gs_)))
						Utils::EndMsg("GSの生成に失敗しました。");

				Utils::Memory::SafeRelease(errors);
			}

			{// ピクセルシェーダー作成
				if (FAILED(D3DX11CompileFromFileA(hlsl.c_str(), nullptr, nullptr, "PS", "ps_5_0",
					D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, &compiled_shader, &errors, nullptr)))
					errors ? Utils::EndMsg((char*)errors->GetBufferPointer()) : Utils::EndMsg("PSシェーダファイルが見つかりませんでした");
				else
					if (FAILED(d3d->device_->CreatePixelShader(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), nullptr, &this->ps_)))
						Utils::EndMsg("PSの生成に失敗しました。");

				Utils::Memory::SafeRelease(errors);
			}
		}

	public:
		virtual ~Shader(void)
		{
			if(this->vs_ != nullptr)
				this->vs_->Release();

			if (this->gs_ != nullptr)
				this->gs_->Release();

			if (this->ps_ != nullptr)
				this->ps_->Release();

			this->layout_->Release();

			for (auto cb : this->cbuffers_)
				if (cb != nullptr)
					cb->Release();
		}

	protected:
		template<class _CBUFFER>
		void CreateConstantBuffer(int num)
		{
			{// コンスタントバッファー作成
				D3D11_BUFFER_DESC cb;
				cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				cb.ByteWidth = sizeof(_CBUFFER);
				cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				cb.MiscFlags = 0;
				cb.StructureByteStride = 0;
				cb.Usage = D3D11_USAGE_DYNAMIC;

				d3d->device_->CreateBuffer(&cb, nullptr, &this->cbuffers_[num]);
			}
		}

	public:
		void SetSampler(int num, ID3D11SamplerState * sampler)
		{
			this->samplers_[num] = sampler;
		}

		void SetTeture(int num, std::string file_name)
		{
			this->resources_[num] = Game::GetSystem<System::Loader::Texture>()->Get(file_name)->resource_;
		}

	public:
		template<class _CBUFFER>
		void UpdateConstantBuffer(int num, _CBUFFER * cb)
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();
			
			D3D11_MAPPED_SUBRESOURCE data;
			if (SUCCEEDED(d3d->context_->Map(this->cbuffer_[num], 0, D3D11_MAP_WRITE_DISCARD, 0, &data)))
			{
				memcpy_s(data.pData, data.RowPitch, cb, sizeof(_CBUFFER));
				d3d->context_->Unmap(this->cbuffers_[num], 0);
			}
		}

	public:
		void Setup(void)
		{
			auto d3d = Game::GetSystem<System::Direct3D11>();

			d3d->context_->VSSetShader(this->vs_, nullptr, 0);
			d3d->context_->GSSetShader(this->gs_, nullptr, 0);
			d3d->context_->PSSetShader(this->ps_, nullptr, 0);

			d3d->context_->VSSetConstantBuffers(0, 10, this->cbuffers_);
			d3d->context_->GSSetConstantBuffers(0, 10, this->cbuffers_);
			d3d->context_->PSSetConstantBuffers(0, 10, this->cbuffers_);

			d3d->context_->PSSetSamplers(0, 10, this->samplers_);
			d3d->context_->PSSetShaderResources(0, 10, this->resources_);
		}
	};
}