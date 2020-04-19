#pragma once

#include "Node.h"
#include "Vertex.h"
#include "math/matrix.h"
#include <memory>

class Aether;
//#include "plane/Plane.h"
//#include "Aether.h"

namespace Engine::Map
{
  class Graph
  {
    const double maxDistance = 1010;
    const uint32_t maxCloseNeighbors = 2;
    std::vector<std::shared_ptr<Node>> _nodes; // TODO make this a bsp if finding a node is too slow

  public:
    Graph() { std::cout << __FUNCTION__ << std::endl; }
    ~Graph() { std::cout << __FUNCTION__ << std::endl; }

    void addVertex(Vertex const& v);
    void renewNeighbors(Node& n);
    void renewAllNeighbors();
    std::vector<std::weak_ptr<Vertex>> getPath(Engine::Math::vec3 const& start, Engine::Math::vec3 const& end) const;
    void draw(Aether& renderer) const;
  };

} // namespace Engine::Map
