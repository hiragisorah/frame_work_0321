#pragma once

// データ
#include <data\mesh.h>

// Utils
#include <utils\process.h>

// SDK
#include <fbxsdk.h>

// ライブラリ読込
#pragma comment(lib,"libfbxsdk-mt.lib")

namespace Data
{
	class Fbx
	{
		struct Vertex
		{
			Vertex(D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXVECTOR3 uv)
				: position_(position), normal_(normal), uv_(uv) {}

			D3DXVECTOR3 position_;
			D3DXVECTOR3 normal_;
			D3DXVECTOR2 uv_;
		};

	public:
		Fbx * parent_ = nullptr;
		std::vector<Fbx*> children_ = {};

	public:
		Data::IMesh mesh_;
		std::string texture_ = "";

	public:
		Fbx(std::string file_name)
		{
			FbxManager * manager = FbxManager::Create();
			manager ? printf("FBX SDK version %s\n", manager->GetVersion()) : Utils::EndMsg("FBX SDK Failed.\n");

			FbxIOSettings * ios = FbxIOSettings::Create(manager, "IOSRoot");
			manager->SetIOSettings(ios);

			FbxScene * scene = FbxScene::Create(manager, "scene");
			scene ? printf("FBX Scene created.\n") : Utils::EndMsg("FBX Scene failed.\n");

			FbxImporter * importer = FbxImporter::Create(manager, "manager");
			const bool import_status = importer->Initialize(file_name.c_str(), -1, manager->GetIOSettings());
			import_status ? printf("FBX Model imported.\n") : Utils::EndMsg("FBX Model failed.\n");
			!importer->IsFBX() ? Utils::EndMsg("It is not FBX.\n") : importer->Import(scene);

			FbxGeometryConverter geometry_converter(manager);

			geometry_converter.Triangulate(scene, true);
			geometry_converter.SplitMeshesPerMaterial(scene, true);

			this->Init(scene->GetRootNode());

			importer->Destroy();
			scene->Destroy();
			manager->Destroy();
		}

	private:
		void Init(FbxNode * node)
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			{// 子の追加
				int child_cnt = node->GetChildCount();
				for (int i = 0; i < child_cnt; ++i)
					this->children_.emplace_back(new Fbx(this, node->GetChild(i)));
			}

