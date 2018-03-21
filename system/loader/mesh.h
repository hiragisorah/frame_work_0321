#pragma once

// フレームワーク
#include <framework\system.h>

// データ
#include <data\mesh.h>

// 標準ライブラリ
#include <unordered_map>
#include <string>
#include <typeinfo>

namespace System
{
	namespace Loader
	{
		class Mesh : public ISystem
		{
		private:
			std::unordered_map<std::string, Data::IMesh*> database_ = {};

		public:
			template<class _Mesh>
			void Load(void)
			{
				auto name = typeid(_Mesh).name();
				delete this->database_[name];
				this->database_[name] = new _Mesh;
			}

		public:
			template<class _Mesh>
			void Unload(void)
			{
				auto name = typeid(_Mesh).name();
				delete this->database_[name];
				this->database_[name] = nullptr;
			}

		public:
			template<class _Mesh>
			_Mesh * const Get(void)
			{
				auto name = typeid(_Mesh).name();
				return static_cast<_Mesh*>(this->database_[name]);
			}

		public:
			~Mesh(void)
			{
				for (auto db : this->database_)
					delete db.second;
			}
		};
	}
}