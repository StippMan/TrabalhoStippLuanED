#include <stdio.h>
#include <stdlib.h>
#include "domino.h"

//************************************************************************

struct tipo_peca{
	int left;
	int right;
	peca *prox;
	peca *pred;
	short flag_left;
	short flag_right;
};

//************************************************************************

peca* embaralhar_monte(peca* monte_in){   //FUNCIONA, AMEM SENHOR
	int monte_in_size = 28;                                                               //temporario?
	if(monte_in->prox == NULL){
		printf("\n\n\nMonte vazio, crie-o primeiro.\n");
		return monte_in;
	}
	else{
		peca *aux1, *aux2, *monte_out;
		int position;
		monte_out = (peca*)calloc(1, sizeof(peca));
		aux2 = monte_out;

		while(monte_in_size > 0){
			aux1 = monte_in;
			position = rand()%monte_in_size;    //position randomizada
			position++;
			for (int i = 0; i < position; i++){ //aux vai até position
				aux1 = aux1->prox;
			}
			if(position == monte_in_size){      //se for o ultimo, faz o prox do anterior ser NULL
				aux1->pred->prox = NULL;
			}
			else{
				aux1->pred->prox = aux1->prox;
				aux1->prox->pred = aux1->pred;
			}
			aux2->prox = aux1;      //--------------------------------------------------v
			aux1->pred = aux2;      // 	adicionando a peca selecionada ao monte_out		|
			aux2->prox = aux1;      //	e aux2 sempre aponta p/ ultimo do monte_out		|
			aux2 = aux1;            //--------------------------------------------------^
			monte_in_size--;
		}
		aux2->prox = NULL;			//ultimo aponta p/ NULL	
		return monte_out;
	}
}









//************************************************************************
peca* criar_monte(){                                                                     //mudei pra lista duplamente encadeada
	peca *p, *aux;                //p é cabeça, sem dados, p->prox é a primeira peça

	p = (peca*)calloc(1,sizeof (peca)); //iniciando a cabeça
	p->prox = NULL;
	aux = p;
	peca *p1; //criando a primeira peça do monte
	p1 = (peca*)calloc(1,sizeof (peca));
	aux->prox = p1;  //fazendo a cabeça apontar para a primeira peça
	p1->pred = aux;
	aux = aux->prox;
	free(p1);
	
	peca *aux2; 

	
	for(int i=0; i <= 6; i++){      //preenchendo o lado esquerdo das peças
		for(int j=i; j <= 6; j++){
			aux->left = i;
			aux->right = j;
			aux->prox = (peca*)calloc(1,sizeof (peca));
			aux2 = aux;
			aux = aux->prox;
			aux->pred = aux2;
			aux->prox = NULL;
		}
	}

	
	aux2->prox = NULL;

	//embaralhando o monte

	p = embaralhar_monte(p); // nao esta funcionando


	return p;
}

//************************************************************************



void mostrar_monte(peca *monte){
	peca *aux;
	aux = monte;
	int i=0;
	if(aux->prox == NULL){
		printf("\nErro, monte vazio, por favor, crie o monte antes de selecionar esta opção.");
		return;
	}

	aux = aux->prox;
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

peca* criar_hand(peca *monte){    //ærrumar essa ou mostrar hand pq nao ta funfando

	peca *hand, *auxhand;
	hand = (peca*)calloc(1, sizeof(peca)); //hand tambem tem cabeca. hand->prox é a 1ª peca da mao

	peca *hand1 = (peca*)calloc(1, sizeof(peca));  //criando a primeira peca da mao
	hand->prox = hand1;
	free(hand1);
	auxhand = hand->prox;

	peca *aux;
	aux = monte->prox; 

	int i=0, quantmont=27;
	int random_num;
	while(i<7){
		random_num = rand()% (quantmont+1); // gerando um n random entre n de pecas do monte
		
		for(int j=0; j<random_num; j++){
			aux = aux->prox;            //navegando no monte ate a peca rand
		}


		auxhand->left = aux->prox->left;
		auxhand->right = aux->prox->right;

		aux->prox = aux->prox->prox;
		auxhand->prox = (peca*)calloc(1, sizeof(peca));
		auxhand = auxhand->prox;

		aux = monte->prox;

		i++;
		quantmont--;
	}

	
	//printf("\n*********COMPRA INICIAL REALIZADA**********\n");
	return hand;


}

//************************************************************************

peca* iniciar_mesa(peca *monte){
	
	peca *aux;
	aux = monte;

	peca *mesa, *mesa1;
	mesa = (peca*)calloc(1, sizeof(peca)); //mesa é cabeca
	mesa1 = (peca*)calloc(1, sizeof(peca));
	mesa->prox = mesa1;
	mesa->pred = NULL;
	free(mesa1);

	while(aux->prox->left != 6 || aux->prox->right != 6){
		aux = aux->prox;           //procurando a peca [6/6]
	}
	 
	mesa->prox = aux->prox;
	mesa->prox->prox = NULL;
	mesa->prox->pred = NULL;

	mesa->prox->flag_left = 0;
	mesa->prox->flag_right = 0;

	aux->prox = aux->prox->prox;
	

   


	//printf("\n**********MESA INICIADA**********");
	return mesa;
}

//************************************************************************

void mostrar_mesa(peca *mesa){
	printf("\n**********MESA DO JOGO**********\n");


	printf("\n");
}

//************************************************************************

void mostrar_hand(peca *hand){
	printf("\n**********SUA MÃO ATUAL**********\n\n");
	
	peca *auxhand;
	auxhand = hand->prox;

	while (auxhand != NULL){
		printf("[%i|%i] ", auxhand->left, auxhand->right);
		auxhand = auxhand->prox;
	}
	printf("\n");
	
}

//************************************************************************

void iniciar_jogo(peca *p){
	peca *mesa, *mao;

	mesa = iniciar_mesa(p);
	mao = criar_hand(p);
	mao = comprar(7);

	printf("\n~~~~~O JOGO COMEÇOU!~~~~~\n");
	

	mostrar_mesa(mesa); //funcao nao feita
	mostrar_hand(mao); 
	
	
}

//************************************************************************


void comprar(peca* monte, peca* hand, int qtde){

	peca *auxM = monte, *auxH = hand;
	
	while(auxH->prox != NULL){

		auxH = auxH->prox;
	}

	for (qtde; qtde > 0; qtde--){
		
		auxM = monte->prox;

		if(auxM->prox == NULL){      //se for o ultimo, faz o prox do anterior ser NULL
			monte->prox = NULL;
		}
		else{
			monte->prox = auxM->prox;
			auxM->prox->pred = auxM->pred;
		}

		auxH->prox = auxM;
		auxM->pred = auxH;
		auxM->prox = NULL;
		auxH = auxM;

	}
}

//****************************************************************************