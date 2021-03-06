#include "Graph.h"
#include <vector>

namespace Engine::Map
{
  Graph::Graph() { std::cout << __FUNCTION__ << std::endl; }

  Graph::~Graph() { std::cout << __FUNCTION__ << std::endl; }

  void Graph::addVertex(Vertex const& v)
  {
    std::cout << __FUNCTION__ << std::endl;
    std::unique_ptr<Node> newNode(new Node(v, *this));
    renewNeighbors(*newNode);
    this->_nodes.push_back(std::move(newNode));
  }

  void Graph::renewNeighbors(Node& n)
  {
    n.deleteCloseNeighbors();
    for(auto const& node : _nodes)
    {
      if(node->distanceTo(n) <= this->maxDistance) { n.addCloseNeighbor(node); }
    }
  }

  void Graph::renewAllNeighbors()
  {
    for(auto& node : _nodes) renewNeighbors(*node);
  }

  inline std::vector<std::weak_ptr<Vertex>> Graph::getPath(Engine::Math::vec3 const& start, Engine::Math::vec3 const& end) const
  {
    //TODO
    // find closest vertex node to start/end then path between

    return std::vector<std::weak_ptr<Vertex>>();
  }

  void Graph::draw(Aether& renderer) const
  {
    for(auto const& n : this->_nodes) { n->draw(renderer); }
  }
} // namespace Engine::Map
