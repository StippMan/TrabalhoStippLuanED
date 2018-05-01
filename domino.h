#ifndef DOMINO_HEADER
#define DOMINO_HEADER

typedef struct tipo_peca peca; //declarado

peca* embaralhar_monte(peca* monte); //DONE, AMEM SR.

peca* criar_monte(); //FINALIZADO SEM BUGS

void mostrar_monte(peca *p); //FINALIZADO SEM BUGS

void iniciar_jogo();

peca* criar_hand(peca *p);

peca* iniciar_mesa(peca *p);

void mostrar_mesa(peca *mesa);

void mostrar_hand();

void comprar(peca* monte, peca* hand, int qtde); //Falta testar.

peca* buscar_mao();

void inserir_mesa();




#endif