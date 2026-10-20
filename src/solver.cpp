#include "solver.h"
#include <stdexcept>

DPLLSolver::DPLLSolver(const FormulaInfo& f,
                       std::unique_ptr<Heuristic> heuristic)
    : num_vars_(f.num_vars), heuristic_(std::move(heuristic))
{
    heuristic_->init(f); // já fornecido: a heurística recebe a fórmula original

    // TODO: inicializar assignment_ e decision_level_ com tamanho num_vars_ + 1
    //       (variáveis indexadas de 1; a posição 0 não é usada)
    //       e watches_ com tamanho 2 * (num_vars_ + 1) (um slot por literal)
    // Para cada cláusula em f.clauses, criar um WatchedClause
    // com watch1=0 e watch2=1 (ou cláusula unitária: watch1=watch2=0)
    // e registrar nas listas watches_
}

Result DPLLSolver::solve() {
    // TODO (antes do laço): propagar as cláusulas unitárias da entrada
    //   (watch1 == watch2 == 0) no nível 0 — o bcp() só é disparado por
    //   literais falsificados, então elas não seriam vistas sozinhas.
    //   Se duas unitárias forem contraditórias: retornar UNSAT.

    while (true) {
        // TODO:
        // 1. Chamar bcp(). Se retornar false (conflito):
        //    - Se estamos no nível 0: retornar UNSAT
        //    - Senão: backtrack() e continuar
        // 2. Escolher próximo literal via heuristic_->choose_literal(assignment_)
        // 3. Se -1: todas variáveis valoradas → retornar SAT
        // 4. Senão: registrar novo nível de decisão e assign(literal, nivel)
    }
}

bool DPLLSolver::bcp() {
    // TODO: implementar BCP via watched literals.
    // Para cada literal falsificado recentemente no trail_:
    //   percorrer watches_[neg(l)] e para cada cláusula observada:
    //     - Se a cláusula já tem outro literal verdadeiro: ok
    //     - Se há literal livre: atualizar watch, mover para watches_ do novo literal
    //     - Se cláusula unitária: propagar (assign o literal restante)
    //     - Se conflito (todos falsos): retornar false
    // Retornar true se nenhum conflito
    return false;
}

void DPLLSolver::assign(Literal l, int level) {
    // TODO: marcar assignment_[var(l)], registrar decision_level_[var(l)] = level
    // Adicionar l ao trail_, notificar heurística
}

void DPLLSolver::unassign(Literal l) {
    // TODO: reverter assignment_[var(l)] para UNSET
    // Notificar heurística
}

void DPLLSolver::backtrack() {
    // TODO: desfazer todas as valorações do último nível de decisão
    // usando trail_ e trail_lim_ (o literal de decisão é trail_[trail_lim_.back()]).
    // Em seguida, valorar a NEGAÇÃO desse literal de decisão no nível anterior
    // (como implicação, não como nova decisão). Sem essa inversão, a heurística
    // escolheria o mesmo literal de novo e o solver entraria em laço infinito.
}

const std::vector<VarState>& DPLLSolver::get_assignment() const {
    return assignment_;
}