//
// Created by Sanae Ailla on 10/04/2023.
//

#include "vector"
#include "Univers.h"
#include <random>

int main() {
    const int dim = 2;
    Vecteur<dim> ld = {{45, 25}};
    double rcut = 2.5;
    double sigma = 1;
    double epsilon = 5;
    std::vector<Particule<dim> *> particules;
    double distInterParticules = std::pow(2, 1.0 / 6);


    for (int i = -5; i < 5; ++i) {
        for (int j = -20; j < 20; ++j) {
            Particule<dim> *p = new Particule<dim>({{j * distInterParticules,  i * distInterParticules}}, {{0, 0}}, 1);
            particules.push_back(p);
        }
    }
    for (int i = -5; i < 5; ++i) {
        for (int j = -5; j < 5; ++j) {
            Particule<dim> *p = new Particule<dim>({{j * distInterParticules, 12+i * distInterParticules}}, {{0, -10}}, 1);
            particules.push_back(p);
        }
    }
    Univers univers = Univers(rcut, sigma, epsilon, ld, particules);
    double t = 0;
    double tf = 2;
    double dt = 0.00005;
    int i = 0;
    std::string filename = "collision_file" + std::to_string(0) + ".vtu";
    univers.createVtkFile(filename);
    univers.compute_force_grav();
    if (sigma != 0){
        univers.compute_force_el();
    }
    while (t < tf){
        t = t + dt;
        univers.evolution(dt);
        i++;
        if (i%1000 == 0){
            std::string fileinter = "collision_file" + std::to_string(i) + ".vtu";
            univers.createVtkFile(fileinter);
        }


    }
    std::string fileend = "collision_file" + std::to_string(i++) + ".vtu";
    univers.createVtkFile(fileend);

}