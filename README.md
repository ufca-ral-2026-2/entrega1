# Entrega 1 — DPLL com Watched Literals

Disciplina: Raciocínio Automatizado via Lógica  
Professor: Luis Henrique Bustamante de Morais  
UFCA — Ciência da Computação

**Prazo: sábado, 14/11/2026.** Será avaliado o último commit na branch
`main` do seu repositório até o fim desse dia.

---

## Como começar

> **Não faça fork deste repositório.** Forks de repositórios públicos são
> públicos, e o seu código ficaria visível para toda a turma.

1. Nesta página, clique em **Use this template → Create a new repository**.
2. Em *Owner*, escolha a sua conta. Dê o nome `ral-solver-<sua-matrícula>`.
3. Marque **Private** e clique em **Create repository**.
4. No seu repositório: **Settings → Collaborators → Add people** e adicione
   o usuário `bustamante` (o professor).
5. Clone o seu repositório e trabalhe nele:
   ```bash
   git clone https://github.com/<seu-usuario>/ral-solver-<sua-matrícula>.git
   ```

As entregas seguintes (CDCL e CDCL(T)) estendem este mesmo código, então continue usando o mesmo repositório até o fim da disciplina.

---

## Objetivo

Implementar o algoritmo DPLL com as seguintes funcionalidades:

- **Watched literals**: representação eficiente de cláusulas para BCP
- **BCP** (Boolean Constraint Propagation): propagação unitária via watched literals
- **Heurística de decisão estática**: Jeroslow-Wang
- **Backtracking cronológico**
- **Parser DIMACS**: já implementado em `src/parser.cpp`

---

## O que você deve implementar

Os arquivos que você deve preencher estão em `src/`:

| Arquivo | O que implementar |
|---|---|
| `src/solver.cpp` | Construtor, `solve()`, `bcp()`, `assign()`, `unassign()`, `backtrack()` |
| `src/heuristic.cpp` | `JeroslowWang::init()` e `JeroslowWang::choose_literal()` |
| `src/formula.cpp` | Funções auxiliares opcionais |

Leia com atenção os comentários `// TODO` em cada arquivo — eles descrevem
exatamente o que cada função deve fazer.

**Não modifique** os headers em `include/` nem o `src/main.cpp`.

---

## Compilando

```bash
mkdir build && cd build
cmake ..
make
```

O executável gerado será `build/dpll`.

---

## Executando

```bash
./build/dpll caminho/para/instancia.cnf
```

### Formato de saída

Se satisfatível:

SAT
1 -2 3 0

A segunda linha lista os literais da valoração (positivo = verdadeiro,
negativo = falso), terminada por 0. Um literal por variável, na ordem
x_1, x_2, ..., x_n.

Se insatisfatível:

UNSAT

---

## Testando

A pasta `tests/` contém instâncias no formato DIMACS CNF:

- `tests/sat/` — instâncias satisfatíveis (a saída correta começa com `SAT`)
- `tests/unsat/` — instâncias insatisfatíveis (a saída correta é `UNSAT`)

| Arquivo | Resultado | Observação |
|---|---|---|
| `tests/sat/exemplo.cnf` | SAT | 3 variáveis, 3 cláusulas |
| `tests/sat/unitarias.cnf` | SAT | cláusulas unitárias na entrada |
| `tests/unsat/exemplo.cnf` | UNSAT | `x1` e `¬x1` |
| `tests/unsat/pombos-3-2.cnf` | UNSAT | casa dos pombos: 3 pombos, 2 casas |
| `tests/unsat/completa-3.cnf` | UNSAT | as 8 valorações de 3 variáveis proibidas |

Para instâncias maiores, use os benchmarks da SATLIB (ex.: `uf20-91`, `uuf50-218`):
<https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html>

Para testar manualmente:
```bash
./build/dpll tests/sat/exemplo.cnf
./build/dpll tests/unsat/exemplo.cnf
```

---

## Referência

- Kroening & Strichman. *Decision Procedures*, cap. 2. Springer, 2016.
- Seções 2.2.2 (CDCL Framework), 2.2.3 (BCP e grafo de implicação),
  2.2.5 (heurísticas de decisão).