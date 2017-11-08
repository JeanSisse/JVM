#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../headers/instructions.h"

#ifndef LEITOR
	#define LEITOR

	#ifdef LEITOR_SERVER
		#define EXT_LEITOR
	#else
		#define EXT_LEITOR extern
	#endif

	//#include "../headers/decoder.h"

	/*struct de uniao para armazenar todos os tamanhos de variavel que serao lidos*/
	typedef union {
		uint8_t *array;		/*Ponteiro para uma strig*/
		uint8_t u1; 		/*para armazenar leitura de um byte*/
		uint16_t u2;		/*para armazenar leitura de dois byte*/
		uint32_t u4;		/*para armazenar leitura de quatro byte*/
	}classLoadrType;

	/* Structs que serao uteis */
	typedef struct {
		uint8_t tag;
		classLoadrType *info;
	}cp_info;

	typedef struct {
		uint16_t attribute_name_index;
		uint32_t attribute_length;
		uint8_t *info;
	}attribute_info;

	typedef struct{
		uint16_t start_pc;
		uint16_t end_pc;
		uint16_t handler_pc;
		uint16_t catch_type;
	}exception_table;

	typedef struct{
		uint16_t attribute_name_index;		//index para nome do atributo na tabela de constPool
		uint32_t attribute_length;			//numero de bytes desse atributo
		uint16_t max_stack;
		uint16_t max_locals;
		uint32_t code_length;				//numeor de bytes no seu array code (deve ser maior que zero)
		uint8_t *code;						//bytecode da jvm que implementam o código desse metodo
		uint16_t exception_table_length;
		exception_table *EXC_table;
		uint16_t attributes_count;			//numero de atributos associados ao atributo "Code" de um metodo
		attribute_info *attributes;			//possíveis existencias de atributos opcionais associado ao atributo code
	}AT_Code;

	typedef struct{
		uint16_t attribute_name_index;
		uint32_t attribute_length;
		uint16_t number_of_exceptions;
		uint16_t *exception_index_table;
	}AT_Exceptions;

	typedef struct {
		uint16_t access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		attribute_info *attributes;
		AT_Code *att_code;
		AT_Exceptions *att_excp;
	}method_info;

	typedef struct {
		uint16_t access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attribute_count;
		attribute_info *attributes;
	} field_info;

	typedef struct{
		uint16_t attribute_name_index;
		uint32_t attribute_length;
		uint16_t constantvalue_index;
	}AT_ConstantValue;
	

	typedef struct{}AT_InnerClasses;

	typedef struct{
		uint32_t magic;
		uint16_t minor_version;
		uint16_t major_version;
		uint16_t constant_pool_count;
		cp_info *constant_pool;
		uint16_t access_flags;
		uint16_t this_class;
		uint16_t super_class;
		uint16_t interfaces_count;
		uint16_t *interfaces;
		uint16_t fields_count;
		field_info *fields;
		uint16_t methods_count;
		method_info *methods;
		uint16_t attributes_count;
		attribute_info *attributes;
	}cFile;



	#define	INSTRUC_NAME	35

	typedef struct {
		char instruc[INSTRUC_NAME];
		int bytes;
		void (*ins)(); 
	}decoder;




	/*DEFINIÇÃO PARA TRATAMENTO DE POSSIVEIS ERROS*/
	#define MISSING_ARGUMENT 1
	#define CANT_OPEN 		 2
	#define INVALID_FILE 	 3
	#define UNKNOWN_TYPE 	 4

	/*NUMERO DE INSTRUÇÃO PARA ENTRADA DO VETOR DECODE*/
	#define NUM_INSTRUC		256	 //DEFINE 255 POSIÇÕES NO ARRAY DE INSTRUÇÕES

	/*INSTRUÇÕES ESPECIAIS*/
	#define TABLESWITCH		0xAA
	#define WIDE			0xC4
	#define LOOKUPSWITCH 	0xAB

	//INSTRUÇÕES PARA WIDE
	//FORMATO 1
	#define ILOAD	0x15
	#define LLOAD	0x16
	#define FLOAD	0x17
	#define DLOAD	0x18
	#define ALOAD	0x19
	#define ISTORE	0x36
	#define LSTORE	0x37
	#define FSTORE	0x38
	#define DSTORE	0x39
	#define ASTORE	0x3a
	#define RET		0xa9

	//FORMATO 2
	#define IINC	0x84

	EXT_LEITOR int init_leitor(FILE *fp);
	EXT_LEITOR uint8_t ler_u1 (FILE *fp);
	EXT_LEITOR int loadInfConstPool (cp_info *constPool, int const_pool_cont, FILE *fp);
	EXT_LEITOR void dereference_index_UTF8 (int index, cp_info *cp);
	EXT_LEITOR float convert_u4_toFloat(classLoadrType ent);
	EXT_LEITOR long convert_u4_toLong (classLoadrType entHigh, classLoadrType entLow);
	EXT_LEITOR double convert_u4_toDouble(classLoadrType entHigh, classLoadrType entLow);
	EXT_LEITOR void loadInterfaces(uint16_t *interfaces, int interfaces_count, cp_info *constPool, FILE *fp);
	EXT_LEITOR uint8_t *ler_UTF8 (int size, FILE *fp);
	EXT_LEITOR uint32_t ler_u4(FILE *fp);
	EXT_LEITOR uint16_t ler_u2 (FILE *fp);
	EXT_LEITOR attribute_info ler_attribute(FILE *fp, cp_info *constPool, cFile cf);
	EXT_LEITOR method_info ler_methods(FILE *fp, cp_info *constPool, cFile cf);
	EXT_LEITOR field_info ler_fields (FILE *fp, cp_info *constPool, cFile cf);
	EXT_LEITOR AT_Code ler_Att_code(AT_Code **code_att, FILE *fp, uint16_t name_ind, uint32_t att_len, cp_info *constPool);
	EXT_LEITOR int findMain (cFile classFile);
	EXT_LEITOR void verifica_instrucao(AT_Code **att_code, FILE *fp, cp_info *constPool);
	EXT_LEITOR void if_tableswitch(uint32_t *i, FILE *fp, AT_Code **att_code);
	EXT_LEITOR void if_lookupswitch(uint32_t *i, FILE *fp, AT_Code **att_code);
	EXT_LEITOR void if_wide(uint32_t *i, FILE *fp, AT_Code **att_code, int *opcode);
	EXT_LEITOR void pega_operandos(AllIns/*decoder*/ decode[], FILE *fp, int opcode, AT_Code **att_code, uint32_t *i);
	EXT_LEITOR void init_decoder(decoder decode[]);
	EXT_LEITOR AT_Exceptions ler_att_excp(AT_Exceptions **att_excp, FILE *fp, uint16_t name_ind, uint32_t att_len, cp_info *constPool);
#endif