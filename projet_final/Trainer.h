#pragma once
#include "MCTS.h"
#include "jeu.h"

class MCTSTrainer
{
private:
    int num_games;
    int simulations_per_move;

public:
    MCTSTrainer(int games = 1000, int sims = 100)
        : num_games(games), simulations_per_move(sims) {}

    MCTS mcts;
    void train()
    {
        mcts.enable_entrainement();
        mcts.load_arbre("expert_mcts.json");

        for (int i = 0; i < num_games; ++i)
        {
            Jeu game;
            self_play(game);

            if (i % 100 == 0)
            {
                std::cout << "Jeu " << i << " complété" << std::endl;
                mcts.save_arbre("expert_mcts.json");
            }
        }
    }

    void self_play(Jeu &game)
    {
        std::vector<std::shared_ptr<Noeud>> history;
        mcts.reset(game.get_etat());

        while (!game.terminal())
        {
            mcts.effectuer_recherche(simulations_per_move);
            history.push_back(mcts.get_root());

            int best_move = mcts.meilleur_coup();
            game.joue(best_move);

            // Déplacer la racine vers l'enfant correspondant au coup joué
            bool found = false;
            for (auto &enfant : mcts.get_root()->enfants)
            {
                if (enfant->coup_from_parent == best_move)
                {
                    mcts.get_root() = enfant;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                mcts.reset(game.get_etat()); // Recalculer si l'enfant n'existe pas
            }
        }

        // Rétropropagation
        double result = game.victoire() ? 1.0 : 0.0;
        for (auto &node : history)
        {
            mcts.retropropagation(node, result);
        }
    }

    void update_tree_with_final_result(Jeu &final_state)
    {
        double result = final_state.victoire() ? 1.0 : 0.0;
        auto node = mcts.get_root();
        mcts.retropropagation(node, result);
    }
};