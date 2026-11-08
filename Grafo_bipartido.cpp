#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 101

// ATENÇÃO: O cálculo da complexidade deve incluir todo o código, inclusive a leitura do arquivo.
// Complexidade: O(n) + O(n^2) + O(n^2) + O(n^2) + O(n^2) = O(n^2)


char nome_arquivo[50], aux[MAX];								// proibido alterar esta linha
int opcao, tamanho, i, j, n, m, digrafo, matriz_adj[MAX][MAX];  // proibido alterar esta linha
// Declare variáveis globais a partir daqui.

int gp_vertice[MAX];                                      // Grupo de cada vértice: 0 ou 1 (-1 = sem grupo)

int pinta_vertices(int v, int gp) {                          // Busca em profundidade(DFS): pinta v e os vizinhos, retorna 0 se houver conflito
    int w;                                                      // Vizinho que está pra ser analisado
    gp_vertice[v] = gp;                                // Marca o grupo do vértice atual

    for (w = 1; w <= n; w++) {                                  // Percorre uma linha da matriz, O(n)
        if (matriz_adj[v][w] != 0 || matriz_adj[w][v] != 0) {   // Existe ligação entre v e w (qualquer sentido)
            if (gp_vertice[w] == -1) {                    // Vizinho ainda sem grupo
                if (pinta_vertices(w, 1 - gp) == 0)          // Desce a busca em profundidade(DFS) com o grupo oposto
                    return 0;                                   // Conflito encontrado mais abaixo
            } else if (gp_vertice[w] == gp) {          // Vizinho ou laço no mesmo grupo
                return 0;                                       // Deu conflito então não é bipartido
            }
        }
    }
    return 1;                                                   // nenhum conflito a partir deste vértice
}

void mostrar_gp(int gp, const char *titulo) {             // Imprime os vértices de um grupo, O(n)
    int v;                                                      // Serve pra contar os vértices
    printf("%s", titulo);                                       // Escreve o título do grupo
    for (v = 1; v <= n; v++) {                                  // Olha todos os vértices,O(n)
        if (gp_vertice[v] == gp)                       // Vértice que pertence ao grupo pedido
            printf("V%d ", v);                                  // Mostra o vértice
    }
    printf("\n");                                               // Quebra a linha
}

void executafuncao (){   										// é dentro desta função que o aluno deverá escrever seu código
    int v, bipartido = 1;                                       // v = contador; bipartido = 1 enquanto não houver conflito

    for (v = 1; v <= n; v++) {                                  // O(n)
        gp_vertice[v] = -1;                               // Os vértices não pertencem a nenhum grupo no começo
    }

    for (v = 1; v <= n && bipartido; v++) {                     // Uma busca em profundidade(DFS) por componente, O(n^2) no total
        if (gp_vertice[v] == -1) {                        // Vértice ainda não visitado
            bipartido = pinta_vertices(v, 0);                   // começa a busca em profundidade(DFS) com o grupo 0
        }
    }

    if (bipartido) {                                            // Nenhum conflito foi encontrado
        printf("SIM, o grafo e bipartido.\n");                  // Resposta positiva
        mostrar_gp(0, "Grupo 1: ");                          // Exibe o primeiro grupo
        mostrar_gp(1, "Grupo 2: ");                          // Exibe o segundo grupo
    } else {
        printf("NAO, o grafo nao e bipartido.\n");              // Resposta negativa
    }
}




int main() {
	opcao = 1;

    while(opcao != 0){
        inicio:
        tamanho = 0;
        m = 0;
        digrafo = 0;
        system("cls"); 
        fflush(stdin); 
        printf("Digite o nome do arquivo (sem o .txt): ");
        gets(nome_arquivo);
        FILE *arquivo; 
        strcat(nome_arquivo,".txt"); 
            
        if((arquivo = fopen(nome_arquivo,"r")) != NULL){
        	while(fgets(aux, MAX, arquivo)) { 
                   char *elemento; 
                   elemento = strtok(aux, " ");
                    while (elemento != NULL){
                        elemento = strtok(NULL, " "); 
                    }
                    tamanho = tamanho + 1; 
                }
                fclose(arquivo);
                
                printf ("\n --------------------------- MATRIZ DE ADJACÊNCIA ---------------------------\n");
                
                if((arquivo = fopen(nome_arquivo,"r")) != NULL){
                    printf("\n");
                    for(int i = 1; i <= tamanho; i++){
                        for(int j = 1; j <= tamanho; j++){
                            fscanf(arquivo, "%d", &matriz_adj[i][j]);
							printf("%3d ", matriz_adj[i][j]); 
                        }
                        printf("\n");
                    }
                }
                fclose(arquivo);
				n = tamanho;
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (matriz_adj[i][j] != matriz_adj[j][i]) {
							digrafo = 1;   // é dígrafo
						}
					}
				}
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (digrafo == 1 && matriz_adj[i][j] != 0) {
							m = m + 1;
						} 
						if (digrafo == 0 && matriz_adj[i][j] != 0 && i <= j) {
							m = m + 1;
						}
					}
				}
				
	          printf ("\nN = %d e M = %d \n \n",n,m);     
            } else {
                printf("\nErro ao abrir o arquivo/Erro ao localizar o arquivo\n\n");
                
            }
        	  
		executafuncao ();       
        printf("\nDigite 0 para sair ou qualquer outra coisa para continuar: ");
		scanf("%d", &opcao);
        
    }
    return 0;
}
