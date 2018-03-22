#pragma once

// �V�X�e��
#include <system\direct3d11.h>
#include <system\camera.h>

// �f�[�^
#include <data\model.h>

// �V�F�[�_
#include <data\shader\default3d.h>

// ���[�_�[
#include <system\loader\shader.h>
#include <system\loader\mesh.h>

namespace Data
{
	namespace Model
	{
		template<class _Mesh>
		class Primitive3D : public IModel
		{
		public:
			IMesh * mesh_ = nullptr;
			Shader::Default3d * shader_;
			Shader::Default3d::CBUFFER cb_;

		public:
			Primitive3D(void)
			{
				this->shader_ = Game::GetSystem<System::Loader::Shader>()->Get<Shader::Default3d>();
				this->mesh_ = Game::GetSystem<System::Loader::Mesh>()->Get<_Mesh>();
			}

		private:
			void Rendering(void) override
			{
				auto d3d = Game::GetSystem<System::Direct3D11>();
				auto camera = Game::GetSystem<System::Camera>();

				this->cb_.v_ = camera->GetView();
				this->cb_.p_ = camera->GetProjection();

				this->cb_.color_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

				this->shader_->Setup();
				this->shader_->UpdateConstantBuffer(0, &this->cb_);

				d3d->context_->IASetVertexBuffers(0, 1, &this->mesh_->vertex_buffer_, &this->mesh_->stride_, &this->mesh_->offset_);
				//�v���~�e�B�u�E�g�|���W�[���Z�b�g
				d3d->context_->IASetPrimitiveTopology(this->mesh_->topology_);
				//�v���~�e�B�u�������_�����O
				d3d->context_->Draw(this->mesh_->vtx_num_, 0);
			}
		};
	}
}