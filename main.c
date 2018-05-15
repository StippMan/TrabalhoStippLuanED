#include <stdio.h>
#include <stdlib.h>
#include "domino.c"
#include <time.h>
char a;
												//arrumando novo_jogo, todos mostrar funfa, da core dump
int menu(int playing){
	int op;

	if(!playing){
		printf("\n\n**********JOGO DE DOMINO**********");
		printf("\n*                                *");
		printf("\n*  0. Sair do jogo               *");
		printf("\n*  1. criar e mostrar monte      *");
		printf("\n*  2. Novo jogo                  *"); // sair - novo jogo - criar/mostrar monte
		printf("\n*                                *");
		printf("\n**********************************");

	}else{
		printf("\n/-------------------\\\n");
		printf("| 0. Sair           |\n");
		printf("| 1. Proximo turno  |\n");
		printf("\\-------------------/\n");	
	}
	printf("\nSelecione a opção desejada: ");
	scanf("%i", &op);	
	return op;
}

int main(){
	srand(time(NULL));
	int hand_size = 7; //temporario?
	int op, playing = 0;
	peca *monte, *mesa, *hand;
	system("clear");
	printf("\n Pressione enter para começar!");
	
	do{
		scanf("%c", &a);
		system("clear");
		if(playing){
			mostrar_monte(monte);
			mostrar_mesa(mesa);
			mostrar_hand(hand);
		}
		op = menu(playing);
		if(!playing){
			switch(op){
				case 1:

					monte = criar_monte();
					mesa = criar_mesa(monte);
					hand = criar_hand(monte);
					mostrar_monte(monte);
					mostrar_mesa(mesa);
					mostrar_hand(hand);
					printf("\nPressione qqr tecla para continuar...\n");
					scanf("%c", &a);
				break;

				case 2:

					playing = novo_jogo(monte, mesa, hand);

				break;
			}
		}else{
			switch(op){
				case 1:	
					hand_size = next_turn(monte, mesa, hand, hand_size);
				break;
			}
		}
		if(!hand_size){
			system("clear");
			mostrar_mesa(mesa);
			mostrar_hand(hand);
			printf("JOGO FINALIZADO!\n");
			return 0;	
		}
	}while(op!=0);
	return 0;
}