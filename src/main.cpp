#include "parser.h"
#include "solver.h"
#include "heuristic.h"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: dpll <arquivo.cnf>\n";
        return 1;
    }

    FormulaInfo f = parse_dimacs(argv[1]);

    auto heuristic = std::make_unique<JeroslowWang>();
    DPLLSolver solver(f, std::move(heuristic));

    Result result = solver.solve();

    if (result == Result::SAT) {
        std::cout << "SAT\n";
        const auto& assignment = solver.get_assignment();
        for (int i = 1; i <= f.num_vars; ++i) {
            int val = (assignment[i] == VarState::TRUE) ? i : -i;
            std::cout << val << " ";
        }
        std::cout << "0\n";
    } else {
        std::cout << "UNSAT\n";
    }

    return 0;
}