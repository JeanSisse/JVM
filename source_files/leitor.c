
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
** compile com: make													   **
*****************************************************************************/

#define LEITOR_SERVER

#include "../headers/leitor.h"
#include "../headers/exibidor.h"


/*Função ler_u4: a partir do arquivo recebido, lê 4 bytes e inverte-os*/
uint32_t ler_u4(FILE *fp){
	uint8_t aux;
	uint32_t ret = 0;

	for(int i = 0; i <= 3; i++){ /*for para ler os 4 bytes do .class*/
		fread(&aux, 1, 1, fp); 	/*lê um byte*/
		ret = ret << 8;			/*Deslocamento de 8 bits a esquerda*/
		ret = ret | aux;		/*Faz um or bit a bit*/
	}

	//printf("ret_u4 = %x\n", ret);
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

	//printf("ret_u2 = %x\n", ret);
	return ret;
}

/*ler_u1: a partir do arquivo recebido, lê 1 byte do mesmo.*/
uint8_t ler_u1 (FILE *fp){
	uint8_t ret;

	fread(&ret, 1, 1, fp);
	/*printf("%02x\n", ret);*/
	//printf("ret_u1 = %x\n", ret);
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

				/*SOLUÇÃO TEMPORÁRIA (CONFIRMAR COM O PROFESSOR)*/
				/*DOUBLE OCUPA DUAS POSIÇÕES NO CONST POOL*/
				constPool[i+1].info = (classLoadrType *) malloc(sizeof(classLoadrType) * 2);
				constPool[i+1].info[0].u4 = (intptr_t)NULL;		
				constPool[i+1].info[1].u4 = (intptr_t)NULL;
				 i++;	//desconsidera a proxima posição do constPool, pois é a regra qundo é double ou long
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
* deve ser considerado como byte de preenchimeto de modo qeu o defaultbyte1 comece em um endereço
* que é multipo de 4 byte a partir do inicio (alinha 4 em 4 bytes do início do método), após o 
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
	int byte_preechimento, match_offset;
	uint32_t defaultbyte = 0, low = 0, high = 0;	//variaveis (operandos) de tabela de salto de tableswitch


	byte_preechimento = (4 - (*i % 4)) % 4;
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
	int byte_preenchimento;

	// printf("i = %d\n", *i);
	byte_preenchimento = (4 - (*i % 4)) % 4;

	// printf("byte_preenchimento = %d\n", byte_preenchimento);
	//preenche code[] com bytes de preenchimento
	for(int x = 0; x < byte_preenchimento; x++){
		(*att_code)->code[*i] = ler_u1(fp);
		(*i)++;
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
	for(uint32_t x = 0; x < npairs; x++){
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

void pega_operandos(AllIns /*decoder*/ *decode, FILE *fp, int opcode, AT_Code **att_code, uint32_t *i){

	mount_inst_array(decode);
	//init_decoder(decode);
	int n_bytes = decode[opcode].bytes;

	//percorre os n_bytes para pegar os operandos
	//printf("N-BYTES === %d\n", n_bytes);
	 for(int x = 0; x < n_bytes; x++){
	 	(*att_code)->code[*i] = ler_u1(fp);
	 	(*i)++;
	 }
}

/*Na tabela code[]:
* As instuções lookupswitch, tableswitch e wide são as 3 três instruções que requerem
* tratamento diferentes, ou seja, são instruções especias, todas as outras instruções documentadas
* devem aparecer no array code[]. 
* A funçao checa e chama funções auxiliares para cada uma das instruçoes citadas acima.
*/
void verifica_instrucao(AT_Code **att_code, FILE *fp){
	int opcode;
	
	AllIns decode[NUM_INSTRUC];
	// decoder decode[NUM_INSTRUC];
	

	//code fornece byte atual da jvm que implementa o method
	//aloca espaço que conterá o bytecode da jvm que implementam o código desse metodo
	(*att_code)->code = (uint8_t *) malloc(sizeof(uint8_t) * (*att_code)->code_length);

	//SALVAR AS INSTRUÇÕES DO METODO
	//Enquanto tiver byte, trata o bytecode

	for(uint32_t i = 0; i < (*att_code)->code_length; ){
		(*att_code)->code[i] = ler_u1(fp);	//pega o bytecode que é o opcode.

		opcode = (*att_code)->code[i];
		i++;	//posição seguinte para leitura do byte de preenchimeto que esta entre 0 e 3 bytes

		switch(opcode){
			case TABLESWITCH:
				if_tableswitch(&i, fp, att_code);
				break;
			case LOOKUPSWITCH:
				if_lookupswitch(&i, fp, att_code);
				break;
			case WIDE:
				if_wide(&i, fp, att_code, &opcode);
				break;
			default:
				pega_operandos(decode, fp, opcode, att_code, &i);
				break;
		}
	}
}

AT_Code ler_Att_code(AT_Code **code_att, FILE *fp, uint16_t name_ind){
	AT_Code *out = (*code_att);


	//pega o indice do nome do atributo e comprimento
	out->attribute_name_index = name_ind;
	// out->attribute_length = att_len;
	out->attribute_length = ler_u4(fp);

	int pos_init = ftell(fp);	//pega a posição atual do ponteiro no arquivo fp


	out->max_stack = ler_u2(fp);	//Informação da profundidade maxima da pilha de operando durante a execução do mento
	out->max_locals = ler_u2(fp);	//número de variaveis locais (inclui os paramemtros) do vetor de var. locais
	out->code_length = ler_u4(fp);	//numero de bytes no seu array code[] (deve ser maior que zero)
	
	verifica_instrucao(&(out), fp);
	
	
	out->exception_table_length = ler_u2(fp);
	//dereference_index_UTF8(out->exception_table_length, constPool);
	out->EXC_table = (exception_table *) malloc(sizeof(exception_table) * out->exception_table_length);

	//para cada entrada entrada na tabela de exception, lê os dados referentes
	for(int i = 0; i < out->exception_table_length; i++){
		out->EXC_table[i].start_pc = ler_u2(fp);		//
		out->EXC_table[i].end_pc = ler_u2(fp);			//
		out->EXC_table[i].handler_pc = ler_u2(fp);
		out->EXC_table[i].catch_type = ler_u2(fp);		//
	}

	out->attributes_count = ler_u2(fp);

	out->attributes = (attribute_info *) malloc(sizeof(attribute_info) * (out)->attributes_count);
	//começa a partir da posição atual do arquivo e lê o restante dos operandos
	for (int i = (ftell(fp) - pos_init); i < out->attribute_length; i++)
		ler_u1(fp);

	// printf("out->attribute_length - %d\n", out->attribute_length);
	while(ftell(fp) - pos_init < (int32_t)(out->attribute_length)){
		/*out->attributes[i]*/ ler_u1(fp);
	}

	return *out;
}

AT_Exceptions ler_att_excp(AT_Exceptions **att_excp, FILE *fp, uint16_t name_ind){
	AT_Exceptions *out = (*att_excp);

	//pega name index e index length
	out->attribute_name_index = name_ind;
	out->attribute_length = ler_u4(fp);

	//numero de exceptions
	out->number_of_exceptions = ler_u2(fp);

	//aloca espaço para qtd de exceptions
	out->exception_index_table = (uint16_t *) malloc(sizeof(exception_table) * out->number_of_exceptions);

	//mostra as exceptions, não preenche a tabela(deveria?? não sei).
	for(int x = 0; x < out->number_of_exceptions; x++){
		printf("%x\n", ler_u2(fp));
	}

	return *out;
}

/*AT_ConstantValue ler_att_ctv(FILE *cp, cp_info constPool, cFile cf){
	AT_ConstantValue out;

	out.attribute_name_index = ler_u2(fp);		//pega o index de referencia para tabela de constPool que referencia o nome do atributo
	out.attribute_length = ler_u4(fp);			//pega o tamanho em byte do restante do atributo (não inclui os 6 bytes que contem o indice do nome e o comprimento do atributo)

	out.
}
*/
/*Lê os fields*/
field_info ler_fields (FILE *fp, cp_info *constPool){
	field_info out;

	out.access_flags = ler_u2(fp) & 0x0df;
	out.name_index = ler_u2(fp);
	out.descriptor_index = ler_u2(fp);
	out.attribute_count = ler_u2(fp);

	//verificar o tipo de attribute, se for (constantValue)
	if(out.attribute_count != 0){
		out.att_ctv = (AT_ConstantValue *) malloc(sizeof(AT_ConstantValue) * out.attribute_count);
		for(int i = 0; i < out.attribute_count; i++){
			//out.att_ctv[i] = ler_attribute(fp, constPool, cf);
		}
	}

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
method_info ler_methods(FILE *fp, cp_info *constPool){
	method_info ret;
	
	uint16_t name_ind;					//name_index auxiliar para atributo

	ret.access_flags = ler_u2(fp);			//pega o flag
	ret.name_index = ler_u2(fp);			//pega index de referencia para tabeal constPool que referencia o nome do metodo
	ret.descriptor_index = ler_u2(fp);		//pega index de referencia para tabeal constPool que referencia um descritor do metodo
	ret.attributes_count = ler_u2(fp);		//pega o número de atributos do metodo
	
	/*printf("access_flags = ");
	dereference_index_UTF8(ret.access_flags, constPool);
	printf("name_index = ");
	dereference_index_UTF8(ret.name_index, constPool);
	printf("\n");
	printf("descriptor_index = ");
	dereference_index_UTF8(ret.descriptor_index, constPool);
	printf("\n");
	printf("attributes_count = %d\n", ret.attributes_count);*/

	for (int i = 0; i < ret.attributes_count; i++){

		name_ind = ler_u2(fp);

		// printf("%s\n", (char *) constPool[name_ind].info[1].array);
		// checa se é atributo Code:
		if(strcmp((char *) constPool[name_ind].info[1].array, "Code") == 0){
			ret.att_code = (AT_Code *) malloc(sizeof(AT_Code));	//aloca memoria para o atributo Code
			ler_Att_code(&(ret.att_code), fp, name_ind);		//le o Code

		}else if(strcmp((char *) constPool[name_ind].info[1].array, "Exception") == 0){
			//aloca espaço adequado
			//chama função para tratar exceptions
			ret.att_excp = (AT_Exceptions *) malloc(sizeof(AT_Exceptions));
			ler_att_excp(&(ret.att_excp), fp, name_ind);
		}
	}
	return ret;
}


/*carrega e mostra todas interfaces que estão presentes.*/
void loadInterfaces(uint16_t *interfaces, int interfaces_count, cp_info *constPool, FILE *fp){

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

		for (int i = 0; i < classFile.fields_count; ++i)
			classFile.fields[i] = ler_fields(fp, classFile.constant_pool);
	}


	classFile.methods_count = ler_u2(fp);
	if(classFile.methods_count != 0){
		classFile.methods = (method_info*) malloc (sizeof(method_info)*classFile.methods_count);

		for (int j = 0; j < classFile.methods_count; j++)
			classFile.methods[j] = ler_methods(fp, classFile.constant_pool);
	}

	classFile.attributes_count = ler_u2(fp);
	if(classFile.attributes_count != 0){
		classFile.attributes = (attribute_info *) malloc (sizeof(attribute_info) * classFile.attributes_count);
		for (int i = 0; i < classFile.attributes_count; i++){
			classFile.attributes[i] = ler_attribute(fp, classFile.constant_pool, classFile);
		}
	}


	
	/*Mostra as informações basicas como magic number, minversion...etc*/

	infoBasic(classFile);
	/*chama a função para mostrar as flags ativas*/
	show_flags(classFile.access_flags, splitFlags);
	/*Exibe informações de Pool de constante*/
	showConstPool(classFile.constant_pool_count, classFile.constant_pool); 
	
	for(int i = 0; i < classFile.methods_count; i++){
		printf ("\n	Method [%d]:\n", i);
		show_methods(classFile.constant_pool, classFile.methods[i]);
	}

	for(int i = 0; i < classFile.fields_count; i++){
		printf("\n\tFields[%d]:\n", i);
		show_fields(classFile.constant_pool, classFile.fields[i]);
	}

	
	return 0;
}

int findMain (cFile classFile){

	int i;

	while (i<classFile.methods_count){
		if (strcmp((char *)classFile.constant_pool[(classFile.methods[i].name_index)].info[1].array, "main")==0){
			return i;
		}
		i++;
	}
	return -1;
}
