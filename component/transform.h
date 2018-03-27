#pragma once

// フレームワーク
#include <framework\component.h>
#include <framework\entity.h>

// SDK
#include <D3DX10.h>

namespace Component
{
	class Transform : public IComponent
	{
	public:
		Transform(void) : IComponent(nullptr) {} 
		Transform(Entity * parent) : IComponent(parent)
		{

		}

	public:
		D3DXVECTOR3 position_ = { 0.f, 0.f, 0.f };
		D3DXVECTOR3 scale_ = { 1.f, 1.f, 1.f };
		D3DXVECTOR3 rotation_ = { 0.f, 0.f, 0.f };

	public:
		D3DXMATRIX GetMatrix(void)
		{
			D3DXMATRIX trans, rot, scale;

			D3DXMatrixTranslation(&trans, this->position_.x, this->position_.y, this->position_.z);
			D3DXMatrixRotationYawPitchRoll(&rot, (float)D3DXToRadian(this->rotation_.y), (float)D3DXToRadian(this->rotation_.x), (float)D3DXToRadian(this->rotation_.z));
			D3DXMatrixScaling(&scale, this->scale_.x, this->scale_.y, this->scale_.z);

			return scale * rot * trans;
		}

	public:
		D3DXMATRIX GetParentMatrix(void)
		{
			D3DXMATRIX ret = this->GetMatrix();

			if (this->GetParent() && this->GetParent()->GetParent() && this->GetParent()->GetParent()->GetComponent<Transform>())
				ret *= this->GetParent()->GetParent()->GetComponent<Transform>()->GetParentMatrix();

			return ret;
		}
	};

	class TransformX : public IComponent
	{
	public:
		TransformX(Entity * parent) : IComponent(parent)
		{

		}

	public:
		D3DXMATRIX world_;

	public:
		D3DXMATRIX GetParentMatrix(void)
		{
			return this->world_;
		}
	};
}