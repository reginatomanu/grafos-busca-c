# Sistema de Busca em Grafos: Pontos de Ônibus (Cornélio Procópio - PR)

Implementação em linguagem **C** de algoritmos de busca em grafos (**DFS** e **BFS**) aplicados a uma rede de pontos de ônibus de **Cornélio Procópio - PR**.

**Autora:** Manuella Vieira Reginato

---

## 📋 Sobre o Projeto

O sistema modela um grafo não-direcionado de $N = 6$ vértices utilizando uma **matriz de adjacência**, onde cada vértice representa um ponto de ônibus da cidade e as arestas indicam as conexões diretas entre eles.

### Vértices do Grafo

| Índice | Ponto de Ônibus | Conexões Diretas |
| :---: | :--- | :--- |
| `0` | Conjunto Sibim | `[1]` Jardim Panorama, `[2]` Conjunto Popular |
| `1` | Jardim Panorama | `[0]` Conjunto Sibim, `[2]` Conjunto Popular, `[3]` José B. Catarino |
| `2` | Conjunto Popular | `[0]` Conjunto Sibim, `[1]` Jardim Panorama |
| `3` | José B. Catarino | `[1]` Jardim Panorama |
| `4` | Vitor Dantas | `[5]` Martha Dequech |
| `5` | Martha Dequech | `[4]` Vitor Dantas |

> **Nota:** O grafo possui dois componentes conexos: `{0, 1, 2, 3}` e `{4, 5}`, permitindo demonstrar tanto buscas bem-sucedidas quanto casos em que o destino é inalcançável (vértice desconexo).

---

## 🚀 Funcionalidades

1. **Busca em Profundidade (DFS - *Depth-First Search*)**
   - Implementação recursiva com exibição passo a passo dos avanços e retornos (*backtracking*).
   - Registro da ordem de visita, quantidade de vértices visitados, arestas percorridas e arestas analisadas.
   - Reconstrução do caminho encontrado até o destino.

2. **Busca em Largura (BFS - *Breadth-First Search*)**
   - Implementação iterativa com estrutura de **Fila (FIFO)** própria.
   - Exibição detalhada do processamento da fila (enfileiramento e desenfileiramento).
   - Reconstrução do **menor caminho** (em número de arestas) entre origem e destino utilizando vetor de predecessores (`pai`).

3. **Visualização do Grafo**
   - Exibição da tabela de vértices e da lista completa de adjacências/conexões no terminal.

4. **Modo de Exploração Total ou Direcionada**
   - Permite informar um vértice de destino específico (`0` a `5`) ou `-1` para explorar todo o componente conexo a partir da origem.

---

## 🛠️ Como Compilar e Executar

Certifique-se de ter um compilador C instalado (como `gcc` ou `clang`).

```bash
# Compilar o programa
gcc grafo_busca.c -o grafo_busca

# Executar no Linux / macOS
./grafo_busca

# Executar no Windows (PowerShell / CMD)
.\grafo_busca.exe
```

---

## 📂 Estrutura do Repositório

- `grafo_busca.c` - Código-fonte completo contendo estruturas de dados (`Fila`, `ResultadoBusca`), algoritmos `DFS` e `BFS`, relatórios detalhados e menu interativo.
- `README.md` - Documentação do projeto.
