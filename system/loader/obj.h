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

			struct VertexNormal
			{
				VertexNormal(void) {}
				VertexNormal(D3DXVECTOR3 position, D3DXVECTOR3 normal) : position_(position), normal_(normal) {}
				D3DXVECTOR3 position_;
				D3DXVECTOR3 normal_;
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

				FILE * fp = fopen(file_name.c_str(), "r");

				char line[100];

				fseek(fp, 0L, SEEK_SET);

				std::vector<unsigned int> indices = {};
				std::vector<D3DXVECTOR3> vtx = {};
				std::vector<D3DXVECTOR3> normal = {};
				std::vector<VertexNormal> vtx_normal = {};

				float vx = 0, vy = 0, vz = 0;
				float nx = 0, ny = 0, nz = 0;

				unsigned int ia = 0, ib = 0, ic = 0;
				unsigned int na = 0, nb = 0, nc = 0;

				while (fgets(line, 100, fp))
				{
					if (line[0] == 'v' && line[1] == ' ')
					{
						sscanf(line, "v %f %f %f", &vx, &vy, &vz);
						vtx.emplace_back(vx, vy, vz);
						vtx_normal.resize(vtx_normal.size() + 1);
					}
					else if (line[0] == 'v' && line[1] == 'n')
					{
						sscanf(line, "vn %f %f %f", &nx, &ny, &nz);
						normal.emplace_back(nx, ny, nz);
					}
					else if (line[0] == 'f')
					{
						if (normal.size())
						{
							sscanf(line, "f %d//%d %d//%d %d//%d", &ia, &na, &ib, &nb, &ic, &nc);
							vtx_normal[ia - 1] = VertexNormal(vtx[ia - 1], normal[na - 1]);
							vtx_normal[ib - 1] = VertexNormal(vtx[ib - 1], normal[nb - 1]);
							vtx_normal[ic - 1] = VertexNormal(vtx[ic - 1], normal[nc - 1]);
						}
						else
						{
							sscanf(line, "f %d// %d// %d//", &ia, &ib, &ic);
						}
						indices.emplace_back(ia - 1);
						indices.emplace_back(ib - 1);
						indices.emplace_back(ic - 1);
					}
				}

				fclose(fp);

				if(normal.size())
					mesh->CreateVertexBuffer(&vtx_normal, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				else
					mesh->CreateVertexBuffer(&vtx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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