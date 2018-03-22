#pragma once

// フレームワーク
#include <framework\system.h>

// システム
#include <system\direct3d11.h>

// データ
#include <data\obj.h>

// 標準ライブラリ
#include <unordered_map>
#include <string>

namespace System
{
	namespace Loader
	{
		class Obj : public ISystem
		{
		public:
			~Obj(void)
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

		private:
			std::unordered_map<std::string, Data::IObj*> database_;

		public:
			void Load(std::string file_name)
			{
				delete this->database_[file_name];
				this->database_[file_name] = new Data::IObj;
				auto * mesh = &this->database_[file_name]->mesh_;
				file_name = "resource/model/" + file_name + ".obj";

				std::vector<Vertex> vertices;
				std::vector<unsigned int> indices;

				FILE * fp = fopen(file_name.c_str(), "r");

				char line[100];

				float vx = 0, vy = 0, vz = 0;
				unsigned int ia = 0, ib = 0, ic = 0;

				while (fgets(line, 100, fp))
				{
					if (line[0] == 'v')
					{
						sscanf(line, "v %f %f %f", &vx, &vy, &vz);
						vertices.emplace_back(-vx, vy, vz);
					}
					else if (line[0] == 'f')
					{
						sscanf(line, "f %d// %d// %d//", &ia, &ib, &ic);
						indices.emplace_back(ia - 1);
						indices.emplace_back(ib - 1);
						indices.emplace_back(ic - 1);
					}
				}

				fclose(fp);

 				mesh->CreateVertexBuffer(&vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				mesh->CreateIndexBuffer(&indices);
			}
			void Unload(std::string file_name)
			{
				delete this->database_[file_name];
				this->database_[file_name] = nullptr;
			}
			Data::IObj * const Get(std::string file_name)
			{
				return this->database_[file_name];
			}
		};
	}
}