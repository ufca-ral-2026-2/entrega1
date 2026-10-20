#pragma once
#include "formula.h"
#include "heuristic.h"
#include <vector>
#include <memory>

// Resultado do solver
enum class Result { SAT, UNSAT };

// Watched literals: cada cláusula observa dois literais.
// Quando um literal observado é falsificado, o solver
// procura um novo literal para observar.
struct WatchedClause {
    Clause literals;
    int watch1; // índice do 1º literal observado
    int watch2; // índice do 2º literal observado
};

class DPLLSolver {
public:
    explicit DPLLSolver(const FormulaInfo& f,
                        std::unique_ptr<Heuristic> heuristic);

    // Resolve a fórmula. Retorna SAT ou UNSAT.
    Result solve();

    // Se solve() retornou SAT, retorna a valoração.
    // assignment[i] == VarState::TRUE  => x_{i} é verdadeiro
    // assignment[i] == VarState::FALSE => x_{i} é falso
    const std::vector<VarState>& get_assignment() const;

private:
    // Boolean Constraint Propagation via watched literals.
    // Retorna true se não há conflito, false se há.
    bool bcp();

    // Desfaz a última decisão (backtrack cronológico).
    void backtrack();

    // Aplica uma valoração ao literal l, registrando o nível de decisão.
    void assign(Literal l, int level);

    // Desfaz a valoração do literal l.
    void unassign(Literal l);

    // Dados internos
    int num_vars_;
    std::vector<WatchedClause> clauses_;
    std::vector<VarState> assignment_;
    std::vector<int>      decision_level_; // nível de decisão por variável
    std::vector<Literal>  trail_;          // sequência de literais valorados
    std::vector<int>      trail_lim_;      // índices no trail por nível de decisão

    // Listas de observação: watches_[literal] = índices das cláusulas que observam esse literal
    std::vector<std::vector<int>> watches_;

    std::unique_ptr<Heuristic> heuristic_;
};