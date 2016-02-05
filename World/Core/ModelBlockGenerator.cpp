// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "ModelBlockGenerator.h"
#include "..\Graphic\Render\RenderMeshGL1.h"
#include "..\Graphic\RegistryGraphic.h"

static glm::vec3 vertexCube[] =
{
  { -0.5f, -0.5f, -0.5f },{ -0.5f, -0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f },{ 0.5f, -0.5f, -0.5f }, // front
  { 0.5f, -0.5f, -0.5f },{ 0.5f, -0.5f,  0.5f },{ 0.5f,  0.5f,  0.5f },{ 0.5f,  0.5f, -0.5f }, // right 
  { 0.5f,  0.5f, -0.5f },{ 0.5f,  0.5f,  0.5f },{ -0.5f, 0.5f, 0.5f },{ -0.5f,  0.5f, -0.5f }, // back
  { -0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f,  0.5f },{ -0.5f, -0.5f,  0.5f },{ -0.5f, -0.5f, -0.5f }, // left
  { -0.5f, -0.5f, 0.5f },{ -0.5f,  0.5f,  0.5f },{ 0.5f,  0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f }, // top
  { -0.5f,  0.5f, -0.5f },{ -0.5f, -0.5f, -0.5f },{ 0.5f, -0.5f, -0.5f },{ 0.5f,  0.5f, -0.5f }  // bot
};

static size_t indexCubeSide[] =
{
  0, 3, 2, 2, 1, 0
};

static glm::vec2 textureCube[] =
{
  { 0.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f },{ 1.0f, 0.0f }
};




ModelBlockGenerator::ModelBlockGenerator()
  : mTypeName("ModelBlockGenerator")
{
  PMesh mesh = std::make_shared<Mesh>(std::make_unique<RenderMeshGL1>());

  //mesh->Set(vertex, index);
  mesh->SetAttribute(ATTRIBUTE_VERTEX, { true, sizeof(VertexVT{}.vertex), offsetof(VertexVT, vertex) });
  mesh->SetAttribute(ATTRIBUTE_TEXTURE, { true, sizeof(VertexVT{}.texture), offsetof(VertexVT, texture) });
  mesh->SetVertexSize(sizeof(VertexVT));

  mModel.SetMesh(mesh);
}


ModelBlockGenerator::~ModelBlockGenerator()
{
}

Model &ModelBlockGenerator::Create()
{
  enum 
  {
    VERTEX_COUNT = sizeof(vertexCube) / sizeof(vertexCube[0]),
    SIDE_COUNT = VERTEX_COUNT / 4,

  };

  //static std::vector<float> vertex;
  //static std::vector<size_t> index;
  auto &vertex = mModel.GetMesh()->GetVertex();
  auto &index = mModel.GetMesh()->GetIndex();
  vertex.clear();
  index.clear();

  for (size_t i = 0, sideCount = 0; i < SIDE_COUNT; ++i)
  {
    if (mEnabled[i])
    {
      

      glm::vec2 test[] =
      {
        { mTextures[i].x, mTextures[i].y },
        { mTextures[i].x, mTextures[i].w },
        { mTextures[i].z, mTextures[i].w },
        { mTextures[i].z, mTextures[i].y },
      };

      for (size_t j = 0; j < 4; ++j)
      {
        vertex.push_back(vertexCube[i * 4 + j][0] + mPosition.x);
        vertex.push_back(vertexCube[i * 4 + j][1] + mPosition.y);
        vertex.push_back(vertexCube[i * 4 + j][2] + mPosition.z);
//         vertex.push_back(textureCube[j][0] * txtScale[0] + txtCoord[0].x);
//         vertex.push_back(textureCube[j][1] * txtScale[1] + txtCoord[0].y);
        vertex.push_back(test[j][0]);
        vertex.push_back(test[j][1]);
      }

      for (size_t j = 0; j < (sizeof(indexCubeSide) / sizeof(indexCubeSide[0])); ++j)
      {
        index.push_back(indexCubeSide[j] + sideCount);
      }
      sideCount += 4;
    }
  }

//   PMesh mesh = std::make_shared<Mesh>(std::make_unique<RenderMeshGL1>());
// 
//   mesh->Set(vertex, index);
//   mesh->SetAttribute(ATTRIBUTE_VERTEX, { true, sizeof(VertexVT{}.vertex), offsetof(VertexVT, vertex) });
//   mesh->SetAttribute(ATTRIBUTE_TEXTURE, { true, sizeof(VertexVT{}.texture), offsetof(VertexVT, texture) });
//   mesh->SetVertexSize(sizeof(VertexVT));

  //mModel.GetMesh()->Set(vertex, index);
  //mModel.GetMesh()->SetAttribute(ATTRIBUTE_VERTEX, { true, sizeof(VertexVT{}.vertex), offsetof(VertexVT, vertex) });
  //mModel.GetMesh()->SetAttribute(ATTRIBUTE_TEXTURE, { true, sizeof(VertexVT{}.texture), offsetof(VertexVT, texture) });
  //mModel.GetMesh()->SetVertexSize(sizeof(VertexVT));
  mModel.SetTexture(mActiveTexture);

  return mModel;
}

void ModelBlockGenerator::SetTexture(int side, std::string texture)
{
  mActiveTexture = std::get<0>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture(texture));

  for (unsigned int i = 0; i < 6; ++i)
  {
    if (side & (1 << i))
    {
      const auto &txtPos = std::get<glm::uvec4>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture(texture));

      glm::vec2 txtCoord[] =
      {
        { txtPos.x,            txtPos.y },
        { txtPos.x,            txtPos.y + txtPos.w },
        { txtPos.x + txtPos.z, txtPos.y + txtPos.w },
        { txtPos.x + txtPos.z, txtPos.y }
      };

      glm::vec2 scale(1.0f / (static_cast<glm::vec2>(mActiveTexture->GetSize())));
      txtCoord[0] *= scale;
      txtCoord[1] *= scale;
      txtCoord[2] *= scale;
      txtCoord[3] *= scale;

      glm::vec2 txtScale((txtCoord[2].x - txtCoord[0].x), (txtCoord[2].y - txtCoord[0].y));

      glm::vec2 test[] =
      {
        textureCube[0] * txtScale + txtCoord[0],
        textureCube[1] * txtScale + txtCoord[0],
        textureCube[2] * txtScale + txtCoord[0],
        textureCube[3] * txtScale + txtCoord[0],
      };

      mTextures[i].x = test[0].x;
      mTextures[i].y = test[0].y;
      mTextures[i].z = test[2].x;
      mTextures[i].w = test[2].y;
    }
  }
}

void ModelBlockGenerator::Enable(int side, bool enabled)
{
  for (unsigned int i = 0; i < 6; ++i)
  {
    if (side & (1 << i))
    {
      mEnabled[i] = enabled;
    }
  }
}

const StringIntern &ModelBlockGenerator::GetTypeName() const
{
  return mTypeName;
}

void ModelBlockGenerator::SetPosition(const glm::vec3 &pos)
{
  mPosition = pos;
}
