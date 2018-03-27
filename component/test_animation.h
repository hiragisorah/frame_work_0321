#pragma once

// コンポーネント
#include <component\animation_manager.h>

// システム
#include <system\input\wm.h>

namespace Component
{
	class TestAnimation : public AnimationManager
	{
	private:
		Animation wait_[2];
		Animation atk_[1];

	public:
		TestAnimation(Entity * parent) : AnimationManager(parent)
		{
			{// 待機モーション
				this->wait_[0].next_ = &this->wait_[1];
				this->wait_[1].next_ = &this->wait_[0];

				this->wait_[0].frames_ = 50;
				this->wait_[1].frames_ = 50;

				this->wait_[0].transform_.position_ = { 1.f, 0, 0 };
				this->wait_[1].transform_.position_ = { -1.f, 0, 0 };
				this->wait_[0].transform_.rotation_ = { 0, 0, -20.f };
				this->wait_[1].transform_.rotation_ = { 0, 0, 20.f };

				this->Intercept(&this->wait_[0]);
			}

			{// 攻撃モーション
				this->atk_[0].next_ = &this->wait_[0];

				this->atk_[0].frames_ = 20;

				this->atk_[0].transform_.position_.z = 10.f;
			}
		}

	public:
		void Update(void)
		{
			auto input = Game::GetSystem<System::Input::WM>();

			if (input->KeyTriggered(VK_SPACE) && !this->IsPlaying(&this->atk_[0]))
				this->Intercept(&this->atk_[0]);
		}
	};
}