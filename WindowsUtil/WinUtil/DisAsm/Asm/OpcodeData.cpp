#include "OpcodeData.h"


extern RegOrOperandGroup Operands[] = {
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
	/*81*/{ REG_RAX,CHANGE_REG }, // rAX
	/*82*/{ SPC_RAX_EAX_R8_R8D,NULL }, // RAX/EAX/R8/R8D
	/*83*/{ SPC_rAX_r8,NULL }, // rAX/r8
	/*84*/{ SPC_RBP_EBP_R13_R13D,NULL }, // RBP/EBP/R13/R13D
	/*85*/{ SPC_rBP_r13,NULL }, // rBP/r13
	/*86*/{ SPC_RBX_EBX_R11_R11D,NULL }, // RBX/EBX/R11/R11D
	/*87*/{ SPC_rBX_r11,NULL }, // rBX/r11
	/*88*/{ SPC_RCX_ECX_R9_R9D,NULL }, // RCX/ECX/R9/R9D
	/*89*/{ SPC_rCX_r9,NULL }, // rCX/r9
	/*90*/{ H_R,L_d }, // Rd
	/*91*/{ SPC_Rd_Mb,NULL }, // Rd/Mb
	/*92*/{ SPC_Rd_Mw,NULL }, // Rd/Mw
	/*93*/{ SPC_RDI_EDI_R15_R15D,NULL }, // RDI/EDI/R15/R15D
	/*94*/{ SPC_rDI_r15,NULL }, // rDI/r15
	/*95*/{ REG_RDX,CHANGE_REG }, // rDX
	/*96*/{ SPC_RDX_EDX_R10_R10D,NULL }, // RDX/EDX/R10/R10D
	/*97*/{ SPC_rDX_r10,NULL }, // rDX/r10
	/*98*/{ SPC_RSI_ESI_R14_R14D,NULL }, // RSI/ESI/R14/R14D
	/*99*/{ SPC_rSI_r14,NULL }, // rSI/r14
	/*100*/{ SPC_RSP_ESP_R12_R12D,NULL }, // RSP/ESP/R12/R12D
	/*101*/{ SPC_rSP_r12,NULL }, // rSP/r12
	/*102*/{ H_R,L_v }, // Rv
	/*103*/{ SPC_Rv_Mw,NULL }, // Rv/Mw
	/*104*/{ H_R,L_y }, // Ry
	/*105*/{ SPC_Ry_Mb,NULL }, // Ry/Mb
	/*106*/{ SPC_Ry_Mw,NULL }, // Ry/Mw
	/*107*/{ SEG_SS,NULL }, // SS
	/*108*/{ H_S,L_w }, // Sw
	/*109*/{ H_U,L_dq }, // Udq
	/*110*/{ SPC_Udq_Md,NULL }, // Udq/Md
	/*111*/{ H_U,L_pd }, // Upd
	/*112*/{ H_U,L_ps }, // Ups
	/*113*/{ H_U,L_q }, // Uq
	/*114*/{ H_U,L_x }, // Ux
	/*115*/{ SPC_Ux_Md,NULL }, // Ux/Md
	/*116*/{ SPC_Ux_Mq,NULL }, // Ux/Mq
	/*117*/{ SPC_Ux_Mw,NULL }, // Ux/Mw
	/*118*/{ H_V,L_dq }, // Vdq
	/*119*/{ H_V,L_pd }, // Vpd
	/*120*/{ H_V,L_ps }, // Vps
	/*121*/{ H_V,L_q }, // Vq
	/*122*/{ H_V,L_qq }, // Vqq
	/*123*/{ H_V,L_sd }, // Vsd
	/*124*/{ H_V,L_ss }, // Vss
	/*125*/{ H_V,L_x }, // Vx
	/*126*/{ H_V,L_y }, // Vy
	/*127*/{ H_W,L_d }, // Wd
	/*128*/{ H_W,L_dq }, // Wdq
	/*129*/{ H_W,L_pd }, // Wpd
	/*130*/{ H_W,L_ps }, // Wps
	/*131*/{ H_W,L_q }, // Wq
	/*132*/{ H_W,L_qq }, // Wqq
	/*133*/{ H_W,L_sd }, // Wsd
	/*134*/{ H_W,L_ss }, // Wss
	/*135*/{ H_W,L_x }, // Wx
	/*136*/{ H_X,L_b }, // Xb
	/*137*/{ H_X,L_v }, // Xv
	/*138*/{ H_X,L_z }, // Xz
	/*139*/{ H_Y,L_b }, // Yb
	/*140*/{ H_Y,L_v }, // Yv
	/*141*/{ H_Y,L_z }, // Yz
};
extern LPCSTR InstructionNames[] = {
	/*  0*/ "(esc)", 	// Len:1
	/*  1*/ "(grp/1)", 	// Len:1
	/*  2*/ "(grp/10)", 	// Len:1
	/*  3*/ "(grp/11)", 	// Len:1
	/*  4*/ "(grp/12)", 	// Len:1
	/*  5*/ "(grp/13)", 	// Len:1
	/*  6*/ "(grp/14)", 	// Len:1
	/*  7*/ "(grp/15)", 	// Len:1
	/*  8*/ "(grp/16)", 	// Len:1
	/*  9*/ "(grp/17)", 	// Len:1
	/* 10*/ "(grp/1a)", 	// Len:1
	/* 11*/ "(grp/2)", 	// Len:1
	/* 12*/ "(grp/3)", 	// Len:1
	/* 13*/ "(grp/4)", 	// Len:1
	/* 14*/ "(grp/5)", 	// Len:1
	/* 15*/ "(grp/6)", 	// Len:1
	/* 16*/ "(grp/7)", 	// Len:1
	/* 17*/ "(grp/8)", 	// Len:1
	/* 18*/ "(grp/9)", 	// Len:1
	/* 19*/ "(prefix/addresssize)", 	// Len:1
	/* 20*/ "(prefix/lock)", 	// Len:1
	/* 21*/ "(prefix/operandsize)", 	// Len:1
	/* 22*/ "(prefix/repnexacquire)", 	// Len:1
	/* 23*/ "(prefix/repxrelease/repexrelease)", 	// Len:1
	/* 24*/ "(prefix/rex)", 	// Len:1
	/* 25*/ "(prefix/rex.b)", 	// Len:1
	/* 26*/ "(prefix/rex.r)", 	// Len:1
	/* 27*/ "(prefix/rex.rb)", 	// Len:1
	/* 28*/ "(prefix/rex.rx)", 	// Len:1
	/* 29*/ "(prefix/rex.rxb)", 	// Len:1
	/* 30*/ "(prefix/rex.w)", 	// Len:1
	/* 31*/ "(prefix/rex.wb)", 	// Len:1
	/* 32*/ "(prefix/rex.wr)", 	// Len:1
	/* 33*/ "(prefix/rex.wrb)", 	// Len:1
	/* 34*/ "(prefix/rex.wrx)", 	// Len:1
	/* 35*/ "(prefix/rex.wrxb)", 	// Len:1
	/* 36*/ "(prefix/rex.wx)", 	// Len:1
	/* 37*/ "(prefix/rex.wxb)", 	// Len:1
	/* 38*/ "(prefix/rex.x)", 	// Len:1
	/* 39*/ "(prefix/rex.xb)", 	// Len:1
	/* 40*/ "(prefix/seg=cs)", 	// Len:1
	/* 41*/ "(prefix/seg=ds)", 	// Len:1
	/* 42*/ "(prefix/seg=es)", 	// Len:1
	/* 43*/ "(prefix/seg=fs)", 	// Len:1
	/* 44*/ "(prefix/seg=gs)", 	// Len:1
	/* 45*/ "(prefix/seg=ss)", 	// Len:1
	/* 46*/ "(prefix/vex+1byte)", 	// Len:1
	/* 47*/ "(prefix/vex+2byte)", 	// Len:1
	/* 48*/ "(table/0f)", 	// Len:1
	/* 49*/ "(table/0f38)", 	// Len:1
	/* 50*/ "(table/0f3a)", 	// Len:1
	/* 51*/ "aaa", 	// Len:1
	/* 52*/ "aad", 	// Len:1
	/* 53*/ "aam", 	// Len:1
	/* 54*/ "aas", 	// Len:1
	/* 55*/ "adc", 	// Len:1
	/* 56*/ "adcx", 	// Len:1
	/* 57*/ "add", 	// Len:1
	/* 58*/ "adox", 	// Len:1
	/* 59*/ "and", 	// Len:1
	/* 60*/ "andn", 	// Len:1
	/* 61*/ "arpl", 	// Len:1
	/* 62*/ "bextr", 	// Len:1
	/* 63*/ "blendvpd", 	// Len:1
	/* 64*/ "blendvps", 	// Len:1
	/* 65*/ "blsi", 	// Len:1
	/* 66*/ "blsmsk", 	// Len:1
	/* 67*/ "blsr", 	// Len:1
	/* 68*/ "bound", 	// Len:1
	/* 69*/ "bsf", 	// Len:1
	/* 70*/ "bsr", 	// Len:1
	/* 71*/ "bswap", 	// Len:1
	/* 72*/ "bt", 	// Len:1
	/* 73*/ "btc", 	// Len:1
	/* 74*/ "btr", 	// Len:1
	/* 75*/ "bts", 	// Len:1
	/* 76*/ "bzhi", 	// Len:1
	/* 77*/ "call", 	// Len:1
	/* 78*/ "cbw", 	// Len:3 
	/* 79*/ "cwde",
	/* 80*/ "cdqe",
	/* 81*/ "clac", 	// Len:1
	/* 82*/ "clc", 	// Len:1
	/* 83*/ "cld", 	// Len:1
	/* 84*/ "clflush", 	// Len:1
	/* 85*/ "cli", 	// Len:1
	/* 86*/ "clts", 	// Len:1
	/* 87*/ "cmc", 	// Len:1
	/* 88*/ "cmova", 	// Len:2 
	/* 89*/ "cmovnbe",
	/* 90*/ "cmovae", 	// Len:3 
	/* 91*/ "cmovnb",
	/* 92*/ "cmovnc",
	/* 93*/ "cmovb", 	// Len:3 
	/* 94*/ "cmovc",
	/* 95*/ "cmovnae",
	/* 96*/ "cmovbe", 	// Len:2 
	/* 97*/ "cmovna",
	/* 98*/ "cmove", 	// Len:2 
	/* 99*/ "cmovz",
	/*100*/ "cmovl", 	// Len:2 
	/*101*/ "cmovnge",
	/*102*/ "cmovle", 	// Len:2 
	/*103*/ "cmovng",
	/*104*/ "cmovne", 	// Len:2 
	/*105*/ "cmovnz",
	/*106*/ "cmovnl", 	// Len:2 
	/*107*/ "cmovge",
	/*108*/ "cmovnle", 	// Len:2 
	/*109*/ "cmovg",
	/*110*/ "cmovno", 	// Len:1
	/*111*/ "cmovnp", 	// Len:2 
	/*112*/ "cmovpo",
	/*113*/ "cmovns", 	// Len:1
	/*114*/ "cmovo", 	// Len:1
	/*115*/ "cmovp", 	// Len:2 
	/*116*/ "cmovpe",
	/*117*/ "cmovs", 	// Len:1
	/*118*/ "cmp", 	// Len:1
	/*119*/ "cmps", 	// Len:2 Type:Size
	/*120*/ "cmpsb",
	/*121*/ "cmps", 	// Len:3 Type:Size
	/*122*/ "cmpsw",
	/*123*/ "cmpsd",
	/*124*/ "cmpxch8b", 	// Len:1
	/*125*/ "cmpxchg", 	// Len:1
	/*126*/ "cmpxchg16b", 	// Len:1
	/*127*/ "cpuid", 	// Len:1
	/*128*/ "crc32", 	// Len:1
	/*129*/ "cvtpd2pi", 	// Len:1
	/*130*/ "cvtpi2pd", 	// Len:1
	/*131*/ "cvtpi2ps", 	// Len:1
	/*132*/ "cvtps2pi", 	// Len:1
	/*133*/ "cvttpd2pi", 	// Len:1
	/*134*/ "cvttps2pi", 	// Len:1
	/*135*/ "cwd", 	// Len:3 
	/*136*/ "cdq",
	/*137*/ "cqo",
	/*138*/ "daa", 	// Len:1
	/*139*/ "das", 	// Len:1
	/*140*/ "dec", 	// Len:1
	/*141*/ "div", 	// Len:1
	/*142*/ "emms", 	// Len:1
	/*143*/ "enter", 	// Len:1
	/*144*/ "fwait", 	// Len:2 
	/*145*/ "wait",
	/*146*/ "fxrstor", 	// Len:1
	/*147*/ "fxsave", 	// Len:1
	/*148*/ "getsec", 	// Len:1
	/*149*/ "hlt", 	// Len:1
	/*150*/ "idiv", 	// Len:1
	/*151*/ "imul", 	// Len:1
	/*152*/ "in", 	// Len:1
	/*153*/ "inc", 	// Len:1
	/*154*/ "ins", 	// Len:2 Type:Size
	/*155*/ "insb",
	/*156*/ "ins", 	// Len:3 Type:Size
	/*157*/ "insw",
	/*158*/ "insd",
	/*159*/ "int", 	// Len:1
	/*160*/ "int3", 	// Len:1
	/*161*/ "into", 	// Len:1
	/*162*/ "invd", 	// Len:1
	/*163*/ "invept", 	// Len:1
	/*164*/ "invlpg", 	// Len:1
	/*165*/ "invpcid", 	// Len:1
	/*166*/ "invvpid", 	// Len:1
	/*167*/ "iret", 	// Len:3 Type:Size
	/*168*/ "iretd",
	/*169*/ "iretq",
	/*170*/ "ja", 	// Len:2 
	/*171*/ "jnbe",
	/*172*/ "jae", 	// Len:3 
	/*173*/ "jnb",
	/*174*/ "jnc",
	/*175*/ "jb", 	// Len:3 
	/*176*/ "jnae",
	/*177*/ "jc",
	/*178*/ "jb", 	// Len:2 
	/*179*/ "jcnae",
	/*180*/ "jbe", 	// Len:2 
	/*181*/ "jna",
	/*182*/ "je", 	// Len:2 
	/*183*/ "jz",
	/*184*/ "jl", 	// Len:2 
	/*185*/ "jnge",
	/*186*/ "jle", 	// Len:2 
	/*187*/ "jng",
	/*188*/ "jmp", 	// Len:1
	/*189*/ "jmpe", 	// Len:1
	/*190*/ "jnb", 	// Len:3 
	/*191*/ "jae",
	/*192*/ "jnc",
	/*193*/ "jnbe", 	// Len:2 
	/*194*/ "ja",
	/*195*/ "jne", 	// Len:2 
	/*196*/ "jnz",
	/*197*/ "jnl", 	// Len:2 
	/*198*/ "jge",
	/*199*/ "jnle", 	// Len:2 
	/*200*/ "jg",
	/*201*/ "jno", 	// Len:1
	/*202*/ "jnp", 	// Len:2 
	/*203*/ "jpo",
	/*204*/ "jns", 	// Len:1
	/*205*/ "jnz", 	// Len:2 
	/*206*/ "jne",
	/*207*/ "jo", 	// Len:1
	/*208*/ "jp", 	// Len:2 
	/*209*/ "jpe",
	/*210*/ "jrcxz", 	// Len:1
	/*211*/ "js", 	// Len:1
	/*212*/ "jz", 	// Len:2 
	/*213*/ "je",
	/*214*/ "lahf", 	// Len:1
	/*215*/ "lar", 	// Len:1
	/*216*/ "ldmxcsr", 	// Len:1
	/*217*/ "lds", 	// Len:1
	/*218*/ "lea", 	// Len:1
	/*219*/ "leave", 	// Len:1
	/*220*/ "les", 	// Len:1
	/*221*/ "lfence", 	// Len:1
	/*222*/ "lfs", 	// Len:1
	/*223*/ "lgdt", 	// Len:1
	/*224*/ "lgs", 	// Len:1
	/*225*/ "lidt", 	// Len:1
	/*226*/ "lldt", 	// Len:1
	/*227*/ "lmsw", 	// Len:1
	/*228*/ "lods", 	// Len:2 Type:Size
	/*229*/ "lodsb",
	/*230*/ "lods", 	// Len:4 Type:Size
	/*231*/ "lodsw",
	/*232*/ "lodsd",
	/*233*/ "lodsq",
	/*234*/ "loop", 	// Len:1
	/*235*/ "loope", 	// Len:2 
	/*236*/ "loopz",
	/*237*/ "loopne", 	// Len:2 
	/*238*/ "loopnz",
	/*239*/ "lsl", 	// Len:1
	/*240*/ "lss", 	// Len:1
	/*241*/ "ltr", 	// Len:1
	/*242*/ "lzcnt", 	// Len:1
	/*243*/ "maskmovq", 	// Len:1
	/*244*/ "mfence", 	// Len:1
	/*245*/ "monitor", 	// Len:1
	/*246*/ "mov", 	// Len:1
	/*247*/ "movbe", 	// Len:1
	/*248*/ "movd", 	// Len:2 Type:Size
	/*249*/ "movdq",
	/*250*/ "movdq2q", 	// Len:1
	/*251*/ "movnti", 	// Len:1
	/*252*/ "movntq", 	// Len:1
	/*253*/ "movq", 	// Len:1
	/*254*/ "movq2dq", 	// Len:1
	/*255*/ "movs", 	// Len:2 Type:Size
	/*256*/ "movsb",
	/*257*/ "movs", 	// Len:4 Type:Size
	/*258*/ "movsw",
	/*259*/ "movsd",
	/*260*/ "movsq",
	/*261*/ "movsx", 	// Len:1
	/*262*/ "movsxd", 	// Len:1
	/*263*/ "movzx", 	// Len:1
	/*264*/ "mul", 	// Len:1
	/*265*/ "mulx", 	// Len:1
	/*266*/ "mwait", 	// Len:1
	/*267*/ "neg", 	// Len:1
	/*268*/ "nop", 	// Len:1
	/*269*/ "not", 	// Len:1
	/*270*/ "or", 	// Len:1
	/*271*/ "out", 	// Len:1
	/*272*/ "outs", 	// Len:2 Type:Size
	/*273*/ "outsb",
	/*274*/ "outs", 	// Len:3 Type:Size
	/*275*/ "outsw",
	/*276*/ "outsd",
	/*277*/ "pabsb", 	// Len:1
	/*278*/ "pabsd", 	// Len:1
	/*279*/ "pabsw", 	// Len:1
	/*280*/ "packssdw", 	// Len:1
	/*281*/ "packsswb", 	// Len:1
	/*282*/ "packuswb", 	// Len:1
	/*283*/ "paddb", 	// Len:1
	/*284*/ "paddd", 	// Len:1
	/*285*/ "paddq", 	// Len:1
	/*286*/ "paddsb", 	// Len:1
	/*287*/ "paddsw", 	// Len:1
	/*288*/ "paddusb", 	// Len:1
	/*289*/ "paddusw", 	// Len:1
	/*290*/ "paddw", 	// Len:1
	/*291*/ "palignr", 	// Len:1
	/*292*/ "pand", 	// Len:1
	/*293*/ "pandn", 	// Len:1
	/*294*/ "pause", 	// Len:1
	/*295*/ "pavgb", 	// Len:1
	/*296*/ "pavgw", 	// Len:1
	/*297*/ "pblendvb", 	// Len:1
	/*298*/ "pcmpeqb", 	// Len:1
	/*299*/ "pcmpeqd", 	// Len:1
	/*300*/ "pcmpeqw", 	// Len:1
	/*301*/ "pcmpgtb", 	// Len:1
	/*302*/ "pcmpgtd", 	// Len:1
	/*303*/ "pcmpgtw", 	// Len:1
	/*304*/ "pdep", 	// Len:1
	/*305*/ "pext", 	// Len:1
	/*306*/ "pextrw", 	// Len:1
	/*307*/ "phaddd", 	// Len:1
	/*308*/ "phaddsw", 	// Len:1
	/*309*/ "phaddw", 	// Len:1
	/*310*/ "phsubd", 	// Len:1
	/*311*/ "phsubsw", 	// Len:1
	/*312*/ "phsubw", 	// Len:1
	/*313*/ "pinsrw", 	// Len:1
	/*314*/ "pmaddubsw", 	// Len:1
	/*315*/ "pmaddwd", 	// Len:1
	/*316*/ "pmaxsw", 	// Len:1
	/*317*/ "pmaxub", 	// Len:1
	/*318*/ "pminsw", 	// Len:1
	/*319*/ "pminub", 	// Len:1
	/*320*/ "pmovmskb", 	// Len:1
	/*321*/ "pmulhrsw", 	// Len:1
	/*322*/ "pmulhuw", 	// Len:1
	/*323*/ "pmulhw", 	// Len:1
	/*324*/ "pmullw", 	// Len:1
	/*325*/ "pmuludq", 	// Len:1
	/*326*/ "pop", 	// Len:1
	/*327*/ "popa", 	// Len:2 
	/*328*/ "popad",
	/*329*/ "popcnt", 	// Len:1
	/*330*/ "popf", 	// Len:3 Type:Size
	/*331*/ "popfd",
	/*332*/ "popfq",
	/*333*/ "por", 	// Len:1
	/*334*/ "prefetchnta", 	// Len:1
	/*335*/ "prefetcht0", 	// Len:1
	/*336*/ "prefetcht1", 	// Len:1
	/*337*/ "prefetcht2", 	// Len:1
	/*338*/ "prefetchw", 	// Len:1
	/*339*/ "psadbw", 	// Len:1
	/*340*/ "pshufb", 	// Len:1
	/*341*/ "pshufw", 	// Len:1
	/*342*/ "psignb", 	// Len:1
	/*343*/ "psignd", 	// Len:1
	/*344*/ "psignw", 	// Len:1
	/*345*/ "pslld", 	// Len:1
	/*346*/ "psllq", 	// Len:1
	/*347*/ "psllw", 	// Len:1
	/*348*/ "psrad", 	// Len:1
	/*349*/ "psraw", 	// Len:1
	/*350*/ "psrld", 	// Len:1
	/*351*/ "psrlq", 	// Len:1
	/*352*/ "psrlw", 	// Len:1
	/*353*/ "psubb", 	// Len:1
	/*354*/ "psubd", 	// Len:1
	/*355*/ "psubq", 	// Len:1
	/*356*/ "psubsb", 	// Len:1
	/*357*/ "psubsw", 	// Len:1
	/*358*/ "psubusb", 	// Len:1
	/*359*/ "psubusw", 	// Len:1
	/*360*/ "psubw", 	// Len:1
	/*361*/ "punpckhbw", 	// Len:1
	/*362*/ "punpckhdq", 	// Len:1
	/*363*/ "punpckhwd", 	// Len:1
	/*364*/ "punpcklbw", 	// Len:1
	/*365*/ "punpckldq", 	// Len:1
	/*366*/ "punpcklwd", 	// Len:1
	/*367*/ "push", 	// Len:1
	/*368*/ "pusha", 	// Len:2 
	/*369*/ "pushad",
	/*370*/ "pushf", 	// Len:3 Type:Size
	/*371*/ "pushfd",
	/*372*/ "pushfq",
	/*373*/ "pxor", 	// Len:1
	/*374*/ "rcl", 	// Len:1
	/*375*/ "rcr", 	// Len:1
	/*376*/ "rdfsbase", 	// Len:1
	/*377*/ "rdgsbase", 	// Len:1
	/*378*/ "rdmsr", 	// Len:1
	/*379*/ "rdpmc", 	// Len:1
	/*380*/ "rdrand", 	// Len:1
	/*381*/ "rdseed", 	// Len:1
	/*382*/ "rdtsc", 	// Len:1
	/*383*/ "rdtscp", 	// Len:1
	/*384*/ "ret", 	// Len:1
	/*385*/ "rol", 	// Len:1
	/*386*/ "ror", 	// Len:1
	/*387*/ "rorx", 	// Len:1
	/*388*/ "rsm", 	// Len:1
	/*389*/ "sahf", 	// Len:1
	/*390*/ "sar", 	// Len:1
	/*391*/ "sarx", 	// Len:1
	/*392*/ "sbb", 	// Len:1
	/*393*/ "scas", 	// Len:2 Type:Size
	/*394*/ "scasb",
	/*395*/ "scas", 	// Len:4 Type:Size
	/*396*/ "scasw",
	/*397*/ "scasd",
	/*398*/ "scasq",
	/*399*/ "seta", 	// Len:2 
	/*400*/ "setnbe",
	/*401*/ "setae", 	// Len:3 
	/*402*/ "setnb",
	/*403*/ "setnc",
	/*404*/ "setb", 	// Len:3 
	/*405*/ "setc",
	/*406*/ "setnae",
	/*407*/ "setbe", 	// Len:2 
	/*408*/ "setna",
	/*409*/ "sete", 	// Len:2 
	/*410*/ "setz",
	/*411*/ "setl", 	// Len:2 
	/*412*/ "setnge",
	/*413*/ "setle", 	// Len:2 
	/*414*/ "setng",
	/*415*/ "setne", 	// Len:2 
	/*416*/ "setnz",
	/*417*/ "setnl", 	// Len:2 
	/*418*/ "setge",
	/*419*/ "setnle", 	// Len:2 
	/*420*/ "setg",
	/*421*/ "setno", 	// Len:1
	/*422*/ "setnp", 	// Len:2 
	/*423*/ "setpo",
	/*424*/ "setns", 	// Len:1
	/*425*/ "seto", 	// Len:1
	/*426*/ "setp", 	// Len:2 
	/*427*/ "setpe",
	/*428*/ "sets", 	// Len:1
	/*429*/ "sfence", 	// Len:1
	/*430*/ "sgdt", 	// Len:1
	/*431*/ "shl", 	// Len:2 
	/*432*/ "sal",
	/*433*/ "shld", 	// Len:1
	/*434*/ "shlx", 	// Len:1
	/*435*/ "shr", 	// Len:1
	/*436*/ "shrd", 	// Len:1
	/*437*/ "shrx", 	// Len:1
	/*438*/ "sidt", 	// Len:1
	/*439*/ "sldt", 	// Len:1
	/*440*/ "smsw", 	// Len:1
	/*441*/ "stac", 	// Len:1
	/*442*/ "stc", 	// Len:1
	/*443*/ "std", 	// Len:1
	/*444*/ "sti", 	// Len:1
	/*445*/ "stmxcsr", 	// Len:1
	/*446*/ "stos", 	// Len:2 Type:Size
	/*447*/ "stosb",
	/*448*/ "stos", 	// Len:4 Type:Size
	/*449*/ "stosw",
	/*450*/ "stosd",
	/*451*/ "stosq",
	/*452*/ "str", 	// Len:1
	/*453*/ "sub", 	// Len:1
	/*454*/ "swapgs", 	// Len:1
	/*455*/ "syscall", 	// Len:1
	/*456*/ "sysenter", 	// Len:1
	/*457*/ "sysexit", 	// Len:1
	/*458*/ "sysret", 	// Len:1
	/*459*/ "test", 	// Len:1
	/*460*/ "tzcnt", 	// Len:1
	/*461*/ "ud2", 	// Len:1
	/*462*/ "vaddpd", 	// Len:1
	/*463*/ "vaddps", 	// Len:1
	/*464*/ "vaddsd", 	// Len:1
	/*465*/ "vaddss", 	// Len:1
	/*466*/ "vaddsubpd", 	// Len:1
	/*467*/ "vaddsubps", 	// Len:1
	/*468*/ "vaesdec", 	// Len:1
	/*469*/ "vaesdeclast", 	// Len:1
	/*470*/ "vaesenc", 	// Len:1
	/*471*/ "vaesenclast", 	// Len:1
	/*472*/ "vaesimc", 	// Len:1
	/*473*/ "vaeskeygen", 	// Len:1
	/*474*/ "vandnpd", 	// Len:1
	/*475*/ "vandnps", 	// Len:1
	/*476*/ "vandpd", 	// Len:1
	/*477*/ "vandps", 	// Len:1
	/*478*/ "vblendpd", 	// Len:1
	/*479*/ "vblendps", 	// Len:1
	/*480*/ "vblendvpd", 	// Len:1
	/*481*/ "vblendvps", 	// Len:1
	/*482*/ "vbroadcastf128", 	// Len:1
	/*483*/ "vbroadcasti128", 	// Len:1
	/*484*/ "vbroadcastsd", 	// Len:1
	/*485*/ "vbroadcastss", 	// Len:1
	/*486*/ "vcmppd", 	// Len:1
	/*487*/ "vcmpps", 	// Len:1
	/*488*/ "vcmpsd", 	// Len:1
	/*489*/ "vcmpss", 	// Len:1
	/*490*/ "vcomisd", 	// Len:1
	/*491*/ "vcomiss", 	// Len:1
	/*492*/ "vcvtdq2pd", 	// Len:1
	/*493*/ "vcvtdq2ps", 	// Len:1
	/*494*/ "vcvtpd2dq", 	// Len:1
	/*495*/ "vcvtpd2ps", 	// Len:1
	/*496*/ "vcvtph2ps", 	// Len:1
	/*497*/ "vcvtps2dq", 	// Len:1
	/*498*/ "vcvtps2pd", 	// Len:1
	/*499*/ "vcvtps2ph", 	// Len:1
	/*500*/ "vcvtsd2si", 	// Len:1
	/*501*/ "vcvtsd2ss", 	// Len:1
	/*502*/ "vcvtsi2sd", 	// Len:1
	/*503*/ "vcvtsi2ss", 	// Len:1
	/*504*/ "vcvtss2sd", 	// Len:1
	/*505*/ "vcvtss2si", 	// Len:1
	/*506*/ "vcvttpd2dq", 	// Len:1
	/*507*/ "vcvttps2dq", 	// Len:1
	/*508*/ "vcvttsd2si", 	// Len:1
	/*509*/ "vcvttss2si", 	// Len:1
	/*510*/ "vdivpd", 	// Len:1
	/*511*/ "vdivps", 	// Len:1
	/*512*/ "vdivsd", 	// Len:1
	/*513*/ "vdivss", 	// Len:1
	/*514*/ "vdppd", 	// Len:1
	/*515*/ "vdpps", 	// Len:1
	/*516*/ "verr", 	// Len:1
	/*517*/ "verw", 	// Len:1
	/*518*/ "vextractf128", 	// Len:1
	/*519*/ "vextracti128", 	// Len:1
	/*520*/ "vextractps", 	// Len:1
	/*521*/ "vfmadd132ps", 	// Len:2 Type:Size
	/*522*/ "vfmadd132psd",
	/*523*/ "vfmadd132ss", 	// Len:2 Type:Size
	/*524*/ "vfmadd132ssd",
	/*525*/ "vfmadd213ps", 	// Len:2 Type:Size
	/*526*/ "vfmadd213psd",
	/*527*/ "vfmadd213ss", 	// Len:2 Type:Size
	/*528*/ "vfmadd213ssd",
	/*529*/ "vfmadd231ps", 	// Len:2 Type:Size
	/*530*/ "vfmadd231psd",
	/*531*/ "vfmadd231ss", 	// Len:2 Type:Size
	/*532*/ "vfmadd231ssd",
	/*533*/ "vfmaddsub132ps", 	// Len:2 Type:Size
	/*534*/ "vfmaddsub132psd",
	/*535*/ "vfmaddsub213ps", 	// Len:2 Type:Size
	/*536*/ "vfmaddsub213psd",
	/*537*/ "vfmaddsub231ps", 	// Len:2 Type:Size
	/*538*/ "vfmaddsub231psd",
	/*539*/ "vfmsub132ps", 	// Len:2 Type:Size
	/*540*/ "vfmsub132psd",
	/*541*/ "vfmsub132ss", 	// Len:2 Type:Size
	/*542*/ "vfmsub132ssd",
	/*543*/ "vfmsub213ps", 	// Len:2 Type:Size
	/*544*/ "vfmsub213psd",
	/*545*/ "vfmsub213ss", 	// Len:2 Type:Size
	/*546*/ "vfmsub213ssd",
	/*547*/ "vfmsub231ps", 	// Len:2 Type:Size
	/*548*/ "vfmsub231psd",
	/*549*/ "vfmsub231ss", 	// Len:2 Type:Size
	/*550*/ "vfmsub231ssd",
	/*551*/ "vfmsubadd132ps", 	// Len:2 Type:Size
	/*552*/ "vfmsubadd132psd",
	/*553*/ "vfmsubadd213ps", 	// Len:2 Type:Size
	/*554*/ "vfmsubadd213psd",
	/*555*/ "vfmsubadd231ps", 	// Len:2 Type:Size
	/*556*/ "vfmsubadd231psd",
	/*557*/ "vfnmadd132ps", 	// Len:2 Type:Size
	/*558*/ "vfnmadd132psd",
	/*559*/ "vfnmadd132ss", 	// Len:2 Type:Size
	/*560*/ "vfnmadd132ssd",
	/*561*/ "vfnmadd213ps", 	// Len:2 Type:Size
	/*562*/ "vfnmadd213psd",
	/*563*/ "vfnmadd213ss", 	// Len:2 Type:Size
	/*564*/ "vfnmadd213ssd",
	/*565*/ "vfnmadd231ps", 	// Len:2 Type:Size
	/*566*/ "vfnmadd231psd",
	/*567*/ "vfnmadd231ss", 	// Len:2 Type:Size
	/*568*/ "vfnmadd231ssd",
	/*569*/ "vfnmsub132ps", 	// Len:2 Type:Size
	/*570*/ "vfnmsub132psd",
	/*571*/ "vfnmsub132ss", 	// Len:2 Type:Size
	/*572*/ "vfnmsub132ssd",
	/*573*/ "vfnmsub213ps", 	// Len:2 Type:Size
	/*574*/ "vfnmsub213psd",
	/*575*/ "vfnmsub213ss", 	// Len:2 Type:Size
	/*576*/ "vfnmsub213ssd",
	/*577*/ "vfnmsub231ps", 	// Len:2 Type:Size
	/*578*/ "vfnmsub231psd",
	/*579*/ "vfnmsub231ss", 	// Len:2 Type:Size
	/*580*/ "vfnmsub231ssd",
	/*581*/ "vgatherdd", 	// Len:2 Type:Size
	/*582*/ "vgatherddq",
	/*583*/ "vgatherdps", 	// Len:2 Type:Size
	/*584*/ "vgatherdpsd",
	/*585*/ "vgatherqd", 	// Len:2 Type:Size
	/*586*/ "vgatherqdq",
	/*587*/ "vgatherqps", 	// Len:2 Type:Size
	/*588*/ "vgatherqpsd",
	/*589*/ "vhaddpd", 	// Len:1
	/*590*/ "vhaddps", 	// Len:1
	/*591*/ "vhsubpd", 	// Len:1
	/*592*/ "vhsubps", 	// Len:1
	/*593*/ "vinsertf128", 	// Len:1
	/*594*/ "vinserti128", 	// Len:1
	/*595*/ "vinsertps", 	// Len:1
	/*596*/ "vlddqu", 	// Len:1
	/*597*/ "vmaskmovdqu", 	// Len:1
	/*598*/ "vmaskmovpd", 	// Len:1
	/*599*/ "vmaskmovps", 	// Len:1
	/*600*/ "vmaxpd", 	// Len:1
	/*601*/ "vmaxps", 	// Len:1
	/*602*/ "vmaxsd", 	// Len:1
	/*603*/ "vmaxss", 	// Len:1
	/*604*/ "vmcall", 	// Len:1
	/*605*/ "vmclear", 	// Len:1
	/*606*/ "vmfunc", 	// Len:1
	/*607*/ "vminpd", 	// Len:1
	/*608*/ "vminps", 	// Len:1
	/*609*/ "vminsd", 	// Len:1
	/*610*/ "vminss", 	// Len:1
	/*611*/ "vmlaunch", 	// Len:1
	/*612*/ "vmovapd", 	// Len:1
	/*613*/ "vmovaps", 	// Len:1
	/*614*/ "vmovd", 	// Len:2 Type:Size
	/*615*/ "vmovdq",
	/*616*/ "vmovddup", 	// Len:1
	/*617*/ "vmovdqa", 	// Len:1
	/*618*/ "vmovdqu", 	// Len:1
	/*619*/ "vmovhlps", 	// Len:1
	/*620*/ "vmovhpd", 	// Len:1
	/*621*/ "vmovhps", 	// Len:1
	/*622*/ "vmovlhps", 	// Len:1
	/*623*/ "vmovlpd", 	// Len:1
	/*624*/ "vmovlps", 	// Len:1
	/*625*/ "vmovmskpd", 	// Len:1
	/*626*/ "vmovmskps", 	// Len:1
	/*627*/ "vmovntdq", 	// Len:1
	/*628*/ "vmovntdqa", 	// Len:1
	/*629*/ "vmovntpd", 	// Len:1
	/*630*/ "vmovntps", 	// Len:1
	/*631*/ "vmovq", 	// Len:1
	/*632*/ "vmovsd", 	// Len:1
	/*633*/ "vmovshdup", 	// Len:1
	/*634*/ "vmovsldup", 	// Len:1
	/*635*/ "vmovss", 	// Len:1
	/*636*/ "vmovupd", 	// Len:1
	/*637*/ "vmovups", 	// Len:1
	/*638*/ "vmpsadbw", 	// Len:1
	/*639*/ "vmptrld", 	// Len:1
	/*640*/ "vmptrst", 	// Len:1
	/*641*/ "vmread", 	// Len:1
	/*642*/ "vmresume", 	// Len:1
	/*643*/ "vmulpd", 	// Len:1
	/*644*/ "vmulps", 	// Len:1
	/*645*/ "vmulsd", 	// Len:1
	/*646*/ "vmulss", 	// Len:1
	/*647*/ "vmwrite", 	// Len:1
	/*648*/ "vmxoff", 	// Len:1
	/*649*/ "vmxon", 	// Len:1
	/*650*/ "vorpd", 	// Len:1
	/*651*/ "vorps", 	// Len:1
	/*652*/ "vpabsb", 	// Len:1
	/*653*/ "vpabsd", 	// Len:1
	/*654*/ "vpabsw", 	// Len:1
	/*655*/ "vpackssdw", 	// Len:1
	/*656*/ "vpacksswb", 	// Len:1
	/*657*/ "vpackusdw", 	// Len:1
	/*658*/ "vpackuswb", 	// Len:1
	/*659*/ "vpaddb", 	// Len:1
	/*660*/ "vpaddd", 	// Len:1
	/*661*/ "vpaddq", 	// Len:1
	/*662*/ "vpaddsb", 	// Len:1
	/*663*/ "vpaddsw", 	// Len:1
	/*664*/ "vpaddusb", 	// Len:1
	/*665*/ "vpaddusw", 	// Len:1
	/*666*/ "vpaddw", 	// Len:1
	/*667*/ "vpalignr", 	// Len:1
	/*668*/ "vpand", 	// Len:1
	/*669*/ "vpandn", 	// Len:1
	/*670*/ "vpavgb", 	// Len:1
	/*671*/ "vpavgw", 	// Len:1
	/*672*/ "vpblendd", 	// Len:1
	/*673*/ "vpblendvb", 	// Len:1
	/*674*/ "vpblendw", 	// Len:1
	/*675*/ "vpbroadcastb", 	// Len:1
	/*676*/ "vpbroadcastd", 	// Len:1
	/*677*/ "vpbroadcastq", 	// Len:1
	/*678*/ "vpbroadcastw", 	// Len:1
	/*679*/ "vpclmulqdq", 	// Len:1
	/*680*/ "vpcmpeqb", 	// Len:1
	/*681*/ "vpcmpeqd", 	// Len:1
	/*682*/ "vpcmpeqq", 	// Len:1
	/*683*/ "vpcmpeqw", 	// Len:1
	/*684*/ "vpcmpestri", 	// Len:1
	/*685*/ "vpcmpestrm", 	// Len:1
	/*686*/ "vpcmpgtb", 	// Len:1
	/*687*/ "vpcmpgtd", 	// Len:1
	/*688*/ "vpcmpgtq", 	// Len:1
	/*689*/ "vpcmpgtw", 	// Len:1
	/*690*/ "vpcmpistri", 	// Len:1
	/*691*/ "vpcmpistrm", 	// Len:1
	/*692*/ "vperm2f128", 	// Len:1
	/*693*/ "vperm2i128", 	// Len:1
	/*694*/ "vpermd", 	// Len:1
	/*695*/ "vpermilpd", 	// Len:1
	/*696*/ "vpermilps", 	// Len:1
	/*697*/ "vpermpd", 	// Len:1
	/*698*/ "vpermps", 	// Len:1
	/*699*/ "vpermq", 	// Len:1
	/*700*/ "vpextrb", 	// Len:1
	/*701*/ "vpextrd", 	// Len:2 Type:Size
	/*702*/ "vpextrdq",
	/*703*/ "vpextrw", 	// Len:1
	/*704*/ "vphaddd", 	// Len:1
	/*705*/ "vphaddsw", 	// Len:1
	/*706*/ "vphaddw", 	// Len:1
	/*707*/ "vphminposuw", 	// Len:1
	/*708*/ "vphsubd", 	// Len:1
	/*709*/ "vphsubsw", 	// Len:1
	/*710*/ "vphsubw", 	// Len:1
	/*711*/ "vpinsrb", 	// Len:1
	/*712*/ "vpinsrd", 	// Len:2 Type:Size
	/*713*/ "vpinsrdq",
	/*714*/ "vpinsrw", 	// Len:1
	/*715*/ "vpmaddubsw", 	// Len:1
	/*716*/ "vpmaddwd", 	// Len:1
	/*717*/ "vpmaskmovd", 	// Len:2 Type:Size
	/*718*/ "vpmaskmovdq",
	/*719*/ "vpmaxsb", 	// Len:1
	/*720*/ "vpmaxsd", 	// Len:1
	/*721*/ "vpmaxsw", 	// Len:1
	/*722*/ "vpmaxub", 	// Len:1
	/*723*/ "vpmaxud", 	// Len:1
	/*724*/ "vpmaxuw", 	// Len:1
	/*725*/ "vpminsb", 	// Len:1
	/*726*/ "vpminsd", 	// Len:1
	/*727*/ "vpminsw", 	// Len:1
	/*728*/ "vpminub", 	// Len:1
	/*729*/ "vpminud", 	// Len:1
	/*730*/ "vpminuw", 	// Len:1
	/*731*/ "vpmovmskb", 	// Len:1
	/*732*/ "vpmovsxbd", 	// Len:1
	/*733*/ "vpmovsxbq", 	// Len:1
	/*734*/ "vpmovsxbw", 	// Len:1
	/*735*/ "vpmovsxdq", 	// Len:1
	/*736*/ "vpmovsxwd", 	// Len:1
	/*737*/ "vpmovsxwq", 	// Len:1
	/*738*/ "vpmovzxbd", 	// Len:1
	/*739*/ "vpmovzxbq", 	// Len:1
	/*740*/ "vpmovzxbw", 	// Len:1
	/*741*/ "vpmovzxdq", 	// Len:1
	/*742*/ "vpmovzxwd", 	// Len:1
	/*743*/ "vpmovzxwq", 	// Len:1
	/*744*/ "vpmuldq", 	// Len:1
	/*745*/ "vpmulhrsw", 	// Len:1
	/*746*/ "vpmulhuw", 	// Len:1
	/*747*/ "vpmulhw", 	// Len:1
	/*748*/ "vpmulld", 	// Len:1
	/*749*/ "vpmullw", 	// Len:1
	/*750*/ "vpmuludq", 	// Len:1
	/*751*/ "vpor", 	// Len:1
	/*752*/ "vpsadbw", 	// Len:1
	/*753*/ "vpshufb", 	// Len:1
	/*754*/ "vpshufd", 	// Len:1
	/*755*/ "vpshufhw", 	// Len:1
	/*756*/ "vpshuflw", 	// Len:1
	/*757*/ "vpsignb", 	// Len:1
	/*758*/ "vpsignd", 	// Len:1
	/*759*/ "vpsignw", 	// Len:1
	/*760*/ "vpslld", 	// Len:1
	/*761*/ "vpslldq", 	// Len:1
	/*762*/ "vpsllq", 	// Len:1
	/*763*/ "vpsllvd", 	// Len:2 Type:Size
	/*764*/ "vpsllvdq",
	/*765*/ "vpsllw", 	// Len:1
	/*766*/ "vpsrad", 	// Len:1
	/*767*/ "vpsravd", 	// Len:1
	/*768*/ "vpsraw", 	// Len:1
	/*769*/ "vpsrld", 	// Len:1
	/*770*/ "vpsrldq", 	// Len:1
	/*771*/ "vpsrlq", 	// Len:1
	/*772*/ "vpsrlvd", 	// Len:2 Type:Size
	/*773*/ "vpsrlvdq",
	/*774*/ "vpsrlw", 	// Len:1
	/*775*/ "vpsubb", 	// Len:1
	/*776*/ "vpsubd", 	// Len:1
	/*777*/ "vpsubq", 	// Len:1
	/*778*/ "vpsubsb", 	// Len:1
	/*779*/ "vpsubsw", 	// Len:1
	/*780*/ "vpsubusb", 	// Len:1
	/*781*/ "vpsubusw", 	// Len:1
	/*782*/ "vpsubw", 	// Len:1
	/*783*/ "vptest", 	// Len:1
	/*784*/ "vpunpckhbw", 	// Len:1
	/*785*/ "vpunpckhdq", 	// Len:1
	/*786*/ "vpunpckhqdq", 	// Len:1
	/*787*/ "vpunpckhwd", 	// Len:1
	/*788*/ "vpunpcklbw", 	// Len:1
	/*789*/ "vpunpckldq", 	// Len:1
	/*790*/ "vpunpcklqdq", 	// Len:1
	/*791*/ "vpunpcklwd", 	// Len:1
	/*792*/ "vpxor", 	// Len:1
	/*793*/ "vrcpps", 	// Len:1
	/*794*/ "vrcpss", 	// Len:1
	/*795*/ "vroundpd", 	// Len:1
	/*796*/ "vroundps", 	// Len:1
	/*797*/ "vroundsd", 	// Len:1
	/*798*/ "vroundss", 	// Len:1
	/*799*/ "vrsqrtps", 	// Len:1
	/*800*/ "vrsqrtss", 	// Len:1
	/*801*/ "vshufpd", 	// Len:1
	/*802*/ "vshufps", 	// Len:1
	/*803*/ "vsqrtpd", 	// Len:1
	/*804*/ "vsqrtps", 	// Len:1
	/*805*/ "vsqrtsd", 	// Len:1
	/*806*/ "vsqrtss", 	// Len:1
	/*807*/ "vsubpd", 	// Len:1
	/*808*/ "vsubps", 	// Len:1
	/*809*/ "vsubsd", 	// Len:1
	/*810*/ "vsubss", 	// Len:1
	/*811*/ "vtestpd", 	// Len:1
	/*812*/ "vtestps", 	// Len:1
	/*813*/ "vucomisd", 	// Len:1
	/*814*/ "vucomiss", 	// Len:1
	/*815*/ "vunpckhpd", 	// Len:1
	/*816*/ "vunpckhps", 	// Len:1
	/*817*/ "vunpcklpd", 	// Len:1
	/*818*/ "vunpcklps", 	// Len:1
	/*819*/ "vxorpd", 	// Len:1
	/*820*/ "vxorps", 	// Len:1
	/*821*/ "vzeroall", 	// Len:1
	/*822*/ "vzeroupper", 	// Len:1
	/*823*/ "wbinvd", 	// Len:1
	/*824*/ "wrfsbase", 	// Len:1
	/*825*/ "wrgsbase", 	// Len:1
	/*826*/ "wrmsr", 	// Len:1
	/*827*/ "xabort", 	// Len:1
	/*828*/ "xadd", 	// Len:1
	/*829*/ "xbegin", 	// Len:1
	/*830*/ "xchg", 	// Len:1
	/*831*/ "xend", 	// Len:1
	/*832*/ "xgetbv", 	// Len:1
	/*833*/ "xlat", 	// Len:2 Type:Size
	/*834*/ "xlatb",
	/*835*/ "xor", 	// Len:1
	/*836*/ "xrstor", 	// Len:1
	/*837*/ "xsave", 	// Len:1
	/*838*/ "xsaveopt", 	// Len:1
	/*839*/ "xsetbv", 	// Len:1
	/*840*/ "xtest", 	// Len:1
};
extern unsigned char OperandGroup1[] = {
	/*0*/ 28, // ES
	/*1*/ 107, // SS
	/*2*/ 19, // eAX
	/*3*/ 23, // eCX
	/*4*/ 26, // eDX
	/*5*/ 22, // eBX
	/*6*/ 30, // eSP
	/*7*/ 21, // eBP
	/*8*/ 29, // eSI
	/*9*/ 25, // eDI
	/*10*/ 83, // rAX/r8
	/*11*/ 89, // rCX/r9
	/*12*/ 97, // rDX/r10
	/*13*/ 87, // rBX/r11
	/*14*/ 101, // rSP/r12
	/*15*/ 85, // rBP/r13
	/*16*/ 99, // rSI/r14
	/*17*/ 94, // rDI/r15
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
	/*31*/ 82, // RAX/EAX/R8/R8D
	/*32*/ 88, // RCX/ECX/R9/R9D
	/*33*/ 96, // RDX/EDX/R10/R10D
	/*34*/ 86, // RBX/EBX/R11/R11D
	/*35*/ 100, // RSP/ESP/R12/R12D
	/*36*/ 84, // RBP/EBP/R13/R13D
	/*37*/ 98, // RSI/ESI/R14/R14D
	/*38*/ 93, // RDI/EDI/R15/R15D
	/*39*/ 52, // Ib/Iz
	/*40*/ 4, // AL/rAX
	/*41*/ 27, // Ep
	/*42*/ 63, // Mp
	/*43*/ 103, // Rv/Mw
	/*44*/ 32, // Ew
	/*45*/ 67, // Ms
	/*46*/ 69, // Mw/Rv
	/*47*/ 61, // Mb
	/*48*/ 66, // Mq
	/*49*/ 62, // Mdq
	/*50*/ 102, // Rv
	/*51*/ 104, // Ry
};
extern unsigned char OperandGroup2[][2] = {
	/*0*/{ 20,36 }, // Eb,Gb
	/*1*/{ 31,39 }, // Ev,Gv
	/*2*/{ 36,20 }, // Gb,Eb
	/*3*/{ 39,31 }, // Gv,Ev
	/*4*/{ 2,51 }, // AL,Ib
	/*5*/{ 81,55 }, // rAX,Iz
	/*6*/{ 39,60 }, // Gv,Ma
	/*7*/{ 32,40 }, // Ew,Gw
	/*8*/{ 20,51 }, // Eb,Ib
	/*9*/{ 31,55 }, // Ev,Iz
	/*10*/{ 31,51 }, // Ev,Ib
	/*11*/{ 89,81 }, // rCX/r9,rAX
	/*12*/{ 97,81 }, // rDX/r10,rAX
	/*13*/{ 87,81 }, // rBX/r11,rAX
	/*14*/{ 101,81 }, // rSP/r12,rAX
	/*15*/{ 85,81 }, // rBP/r13,rAX
	/*16*/{ 99,81 }, // rSI/r14,rAX
	/*17*/{ 94,81 }, // rDI/r15,rAX
	/*18*/{ 2,73 }, // AL,Ob
	/*19*/{ 81,74 }, // rAX,Ov
	/*20*/{ 73,2 }, // Ob,AL
	/*21*/{ 74,81 }, // Ov,rAX
	/*22*/{ 139,136 }, // Yb,Xb
	/*23*/{ 140,137 }, // Yv,Xv
	/*24*/{ 136,139 }, // Xb,Yb
	/*25*/{ 137,140 }, // Xv,Yv
	/*26*/{ 3,51 }, // AL/R8L,Ib
	/*27*/{ 12,51 }, // CL/R9L,Ib
	/*28*/{ 16,51 }, // DL/R10L,Ib
	/*29*/{ 7,51 }, // BL/R11L,Ib
	/*30*/{ 1,51 }, // AH/R12L,Ib
	/*31*/{ 10,51 }, // CH/R13L,Ib
	/*32*/{ 15,51 }, // DH/R14L,Ib
	/*33*/{ 6,51 }, // BH/R15L,Ib
	/*34*/{ 42,63 }, // Gz,Mp
	/*35*/{ 20,0 }, // Eb,1
	/*36*/{ 31,0 }, // Ev,1
	/*37*/{ 20,11 }, // Eb,CL
	/*38*/{ 31,11 }, // Ev,CL
	/*39*/{ 19,51 }, // eAX,Ib
	/*40*/{ 51,2 }, // Ib,AL
	/*41*/{ 51,19 }, // Ib,eAX
	/*42*/{ 139,18 }, // Yb,DX
	/*43*/{ 141,18 }, // Yz,DX
	/*44*/{ 18,136 }, // DX,Xb
	/*45*/{ 18,138 }, // DX,Xz
	/*46*/{ 31,108 }, // Ev,Sw
	/*47*/{ 39,59 }, // Gv,M
	/*48*/{ 108,32 }, // Sw,Ew
	/*49*/{ 139,2 }, // Yb,AL
	/*50*/{ 140,81 }, // Yv,rAX
	/*51*/{ 2,136 }, // AL,Xb
	/*52*/{ 81,137 }, // rAX,Xv
	/*53*/{ 2,139 }, // AL,Yb
	/*54*/{ 81,140 }, // rAX,Yv
	/*55*/{ 83,53 }, // rAX/r8,Iv
	/*56*/{ 89,53 }, // rCX/r9,Iv
	/*57*/{ 97,53 }, // rDX/r10,Iv
	/*58*/{ 87,53 }, // rBX/r11,Iv
	/*59*/{ 101,53 }, // rSP/r12,Iv
	/*60*/{ 85,53 }, // rBP/r13,Iv
	/*61*/{ 99,53 }, // rSI/r14,Iv
	/*62*/{ 94,53 }, // rDI/r15,Iv
	/*63*/{ 54,51 }, // Iw,Ib
	/*64*/{ 2,18 }, // AL,DX
	/*65*/{ 19,18 }, // eAX,DX
	/*66*/{ 18,2 }, // DX,AL
	/*67*/{ 18,19 }, // DX,eAX
	/*68*/{ 39,32 }, // Gv,Ew
	/*69*/{ 120,130 }, // Vps,Wps
	/*70*/{ 130,120 }, // Wps,Vps
	/*71*/{ 66,121 }, // Mq,Vq
	/*72*/{ 119,129 }, // Vpd,Wpd
	/*73*/{ 129,119 }, // Wpd,Vpd
	/*74*/{ 125,135 }, // Vx,Wx
	/*75*/{ 90,9 }, // Rd,Cd
	/*76*/{ 90,14 }, // Rd,Dd
	/*77*/{ 9,90 }, // Cd,Rd
	/*78*/{ 14,90 }, // Dd,Rd
	/*79*/{ 41,112 }, // Gy,Ups
	/*80*/{ 41,111 }, // Gy,Upd
	/*81*/{ 77,78 }, // Pq,Qd
	/*82*/{ 77,80 }, // Pq,Qq
	/*83*/{ 120,79 }, // Vps,Qpi
	/*84*/{ 65,120 }, // Mps,Vps
	/*85*/{ 76,130 }, // Ppi,Wps
	/*86*/{ 124,134 }, // Vss,Wss
	/*87*/{ 119,79 }, // Vpd,Qpi
	/*88*/{ 64,119 }, // Mpd,Vpd
	/*89*/{ 76,129 }, // Ppi,Wpd
	/*90*/{ 79,129 }, // Qpi,Wpd
	/*91*/{ 123,133 }, // Vsd,Wsd
	/*92*/{ 41,134 }, // Gy,Wss
	/*93*/{ 41,133 }, // Gy,Wsd
	/*94*/{ 119,130 }, // Vpd,Wps
	/*95*/{ 120,128 }, // Vps,Wdq
	/*96*/{ 120,129 }, // Vps,Wpd
	/*97*/{ 118,130 }, // Vdq,Wps
	/*98*/{ 75,33 }, // Pd,Ey
	/*99*/{ 126,33 }, // Vy,Ey
	/*100*/{ 33,41 }, // Ey,Gy
	/*101*/{ 41,33 }, // Gy,Ey
	/*102*/{ 33,75 }, // Ey,Pd
	/*103*/{ 80,77 }, // Qq,Pq
	/*104*/{ 33,126 }, // Ey,Vy
	/*105*/{ 135,125 }, // Wx,Vx
	/*106*/{ 121,131 }, // Vq,Wq
	/*107*/{ 39,63 }, // Gv,Mp
	/*108*/{ 39,20 }, // Gv,Eb
	/*109*/{ 71,41 }, // My,Gy
	/*110*/{ 37,72 }, // Gd,Nq
	/*111*/{ 131,121 }, // Wq,Vq
	/*112*/{ 37,114 }, // Gd,Ux
	/*113*/{ 118,72 }, // Vdq,Nq
	/*114*/{ 77,113 }, // Pq,Uq
	/*115*/{ 66,77 }, // Mq,Pq
	/*116*/{ 125,129 }, // Vx,Wpd
	/*117*/{ 70,125 }, // Mx,Vx
	/*118*/{ 77,72 }, // Pq,Nq
	/*119*/{ 118,109 }, // Vdq,Udq
	/*120*/{ 125,70 }, // Vx,Mx
	/*121*/{ 118,128 }, // Vdq,Wdq
	/*122*/{ 125,116 }, // Vx,Ux/Mq
	/*123*/{ 125,115 }, // Vx,Ux/Md
	/*124*/{ 125,117 }, // Vx,Ux/Mw
	/*125*/{ 41,62 }, // Gy,Mdq
	/*126*/{ 41,71 }, // Gy,My
	/*127*/{ 40,68 }, // Gw,Mw
	/*128*/{ 68,40 }, // Mw,Gw
	/*129*/{ 37,20 }, // Gd,Eb
	/*130*/{ 37,33 }, // Gd,Ey
	/*131*/{ 37,32 }, // Gd,Ew
	/*132*/{ 125,127 }, // Vx,Wd
	/*133*/{ 122,131 }, // Vqq,Wq
	/*134*/{ 122,62 }, // Vqq,Mdq
	/*135*/{ 72,51 }, // Nq,Ib
	/*136*/{ 8,33 }, // By,Ey
};
extern unsigned char OperandGroup3[][3] = {
	/*0*/{ 39,31,55 }, // Gv,Ev,Iz
	/*1*/{ 39,31,51 }, // Gv,Ev,Ib
	/*2*/{ 121,46,66 }, // Vq,Hq,Mq
	/*3*/{ 121,46,113 }, // Vq,Hq,Uq
	/*4*/{ 125,50,135 }, // Vx,Hx,Wx
	/*5*/{ 118,46,66 }, // Vdq,Hq,Mq
	/*6*/{ 118,46,113 }, // Vdq,Hq,Uq
	/*7*/{ 125,50,134 }, // Vx,Hx,Wss
	/*8*/{ 134,50,124 }, // Wss,Hx,Vss
	/*9*/{ 125,50,133 }, // Vx,Hx,Wsd
	/*10*/{ 133,50,123 }, // Wsd,Hx,Vsd
	/*11*/{ 120,45,130 }, // Vps,Hps,Wps
	/*12*/{ 119,44,129 }, // Vpd,Hpd,Wpd
	/*13*/{ 124,49,134 }, // Vss,Hss,Wss
	/*14*/{ 123,48,133 }, // Vsd,Hsd,Wsd
	/*15*/{ 77,80,51 }, // Pq,Qq,Ib
	/*16*/{ 125,135,51 }, // Vx,Wx,Ib
	/*17*/{ 124,49,33 }, // Vss,Hss,Ey
	/*18*/{ 123,48,33 }, // Vsd,Hsd,Ey
	/*19*/{ 123,50,134 }, // Vsd,Hx,Wss
	/*20*/{ 124,50,133 }, // Vss,Hx,Wsd
	/*21*/{ 31,39,51 }, // Ev,Gv,Ib
	/*22*/{ 31,39,11 }, // Ev,Gv,CL
	/*23*/{ 77,106,51 }, // Pq,Ry/Mw,Ib
	/*24*/{ 37,72,51 }, // Gd,Nq,Ib
	/*25*/{ 37,109,51 }, // Gd,Udq,Ib
	/*26*/{ 122,47,132 }, // Vqq,Hqq,Wqq
	/*27*/{ 41,8,33 }, // Gy,By,Ey
	/*28*/{ 41,33,8 }, // Gy,Ey,By
	/*29*/{ 125,50,70 }, // Vx,Hx,Mx
	/*30*/{ 70,50,125 }, // Mx,Hx,Vx
	/*31*/{ 70,125,50 }, // Mx,Vx,Hx
	/*32*/{ 118,43,128 }, // Vdq,Hdq,Wdq
	/*33*/{ 122,132,51 }, // Vqq,Wqq,Ib
	/*34*/{ 91,118,51 }, // Rd/Mb,Vdq,Ib
	/*35*/{ 92,118,51 }, // Rd/Mw,Vdq,Ib
	/*36*/{ 33,118,51 }, // Ey,Vdq,Ib
	/*37*/{ 24,118,51 }, // Ed,Vdq,Ib
	/*38*/{ 118,128,51 }, // Vdq,Wdq,Ib
	/*39*/{ 41,33,51 }, // Gy,Ey,Ib
	/*40*/{ 124,134,51 }, // Vss,Wss,Ib
	/*41*/{ 123,133,51 }, // Vsd,Wsd,Ib
	/*42*/{ 128,122,51 }, // Wdq,Vqq,Ib
	/*43*/{ 135,125,51 }, // Wx,Vx,Ib
	/*44*/{ 50,114,51 }, // Hx,Ux,Ib
};
extern unsigned char OperandGroup4[][4] = {
	/*0*/{ 120,45,130,51 }, // Vps,Hps,Wps,Ib
	/*1*/{ 119,44,129,51 }, // Vpd,Hpd,Wpd,Ib
	/*2*/{ 118,43,106,51 }, // Vdq,Hdq,Ry/Mw,Ib
	/*3*/{ 124,49,134,51 }, // Vss,Hss,Wss,Ib
	/*4*/{ 123,48,133,51 }, // Vsd,Hsd,Wsd,Ib
	/*5*/{ 8,41,95,33 }, // By,Gy,rDX,Ey
	/*6*/{ 125,50,135,51 }, // Vx,Hx,Wx,Ib
	/*7*/{ 122,47,132,51 }, // Vqq,Hqq,Wqq,Ib
	/*8*/{ 118,43,105,51 }, // Vdq,Hdq,Ry/Mb,Ib
	/*9*/{ 118,43,110,51 }, // Vdq,Hdq,Udq/Md,Ib
	/*10*/{ 118,43,33,51 }, // Vdq,Hdq,Ey,Ib
	/*11*/{ 118,43,128,51 }, // Vdq,Hdq,Wdq,Ib
	/*12*/{ 125,50,135,58 }, // Vx,Hx,Wx,Lx
};
extern OpcodeData Byte1[] = {
	{ 1,1 },{ 2,1 },{ 3,1 },{ 4,1 },{ 5,1 },{ 6,1 },{ 7,1 },{ 8,1 },
	{ 139,1 },{ 140,1 },{ 141,1 },{ 142,1 },{ 143,1 },{ 144,1 },{ 145,1 },{ 146,1 },
	{ 9,1 },{ 10,1 },{ 11,1 },{ 12,1 },{ 13,1 },{ 14,1 },{ 15,1 },{ 16,1 },
	{ 147,1 },{ 148,1 },{ 149,1 },{ 150,1 },{ 151,1 },{ 152,1 },{ 153,1 },{ 154,1 },
	{ 17,1 },{ 18,1 },{ 19,1 },{ 20,1 },{ 21,1 },{ 22,1 },{ 23,1 },{ 24,1 },
	{ 155,1 },{ 156,1 },{ 157,1 },{ 158,1 },{ 159,1 },{ 160,1 },{ 161,1 },{ 162,1 },
	{ 25,1 },{ 26,1 },{ 27,1 },{ 28,1 },{ 29,1 },{ 30,1 },{ 31,1 },{ 32,1 },
	{ 163,1 },{ 164,1 },{ 165,1 },{ 166,1 },{ 167,1 },{ 168,1 },{ 169,1 },{ 170,1 },
	{ 33,2 },{ 35,2 },{ 37,2 },{ 39,2 },{ 41,2 },{ 43,2 },{ 45,2 },{ 47,2 },
	{ 171,2 },{ 173,2 },{ 175,2 },{ 177,2 },{ 179,2 },{ 181,2 },{ 183,2 },{ 185,2 },
	{ 49,1 },{ 50,1 },{ 51,1 },{ 52,1 },{ 53,1 },{ 54,1 },{ 55,1 },{ 56,1 },
	{ 187,1 },{ 188,1 },{ 189,1 },{ 190,1 },{ 191,1 },{ 192,1 },{ 193,1 },{ 194,1 },
	{ 57,1 },{ 58,1 },{ 59,1 },{ 60,2 },{ 62,1 },{ 63,1 },{ 64,1 },{ 65,1 },
	{ 195,1 },{ 196,1 },{ 197,1 },{ 198,1 },{ 199,1 },{ 200,1 },{ 201,1 },{ 202,1 },
	{ 66,1 },{ 67,1 },{ 68,1 },{ 69,1 },{ 70,1 },{ 71,1 },{ 72,1 },{ 73,1 },
	{ 203,1 },{ 204,1 },{ 205,1 },{ 206,1 },{ 207,1 },{ 208,1 },{ 209,1 },{ 210,1 },
	{ 74,1 },{ 75,1 },{ 76,1 },{ 77,1 },{ 78,1 },{ 79,1 },{ 80,1 },{ 81,1 },
	{ 211,1 },{ 212,1 },{ 213,1 },{ 214,1 },{ 215,1 },{ 216,1 },{ 217,1 },{ 218,1 },
	{ 82,2 },{ 84,1 },{ 85,1 },{ 86,1 },{ 87,1 },{ 88,1 },{ 89,1 },{ 90,1 },
	{ 219,1 },{ 220,1 },{ 221,1 },{ 222,1 },{ 223,1 },{ 224,1 },{ 225,1 },{ 226,1 },
	{ 91,1 },{ 92,1 },{ 93,1 },{ 94,1 },{ 95,1 },{ 96,1 },{ 97,1 },{ 98,1 },
	{ 227,1 },{ 228,1 },{ 229,1 },{ 230,1 },{ 231,1 },{ 232,1 },{ 233,1 },{ 234,1 },
	{ 99,1 },{ 100,1 },{ 101,1 },{ 102,1 },{ 103,1 },{ 104,1 },{ 105,1 },{ 106,1 },
	{ 235,1 },{ 236,1 },{ 237,1 },{ 238,1 },{ 239,1 },{ 240,1 },{ 241,1 },{ 242,1 },
	{ 107,1 },{ 108,1 },{ 109,1 },{ 110,1 },{ 111,2 },{ 113,2 },{ 115,1 },{ 116,1 },
	{ 243,1 },{ 244,1 },{ 245,1 },{ 246,1 },{ 247,1 },{ 248,1 },{ 249,1 },{ 250,1 },
	{ 117,1 },{ 118,1 },{ 119,1 },{ 120,1 },{ 121,1 },{ 122,1 },{ 0,0 },{ 123,1 },
	{ 251,1 },{ 252,1 },{ 253,1 },{ 254,1 },{ 255,1 },{ 256,1 },{ 257,1 },{ 258,1 },
	{ 124,1 },{ 125,1 },{ 126,1 },{ 127,1 },{ 128,1 },{ 129,1 },{ 130,1 },{ 131,1 },
	{ 259,1 },{ 260,1 },{ 261,1 },{ 262,1 },{ 263,1 },{ 264,1 },{ 265,1 },{ 266,1 },
	{ 132,1 },{ 0,0 },{ 133,1 },{ 134,1 },{ 135,1 },{ 136,1 },{ 137,1 },{ 138,1 },
	{ 267,1 },{ 268,1 },{ 269,1 },{ 270,1 },{ 271,1 },{ 272,1 },{ 273,1 },{ 274,1 },
};
extern OpcodeData Byte2[] = {
	{ 275,1 },{ 276,1 },{ 277,1 },{ 278,1 },{ 0,0 },{ 279,1 },{ 280,1 },{ 281,1 },
	{ 376,1 },{ 377,1 },{ 0,0 },{ 378,1 },{ 0,0 },{ 379,1 },{ 0,0 },{ 0,0 },
	{ 282,4 },{ 286,4 },{ 290,5 },{ 295,2 },{ 297,2 },{ 299,2 },{ 301,4 },{ 305,2 },
	{ 380,1 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 381,1 },
	{ 307,1 },{ 308,1 },{ 309,1 },{ 310,1 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },
	{ 382,2 },{ 384,2 },{ 386,4 },{ 390,2 },{ 392,4 },{ 396,4 },{ 400,2 },{ 402,2 },
	{ 311,1 },{ 312,1 },{ 313,1 },{ 314,1 },{ 315,1 },{ 316,1 },{ 0,0 },{ 317,1 },
	{ 404,1 },{ 0,0 },{ 405,1 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },
	{ 318,1 },{ 319,1 },{ 320,1 },{ 321,1 },{ 322,1 },{ 323,1 },{ 324,1 },{ 325,1 },
	{ 406,1 },{ 407,1 },{ 408,1 },{ 409,1 },{ 410,1 },{ 411,1 },{ 412,1 },{ 413,1 },
	{ 326,2 },{ 328,4 },{ 332,2 },{ 334,2 },{ 336,2 },{ 338,2 },{ 340,2 },{ 342,2 },
	{ 414,4 },{ 418,4 },{ 422,4 },{ 426,3 },{ 429,4 },{ 433,4 },{ 437,4 },{ 441,4 },
	{ 344,2 },{ 346,2 },{ 348,2 },{ 350,2 },{ 352,2 },{ 354,2 },{ 356,2 },{ 358,2 },
	{ 445,2 },{ 447,2 },{ 449,2 },{ 451,2 },{ 458,1 },{ 459,1 },{ 453,2 },{ 455,3 },
	{ 360,4 },{ 364,1 },{ 365,1 },{ 366,1 },{ 367,2 },{ 369,2 },{ 371,2 },{ 373,3 },
	{ 460,1 },{ 461,1 },{ 0,0 },{ 0,0 },{ 468,2 },{ 470,2 },{ 462,3 },{ 465,3 },
	{ 472,1 },{ 473,1 },{ 474,1 },{ 475,1 },{ 476,1 },{ 477,1 },{ 478,1 },{ 479,1 },
	{ 565,1 },{ 566,1 },{ 567,1 },{ 568,1 },{ 569,1 },{ 570,1 },{ 571,1 },{ 572,1 },
	{ 480,1 },{ 481,1 },{ 482,1 },{ 483,1 },{ 484,1 },{ 485,1 },{ 486,1 },{ 487,1 },
	{ 573,1 },{ 574,1 },{ 575,1 },{ 576,1 },{ 577,1 },{ 578,1 },{ 579,1 },{ 580,1 },
	{ 488,1 },{ 489,1 },{ 490,1 },{ 491,1 },{ 492,1 },{ 493,1 },{ 0,0 },{ 0,0 },
	{ 581,1 },{ 582,1 },{ 583,1 },{ 584,1 },{ 585,1 },{ 586,1 },{ 587,1 },{ 588,1 },
	{ 494,1 },{ 495,1 },{ 496,1 },{ 497,1 },{ 498,1 },{ 499,1 },{ 500,1 },{ 501,1 },
	{ 589,2 },{ 591,1 },{ 592,1 },{ 593,1 },{ 594,2 },{ 596,2 },{ 598,1 },{ 599,1 },
	{ 502,1 },{ 503,1 },{ 504,4 },{ 508,1 },{ 509,2 },{ 511,2 },{ 513,2 },{ 515,1 },
	{ 600,1 },{ 601,1 },{ 602,1 },{ 603,1 },{ 604,1 },{ 605,1 },{ 606,1 },{ 607,1 },
	{ 528,2 },{ 516,2 },{ 518,2 },{ 520,2 },{ 522,2 },{ 524,2 },{ 530,3 },{ 526,2 },
	{ 608,2 },{ 610,2 },{ 612,2 },{ 614,2 },{ 616,2 },{ 618,2 },{ 620,2 },{ 622,2 },
	{ 533,2 },{ 535,2 },{ 537,2 },{ 539,2 },{ 541,2 },{ 543,2 },{ 547,3 },{ 545,2 },
	{ 624,2 },{ 626,2 },{ 628,2 },{ 630,2 },{ 632,2 },{ 634,2 },{ 636,2 },{ 638,2 },
	{ 564,1 },{ 550,2 },{ 552,2 },{ 554,2 },{ 556,2 },{ 558,2 },{ 560,2 },{ 562,2 },
	{ 640,2 },{ 642,2 },{ 644,2 },{ 646,2 },{ 648,2 },{ 650,2 },{ 652,2 },{ 0,0 },
};
extern ZipOpcodeData Byte3Zip_38[] = {
	{ 654,2,0 },{ 656,2,1 },{ 658,2,2 },{ 660,2,3 },{ 662,2,4 },{ 664,2,5 },{ 666,2,6 },{ 668,2,7 },
	{ 728,2,8 },{ 730,2,9 },{ 732,2,10 },{ 734,2,11 },{ 736,1,12 },{ 737,1,13 },{ 738,1,14 },{ 739,1,15 },
	{ 670,1,16 },{ 671,1,19 },{ 672,1,20 },{ 673,1,21 },{ 674,1,22 },{ 675,1,23 },{ 746,1,24 },{ 747,1,25 },
	{ 748,1,26 },{ 740,2,28 },{ 742,2,29 },{ 744,2,30 },{ 676,1,32 },{ 677,1,33 },{ 678,1,34 },{ 679,1,35 },
	{ 680,1,36 },{ 681,1,37 },{ 749,1,40 },{ 750,1,41 },{ 751,1,42 },{ 752,1,43 },{ 753,1,44 },{ 754,1,45 },
	{ 755,1,46 },{ 756,1,47 },{ 682,1,48 },{ 683,1,49 },{ 684,1,50 },{ 685,1,51 },{ 686,1,52 },{ 687,1,53 },
	{ 688,1,54 },{ 689,1,55 },{ 757,1,56 },{ 758,1,57 },{ 759,1,58 },{ 760,1,59 },{ 761,1,60 },{ 762,1,61 },
	{ 763,1,62 },{ 764,1,63 },{ 690,1,64 },{ 691,1,65 },{ 692,1,69 },{ 693,1,70 },{ 694,1,71 },{ 765,1,88 },
	{ 766,1,89 },{ 767,1,90 },{ 768,1,120 },{ 769,1,121 },{ 695,1,128 },{ 696,1,129 },{ 697,1,130 },{ 770,1,140 },
	{ 771,1,142 },{ 698,1,144 },{ 699,1,145 },{ 700,1,146 },{ 701,1,147 },{ 702,1,150 },{ 703,1,151 },{ 772,1,152 },
	{ 773,1,153 },{ 774,1,154 },{ 775,1,155 },{ 776,1,156 },{ 777,1,157 },{ 778,1,158 },{ 779,1,159 },{ 704,1,166 },
	{ 705,1,167 },{ 780,1,168 },{ 781,1,169 },{ 782,1,170 },{ 783,1,171 },{ 784,1,172 },{ 785,1,173 },{ 786,1,174 },
	{ 787,1,175 },{ 706,1,182 },{ 707,1,183 },{ 788,1,184 },{ 789,1,185 },{ 790,1,186 },{ 791,1,187 },{ 792,1,188 },
	{ 793,1,189 },{ 794,1,190 },{ 795,1,191 },{ 796,1,219 },{ 797,1,220 },{ 798,1,221 },{ 799,1,222 },{ 800,1,223 },
	{ 708,4,240 },{ 712,4,241 },{ 716,1,242 },{ 717,1,243 },{ 718,3,245 },{ 725,3,246 },{ 721,4,247 },
};
extern ZipOpcodeData Byte3Zip_3A[] = {
	{ 801,1,0 },{ 802,1,1 },{ 803,1,2 },{ 804,1,4 },{ 805,1,5 },{ 806,1,6 },{ 826,2,8 },{ 828,2,9 },
	{ 830,1,10 },{ 831,1,11 },{ 832,1,12 },{ 833,2,13 },{ 835,1,14 },{ 824,2,15 },{ 807,1,20 },{ 808,1,21 },
	{ 809,1,22 },{ 810,1,23 },{ 811,1,32 },{ 812,1,33 },{ 813,1,34 },{ 836,1,56 },{ 837,1,57 },{ 814,1,64 },
	{ 815,1,65 },{ 816,1,66 },{ 817,1,68 },{ 818,1,70 },{ 838,1,74 },{ 839,1,75 },{ 840,1,76 },{ 819,1,96 },
	{ 820,1,97 },{ 821,1,98 },{ 822,1,99 },{ 841,1,223 },{ 823,1,240 },
};


