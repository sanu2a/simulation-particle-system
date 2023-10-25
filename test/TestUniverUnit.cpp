//
// Created by morad on 23/04/23.
#include <gtest/gtest.h>
#include "Univers.h"



std::vector<Particule<2>*> create_test_particles() {
    std::vector<Particule<2>*> particles;
    particles.push_back(new Particule<2>( Vecteur<2>({1,-0.5}), Vecteur<2>({0,0}),1));
    particles.push_back(new Particule<2>( Vecteur<2>({0.5,-0.5}), Vecteur<2>({0,0}),1));
    particles.push_back(new Particule<2>( Vecteur<2>({-0.5,0.25}), Vecteur<2>({0,0}),1));
    particles.push_back(new Particule<2>( Vecteur<2>({-1.5,-1.5}), Vecteur<2>({0,0}),1));
    particles.push_back(new Particule<2>( Vecteur<2>({1.5,1.5}), Vecteur<2>({0,0}),1));
    return particles;
}

TEST(UniversTest2D, Evolution) {
    double delta = 0.1;
    double rcut = 1;
    double sigma = 1;
    double epsilon = 1;
    Univers<2> univer = Univers(rcut,sigma,epsilon,Vecteur<2>({4,3}),create_test_particles());
    // Get initial state of particles
    EXPECT_EQ(univer.epsilon, epsilon);
    EXPECT_EQ(univer.rcut, rcut);
    EXPECT_EQ(univer.sigma, sigma);
    EXPECT_EQ(univer.particules.size(), 5);
    EXPECT_EQ(univer.cellules.size(), 12);
    EXPECT_TRUE(univer.longeur_d==Vecteur<2>({4,3}));
    std::vector<Vecteur<2>> initial_positions;
    std::vector<Vecteur<2>> initial_velocities;
    for (const auto& particle : univer.particules) {
        initial_positions.push_back(particle->getPosition());
        initial_velocities.push_back(particle->getVitesse());
    }

    // Evolve the universe
    univer.compute_force_grav();
    if (sigma != 0){
        univer.compute_force_el();
    }
    univer.evolution(delta);

    // Test if particles have changed their positions and velocities
    for (size_t i = 0; i < univer.particules.size(); ++i) {
        EXPECT_FALSE(initial_positions[i]==univer.particules[i]->getPosition());
        EXPECT_FALSE(initial_velocities[i]==univer.particules[i]->getVitesse());
    }
}


