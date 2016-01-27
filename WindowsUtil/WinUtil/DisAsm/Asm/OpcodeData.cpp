#include "OpcodeData.h"
extern RegOrOperandGroup Operands[] =
{
	/*0*/{ H_1,NULL }, // 1
	/*1*/{ SPC_AH_R12L,NULL }, // AH/R12L
	/*2*/{ REG_AL,NULL }, // AL
	/*3*/{ SPC_AL_R8L,NULL }, // AL/R8L
	/*4*/{ SPC_AL_rAX,NULL }, // AL/rAX
	/*5*/{ H_A,L_p }, // Ap
	/*6*/{ SPC_BH_R15L,NULL }, // BH/R15L
	/*7*/{ SPC_BL_R11L,NULL }, // BL/R11L
	/*8*/{ H_B,L_y }, // By
	/*9*/{ H_C,L_d }, // Cd
	/*10*/{ SPC_CH_R13L,NULL }, // CH/R13L
	/*11*/{ REG_CL,NULL }, // CL
	/*12*/{ SPC_CL_R9L,NULL }, // CL/R9L
	/*13*/{ SEG_CS,NULL }, // CS
	/*14*/{ H_D,L_d }, // Dd
	/*15*/{ SPC_DH_R14L,NULL }, // DH/R14L
	/*16*/{ SPC_DL_R10L,NULL }, // DL/R10L
	/*17*/{ SEG_DS,NULL }, // DS
	/*18*/{ REG_DX,NULL }, // DX
	/*19*/{ REG_EAX,CHANGE_REG }, // eAX
	/*20*/{ H_E,L_b }, // Eb
	/*21*/{ REG_EBP,CHANGE_REG }, // eBP
	/*22*/{ REG_EBX,CHANGE_REG }, // eBX
	/*23*/{ REG_ECX,CHANGE_REG }, // eCX
	/*24*/{ H_E,L_d }, // Ed
	/*25*/{ REG_EDI,CHANGE_REG }, // eDI
	/*26*/{ REG_EDX,CHANGE_REG }, // eDX
	/*27*/{ H_E,L_p }, // Ep
	/*28*/{ SEG_ES,NULL }, // ES
	/*29*/{ REG_ESI,CHANGE_REG }, // eSI
	/*30*/{ REG_ESP,CHANGE_REG }, // eSP
	/*31*/{ H_E,L_v }, // Ev
	/*32*/{ H_E,L_w }, // Ew
	/*33*/{ H_E,L_y }, // Ey
	/*34*/{ SEG_FS,NULL }, // FS
	/*35*/{ H_F,L_v }, // Fv
	/*36*/{ H_G,L_b }, // Gb
	/*37*/{ H_G,L_d }, // Gd
	/*38*/{ SEG_GS,NULL }, // GS
	/*39*/{ H_G,L_v }, // Gv
	/*40*/{ H_G,L_w }, // Gw
	/*41*/{ H_G,L_y }, // Gy
	/*42*/{ H_G,L_z }, // Gz
	/*43*/{ H_H,L_dq }, // Hdq
	/*44*/{ H_H,L_pd }, // Hpd
	/*45*/{ H_H,L_ps }, // Hps
	/*46*/{ H_H,L_q }, // Hq
	/*47*/{ H_H,L_qq }, // Hqq
	/*48*/{ H_H,L_sd }, // Hsd
	/*49*/{ H_H,L_ss }, // Hss
	/*50*/{ H_H,L_x }, // Hx
	/*51*/{ H_I,L_b }, // Ib
	/*52*/{ SPC_Ib_Iz,NULL }, // Ib/Iz
	/*53*/{ H_I,L_v }, // Iv
	/*54*/{ H_I,L_w }, // Iw
	/*55*/{ H_I,L_z }, // Iz
	/*56*/{ H_J,L_b }, // Jb
	/*57*/{ H_J,L_z }, // Jz
	/*58*/{ H_L,L_x }, // Lx
	/*59*/{ H_M,NULL }, // M
	/*60*/{ H_M,L_a }, // Ma
	/*61*/{ H_M,L_b }, // Mb
	/*62*/{ H_M,L_dq }, // Mdq
	/*63*/{ H_M,L_p }, // Mp
	/*64*/{ H_M,L_pd }, // Mpd
	/*65*/{ H_M,L_ps }, // Mps
	/*66*/{ H_M,L_q }, // Mq
	/*67*/{ H_M,L_s }, // Ms
	/*68*/{ H_M,L_w }, // Mw
	/*69*/{ SPC_Mw_Rv,NULL }, // Mw/Rv
	/*70*/{ H_M,L_x }, // Mx
	/*71*/{ H_M,L_y }, // My
	/*72*/{ H_N,L_q }, // Nq
	/*73*/{ H_O,L_b }, // Ob
	/*74*/{ H_O,L_v }, // Ov
	/*75*/{ H_P,L_d }, // Pd
	/*76*/{ H_P,L_pi }, // Ppi
	/*77*/{ H_P,L_q }, // Pq
	/*78*/{ H_Q,L_d }, // Qd
	/*79*/{ H_Q,L_pi }, // Qpi
	/*80*/{ H_Q,L_q }, // Qq
	/*81*/{ REG_R8,CHANGE_REG }, // r8
	/*82*/{ REG_RAX,CHANGE_REG }, // rAX
	/*83*/{ SPC_RAX_EAX_R8_R8D,NULL }, // RAX/EAX/R8/R8D
	/*84*/{ SPC_rAX_r8,NULL }, // rAX/r8
	/*85*/{ SPC_RBP_EBP_R13_R13D,NULL }, // RBP/EBP/R13/R13D
	/*86*/{ SPC_rBP_r13,NULL }, // rBP/r13
	/*87*/{ SPC_RBX_EBX_R11_R11D,NULL }, // RBX/EBX/R11/R11D
	/*88*/{ SPC_rBX_r11,NULL }, // rBX/r11
	/*89*/{ SPC_RCX_ECX_R9_R9D,NULL }, // RCX/ECX/R9/R9D
	/*90*/{ SPC_rCX_r9,NULL }, // rCX/r9
	/*91*/{ H_R,L_d }, // Rd
	/*92*/{ SPC_Rd_Mb,NULL }, // Rd/Mb
	/*93*/{ SPC_Rd_Mw,NULL }, // Rd/Mw
	/*94*/{ SPC_RDI_EDI_R15_R15D,NULL }, // RDI/EDI/R15/R15D
	/*95*/{ SPC_rDI_r15,NULL }, // rDI/r15
	/*96*/{ REG_RDX,CHANGE_REG }, // rDX
	/*97*/{ SPC_RDX_EDX_R10_R10D,NULL }, // RDX/EDX/R10/R10D
	/*98*/{ SPC_rDX_r10,NULL }, // rDX/r10
	/*99*/{ SPC_RSI_ESI_R14_R14D,NULL }, // RSI/ESI/R14/R14D
	/*100*/{ SPC_rSI_r14,NULL }, // rSI/r14
	/*101*/{ SPC_RSP_ESP_R12_R12D,NULL }, // RSP/ESP/R12/R12D
	/*102*/{ SPC_rSP_r12,NULL }, // rSP/r12
	/*103*/{ H_R,L_v }, // Rv
	/*104*/{ SPC_Rv_Mw,NULL }, // Rv/Mw
	/*105*/{ H_R,L_y }, // Ry
	/*106*/{ SPC_Ry_Mb,NULL }, // Ry/Mb
	/*107*/{ SPC_Ry_Mw,NULL }, // Ry/Mw
	/*108*/{ SEG_SS,NULL }, // SS
	/*109*/{ H_S,L_w }, // Sw
	/*110*/{ H_U,L_dq }, // Udq
	/*111*/{ SPC_Udq_Md,NULL }, // Udq/Md
	/*112*/{ H_U,L_pd }, // Upd
	/*113*/{ H_U,L_ps }, // Ups
	/*114*/{ H_U,L_q }, // Uq
	/*115*/{ H_U,L_x }, // Ux
	/*116*/{ SPC_Ux_Md,NULL }, // Ux/Md
	/*117*/{ SPC_Ux_Mq,NULL }, // Ux/Mq
	/*118*/{ SPC_Ux_Mw,NULL }, // Ux/Mw
	/*119*/{ H_V,L_dq }, // Vdq
	/*120*/{ H_V,L_pd }, // Vpd
	/*121*/{ H_V,L_ps }, // Vps
	/*122*/{ H_V,L_q }, // Vq
	/*123*/{ H_V,L_qq }, // Vqq
	/*124*/{ H_V,L_sd }, // Vsd
	/*125*/{ H_V,L_ss }, // Vss
	/*126*/{ H_V,L_x }, // Vx
	/*127*/{ H_V,L_y }, // Vy
	/*128*/{ H_W,L_d }, // Wd
	/*129*/{ H_W,L_dq }, // Wdq
	/*130*/{ H_W,L_pd }, // Wpd
	/*131*/{ H_W,L_ps }, // Wps
	/*132*/{ H_W,L_q }, // Wq
	/*133*/{ H_W,L_qq }, // Wqq
	/*134*/{ H_W,L_sd }, // Wsd
	/*135*/{ H_W,L_ss }, // Wss
	/*136*/{ H_W,L_x }, // Wx
	/*137*/{ H_X,L_b }, // Xb
	/*138*/{ H_X,L_v }, // Xv
	/*139*/{ H_X,L_z }, // Xz
	/*140*/{ H_Y,L_b }, // Yb
	/*141*/{ H_Y,L_v }, // Yv
	/*142*/{ H_Y,L_z }, // Yz
};
extern LPCSTR InstructionNames[] =
{
	/*  0*/ "(prefix/addresssize)", 	// Len:1
	/*  1*/ "(prefix/lock)", 	// Len:1
	/*  2*/ "(prefix/operandsize)", 	// Len:1
	/*  3*/ "(prefix/repnexacquire)", 	// Len:1
	/*  4*/ "(prefix/repxrelease/repexrelease)", 	// Len:1
	/*  5*/ "(prefix/rex)", 	// Len:1
	/*  6*/ "(prefix/rex.b)", 	// Len:1
	/*  7*/ "(prefix/rex.r)", 	// Len:1
	/*  8*/ "(prefix/rex.rb)", 	// Len:1
	/*  9*/ "(prefix/rex.rx)", 	// Len:1
	/* 10*/ "(prefix/rex.rxb)", 	// Len:1
	/* 11*/ "(prefix/rex.w)", 	// Len:1
	/* 12*/ "(prefix/rex.wb)", 	// Len:1
	/* 13*/ "(prefix/rex.wr)", 	// Len:1
	/* 14*/ "(prefix/rex.wrb)", 	// Len:1
	/* 15*/ "(prefix/rex.wrx)", 	// Len:1
	/* 16*/ "(prefix/rex.wrxb)", 	// Len:1
	/* 17*/ "(prefix/rex.wx)", 	// Len:1
	/* 18*/ "(prefix/rex.wxb)", 	// Len:1
	/* 19*/ "(prefix/rex.x)", 	// Len:1
	/* 20*/ "(prefix/rex.xb)", 	// Len:1
	/* 21*/ "(prefix/seg=cs)", 	// Len:1
	/* 22*/ "(prefix/seg=ds)", 	// Len:1
	/* 23*/ "(prefix/seg=es)", 	// Len:1
	/* 24*/ "(prefix/seg=fs)", 	// Len:1
	/* 25*/ "(prefix/seg=gs)", 	// Len:1
	/* 26*/ "(prefix/seg=ss)", 	// Len:1
	/* 27*/ "(prefix/vex+1byte)", 	// Len:1
	/* 28*/ "(prefix/vex+2byte)", 	// Len:1
	/* 29*/ "aaa", 	// Len:1
	/* 30*/ "aad", 	// Len:1
	/* 31*/ "aam", 	// Len:1
	/* 32*/ "aas", 	// Len:1
	/* 33*/ "adc", 	// Len:1
	/* 34*/ "adcx", 	// Len:1
	/* 35*/ "add", 	// Len:1
	/* 36*/ "adox", 	// Len:1
	/* 37*/ "and", 	// Len:1
	/* 38*/ "andn", 	// Len:1
	/* 39*/ "arpl", 	// Len:1
	/* 40*/ "bextr", 	// Len:1
	/* 41*/ "blendvpd", 	// Len:1
	/* 42*/ "blendvps", 	// Len:1
	/* 43*/ "blsi", 	// Len:1
	/* 44*/ "blsmsk", 	// Len:1
	/* 45*/ "blsr", 	// Len:1
	/* 46*/ "bound", 	// Len:1
	/* 47*/ "bsf", 	// Len:1
	/* 48*/ "bsr", 	// Len:1
	/* 49*/ "bswap", 	// Len:1
	/* 50*/ "bt", 	// Len:1
	/* 51*/ "btc", 	// Len:1
	/* 52*/ "btr", 	// Len:1
	/* 53*/ "bts", 	// Len:1
	/* 54*/ "bzhi", 	// Len:1
	/* 55*/ "call", 	// Len:1
	/* 56*/ "cbw", 	// Len:3 
	/* 57*/ "cwde",
	/* 58*/ "cdqe",
	/* 59*/ "clac", 	// Len:1
	/* 60*/ "clc", 	// Len:1
	/* 61*/ "cld", 	// Len:1
	/* 62*/ "clflush", 	// Len:1
	/* 63*/ "cli", 	// Len:1
	/* 64*/ "clts", 	// Len:1
	/* 65*/ "cmc", 	// Len:1
	/* 66*/ "cmova", 	// Len:2 
	/* 67*/ "cmovnbe",
	/* 68*/ "cmovae", 	// Len:3 
	/* 69*/ "cmovnb",
	/* 70*/ "cmovnc",
	/* 71*/ "cmovb", 	// Len:3 
	/* 72*/ "cmovc",
	/* 73*/ "cmovnae",
	/* 74*/ "cmovbe", 	// Len:2 
	/* 75*/ "cmovna",
	/* 76*/ "cmove", 	// Len:2 
	/* 77*/ "cmovz",
	/* 78*/ "cmovl", 	// Len:2 
	/* 79*/ "cmovnge",
	/* 80*/ "cmovle", 	// Len:2 
	/* 81*/ "cmovng",
	/* 82*/ "cmovne", 	// Len:2 
	/* 83*/ "cmovnz",
	/* 84*/ "cmovnl", 	// Len:2 
	/* 85*/ "cmovge",
	/* 86*/ "cmovnle", 	// Len:2 
	/* 87*/ "cmovg",
	/* 88*/ "cmovno", 	// Len:1
	/* 89*/ "cmovnp", 	// Len:2 
	/* 90*/ "cmovpo",
	/* 91*/ "cmovns", 	// Len:1
	/* 92*/ "cmovo", 	// Len:1
	/* 93*/ "cmovp", 	// Len:2 
	/* 94*/ "cmovpe",
	/* 95*/ "cmovs", 	// Len:1
	/* 96*/ "cmp", 	// Len:1
	/* 97*/ "cmps", 	// Len:2 Type:Size
	/* 98*/ "cmpsb",
	/* 99*/ "cmps", 	// Len:3 Type:Size
	/*100*/ "cmpsw",
	/*101*/ "cmpsd",
	/*102*/ "cmpxch8b", 	// Len:1
	/*103*/ "cmpxchg", 	// Len:1
	/*104*/ "cmpxchg16b", 	// Len:1
	/*105*/ "cpuid", 	// Len:1
	/*106*/ "crc32", 	// Len:1
	/*107*/ "cvtpd2pi", 	// Len:1
	/*108*/ "cvtpi2pd", 	// Len:1
	/*109*/ "cvtpi2ps", 	// Len:1
	/*110*/ "cvtps2pi", 	// Len:1
	/*111*/ "cvttpd2pi", 	// Len:1
	/*112*/ "cvttps2pi", 	// Len:1
	/*113*/ "cwd", 	// Len:3 
	/*114*/ "cdq",
	/*115*/ "cqo",
	/*116*/ "daa", 	// Len:1
	/*117*/ "das", 	// Len:1
	/*118*/ "dec", 	// Len:1
	/*119*/ "div", 	// Len:1
	/*120*/ "emms", 	// Len:1
	/*121*/ "enter", 	// Len:1
	/*122*/ "fwait", 	// Len:2 
	/*123*/ "wait",
	/*124*/ "fxrstor", 	// Len:1
	/*125*/ "fxsave", 	// Len:1
	/*126*/ "getsec", 	// Len:1
	/*127*/ "hlt", 	// Len:1
	/*128*/ "idiv", 	// Len:1
	/*129*/ "imul", 	// Len:1
	/*130*/ "in", 	// Len:1
	/*131*/ "inc", 	// Len:1
	/*132*/ "ins", 	// Len:2 Type:Size
	/*133*/ "insb",
	/*134*/ "ins", 	// Len:3 Type:Size
	/*135*/ "insw",
	/*136*/ "insd",
	/*137*/ "int", 	// Len:1
	/*138*/ "int3", 	// Len:1
	/*139*/ "into", 	// Len:1
	/*140*/ "invd", 	// Len:1
	/*141*/ "invept", 	// Len:1
	/*142*/ "invlpg", 	// Len:1
	/*143*/ "invpcid", 	// Len:1
	/*144*/ "invvpid", 	// Len:1
	/*145*/ "iret", 	// Len:3 Type:Size
	/*146*/ "iretd",
	/*147*/ "iretq",
	/*148*/ "ja", 	// Len:2 
	/*149*/ "jnbe",
	/*150*/ "jae", 	// Len:3 
	/*151*/ "jnb",
	/*152*/ "jnc",
	/*153*/ "jb", 	// Len:3 
	/*154*/ "jnae",
	/*155*/ "jc",
	/*156*/ "jb", 	// Len:2 
	/*157*/ "jcnae",
	/*158*/ "jbe", 	// Len:2 
	/*159*/ "jna",
	/*160*/ "je", 	// Len:2 
	/*161*/ "jz",
	/*162*/ "jl", 	// Len:2 
	/*163*/ "jnge",
	/*164*/ "jle", 	// Len:2 
	/*165*/ "jng",
	/*166*/ "jmp", 	// Len:1
	/*167*/ "jmpe", 	// Len:1
	/*168*/ "jnb", 	// Len:3 
	/*169*/ "jae",
	/*170*/ "jnc",
	/*171*/ "jnbe", 	// Len:2 
	/*172*/ "ja",
	/*173*/ "jne", 	// Len:2 
	/*174*/ "jnz",
	/*175*/ "jnl", 	// Len:2 
	/*176*/ "jge",
	/*177*/ "jnle", 	// Len:2 
	/*178*/ "jg",
	/*179*/ "jno", 	// Len:1
	/*180*/ "jnp", 	// Len:2 
	/*181*/ "jpo",
	/*182*/ "jns", 	// Len:1
	/*183*/ "jnz", 	// Len:2 
	/*184*/ "jne",
	/*185*/ "jo", 	// Len:1
	/*186*/ "jp", 	// Len:2 
	/*187*/ "jpe",
	/*188*/ "jrcxz", 	// Len:1
	/*189*/ "js", 	// Len:1
	/*190*/ "jz", 	// Len:2 
	/*191*/ "je",
	/*192*/ "lahf", 	// Len:1
	/*193*/ "lar", 	// Len:1
	/*194*/ "ldmxcsr", 	// Len:1
	/*195*/ "lds", 	// Len:1
	/*196*/ "lea", 	// Len:1
	/*197*/ "leave", 	// Len:1
	/*198*/ "les", 	// Len:1
	/*199*/ "lfence", 	// Len:1
	/*200*/ "lfs", 	// Len:1
	/*201*/ "lgdt", 	// Len:1
	/*202*/ "lgs", 	// Len:1
	/*203*/ "lidt", 	// Len:1
	/*204*/ "lldt", 	// Len:1
	/*205*/ "lmsw", 	// Len:1
	/*206*/ "lods", 	// Len:2 Type:Size
	/*207*/ "lodsb",
	/*208*/ "lods", 	// Len:4 Type:Size
	/*209*/ "lodsw",
	/*210*/ "lodsd",
	/*211*/ "lodsq",
	/*212*/ "loop", 	// Len:1
	/*213*/ "loope", 	// Len:2 
	/*214*/ "loopz",
	/*215*/ "loopne", 	// Len:2 
	/*216*/ "loopnz",
	/*217*/ "lsl", 	// Len:1
	/*218*/ "lss", 	// Len:1
	/*219*/ "ltr", 	// Len:1
	/*220*/ "lzcnt", 	// Len:1
	/*221*/ "maskmovq", 	// Len:1
	/*222*/ "mfence", 	// Len:1
	/*223*/ "monitor", 	// Len:1
	/*224*/ "mov", 	// Len:1
	/*225*/ "movbe", 	// Len:1
	/*226*/ "movd", 	// Len:2 Type:Size
	/*227*/ "movdq",
	/*228*/ "movdq2q", 	// Len:1
	/*229*/ "movnti", 	// Len:1
	/*230*/ "movntq", 	// Len:1
	/*231*/ "movq", 	// Len:1
	/*232*/ "movq2dq", 	// Len:1
	/*233*/ "movs", 	// Len:2 Type:Size
	/*234*/ "movsb",
	/*235*/ "movs", 	// Len:4 Type:Size
	/*236*/ "movsw",
	/*237*/ "movsd",
	/*238*/ "movsq",
	/*239*/ "movsx", 	// Len:1
	/*240*/ "movsxd", 	// Len:1
	/*241*/ "movzx", 	// Len:1
	/*242*/ "mul", 	// Len:1
	/*243*/ "mulx", 	// Len:1
	/*244*/ "mwait", 	// Len:1
	/*245*/ "neg", 	// Len:1
	/*246*/ "nop", 	// Len:1
	/*247*/ "not", 	// Len:1
	/*248*/ "or", 	// Len:1
	/*249*/ "out", 	// Len:1
	/*250*/ "outs", 	// Len:2 Type:Size
	/*251*/ "outsb",
	/*252*/ "outs", 	// Len:3 Type:Size
	/*253*/ "outsw",
	/*254*/ "outsd",
	/*255*/ "pabsb", 	// Len:1
	/*256*/ "pabsd", 	// Len:1
	/*257*/ "pabsw", 	// Len:1
	/*258*/ "packssdw", 	// Len:1
	/*259*/ "packsswb", 	// Len:1
	/*260*/ "packuswb", 	// Len:1
	/*261*/ "paddb", 	// Len:1
	/*262*/ "paddd", 	// Len:1
	/*263*/ "paddq", 	// Len:1
	/*264*/ "paddsb", 	// Len:1
	/*265*/ "paddsw", 	// Len:1
	/*266*/ "paddusb", 	// Len:1
	/*267*/ "paddusw", 	// Len:1
	/*268*/ "paddw", 	// Len:1
	/*269*/ "palignr", 	// Len:1
	/*270*/ "pand", 	// Len:1
	/*271*/ "pandn", 	// Len:1
	/*272*/ "pause", 	// Len:1
	/*273*/ "pavgb", 	// Len:1
	/*274*/ "pavgw", 	// Len:1
	/*275*/ "pblendvb", 	// Len:1
	/*276*/ "pcmpeqb", 	// Len:1
	/*277*/ "pcmpeqd", 	// Len:1
	/*278*/ "pcmpeqw", 	// Len:1
	/*279*/ "pcmpgtb", 	// Len:1
	/*280*/ "pcmpgtd", 	// Len:1
	/*281*/ "pcmpgtw", 	// Len:1
	/*282*/ "pdep", 	// Len:1
	/*283*/ "pext", 	// Len:1
	/*284*/ "pextrw", 	// Len:1
	/*285*/ "phaddd", 	// Len:1
	/*286*/ "phaddsw", 	// Len:1
	/*287*/ "phaddw", 	// Len:1
	/*288*/ "phsubd", 	// Len:1
	/*289*/ "phsubsw", 	// Len:1
	/*290*/ "phsubw", 	// Len:1
	/*291*/ "pinsrw", 	// Len:1
	/*292*/ "pmaddubsw", 	// Len:1
	/*293*/ "pmaddwd", 	// Len:1
	/*294*/ "pmaxsw", 	// Len:1
	/*295*/ "pmaxub", 	// Len:1
	/*296*/ "pminsw", 	// Len:1
	/*297*/ "pminub", 	// Len:1
	/*298*/ "pmovmskb", 	// Len:1
	/*299*/ "pmulhrsw", 	// Len:1
	/*300*/ "pmulhuw", 	// Len:1
	/*301*/ "pmulhw", 	// Len:1
	/*302*/ "pmullw", 	// Len:1
	/*303*/ "pmuludq", 	// Len:1
	/*304*/ "pop", 	// Len:1
	/*305*/ "popa", 	// Len:2 
	/*306*/ "popad",
	/*307*/ "popcnt", 	// Len:1
	/*308*/ "popf", 	// Len:3 Type:Size
	/*309*/ "popfd",
	/*310*/ "popfq",
	/*311*/ "por", 	// Len:1
	/*312*/ "prefetchnta", 	// Len:1
	/*313*/ "prefetcht0", 	// Len:1
	/*314*/ "prefetcht1", 	// Len:1
	/*315*/ "prefetcht2", 	// Len:1
	/*316*/ "prefetchw", 	// Len:1
	/*317*/ "psadbw", 	// Len:1
	/*318*/ "pshufb", 	// Len:1
	/*319*/ "pshufw", 	// Len:1
	/*320*/ "psignb", 	// Len:1
	/*321*/ "psignd", 	// Len:1
	/*322*/ "psignw", 	// Len:1
	/*323*/ "pslld", 	// Len:1
	/*324*/ "psllq", 	// Len:1
	/*325*/ "psllw", 	// Len:1
	/*326*/ "psrad", 	// Len:1
	/*327*/ "psraw", 	// Len:1
	/*328*/ "psrld", 	// Len:1
	/*329*/ "psrlq", 	// Len:1
	/*330*/ "psrlw", 	// Len:1
	/*331*/ "psubb", 	// Len:1
	/*332*/ "psubd", 	// Len:1
	/*333*/ "psubq", 	// Len:1
	/*334*/ "psubsb", 	// Len:1
	/*335*/ "psubsw", 	// Len:1
	/*336*/ "psubusb", 	// Len:1
	/*337*/ "psubusw", 	// Len:1
	/*338*/ "psubw", 	// Len:1
	/*339*/ "punpckhbw", 	// Len:1
	/*340*/ "punpckhdq", 	// Len:1
	/*341*/ "punpckhwd", 	// Len:1
	/*342*/ "punpcklbw", 	// Len:1
	/*343*/ "punpckldq", 	// Len:1
	/*344*/ "punpcklwd", 	// Len:1
	/*345*/ "push", 	// Len:1
	/*346*/ "pusha", 	// Len:2 
	/*347*/ "pushad",
	/*348*/ "pushf", 	// Len:3 Type:Size
	/*349*/ "pushfd",
	/*350*/ "pushfq",
	/*351*/ "pxor", 	// Len:1
	/*352*/ "rcl", 	// Len:1
	/*353*/ "rcr", 	// Len:1
	/*354*/ "rdfsbase", 	// Len:1
	/*355*/ "rdgsbase", 	// Len:1
	/*356*/ "rdmsr", 	// Len:1
	/*357*/ "rdpmc", 	// Len:1
	/*358*/ "rdrand", 	// Len:1
	/*359*/ "rdseed", 	// Len:1
	/*360*/ "rdtsc", 	// Len:1
	/*361*/ "rdtscp", 	// Len:1
	/*362*/ "ret", 	// Len:1
	/*363*/ "rol", 	// Len:1
	/*364*/ "ror", 	// Len:1
	/*365*/ "rorx", 	// Len:1
	/*366*/ "rsm", 	// Len:1
	/*367*/ "sahf", 	// Len:1
	/*368*/ "sar", 	// Len:1
	/*369*/ "sarx", 	// Len:1
	/*370*/ "sbb", 	// Len:1
	/*371*/ "scas", 	// Len:2 Type:Size
	/*372*/ "scasb",
	/*373*/ "scas", 	// Len:4 Type:Size
	/*374*/ "scasw",
	/*375*/ "scasd",
	/*376*/ "scasq",
	/*377*/ "seta", 	// Len:2 
	/*378*/ "setnbe",
	/*379*/ "setae", 	// Len:3 
	/*380*/ "setnb",
	/*381*/ "setnc",
	/*382*/ "setb", 	// Len:3 
	/*383*/ "setc",
	/*384*/ "setnae",
	/*385*/ "setbe", 	// Len:2 
	/*386*/ "setna",
	/*387*/ "sete", 	// Len:2 
	/*388*/ "setz",
	/*389*/ "setl", 	// Len:2 
	/*390*/ "setnge",
	/*391*/ "setle", 	// Len:2 
	/*392*/ "setng",
	/*393*/ "setne", 	// Len:2 
	/*394*/ "setnz",
	/*395*/ "setnl", 	// Len:2 
	/*396*/ "setge",
	/*397*/ "setnle", 	// Len:2 
	/*398*/ "setg",
	/*399*/ "setno", 	// Len:1
	/*400*/ "setnp", 	// Len:2 
	/*401*/ "setpo",
	/*402*/ "setns", 	// Len:1
	/*403*/ "seto", 	// Len:1
	/*404*/ "setp", 	// Len:2 
	/*405*/ "setpe",
	/*406*/ "sets", 	// Len:1
	/*407*/ "sfence", 	// Len:1
	/*408*/ "sgdt", 	// Len:1
	/*409*/ "shl", 	// Len:2 
	/*410*/ "sal",
	/*411*/ "shld", 	// Len:1
	/*412*/ "shlx", 	// Len:1
	/*413*/ "shr", 	// Len:1
	/*414*/ "shrd", 	// Len:1
	/*415*/ "shrx", 	// Len:1
	/*416*/ "sidt", 	// Len:1
	/*417*/ "sldt", 	// Len:1
	/*418*/ "smsw", 	// Len:1
	/*419*/ "stac", 	// Len:1
	/*420*/ "stc", 	// Len:1
	/*421*/ "std", 	// Len:1
	/*422*/ "sti", 	// Len:1
	/*423*/ "stmxcsr", 	// Len:1
	/*424*/ "stos", 	// Len:2 Type:Size
	/*425*/ "stosb",
	/*426*/ "stos", 	// Len:4 Type:Size
	/*427*/ "stosw",
	/*428*/ "stosd",
	/*429*/ "stosq",
	/*430*/ "str", 	// Len:1
	/*431*/ "sub", 	// Len:1
	/*432*/ "swapgs", 	// Len:1
	/*433*/ "syscall", 	// Len:1
	/*434*/ "sysenter", 	// Len:1
	/*435*/ "sysexit", 	// Len:1
	/*436*/ "sysret", 	// Len:1
	/*437*/ "test", 	// Len:1
	/*438*/ "tzcnt", 	// Len:1
	/*439*/ "ud2", 	// Len:1
	/*440*/ "vaddpd", 	// Len:1
	/*441*/ "vaddps", 	// Len:1
	/*442*/ "vaddsd", 	// Len:1
	/*443*/ "vaddss", 	// Len:1
	/*444*/ "vaddsubpd", 	// Len:1
	/*445*/ "vaddsubps", 	// Len:1
	/*446*/ "vaesdec", 	// Len:1
	/*447*/ "vaesdeclast", 	// Len:1
	/*448*/ "vaesenc", 	// Len:1
	/*449*/ "vaesenclast", 	// Len:1
	/*450*/ "vaesimc", 	// Len:1
	/*451*/ "vaeskeygen", 	// Len:1
	/*452*/ "vandnpd", 	// Len:1
	/*453*/ "vandnps", 	// Len:1
	/*454*/ "vandpd", 	// Len:1
	/*455*/ "vandps", 	// Len:1
	/*456*/ "vblendpd", 	// Len:1
	/*457*/ "vblendps", 	// Len:1
	/*458*/ "vblendvpd", 	// Len:1
	/*459*/ "vblendvps", 	// Len:1
	/*460*/ "vbroadcastf128", 	// Len:1
	/*461*/ "vbroadcasti128", 	// Len:1
	/*462*/ "vbroadcastsd", 	// Len:1
	/*463*/ "vbroadcastss", 	// Len:1
	/*464*/ "vcmppd", 	// Len:1
	/*465*/ "vcmpps", 	// Len:1
	/*466*/ "vcmpsd", 	// Len:1
	/*467*/ "vcmpss", 	// Len:1
	/*468*/ "vcomisd", 	// Len:1
	/*469*/ "vcomiss", 	// Len:1
	/*470*/ "vcvtdq2pd", 	// Len:1
	/*471*/ "vcvtdq2ps", 	// Len:1
	/*472*/ "vcvtpd2dq", 	// Len:1
	/*473*/ "vcvtpd2ps", 	// Len:1
	/*474*/ "vcvtph2ps", 	// Len:1
	/*475*/ "vcvtps2dq", 	// Len:1
	/*476*/ "vcvtps2pd", 	// Len:1
	/*477*/ "vcvtps2ph", 	// Len:1
	/*478*/ "vcvtsd2si", 	// Len:1
	/*479*/ "vcvtsd2ss", 	// Len:1
	/*480*/ "vcvtsi2sd", 	// Len:1
	/*481*/ "vcvtsi2ss", 	// Len:1
	/*482*/ "vcvtss2sd", 	// Len:1
	/*483*/ "vcvtss2si", 	// Len:1
	/*484*/ "vcvttpd2dq", 	// Len:1
	/*485*/ "vcvttps2dq", 	// Len:1
	/*486*/ "vcvttsd2si", 	// Len:1
	/*487*/ "vcvttss2si", 	// Len:1
	/*488*/ "vdivpd", 	// Len:1
	/*489*/ "vdivps", 	// Len:1
	/*490*/ "vdivsd", 	// Len:1
	/*491*/ "vdivss", 	// Len:1
	/*492*/ "vdppd", 	// Len:1
	/*493*/ "vdpps", 	// Len:1
	/*494*/ "verr", 	// Len:1
	/*495*/ "verw", 	// Len:1
	/*496*/ "vextractf128", 	// Len:1
	/*497*/ "vextracti128", 	// Len:1
	/*498*/ "vextractps", 	// Len:1
	/*499*/ "vfmadd132ps", 	// Len:2 Type:Size
	/*500*/ "vfmadd132psd",
	/*501*/ "vfmadd132ss", 	// Len:2 Type:Size
	/*502*/ "vfmadd132ssd",
	/*503*/ "vfmadd213ps", 	// Len:2 Type:Size
	/*504*/ "vfmadd213psd",
	/*505*/ "vfmadd213ss", 	// Len:2 Type:Size
	/*506*/ "vfmadd213ssd",
	/*507*/ "vfmadd231ps", 	// Len:2 Type:Size
	/*508*/ "vfmadd231psd",
	/*509*/ "vfmadd231ss", 	// Len:2 Type:Size
	/*510*/ "vfmadd231ssd",
	/*511*/ "vfmaddsub132ps", 	// Len:2 Type:Size
	/*512*/ "vfmaddsub132psd",
	/*513*/ "vfmaddsub213ps", 	// Len:2 Type:Size
	/*514*/ "vfmaddsub213psd",
	/*515*/ "vfmaddsub231ps", 	// Len:2 Type:Size
	/*516*/ "vfmaddsub231psd",
	/*517*/ "vfmsub132ps", 	// Len:2 Type:Size
	/*518*/ "vfmsub132psd",
	/*519*/ "vfmsub132ss", 	// Len:2 Type:Size
	/*520*/ "vfmsub132ssd",
	/*521*/ "vfmsub213ps", 	// Len:2 Type:Size
	/*522*/ "vfmsub213psd",
	/*523*/ "vfmsub213ss", 	// Len:2 Type:Size
	/*524*/ "vfmsub213ssd",
	/*525*/ "vfmsub231ps", 	// Len:2 Type:Size
	/*526*/ "vfmsub231psd",
	/*527*/ "vfmsub231ss", 	// Len:2 Type:Size
	/*528*/ "vfmsub231ssd",
	/*529*/ "vfmsubadd132ps", 	// Len:2 Type:Size
	/*530*/ "vfmsubadd132psd",
	/*531*/ "vfmsubadd213ps", 	// Len:2 Type:Size
	/*532*/ "vfmsubadd213psd",
	/*533*/ "vfmsubadd231ps", 	// Len:2 Type:Size
	/*534*/ "vfmsubadd231psd",
	/*535*/ "vfnmadd132ps", 	// Len:2 Type:Size
	/*536*/ "vfnmadd132psd",
	/*537*/ "vfnmadd132ss", 	// Len:2 Type:Size
	/*538*/ "vfnmadd132ssd",
	/*539*/ "vfnmadd213ps", 	// Len:2 Type:Size
	/*540*/ "vfnmadd213psd",
	/*541*/ "vfnmadd213ss", 	// Len:2 Type:Size
	/*542*/ "vfnmadd213ssd",
	/*543*/ "vfnmadd231ps", 	// Len:2 Type:Size
	/*544*/ "vfnmadd231psd",
	/*545*/ "vfnmadd231ss", 	// Len:2 Type:Size
	/*546*/ "vfnmadd231ssd",
	/*547*/ "vfnmsub132ps", 	// Len:2 Type:Size
	/*548*/ "vfnmsub132psd",
	/*549*/ "vfnmsub132ss", 	// Len:2 Type:Size
	/*550*/ "vfnmsub132ssd",
	/*551*/ "vfnmsub213ps", 	// Len:2 Type:Size
	/*552*/ "vfnmsub213psd",
	/*553*/ "vfnmsub213ss", 	// Len:2 Type:Size
	/*554*/ "vfnmsub213ssd",
	/*555*/ "vfnmsub231ps", 	// Len:2 Type:Size
	/*556*/ "vfnmsub231psd",
	/*557*/ "vfnmsub231ss", 	// Len:2 Type:Size
	/*558*/ "vfnmsub231ssd",
	/*559*/ "vgatherdd", 	// Len:2 Type:Size
	/*560*/ "vgatherddq",
	/*561*/ "vgatherdps", 	// Len:2 Type:Size
	/*562*/ "vgatherdpsd",
	/*563*/ "vgatherqd", 	// Len:2 Type:Size
	/*564*/ "vgatherqdq",
	/*565*/ "vgatherqps", 	// Len:2 Type:Size
	/*566*/ "vgatherqpsd",
	/*567*/ "vhaddpd", 	// Len:1
	/*568*/ "vhaddps", 	// Len:1
	/*569*/ "vhsubpd", 	// Len:1
	/*570*/ "vhsubps", 	// Len:1
	/*571*/ "vinsertf128", 	// Len:1
	/*572*/ "vinserti128", 	// Len:1
	/*573*/ "vinsertps", 	// Len:1
	/*574*/ "vlddqu", 	// Len:1
	/*575*/ "vmaskmovdqu", 	// Len:1
	/*576*/ "vmaskmovpd", 	// Len:1
	/*577*/ "vmaskmovps", 	// Len:1
	/*578*/ "vmaxpd", 	// Len:1
	/*579*/ "vmaxps", 	// Len:1
	/*580*/ "vmaxsd", 	// Len:1
	/*581*/ "vmaxss", 	// Len:1
	/*582*/ "vmcall", 	// Len:1
	/*583*/ "vmclear", 	// Len:1
	/*584*/ "vmfunc", 	// Len:1
	/*585*/ "vminpd", 	// Len:1
	/*586*/ "vminps", 	// Len:1
	/*587*/ "vminsd", 	// Len:1
	/*588*/ "vminss", 	// Len:1
	/*589*/ "vmlaunch", 	// Len:1
	/*590*/ "vmovapd", 	// Len:1
	/*591*/ "vmovaps", 	// Len:1
	/*592*/ "vmovd", 	// Len:2 Type:Size
	/*593*/ "vmovdq",
	/*594*/ "vmovddup", 	// Len:1
	/*595*/ "vmovdqa", 	// Len:1
	/*596*/ "vmovdqu", 	// Len:1
	/*597*/ "vmovhlps", 	// Len:1
	/*598*/ "vmovhpd", 	// Len:1
	/*599*/ "vmovhps", 	// Len:1
	/*600*/ "vmovlhps", 	// Len:1
	/*601*/ "vmovlpd", 	// Len:1
	/*602*/ "vmovlps", 	// Len:1
	/*603*/ "vmovmskpd", 	// Len:1
	/*604*/ "vmovmskps", 	// Len:1
	/*605*/ "vmovntdq", 	// Len:1
	/*606*/ "vmovntdqa", 	// Len:1
	/*607*/ "vmovntpd", 	// Len:1
	/*608*/ "vmovntps", 	// Len:1
	/*609*/ "vmovq", 	// Len:1
	/*610*/ "vmovsd", 	// Len:1
	/*611*/ "vmovshdup", 	// Len:1
	/*612*/ "vmovsldup", 	// Len:1
	/*613*/ "vmovss", 	// Len:1
	/*614*/ "vmovupd", 	// Len:1
	/*615*/ "vmovups", 	// Len:1
	/*616*/ "vmpsadbw", 	// Len:1
	/*617*/ "vmptrld", 	// Len:1
	/*618*/ "vmptrst", 	// Len:1
	/*619*/ "vmread", 	// Len:1
	/*620*/ "vmresume", 	// Len:1
	/*621*/ "vmulpd", 	// Len:1
	/*622*/ "vmulps", 	// Len:1
	/*623*/ "vmulsd", 	// Len:1
	/*624*/ "vmulss", 	// Len:1
	/*625*/ "vmwrite", 	// Len:1
	/*626*/ "vmxoff", 	// Len:1
	/*627*/ "vmxon", 	// Len:1
	/*628*/ "vorpd", 	// Len:1
	/*629*/ "vorps", 	// Len:1
	/*630*/ "vpabsb", 	// Len:1
	/*631*/ "vpabsd", 	// Len:1
	/*632*/ "vpabsw", 	// Len:1
	/*633*/ "vpackssdw", 	// Len:1
	/*634*/ "vpacksswb", 	// Len:1
	/*635*/ "vpackusdw", 	// Len:1
	/*636*/ "vpackuswb", 	// Len:1
	/*637*/ "vpaddb", 	// Len:1
	/*638*/ "vpaddd", 	// Len:1
	/*639*/ "vpaddq", 	// Len:1
	/*640*/ "vpaddsb", 	// Len:1
	/*641*/ "vpaddsw", 	// Len:1
	/*642*/ "vpaddusb", 	// Len:1
	/*643*/ "vpaddusw", 	// Len:1
	/*644*/ "vpaddw", 	// Len:1
	/*645*/ "vpalignr", 	// Len:1
	/*646*/ "vpand", 	// Len:1
	/*647*/ "vpandn", 	// Len:1
	/*648*/ "vpavgb", 	// Len:1
	/*649*/ "vpavgw", 	// Len:1
	/*650*/ "vpblendd", 	// Len:1
	/*651*/ "vpblendvb", 	// Len:1
	/*652*/ "vpblendw", 	// Len:1
	/*653*/ "vpbroadcastb", 	// Len:1
	/*654*/ "vpbroadcastd", 	// Len:1
	/*655*/ "vpbroadcastq", 	// Len:1
	/*656*/ "vpbroadcastw", 	// Len:1
	/*657*/ "vpclmulqdq", 	// Len:1
	/*658*/ "vpcmpeqb", 	// Len:1
	/*659*/ "vpcmpeqd", 	// Len:1
	/*660*/ "vpcmpeqq", 	// Len:1
	/*661*/ "vpcmpeqw", 	// Len:1
	/*662*/ "vpcmpestri", 	// Len:1
	/*663*/ "vpcmpestrm", 	// Len:1
	/*664*/ "vpcmpgtb", 	// Len:1
	/*665*/ "vpcmpgtd", 	// Len:1
	/*666*/ "vpcmpgtq", 	// Len:1
	/*667*/ "vpcmpgtw", 	// Len:1
	/*668*/ "vpcmpistri", 	// Len:1
	/*669*/ "vpcmpistrm", 	// Len:1
	/*670*/ "vperm2f128", 	// Len:1
	/*671*/ "vperm2i128", 	// Len:1
	/*672*/ "vpermd", 	// Len:1
	/*673*/ "vpermilpd", 	// Len:1
	/*674*/ "vpermilps", 	// Len:1
	/*675*/ "vpermpd", 	// Len:1
	/*676*/ "vpermps", 	// Len:1
	/*677*/ "vpermq", 	// Len:1
	/*678*/ "vpextrb", 	// Len:1
	/*679*/ "vpextrd", 	// Len:2 Type:Size
	/*680*/ "vpextrdq",
	/*681*/ "vpextrw", 	// Len:1
	/*682*/ "vphaddd", 	// Len:1
	/*683*/ "vphaddsw", 	// Len:1
	/*684*/ "vphaddw", 	// Len:1
	/*685*/ "vphminposuw", 	// Len:1
	/*686*/ "vphsubd", 	// Len:1
	/*687*/ "vphsubsw", 	// Len:1
	/*688*/ "vphsubw", 	// Len:1
	/*689*/ "vpinsrb", 	// Len:1
	/*690*/ "vpinsrd", 	// Len:2 Type:Size
	/*691*/ "vpinsrdq",
	/*692*/ "vpinsrw", 	// Len:1
	/*693*/ "vpmaddubsw", 	// Len:1
	/*694*/ "vpmaddwd", 	// Len:1
	/*695*/ "vpmaskmovd", 	// Len:2 Type:Size
	/*696*/ "vpmaskmovdq",
	/*697*/ "vpmaxsb", 	// Len:1
	/*698*/ "vpmaxsd", 	// Len:1
	/*699*/ "vpmaxsw", 	// Len:1
	/*700*/ "vpmaxub", 	// Len:1
	/*701*/ "vpmaxud", 	// Len:1
	/*702*/ "vpmaxuw", 	// Len:1
	/*703*/ "vpminsb", 	// Len:1
	/*704*/ "vpminsd", 	// Len:1
	/*705*/ "vpminsw", 	// Len:1
	/*706*/ "vpminub", 	// Len:1
	/*707*/ "vpminud", 	// Len:1
	/*708*/ "vpminuw", 	// Len:1
	/*709*/ "vpmovmskb", 	// Len:1
	/*710*/ "vpmovsxbd", 	// Len:1
	/*711*/ "vpmovsxbq", 	// Len:1
	/*712*/ "vpmovsxbw", 	// Len:1
	/*713*/ "vpmovsxdq", 	// Len:1
	/*714*/ "vpmovsxwd", 	// Len:1
	/*715*/ "vpmovsxwq", 	// Len:1
	/*716*/ "vpmovzxbd", 	// Len:1
	/*717*/ "vpmovzxbq", 	// Len:1
	/*718*/ "vpmovzxbw", 	// Len:1
	/*719*/ "vpmovzxdq", 	// Len:1
	/*720*/ "vpmovzxwd", 	// Len:1
	/*721*/ "vpmovzxwq", 	// Len:1
	/*722*/ "vpmuldq", 	// Len:1
	/*723*/ "vpmulhrsw", 	// Len:1
	/*724*/ "vpmulhuw", 	// Len:1
	/*725*/ "vpmulhw", 	// Len:1
	/*726*/ "vpmulld", 	// Len:1
	/*727*/ "vpmullw", 	// Len:1
	/*728*/ "vpmuludq", 	// Len:1
	/*729*/ "vpor", 	// Len:1
	/*730*/ "vpsadbw", 	// Len:1
	/*731*/ "vpshufb", 	// Len:1
	/*732*/ "vpshufd", 	// Len:1
	/*733*/ "vpshufhw", 	// Len:1
	/*734*/ "vpshuflw", 	// Len:1
	/*735*/ "vpsignb", 	// Len:1
	/*736*/ "vpsignd", 	// Len:1
	/*737*/ "vpsignw", 	// Len:1
	/*738*/ "vpslld", 	// Len:1
	/*739*/ "vpslldq", 	// Len:1
	/*740*/ "vpsllq", 	// Len:1
	/*741*/ "vpsllvd", 	// Len:2 Type:Size
	/*742*/ "vpsllvdq",
	/*743*/ "vpsllw", 	// Len:1
	/*744*/ "vpsrad", 	// Len:1
	/*745*/ "vpsravd", 	// Len:1
	/*746*/ "vpsraw", 	// Len:1
	/*747*/ "vpsrld", 	// Len:1
	/*748*/ "vpsrldq", 	// Len:1
	/*749*/ "vpsrlq", 	// Len:1
	/*750*/ "vpsrlvd", 	// Len:2 Type:Size
	/*751*/ "vpsrlvdq",
	/*752*/ "vpsrlw", 	// Len:1
	/*753*/ "vpsubb", 	// Len:1
	/*754*/ "vpsubd", 	// Len:1
	/*755*/ "vpsubq", 	// Len:1
	/*756*/ "vpsubsb", 	// Len:1
	/*757*/ "vpsubsw", 	// Len:1
	/*758*/ "vpsubusb", 	// Len:1
	/*759*/ "vpsubusw", 	// Len:1
	/*760*/ "vpsubw", 	// Len:1
	/*761*/ "vptest", 	// Len:1
	/*762*/ "vpunpckhbw", 	// Len:1
	/*763*/ "vpunpckhdq", 	// Len:1
	/*764*/ "vpunpckhqdq", 	// Len:1
	/*765*/ "vpunpckhwd", 	// Len:1
	/*766*/ "vpunpcklbw", 	// Len:1
	/*767*/ "vpunpckldq", 	// Len:1
	/*768*/ "vpunpcklqdq", 	// Len:1
	/*769*/ "vpunpcklwd", 	// Len:1
	/*770*/ "vpxor", 	// Len:1
	/*771*/ "vrcpps", 	// Len:1
	/*772*/ "vrcpss", 	// Len:1
	/*773*/ "vroundpd", 	// Len:1
	/*774*/ "vroundps", 	// Len:1
	/*775*/ "vroundsd", 	// Len:1
	/*776*/ "vroundss", 	// Len:1
	/*777*/ "vrsqrtps", 	// Len:1
	/*778*/ "vrsqrtss", 	// Len:1
	/*779*/ "vshufpd", 	// Len:1
	/*780*/ "vshufps", 	// Len:1
	/*781*/ "vsqrtpd", 	// Len:1
	/*782*/ "vsqrtps", 	// Len:1
	/*783*/ "vsqrtsd", 	// Len:1
	/*784*/ "vsqrtss", 	// Len:1
	/*785*/ "vsubpd", 	// Len:1
	/*786*/ "vsubps", 	// Len:1
	/*787*/ "vsubsd", 	// Len:1
	/*788*/ "vsubss", 	// Len:1
	/*789*/ "vtestpd", 	// Len:1
	/*790*/ "vtestps", 	// Len:1
	/*791*/ "vucomisd", 	// Len:1
	/*792*/ "vucomiss", 	// Len:1
	/*793*/ "vunpckhpd", 	// Len:1
	/*794*/ "vunpckhps", 	// Len:1
	/*795*/ "vunpcklpd", 	// Len:1
	/*796*/ "vunpcklps", 	// Len:1
	/*797*/ "vxorpd", 	// Len:1
	/*798*/ "vxorps", 	// Len:1
	/*799*/ "vzeroall", 	// Len:1
	/*800*/ "vzeroupper", 	// Len:1
	/*801*/ "wbinvd", 	// Len:1
	/*802*/ "wrfsbase", 	// Len:1
	/*803*/ "wrgsbase", 	// Len:1
	/*804*/ "wrmsr", 	// Len:1
	/*805*/ "xabort", 	// Len:1
	/*806*/ "xadd", 	// Len:1
	/*807*/ "xbegin", 	// Len:1
	/*808*/ "xchg", 	// Len:1
	/*809*/ "xend", 	// Len:1
	/*810*/ "xgetbv", 	// Len:1
	/*811*/ "xlat", 	// Len:2 Type:Size
	/*812*/ "xlatb",
	/*813*/ "xor", 	// Len:1
	/*814*/ "xrstor", 	// Len:1
	/*815*/ "xsave", 	// Len:1
	/*816*/ "xsaveopt", 	// Len:1
	/*817*/ "xsetbv", 	// Len:1
	/*818*/ "xtest", 	// Len:1
};

