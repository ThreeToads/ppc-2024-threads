// Copyright 2024 Savotina Valeria

#include "tbb/savotina_v_grahams_alg/include/point.hpp"

SavotinaTbb::SavotinaPoint::SavotinaPoint() {
  x = 0;
  y = 0;
}

SavotinaTbb::SavotinaPoint::SavotinaPoint(double X, double Y) {
  x = X;
  y = Y;
}

SavotinaTbb::SavotinaPoint::SavotinaPoint(const SavotinaTbb::SavotinaPoint& p2) {
  x = p2.x;
  y = p2.y;
}

SavotinaTbb::SavotinaPoint& SavotinaTbb::SavotinaPoint::operator=(const SavotinaTbb::SavotinaPoint& p2) {
  if (this == &p2) return *this;
  x = p2.x;
  y = p2.y;
  return *this;
}

bool SavotinaTbb::SavotinaPoint::operator==(const SavotinaTbb::SavotinaPoint& p2) const {
  bool res = false;
  if (x == p2.x && y == p2.y) res = true;
  return res;
}

void SavotinaTbb::SavotinaPoint::swap(SavotinaTbb::SavotinaPoint& p2) {
  SavotinaTbb::SavotinaPoint tmp = (*this);
  (*this) = p2;
  p2 = tmp;
}

double SavotinaTbb::SavotinaPoint::angle(const SavotinaPoint& p) const {
  double dx = p.x - x;
  double dy = p.y - y;
  return atan2(dy, dx);
}

bool SavotinaTbb::SavotinaPoint::operator()(SavotinaTbb::SavotinaPoint& p0, SavotinaTbb::SavotinaPoint& p1) const {
  bool res = false;
  double angle1 = p0.angle((*this));
  double angle2 = p0.angle(p1);

  if (angle1 < angle2)
    res = true;
  else if (angle1 == angle2)
    res = (*this).Distance(p0) < p1.Distance(p0);

  return res;
}

double SavotinaTbb::SavotinaPoint::Distance(const SavotinaTbb::SavotinaPoint& p) const {
  return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
}

int SavotinaTbb::SavotinaPoint::Compare(const SavotinaTbb::SavotinaPoint& pivot,
                                        const SavotinaTbb::SavotinaPoint& P) const {
  int res = 0;  // ==
  double x1 = pivot.x - x;
  double y1 = pivot.y - y;
  double x2 = P.x - pivot.x;
  double y2 = P.y - pivot.y;
  double val = x1 * y2 - y1 * x2;

  if (val > 0)
    res = 1;  // 2 upper 1 | 2 > 1
  else if (val < 0)
    res = -1;  // 2 downer 1 | 2 < 1
  else {
    float dist1 = (*this).Distance(pivot);
    float dist2 = (*this).Distance(P);

    if (dist1 != 0.0 || dist2 != 0.0) {
      if (dist2 > dist1)
        res = 2;  // 2 > 1
      else if (dist2 < dist1)
        res = -2;  // 2 < 1
    }
  }

  return res;
}

SavotinaTbb::SavotinaPoint SavotinaTbb::SavotinaPoint::aRandomPoint(double min, double max) {
  std::random_device rd;
  std::default_random_engine gen{rd()};
  std::uniform_real_distribution<double> random(min, max);

  return SavotinaTbb::SavotinaPoint(random(gen), random(gen));
}
