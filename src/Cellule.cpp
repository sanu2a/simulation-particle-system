//
// Created by Sanae Ailla on 12/04/2023.
//

#include "Cellule.h"
template<int dim>
Cellule<dim> ::Cellule(std::array<int,dim> index,Vecteur<dim> centre){
    indice = index;
    centreCell = centre;
}
template<int dim>
Cellule<dim> ::Cellule(){

}
template<int dim>
void Cellule<dim> :: ajouterParticule( Particule<dim> *p){
    Particules.push_back(p);
}

template<int dim>
void Cellule<dim> :: ajouterVoisin(Cellule *c){
    Voisins.push_back(c);
};
template<int dim>
void Cellule<dim> ::  afficher_particules(){
    for (auto particule : Particules) {
        particule->affiche_position();
    }
}
template<int dim>
const std::vector<Particule<dim>*>& Cellule<dim> :: getParticules(){return Particules;}
template<int dim>
void Cellule<dim> :: reset_particules(){
    Particules = std::vector<Particule<dim>*>();

}
