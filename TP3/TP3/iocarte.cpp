/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */
#include <cassert>
#include <cstdlib>
#include "carte.h"

/* Lire une carte. 
   Normalement, vous n'aurez pas à modifier ceci.
*/
istream& operator >> (istream& is, Carte& carte)
{
    // Lire les lieux
    while(is){
        string nomlieu;
        long osmid;
        is >> nomlieu;
        if(nomlieu == "---") break;
        assert(nomlieu[0]=='n');
        osmid = atol(nomlieu.c_str()+1);
        Point point;
        char pv;
        is >> point >> pv;
        assert(pv==';');
        carte.ajouter_noeud(osmid, point);
    }

    // Lire les routes
    while(is){
        string nomroute;
        is >> nomroute;
        if(nomroute == "---") break;
        
        char deuxpoints;
        is >> deuxpoints;
        assert(deuxpoints == ':');
        
        std::list<long> listenomslieux;
        while(is){
            string nomlieu;
            is>>nomlieu;
            if(nomlieu==";") break;
            assert(nomlieu!=":"); // pour robustesse
            assert(nomlieu.find(";")==string::npos); // pour robustesse
            long osmid;
            assert(nomlieu[0]=='n');
            osmid = atol(nomlieu.c_str()+1);
            listenomslieux.push_back(osmid);
        }
        carte.ajouter_route(nomroute, listenomslieux);
    }

    return is;
}

