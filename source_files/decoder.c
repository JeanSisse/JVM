#define DECODER_SERVER

#include "../headers/decoder.h"

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