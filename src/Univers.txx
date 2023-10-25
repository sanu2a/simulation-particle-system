//
// Created by aillas on 06/04/2023.
//

#include "Univers.h"
#include <fstream>
#include "iostream"
#include "math.h"


template<int dim>
Univers<dim>::Univers(std::vector<Particule<dim>*> particules):particules(particules){};
template<>
Univers<2>::Univers(double rcut , double sigma, double epsilon,Vecteur<2> longeur_d,std::vector<Particule<2>*>  particules):particules(std::move(particules)),longeur_d(longeur_d),epsilon(epsilon),rcut(rcut),sigma(sigma){
    Vecteur<2> v = longeur_d/(rcut);
    n_cells = Vecteur({floor(v.val[0]),floor(v.val[1])});
    double x_shift =  rcut*n_cells[0]/2;
    double y_shift =  rcut*n_cells[1]/2;
    double taille_cell = longeur_d[0]/n_cells[0];
    for (int i = 1; i <= n_cells[0]; i++) {
        for (int j = 1; j <= n_cells[1]; j++) {
            std::array<int, 2> index = {i, j};
            double x_centre = (i - 1)*rcut - x_shift + taille_cell/2;
            double y_centre = (j - 1 )*rcut - y_shift + taille_cell/2;;
            Cellule<2> * cellule = new Cellule<2>(index,Vecteur<2>({x_centre,y_centre}));
            cellules[index] = cellule;
        }
    }
    for (auto& cell : cellules) {
        auto [x, y] = cell.first;
        if (x > 1 && x < n_cells[0] && y > 1 && y < n_cells[1]) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <=1 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y + j}]);
                }
            }
        }
        else if (x == 1 && y == 1) {
            for (int i = 0; i <= 1; ++i) {
                for (int j = 0; j <=1 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        }

        else if (x == 1 && y == n_cells[1]) {
            for (int i = 0; i <= 1; ++i) {
                for (int j = -1; j <=0 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        } else if (x == n_cells[0] && y == 1) {
            for (int i = -1; i <= 0; ++i) {
                for (int j = 0; j <=1 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        } else if (x == n_cells[0] && y == n_cells[1]) {
            for (int i = -1; i <= 0; ++i) {
                for (int j = -1; j <=0 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        }
        else if (x == 1 && y > 1 && y < n_cells[1]) {
            for (int i = 0; i <= 1; ++i) {
                for (int j = -1; j <=1 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        }
        else if (x == n_cells[0] && y > 1 && y < n_cells[1]) {
            for (int i = -1; i <= 0; ++i) {
                for (int j = -1; j <=1 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        }
        else if (y == 1 && x > 1 && x < n_cells[0]) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = 0; j <=1 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        }
        else if (y == n_cells[1] && x > 1 && x < n_cells[0]) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <=0 ; ++j) {
                    cell.second->ajouterVoisin(cellules[{x + i, y+ j}]);
                }
            }
        }
    }
    maj_cellules();
}

template<int dim>
void Univers<dim>::createVtkFile(std::string filename) {
    std::ofstream output("../../demo/collision_vtk/" + filename, std::ios::out | std::ios::trunc);
    output << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    output << "<UnstructuredGrid>\n";
    std::string positions, vitesses, masses;
    for (int i = 0; i < particules.size(); ++i) {
        positions += std::to_string(particules[i]->getPosition()[0]) + " " +
                     std::to_string(particules[i]->getPosition()[1]) + " " +
                     std::to_string(particules[i]->getPosition()[2]) + "\n";

        vitesses += std::to_string(particules[i]->getVitesse()[0]) + " " +
                    std::to_string(particules[i]->getVitesse()[1]) + " " +
                    std::to_string(particules[i]->getVitesse()[2]) + "\n";

        masses += std::to_string(particules[i]->getMasse()) + "\n";
    }
    output << "<Piece NumberOfPoints=\"" << particules.size() << "\" NumberOfCells=\"0\">\n";
    output << "<Points>\n";
    output << "<DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\"  format=\"ascii\">\n";
    output << positions;
    output << "</DataArray>\n";
    output << "</Points>\n";
    output << "<PointData Vectors=\"vector\">\n";
    output << "<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    output << vitesses;
    output << "</DataArray>\n";
    output << "<DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";
    output << masses;
    output << "</DataArray>\n";
    output << "</PointData>\n";
    output << "<Cells>\n";
    output << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
    output << "</DataArray>\n";
    output << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
    output << "</DataArray>\n";
    output << "<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n";
    output << "</DataArray>\n";
    output << "</Cells>\n";
    output << "</Piece>\n";
    output << "</UnstructuredGrid>\n";
    output << "</VTKFile>\n";
    output.close();
}


template<int dim>
void Univers<dim>::maj_cellules() {
    for (auto cell:cellules){
        cell.second->reset_particules();
    }
    for (auto it = particules.begin(); it != particules.end();) {
        Vecteur coordonne = (*it)->getPosition() + this->longeur_d/2;
        Vecteur indexCell = coordonne/rcut;
        int i = ceil(indexCell.val[0]) > 0 ? ceil(indexCell.val[0]) : 1;
        int j = ceil(indexCell.val[1]) > 0 ? ceil(indexCell.val[1]) : 1;
        // dans la zone
        if (0 < i and i <= this->n_cells.val[0] and 0 < j and j <= this->n_cells.val[1]){
            cellules[{i, j}]->ajouterParticule(*it);
            ++it;
        }else{
            // Remove the particule in constant time
            it = particules.erase(it);
        }
    }

}

template<int dim>
void Univers<dim>::afficher_etat() {
    for (auto particule : particules){
            particule->affiche_position();}
    std::cout << std::endl;
}
template<int dim>
void Univers<dim>::evolution(double delta){
    for (auto& particule : particules) {
        particule->advance_position(delta);
        particule->maj_fold();
    }
    maj_cellules();
    compute_force_grav();
    if (sigma != 0){
        compute_force_el();
    }
    for  (auto &particule : particules){
        particule->advance_vitesse(delta);
    }
}



template<int dim>
void Univers<dim>::compute_force_grav() {
    Vecteur<dim> rij;
    double norme_rij;
    Vecteur<dim> f;
    for (auto particule_i = particules.begin(); particule_i != particules.end(); ++particule_i++) {
        for (auto particule_j = std::next(particule_i); particule_j != particules.end(); ++particule_j++) {
            rij = (*particule_j)->getPosition() - (*particule_i)->getPosition();
            norme_rij = rij.norme();
            f = rij * (*particule_i)->getMasse() * (*particule_j)->getMasse() / (pow(norme_rij, 3));
            (*particule_i)->update_force(f);
            (*particule_j)->update_force(-f);
        }
    }
}

template<int dim>
void Univers<dim>::compute_force_el() {
    Vecteur<dim> f, rij, dist_cell;
    double norme_rij, dist_cell_norme;
    double const val = 24 * epsilon;
    for (auto &cell: cellules) {
        for (auto &particule: cell.second->Particules) {
            for (auto &cellvoisin: cell.second->Voisins) {
                dist_cell = (particule->getPosition() - cellvoisin->centreCell);
                dist_cell_norme = rij.norme();
                if (dist_cell_norme <= rcut) {
                    for (auto particule_vois: cellvoisin->Particules) {
                        rij = (particule_vois->getPosition() - particule->getPosition());
                        norme_rij = rij.norme();
                        if (0 < norme_rij) {
                            double facteur1 = 1 / pow(norme_rij, 2);
                            double facteur2 = pow(sigma / norme_rij, 6);
                            double facteur3 = (1 - 2 * facteur2);
                            particule->update_force(val * facteur1 * facteur2 * facteur3 * rij);
                        }
                    }
                }
            }
        }
    }
}


template<int dim>
void Univers<dim>::visualiser_maillage() {
    std::ofstream output_file("maillage"); // Open the output file
    output_file << n_cells[0] << " " << n_cells[1] << " " <<  rcut << std::endl;
    double x_shift =  rcut*n_cells[0]/2;
    double y_shift =  rcut*n_cells[1]/2;
    for (int i=1; i<=n_cells[0] ; i++){
        for (int j=1; j<=n_cells[1]; j++){
            double x = (i - 1)*rcut - x_shift;
            double y = (j - 1 )*rcut - y_shift;
            output_file << x << " " << y << std::endl;
        }
    }
    output_file.close();
}




