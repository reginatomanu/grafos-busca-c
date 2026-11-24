// Aluna: Manuella Vieira Reginato                RA: a2767120

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6

// Nomes dos vertices (Pontos de Onibus - Cornelio Procopio)
const char *nomes[N] = {
    "Conjunto Sibim",
    "Jardim Panorama",
    "Conjunto Popular",
    "Jose B. Catarino",
    "Vitor Dantas",
    "Martha Dequech"
};

// Matriz de adjacencia do grafo
const int grafo[N][N] = {
    {0, 1, 1, 0, 0, 0}, // 0: Conjunto Sibim
    {1, 0, 1, 1, 0, 0}, // 1: Jardim Panorama
    {1, 1, 0, 0, 0, 0}, // 2: Conjunto Popular
    {0, 1, 0, 0, 0, 0}, // 3: Jose B. Catarino
    {0, 0, 0, 0, 0, 1}, // 4: Vitor Dantas
    {0, 0, 0, 0, 1, 0}  // 5: Martha Dequech
};

// ============================================================================
// ESTRUTURA DE FILA (Para a Busca em Largura - BFS)
// ============================================================================
typedef struct {
    int itens[N];
    int inicio;
    int fim;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == f->fim;
}

void enfileirar(Fila *f, int vertice) {
    if (f->fim < N) {
        f->itens[f->fim++] = vertice;
    }
}

int desenfileirar(Fila *f) {
    if (!filaVazia(f)) {
        return f->itens[f->inicio++];
    }
    return -1;
}

// ============================================================================
// ESTRUTURA PARA ARMAZENAR OS DADOS GERAIS DA BUSCA
// ============================================================================
typedef struct {
    int visitado[N];
    int ordemVisita[N];
    int caminho[N];
    int qtdVisitados;
    int qtdArestasPercorridas; // Transicoes para novos vertices
    int qtdArestasAnalisadas;  // Total de adjacencias verificadas
    int tamCaminho;
    int encontrado;
} ResultadoBusca;

void inicializarResultado(ResultadoBusca *res) {
    for (int i = 0; i < N; i++) {
        res->visitado[i] = 0;
        res->ordemVisita[i] = -1;
        res->caminho[i] = -1;
    }
    res->qtdVisitados = 0;
    res->qtdArestasPercorridas = 0;
    res->qtdArestasAnalisadas = 0;
    res->tamCaminho = 0;
    res->encontrado = 0;
}

// ============================================================================
// FUNCOES AUXILIARES DE EXIBICAO
// ============================================================================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarVertices() {
    printf("\n+------------------------------------------+\n");
    printf("|       VERTICES (PONTOS DE ONIBUS)        |\n");
    printf("+------------------------------------------+\n");
    for (int i = 0; i < N; i++) {
        printf("|  [%d] %-35s |\n", i, nomes[i]);
    }
    printf("+------------------------------------------+\n");
}

void mostrarGrafo() {
    mostrarVertices();
    printf("\n===== LISTA DE ADJACENCIAS (CONEXOES) =====\n");
    for (int i = 0; i < N; i++) {
        printf("[%d] %s se conecta com:\n", i, nomes[i]);
        int temConexao = 0;
        for (int j = 0; j < N; j++) {
            if (grafo[i][j] == 1) {
                printf("    -> [%d] %s\n", j, nomes[j]);
                temConexao = 1;
            }
        }
        if (!temConexao) {
            printf("    (Nenhuma conexao)\n");
        }
    }
}

