#pragma once
#include "Vertex.h"
#include <iostream>
#include <memory>
#include <vector>

#include "plane/Plane.h"
#include <iomanip>
#include <sstream>

namespace Engine::Map
{
  class Node
  {
    Vertex _dataVert;
    std::vector<std::weak_ptr<Node>> _neighbors;

  public:
    Node(Vertex const& v)
      : _dataVert(v)
    {
      std::cout << __FUNCTION__ << std::endl;
    }

    [[deprecated]] Node() { std::cout << __FUNCTION__ << std::endl; }

    bool addNeighbor(std::weak_ptr<Node> const& n)
    {
      if(n.expired()) return false;

      //TODO check if valid, for example by distance between new nodes position and this position

      this->_neighbors.push_back(n);
      n.lock()->_neighbors.push_back(n);

      return true;
    }

    Vertex const& getVertex() { return _dataVert; }
    Vertex const& setVertex(Vertex const& v) { return _dataVert = v; }

    Vertex const& getVertex() const { return _dataVert; }
    ~Node() { std::cout << __FUNCTION__ << std::endl; }

    void draw(Plane& p) const
    {
      auto const& pos{ this->_dataVert.getPos() };
      p.FillCircle(pos.x(), pos.y(), 15, olc::VERY_DARK_YELLOW);
      p.FillCircle(pos.x(), pos.y(), 14, olc::DARK_YELLOW);
      p.FillCircle(pos.x(), pos.y(), 13, olc::YELLOW);
      p.FillCircle(pos.x(), pos.y(), 2, olc::RED);
      std::stringstream ss;
      ss << '(' << std::fixed << std::setprecision(1) << pos.x() << ", " << pos.y() << ')';
      p.DrawString(pos.x() + 1, pos.y() + 1, ss.str(), olc::VERY_DARK_GREY, 1);
      p.DrawString(pos.x(), pos.y(), ss.str(), olc::WHITE, 1);
    }
  };
} // namespace Engine::Map
