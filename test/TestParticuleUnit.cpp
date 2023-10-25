//
// Created by morad on 23/04/23.
//
#include "gtest/gtest.h"
#include "Particule.hxx"

// Test du constructeur sans masse
TEST(ParticuleTest, ConstructorNoMass) {
    Vecteur<3> position({1, 2, 3});
    Vecteur<3> vitesse({4, 5, 6});
    Particule<3> p(position, vitesse);

    EXPECT_TRUE(p.getPosition() == position);
    EXPECT_TRUE(p.getVitesse() == vitesse);
    EXPECT_EQ(p.getMasse(), 0);
}

// Test du constructeur avec masse
TEST(ParticuleTest, ConstructorWithMass) {
    Vecteur<3> position({1, 2, 3});
    Vecteur<3> vitesse({4, 5, 6});
    double masse = 1.0;
    Particule<3> p(position, vitesse, masse);

    EXPECT_TRUE(p.getPosition() == position);
    EXPECT_TRUE(p.getPosition() == position);
    EXPECT_EQ(p.getMasse(), masse);
}

// Test de la méthode advance_position
TEST(ParticuleTest, AdvancePosition) {
    Vecteur<3> position({0, 0, 0});
    Vecteur<3> vitesse({1, 1, 1});
    double masse = 1.0;
    Particule<3> p(position, vitesse, masse);

    double delta = 1.0;
    p.advance_position(delta);

    Vecteur<3> expected_position({1, 1, 1});
    EXPECT_TRUE(p.getPosition()==expected_position);
}

// Test de la méthode advance_vitesse
TEST(ParticuleTest, AdvanceVitesse) {
    Vecteur<3> position({0, 0, 0});
    Vecteur<3> vitesse({1, 1, 1});
    double masse = 1.0;
    Particule<3> p(position, vitesse, masse);

    double delta = 1.0;
    Vecteur<3> force({1, 1, 1});
    p.update_force(force);
    p.advance_vitesse(delta);

    Vecteur<3> expected_vitesse({1.5, 1.5, 1.5});
    EXPECT_TRUE(p.getVitesse()== expected_vitesse);
}

// Test de la méthode is_active et resetForce
TEST(ParticuleTest, IsActiveResetforce) {
    Vecteur<3> position({0, 0, 0});
    Vecteur<3> vitesse({1, 1, 1});
    double masse = 1.0;
    Particule<3> p(position, vitesse, masse);
    p.resetForce();
    EXPECT_TRUE(p.is_active());
    EXPECT_TRUE(p.getforce()==position);
}

// Test de la méthode maj_fold
TEST(ParticuleTest, majForceOld) {
    Vecteur<3> position({0, 0, 0});
    Vecteur<3> vitesse({1, 1, 1});
    Vecteur<3> force({1, -1, -51});
    Particule<3> p(position, vitesse);
    p.update_force(force);
    p.maj_fold();
    EXPECT_TRUE(p.getforce()== position);
    EXPECT_TRUE(p.getforceold()== force);



}


