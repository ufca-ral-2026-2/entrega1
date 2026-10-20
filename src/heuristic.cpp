#include "heuristic.h"
#include <cmath>
#include <limits>

void JeroslowWang::init(const FormulaInfo& f) {
    // TODO: inicializar score_ com tamanho 2 * (f.num_vars + 1)
    // Para cada cláusula c e cada literal l em c:
    //   score_[l] += pow(2.0, -(double)c.size())
}

Literal JeroslowWang::choose_literal(const std::vector<VarState>& assignment) {
    // TODO: percorrer score_ e retornar o literal com maior score
    // cuja variável ainda esteja UNSET em assignment.
    // Retornar -1 se não houver variável livre.
    return -1;
}