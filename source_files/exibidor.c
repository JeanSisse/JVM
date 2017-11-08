#define EXIBIDOR_SERVER
#include "../headers/exibidor.h"
#include "../headers/instructions.h"

/*CONSTANTES PARA FORMATAÇÃO DOS DADOS*/
const char *flag_name [5] = {"ACC_PUBLIC", "ACC_FINAL", "ACC_SUPER", "ACC_INTERFACE", "ACC_ABSTRACT"};
const char *type_Names [12] = {"UFT8_info", "-", "Integer_info", "Float_info", "Long_info", "Double_info", "Class_info", "String_info", "Fieldref_info", "Methodref_info", "Interface_info", "Name and Type"};

/*show_UTF8: monta e mostringa a stringing UTF8*/
void show_UTF8 (int size, unsigned char *string){
	int i = 0;

	/*printf("   ");*/
	while(i < size){ 	/*enquanto tiver byte no array de bytes*/
		if(!(string[i] & 0x80)){ 	/*1 byte para utf-8: Se inverso é true, então caracter é representado por 0, ou seja, o bit 7 é 0*/
			printf("%c", string[i]);
		}else{	/*Caso não esteja na faixa dos caracteres "usuais"*/
			unsigned short aux;
			if(!(string[i+1] & 0x20)){	/* para utf8 de 2 bytes */
				aux = ((string[i] & 0xf) << 6) + ((string[i+1] & 0x3f));
			}else{	/*para utf8 de 3 byte*/
				aux = ((string[i] & 0xf) << 12) + ((string[i+1] & 0x3f) << 6) + (string[i + 2] & 0x3f);
				i++;
			}
			i++;
			printf("%d", aux);
		}
		i++;
	}
}

void infoBasic(cFile classFile){

	printf("Informações gerais:\n\n");
	printf ("\tMagic number: 0x%x\n", classFile.magic);
	printf("\tMinVersion = %d\n", classFile.minor_version);
	printf("\tMajVersion = %d\n", classFile.major_version);
	printf("\tConstant pool count: %d\n", classFile.constant_pool_count);
	printf("\tthis_class_info: ");
	/*Exibe a informação (string) da classe*/
	dereference_index_UTF8(classFile.this_class, classFile.constant_pool);
	printf("\n");
	printf("\tsuper_class_info: ");
	/*Exibe a informação (string) da super_classe*/
	dereference_index_UTF8(classFile.super_class, classFile.constant_pool);
	printf("\n");
	printf("\tField count: %d\n", classFile.fields_count);
	printf("\tMethod count: %d\n", classFile.methods_count);

}

/* A recebe a qtd de constantes presentes na tabela do CP
** e ponteiro para a tabela dos constantes.
** Percorre a tabela e exibe toda a informação contida nela.
** %d|%d mostringa os indices na estringutura seguido das informações
** relacionadas aos stringings nas outras estringuturas.*/
void showConstPool(int const_pool_cont, cp_info *constPool){

	printf("Pool de Constantes:\n");

	for(int i = 1; i < const_pool_cont; i++){
		printf("\t[%d] = %s", i, type_Names[constPool[i].tag-1]);

		switch(constPool[i].tag){
			case UTF8: /*tem um campo u2 e um array u1 como info*/
				printf("\t\t");
				show_UTF8(constPool[i].info[0].u2, constPool[i].info[1].array);
				break;
			
			case FLOAT:
				printf("\t%f", convert_u4_toFloat(constPool[i].info[0]));
				break;

			case INTEGER:
				printf("\t%d", constPool[i].info[0].u4);
				break;

			case LONG:
				printf("\t%ld", convert_u4_toLong(constPool[i].info[0], constPool[i].info[1]));
				break;
			
			case DOUBLE:
				printf("\t%lf", convert_u4_toDouble(constPool[i].info[0], constPool[i].info[1]));
				break;
			case CLASS:
			case STRING:
				printf("   \t\t#%d\t\t", constPool[i].info[0].u2);
				dereference_index_UTF8 (i, constPool);
				break;

			case INTERFACE_REF:
			case FIELD_REF:
			case METHOD_REF:
				printf("  \t\t#%d|#%d\t", constPool[i].info[0].u2, constPool[i].info[1].u2);
				dereference_index_UTF8(i, constPool);
				break;

			case NAME_AND_TYPE:
				printf("  \t\t#%d|#%d\t",  constPool[i].info[0].u2, constPool[i].info[1].u2);
				dereference_index_UTF8(i, constPool);
				break;
		}
		printf("\n");
	}
}


/*Verifica flags ativas e mostringa.*/
void show_flags(uint16_t access_flags, bool *flags){
	bool first = true; /*Apenas para exibir a mensagem "Flags" uma vez na tela.*/

	for (int i = 0; i < 5; ++i){
		if(flags[i]){
			if(first){
				printf("	ACcess flags: 0x%04x", access_flags);
			}else{
				printf("]");
			}
			first = false;
			printf("[%s", flag_name[i]);
		}
	}
	printf("]\n");
}