extern unsigned char OperandGroup1[] =
{
	/*0*/ 28, // ES
	/*1*/ 108, // SS
	/*2*/ 19, // eAX
	/*3*/ 23, // eCX
	/*4*/ 26, // eDX
	/*5*/ 22, // eBX
	/*6*/ 30, // eSP
	/*7*/ 21, // eBP
	/*8*/ 29, // eSI
	/*9*/ 25, // eDI
	/*10*/ 84, // rAX/r8
	/*11*/ 90, // rCX/r9
	/*12*/ 98, // rDX/r10
	/*13*/ 88, // rBX/r11
	/*14*/ 102, // rSP/r12
	/*15*/ 86, // rBP/r13
	/*16*/ 100, // rSI/r14
	/*17*/ 95, // rDI/r15
	/*18*/ 56, // Jb
	/*19*/ 54, // Iw
	/*20*/ 51, // Ib
	/*21*/ 20, // Eb
	/*22*/ 31, // Ev
	/*23*/ 13, // CS
	/*24*/ 17, // DS
	/*25*/ 55, // Iz
	/*26*/ 5, // Ap
	/*27*/ 35, // Fv
	/*28*/ 57, // Jz
	/*29*/ 34, // FS
	/*30*/ 38, // GS
	/*31*/ 83, // RAX/EAX/R8/R8D
	/*32*/ 89, // RCX/ECX/R9/R9D
	/*33*/ 97, // RDX/EDX/R10/R10D
	/*34*/ 87, // RBX/EBX/R11/R11D
	/*35*/ 101, // RSP/ESP/R12/R12D
	/*36*/ 85, // RBP/EBP/R13/R13D
	/*37*/ 99, // RSI/ESI/R14/R14D
	/*38*/ 94, // RDI/EDI/R15/R15D
	/*39*/ 52, // Ib/Iz
	/*40*/ 4, // AL/rAX
	/*41*/ 27, // Ep
	/*42*/ 63, // Mp
	/*43*/ 104, // Rv/Mw
	/*44*/ 32, // Ew
	/*45*/ 67, // Ms
	/*46*/ 69, // Mw/Rv
	/*47*/ 61, // Mb
	/*48*/ 66, // Mq
	/*49*/ 62, // Mdq
	/*50*/ 103, // Rv
	/*51*/ 105, // Ry
};
extern unsigned char OperandGroup2[][2] =
{
	/*0*/{ 20,36 }, // Eb,Gb
	/*1*/{ 31,39 }, // Ev,Gv
	/*2*/{ 36,20 }, // Gb,Eb
	/*3*/{ 39,31 }, // Gv,Ev
	/*4*/{ 2,51 }, // AL,Ib
	/*5*/{ 82,55 }, // rAX,Iz
	/*6*/{ 39,60 }, // Gv,Ma
	/*7*/{ 32,40 }, // Ew,Gw
	/*8*/{ 20,51 }, // Eb,Ib
	/*9*/{ 31,55 }, // Ev,Iz
	/*10*/{ 31,51 }, // Ev,Ib
	/*11*/{ 81,82 }, // r8,rAX
	/*12*/{ 90,82 }, // rCX/r9,rAX
	/*13*/{ 98,82 }, // rDX/r10,rAX
	/*14*/{ 88,82 }, // rBX/r11,rAX
	/*15*/{ 102,82 }, // rSP/r12,rAX
	/*16*/{ 86,82 }, // rBP/r13,rAX
	/*17*/{ 100,82 }, // rSI/r14,rAX
	/*18*/{ 95,82 }, // rDI/r15,rAX
	/*19*/{ 2,73 }, // AL,Ob
	/*20*/{ 82,74 }, // rAX,Ov
	/*21*/{ 73,2 }, // Ob,AL
	/*22*/{ 74,82 }, // Ov,rAX
	/*23*/{ 140,137 }, // Yb,Xb
	/*24*/{ 141,138 }, // Yv,Xv
	/*25*/{ 137,140 }, // Xb,Yb
	/*26*/{ 138,141 }, // Xv,Yv
	/*27*/{ 3,51 }, // AL/R8L,Ib
	/*28*/{ 12,51 }, // CL/R9L,Ib
	/*29*/{ 16,51 }, // DL/R10L,Ib
	/*30*/{ 7,51 }, // BL/R11L,Ib
	/*31*/{ 1,51 }, // AH/R12L,Ib
	/*32*/{ 10,51 }, // CH/R13L,Ib
	/*33*/{ 15,51 }, // DH/R14L,Ib
	/*34*/{ 6,51 }, // BH/R15L,Ib
	/*35*/{ 42,63 }, // Gz,Mp
	/*36*/{ 20,0 }, // Eb,1
	/*37*/{ 31,0 }, // Ev,1
	/*38*/{ 20,11 }, // Eb,CL
	/*39*/{ 31,11 }, // Ev,CL
	/*40*/{ 19,51 }, // eAX,Ib
	/*41*/{ 51,2 }, // Ib,AL
	/*42*/{ 51,19 }, // Ib,eAX
	/*43*/{ 140,18 }, // Yb,DX
	/*44*/{ 142,18 }, // Yz,DX
	/*45*/{ 18,137 }, // DX,Xb
	/*46*/{ 18,139 }, // DX,Xz
	/*47*/{ 31,109 }, // Ev,Sw
	/*48*/{ 39,59 }, // Gv,M
	/*49*/{ 109,32 }, // Sw,Ew
	/*50*/{ 140,2 }, // Yb,AL
	/*51*/{ 141,82 }, // Yv,rAX
	/*52*/{ 2,137 }, // AL,Xb
	/*53*/{ 82,138 }, // rAX,Xv
	/*54*/{ 2,140 }, // AL,Yb
	/*55*/{ 82,141 }, // rAX,Yv
	/*56*/{ 84,53 }, // rAX/r8,Iv
	/*57*/{ 90,53 }, // rCX/r9,Iv
	/*58*/{ 98,53 }, // rDX/r10,Iv
	/*59*/{ 88,53 }, // rBX/r11,Iv
	/*60*/{ 102,53 }, // rSP/r12,Iv
	/*61*/{ 86,53 }, // rBP/r13,Iv
	/*62*/{ 100,53 }, // rSI/r14,Iv
	/*63*/{ 95,53 }, // rDI/r15,Iv
	/*64*/{ 54,51 }, // Iw,Ib
	/*65*/{ 2,18 }, // AL,DX
	/*66*/{ 19,18 }, // eAX,DX
	/*67*/{ 18,2 }, // DX,AL
	/*68*/{ 18,19 }, // DX,eAX
	/*69*/{ 39,32 }, // Gv,Ew
	/*70*/{ 121,131 }, // Vps,Wps
	/*71*/{ 131,121 }, // Wps,Vps
	/*72*/{ 66,122 }, // Mq,Vq
	/*73*/{ 120,130 }, // Vpd,Wpd
	/*74*/{ 130,120 }, // Wpd,Vpd
	/*75*/{ 126,136 }, // Vx,Wx
	/*76*/{ 91,9 }, // Rd,Cd
	/*77*/{ 91,14 }, // Rd,Dd
	/*78*/{ 9,91 }, // Cd,Rd
	/*79*/{ 14,91 }, // Dd,Rd
	/*80*/{ 41,113 }, // Gy,Ups
	/*81*/{ 41,112 }, // Gy,Upd
	/*82*/{ 77,78 }, // Pq,Qd
	/*83*/{ 77,80 }, // Pq,Qq
	/*84*/{ 121,79 }, // Vps,Qpi
	/*85*/{ 65,121 }, // Mps,Vps
	/*86*/{ 76,131 }, // Ppi,Wps
	/*87*/{ 125,135 }, // Vss,Wss
	/*88*/{ 120,79 }, // Vpd,Qpi
	/*89*/{ 64,120 }, // Mpd,Vpd
	/*90*/{ 76,130 }, // Ppi,Wpd
	/*91*/{ 79,130 }, // Qpi,Wpd
	/*92*/{ 124,134 }, // Vsd,Wsd
	/*93*/{ 41,135 }, // Gy,Wss
	/*94*/{ 41,134 }, // Gy,Wsd
	/*95*/{ 120,131 }, // Vpd,Wps
	/*96*/{ 121,129 }, // Vps,Wdq
	/*97*/{ 121,130 }, // Vps,Wpd
	/*98*/{ 119,131 }, // Vdq,Wps
	/*99*/{ 75,33 }, // Pd,Ey
	/*100*/{ 127,33 }, // Vy,Ey
	/*101*/{ 33,41 }, // Ey,Gy
	/*102*/{ 41,33 }, // Gy,Ey
	/*103*/{ 33,75 }, // Ey,Pd
	/*104*/{ 80,77 }, // Qq,Pq
	/*105*/{ 33,127 }, // Ey,Vy
	/*106*/{ 136,126 }, // Wx,Vx
	/*107*/{ 122,132 }, // Vq,Wq
	/*108*/{ 39,63 }, // Gv,Mp
	/*109*/{ 39,20 }, // Gv,Eb
	/*110*/{ 71,41 }, // My,Gy
	/*111*/{ 37,72 }, // Gd,Nq
	/*112*/{ 132,122 }, // Wq,Vq
	/*113*/{ 37,115 }, // Gd,Ux
	/*114*/{ 119,72 }, // Vdq,Nq
	/*115*/{ 77,114 }, // Pq,Uq
	/*116*/{ 66,77 }, // Mq,Pq
	/*117*/{ 126,130 }, // Vx,Wpd
	/*118*/{ 70,126 }, // Mx,Vx
	/*119*/{ 77,72 }, // Pq,Nq
	/*120*/{ 119,110 }, // Vdq,Udq
	/*121*/{ 126,70 }, // Vx,Mx
	/*122*/{ 119,129 }, // Vdq,Wdq
	/*123*/{ 126,117 }, // Vx,Ux/Mq
	/*124*/{ 126,116 }, // Vx,Ux/Md
	/*125*/{ 126,118 }, // Vx,Ux/Mw
	/*126*/{ 41,62 }, // Gy,Mdq
	/*127*/{ 41,71 }, // Gy,My
	/*128*/{ 40,68 }, // Gw,Mw
	/*129*/{ 68,40 }, // Mw,Gw
	/*130*/{ 37,20 }, // Gd,Eb
	/*131*/{ 37,33 }, // Gd,Ey
	/*132*/{ 37,32 }, // Gd,Ew
	/*133*/{ 126,128 }, // Vx,Wd
	/*134*/{ 123,132 }, // Vqq,Wq
	/*135*/{ 123,62 }, // Vqq,Mdq
	/*136*/{ 72,51 }, // Nq,Ib
	/*137*/{ 8,33 }, // By,Ey
};
extern unsigned char OperandGroup3[][3] =
{
	/*0*/{ 39,31,55 }, // Gv,Ev,Iz
	/*1*/{ 39,31,51 }, // Gv,Ev,Ib
	/*2*/{ 122,46,66 }, // Vq,Hq,Mq
	/*3*/{ 122,46,114 }, // Vq,Hq,Uq
	/*4*/{ 126,50,136 }, // Vx,Hx,Wx
	/*5*/{ 119,46,66 }, // Vdq,Hq,Mq
	/*6*/{ 119,46,114 }, // Vdq,Hq,Uq
	/*7*/{ 126,50,135 }, // Vx,Hx,Wss
	/*8*/{ 135,50,125 }, // Wss,Hx,Vss
	/*9*/{ 126,50,134 }, // Vx,Hx,Wsd
	/*10*/{ 134,50,124 }, // Wsd,Hx,Vsd
	/*11*/{ 121,45,131 }, // Vps,Hps,Wps
	/*12*/{ 120,44,130 }, // Vpd,Hpd,Wpd
	/*13*/{ 125,49,135 }, // Vss,Hss,Wss
	/*14*/{ 124,48,134 }, // Vsd,Hsd,Wsd
	/*15*/{ 77,80,51 }, // Pq,Qq,Ib
	/*16*/{ 126,136,51 }, // Vx,Wx,Ib
	/*17*/{ 125,49,33 }, // Vss,Hss,Ey
	/*18*/{ 124,48,33 }, // Vsd,Hsd,Ey
	/*19*/{ 124,50,135 }, // Vsd,Hx,Wss
	/*20*/{ 125,50,134 }, // Vss,Hx,Wsd
	/*21*/{ 31,39,51 }, // Ev,Gv,Ib
	/*22*/{ 31,39,11 }, // Ev,Gv,CL
	/*23*/{ 77,107,51 }, // Pq,Ry/Mw,Ib
	/*24*/{ 37,72,51 }, // Gd,Nq,Ib
	/*25*/{ 37,110,51 }, // Gd,Udq,Ib
	/*26*/{ 123,47,133 }, // Vqq,Hqq,Wqq
	/*27*/{ 41,8,33 }, // Gy,By,Ey
	/*28*/{ 41,33,8 }, // Gy,Ey,By
	/*29*/{ 126,50,70 }, // Vx,Hx,Mx
	/*30*/{ 70,50,126 }, // Mx,Hx,Vx
	/*31*/{ 70,126,50 }, // Mx,Vx,Hx
	/*32*/{ 119,43,129 }, // Vdq,Hdq,Wdq
	/*33*/{ 123,133,51 }, // Vqq,Wqq,Ib
	/*34*/{ 92,119,51 }, // Rd/Mb,Vdq,Ib
	/*35*/{ 93,119,51 }, // Rd/Mw,Vdq,Ib
	/*36*/{ 33,119,51 }, // Ey,Vdq,Ib
	/*37*/{ 24,119,51 }, // Ed,Vdq,Ib
	/*38*/{ 119,129,51 }, // Vdq,Wdq,Ib
	/*39*/{ 41,33,51 }, // Gy,Ey,Ib
	/*40*/{ 125,135,51 }, // Vss,Wss,Ib
	/*41*/{ 124,134,51 }, // Vsd,Wsd,Ib
	/*42*/{ 129,123,51 }, // Wdq,Vqq,Ib
	/*43*/{ 136,126,51 }, // Wx,Vx,Ib
	/*44*/{ 50,115,51 }, // Hx,Ux,Ib
};
extern unsigned char OperandGroup4[][4] =
{
	/*0*/{ 121,45,131,51 }, // Vps,Hps,Wps,Ib
	/*1*/{ 120,44,130,51 }, // Vpd,Hpd,Wpd,Ib
	/*2*/{ 119,43,107,51 }, // Vdq,Hdq,Ry/Mw,Ib
	/*3*/{ 125,49,135,51 }, // Vss,Hss,Wss,Ib
	/*4*/{ 124,48,134,51 }, // Vsd,Hsd,Wsd,Ib
	/*5*/{ 8,41,96,33 }, // By,Gy,rDX,Ey
	/*6*/{ 126,50,136,51 }, // Vx,Hx,Wx,Ib
	/*7*/{ 123,47,133,51 }, // Vqq,Hqq,Wqq,Ib
	/*8*/{ 119,43,106,51 }, // Vdq,Hdq,Ry/Mb,Ib
	/*9*/{ 119,43,111,51 }, // Vdq,Hdq,Udq/Md,Ib
	/*10*/{ 119,43,33,51 }, // Vdq,Hdq,Ey,Ib
	/*11*/{ 119,43,129,51 }, // Vdq,Hdq,Wdq,Ib
	/*12*/{ 126,50,136,58 }, // Vx,Hx,Wx,Lx
};

