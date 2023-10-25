//
// Created by Sanae Ailla on 23/04/2023.
//
#include "Particule.hxx"
#include "random"
#include <vector>
#include "chrono"
#include <fstream>

int main() {
    std::vector<Particule<3>*> vector_particule;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    Vecteur<3> rd_vec = Vecteur<3>({dist(mt),dist(mt),dist(mt)});
    Particule<3>* particule = new  Particule(rd_vec,rd_vec,dist(mt));
    std::ofstream outfile("insertion.csv");
    outfile << "k,temps d'interactions\n";
    for (int k = 3; k < 8; k++) {
        const int n = pow(pow(2,3),k);
        // forward list
        for (int i = 0; i < n; ++i) {
            vector_particule.push_back(particule);
        }
        auto start =  std::chrono::steady_clock::now();
        force_grav<3>(vector_particule);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_flist = end-start;
        outfile << k << "," << time_flist.count() <<  "\n";
    }
    outfile.close();
    return 0;
}
