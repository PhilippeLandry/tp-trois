/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */
#include <limits>
#include "carte.h"

void Carte::ajouter_noeud(long osmid, const Point& p){
    
    noeuds[ osmid ] = Noeud(osmid, p);
}

void Carte::ajouter_route(const string& nom, const list<long>& n){
    
    if( n.size() == 0 ) return;
    
    // ON SAUVE LA ROUTE AVEC SON NOM POUR L'AFFICHER À LA FIN
    routes[nom] = n;
    
    // ON CRÉE LES ARÊTES
    std::list<long>::const_iterator itr_src = n.begin();
    std::list<long>::const_iterator itr_dest = n.begin();
    itr_dest++;
    while( itr_dest != n.end()){
        
        Noeud& source = noeuds[*itr_src];
        Noeud::Arete arete;
        arete.dest = &noeuds[*itr_dest];
        arete.poids = source.p.distance(arete.dest->p);
        source.aretes.push_back(arete);
        itr_src++;
        itr_dest++;
    }
    
}

void Carte::ajouter_cafe(const string& nom, const Point& p){
    
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