extern OpcodeData HexTable1[] =
{
	{ 1,1 },{ 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 6,1 },{ 7,1 },{ 8,1 },
	{ 140,1 },{ 141,1 },{ 142,1 },{ 143,1 },{ 144,1 },{ 145,1 },{ 146,1 },{ 147,1 },
	{ 9,1 },{ 10,1 },{ 11,1 },{ 12,1 },{ 13,1 },{ 14,1 },{ 15,1 },{ 16,1 },
	{ 148,1 },{ 149,1 },{ 150,1 },{ 151,1 },{ 152,1 },{ 153,1 },{ 154,1 },{ 155,1 },
	{ 17,1 },{ 18,1 },{ 19,1 },{ 20,1 },{ 21,1 },{ 22,1 },{ 23,1 },{ 24,1 },
	{ 156,1 },{ 157,1 },{ 158,1 },{ 159,1 },{ 160,1 },{ 161,1 },{ 162,1 },{ 163,1 },
	{ 25,1 },{ 26,1 },{ 27,1 },{ 28,1 },{ 29,1 },{ 30,1 },{ 31,1 },{ 32,1 },
	{ 164,1 },{ 165,1 },{ 166,1 },{ 167,1 },{ 168,1 },{ 169,1 },{ 170,1 },{ 171,1 },
	{ 33,2 },{ 35,2 },{ 37,2 },{ 39,2 },{ 41,2 },{ 43,2 },{ 45,2 },{ 47,2 },
	{ 172,2 },{ 174,2 },{ 176,2 },{ 178,2 },{ 180,2 },{ 182,2 },{ 184,2 },{ 186,2 },
	{ 49,1 },{ 50,1 },{ 51,1 },{ 52,1 },{ 53,1 },{ 54,1 },{ 55,1 },{ 56,1 },
	{ 188,1 },{ 189,1 },{ 190,1 },{ 191,1 },{ 192,1 },{ 193,1 },{ 194,1 },{ 195,1 },
	{ 57,1 },{ 58,1 },{ 59,1 },{ 60,2 },{ 62,1 },{ 63,1 },{ 64,1 },{ 65,1 },
	{ 196,1 },{ 197,1 },{ 198,1 },{ 199,1 },{ 200,1 },{ 201,1 },{ 202,1 },{ 203,1 },
	{ 66,1 },{ 67,1 },{ 68,1 },{ 69,1 },{ 70,1 },{ 71,1 },{ 72,1 },{ 73,1 },
	{ 204,1 },{ 205,1 },{ 206,1 },{ 207,1 },{ 208,1 },{ 209,1 },{ 210,1 },{ 211,1 },
	{ 74,1 },{ 75,1 },{ 76,1 },{ 77,1 },{ 78,1 },{ 79,1 },{ 80,1 },{ 81,1 },
	{ 212,1 },{ 213,1 },{ 214,1 },{ 215,1 },{ 216,1 },{ 217,1 },{ 218,1 },{ 219,1 },
	{ 82,3 },{ 85,1 },{ 86,1 },{ 87,1 },{ 88,1 },{ 89,1 },{ 90,1 },{ 91,1 },
	{ 220,1 },{ 221,1 },{ 222,1 },{ 223,1 },{ 224,1 },{ 225,1 },{ 226,1 },{ 227,1 },
	{ 92,1 },{ 93,1 },{ 94,1 },{ 95,1 },{ 96,1 },{ 97,1 },{ 98,1 },{ 99,1 },
	{ 228,1 },{ 229,1 },{ 230,1 },{ 231,1 },{ 232,1 },{ 233,1 },{ 234,1 },{ 235,1 },
	{ 100,1 },{ 101,1 },{ 102,1 },{ 103,1 },{ 104,1 },{ 105,1 },{ 106,1 },{ 107,1 },
	{ 236,1 },{ 237,1 },{ 238,1 },{ 239,1 },{ 240,1 },{ 241,1 },{ 242,1 },{ 243,1 },
	{ 108,1 },{ 109,1 },{ 110,1 },{ 111,1 },{ 112,2 },{ 114,2 },{ 116,1 },{ 117,1 },
	{ 244,1 },{ 245,1 },{ 246,1 },{ 247,1 },{ 248,1 },{ 249,1 },{ 250,1 },{ 251,1 },
	{ 118,1 },{ 119,1 },{ 120,1 },{ 121,1 },{ 122,1 },{ 123,1 },{ 0,0 },{ 124,1 },
	{ 252,1 },{ 253,1 },{ 254,1 },{ 255,1 },{ 256,1 },{ 257,1 },{ 258,1 },{ 259,1 },
	{ 125,1 },{ 126,1 },{ 127,1 },{ 128,1 },{ 129,1 },{ 130,1 },{ 131,1 },{ 132,1 },
	{ 260,1 },{ 261,1 },{ 262,1 },{ 263,1 },{ 264,1 },{ 265,1 },{ 266,1 },{ 267,1 },
	{ 133,1 },{ 0,0 },{ 134,1 },{ 135,1 },{ 136,1 },{ 137,1 },{ 138,1 },{ 139,1 },
	{ 268,1 },{ 269,1 },{ 270,1 },{ 271,1 },{ 272,1 },{ 273,1 },{ 274,1 },{ 275,1 },
};

