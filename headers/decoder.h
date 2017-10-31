#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DECODER
	#define DECODER

	#ifdef DECODER_SERVER
		#define EXT_DECODER
	#else
		#define EXT_DECODER extern
	#endif

	#define	INSTRUC_NAME	35

	typedef struct {
		char instruc[INSTRUC_NAME];
		int bytes;
	}decoder;

	//função que irá inicializar o vetor de instruções
	EXT_DECODER void init_decoder(decoder decode[]);
#endif