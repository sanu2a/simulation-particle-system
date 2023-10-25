//
// Created by Sanae Ailla on 23/03/2023.
//

#ifndef LAB3_UNIVERS_H
#define LAB3_UNIVERS_H
#include "ostream"
#include "Cellule.h"
#include "map"
#include "vector"
template <int dim = 2>
class Univers {
public:

    std::map<std::array<int,dim>, Cellule<dim>*> cellules;

    std::vector<Particule<dim>*> particules;

    Vecteur<dim> longeur_d;

    double rcut;
    Vecteur<dim> n_cells;

    int nparticules;
    double epsilon = 0;
    double sigma = 0;
    Univers(std::vector<Particule<dim>*> );
    Univers(double,double,double, Vecteur<dim>, std::vector<Particule<dim>*>);
    void evolution(double);
    void compute_force_el();
    void compute_force_grav();
    void afficher_etat();
    void maj_cellules();
    void createVtkFile(std::string);
    void visualiser_maillage();
};

#include "../src/Univers.txx"
#endif //LAB3_UNIVERS_H
