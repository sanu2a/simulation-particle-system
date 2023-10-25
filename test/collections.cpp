//
// Created by morad on 24/04/23.
//
#include "Particule.hxx"
#include "random"
#include <list>
#include <deque>
#include <vector>
#include <forward_list>
#include "chrono"
#include <fstream>

int main() {
    // Generate random particles
    std::forward_list<Particule<3>> forward_list_particule;
    std::list<Particule<3>> list_particule;
    std::deque<Particule<3>> deque_particule;
    std::vector<Particule<3>> vector_particule;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    Vecteur<3> rd_vec = Vecteur<3>({dist(mt),dist(mt),dist(mt)});
    Particule<3> particule = Particule(rd_vec,rd_vec,dist(mt));
    std::ofstream outfile("results.csv");
    outfile << "k,forward_list,list,deque,vector\n";
    for (int k = 6; k < 25; k++) {
        const int n = pow(2,k);
        // forward list
        auto start_flist =  std::chrono::steady_clock::now();
        for (int i = 0; i < n; ++i) {
            forward_list_particule.push_front(particule);
        }
        auto end_flist = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_flist = end_flist-start_flist;
        // vector
        auto start_vector =  std::chrono::steady_clock::now();
        for (int i = 0; i < n; ++i) {
            vector_particule.push_back(particule);
        }
        auto end_vector = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_vector = end_vector-start_vector;
        // list
        auto start_list =  std::chrono::steady_clock::now();
        for (int i = 0; i < n; ++i) {
            list_particule.push_back(particule);
        }
        auto end_list = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_list = end_list-start_list;
        // deque
        auto start_deque =  std::chrono::steady_clock::now();
        for (int i = 0; i < n; ++i) {
            deque_particule.push_back(particule);
        }
        auto end_deque = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_deque = end_deque-start_deque;
        outfile << k << "," << time_flist.count() << "," << time_list.count() << "," << time_deque.count() << "," << time_vector.count() << "\n";
    }
    outfile.close();
    return 0;
}
