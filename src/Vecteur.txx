#include "Vecteur.hxx"
#include "math.h"
template<int dim>
Vecteur<dim>::Vecteur(){
    val = {};
}

template<int dim>
double Vecteur<dim>::norme(){
    double norme = 0;
    for (int i = 0; i < dim; ++i) {
      norme += pow(val[i],2);
    }
    return sqrt(norme);
}

template<int dim>
Vecteur<dim>::Vecteur(std::array<double,dim> values) {
    for (int i = 0; i < dim; ++i) {
        val[i] = values[i];
    }
}
template<int dim>
Vecteur<dim> & Vecteur<dim>::operator=(const Vecteur<dim> &v){
    for (int i = 0; i < dim; ++i) {
        val[i] = v.val[i];
    }
    return *this;
}

template<int dim>
Vecteur<dim>::Vecteur(const Vecteur<dim> & v){
    for (int i = 0; i < dim; ++i) {
        val[i] = v.val[i];
    }
}
template<int dim>
Vecteur<dim> & Vecteur<dim>::operator+=(const Vecteur<dim> &v){
    for (int i = 0; i < dim; ++i) {
        val[i] += v.val[i];
    }
    return *this;
}
template<int dim>
Vecteur<dim> & Vecteur<dim>::operator*(double d){
    for (int i = 0; i < dim; ++i) {
        val[i] *= d;
    }
    return  *this;
}

template<int dim>
bool Vecteur<dim>::operator==(const Vecteur<dim>& v) {
    for (int i = 0; i < dim; ++i) {
        if (val[i] != v.val[i]) {
            return false;
        }
    }
    return true;
}

template<int dim>
std::ostream &operator<<(std::ostream &stream, const Vecteur<dim> &v) {
    stream << "(";
    for (int i = 0; i < dim; ++i) {
        stream << v.val[i];
        if (i != dim - 1) {
            stream << ",";
        }
    }
    stream << ")" << std::endl;
    return stream;
}

template<int dim>
Vecteur<dim> operator+(const Vecteur<dim> &v1, const Vecteur<dim> &v2) {
    Vecteur<dim> sum;
    for (int i = 0; i < dim; ++i) {
        sum.val[i] = v1.val[i] + v2.val[i];
    }
    return sum;
}

template<int dim>
Vecteur<dim> operator*(const Vecteur<dim> &v, double d){
    Vecteur<dim> mult;
    for (int i = 0; i < dim; ++i) {
        mult.val[i] = v.val[i]*d;
    }
    return mult;
}

template<int dim>
Vecteur<dim> Vecteur<dim>::operator/(const Vecteur<dim> &v2) {
    Vecteur<dim> div;
    for (int i = 0; i < dim; ++i) {
        div.val[i] = val[i] / v2.val[i];
    }
    return div;
}

template<int dim>
Vecteur<dim> operator/(const Vecteur<dim> &v, double d) {
    Vecteur<dim> div;
    for (int i = 0; i < dim; ++i) {
        div.val[i] = v.val[i] / d;
    }
    return div;
}

template<int dim>
Vecteur<dim> operator*(double d,const Vecteur<dim> &v){
    Vecteur<dim> result;
    for (int i = 0; i < dim; ++i) {
        result.val[i] = d * v.val[i];
    }
    return result;
}
template<int dim>
Vecteur<dim> operator/(double d,const Vecteur<dim> &v){
    Vecteur<dim> div;
    for (int i = 0; i < dim; ++i) {
        div.val[i] = v.val[i] / d;
    }
    return div;
}
template<int dim>
Vecteur<dim> operator-(const Vecteur<dim> &v1, const Vecteur<dim> &v2){
    Vecteur<dim> sous;
    for(int i=0; i<dim; i++){
        sous.val[i] = v1.val[i] - v2.val[i];
    }
    return sous;
}

template<int dim>
Vecteur<dim> Vecteur<dim>::operator-() {
    Vecteur<dim> min_un;
    for (int i = 0; i < dim; i++) {
        min_un.val[i] = -val[i];
    }
    return min_un;
}

template<int dim>
const double& Vecteur<dim>::operator[](int i) const{
    if (i<0 and i>=dim){
        throw std::out_of_range("Index out of bounds");
    }
    return val[i];
}

template<int dim>
Vecteur<dim>::~Vecteur(){}

