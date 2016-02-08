// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "MeshBlockGenerator.h"
#include "..\Graphic\RegistryGraphic.h"
#include <type_traits>

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


MeshBlockGenerator::MeshBlockGenerator()
{
  for (auto &i : mMeshArray)
  {
    i = std::make_shared<std::remove_reference_t<decltype(i)>::element_type>();
  }
}

void MeshBlockGenerator::Create(Mesh<VertexVT> &mesh, Side side)
{
  enum 
  {
    VERTEX_COUNT = sizeof(vertexCube) / sizeof(vertexCube[0]),
    SIDE_COUNT = VERTEX_COUNT / 4,

  };
  
  for (size_t i = 0, sideCount = 0; i < SIDE_COUNT; ++i)
  {
    if (side & (1 << i))
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
        mesh.PushVertex({
          { 
            vertexCube[i * 4 + j][0],
            vertexCube[i * 4 + j][1],
            vertexCube[i * 4 + j][2]
          },
          {
            test[j][0],
            test[j][1]
          }
        });
      }

      for (size_t j = 0; j < (sizeof(indexCubeSide) / sizeof(indexCubeSide[0])); ++j)
      {
        mesh.PushIndex(indexCubeSide[j] + sideCount);
      }
      sideCount += 4;
    }
  }
}

void MeshBlockGenerator::SetTexture(int side, std::string texture)
{
  auto mActiveTexture = std::get<0>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture(texture));

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

void MeshBlockGenerator::Generate()
{
  for (size_t i = 0; i < 64; ++i)
  {
    Create(*mMeshArray[i], static_cast<Side>(i));
  }
}
