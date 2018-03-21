#pragma once

// フレームワーク
#include <framework\system.h>

// データ
#include <data\shader.h>

// 標準ライブラリ
#include <unordered_map>
#include <string>
#include <typeinfo>

namespace System
{
	namespace Loader
	{
		class Shader : public ISystem
		{
		private:
			std::unordered_map<std::string, Data::Shader*> database_ = {};

		public:
			template<class _Shader>
			void Load(void)
			{
				auto name = typeid(_Shader).name();
				delete this->database_[name];
				this->database_[name] = new _Shader;
			}

		public:
			template<class _Shader>
			void Unload(void)
			{
				auto name = typeid(_Shader).name();
				delete this->database_[name];
				this->database_[name] = nullptr;
			}

		public:
			template<class _Shader>
			_Shader * const Get(void)
			{
				auto name = typeid(_Shader).name();
				return static_cast<_Shader*>(this->database_[name]);
			}

		public:
			~Shader(void)
			{
				for (auto db : this->database_)
					delete db.second;
			}
		};
	}
}