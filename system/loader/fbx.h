#pragma once

// �t���[�����[�N
#include <framework\system.h>

// �V�X�e��
#include <system\direct3d11.h>

// �f�[�^
#include <data\fbx.h>

// �W�����C�u����
#include <unordered_map>
#include <string>

namespace System
{
	namespace Loader
	{
		class Fbx : public ISystem
		{
		public:
			~Fbx(void)
			{
				for (auto obj : this->database_)
					delete obj.second;
			}

		private:
			struct Vertex
			{
				Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
				float x, y, z;
			};

			struct VertexNormal
			{
				VertexNormal(void) {}
				VertexNormal(D3DXVECTOR3 position, D3DXVECTOR3 normal) : position_(position), normal_(normal) {}
				D3DXVECTOR3 position_;
				D3DXVECTOR3 normal_;
			};

		private:
			std::unordered_map<std::string, Data::Fbx*> database_;

		public:
			void Load(std::string file_name)
			{
				delete this->database_[file_name];
				this->database_[file_name] = new Data::Fbx("resource/model/" + file_name);
			}
			void Unload(std::string file_name)
			{
				delete this->database_[file_name];
				this->database_[file_name] = nullptr;
			}
			Data::Fbx * const Get(std::string file_name)
			{
				return this->database_[file_name];
			}
		};
	}
}