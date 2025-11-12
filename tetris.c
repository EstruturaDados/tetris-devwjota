#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO_FILA 5

int proximo_id = 1;

typedef struct {
    int id;
    char nome[2];
} Peca;

typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int count;
} FilaCircular;

Peca gerarPeca() {
    Peca novaPeca;
    char *tipos[] = {"I", "O", "T", "L", "J", "S", "Z"}; 
    int num_tipos = sizeof(tipos) / sizeof(tipos[0]);

    novaPeca.id = proximo_id++;
    strcpy(novaPeca.nome, tipos[rand() % num_tipos]);

    return novaPeca;
}

void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->tras = 0;
    f->count = 0;
    
    printf("--- Inicializando a Fila de Peças Futuras ---\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca();
        f->pecas[f->tras] = novaPeca;
        f->tras = (f->tras + 1) % TAMANHO_FILA;
        f->count++;
    }
    printf("Fila inicializada com %d peças.\n", f->count);
}

Peca dequeue(FilaCircular *f) {
    if (f->count == 0) {
        Peca pecaVazia = {0, ""};
        printf("\n🚩 ERRO: Não há peças para jogar. A fila está vazia.\n");
        return pecaVazia;
    }

    Peca pecaRemovida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->count--;

    printf("\n✅ Peça jogada! -> Tipo: **%s**, ID: %d\n", pecaRemovida.nome, pecaRemovida.id);
    
    return pecaRemovida;
}

void enqueue(FilaCircular *f, Peca novaPeca) {
    if (f->count == TAMANHO_FILA) {
        printf("\n🚩 A fila está CHEIA. Não é possível inserir mais peças.\n");
        return;
    }

    f->pecas[f->tras] = novaPeca;
    f->tras = (f->tras + 1) % TAMANHO_FILA;
    f->count++;

    printf("⭐ Nova peça inserida: Tipo **%s**, ID: %d\n", novaPeca.nome, novaPeca.id);
}

void visualizarFila(const FilaCircular *f) {
    printf("\n--- 🎮 Fila de Peças Futuras (TAM: %d, Elementos: %d) ---\n", TAMANHO_FILA, f->count);

    if (f->count == 0) {
        printf(" >> A fila está vazia! <<\n");
        return;
    }

    printf("Fila: [ ");
    int i = f->frente;
    int elementos_exibidos = 0;

    while (elementos_exibidos < f->count) {
        printf(" **%s** (ID: %d) ", f->pecas[i].nome, f->pecas[i].id);
        
        if (elementos_exibidos == 0) {
            printf("<-- **FRENTE**");
        }
        
        if (elementos_exibidos < f->count - 1) {
            printf(" | ");
        }

        i = (i + 1) % TAMANHO_FILA;
        elementos_exibidos++;
    }
    printf(" ]\n");
}

int main() {
    srand(time(NULL));

    FilaCircular fila;
    
    inicializarFila(&fila);
    visualizarFila(&fila);

    int opcao;
    
    do {
        printf("\n===================================\n");
        printf("🎮 Tetris Stack - Fila de Peças\n");
        printf("1. Jogar uma Peça (Remove a da Frente e Insere uma Nova)\n");
        printf("2. Visualizar a Fila\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Por favor, digite um número.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                Peca pecaJogada = dequeue(&fila);
                
                if (pecaJogada.id != 0) {
                    Peca novaPeca = gerarPeca();
                    enqueue(&fila, novaPeca);
                }
                visualizarFila(&fila);
                break;
            case 2:
                visualizarFila(&fila);
                break;
            case 3:
                printf("\nObrigado por utilizar o sistema de fila! Encerrando o programa.\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}