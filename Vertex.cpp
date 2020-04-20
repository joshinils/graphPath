#include "Vertex.h"

namespace Engine::Map
{
  Vertex::Vertex(Engine::Math::vec3 pos, bool walkable)
    : _pos(pos)
    , _isWalkable(walkable)
  {
    std::cout << __FUNCTION__ << std::endl;
  }

  Vertex::~Vertex() { std::cout << __FUNCTION__ << std::endl; }

  Math::vec3 const& Engine::Map::Vertex::getPos() const { return _pos; }

  bool Vertex::operator==(Vertex const& other) const { return this->_pos == other._pos; }
} // namespace Engine::Map
