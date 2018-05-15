#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"

char a;
//************************************************************************				   Head
struct tipo_peca{											//						<-pred	 V	prox->
	int left;												//			.-----------------[ :D ]----------------.
	int right;												//			|										|		
	peca *prox;												//			V 										V
	peca *pred;												//	NULL <- [x|x] <-> [x|x] <-> [x|x] <-> [x|x] <-> [x|x] -> NULL
	short flag_left;										//	 		  ^										  ^
	short flag_right;										//	 primeiro da fila/lista					ultimo da fila/lista			
};
//****************************************************************************
peca* criar_peca(int left, int right){ //cria uma peca |left|right|
	peca* novo = (peca*)calloc(1,sizeof(peca));
	novo->left = left;
	novo->right = right;
	return novo;
}
//************************************************************************
peca* criar_hand(peca* monte){ //cria a lista da mão
	peca *aux, *hand = (peca*)calloc(1,sizeof(peca));
	
	for(int i = 0; i<7; i++){
		aux = desenfileirar(monte);
		inserir_fim(hand, aux);
	}
	return hand;
}
//************************************************************************
peca* criar_monte(){ //cria as pecas do monte e depois as embaralha                             
	peca* monte = (peca*)calloc(1,sizeof(peca));
	peca* aux = monte;
	for(int i=0; i <= 6; i++){      
		for(int j=i; j <= 6; j++){
			aux->prox = criar_peca(i,j);
			aux->prox->pred = aux;
			aux = aux->prox;
		}
	}
	monte->pred = monte->prox; 	//
	monte->prox = aux;			// só para deixar em formato "padrão" -- pred = primeiro, prox = ultimo	
	monte = embaralhar_monte(monte);
	return monte;
}
//************************************************************************
peca* criar_mesa(peca *monte){ //cria a lista da mesa com a peca |6|6| já presente
	peca* mesa = (peca*)calloc(1,sizeof(peca));
	peca* aux = monte->pred;	//aux aponta para o primeiro
	int position = 0;

	while(aux->left != 6 || aux->right != 6){	//procura a [6|6]
		aux = aux->prox;
		position++;
	}

	aux = remover(monte, position);
	inserir_inicio(mesa, aux);

	return mesa;
}
//************************************************************************
void mostrar_monte(peca *monte){
	peca *aux = monte->pred;	//aux aponta para o primeiro
	int i=0;
	if(aux == NULL){
		printf("\nErro, monte vazio, por favor, crie o monte antes de selecionar esta opção.");
		return;
	}
	printf("\n**********PEÇAS DO MONTE**********\n\n");

	while (aux != NULL){
		
		if(i>3){
			printf("\n");
			i=0;
		}

		printf("[%i|%i] ", aux->left, aux->right);
		aux = aux->prox;
		i++;

	}
	printf("\n\n");
}
//************************************************************************
void mostrar_mesa(peca *mesa){
	peca* aux = mesa->pred;	//aux aponta para o primeiro
	printf("\n**********MESA DO JOGO**********\n");
	
	if(aux == NULL){
		printf("Mesa vazia\n");
	}
	else{
		while(aux != NULL){
			printf("[%d|%d] ", aux->left, aux->right);
			aux = aux->prox;
		}
	}
	printf("\n");
}
//************************************************************************
void mostrar_hand(peca *hand){
	printf("\n**********SUA MÃO ATUAL**********\n\n");
	
	peca *aux = hand->pred; //aux aponta para o primeiro
	if(aux == NULL){
		printf("Mão vazia!\n");
	}
	while (aux != NULL){
		printf("[%i|%i] ", aux->left, aux->right);
		aux = aux->prox;
	}
	printf("\n");
	
}
//************************************************************************
peca* embaralhar_monte(peca* monte_in){																	//ok
	int monte_in_size = 27; //temporario?
	if(monte_in->prox == NULL){
		printf("\n\n\nMonte vazio, crie-o primeiro.\n");

		return monte_in;
	}
	else{
		peca *aux, *monte_out = (peca*)calloc(1, sizeof(peca));
		int position;
		while(monte_in_size > 0){
			aux = monte_in->pred;

			position = rand()%(monte_in_size+1);    //position randomizada

			aux = remover(monte_in, position);
			inserir_fim(monte_out, aux);
			monte_in_size--;	
		}
		inserir_fim(monte_out, monte_in->pred);
		free(monte_in);
		return monte_out;
	}
}
//************************************************************************
peca* desenfileirar(peca *fila){ //a peca desenfileirada tem prox e pred = NULL
	peca* aux = fila->pred;
	if(aux == NULL)	return NULL;

	fila->pred = aux->prox;
	aux->prox->pred = NULL;
	aux->prox = NULL;					//"cortando ligaçoes"
	aux->pred = NULL;
	return aux;
}
//************************************************************************
peca* remover(peca* lista, int position){	//remove uma peca de uma posicao							//ok
	peca *aux = lista->pred;
	for (int i = 0; i < position; i++){ //aux vai até position
		aux = aux->prox;
	}
	if(lista->pred == lista->prox){
		lista->pred = NULL;
		lista->prox = NULL;
	}
	else if(aux == lista->prox){      	//se for o ultimo, faz o prox do predecessor ser NULL
		lista->prox = aux->pred;
		aux->pred->prox = NULL;
	}
	else if(aux == lista->pred){	//se for o primeiro, faz o pred do proximo ser NULL
		lista->pred = aux->prox;
		aux->prox->pred = NULL;
	}
	else{								
		aux->pred->prox = aux->prox;
		aux->prox->pred = aux->pred;
	}
	aux->prox = NULL;					//"cortando ligaçoes"
	aux->pred = NULL;
	return aux;

}
//************************************************************************
void inserir_fim(peca* lista, peca* input){ //"enfileirar"
	if(lista->prox == NULL){
		lista->pred = input;
		lista->prox = input;
	}
	else{
		lista->prox->prox = input;
		input->pred = lista->prox;
		lista->prox = input;
	}
}
//************************************************************************
void inserir_inicio(peca* lista, peca* input){
	if(lista->pred == NULL){
		lista->pred = input;
		lista->prox = input;
	}
	else{
		lista->pred->pred = input;
		input->prox = lista->pred;
		lista->pred = input;
	}
}
//************************************************************************
int check(peca* hand, peca* mesa){
	peca* aux = hand->pred; // aux aponta pro primeiro
	int position = 0;
	while(aux != NULL){
		if ((aux->left == mesa->pred->left || aux->right == mesa->prox->right) && aux->left != aux->right) {
		swap(aux);	//se estiver trocado
		printf("[%d|%d] inverte para [%d|%d]\n", aux->right, aux->left, aux->left, aux->right);	
		}
		if (aux->right == mesa->pred->left || aux->left == mesa->prox->right)	return position; 		//se encaixar no começo
		position++;
		aux = aux->prox;
	}	
	return -1;
}
//************************************************************************
void swap(peca* input){
	int aux = input->left;
	input->left = input->right;
	input->right = aux;
}
//************************************************************************
int next_turn(peca* monte, peca* mesa, peca* hand, int hand_size){
	int ck;
	peca *aux;
	ck = check(hand, mesa);
	if(ck < 0){
		while(ck < 0){
			aux = desenfileirar(monte);
			inserir_inicio(hand, aux);
			printf("peca comprada: [%d|%d]\n", aux->left, aux->right);
			printf("\nPressione 1 para continuar: ");
			scanf(" %c", &a);
			hand_size++;
			ck = check(hand, mesa);
		}

	}
	aux = remover(hand, ck);
	if(aux->left == mesa->prox->right){
		printf("peca [%d|%d] inserida no final\n", aux->left, aux->right);
		inserir_fim(mesa, aux);
	}else{
		printf("peca [%d|%d] inserida no inicio\n", aux->left, aux->right);
		inserir_inicio(mesa,aux);
	}
	scanf("%c", &a);
	hand_size--;

	return hand_size;
}
//************************************************************************
int novo_jogo(peca* monte, peca* mesa, peca* hand){ //inicializa o jogo

	printf("JOGO INICIADO!\n");
	scanf("%c", &a);
	return 1;
}
