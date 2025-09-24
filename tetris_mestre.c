#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a estrutura para uma peça de Tetris.
typedef struct {
    char nome;
    int id;
} Peca;

// Define os tamanhos da fila e da pilha.
#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// --- Variáveis Globais ---

// Fila circular para as peças do jogo.
Peca fila[TAMANHO_FILA];
int frente = -1;
int tras = -1;

// Pilha para as peças reservadas.
Peca pilha[TAMANHO_PILHA];
int topo = -1;

// Contador para o ID único das peças.
int proximo_id = 0;

// --- Funções do Jogo ---

// Gera uma nova peça com tipo e ID aleatórios.
Peca gerarPeca() {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova_peca.nome = tipos[rand() % 4];
    nova_peca.id = proximo_id++;
    return nova_peca;
}

// Adiciona uma peça no final da fila.
void enqueue(Peca peca) {
    if ((tras + 1) % TAMANHO_FILA == frente) {
        // Fila cheia, não faz nada.
        return;
    }
    if (frente == -1) {
        frente = 0;
    }
    tras = (tras + 1) % TAMANHO_FILA;
    fila[tras] = peca;
}

// Remove uma peça da frente da fila.
Peca dequeue() {
    Peca peca_removida;
    if (frente == -1) {
        printf("\n--- A fila de pecas esta vazia! ---\n");
        peca_removida.id = -1; // Sinaliza erro.
    } else {
        peca_removida = fila[frente];
        if (frente == tras) {
            frente = -1;
            tras = -1;
        } else {
            frente = (frente + 1) % TAMANHO_FILA;
        }
    }
    return peca_removida;
}

// Adiciona uma peça no topo da pilha.
void push(Peca peca) {
    if (topo == TAMANHO_PILHA - 1) {
        printf("\n--- A pilha de reserva esta cheia! ---\n");
    } else {
        topo++;
        pilha[topo] = peca;
        printf("\n--- Peca [%c %d] reservada com sucesso! ---\n", peca.nome, peca.id);
    }
}

// Remove uma peça do topo da pilha.
Peca pop() {
    Peca peca_removida;
    if (topo == -1) {
        printf("\n--- A pilha de reserva esta vazia! ---\n");
        peca_removida.id = -1; // Sinaliza erro.
    } else {
        peca_removida = pilha[topo];
        topo--;
    }
    return peca_removida;
}

// Exibe o conteúdo da fila.
void exibirFila() {
    printf("Fila de pecas: ");
    if (frente == -1) {
        printf("vazia");
        return;
    }
    int i = frente;
    while (1) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        if (i == tras) {
            break;
        }
        i = (i + 1) % TAMANHO_FILA;
    }
}

// Exibe o conteúdo da pilha.
void exibirPilha() {
    printf("Pilha de reserva (Topo -> Base): ");
    if (topo == -1) {
        printf("vazia");
        return;
    }
    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
}

// Exibe o menu de opções.
void exibirMenu() {
    printf("\n\nOpcoes:\n\n");
    printf("1. Jogar peca da frente da fila\n");
    printf("2. Enviar peca da fila para a reserva (pilha)\n");
    printf("3. Usar peca da reserva (pilha)\n");
    printf("4. Trocar peca da frente da fila com o topo da pilha\n");
    printf("5. Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
    printf("0. Sair\n");
    printf("\nEscolha uma opcao: ");
}

// Inicializa a fila com as peças iniciais.
void inicializarFila() {
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(gerarPeca());
    }
}

// --- Funções de Troca ---

// Troca a peça da frente da fila com a do topo da pilha.
void trocarPecaUnica() {
    // Verifica se a fila e a pilha têm pelo menos uma peça.
    if (frente == -1 || topo == -1) {
        printf("\n--- Nao e possivel realizar a troca. Fila ou pilha vazias. ---\n");
        return;
    }

    Peca tempFila = fila[frente];
    fila[frente] = pilha[topo];
    pilha[topo] = tempFila;

    printf("\n--- Troca realizada entre a peca da fila e a do topo da pilha. ---\n");
}

// Troca as 3 primeiras peças da fila com as 3 da pilha.
void trocarPecaMultipla() {
    // Verifica se a fila e a pilha têm pelo menos 3 peças.
    int elementos_fila = (tras >= frente) ? (tras - frente + 1) : (TAMANHO_FILA - frente + tras + 1);
    if (elementos_fila < 3 || topo < 2) {
        printf("\n--- Nao e possivel realizar a troca. A fila ou a pilha nao tem 3 pecas. ---\n");
        return;
    }

    Peca tempFila[3];
    Peca tempPilha[3];

    // Guarda as 3 peças da fila em um array temporário.
    int i_fila = frente;
    for (int i = 0; i < 3; i++) {
        tempFila[i] = fila[i_fila];
        i_fila = (i_fila + 1) % TAMANHO_FILA;
    }

    // Guarda as 3 peças da pilha em um array temporário.
    int i_pilha = topo;
    for (int i = 0; i < 3; i++) {
        tempPilha[i] = pilha[i_pilha];
        i_pilha--;
    }

    // Troca as peças.
    i_fila = frente;
    for (int i = 0; i < 3; i++) {
        fila[i_fila] = tempPilha[i];
        i_fila = (i_fila + 1) % TAMANHO_FILA;
    }

    i_pilha = topo;
    for (int i = 0; i < 3; i++) {
        pilha[i_pilha] = tempFila[i];
        i_pilha--;
    }

    printf("\n--- Troca realizada entre os 3 primeiros da fila e os 3 da pilha. ---\n");
}

// --- Função Principal ---

int main() {
    srand(time(NULL));
    int opcao;

    inicializarFila();

    do {
        printf("\n=== Estado atual ===\n\n");
        exibirFila();
        printf("\n");
        exibirPilha();
        printf("\n");

        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça (dequeue da fila)
                Peca peca_jogada = dequeue();
                if (peca_jogada.id != -1) {
                    printf("\n--- Peca [%c %d] jogada com sucesso! ---\n", peca_jogada.nome, peca_jogada.id);
                    enqueue(gerarPeca()); // Mantém a fila cheia.
                }
                break;
            }
            case 2: { // Reservar peça (dequeue da fila e push na pilha)
                if (frente != -1) {
                    Peca peca_reservada = dequeue();
                    push(peca_reservada);
                    enqueue(gerarPeca()); // Mantém a fila cheia.
                } else {
                    printf("\n--- A fila de pecas esta vazia! Nao ha pecas para reservar. ---\n");
                }
                break;
            }
            case 3: { // Usar peça reservada (pop da pilha)
                Peca peca_usada = pop();
                if (peca_usada.id != -1) {
                    printf("\n--- Peca [%c %d] da reserva usada com sucesso! ---\n", peca_usada.nome, peca_usada.id);
                    enqueue(gerarPeca()); // Mantém a fila cheia.
                }
                break;
            }
            case 4: { // Trocar peça única
                trocarPecaUnica();
                break;
            }
            case 5: { // Trocar múltiplas peças
                trocarPecaMultipla();
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
