#define INSTRUCTIONS_SERVER
#include "../headers/instructions.h"
// #include "../headers/leitor.h" 


void mount_inst_array(AllIns *instructions){
	
	//instructions[0].ins(); //Chamada para a execução da instrução
	
	char vec_strings[256][20];
	
	//******************************************************************
	//CONSTANTES
	
	strcpy(vec_strings[0], "nop");
	strcpy(vec_strings[1], "aconst_null");
	strcpy(vec_strings[2], "iconst_m1");
	strcpy(vec_strings[3], "iconst_0");
	strcpy(vec_strings[4], "iconst_1");
	strcpy(vec_strings[5], "iconst_2");
	strcpy(vec_strings[6], "iconst_3");
	strcpy(vec_strings[7], "iconst_4");
	strcpy(vec_strings[8], "iconst_5");
	strcpy(vec_strings[9], "lconst_0");
	strcpy(vec_strings[10], "lconst_1");
	strcpy(vec_strings[11], "fconst_0");
	strcpy(vec_strings[12], "fconst_1");
	strcpy(vec_strings[13], "fconst_2");
	strcpy(vec_strings[14], "dconst_0");
	strcpy(vec_strings[15], "dconst_1");
	strcpy(vec_strings[16], "bipush");
	strcpy(vec_strings[17], "sipush");
	strcpy(vec_strings[18], "ldc");
	strcpy(vec_strings[19], "ldc_w");
	strcpy(vec_strings[20], "ldc2_w");
	
	//******************************************************************
	//LOADS
	
	strcpy(vec_strings[21], "iload");
	strcpy(vec_strings[22], "lload");
	strcpy(vec_strings[23], "fload");
	strcpy(vec_strings[24], "dload");
	strcpy(vec_strings[25], "aload");
	strcpy(vec_strings[26], "iload_0");
	strcpy(vec_strings[27], "iload_1");
	strcpy(vec_strings[28], "iload_2");
	strcpy(vec_strings[29], "iload_3");
	strcpy(vec_strings[30], "lload_0");
	strcpy(vec_strings[31], "lload_1");
	strcpy(vec_strings[32], "lload_2");
	strcpy(vec_strings[33], "lload_3");
	strcpy(vec_strings[34], "fload_0");
	strcpy(vec_strings[35], "fload_1");
	strcpy(vec_strings[36], "fload_2");
	strcpy(vec_strings[37], "fload_3");
	strcpy(vec_strings[38], "dload_0");
	strcpy(vec_strings[39], "dload_1");
	strcpy(vec_strings[40], "dload_2");
	strcpy(vec_strings[41], "dload_3");
	strcpy(vec_strings[42], "aload_0");
	strcpy(vec_strings[43], "aload_1");
	strcpy(vec_strings[44], "aload_2");
	strcpy(vec_strings[45], "aload_3");
	strcpy(vec_strings[46], "iaload");
	strcpy(vec_strings[47], "laload");
	strcpy(vec_strings[48], "faload");
	strcpy(vec_strings[49], "daload");
	strcpy(vec_strings[50], "aaload");
	strcpy(vec_strings[51], "baload");
	strcpy(vec_strings[52], "caload");
	strcpy(vec_strings[53], "saload");
	
	//******************************************************************
	//STORES
	
	strcpy(vec_strings[54], "istore");
	strcpy(vec_strings[55], "lstore");
	strcpy(vec_strings[56], "fstore");
	strcpy(vec_strings[57], "dstore");
	strcpy(vec_strings[58], "astore");
	strcpy(vec_strings[59], "istore_0");
	strcpy(vec_strings[60], "istore_1");
	strcpy(vec_strings[61], "istore_2");
	strcpy(vec_strings[62], "istore_3");
	strcpy(vec_strings[63], "lstore_0");
	strcpy(vec_strings[64], "lstore_1");
	strcpy(vec_strings[65], "lstore_2");
	strcpy(vec_strings[66], "lstore_3");
	strcpy(vec_strings[67], "fstore_0");
	strcpy(vec_strings[68], "fstore_1");
	strcpy(vec_strings[69], "fstore_2");
	strcpy(vec_strings[70], "fstore_3");
	strcpy(vec_strings[71], "dstore_0");
	strcpy(vec_strings[72], "dstore_1");
	strcpy(vec_strings[73], "dstore_2");
	strcpy(vec_strings[74], "dstore_3");
	strcpy(vec_strings[75], "astore_0");
	strcpy(vec_strings[76], "astore_1");
	strcpy(vec_strings[77], "astore_2");
	strcpy(vec_strings[78], "astore_3");
	strcpy(vec_strings[79], "iastore");
	strcpy(vec_strings[80], "lastore");
	strcpy(vec_strings[81], "fastore");
	strcpy(vec_strings[82], "dastore");
	strcpy(vec_strings[83], "aastore");
	strcpy(vec_strings[84], "bastore");
	strcpy(vec_strings[85], "castore");
	strcpy(vec_strings[86], "sastore");
	
	//******************************************************************
	//PILHA
	
	strcpy(vec_strings[87], "pop");
	strcpy(vec_strings[88], "pop2");
	strcpy(vec_strings[89], "dup");
	strcpy(vec_strings[90], "dup_x1");
	strcpy(vec_strings[91], "dup_x2");
	strcpy(vec_strings[92], "dup2");
	strcpy(vec_strings[93], "dup2_x1");
	strcpy(vec_strings[94], "dup2_x2");
	strcpy(vec_strings[95], "swap");
	
	//******************************************************************
	//OPERAÇÕES MATEMÁTICAS
	
	strcpy(vec_strings[96], "iadd");
	strcpy(vec_strings[97], "ladd");
	strcpy(vec_strings[98], "fadd");
	strcpy(vec_strings[99], "dadd");
	strcpy(vec_strings[100], "isub");
	strcpy(vec_strings[101], "lsub");
	strcpy(vec_strings[102], "fsub");
	strcpy(vec_strings[103], "dsub");
	strcpy(vec_strings[104], "imul");
	strcpy(vec_strings[105], "lmul");
	strcpy(vec_strings[106], "fmul");
	strcpy(vec_strings[107], "dmul");
	strcpy(vec_strings[108], "idiv");
	strcpy(vec_strings[109], "ldiv");
	strcpy(vec_strings[110], "fdiv");
	strcpy(vec_strings[111], "ddiv");
	strcpy(vec_strings[112], "irem");
	strcpy(vec_strings[113], "lrem");
	strcpy(vec_strings[114], "frem");
	strcpy(vec_strings[115], "drem");
	strcpy(vec_strings[116], "ineg");
	strcpy(vec_strings[117], "lneg");
	strcpy(vec_strings[118], "fneg");
	strcpy(vec_strings[119], "dneg");
	strcpy(vec_strings[120], "ishl");
	strcpy(vec_strings[121], "lshl");
	strcpy(vec_strings[122], "ishr");
	strcpy(vec_strings[123], "lshr");
	strcpy(vec_strings[124], "iushr");
	strcpy(vec_strings[125], "lushr");
	strcpy(vec_strings[126], "iand");
	strcpy(vec_strings[127], "land");
	strcpy(vec_strings[128], "ior");
	strcpy(vec_strings[129], "lor");
	strcpy(vec_strings[130], "ixor");
	strcpy(vec_strings[131], "lxor");
	strcpy(vec_strings[132], "iin");
	
	//******************************************************************
	//CONVERSÕES
	
	strcpy(vec_strings[133], "i2l");
	strcpy(vec_strings[134], "i2f");
	strcpy(vec_strings[135], "i2d");
	strcpy(vec_strings[136], "l2i");
	strcpy(vec_strings[137], "l2f");
	strcpy(vec_strings[138], "l2d");
	strcpy(vec_strings[139], "f2i");
	strcpy(vec_strings[140], "f2l");
	strcpy(vec_strings[141], "f2d");
	strcpy(vec_strings[142], "d2i");
	strcpy(vec_strings[143], "d2l");
	strcpy(vec_strings[144], "d2f");
	strcpy(vec_strings[145], "i2b");
	strcpy(vec_strings[146], "i2c");
	strcpy(vec_strings[147], "i2s");
	
	//******************************************************************
	//COMPARAÇÕES
	
	strcpy(vec_strings[148], "lcmp");
	strcpy(vec_strings[149], "fcmpl");
	strcpy(vec_strings[150], "fcmpg");
	strcpy(vec_strings[151], "dcmpl");
	strcpy(vec_strings[152], "dcmpg");
	strcpy(vec_strings[153], "ifeq");
	strcpy(vec_strings[154], "ifne");
	strcpy(vec_strings[155], "iflt");
	strcpy(vec_strings[156], "ifge");
	strcpy(vec_strings[157], "ifgt");
	strcpy(vec_strings[158], "ifle");
	strcpy(vec_strings[159], "if_icmpeq");
	strcpy(vec_strings[160], "if_icmpne");
	strcpy(vec_strings[161], "if_icmplt");
	strcpy(vec_strings[162], "if_icmpge");
	strcpy(vec_strings[163], "if_icmpgt");
	strcpy(vec_strings[164], "if_icmple");
	strcpy(vec_strings[165], "if_acmpeq");
	strcpy(vec_strings[166], "if_acmpne");
	
	//******************************************************************
	//CONTROLE
	
	strcpy(vec_strings[167], "goto");
	strcpy(vec_strings[168], "jsr");
	strcpy(vec_strings[169], "ret");
	strcpy(vec_strings[170], "tableswitch");
	strcpy(vec_strings[171], "lookupswitch");
	strcpy(vec_strings[172], "ireturn");
	strcpy(vec_strings[173], "lreturn");
	strcpy(vec_strings[174], "freturn");
	strcpy(vec_strings[175], "dreturn");
	strcpy(vec_strings[176], "areturn");
	strcpy(vec_strings[177], "return");
	
	//******************************************************************
	//REFERÊNCIAS
	
	strcpy(vec_strings[178], "getstatic");
	strcpy(vec_strings[179], "putstatic");
	strcpy(vec_strings[180], "getfield");
	strcpy(vec_strings[181], "putfield");
	strcpy(vec_strings[182], "invokevirtual");
	strcpy(vec_strings[183], "invokespecial");
	strcpy(vec_strings[184], "invokestatic");
	strcpy(vec_strings[185], "invokeinterface");
	strcpy(vec_strings[186], "invokedynamic");
	strcpy(vec_strings[187], "new");
	strcpy(vec_strings[188], "newarray");
	strcpy(vec_strings[189], "anewarray");
	strcpy(vec_strings[190], "arraylength");
	strcpy(vec_strings[191], "athrow");
	strcpy(vec_strings[192], "checkcast");
	strcpy(vec_strings[193], "instanceof");
	strcpy(vec_strings[194], "monitorenter");
	strcpy(vec_strings[195], "monitorexit");
	
	//******************************************************************
	//EXTENDIDO
	
	strcpy(vec_strings[196], "wide");
	strcpy(vec_strings[197], "multianewarray");
	strcpy(vec_strings[198], "ifnull");
	strcpy(vec_strings[199], "ifnonnull");
	strcpy(vec_strings[200], "goto_w");
	strcpy(vec_strings[201], "jsr_w");
	
	//******************************************************************
	//CONSTANTES
	
  	instructions[0].ins = nop;		instructions[0].bytes = 0;
  	instructions[1].ins = aconst_null;	instructions[1].bytes = 0;
  	instructions[2].ins = iconst_m1;	instructions[2].bytes = 0;
  	instructions[3].ins = iconst_0;		instructions[3].bytes = 0;
  	instructions[4].ins = iconst_1;		instructions[4].bytes = 0;
  	instructions[5].ins = iconst_2;		instructions[5].bytes = 0;
	instructions[6].ins = iconst_3;		instructions[6].bytes = 0;
  	instructions[7].ins = iconst_4;		instructions[7].bytes = 0;
  	instructions[8].ins = iconst_5;		instructions[8].bytes = 0;
  	instructions[9].ins = lconst_0;		instructions[9].bytes = 0;
  	instructions[10].ins = lconst_1;	instructions[10].bytes = 0;
  	instructions[11].ins = fconst_0;	instructions[11].bytes = 0;
  	instructions[12].ins = fconst_1;	instructions[12].bytes = 0;
  	instructions[13].ins = fconst_2;	instructions[13].bytes = 0;
  	instructions[14].ins = dconst_0;	instructions[14].bytes = 0;
  	instructions[15].ins = dconst_1;	instructions[15].bytes = 0;
  	instructions[16].ins = bipush;		instructions[16].bytes = 1;
  	instructions[17].ins = sipush;		instructions[17].bytes = 2;
  	instructions[18].ins = ldc;		instructions[18].bytes = 1;
  	instructions[19].ins = ldc_w;		instructions[19].bytes = 2;
  	instructions[20].ins = ldc2_w;		instructions[20].bytes = 2;
	
	//******************************************************************
	//LOADS
	
	instructions[21].ins = iload;		instructions[21].bytes = 1;
	instructions[22].ins = lload;		instructions[22].bytes = 1;
	instructions[23].ins = fload;		instructions[23].bytes = 1;
	instructions[24].ins = dload;		instructions[24].bytes = 1;
	instructions[25].ins = aload;		instructions[25].bytes = 1;
	instructions[26].ins = iload_0;		instructions[26].bytes = 0;
	instructions[27].ins = iload_1;		instructions[27].bytes = 0;
	instructions[28].ins = iload_2;		instructions[28].bytes = 0;
	instructions[29].ins = iload_3;		instructions[29].bytes = 0;
	instructions[30].ins = lload_0;		instructions[30].bytes = 0;
	instructions[31].ins = lload_1;		instructions[31].bytes = 0;
	instructions[32].ins = lload_2;		instructions[32].bytes = 0;
	instructions[33].ins = lload_3;		instructions[33].bytes = 0;
	instructions[34].ins = fload_0;		instructions[34].bytes = 0;
	instructions[35].ins = fload_1;		instructions[35].bytes = 0;
	instructions[36].ins = fload_2;		instructions[36].bytes = 0;
	instructions[37].ins = fload_3;		instructions[37].bytes = 0;
	instructions[38].ins = dload_0;		instructions[38].bytes = 0;
	instructions[39].ins = dload_1;		instructions[39].bytes = 0;
	instructions[40].ins = dload_2;		instructions[40].bytes = 0;
	instructions[41].ins = dload_3;		instructions[41].bytes = 0;
	instructions[42].ins = aload_0;		instructions[42].bytes = 0;
	instructions[43].ins = aload_1;		instructions[43].bytes = 0;
	instructions[44].ins = aload_2;		instructions[44].bytes = 0;
	instructions[45].ins = aload_3;		instructions[45].bytes = 0;
	instructions[46].ins = iaload;		instructions[46].bytes = 0;
	instructions[47].ins = laload;		instructions[47].bytes = 0;
	instructions[48].ins = faload;		instructions[48].bytes = 0;
	instructions[49].ins = daload;		instructions[49].bytes = 0;
	instructions[50].ins = aaload;		instructions[50].bytes = 0;
	instructions[51].ins = baload;		instructions[51].bytes = 0;
	instructions[52].ins = caload;		instructions[52].bytes = 0;
	instructions[53].ins = saload;		instructions[53].bytes = 0;
	
	//******************************************************************
	//STORES
	
	instructions[54].ins = istore;		instructions[54].bytes = 1;
	instructions[55].ins = lstore;		instructions[55].bytes = 1;
	instructions[56].ins = fstore;		instructions[56].bytes = 1;
	instructions[57].ins = dstore;		instructions[57].bytes = 1;
	instructions[58].ins = astore;		instructions[58].bytes = 1;
	instructions[59].ins = istore_0;	instructions[59].bytes = 0;
	instructions[60].ins = istore_1;	instructions[60].bytes = 0;
	instructions[61].ins = istore_2;	instructions[61].bytes = 0;
	instructions[62].ins = istore_3;	instructions[62].bytes = 0;
	instructions[63].ins = lstore_0;	instructions[63].bytes = 0;
	instructions[64].ins = lstore_1;	instructions[64].bytes = 0;
	instructions[65].ins = lstore_2;	instructions[65].bytes = 0;
	instructions[66].ins = lstore_3;	instructions[66].bytes = 0;
	instructions[67].ins = fstore_0;	instructions[67].bytes = 0;
	instructions[68].ins = fstore_1;	instructions[68].bytes = 0;
	instructions[69].ins = fstore_2;	instructions[69].bytes = 0;
	instructions[70].ins = fstore_3;	instructions[70].bytes = 0;
	instructions[71].ins = dstore_0;	instructions[71].bytes = 0;
	instructions[72].ins = dstore_1;	instructions[72].bytes = 0;
	instructions[73].ins = dstore_2;	instructions[73].bytes = 0;
	instructions[74].ins = dstore_3;	instructions[74].bytes = 0;
	instructions[75].ins = astore_0;	instructions[75].bytes = 0;
	instructions[76].ins = astore_1;	instructions[76].bytes = 0;
	instructions[77].ins = astore_2;	instructions[77].bytes = 0;
	instructions[78].ins = astore_3;	instructions[78].bytes = 0;
	instructions[79].ins = iastore;		instructions[79].bytes = 0;
	instructions[80].ins = lastore;		instructions[80].bytes = 0;
	instructions[81].ins = fastore;		instructions[81].bytes = 0;
	instructions[82].ins = dastore;		instructions[82].bytes = 0;
	instructions[83].ins = aastore;		instructions[83].bytes = 0;
	instructions[84].ins = bastore;		instructions[84].bytes = 0;
	instructions[85].ins = castore;		instructions[85].bytes = 0;
	instructions[86].ins = sastore;		instructions[86].bytes = 0;
	
	//******************************************************************
	//PILHA
	
// 	instructions[87].ins = pop;		instructions[87].bytes = 0;
// 	instructions[88].ins = pop2;		instructions[88].bytes = 0;
// 	instructions[89].ins = dup;		instructions[89].bytes = 0;
// 	instructions[90].ins = dup_x1;		instructions[90].bytes = 0;
// 	instructions[91].ins = dup_x2;		instructions[91].bytes = 0;
// 	instructions[92].ins = dup2;		instructions[92].bytes = 0;
// 	instructions[93].ins = dup2_x1;		instructions[93].bytes = 0;
// 	instructions[94].ins = dup2_x2;		instructions[94].bytes = 0;
// 	instructions[95].ins = swap;		instructions[95].bytes = 0;
	
	//******************************************************************
	//OPERAÇÕES MATEMÁTICAS	
	
	instructions[96].ins = iadd;		instructions[96].bytes = 0;
	instructions[97].ins = ladd;		instructions[97].bytes = 0;
	instructions[98].ins = fadd;		instructions[98].bytes = 0;
	instructions[99].ins = dadd;		instructions[99].bytes = 0;
	instructions[100].ins = isub;		instructions[100].bytes = 0;
	instructions[101].ins = lsub;		instructions[101].bytes = 0;
	instructions[102].ins = fsub;		instructions[102].bytes = 0;
	instructions[103].ins = dsub;		instructions[103].bytes = 0;
	instructions[104].ins = imul;		instructions[104].bytes = 0;
	instructions[105].ins = lmul;		instructions[105].bytes = 0;
	instructions[106].ins = fmul;		instructions[106].bytes = 0;
	instructions[107].ins = dmul;		instructions[107].bytes = 0;
	instructions[108].ins = idiv;		instructions[108].bytes = 0;
	instructions[109].ins = ldiv_;		instructions[109].bytes = 0;
	instructions[110].ins = fdiv;		instructions[110].bytes = 0;
	instructions[111].ins = ddiv;		instructions[111].bytes = 0;
	instructions[112].ins = irem;		instructions[112].bytes = 0;
	instructions[113].ins = lrem;		instructions[111].bytes = 0;
	instructions[114].ins = frem;		instructions[114].bytes = 0;
	instructions[115].ins = drem_;	instructions[115].bytes = 0;
	instructions[116].ins = ineg;		instructions[116].bytes = 0;
	instructions[117].ins = lneg;		instructions[117].bytes = 0;
	instructions[118].ins = fneg;		instructions[118].bytes = 0;
	instructions[119].ins = dneg;		instructions[119].bytes = 0;
	instructions[120].ins = ishl;		instructions[120].bytes = 0;
	instructions[121].ins = lshl;		instructions[121].bytes = 0;
	instructions[122].ins = ishr;		instructions[122].bytes = 0;
	instructions[123].ins = lshr;		instructions[123].bytes = 0;
	instructions[124].ins = iushr;		instructions[124].bytes = 0;
	instructions[125].ins = lushr;		instructions[125].bytes = 0;
	instructions[126].ins = iand;		instructions[126].bytes = 0;
	instructions[127].ins = land;		instructions[127].bytes = 0;
	instructions[128].ins = ior;		instructions[128].bytes = 0;
	instructions[129].ins = lor;		instructions[129].bytes = 0;
	instructions[130].ins = ixor;		instructions[130].bytes = 0;
	instructions[131].ins = lxor;		instructions[131].bytes = 0;
	instructions[132].ins = iinc;		instructions[132].bytes = 2;
	
	//******************************************************************
	//CONVERSÕES
	
	instructions[133].ins = i2l;		instructions[133].bytes = 0;
	instructions[134].ins = i2f;		instructions[134].bytes = 0;
	instructions[135].ins = i2d;		instructions[135].bytes = 0;
	instructions[136].ins = l2i;		instructions[136].bytes = 0;
	instructions[137].ins = l2f;		instructions[137].bytes = 0;
	instructions[138].ins = l2d;		instructions[138].bytes = 0;
	instructions[139].ins = f2i;		instructions[139].bytes = 0;
	instructions[140].ins = f2l;		instructions[140].bytes = 0;
	instructions[141].ins = f2d;		instructions[141].bytes = 0;
	instructions[142].ins = d2i;		instructions[142].bytes = 0;
	instructions[143].ins = d2l;		instructions[143].bytes = 0;
	instructions[144].ins = d2f;		instructions[144].bytes = 0;
	instructions[145].ins = i2b;		instructions[145].bytes = 0;
	instructions[146].ins = i2c;		instructions[146].bytes = 0;
	instructions[147].ins = i2s;		instructions[147].bytes = 0;
	
	//******************************************************************
	//COMPARAÇÕES
		
	instructions[148].ins = lcmp;		instructions[148].bytes = 0;
	instructions[149].ins = fcmpl;		instructions[149].bytes = 0;
	instructions[150].ins = fcmpg;		instructions[148].bytes = 0;
	instructions[151].ins = dcmpl;		instructions[151].bytes = 0;
	instructions[152].ins = dcmpg;		instructions[152].bytes = 0;
	instructions[153].ins = ifeq;		instructions[153].bytes = 2;
	instructions[154].ins = ifne;		instructions[154].bytes = 2;
	instructions[155].ins = iflt;		instructions[155].bytes = 2;
	instructions[156].ins = ifge;		instructions[156].bytes = 2;
	instructions[157].ins = ifgt;		instructions[157].bytes = 2;
	instructions[158].ins = ifle;		instructions[158].bytes = 2;
	instructions[159].ins = if_icmpeq;	instructions[159].bytes = 2;
	instructions[160].ins = if_icmpne;	instructions[160].bytes = 2;
	instructions[161].ins = if_icmplt;	instructions[161].bytes = 2;
	instructions[162].ins = if_icmpge;	instructions[162].bytes = 2;
	instructions[163].ins = if_icmpgt;	instructions[163].bytes = 2;
	instructions[164].ins = if_icmple;	instructions[164].bytes = 2;
	instructions[165].ins = if_acmpeq;	instructions[165].bytes = 2;
	instructions[166].ins = if_acmpne;	instructions[166].bytes = 2;
	
	//******************************************************************
	//CONTROLE
	
	instructions[167].ins = goto_;		instructions[167].bytes = 2;
	instructions[168].ins = jsr;		instructions[168].bytes = 2;
	instructions[169].ins = ret;		instructions[169].bytes = 1;
	instructions[170].ins = tableswitch;	instructions[170].bytes = 14; //CONFIRMAR
	instructions[171].ins = lookupswitch;	instructions[171].bytes = 10; //CONFIRMAR
	instructions[172].ins = ireturn;	instructions[172].bytes = 0;
	instructions[173].ins = lreturn;	instructions[173].bytes = 0;
	instructions[174].ins = freturn;	instructions[174].bytes = 0;
	instructions[175].ins = dreturn;	instructions[175].bytes = 0;
	instructions[176].ins = areturn;	instructions[176].bytes = 0;
	instructions[177].ins = return_;	instructions[177].bytes = 0;
	
	//******************************************************************
	//REFERÊNCIAS
	
	instructions[178].ins = getstatic;	instructions[178].bytes = 2;
	instructions[179].ins = putstatic;	instructions[179].bytes = 2;
	instructions[180].ins = getfield;	instructions[180].bytes = 2;
	instructions[181].ins = putfield;	instructions[181].bytes = 2;
	instructions[182].ins = invokevirtual;	instructions[182].bytes = 2;
	instructions[183].ins = invokespecial;	instructions[183].bytes = 2;
	instructions[184].ins = invokestatic;	instructions[184].bytes = 2;
	instructions[185].ins = invokeinterface;instructions[185].bytes = 4;
// 	instructions[186].ins = invokedynamic;	instructions[186].bytes = 4;
	instructions[187].ins = new_;		instructions[187].bytes = 2;
	instructions[188].ins = newarray;	instructions[188].bytes = 1;
	instructions[189].ins = anewarray;	instructions[189].bytes = 2;
	instructions[190].ins = arraylength;	instructions[190].bytes = 0;
// 	instructions[191].ins = athrow;		instructions[191].bytes = 0;
// 	instructions[192].ins = checkcast;	instructions[192].bytes = 2;
// 	instructions[193].ins = instanceof;	instructions[193].bytes = 2;
// 	instructions[194].ins = monitorenter;	instructions[194].bytes = 0;
// 	instructions[195].ins = monitorexit;	instructions[195].bytes = 0;
	
	//******************************************************************
	//EXTENDIDO
	
	instructions[196].ins = wide;		instructions[196].bytes = 3; //PODE SER 5 TAMBÉM DEPENDENDO DO OPCODE, FAZER A EXCESSÃO DEPOIS
	instructions[197].ins = multianewarray;	instructions[197].bytes = 3;
	instructions[198].ins = ifnull;		instructions[198].bytes = 2;
	instructions[199].ins = ifnonnull;	instructions[199].bytes = 2;
	instructions[200].ins = goto_w;		instructions[200].bytes = 4;
	instructions[201].ins = jsr_w;		instructions[201].bytes = 4;

 	for (int i=0; i < 202; i++){
  		instructions[i].hexa = i;
		strcpy(instructions[i].name, vec_strings[i]);
 	}
	
	//******************************************************************
	//OPCODES RESERVADOS -> Não podem aparecer em aquivos .class válidos
	//Usado para debug e pra implementar breakpoints
	instructions[202].hexa = 0xCA;
	strcpy(instructions[202].name, "breakpoint");
	
	//Instruções para fornecer backdoor
	instructions[254].hexa = 0xFE;
 	strcpy(instructions[254].name, "impdep1");
	instructions[255].hexa = 0xFF;
	strcpy(instructions[255].name, "impdep2");
	
}

