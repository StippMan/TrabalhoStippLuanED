#include <stdio.h>
#include <stdlib.h>
#include "domino.c"

int menu(){
	int op;
	char a;
	scanf("%c", &a);
	system("clear");

		  printf("\n\n**********JOGO DE DOMINO**********");
		  printf("\n*                                *");
		  printf("\n*  0. Sair do jogo               *");
		  printf("\n*  1. Criar pecas do monte       *");
		  printf("\n*  2. Imprimir peças do monte    *");
		  printf("\n*  3. Iniciar jogo               *");
		  printf("\n*  4. Próxima jogada (nfeita)    *");
		  printf("\n*  5. embaralhar_monte           *");
		  printf("\n*                                *");
		  printf("\n**********************************");

		printf("\nSelecione a opção desejada: ");
		scanf("%i", &op);

	return op;
}

int main(){
	int op;
	char a;
	peca *p, *mesa;
	p = (peca*)calloc(1,sizeof(peca));
	//p->prox = NULL;                          //??   calloc ja faz :v

	printf("\n Pressione enter para começar!");
	
	do{
		op = menu();

		switch(op){
			case 1:
				p = criar_monte();
				printf("\n\n~Monte criado com sucesso!~\n");
				printf("\nAperte qualquer tecla para continuar... ");
				scanf("%c", &a);
			break;
			
			case 2:
				mostrar_monte(p);
				printf("\nAperte qualquer tecla para continuar... ");
				scanf("%c", &a);
			break;
		
			case 3:
				iniciar_jogo(p); // cria a mesa do jogo com a peca 6/6 e a mao do jogador com 7pecas
				printf("\nAperte qualquer tecla para continuar... ");
				scanf("%c", &a);
			break;
	
			case 4:
				
								
			break;

			case 5:
				p = embaralhar_monte(p);				
				printf("\nAperte qualquer tecla para continuar... ");
				scanf("%c", &a);
			break;
		}
		

	}while(op!=0);
	return 0;
}