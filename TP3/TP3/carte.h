/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */
#if !defined(__CARTE_H__)
#define __CARTE_H__

#include <istream>
#include <list>
#include <string>
#include "point.h"
using namespace std;

class Carte{
  public:
    void ajouter_noeud(long osmid, const Point& p);
    void ajouter_route(const string& nom, const list<long>& noeuds);
    void ajouter_cafe(const string& nom, const Point& p);

    double calculer_chemin(const Point& a, const Point& b, list<Point>& chemin) const;
    string suggerer_lieu_rencontre(const Point& membre1, const Point& membre2, double& d1, double& d2, list<Point>& chemin1, list<Point>& chemin2) const;

  private:
    // À coder.

  friend istream& operator >> (istream& is, Carte& carte);
};

#endif