void internal_error(){ printf("InternalError\n"); exit(0);}

void out_of_mem(){ printf("OutOfMemoryError\n"); exit(0);}

void stack__ovflw_error(){ printf("StackOverflowError\n"); exit(0);}

void unkwn_err(){ printf("UnknownError\n"); exit(0);}

//CONSTANTES
void nop(){return;}
void aconst_null(){return;}
void iconst_m1(){return;}
void iconst_0(){return;}
void iconst_1(){return;}
void iconst_2(){return;}
void iconst_3(){return;}
void iconst_4(){return;}
void iconst_5(){return;}
void lconst_0(){return;}
void lconst_1(){return;}
void fconst_0(){return;}
void fconst_1(){return;}
void fconst_2(){return;}
void dconst_0(){return;}
void dconst_1(){return;}
void bipush(){return;}
void sipush(){return;}
void ldc(){return;}
void ldc_w(){return;}
void ldc2_w(){return;}

//LOADS
void iload(){return;}
void lload(){return;}
void fload(){return;}
void dload(){return;}
void aload(){return;}
void iload_0(){return;}
void iload_1(){return;}
void iload_2(){return;}
void iload_3(){return;}
void lload_0(){return;}
void lload_1(){return;}
void lload_2(){return;}
void lload_3(){return;}
void fload_0(){return;}
void fload_1(){return;}
void fload_2(){return;}
void fload_3(){return;}
void dload_0(){return;}
void dload_1(){return;}
void dload_2(){return;}
void dload_3(){return;}
void aload_0(){return;}
void aload_1(){return;}
void aload_2(){return;}
void aload_3(){return;}
void iaload(){return;}
void laload(){return;}
void faload(){return;}
void daload(){return;}
void aaload(){return;}
void baload(){return;}
void caload(){return;}
void saload(){return;}

