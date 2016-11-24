/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */

#include <math.h>
#include <assert.h>
#include "point.h"
#define RAYONTERRE 6371000  // en mètres
#define PI 3.14159265359




/*
//  DIJKSTRA mLog(n) mais avec priority_queue<X>, ça donne mLog(m)
 class X {
    string nom_parent
 ;
    double distance;
    operator <(...) // attention: distances négatives,
 // Aussi: aulieu de réduire la clef, inserer
 }
 DIJKSTRA(G=(V,E),s∈V) pourtoutv∈V
    distances[v] ← +∞
    parents[v] ← indéfini
    distances[s] ← 0
    Q ← créer FilePrioritaire(V )
    tant que ¬Q.vide()
        v ← Enlever v ∈ Q avec la plus petite valeur distances[v
        si distances[v] = +∞ break
        pour toute arête sortante e = (v, w) depuis le sommet v
        d ← distances[v] + e.distance
        si d < distances[w]
            parents[w] ← v
            distances[w] ← d
            Q.RéduireClé(w) // ou Q.insérer(w)
 retourner (distances, parents)
 
 */
double Point::distance(const Point& point) const {
  double s1 = sin((point.latitude-latitude)/2);
  double s2 = sin((point.longitude-longitude)/2);
  return 2*RAYONTERRE * asin(sqrt(s1*s1 + cos(latitude)*cos(point.latitude)*s2*s2));
}

std::istream& operator >> (std::istream& is, Point& point) {
  char po, vir, pf;
  is >> po;
  if(is){
    is >> point.latitude >> vir >> point.longitude >> pf;
    assert(po=='(');
    assert(vir==',');
    assert(pf==')');
    point.longitude *= PI / 180.0;
    point.latitude  *= PI / 180.0;
  }
  return is;
}

std::ostream& operator << (std::ostream& os, const Point& point) {
  os << "(" 
     << (point.latitude * 180.0 / PI)
     << "," 
     << (point.longitude * 180.0 / PI)
     << ")";
  return os;
}
