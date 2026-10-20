#pragma once
#include "formula.h"
#include <string>

// Lê uma fórmula no formato DIMACS CNF.
// Formato esperado:
//   c comentário (ignorado)
//   p cnf <num_vars> <num_clauses>
//   <lit1> <lit2> ... 0   (uma cláusula por linha, terminada por 0)
// Literais negativos são representados por inteiros negativos no DIMACS
// e convertidos para a convenção interna (2*i / 2*i+1) pelo parser.
//
// Lança std::runtime_error em caso de formato inválido.
FormulaInfo parse_dimacs(const std::string& filename);