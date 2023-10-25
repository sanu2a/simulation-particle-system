//
// Created by Sanae Ailla on 10/03/2023.

#ifndef DEMO_PARTICULE_H
#define DEMO_PARTICULE_H
#include "Vecteur.hxx"
template<int dim = 2>
class Particule {

    Vecteur<dim> vitesse;
    Vecteur<dim> position;
    Vecteur<dim> force;
    Vecteur<dim> f_old;

    int id;
    int categorie;

    double masse=0;
    bool active = true;

public:

    Particule(Vecteur<dim>,Vecteur<dim>);
    Particule(Vecteur<dim>,Vecteur<dim>,double);
    void etat(bool);
    bool is_active();
    void affiche() const;
    void affiche_position() const;
    void affiche_vitesse() const;
    void affiche_force() const;
    Vecteur<dim> getVitesse();
    Vecteur<dim> getPosition();
    Vecteur<dim> getforce();
    Vecteur<dim> getforceold();
    double getMasse();
    void advance_position(double );
    void advance_vitesse(double );
    void maj_fold();
    void update_force(Vecteur<dim>);
    void resetForce();

};
template<int dim>
void stromer_verlet(std::vector<Particule<dim>*>,double,double);
#include "../src/Particule.txx"
#endif //DEMO_PARTICULE_H
