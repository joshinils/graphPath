#include "Node.h"
#include "Aether.h"

bool Engine::Map::Node::addCloseNeighbor(std::weak_ptr<Node> const& n)
{
  if(n.expired()) return false;
  if(this == &(*n.lock()) ) return false;

  //TODO check if valid, for example by distance between new nodes position and this position

  this->_closeNeighbors.push_back(n);
  n.lock()->_farNeighbors.push_back(n);

  return true;
}

void Engine::Map::Node::draw(Aether& renderer) const
{
  auto const& pos{ this->_dataVert.getPos() };
  renderer.FillCircle(pos.x(), pos.y(), 15, olc::VERY_DARK_YELLOW);
  renderer.FillCircle(pos.x(), pos.y(), 14, olc::DARK_YELLOW);
  renderer.FillCircle(pos.x(), pos.y(), 13, olc::YELLOW);
  renderer.FillCircle(pos.x(), pos.y(), 2, olc::RED);

  for (auto const& other : _closeNeighbors)
  {
    auto const& otherPos{ other.lock()->_dataVert.getPos() };
    renderer.DrawArrow({ pos.x(), pos.y() }, { otherPos.x(), otherPos.y() }, 2, olc::Pixel(200, 200, 200), olc::VERY_DARK_GREY);
  }

  std::stringstream ss;
  ss << '(' << std::fixed << std::setprecision(1) << pos.x() << ", " << pos.y() << ')';
  renderer.DrawString(pos.x() + 1, pos.y() + 1, ss.str(), olc::VERY_DARK_GREY, 1);
  renderer.DrawString(pos.x(), pos.y(), ss.str(), olc::WHITE, 1);

}
