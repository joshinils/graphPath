#include "Node.h"
#include "Aether.h"
#include <algorithm>

namespace Engine::Map
{
  Node::Node(Vertex const& v, Graph const& container)
    : _dataVert(v)
    , maxCloseNeighbors(container.maxCloseNeighbors)
  {
    std::cout << __FUNCTION__ << std::endl;
  }

  Node::~Node() { std::cout << __FUNCTION__ << std::endl; }

  bool Node::addCloseNeighbor(std::weak_ptr<Node> const& n)
  {
    if(n.expired()) return false;
    if(this == &(*n.lock())) return false;

    //TODO check if valid, for example by distance between new nodes position and this position

    double distance = n.lock()->distanceTo(*this);

    this->_closeNeighbors.insert(NodeCapsule(n, distance));
    n.lock()->_farNeighbors.insert(NodeCapsule(weak_from_this(), distance));

    return true;
  }

  void Node::deleteCloseNeighbors()
  {
    for(auto& n : _closeNeighbors)
    {
      if(n.node.expired()) continue;
      ((n.node).lock())->deleteFarNeighbor(*this);
    }
    _closeNeighbors.clear();
  }

  void Node::deleteFarNeighbor(Node const& toDelete)
  {
    //this->_farNeighbors.erase(std::remove_if(_farNeighbors.begin(), _farNeighbors.end(), [&](NodeCapsule const& capsule) { return !capsule.node.expired() && toDelete == *capsule.node.lock(); }), _farNeighbors.end());

    bool done = false;
    while(!done)
    {
      for(auto& capsule : this->_farNeighbors)
      {
        if(capsule.node.expired() || capsule.node.lock()->getVertex() == toDelete.getVertex())
        {
          this->_farNeighbors.erase(capsule);
          break;
        }
      }
      done = true;
    }
  }

  Vertex const& Node::getVertex() const { return _dataVert; }

  Vertex const& Node::setVertex(Vertex const& v) { return _dataVert = v; }

  bool Node::operator==(Node const& other) const { return this->_dataVert == other._dataVert; }

  void Node::draw(Aether& renderer) const
  {
    auto const& pos{ this->_dataVert.getPos() };
    renderer.FillCircle(pos.x(), pos.y(), 15, olc::VERY_DARK_YELLOW);
    renderer.FillCircle(pos.x(), pos.y(), 14, olc::DARK_YELLOW);
    renderer.FillCircle(pos.x(), pos.y(), 13, olc::YELLOW);
    renderer.FillCircle(pos.x(), pos.y(), 2, olc::RED);

    for(auto const& other : _closeNeighbors)
    {
      auto const& otherPos{ other.node.lock()->_dataVert.getPos() };
      renderer.DrawArrow({ pos.x(), pos.y() }, { otherPos.x(), otherPos.y() }, 2, olc::Pixel(200, 200, 200), olc::VERY_DARK_GREY);
    }

    std::stringstream ss;
    ss << '(' << std::fixed << std::setprecision(1) << pos.x() << ", " << pos.y() << ')';
    renderer.DrawString((double)pos.x() + 1, (double)pos.y() + 1, ss.str(), olc::VERY_DARK_GREY, 1);
    renderer.DrawString((double)pos.x(), pos.y(), ss.str(), olc::WHITE, 1);
  }

  double Node::distanceTo(Node const& other) const
  {
    auto foo = this->getVertex().getPos() - other.getVertex().getPos();
    return std::sqrt(float(foo * foo));
  }
} // namespace Engine::Map
