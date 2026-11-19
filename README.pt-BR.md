# Tree Balance Benchmark

[Inglês](README.md) | **Português**

Benchmark em C que compara o esforço computacional de árvores balanceadas na adição e na remoção de chaves, incluindo o trabalho de balanceamento, usando as mesmas chaves aleatórias para todas as estruturas.

As árvores comparadas são AVL, Rubro-Negra e Árvore B com ordens 1, 5 e 10.

## O que é medido

Para cada tamanho de conjunto, de 1 a 10.000 chaves, o programa mede o esforço de:

- **Adição:** inserir todas as chaves do conjunto em uma árvore vazia.
- **Remoção:** remover todas as chaves inseridas.

Cada tamanho é executado com 10 conjuntos aleatórios diferentes, e o resultado é a média das 10 execuções. As cinco árvores recebem o mesmo conjunto em cada execução.

### Esforço computacional

O esforço é um contador (`effort`, em `src/utils/`) incrementado em um a cada:

- iteração de laço dentro de uma adição ou remoção (descida na árvore, busca do sucessor ou predecessor, subida durante o balanceamento, deslocamento de chaves dentro de um nó da Árvore B);
- operação de balanceamento (rotações da AVL e da Rubro-Negra; split, merge e empréstimo da Árvore B; e cada nó visitado pela recursão da Árvore B).

### Chaves

As chaves são geradas com `rand() % (10 * n)`, onde `n` é o tamanho do conjunto. Chaves repetidas são ignoradas por todas as árvores.

## Resultados

![Esforço na adição](public/addition_effort.png)

![Esforço na remoção](public/removal_effort.png)

### Discussão

A tabela mostra o esforço médio no maior tamanho de conjunto (10.000 chaves) e o esforço por chave (total dividido por 10.000):

| Árvore | Adição | Por chave | Remoção | Por chave |
|---|---|---|---|---|
| Rubro-Negra | 135.012 | 13,5 | 124.727 | 12,5 |
| Árvore B ordem 5 | 212.626 | 21,3 | 221.211 | 22,1 |
| Árvore B ordem 10 | 236.045 | 23,6 | 256.772 | 25,7 |
| AVL | 241.491 | 24,1 | 221.105 | 22,1 |
| Árvore B ordem 1 | 250.678 | 25,1 | 252.201 | 25,2 |

**Crescimento.** Todas as curvas crescem como `n log n`: o esforço dividido por `n log₂ n` fica quase constante entre 1.000 e 10.000 chaves (por exemplo, 1,76 e 1,82 na adição da AVL). Isso confirma o custo `O(log n)` esperado para uma adição ou remoção numa árvore balanceada, repetido `n` vezes. Nenhuma estrutura degrada conforme o conjunto cresce; elas diferem por um fator constante.

**A Rubro-Negra é a mais barata nas duas operações**, com cerca de 55% do esforço da AVL. As duas árvores terminam com a mesma altura (cerca de 16 níveis para 10.000 chaves) e fazem uma quantidade parecida de rotações (AVL: 6.668 na adição; Rubro-Negra: 5.550). A diferença está no que acontece depois da alteração:

- A AVL implementada sobe do nó alterado até a raiz em toda operação, recalculando alturas e fatores de balanceamento: cerca de 11 passos por adição e 10 por remoção.
- A correção da Rubro-Negra só continua enquanto há conflito vermelho-vermelho ou falta de nó preto, o que normalmente termina em 1 passo: cerca de 0,9 passo por adição e 0,7 por remoção.

**A AVL é mais cara na adição do que na remoção** (24,1 contra 22,1 por chave). Nos dois casos ela sobe até a raiz, mas a adição faz quase o dobro de rotações (6.668 contra 3.811).

**Árvore B: a ordem troca altura por trabalho dentro do nó.**

