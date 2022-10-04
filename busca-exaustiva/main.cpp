// Metodologia de busca exaustiva para solucao do problema do caixeiro viajante
// Autor: Rafael Malcervelli
// Email: rafaelsm9@al.insper.edu.br
// Referencias: https://en.cppreference.com/w/cpp/algorithm/next_permutation
//              https://www.geeksforgeeks.org/next_permutation-in-cpp-stl/
//              https://www.programiz.com/cpp-programming/examples/factorial 


#include <iostream>
#include <vector>
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

struct result {
    vector <City> cities_best;
    double total_distance;
    long int counter;
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

// Funcao para realizr a busca exaustiva
result busca_exaustiva(vector <City> cities, vector <City> cities_aux, vector <City> cities_best, vector <int> idxs, double &total_distance_aux, double &total_distance, long int &count, int n) {

    do {
        for (int i = 0; i < n; i++) {
            cities_aux[i] = cities[idxs[i]];
        }

        // Calcula a distancia total da rota atual
        total_distance_aux = calc_total_distance(cities_aux);

        // Verifica se a distancia atual eh menor que a distancia total
        if (total_distance_aux < total_distance) {
            count ++;
            total_distance = total_distance_aux;
            cities_best = cities_aux;
        }

    } while (next_permutation(idxs.begin(), idxs.end()));

    return result {cities_best, total_distance, count};
}

int main() {
    // Quantidade de cidades
    int n;
    cin >> n;

    // Atribuicao das cidades e suas coordenadas
    vector<City> cities;

    // Atribuicao de indices das cidades para realizar a busca exaustiva
    // (nao tem como realizar std::next_permutation com um vector de structs)) 
    vector<int> idxs;

    // Inicializacao das distancias
    double total_distance = 0;
    double total_distance_aux = 0;

    for (int i = 0; i < n; i++) {
        City city;
        cin >> city.x;
        cin >> city.y;
        city.idx = i;

        // Adiciona no vetor de indices 
        idxs.push_back(i);

        // Adiciona no vetor de cidades
        cities.push_back(city);
    }

    vector <City> cities_aux = cities;
    vector <City> cities_best = cities;

    // ======================== Busca Exaustiva ========================
    // Distancia total inicial
    total_distance = calc_total_distance(cities);  
    
    // Calculando o numero de folhas da arvore error
    long int count = 0;

    // Calculando o fatorial
    long int n_factorial = 1;
    for (int i = 1; i <= n; i++) {
        n_factorial *= i;
    }
    
    // Ordenando o vetor de indices
    sort(idxs.begin(), idxs.end());

    // Realiza a busca exaustiva
    auto [cities_best_res, total_distance_res, count_res] = busca_exaustiva(cities, cities_aux, cities_best, idxs, total_distance_aux, total_distance, count, n);

    // ======================== Error ========================
    cerr << "num_leaf " << count_res << endl;

    // ======================== Resultado ========================
    cout << total_distance_res << " 1" << endl;
    for (int i = 0; i < n; i++) {
        cout << cities_best_res[i].idx << " ";
    }
    cout << endl;
}