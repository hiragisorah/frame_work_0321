#pragma once

// �V�X�e��
#include <system\direct3d11.h>

// �f�[�^
#include <data\model.h>

// �V�F�[�_
#include <data\shader\triangle2d.h>

// ���[�_�[
#include <system\loader\shader.h>

namespace Data
{
	namespace Model
	{
		class Triangle2d : public IModel
		{
		public:
			Shader::Triangle2d * shader_;
			Shader::Triangle2d::CBUFFER cb_;

		public:
			Triangle2d(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Triangle2d>();
			}

		private:
			void Rendering(void) override
			{
				auto d2d = Game::GetSystem<System::Direct3D11>();
				auto window = Game::GetSystem<System::Window>();

				this->cb_.viewport_ = { window->Width<float>(), window->Height<float>() };

				this->cb_.color_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

				this->shader_->Setup();
				this->shader_->UpdateConstantBuffer(0, &this->cb_);

				//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
				UINT stride = sizeof(Shader::Triangle2d::Vertex);
				UINT offset = 0;

				d2d->context_->IASetVertexBuffers(0, 1, &this->shader_->vertex_buffer_, &stride, &offset);
				//�v���~�e�B�u�E�g�|���W�[���Z�b�g
				d2d->context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				//�v���~�e�B�u�������_�����O
				d2d->context_->Draw(3, 0);
			}
		};
	}
}