
/****************************************************************************
** MEMBROS:                                                                **
**		Aluno 1: Jean Pierre Sissé                                         **
**		Aluno 2: Samuel Sousa Almeida                                      **
**		Aluno 3: Rafael Rodrigues                                          **
**		Aluno 3: Raphael Rodrigues                                         **
**		Aluno 4: Teogenes Moura                                            **
**		Aluno 5: Michel Melo                                               **
**                                                                         **
** Descrição: Lietor de arquivo .class                                     **
**compile com: gcc -ansi -Wall -std=c99 -o [prog_name] [prog_name.c] -lm   **
*****************************************************************************/

#define LEITOR_SERVER

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../headers/leitor.h"
#include "../headers/exibidor.h"
//#include "../headers/decoder.h"


/*Função ler_u4: a partir do arquivo recebido, lê 4 bytes e inverte-os*/
uint32_t ler_u4(FILE *fp){
	uint8_t aux;
	uint32_t ret = 0;

	for(int i = 0; i <= 3; i++){ /*for para ler os 4 bytes do .class*/
		fread(&aux, 1, 1, fp); 	/*lê um byte*/
		ret = ret << 8;			/*Deslocamento de 8 bits a esquerda*/
		ret = ret | aux;		/*Faz um or bit a bit*/
	}

	return ret;
}

/*ler_u2: a partir do arquivo recebido, lê 2 bytes e inverte-os*/
uint16_t ler_u2 (FILE *fp){
	uint8_t aux;
	uint16_t ret = 0;

	fread(&ret, 1, 1, fp);
	fread(&aux, 1, 1, fp);

	ret <<= 8;
	ret |= aux;

	return ret;
}

/*ler_u1: a partir do arquivo recebido, lê 1 byte do mesmo.*/
uint8_t ler_u1 (FILE *fp){
	uint8_t ret;

	fread(&ret, 1, 1, fp);
	/*printf("%02x\n", ret);*/
	return ret;
}

/* função para ler os bytes da string UTF8.
** aloca a memória para a quantidade de byte no array de byte.
** faz um loop com a qtd de byte no array lendo byte a byte e armazenando 
** na memoria alocada.*/
uint8_t * ler_UTF8 (int size, FILE *fp){
	uint8_t *ret = (uint8_t *) malloc(sizeof(uint8_t) * size);

	for(int i = 0; i < size; i++)
		ret[i] = ler_u1(fp);
	
	return ret;
}

/*Retirado do slide do prof, efetua conversão do valor para float.*/
float convert_u4_toFloat(classLoadrType ent){
	float out;

	int s = ((ent.u4 >> 31) == 0) ? 1 : -1;
	int e = ((ent.u4 >> 23) & 0xff);
	int m = (e == 0) ? (ent.u4 & 0x7fffff) << 1 : (ent.u4 & 0x7fffff) | 0x800000;

	out = s * m * (pow(2,(e-150)));

	return out;
}

/*Converte o valor em u4 para long.*/
long convert_u4_toLong (classLoadrType entHigh, classLoadrType entLow){
	long out;

	out = (((long) entHigh.u4) << 32) | entLow.u4;
	return out;
}

/*Converte o valor em u4 para double.*/
double convert_u4_toDouble(classLoadrType entHigh, classLoadrType entLow){
	double out;

	long check_boundaries = convert_u4_toLong(entHigh, entLow);

	if(check_boundaries == 0x7ff0000000000000L){
		/*verifica se retorna +infinito*/
	}else if(check_boundaries == 0xfff0000000000000L){
		/*verifica se retorna -infinito*/
	}else if((check_boundaries >= 0x7ff0000000000001L) && (check_boundaries <= 0x7ffffffffffffL)){
		/*verifica se retorna NaN*/
	}else if((check_boundaries >= 0xfff0000000000001L) && (check_boundaries <= 0xffffffffffffffffL)){
		/*verifica se retorna NaN*/
	}else{
		int s = ((check_boundaries >> 63) == 0) ? 1 : -1;
		int e = ((check_boundaries >> 52) & 0x7ffL);
		long m = (e == 0) ? (check_boundaries & 0xfffffffffffffL) << 1 : (check_boundaries & 0xfffffffffffffL) | 0x10000000000000L;
		out = s * m * (pow(2,(e-1075)));
	}

	return out;
}



/* função recursiva para desreferenciar indices das constantes
** que contem strings nas suas informações.
** Recebe o indice (posição) de uma constante na tabela
** e o penteiro para a tabela e recursivamente acessa os
** indices na tabela até chegar no indice referenciando
** estrutura UTF8 que contem a string da constante inicialmente
** passado.*/
void dereference_index_UTF8 (int index, cp_info *cp){ 
	switch(cp[index].tag){
		case UTF8: /*Neste caso, estamos no caso trivial, onde a estrutura contem a string desejada.*/
			show_UTF8(cp[index].info[0].u2, cp[index].info[1].array); /*eh passado qtd de byte no array de byte e array contendo bytes*/
			break;

		case CLASS:
		case STRING:
			dereference_index_UTF8(cp[index].info[0].u2, cp);
			break;

		case INTERFACE_REF:
		case METHOD_REF:
		case FIELD_REF:
			dereference_index_UTF8(cp[index].info[0].u2, cp);
			printf("|");
			dereference_index_UTF8(cp[index].info[1].u2, cp);
			break;

		case NAME_AND_TYPE:
			dereference_index_UTF8(cp[index].info[0].u2, cp);
			printf(":");
			dereference_index_UTF8(cp[index].info[1].u2, cp);
			break;
	}
}

