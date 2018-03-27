#pragma once

// データ
#include <data\mesh.h>

// シェーダ
#include <data\shader\specular.h>

namespace Data
{
	namespace Mesh
	{
		class Cube : public IMesh
		{
		public:
			Cube(void)
			{
				std::vector<Shader::Specular::Vertex> vertices;
				std::vector<unsigned int> indices;

				vertices.emplace_back(D3DXVECTOR3(-.5f, +.5f, -.5f), D3DXVECTOR3(-1.f, +1.f, -1.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, +.5f, -.5f), D3DXVECTOR3(+1.f, +1.f, -1.f));
				vertices.emplace_back(D3DXVECTOR3(-.5f, -.5f, -.5f), D3DXVECTOR3(-1.f, -1.f, -1.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, -.5f, -.5f), D3DXVECTOR3(+1.f, -1.f, -1.f));
				vertices.emplace_back(D3DXVECTOR3(-.5f, +.5f, +.5f), D3DXVECTOR3(-1.f, +1.f, +1.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, +.5f, +.5f), D3DXVECTOR3(+1.f, +1.f, +1.f));
				vertices.emplace_back(D3DXVECTOR3(-.5f, -.5f, +.5f), D3DXVECTOR3(-1.f, -1.f, +1.f));
				vertices.emplace_back(D3DXVECTOR3(+.5f, -.5f, +.5f), D3DXVECTOR3(+1.f, -1.f, +1.f));

				indices.emplace_back(0); indices.emplace_back(1); indices.emplace_back(2);
				indices.emplace_back(2); indices.emplace_back(1); indices.emplace_back(3);

				indices.emplace_back(4); indices.emplace_back(0); indices.emplace_back(6);
				indices.emplace_back(6); indices.emplace_back(0); indices.emplace_back(2);

				indices.emplace_back(5); indices.emplace_back(4); indices.emplace_back(7);
				indices.emplace_back(7); indices.emplace_back(4); indices.emplace_back(6);

				indices.emplace_back(1); indices.emplace_back(5); indices.emplace_back(3);
				indices.emplace_back(3); indices.emplace_back(5); indices.emplace_back(7);

				indices.emplace_back(4); indices.emplace_back(5); indices.emplace_back(0);
				indices.emplace_back(0); indices.emplace_back(5); indices.emplace_back(1);

				indices.emplace_back(7); indices.emplace_back(6); indices.emplace_back(3);
				indices.emplace_back(3); indices.emplace_back(6); indices.emplace_back(2);

				this->CreateIndexBuffer(&indices);
				this->CreateVertexBuffer(&vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			}
		};
	}
}