- A ordem 1 (1 a 2 chaves por nó, uma árvore 2-3) é a mais alta, com 11 níveis, e a que mais faz splits (7.054) e correções de underflow (10.121). Seu esforço vai em descer níveis.
- A ordem 5 (5 a 10 chaves por nó) cai para 5 níveis e é a árvore B mais barata nas duas operações.
- A ordem 10 (10 a 20 chaves por nó) só cai para 4 níveis, mas cada adição ou remoção desloca o dobro de chaves dentro do nó, e cada split, merge ou empréstimo move o dobro de chaves. Esse trabalho extra supera o nível economizado: a ordem 10 fica acima da ordem 5 e, na remoção, é a mais cara de todas as árvores.

A busca binária dentro dos nós custa praticamente o mesmo em todas as ordens: menos níveis significam mais comparações por nó, e o total fica próximo de `log₂ n` por chave.

**Remoção x adição na árvore B.** A remoção é um pouco mais cara em todas as ordens, porque um underflow exige pegar emprestado ou fundir com um irmão, e remover uma chave de um nó interno exige encontrar antes o seu predecessor.

**AVL x árvore B ordem 5 na remoção.** As duas chegam praticamente ao mesmo esforço com 10.000 chaves (221.105 contra 221.211). As curvas se sobrepõem no gráfico de remoção, então nenhuma das duas é claramente melhor ali.

### Observações sobre os resultados

- **O esforço depende do critério de contagem.** Contar só comparações de chave, ou cada atribuição, mudaria as curvas. O critério usado está descrito em [Esforço computacional](#esforço-computacional).
- **O resultado da árvore B vale para memória.** Cada nó já está em memória, então deslocar chaves dentro dele tem custo real nesta contagem. Em disco, o custo dominante é ler cada nó, e mover chaves dentro de um nó já lido é quase de graça. Por esse critério, uma ordem maior venceria, por ter menos níveis.
- **Implementação da AVL.** Esta AVL sempre sobe até a raiz. Uma implementação que pare assim que a altura de um nó não mudar reduziria seu esforço, principalmente na adição.
- **Chaves repetidas.** As chaves vêm de `rand() % (10 * n)`, então cerca de 5% delas se repetem. Todas as árvores ignoram chaves repetidas, então as cinco processam o mesmo conjunto.

## Requisitos

- GCC
- Make
- Python 3 (apenas para os gráficos)

## Como compilar e executar

Para compilar:

```bash
make compilation
```

Para compilar e executar:

```bash
make run
```

O programa roda sem nenhuma entrada e mostra o progresso a cada 500 tamanhos. Cada execução cria um novo arquivo `src/results/results_<data>_<hora>.csv` (ignorado pelo git), com uma linha por tamanho de conjunto:

```
dataset_size,avl_add,red_black_add,btree_1_add,btree_5_add,btree_10_add,avl_remove,red_black_remove,btree_1_remove,btree_5_remove,btree_10_remove
```

## Gráficos

Para gerar os gráficos a partir do arquivo de resultados mais recente:

```bash
make plot
```

Na primeira execução, o comando cria um ambiente virtual Python (`.venv`) e instala `pandas` e `matplotlib` a partir do `requirements.txt`. O script `scripts/plot_results.py` lê o `src/results/results_*.csv` mais recente e sobrescreve `public/addition_effort.png` e `public/removal_effort.png`, então as imagens da seção Resultados estão sempre atualizadas.

## Estrutura do projeto

```
.
├── makefile
├── requirements.txt           # Dependências Python dos gráficos
├── public/                    # Gráficos usados no README
├── scripts/
│   └── plot_results.py        # Gera os gráficos
└── src
    ├── results/               # Resultados (CSV)
    ├── main.c                 # Fluxo principal do benchmark
    ├── trees
    │   ├── avl/               # Árvore AVL
    │   ├── red_black/         # Árvore Rubro-Negra
    │   └── btree/             # Árvore B
    └── utils/                 # Chaves aleatórias e contador de esforço
```

## Participantes

- [Ruan Carlos da Silva](https://github.com/ruansilva123)
- [Guilherme Becker](https://github.com/GuiBecko)
- [Pedro Henrique Urio dos Santos](https://github.com/pedrourio)
- [Vitor Rafael Marcelino](https://github.com/vitorrmarcelino)
