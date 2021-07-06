#include <fstream>
#include <string>
#include <vector>

#include "setup.h"
#include "ortools/linear_solver/linear_solver.h"
#include "ortools/linear_solver/linear_solver.pb.h"

using namespace operations_research;

void dieta_frutas()
{
    const std::vector<std::pair<std::string, double>> TabelaNutrientes {
        {"Vitamin A (1000 IU)",3000},
        {"Vitamin C (mg)",50}
    };

    const std::vector<std::pair<std::string, double>> TabelaAlimentos {
        {"Abacaxi.", 1.50},
        {"Banana.", 2.00},
        {"Maçã.", 3.00},
        {"Melãncia.", 0.80}
    };

    const std::vector<std::vector<double>> TabelaNutricional {
        { 7000, 550},
        { 8000, 300},
        { 30000, 400},
        { 6000, 250}
    };

    MPSolver solver("DietaStigler", MPSolver::GLOP_LINEAR_PROGRAMMING);

    auto N = TabelaAlimentos.size();
    std::vector<MPVariable*> x(N);
    for (int j=0; j < N; j++) 
        x[j] = solver.MakeNumVar(0.0, 1, TabelaAlimentos[j].first);

    auto M = TabelaNutrientes.size();
    std::vector<MPConstraint*> a(M);
    for (int i=0; i < M; i++) {
        a[i] = solver.MakeRowConstraint(TabelaNutrientes[i].second, solver.infinity());
        for (int j=0; j < N; j++)
            a[i]->SetCoefficient(x[j], TabelaNutricional[j][i]);
    }

    auto const objective = solver.MutableObjective();
    for(int j=0; j < N; j++) 
        objective->SetCoefficient(x[j], TabelaAlimentos[j].second);
        objective->SetMinimization();

    auto status = solver.Solve();

    if (status == MPSolver::OPTIMAL) {
        // Display the amounts (in dollars) to purchase of each food.
        auto price = 0.0;

        std::vector<double> nutrientes(M);
        for (int j=0; j < N; j++){
            price += x[j]->solution_value();

            for (int i = 0; i < M; i++)
                nutrientes[i] += TabelaNutricional[j][i] * x[j]->solution_value();

            if (x[j]->solution_value() > 0.0)
                std::cout << TabelaAlimentos[j].first << " = " << x[j]->solution_value() << std::endl;
        }
        std::cout << "Optimal daily price: " << (price) << std::endl;

            for (int i=0; i < M; i++){
                std::cout << TabelaNutrientes[i].first << nutrientes[i] << std::endl;
            }
    } 
    else if (status == MPSolver::FEASIBLE) // No optimal solution was found.
      std::cout << "A potentially suboptimal solution was found.";
    else
      std::cout << "The solver could not solve the problem.";
    
}