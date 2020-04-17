#pragma once

#include "Graph.h"
#include "olcPixelGameEngine/olcPixelGameEngine.h"
#include "plane/Plane.h"

class Aether : public Plane
{
private:
  double _totalElapsedTime = 0;
  Engine::Map::Graph g;

public:
  Aether();
  ~Aether() = default;

  virtual bool OnUserCreate();
  virtual bool OnUserUpdate(float fElapsedTime);
};
