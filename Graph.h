#pragma once

#include "Node.h"
#include "Vertex.h"
#include "math/matrix.h"
#include <iostream>
#include <memory>

class Aether;
//#include "plane/Plane.h"
//#include "Aether.h"

namespace Engine::Map
{
  class Graph
  {
    const static double MAX_DISTANCE;
    std::vector<std::shared_ptr<Node>> _nodes; // TODO make this a bsp if finding a node is too slow

  public:
    Graph() { std::cout << __FUNCTION__ << std::endl; }

    void addVertex(Vertex const& v)
    {
      std::cout << __FUNCTION__ << std::endl;
      std::unique_ptr<Node> newNode(new Node(v));
      renewNeighbors(*newNode);
      this->_nodes.push_back(std::move(newNode));
    }

    void renewNeighbors(Node& n)
    {
      for (auto const& other : _nodes)
      {
        auto foo = other->getVertex().getPos() - n.getVertex().getPos();
        if(std::sqrtf(float(foo * foo)) <= Graph::MAX_DISTANCE)
        {
          n.addCloseNeighbor(other);
        }
      }
    }

    std::vector<std::weak_ptr<Vertex>> getPath(Engine::Math::vec3 const& start, Engine::Math::vec3 const& end) const
    {
      //TODO
      // find closest vertex node to start/end then path between

      return std::vector<std::weak_ptr<Vertex>>();
    }

    void draw(Aether& renderer) const
    {
      for(auto const& n : this->_nodes) { n->draw(renderer); }
    }

    ~Graph() { std::cout << __FUNCTION__ << std::endl; }
  };

} // namespace Engine::Map