/*mostringa as flags do campo verificando todas as flags presentes no field*/
void show_field_flags(unsigned short flags){
	bool first = true;

	if(flags & 0x01){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_PUBLIC]");
	}

	if(flags & 0x02){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_PRIVATE]");
	}

	if(flags & 0x04){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_PROTECTED]");
	}

	if(flags & 0x08){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_STATIC]");
	}

	if(flags & 0x010){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_FINAL]");
	}

	if(flags & 0x0040){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_VOLATILE]");
	}

	if(flags & 0x0080){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_TRANSIENT]");
	}

	if(flags & 0x1000){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_SYNTHETIC]");
	}

	if(flags & 0x4000){
		if(first){
			printf(" \tFlags: ");
			first = false;
		}else{
			printf(", ");
		}
		printf("[ACC_ENUM]");
	}

	printf("\n");
}



void show_field_attribute(cp_info *cp, AT_Code att_code){
	int i = 0;
	AllIns decode[NUM_INSTRUC];
	mount_inst_array(decode);

	printf(" \n\tNome do atributo: ");
	dereference_index_UTF8(att_code.attribute_name_index, cp);

	printf("\n");
	printf(" \tAttribute length: %d\n", att_code.attribute_length);

	/*Completar a função para diferente tipos de atributo*/
	if(strcmp((char *) cp[att_code.attribute_name_index].info[1].array, "Code") == 0){
		printf("\tmax_stack = %d\n", att_code.max_stack);
		printf("\tmax_locals = %d\n", att_code.max_locals);
		printf("\tcode_length = %d\n", att_code.code_length);
		printf("\topcde = %x\n", att_code.code[i]);
		printf("\tInstrução: %s\n", decode[att_code.code[i]].name);
		
		for(int i = 1; i < att_code.code_length; ){

			if(att_code.code[i] == TABLESWITCH){
				printf("TABLESWITCH...\n");
			}else if(att_code.code[i] == LOOKUPSWITCH){
				printf("LOOKUPSWITCH...\n");
			}else if(att_code.code[i] == WIDE){
				printf("WIDE...\n");
				i++;
				if(att_code.code[i] == IINC){
					printf("IINC...\n");
					i++;
				}else if(att_code.code[i] == ALOAD || att_code.code[i] == FLOAD || att_code.code[i] == ILOAD || att_code.code[i] == DLOAD || \
						att_code.code[i] == ISTORE || att_code.code[i] == LSTORE || att_code.code[i] == ASTORE || att_code.code[i] == FSTORE || \
						att_code.code[i] == RET || att_code.code[i] == DSTORE || att_code.code[i] == LLOAD)
				{
					printf("ALGUM I/FLOAD...\n");
					i++;
				}
			}else if(decode[att_code.code[i]].bytes != 0){
				printf("\toperando: %d\n", att_code.code[i]);
				i++;
			}else{
				i++;
			}
		}
	}
}

/*Mostringa um field*/
void show_fields (cp_info *cp, field_info fields){
	/*mostra flags*/
	show_field_flags(fields.access_flags);

	printf(" \tNome do campo: ");
	dereference_index_UTF8(fields.name_index, cp);
	printf("\n");

	printf(" \tDescriptor do campo: ");
	dereference_index_UTF8(fields.descriptor_index, cp);
	printf("\n");

	printf(" \tNumero de atributos: %d\n", fields.attribute_count);
	for (int i = 0; i < fields.attribute_count; ++i){
		printf(" Atributo[%d]: ", i);
		//show_field_attribute(cp, fields.attributes[i]);
	}
}

void show_method_flags(unsigned short flags){
	/*bool first = true;*/

	if(flags & 0x0001){
		printf("[ACC_PUBLIC] ");
	}
	if(flags & 0x0002){
		printf("[ACC_PRIVATE] ");
	}
	if(flags & 0x0004){
		printf("[ACC_PROTECTED] ");
	}
	if(flags & 0x0008){
		printf("[ACC_STATIC] ");
	}
	if(flags & 0x0010){
		printf("[ACC_FINAL] ");
	}
	if(flags & 0x0020){
		printf("[ACC_SYNCHRONIZED] ");
	}
	if(flags & 0x0040){
		printf("[ACC_BRIDGE] ");
	}
	if(flags & 0x0080){
		printf("[ACC_VARARGS] ");
	}
	if(flags & 0x0100){
		printf("[ACC_NATIVE] ");
	}
	if(flags & 0x0400){
		printf("[ACC_ABstringACT] ");
	}
	if(flags & 0x0800){
		printf("[ACC_stringICT] ");
	}
	if(flags & 0x1000){
		printf("[ACC_SYNTHETIC] ");
	}
}

void show_methods(cp_info *cp, method_info method){


	printf ("	access_flags: 0x%04x", method.access_flags);
	show_method_flags(method.access_flags);
	printf ("\n");
	printf ("	Name_index: ");
	dereference_index_UTF8(method.name_index, cp);
	printf ("\n");
	printf ("	Descriptor_index: ");
	dereference_index_UTF8(method.descriptor_index, cp);
	printf ("\n");
	printf ("	attribute_count: %d", method.attributes_count);
	printf ("\n");
	for (int i = 0; i < method.attributes_count; ++i){
		printf("\tAtributo [%d]: ", i+1);
		show_field_attribute(cp, method.att_code[i]);
		printf("\n");
	}
}

