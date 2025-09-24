#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a estrutura para uma peça de Tetris, com nome e id.

typedef struct {
    char nome;
    int id;
} Peca;

#define TAMANHO_FILA 5

// --- Variáveis para a Fila ---

Peca fila[TAMANHO_FILA];
int frente = -1; 
int tras = -1; 
int proximo_id = 0; 

// --- Funções de Manipulação da Fila ---

// Gera uma nova peça com um tipo aleatório ('I', 'O', 'T', 'L') e um ID exclusivo.
// Retorna a peça gerada.

Peca gerarPeca() {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova_peca.nome = tipos[rand() % 4];
    nova_peca.id = proximo_id++;
    return nova_peca;
}

// Insere uma peça no final da fila (enqueue).

void enqueue(Peca peca) {
    // A fila está cheia se o próximo espaço de 'tras' for a 'frente'.
    if ((tras + 1) % TAMANHO_FILA == frente) {
        printf("\n--- A fila de pecas esta cheia! Nao e possivel adicionar. ---\n");
    } else {
        // Se a fila está vazia, a frente e o final são o mesmo.
        if (frente == -1) {
            frente = 0;
        }
        tras = (tras + 1) % TAMANHO_FILA;
        fila[tras] = peca;
    }
}

/**
 * Remove a peça da frente da fila (dequeue).
 * Retorna a peça removida. Se a fila estiver vazia, retorna
 * uma peça com ID -1 para indicar falha.
 */
Peca dequeue() {
    Peca peca_removida;
    // A fila está vazia se a 'frente' for -1.
    if (frente == -1) {
        printf("\n--- A fila de pecas esta vazia! Nao ha pecas para jogar. ---\n");
        peca_removida.id = -1; // Sinaliza erro.
    } else {
        peca_removida = fila[frente];
        // Se a fila tiver apenas um item, ela ficará vazia após a remoção.
        if (frente == tras) {
            frente = -1;
            tras = -1;
        } else {
            frente = (frente + 1) % TAMANHO_FILA;
        }
    }
    return peca_removida;
}

//Exibe o estado atual da fila de peças.

void exibirFila() {
    printf("\n--- Confira as pecas: ---\n\n");
    printf("Fila de pecas: ");

    if (frente == -1) {
        printf("vazia\n");
        return;
    }

    int i = frente;
    // Loop para imprimir os elementos da fila circular.
    while (1) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        if (i == tras) {
            break;
        }
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// Exibe o menu de opções para o usuário.

void exibirMenu() {
    printf("\nEscolha de acao:\n\n");
    printf("1. Jogar peca\n");
    printf("2. Inserir nova peca\n");
    printf("0. Sair\n");
    printf("\nDigite sua escolha: ");
}

//Inicializa a fila com 5 peças geradas automaticamente.
 
void inicializarFila() {
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(gerarPeca());
    }
}

// --- Função Principal ---

int main() {
    srand(time(NULL));
    int opcao;

    inicializarFila();
    
    do {
        exibirFila();
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça
                Peca peca_jogada = dequeue();
                if (peca_jogada.id != -1) {
                    printf("\n--- Peca [%c %d] jogada com sucesso! ---\n", peca_jogada.nome, peca_jogada.id);
                }
                break;
            }
            case 2: { // Inserir nova peça
                Peca nova_peca = gerarPeca();
                enqueue(nova_peca);
                if ((tras + 1) % TAMANHO_FILA != frente) {
                     printf("\n--- Nova peca [%c %d] inserida com sucesso. ---\n", nova_peca.nome, nova_peca.id);
                }
                break;
            }
            case 0: // Sair do programa
                printf("\n--- Saindo do simulador. Ate mais! ---\n");
                break;
            default:
                printf("\n--- Opcao invalida. Por favor, tente novamente. ---\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
