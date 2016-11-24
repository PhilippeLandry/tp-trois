/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */
#include <limits>
#include "carte.h"

void Carte::ajouter_noeud(long osmid, const Point& p){
    // À coder.
}

void Carte::ajouter_route(const string& nom, const list<long>& noeuds){
    // À coder.
}

void Carte::ajouter_cafe(const string& nom, const Point& p){
    // À coder.
}

double Carte::calculer_chemin(const Point& a, const Point& b, list<Point>& chemin) const{
    // À coder.
    // En principe, l'algorithme de Dijkstra.
    return numeric_limits<double>::infinity();
}

string Carte::suggerer_lieu_rencontre(const Point& membre1, const Point& membre2, double& d1, double& d2, list<Point>& chemin1, list<Point>& chemin2) const{
    // À coder.
    d1 = d2 = numeric_limits<double>::infinity();
    chemin1.clear();
    chemin2.clear();
    return "Impossible!";
}

