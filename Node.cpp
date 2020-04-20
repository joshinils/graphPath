#include "Node.h"
#include "Aether.h"

namespace Engine::Map
{
  Node::Node(Vertex const& v)
    : _dataVert(v)
  {
    std::cout << __FUNCTION__ << std::endl;
  }

  Node::~Node() { std::cout << __FUNCTION__ << std::endl; }

  bool Node::addCloseNeighbor(std::weak_ptr<Node> const& n)
  {
    if(n.expired()) return false;
    if(this == &(*n.lock())) return false;

    //TODO check if valid, for example by distance between new nodes position and this position

    this->_closeNeighbors.push_back(n);
    n.lock()->_farNeighbors.push_back(n);

    return true;
  }

  void Node::deleteCloseNeighbors()
  {
    for(auto& n : _closeNeighbors)
    {
      if(n.expired()) continue;
      n.lock()->deleteFarNeighbor(*this);
    }
    _closeNeighbors.clear();
  }

  void Node::deleteFarNeighbor(Node const& toDelete)
  {
    this->_farNeighbors.erase(std::remove_if(_farNeighbors.begin(), _farNeighbors.end(), [&](std::weak_ptr<Node> const& elem) { return toDelete == *elem.lock(); }), _farNeighbors.end());
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
      auto const& otherPos{ other.lock()->_dataVert.getPos() };
      renderer.DrawArrow({ pos.x(), pos.y() }, { otherPos.x(), otherPos.y() }, 2, olc::Pixel(200, 200, 200), olc::VERY_DARK_GREY);
    }

    std::stringstream ss;
    ss << '(' << std::fixed << std::setprecision(1) << pos.x() << ", " << pos.y() << ')';
    renderer.DrawString((double)pos.x() + 1, (double)pos.y() + 1, ss.str(), olc::VERY_DARK_GREY, 1);
    renderer.DrawString((double)pos.x(), pos.y(), ss.str(), olc::WHITE, 1);
  }
} // namespace Engine::Map