//STORES
void istore(){return;}
void lstore(){return;}
void fstore(){return;}
void dstore(){return;}
void astore(){return;}
void istore_0(){return;}
void istore_1(){return;}
void istore_2(){return;}
void istore_3(){return;}
void lstore_0(){return;}
void lstore_1(){return;}
void lstore_2(){return;}
void lstore_3(){return;}
void fstore_0(){return;}
void fstore_1(){return;}
void fstore_2(){return;}
void fstore_3(){return;}
void dstore_0(){return;}
void dstore_1(){return;}
void dstore_2(){return;}
void dstore_3(){return;}
void astore_0(){return;}
void astore_1(){return;}
void astore_2(){return;}
void astore_3(){return;}
void iastore(){return;}
void lastore(){return;}
void fastore(){return;}
void dastore(){return;}
void aastore(){return;}
void bastore(){return;}
void castore(){return;}
void sastore(){return;}

//OPERAÇÕES MATEMÁTICAS
void iadd(){return;}
void ladd(){return;}
void fadd(){return;}
void dadd(){return;}
void isub(){return;}
void lsub(){return;}
void fsub(){return;}
void dsub(){return;}
void imul(){return;}
void lmul(){return;}
void fmul(){return;}
void dmul(){return;}
void idiv(){return;}
void ldiv_(){return;}
void fdiv(){return;}
void ddiv(){return;}
void irem(){return;}
void lrem(){return;}
void frem(){return;}
void drem_(){return;}
void ineg(){return;}
void lneg(){return;}
void fneg(){return;}
void dneg(){return;}
void ishl(){return;}
void lshl(){return;}
void ishr(){return;}
void lshr(){return;}
void iushr(){return;}
void lushr(){return;}
void iand(){return;}
void land(){return;}
void ior(){return;}
void lor(){return;}
void ixor(){return;}
void lxor(){return;}
void iinc(){return;}