extern OpcodeData HexTable2[] =
{
	{ 276,1 },{ 277,1 },{ 278,1 },{ 279,1 },{ 0,0 },{ 280,1 },{ 281,1 },{ 282,1 },
	{ 377,1 },{ 378,1 },{ 0,0 },{ 379,1 },{ 0,0 },{ 380,1 },{ 0,0 },{ 0,0 },
	{ 283,4 },{ 287,4 },{ 291,5 },{ 296,2 },{ 298,2 },{ 300,2 },{ 302,4 },{ 306,2 },
	{ 381,1 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 382,1 },
	{ 308,1 },{ 309,1 },{ 310,1 },{ 311,1 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },
	{ 383,2 },{ 385,2 },{ 387,4 },{ 391,2 },{ 393,4 },{ 397,4 },{ 401,2 },{ 403,2 },
	{ 312,1 },{ 313,1 },{ 314,1 },{ 315,1 },{ 316,1 },{ 317,1 },{ 0,0 },{ 318,1 },
	{ 405,1 },{ 0,0 },{ 406,1 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },
	{ 319,1 },{ 320,1 },{ 321,1 },{ 322,1 },{ 323,1 },{ 324,1 },{ 325,1 },{ 326,1 },
	{ 407,1 },{ 408,1 },{ 409,1 },{ 410,1 },{ 411,1 },{ 412,1 },{ 413,1 },{ 414,1 },
	{ 327,2 },{ 329,4 },{ 333,2 },{ 335,2 },{ 337,2 },{ 339,2 },{ 341,2 },{ 343,2 },
	{ 415,4 },{ 419,4 },{ 423,4 },{ 427,3 },{ 430,4 },{ 434,4 },{ 438,4 },{ 442,4 },
	{ 345,2 },{ 347,2 },{ 349,2 },{ 351,2 },{ 353,2 },{ 355,2 },{ 357,2 },{ 359,2 },
	{ 446,2 },{ 448,2 },{ 450,2 },{ 452,2 },{ 459,1 },{ 460,1 },{ 454,2 },{ 456,3 },
	{ 361,4 },{ 365,1 },{ 366,1 },{ 367,1 },{ 368,2 },{ 370,2 },{ 372,2 },{ 374,3 },
	{ 461,1 },{ 462,1 },{ 0,0 },{ 0,0 },{ 469,2 },{ 471,2 },{ 463,3 },{ 466,3 },
	{ 473,1 },{ 474,1 },{ 475,1 },{ 476,1 },{ 477,1 },{ 478,1 },{ 479,1 },{ 480,1 },
	{ 566,1 },{ 567,1 },{ 568,1 },{ 569,1 },{ 570,1 },{ 571,1 },{ 572,1 },{ 573,1 },
	{ 481,1 },{ 482,1 },{ 483,1 },{ 484,1 },{ 485,1 },{ 486,1 },{ 487,1 },{ 488,1 },
	{ 574,1 },{ 575,1 },{ 576,1 },{ 577,1 },{ 578,1 },{ 579,1 },{ 580,1 },{ 581,1 },
	{ 489,1 },{ 490,1 },{ 491,1 },{ 492,1 },{ 493,1 },{ 494,1 },{ 0,0 },{ 0,0 },
	{ 582,1 },{ 583,1 },{ 584,1 },{ 585,1 },{ 586,1 },{ 587,1 },{ 588,1 },{ 589,1 },
	{ 495,1 },{ 496,1 },{ 497,1 },{ 498,1 },{ 499,1 },{ 500,1 },{ 501,1 },{ 502,1 },
	{ 590,2 },{ 592,1 },{ 593,1 },{ 594,1 },{ 595,2 },{ 597,2 },{ 599,1 },{ 600,1 },
	{ 503,1 },{ 504,1 },{ 505,4 },{ 509,1 },{ 510,2 },{ 512,2 },{ 514,2 },{ 516,1 },
	{ 601,1 },{ 602,1 },{ 603,1 },{ 604,1 },{ 605,1 },{ 606,1 },{ 607,1 },{ 608,1 },
	{ 529,2 },{ 517,2 },{ 519,2 },{ 521,2 },{ 523,2 },{ 525,2 },{ 531,3 },{ 527,2 },
	{ 609,2 },{ 611,2 },{ 613,2 },{ 615,2 },{ 617,2 },{ 619,2 },{ 621,2 },{ 623,2 },
	{ 534,2 },{ 536,2 },{ 538,2 },{ 540,2 },{ 542,2 },{ 544,2 },{ 548,3 },{ 546,2 },
	{ 625,2 },{ 627,2 },{ 629,2 },{ 631,2 },{ 633,2 },{ 635,2 },{ 637,2 },{ 639,2 },
	{ 565,1 },{ 551,2 },{ 553,2 },{ 555,2 },{ 557,2 },{ 559,2 },{ 561,2 },{ 563,2 },
	{ 641,2 },{ 643,2 },{ 645,2 },{ 647,2 },{ 649,2 },{ 651,2 },{ 653,2 },{ 0,0 },
};

extern ZipOpcodeData HexTable3Zip_38[] =
{
	{ 655,2,0 },{ 657,2,1 },{ 659,2,2 },{ 661,2,3 },{ 663,2,4 },{ 665,2,5 },{ 667,2,6 },{ 669,2,7 },
	{ 729,2,8 },{ 731,2,9 },{ 733,2,10 },{ 735,2,11 },{ 737,1,12 },{ 738,1,13 },{ 739,1,14 },{ 740,1,15 },
	{ 671,1,16 },{ 672,1,19 },{ 673,1,20 },{ 674,1,21 },{ 675,1,22 },{ 676,1,23 },{ 747,1,24 },{ 748,1,25 },
	{ 749,1,26 },{ 741,2,28 },{ 743,2,29 },{ 745,2,30 },{ 677,1,32 },{ 678,1,33 },{ 679,1,34 },{ 680,1,35 },
	{ 681,1,36 },{ 682,1,37 },{ 750,1,40 },{ 751,1,41 },{ 752,1,42 },{ 753,1,43 },{ 754,1,44 },{ 755,1,45 },
	{ 756,1,46 },{ 757,1,47 },{ 683,1,48 },{ 684,1,49 },{ 685,1,50 },{ 686,1,51 },{ 687,1,52 },{ 688,1,53 },
	{ 689,1,54 },{ 690,1,55 },{ 758,1,56 },{ 759,1,57 },{ 760,1,58 },{ 761,1,59 },{ 762,1,60 },{ 763,1,61 },
	{ 764,1,62 },{ 765,1,63 },{ 691,1,64 },{ 692,1,65 },{ 693,1,69 },{ 694,1,70 },{ 695,1,71 },{ 766,1,88 },
	{ 767,1,89 },{ 768,1,90 },{ 769,1,120 },{ 770,1,121 },{ 696,1,128 },{ 697,1,129 },{ 698,1,130 },{ 771,1,140 },
	{ 772,1,142 },{ 699,1,144 },{ 700,1,145 },{ 701,1,146 },{ 702,1,147 },{ 703,1,150 },{ 704,1,151 },{ 773,1,152 },
	{ 774,1,153 },{ 775,1,154 },{ 776,1,155 },{ 777,1,156 },{ 778,1,157 },{ 779,1,158 },{ 780,1,159 },{ 705,1,166 },
	{ 706,1,167 },{ 781,1,168 },{ 782,1,169 },{ 783,1,170 },{ 784,1,171 },{ 785,1,172 },{ 786,1,173 },{ 787,1,174 },
	{ 788,1,175 },{ 707,1,182 },{ 708,1,183 },{ 789,1,184 },{ 790,1,185 },{ 791,1,186 },{ 792,1,187 },{ 793,1,188 },
	{ 794,1,189 },{ 795,1,190 },{ 796,1,191 },{ 797,1,219 },{ 798,1,220 },{ 799,1,221 },{ 800,1,222 },{ 801,1,223 },
	{ 709,4,240 },{ 713,4,241 },{ 717,1,242 },{ 718,1,243 },{ 719,3,245 },{ 726,3,246 },{ 722,4,247 },
};

extern ZipOpcodeData HexTable3Zip_3A[] =
{
	{ 802,1,0 },{ 803,1,1 },{ 804,1,2 },{ 805,1,4 },{ 806,1,5 },{ 807,1,6 },{ 827,2,8 },{ 829,2,9 },
	{ 831,1,10 },{ 832,1,11 },{ 833,1,12 },{ 834,2,13 },{ 836,1,14 },{ 825,2,15 },{ 808,1,20 },{ 809,1,21 },
	{ 810,1,22 },{ 811,1,23 },{ 812,1,32 },{ 813,1,33 },{ 814,1,34 },{ 837,1,56 },{ 838,1,57 },{ 815,1,64 },
	{ 816,1,65 },{ 817,1,66 },{ 818,1,68 },{ 819,1,70 },{ 839,1,74 },{ 840,1,75 },{ 841,1,76 },{ 820,1,96 },
	{ 821,1,97 },{ 822,1,98 },{ 823,1,99 },{ 842,1,223 },{ 824,1,240 },
};

