/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */

#if !defined(__POINT_H__)
#define __POINT_H__
#include <iostream>

class Point {
  public:
    Point& operator = (const Point& point){ longitude = point.longitude; latitude = point.latitude; return *this; }
    double distance(const Point&) const;
  private:
    double latitude;
    double longitude;

  friend std::ostream& operator << (std::ostream&, const Point&);
  friend std::istream& operator >> (std::istream&, Point&);
};

#endif

