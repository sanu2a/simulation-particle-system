//
// Created by aillas on 05/04/2023.
//

#include "Particule.hxx"
#include "ostream"
#include "iostream"
#include "fstream"
template<int dim>
Particule<dim>::Particule(Vecteur<dim> p,Vecteur<dim> v){
    this->vitesse  = v;
    this->position = p;
}
template<int dim>
Particule<dim>::Particule(Vecteur<dim> p,Vecteur<dim> v,double m){
    this->vitesse  = v;
    this->position = p;
    this->masse = m;
}
template<int dim>
void Particule<dim>::affiche_position() const{
    for(int i = 0; i < dim; ++i) {
        std::cout << position.val[i] << " ";
    }
}
template<int dim>
void Particule<dim>::affiche_vitesse() const{
    for(int i = 0; i < dim; ++i) {
        std::cout << vitesse.val[i] << " ";
    }
}
template<int dim>
void Particule<dim>::affiche_force() const{
    std::cout<<force<< "\n";
}
template<int dim>
void Particule<dim>::affiche() const {
    this->affiche_position();
    std::cout<<" ";
    this->affiche_vitesse();
    std::cout<<" ";
    this->affiche_force();
    std::cout<<std::endl;
}
template<int dim>
Vecteur<dim> Particule<dim>:: getPosition(){
    return position;
}
template<int dim>
Vecteur<dim> Particule<dim>:: getVitesse(){
    return vitesse;
}
template<int dim>
double Particule<dim>:: getMasse(){
    return masse;
}
template<int dim>
Vecteur<dim> Particule<dim>:: getforce(){
    return force;
}

template<int dim>
Vecteur<dim> Particule<dim>:: getforceold(){
    return f_old;
}
template<int dim>
void Particule<dim>::advance_position(double delta) {
    this->position +=  delta*(this->vitesse + 0.5/this->masse*this->force*delta);
}
template<int dim>
void Particule<dim>::advance_vitesse(double delta){
    this->vitesse  += delta*0.5/this->masse*(this->force + this->f_old);
}
template<int dim>
void Particule<dim>::maj_fold(){
    this->f_old = this->force;
    this -> resetForce();
}
template<int dim>
void Particule<dim>::etat(bool etat){
    active = etat;
}
template<int dim>
void Particule<dim>::update_force(Vecteur<dim> force_new){
    this->force += force_new;
}
template<int dim>
bool Particule<dim>::is_active(){
    return active;
}
template<int dim>
void Particule<dim>::resetForce() {
    force = Vecteur<dim>();
}
template <int dim>
void force_grav(std::vector<Particule<dim>*> particules){
    Vecteur<dim> rij;
    double norme_rij;
    for (auto particule_i = particules.begin(); particule_i != particules.end(); ++particule_i++){
        Vecteur<dim> forcesuri;
        for (auto particule_j = particules.begin(); particule_j != particules.end(); ++particule_j++){
            rij = (*particule_j)->getPosition() - (*particule_i)->getPosition();
            norme_rij = rij.norme();
            if (norme_rij!=0){
                forcesuri += rij*(*particule_i)->getMasse()* (*particule_j)->getMasse()/(pow(norme_rij,3));
            }
        }
        (*particule_i)->resetForce();
        (*particule_i)->update_force(forcesuri);
    }
}

template<int dim>
void stromer_verlet(std::vector<Particule<dim>*> particules, double dt, double t_end) {
    double t = 0;
    force_grav<dim>(particules);
    std::ofstream fichier("../../demo/solar_system.positions");
    while (t < t_end) {
        t = t + dt;
        fichier << t << ",";
        for (auto &particule: particules) {
            particule->advance_position(dt);
            particule->maj_fold();
            for (int i = 0;  i < dim ; i++) {
                fichier << particule->getPosition()[i] << " ";
            }
            fichier << ",";
        }
        force_grav(particules);
        for (auto &particule: particules) {
            particule->advance_vitesse(dt);
        }
        fichier << "\n";
    }
    fichier.close();
}


