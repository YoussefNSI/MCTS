#pragma once

#include "jeu.h"

#include <memory>
#include <vector>

#include <map>
#include <queue>


class Noeud : public std::enable_shared_from_this<Noeud>
{

    public:

        Noeud(Jeu const & j, std::shared_ptr<Noeud> p, int coup)
        : etat_de_la_partie(j),parent(p), coup_from_parent(coup), compteur_scenario(0), gain_accumule(0) {};

        //void fabriqueFils(Jeu j);

        void ajouterNoeud(std::shared_ptr<Noeud> n);

        std::shared_ptr<Noeud> getParent() { return parent; }

        int getGain() { return gain_accumule; }
        int getNbScenario() { return compteur_scenario; }
        int getCoupParent() { return coup_from_parent; }
        std::vector<std::shared_ptr<Noeud>> getFils() { return noeuds_fils; };

        void setNbScenario(int valeur) { compteur_scenario += valeur; };
        void augmenterNbScenario() { ++compteur_scenario; }
        void setGain(int score) { gain_accumule += score; }


    private:

        Jeu etat_de_la_partie;
        std::shared_ptr<Noeud> parent;
        int coup_from_parent;
        std::vector<std::shared_ptr<Noeud>> noeuds_fils;
        int compteur_scenario;
        int gain_accumule;

};



class MCTS
{


    public :

        MCTS() :racine(std::make_shared<Noeud>(jeu_courant,nullptr,0)) { };

        void reset(int nouvel_etat) { // la nouvelle racine est le nouvel état
            racine.reset(); 
            racine = std::make_shared<Noeud>(jeu_courant,nullptr,nouvel_etat);
    }
    
        int score(Jeu j);

        void descente(Jeu j,int & coup);
        
        int roll_out(Jeu j);
        
        void update(std::shared_ptr<Noeud> n, int score);

        std::shared_ptr<Noeud> UBC(std::shared_ptr<Noeud> filsA, std::shared_ptr<Noeud> filsB);

        std::shared_ptr<Noeud> getRacine() { return racine; };

      
        int meilleur_coup();
        void rechercher(int iterations);

        
        void load_arbre(const std::string& filename);
        void save_arbre(const std::string& filename);

        void self_play(int nb_parties);



     private :
        std::shared_ptr<Noeud> racine;
        const double exploration_param = 2.5;
        Jeu jeu_courant;
     
};
