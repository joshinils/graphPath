#include "Aether.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

Aether::Aether() { }

bool Aether::OnUserCreate()
{
  olc::PixelGameEngine::SetPixelMode(olc::Pixel::ALPHA);

  Plane::OnUserCreate();
  std::cout << __FUNCTION__ << std::endl;
  this->_graph.addVertex({ Engine::Math::vec3{ { 0 }, { 0 } } });

  this->_graph.addVertex({ Engine::Math::vec3{ { -42 }, { 158 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { -131 }, { -23 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { 200 }, { 142 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { 60 }, { 188 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { 16 }, { -167 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { -181 }, { -187 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { -4 }, { -116 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { 51 }, { -132 } } });

  this->_graph.renewAllNeighbors();

  return true;
}

bool Aether::OnUserUpdate(float fElapsedTime)
{
  this->_totalElapsedTime += fElapsedTime;
  Plane::OnUserUpdate(fElapsedTime);
  this->_graph.draw(*this);

  auto mouseX{ stocx(GetMouseX()) };
  auto mouseY{ stocy(GetMouseY()) };

  FillCircle(mouseX, mouseY, 10, olc::RED);

  return true;
}

olc::vf2d turnVec(olc::vf2d const& in, float angle)
{
  auto cs = cos(angle);
  auto sn = sin(angle);
  return { in.x * cs - in.y * sn, in.x * sn + in.y * cs };
}

void Aether::DrawArrow(olc::vf2d start, olc::vf2d end, double width, olc::Pixel colorTo, olc::Pixel colorFrom)
{
  olc::vf2d lineDirection = (start - end);
  for(float total = std::min(100.f, lineDirection.dot(lineDirection)), i = 0; i < total; ++i)
  {
    //std::cout << "total " << total << " i " << i << " i/t " << i/total << std::endl;
    FillLine(start - lineDirection * (i / total), end + lineDirection * (1 - ((i + 1) / total)), width, average(colorTo, colorFrom, (i / (total)), (1. - i / total)));
  }

  auto turned0 = turnVec((start - end).norm(), float( M_PI / 11));
  auto turned1 = turnVec((start - end).norm(), float(-M_PI / 11));

  FillCircle(end, width / 2, colorTo);

  FillLine(end, end + turned0 * (float)width * 5, width * 8 / 10, colorTo);
  FillLine(end, end + turned1 * (float)width * 5, width * 8 / 10, colorTo);

  //FillCircle(start, 10, colorFrom);
  //FillCircle(end,   10, colorTo);
}

void Aether::FillLine(olc::vf2d start, olc::vf2d end, double width, olc::Pixel color)
{
  olc::vf2d lineDirection = (start - end).norm();
  olc::vf2d orthog{ -lineDirection.y, lineDirection.x };
  orthog *= (float)width / 2;
  auto corner0 = start + orthog;
  auto corner1 = start - orthog;
  auto corner2 = end + orthog;
  auto corner3 = end - orthog;
  Plane::FillTriangle(corner0, corner1, corner2, color);
  Plane::FillTriangle(corner3, corner1, corner2, color);
}

olc::Pixel operator*(olc::Pixel const& p, float fac) { return olc::Pixel(uint8_t(p.r * fac), uint8_t(p.g * fac), uint8_t(p.b * fac), uint8_t(p.a * fac)); }

olc::Pixel operator+(olc::Pixel const& a, olc::Pixel const& b) { return olc::Pixel(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a); }

// correctly blends color; see: https://www.youtube.com/watch?v=LKnqECcg6Gw
olc::Pixel average(olc::Pixel const& left, olc::Pixel const& right, double weightA, double weightB)
{
  uint8_t r = (uint8_t)sqrt((uint64_t)left.r * left.r * weightA + (uint64_t)right.r * right.r * weightB);
  uint8_t g = (uint8_t)sqrt((uint64_t)left.g * left.g * weightA + (uint64_t)right.g * right.g * weightB);
  uint8_t b = (uint8_t)sqrt((uint64_t)left.b * left.b * weightA + (uint64_t)right.b * right.b * weightB);
  uint8_t a = (uint8_t)sqrt((uint64_t)left.a * left.a * weightA + (uint64_t)right.a * right.a * weightB);
  return olc::Pixel(r, g, b, a);
}
