// Metodologia heuristica para solucao do problema do caixeiro viajante
// Autor: Rafael Malcervelli
// Email: rafaelsm9@al.insper.edu.br

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

// Funcao para calcular cidade proxima
City closest_city(vector<City> cities, City currentCity) {
    double minDistance = 10000000000;
    double dist;
    City closerCity;

    for (int i = 0; i < (int) cities.size(); i++) {
        if (cities[i].idx != currentCity.idx) {
            // Se a cidade iterada for diferente da cidade atual, calcula a distancia.
            dist = calc_distance(currentCity, cities[i]);

            if (dist < minDistance) {
                minDistance = dist;
                closerCity = cities[i];
            }
        }
    }
    return closerCity;
}

// Funcao main
int main() {
    // Quantidade de cidades
    int n;
    cin >> n;

    // Atribuicao das cidades e suas coordenadas
    vector<City> cities;
    for (int i = 0; i < n; i++) {
        City city;
        cin >> city.x;
        cin >> city.y;
        city.idx = i;

        cities.push_back(city);
    }

    // Inicializando variaveis
    City currentCity = cities[0];
    vector<City> path;
    double totalDistance = 0;
    int count = 0;

    path.push_back(currentCity); // Adiciona a primeira cidade ao caminho
        
    // Enquanto o caminho nao tiver todas as cidades
    while ((int) path.size() < n) {
        count ++;

        // Remove primeira cidade da iteracao. 
        if (count == 1){
            cities.erase(cities.begin());
        }

        // Encontra a cidade mais proxima
        City closerCity = closest_city(cities, currentCity);
        
        // Remove a cidade mais proxima do vetor de cidades
        for (int i = 0; i < (int) cities.size(); i++) {
            if (cities[i].idx == closerCity.idx) {
                cities.erase(cities.begin() + i);
            }
        }

        // Adiciona a cidade mais proxima ao caminho
        path.push_back(closerCity);

        // Calcula a distancia entre a cidade atual e a cidade mais proxima
        totalDistance += calc_distance(currentCity, closerCity);

        // Atualiza a cidade atual
        currentCity = closerCity;
    }

    // Calcula a distancia entre a ultima cidade e a primeira
    totalDistance += calc_distance(currentCity, path[0]);

    // Imprime a distancia total
    cout << totalDistance << " " << "0" << endl;

    // Imprime o caminho e a distancia total
    for (int i = 0; i < (int) path.size(); i++) {
        cout << path[i].idx << " ";
    }
    cout << endl;
}