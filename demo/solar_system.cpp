#include "Particule.hxx"
int main() {
    const int dim = 2;
    std::vector<Particule<dim>*> particules;
    Particule Soleil = Particule<dim>({{0,0}},{{0,0}},1);
    Particule Terre = Particule<dim>({{0,1}},{{-1,0}},3e-6);
    Particule Jupyter = Particule<dim>({{0,5.36}},{{-0.425,0}},9.55e-4);
    Particule Halley = Particule<dim>({{34.75,0}},{{0,0.0296}},1e-14);
    particules.push_back(&Soleil);
    particules.push_back(&Terre);
    particules.push_back(&Jupyter);
    particules.push_back(&Halley);
    double t_end = 468.5;
    double dt = 0.015;
    stromer_verlet<dim>(particules,dt,t_end);
}
