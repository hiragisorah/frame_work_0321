#pragma once

// フレームワーク 
#include <framework\component.h>
#include <framework\entity.h>

// コンポーネント
#include <component\transform.h>

namespace Component
{
	D3DXVECTOR3 Interpolate(D3DXVECTOR3 start, D3DXVECTOR3 end, float now)
	{
		return start + (end - start) * now;
	}

	D3DXVECTOR3 InterpolateR(D3DXVECTOR3 start, D3DXVECTOR3 end, float now)
	{
		while (fabsf(start.x - end.x) > 180.f)
			start.x > end.x ? start.x -= 360.f : start.x += 360.f;

		while (fabsf(start.y - end.y) > 180.f)
			start.y > end.y ? start.y -= 360.f : start.y += 360.f;

		while (fabsf(start.z - end.z) > 180.f)
			start.z > end.z ? start.z -= 360.f : start.z += 360.f;

		return Interpolate(start, end, now);
	}

	Transform Interpolate(Transform start, Transform end, float now)
	{
		Transform ret = {};
		ret.position_ = Interpolate(start.position_, end.position_, now);
		ret.rotation_ = InterpolateR(start.rotation_, end.rotation_, now);
		ret.scale_ = Interpolate(start.scale_, end.scale_, now);

		return ret;
	}

	struct Animation
	{
		Transform transform_;
		Animation * next_ = nullptr;

		int frames_;
	};

	class AnimationManager : public IComponent
	{
	private:
		float frame_time_ = 0.f;
		float speed_ = 1.f;
		Animation * start_ = nullptr;
		Animation * end_ = nullptr;
		Animation copy_;
		Transform * transform_;

	public:
		AnimationManager(Entity * parent) : IComponent(parent)
		{
			this->transform_ = this->GetParent()->GetComponent<Transform>();
		}

	public:
		void Intercept(Animation * anim)
		{
			this->copy_.transform_ = *this->transform_;
			this->start_ = &this->copy_;
			this->end_ = anim;
			this->frame_time_ = 0.f;
		}

	public:
		bool IsPlaying(Animation * anim)
		{
			return anim == this->end_ || anim == this->start_;
		}

	public:
		virtual void Update(void) override {}
		virtual void Pause(void) override {}
		virtual void Always(void) override
		{
			*this->transform_ = Interpolate(this->start_->transform_, this->end_->transform_, frame_time_ / this->end_->frames_);

			if (this->frame_time_ / this->end_->frames_ > 1.f)
			{
				this->start_ = this->end_;
				this->end_ = this->end_->next_;
				this->frame_time_ = 0.f;
			}

			this->frame_time_ += this->speed_;
		}
	};
}