/*loadInfConstPoos: carrega as informacoes de pool de constate para memoria*/
int loadInfConstPool (cp_info *constPool, int const_pool_cont, FILE *fp){
	int i;

	/*percorre verificando os tipos da tags e carregando na memoria
	**de acordo.*/
	for(i = 1; i < const_pool_cont; i++){
		/*Carrega a tag que define o tipo da informação em cp_info*/
		constPool[i].tag = ler_u1(fp);

		/*verifica s o tipo lido é conhecido de acordo com a tabela no slide*/
		if((constPool[i].tag <= 0) && (constPool[i].tag >= 12) && (constPool[i].tag == 2))
			return i; /*encerra a execução se não for conhecido*/

		/*checagem do campo info e leitura dos parametros de acordo com o tipo da tag lida*/
		switch (constPool[i].tag){

			case UTF8:/*contem um campo u2 e um array de bayte u1 como info*/
				constPool[i].info = (classLoadrType *) malloc(sizeof(classLoadrType) * 2);
				constPool[i].info[0].u2 = ler_u2(fp); /*lê o número de bytes que o array de bytes contem*/
				constPool[i].info[1].array = ler_UTF8(constPool[i].info[0].u2, fp); /*bytes da string*/
				break;

			case INTEGER: /*possui apenas um campo u4 em info*/
			case FLOAT:
				constPool[i].info = (classLoadrType *) malloc(sizeof(classLoadrType));
				constPool[i].info[0].u4 = ler_u4(fp);
				break;

			case LONG: /*possui dois campos u4 em info*/
			case DOUBLE:
				constPool[i].info = (classLoadrType *) malloc(sizeof(classLoadrType) * 2);
				constPool[i].info[0].u4 = ler_u4(fp);
				constPool[i].info[1].u4 = ler_u4(fp);
				break;

			case CLASS: /*contem um campo u2 em info*/
			case STRING:
				constPool[i].info = (classLoadrType *) malloc(sizeof(classLoadrType));
				constPool[i].info[0].u2 = ler_u2(fp);
				break;

			case FIELD_REF: /*contem dois campos u2 em info*/
			case METHOD_REF:
			case INTERFACE_REF:
			case NAME_AND_TYPE:
				constPool[i].info = (classLoadrType *) malloc(sizeof(classLoadrType) * 2);
				constPool[i].info[0].u2 = ler_u2(fp);
				constPool[i].info[1].u2 = ler_u2(fp);
				break;
		}
	}
	/*retorna o numero de elementos lidos*/
	return i;
}

/*TABLESWITCH é usado quando os cases do switch podem ser representados de forma eficientes com 
* indeices na tabela de deslocamento de target. Valida o valor de switch dentro de um intervalo 
* válido de indices na tabela (tem que ser consistente com o seu valor low e high na tabela de salto).
*
* Imediatamente apos o opcode de uma dessas instrução, entre 0 e 3 bytes
* de ser considerado como byte de preenchimeto de modo qeu o defaultbyte1 comece em um endereço
* que é multipo de 4 byte a partir do do inicio (alinha 4 em 4 bytes do início do método), após o 
* preenchimento seguem os três valores signed de 32bits cada (default, low e high). Em seguida
* vem os X offsets de 32bits .
* X = high - low + 1 (determina o bytes do offset).
* Cada um dos valores (default, low e high) é construido como:
*	os valores são de 32-bits faça: 4x (byte1 << 8):
* 	(byte1 << 24)|(byte2 << 16)|(byte3 << 8)|byte4 ??? entendi+-.
*
* Ilustr:
*	        |prenchimento||defaultbyte1..||low 32bits........||high 32bits.......|
* code[[opc][][b2][b3][b4][b5][b6][b7][b8][b9][b10][b11][b12][b13][b14][b15][b16][b17][][][][][]....[]]
*
* lê checa e armazena as informações no code[]
*/
void if_tableswitch(uint32_t *i, FILE *fp, AT_Code **att_code){
	int referencia_ini, byte_preechimento, opcode, match_offset;
	uint32_t defaultbyte = 0, low = 0, high = 0;	//variaveis (operandos) de tabela de salto de tableswitch
	referencia_ini = (*i) - 1;

	byte_preechimento = (4 - (*i % 4)) % 4; //TODO: PQ BYTE DE PREENCIMENTO????????
	//preenche code[] com bytes de preenchimento
	for(int x = 0; x < byte_preechimento; x++){
		(*i)++;
		(*att_code)->code[*i] = ler_u1(fp);
	}

	//pega os 4byte do defaultbyte
	for(int x = 0; x < 4; x++){
		(*att_code)->code[*i] = ler_u1(fp); //preenche a ultima posição anterior(byte_preenchimento)
		defaultbyte = (defaultbyte << 8) + (*att_code)->code[*i];
		(*i)++;
	}

	//pega byte low
	for(int x = 0; x < 4; x++){
		(*att_code)->code[*i] = ler_u1(fp);
		low = (low << 8) + (*att_code)->code[*i];
		(*i)++;
	}

	//pega byte high
	for(int x = 0; x < 4; x++){
		(*att_code)->code[*i] = ler_u1(fp);
		high = (high << 8) + (*att_code)->code[*i];
		(*i)++;
	}

	//pega qtd. de bytes do offset
	match_offset = high - low + 1;
	for(int x = 0; x < match_offset; x++){
		//para cada byte pega o offset deste byte
		for(int j = 0; j < 4; j++){
			(*att_code)->code[*i] = ler_u1(fp);
			(*i)++;
		}
	}
}

/*LOOKUPSWITCH é usado quando os cases do switch são esparsas, a tabela de pares é ordenada por
* match crescente.
* A instrução pareia chaves com o target na tabela de deslocamento, o valor (key) de switch é
* comparada com os match na tabela de deslocamento.
* npairs é o numero de pares na tabela de offset;
* pares têm a forma <match><deslocamento>
* Cada instrução tem um numero de match-offset que é consitente com o seu valor de operando nparis.
*
*
* lê checa e armazena as informações no code[] 
*/
void if_lookupswitch(uint32_t *i, FILE *fp, AT_Code **att_code){
	uint32_t npairs = 0;	// operando da instrução lookupswitch
	uint32_t defaultbyte = 0;
	int referencia_ini, byte_preechimento, opcode;

	referencia_ini = (*i) - 1;

	byte_preechimento = (4 - (*i % 4)) % 4; //TODO: PQ BYTE DE PREENCIMENTO????????
	//preenche code[] com bytes de preenchimento
	for(int x = 0; x < byte_preechimento; x++){
		(*i)++;
		(*att_code)->code[*i] = ler_u1(fp);
	}

	//pega os 4byte do defaultbyte (target default)
	for(int x = 0; x < 4; x++){
		(*att_code)->code[*i] = ler_u1(fp); //preenche a ultima posição anterior(byte_preenchimento)
		defaultbyte = (defaultbyte << 8) + (*att_code)->code[*i];
		(*i)++;
	}

	//pega o byte de npairs (numero de pares na tabela)
	for(int x = 0; x < 4; x++){
		(*att_code)->code[*i] = ler_u1(fp);
		npairs = (npairs << 8) + (*att_code)->code[*i];
		(*i)++;
	}

	//pega os match e os deslocamentos(offset)
	//na mesm qtd de numero de pairs
	for(uint32_t x = 0; x < npairs; i++){
		//pega o valor de match atual
		for(int j = 0; j < 4; j++){
			(*att_code)->code[*i] = ler_u1(fp);
			(*i)++;
		}
		//pega o deslocamento(offset) do match anterior <match><offset>
		for(int j = 0; j < 4; j++){
			(*att_code)->code[*i] = ler_u1(fp);
			(*i)++;
		}
	}
}

