/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */
#if !defined(__CARTE_H__)
#define __CARTE_H__

#include <istream>
#include <list>
#include <map>
#include <map>
#include <vector>
#include <string>
#include "point.h"
using namespace std;

class Carte{
    
    class Noeud {
    public:
        Noeud(){};
        Noeud( const Noeud& noeud): osmid(noeud.osmid) , p(noeud.p){}
        Noeud& operator = (const Noeud& noeud){ osmid = noeud.osmid; p = noeud.p; return *this; }
        Noeud( const long& osmid , const Point& p): osmid(osmid) , p(p){}
        
        long osmid;
        Point p;
        
        struct Arete {
            Noeud* dest;
            double poids;
        };
        list<Arete> aretes;
        bool iscafe;
        string nom;
        
    };
  public:
    void ajouter_noeud(long osmid, const Point& p);
    void ajouter_route(const string& nom, const list<long>& noeuds);
    void ajouter_cafe(const string& nom, const Point& p);
    string suggerer_lieu_rencontre(const Point& membre1, const Point& membre2, double& d1, double& d2, list<Point>& chemin1, list<Point>& chemin2) const;

    struct DijsktraResult {
        long parent;
        double distance;
        DijsktraResult( const long& parent, const double& distance ) : parent(parent) , distance(distance){}
        DijsktraResult( const DijsktraResult& source ) : parent(source.parent) , distance(source.distance){}
        DijsktraResult(){}
        DijsktraResult& operator = (const DijsktraResult& source){ parent = source.parent; distance = source.distance; return *this; }
    };
    map<long, DijsktraResult> dijsktra( long source ) const;
  private:
   
    
    map<long, Noeud> noeuds;
    map<string, list<long> > routes;
    list<long> cafes;
  friend istream& operator >> (istream& is, Carte& carte);
};

#endif
