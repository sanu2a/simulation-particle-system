//
// Created by morad on 23/04/23.
//
#include "gtest/gtest.h"
#include "Vecteur.hxx"

// Test du constructeur par défaut
TEST(VecteurTest, DefaultConstructor) {
    Vecteur<3> v;
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
    EXPECT_EQ(v[2], 0);
}

// Test du constructeur avec array et copie
TEST(VecteurTest, ConstructorArraycopy) {
    Vecteur<3> v({10, 25, 33});
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 25);
    EXPECT_EQ(v[2], 33);
    Vecteur<3> l(v);
    EXPECT_EQ(l[0], 10);
    EXPECT_EQ(l[1], 25);
    EXPECT_EQ(l[2], 33);

}

// test de la norme
TEST(VecteurTest, Norme) {
    Vecteur<3> l({0, 4, 0});
    EXPECT_EQ(l.norme(), 4);
}
// Test d'égalité
TEST(VecteurTest, egalite) {
    Vecteur<3> v1({10, 27, -0.72});
    Vecteur<3> v2({10, 27.0, -0.7199999999999997});
    Vecteur<3> v3({20, 2, 0.2});
    EXPECT_NEAR(v1[2],v2[2],1e-6);
    EXPECT_FALSE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}
// Test de l'opérateur =
TEST(VecteurTest, AssignmentOperator) {
    Vecteur<4> v1({-1, 0, 0,2});
    Vecteur<4> v2({0,0,0,1});
    v2 = v1;
    EXPECT_EQ(v2[0], -1);
    EXPECT_EQ(v2[1], 0);
    EXPECT_EQ(v2[2], 0);
    EXPECT_EQ(v2[3], 2);
}

// Test de l'opérateur +=
TEST(VecteurTest, AdditionAssignmentOperator) {
    Vecteur<2> v1({1,3});
    Vecteur<2> v2({4, 6});
    v1 += v2;
    EXPECT_EQ(v1[0], 5);
    EXPECT_EQ(v1[1], 9);
}

// Test de l'opérateur de *
TEST(VecteurTest, MultiplicationOperator) {
    Vecteur<3> v1({1, 2, 3});
    double d = 3;
    Vecteur<3> v2 = v1 * d;
    EXPECT_EQ(v2[0], 3);
    EXPECT_EQ(v2[1], 6);
    EXPECT_EQ(v2[2], 9);
}


TEST(VecteurTest, SoustractionOperator) {
    Vecteur<3> v1({1, 2, 3});
    Vecteur<3> v2 =-v1;
    EXPECT_EQ(v2[0], -1);
    EXPECT_EQ(v2[1], -2);
    EXPECT_EQ(v2[2], -3);
    Vecteur<3>  v3 = v2/v1;
    EXPECT_EQ(v3[0], -1);
    EXPECT_EQ(v3[1], -1);
    EXPECT_EQ(v3[2], -1);
}

// Test de l'opérateur de + de vecteurs
TEST(VecteurTest, additionVecteurOperator) {
    Vecteur<3> v1({1, 2, 3});
    Vecteur<3> v2({2, 3, 4});
    Vecteur<3> v3 = v1 + v2;
    EXPECT_EQ(v3[0], 3);
    EXPECT_EQ(v3[1], 5);
    EXPECT_EQ(v3[2], 7);
}



