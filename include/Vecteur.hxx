#ifndef LAB3_INFRA_VECTEUR_H
#define LAB3_INFRA_VECTEUR_H
#include "ostream"
#include "array"
#include "vector"
template <int dim = 2>
class Vecteur {
public:
    std::array<double,dim> val;
    Vecteur();
    Vecteur(std::array<double,dim>);
    Vecteur(const Vecteur<dim> &);    // Constructeur par copie

    bool operator == (const Vecteur<dim> &);
    Vecteur<dim> & operator=(const Vecteur<dim> &); // operateur de recopie
    Vecteur<dim> & operator+=(const Vecteur<dim> &);
    const double& operator[](int i) const;
    Vecteur<dim> & operator*( double);
    Vecteur<dim> operator-();
    Vecteur<dim> operator / (const Vecteur<dim> &);

    double norme();

    ~Vecteur();
};
template <int dim>
Vecteur<dim> operator/(const Vecteur<dim> &, double );
template <int dim>
Vecteur<dim>  operator/(double ,const Vecteur<dim> &);
template <int dim>
Vecteur<dim> operator-(const Vecteur<dim> & , const Vecteur<dim> & );
template <int dim>
Vecteur<dim> operator+(const Vecteur<dim> &, const Vecteur<dim> &);
template <int dim>
Vecteur<dim> operator*(const Vecteur<dim> &, double);
template <int dim>
Vecteur<dim> operator*(double,const Vecteur<dim> &);
template <int dim>
std::ostream &operator<<(std::ostream &, const Vecteur<dim> &);
#include "../src/Vecteur.txx"
#endif //LAB3_INFRA_VECTEUR_H
