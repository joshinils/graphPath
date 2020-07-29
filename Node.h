#pragma once
#include "Vertex.h"
#include <iostream>
#include <memory>
#include <vector>
#include <set>

namespace Engine::Map
{
  class Graph;
}
#include "Graph.h"

class Aether;
//#include "Aether.h"
#include <iomanip>
#include <sstream>

#include <utility>

namespace Engine::Map
{
  class Node;
  struct NodeCapsule
  {
    NodeCapsule(std::weak_ptr<Node> const& n_ptr, double dist)
      : node(n_ptr)
      , distance(dist)
    { }
    std::weak_ptr<Node> node;
    double distance;

    bool operator==(NodeCapsule const& other) const { return this->distance == other.distance; }
    bool operator<(NodeCapsule const& other) const { return this->distance < other.distance; }
  };
  using namespace std::rel_ops;

  class Node : public std::enable_shared_from_this<Node>
  {
    Vertex _dataVert;

    //todo: sort dy distance
    //todo: max amount allowed, remove furthest
    //todo: change to std:array< ? >
    std::set<NodeCapsule> _closeNeighbors; // i am pointing at
    std::set<NodeCapsule> _farNeighbors; // are pointing at me
    uint64_t maxCloseNeighbors;

  public:
    Node(Vertex const& v, Graph const& container);
    ~Node();

    bool addCloseNeighbor(std::weak_ptr<Node> const& n);
    void deleteCloseNeighbors();
    void deleteFarNeighbor(Node const& toDelete);
    bool operator==(Node const& other) const;
    Vertex const& getVertex() const;
    Vertex const& setVertex(Vertex const& v);
    void draw(Aether& renderer) const;
    double distanceTo(Node const& other) const;
  };
} // namespace Engine::Map
