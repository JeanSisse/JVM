#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<errno.h>

#ifndef DECODER
	#define DECODER

	#ifdef DECODER_SERVER
		#define EXT_DECODER
	#else
		#define EXT_DECODER extern
	#endif

	#define	INSTRUC_NAME	35

	typedef struct{ //Nome da struct = ""
		int32_t hexa;
		char instruc[INSTRUC_NAME]; //Definindo com *name cria-se uma posição na memória sendo read-only
		int8_t bytes; //Quantidade de argumentos
		//Chamada da função
		void (*ins)();
	}decoder; //"Abreviação" do nome struct + ""

	//função que irá inicializar o vetor de instruções
	EXT_DECODER void init_decoder(decoder decode[]);
#endif