/*A instrução wide modifica as outras instruções, ou seja, estende o indece de uma variavel
* local para 2 bytes. Comporta de acordo com um dos dois
* tipos de formato dependendo do tipo da instrução que esta sendo modificado.
* No primeiro formato, uma seria de instrução de manipulação de transferencia
* de valores entre pilha de operandos e array de variaveis locais.
*
* O segundo formato consiste em atuar encima da instrução IINC usada para incrementar
* variavel local.
* Nos dois casos, dois bytes unsigned seguem o bytecode da intrução modificada 
* (IINC ou outras), os bytes para primeira forma são indexbyte1 e indexbyte2 e
* são montados como indices de 16-bits de uma variavel local no frame corrente.
*
* Na segunda forma, além dos bytes indexbyte1 e indexbyte2, os bytes constbyte1 e
* constbyte1 são montadados como uma constante com sinal de 16bits (constbyte1 << 8)|constbyte2...
*/
void if_wide(uint32_t *i, FILE *fp, AT_Code **att_code, int *opcode){
	//printf("sendo montado...aguarde.\n");

	//pega opcode da instrução
	(*att_code)->code[*i] = ler_u1(fp);
	*opcode = (*att_code)->code[*i];
	(*i)++;

	//checa uma das operações usados pelo wide
	if(*opcode == ALOAD || *opcode == FLOAD || *opcode == ILOAD || *opcode == DLOAD || \
		*opcode == ISTORE || *opcode == LSTORE || *opcode == ASTORE || *opcode == FSTORE || \
		*opcode == RET || *opcode == DSTORE || *opcode == LLOAD)
	{
		//Após o opcode segue os indexbyte1 e indexbyte2 que serão lidos
		//pega indexbyte1
		(*att_code)->code[*i] = ler_u1(fp);
		(*i)++;

		//pega indexbyte2
		(*att_code)->code[*i] = ler_u1(fp);
		(*i)++;
	}else if (*opcode == IINC){
		//pega indexbyte1
		(*att_code)->code[*i] = ler_u1(fp);
		(*i)++;

		//pega indexbyte2
		(*att_code)->code[*i] = ler_u1(fp);
		(*i)++;

		//para esta instrução, ainda existem constbyte1 e constbyte2
		//pega constbyte1
		(*att_code)->code[*i] = ler_u1(fp);
		(*i)++;

		//pega constbyte2
		(*att_code)->code[*i] = ler_u1(fp);
	}else{
		//se ler opcode relacionado ao wide e não for nenhuma dessas instruções, então o 
		//arquivo .class não é valido
		printf("Arquivo .class invalido para instrução winde.\n");
		exit(1);
	}
}

void pega_operandos(decoder decode[], FILE *fp, int opcode, AT_Code **att_code, uint32_t *i){

	init_decoder(decode);
	int n_bytes = decode[opcode].bytes;

	//printf("i = %d, n_bytes = %d\n", *i, n_bytes);
	//percorre os n_bytes para pegar os operandos
	for(int x = 0; x < n_bytes; x++){
		//printf("i = %d, n_bytes = %d\n", *i, n_bytes);
		(*att_code)->code[*i] = ler_u1(fp);
		(*i)++;
	}
	//printf("depois do for pega_operandos: i = %d, n_bytes = %d\n", *i, n_bytes);
}

/*Na tabela code[]:
* As instuções lookupswitch, tableswitch e wide são as 3 três instruções que requerem
* tratamento diferentes, ou seja, são instruções especias, todas as outras instruções documentadas
* devem aparecer no array code[]. 
* A funçao checa e chama funções auxiliares para cada uma das instruçoes citadas acima.
*/
void verifica_instrucao(AT_Code **att_code, FILE *fp,  cp_info *constPool){
	int opcode;
	//uint32_t defaultbyte = 0, low = 0, high = 0;	//variaveis (operandos) de tabela de salto de tableswitch
	//uint32_t npairs = 0;	// operando da instrução lookupswitch
	
	decoder decode[NUM_INSTRUC];
	
	/***********************************************************************************/
	//dereference_index_UTF8((*att_code)->attribute_name_index, constPool); printf("\n");
	//printf("attribute_length = %d\n", (*att_code)->attribute_length);
	//printf("out->max_stack = %d\n", (*att_code)->max_stack);
	//printf("out->max_locals = %d\n", (*att_code)->max_locals);
	//printf("out->code_length = %d\n", (*att_code)->code_length);
/*****************************************************************************/

	//code fornece byte atual da jvm que implementa o method
	//aloca espaço que conterá o bytecode da jvm que implementam o código desse metodo
	(*att_code)->code = (uint8_t *) malloc(sizeof(uint8_t) * (*att_code)->code_length);
	
	//SALVAR AS INSTRUÇÕES DO METODO
	//Enquanto tiver byte, trata o bytecode

	for(uint32_t i = 0; i < (*att_code)->code_length; ){
		//printf("forSwitch: o valor i = %d\n", i);
		(*att_code)->code[i] = ler_u1(fp);	//pega o bytecode que é o opcode.

		opcode = (*att_code)->code[i];
		//printf("opcode antes do switch = %d\n", opcode);
		i++;	//posição seguinte para leitura do byte de preenchimeto que esta entre 0 e 3 bytes

		
		//printf("DENTRO DE Verifica INSTRUÇÕES; %d ,opcode = %x\n", (*att_code)->code_length, opcode);
		switch(opcode){
			case TABLESWITCH:
				//printf("CHAMANDO if_tableswitch:\n");
				if_tableswitch(&i, fp, att_code);
				break;
			case LOOKUPSWITCH:
				//printf("CHAMANDO if_LOOKUPswitch:\n");
				if_lookupswitch(&i, fp, att_code);
				break;
			case WIDE:
				//printf("CHAMANDO WIDE:\n");
				if_wide(&i, fp, att_code, &opcode);
				break;
			default:
				//printf("CHAMANDO pega_operandos:\n");
				pega_operandos(decode, fp, opcode, att_code, &i);
				break;
		}
		// printf("depois do switch: i = %d, code_length = %d\n", i, (*att_code)->code_length);
		// printf("opcode anterior = %d\n", (*att_code)->code[i-1]);
		// printf("proxima posição opcode = %d\n", (*att_code)->code[i]);
	}
	//printf("SAINDO FORA DO FOR SWITCH:\n");
}

