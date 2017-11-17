#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "../headers/leitor.h"

#ifndef EXIBIDOR
	#define EXIBIDOR

	#ifdef EXIBIDOR_SERVER
		#define EXT_EXIBIDOR
	#else
		#define EXT_EXIBIDOR extern
	#endif
	

	/*DEFINIÇÃO DOS TIPOS POSSIVEIS DE TAGS NO POOL DE CONSTANTES*/
	#define UTF8 			1
	#define INTEGER 		3
	#define FLOAT 			4
	#define LONG 			5
	#define DOUBLE 			6
	#define CLASS 			7
	#define STRING 			8
	#define FIELD_REF 		9
	#define METHOD_REF  	10
	#define INTERFACE_REF 	11
	#define NAME_AND_TYPE 	12

	EXT_EXIBIDOR void infoBasic(cFile classFile);
	EXT_EXIBIDOR void show_method_flags(unsigned short flags);
	EXT_EXIBIDOR void show_UTF8 (int size, unsigned char *str);
	EXT_EXIBIDOR void showConstPool(int const_pool_cont, cp_info *constPool);
	EXT_EXIBIDOR void show_flags(uint16_t access_flags, bool *flags);
	EXT_EXIBIDOR void show_methods(cp_info *cp, method_info method);
	EXT_EXIBIDOR void show_field_flags(unsigned short flags);
	EXT_EXIBIDOR void show_method_attribute(cp_info *cp, AT_Code att_code);
	EXT_EXIBIDOR void show_field_attribute(cp_info *cp, AT_ConstantValue att_cvt);
	EXT_EXIBIDOR void show_fields(cp_info *cp, field_info field);
	EXT_EXIBIDOR void show_info();
	
#endif