// Define os tamanhos da fila e da pilha.
#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// --- Variáveis para a Fila ---

// Array que armazena as peças da fila.
Peca fila[TAMANHO_FILA];
// 'frente' aponta para o índice do primeiro elemento da fila.
int frente = -1;
// 'tras' aponta para o índice do último elemento da fila.
int tras = -1;

// --- Variáveis para a Pilha ---

// Array que armazena as peças da pilha.
Peca pilha[TAMANHO_PILHA];
// 'topo' aponta para o índice do último elemento da pilha.
int topo = -1;

// Um contador global para garantir que cada peça tenha um ID único.
int proximo_id = 0;

// --- Funções de Manipulação da Fila e da Pilha ---

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
        // Não faz nada, pois a fila sempre será mantida cheia e a nova peça
        // só será adicionada após a remoção de uma existente.
        return;
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

// Insere uma peça no topo da pilha (push).
void push(Peca peca) {
    // A pilha está cheia se o topo for igual ao tamanho máximo - 1.
    if (topo == TAMANHO_PILHA - 1) {
        printf("\n--- A pilha de reserva esta cheia! Nao e possivel reservar mais pecas. ---\n");
    } else {
        topo++;
        pilha[topo] = peca;
        printf("\n--- Peca [%c %d] reservada com sucesso! ---\n", peca.nome, peca.id);
    }
}

/**
 * Remove a peça do topo da pilha (pop).
 * Retorna a peça removida. Se a pilha estiver vazia, retorna
 * uma peça com ID -1 para indicar falha.
 */
Peca pop() {
    Peca peca_removida;
    // A pilha está vazia se o topo for -1.
    if (topo == -1) {
        printf("\n--- A pilha de reserva esta vazia! Nao ha pecas para usar. ---\n");
        peca_removida.id = -1; // Sinaliza erro.
    } else {
        peca_removida = pilha[topo];
        topo--;
    }
    return peca_removida;
}

// Exibe o estado atual da fila de peças.
void exibirFila() {
    printf("Fila de pecas: ");

    if (frente == -1) {
        printf("vazia");
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
}

// Exibe o estado atual da pilha de peças.
void exibirPilha() {
    printf("Pilha de reserva (Topo -> Base): ");

    if (topo == -1) {
        printf("vazia");
        return;
    }

    // Loop para imprimir os elementos da pilha.
    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
}

// Exibe o menu de opções para o usuário.
void exibirMenu() {
    printf("\n\nOpcoes de Acao:\n\n");
    printf("1. Jogar peca\n");
    printf("2. Reservar peca\n");
    printf("3. Usar peca reservada\n");
    printf("0. Sair\n");
    printf("\nDigite sua escolha: ");
}

// Inicializa a fila com 5 peças geradas automaticamente.
void inicializarFila() {
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(gerarPeca());
    }
}

// --- Função Principal ---

int main() {
    // Inicializa a semente do gerador de números aleatórios com o tempo atual.
    srand(time(NULL));
    int opcao;

    // A fila é inicializada com o número máximo de peças.
    inicializarFila();

    do {
        printf("\n--- Estado atual ---\n\n");
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
                    // Adiciona uma nova peça para manter a fila cheia.
                    enqueue(gerarPeca());
                }
                break;
            }
            case 2: { // Reservar peça (dequeue da fila e push na pilha)
                // A fila não pode estar vazia para reservar uma peça
                if (frente != -1) {
                    Peca peca_reservada = dequeue();
                    push(peca_reservada);
                    // Adiciona uma nova peça para manter a fila cheia.
                    enqueue(gerarPeca());
                } else {
                    printf("\n--- A fila de pecas esta vazia! Nao ha pecas para reservar. ---\n");
                }
                break;
            }
            case 3: { // Usar peça reservada (pop da pilha)
                Peca peca_usada = pop();
                if (peca_usada.id != -1) {
                    printf("\n--- Peca [%c %d] da reserva usada com sucesso! ---\n", peca_usada.nome, peca_usada.id);
                    // Adiciona uma nova peça para manter a fila cheia.
                    enqueue(gerarPeca());
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
