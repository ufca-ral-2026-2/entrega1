#pragma once
#include "formula.h"
#include <vector>

// Estado de valoração de cada variável.
enum class VarState { UNSET, TRUE, FALSE };

// Interface de heurística de decisão.
// O solver consulta choose_literal() sempre que precisa tomar uma decisão.
class Heuristic {
public:
    virtual ~Heuristic() = default;

    // Inicializa a heurística com a fórmula original.
    virtual void init(const FormulaInfo& f) = 0;

    // Retorna o próximo literal a ser decidido,
    // dado o estado atual de valoração das variáveis.
    // Retorna -1 se todas as variáveis já estão valoradas.
    virtual Literal choose_literal(const std::vector<VarState>& assignment) = 0;

    // Notifica a heurística que uma variável foi valorada
    // (por decisão ou por propagação).
    virtual void notify_assigned(Literal l) {}

    // Notifica a heurística que uma variável foi desfeita (backtrack).
    virtual void notify_unassigned(int var) {}
};

// Heurística estática: Jeroslow-Wang (one-sided).
// Prioriza literais que ocorrem mais em cláusulas menores.
// score(l) = sum_{c contendo l} 2^{-|c|}
class JeroslowWang : public Heuristic {
public:
    void init(const FormulaInfo& f) override;
    Literal choose_literal(const std::vector<VarState>& assignment) override;

private:
    std::vector<double> score_; // score_[literal]
};