extern Hex_Inst HexInsts[] =
{
	{ OT_Inst,0 }, // 0
	{ OT_Inst,1 }, // 1
	{ OT_Inst,2 }, // 2
	{ OT_Inst,3 }, // 3
	{ OT_Inst,4 }, // 4
	{ OT_Inst,5 }, // 5
	{ OT_Inst,6 }, // 6
	{ OT_Inst,7 }, // 7
	{ OT_Inst,8 }, // 8
	{ OT_Inst,9 }, // 9
	{ OT_Inst,10 }, // 10
	{ OT_Inst,11 }, // 11
	{ OT_Inst,12 }, // 12
	{ OT_Inst,13 }, // 13
	{ OT_Inst,14 }, // 14
	{ OT_Inst,15 }, // 15
	{ OT_Inst,16 }, // 16
	{ OT_Inst,17 }, // 17
	{ OT_Inst,18 }, // 18
	{ OT_Inst,19 }, // 19
	{ OT_Inst,20 }, // 20
	{ OT_Inst,21 }, // 21
	{ OT_Prefix,PfxGrp_2 }, // 22
	{ OT_Inst,22 }, // 23
	{ OT_Inst,23 }, // 24
	{ OT_Inst,24 }, // 25
	{ OT_Inst,25 }, // 26
	{ OT_Inst,26 }, // 27
	{ OT_Inst,27 }, // 28
	{ OT_Inst,28 }, // 29
	{ OT_Prefix,PfxGrp_2 }, // 30
	{ OT_Inst,29 }, // 31
	{ OT_Inst,30 }, // 32
	{ OT_Prefix,PfxGrp_Rex }, // 33
	{ OT_Inst,31 }, // 34
	{ OT_Prefix,PfxGrp_Rex }, // 35
	{ OT_Inst,32 }, // 36
	{ OT_Prefix,PfxGrp_Rex }, // 37
	{ OT_Inst,33 }, // 38
	{ OT_Prefix,PfxGrp_Rex }, // 39
	{ OT_Inst,34 }, // 40
	{ OT_Prefix,PfxGrp_Rex }, // 41
	{ OT_Inst,35 }, // 42
	{ OT_Prefix,PfxGrp_Rex }, // 43
	{ OT_Inst,36 }, // 44
	{ OT_Prefix,PfxGrp_Rex }, // 45
	{ OT_Inst,37 }, // 46
	{ OT_Prefix,PfxGrp_Rex }, // 47
	{ OT_Inst,38 }, // 48
	{ OT_Inst,39 }, // 49
	{ OT_Inst,40 }, // 50
	{ OT_Inst,41 }, // 51
	{ OT_Inst,42 }, // 52
	{ OT_Inst,43 }, // 53
	{ OT_Inst,44 }, // 54
	{ OT_Inst,45 }, // 55
	{ OT_Inst,46 }, // 56
	{ OT_Inst,47 }, // 57
	{ OT_Inst,48 }, // 58
	{ OT_Inst,49 }, // 59
	{ OT_Inst,50 }, // 60
	{ OT_Prefix,PfxGrp_2 }, // 61
	{ OT_Prefix,PfxGrp_2 }, // 62
	{ OT_Prefix,PfxGrp_3 }, // 63
	{ OT_Prefix,PfxGrp_4 }, // 64
	{ OT_Inst,51 }, // 65
	{ OT_Inst,52 }, // 66
	{ OT_Inst,53 }, // 67
	{ OT_Inst,54 }, // 68
	{ OT_Inst,55 }, // 69
	{ OT_Inst,56 }, // 70
	{ OT_Inst,57 }, // 71
	{ OT_Inst,58 }, // 72
	{ OT_Grp,Grp_1 }, // 73
	{ OT_Grp,Grp_1 }, // 74
	{ OT_Grp,Grp_1 }, // 75
	{ OT_Grp,Grp_1 }, // 76
	{ OT_Inst,59 }, // 77
	{ OT_Inst,60 }, // 78
	{ OT_Inst,61 }, // 79
	{ OT_Inst,62 }, // 80
	{ OT_Inst,63 }, // 81
	{ OT_Inst,64 }, // 82
	{ OT_Inst,65 }, // 83
	{ OT_Inst,66 }, // 84
	{ OT_Inst,67 }, // 85
	{ OT_Inst,68 }, // 86
	{ OT_Inst,69 }, // 87
	{ OT_Inst,70 }, // 88
	{ OT_Inst,71 }, // 89
	{ OT_Inst,72 }, // 90
	{ OT_Inst,73 }, // 91
	{ OT_Inst,74 }, // 92
	{ OT_Inst,75 }, // 93
	{ OT_Inst,76 }, // 94
	{ OT_Inst_Change,0 }, // 95
	{ OT_Inst_Change,1 }, // 96
	{ OT_Inst_Change,2 }, // 97
	{ OT_Inst_Change,3 }, // 98
	{ OT_Inst,77 }, // 99
	{ OT_Inst,78 }, // 100
	{ OT_Inst,79 }, // 101
	{ OT_Inst,80 }, // 102
	{ OT_Inst,81 }, // 103
	{ OT_Inst,82 }, // 104
	{ OT_Inst,83 }, // 105
	{ OT_Inst,84 }, // 106
	{ OT_Grp,Grp_2 }, // 107
	{ OT_Grp,Grp_2 }, // 108
	{ OT_Inst,85 }, // 109
	{ OT_Inst,86 }, // 110
	{ OT_Inst,87 }, // 111
	{ OT_Prefix,PfxGrp_Vex }, // 112
	{ OT_Inst,88 }, // 113
	{ OT_Prefix,PfxGrp_Vex }, // 114
	{ OT_Grp,Grp_11_C6 }, // 115
	{ OT_Grp,Grp_11_C7 }, // 116
	{ OT_Grp,Grp_2 }, // 117
	{ OT_Grp,Grp_2 }, // 118
	{ OT_Grp,Grp_2 }, // 119
	{ OT_Grp,Grp_2 }, // 120
	{ OT_Inst,89 }, // 121
	{ OT_Inst,90 }, // 122
	{ OT_Inst_Change,4 }, // 123
	{ OT_Inst,91 }, // 124
	{ OT_Inst,92 }, // 125
	{ OT_Inst,93 }, // 126
	{ OT_Inst,94 }, // 127
	{ OT_Inst,95 }, // 128
	{ OT_Inst,96 }, // 129
	{ OT_Inst,97 }, // 130
	{ OT_Inst,98 }, // 131
	{ OT_Prefix,PfxGrp_1 }, // 132
	{ OT_Prefix,PfxGrp_1 }, // 133
	{ OT_Prefix,PfxGrp_1 }, // 134
	{ OT_Inst,99 }, // 135
	{ OT_Inst,100 }, // 136
	{ OT_Grp,Grp_3 }, // 137
	{ OT_Grp,Grp_3 }, // 138
	{ OT_Inst,101 }, // 139
	{ OT_Inst,102 }, // 140
	{ OT_Inst,103 }, // 141
	{ OT_Inst,104 }, // 142
	{ OT_Inst,105 }, // 143
	{ OT_Inst,106 }, // 144
	{ OT_Inst,107 }, // 145
	{ OT_Table,T_0F }, // 146
	{ OT_Inst,108 }, // 147
	{ OT_Inst,109 }, // 148
	{ OT_Inst,110 }, // 149
	{ OT_Inst,111 }, // 150
	{ OT_Inst,112 }, // 151
	{ OT_Inst,113 }, // 152
	{ OT_Inst,114 }, // 153
	{ OT_Inst,115 }, // 154
	{ OT_Inst,116 }, // 155
	{ OT_Inst,117 }, // 156
	{ OT_Inst,118 }, // 157
	{ OT_Inst,119 }, // 158
	{ OT_Inst,120 }, // 159
	{ OT_Inst,121 }, // 160
	{ OT_Prefix,PfxGrp_2 }, // 161
	{ OT_Inst,122 }, // 162
	{ OT_Inst,123 }, // 163
	{ OT_Inst,124 }, // 164
	{ OT_Inst,125 }, // 165
	{ OT_Inst,126 }, // 166
	{ OT_Inst,127 }, // 167
	{ OT_Inst,128 }, // 168
	{ OT_Prefix,PfxGrp_2 }, // 169
	{ OT_Inst,129 }, // 170
	{ OT_Inst,130 }, // 171
	{ OT_Prefix,PfxGrp_Rex }, // 172
	{ OT_Inst,131 }, // 173
	{ OT_Prefix,PfxGrp_Rex }, // 174
	{ OT_Inst,132 }, // 175
	{ OT_Prefix,PfxGrp_Rex }, // 176
	{ OT_Inst,133 }, // 177
	{ OT_Prefix,PfxGrp_Rex }, // 178
	{ OT_Inst,134 }, // 179
	{ OT_Prefix,PfxGrp_Rex }, // 180
	{ OT_Inst,135 }, // 181
	{ OT_Prefix,PfxGrp_Rex }, // 182
	{ OT_Inst,136 }, // 183
	{ OT_Prefix,PfxGrp_Rex }, // 184
	{ OT_Inst,137 }, // 185
	{ OT_Prefix,PfxGrp_Rex }, // 186
	{ OT_Inst,138 }, // 187
	{ OT_Inst,139 }, // 188
	{ OT_Inst,140 }, // 189
	{ OT_Inst,141 }, // 190
	{ OT_Inst,142 }, // 191
	{ OT_Inst,143 }, // 192
	{ OT_Inst,144 }, // 193
	{ OT_Inst,145 }, // 194
	{ OT_Inst,146 }, // 195
	{ OT_Inst,147 }, // 196
	{ OT_Inst,148 }, // 197
	{ OT_Inst,149 }, // 198
	{ OT_Inst_Change,5 }, // 199
	{ OT_Inst_Change,6 }, // 200
	{ OT_Inst_Change,7 }, // 201
	{ OT_Inst_Change,8 }, // 202
	{ OT_Inst,150 }, // 203
	{ OT_Inst,151 }, // 204
	{ OT_Inst,152 }, // 205
	{ OT_Inst,153 }, // 206
	{ OT_Inst,154 }, // 207
	{ OT_Inst,155 }, // 208
	{ OT_Inst,156 }, // 209
	{ OT_Inst,157 }, // 210
	{ OT_Inst,158 }, // 211
	{ OT_Inst,159 }, // 212
	{ OT_Inst,160 }, // 213
	{ OT_Inst,161 }, // 214
	{ OT_Inst,162 }, // 215
	{ OT_Inst,163 }, // 216
	{ OT_Inst,164 }, // 217
	{ OT_Grp,Grp_1A }, // 218
	{ OT_Inst,165 }, // 219
	{ OT_Inst,166 }, // 220
	{ OT_Inst,167 }, // 221
	{ OT_Inst,168 }, // 222
	{ OT_Inst_Change,9 }, // 223
	{ OT_Inst_Change,10 }, // 224
	{ OT_Inst,169 }, // 225
	{ OT_Inst,170 }, // 226
	{ OT_Inst,171 }, // 227
	{ OT_Inst,172 }, // 228
	{ OT_Inst_Change,11 }, // 229
	{ OT_Inst_Change,12 }, // 230
	{ OT_Inst_Change,13 }, // 231
	{ OT_Inst_Change,14 }, // 232
	{ OT_Inst_Change,15 }, // 233
	{ OT_Inst_Change,16 }, // 234
	{ OT_Inst,173 }, // 235
	{ OT_Inst,174 }, // 236
	{ OT_Inst,175 }, // 237
	{ OT_Inst,176 }, // 238
	{ OT_Inst,177 }, // 239
	{ OT_Inst,178 }, // 240
	{ OT_Inst,179 }, // 241
	{ OT_Inst,180 }, // 242
	{ OT_Inst,181 }, // 243
	{ OT_Inst,182 }, // 244
	{ OT_Inst,183 }, // 245
	{ OT_Inst,184 }, // 246
	{ OT_Inst,185 }, // 247
	{ OT_Inst,186 }, // 248
	{ OT_Inst,187 }, // 249
	{ OT_Inst_Change,17 }, // 250
	{ OT_Esc,0 }, // 251
	{ OT_Esc,0 }, // 252
	{ OT_Esc,0 }, // 253
	{ OT_Esc,0 }, // 254
	{ OT_Esc,0 }, // 255
	{ OT_Esc,0 }, // 256
	{ OT_Esc,0 }, // 257
	{ OT_Esc,0 }, // 258
	{ OT_Inst,188 }, // 259
	{ OT_Inst,189 }, // 260
	{ OT_Inst,190 }, // 261
	{ OT_Inst,191 }, // 262
	{ OT_Inst,192 }, // 263
	{ OT_Inst,193 }, // 264
	{ OT_Inst,194 }, // 265
	{ OT_Inst,195 }, // 266
	{ OT_Inst,196 }, // 267
	{ OT_Inst,197 }, // 268
	{ OT_Inst,198 }, // 269
	{ OT_Inst,199 }, // 270
	{ OT_Inst,200 }, // 271
	{ OT_Inst,201 }, // 272
	{ OT_Grp,Grp_4 }, // 273
	{ OT_Grp,Grp_5 }, // 274
	{ OT_Grp,Grp_6 }, // 275
	{ OT_Grp,Grp_7 }, // 276
	{ OT_Inst,202 }, // 277
	{ OT_Inst,203 }, // 278
	{ OT_Inst,204 }, // 279
	{ OT_Inst,205 }, // 280
	{ OT_Inst,206 }, // 281
	{ OT_Inst,207 }, // 282
	{ OT_Inst,208 }, // 283
	{ OT_Inst,209 }, // 284
	{ OT_Inst,210 }, // 285
	{ OT_Inst,211 }, // 286
	{ OT_Inst,212 }, // 287
	{ OT_Inst,213 }, // 288
	{ OT_Inst,214 }, // 289
	{ OT_Inst,215 }, // 290
	{ OT_Inst,216 }, // 291
	{ OT_Inst,217 }, // 292
	{ OT_Inst,218 }, // 293
	{ OT_Inst,219 }, // 294
	{ OT_Inst,220 }, // 295
	{ OT_Inst,221 }, // 296
	{ OT_Inst,222 }, // 297
	{ OT_Inst,223 }, // 298
	{ OT_Inst,224 }, // 299
	{ OT_Inst,225 }, // 300
	{ OT_Inst,226 }, // 301
	{ OT_Inst,227 }, // 302
	{ OT_Inst,228 }, // 303
	{ OT_Inst,229 }, // 304
	{ OT_Inst,230 }, // 305
	{ OT_Inst,231 }, // 306
	{ OT_Inst,232 }, // 307
	{ OT_Inst,233 }, // 308
	{ OT_Inst,234 }, // 309
	{ OT_Inst,235 }, // 310
	{ OT_Inst,236 }, // 311
	{ OT_Inst,237 }, // 312
	{ OT_Inst,238 }, // 313
	{ OT_Inst,239 }, // 314
	{ OT_Inst,240 }, // 315
	{ OT_Inst,241 }, // 316
	{ OT_Inst,242 }, // 317
	{ OT_Inst,243 }, // 318
	{ OT_Inst,244 }, // 319
	{ OT_Inst,245 }, // 320
	{ OT_Inst,246 }, // 321
	{ OT_Inst,247 }, // 322
	{ OT_Inst,248 }, // 323
	{ OT_Inst,249 }, // 324
	{ OT_Inst,250 }, // 325
	{ OT_Inst,251 }, // 326
	{ OT_Inst,252 }, // 327
	{ OT_Inst,253 }, // 328
	{ OT_Inst,254 }, // 329
	{ OT_Inst,255 }, // 330
	{ OT_Inst,256 }, // 331
	{ OT_Inst,257 }, // 332
	{ OT_Inst,258 }, // 333
	{ OT_Inst,259 }, // 334
	{ OT_Inst,260 }, // 335
	{ OT_Inst,261 }, // 336
	{ OT_Inst,262 }, // 337
	{ OT_Inst,263 }, // 338
	{ OT_Inst,264 }, // 339
	{ OT_Inst,265 }, // 340
	{ OT_Inst,266 }, // 341
	{ OT_Inst,267 }, // 342
	{ OT_Inst,268 }, // 343
	{ OT_Inst,269 }, // 344
	{ OT_Inst,270 }, // 345
	{ OT_Inst,271 }, // 346
	{ OT_Inst,272 }, // 347
	{ OT_Inst,273 }, // 348
	{ OT_Inst,274 }, // 349
	{ OT_Inst,275 }, // 350
	{ OT_Inst,276 }, // 351
	{ OT_Inst,277 }, // 352
	{ OT_Inst,278 }, // 353
	{ OT_Inst,279 }, // 354
	{ OT_Inst,280 }, // 355
	{ OT_Inst,281 }, // 356
	{ OT_Inst,282 }, // 357
	{ OT_Inst,283 }, // 358
	{ OT_Inst,284 }, // 359
	{ OT_Inst,285 }, // 360
	{ OT_Inst,286 }, // 361
	{ OT_Inst,287 }, // 362
	{ OT_Inst,288 }, // 363
	{ OT_Grp,Grp_12 }, // 364
	{ OT_Grp,Grp_13 }, // 365
	{ OT_Grp,Grp_14 }, // 366
	{ OT_Inst,289 }, // 367
	{ OT_Inst,290 }, // 368
	{ OT_Inst,291 }, // 369
	{ OT_Inst,292 }, // 370
	{ OT_Inst,293 }, // 371
	{ OT_Inst,294 }, // 372
	{ OT_Inst,295 }, // 373
	{ OT_Inst,296 }, // 374
	{ OT_Inst,297 }, // 375
	{ OT_Inst,298 }, // 376
	{ OT_Inst,299 }, // 377
	{ OT_Inst,300 }, // 378
	{ OT_Inst,301 }, // 379
	{ OT_Grp,Grp_16 }, // 380
	{ OT_Inst,302 }, // 381
	{ OT_Inst,303 }, // 382
	{ OT_Inst,304 }, // 383
	{ OT_Inst,305 }, // 384
	{ OT_Inst,306 }, // 385
	{ OT_Inst,307 }, // 386
	{ OT_Inst,308 }, // 387
	{ OT_Inst,309 }, // 388
	{ OT_Inst,310 }, // 389
	{ OT_Inst,311 }, // 390
	{ OT_Inst,312 }, // 391
	{ OT_Inst,313 }, // 392
	{ OT_Inst,314 }, // 393
	{ OT_Inst,315 }, // 394
	{ OT_Inst,316 }, // 395
	{ OT_Inst,317 }, // 396
	{ OT_Inst,318 }, // 397
	{ OT_Inst,319 }, // 398
	{ OT_Inst,320 }, // 399
	{ OT_Inst,321 }, // 400
	{ OT_Inst,322 }, // 401
	{ OT_Inst,323 }, // 402
	{ OT_Inst,324 }, // 403
	{ OT_Table,T_0F38 }, // 404
	{ OT_Table,T_0F3A }, // 405
	{ OT_Inst,325 }, // 406
	{ OT_Inst,326 }, // 407
	{ OT_Inst,327 }, // 408
	{ OT_Inst,328 }, // 409
	{ OT_Inst,329 }, // 410
	{ OT_Inst,330 }, // 411
	{ OT_Inst,331 }, // 412
	{ OT_Inst,332 }, // 413
	{ OT_Inst,333 }, // 414
	{ OT_Inst,334 }, // 415
	{ OT_Inst,335 }, // 416
	{ OT_Inst,336 }, // 417
	{ OT_Inst,337 }, // 418
	{ OT_Inst,338 }, // 419
	{ OT_Inst,339 }, // 420
	{ OT_Inst,340 }, // 421
	{ OT_Inst,341 }, // 422
	{ OT_Inst,342 }, // 423
	{ OT_Inst,343 }, // 424
	{ OT_Inst,344 }, // 425
	{ OT_Inst,345 }, // 426
	{ OT_Inst,346 }, // 427
	{ OT_Inst,347 }, // 428
	{ OT_Inst,348 }, // 429
	{ OT_Inst,349 }, // 430
	{ OT_Inst,350 }, // 431
	{ OT_Inst,351 }, // 432
	{ OT_Inst,352 }, // 433
	{ OT_Inst,353 }, // 434
	{ OT_Inst,354 }, // 435
	{ OT_Inst,355 }, // 436
	{ OT_Inst,356 }, // 437
	{ OT_Inst,357 }, // 438
	{ OT_Inst,358 }, // 439
	{ OT_Inst,359 }, // 440
	{ OT_Inst,360 }, // 441
	{ OT_Inst,361 }, // 442
	{ OT_Inst,362 }, // 443
	{ OT_Inst,363 }, // 444
	{ OT_Inst,364 }, // 445
	{ OT_Inst,365 }, // 446
	{ OT_Inst,366 }, // 447
	{ OT_Inst,367 }, // 448
	{ OT_Inst,368 }, // 449
	{ OT_Inst,369 }, // 450
	{ OT_Inst,370 }, // 451
	{ OT_Inst,371 }, // 452
	{ OT_Inst_Change,18 }, // 453
	{ OT_Inst_Change,19 }, // 454
	{ OT_Inst,372 }, // 455
	{ OT_Inst,373 }, // 456
	{ OT_Inst,374 }, // 457
	{ OT_Inst,375 }, // 458
	{ OT_Inst,376 }, // 459
	{ OT_Inst,377 }, // 460
	{ OT_Inst,378 }, // 461
	{ OT_Inst_Change,20 }, // 462
	{ OT_Inst_Change,21 }, // 463
	{ OT_Inst,379 }, // 464
	{ OT_Inst,380 }, // 465
	{ OT_Inst,381 }, // 466
	{ OT_Inst,382 }, // 467
	{ OT_Inst,383 }, // 468
	{ OT_Inst,384 }, // 469
	{ OT_Inst,385 }, // 470
	{ OT_Inst,386 }, // 471
	{ OT_Inst,387 }, // 472
	{ OT_Inst,388 }, // 473
	{ OT_Inst,389 }, // 474
	{ OT_Inst,390 }, // 475
	{ OT_Inst,391 }, // 476
	{ OT_Inst,392 }, // 477
	{ OT_Inst,393 }, // 478
	{ OT_Inst,394 }, // 479
	{ OT_Inst,395 }, // 480
	{ OT_Inst,396 }, // 481
	{ OT_Inst,397 }, // 482
	{ OT_Inst,398 }, // 483
	{ OT_Inst,399 }, // 484
	{ OT_Inst,400 }, // 485
	{ OT_Inst,401 }, // 486
	{ OT_Inst,402 }, // 487
	{ OT_Inst,403 }, // 488
	{ OT_Inst,404 }, // 489
	{ OT_Inst,405 }, // 490
	{ OT_Inst,406 }, // 491
	{ OT_Inst,407 }, // 492
	{ OT_Inst,408 }, // 493
	{ OT_Inst,409 }, // 494
	{ OT_Inst,410 }, // 495
	{ OT_Inst,411 }, // 496
	{ OT_Inst,412 }, // 497
	{ OT_Inst,413 }, // 498
	{ OT_Inst,414 }, // 499
	{ OT_Inst,415 }, // 500
	{ OT_Inst,416 }, // 501
	{ OT_Inst,417 }, // 502
	{ OT_Inst,418 }, // 503
	{ OT_Inst,419 }, // 504
	{ OT_Inst,420 }, // 505
	{ OT_Inst,421 }, // 506
	{ OT_Inst,422 }, // 507
	{ OT_Inst,423 }, // 508
	{ OT_Inst,424 }, // 509
	{ OT_Inst,425 }, // 510
	{ OT_Inst,426 }, // 511
	{ OT_Inst,427 }, // 512
	{ OT_Inst,428 }, // 513
	{ OT_Inst,429 }, // 514
	{ OT_Grp,Grp_9 }, // 515
	{ OT_Inst,430 }, // 516
	{ OT_Inst,431 }, // 517
	{ OT_Inst,432 }, // 518
	{ OT_Inst,433 }, // 519
	{ OT_Inst,434 }, // 520
	{ OT_Inst,435 }, // 521
	{ OT_Inst,436 }, // 522
	{ OT_Inst,437 }, // 523
	{ OT_Inst,438 }, // 524
	{ OT_Inst,439 }, // 525
	{ OT_Inst,440 }, // 526
	{ OT_Inst,441 }, // 527
	{ OT_Inst,442 }, // 528
	{ OT_Inst,443 }, // 529
	{ OT_Inst,444 }, // 530
	{ OT_Inst,445 }, // 531
	{ OT_Inst,446 }, // 532
	{ OT_Inst,447 }, // 533
	{ OT_Inst,448 }, // 534
	{ OT_Inst,449 }, // 535
	{ OT_Inst,450 }, // 536
	{ OT_Inst,451 }, // 537
	{ OT_Inst,452 }, // 538
	{ OT_Inst,453 }, // 539
	{ OT_Inst,454 }, // 540
	{ OT_Inst,455 }, // 541
	{ OT_Inst,456 }, // 542
	{ OT_Inst,457 }, // 543
	{ OT_Inst,458 }, // 544
	{ OT_Inst,459 }, // 545
	{ OT_Inst,460 }, // 546
	{ OT_Inst,461 }, // 547
	{ OT_Inst,462 }, // 548
	{ OT_Inst,463 }, // 549
	{ OT_Inst,464 }, // 550
	{ OT_Inst,465 }, // 551
	{ OT_Inst,466 }, // 552
	{ OT_Inst,467 }, // 553
	{ OT_Inst,468 }, // 554
	{ OT_Inst,469 }, // 555
	{ OT_Inst,470 }, // 556
	{ OT_Inst,471 }, // 557
	{ OT_Inst,472 }, // 558
	{ OT_Inst,473 }, // 559
	{ OT_Inst,474 }, // 560
	{ OT_Inst,475 }, // 561
	{ OT_Inst,476 }, // 562
	{ OT_Inst,477 }, // 563
	{ OT_Inst,478 }, // 564
	{ OT_Inst,479 }, // 565
	{ OT_Inst,480 }, // 566
	{ OT_Inst,481 }, // 567
	{ OT_Inst,482 }, // 568
	{ OT_Inst,483 }, // 569
	{ OT_Inst,484 }, // 570
	{ OT_Inst,485 }, // 571
	{ OT_Inst,486 }, // 572
	{ OT_Inst,487 }, // 573
	{ OT_Inst,488 }, // 574
	{ OT_Inst,489 }, // 575
	{ OT_Inst,490 }, // 576
	{ OT_Inst,491 }, // 577
	{ OT_Inst,492 }, // 578
	{ OT_Inst,493 }, // 579
	{ OT_Inst,494 }, // 580
	{ OT_Inst,495 }, // 581
	{ OT_Inst,496 }, // 582
	{ OT_Inst,497 }, // 583
	{ OT_Inst,498 }, // 584
	{ OT_Inst,499 }, // 585
	{ OT_Inst,500 }, // 586
	{ OT_Grp,Grp_15 }, // 587
	{ OT_Inst,501 }, // 588
	{ OT_Inst,502 }, // 589
	{ OT_Inst,503 }, // 590
	{ OT_Grp,Grp_10 }, // 591
	{ OT_Grp,Grp_8 }, // 592
	{ OT_Inst,504 }, // 593
	{ OT_Inst,505 }, // 594
	{ OT_Inst,506 }, // 595
	{ OT_Inst,507 }, // 596
	{ OT_Inst,508 }, // 597
	{ OT_Inst,509 }, // 598
	{ OT_Inst,510 }, // 599
	{ OT_Inst,511 }, // 600
	{ OT_Inst,512 }, // 601
	{ OT_Inst,513 }, // 602
	{ OT_Inst,514 }, // 603
	{ OT_Inst,515 }, // 604
	{ OT_Inst,516 }, // 605
	{ OT_Inst,517 }, // 606
	{ OT_Inst,518 }, // 607
	{ OT_Inst,519 }, // 608
	{ OT_Inst,520 }, // 609
	{ OT_Inst,521 }, // 610
	{ OT_Inst,522 }, // 611
	{ OT_Inst,523 }, // 612
	{ OT_Inst,524 }, // 613
	{ OT_Inst,525 }, // 614
	{ OT_Inst,526 }, // 615
	{ OT_Inst,527 }, // 616
	{ OT_Inst,528 }, // 617
	{ OT_Inst,529 }, // 618
	{ OT_Inst,530 }, // 619
	{ OT_Inst,531 }, // 620
	{ OT_Inst,532 }, // 621
	{ OT_Inst,533 }, // 622
	{ OT_Inst,534 }, // 623
	{ OT_Inst,535 }, // 624
	{ OT_Inst,536 }, // 625
	{ OT_Inst,537 }, // 626
	{ OT_Inst,538 }, // 627
	{ OT_Inst,539 }, // 628
	{ OT_Inst,540 }, // 629
	{ OT_Inst,541 }, // 630
	{ OT_Inst,542 }, // 631
	{ OT_Inst,543 }, // 632
	{ OT_Inst,544 }, // 633
	{ OT_Inst,545 }, // 634
	{ OT_Inst,546 }, // 635
	{ OT_Inst,547 }, // 636
	{ OT_Inst,548 }, // 637
	{ OT_Inst,549 }, // 638
	{ OT_Inst,550 }, // 639
	{ OT_Inst,551 }, // 640
	{ OT_Inst,552 }, // 641
	{ OT_Inst,553 }, // 642
	{ OT_Inst,554 }, // 643
	{ OT_Inst,555 }, // 644
	{ OT_Inst,556 }, // 645
	{ OT_Inst,557 }, // 646
	{ OT_Inst,558 }, // 647
	{ OT_Inst,559 }, // 648
	{ OT_Inst,560 }, // 649
	{ OT_Inst,561 }, // 650
	{ OT_Inst,562 }, // 651
	{ OT_Inst,563 }, // 652
	{ OT_Inst,564 }, // 653
	{ OT_Inst,565 }, // 654
	{ OT_Inst,566 }, // 655
	{ OT_Inst,567 }, // 656
	{ OT_Inst,568 }, // 657
	{ OT_Inst,569 }, // 658
	{ OT_Inst,570 }, // 659
	{ OT_Inst,571 }, // 660
	{ OT_Inst,572 }, // 661
	{ OT_Inst,573 }, // 662
	{ OT_Inst,574 }, // 663
	{ OT_Inst,575 }, // 664
	{ OT_Inst,576 }, // 665
	{ OT_Inst,577 }, // 666
	{ OT_Inst,578 }, // 667
	{ OT_Inst,579 }, // 668
	{ OT_Inst,580 }, // 669
	{ OT_Inst,581 }, // 670
	{ OT_Inst,582 }, // 671
	{ OT_Inst,583 }, // 672
	{ OT_Inst,584 }, // 673
	{ OT_Inst,585 }, // 674
	{ OT_Inst,586 }, // 675
	{ OT_Inst,587 }, // 676
	{ OT_Inst,588 }, // 677
	{ OT_Inst,589 }, // 678
	{ OT_Inst,590 }, // 679
	{ OT_Inst,591 }, // 680
	{ OT_Inst,592 }, // 681
	{ OT_Inst,593 }, // 682
	{ OT_Inst,594 }, // 683
	{ OT_Inst,595 }, // 684
	{ OT_Inst,596 }, // 685
	{ OT_Inst,597 }, // 686
	{ OT_Inst,598 }, // 687
	{ OT_Inst,599 }, // 688
	{ OT_Inst,600 }, // 689
	{ OT_Inst,601 }, // 690
	{ OT_Inst,602 }, // 691
	{ OT_Inst_Change,22 }, // 692
	{ OT_Inst,603 }, // 693
	{ OT_Inst_Change,23 }, // 694
	{ OT_Inst,604 }, // 695
	{ OT_Inst,605 }, // 696
	{ OT_Inst,606 }, // 697
	{ OT_Inst_Change,24 }, // 698
	{ OT_Inst_Change,25 }, // 699
	{ OT_Inst_Change,26 }, // 700
	{ OT_Inst_Change,27 }, // 701
	{ OT_Inst_Change,28 }, // 702
	{ OT_Inst_Change,29 }, // 703
	{ OT_Inst_Change,30 }, // 704
	{ OT_Inst_Change,31 }, // 705
	{ OT_Inst_Change,32 }, // 706
	{ OT_Inst_Change,33 }, // 707
	{ OT_Inst,607 }, // 708
	{ OT_Inst,608 }, // 709
	{ OT_Inst,609 }, // 710
	{ OT_Inst,610 }, // 711
	{ OT_Inst,611 }, // 712
	{ OT_Inst,612 }, // 713
	{ OT_Inst,613 }, // 714
	{ OT_Inst,614 }, // 715
	{ OT_Inst,615 }, // 716
	{ OT_Grp,Grp_17 }, // 717
	{ OT_Inst,616 }, // 718
	{ OT_Inst,617 }, // 719
	{ OT_Inst,618 }, // 720
	{ OT_Inst,619 }, // 721
	{ OT_Inst,620 }, // 722
	{ OT_Inst,621 }, // 723
	{ OT_Inst,622 }, // 724
	{ OT_Inst,623 }, // 725
	{ OT_Inst,624 }, // 726
	{ OT_Inst,625 }, // 727
	{ OT_Inst,626 }, // 728
	{ OT_Inst,627 }, // 729
	{ OT_Inst,628 }, // 730
	{ OT_Inst,629 }, // 731
	{ OT_Inst,630 }, // 732
	{ OT_Inst,631 }, // 733
	{ OT_Inst,632 }, // 734
	{ OT_Inst,633 }, // 735
	{ OT_Inst,634 }, // 736
	{ OT_Inst,635 }, // 737
	{ OT_Inst,636 }, // 738
	{ OT_Inst,637 }, // 739
	{ OT_Inst,638 }, // 740
	{ OT_Inst,639 }, // 741
	{ OT_Inst,640 }, // 742
	{ OT_Inst,641 }, // 743
	{ OT_Inst,642 }, // 744
	{ OT_Inst,643 }, // 745
	{ OT_Inst,644 }, // 746
	{ OT_Inst,645 }, // 747
	{ OT_Inst,646 }, // 748
	{ OT_Inst,647 }, // 749
	{ OT_Inst,648 }, // 750
	{ OT_Inst,649 }, // 751
	{ OT_Inst,650 }, // 752
	{ OT_Inst,651 }, // 753
	{ OT_Inst,652 }, // 754
	{ OT_Inst,653 }, // 755
	{ OT_Inst,654 }, // 756
	{ OT_Inst,655 }, // 757
	{ OT_Inst,656 }, // 758
	{ OT_Inst,657 }, // 759
	{ OT_Inst,658 }, // 760
	{ OT_Inst,659 }, // 761
	{ OT_Inst,660 }, // 762
	{ OT_Inst,661 }, // 763
	{ OT_Inst,662 }, // 764
	{ OT_Inst,663 }, // 765
	{ OT_Inst,664 }, // 766
	{ OT_Inst,665 }, // 767
	{ OT_Inst,666 }, // 768
	{ OT_Inst,667 }, // 769
	{ OT_Inst_Change,34 }, // 770
	{ OT_Inst_Change,35 }, // 771
	{ OT_Inst_Change,36 }, // 772
	{ OT_Inst_Change,37 }, // 773
	{ OT_Inst_Change,38 }, // 774
	{ OT_Inst_Change,39 }, // 775
	{ OT_Inst_Change,40 }, // 776
	{ OT_Inst_Change,41 }, // 777
	{ OT_Inst_Change,42 }, // 778
	{ OT_Inst_Change,43 }, // 779
	{ OT_Inst_Change,44 }, // 780
	{ OT_Inst_Change,45 }, // 781
	{ OT_Inst_Change,46 }, // 782
	{ OT_Inst_Change,47 }, // 783
	{ OT_Inst_Change,48 }, // 784
	{ OT_Inst_Change,49 }, // 785
	{ OT_Inst_Change,50 }, // 786
	{ OT_Inst_Change,51 }, // 787
	{ OT_Inst_Change,52 }, // 788
	{ OT_Inst_Change,53 }, // 789
	{ OT_Inst_Change,54 }, // 790
	{ OT_Inst_Change,55 }, // 791
	{ OT_Inst_Change,56 }, // 792
	{ OT_Inst_Change,57 }, // 793
	{ OT_Inst_Change,58 }, // 794
	{ OT_Inst_Change,59 }, // 795
	{ OT_Inst,668 }, // 796
	{ OT_Inst,669 }, // 797
	{ OT_Inst,670 }, // 798
	{ OT_Inst,671 }, // 799
	{ OT_Inst,672 }, // 800
	{ OT_Inst,673 }, // 801
	{ OT_Inst,674 }, // 802
	{ OT_Inst,675 }, // 803
	{ OT_Inst,676 }, // 804
	{ OT_Inst,677 }, // 805
	{ OT_Inst,678 }, // 806
	{ OT_Inst,679 }, // 807
	{ OT_Inst,680 }, // 808
	{ OT_Inst_Change,60 }, // 809
	{ OT_Inst,681 }, // 810
	{ OT_Inst,682 }, // 811
	{ OT_Inst,683 }, // 812
	{ OT_Inst_Change,61 }, // 813
	{ OT_Inst,684 }, // 814
	{ OT_Inst,685 }, // 815
	{ OT_Inst,686 }, // 816
	{ OT_Inst,687 }, // 817
	{ OT_Inst,688 }, // 818
	{ OT_Inst,689 }, // 819
	{ OT_Inst,690 }, // 820
	{ OT_Inst,691 }, // 821
	{ OT_Inst,692 }, // 822
	{ OT_Inst,693 }, // 823
	{ OT_Inst,694 }, // 824
	{ OT_Inst,695 }, // 825
	{ OT_Inst,696 }, // 826
	{ OT_Inst,697 }, // 827
	{ OT_Inst,698 }, // 828
	{ OT_Inst,699 }, // 829
	{ OT_Inst,700 }, // 830
	{ OT_Inst,701 }, // 831
	{ OT_Inst,702 }, // 832
	{ OT_Inst,703 }, // 833
	{ OT_Inst,704 }, // 834
	{ OT_Inst,705 }, // 835
	{ OT_Inst,706 }, // 836
	{ OT_Inst,707 }, // 837
	{ OT_Inst,708 }, // 838
	{ OT_Inst,709 }, // 839
	{ OT_Inst,710 }, // 840
	{ OT_Inst,711 }, // 841
};

