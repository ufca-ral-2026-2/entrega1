#include "parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

FormulaInfo parse_dimacs(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Não foi possível abrir o arquivo: " + filename);

    FormulaInfo info;
    info.num_vars    = 0;
    info.num_clauses = 0;

    std::string line;
    bool header_found = false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Comentários
        if (line[0] == 'c') continue;

        // Cabeçalho: p cnf <num_vars> <num_clauses>
        if (line[0] == 'p') {
            std::istringstream iss(line);
            std::string p, cnf;
            iss >> p >> cnf >> info.num_vars >> info.num_clauses;
            if (cnf != "cnf")
                throw std::runtime_error("Formato inválido: esperado 'p cnf'");
            header_found = true;
            continue;
        }

        if (!header_found)
            throw std::runtime_error("Cláusula encontrada antes do cabeçalho");

        // Cláusula: sequência de inteiros terminada por 0
        std::istringstream iss(line);
        Clause clause;
        int dimacs_lit;
        while (iss >> dimacs_lit) {
            if (dimacs_lit == 0) break;
            // Converte para convenção interna: var = |l|, sinal pelo bit 0
            int v = std::abs(dimacs_lit); // variáveis indexadas de 1 (x_1, ..., x_n)
            Literal l = (dimacs_lit > 0) ? 2 * v : 2 * v + 1;
            clause.push_back(l);
        }
        if (!clause.empty())
            info.clauses.push_back(clause);
    }

    return info;
}