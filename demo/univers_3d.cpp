//
// Created by Sanae Ailla on 23/04/2023.
//
#include "Univers.h"
#include <vector>
#include <random>



int main() {
    const int dim = 3;
    const int n = pow(pow(2,5),3);
    std::vector<Particule<dim>*> particules;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0, 1);
    Vecteur<dim> vitesse = Vecteur<dim>({0,0,0});
    double masse = 1.0;
    for (int i = 0; i < n; ++i) {
        Vecteur<dim> pos = Vecteur<dim>({dis(gen),dis(gen),dis(gen)});
        Particule<dim>* particule = new  Particule<dim>(pos, vitesse, masse);
        particules.push_back(particule);
    }
    Univers<dim> univers = Univers<dim>(particules);
    univers.createVtkFile("../../demo/3d_univers.vtu");
}
