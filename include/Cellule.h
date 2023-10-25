//
// Created by aillas on 05/04/2023.
//

#ifndef LAB3_CELLULE_H
#define LAB3_CELLULE_H
#include "Particule.hxx"
#include "vector"
#include "ostream"
template<int dim = 2>
class Cellule {
public :
    std::vector<Particule<dim>*> Particules;
    std::vector<Cellule*> Voisins ;
    std::array<int,dim> indice = {};
    Vecteur<dim> centreCell;
    Cellule();

    void ajouterParticule( Particule<dim> *p);
    void ajouterVoisin(Cellule *c);
    void afficher_particules();


    const std::vector<Particule<dim>*>& getParticules();
    //const std::vector<Cellule*>& getVoisins();
    void reset_particules();

    Cellule(std::array<int,dim> index,Vecteur<dim> centre);
};


#include "../src/Cellule.cpp"
#endif //LAB3_CELLULE_H
