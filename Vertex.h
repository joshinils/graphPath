#pragma once
#include "math/matrix.h"

namespace Engine::Map
{
  class Vertex
  {
    Math::vec3 _pos;
    bool _isWalkable;

  public:
    Vertex(Engine::Math::vec3 pos = { { 9999 }, { 9999 }, { 9999 } }, bool walkable = true);
    ~Vertex();

    Math::vec3 const& getPos() const;
    bool operator==(Vertex const& other) const;
  };
} // namespace Engine::Map
