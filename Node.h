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
    Node(Vertex const& v)
      : _dataVert(v)
    {
      std::cout << __FUNCTION__ << std::endl;
    }

    [[deprecated]] Node() { std::cout << __FUNCTION__ << std::endl; }

    bool addCloseNeighbor(std::weak_ptr<Node> const& n);
    void deleteCloseNeighbors()
    {
      for(auto& n : _closeNeighbors)
      {
        if(n.expired()) continue;
        n.lock()->deleteFarNeighbor(*this);
      }
      _closeNeighbors.clear();
    }

    void deleteFarNeighbor(Node const& toDelete)
    {
      this->_farNeighbors.erase(std::remove_if(_farNeighbors.begin(), _farNeighbors.end(), [&](std::weak_ptr<Node> const& elem) { return toDelete == *elem.lock(); }), _farNeighbors.end());
    }

    bool operator==(Node const& other) const { return this->_dataVert == other._dataVert; }

    Vertex const& getVertex() { return _dataVert; }
    Vertex const& setVertex(Vertex const& v) { return _dataVert = v; }

    Vertex const& getVertex() const { return _dataVert; }
    ~Node() { std::cout << __FUNCTION__ << std::endl; }

    void draw(Aether& renderer) const;
  };
} // namespace Engine::Map