void imprimirSequencia(const int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s", vetor[i], nomes[vetor[i]]);
        if (i < tamanho - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void exibirRelatorio(const char *nomeAlgoritmo, int origem, int destino, const ResultadoBusca *res) {
    printf("\n====================================================\n");
    printf("              RELATORIO DE BUSCA - %s\n", nomeAlgoritmo);
    printf("====================================================\n");
    printf("-> Vertice de origem               : [%d] %s\n", origem, nomes[origem]);

    if (destino != -1) {
        printf("-> Vertice de destino (Objetivo)   : [%d] %s\n", destino, nomes[destino]);
    } else {
        printf("-> Vertice de destino (Objetivo)   : Nao especificado (Exploracao total)\n");
    }

    printf("-> Quantidade de vertices visitados: %d\n", res->qtdVisitados);
    printf("-> Arestas percorridas (avancos)   : %d\n", res->qtdArestasPercorridas);
    printf("-> Arestas verificadas no grafo    : %d\n", res->qtdArestasAnalisadas);

    printf("\n-> Vertices visitados (Ordem de visita):\n   ");
    imprimirSequencia(res->ordemVisita, res->qtdVisitados);

    if (destino != -1) {
        printf("\n-> Status do objetivo              : ");
        if (res->encontrado) {
            printf("OBJETIVO ENCONTRADO!\n");
            printf("-> Caminho percorrido ate o destino (%d aresta(s)):\n   ",
                   res->tamCaminho - 1);
            imprimirSequencia(res->caminho, res->tamCaminho);
        } else {
            printf("OBJETIVO NAO ENCONTRADO (Vertice desconexo/inalcancavel).\n");
            printf("-> Caminho percorrido na tentativa :\n   ");
            imprimirSequencia(res->ordemVisita, res->qtdVisitados);
        }
    } else {
        printf("\n-> Caminho percorrido na busca:\n   ");
        imprimirSequencia(res->ordemVisita, res->qtdVisitados);
    }
    printf("====================================================\n");
}

// ============================================================================
// BUSCA EM PROFUNDIDADE (DFS) - RECURSIVA COM BACKTRACKING
// ============================================================================
void dfsRecursiva(int atual, int destino, ResultadoBusca *res) {
    // Marca o vertice atual como visitado e registra na ordem de visita
    res->visitado[atual] = 1;
    res->ordemVisita[res->qtdVisitados++] = atual;

    // Empilha o vertice no caminho atual
    res->caminho[res->tamCaminho++] = atual;

    // Verifica se atingiu o vertice objetivo
    if (destino != -1 && atual == destino) {
        res->encontrado = 1;
        return;
    }

    // Explora os vizinhos adjacentes
    for (int i = 0; i < N; i++) {
        if (grafo[atual][i] == 1) {
            res->qtdArestasAnalisadas++;

            if (!res->visitado[i]) {
                res->qtdArestasPercorridas++;
                printf("   [Avanco]       [%d] %s -> [%d] %s\n",
                       atual, nomes[atual], i, nomes[i]);

                dfsRecursiva(i, destino, res);

                // Se encontrou o objetivo na chamada recursiva, preserva o caminho e retorna
                if (res->encontrado) {
                    return;
                }

                // Caso nao tenha encontrado por esse ramo, exibe o retorno (Backtracking)
                printf("   [Backtracking] Retornando de [%d] %s para [%d] %s\n",
                       i, nomes[i], atual, nomes[atual]);
            }
        }
    }

    // Backtracking: remove o vertice atual do caminho, pois este ramo nao levou ao destino
    res->tamCaminho--;
}

void executarDFS(int origem, int destino) {
    ResultadoBusca res;
    inicializarResultado(&res);

    printf("\n--- Passo a passo da DFS (Recursao e Backtracking) ---\n");
    dfsRecursiva(origem, destino, &res);

    exibirRelatorio("DFS", origem, destino, &res);
}

// ============================================================================
// BUSCA EM LARGURA (BFS) - COM ESTRUTURA DE FILA
// ============================================================================
void executarBFS(int origem, int destino) {
    ResultadoBusca res;
    inicializarResultado(&res);

    Fila fila;
    inicializarFila(&fila);

    int pai[N];
    for (int i = 0; i < N; i++) {
        pai[i] = -1;
    }

    // Insere o vertice de origem na fila
    res.visitado[origem] = 1;
    enfileirar(&fila, origem);

    printf("\n--- Passo a passo da BFS (Processamento da Fila) ---\n");

    while (!filaVazia(&fila)) {
        int atual = desenfileirar(&fila);
        res.ordemVisita[res.qtdVisitados++] = atual;

        printf("   [Fila] Desenfileirou e visitou: [%d] %s\n", atual, nomes[atual]);

        // Verifica se encontrou o destino
        if (destino != -1 && atual == destino) {
            res.encontrado = 1;
            break;
        }

        // Percorre os vizinhos do vertice atual
        for (int i = 0; i < N; i++) {
            if (grafo[atual][i] == 1) {
                res.qtdArestasAnalisadas++;

                if (!res.visitado[i]) {
                    res.visitado[i] = 1;
                    pai[i] = atual;
                    res.qtdArestasPercorridas++;
                    enfileirar(&fila, i);

                    printf("          -> Enfileirou vizinho: [%d] %s\n", i, nomes[i]);
                }
            }
        }
    }

    // Reconstrucao do menor caminho da origem ao destino usando o vetor 'pai'
    if (destino != -1 && res.encontrado) {
        int temp[N];
        int tam = 0;
        int v = destino;

        while (v != -1) {
            temp[tam++] = v;
            v = pai[v];
        }

        // Inverte para ficar na ordem Origem -> Destino
        res.tamCaminho = tam;
        for (int i = 0; i < tam; i++) {
            res.caminho[i] = temp[tam - 1 - i];
        }
    }

    exibirRelatorio("BFS", origem, destino, &res);
}

// ============================================================================
// LEITURA SEGURA Dos VERTICES
// ============================================================================
int lerParametrosBusca(int *origem, int *destino) {
    mostrarVertices();

    printf("\nInforme o numero do vertice de ORIGEM (0 a %d): ", N - 1);
    if (scanf("%d", origem) != 1 || *origem < 0 || *origem >= N) {
        limparBuffer();
        printf("\n[ERRO] Vertice de origem invalido!\n");
        return 0;
    }

    printf("Informe o numero do vertice de DESTINO (0 a %d, ou -1 para percorrer tudo): ", N - 1);
    if (scanf("%d", destino) != 1 || *destino < -1 || *destino >= N) {
        limparBuffer();
        printf("\n[ERRO] Vertice de destino invalido!\n");
        return 0;
    }

    return 1;
}

// ============================================================================
// MENU INTERATIVO PRINCIPAL
// ============================================================================
int main() {
    int opcao;
    int origem, destino;

    do {
        printf("\n============================================\n");
        printf("      SISTEMA DE BUSCA EM GRAFOS (ONIBUS)\n");
        printf("           CORNELIO PROCOPIO - PR\n");
        printf("============================================\n");
        printf("  1 - Busca em Profundidade (DFS)\n");
        printf("  2 - Busca em Largura (BFS)\n");
        printf("  3 - Mostrar Vertices e Conexoes do Grafo\n");
        printf("  0 - Sair\n");
        printf("============================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                if (lerParametrosBusca(&origem, &destino)) {
                    executarDFS(origem, destino);
                }
                break;

            case 2:
                if (lerParametrosBusca(&origem, &destino)) {
                    executarBFS(origem, destino);
                }
                break;

            case 3:
                mostrarGrafo();
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
