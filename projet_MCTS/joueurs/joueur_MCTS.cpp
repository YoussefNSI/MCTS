#include "joueur_MCTS.h"


Joueur_MCTS::Joueur_MCTS(std::string nom, bool joueur, int nb_iterations)
    :Joueur(nom, joueur), iterations(nb_iterations)  {
        mcts = std::make_unique<MCTS>();
    }

void Joueur_MCTS::initialisation()
{
     mcts->load_arbre("arbre2_mcts");
}

void Joueur_MCTS::init_partie()
{   
   
    mcts->reset(RACINE);

}

char Joueur_MCTS::nom_abbrege() const
{
    return 'M';
}





void Joueur_MCTS::recherche_coup(Jeu jeu, int & coup)
{
   mcts->reset(jeu.getEtat());

   // mcts->rechercher(iterations); // seulement pour le selfplay

   coup = mcts->meilleur_coup();

   if (coup == -1 || !jeu.coup_licite(coup))
    coup = 1;

}