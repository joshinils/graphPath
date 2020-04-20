#pragma once
#include "Vertex.h"
#include <iostream>
#include <memory>
#include <vector>

class Aether;
//#include "Aether.h"
#include <iomanip>
#include <sstream>

namespace Engine::Map
{
  class Node
  {
    Vertex _dataVert;

    //todo: sort dy distance
    //todo: max amount allowed, remove furthest
    //todo: change to std:array< ? >
    //todo: store distance in ---^
    std::vector<std::weak_ptr<Node>> _closeNeighbors; // i am pointing at
    std::vector<std::weak_ptr<Node>> _farNeighbors; // are pointing at me

  public:
    Node(Vertex const& v);
    ~Node();

    bool addCloseNeighbor(std::weak_ptr<Node> const& n);
    void deleteCloseNeighbors();
    void deleteFarNeighbor(Node const& toDelete);
    bool operator ==(Node const& other) const;
    Vertex const& getVertex() const;
    Vertex const& setVertex(Vertex const& v);
    void draw(Aether& renderer) const;
  };
} // namespace Engine::Map
