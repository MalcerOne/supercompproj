// Metodologia de busca local utilizando paralelismo com a biblioteca OpenMP para solucao do problema do caixeiro viajante
// Autor: Rafael Malcervelli
// Email: rafaelsm9@al.insper.edu.br

#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <cmath>
#include <random>


using namespace std;

// ======================== Struct ========================
// Estrutura da cidade
struct City {
    int idx;
    double x;
    double y;
};

// ======================== Funcoes ========================
// Funcao para calcular a distancia entre duas cidades
double calc_distance(City a, City b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Funcao para calcular a distancia total percorrida
double calc_total_distance(vector<City> cities) {
    double total_distance = 0;

    for (int i = 0; i < (int) cities.size() - 1; i++) {
        total_distance += calc_distance(cities[i], cities[i + 1]);
    }

    total_distance += calc_distance(cities[cities.size() - 1], cities[0]);

    return total_distance;
}

int main() {
    // Quantidade de cidades
    int n;
    cin >> n;

    // Atribuicao das cidades e suas coordenadas
    vector<City> cities, best_cities;
    double total_distance = 0;
    double total_distance_aux = 0;

    for (int i = 0; i < n; i++) {
        City city;
        cin >> city.x;
        cin >> city.y;
        city.idx = i;

        cities.push_back(city);
    }

    double best_distance = calc_total_distance(cities);

    // Geracao de numero aleatorio
    srand(unsigned(time(0)));

    // Utilizando OpenMP para palalelizar as operacoes na busca local
    #pragma omp parallel for
        // ======================== Busca Local ========================
        for (int i = 0; i < (10 * n); i++) {
            // Geracao de numero aleatorio
            random_shuffle(cities.begin(), cities.end());

            // Calculo da distancia total
            total_distance = calc_total_distance(cities);

            for (int main_vector_idx = 0; main_vector_idx < (int) cities.size(); main_vector_idx++) {
                for (int aux_vector_idx = main_vector_idx + 1; aux_vector_idx < (int) cities.size(); aux_vector_idx++) {
                    if (main_vector_idx != aux_vector_idx) {
                        // Troca de posicao das cidades
                        vector<City> cities_aux = cities;
                        swap(cities_aux[main_vector_idx], cities_aux[aux_vector_idx]);

                        // Calculo da distancia total com base na troca realizada
                        total_distance_aux = calc_total_distance(cities_aux);

                            // Verificacao se a distancia total e menor
                            if (total_distance_aux < total_distance) {
                                cities = cities_aux;
                                total_distance = total_distance_aux;
                            } else {
                                swap(cities_aux[main_vector_idx], cities_aux[aux_vector_idx]);
                            }
                    }
                }
            }

            // Verificacao se a distancia total e menor
            #pragma omp critical
                if (total_distance < best_distance) {
                    cout << "Melhor distancia: " << total_distance << endl;
                    best_distance = total_distance;
                    best_cities = cities;
                }

            // Error
            cerr << "local: " << total_distance << " ";
            // Imprime a sequencia de cidades
            for (int i = 0; i < (int) cities.size(); i++) {
                cerr << cities[i].idx << " ";
            }
            cerr << endl;
        }

    // ======================== Resultado ========================
    cout << best_distance << " 0" << endl;
    for (int i = 0; i < (int) best_cities.size(); i++) {
        cout << best_cities[i].idx << " ";
    }
    cout << endl;
    
    return 0;
}