AT_Code ler_Att_code(AT_Code **code_att, FILE *fp, uint16_t name_ind, uint32_t att_len, cp_info *constPool){
	AT_Code *out = (*code_att);

	int pos_init = ftell(fp);	//pega a posição atual do ponteiro no arquivo fp

	//pega o indice do nome do atributo e comprimento
	out->attribute_name_index = name_ind;
	out->attribute_length = att_len;



	out->max_stack = ler_u2(fp);	//Informação da profundidade maxima da pilha de operando durante a execução do mento
	out->max_locals = ler_u2(fp);	//número de variaveis locais (inclui os paramemtros) do vetor de var. locais
	out->code_length = ler_u4(fp);	//numero de bytes no seu array code[] (deve ser maior que zero)
	//printf("%d\n", out->code_length);
// /***********************************************************************************/
// 	dereference_index_UTF8(out->attribute_name_index, constPool); printf("\n");
// 	printf("attribute_length = %d\n", out->attribute_length);
// 	printf("out->max_stack = %d\n", out->max_stack);
// 	printf("out->max_locals = %d\n", out->max_locals);
// 	printf("out->code_length = %d\n", out->code_length);
// /*****************************************************************************/

	//Verifica o tipo da instrução pelo opcode e salva na tabela code[] 
	//printf("out = %d, &out = %d\n", out, &out);
	//printf("CHAMANDO VERIFICAR_INSTRUÇÃO\n");
	verifica_instrucao((&out), fp, constPool);

	//printf("VOLTANDO APOS VERIFICAR INSTRUÇÕES DENTRO DO LERR_ATT_CODE\n");

	out->exception_table_length = ler_u2(fp);
	out->EXC_table = (exception_table *) malloc(sizeof(exception_table) * out->exception_table_length);
	//printf("out->exception_table_length = %d\n", out->exception_table_length);

	//para cada entrada entrada na tabela de exception, lê os dados referentes
	for(int i = 0; i < out->exception_table_length; i++){
		out->EXC_table[i].start_pc = ler_u2(fp);		//
		//printf("out->EXC_table[i].start_pc = %d\n", out->EXC_table[i].start_pc);
		out->EXC_table[i].end_pc = ler_u2(fp);		//
		//printf("out->EXC_table[i].end_pc = %d\n", out->EXC_table[i].end_pc);
		out->EXC_table[i].handler_pc = ler_u2(fp);
		//printf("out->EXC_table[i].handler_pc = %d\n", out->EXC_table[i].handler_pc);
		out->EXC_table[i].catch_type = ler_u2(fp);	//
		//printf("out->EXC_table[i].catch_type = %d\n", out->EXC_table[i].catch_type);
	}

/******************** ACHAR E CORRIGIR ERRO NESSA ÁREA DE CODIGO   **********************************/
	out->attributes_count = ler_u2(fp);

	//printf("out->attributes_count = %d\n", out->attributes_count);
	
	out->attributes = (attribute_info *) malloc(sizeof(attribute_info) * (out)->attributes_count);
	//começa a partir da posição atual do arquivo e lê o restante dos operandos
	for (int i = (ftell(fp) - pos_init); i < out->attribute_length; i++){
		//out->attributes[i].attribute_name_index = ler_u2(fp);
		//out->attributes[i].attribute_length = ler_u4(fp);
		//out->attributes[i].info[]
		//printf("byte lixo = %x\n", ler_u1(fp));
		ler_u1(fp);
	}

	//printf("FOR ATTLENGTH\n");
	return *out;
}

AT_Exceptions ler_att_excp(AT_Exceptions **att_excp, FILE *fp, uint16_t name_ind, uint32_t att_len, cp_info *constPool){
	AT_Exceptions *out = (*att_excp);

	//pega name index e index length
	out->attribute_name_index = name_ind;
	out->attribute_length = att_len;

	//numero de exceptions
	out->number_of_exceptions = ler_u2(fp);

	//aloca espaço para qtd de exceptions
	out->exception_index_table = (uint16_t *) malloc(sizeof(exception_table) * out->number_of_exceptions);

	//mostra as exceptions, não preenche a tabela(deveria?? não sei).
	for(int x = 0; x < out->number_of_exceptions; x++){
		printf("%x\n", ler_u2(fp));
	}
}
/*Lê os fields*/
field_info ler_fields (FILE *fp, cp_info *constPool, cFile cf){
	field_info out;

	out.access_flags = ler_u2(fp) & 0x0df;
	out.name_index = ler_u2(fp);
	out.descriptor_index = ler_u2(fp);
	out.attribute_count = ler_u2(fp);
	out.attributes = (attribute_info *) malloc(sizeof(attribute_info) * out.attribute_count);
	for(int i = 0; i < out.attribute_count; i++)
		out.attributes[i] = ler_attribute(fp, constPool, cf);

	return out;
}

/*lê um atributo*/
attribute_info ler_attribute(FILE *fp, cp_info *constPool, cFile cf){
	attribute_info out;


	out.attribute_name_index = ler_u2(fp);		//pega o index de referencia para tabela de constPool que referencia o nome do atributo
	out.attribute_length = ler_u4(fp);			//pega o tamanho em byte do restante do atributo (não inclui os 6 bytes que contem o indice do nome e o comprimento do atributo)

	out.info = (uint8_t *) malloc(sizeof(uint8_t) * out.attribute_length);

	//lê atributos finais da classe
	for (int i = 0; i < out.attribute_length; i++)
		out.info[i] = ler_u1(fp);

	return out;
}



/* Funcoes de methods */
method_info ler_methods(FILE *fp, cp_info *constPool, cFile cf){
	method_info *out = cf.methods;
	
	AT_Code ret;
	uint32_t att_len;					//attribute_length auxiliar para atributo
	uint16_t name_ind;					//name_index auxiliar para atributo

	out->access_flags = ler_u2(fp);		//pega o flag
	out->name_index = ler_u2(fp);		//pega index de referencia para tabeal constPool que referencia o nome do metodo
	out->descriptor_index = ler_u2(fp);	//pega index de referencia para tabeal constPool que referencia um descritor do metodo
	out->attributes_count = ler_u2(fp);	//pega o número de atributos do metodo
	
	/**************************	DEBUGANDO COM PRINTS **********************/

	//dereference_index_UTF8(out->name_index, cf.constant_pool); printf("\n");
	/***********************************************************************/
	for (int i = 0; i < out->attributes_count; i++){

		
		name_ind = ler_u2(fp);
		att_len = ler_u4(fp);

		//dereference_index_UTF8(name_ind, cf.constant_pool); printf("\n");
		//printf("out->attributes_count = %d, i = %d\n", out->attributes_count, i);
/***************************************************************************************/

		// checa se é atributo Code:
		if(strcmp((char *) constPool[name_ind].info[1].array, "Code") == 0){
			out->att_code = (AT_Code *) malloc(sizeof(AT_Code));	//aloca memoria para o atributo Code
			ler_Att_code(&(out->att_code), fp, name_ind, att_len, constPool);		//le o Code
		}else if(strcmp((char *) constPool[name_ind].info[1].array, "Exception") == 0){
			//aloca espaço adequado
			//chama função para tratar exceptions
			out->att_excp = (AT_Exceptions *) malloc(sizeof(AT_Exceptions));
		}
	}

	//show_methods(constPool, *out);
	return *out;
}


