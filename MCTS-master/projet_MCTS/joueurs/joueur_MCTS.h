#pragma once


#include "joueur.h"
#include <memory>

#include "../MCTS.h"


class Joueur_MCTS : public Joueur
{
private :
  unsigned int _etat;
  int iterations;
  std::unique_ptr<MCTS> mcts;
  
  
public:
  Joueur_MCTS(std::string nom, bool joueur, int nb_iterations = 10);

  void initialisation() override;

  void init_partie() override;

  char nom_abbrege() const override;

  void recherche_coup(Jeu jeu, int & coup) override;

 
};

