#include <stdbool.h>
#include <stdio.h>
#include "../headers/interface.h"
#include "../headers/leitor.h"

int main (int argc, char *argv[]){

	bool True = true;
	int ret;
	/*Verifica se o arquivo foi passado*/
	if(argc != 2)
		ret = error_missingFile();

	FILE *fp = fopen(argv[1], "rb");
	
	if(fp == NULL)
		ret = error_openFile();

	//FILE *cruzeiro = fopen("cruzeiro.txt", "r");

	/*Verifica se o arquivo recebido foi aberto com sucesso*/


	//if(cruzeiro == NULL){
	//	printf("ERRO: não foi possivel abrir o arquivo [cruzeiro.txt].\n");
	//}
	
	while(True)
		True = callFunc(fp);

	fclose(fp);
	printf("\n\n");
	return 0;

}