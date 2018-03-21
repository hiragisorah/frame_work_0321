#pragma once

// �f�[�^
#include <data\mesh.h>

// �V�F�[�_
#include <data\shader\default2d.h>

namespace Data
{
	namespace Mesh
	{
		class Point2d : public IMesh
		{
		public:
			Point2d(void)
			{
				std::vector<Shader::Default2d::Vertex> vertices;

				vertices.emplace_back(D3DXVECTOR3(0.0f, 0.0f, .0f));

				this->CreateVertexBuffer(&vertices);
			}
		};
	}
}