			{// メッシュの取得
				FbxMesh * mesh = node->GetMesh();
				mesh ? printf("Mesh: %s loaded.\n", mesh->GetName()) : printf("Mesh failed.\n");
				if (!mesh) return;
				{// 頂点の取得
					int vtx_cnt = mesh->GetControlPointsCount();
					FbxVector4 * vtx_array = mesh->GetControlPoints();
					for (int i = 0; i < vtx_cnt; ++i)
					{

						vertices.emplace_back(D3DXVECTOR3((float)vtx_array[i][0], (float)vtx_array[i][1], (float)vtx_array[i][2]), D3DXVECTOR3(), D3DXVECTOR3());
						/*v_position.emplace_back(vtx_array[i].mData[0], vtx_array[i].mData[1], vtx_array[i].mData[2]);
						int normal_cnt = mesh->GetElementNormalCount();
						for (int n = 0; n < normal_cnt; ++n)
						{
						FbxGeometryElementNormal * normals = mesh->GetElementNormal(n);
						if (normals->GetMappingMode() == FbxGeometryElement::eByControlPoint)
						{
						if (normals->GetReferenceMode() == FbxGeometryElement::eDirect)
						{
						auto normal = normals->GetDirectArray().GetAt(i).mData;
						v_normal.emplace_back(normal[0], normal[1], normal[2]);
						}
						}
						}*/
					}
				}

				FbxFileTexture * tex_file = nullptr;

				{// テクスチャ名の取得
					int mat_cnt = mesh->GetNode()->GetMaterialCount();

					for (int i = 0; i < mat_cnt; ++i)
					{
						FbxSurfaceMaterial * mat = mesh->GetNode()->GetMaterial(i);
						FbxProperty prop = mat->FindProperty(FbxSurfaceMaterial::sDiffuse);

						int layered_cnt = prop.GetSrcObjectCount<FbxLayeredTexture>();

						if (layered_cnt)
						{
							for (int n = 0; n < layered_cnt; ++n)
							{
								FbxLayeredTexture * layered_tex = prop.GetSrcObject<FbxLayeredTexture>(n);

								int tex_cnt = layered_tex->GetSrcObjectCount<FbxFileTexture>();

								for (int m = 0; m < tex_cnt; ++m)
								{
									FbxFileTexture * texture = prop.GetSrcObject<FbxFileTexture>(m);

									if (texture)
									{
										this->texture_ = texture->GetRelativeFileName();
										
										this->texture_.replace(0, this->texture_.rfind("\\") + 1, "");

										if (this->texture_.rfind(".tga") != -1)
											this->texture_.replace(this->texture_.rfind(".tga"), 4, ".png");

										tex_file = texture;
									}
								}
							}
						}
						else
						{
							int tex_cnt = prop.GetSrcObjectCount<FbxFileTexture>();

							for (int n = 0; n < tex_cnt; ++n)
							{
								FbxFileTexture * texture = prop.GetSrcObject<FbxFileTexture>(n);

								if (texture)
								{
									this->texture_ = texture->GetRelativeFileName();

									this->texture_.replace(0, this->texture_.rfind("\\") + 1, "");

									if (this->texture_.rfind(".tga") != -1)
										this->texture_.replace(this->texture_.rfind(".tga"), 4, ".png");

									tex_file = texture;
								}
							}
						}
					}
				}

				if (this->texture_ != "")
					if (!Game::GetSystem<System::Loader::Texture>()->Get(this->texture_))
						Game::GetSystem<System::Loader::Texture>()->Load(this->texture_);

				{// マテリアルの取得
					/*int mat_cnt = node->GetMaterialCount();
					for (int i = 0; i < mat_cnt; ++i)
					{
						FbxSurfaceMaterial * mat = node->GetMaterial(i);
						FbxProperty prop = mat->FindProperty(FbxSurfaceMaterial::sDiffuse);
						int layered_cnt = prop.GetSrcObjectCount<FbxLayeredTexture>();
						if (!layered_cnt)
						{
							int tex_cnt = prop.GetSrcObjectCount<FbxFileTexture>();
							for (int n = 0; n < tex_cnt; ++n)
							{
								FbxFileTexture * texture = prop.GetSrcObject<FbxFileTexture>(n);
								if (texture)
								{
									this->texture_ = texture->UVSet.Get().Buffer();
								}
							}
						}
					}*/
				}

				{// インデックスの取得
					int vtx_cnt = mesh->GetPolygonCount();
					FbxStringList uv_name_list;
					mesh->GetUVSetNames(uv_name_list);
					
					for (int i = 0; i < vtx_cnt; ++i)
					{
						for (int n = 0; n < 3; ++n)
						{
							int index = mesh->GetPolygonVertex(i, n);
							indices.emplace_back(index);

							{// 法線
								FbxVector4 normal;
								mesh->GetPolygonVertexNormal(i, n, normal);
								vertices[index].normal_ = -D3DXVECTOR3((float)normal[0], (float)normal[1], (float)normal[2]);
							}

							{// テクスチャ座標
								FbxVector2 uv;
								bool ummap;
								mesh->GetPolygonVertexUV(i, n, uv_name_list[0], uv, ummap);
								vertices[index].uv_ = D3DXVECTOR2((float)uv[0], 1.f - (float)uv[1]);
							}
						}
					}
				}

				if (!indices.size() || !vertices.size()) return;


				{// 頂点バッファーの生成
					this->mesh_.CreateVertexBuffer(&vertices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				}

				{// インデックスバッファーの生成
					this->mesh_.CreateIndexBuffer(&indices);
				}
			}
		}

	private:
		Fbx(Fbx * parent, FbxNode * node) : parent_(parent)
		{
			this->Init(node);
		}

	public:
		~Fbx(void)
		{
			for (auto child : this->children_)
				delete child;
		}
	};
}