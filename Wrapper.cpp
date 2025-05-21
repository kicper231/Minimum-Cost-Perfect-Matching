#include "Matching.h"
#include "Graph.h"

extern "C" __declspec(dllexport)
int SolveMinCostMatching(
    int nodeCount,
    int edgeCount,
    const int* edgeU,
    const int* edgeV,
    const double* costs,
    int* matchedPairsOut 
) {
    // Budujemy graf
    Graph G(nodeCount);
    for (int i = 0; i < edgeCount; ++i) {
        G.AddEdge(edgeU[i], edgeV[i]);
    }

    // Tworzymy solver
    Matching matcher(G);

    // Koszty muszą być przekazane jako wektor
    std::vector<double> costVec(costs, costs + edgeCount);

    // Uruchamiamy algorytm
    std::pair<std::list<int>, double> result;
    try {
        result = matcher.SolveMinimumCostPerfectMatching(costVec);
    } catch (const char* err) {
        return -1; // brak perfekcyjnego dopasowania
    }

    // Parsujemy krawędzie dopasowania i zapisujemy końce do matchedPairsOut
    const std::list<int>& matchedEdges = result.first;

    int i = 0;
    for (int edgeIdx : matchedEdges) {
        auto [u, v] = G.GetEdge(edgeIdx); // funkcja dostępna w Graph.h
        matchedPairsOut[i++] = u;
        matchedPairsOut[i++] = v;
    }

    // Zwracamy koszt dopasowania jako int (opcjonalnie: zwróć double przez dodatkowy argument)
    return static_cast<int>(result.second);
}
