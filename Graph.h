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
  private:
    std::vector<std::shared_ptr<Node>> _nodes; // TODO make this a bsp if finding a node is too slow

  public:
    const double maxDistance         = 1010;
    const uint64_t maxCloseNeighbors = 2;

    Graph();
    ~Graph();

    void addVertex(Vertex const& v);
    void renewNeighbors(Node& n);
    void renewAllNeighbors();
    std::vector<std::weak_ptr<Vertex>> getPath(Engine::Math::vec3 const& start, Engine::Math::vec3 const& end) const;
    void draw(Aether& renderer) const;
  };

} // namespace Engine::Map