/*carrega e mostra todas interfaces que estão presentes.*/
void loadInterfaces(uint16_t *interfaces, int interfaces_count, cp_info *constPool, FILE *fp){

	/*printf("	Interface count: %d\n", interfaces_count);*/
	if(interfaces_count == 0){
		return;
	}else{
		for (int i = 0; i < interfaces_count; ++i){
			interfaces[i] = ler_u2(fp);
			printf("\tInterface %d:", i);
			dereference_index_UTF8(interfaces[i], constPool);
			printf("\n");
		}
	}
}

int init_leitor(FILE *fp){
	//attribute_info *attributes;

	cFile classFile;
	int checkCP;

	/*vetor booleano para controle de flags presentes.*/
	bool splitFlags[5];


	/*Verificação da assinatura do arquivo (verifica se esta presente cafe babe)*/
	if((classFile.magic = ler_u4(fp)) != 0xcafebabe){
		printf("ERRO: Arquivo invalido.\nAssinatura \"cafe babe\" nao encontrado");
		return INVALID_FILE;
	}

	classFile.minor_version = ler_u2(fp);		/* lê a minor version */
	classFile.major_version = ler_u2(fp);		/* lê a major version */
	classFile.constant_pool_count = ler_u2(fp);	/* lê quantidade de constates no pool de constantes */
	/* aloca a memoria (tabela) do tamanho da quantidade de const na entrada no CP */
	classFile.constant_pool = (cp_info *) malloc(sizeof(cp_info) * classFile.constant_pool_count);
	checkCP = loadInfConstPool(classFile.constant_pool, classFile.constant_pool_count, fp);



	/*Verifica se todos os elementos da entrada do CP foram lidos*/
	if(classFile.constant_pool_count != checkCP){
		printf("ERRO: Tipo desconhecido para pool de constante.\n");
		printf("Nao foi possivel carregar todas as entradas do CP.\n");
		printf("Elementos #%d\n", checkCP+1);
		return UNKNOWN_TYPE;
	}
	
	/* access_flags, this_class, super_class, interfaces_count */
	classFile.access_flags = ler_u2(fp);
	
	/*Assumindo que todas as flags são false (ou seja, não estão presentes)*/
	for(int i = 0; i < 5; i++){
		splitFlags[i] = false;
	}

	/*Testa uma a uma setando como true as que estão presentes*/
	if (classFile.access_flags & 0x01){
		splitFlags[0] = true;
	}
	if (classFile.access_flags & 0x010){
		splitFlags[1] = true;
	}
	if (classFile.access_flags & 0x020){
		splitFlags[2] = true;
	}
	if (classFile.access_flags & 0x0200){
		splitFlags[3] = true;
	}
	if (classFile.access_flags & 0x0400){
		splitFlags[4] = true;
	}

	classFile.this_class = ler_u2(fp);
	classFile.super_class = ler_u2(fp);
	classFile.interfaces_count = ler_u2(fp);
	classFile.interfaces = (uint16_t*) (malloc (sizeof(uint16_t)*classFile.interfaces_count));
	/*Carregando e mostrando todas as interfaces que estão presentes*/
	loadInterfaces(classFile.interfaces, classFile.interfaces_count, classFile.constant_pool, fp);

	classFile.fields_count = ler_u2(fp);
	if(classFile.fields_count != 0){
		classFile.fields = (field_info *) malloc(sizeof(field_info) * classFile.fields_count);
		/*Carrega e mostra os fields existentes */

		for (int i = 0; i < classFile.fields_count; ++i){
			classFile.fields[i] = ler_fields(fp, classFile.constant_pool, classFile);
			/*show_fields(classFile.constant_pool, classFile.fields[i]);*/

		}
	}

	classFile.methods_count = ler_u2(fp);
	if(classFile.methods_count != 0){
		classFile.methods = (method_info*) malloc (sizeof(method_info)*classFile.methods_count);

		for (int i = 0;i < classFile.methods_count; i++){
			//printf("I na leitura de methods = %d, methods_count = %d\n", i, classFile.methods_count);
			printf ("\n	Method [%d], classFile.methods_count = %d\n", i, classFile.methods_count);
			classFile.methods[i] = ler_methods(fp, classFile.constant_pool, classFile);
			show_methods(classFile.constant_pool, classFile.methods[i]);
		}
	}

	/*Mostra as informações basicas como magic number, minversion...etc*/
	infoBasic(classFile);

	classFile.attributes_count = ler_u2(fp);
	printf("attribute_count = %d\n", classFile.attributes_count);
	if(classFile.attributes_count != 0){
		classFile.attributes = (attribute_info *) malloc (sizeof(attribute_info) * classFile.attributes_count);
		for (int i = 0; i < classFile.attributes_count; i++){
			classFile.attributes[i] = ler_attribute(fp, classFile.constant_pool, classFile);
			/*printf("%x\n", attributes[i]);*/
		}
	}


	/*chama a função para mostrar as flags ativas*/
	show_flags(classFile.access_flags, splitFlags);
	/*Exibe a informação (string) da classe*/
	dereference_index_UTF8(classFile.this_class, classFile.constant_pool);
	/*Exibe a informação (string) da super_classe*/
	dereference_index_UTF8(classFile.super_class, classFile.constant_pool);
	showConstPool(classFile.constant_pool_count, classFile.constant_pool);

	return 0;
}

int findMain (cFile classFile){
	int i;

	while (i<classFile.methods_count){
		if (strcmp(classFile.constant_pool[(classFile.methods[i].name_index)].info[1].array, "main")==0){
			return i;
		}
		i++;
	}
	return -1;
}

