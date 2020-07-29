#pragma once

//namespace Engine::Map
//{
//  class Graph;
//}
#include "Graph.h"
#include "olcPixelGameEngine/olcPixelGameEngine.h"
#include "plane/Plane.h"

class Aether : public Plane
{
private:
  double _totalElapsedTime = 0;
  Engine::Map::Graph _graph;

public:
  Aether();
  ~Aether() = default;

  virtual bool OnUserCreate() override;
  virtual bool OnUserUpdate(float fElapsedTime) override;

  void DrawArrow(olc::vf2d start, olc::vf2d end, double width, olc::Pixel colorTo, olc::Pixel colorFrom);
  void DrawArrow(olc::vf2d start, olc::vf2d end, double width, olc::Pixel colorTo) { DrawArrow(start, end, width, colorTo, colorTo); }
  void DrawArrow(olc::vf2d start, olc::vf2d end, double width) { DrawArrow(start, end, width, olc::WHITE); }
  void FillLine(olc::vf2d start, olc::vf2d end, double width, olc::Pixel color = olc::WHITE);
};

olc::Pixel operator*(olc::Pixel const& p, float fac);
olc::Pixel operator+(olc::Pixel const& a, olc::Pixel const& b);
olc::Pixel average(olc::Pixel const& a, olc::Pixel const& b, double weightA = 0.5, double weightB = 0.5);
