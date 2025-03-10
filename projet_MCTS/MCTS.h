#pragma once

#include "jeu.h"

#include <memory>
#include <vector>

class Noeud : public std::enable_shared_from_this<Noeud>
{

    public:

        Noeud(Jeu j, std::shared_ptr<Noeud> p)
        : etat_de_la_partie(j),parent(p), compteur_scenario(0), gain_accumule(0) {};

        //void fabriqueFils(Jeu j);

        void ajouterNoeud(std::shared_ptr<Noeud> n);

        int score(Jeu j);

        void descente(Jeu j,int & coup);
        
        int roll_out(Jeu j);
        
        void update(int score);

        std::shared_ptr<Noeud> UBC(std::shared_ptr<Noeud> filsA, std::shared_ptr<Noeud> filsB);

        int getGain() { return gain_accumule; }

    private:

        Jeu etat_de_la_partie;
        std::shared_ptr<Noeud> parent;
        std::vector<std::shared_ptr<Noeud>> noeuds_fils;
        int compteur_scenario;
        int gain_accumule;

};

