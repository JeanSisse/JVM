#define INTERFACE_SERVER

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "../headers/leitor.h"
int menu_interface(){
	
	bool erro = true;
	int type;
	printf("\n\n\n");
	printf("\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\t+ [1] - Exibir informações                             +\n");
	printf("\t+ [2] - Executar JVM                                   +\n");
	printf("\t+ [3] - Sair.                                          +\n");
	printf("\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	do{
		printf("\n\t\t>> Escolha uma das opções acima.<<: ");
		scanf("%d%*c", &type);
		if(type < 1 || type > 3){
			erro = false;
			printf("Tente novamente.\n");
		}
		else
			erro = true;
	}while(!erro);

	return type;
}

bool callFunc(FILE *fp){

	int type = menu_interface();
	switch (type){
		case 1:
			init_leitor(fp);
			break;
		case 2:
			//roda jvm
			break;
		case 3:
			return false;
		default:
			printf("Erro na escolha da opçao.\n");
			break;
	}
	printf("\n\n\t\t[>>> Aperte ENTER para continuar <<<]\n");

	getchar();
	return true;
}

int error_missingFile(){
	printf("ERRO: deve ser passado um argumento!\n");
	printf("Execute com:[program_name] [arquivo.class]\n");
	return MISSING_ARGUMENT;
}

int error_openFile(){
	printf("ERRO: não foi possivel abrir o arquivo .class.\n");
	return CANT_OPEN;
}
