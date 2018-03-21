#pragma once

// �t���[�����[�N
#include <framework\system.h>

// �f�[�^
#include <data\texture.h>

// �W�����C�u����
#include <unordered_map>
#include <string>

namespace System
{
	namespace Loader
	{
		class Texture : public ISystem
		{
		private:
			std::unordered_map<std::string, Data::Texture*> database_ = {};

		public:
			void Load(std::string file_name)
			{
				delete this->database_[file_name];
				this->database_[file_name] = new Data::Texture(file_name);
			}

		public:
			void Unload(std::string file_name)
			{
				delete this->database_[file_name];
				this->database_[file_name] = nullptr;
			}

		public:
			Data::Texture * const Get(std::string file_name)
			{
				return this->database_[file_name];
			}

		public:
			~Texture(void)
			{
				for (auto db : this->database_)
					delete db.second;
			}
		};
	}
}