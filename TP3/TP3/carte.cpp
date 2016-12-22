/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2016 | TP3
    http://ericbeaudry.ca/INF3105/tp3/ -- beaudry.eric@uqam.ca    */
#include <limits>
#include "carte.h"
#include <queue>
#include <stack>

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
        Noeud& dest = noeuds[*itr_dest];
        Noeud::Arete arete1;
        arete1.dest = &dest;
        arete1.poids = source.p.distance(arete1.dest->p);
        source.aretes.push_back(arete1);

        Noeud::Arete arete2;
        arete2.dest = &source;
        arete2.poids = dest.p.distance(arete2.dest->p);
        dest.aretes.push_back(arete2);

        
        
        itr_src++;
        itr_dest++;
    }
    
}

unordered_map<long, Carte::DijsktraResult>
Carte::dijsktra(long source) const{
    
    // L'object qui sera placé dans le monceau de Dijsktra
    class Element {
    public:
        Element( const double& distance, const long& noeud ) : distance(distance), noeud(noeud){}
        Element(){}
        Element(const Element& source) : noeud(source.noeud), distance( source.distance){}
        long getNoeud() const { return noeud; }
        double getDistance() const { return distance; }
        bool operator < (const Element& o) const { return distance > o.distance; }
        bool operator > (const Element& o) const { return distance < o.distance; }
    private:
        long noeud;
        double distance;
        long parent;
        
        
    };
    
    // ON CRÉER LE MONCEAU DE DISTANCES
    priority_queue<Element> monceau;
    monceau.push(Element(0,source));

    
    // ON CRÉER UNE TABLE QUI CONTIENT LE PARENT IMMÉDIAT DE CHAQUE CHEMIN
    unordered_map<long, long> parents;

    
    // ON CRÉE UNE TABLE QUI CONTIENT LES DISTANCES DE TOUS LES NOEUDS DE LA SOURCE
    unordered_map<long, DijsktraResult> distances;
    
    // ON INITIALISE LES DISTANCES À L'INFINI
    unordered_map<long, Noeud>::const_iterator itr;
    for( itr = noeuds.begin(); itr != noeuds.end(); itr++){
        distances[itr->first] = DijsktraResult( -1, std::numeric_limits<double>::infinity());
    }
    
    // ON INITIALISE LA DISTANCE DE LA SOURCE À L'INFINI
    distances[source] = DijsktraResult( -1, 0);
    parents[source] = -1;
    
    
    // ON VIDE LE MONCEAU DE DISTANCES
    while(!monceau.empty()){
        const Element u = monceau.top();
        monceau.pop();
        
        const Noeud& noeud = noeuds.at(u.getNoeud());
        list<Noeud::Arete>::const_iterator itr;
        for( itr = noeud.aretes.begin(); itr != noeud.aretes.end(); itr++ ){
            long v = itr->dest->osmid;
            double poids = itr->poids;
            double d = distances[u.getNoeud()].distance + poids;
            if(distances[v].distance > d ){
                distances[v] = DijsktraResult( u.getNoeud(), d);
                monceau.push(Element(d, v));
            }
        }
    }
    
    

    
    return distances;
}
void Carte::ajouter_cafe(const string& nom, const Point& p){
    // ON CHERCHE LE NOEUDS LE PLUS PRET DU CAFÉ
    double min =  std::numeric_limits<double>::infinity();
    long noeud;
    for( std::unordered_map<long, Noeud>::const_iterator it = this->noeuds.begin(); it != this->noeuds.end(); it++ ){
        double d = it->second.p.distance(p);
        if( d < min ){
            min = d;
            noeud = it->second.osmid;
        }
    }
    
    noeuds[noeud].iscafe = true;
    noeuds[noeud].nom = nom;
    cafes.push_back(noeud);
    
}

double Carte::calculer_chemin(const Point& a, const Point& b, list<Point>& chemin) const{
    
    // ON CHERCHE LES DEUX NOEUDS LES PLUS PRETS DE CHAQUE AMOUREUX
    double min1 =  std::numeric_limits<double>::infinity();
    double min2 =  std::numeric_limits<double>::infinity();
    long noeud1(-1);
    long noeud2(-1);
    
    for( std::unordered_map<long, Noeud>::const_iterator it = this->noeuds.begin(); it != this->noeuds.end(); it++ ){
        double d1 = it->second.p.distance(a);
        if( d1 < min1 ){
            min1 = d1;
            noeud1 = it->second.osmid;
        }
        double d2 = it->second.p.distance(b);
        if( d2 < min2 ){
            min2 = d2;
            noeud2 = it->second.osmid;
        }
    }
    
    // ON CALCULE DIJSKTRA POUR LE PREMIER NOEUD
    unordered_map<long, Carte::DijsktraResult> distances1 = dijsktra( noeud1 );
    
    // ON CALCULE DIJSTRA POUR LE SECOND NOEUD
    unordered_map<long, Carte::DijsktraResult> distances2 = dijsktra( noeud2 );
    
    // ON CHERCHE LE CHEMIN DE COÛT MINIMUM
    list<long>::const_iterator itr;
    double distance = numeric_limits<double>::infinity();
    long result = -1;
    for( itr = cafes.begin(); itr != cafes.end(); itr++ ){
        long cafe = *itr;
        
        double d1 = distances1[cafe].distance;
        double d2 = distances2[cafe].distance;
        double d = max( d1 , d2);
        if( d < distance ){
            //if( distance == 0 ){ continue; }
            distance = d;
            result = cafe;
        }
        
    }
    
    
    // ON AFFICHE LE NOM DU CAFÉ
    cout <<  noeuds.at(result).nom << endl;
    
    // ON AFFICHE LES DISTANCES
    cout << round(distances1[result].distance + min1) << "m " << round(distances2[result].distance + min2) << "m " << endl;
    
    // ON AFFICE LE CHEMIN 1
    
    std::stack<long> chemin1;
    chemin1.push(result);
    DijsktraResult noeud = distances1[result];
    long parent = noeud.parent;
    while(true ) {
        noeud = distances1[parent];
        if( noeud.parent == -1 ){ break; }
        chemin1.push(noeud.parent);
        parent = noeud.parent;
    }
    while( !chemin1.empty()){
        long top = chemin1.top();
        cout << noeuds.at(top).p << " ";
        chemin1.pop();
    }
    cout << endl;
    
    
    std::stack<long> chemin2;
    chemin2.push(result);
    noeud = distances2[result];
    parent = noeud.parent;
    while(true ) {
        noeud = distances2[parent];
        if( noeud.parent == -1 ){ break; }
        chemin2.push(noeud.parent);
        parent = noeud.parent;
    }
    while( !chemin2.empty()){
        long top = chemin2.top();
        cout << noeuds.at(top).p << " ";
        chemin2.pop();
    }
    cout << endl;
    
    return distance;
}

string Carte::suggerer_lieu_rencontre(const Point& membre1, const Point& membre2, double& d1, double& d2, list<Point>& chemin1, list<Point>& chemin2) const{
    // À coder.
    d1 = d2 = numeric_limits<double>::infinity();
    chemin1.clear();
    chemin2.clear();
    
    //calculer_chemin(membre1, membre2, chemin1);
    
    return calculer_chemin(membre1, membre2, chemin1) == numeric_limits<double>::infinity() ? "Impossible" : "";
}

