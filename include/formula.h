#pragma once
#include <vector>
#include <string>

// Um literal é uma variável (positiva ou negada).
// Convenção: variável x_i é representada por 2*i (positiva) e 2*i+1 (negada).
// Exemplo: x_1 = 2, ¬x_1 = 3, x_2 = 4, ¬x_2 = 5
using Literal  = int;
using Clause   = std::vector<Literal>;
using Formula  = std::vector<Clause>;

// Retorna a variável de um literal
inline int var(Literal l)     { return l >> 1; }

// Retorna o literal negado
inline Literal neg(Literal l) { return l ^ 1; }

// Retorna true se o literal é positivo
inline bool is_pos(Literal l) { return !(l & 1); }

// Número de variáveis e cláusulas da fórmula
struct FormulaInfo {
    int num_vars;
    int num_clauses;
    Formula clauses;
};