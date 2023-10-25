//
// Created by morad on 23/04/23.
//


#include "gtest/gtest.h"
#include "Cellule.h"
#include "Particule.hxx"

TEST(CelluleTest, AjouterParticule) {
    Cellule<3> cell;
    Vecteur<3> position({1, 2, 3});
    Vecteur<3> vitesse({4, 5, 6});
    Particule<3> p = Particule(position, vitesse);

    cell.ajouterParticule(&p);
    ASSERT_EQ(cell.getParticules().size(), 1);
    ASSERT_EQ(cell.getParticules()[0],&p);
}

TEST(CelluleTest, AjouterVoisin) {
    Cellule<3> cell1;
    Cellule<3> cell2;

    cell1.ajouterVoisin(&cell2);
    ASSERT_EQ(cell1.Voisins.size(), 1);
    ASSERT_EQ(cell1.Voisins[0], &cell2);
}

TEST(CelluleTest, ResetParticules) {
    Cellule<3> cell;
    Vecteur<3> position({1, 2, 3});
    Vecteur<3> vitesse({4, 5, 6});
    Particule<3> p1 = Particule(position, vitesse);

    cell.ajouterParticule(&p1);
    ASSERT_EQ(cell.getParticules().size(), 1);

    cell.reset_particules();
    ASSERT_EQ(cell.getParticules().size(), 0);
}



