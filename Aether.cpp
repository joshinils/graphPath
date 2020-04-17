#include "Aether.h"
#include "plane/Plane.h"
#include <iostream>

Aether::Aether() { }

bool Aether::OnUserCreate()
{
  olc::PixelGameEngine::SetPixelMode(olc::Pixel::ALPHA);

  Plane::OnUserCreate();
  std::cout << __FUNCTION__ << std::endl;
  this->g.addVertex({ Engine::Math::vec3{ {   0 }, {   0 } } });
  this->g.addVertex({ Engine::Math::vec3{ { 100 }, {   0 } } });
  this->g.addVertex({ Engine::Math::vec3{ {   0 }, { 100 } } });
  this->g.addVertex({ Engine::Math::vec3{ { 100 }, { 100 } } });

  return true;
}

bool Aether::OnUserUpdate(float fElapsedTime)
{
  this->_totalElapsedTime += fElapsedTime;
  Plane::OnUserUpdate(fElapsedTime);
  this->g.draw(*this);

  auto mouseX{ stocx(GetMouseX()) };
  auto mouseY{ stocy(GetMouseY()) };

  FillCircle(mouseX, mouseY, 10, olc::RED);

  return true;
}