//CONVERSÕES
void i2l(){return;}
void i2f(){return;}
void i2d(){return;}
void l2i(){return;}
void l2f(){return;}
void l2d(){return;}
void f2i(){return;}
void f2l(){return;}
void f2d(){return;}
void d2i(){return;}
void d2l(){return;}
void d2f(){return;}
void i2b(){return;}
void i2c(){return;}
void i2s(){return;}

//COMPARAÇÕES
void lcmp(){return;}
void fcmpl(){return;}
void fcmpg(){return;}
void dcmpl(){return;}
void dcmpg(){return;}
void ifeq(){return;}
void ifne(){return;}
void iflt(){return;}
void ifge(){return;}
void ifgt(){return;}
void ifle(){return;}
void if_icmpeq(){return;}
void if_icmpne(){return;}
void if_icmplt(){return;}
void if_icmpge(){return;}
void if_icmpgt(){return;}
void if_icmple(){return;}
void if_acmpeq(){return;}
void if_acmpne(){return;}

//CONTROLES
void goto_(){return;}
void jsr(){return;}
void ret(){return;}
void tableswitch(){return;}
void lookupswitch(){return;}
void ireturn(){return;}
void lreturn(){return;}
void freturn(){return;}
void dreturn(){return;}
void areturn(){return;}
void return_(){return;}

//REFERÊNCIAS
void getstatic(){return;}
void putstatic(){return;}
void getfield(){return;}
void putfield(){return;}
void invokevirtual(){return;}
void invokespecial(){return;}
void invokestatic(){return;}
void invokeinterface(){return;}
// void invokedynamic(){return;}
void new_(){return;}
void newarray(){return;}
void anewarray(){return;}
void arraylength(){return;}
// void athrow(){return;}
// void checkcast(){return;}
// void instanceof(){return;}
// void monitorenter(){return;}
// void monitorexit(){return;}

//EXTENDIDO
void wide(){return;}
void multianewarray(){return;}
void ifnull(){return;}
void ifnonnull(){return;}
void goto_w(){return;}
void jsr_w(){return;}