void init_decoder(decoder decode[]){

	/*Instruções constantes*/

	//nop
	strcpy(decode[0].instruc, "nop");
	decode[0].bytes = 0;

	//aconst_null
	strcpy(decode[1].instruc, "aconst_null");
	decode[1].bytes = 0;

	//aconst_m1
	strcpy(decode[2].instruc, "iconst_m1");
	decode[2].bytes = 0;

	//aconst_0
	strcpy(decode[3].instruc, "iconst_0");
	decode[3].bytes = 0;

	//aconst_1
	strcpy(decode[4].instruc, "iconst_1");
	decode[4].bytes = 0;

	//aconst_2
	strcpy(decode[5].instruc, "iconst_2");
	decode[5].bytes = 0;

	//aconst_3
	strcpy(decode[6].instruc, "iconst_3");
	decode[6].bytes = 0;

	//aconst_4
	strcpy(decode[7].instruc, "iconst_4");
	decode[7].bytes = 0;

	//aconst_5
	strcpy(decode[8].instruc, "iconst_5");
	decode[8].bytes = 0;

	//lconst_0
	strcpy(decode[9].instruc, "lconst_0");
	decode[9].bytes = 0;
	
	//lconst_1
	strcpy(decode[10].instruc, "lconst_1");
	decode[10].bytes = 0;

	//fconst_0
	strcpy(decode[11].instruc, "fconst_0");
	decode[11].bytes = 0;

	//fconst_1
	strcpy(decode[12].instruc, "fconst_1");
	decode[12].bytes = 0;

	//fconst_2
	strcpy(decode[13].instruc, "fconst_2");
	decode[13].bytes = 0;

	//dconst_0
	strcpy(decode[14].instruc, "dconst_0");
	decode[14].bytes = 0;

	//decodeonst_1
	strcpy(decode[15].instruc, "decodeonst_1");
	decode[15].bytes = 0;

	//bipush
	strcpy(decode[16].instruc, "bipush");
	decode[16].bytes = 1;

	//sipush
	strcpy(decode[17].instruc, "sipush");
	decode[17].bytes = 2;

	//ldc
	strcpy(decode[18].instruc, "ldc");
	decode[18].bytes = 1;

	//ldc_w
	strcpy(decode[19].instruc, "ldc_w");
	decode[19].bytes = 2;

	//ldc2_w
	strcpy(decode[20].instruc, "ldc2_w");
	decode[20].bytes = 2;

	/*Instruções de loads*/

	//iload
	strcpy(decode[21].instruc, "iload");
	decode[21].bytes = 1;

	//lload
	strcpy(decode[22].instruc, "lload");
	decode[22].bytes = 1;

	//fload
	strcpy(decode[23].instruc, "fload");
	decode[23].bytes = 1;

	//dload
	strcpy(decode[24].instruc, "dload");
	decode[24].bytes = 1;

	//aload
	strcpy(decode[25].instruc, "aload");
	decode[25].bytes = 1;

	//iload_0
	strcpy(decode[26].instruc, "iload_0");
	decode[26].bytes = 0;

	//iload_1
	strcpy(decode[27].instruc, "iload_1");
	decode[27].bytes = 0;

	//iload_2
	strcpy(decode[28].instruc, "iload_2");
	decode[28].bytes = 0;

	//iload_3
	strcpy(decode[29].instruc, "iload_3");
	decode[29].bytes = 0;

	//lload_0
	strcpy(decode[30].instruc, "lload_0");
	decode[30].bytes = 0;

	//lload_1
	strcpy(decode[31].instruc, "lload_1");
	decode[31].bytes = 0;

	//lload_2
	strcpy(decode[32].instruc, "lload_2");
	decode[32].bytes = 0;

	//lload_3
	strcpy(decode[33].instruc, "lload_3");
	decode[33].bytes = 0;

	//fload_0
	strcpy(decode[34].instruc, "fload_0");
	decode[34].bytes = 0;

	//fload_1
	strcpy(decode[35].instruc, "fload_1");
	decode[35].bytes = 0;

	//fload_2
	strcpy(decode[36].instruc, "fload_2");
	decode[36].bytes = 0;

	//fload_3
	strcpy(decode[37].instruc, "fload_3");
	decode[37].bytes = 0;

	//dload_0
	strcpy(decode[38].instruc, "dload_0");
	decode[38].bytes = 0;

	//dload_1
	strcpy(decode[39].instruc, "dload_1");
	decode[39].bytes = 0;

	//dload_2
	strcpy(decode[40].instruc, "dload_2");
	decode[40].bytes = 0;

	//dload_3
	strcpy(decode[41].instruc, "dload_3");
	decode[41].bytes = 0;

	//aload_0
	strcpy(decode[42].instruc, "aload_0");
	decode[42].bytes = 0;

	//aload_1
	strcpy(decode[43].instruc, "aload_1");
	decode[43].bytes = 0;

	//aload_2
	strcpy(decode[44].instruc, "aload_2");
	decode[44].bytes = 0;

	//aload_3
	strcpy(decode[45].instruc, "aload_3");
	decode[45].bytes = 0;

	//iaload
	strcpy(decode[46].instruc, "iaload");
	decode[46].bytes = 0;

	//laload
	strcpy(decode[47].instruc, "laload");
	decode[47].bytes = 0;

	//faload
	strcpy(decode[48].instruc, "faload");
	decode[48].bytes = 0;

	//daload
	strcpy(decode[49].instruc, "daload");
	decode[49].bytes = 0;

	//aaload
	strcpy(decode[50].instruc, "aaload");
	decode[50].bytes = 0;

	//baload
	strcpy(decode[51].instruc, "baload");
	decode[51].bytes = 0;

	//caload
	strcpy(decode[52].instruc, "caload");
	decode[52].bytes = 0;

	//saload
	strcpy(decode[53].instruc, "saload");
	decode[53].bytes = 0;

	//Stores

	//istore
	strcpy(decode[54].instruc, "istore");
	decode[54].bytes = 1;

	//lstore
	strcpy(decode[55].instruc, "lstore");
	decode[55].bytes = 1;

	//fstore
	strcpy(decode[56].instruc, "fstore");
	decode[56].bytes = 1;

	//dstore
	strcpy(decode[57].instruc, "dstore");
	decode[57].bytes = 1;

	//astore
	strcpy(decode[58].instruc, "astore");
	decode[58].bytes = 1;

	//istore_0
	strcpy(decode[59].instruc, "istore_0");
	decode[59].bytes = 0;

	//istore_1
	strcpy(decode[60].instruc, "istore_1");
	decode[60].bytes = 0;

	//istore_2
	strcpy(decode[61].instruc, "istore_2");
	decode[61].bytes = 0;

	//istore_3
	strcpy(decode[62].instruc, "istore_3");
	decode[62].bytes = 0;

	//lstore_0
	strcpy(decode[63].instruc, "lstore_0");
    decode[63].bytes = 0;

    //lstore_1
    strcpy(decode[64].instruc, "lstore_1");
    decode[64].bytes = 0;

    //lstore_2
    strcpy(decode[65].instruc, "lstore_2");
    decode[65].bytes = 0;

    //lstore_3
    strcpy(decode[66].instruc, "lstore_3");
    decode[66].bytes = 0;

    // fstore_0
    strcpy(decode[67].instruc, "fstore_0");
    decode[67].bytes = 0;

    //fstore_1
    strcpy(decode[68].instruc, "fstore_1");
    decode[68].bytes = 0;

    //fstore_2
    strcpy(decode[69].instruc, "fstore_2");
    decode[69].bytes = 0;

    //fstore_3
    strcpy(decode[70].instruc, "fstore_3");
    decode[70].bytes = 0;

    /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

    // dstore_0
    strcpy(decode[71].instruc, "dstore_0");
    decode[71].bytes = 0;

    // dstore_1
    strcpy(decode[72].instruc, "dstore_1");
    decode[72].bytes = 0;

    // dstore_2
    strcpy(decode[73].instruc, "dstore_2");
    decode[73].bytes = 0;

    // dstore_3
    strcpy(decode[74].instruc, "dstore_3");
    decode[74].bytes = 0;

    // astore_0
    strcpy(decode[75].instruc, "astore_0");
    decode[75].bytes = 0;

    // astore_1
    strcpy(decode[76].instruc, "astore_1");
    decode[76].bytes = 0;

    // astore_2
    strcpy(decode[77].instruc, "astore_2");
    decode[77].bytes = 0;

    // astore_3
    strcpy(decode[78].instruc, "astore_3");
    decode[78].bytes = 0;

    // iastore
    strcpy(decode[79].instruc, "iastore");
    decode[79].bytes = 0;

    //lastore
    strcpy(decode[80].instruc, "lastore");
    decode[80].bytes = 0;

    //fastore
    strcpy(decode[81].instruc, "fastore");
    decode[81].bytes = 0;

    //dastore
    strcpy(decode[82].instruc, "dastore");
    decode[82].bytes = 0;

    //aastores
    strcpy(decode[83].instruc, "aastore");
    decode[83].bytes = 0;

    //bastore
    strcpy(decode[84].instruc, "bastore");
    decode[84].bytes = 0;

    //castore
    strcpy(decode[85].instruc, "castore");
    decode[85].bytes = 0;

    //sastore
    strcpy(decode[86].instruc, "sastore");
	decode[86].bytes = 0;

	//Stack

	//pop
	strcpy(decode[87].instruc, "pop");
	decode[87].bytes = 0;

	//pop2
	strcpy(decode[88].instruc, "pop2");
	decode[88].bytes = 0;

	//dup
	strcpy(decode[89].instruc, "dup");
	decode[89].bytes = 0;

	//dup_x1
	strcpy(decode[90].instruc, "dup_x1");
	decode[90].bytes = 0;

	//dup_x2
	strcpy(decode[91].instruc, "dup_x2");
	decode[91].bytes = 0;

	//dup2
	strcpy(decode[92].instruc, "dup2");
	decode[92].bytes = 0;

	//dup2_x1
	strcpy(decode[93].instruc, "dup2_x1");
	decode[93].bytes = 0;

	//dup2_x2
	strcpy(decode[94].instruc, "dup2_x2");
	decode[94].bytes = 0;

	//swap
	strcpy(decode[95].instruc, "swap");
	decode[95].bytes = 0;

	//Math

	//iadd
	strcpy(decode[96].instruc, "iadd");
	decode[96].bytes = 0;

	//ladd
	strcpy(decode[97].instruc, "ladd");
	decode[97].bytes = 0;

	//fadd
	strcpy(decode[98].instruc, "fadd");
	decode[98].bytes = 0;

	//dadd
	strcpy(decode[99].instruc, "dadd");
	decode[99].bytes = 0;

	//isub
	strcpy(decode[100].instruc, "isub");
	decode[100].bytes = 0;

	//lsub
	strcpy(decode[101].instruc, "lsub");
	decode[101].bytes = 0;

	//fsub
	strcpy(decode[102].instruc, "fsub");
	decode[102].bytes = 0;

	//dsub
	strcpy(decode[103].instruc, "dsub");
	decode[103].bytes = 0;

	//imul
	strcpy(decode[104].instruc, "imul");
	decode[104].bytes = 0;

	//lmul
	strcpy(decode[105].instruc, "lmul");
	decode[105].bytes = 0;

	//fmul
	strcpy(decode[106].instruc, "fmul");
	decode[106].bytes = 0;

	//dmul
	strcpy(decode[107].instruc, "dmul");
	decode[107].bytes = 0;

	//idiv
	strcpy(decode[108].instruc, "idiv");
	decode[108].bytes = 0;

	//ldiv
	strcpy(decode[109].instruc, "ldiv");
	decode[109].bytes = 0;

	//fdiv
	strcpy(decode[110].instruc, "fdiv");
	decode[110].bytes = 0;

	//ddiv
	strcpy(decode[111].instruc, "ddiv");
	decode[111].bytes = 0;

	//irem
	strcpy(decode[112].instruc, "irem");
	decode[112].bytes = 0;

	//lrem
	strcpy(decode[113].instruc, "lrem");
	decode[113].bytes = 0;

	//frem
	strcpy(decode[114].instruc, "frem");
	decode[114].bytes = 0;

	//drem
	strcpy(decode[115].instruc, "drem");
	decode[115].bytes = 0;

	//ineg
	strcpy(decode[116].instruc, "ineg");
	decode[116].bytes = 0;

	//lneg
	strcpy(decode[117].instruc, "lneg");
	decode[117].bytes = 0;

	//fneg
	strcpy(decode[118].instruc, "fneg");
	decode[118].bytes = 0;

	//dneg
	strcpy(decode[119].instruc, "dneg");
	decode[119].bytes = 0;

	//ishl
	strcpy(decode[120].instruc, "ishl");
	decode[120].bytes = 0;

	//lshl
	strcpy(decode[121].instruc, "lshl");
	decode[121].bytes = 0;

	//ishr
	strcpy(decode[122].instruc, "ishr");
	decode[122].bytes = 0;

	//lshr
	strcpy(decode[123].instruc, "lshr");
	decode[123].bytes = 0;

	//iushr
	strcpy(decode[124].instruc, "iushr");
	decode[124].bytes = 0;

	//lushr
	strcpy(decode[125].instruc, "lushr");
	decode[125].bytes = 0;

	//iand
	strcpy(decode[126].instruc, "iand");
	decode[126].bytes = 0;

	//land
	strcpy(decode[127].instruc, "land");
	decode[127].bytes = 0;

	//ior
	strcpy(decode[128].instruc, "ior");
	decode[128].bytes = 0;

	//lor
	strcpy(decode[129].instruc, "lor");
	decode[129].bytes = 0;

	//ixor
	strcpy(decode[130].instruc, "ixor");
	decode[130].bytes = 0;

	//lxor
	strcpy(decode[131].instruc, "lxor");
	decode[131].bytes = 0;

	//iinc
	strcpy(decode[132].instruc, "iinc");
	decode[132].bytes = 2;

	// CONVERSIONS

	//i2l
	strcpy(decode[133].instruc, "i2l");
	decode[133].bytes = 0;

	//i2f
    strcpy(decode[134].instruc, "i2f");
    decode[134].bytes = 0;

    //i2d
    strcpy(decode[135].instruc, "i2d");
    decode[135].bytes = 0;

    //l2i
    strcpy(decode[136].instruc, "l2i");
    decode[136].bytes = 0;

    //l2f
    strcpy(decode[137].instruc, "l2f");
    decode[137].bytes = 0;

    //l2d
    strcpy(decode[138].instruc, "l2d");
    decode[138].bytes = 0;

    //f2i
    strcpy(decode[139].instruc, "f2i");
    decode[139].bytes = 0;

    //f2l
    strcpy(decode[140].instruc, "f2l");
    decode[140].bytes = 0;

    //f2d
    strcpy(decode[141].instruc, "f2d");
    decode[141].bytes = 0;

    //d2i
    strcpy(decode[142].instruc, "d2i");
    decode[142].bytes = 0;

    //d2l
    strcpy(decode[143].instruc, "d2l");
    decode[143].bytes = 0;

    //d2f
    strcpy(decode[144].instruc, "d2f");
    decode[144].bytes = 0;

    //i2b
    strcpy(decode[145].instruc, "i2b");
    decode[145].bytes = 0;

    //i2c
    strcpy(decode[146].instruc, "i2c");
    decode[146].bytes = 0;

    //i2s
    strcpy(decode[147].instruc, "i2s");
    decode[147].bytes = 0;

    // COMPARISONS

    //lcmp
    strcpy(decode[148].instruc, "lcmp");
    decode[148].bytes = 0;

    //fcmpl
    strcpy(decode[149].instruc, "fcmpl");
    decode[149].bytes = 0;

    //fcmpg
    strcpy(decode[150].instruc, "fcmpg");
    decode[150].bytes = 0;

    //dcmpl
    strcpy(decode[151].instruc, "dcmpl");
    decode[151].bytes = 0;

    //dcmpg
    strcpy(decode[152].instruc, "dcmpg");
    decode[152].bytes = 0;

    //ifeq
    strcpy(decode[153].instruc, "ifeq");
    decode[153].bytes = 2;

    //ifne
    strcpy(decode[154].instruc, "ifne");
    decode[154].bytes = 2;

    //iflt
    strcpy(decode[155].instruc, "iflt");
    decode[155].bytes = 2;

    //ifge
    strcpy(decode[156].instruc, "ifge");
    decode[156].bytes = 2;

    //ifgt
    strcpy(decode[157].instruc, "ifgt");
    decode[157].bytes = 2;

    //ifle
    strcpy(decode[158].instruc, "ifle");
    decode[158].bytes = 2;

    //if_icmpeq
    strcpy(decode[159].instruc, "if_icmpeq");
    decode[159].bytes = 2;

    //if_icmpne
    strcpy(decode[160].instruc, "if_icmpne");
    decode[160].bytes = 2;

    //if_icmplt
    strcpy(decode[161].instruc, "if_icmplt");
    decode[161].bytes = 0;

    //if_icmpge
    strcpy(decode[162].instruc, "if_icmpge");
    decode[162].bytes = 0;

    //if_icmpgt
    strcpy(decode[163].instruc, "if_icmpgt");
    decode[163].bytes = 0;

    //if_icmple
    strcpy(decode[164].instruc, "if_icmple");
    decode[164].bytes = 0;

    //if_acmpeq
    strcpy(decode[165].instruc, "if_acmpeq");
    decode[165].bytes = 2;

    //if_acmpne
    strcpy(decode[166].instruc, "if_acmpne");
    decode[166].bytes = 2;

    // CONTROL

    //goto
    strcpy(decode[167].instruc, "goto");
    decode[167].bytes = 2;

    //jsr
    strcpy(decode[168].instruc, "jsr");
    decode[168].bytes = 2;

    //ret
    strcpy(decode[169].instruc, "ret");
    decode[169].bytes = 1;

    //tableswitch
    strcpy(decode[170].instruc, "tableswitch"); // VERIFICAR A QUANTIDADE DE BYTES (instrução de comprimento variável)
    decode[170].bytes = 14;

    //lookupswitch
    strcpy(decode[171].instruc, "lookupswitch"); // VERIFICAR A QUANTIDADE DE BYTES (instrução de comprimento variável)
    decode[171].bytes = 10;

    //ireturn
    strcpy(decode[172].instruc, "ireturn");
    decode[172].bytes = 0;

    //lreturn
    strcpy(decode[173].instruc, "lreturn");
    decode[173].bytes = 0;

    //freturn
    strcpy(decode[174].instruc, "freturn");
    decode[174].bytes = 0;

    //dreturn
    strcpy(decode[175].instruc, "dreturn");
    decode[176].bytes = 0;

    //areturn
    strcpy(decode[176].instruc, "areturn");
    decode[176].bytes = 0;

    // return 
    strcpy(decode[177].instruc, "return");
    decode[177].bytes = 0;

    // REFERENCES

    //getstatic
    strcpy(decode[178].instruc, "getstatic");
    decode[178].bytes = 2;

    strcpy(decode[179].instruc, "putstatic");
    decode[179].bytes = 2;

    strcpy(decode[180].instruc, "getfield");
    decode[180].bytes = 2;

    strcpy(decode[181].instruc, "putfield");
    decode[181].bytes = 2;
    
    // invokevirtual 
    strcpy(decode[182].instruc, "invokevirtual");
    decode[182].bytes = 2;

    // invokespecial 
    strcpy(decode[183].instruc, "invokespecial");
    decode[183].bytes = 2;

    strcpy(decode[184].instruc, "invokestatic");
    decode[184].bytes = 2;

    // invokeinterface 
    strcpy(decode[185].instruc, "invokeinterface");
    decode[185].bytes = 4;

    strcpy(decode[186].instruc, "invokedynamic");
    decode[186].bytes = 4;

    // new 
    strcpy(decode[187].instruc, "new");
    decode[187].bytes = 2;

    strcpy(decode[188].instruc, "newarray");
    decode[188].bytes = 1;

    strcpy(decode[189].instruc, "anewarray");
    decode[189].bytes = 2;

    strcpy(decode[190].instruc, "arraylength");
    decode[190].bytes = 0;

    strcpy(decode[191].instruc, "athrow");
    decode[191].bytes = 0;

    strcpy(decode[192].instruc, "checkcast");
    decode[192].bytes = 2;

    strcpy(decode[193].instruc, "instanceof");
    decode[193].bytes = 2;

    strcpy(decode[194].instruc, "monitorenter");
    decode[194].bytes = 0;

    strcpy(decode[195].instruc, "monitorexit");
    decode[195].bytes = 0;

    strcpy(decode[196].instruc, "wide"); // VERIFICAR A QUANTIDADE DE BYTES
    decode[196].bytes = 3;

    strcpy(decode[197].instruc, "multianewarray");
    decode[197].bytes = 3;

    strcpy(decode[198].instruc, "ifnull");
    decode[198].bytes = 2;

    strcpy(decode[199].instruc, "ifnonnull");
    decode[199].bytes = 2;

    strcpy(decode[200].instruc, "goto_w");
    decode[200].bytes = 4;

    strcpy(decode[201].instruc, "jsr_w");
    decode[201].bytes = 4;

    //codigos reservados
    strcpy(decode[202].instruc, "breakpoint");
    decode[202].bytes = 0;

    strcpy(decode[254].instruc, "impdep1");
    decode[254].bytes = 0;

    strcpy(decode[255].instruc, "impdep2");
    decode[255].bytes = 0;
}