extern InstData Inst[] =
{
	{ NULL,NULL,1,2,1,35 }, // 0
	{ NULL,NULL,2,2,1,35 }, // 1
	{ NULL,NULL,3,2,1,35 }, // 2
	{ NULL,NULL,4,2,1,35 }, // 3
	{ NULL,NULL,5,2,1,35 }, // 4
	{ NULL,NULL,6,2,1,35 }, // 5
	{ NULL,S_i64,1,1,1,345 }, // 6
	{ NULL,S_i64,1,1,1,304 }, // 7
	{ NULL,NULL,1,2,1,33 }, // 8
	{ NULL,NULL,2,2,1,33 }, // 9
	{ NULL,NULL,3,2,1,33 }, // 10
	{ NULL,NULL,4,2,1,33 }, // 11
	{ NULL,NULL,5,2,1,33 }, // 12
	{ NULL,NULL,6,2,1,33 }, // 13
	{ NULL,S_i64,2,1,1,345 }, // 14
	{ NULL,S_i64,2,1,1,304 }, // 15
	{ NULL,NULL,1,2,1,37 }, // 16
	{ NULL,NULL,2,2,1,37 }, // 17
	{ NULL,NULL,3,2,1,37 }, // 18
	{ NULL,NULL,4,2,1,37 }, // 19
	{ NULL,NULL,5,2,1,37 }, // 20
	{ NULL,NULL,6,2,1,37 }, // 21
	{ NULL,S_i64,0,0,1,116 }, // 22
	{ NULL,NULL,1,2,1,813 }, // 23
	{ NULL,NULL,2,2,1,813 }, // 24
	{ NULL,NULL,3,2,1,813 }, // 25
	{ NULL,NULL,4,2,1,813 }, // 26
	{ NULL,NULL,5,2,1,813 }, // 27
	{ NULL,NULL,6,2,1,813 }, // 28
	{ NULL,S_i64,0,0,1,29 }, // 29
	{ NULL,S_i64,3,1,1,131 }, // 30
	{ NULL,S_i64,4,1,1,131 }, // 31
	{ NULL,S_i64,5,1,1,131 }, // 32
	{ NULL,S_i64,6,1,1,131 }, // 33
	{ NULL,S_i64,7,1,1,131 }, // 34
	{ NULL,S_i64,8,1,1,131 }, // 35
	{ NULL,S_i64,9,1,1,131 }, // 36
	{ NULL,S_i64,10,1,1,131 }, // 37
	{ NULL,S_d64,11,1,1,345 }, // 38
	{ NULL,S_d64,12,1,1,345 }, // 39
	{ NULL,S_d64,13,1,1,345 }, // 40
	{ NULL,S_d64,14,1,1,345 }, // 41
	{ NULL,S_d64,15,1,1,345 }, // 42
	{ NULL,S_d64,16,1,1,345 }, // 43
	{ NULL,S_d64,17,1,1,345 }, // 44
	{ NULL,S_d64,18,1,1,345 }, // 45
	{ NULL,S_i64,0,0,2,346 }, // 46
	{ NULL,S_i64,0,0,2,305 }, // 47
	{ NULL,S_i64,7,2,1,46 }, // 48
	{ NULL,S_i64,8,2,1,39 }, // 49
	{ NULL,S_o64,4,2,1,240 }, // 50
	{ NULL,S_f64,19,1,1,185 }, // 51
	{ NULL,S_f64,19,1,1,179 }, // 52
	{ NULL,S_f64,19,1,3,153 }, // 53
	{ NULL,S_f64,19,1,3,168 }, // 54
	{ NULL,S_f64,19,1,2,190 }, // 55
	{ NULL,S_f64,19,1,2,183 }, // 56
	{ NULL,S_f64,19,1,2,158 }, // 57
	{ NULL,S_f64,19,1,2,171 }, // 58
	{ NULL,NULL,1,2,1,437 }, // 59
	{ NULL,NULL,2,2,1,437 }, // 60
	{ NULL,NULL,1,2,1,808 }, // 61
	{ NULL,NULL,2,2,1,808 }, // 62
	{ NULL,NULL,0,0,1,246 }, // 63
	{ C_F3,NULL,0,0,1,272 }, // 64
	{ NULL,NULL,12,2,1,808 }, // 65
	{ NULL,NULL,13,2,1,808 }, // 66
	{ NULL,NULL,14,2,1,808 }, // 67
	{ NULL,NULL,15,2,1,808 }, // 68
	{ NULL,NULL,16,2,1,808 }, // 69
	{ NULL,NULL,17,2,1,808 }, // 70
	{ NULL,NULL,18,2,1,808 }, // 71
	{ NULL,NULL,19,2,1,808 }, // 72
	{ NULL,NULL,20,2,1,224 }, // 73
	{ NULL,NULL,21,2,1,224 }, // 74
	{ NULL,NULL,22,2,1,224 }, // 75
	{ NULL,NULL,23,2,1,224 }, // 76
	{ NULL,NULL,28,2,1,224 }, // 77
	{ NULL,NULL,29,2,1,224 }, // 78
	{ NULL,NULL,30,2,1,224 }, // 79
	{ NULL,NULL,31,2,1,224 }, // 80
	{ NULL,NULL,32,2,1,224 }, // 81
	{ NULL,NULL,33,2,1,224 }, // 82
	{ NULL,NULL,34,2,1,224 }, // 83
	{ NULL,NULL,35,2,1,224 }, // 84
	{ NULL,S_f64,20,1,1,362 }, // 85
	{ NULL,S_f64,0,0,1,362 }, // 86
	{ NULL,S_i64,36,2,1,198 }, // 87
	{ NULL,S_i64,36,2,1,195 }, // 88
	{ NULL,S_i64,21,1,1,31 }, // 89
	{ NULL,S_i64,21,1,1,30 }, // 90
	{ NULL,S_f64,19,1,2,215 }, // 91
	{ NULL,S_f64,19,1,2,213 }, // 92
	{ NULL,S_f64,19,1,1,212 }, // 93
	{ NULL,S_f64,19,1,1,188 }, // 94
	{ NULL,NULL,5,2,1,130 }, // 95
	{ NULL,NULL,41,2,1,130 }, // 96
	{ NULL,NULL,42,2,1,249 }, // 97
	{ NULL,NULL,43,2,1,249 }, // 98
	{ NULL,NULL,0,0,1,127 }, // 99
	{ NULL,NULL,0,0,1,65 }, // 100
	{ NULL,NULL,1,2,1,248 }, // 101
	{ NULL,NULL,2,2,1,248 }, // 102
	{ NULL,NULL,3,2,1,248 }, // 103
	{ NULL,NULL,4,2,1,248 }, // 104
	{ NULL,NULL,5,2,1,248 }, // 105
	{ NULL,NULL,6,2,1,248 }, // 106
	{ NULL,S_i64,24,1,1,345 }, // 107
	{ NULL,NULL,1,2,1,370 }, // 108
	{ NULL,NULL,2,2,1,370 }, // 109
	{ NULL,NULL,3,2,1,370 }, // 110
	{ NULL,NULL,4,2,1,370 }, // 111
	{ NULL,NULL,5,2,1,370 }, // 112
	{ NULL,NULL,6,2,1,370 }, // 113
	{ NULL,S_i64,25,1,1,345 }, // 114
	{ NULL,S_i64,25,1,1,304 }, // 115
	{ NULL,NULL,1,2,1,431 }, // 116
	{ NULL,NULL,2,2,1,431 }, // 117
	{ NULL,NULL,3,2,1,431 }, // 118
	{ NULL,NULL,4,2,1,431 }, // 119
	{ NULL,NULL,5,2,1,431 }, // 120
	{ NULL,NULL,6,2,1,431 }, // 121
	{ NULL,S_i64,0,0,1,117 }, // 122
	{ NULL,NULL,1,2,1,96 }, // 123
	{ NULL,NULL,2,2,1,96 }, // 124
	{ NULL,NULL,3,2,1,96 }, // 125
	{ NULL,NULL,4,2,1,96 }, // 126
	{ NULL,NULL,5,2,1,96 }, // 127
	{ NULL,NULL,6,2,1,96 }, // 128
	{ NULL,S_i64,0,0,1,32 }, // 129
	{ NULL,S_i64,3,1,1,118 }, // 130
	{ NULL,S_i64,4,1,1,118 }, // 131
	{ NULL,S_i64,5,1,1,118 }, // 132
	{ NULL,S_i64,6,1,1,118 }, // 133
	{ NULL,S_i64,7,1,1,118 }, // 134
	{ NULL,S_i64,8,1,1,118 }, // 135
	{ NULL,S_i64,9,1,1,118 }, // 136
	{ NULL,S_i64,10,1,1,118 }, // 137
	{ NULL,S_d64,11,1,1,304 }, // 138
	{ NULL,S_d64,12,1,1,304 }, // 139
	{ NULL,S_d64,13,1,1,304 }, // 140
	{ NULL,S_d64,14,1,1,304 }, // 141
	{ NULL,S_d64,15,1,1,304 }, // 142
	{ NULL,S_d64,16,1,1,304 }, // 143
	{ NULL,S_d64,17,1,1,304 }, // 144
	{ NULL,S_d64,18,1,1,304 }, // 145
	{ NULL,S_d64,26,1,1,345 }, // 146
	{ NULL,NULL,1,3,1,129 }, // 147
	{ NULL,S_d64,21,1,1,345 }, // 148
	{ NULL,NULL,2,3,1,129 }, // 149
	{ NULL,S_f64,19,1,1,189 }, // 150
	{ NULL,S_f64,19,1,1,182 }, // 151
	{ NULL,S_f64,19,1,2,186 }, // 152
	{ NULL,S_f64,19,1,2,180 }, // 153
	{ NULL,S_f64,19,1,2,162 }, // 154
	{ NULL,S_f64,19,1,2,175 }, // 155
	{ NULL,S_f64,19,1,2,164 }, // 156
	{ NULL,S_f64,19,1,2,177 }, // 157
	{ NULL,NULL,1,2,1,224 }, // 158
	{ NULL,NULL,2,2,1,224 }, // 159
	{ NULL,NULL,3,2,1,224 }, // 160
	{ NULL,NULL,4,2,1,224 }, // 161
	{ NULL,NULL,48,2,1,224 }, // 162
	{ NULL,NULL,49,2,1,196 }, // 163
	{ NULL,NULL,50,2,1,224 }, // 164
	{ NULL,NULL,0,0,3,56 }, // 165
	{ NULL,NULL,0,0,3,113 }, // 166
	{ NULL,S_i64,27,1,1,55 }, // 167
	{ NULL,NULL,0,0,2,122 }, // 168
	{ NULL,NULL,0,0,1,367 }, // 169
	{ NULL,NULL,0,0,1,192 }, // 170
	{ NULL,NULL,5,2,1,437 }, // 171
	{ NULL,NULL,6,2,1,437 }, // 172
	{ NULL,NULL,57,2,1,224 }, // 173
	{ NULL,NULL,58,2,1,224 }, // 174
	{ NULL,NULL,59,2,1,224 }, // 175
	{ NULL,NULL,60,2,1,224 }, // 176
	{ NULL,NULL,61,2,1,224 }, // 177
	{ NULL,NULL,62,2,1,224 }, // 178
	{ NULL,NULL,63,2,1,224 }, // 179
	{ NULL,NULL,64,2,1,224 }, // 180
	{ NULL,NULL,65,2,1,121 }, // 181
	{ NULL,S_d64,0,0,1,197 }, // 182
	{ NULL,NULL,20,1,1,362 }, // 183
	{ NULL,NULL,0,0,1,362 }, // 184
	{ NULL,NULL,0,0,1,138 }, // 185
	{ NULL,NULL,21,1,1,137 }, // 186
	{ NULL,S_i64,0,0,1,139 }, // 187
	{ NULL,S_f64,29,1,1,55 }, // 188
	{ NULL,S_f64,29,1,1,166 }, // 189
	{ NULL,S_i64,27,1,1,166 }, // 190
	{ NULL,S_f64,19,1,1,166 }, // 191
	{ NULL,NULL,66,2,1,130 }, // 192
	{ NULL,NULL,67,2,1,130 }, // 193
	{ NULL,NULL,68,2,1,249 }, // 194
	{ NULL,NULL,69,2,1,249 }, // 195
	{ NULL,NULL,0,0,1,60 }, // 196
	{ NULL,NULL,0,0,1,420 }, // 197
	{ NULL,NULL,0,0,1,63 }, // 198
	{ NULL,NULL,0,0,1,422 }, // 199
	{ NULL,NULL,0,0,1,61 }, // 200
	{ NULL,NULL,0,0,1,421 }, // 201
	{ NULL,NULL,70,2,1,193 }, // 202
	{ NULL,NULL,70,2,1,217 }, // 203
	{ NULL,S_o64,0,0,1,433 }, // 204
	{ NULL,NULL,0,0,1,64 }, // 205
	{ NULL,S_o64,0,0,1,436 }, // 206
	{ NULL,NULL,71,2,1,615 }, // 207
	{ C_66,NULL,74,2,1,614 }, // 208
	{ C_F3,NULL,8,3,1,613 }, // 209
	{ C_F2,NULL,10,3,1,610 }, // 210
	{ NULL,NULL,72,2,1,615 }, // 211
	{ C_66,NULL,75,2,1,614 }, // 212
	{ C_F3,NULL,9,3,1,613 }, // 213
	{ C_F2,NULL,11,3,1,610 }, // 214
	{ NULL,NULL,3,3,1,602 }, // 215
	{ NULL,NULL,4,3,1,597 }, // 216
	{ C_66,NULL,3,3,1,601 }, // 217
	{ C_F3,NULL,76,2,1,612 }, // 218
	{ C_F2,NULL,76,2,1,594 }, // 219
	{ NULL,NULL,73,2,1,602 }, // 220
	{ C_66,NULL,73,2,1,601 }, // 221
	{ NULL,NULL,5,3,1,796 }, // 222
	{ C_66,NULL,5,3,1,795 }, // 223
	{ NULL,NULL,5,3,1,794 }, // 224
	{ C_66,NULL,5,3,1,793 }, // 225
	{ NULL,S_v1,6,3,1,599 }, // 226
	{ NULL,NULL,7,3,1,600 }, // 227
	{ C_66,S_v1,6,3,1,598 }, // 228
	{ C_F3,NULL,76,2,1,611 }, // 229
	{ NULL,S_v1,73,2,1,599 }, // 230
	{ C_66,S_v1,73,2,1,598 }, // 231
	{ NULL,NULL,77,2,1,224 }, // 232
	{ NULL,NULL,78,2,1,224 }, // 233
	{ NULL,NULL,79,2,1,224 }, // 234
	{ NULL,NULL,80,2,1,224 }, // 235
	{ NULL,NULL,0,0,1,804 }, // 236
	{ NULL,NULL,0,0,1,360 }, // 237
	{ NULL,NULL,0,0,1,356 }, // 238
	{ NULL,NULL,0,0,1,357 }, // 239
	{ NULL,NULL,0,0,1,434 }, // 240
	{ NULL,NULL,0,0,1,435 }, // 241
	{ NULL,NULL,0,0,1,126 }, // 242
	{ NULL,NULL,4,2,1,92 }, // 243
	{ NULL,NULL,4,2,1,88 }, // 244
	{ NULL,NULL,4,2,3,71 }, // 245
	{ NULL,NULL,4,2,3,68 }, // 246
	{ NULL,NULL,4,2,2,76 }, // 247
	{ NULL,NULL,4,2,2,82 }, // 248
	{ NULL,NULL,4,2,2,74 }, // 249
	{ NULL,NULL,4,2,2,66 }, // 250
	{ NULL,NULL,81,2,1,604 }, // 251
	{ C_66,NULL,82,2,1,603 }, // 252
	{ NULL,NULL,71,2,1,782 }, // 253
	{ C_66,NULL,74,2,1,781 }, // 254
	{ C_F3,NULL,14,3,1,784 }, // 255
	{ C_F2,NULL,15,3,1,783 }, // 256
	{ NULL,NULL,71,2,1,777 }, // 257
	{ C_F3,NULL,14,3,1,778 }, // 258
	{ NULL,NULL,71,2,1,771 }, // 259
	{ C_F3,NULL,14,3,1,772 }, // 260
	{ NULL,NULL,12,3,1,455 }, // 261
	{ C_66,NULL,13,3,1,454 }, // 262
	{ NULL,NULL,12,3,1,453 }, // 263
	{ C_66,NULL,13,3,1,452 }, // 264
	{ NULL,NULL,12,3,1,629 }, // 265
	{ C_66,NULL,13,3,1,628 }, // 266
	{ NULL,NULL,12,3,1,798 }, // 267
	{ C_66,NULL,13,3,1,797 }, // 268
	{ NULL,NULL,83,2,1,342 }, // 269
	{ C_66,NULL,5,3,1,766 }, // 270
	{ NULL,NULL,83,2,1,344 }, // 271
	{ C_66,NULL,5,3,1,769 }, // 272
	{ NULL,NULL,83,2,1,343 }, // 273
	{ C_66,NULL,5,3,1,767 }, // 274
	{ NULL,NULL,84,2,1,259 }, // 275
	{ C_66,NULL,5,3,1,634 }, // 276
	{ NULL,NULL,84,2,1,279 }, // 277
	{ C_66,NULL,5,3,1,664 }, // 278
	{ NULL,NULL,84,2,1,281 }, // 279
	{ C_66,NULL,5,3,1,667 }, // 280
	{ NULL,NULL,84,2,1,280 }, // 281
	{ C_66,NULL,5,3,1,665 }, // 282
	{ NULL,NULL,84,2,1,260 }, // 283
	{ C_66,NULL,5,3,1,636 }, // 284
	{ NULL,NULL,16,3,1,319 }, // 285
	{ C_66,NULL,17,3,1,732 }, // 286
	{ C_F3,NULL,17,3,1,733 }, // 287
	{ C_F2,NULL,17,3,1,734 }, // 288
	{ NULL,NULL,84,2,1,276 }, // 289
	{ C_66,NULL,5,3,1,658 }, // 290
	{ NULL,NULL,84,2,1,278 }, // 291
	{ C_66,NULL,5,3,1,661 }, // 292
	{ NULL,NULL,84,2,1,277 }, // 293
	{ C_66,NULL,5,3,1,659 }, // 294
	{ NULL,NULL,0,0,1,120 }, // 295
	{ NULL,S_v,0,0,1,800 }, // 296
	{ NULL,S_v,0,0,1,799 }, // 297
	{ NULL,NULL,0,0,1,140 }, // 298
	{ NULL,NULL,0,0,1,801 }, // 299
	{ NULL,S_1B,0,0,1,439 }, // 300
	{ NULL,NULL,23,1,1,316 }, // 301
	{ NULL,NULL,23,1,1,246 }, // 302
	{ NULL,NULL,71,2,1,591 }, // 303
	{ C_66,NULL,74,2,1,590 }, // 304
	{ NULL,NULL,72,2,1,591 }, // 305
	{ C_66,NULL,75,2,1,590 }, // 306
	{ NULL,NULL,85,2,1,109 }, // 307
	{ C_66,NULL,89,2,1,108 }, // 308
	{ C_F3,NULL,18,3,1,481 }, // 309
	{ C_F2,NULL,19,3,1,480 }, // 310
	{ NULL,NULL,86,2,1,608 }, // 311
	{ C_66,NULL,90,2,1,607 }, // 312
	{ NULL,NULL,87,2,1,112 }, // 313
	{ C_66,NULL,91,2,1,111 }, // 314
	{ C_F3,NULL,94,2,1,487 }, // 315
	{ C_F2,NULL,95,2,1,486 }, // 316
	{ NULL,NULL,87,2,1,110 }, // 317
	{ C_66,NULL,92,2,1,107 }, // 318
	{ C_F3,NULL,94,2,1,483 }, // 319
	{ C_F2,NULL,95,2,1,478 }, // 320
	{ NULL,NULL,88,2,1,792 }, // 321
	{ C_66,NULL,93,2,1,791 }, // 322
	{ NULL,NULL,88,2,1,469 }, // 323
	{ C_66,NULL,93,2,1,468 }, // 324
	{ NULL,NULL,4,2,1,95 }, // 325
	{ NULL,NULL,4,2,1,91 }, // 326
	{ NULL,NULL,4,2,2,93 }, // 327
	{ NULL,NULL,4,2,2,89 }, // 328
	{ NULL,NULL,4,2,2,78 }, // 329
	{ NULL,NULL,4,2,2,84 }, // 330
	{ NULL,NULL,4,2,2,80 }, // 331
	{ NULL,NULL,4,2,2,86 }, // 332
	{ NULL,NULL,12,3,1,441 }, // 333
	{ C_66,NULL,13,3,1,440 }, // 334
	{ C_F3,NULL,14,3,1,443 }, // 335
	{ C_F2,NULL,15,3,1,442 }, // 336
	{ NULL,NULL,12,3,1,622 }, // 337
	{ C_66,NULL,13,3,1,621 }, // 338
	{ C_F3,NULL,14,3,1,624 }, // 339
	{ C_F2,NULL,15,3,1,623 }, // 340
	{ NULL,NULL,96,2,1,476 }, // 341
	{ C_66,NULL,98,2,1,473 }, // 342
	{ C_F3,NULL,20,3,1,482 }, // 343
	{ C_F2,NULL,21,3,1,479 }, // 344
	{ NULL,NULL,97,2,1,471 }, // 345
	{ C_66,NULL,99,2,1,475 }, // 346
	{ C_F3,NULL,99,2,1,485 }, // 347
	{ NULL,NULL,12,3,1,786 }, // 348
	{ C_66,NULL,13,3,1,785 }, // 349
	{ C_F3,NULL,14,3,1,788 }, // 350
	{ C_F2,NULL,15,3,1,787 }, // 351
	{ NULL,NULL,12,3,1,586 }, // 352
	{ C_66,NULL,13,3,1,585 }, // 353
	{ C_F3,NULL,14,3,1,588 }, // 354
	{ C_F2,NULL,15,3,1,587 }, // 355
	{ NULL,NULL,12,3,1,489 }, // 356
	{ C_66,NULL,13,3,1,488 }, // 357
	{ C_F3,NULL,14,3,1,491 }, // 358
	{ C_F2,NULL,15,3,1,490 }, // 359
	{ NULL,NULL,12,3,1,579 }, // 360
	{ C_66,NULL,13,3,1,578 }, // 361
	{ C_F3,NULL,14,3,1,581 }, // 362
	{ C_F2,NULL,15,3,1,580 }, // 363
	{ NULL,NULL,83,2,1,339 }, // 364
	{ C_66,NULL,5,3,1,762 }, // 365
	{ NULL,NULL,83,2,1,341 }, // 366
	{ C_66,NULL,5,3,1,765 }, // 367
	{ NULL,NULL,83,2,1,340 }, // 368
	{ C_66,NULL,5,3,1,763 }, // 369
	{ NULL,NULL,83,2,1,258 }, // 370
	{ C_66,NULL,5,3,1,633 }, // 371
	{ NULL,NULL,84,2,1,231 }, // 372
	{ C_66,NULL,76,2,1,595 }, // 373
	{ C_F3,NULL,76,2,1,596 }, // 374
	{ C_66,NULL,5,3,1,768 }, // 375
	{ C_66,NULL,5,3,1,764 }, // 376
	{ NULL,NULL,102,2,1,619 }, // 377
	{ NULL,NULL,103,2,1,625 }, // 378
	{ C_F3,NULL,108,2,1,609 }, // 379
	{ NULL,NULL,105,2,1,231 }, // 380
	{ C_66,NULL,107,2,1,595 }, // 381
	{ C_F3,NULL,107,2,1,596 }, // 382
	{ C_66,NULL,13,3,1,567 }, // 383
	{ C_F2,NULL,12,3,1,568 }, // 384
	{ C_66,NULL,13,3,1,569 }, // 385
	{ C_F2,NULL,12,3,1,570 }, // 386
	{ NULL,S_f64,29,1,1,185 }, // 387
	{ NULL,S_f64,29,1,1,179 }, // 388
	{ NULL,S_f64,29,1,2,156 }, // 389
	{ NULL,S_f64,29,1,3,150 }, // 390
	{ NULL,S_f64,29,1,2,160 }, // 391
	{ NULL,S_f64,29,1,2,173 }, // 392
	{ NULL,S_f64,29,1,2,158 }, // 393
	{ NULL,S_f64,29,1,2,148 }, // 394
	{ NULL,NULL,22,1,1,403 }, // 395
	{ NULL,NULL,22,1,1,399 }, // 396
	{ NULL,NULL,22,1,3,382 }, // 397
	{ NULL,NULL,22,1,3,379 }, // 398
	{ NULL,NULL,22,1,2,387 }, // 399
	{ NULL,NULL,22,1,2,393 }, // 400
	{ NULL,NULL,22,1,2,385 }, // 401
	{ NULL,NULL,22,1,2,377 }, // 402
	{ NULL,S_d64,30,1,1,345 }, // 403
	{ NULL,S_d64,30,1,1,304 }, // 404
	{ NULL,NULL,0,0,1,105 }, // 405
	{ NULL,NULL,2,2,1,50 }, // 406
	{ NULL,NULL,22,3,1,411 }, // 407
	{ NULL,NULL,23,3,1,411 }, // 408
	{ NULL,NULL,1,2,1,103 }, // 409
	{ NULL,NULL,2,2,1,103 }, // 410
	{ NULL,NULL,109,2,1,218 }, // 411
	{ NULL,NULL,2,2,1,52 }, // 412
	{ NULL,NULL,109,2,1,200 }, // 413
	{ NULL,NULL,109,2,1,202 }, // 414
	{ NULL,NULL,110,2,1,241 }, // 415
	{ NULL,NULL,70,2,1,241 }, // 416
	{ NULL,NULL,1,2,1,806 }, // 417
	{ NULL,NULL,2,2,1,806 }, // 418
	{ NULL,NULL,1,4,1,465 }, // 419
	{ C_66,NULL,2,4,1,464 }, // 420
	{ C_F3,NULL,4,4,1,467 }, // 421
	{ C_F2,NULL,5,4,1,466 }, // 422
	{ NULL,NULL,111,2,1,229 }, // 423
	{ NULL,NULL,24,3,1,291 }, // 424
	{ C_66,NULL,3,4,1,692 }, // 425
	{ NULL,NULL,25,3,1,284 }, // 426
	{ C_66,NULL,26,3,1,681 }, // 427
	{ NULL,NULL,1,4,1,780 }, // 428
	{ C_66,NULL,2,4,1,779 }, // 429
	{ NULL,NULL,84,2,1,330 }, // 430
	{ C_66,NULL,5,3,1,752 }, // 431
	{ NULL,NULL,84,2,1,328 }, // 432
	{ C_66,NULL,5,3,1,747 }, // 433
	{ NULL,NULL,84,2,1,329 }, // 434
	{ C_66,NULL,5,3,1,749 }, // 435
	{ NULL,NULL,84,2,1,263 }, // 436
	{ C_66,NULL,5,3,1,639 }, // 437
	{ NULL,NULL,84,2,1,302 }, // 438
	{ C_66,NULL,5,3,1,727 }, // 439
	{ NULL,NULL,112,2,1,298 }, // 440
	{ C_66,NULL,114,2,1,709 }, // 441
	{ C_66,NULL,13,3,1,444 }, // 442
	{ C_F2,NULL,12,3,1,445 }, // 443
	{ C_66,NULL,113,2,1,609 }, // 444
	{ C_F3,NULL,115,2,1,232 }, // 445
	{ C_F2,NULL,116,2,1,228 }, // 446
	{ NULL,NULL,84,2,1,273 }, // 447
	{ C_66,NULL,5,3,1,648 }, // 448
	{ NULL,NULL,84,2,1,327 }, // 449
	{ C_66,NULL,5,3,1,746 }, // 450
	{ NULL,NULL,84,2,1,326 }, // 451
	{ C_66,NULL,5,3,1,744 }, // 452
	{ NULL,NULL,84,2,1,274 }, // 453
	{ C_66,NULL,5,3,1,649 }, // 454
	{ NULL,NULL,84,2,1,300 }, // 455
	{ C_66,NULL,5,3,1,724 }, // 456
	{ NULL,NULL,84,2,1,301 }, // 457
	{ C_66,NULL,5,3,1,725 }, // 458
	{ NULL,NULL,117,2,1,230 }, // 459
	{ C_66,NULL,119,2,1,605 }, // 460
	{ C_66,NULL,118,2,1,484 }, // 461
	{ C_F3,NULL,118,2,1,470 }, // 462
	{ C_F2,NULL,118,2,1,472 }, // 463
	{ NULL,NULL,84,2,1,325 }, // 464
	{ C_66,NULL,5,3,1,743 }, // 465
	{ NULL,NULL,84,2,1,323 }, // 466
	{ C_66,NULL,5,3,1,738 }, // 467
	{ NULL,NULL,84,2,1,324 }, // 468
	{ C_66,NULL,5,3,1,740 }, // 469
	{ NULL,NULL,84,2,1,303 }, // 470
	{ C_66,NULL,5,3,1,728 }, // 471
	{ NULL,NULL,84,2,1,293 }, // 472
	{ C_66,NULL,5,3,1,694 }, // 473
	{ NULL,NULL,84,2,1,317 }, // 474
	{ C_66,NULL,5,3,1,730 }, // 475
	{ NULL,NULL,120,2,1,221 }, // 476
	{ C_66,NULL,121,2,1,575 }, // 477
	{ C_F2,NULL,122,2,1,574 }, // 478
	{ NULL,S_f64,29,1,1,189 }, // 479
	{ NULL,S_f64,29,1,1,182 }, // 480
	{ NULL,S_f64,29,1,2,186 }, // 481
	{ NULL,S_f64,29,1,2,180 }, // 482
	{ NULL,S_f64,29,1,2,162 }, // 483
	{ NULL,S_f64,29,1,2,175 }, // 484
	{ NULL,S_f64,29,1,2,164 }, // 485
	{ NULL,S_f64,29,1,2,177 }, // 486
	{ NULL,NULL,22,1,1,406 }, // 487
	{ NULL,NULL,22,1,1,402 }, // 488
	{ NULL,NULL,22,1,2,404 }, // 489
	{ NULL,NULL,22,1,2,400 }, // 490
	{ NULL,NULL,22,1,2,389 }, // 491
	{ NULL,NULL,22,1,2,395 }, // 492
	{ NULL,NULL,22,1,2,391 }, // 493
	{ NULL,NULL,22,1,2,397 }, // 494
	{ NULL,S_d64,31,1,1,345 }, // 495
	{ NULL,S_d64,31,1,1,304 }, // 496
	{ NULL,NULL,0,0,1,366 }, // 497
	{ NULL,NULL,2,2,1,53 }, // 498
	{ NULL,NULL,22,3,1,414 }, // 499
	{ NULL,NULL,23,3,1,414 }, // 500
	{ NULL,NULL,4,2,1,129 }, // 501
	{ NULL,NULL,0,0,1,167 }, // 502
	{ C_F3,NULL,4,2,1,307 }, // 503
	{ NULL,NULL,2,2,1,51 }, // 504
	{ NULL,NULL,4,2,1,47 }, // 505
	{ C_F3,NULL,4,2,1,438 }, // 506
	{ NULL,NULL,4,2,1,48 }, // 507
	{ C_F3,NULL,4,2,1,220 }, // 508
	{ NULL,NULL,110,2,1,239 }, // 509
	{ NULL,NULL,70,2,1,239 }, // 510
	{ NULL,NULL,32,1,1,49 }, // 511
	{ NULL,NULL,33,1,1,49 }, // 512
	{ NULL,NULL,34,1,1,49 }, // 513
	{ NULL,NULL,35,1,1,49 }, // 514
	{ NULL,NULL,36,1,1,49 }, // 515
	{ NULL,NULL,37,1,1,49 }, // 516
	{ NULL,NULL,38,1,1,49 }, // 517
	{ NULL,NULL,39,1,1,49 }, // 518
	{ NULL,NULL,84,2,1,336 }, // 519
	{ C_66,NULL,5,3,1,758 }, // 520
	{ NULL,NULL,84,2,1,337 }, // 521
	{ C_66,NULL,5,3,1,759 }, // 522
	{ NULL,NULL,84,2,1,297 }, // 523
	{ C_66,NULL,5,3,1,706 }, // 524
	{ NULL,NULL,84,2,1,270 }, // 525
	{ C_66,NULL,5,3,1,646 }, // 526
	{ NULL,NULL,84,2,1,266 }, // 527
	{ C_66,NULL,5,3,1,642 }, // 528
	{ NULL,NULL,84,2,1,267 }, // 529
	{ C_66,NULL,5,3,1,643 }, // 530
	{ NULL,NULL,84,2,1,295 }, // 531
	{ C_66,NULL,5,3,1,700 }, // 532
	{ NULL,NULL,84,2,1,271 }, // 533
	{ C_66,NULL,5,3,1,647 }, // 534
	{ NULL,NULL,84,2,1,334 }, // 535
	{ C_66,NULL,5,3,1,756 }, // 536
	{ NULL,NULL,84,2,1,335 }, // 537
	{ C_66,NULL,5,3,1,757 }, // 538
	{ NULL,NULL,84,2,1,296 }, // 539
	{ C_66,NULL,5,3,1,705 }, // 540
	{ NULL,NULL,84,2,1,311 }, // 541
	{ C_66,NULL,5,3,1,729 }, // 542
	{ NULL,NULL,84,2,1,264 }, // 543
	{ C_66,NULL,5,3,1,640 }, // 544
	{ NULL,NULL,84,2,1,265 }, // 545
	{ C_66,NULL,5,3,1,641 }, // 546
	{ NULL,NULL,84,2,1,294 }, // 547
	{ C_66,NULL,5,3,1,699 }, // 548
	{ NULL,NULL,84,2,1,351 }, // 549
	{ C_66,NULL,5,3,1,770 }, // 550
	{ NULL,NULL,84,2,1,331 }, // 551
	{ C_66,NULL,5,3,1,753 }, // 552
	{ NULL,NULL,84,2,1,338 }, // 553
	{ C_66,NULL,5,3,1,760 }, // 554
	{ NULL,NULL,84,2,1,332 }, // 555
	{ C_66,NULL,5,3,1,754 }, // 556
	{ NULL,NULL,84,2,1,333 }, // 557
	{ C_66,NULL,5,3,1,755 }, // 558
	{ NULL,NULL,84,2,1,261 }, // 559
	{ C_66,NULL,5,3,1,637 }, // 560
	{ NULL,NULL,84,2,1,268 }, // 561
	{ C_66,NULL,5,3,1,644 }, // 562
	{ NULL,NULL,84,2,1,262 }, // 563
	{ C_66,NULL,5,3,1,638 }, // 564
	{ NULL,NULL,84,2,1,318 }, // 565
	{ C_66,NULL,5,3,1,731 }, // 566
	{ NULL,NULL,84,2,1,287 }, // 567
	{ C_66,NULL,5,3,1,684 }, // 568
	{ NULL,NULL,84,2,1,285 }, // 569
	{ C_66,NULL,5,3,1,682 }, // 570
	{ NULL,NULL,84,2,1,286 }, // 571
	{ C_66,NULL,5,3,1,683 }, // 572
	{ NULL,NULL,84,2,1,292 }, // 573
	{ C_66,NULL,5,3,1,693 }, // 574
	{ NULL,NULL,84,2,1,290 }, // 575
	{ C_66,NULL,5,3,1,688 }, // 576
	{ NULL,NULL,84,2,1,288 }, // 577
	{ C_66,NULL,5,3,1,686 }, // 578
	{ NULL,NULL,84,2,1,289 }, // 579
	{ C_66,NULL,5,3,1,687 }, // 580
	{ C_66,NULL,123,2,1,275 }, // 581
	{ C_66,S_v,17,3,1,474 }, // 582
	{ C_66,NULL,123,2,1,42 }, // 583
	{ C_66,NULL,123,2,1,41 }, // 584
	{ C_66,S_v,27,3,1,676 }, // 585
	{ C_66,NULL,76,2,1,761 }, // 586
	{ C_66,NULL,124,2,1,712 }, // 587
	{ C_66,NULL,125,2,1,710 }, // 588
	{ C_66,NULL,126,2,1,711 }, // 589
	{ C_66,NULL,124,2,1,714 }, // 590
	{ C_66,NULL,125,2,1,715 }, // 591
	{ C_66,NULL,124,2,1,713 }, // 592
	{ C_66,NULL,124,2,1,718 }, // 593
	{ C_66,NULL,125,2,1,716 }, // 594
	{ C_66,NULL,126,2,1,717 }, // 595
	{ C_66,NULL,124,2,1,720 }, // 596
	{ C_66,NULL,125,2,1,721 }, // 597
	{ C_66,NULL,124,2,1,719 }, // 598
	{ C_66,S_v,27,3,1,672 }, // 599
	{ C_66,NULL,5,3,1,666 }, // 600
	{ C_66,NULL,5,3,1,726 }, // 601
	{ C_66,NULL,123,2,1,685 }, // 602
	{ C_66,S_v,5,3,1,745 }, // 603
	{ C_66,NULL,127,2,1,141 }, // 604
	{ C_66,NULL,127,2,1,144 }, // 605
	{ C_66,NULL,127,2,1,143 }, // 606
	{ NULL,NULL,128,2,1,225 }, // 607
	{ C_66,NULL,129,2,1,225 }, // 608
	{ C_F2,NULL,131,2,1,106 }, // 609
	{ C_66_F2,NULL,131,2,1,106 }, // 610
	{ NULL,NULL,111,2,1,225 }, // 611
	{ C_66,NULL,130,2,1,225 }, // 612
	{ C_F2,NULL,132,2,1,106 }, // 613
	{ C_66_F2,NULL,133,2,1,106 }, // 614
	{ NULL,S_v,28,3,1,38 }, // 615
	{ NULL,S_v,29,3,1,54 }, // 616
	{ C_F3,S_v,28,3,1,283 }, // 617
	{ C_F2,S_v,28,3,1,282 }, // 618
	{ NULL,S_v,29,3,1,40 }, // 619
	{ C_66,S_v,29,3,1,412 }, // 620
	{ C_F3,S_v,29,3,1,369 }, // 621
	{ C_F2,S_v,29,3,1,415 }, // 622
	{ C_66,NULL,103,2,1,34 }, // 623
	{ C_F3,NULL,103,2,1,36 }, // 624
	{ C_F2,S_v,6,4,1,243 }, // 625
	{ NULL,NULL,84,2,1,320 }, // 626
	{ C_66,NULL,5,3,1,735 }, // 627
	{ NULL,NULL,84,2,1,322 }, // 628
	{ C_66,NULL,5,3,1,737 }, // 629
	{ NULL,NULL,84,2,1,321 }, // 630
	{ C_66,NULL,5,3,1,736 }, // 631
	{ NULL,NULL,84,2,1,299 }, // 632
	{ C_66,NULL,5,3,1,723 }, // 633
	{ C_66,S_v,5,3,1,674 }, // 634
	{ C_66,S_v,5,3,1,673 }, // 635
	{ C_66,S_v,76,2,1,790 }, // 636
	{ C_66,S_v,76,2,1,789 }, // 637
	{ NULL,NULL,84,2,1,255 }, // 638
	{ C_66,NULL,76,2,1,630 }, // 639
	{ NULL,NULL,84,2,1,257 }, // 640
	{ C_66,NULL,76,2,1,632 }, // 641
	{ NULL,NULL,84,2,1,256 }, // 642
	{ C_66,NULL,76,2,1,631 }, // 643
	{ C_66,S_v,134,2,1,463 }, // 644
	{ C_66,S_v,135,2,1,462 }, // 645
	{ C_66,S_v,136,2,1,460 }, // 646
	{ C_66,NULL,5,3,1,722 }, // 647
	{ C_66,NULL,5,3,1,660 }, // 648
	{ C_66,NULL,122,2,1,606 }, // 649
	{ C_66,NULL,5,3,1,635 }, // 650
	{ C_66,S_v,30,3,1,577 }, // 651
	{ C_66,S_v,30,3,1,576 }, // 652
	{ C_66,S_v,31,3,1,577 }, // 653
	{ C_66,S_v,31,3,1,576 }, // 654
	{ C_66,NULL,5,3,1,703 }, // 655
	{ C_66,NULL,5,3,1,704 }, // 656
	{ C_66,NULL,5,3,1,708 }, // 657
	{ C_66,NULL,5,3,1,707 }, // 658
	{ C_66,NULL,5,3,1,697 }, // 659
	{ C_66,NULL,5,3,1,698 }, // 660
	{ C_66,NULL,5,3,1,702 }, // 661
	{ C_66,NULL,5,3,1,701 }, // 662
	{ C_66,S_v,76,2,1,654 }, // 663
	{ C_66,S_v,76,2,1,655 }, // 664
	{ C_66,S_v,136,2,1,461 }, // 665
	{ C_66,S_v,76,2,1,653 }, // 666
	{ C_66,S_v,76,2,1,656 }, // 667
	{ C_66,NULL,123,2,1,450 }, // 668
	{ C_66,NULL,33,3,1,448 }, // 669
	{ C_66,NULL,33,3,1,449 }, // 670
	{ C_66,NULL,33,3,1,446 }, // 671
	{ C_66,NULL,33,3,1,447 }, // 672
	{ C_66,S_v,34,3,1,677 }, // 673
	{ C_66,S_v,34,3,1,675 }, // 674
	{ C_66,S_v,7,4,1,650 }, // 675
	{ C_66,S_v,17,3,1,674 }, // 676
	{ C_66,S_v,17,3,1,673 }, // 677
	{ C_66,S_v,8,4,1,670 }, // 678
	{ C_66,NULL,35,3,1,678 }, // 679
	{ C_66,NULL,36,3,1,681 }, // 680
	{ C_66,NULL,38,3,1,498 }, // 681
	{ C_66,NULL,9,4,1,689 }, // 682
	{ C_66,NULL,10,4,1,573 }, // 683
	{ C_66,NULL,7,4,1,493 }, // 684
	{ C_66,NULL,12,4,1,492 }, // 685
	{ C_66,NULL,7,4,1,616 }, // 686
	{ C_66,NULL,12,4,1,657 }, // 687
	{ C_66,S_v,8,4,1,671 }, // 688
	{ C_66,NULL,39,3,1,663 }, // 689
	{ C_66,NULL,39,3,1,662 }, // 690
	{ C_66,NULL,39,3,1,669 }, // 691
	{ C_66,NULL,39,3,1,668 }, // 692
	{ C_F2,S_v,40,3,1,365 }, // 693
	{ NULL,NULL,16,3,1,269 }, // 694
	{ C_66,NULL,7,4,1,645 }, // 695
	{ C_66,NULL,17,3,1,774 }, // 696
	{ C_66,S_v,8,4,1,571 }, // 697
	{ C_66,NULL,17,3,1,773 }, // 698
	{ C_66,S_v,43,3,1,496 }, // 699
	{ C_66,NULL,41,3,1,776 }, // 700
	{ C_66,NULL,42,3,1,775 }, // 701
	{ C_66,NULL,7,4,1,457 }, // 702
	{ C_66,NULL,7,4,1,456 }, // 703
	{ C_66,S_v,44,3,1,477 }, // 704
	{ C_66,NULL,7,4,1,652 }, // 705
	{ C_66,S_v,8,4,1,572 }, // 706
	{ C_66,S_v,43,3,1,497 }, // 707
	{ C_66,S_v,13,4,1,459 }, // 708
	{ C_66,S_v,13,4,1,458 }, // 709
	{ C_66,S_v,13,4,1,651 }, // 710
	{ C_66,NULL,39,3,1,451 }, // 711
};
extern InstChangeData InstChange[] =
{
	{ NULL,NULL,24,2,2,233,Ext_B }, // 0
	{ NULL,NULL,25,2,4,235,Ext_W | Ext_D | Ext_Q }, // 1
	{ NULL,NULL,26,2,2,97,Ext_B }, // 2
	{ NULL,NULL,27,2,3,99,Ext_W | Ext_D }, // 3
	{ NULL,NULL,0,0,2,811,Ext_B }, // 4
	{ NULL,NULL,44,2,2,132,Ext_B }, // 5
	{ NULL,NULL,45,2,3,134,Ext_W | Ext_D }, // 6
	{ NULL,NULL,46,2,2,250,Ext_B }, // 7
	{ NULL,NULL,47,2,3,252,Ext_W | Ext_D }, // 8
	{ NULL,S_d64,28,1,3,348,Ext_D | Ext_Q }, // 9
	{ NULL,S_d64,28,1,3,308,Ext_D | Ext_Q }, // 10
	{ NULL,NULL,51,2,2,424,Ext_B }, // 11
	{ NULL,NULL,52,2,4,426,Ext_W | Ext_D | Ext_Q }, // 12
	{ NULL,NULL,53,2,2,206,Ext_B }, // 13
	{ NULL,NULL,54,2,4,208,Ext_W | Ext_D | Ext_Q }, // 14
	{ NULL,NULL,55,2,2,371,Ext_B }, // 15
	{ NULL,NULL,56,2,4,373,Ext_W | Ext_D | Ext_Q }, // 16
	{ NULL,NULL,0,0,3,145,Ext_D | Ext_Q }, // 17
	{ NULL,NULL,100,2,2,226,Ext_Q }, // 18
	{ C_66,NULL,101,2,2,592,Ext_Q }, // 19
	{ NULL,NULL,104,2,2,226,Ext_Q }, // 20
	{ C_66,NULL,106,2,2,592,Ext_Q }, // 21
	{ C_66,S_v,5,3,2,750,Ext_Q }, // 22
	{ C_66,S_v,5,3,2,741,Ext_Q }, // 23
	{ C_66,S_v,5,3,2,559,Ext_Q }, // 24
	{ C_66,S_v,5,3,2,563,Ext_Q }, // 25
	{ C_66,S_v,5,3,2,561,Ext_D }, // 26
	{ C_66,S_v,5,3,2,565,Ext_D }, // 27
	{ C_66,S_v,5,3,2,511,Ext_D }, // 28
	{ C_66,S_v,5,3,2,529,Ext_D }, // 29
	{ C_66,S_v,5,3,2,513,Ext_D }, // 30
	{ C_66,S_v,5,3,2,531,Ext_D }, // 31
	{ C_66,S_v,5,3,2,515,Ext_D }, // 32
	{ C_66,S_v,5,3,2,533,Ext_D }, // 33
	{ C_66,S_v,30,3,2,695,Ext_Q }, // 34
	{ C_66,S_v,32,3,2,695,Ext_Q }, // 35
	{ C_66,S_v,5,3,2,499,Ext_D }, // 36
	{ C_66,S_v,5,3,2,501,Ext_D }, // 37
	{ C_66,S_v,5,3,2,517,Ext_D }, // 38
	{ C_66,S_v,5,3,2,519,Ext_D }, // 39
	{ C_66,S_v,5,3,2,535,Ext_D }, // 40
	{ C_66,S_v,5,3,2,537,Ext_D }, // 41
	{ C_66,S_v,5,3,2,547,Ext_D }, // 42
	{ C_66,S_v,5,3,2,549,Ext_D }, // 43
	{ C_66,S_v,5,3,2,503,Ext_D }, // 44
	{ C_66,S_v,5,3,2,505,Ext_D }, // 45
	{ C_66,S_v,5,3,2,521,Ext_D }, // 46
	{ C_66,S_v,5,3,2,523,Ext_D }, // 47
	{ C_66,S_v,5,3,2,539,Ext_D }, // 48
	{ C_66,S_v,5,3,2,541,Ext_D }, // 49
	{ C_66,S_v,5,3,2,551,Ext_D }, // 50
	{ C_66,S_v,5,3,2,553,Ext_D }, // 51
	{ C_66,S_v,5,3,2,507,Ext_D }, // 52
	{ C_66,S_v,5,3,2,509,Ext_D }, // 53
	{ C_66,S_v,5,3,2,525,Ext_D }, // 54
	{ C_66,S_v,5,3,2,527,Ext_D }, // 55
	{ C_66,S_v,5,3,2,543,Ext_D }, // 56
	{ C_66,S_v,5,3,2,545,Ext_D }, // 57
	{ C_66,S_v,5,3,2,555,Ext_D }, // 58
	{ C_66,S_v,5,3,2,557,Ext_D }, // 59
	{ C_66,NULL,37,3,2,679,Ext_Q }, // 60
	{ C_66,NULL,11,4,2,690,Ext_Q }, // 61
};

