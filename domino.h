#ifndef DOMINO_HEADER_H
#define DOMINO_HEADER_H

typedef struct tipo_peca peca; 

peca* criar_peca(int left, int right);
peca* criar_monte();
peca* criar_hand(peca *monte);
peca* criar_mesa(peca *monte);
void mostrar_monte(peca *monte); 
void mostrar_mesa(peca *mesa);
void mostrar_hand(peca *hand);
peca* embaralhar_monte(peca* monte);
void inserir_fim(peca* lista, peca* input);
void inserir_inicio(peca* lista, peca* input);
int novo_jogo(peca* monte, peca* mesa, peca* hand);
int next_turn(peca* monte, peca* mesa, peca* hand, int hand_size);
int check(peca* input, peca* mesa);
peca* remover(peca* lista, int position);
void swap(peca* input);
peca* desenfileirar(peca *fila);
#endif