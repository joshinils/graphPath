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
  this->_graph.addVertex({ Engine::Math::vec3{ {   0 }, {   0 } } });

  this->_graph.addVertex({ Engine::Math::vec3{ { 100 }, {   0 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ {   0 }, { 100 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ { 100 }, { 100 } } });

  this->_graph.addVertex({ Engine::Math::vec3{ {-100 }, {   0 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ {   0 }, {-100 } } });
  this->_graph.addVertex({ Engine::Math::vec3{ {-100 }, {-100 } } });

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
  return {in.x * cs - in.y * sn,
          in.x * sn + in.y * cs};
}

void Aether::DrawArrow(olc::vf2d start, olc::vf2d end, double width, olc::Pixel colorTo, olc::Pixel colorFrom)
{
  olc::vf2d lineDirection = (start - end);
  for(float total = 255*2, i = 0; i < total; ++i)
  {
    //std::cout << "total " << total << " i " << i << " i/t " << i/total << std::endl;
    FillLine(start - lineDirection * (i/total), end + lineDirection * (1-((i+1)/total)), width, average(colorTo, colorFrom, (i/(total)), (1 - i/total)));
  }

  auto turned0 = turnVec((start-end).norm(),  M_PI/11);
  auto turned1 = turnVec((start-end).norm(), -M_PI/11);

  FillCircle(end, width/2, colorTo);

  FillLine(end, end + turned0 * width * 5, width * 8/10, colorTo);
  FillLine(end, end + turned1 * width * 5, width * 8/10, colorTo);

  //FillCircle(start, 10, colorFrom);
  //FillCircle(end,   10, colorTo);
}

void Aether::FillLine(olc::vf2d start, olc::vf2d end, double width, olc::Pixel color)
{
  olc::vf2d lineDirection = (start - end).norm();
  olc::vf2d orthog{-lineDirection.y, lineDirection.x};
  orthog *= width/2;
  auto corner0 = start + orthog;
  auto corner1 = start - orthog;
  auto corner2 = end   + orthog;
  auto corner3 = end   - orthog;
  Plane::FillTriangle(corner0, corner1, corner2, color);
  Plane::FillTriangle(corner3, corner1, corner2, color);
}

olc::Pixel operator*(olc::Pixel const& p, float fac)
{
  return olc::Pixel(p.r * fac, p.g * fac, p.b * fac, p.a * fac);
}

olc::Pixel operator+(olc::Pixel const& a, olc::Pixel const& b)
{
  return olc::Pixel(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);
}

// correctly blends color; see: https://www.youtube.com/watch?v=LKnqECcg6Gw
olc::Pixel average(olc::Pixel const& left, olc::Pixel const& right, double weightA, double weightB)
{
  double r = sqrt(left.r * left.r * weightA + right.r * right.r * weightB);
  double g = sqrt(left.g * left.g * weightA + right.g * right.g * weightB);
  double b = sqrt(left.b * left.b * weightA + right.b * right.b * weightB);
  double a = sqrt(left.a * left.a * weightA + right.a * right.a * weightB);
  return olc::Pixel(r,g,b,a);
}
