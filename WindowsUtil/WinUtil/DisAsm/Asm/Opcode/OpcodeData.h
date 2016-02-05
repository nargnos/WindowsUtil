#pragma once
#include <memory>
#include <Windows.h>
#include "OpcodeDef.h"

// 1byte指向多指令，满足条件就选择该指令（对应唯一的操作数组合）
// Byte_xxx ->n*InstIndex-> Inst -> n * OperandGroup_xxx -> n * operand
//							|-> n * NameId	    ^
//				|-> n * Group_xxx  /

// 多名指令在名字字符串注释里用Count标识表示包括自身在内，往下有几个名字选择（所以局部没有排序）
// 数组元素带的数字注释表示下标，方便检查

// #pragma code_seg(".opcode")

// #pragma code_seg()
// #pragma comment(linker, "/SECTION:.opcode,R")
// FIX: 数据占位太大啦

const RegOrOperandGroup Operands[] =
{
	/*  0*/{ H_1, NULL },                        // 1
	/*  1*/{ SPC_AH_R12L, NULL },                // AH/R12L
	/*  2*/{ REG_AL, NULL },                     // AL
	/*  3*/{ SPC_AL_R8L, NULL },                 // AL/R8L
	/*  4*/{ SPC_AL_rAX, NULL },                 // AL/rAX
	/*  5*/{ H_A, L_p },                         // Ap
	/*  6*/{ SPC_BH_R15L, NULL },                // BH/R15L
	/*  7*/{ SPC_BL_R11L, NULL },                // BL/R11L
	/*  8*/{ H_B, L_y },                         // By
	/*  9*/{ H_C, L_d },                         // Cd
	/* 10*/{ SPC_CH_R13L, NULL },                // CH/R13L
	/* 11*/{ REG_CL, NULL },                     // CL
	/* 12*/{ SPC_CL_R9L, NULL },                 // CL/R9L
	/* 13*/{ SEG_CS, NULL },                     // CS
	/* 14*/{ H_D, L_d },                         // Dd
	/* 15*/{ SPC_DH_R14L, NULL },                // DH/R14L
	/* 16*/{ SPC_DL_R10L, NULL },                // DL/R10L
	/* 17*/{ SEG_DS, NULL },                     // DS
	/* 18*/{ REG_DX, NULL },                     // DX
	/* 19*/{ REG_EAX, CHANGE_REG },              // eAX
	/* 20*/{ H_E, L_b },                         // Eb
	/* 21*/{ REG_EBP, CHANGE_REG },              // eBP
	/* 22*/{ REG_EBX, CHANGE_REG },              // eBX
	/* 23*/{ REG_ECX, CHANGE_REG },              // eCX
	/* 24*/{ H_E, L_d },                         // Ed
	/* 25*/{ REG_EDI, CHANGE_REG },              // eDI
	/* 26*/{ REG_EDX, CHANGE_REG },              // eDX
	/* 27*/{ H_E, L_p },                         // Ep
	/* 28*/{ SEG_ES, NULL },                     // ES
	/* 29*/{ REG_ESI, CHANGE_REG },              // eSI
	/* 30*/{ REG_ESP, CHANGE_REG },              // eSP
	/* 31*/{ H_E, L_v },                         // Ev
	/* 32*/{ H_E, L_w },                         // Ew
	/* 33*/{ H_E, L_y },                         // Ey
	/* 34*/{ SEG_FS, NULL },                     // FS
	/* 35*/{ H_F, L_v },                         // Fv
	/* 36*/{ H_G, L_b },                         // Gb
	/* 37*/{ H_G, L_d },                         // Gd
	/* 38*/{ SEG_GS, NULL },                     // GS
	/* 39*/{ H_G, L_v },                         // Gv
	/* 40*/{ H_G, L_w },                         // Gw
	/* 41*/{ H_G, L_y },                         // Gy
	/* 42*/{ H_G, L_z },                         // Gz
	/* 43*/{ H_H, L_dq },                        // Hdq
	/* 44*/{ H_H, L_pd },                        // Hpd
	/* 45*/{ H_H, L_ps },                        // Hps
	/* 46*/{ H_H, L_q },                         // Hq
	/* 47*/{ H_H, L_qq },                        // Hqq
	/* 48*/{ H_H, L_sd },                        // Hsd
	/* 49*/{ H_H, L_ss },                        // Hss
	/* 50*/{ H_H, L_x },                         // Hx
	/* 51*/{ H_I, L_b },                         // Ib
	/* 52*/{ SPC_Ib_Iz, NULL },                  // Ib/Iz
	/* 53*/{ H_I, L_v },                         // Iv
	/* 54*/{ H_I, L_w },                         // Iw
	/* 55*/{ H_I, L_z },                         // Iz
	/* 56*/{ H_J, L_b },                         // Jb
	/* 57*/{ H_J, L_z },                         // Jz
	/* 58*/{ H_L, L_x },                         // Lx
	/* 59*/{ H_M, NULL },                        // M
	/* 60*/{ H_M, L_a },                         // Ma
	/* 61*/{ H_M, L_b },                         // Mb
	/* 62*/{ H_M, L_dq },                        // Mdq
	/* 63*/{ H_M, L_p },                         // Mp
	/* 64*/{ H_M, L_pd },                        // Mpd
	/* 65*/{ H_M, L_ps },                        // Mps
	/* 66*/{ H_M, L_q },                         // Mq
	/* 67*/{ H_M, L_s },                         // Ms
	/* 68*/{ H_M, L_w },                         // Mw
	/* 69*/{ SPC_Mw_Rv, NULL },                  // Mw/Rv
	/* 70*/{ H_M, L_x },                         // Mx
	/* 71*/{ H_M, L_y },                         // My
	/* 72*/{ H_N, L_q },                         // Nq
	/* 73*/{ H_O, L_b },                         // Ob
	/* 74*/{ H_O, L_v },                         // Ov
	/* 75*/{ H_P, L_d },                         // Pd
	/* 76*/{ H_P, L_pi },                        // Ppi
	/* 77*/{ H_P, L_q },                         // Pq
	/* 78*/{ H_Q, L_d },                         // Qd
	/* 79*/{ H_Q, L_pi },                        // Qpi
	/* 80*/{ H_Q, L_q },                         // Qq
	/* 81*/{ REG_R8, CHANGE_REG },               // r8
	/* 82*/{ REG_RAX, CHANGE_REG },              // rAX
	/* 83*/{ SPC_RAX_EAX_R8_R8D, NULL },         // RAX/EAX/R8/R8D
	/* 84*/{ SPC_rAX_r8, NULL },                 // rAX/r8
	/* 85*/{ SPC_RBP_EBP_R13_R13D, NULL },       // RBP/EBP/R13/R13D
	/* 86*/{ SPC_rBP_r13, NULL },                // rBP/r13
	/* 87*/{ SPC_RBX_EBX_R11_R11D, NULL },       // RBX/EBX/R11/R11D
	/* 88*/{ SPC_rBX_r11, NULL },                // rBX/r11
	/* 89*/{ SPC_RCX_ECX_R9_R9D, NULL },         // RCX/ECX/R9/R9D
	/* 90*/{ SPC_rCX_r9, NULL },                 // rCX/r9
	/* 91*/{ H_R, L_d },                         // Rd
	/* 92*/{ SPC_Rd_Mb, NULL },                  // Rd/Mb
	/* 93*/{ SPC_Rd_Mw, NULL },                  // Rd/Mw
	/* 94*/{ SPC_RDI_EDI_R15_R15D, NULL },       // RDI/EDI/R15/R15D
	/* 95*/{ SPC_rDI_r15, NULL },                // rDI/r15
	/* 96*/{ REG_RDX, CHANGE_REG },              // rDX
	/* 97*/{ SPC_RDX_EDX_R10_R10D, NULL },       // RDX/EDX/R10/R10D
	/* 98*/{ SPC_rDX_r10, NULL },                // rDX/r10
	/* 99*/{ SPC_RSI_ESI_R14_R14D, NULL },       // RSI/ESI/R14/R14D
	/*100*/{ SPC_rSI_r14, NULL },                // rSI/r14
	/*101*/{ SPC_RSP_ESP_R12_R12D, NULL },       // RSP/ESP/R12/R12D
	/*102*/{ SPC_rSP_r12, NULL },                // rSP/r12
	/*103*/{ H_R, L_v },                         // Rv
	/*104*/{ SPC_Rv_Mw, NULL },                  // Rv/Mw
	/*105*/{ H_R, L_y },                         // Ry
	/*106*/{ SPC_Ry_Mb, NULL },                  // Ry/Mb
	/*107*/{ SPC_Ry_Mw, NULL },                  // Ry/Mw
	/*108*/{ SEG_SS, NULL },                     // SS
	/*109*/{ H_S, L_w },                         // Sw
	/*110*/{ H_U, L_dq },                        // Udq
	/*111*/{ SPC_Udq_Md, NULL },                 // Udq/Md
	/*112*/{ H_U, L_pd },                        // Upd
	/*113*/{ H_U, L_ps },                        // Ups
	/*114*/{ H_U, L_q },                         // Uq
	/*115*/{ H_U, L_x },                         // Ux
	/*116*/{ SPC_Ux_Md, NULL },                  // Ux/Md
	/*117*/{ SPC_Ux_Mq, NULL },                  // Ux/Mq
	/*118*/{ SPC_Ux_Mw, NULL },                  // Ux/Mw
	/*119*/{ H_V, L_dq },                        // Vdq
	/*120*/{ H_V, L_pd },                        // Vpd
	/*121*/{ H_V, L_ps },                        // Vps
	/*122*/{ H_V, L_q },                         // Vq
	/*123*/{ H_V, L_qq },                        // Vqq
	/*124*/{ H_V, L_sd },                        // Vsd
	/*125*/{ H_V, L_ss },                        // Vss
	/*126*/{ H_V, L_x },                         // Vx
	/*127*/{ H_V, L_y },                         // Vy
	/*128*/{ H_W, L_d },                         // Wd
	/*129*/{ H_W, L_dq },                        // Wdq
	/*130*/{ H_W, L_pd },                        // Wpd
	/*131*/{ H_W, L_ps },                        // Wps
	/*132*/{ H_W, L_q },                         // Wq
	/*133*/{ H_W, L_qq },                        // Wqq
	/*134*/{ H_W, L_sd },                        // Wsd
	/*135*/{ H_W, L_ss },                        // Wss
	/*136*/{ H_W, L_x },                         // Wx
	/*137*/{ H_X, L_b },                         // Xb
	/*138*/{ H_X, L_v },                         // Xv
	/*139*/{ H_X, L_z },                         // Xz
	/*140*/{ H_Y, L_b },                         // Yb
	/*141*/{ H_Y, L_v },                         // Yv
	/*142*/{ H_Y, L_z },                         // Yz
};
const LPCSTR InstructionNames[] =
{
	/*  0*/ "(prefix/addresssize)",             // Count: 1
	/*  1*/ "(prefix/lock)",                    // Count: 1
	/*  2*/ "(prefix/operandsize)",             // Count: 1
	/*  3*/ "(prefix/repnexacquire)",           // Count: 1
	/*  4*/ "(prefix/repxrelease/repexrelease)",// Count: 1
	/*  5*/ "(prefix/rex)",                     // Count: 1
	/*  6*/ "(prefix/rex.b)",                   // Count: 1
	/*  7*/ "(prefix/rex.r)",                   // Count: 1
	/*  8*/ "(prefix/rex.rb)",                  // Count: 1
	/*  9*/ "(prefix/rex.rx)",                  // Count: 1
	/* 10*/ "(prefix/rex.rxb)",                 // Count: 1
	/* 11*/ "(prefix/rex.w)",                   // Count: 1
	/* 12*/ "(prefix/rex.wb)",                  // Count: 1
	/* 13*/ "(prefix/rex.wr)",                  // Count: 1
	/* 14*/ "(prefix/rex.wrb)",                 // Count: 1
	/* 15*/ "(prefix/rex.wrx)",                 // Count: 1
	/* 16*/ "(prefix/rex.wrxb)",                // Count: 1
	/* 17*/ "(prefix/rex.wx)",                  // Count: 1
	/* 18*/ "(prefix/rex.wxb)",                 // Count: 1
	/* 19*/ "(prefix/rex.x)",                   // Count: 1
	/* 20*/ "(prefix/rex.xb)",                  // Count: 1
	/* 21*/ "(prefix/seg=cs)",                  // Count: 1
	/* 22*/ "(prefix/seg=ds)",                  // Count: 1
	/* 23*/ "(prefix/seg=es)",                  // Count: 1
	/* 24*/ "(prefix/seg=fs)",                  // Count: 1
	/* 25*/ "(prefix/seg=gs)",                  // Count: 1
	/* 26*/ "(prefix/seg=ss)",                  // Count: 1
	/* 27*/ "(prefix/vex+1byte)",               // Count: 1
	/* 28*/ "(prefix/vex+2byte)",               // Count: 1
	/* 29*/ "aaa",                              // Count: 1
	/* 30*/ "aad",                              // Count: 1
	/* 31*/ "aam",                              // Count: 1
	/* 32*/ "aas",                              // Count: 1
	/* 33*/ "adc",                              // Count: 1
	/* 34*/ "adcx",                             // Count: 1
	/* 35*/ "add",                              // Count: 1
	/* 36*/ "adox",                             // Count: 1
	/* 37*/ "and",                              // Count: 1
	/* 38*/ "andn",                             // Count: 1
	/* 39*/ "arpl",                             // Count: 1
	/* 40*/ "bextr",                            // Count: 1
	/* 41*/ "blendvpd",                         // Count: 1
	/* 42*/ "blendvps",                         // Count: 1
	/* 43*/ "blsi",                             // Count: 1
	/* 44*/ "blsmsk",                           // Count: 1
	/* 45*/ "blsr",                             // Count: 1
	/* 46*/ "bound",                            // Count: 1
	/* 47*/ "bsf",                              // Count: 1
	/* 48*/ "bsr",                              // Count: 1
	/* 49*/ "bswap",                            // Count: 1
	/* 50*/ "bt",                               // Count: 1
	/* 51*/ "btc",                              // Count: 1
	/* 52*/ "btr",                              // Count: 1
	/* 53*/ "bts",                              // Count: 1
	/* 54*/ "bzhi",                             // Count: 1
	/* 55*/ "call",                             // Count: 1
	/* 56*/ "cbw",                              // Count: 3
	/* 57*/ "cwde",
	/* 58*/ "cdqe",
	/* 59*/ "clac",                             // Count: 1
	/* 60*/ "clc",                              // Count: 1
	/* 61*/ "cld",                              // Count: 1
	/* 62*/ "clflush",                          // Count: 1
	/* 63*/ "cli",                              // Count: 1
	/* 64*/ "clts",                             // Count: 1
	/* 65*/ "cmc",                              // Count: 1
	/* 66*/ "cmova",                            // Count: 2
	/* 67*/ "cmovnbe",
	/* 68*/ "cmovae",                           // Count: 3
	/* 69*/ "cmovnb",
	/* 70*/ "cmovnc",
	/* 71*/ "cmovb",                            // Count: 3
	/* 72*/ "cmovc",
	/* 73*/ "cmovnae",
	/* 74*/ "cmovbe",                           // Count: 2
	/* 75*/ "cmovna",
	/* 76*/ "cmove",                            // Count: 2
	/* 77*/ "cmovz",
	/* 78*/ "cmovl",                            // Count: 2
	/* 79*/ "cmovnge",
	/* 80*/ "cmovle",                           // Count: 2
	/* 81*/ "cmovng",
	/* 82*/ "cmovne",                           // Count: 2
	/* 83*/ "cmovnz",
	/* 84*/ "cmovnl",                           // Count: 2
	/* 85*/ "cmovge",
	/* 86*/ "cmovnle",                          // Count: 2
	/* 87*/ "cmovg",
	/* 88*/ "cmovno",                           // Count: 1
	/* 89*/ "cmovnp",                           // Count: 2
	/* 90*/ "cmovpo",
	/* 91*/ "cmovns",                           // Count: 1
	/* 92*/ "cmovo",                            // Count: 1
	/* 93*/ "cmovp",                            // Count: 2
	/* 94*/ "cmovpe",
	/* 95*/ "cmovs",                            // Count: 1
	/* 96*/ "cmp",                              // Count: 1
	/* 97*/ "cmps",                             // Count: 1
	/* 98*/ "cmpxch8b",                         // Count: 1
	/* 99*/ "cmpxchg",                          // Count: 1
	/*100*/ "cmpxchg16b",                       // Count: 1
	/*101*/ "cpuid",                            // Count: 1
	/*102*/ "crc32",                            // Count: 1
	/*103*/ "cvtpd2pi",                         // Count: 1
	/*104*/ "cvtpi2pd",                         // Count: 1
	/*105*/ "cvtpi2ps",                         // Count: 1
	/*106*/ "cvtps2pi",                         // Count: 1
	/*107*/ "cvttpd2pi",                        // Count: 1
	/*108*/ "cvttps2pi",                        // Count: 1
	/*109*/ "cwd",                              // Count: 3
	/*110*/ "cdq",
	/*111*/ "cqo",
	/*112*/ "daa",                              // Count: 1
	/*113*/ "das",                              // Count: 1
	/*114*/ "dec",                              // Count: 1
	/*115*/ "div",                              // Count: 1
	/*116*/ "emms",                             // Count: 1
	/*117*/ "enter",                            // Count: 1
	/*118*/ "fwait",                            // Count: 2
	/*119*/ "wait",
	/*120*/ "fxrstor",                          // Count: 1
	/*121*/ "fxsave",                           // Count: 1
	/*122*/ "getsec",                           // Count: 1
	/*123*/ "hlt",                              // Count: 1
	/*124*/ "idiv",                             // Count: 1
	/*125*/ "imul",                             // Count: 1
	/*126*/ "in",                               // Count: 1
	/*127*/ "inc",                              // Count: 1
	/*128*/ "ins",                              // Count: 1
	/*129*/ "int",                              // Count: 1
	/*130*/ "int3",                             // Count: 1
	/*131*/ "into",                             // Count: 1
	/*132*/ "invd",                             // Count: 1
	/*133*/ "invept",                           // Count: 1
	/*134*/ "invlpg",                           // Count: 1
	/*135*/ "invpcid",                          // Count: 1
	/*136*/ "invvpid",                          // Count: 1
	/*137*/ "iret",                             // Count: 1
	/*138*/ "ja",                               // Count: 2
	/*139*/ "jnbe",
	/*140*/ "jae",                              // Count: 3
	/*141*/ "jnb",
	/*142*/ "jnc",
	/*143*/ "jb",                               // Count: 3
	/*144*/ "jnae",
	/*145*/ "jc",
	/*146*/ "jb",                               // Count: 2
	/*147*/ "jcnae",
	/*148*/ "jbe",                              // Count: 2
	/*149*/ "jna",
	/*150*/ "je",                               // Count: 2
	/*151*/ "jz",
	/*152*/ "jl",                               // Count: 2
	/*153*/ "jnge",
	/*154*/ "jle",                              // Count: 2
	/*155*/ "jng",
	/*156*/ "jmp",                              // Count: 1
	/*157*/ "jmpe",                             // Count: 1
	/*158*/ "jnb",                              // Count: 3
	/*159*/ "jae",
	/*160*/ "jnc",
	/*161*/ "jnbe",                             // Count: 2
	/*162*/ "ja",
	/*163*/ "jne",                              // Count: 2
	/*164*/ "jnz",
	/*165*/ "jnl",                              // Count: 2
	/*166*/ "jge",
	/*167*/ "jnle",                             // Count: 2
	/*168*/ "jg",
	/*169*/ "jno",                              // Count: 1
	/*170*/ "jnp",                              // Count: 2
	/*171*/ "jpo",
	/*172*/ "jns",                              // Count: 1
	/*173*/ "jnz",                              // Count: 2
	/*174*/ "jne",
	/*175*/ "jo",                               // Count: 1
	/*176*/ "jp",                               // Count: 2
	/*177*/ "jpe",
	/*178*/ "jrcxz",                            // Count: 1
	/*179*/ "js",                               // Count: 1
	/*180*/ "jz",                               // Count: 2
	/*181*/ "je",
	/*182*/ "lahf",                             // Count: 1
	/*183*/ "lar",                              // Count: 1
	/*184*/ "ldmxcsr",                          // Count: 1
	/*185*/ "lds",                              // Count: 1
	/*186*/ "lea",                              // Count: 1
	/*187*/ "leave",                            // Count: 1
	/*188*/ "les",                              // Count: 1
	/*189*/ "lfence",                           // Count: 1
	/*190*/ "lfs",                              // Count: 1
	/*191*/ "lgdt",                             // Count: 1
	/*192*/ "lgs",                              // Count: 1
	/*193*/ "lidt",                             // Count: 1
	/*194*/ "lldt",                             // Count: 1
	/*195*/ "lmsw",                             // Count: 1
	/*196*/ "lods",                             // Count: 1
	/*197*/ "loop",                             // Count: 1
	/*198*/ "loope",                            // Count: 2
	/*199*/ "loopz",
	/*200*/ "loopne",                           // Count: 2
	/*201*/ "loopnz",
	/*202*/ "lsl",                              // Count: 1
	/*203*/ "lss",                              // Count: 1
	/*204*/ "ltr",                              // Count: 1
	/*205*/ "lzcnt",                            // Count: 1
	/*206*/ "maskmovq",                         // Count: 1
	/*207*/ "mfence",                           // Count: 1
	/*208*/ "monitor",                          // Count: 1
	/*209*/ "mov",                              // Count: 1
	/*210*/ "movbe",                            // Count: 1
	/*211*/ "movd",                             // Count: 1
	/*212*/ "movdq2q",                          // Count: 1
	/*213*/ "movnti",                           // Count: 1
	/*214*/ "movntq",                           // Count: 1
	/*215*/ "movq",                             // Count: 1
	/*216*/ "movq2dq",                          // Count: 1
	/*217*/ "movs",                             // Count: 1
	/*218*/ "movsx",                            // Count: 1
	/*219*/ "movsxd",                           // Count: 1
	/*220*/ "movzx",                            // Count: 1
	/*221*/ "mul",                              // Count: 1
	/*222*/ "mulx",                             // Count: 1
	/*223*/ "mwait",                            // Count: 1
	/*224*/ "neg",                              // Count: 1
	/*225*/ "nop",                              // Count: 1
	/*226*/ "not",                              // Count: 1
	/*227*/ "or",                               // Count: 1
	/*228*/ "out",                              // Count: 1
	/*229*/ "outs",                             // Count: 1
	/*230*/ "pabsb",                            // Count: 1
	/*231*/ "pabsd",                            // Count: 1
	/*232*/ "pabsw",                            // Count: 1
	/*233*/ "packssdw",                         // Count: 1
	/*234*/ "packsswb",                         // Count: 1
	/*235*/ "packuswb",                         // Count: 1
	/*236*/ "paddb",                            // Count: 1
	/*237*/ "paddd",                            // Count: 1
	/*238*/ "paddq",                            // Count: 1
	/*239*/ "paddsb",                           // Count: 1
	/*240*/ "paddsw",                           // Count: 1
	/*241*/ "paddusb",                          // Count: 1
	/*242*/ "paddusw",                          // Count: 1
	/*243*/ "paddw",                            // Count: 1
	/*244*/ "palignr",                          // Count: 1
	/*245*/ "pand",                             // Count: 1
	/*246*/ "pandn",                            // Count: 1
	/*247*/ "pause",                            // Count: 1
	/*248*/ "pavgb",                            // Count: 1
	/*249*/ "pavgw",                            // Count: 1
	/*250*/ "pblendvb",                         // Count: 1
	/*251*/ "pcmpeqb",                          // Count: 1
	/*252*/ "pcmpeqd",                          // Count: 1
	/*253*/ "pcmpeqw",                          // Count: 1
	/*254*/ "pcmpgtb",                          // Count: 1
	/*255*/ "pcmpgtd",                          // Count: 1
	/*256*/ "pcmpgtw",                          // Count: 1
	/*257*/ "pdep",                             // Count: 1
	/*258*/ "pext",                             // Count: 1
	/*259*/ "pextrw",                           // Count: 1
	/*260*/ "phaddd",                           // Count: 1
	/*261*/ "phaddsw",                          // Count: 1
	/*262*/ "phaddw",                           // Count: 1
	/*263*/ "phsubd",                           // Count: 1
	/*264*/ "phsubsw",                          // Count: 1
	/*265*/ "phsubw",                           // Count: 1
	/*266*/ "pinsrw",                           // Count: 1
	/*267*/ "pmaddubsw",                        // Count: 1
	/*268*/ "pmaddwd",                          // Count: 1
	/*269*/ "pmaxsw",                           // Count: 1
	/*270*/ "pmaxub",                           // Count: 1
	/*271*/ "pminsw",                           // Count: 1
	/*272*/ "pminub",                           // Count: 1
	/*273*/ "pmovmskb",                         // Count: 1
	/*274*/ "pmulhrsw",                         // Count: 1
	/*275*/ "pmulhuw",                          // Count: 1
	/*276*/ "pmulhw",                           // Count: 1
	/*277*/ "pmullw",                           // Count: 1
	/*278*/ "pmuludq",                          // Count: 1
	/*279*/ "pop",                              // Count: 1
	/*280*/ "popa",                             // Count: 2
	/*281*/ "popad",
	/*282*/ "popcnt",                           // Count: 1
	/*283*/ "popf",                             // Count: 1
	/*284*/ "por",                              // Count: 1
	/*285*/ "prefetchnta",                      // Count: 1
	/*286*/ "prefetcht0",                       // Count: 1
	/*287*/ "prefetcht1",                       // Count: 1
	/*288*/ "prefetcht2",                       // Count: 1
	/*289*/ "prefetchw",                        // Count: 1
	/*290*/ "psadbw",                           // Count: 1
	/*291*/ "pshufb",                           // Count: 1
	/*292*/ "pshufw",                           // Count: 1
	/*293*/ "psignb",                           // Count: 1
	/*294*/ "psignd",                           // Count: 1
	/*295*/ "psignw",                           // Count: 1
	/*296*/ "pslld",                            // Count: 1
	/*297*/ "psllq",                            // Count: 1
	/*298*/ "psllw",                            // Count: 1
	/*299*/ "psrad",                            // Count: 1
	/*300*/ "psraw",                            // Count: 1
	/*301*/ "psrld",                            // Count: 1
	/*302*/ "psrlq",                            // Count: 1
	/*303*/ "psrlw",                            // Count: 1
	/*304*/ "psubb",                            // Count: 1
	/*305*/ "psubd",                            // Count: 1
	/*306*/ "psubq",                            // Count: 1
	/*307*/ "psubsb",                           // Count: 1
	/*308*/ "psubsw",                           // Count: 1
	/*309*/ "psubusb",                          // Count: 1
	/*310*/ "psubusw",                          // Count: 1
	/*311*/ "psubw",                            // Count: 1
	/*312*/ "punpckhbw",                        // Count: 1
	/*313*/ "punpckhdq",                        // Count: 1
	/*314*/ "punpckhwd",                        // Count: 1
	/*315*/ "punpcklbw",                        // Count: 1
	/*316*/ "punpckldq",                        // Count: 1
	/*317*/ "punpcklwd",                        // Count: 1
	/*318*/ "push",                             // Count: 1
	/*319*/ "pusha",                            // Count: 2
	/*320*/ "pushad",
	/*321*/ "pushf",                            // Count: 1
	/*322*/ "pxor",                             // Count: 1
	/*323*/ "rcl",                              // Count: 1
	/*324*/ "rcr",                              // Count: 1
	/*325*/ "rdfsbase",                         // Count: 1
	/*326*/ "rdgsbase",                         // Count: 1
	/*327*/ "rdmsr",                            // Count: 1
	/*328*/ "rdpmc",                            // Count: 1
	/*329*/ "rdrand",                           // Count: 1
	/*330*/ "rdseed",                           // Count: 1
	/*331*/ "rdtsc",                            // Count: 1
	/*332*/ "rdtscp",                           // Count: 1
	/*333*/ "ret",                              // Count: 1
	/*334*/ "rol",                              // Count: 1
	/*335*/ "ror",                              // Count: 1
	/*336*/ "rorx",                             // Count: 1
	/*337*/ "rsm",                              // Count: 1
	/*338*/ "sahf",                             // Count: 1
	/*339*/ "sar",                              // Count: 1
	/*340*/ "sarx",                             // Count: 1
	/*341*/ "sbb",                              // Count: 1
	/*342*/ "scas",                             // Count: 1
	/*343*/ "seta",                             // Count: 2
	/*344*/ "setnbe",
	/*345*/ "setae",                            // Count: 3
	/*346*/ "setnb",
	/*347*/ "setnc",
	/*348*/ "setb",                             // Count: 3
	/*349*/ "setc",
	/*350*/ "setnae",
	/*351*/ "setbe",                            // Count: 2
	/*352*/ "setna",
	/*353*/ "sete",                             // Count: 2
	/*354*/ "setz",
	/*355*/ "setl",                             // Count: 2
	/*356*/ "setnge",
	/*357*/ "setle",                            // Count: 2
	/*358*/ "setng",
	/*359*/ "setne",                            // Count: 2
	/*360*/ "setnz",
	/*361*/ "setnl",                            // Count: 2
	/*362*/ "setge",
	/*363*/ "setnle",                           // Count: 2
	/*364*/ "setg",
	/*365*/ "setno",                            // Count: 1
	/*366*/ "setnp",                            // Count: 2
	/*367*/ "setpo",
	/*368*/ "setns",                            // Count: 1
	/*369*/ "seto",                             // Count: 1
	/*370*/ "setp",                             // Count: 2
	/*371*/ "setpe",
	/*372*/ "sets",                             // Count: 1
	/*373*/ "sfence",                           // Count: 1
	/*374*/ "sgdt",                             // Count: 1
	/*375*/ "shl",                              // Count: 2
	/*376*/ "sal",
	/*377*/ "shld",                             // Count: 1
	/*378*/ "shlx",                             // Count: 1
	/*379*/ "shr",                              // Count: 1
	/*380*/ "shrd",                             // Count: 1
	/*381*/ "shrx",                             // Count: 1
	/*382*/ "sidt",                             // Count: 1
	/*383*/ "sldt",                             // Count: 1
	/*384*/ "smsw",                             // Count: 1
	/*385*/ "stac",                             // Count: 1
	/*386*/ "stc",                              // Count: 1
	/*387*/ "std",                              // Count: 1
	/*388*/ "sti",                              // Count: 1
	/*389*/ "stmxcsr",                          // Count: 1
	/*390*/ "stos",                             // Count: 1
	/*391*/ "str",                              // Count: 1
	/*392*/ "sub",                              // Count: 1
	/*393*/ "swapgs",                           // Count: 1
	/*394*/ "syscall",                          // Count: 1
	/*395*/ "sysenter",                         // Count: 1
	/*396*/ "sysexit",                          // Count: 1
	/*397*/ "sysret",                           // Count: 1
	/*398*/ "test",                             // Count: 1
	/*399*/ "tzcnt",                            // Count: 1
	/*400*/ "ud2",                              // Count: 1
	/*401*/ "vaddpd",                           // Count: 1
	/*402*/ "vaddps",                           // Count: 1
	/*403*/ "vaddsd",                           // Count: 1
	/*404*/ "vaddss",                           // Count: 1
	/*405*/ "vaddsubpd",                        // Count: 1
	/*406*/ "vaddsubps",                        // Count: 1
	/*407*/ "vaesdec",                          // Count: 1
	/*408*/ "vaesdeclast",                      // Count: 1
	/*409*/ "vaesenc",                          // Count: 1
	/*410*/ "vaesenclast",                      // Count: 1
	/*411*/ "vaesimc",                          // Count: 1
	/*412*/ "vaeskeygen",                       // Count: 1
	/*413*/ "vandnpd",                          // Count: 1
	/*414*/ "vandnps",                          // Count: 1
	/*415*/ "vandpd",                           // Count: 1
	/*416*/ "vandps",                           // Count: 1
	/*417*/ "vblendpd",                         // Count: 1
	/*418*/ "vblendps",                         // Count: 1
	/*419*/ "vblendvpd",                        // Count: 1
	/*420*/ "vblendvps",                        // Count: 1
	/*421*/ "vbroadcastf128",                   // Count: 1
	/*422*/ "vbroadcasti128",                   // Count: 1
	/*423*/ "vbroadcastsd",                     // Count: 1
	/*424*/ "vbroadcastss",                     // Count: 1
	/*425*/ "vcmppd",                           // Count: 1
	/*426*/ "vcmpps",                           // Count: 1
	/*427*/ "vcmpsd",                           // Count: 1
	/*428*/ "vcmpss",                           // Count: 1
	/*429*/ "vcomisd",                          // Count: 1
	/*430*/ "vcomiss",                          // Count: 1
	/*431*/ "vcvtdq2pd",                        // Count: 1
	/*432*/ "vcvtdq2ps",                        // Count: 1
	/*433*/ "vcvtpd2dq",                        // Count: 1
	/*434*/ "vcvtpd2ps",                        // Count: 1
	/*435*/ "vcvtph2ps",                        // Count: 1
	/*436*/ "vcvtps2dq",                        // Count: 1
	/*437*/ "vcvtps2pd",                        // Count: 1
	/*438*/ "vcvtps2ph",                        // Count: 1
	/*439*/ "vcvtsd2si",                        // Count: 1
	/*440*/ "vcvtsd2ss",                        // Count: 1
	/*441*/ "vcvtsi2sd",                        // Count: 1
	/*442*/ "vcvtsi2ss",                        // Count: 1
	/*443*/ "vcvtss2sd",                        // Count: 1
	/*444*/ "vcvtss2si",                        // Count: 1
	/*445*/ "vcvttpd2dq",                       // Count: 1
	/*446*/ "vcvttps2dq",                       // Count: 1
	/*447*/ "vcvttsd2si",                       // Count: 1
	/*448*/ "vcvttss2si",                       // Count: 1
	/*449*/ "vdivpd",                           // Count: 1
	/*450*/ "vdivps",                           // Count: 1
	/*451*/ "vdivsd",                           // Count: 1
	/*452*/ "vdivss",                           // Count: 1
	/*453*/ "vdppd",                            // Count: 1
	/*454*/ "vdpps",                            // Count: 1
	/*455*/ "verr",                             // Count: 1
	/*456*/ "verw",                             // Count: 1
	/*457*/ "vextractf128",                     // Count: 1
	/*458*/ "vextracti128",                     // Count: 1
	/*459*/ "vextractps",                       // Count: 1
	/*460*/ "vfmadd132ps",                      // Count: 1
	/*461*/ "vfmadd132ss",                      // Count: 1
	/*462*/ "vfmadd213ps",                      // Count: 1
	/*463*/ "vfmadd213ss",                      // Count: 1
	/*464*/ "vfmadd231ps",                      // Count: 1
	/*465*/ "vfmadd231ss",                      // Count: 1
	/*466*/ "vfmaddsub132ps",                   // Count: 1
	/*467*/ "vfmaddsub213ps",                   // Count: 1
	/*468*/ "vfmaddsub231ps",                   // Count: 1
	/*469*/ "vfmsub132ps",                      // Count: 1
	/*470*/ "vfmsub132ss",                      // Count: 1
	/*471*/ "vfmsub213ps",                      // Count: 1
	/*472*/ "vfmsub213ss",                      // Count: 1
	/*473*/ "vfmsub231ps",                      // Count: 1
	/*474*/ "vfmsub231ss",                      // Count: 1
	/*475*/ "vfmsubadd132ps",                   // Count: 1
	/*476*/ "vfmsubadd213ps",                   // Count: 1
	/*477*/ "vfmsubadd231ps",                   // Count: 1
	/*478*/ "vfnmadd132ps",                     // Count: 1
	/*479*/ "vfnmadd132ss",                     // Count: 1
	/*480*/ "vfnmadd213ps",                     // Count: 1
	/*481*/ "vfnmadd213ss",                     // Count: 1
	/*482*/ "vfnmadd231ps",                     // Count: 1
	/*483*/ "vfnmadd231ss",                     // Count: 1
	/*484*/ "vfnmsub132ps",                     // Count: 1
	/*485*/ "vfnmsub132ss",                     // Count: 1
	/*486*/ "vfnmsub213ps",                     // Count: 1
	/*487*/ "vfnmsub213ss",                     // Count: 1
	/*488*/ "vfnmsub231ps",                     // Count: 1
	/*489*/ "vfnmsub231ss",                     // Count: 1
	/*490*/ "vgatherdd",                        // Count: 1
	/*491*/ "vgatherdps",                       // Count: 1
	/*492*/ "vgatherqd",                        // Count: 1
	/*493*/ "vgatherqps",                       // Count: 1
	/*494*/ "vhaddpd",                          // Count: 1
	/*495*/ "vhaddps",                          // Count: 1
	/*496*/ "vhsubpd",                          // Count: 1
	/*497*/ "vhsubps",                          // Count: 1
	/*498*/ "vinsertf128",                      // Count: 1
	/*499*/ "vinserti128",                      // Count: 1
	/*500*/ "vinsertps",                        // Count: 1
	/*501*/ "vlddqu",                           // Count: 1
	/*502*/ "vmaskmovdqu",                      // Count: 1
	/*503*/ "vmaskmovpd",                       // Count: 1
	/*504*/ "vmaskmovps",                       // Count: 1
	/*505*/ "vmaxpd",                           // Count: 1
	/*506*/ "vmaxps",                           // Count: 1
	/*507*/ "vmaxsd",                           // Count: 1
	/*508*/ "vmaxss",                           // Count: 1
	/*509*/ "vmcall",                           // Count: 1
	/*510*/ "vmclear",                          // Count: 1
	/*511*/ "vmfunc",                           // Count: 1
	/*512*/ "vminpd",                           // Count: 1
	/*513*/ "vminps",                           // Count: 1
	/*514*/ "vminsd",                           // Count: 1
	/*515*/ "vminss",                           // Count: 1
	/*516*/ "vmlaunch",                         // Count: 1
	/*517*/ "vmovapd",                          // Count: 1
	/*518*/ "vmovaps",                          // Count: 1
	/*519*/ "vmovd",                            // Count: 1
	/*520*/ "vmovddup",                         // Count: 1
	/*521*/ "vmovdqa",                          // Count: 1
	/*522*/ "vmovdqu",                          // Count: 1
	/*523*/ "vmovhlps",                         // Count: 1
	/*524*/ "vmovhpd",                          // Count: 1
	/*525*/ "vmovhps",                          // Count: 1
	/*526*/ "vmovlhps",                         // Count: 1
	/*527*/ "vmovlpd",                          // Count: 1
	/*528*/ "vmovlps",                          // Count: 1
	/*529*/ "vmovmskpd",                        // Count: 1
	/*530*/ "vmovmskps",                        // Count: 1
	/*531*/ "vmovntdq",                         // Count: 1
	/*532*/ "vmovntdqa",                        // Count: 1
	/*533*/ "vmovntpd",                         // Count: 1
	/*534*/ "vmovntps",                         // Count: 1
	/*535*/ "vmovq",                            // Count: 1
	/*536*/ "vmovsd",                           // Count: 1
	/*537*/ "vmovshdup",                        // Count: 1
	/*538*/ "vmovsldup",                        // Count: 1
	/*539*/ "vmovss",                           // Count: 1
	/*540*/ "vmovupd",                          // Count: 1
	/*541*/ "vmovups",                          // Count: 1
	/*542*/ "vmpsadbw",                         // Count: 1
	/*543*/ "vmptrld",                          // Count: 1
	/*544*/ "vmptrst",                          // Count: 1
	/*545*/ "vmread",                           // Count: 1
	/*546*/ "vmresume",                         // Count: 1
	/*547*/ "vmulpd",                           // Count: 1
	/*548*/ "vmulps",                           // Count: 1
	/*549*/ "vmulsd",                           // Count: 1
	/*550*/ "vmulss",                           // Count: 1
	/*551*/ "vmwrite",                          // Count: 1
	/*552*/ "vmxoff",                           // Count: 1
	/*553*/ "vmxon",                            // Count: 1
	/*554*/ "vorpd",                            // Count: 1
	/*555*/ "vorps",                            // Count: 1
	/*556*/ "vpabsb",                           // Count: 1
	/*557*/ "vpabsd",                           // Count: 1
	/*558*/ "vpabsw",                           // Count: 1
	/*559*/ "vpackssdw",                        // Count: 1
	/*560*/ "vpacksswb",                        // Count: 1
	/*561*/ "vpackusdw",                        // Count: 1
	/*562*/ "vpackuswb",                        // Count: 1
	/*563*/ "vpaddb",                           // Count: 1
	/*564*/ "vpaddd",                           // Count: 1
	/*565*/ "vpaddq",                           // Count: 1
	/*566*/ "vpaddsb",                          // Count: 1
	/*567*/ "vpaddsw",                          // Count: 1
	/*568*/ "vpaddusb",                         // Count: 1
	/*569*/ "vpaddusw",                         // Count: 1
	/*570*/ "vpaddw",                           // Count: 1
	/*571*/ "vpalignr",                         // Count: 1
	/*572*/ "vpand",                            // Count: 1
	/*573*/ "vpandn",                           // Count: 1
	/*574*/ "vpavgb",                           // Count: 1
	/*575*/ "vpavgw",                           // Count: 1
	/*576*/ "vpblendd",                         // Count: 1
	/*577*/ "vpblendvb",                        // Count: 1
	/*578*/ "vpblendw",                         // Count: 1
	/*579*/ "vpbroadcastb",                     // Count: 1
	/*580*/ "vpbroadcastd",                     // Count: 1
	/*581*/ "vpbroadcastq",                     // Count: 1
	/*582*/ "vpbroadcastw",                     // Count: 1
	/*583*/ "vpclmulqdq",                       // Count: 1
	/*584*/ "vpcmpeqb",                         // Count: 1
	/*585*/ "vpcmpeqd",                         // Count: 1
	/*586*/ "vpcmpeqq",                         // Count: 1
	/*587*/ "vpcmpeqw",                         // Count: 1
	/*588*/ "vpcmpestri",                       // Count: 1
	/*589*/ "vpcmpestrm",                       // Count: 1
	/*590*/ "vpcmpgtb",                         // Count: 1
	/*591*/ "vpcmpgtd",                         // Count: 1
	/*592*/ "vpcmpgtq",                         // Count: 1
	/*593*/ "vpcmpgtw",                         // Count: 1
	/*594*/ "vpcmpistri",                       // Count: 1
	/*595*/ "vpcmpistrm",                       // Count: 1
	/*596*/ "vperm2f128",                       // Count: 1
	/*597*/ "vperm2i128",                       // Count: 1
	/*598*/ "vpermd",                           // Count: 1
	/*599*/ "vpermilpd",                        // Count: 1
	/*600*/ "vpermilps",                        // Count: 1
	/*601*/ "vpermpd",                          // Count: 1
	/*602*/ "vpermps",                          // Count: 1
	/*603*/ "vpermq",                           // Count: 1
	/*604*/ "vpextrb",                          // Count: 1
	/*605*/ "vpextrd",                          // Count: 1
	/*606*/ "vpextrw",                          // Count: 1
	/*607*/ "vphaddd",                          // Count: 1
	/*608*/ "vphaddsw",                         // Count: 1
	/*609*/ "vphaddw",                          // Count: 1
	/*610*/ "vphminposuw",                      // Count: 1
	/*611*/ "vphsubd",                          // Count: 1
	/*612*/ "vphsubsw",                         // Count: 1
	/*613*/ "vphsubw",                          // Count: 1
	/*614*/ "vpinsrb",                          // Count: 1
	/*615*/ "vpinsrd",                          // Count: 1
	/*616*/ "vpinsrw",                          // Count: 1
	/*617*/ "vpmaddubsw",                       // Count: 1
	/*618*/ "vpmaddwd",                         // Count: 1
	/*619*/ "vpmaskmovd",                       // Count: 1
	/*620*/ "vpmaxsb",                          // Count: 1
	/*621*/ "vpmaxsd",                          // Count: 1
	/*622*/ "vpmaxsw",                          // Count: 1
	/*623*/ "vpmaxub",                          // Count: 1
	/*624*/ "vpmaxud",                          // Count: 1
	/*625*/ "vpmaxuw",                          // Count: 1
	/*626*/ "vpminsb",                          // Count: 1
	/*627*/ "vpminsd",                          // Count: 1
	/*628*/ "vpminsw",                          // Count: 1
	/*629*/ "vpminub",                          // Count: 1
	/*630*/ "vpminud",                          // Count: 1
	/*631*/ "vpminuw",                          // Count: 1
	/*632*/ "vpmovmskb",                        // Count: 1
	/*633*/ "vpmovsxbd",                        // Count: 1
	/*634*/ "vpmovsxbq",                        // Count: 1
	/*635*/ "vpmovsxbw",                        // Count: 1
	/*636*/ "vpmovsxdq",                        // Count: 1
	/*637*/ "vpmovsxwd",                        // Count: 1
	/*638*/ "vpmovsxwq",                        // Count: 1
	/*639*/ "vpmovzxbd",                        // Count: 1
	/*640*/ "vpmovzxbq",                        // Count: 1
	/*641*/ "vpmovzxbw",                        // Count: 1
	/*642*/ "vpmovzxdq",                        // Count: 1
	/*643*/ "vpmovzxwd",                        // Count: 1
	/*644*/ "vpmovzxwq",                        // Count: 1
	/*645*/ "vpmuldq",                          // Count: 1
	/*646*/ "vpmulhrsw",                        // Count: 1
	/*647*/ "vpmulhuw",                         // Count: 1
	/*648*/ "vpmulhw",                          // Count: 1
	/*649*/ "vpmulld",                          // Count: 1
	/*650*/ "vpmullw",                          // Count: 1
	/*651*/ "vpmuludq",                         // Count: 1
	/*652*/ "vpor",                             // Count: 1
	/*653*/ "vpsadbw",                          // Count: 1
	/*654*/ "vpshufb",                          // Count: 1
	/*655*/ "vpshufd",                          // Count: 1
	/*656*/ "vpshufhw",                         // Count: 1
	/*657*/ "vpshuflw",                         // Count: 1
	/*658*/ "vpsignb",                          // Count: 1
	/*659*/ "vpsignd",                          // Count: 1
	/*660*/ "vpsignw",                          // Count: 1
	/*661*/ "vpslld",                           // Count: 1
	/*662*/ "vpslldq",                          // Count: 1
	/*663*/ "vpsllq",                           // Count: 1
	/*664*/ "vpsllvd",                          // Count: 1
	/*665*/ "vpsllw",                           // Count: 1
	/*666*/ "vpsrad",                           // Count: 1
	/*667*/ "vpsravd",                          // Count: 1
	/*668*/ "vpsraw",                           // Count: 1
	/*669*/ "vpsrld",                           // Count: 1
	/*670*/ "vpsrldq",                          // Count: 1
	/*671*/ "vpsrlq",                           // Count: 1
	/*672*/ "vpsrlvd",                          // Count: 1
	/*673*/ "vpsrlw",                           // Count: 1
	/*674*/ "vpsubb",                           // Count: 1
	/*675*/ "vpsubd",                           // Count: 1
	/*676*/ "vpsubq",                           // Count: 1
	/*677*/ "vpsubsb",                          // Count: 1
	/*678*/ "vpsubsw",                          // Count: 1
	/*679*/ "vpsubusb",                         // Count: 1
	/*680*/ "vpsubusw",                         // Count: 1
	/*681*/ "vpsubw",                           // Count: 1
	/*682*/ "vptest",                           // Count: 1
	/*683*/ "vpunpckhbw",                       // Count: 1
	/*684*/ "vpunpckhdq",                       // Count: 1
	/*685*/ "vpunpckhqdq",                      // Count: 1
	/*686*/ "vpunpckhwd",                       // Count: 1
	/*687*/ "vpunpcklbw",                       // Count: 1
	/*688*/ "vpunpckldq",                       // Count: 1
	/*689*/ "vpunpcklqdq",                      // Count: 1
	/*690*/ "vpunpcklwd",                       // Count: 1
	/*691*/ "vpxor",                            // Count: 1
	/*692*/ "vrcpps",                           // Count: 1
	/*693*/ "vrcpss",                           // Count: 1
	/*694*/ "vroundpd",                         // Count: 1
	/*695*/ "vroundps",                         // Count: 1
	/*696*/ "vroundsd",                         // Count: 1
	/*697*/ "vroundss",                         // Count: 1
	/*698*/ "vrsqrtps",                         // Count: 1
	/*699*/ "vrsqrtss",                         // Count: 1
	/*700*/ "vshufpd",                          // Count: 1
	/*701*/ "vshufps",                          // Count: 1
	/*702*/ "vsqrtpd",                          // Count: 1
	/*703*/ "vsqrtps",                          // Count: 1
	/*704*/ "vsqrtsd",                          // Count: 1
	/*705*/ "vsqrtss",                          // Count: 1
	/*706*/ "vsubpd",                           // Count: 1
	/*707*/ "vsubps",                           // Count: 1
	/*708*/ "vsubsd",                           // Count: 1
	/*709*/ "vsubss",                           // Count: 1
	/*710*/ "vtestpd",                          // Count: 1
	/*711*/ "vtestps",                          // Count: 1
	/*712*/ "vucomisd",                         // Count: 1
	/*713*/ "vucomiss",                         // Count: 1
	/*714*/ "vunpckhpd",                        // Count: 1
	/*715*/ "vunpckhps",                        // Count: 1
	/*716*/ "vunpcklpd",                        // Count: 1
	/*717*/ "vunpcklps",                        // Count: 1
	/*718*/ "vxorpd",                           // Count: 1
	/*719*/ "vxorps",                           // Count: 1
	/*720*/ "vzeroall",                         // Count: 1
	/*721*/ "vzeroupper",                       // Count: 1
	/*722*/ "wbinvd",                           // Count: 1
	/*723*/ "wrfsbase",                         // Count: 1
	/*724*/ "wrgsbase",                         // Count: 1
	/*725*/ "wrmsr",                            // Count: 1
	/*726*/ "xabort",                           // Count: 1
	/*727*/ "xadd",                             // Count: 1
	/*728*/ "xbegin",                           // Count: 1
	/*729*/ "xchg",                             // Count: 1
	/*730*/ "xend",                             // Count: 1
	/*731*/ "xgetbv",                           // Count: 1
	/*732*/ "xlat",                             // Count: 1
	/*733*/ "xor",                              // Count: 1
	/*734*/ "xrstor",                           // Count: 1
	/*735*/ "xsave",                            // Count: 1
	/*736*/ "xsaveopt",                         // Count: 1
	/*737*/ "xsetbv",                           // Count: 1
	/*738*/ "xtest",                            // Count: 1
};

const unsigned char OperandGroup1[] =
{
	/*  0*/ 28,                                 // ES
	/*  1*/ 108,                                // SS
	/*  2*/ 19,                                 // eAX
	/*  3*/ 23,                                 // eCX
	/*  4*/ 26,                                 // eDX
	/*  5*/ 22,                                 // eBX
	/*  6*/ 30,                                 // eSP
	/*  7*/ 21,                                 // eBP
	/*  8*/ 29,                                 // eSI
	/*  9*/ 25,                                 // eDI
	/* 10*/ 84,                                 // rAX/r8
	/* 11*/ 90,                                 // rCX/r9
	/* 12*/ 98,                                 // rDX/r10
	/* 13*/ 88,                                 // rBX/r11
	/* 14*/ 102,                                // rSP/r12
	/* 15*/ 86,                                 // rBP/r13
	/* 16*/ 100,                                // rSI/r14
	/* 17*/ 95,                                 // rDI/r15
	/* 18*/ 56,                                 // Jb
	/* 19*/ 54,                                 // Iw
	/* 20*/ 51,                                 // Ib
	/* 21*/ 20,                                 // Eb
	/* 22*/ 31,                                 // Ev
	/* 23*/ 13,                                 // CS
	/* 24*/ 17,                                 // DS
	/* 25*/ 55,                                 // Iz
	/* 26*/ 5,                                  // Ap
	/* 27*/ 35,                                 // Fv
	/* 28*/ 57,                                 // Jz
	/* 29*/ 34,                                 // FS
	/* 30*/ 38,                                 // GS
	/* 31*/ 83,                                 // RAX/EAX/R8/R8D
	/* 32*/ 89,                                 // RCX/ECX/R9/R9D
	/* 33*/ 97,                                 // RDX/EDX/R10/R10D
	/* 34*/ 87,                                 // RBX/EBX/R11/R11D
	/* 35*/ 101,                                // RSP/ESP/R12/R12D
	/* 36*/ 85,                                 // RBP/EBP/R13/R13D
	/* 37*/ 99,                                 // RSI/ESI/R14/R14D
	/* 38*/ 94,                                 // RDI/EDI/R15/R15D
	/* 39*/ 52,                                 // Ib/Iz
	/* 40*/ 4,                                  // AL/rAX
	/* 41*/ 27,                                 // Ep
	/* 42*/ 63,                                 // Mp
	/* 43*/ 104,                                // Rv/Mw
	/* 44*/ 32,                                 // Ew
	/* 45*/ 67,                                 // Ms
	/* 46*/ 69,                                 // Mw/Rv
	/* 47*/ 61,                                 // Mb
	/* 48*/ 66,                                 // Mq
	/* 49*/ 62,                                 // Mdq
	/* 50*/ 103,                                // Rv
	/* 51*/ 105,                                // Ry
};
const unsigned char OperandGroup2[][2] =
{
	/*  0*/{ 20, 36, },                          // Eb, Gb
	/*  1*/{ 31, 39, },                          // Ev, Gv
	/*  2*/{ 36, 20, },                          // Gb, Eb
	/*  3*/{ 39, 31, },                          // Gv, Ev
	/*  4*/{ 2, 51, },                           // AL, Ib
	/*  5*/{ 82, 55, },                          // rAX, Iz
	/*  6*/{ 39, 60, },                          // Gv, Ma
	/*  7*/{ 32, 40, },                          // Ew, Gw
	/*  8*/{ 20, 51, },                          // Eb, Ib
	/*  9*/{ 31, 55, },                          // Ev, Iz
	/* 10*/{ 31, 51, },                          // Ev, Ib
	/* 11*/{ 81, 82, },                          // r8, rAX
	/* 12*/{ 90, 82, },                          // rCX/r9, rAX
	/* 13*/{ 98, 82, },                          // rDX/r10, rAX
	/* 14*/{ 88, 82, },                          // rBX/r11, rAX
	/* 15*/{ 102, 82, },                         // rSP/r12, rAX
	/* 16*/{ 86, 82, },                          // rBP/r13, rAX
	/* 17*/{ 100, 82, },                         // rSI/r14, rAX
	/* 18*/{ 95, 82, },                          // rDI/r15, rAX
	/* 19*/{ 2, 73, },                           // AL, Ob
	/* 20*/{ 82, 74, },                          // rAX, Ov
	/* 21*/{ 73, 2, },                           // Ob, AL
	/* 22*/{ 74, 82, },                          // Ov, rAX
	/* 23*/{ 140, 137, },                        // Yb, Xb
	/* 24*/{ 141, 138, },                        // Yv, Xv
	/* 25*/{ 137, 140, },                        // Xb, Yb
	/* 26*/{ 138, 141, },                        // Xv, Yv
	/* 27*/{ 3, 51, },                           // AL/R8L, Ib
	/* 28*/{ 12, 51, },                          // CL/R9L, Ib
	/* 29*/{ 16, 51, },                          // DL/R10L, Ib
	/* 30*/{ 7, 51, },                           // BL/R11L, Ib
	/* 31*/{ 1, 51, },                           // AH/R12L, Ib
	/* 32*/{ 10, 51, },                          // CH/R13L, Ib
	/* 33*/{ 15, 51, },                          // DH/R14L, Ib
	/* 34*/{ 6, 51, },                           // BH/R15L, Ib
	/* 35*/{ 42, 63, },                          // Gz, Mp
	/* 36*/{ 20, 0, },                           // Eb, 1
	/* 37*/{ 31, 0, },                           // Ev, 1
	/* 38*/{ 20, 11, },                          // Eb, CL
	/* 39*/{ 31, 11, },                          // Ev, CL
	/* 40*/{ 19, 51, },                          // eAX, Ib
	/* 41*/{ 51, 2, },                           // Ib, AL
	/* 42*/{ 51, 19, },                          // Ib, eAX
	/* 43*/{ 140, 18, },                         // Yb, DX
	/* 44*/{ 142, 18, },                         // Yz, DX
	/* 45*/{ 18, 137, },                         // DX, Xb
	/* 46*/{ 18, 139, },                         // DX, Xz
	/* 47*/{ 31, 109, },                         // Ev, Sw
	/* 48*/{ 39, 59, },                          // Gv, M
	/* 49*/{ 109, 32, },                         // Sw, Ew
	/* 50*/{ 140, 2, },                          // Yb, AL
	/* 51*/{ 141, 82, },                         // Yv, rAX
	/* 52*/{ 2, 137, },                          // AL, Xb
	/* 53*/{ 82, 138, },                         // rAX, Xv
	/* 54*/{ 2, 140, },                          // AL, Yb
	/* 55*/{ 82, 141, },                         // rAX, Yv
	/* 56*/{ 84, 53, },                          // rAX/r8, Iv
	/* 57*/{ 90, 53, },                          // rCX/r9, Iv
	/* 58*/{ 98, 53, },                          // rDX/r10, Iv
	/* 59*/{ 88, 53, },                          // rBX/r11, Iv
	/* 60*/{ 102, 53, },                         // rSP/r12, Iv
	/* 61*/{ 86, 53, },                          // rBP/r13, Iv
	/* 62*/{ 100, 53, },                         // rSI/r14, Iv
	/* 63*/{ 95, 53, },                          // rDI/r15, Iv
	/* 64*/{ 54, 51, },                          // Iw, Ib
	/* 65*/{ 2, 18, },                           // AL, DX
	/* 66*/{ 19, 18, },                          // eAX, DX
	/* 67*/{ 18, 2, },                           // DX, AL
	/* 68*/{ 18, 19, },                          // DX, eAX
	/* 69*/{ 39, 32, },                          // Gv, Ew
	/* 70*/{ 121, 131, },                        // Vps, Wps
	/* 71*/{ 131, 121, },                        // Wps, Vps
	/* 72*/{ 66, 122, },                         // Mq, Vq
	/* 73*/{ 120, 130, },                        // Vpd, Wpd
	/* 74*/{ 130, 120, },                        // Wpd, Vpd
	/* 75*/{ 126, 136, },                        // Vx, Wx
	/* 76*/{ 91, 9, },                           // Rd, Cd
	/* 77*/{ 91, 14, },                          // Rd, Dd
	/* 78*/{ 9, 91, },                           // Cd, Rd
	/* 79*/{ 14, 91, },                          // Dd, Rd
	/* 80*/{ 41, 113, },                         // Gy, Ups
	/* 81*/{ 41, 112, },                         // Gy, Upd
	/* 82*/{ 77, 78, },                          // Pq, Qd
	/* 83*/{ 77, 80, },                          // Pq, Qq
	/* 84*/{ 121, 79, },                         // Vps, Qpi
	/* 85*/{ 65, 121, },                         // Mps, Vps
	/* 86*/{ 76, 131, },                         // Ppi, Wps
	/* 87*/{ 125, 135, },                        // Vss, Wss
	/* 88*/{ 120, 79, },                         // Vpd, Qpi
	/* 89*/{ 64, 120, },                         // Mpd, Vpd
	/* 90*/{ 76, 130, },                         // Ppi, Wpd
	/* 91*/{ 79, 130, },                         // Qpi, Wpd
	/* 92*/{ 124, 134, },                        // Vsd, Wsd
	/* 93*/{ 41, 135, },                         // Gy, Wss
	/* 94*/{ 41, 134, },                         // Gy, Wsd
	/* 95*/{ 120, 131, },                        // Vpd, Wps
	/* 96*/{ 121, 129, },                        // Vps, Wdq
	/* 97*/{ 121, 130, },                        // Vps, Wpd
	/* 98*/{ 119, 131, },                        // Vdq, Wps
	/* 99*/{ 75, 33, },                          // Pd, Ey
	/*100*/{ 127, 33, },                         // Vy, Ey
	/*101*/{ 33, 41, },                          // Ey, Gy
	/*102*/{ 41, 33, },                          // Gy, Ey
	/*103*/{ 33, 75, },                          // Ey, Pd
	/*104*/{ 80, 77, },                          // Qq, Pq
	/*105*/{ 33, 127, },                         // Ey, Vy
	/*106*/{ 136, 126, },                        // Wx, Vx
	/*107*/{ 122, 132, },                        // Vq, Wq
	/*108*/{ 39, 63, },                          // Gv, Mp
	/*109*/{ 39, 20, },                          // Gv, Eb
	/*110*/{ 71, 41, },                          // My, Gy
	/*111*/{ 37, 72, },                          // Gd, Nq
	/*112*/{ 132, 122, },                        // Wq, Vq
	/*113*/{ 37, 115, },                         // Gd, Ux
	/*114*/{ 119, 72, },                         // Vdq, Nq
	/*115*/{ 77, 114, },                         // Pq, Uq
	/*116*/{ 66, 77, },                          // Mq, Pq
	/*117*/{ 126, 130, },                        // Vx, Wpd
	/*118*/{ 70, 126, },                         // Mx, Vx
	/*119*/{ 77, 72, },                          // Pq, Nq
	/*120*/{ 119, 110, },                        // Vdq, Udq
	/*121*/{ 126, 70, },                         // Vx, Mx
	/*122*/{ 119, 129, },                        // Vdq, Wdq
	/*123*/{ 126, 117, },                        // Vx, Ux/Mq
	/*124*/{ 126, 116, },                        // Vx, Ux/Md
	/*125*/{ 126, 118, },                        // Vx, Ux/Mw
	/*126*/{ 41, 62, },                          // Gy, Mdq
	/*127*/{ 41, 71, },                          // Gy, My
	/*128*/{ 40, 68, },                          // Gw, Mw
	/*129*/{ 68, 40, },                          // Mw, Gw
	/*130*/{ 37, 20, },                          // Gd, Eb
	/*131*/{ 37, 33, },                          // Gd, Ey
	/*132*/{ 37, 32, },                          // Gd, Ew
	/*133*/{ 126, 128, },                        // Vx, Wd
	/*134*/{ 123, 132, },                        // Vqq, Wq
	/*135*/{ 123, 62, },                         // Vqq, Mdq
	/*136*/{ 72, 51, },                          // Nq, Ib
	/*137*/{ 8, 33, },                           // By, Ey
};
const unsigned char OperandGroup3[][3] =
{
	/*  0*/{ 39, 31, 55, },                      // Gv, Ev, Iz
	/*  1*/{ 39, 31, 51, },                      // Gv, Ev, Ib
	/*  2*/{ 122, 46, 66, },                     // Vq, Hq, Mq
	/*  3*/{ 122, 46, 114, },                    // Vq, Hq, Uq
	/*  4*/{ 126, 50, 136, },                    // Vx, Hx, Wx
	/*  5*/{ 119, 46, 66, },                     // Vdq, Hq, Mq
	/*  6*/{ 119, 46, 114, },                    // Vdq, Hq, Uq
	/*  7*/{ 126, 50, 135, },                    // Vx, Hx, Wss
	/*  8*/{ 135, 50, 125, },                    // Wss, Hx, Vss
	/*  9*/{ 126, 50, 134, },                    // Vx, Hx, Wsd
	/* 10*/{ 134, 50, 124, },                    // Wsd, Hx, Vsd
	/* 11*/{ 121, 45, 131, },                    // Vps, Hps, Wps
	/* 12*/{ 120, 44, 130, },                    // Vpd, Hpd, Wpd
	/* 13*/{ 125, 49, 135, },                    // Vss, Hss, Wss
	/* 14*/{ 124, 48, 134, },                    // Vsd, Hsd, Wsd
	/* 15*/{ 77, 80, 51, },                      // Pq, Qq, Ib
	/* 16*/{ 126, 136, 51, },                    // Vx, Wx, Ib
	/* 17*/{ 125, 49, 33, },                     // Vss, Hss, Ey
	/* 18*/{ 124, 48, 33, },                     // Vsd, Hsd, Ey
	/* 19*/{ 124, 50, 135, },                    // Vsd, Hx, Wss
	/* 20*/{ 125, 50, 134, },                    // Vss, Hx, Wsd
	/* 21*/{ 31, 39, 51, },                      // Ev, Gv, Ib
	/* 22*/{ 31, 39, 11, },                      // Ev, Gv, CL
	/* 23*/{ 77, 107, 51, },                     // Pq, Ry/Mw, Ib
	/* 24*/{ 37, 72, 51, },                      // Gd, Nq, Ib
	/* 25*/{ 37, 110, 51, },                     // Gd, Udq, Ib
	/* 26*/{ 123, 47, 133, },                    // Vqq, Hqq, Wqq
	/* 27*/{ 41, 8, 33, },                       // Gy, By, Ey
	/* 28*/{ 41, 33, 8, },                       // Gy, Ey, By
	/* 29*/{ 126, 50, 70, },                     // Vx, Hx, Mx
	/* 30*/{ 70, 50, 126, },                     // Mx, Hx, Vx
	/* 31*/{ 70, 126, 50, },                     // Mx, Vx, Hx
	/* 32*/{ 119, 43, 129, },                    // Vdq, Hdq, Wdq
	/* 33*/{ 123, 133, 51, },                    // Vqq, Wqq, Ib
	/* 34*/{ 92, 119, 51, },                     // Rd/Mb, Vdq, Ib
	/* 35*/{ 93, 119, 51, },                     // Rd/Mw, Vdq, Ib
	/* 36*/{ 33, 119, 51, },                     // Ey, Vdq, Ib
	/* 37*/{ 24, 119, 51, },                     // Ed, Vdq, Ib
	/* 38*/{ 119, 129, 51, },                    // Vdq, Wdq, Ib
	/* 39*/{ 41, 33, 51, },                      // Gy, Ey, Ib
	/* 40*/{ 125, 135, 51, },                    // Vss, Wss, Ib
	/* 41*/{ 124, 134, 51, },                    // Vsd, Wsd, Ib
	/* 42*/{ 129, 123, 51, },                    // Wdq, Vqq, Ib
	/* 43*/{ 136, 126, 51, },                    // Wx, Vx, Ib
	/* 44*/{ 50, 115, 51, },                     // Hx, Ux, Ib
};
const unsigned char OperandGroup4[][4] =
{
	/*  0*/{ 121, 45, 131, 51, },                // Vps, Hps, Wps, Ib
	/*  1*/{ 120, 44, 130, 51, },                // Vpd, Hpd, Wpd, Ib
	/*  2*/{ 119, 43, 107, 51, },                // Vdq, Hdq, Ry/Mw, Ib
	/*  3*/{ 125, 49, 135, 51, },                // Vss, Hss, Wss, Ib
	/*  4*/{ 124, 48, 134, 51, },                // Vsd, Hsd, Wsd, Ib
	/*  5*/{ 8, 41, 96, 33, },                   // By, Gy, rDX, Ey
	/*  6*/{ 126, 50, 136, 51, },                // Vx, Hx, Wx, Ib
	/*  7*/{ 123, 47, 133, 51, },                // Vqq, Hqq, Wqq, Ib
	/*  8*/{ 119, 43, 106, 51, },                // Vdq, Hdq, Ry/Mb, Ib
	/*  9*/{ 119, 43, 111, 51, },                // Vdq, Hdq, Udq/Md, Ib
	/* 10*/{ 119, 43, 33, 51, },                 // Vdq, Hdq, Ey, Ib
	/* 11*/{ 119, 43, 129, 51, },                // Vdq, Hdq, Wdq, Ib
	/* 12*/{ 126, 50, 136, 58, },                // Vx, Hx, Wx, Lx
};

const OpcodeData HexTable1[] =
{
	{ 0, 1 },{ 1, 1 },{ 2, 1 },{ 3, 1 },{ 4, 1 },{ 5, 1 },{ 6, 1 },{ 7, 1 },
	{ 139, 1 },{ 140, 1 },{ 141, 1 },{ 142, 1 },{ 143, 1 },{ 144, 1 },{ 145, 1 },{ 146, 1 },
	{ 8, 1 },{ 9, 1 },{ 10, 1 },{ 11, 1 },{ 12, 1 },{ 13, 1 },{ 14, 1 },{ 15, 1 },
	{ 147, 1 },{ 148, 1 },{ 149, 1 },{ 150, 1 },{ 151, 1 },{ 152, 1 },{ 153, 1 },{ 154, 1 },
	{ 16, 1 },{ 17, 1 },{ 18, 1 },{ 19, 1 },{ 20, 1 },{ 21, 1 },{ 22, 1 },{ 23, 1 },
	{ 155, 1 },{ 156, 1 },{ 157, 1 },{ 158, 1 },{ 159, 1 },{ 160, 1 },{ 161, 1 },{ 162, 1 },
	{ 24, 1 },{ 25, 1 },{ 26, 1 },{ 27, 1 },{ 28, 1 },{ 29, 1 },{ 30, 1 },{ 31, 1 },
	{ 163, 1 },{ 164, 1 },{ 165, 1 },{ 166, 1 },{ 167, 1 },{ 168, 1 },{ 169, 1 },{ 170, 1 },
	{ 32, 2 },{ 34, 2 },{ 36, 2 },{ 38, 2 },{ 40, 2 },{ 42, 2 },{ 44, 2 },{ 46, 2 },
	{ 171, 2 },{ 173, 2 },{ 175, 2 },{ 177, 2 },{ 179, 2 },{ 181, 2 },{ 183, 2 },{ 185, 2 },
	{ 48, 1 },{ 49, 1 },{ 50, 1 },{ 51, 1 },{ 52, 1 },{ 53, 1 },{ 54, 1 },{ 55, 1 },
	{ 187, 1 },{ 188, 1 },{ 189, 1 },{ 190, 1 },{ 191, 1 },{ 192, 1 },{ 193, 1 },{ 194, 1 },
	{ 56, 1 },{ 57, 1 },{ 58, 1 },{ 59, 2 },{ 61, 1 },{ 62, 1 },{ 63, 1 },{ 64, 1 },
	{ 195, 1 },{ 196, 1 },{ 197, 1 },{ 198, 1 },{ 199, 1 },{ 200, 1 },{ 201, 1 },{ 202, 1 },
	{ 65, 1 },{ 66, 1 },{ 67, 1 },{ 68, 1 },{ 69, 1 },{ 70, 1 },{ 71, 1 },{ 72, 1 },
	{ 203, 1 },{ 204, 1 },{ 205, 1 },{ 206, 1 },{ 207, 1 },{ 208, 1 },{ 209, 1 },{ 210, 1 },
	{ 73, 1 },{ 74, 1 },{ 75, 1 },{ 76, 1 },{ 77, 1 },{ 78, 1 },{ 79, 1 },{ 80, 1 },
	{ 211, 1 },{ 212, 1 },{ 213, 1 },{ 214, 1 },{ 215, 1 },{ 216, 1 },{ 217, 1 },{ 218, 1 },
	{ 81, 3 },{ 84, 1 },{ 85, 1 },{ 86, 1 },{ 87, 1 },{ 88, 1 },{ 89, 1 },{ 90, 1 },
	{ 219, 1 },{ 220, 1 },{ 221, 1 },{ 222, 1 },{ 223, 1 },{ 224, 1 },{ 225, 1 },{ 226, 1 },
	{ 91, 1 },{ 92, 1 },{ 93, 1 },{ 94, 1 },{ 95, 1 },{ 96, 1 },{ 97, 1 },{ 98, 1 },
	{ 227, 1 },{ 228, 1 },{ 229, 1 },{ 230, 1 },{ 231, 1 },{ 232, 1 },{ 233, 1 },{ 234, 1 },
	{ 99, 1 },{ 100, 1 },{ 101, 1 },{ 102, 1 },{ 103, 1 },{ 104, 1 },{ 105, 1 },{ 106, 1 },
	{ 235, 1 },{ 236, 1 },{ 237, 1 },{ 238, 1 },{ 239, 1 },{ 240, 1 },{ 241, 1 },{ 242, 1 },
	{ 107, 1 },{ 108, 1 },{ 109, 1 },{ 110, 1 },{ 111, 2 },{ 113, 2 },{ 115, 1 },{ 116, 1 },
	{ 243, 1 },{ 244, 1 },{ 245, 1 },{ 246, 1 },{ 247, 1 },{ 248, 1 },{ 249, 1 },{ 250, 1 },
	{ 117, 1 },{ 118, 1 },{ 119, 1 },{ 120, 1 },{ 121, 1 },{ 122, 1 },{ 0, 0 },{ 123, 1 },
	{ 251, 1 },{ 252, 1 },{ 253, 1 },{ 254, 1 },{ 255, 1 },{ 256, 1 },{ 257, 1 },{ 258, 1 },
	{ 124, 1 },{ 125, 1 },{ 126, 1 },{ 127, 1 },{ 128, 1 },{ 129, 1 },{ 130, 1 },{ 131, 1 },
	{ 259, 1 },{ 260, 1 },{ 261, 1 },{ 262, 1 },{ 263, 1 },{ 264, 1 },{ 265, 1 },{ 266, 1 },
	{ 132, 1 },{ 0, 0 },{ 133, 1 },{ 134, 1 },{ 135, 1 },{ 136, 1 },{ 137, 1 },{ 138, 1 },
	{ 267, 1 },{ 268, 1 },{ 269, 1 },{ 270, 1 },{ 271, 1 },{ 272, 1 },{ 273, 1 },{ 274, 1 },
};

const OpcodeData HexTable2[] =
{
	{ 275, 1 },{ 276, 1 },{ 277, 1 },{ 278, 1 },{ 0, 0 },{ 279, 1 },{ 280, 1 },{ 281, 1 },
	{ 376, 1 },{ 377, 1 },{ 0, 0 },{ 378, 1 },{ 0, 0 },{ 379, 1 },{ 0, 0 },{ 0, 0 },
	{ 282, 4 },{ 286, 4 },{ 290, 5 },{ 295, 2 },{ 297, 2 },{ 299, 2 },{ 301, 4 },{ 305, 2 },
	{ 380, 1 },{ 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 },{ 381, 1 },
	{ 307, 1 },{ 308, 1 },{ 309, 1 },{ 310, 1 },{ 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 },
	{ 382, 2 },{ 384, 2 },{ 386, 4 },{ 390, 2 },{ 392, 4 },{ 396, 4 },{ 400, 2 },{ 402, 2 },
	{ 311, 1 },{ 312, 1 },{ 313, 1 },{ 314, 1 },{ 315, 1 },{ 316, 1 },{ 0, 0 },{ 317, 1 },
	{ 404, 1 },{ 0, 0 },{ 405, 1 },{ 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 },
	{ 318, 1 },{ 319, 1 },{ 320, 1 },{ 321, 1 },{ 322, 1 },{ 323, 1 },{ 324, 1 },{ 325, 1 },
	{ 406, 1 },{ 407, 1 },{ 408, 1 },{ 409, 1 },{ 410, 1 },{ 411, 1 },{ 412, 1 },{ 413, 1 },
	{ 326, 2 },{ 328, 4 },{ 332, 2 },{ 334, 2 },{ 336, 2 },{ 338, 2 },{ 340, 2 },{ 342, 2 },
	{ 414, 4 },{ 418, 4 },{ 422, 4 },{ 426, 3 },{ 429, 4 },{ 433, 4 },{ 437, 4 },{ 441, 4 },
	{ 344, 2 },{ 346, 2 },{ 348, 2 },{ 350, 2 },{ 352, 2 },{ 354, 2 },{ 356, 2 },{ 358, 2 },
	{ 445, 2 },{ 447, 2 },{ 449, 2 },{ 451, 2 },{ 458, 1 },{ 459, 1 },{ 453, 2 },{ 455, 3 },
	{ 360, 4 },{ 364, 1 },{ 365, 1 },{ 366, 1 },{ 367, 2 },{ 369, 2 },{ 371, 2 },{ 373, 3 },
	{ 460, 1 },{ 461, 1 },{ 0, 0 },{ 0, 0 },{ 468, 2 },{ 470, 2 },{ 462, 3 },{ 465, 3 },
	{ 472, 1 },{ 473, 1 },{ 474, 1 },{ 475, 1 },{ 476, 1 },{ 477, 1 },{ 478, 1 },{ 479, 1 },
	{ 565, 1 },{ 566, 1 },{ 567, 1 },{ 568, 1 },{ 569, 1 },{ 570, 1 },{ 571, 1 },{ 572, 1 },
	{ 480, 1 },{ 481, 1 },{ 482, 1 },{ 483, 1 },{ 484, 1 },{ 485, 1 },{ 486, 1 },{ 487, 1 },
	{ 573, 1 },{ 574, 1 },{ 575, 1 },{ 576, 1 },{ 577, 1 },{ 578, 1 },{ 579, 1 },{ 580, 1 },
	{ 488, 1 },{ 489, 1 },{ 490, 1 },{ 491, 1 },{ 492, 1 },{ 493, 1 },{ 0, 0 },{ 0, 0 },
	{ 581, 1 },{ 582, 1 },{ 583, 1 },{ 584, 1 },{ 585, 1 },{ 586, 1 },{ 587, 1 },{ 588, 1 },
	{ 494, 1 },{ 495, 1 },{ 496, 1 },{ 497, 1 },{ 498, 1 },{ 499, 1 },{ 500, 1 },{ 501, 1 },
	{ 589, 2 },{ 591, 1 },{ 592, 1 },{ 593, 1 },{ 594, 2 },{ 596, 2 },{ 598, 1 },{ 599, 1 },
	{ 502, 1 },{ 503, 1 },{ 504, 4 },{ 508, 1 },{ 509, 2 },{ 511, 2 },{ 513, 2 },{ 515, 1 },
	{ 600, 1 },{ 601, 1 },{ 602, 1 },{ 603, 1 },{ 604, 1 },{ 605, 1 },{ 606, 1 },{ 607, 1 },
	{ 528, 2 },{ 516, 2 },{ 518, 2 },{ 520, 2 },{ 522, 2 },{ 524, 2 },{ 530, 3 },{ 526, 2 },
	{ 608, 2 },{ 610, 2 },{ 612, 2 },{ 614, 2 },{ 616, 2 },{ 618, 2 },{ 620, 2 },{ 622, 2 },
	{ 533, 2 },{ 535, 2 },{ 537, 2 },{ 539, 2 },{ 541, 2 },{ 543, 2 },{ 547, 3 },{ 545, 2 },
	{ 624, 2 },{ 626, 2 },{ 628, 2 },{ 630, 2 },{ 632, 2 },{ 634, 2 },{ 636, 2 },{ 638, 2 },
	{ 564, 1 },{ 550, 2 },{ 552, 2 },{ 554, 2 },{ 556, 2 },{ 558, 2 },{ 560, 2 },{ 562, 2 },
	{ 640, 2 },{ 642, 2 },{ 644, 2 },{ 646, 2 },{ 648, 2 },{ 650, 2 },{ 652, 2 },{ 0, 0 },
};

const ZipOpcodeData HexTable3Zip_38[] =
{
	{ 654, 2, 0 },{ 656, 2, 1 },{ 658, 2, 2 },{ 660, 2, 3 },{ 662, 2, 4 },{ 664, 2, 5 },{ 666, 2, 6 },{ 668, 2, 7 },
	{ 728, 2, 8 },{ 730, 2, 9 },{ 732, 2, 10 },{ 734, 2, 11 },{ 736, 1, 12 },{ 737, 1, 13 },{ 738, 1, 14 },{ 739, 1, 15 },
	{ 670, 1, 16 },{ 671, 1, 19 },{ 672, 1, 20 },{ 673, 1, 21 },{ 674, 1, 22 },{ 675, 1, 23 },{ 746, 1, 24 },{ 747, 1, 25 },
	{ 748, 1, 26 },{ 740, 2, 28 },{ 742, 2, 29 },{ 744, 2, 30 },{ 676, 1, 32 },{ 677, 1, 33 },{ 678, 1, 34 },{ 679, 1, 35 },
	{ 680, 1, 36 },{ 681, 1, 37 },{ 749, 1, 40 },{ 750, 1, 41 },{ 751, 1, 42 },{ 752, 1, 43 },{ 753, 1, 44 },{ 754, 1, 45 },
	{ 755, 1, 46 },{ 756, 1, 47 },{ 682, 1, 48 },{ 683, 1, 49 },{ 684, 1, 50 },{ 685, 1, 51 },{ 686, 1, 52 },{ 687, 1, 53 },
	{ 688, 1, 54 },{ 689, 1, 55 },{ 757, 1, 56 },{ 758, 1, 57 },{ 759, 1, 58 },{ 760, 1, 59 },{ 761, 1, 60 },{ 762, 1, 61 },
	{ 763, 1, 62 },{ 764, 1, 63 },{ 690, 1, 64 },{ 691, 1, 65 },{ 692, 1, 69 },{ 693, 1, 70 },{ 694, 1, 71 },{ 765, 1, 88 },
	{ 766, 1, 89 },{ 767, 1, 90 },{ 768, 1, 120 },{ 769, 1, 121 },{ 695, 1, 128 },{ 696, 1, 129 },{ 697, 1, 130 },{ 770, 1, 140 },
	{ 771, 1, 142 },{ 698, 1, 144 },{ 699, 1, 145 },{ 700, 1, 146 },{ 701, 1, 147 },{ 702, 1, 150 },{ 703, 1, 151 },{ 772, 1, 152 },
	{ 773, 1, 153 },{ 774, 1, 154 },{ 775, 1, 155 },{ 776, 1, 156 },{ 777, 1, 157 },{ 778, 1, 158 },{ 779, 1, 159 },{ 704, 1, 166 },
	{ 705, 1, 167 },{ 780, 1, 168 },{ 781, 1, 169 },{ 782, 1, 170 },{ 783, 1, 171 },{ 784, 1, 172 },{ 785, 1, 173 },{ 786, 1, 174 },
	{ 787, 1, 175 },{ 706, 1, 182 },{ 707, 1, 183 },{ 788, 1, 184 },{ 789, 1, 185 },{ 790, 1, 186 },{ 791, 1, 187 },{ 792, 1, 188 },
	{ 793, 1, 189 },{ 794, 1, 190 },{ 795, 1, 191 },{ 796, 1, 219 },{ 797, 1, 220 },{ 798, 1, 221 },{ 799, 1, 222 },{ 800, 1, 223 },
	{ 708, 4, 240 },{ 712, 4, 241 },{ 716, 1, 242 },{ 717, 1, 243 },{ 718, 3, 245 },{ 725, 3, 246 },{ 721, 4, 247 },
};

const ZipOpcodeData HexTable3Zip_3A[] =
{
	{ 801, 1, 0 },{ 802, 1, 1 },{ 803, 1, 2 },{ 804, 1, 4 },{ 805, 1, 5 },{ 806, 1, 6 },{ 826, 2, 8 },{ 828, 2, 9 },
	{ 830, 1, 10 },{ 831, 1, 11 },{ 832, 1, 12 },{ 833, 2, 13 },{ 835, 1, 14 },{ 824, 2, 15 },{ 807, 1, 20 },{ 808, 1, 21 },
	{ 809, 1, 22 },{ 810, 1, 23 },{ 811, 1, 32 },{ 812, 1, 33 },{ 813, 1, 34 },{ 836, 1, 56 },{ 837, 1, 57 },{ 814, 1, 64 },
	{ 815, 1, 65 },{ 816, 1, 66 },{ 817, 1, 68 },{ 818, 1, 70 },{ 838, 1, 74 },{ 839, 1, 75 },{ 840, 1, 76 },{ 819, 1, 96 },
	{ 820, 1, 97 },{ 821, 1, 98 },{ 822, 1, 99 },{ 841, 1, 223 },{ 823, 1, 240 },
};

const Hex_Inst HexInsts[] =
{
	{ OT_Inst, 0 },                       // 0
	{ OT_Inst, 1 },                       // 1
	{ OT_Inst, 2 },                       // 2
	{ OT_Inst, 3 },                       // 3
	{ OT_Inst, 4 },                       // 4
	{ OT_Inst, 5 },                       // 5
	{ OT_Inst, 6 },                       // 6
	{ OT_Inst, 7 },                       // 7
	{ OT_Inst, 8 },                       // 8
	{ OT_Inst, 9 },                       // 9
	{ OT_Inst, 10 },                      // 10
	{ OT_Inst, 11 },                      // 11
	{ OT_Inst, 12 },                      // 12
	{ OT_Inst, 13 },                      // 13
	{ OT_Inst, 14 },                      // 14
	{ OT_Inst, 15 },                      // 15
	{ OT_Inst, 16 },                      // 16
	{ OT_Inst, 17 },                      // 17
	{ OT_Inst, 18 },                      // 18
	{ OT_Inst, 19 },                      // 19
	{ OT_Inst, 20 },                      // 20
	{ OT_Inst, 21 },                      // 21
	{ OT_Prefix, 0 },                     // 22
	{ OT_Inst, 22 },                      // 23
	{ OT_Inst, 23 },                      // 24
	{ OT_Inst, 24 },                      // 25
	{ OT_Inst, 25 },                      // 26
	{ OT_Inst, 26 },                      // 27
	{ OT_Inst, 27 },                      // 28
	{ OT_Inst, 28 },                      // 29
	{ OT_Prefix, 1 },                     // 30
	{ OT_Inst, 29 },                      // 31
	{ OT_Inst, 30 },                      // 32
	{ OT_Prefix, 2 },                     // 33
	{ OT_Inst, 31 },                      // 34
	{ OT_Prefix, 3 },                     // 35
	{ OT_Inst, 32 },                      // 36
	{ OT_Prefix, 4 },                     // 37
	{ OT_Inst, 33 },                      // 38
	{ OT_Prefix, 5 },                     // 39
	{ OT_Inst, 34 },                      // 40
	{ OT_Prefix, 6 },                     // 41
	{ OT_Inst, 35 },                      // 42
	{ OT_Prefix, 7 },                     // 43
	{ OT_Inst, 36 },                      // 44
	{ OT_Prefix, 8 },                     // 45
	{ OT_Inst, 37 },                      // 46
	{ OT_Prefix, 9 },                     // 47
	{ OT_Inst, 38 },                      // 48
	{ OT_Inst, 39 },                      // 49
	{ OT_Inst, 40 },                      // 50
	{ OT_Inst, 41 },                      // 51
	{ OT_Inst, 42 },                      // 52
	{ OT_Inst, 43 },                      // 53
	{ OT_Inst, 44 },                      // 54
	{ OT_Inst, 45 },                      // 55
	{ OT_Inst, 46 },                      // 56
	{ OT_Inst, 47 },                      // 57
	{ OT_Inst, 48 },                      // 58
	{ OT_Inst, 49 },                      // 59
	{ OT_Inst, 50 },                      // 60
	{ OT_Prefix, 10 },                    // 61
	{ OT_Prefix, 11 },                    // 62
	{ OT_Prefix, 12 },                    // 63
	{ OT_Prefix, 13 },                    // 64
	{ OT_Inst, 51 },                      // 65
	{ OT_Inst, 52 },                      // 66
	{ OT_Inst, 53 },                      // 67
	{ OT_Inst, 54 },                      // 68
	{ OT_Inst, 55 },                      // 69
	{ OT_Inst, 56 },                      // 70
	{ OT_Inst, 57 },                      // 71
	{ OT_Inst, 58 },                      // 72
	{ OT_Grp, 0 },                        // 73
	{ OT_Grp, 1 },                        // 74
	{ OT_Grp, 2 },                        // 75
	{ OT_Grp, 3 },                        // 76
	{ OT_Inst, 59 },                      // 77
	{ OT_Inst, 60 },                      // 78
	{ OT_Inst, 61 },                      // 79
	{ OT_Inst, 62 },                      // 80
	{ OT_Inst, 63 },                      // 81
	{ OT_Inst, 64 },                      // 82
	{ OT_Inst, 65 },                      // 83
	{ OT_Inst, 66 },                      // 84
	{ OT_Inst, 67 },                      // 85
	{ OT_Inst, 68 },                      // 86
	{ OT_Inst, 69 },                      // 87
	{ OT_Inst, 70 },                      // 88
	{ OT_Inst, 71 },                      // 89
	{ OT_Inst, 72 },                      // 90
	{ OT_Inst, 73 },                      // 91
	{ OT_Inst, 74 },                      // 92
	{ OT_Inst, 75 },                      // 93
	{ OT_Inst, 76 },                      // 94
	{ OT_Inst_Change, 0 },                // 95
	{ OT_Inst_Change, 1 },                // 96
	{ OT_Inst_Change, 2 },                // 97
	{ OT_Inst_Change, 3 },                // 98
	{ OT_Inst, 77 },                      // 99
	{ OT_Inst, 78 },                      // 100
	{ OT_Inst, 79 },                      // 101
	{ OT_Inst, 80 },                      // 102
	{ OT_Inst, 81 },                      // 103
	{ OT_Inst, 82 },                      // 104
	{ OT_Inst, 83 },                      // 105
	{ OT_Inst, 84 },                      // 106
	{ OT_Grp, 4 },                        // 107
	{ OT_Grp, 5 },                        // 108
	{ OT_Inst, 85 },                      // 109
	{ OT_Inst, 86 },                      // 110
	{ OT_Inst, 87 },                      // 111
	{ OT_Prefix, 14 },                    // 112
	{ OT_Inst, 88 },                      // 113
	{ OT_Prefix, 15 },                    // 114
	{ OT_Grp, 6 },                        // 115
	{ OT_Grp, 7 },                        // 116
	{ OT_Grp, 8 },                        // 117
	{ OT_Grp, 9 },                        // 118
	{ OT_Grp, 10 },                       // 119
	{ OT_Grp, 11 },                       // 120
	{ OT_Inst, 89 },                      // 121
	{ OT_Inst, 90 },                      // 122
	{ OT_Inst_Change, 4 },                // 123
	{ OT_Inst, 91 },                      // 124
	{ OT_Inst, 92 },                      // 125
	{ OT_Inst, 93 },                      // 126
	{ OT_Inst, 94 },                      // 127
	{ OT_Inst, 95 },                      // 128
	{ OT_Inst, 96 },                      // 129
	{ OT_Inst, 97 },                      // 130
	{ OT_Inst, 98 },                      // 131
	{ OT_Prefix, 16 },                    // 132
	{ OT_Prefix, 17 },                    // 133
	{ OT_Prefix, 18 },                    // 134
	{ OT_Inst, 99 },                      // 135
	{ OT_Inst, 100 },                     // 136
	{ OT_Grp, 12 },                       // 137
	{ OT_Grp, 13 },                       // 138
	{ OT_Inst, 101 },                     // 139
	{ OT_Inst, 102 },                     // 140
	{ OT_Inst, 103 },                     // 141
	{ OT_Inst, 104 },                     // 142
	{ OT_Inst, 105 },                     // 143
	{ OT_Inst, 106 },                     // 144
	{ OT_Inst, 107 },                     // 145
	{ OT_Table_0F, 0 },                   // 146
	{ OT_Inst, 108 },                     // 147
	{ OT_Inst, 109 },                     // 148
	{ OT_Inst, 110 },                     // 149
	{ OT_Inst, 111 },                     // 150
	{ OT_Inst, 112 },                     // 151
	{ OT_Inst, 113 },                     // 152
	{ OT_Inst, 114 },                     // 153
	{ OT_Inst, 115 },                     // 154
	{ OT_Inst, 116 },                     // 155
	{ OT_Inst, 117 },                     // 156
	{ OT_Inst, 118 },                     // 157
	{ OT_Inst, 119 },                     // 158
	{ OT_Inst, 120 },                     // 159
	{ OT_Inst, 121 },                     // 160
	{ OT_Prefix, 19 },                    // 161
	{ OT_Inst, 122 },                     // 162
	{ OT_Inst, 123 },                     // 163
	{ OT_Inst, 124 },                     // 164
	{ OT_Inst, 125 },                     // 165
	{ OT_Inst, 126 },                     // 166
	{ OT_Inst, 127 },                     // 167
	{ OT_Inst, 128 },                     // 168
	{ OT_Prefix, 20 },                    // 169
	{ OT_Inst, 129 },                     // 170
	{ OT_Inst, 130 },                     // 171
	{ OT_Prefix, 21 },                    // 172
	{ OT_Inst, 131 },                     // 173
	{ OT_Prefix, 22 },                    // 174
	{ OT_Inst, 132 },                     // 175
	{ OT_Prefix, 23 },                    // 176
	{ OT_Inst, 133 },                     // 177
	{ OT_Prefix, 24 },                    // 178
	{ OT_Inst, 134 },                     // 179
	{ OT_Prefix, 25 },                    // 180
	{ OT_Inst, 135 },                     // 181
	{ OT_Prefix, 26 },                    // 182
	{ OT_Inst, 136 },                     // 183
	{ OT_Prefix, 27 },                    // 184
	{ OT_Inst, 137 },                     // 185
	{ OT_Prefix, 28 },                    // 186
	{ OT_Inst, 138 },                     // 187
	{ OT_Inst, 139 },                     // 188
	{ OT_Inst, 140 },                     // 189
	{ OT_Inst, 141 },                     // 190
	{ OT_Inst, 142 },                     // 191
	{ OT_Inst, 143 },                     // 192
	{ OT_Inst, 144 },                     // 193
	{ OT_Inst, 145 },                     // 194
	{ OT_Inst, 146 },                     // 195
	{ OT_Inst, 147 },                     // 196
	{ OT_Inst, 148 },                     // 197
	{ OT_Inst, 149 },                     // 198
	{ OT_Inst_Change, 5 },                // 199
	{ OT_Inst_Change, 6 },                // 200
	{ OT_Inst_Change, 7 },                // 201
	{ OT_Inst_Change, 8 },                // 202
	{ OT_Inst, 150 },                     // 203
	{ OT_Inst, 151 },                     // 204
	{ OT_Inst, 152 },                     // 205
	{ OT_Inst, 153 },                     // 206
	{ OT_Inst, 154 },                     // 207
	{ OT_Inst, 155 },                     // 208
	{ OT_Inst, 156 },                     // 209
	{ OT_Inst, 157 },                     // 210
	{ OT_Inst, 158 },                     // 211
	{ OT_Inst, 159 },                     // 212
	{ OT_Inst, 160 },                     // 213
	{ OT_Inst, 161 },                     // 214
	{ OT_Inst, 162 },                     // 215
	{ OT_Inst, 163 },                     // 216
	{ OT_Inst, 164 },                     // 217
	{ OT_Grp, 14 },                       // 218
	{ OT_Inst, 165 },                     // 219
	{ OT_Inst, 166 },                     // 220
	{ OT_Inst, 167 },                     // 221
	{ OT_Inst, 168 },                     // 222
	{ OT_Inst_Change, 9 },                // 223
	{ OT_Inst_Change, 10 },               // 224
	{ OT_Inst, 169 },                     // 225
	{ OT_Inst, 170 },                     // 226
	{ OT_Inst, 171 },                     // 227
	{ OT_Inst, 172 },                     // 228
	{ OT_Inst_Change, 11 },               // 229
	{ OT_Inst_Change, 12 },               // 230
	{ OT_Inst_Change, 13 },               // 231
	{ OT_Inst_Change, 14 },               // 232
	{ OT_Inst_Change, 15 },               // 233
	{ OT_Inst_Change, 16 },               // 234
	{ OT_Inst, 173 },                     // 235
	{ OT_Inst, 174 },                     // 236
	{ OT_Inst, 175 },                     // 237
	{ OT_Inst, 176 },                     // 238
	{ OT_Inst, 177 },                     // 239
	{ OT_Inst, 178 },                     // 240
	{ OT_Inst, 179 },                     // 241
	{ OT_Inst, 180 },                     // 242
	{ OT_Inst, 181 },                     // 243
	{ OT_Inst, 182 },                     // 244
	{ OT_Inst, 183 },                     // 245
	{ OT_Inst, 184 },                     // 246
	{ OT_Inst, 185 },                     // 247
	{ OT_Inst, 186 },                     // 248
	{ OT_Inst, 187 },                     // 249
	{ OT_Inst_Change, 17 },               // 250
	{ OT_Esc, 0 },                        // 251
	{ OT_Esc, 0 },                        // 252
	{ OT_Esc, 0 },                        // 253
	{ OT_Esc, 0 },                        // 254
	{ OT_Esc, 0 },                        // 255
	{ OT_Esc, 0 },                        // 256
	{ OT_Esc, 0 },                        // 257
	{ OT_Esc, 0 },                        // 258
	{ OT_Inst, 188 },                     // 259
	{ OT_Inst, 189 },                     // 260
	{ OT_Inst, 190 },                     // 261
	{ OT_Inst, 191 },                     // 262
	{ OT_Inst, 192 },                     // 263
	{ OT_Inst, 193 },                     // 264
	{ OT_Inst, 194 },                     // 265
	{ OT_Inst, 195 },                     // 266
	{ OT_Inst, 196 },                     // 267
	{ OT_Inst, 197 },                     // 268
	{ OT_Inst, 198 },                     // 269
	{ OT_Inst, 199 },                     // 270
	{ OT_Inst, 200 },                     // 271
	{ OT_Inst, 201 },                     // 272
	{ OT_Grp, 15 },                       // 273
	{ OT_Grp, 16 },                       // 274
	{ OT_Grp, 17 },                       // 275
	{ OT_Grp, 18 },                       // 276
	{ OT_Inst, 202 },                     // 277
	{ OT_Inst, 203 },                     // 278
	{ OT_Inst, 204 },                     // 279
	{ OT_Inst, 205 },                     // 280
	{ OT_Inst, 206 },                     // 281
	{ OT_Inst, 207 },                     // 282
	{ OT_Inst, 208 },                     // 283
	{ OT_Inst, 209 },                     // 284
	{ OT_Inst, 210 },                     // 285
	{ OT_Inst, 211 },                     // 286
	{ OT_Inst, 212 },                     // 287
	{ OT_Inst, 213 },                     // 288
	{ OT_Inst, 214 },                     // 289
	{ OT_Inst, 215 },                     // 290
	{ OT_Inst, 216 },                     // 291
	{ OT_Inst, 217 },                     // 292
	{ OT_Inst, 218 },                     // 293
	{ OT_Inst, 219 },                     // 294
	{ OT_Inst, 220 },                     // 295
	{ OT_Inst, 221 },                     // 296
	{ OT_Inst, 222 },                     // 297
	{ OT_Inst, 223 },                     // 298
	{ OT_Inst, 224 },                     // 299
	{ OT_Inst, 225 },                     // 300
	{ OT_Inst, 226 },                     // 301
	{ OT_Inst, 227 },                     // 302
	{ OT_Inst, 228 },                     // 303
	{ OT_Inst, 229 },                     // 304
	{ OT_Inst, 230 },                     // 305
	{ OT_Inst, 231 },                     // 306
	{ OT_Inst, 232 },                     // 307
	{ OT_Inst, 233 },                     // 308
	{ OT_Inst, 234 },                     // 309
	{ OT_Inst, 235 },                     // 310
	{ OT_Inst, 236 },                     // 311
	{ OT_Inst, 237 },                     // 312
	{ OT_Inst, 238 },                     // 313
	{ OT_Inst, 239 },                     // 314
	{ OT_Inst, 240 },                     // 315
	{ OT_Inst, 241 },                     // 316
	{ OT_Inst, 242 },                     // 317
	{ OT_Inst, 243 },                     // 318
	{ OT_Inst, 244 },                     // 319
	{ OT_Inst, 245 },                     // 320
	{ OT_Inst, 246 },                     // 321
	{ OT_Inst, 247 },                     // 322
	{ OT_Inst, 248 },                     // 323
	{ OT_Inst, 249 },                     // 324
	{ OT_Inst, 250 },                     // 325
	{ OT_Inst, 251 },                     // 326
	{ OT_Inst, 252 },                     // 327
	{ OT_Inst, 253 },                     // 328
	{ OT_Inst, 254 },                     // 329
	{ OT_Inst, 255 },                     // 330
	{ OT_Inst, 256 },                     // 331
	{ OT_Inst, 257 },                     // 332
	{ OT_Inst, 258 },                     // 333
	{ OT_Inst, 259 },                     // 334
	{ OT_Inst, 260 },                     // 335
	{ OT_Inst, 261 },                     // 336
	{ OT_Inst, 262 },                     // 337
	{ OT_Inst, 263 },                     // 338
	{ OT_Inst, 264 },                     // 339
	{ OT_Inst, 265 },                     // 340
	{ OT_Inst, 266 },                     // 341
	{ OT_Inst, 267 },                     // 342
	{ OT_Inst, 268 },                     // 343
	{ OT_Inst, 269 },                     // 344
	{ OT_Inst, 270 },                     // 345
	{ OT_Inst, 271 },                     // 346
	{ OT_Inst, 272 },                     // 347
	{ OT_Inst, 273 },                     // 348
	{ OT_Inst, 274 },                     // 349
	{ OT_Inst, 275 },                     // 350
	{ OT_Inst, 276 },                     // 351
	{ OT_Inst, 277 },                     // 352
	{ OT_Inst, 278 },                     // 353
	{ OT_Inst, 279 },                     // 354
	{ OT_Inst, 280 },                     // 355
	{ OT_Inst, 281 },                     // 356
	{ OT_Inst, 282 },                     // 357
	{ OT_Inst, 283 },                     // 358
	{ OT_Inst, 284 },                     // 359
	{ OT_Inst, 285 },                     // 360
	{ OT_Inst, 286 },                     // 361
	{ OT_Inst, 287 },                     // 362
	{ OT_Inst, 288 },                     // 363
	{ OT_Grp, 19 },                       // 364
	{ OT_Grp, 20 },                       // 365
	{ OT_Grp, 21 },                       // 366
	{ OT_Inst, 289 },                     // 367
	{ OT_Inst, 290 },                     // 368
	{ OT_Inst, 291 },                     // 369
	{ OT_Inst, 292 },                     // 370
	{ OT_Inst, 293 },                     // 371
	{ OT_Inst, 294 },                     // 372
	{ OT_Inst, 295 },                     // 373
	{ OT_Inst, 296 },                     // 374
	{ OT_Inst, 297 },                     // 375
	{ OT_Inst, 298 },                     // 376
	{ OT_Inst, 299 },                     // 377
	{ OT_Inst, 300 },                     // 378
	{ OT_Inst, 301 },                     // 379
	{ OT_Grp, 22 },                       // 380
	{ OT_Inst, 302 },                     // 381
	{ OT_Inst, 303 },                     // 382
	{ OT_Inst, 304 },                     // 383
	{ OT_Inst, 305 },                     // 384
	{ OT_Inst, 306 },                     // 385
	{ OT_Inst, 307 },                     // 386
	{ OT_Inst, 308 },                     // 387
	{ OT_Inst, 309 },                     // 388
	{ OT_Inst, 310 },                     // 389
	{ OT_Inst, 311 },                     // 390
	{ OT_Inst, 312 },                     // 391
	{ OT_Inst, 313 },                     // 392
	{ OT_Inst, 314 },                     // 393
	{ OT_Inst, 315 },                     // 394
	{ OT_Inst, 316 },                     // 395
	{ OT_Inst, 317 },                     // 396
	{ OT_Inst, 318 },                     // 397
	{ OT_Inst, 319 },                     // 398
	{ OT_Inst, 320 },                     // 399
	{ OT_Inst, 321 },                     // 400
	{ OT_Inst, 322 },                     // 401
	{ OT_Inst, 323 },                     // 402
	{ OT_Inst, 324 },                     // 403
	{ OT_Table_0F38, 0 },                 // 404
	{ OT_Table_0F3A, 0 },                 // 405
	{ OT_Inst, 325 },                     // 406
	{ OT_Inst, 326 },                     // 407
	{ OT_Inst, 327 },                     // 408
	{ OT_Inst, 328 },                     // 409
	{ OT_Inst, 329 },                     // 410
	{ OT_Inst, 330 },                     // 411
	{ OT_Inst, 331 },                     // 412
	{ OT_Inst, 332 },                     // 413
	{ OT_Inst, 333 },                     // 414
	{ OT_Inst, 334 },                     // 415
	{ OT_Inst, 335 },                     // 416
	{ OT_Inst, 336 },                     // 417
	{ OT_Inst, 337 },                     // 418
	{ OT_Inst, 338 },                     // 419
	{ OT_Inst, 339 },                     // 420
	{ OT_Inst, 340 },                     // 421
	{ OT_Inst, 341 },                     // 422
	{ OT_Inst, 342 },                     // 423
	{ OT_Inst, 343 },                     // 424
	{ OT_Inst, 344 },                     // 425
	{ OT_Inst, 345 },                     // 426
	{ OT_Inst, 346 },                     // 427
	{ OT_Inst, 347 },                     // 428
	{ OT_Inst, 348 },                     // 429
	{ OT_Inst, 349 },                     // 430
	{ OT_Inst, 350 },                     // 431
	{ OT_Inst, 351 },                     // 432
	{ OT_Inst, 352 },                     // 433
	{ OT_Inst, 353 },                     // 434
	{ OT_Inst, 354 },                     // 435
	{ OT_Inst, 355 },                     // 436
	{ OT_Inst, 356 },                     // 437
	{ OT_Inst, 357 },                     // 438
	{ OT_Inst, 358 },                     // 439
	{ OT_Inst, 359 },                     // 440
	{ OT_Inst, 360 },                     // 441
	{ OT_Inst, 361 },                     // 442
	{ OT_Inst, 362 },                     // 443
	{ OT_Inst, 363 },                     // 444
	{ OT_Inst, 364 },                     // 445
	{ OT_Inst, 365 },                     // 446
	{ OT_Inst, 366 },                     // 447
	{ OT_Inst, 367 },                     // 448
	{ OT_Inst, 368 },                     // 449
	{ OT_Inst, 369 },                     // 450
	{ OT_Inst, 370 },                     // 451
	{ OT_Inst, 371 },                     // 452
	{ OT_Inst_Change, 18 },               // 453
	{ OT_Inst_Change, 19 },               // 454
	{ OT_Inst, 372 },                     // 455
	{ OT_Inst, 373 },                     // 456
	{ OT_Inst, 374 },                     // 457
	{ OT_Inst, 375 },                     // 458
	{ OT_Inst, 376 },                     // 459
	{ OT_Inst, 377 },                     // 460
	{ OT_Inst, 378 },                     // 461
	{ OT_Inst_Change, 20 },               // 462
	{ OT_Inst_Change, 21 },               // 463
	{ OT_Inst, 379 },                     // 464
	{ OT_Inst, 380 },                     // 465
	{ OT_Inst, 381 },                     // 466
	{ OT_Inst, 382 },                     // 467
	{ OT_Inst, 383 },                     // 468
	{ OT_Inst, 384 },                     // 469
	{ OT_Inst, 385 },                     // 470
	{ OT_Inst, 386 },                     // 471
	{ OT_Inst, 387 },                     // 472
	{ OT_Inst, 388 },                     // 473
	{ OT_Inst, 389 },                     // 474
	{ OT_Inst, 390 },                     // 475
	{ OT_Inst, 391 },                     // 476
	{ OT_Inst, 392 },                     // 477
	{ OT_Inst, 393 },                     // 478
	{ OT_Inst, 394 },                     // 479
	{ OT_Inst, 395 },                     // 480
	{ OT_Inst, 396 },                     // 481
	{ OT_Inst, 397 },                     // 482
	{ OT_Inst, 398 },                     // 483
	{ OT_Inst, 399 },                     // 484
	{ OT_Inst, 400 },                     // 485
	{ OT_Inst, 401 },                     // 486
	{ OT_Inst, 402 },                     // 487
	{ OT_Inst, 403 },                     // 488
	{ OT_Inst, 404 },                     // 489
	{ OT_Inst, 405 },                     // 490
	{ OT_Inst, 406 },                     // 491
	{ OT_Inst, 407 },                     // 492
	{ OT_Inst, 408 },                     // 493
	{ OT_Inst, 409 },                     // 494
	{ OT_Inst, 410 },                     // 495
	{ OT_Inst, 411 },                     // 496
	{ OT_Inst, 412 },                     // 497
	{ OT_Inst, 413 },                     // 498
	{ OT_Inst, 414 },                     // 499
	{ OT_Inst, 415 },                     // 500
	{ OT_Inst, 416 },                     // 501
	{ OT_Inst, 417 },                     // 502
	{ OT_Inst, 418 },                     // 503
	{ OT_Inst, 419 },                     // 504
	{ OT_Inst, 420 },                     // 505
	{ OT_Inst, 421 },                     // 506
	{ OT_Inst, 422 },                     // 507
	{ OT_Inst, 423 },                     // 508
	{ OT_Inst, 424 },                     // 509
	{ OT_Inst, 425 },                     // 510
	{ OT_Inst, 426 },                     // 511
	{ OT_Inst, 427 },                     // 512
	{ OT_Inst, 428 },                     // 513
	{ OT_Inst, 429 },                     // 514
	{ OT_Grp, 23 },                       // 515
	{ OT_Inst, 430 },                     // 516
	{ OT_Inst, 431 },                     // 517
	{ OT_Inst, 432 },                     // 518
	{ OT_Inst, 433 },                     // 519
	{ OT_Inst, 434 },                     // 520
	{ OT_Inst, 435 },                     // 521
	{ OT_Inst, 436 },                     // 522
	{ OT_Inst, 437 },                     // 523
	{ OT_Inst, 438 },                     // 524
	{ OT_Inst, 439 },                     // 525
	{ OT_Inst, 440 },                     // 526
	{ OT_Inst, 441 },                     // 527
	{ OT_Inst, 442 },                     // 528
	{ OT_Inst, 443 },                     // 529
	{ OT_Inst, 444 },                     // 530
	{ OT_Inst, 445 },                     // 531
	{ OT_Inst, 446 },                     // 532
	{ OT_Inst, 447 },                     // 533
	{ OT_Inst, 448 },                     // 534
	{ OT_Inst, 449 },                     // 535
	{ OT_Inst, 450 },                     // 536
	{ OT_Inst, 451 },                     // 537
	{ OT_Inst, 452 },                     // 538
	{ OT_Inst, 453 },                     // 539
	{ OT_Inst, 454 },                     // 540
	{ OT_Inst, 455 },                     // 541
	{ OT_Inst, 456 },                     // 542
	{ OT_Inst, 457 },                     // 543
	{ OT_Inst, 458 },                     // 544
	{ OT_Inst, 459 },                     // 545
	{ OT_Inst, 460 },                     // 546
	{ OT_Inst, 461 },                     // 547
	{ OT_Inst, 462 },                     // 548
	{ OT_Inst, 463 },                     // 549
	{ OT_Inst, 464 },                     // 550
	{ OT_Inst, 465 },                     // 551
	{ OT_Inst, 466 },                     // 552
	{ OT_Inst, 467 },                     // 553
	{ OT_Inst, 468 },                     // 554
	{ OT_Inst, 469 },                     // 555
	{ OT_Inst, 470 },                     // 556
	{ OT_Inst, 471 },                     // 557
	{ OT_Inst, 472 },                     // 558
	{ OT_Inst, 473 },                     // 559
	{ OT_Inst, 474 },                     // 560
	{ OT_Inst, 475 },                     // 561
	{ OT_Inst, 476 },                     // 562
	{ OT_Inst, 477 },                     // 563
	{ OT_Inst, 478 },                     // 564
	{ OT_Inst, 479 },                     // 565
	{ OT_Inst, 480 },                     // 566
	{ OT_Inst, 481 },                     // 567
	{ OT_Inst, 482 },                     // 568
	{ OT_Inst, 483 },                     // 569
	{ OT_Inst, 484 },                     // 570
	{ OT_Inst, 485 },                     // 571
	{ OT_Inst, 486 },                     // 572
	{ OT_Inst, 487 },                     // 573
	{ OT_Inst, 488 },                     // 574
	{ OT_Inst, 489 },                     // 575
	{ OT_Inst, 490 },                     // 576
	{ OT_Inst, 491 },                     // 577
	{ OT_Inst, 492 },                     // 578
	{ OT_Inst, 493 },                     // 579
	{ OT_Inst, 494 },                     // 580
	{ OT_Inst, 495 },                     // 581
	{ OT_Inst, 496 },                     // 582
	{ OT_Inst, 497 },                     // 583
	{ OT_Inst, 498 },                     // 584
	{ OT_Inst, 499 },                     // 585
	{ OT_Inst, 500 },                     // 586
	{ OT_Grp, 24 },                       // 587
	{ OT_Inst, 501 },                     // 588
	{ OT_Inst, 502 },                     // 589
	{ OT_Inst, 503 },                     // 590
	{ OT_Grp, 25 },                       // 591
	{ OT_Grp, 26 },                       // 592
	{ OT_Inst, 504 },                     // 593
	{ OT_Inst, 505 },                     // 594
	{ OT_Inst, 506 },                     // 595
	{ OT_Inst, 507 },                     // 596
	{ OT_Inst, 508 },                     // 597
	{ OT_Inst, 509 },                     // 598
	{ OT_Inst, 510 },                     // 599
	{ OT_Inst, 511 },                     // 600
	{ OT_Inst, 512 },                     // 601
	{ OT_Inst, 513 },                     // 602
	{ OT_Inst, 514 },                     // 603
	{ OT_Inst, 515 },                     // 604
	{ OT_Inst, 516 },                     // 605
	{ OT_Inst, 517 },                     // 606
	{ OT_Inst, 518 },                     // 607
	{ OT_Inst, 519 },                     // 608
	{ OT_Inst, 520 },                     // 609
	{ OT_Inst, 521 },                     // 610
	{ OT_Inst, 522 },                     // 611
	{ OT_Inst, 523 },                     // 612
	{ OT_Inst, 524 },                     // 613
	{ OT_Inst, 525 },                     // 614
	{ OT_Inst, 526 },                     // 615
	{ OT_Inst, 527 },                     // 616
	{ OT_Inst, 528 },                     // 617
	{ OT_Inst, 529 },                     // 618
	{ OT_Inst, 530 },                     // 619
	{ OT_Inst, 531 },                     // 620
	{ OT_Inst, 532 },                     // 621
	{ OT_Inst, 533 },                     // 622
	{ OT_Inst, 534 },                     // 623
	{ OT_Inst, 535 },                     // 624
	{ OT_Inst, 536 },                     // 625
	{ OT_Inst, 537 },                     // 626
	{ OT_Inst, 538 },                     // 627
	{ OT_Inst, 539 },                     // 628
	{ OT_Inst, 540 },                     // 629
	{ OT_Inst, 541 },                     // 630
	{ OT_Inst, 542 },                     // 631
	{ OT_Inst, 543 },                     // 632
	{ OT_Inst, 544 },                     // 633
	{ OT_Inst, 545 },                     // 634
	{ OT_Inst, 546 },                     // 635
	{ OT_Inst, 547 },                     // 636
	{ OT_Inst, 548 },                     // 637
	{ OT_Inst, 549 },                     // 638
	{ OT_Inst, 550 },                     // 639
	{ OT_Inst, 551 },                     // 640
	{ OT_Inst, 552 },                     // 641
	{ OT_Inst, 553 },                     // 642
	{ OT_Inst, 554 },                     // 643
	{ OT_Inst, 555 },                     // 644
	{ OT_Inst, 556 },                     // 645
	{ OT_Inst, 557 },                     // 646
	{ OT_Inst, 558 },                     // 647
	{ OT_Inst, 559 },                     // 648
	{ OT_Inst, 560 },                     // 649
	{ OT_Inst, 561 },                     // 650
	{ OT_Inst, 562 },                     // 651
	{ OT_Inst, 563 },                     // 652
	{ OT_Inst, 564 },                     // 653
	{ OT_Inst, 565 },                     // 654
	{ OT_Inst, 566 },                     // 655
	{ OT_Inst, 567 },                     // 656
	{ OT_Inst, 568 },                     // 657
	{ OT_Inst, 569 },                     // 658
	{ OT_Inst, 570 },                     // 659
	{ OT_Inst, 571 },                     // 660
	{ OT_Inst, 572 },                     // 661
	{ OT_Inst, 573 },                     // 662
	{ OT_Inst, 574 },                     // 663
	{ OT_Inst, 575 },                     // 664
	{ OT_Inst, 576 },                     // 665
	{ OT_Inst, 577 },                     // 666
	{ OT_Inst, 578 },                     // 667
	{ OT_Inst, 579 },                     // 668
	{ OT_Inst, 580 },                     // 669
	{ OT_Inst, 581 },                     // 670
	{ OT_Inst, 582 },                     // 671
	{ OT_Inst, 583 },                     // 672
	{ OT_Inst, 584 },                     // 673
	{ OT_Inst, 585 },                     // 674
	{ OT_Inst, 586 },                     // 675
	{ OT_Inst, 587 },                     // 676
	{ OT_Inst, 588 },                     // 677
	{ OT_Inst, 589 },                     // 678
	{ OT_Inst, 590 },                     // 679
	{ OT_Inst, 591 },                     // 680
	{ OT_Inst, 592 },                     // 681
	{ OT_Inst, 593 },                     // 682
	{ OT_Inst, 594 },                     // 683
	{ OT_Inst, 595 },                     // 684
	{ OT_Inst, 596 },                     // 685
	{ OT_Inst, 597 },                     // 686
	{ OT_Inst, 598 },                     // 687
	{ OT_Inst, 599 },                     // 688
	{ OT_Inst, 600 },                     // 689
	{ OT_Inst, 601 },                     // 690
	{ OT_Inst, 602 },                     // 691
	{ OT_Inst_Change, 22 },               // 692
	{ OT_Inst, 603 },                     // 693
	{ OT_Inst_Change, 23 },               // 694
	{ OT_Inst, 604 },                     // 695
	{ OT_Inst, 605 },                     // 696
	{ OT_Inst, 606 },                     // 697
	{ OT_Inst_Change, 24 },               // 698
	{ OT_Inst_Change, 25 },               // 699
	{ OT_Inst_Change, 26 },               // 700
	{ OT_Inst_Change, 27 },               // 701
	{ OT_Inst_Change, 28 },               // 702
	{ OT_Inst_Change, 29 },               // 703
	{ OT_Inst_Change, 30 },               // 704
	{ OT_Inst_Change, 31 },               // 705
	{ OT_Inst_Change, 32 },               // 706
	{ OT_Inst_Change, 33 },               // 707
	{ OT_Inst, 607 },                     // 708
	{ OT_Inst, 608 },                     // 709
	{ OT_Inst, 609 },                     // 710
	{ OT_Inst, 610 },                     // 711
	{ OT_Inst, 611 },                     // 712
	{ OT_Inst, 612 },                     // 713
	{ OT_Inst, 613 },                     // 714
	{ OT_Inst, 614 },                     // 715
	{ OT_Inst, 615 },                     // 716
	{ OT_Grp, 27 },                       // 717
	{ OT_Inst, 616 },                     // 718
	{ OT_Inst, 617 },                     // 719
	{ OT_Inst, 618 },                     // 720
	{ OT_Inst, 619 },                     // 721
	{ OT_Inst, 620 },                     // 722
	{ OT_Inst, 621 },                     // 723
	{ OT_Inst, 622 },                     // 724
	{ OT_Inst, 623 },                     // 725
	{ OT_Inst, 624 },                     // 726
	{ OT_Inst, 625 },                     // 727
	{ OT_Inst, 626 },                     // 728
	{ OT_Inst, 627 },                     // 729
	{ OT_Inst, 628 },                     // 730
	{ OT_Inst, 629 },                     // 731
	{ OT_Inst, 630 },                     // 732
	{ OT_Inst, 631 },                     // 733
	{ OT_Inst, 632 },                     // 734
	{ OT_Inst, 633 },                     // 735
	{ OT_Inst, 634 },                     // 736
	{ OT_Inst, 635 },                     // 737
	{ OT_Inst, 636 },                     // 738
	{ OT_Inst, 637 },                     // 739
	{ OT_Inst, 638 },                     // 740
	{ OT_Inst, 639 },                     // 741
	{ OT_Inst, 640 },                     // 742
	{ OT_Inst, 641 },                     // 743
	{ OT_Inst, 642 },                     // 744
	{ OT_Inst, 643 },                     // 745
	{ OT_Inst, 644 },                     // 746
	{ OT_Inst, 645 },                     // 747
	{ OT_Inst, 646 },                     // 748
	{ OT_Inst, 647 },                     // 749
	{ OT_Inst, 648 },                     // 750
	{ OT_Inst, 649 },                     // 751
	{ OT_Inst, 650 },                     // 752
	{ OT_Inst, 651 },                     // 753
	{ OT_Inst, 652 },                     // 754
	{ OT_Inst, 653 },                     // 755
	{ OT_Inst, 654 },                     // 756
	{ OT_Inst, 655 },                     // 757
	{ OT_Inst, 656 },                     // 758
	{ OT_Inst, 657 },                     // 759
	{ OT_Inst, 658 },                     // 760
	{ OT_Inst, 659 },                     // 761
	{ OT_Inst, 660 },                     // 762
	{ OT_Inst, 661 },                     // 763
	{ OT_Inst, 662 },                     // 764
	{ OT_Inst, 663 },                     // 765
	{ OT_Inst, 664 },                     // 766
	{ OT_Inst, 665 },                     // 767
	{ OT_Inst, 666 },                     // 768
	{ OT_Inst, 667 },                     // 769
	{ OT_Inst_Change, 34 },               // 770
	{ OT_Inst_Change, 35 },               // 771
	{ OT_Inst_Change, 36 },               // 772
	{ OT_Inst_Change, 37 },               // 773
	{ OT_Inst_Change, 38 },               // 774
	{ OT_Inst_Change, 39 },               // 775
	{ OT_Inst_Change, 40 },               // 776
	{ OT_Inst_Change, 41 },               // 777
	{ OT_Inst_Change, 42 },               // 778
	{ OT_Inst_Change, 43 },               // 779
	{ OT_Inst_Change, 44 },               // 780
	{ OT_Inst_Change, 45 },               // 781
	{ OT_Inst_Change, 46 },               // 782
	{ OT_Inst_Change, 47 },               // 783
	{ OT_Inst_Change, 48 },               // 784
	{ OT_Inst_Change, 49 },               // 785
	{ OT_Inst_Change, 50 },               // 786
	{ OT_Inst_Change, 51 },               // 787
	{ OT_Inst_Change, 52 },               // 788
	{ OT_Inst_Change, 53 },               // 789
	{ OT_Inst_Change, 54 },               // 790
	{ OT_Inst_Change, 55 },               // 791
	{ OT_Inst_Change, 56 },               // 792
	{ OT_Inst_Change, 57 },               // 793
	{ OT_Inst_Change, 58 },               // 794
	{ OT_Inst_Change, 59 },               // 795
	{ OT_Inst, 668 },                     // 796
	{ OT_Inst, 669 },                     // 797
	{ OT_Inst, 670 },                     // 798
	{ OT_Inst, 671 },                     // 799
	{ OT_Inst, 672 },                     // 800
	{ OT_Inst, 673 },                     // 801
	{ OT_Inst, 674 },                     // 802
	{ OT_Inst, 675 },                     // 803
	{ OT_Inst, 676 },                     // 804
	{ OT_Inst, 677 },                     // 805
	{ OT_Inst, 678 },                     // 806
	{ OT_Inst, 679 },                     // 807
	{ OT_Inst, 680 },                     // 808
	{ OT_Inst_Change, 60 },               // 809
	{ OT_Inst, 681 },                     // 810
	{ OT_Inst, 682 },                     // 811
	{ OT_Inst, 683 },                     // 812
	{ OT_Inst_Change, 61 },               // 813
	{ OT_Inst, 684 },                     // 814
	{ OT_Inst, 685 },                     // 815
	{ OT_Inst, 686 },                     // 816
	{ OT_Inst, 687 },                     // 817
	{ OT_Inst, 688 },                     // 818
	{ OT_Inst, 689 },                     // 819
	{ OT_Inst, 690 },                     // 820
	{ OT_Inst, 691 },                     // 821
	{ OT_Inst, 692 },                     // 822
	{ OT_Inst, 693 },                     // 823
	{ OT_Inst, 694 },                     // 824
	{ OT_Inst, 695 },                     // 825
	{ OT_Inst, 696 },                     // 826
	{ OT_Inst, 697 },                     // 827
	{ OT_Inst, 698 },                     // 828
	{ OT_Inst, 699 },                     // 829
	{ OT_Inst, 700 },                     // 830
	{ OT_Inst, 701 },                     // 831
	{ OT_Inst, 702 },                     // 832
	{ OT_Inst, 703 },                     // 833
	{ OT_Inst, 704 },                     // 834
	{ OT_Inst, 705 },                     // 835
	{ OT_Inst, 706 },                     // 836
	{ OT_Inst, 707 },                     // 837
	{ OT_Inst, 708 },                     // 838
	{ OT_Inst, 709 },                     // 839
	{ OT_Inst, 710 },                     // 840
	{ OT_Inst, 711 },                     // 841
};

const InstData Inst[] =
{
	{ NULL, NULL, 1, 2, 1, 35 },                              // 0
	{ NULL, NULL, 2, 2, 1, 35 },                              // 1
	{ NULL, NULL, 3, 2, 1, 35 },                              // 2
	{ NULL, NULL, 4, 2, 1, 35 },                              // 3
	{ NULL, NULL, 5, 2, 1, 35 },                              // 4
	{ NULL, NULL, 6, 2, 1, 35 },                              // 5
	{ NULL, S_i64, 1, 1, 1, 318 },                            // 6
	{ NULL, S_i64, 1, 1, 1, 279 },                            // 7
	{ NULL, NULL, 1, 2, 1, 33 },                              // 8
	{ NULL, NULL, 2, 2, 1, 33 },                              // 9
	{ NULL, NULL, 3, 2, 1, 33 },                              // 10
	{ NULL, NULL, 4, 2, 1, 33 },                              // 11
	{ NULL, NULL, 5, 2, 1, 33 },                              // 12
	{ NULL, NULL, 6, 2, 1, 33 },                              // 13
	{ NULL, S_i64, 2, 1, 1, 318 },                            // 14
	{ NULL, S_i64, 2, 1, 1, 279 },                            // 15
	{ NULL, NULL, 1, 2, 1, 37 },                              // 16
	{ NULL, NULL, 2, 2, 1, 37 },                              // 17
	{ NULL, NULL, 3, 2, 1, 37 },                              // 18
	{ NULL, NULL, 4, 2, 1, 37 },                              // 19
	{ NULL, NULL, 5, 2, 1, 37 },                              // 20
	{ NULL, NULL, 6, 2, 1, 37 },                              // 21
	{ NULL, S_i64, 0, 0, 1, 112 },                            // 22
	{ NULL, NULL, 1, 2, 1, 733 },                             // 23
	{ NULL, NULL, 2, 2, 1, 733 },                             // 24
	{ NULL, NULL, 3, 2, 1, 733 },                             // 25
	{ NULL, NULL, 4, 2, 1, 733 },                             // 26
	{ NULL, NULL, 5, 2, 1, 733 },                             // 27
	{ NULL, NULL, 6, 2, 1, 733 },                             // 28
	{ NULL, S_i64, 0, 0, 1, 29 },                             // 29
	{ NULL, S_i64, 3, 1, 1, 127 },                            // 30
	{ NULL, S_i64, 4, 1, 1, 127 },                            // 31
	{ NULL, S_i64, 5, 1, 1, 127 },                            // 32
	{ NULL, S_i64, 6, 1, 1, 127 },                            // 33
	{ NULL, S_i64, 7, 1, 1, 127 },                            // 34
	{ NULL, S_i64, 8, 1, 1, 127 },                            // 35
	{ NULL, S_i64, 9, 1, 1, 127 },                            // 36
	{ NULL, S_i64, 10, 1, 1, 127 },                           // 37
	{ NULL, S_d64, 11, 1, 1, 318 },                           // 38
	{ NULL, S_d64, 12, 1, 1, 318 },                           // 39
	{ NULL, S_d64, 13, 1, 1, 318 },                           // 40
	{ NULL, S_d64, 14, 1, 1, 318 },                           // 41
	{ NULL, S_d64, 15, 1, 1, 318 },                           // 42
	{ NULL, S_d64, 16, 1, 1, 318 },                           // 43
	{ NULL, S_d64, 17, 1, 1, 318 },                           // 44
	{ NULL, S_d64, 18, 1, 1, 318 },                           // 45
	{ NULL, S_i64, 0, 0, 2, 319 },                            // 46
	{ NULL, S_i64, 0, 0, 2, 280 },                            // 47
	{ NULL, S_i64, 7, 2, 1, 46 },                             // 48
	{ NULL, S_i64, 8, 2, 1, 39 },                             // 49
	{ NULL, S_o64, 4, 2, 1, 219 },                            // 50
	{ NULL, S_f64, 19, 1, 1, 175 },                           // 51
	{ NULL, S_f64, 19, 1, 1, 169 },                           // 52
	{ NULL, S_f64, 19, 1, 3, 143 },                           // 53
	{ NULL, S_f64, 19, 1, 3, 158 },                           // 54
	{ NULL, S_f64, 19, 1, 2, 180 },                           // 55
	{ NULL, S_f64, 19, 1, 2, 173 },                           // 56
	{ NULL, S_f64, 19, 1, 2, 148 },                           // 57
	{ NULL, S_f64, 19, 1, 2, 161 },                           // 58
	{ NULL, NULL, 1, 2, 1, 398 },                             // 59
	{ NULL, NULL, 2, 2, 1, 398 },                             // 60
	{ NULL, NULL, 1, 2, 1, 729 },                             // 61
	{ NULL, NULL, 2, 2, 1, 729 },                             // 62
	{ NULL, NULL, 0, 0, 1, 225 },                             // 63
	{ C_F3, NULL, 0, 0, 1, 247 },                             // 64
	{ NULL, NULL, 12, 2, 1, 729 },                            // 65
	{ NULL, NULL, 13, 2, 1, 729 },                            // 66
	{ NULL, NULL, 14, 2, 1, 729 },                            // 67
	{ NULL, NULL, 15, 2, 1, 729 },                            // 68
	{ NULL, NULL, 16, 2, 1, 729 },                            // 69
	{ NULL, NULL, 17, 2, 1, 729 },                            // 70
	{ NULL, NULL, 18, 2, 1, 729 },                            // 71
	{ NULL, NULL, 19, 2, 1, 729 },                            // 72
	{ NULL, NULL, 20, 2, 1, 209 },                            // 73
	{ NULL, NULL, 21, 2, 1, 209 },                            // 74
	{ NULL, NULL, 22, 2, 1, 209 },                            // 75
	{ NULL, NULL, 23, 2, 1, 209 },                            // 76
	{ NULL, NULL, 28, 2, 1, 209 },                            // 77
	{ NULL, NULL, 29, 2, 1, 209 },                            // 78
	{ NULL, NULL, 30, 2, 1, 209 },                            // 79
	{ NULL, NULL, 31, 2, 1, 209 },                            // 80
	{ NULL, NULL, 32, 2, 1, 209 },                            // 81
	{ NULL, NULL, 33, 2, 1, 209 },                            // 82
	{ NULL, NULL, 34, 2, 1, 209 },                            // 83
	{ NULL, NULL, 35, 2, 1, 209 },                            // 84
	{ NULL, S_f64, 20, 1, 1, 333 },                           // 85
	{ NULL, S_f64, 0, 0, 1, 333 },                            // 86
	{ NULL, S_i64, 36, 2, 1, 188 },                           // 87
	{ NULL, S_i64, 36, 2, 1, 185 },                           // 88
	{ NULL, S_i64, 21, 1, 1, 31 },                            // 89
	{ NULL, S_i64, 21, 1, 1, 30 },                            // 90
	{ NULL, S_f64, 19, 1, 2, 200 },                           // 91
	{ NULL, S_f64, 19, 1, 2, 198 },                           // 92
	{ NULL, S_f64, 19, 1, 1, 197 },                           // 93
	{ NULL, S_f64, 19, 1, 1, 178 },                           // 94
	{ NULL, NULL, 5, 2, 1, 126 },                             // 95
	{ NULL, NULL, 41, 2, 1, 126 },                            // 96
	{ NULL, NULL, 42, 2, 1, 228 },                            // 97
	{ NULL, NULL, 43, 2, 1, 228 },                            // 98
	{ NULL, NULL, 0, 0, 1, 123 },                             // 99
	{ NULL, NULL, 0, 0, 1, 65 },                              // 100
	{ NULL, NULL, 1, 2, 1, 227 },                             // 101
	{ NULL, NULL, 2, 2, 1, 227 },                             // 102
	{ NULL, NULL, 3, 2, 1, 227 },                             // 103
	{ NULL, NULL, 4, 2, 1, 227 },                             // 104
	{ NULL, NULL, 5, 2, 1, 227 },                             // 105
	{ NULL, NULL, 6, 2, 1, 227 },                             // 106
	{ NULL, S_i64, 24, 1, 1, 318 },                           // 107
	{ NULL, NULL, 1, 2, 1, 341 },                             // 108
	{ NULL, NULL, 2, 2, 1, 341 },                             // 109
	{ NULL, NULL, 3, 2, 1, 341 },                             // 110
	{ NULL, NULL, 4, 2, 1, 341 },                             // 111
	{ NULL, NULL, 5, 2, 1, 341 },                             // 112
	{ NULL, NULL, 6, 2, 1, 341 },                             // 113
	{ NULL, S_i64, 25, 1, 1, 318 },                           // 114
	{ NULL, S_i64, 25, 1, 1, 279 },                           // 115
	{ NULL, NULL, 1, 2, 1, 392 },                             // 116
	{ NULL, NULL, 2, 2, 1, 392 },                             // 117
	{ NULL, NULL, 3, 2, 1, 392 },                             // 118
	{ NULL, NULL, 4, 2, 1, 392 },                             // 119
	{ NULL, NULL, 5, 2, 1, 392 },                             // 120
	{ NULL, NULL, 6, 2, 1, 392 },                             // 121
	{ NULL, S_i64, 0, 0, 1, 113 },                            // 122
	{ NULL, NULL, 1, 2, 1, 96 },                              // 123
	{ NULL, NULL, 2, 2, 1, 96 },                              // 124
	{ NULL, NULL, 3, 2, 1, 96 },                              // 125
	{ NULL, NULL, 4, 2, 1, 96 },                              // 126
	{ NULL, NULL, 5, 2, 1, 96 },                              // 127
	{ NULL, NULL, 6, 2, 1, 96 },                              // 128
	{ NULL, S_i64, 0, 0, 1, 32 },                             // 129
	{ NULL, S_i64, 3, 1, 1, 114 },                            // 130
	{ NULL, S_i64, 4, 1, 1, 114 },                            // 131
	{ NULL, S_i64, 5, 1, 1, 114 },                            // 132
	{ NULL, S_i64, 6, 1, 1, 114 },                            // 133
	{ NULL, S_i64, 7, 1, 1, 114 },                            // 134
	{ NULL, S_i64, 8, 1, 1, 114 },                            // 135
	{ NULL, S_i64, 9, 1, 1, 114 },                            // 136
	{ NULL, S_i64, 10, 1, 1, 114 },                           // 137
	{ NULL, S_d64, 11, 1, 1, 279 },                           // 138
	{ NULL, S_d64, 12, 1, 1, 279 },                           // 139
	{ NULL, S_d64, 13, 1, 1, 279 },                           // 140
	{ NULL, S_d64, 14, 1, 1, 279 },                           // 141
	{ NULL, S_d64, 15, 1, 1, 279 },                           // 142
	{ NULL, S_d64, 16, 1, 1, 279 },                           // 143
	{ NULL, S_d64, 17, 1, 1, 279 },                           // 144
	{ NULL, S_d64, 18, 1, 1, 279 },                           // 145
	{ NULL, S_d64, 26, 1, 1, 318 },                           // 146
	{ NULL, NULL, 1, 3, 1, 125 },                             // 147
	{ NULL, S_d64, 21, 1, 1, 318 },                           // 148
	{ NULL, NULL, 2, 3, 1, 125 },                             // 149
	{ NULL, S_f64, 19, 1, 1, 179 },                           // 150
	{ NULL, S_f64, 19, 1, 1, 172 },                           // 151
	{ NULL, S_f64, 19, 1, 2, 176 },                           // 152
	{ NULL, S_f64, 19, 1, 2, 170 },                           // 153
	{ NULL, S_f64, 19, 1, 2, 152 },                           // 154
	{ NULL, S_f64, 19, 1, 2, 165 },                           // 155
	{ NULL, S_f64, 19, 1, 2, 154 },                           // 156
	{ NULL, S_f64, 19, 1, 2, 167 },                           // 157
	{ NULL, NULL, 1, 2, 1, 209 },                             // 158
	{ NULL, NULL, 2, 2, 1, 209 },                             // 159
	{ NULL, NULL, 3, 2, 1, 209 },                             // 160
	{ NULL, NULL, 4, 2, 1, 209 },                             // 161
	{ NULL, NULL, 48, 2, 1, 209 },                            // 162
	{ NULL, NULL, 49, 2, 1, 186 },                            // 163
	{ NULL, NULL, 50, 2, 1, 209 },                            // 164
	{ NULL, NULL, 0, 0, 3, 56 },                              // 165
	{ NULL, NULL, 0, 0, 3, 109 },                             // 166
	{ NULL, S_i64, 27, 1, 1, 55 },                            // 167
	{ NULL, NULL, 0, 0, 2, 118 },                             // 168
	{ NULL, NULL, 0, 0, 1, 338 },                             // 169
	{ NULL, NULL, 0, 0, 1, 182 },                             // 170
	{ NULL, NULL, 5, 2, 1, 398 },                             // 171
	{ NULL, NULL, 6, 2, 1, 398 },                             // 172
	{ NULL, NULL, 57, 2, 1, 209 },                            // 173
	{ NULL, NULL, 58, 2, 1, 209 },                            // 174
	{ NULL, NULL, 59, 2, 1, 209 },                            // 175
	{ NULL, NULL, 60, 2, 1, 209 },                            // 176
	{ NULL, NULL, 61, 2, 1, 209 },                            // 177
	{ NULL, NULL, 62, 2, 1, 209 },                            // 178
	{ NULL, NULL, 63, 2, 1, 209 },                            // 179
	{ NULL, NULL, 64, 2, 1, 209 },                            // 180
	{ NULL, NULL, 65, 2, 1, 117 },                            // 181
	{ NULL, S_d64, 0, 0, 1, 187 },                            // 182
	{ NULL, NULL, 20, 1, 1, 333 },                            // 183
	{ NULL, NULL, 0, 0, 1, 333 },                             // 184
	{ NULL, NULL, 0, 0, 1, 130 },                             // 185
	{ NULL, NULL, 21, 1, 1, 129 },                            // 186
	{ NULL, S_i64, 0, 0, 1, 131 },                            // 187
	{ NULL, S_f64, 29, 1, 1, 55 },                            // 188
	{ NULL, S_f64, 29, 1, 1, 156 },                           // 189
	{ NULL, S_i64, 27, 1, 1, 156 },                           // 190
	{ NULL, S_f64, 19, 1, 1, 156 },                           // 191
	{ NULL, NULL, 66, 2, 1, 126 },                            // 192
	{ NULL, NULL, 67, 2, 1, 126 },                            // 193
	{ NULL, NULL, 68, 2, 1, 228 },                            // 194
	{ NULL, NULL, 69, 2, 1, 228 },                            // 195
	{ NULL, NULL, 0, 0, 1, 60 },                              // 196
	{ NULL, NULL, 0, 0, 1, 386 },                             // 197
	{ NULL, NULL, 0, 0, 1, 63 },                              // 198
	{ NULL, NULL, 0, 0, 1, 388 },                             // 199
	{ NULL, NULL, 0, 0, 1, 61 },                              // 200
	{ NULL, NULL, 0, 0, 1, 387 },                             // 201
	{ NULL, NULL, 70, 2, 1, 183 },                            // 202
	{ NULL, NULL, 70, 2, 1, 202 },                            // 203
	{ NULL, S_o64, 0, 0, 1, 394 },                            // 204
	{ NULL, NULL, 0, 0, 1, 64 },                              // 205
	{ NULL, S_o64, 0, 0, 1, 397 },                            // 206
	{ NULL, NULL, 71, 2, 1, 541 },                            // 207
	{ C_66, NULL, 74, 2, 1, 540 },                            // 208
	{ C_F3, NULL, 8, 3, 1, 539 },                             // 209
	{ C_F2, NULL, 10, 3, 1, 536 },                            // 210
	{ NULL, NULL, 72, 2, 1, 541 },                            // 211
	{ C_66, NULL, 75, 2, 1, 540 },                            // 212
	{ C_F3, NULL, 9, 3, 1, 539 },                             // 213
	{ C_F2, NULL, 11, 3, 1, 536 },                            // 214
	{ NULL, NULL, 3, 3, 1, 528 },                             // 215
	{ NULL, NULL, 4, 3, 1, 523 },                             // 216
	{ C_66, NULL, 3, 3, 1, 527 },                             // 217
	{ C_F3, NULL, 76, 2, 1, 538 },                            // 218
	{ C_F2, NULL, 76, 2, 1, 520 },                            // 219
	{ NULL, NULL, 73, 2, 1, 528 },                            // 220
	{ C_66, NULL, 73, 2, 1, 527 },                            // 221
	{ NULL, NULL, 5, 3, 1, 717 },                             // 222
	{ C_66, NULL, 5, 3, 1, 716 },                             // 223
	{ NULL, NULL, 5, 3, 1, 715 },                             // 224
	{ C_66, NULL, 5, 3, 1, 714 },                             // 225
	{ NULL, S_v1, 6, 3, 1, 525 },                             // 226
	{ NULL, NULL, 7, 3, 1, 526 },                             // 227
	{ C_66, S_v1, 6, 3, 1, 524 },                             // 228
	{ C_F3, NULL, 76, 2, 1, 537 },                            // 229
	{ NULL, S_v1, 73, 2, 1, 525 },                            // 230
	{ C_66, S_v1, 73, 2, 1, 524 },                            // 231
	{ NULL, NULL, 77, 2, 1, 209 },                            // 232
	{ NULL, NULL, 78, 2, 1, 209 },                            // 233
	{ NULL, NULL, 79, 2, 1, 209 },                            // 234
	{ NULL, NULL, 80, 2, 1, 209 },                            // 235
	{ NULL, NULL, 0, 0, 1, 725 },                             // 236
	{ NULL, NULL, 0, 0, 1, 331 },                             // 237
	{ NULL, NULL, 0, 0, 1, 327 },                             // 238
	{ NULL, NULL, 0, 0, 1, 328 },                             // 239
	{ NULL, NULL, 0, 0, 1, 395 },                             // 240
	{ NULL, NULL, 0, 0, 1, 396 },                             // 241
	{ NULL, NULL, 0, 0, 1, 122 },                             // 242
	{ NULL, NULL, 4, 2, 1, 92 },                              // 243
	{ NULL, NULL, 4, 2, 1, 88 },                              // 244
	{ NULL, NULL, 4, 2, 3, 71 },                              // 245
	{ NULL, NULL, 4, 2, 3, 68 },                              // 246
	{ NULL, NULL, 4, 2, 2, 76 },                              // 247
	{ NULL, NULL, 4, 2, 2, 82 },                              // 248
	{ NULL, NULL, 4, 2, 2, 74 },                              // 249
	{ NULL, NULL, 4, 2, 2, 66 },                              // 250
	{ NULL, NULL, 81, 2, 1, 530 },                            // 251
	{ C_66, NULL, 82, 2, 1, 529 },                            // 252
	{ NULL, NULL, 71, 2, 1, 703 },                            // 253
	{ C_66, NULL, 74, 2, 1, 702 },                            // 254
	{ C_F3, NULL, 14, 3, 1, 705 },                            // 255
	{ C_F2, NULL, 15, 3, 1, 704 },                            // 256
	{ NULL, NULL, 71, 2, 1, 698 },                            // 257
	{ C_F3, NULL, 14, 3, 1, 699 },                            // 258
	{ NULL, NULL, 71, 2, 1, 692 },                            // 259
	{ C_F3, NULL, 14, 3, 1, 693 },                            // 260
	{ NULL, NULL, 12, 3, 1, 416 },                            // 261
	{ C_66, NULL, 13, 3, 1, 415 },                            // 262
	{ NULL, NULL, 12, 3, 1, 414 },                            // 263
	{ C_66, NULL, 13, 3, 1, 413 },                            // 264
	{ NULL, NULL, 12, 3, 1, 555 },                            // 265
	{ C_66, NULL, 13, 3, 1, 554 },                            // 266
	{ NULL, NULL, 12, 3, 1, 719 },                            // 267
	{ C_66, NULL, 13, 3, 1, 718 },                            // 268
	{ NULL, NULL, 83, 2, 1, 315 },                            // 269
	{ C_66, NULL, 5, 3, 1, 687 },                             // 270
	{ NULL, NULL, 83, 2, 1, 317 },                            // 271
	{ C_66, NULL, 5, 3, 1, 690 },                             // 272
	{ NULL, NULL, 83, 2, 1, 316 },                            // 273
	{ C_66, NULL, 5, 3, 1, 688 },                             // 274
	{ NULL, NULL, 84, 2, 1, 234 },                            // 275
	{ C_66, NULL, 5, 3, 1, 560 },                             // 276
	{ NULL, NULL, 84, 2, 1, 254 },                            // 277
	{ C_66, NULL, 5, 3, 1, 590 },                             // 278
	{ NULL, NULL, 84, 2, 1, 256 },                            // 279
	{ C_66, NULL, 5, 3, 1, 593 },                             // 280
	{ NULL, NULL, 84, 2, 1, 255 },                            // 281
	{ C_66, NULL, 5, 3, 1, 591 },                             // 282
	{ NULL, NULL, 84, 2, 1, 235 },                            // 283
	{ C_66, NULL, 5, 3, 1, 562 },                             // 284
	{ NULL, NULL, 16, 3, 1, 292 },                            // 285
	{ C_66, NULL, 17, 3, 1, 655 },                            // 286
	{ C_F3, NULL, 17, 3, 1, 656 },                            // 287
	{ C_F2, NULL, 17, 3, 1, 657 },                            // 288
	{ NULL, NULL, 84, 2, 1, 251 },                            // 289
	{ C_66, NULL, 5, 3, 1, 584 },                             // 290
	{ NULL, NULL, 84, 2, 1, 253 },                            // 291
	{ C_66, NULL, 5, 3, 1, 587 },                             // 292
	{ NULL, NULL, 84, 2, 1, 252 },                            // 293
	{ C_66, NULL, 5, 3, 1, 585 },                             // 294
	{ NULL, NULL, 0, 0, 1, 116 },                             // 295
	{ NULL, S_v, 0, 0, 1, 721 },                              // 296
	{ NULL, S_v, 0, 0, 1, 720 },                              // 297
	{ NULL, NULL, 0, 0, 1, 132 },                             // 298
	{ NULL, NULL, 0, 0, 1, 722 },                             // 299
	{ NULL, S_1B, 0, 0, 1, 400 },                             // 300
	{ NULL, NULL, 23, 1, 1, 289 },                            // 301
	{ NULL, NULL, 23, 1, 1, 225 },                            // 302
	{ NULL, NULL, 71, 2, 1, 518 },                            // 303
	{ C_66, NULL, 74, 2, 1, 517 },                            // 304
	{ NULL, NULL, 72, 2, 1, 518 },                            // 305
	{ C_66, NULL, 75, 2, 1, 517 },                            // 306
	{ NULL, NULL, 85, 2, 1, 105 },                            // 307
	{ C_66, NULL, 89, 2, 1, 104 },                            // 308
	{ C_F3, NULL, 18, 3, 1, 442 },                            // 309
	{ C_F2, NULL, 19, 3, 1, 441 },                            // 310
	{ NULL, NULL, 86, 2, 1, 534 },                            // 311
	{ C_66, NULL, 90, 2, 1, 533 },                            // 312
	{ NULL, NULL, 87, 2, 1, 108 },                            // 313
	{ C_66, NULL, 91, 2, 1, 107 },                            // 314
	{ C_F3, NULL, 94, 2, 1, 448 },                            // 315
	{ C_F2, NULL, 95, 2, 1, 447 },                            // 316
	{ NULL, NULL, 87, 2, 1, 106 },                            // 317
	{ C_66, NULL, 92, 2, 1, 103 },                            // 318
	{ C_F3, NULL, 94, 2, 1, 444 },                            // 319
	{ C_F2, NULL, 95, 2, 1, 439 },                            // 320
	{ NULL, NULL, 88, 2, 1, 713 },                            // 321
	{ C_66, NULL, 93, 2, 1, 712 },                            // 322
	{ NULL, NULL, 88, 2, 1, 430 },                            // 323
	{ C_66, NULL, 93, 2, 1, 429 },                            // 324
	{ NULL, NULL, 4, 2, 1, 95 },                              // 325
	{ NULL, NULL, 4, 2, 1, 91 },                              // 326
	{ NULL, NULL, 4, 2, 2, 93 },                              // 327
	{ NULL, NULL, 4, 2, 2, 89 },                              // 328
	{ NULL, NULL, 4, 2, 2, 78 },                              // 329
	{ NULL, NULL, 4, 2, 2, 84 },                              // 330
	{ NULL, NULL, 4, 2, 2, 80 },                              // 331
	{ NULL, NULL, 4, 2, 2, 86 },                              // 332
	{ NULL, NULL, 12, 3, 1, 402 },                            // 333
	{ C_66, NULL, 13, 3, 1, 401 },                            // 334
	{ C_F3, NULL, 14, 3, 1, 404 },                            // 335
	{ C_F2, NULL, 15, 3, 1, 403 },                            // 336
	{ NULL, NULL, 12, 3, 1, 548 },                            // 337
	{ C_66, NULL, 13, 3, 1, 547 },                            // 338
	{ C_F3, NULL, 14, 3, 1, 550 },                            // 339
	{ C_F2, NULL, 15, 3, 1, 549 },                            // 340
	{ NULL, NULL, 96, 2, 1, 437 },                            // 341
	{ C_66, NULL, 98, 2, 1, 434 },                            // 342
	{ C_F3, NULL, 20, 3, 1, 443 },                            // 343
	{ C_F2, NULL, 21, 3, 1, 440 },                            // 344
	{ NULL, NULL, 97, 2, 1, 432 },                            // 345
	{ C_66, NULL, 99, 2, 1, 436 },                            // 346
	{ C_F3, NULL, 99, 2, 1, 446 },                            // 347
	{ NULL, NULL, 12, 3, 1, 707 },                            // 348
	{ C_66, NULL, 13, 3, 1, 706 },                            // 349
	{ C_F3, NULL, 14, 3, 1, 709 },                            // 350
	{ C_F2, NULL, 15, 3, 1, 708 },                            // 351
	{ NULL, NULL, 12, 3, 1, 513 },                            // 352
	{ C_66, NULL, 13, 3, 1, 512 },                            // 353
	{ C_F3, NULL, 14, 3, 1, 515 },                            // 354
	{ C_F2, NULL, 15, 3, 1, 514 },                            // 355
	{ NULL, NULL, 12, 3, 1, 450 },                            // 356
	{ C_66, NULL, 13, 3, 1, 449 },                            // 357
	{ C_F3, NULL, 14, 3, 1, 452 },                            // 358
	{ C_F2, NULL, 15, 3, 1, 451 },                            // 359
	{ NULL, NULL, 12, 3, 1, 506 },                            // 360
	{ C_66, NULL, 13, 3, 1, 505 },                            // 361
	{ C_F3, NULL, 14, 3, 1, 508 },                            // 362
	{ C_F2, NULL, 15, 3, 1, 507 },                            // 363
	{ NULL, NULL, 83, 2, 1, 312 },                            // 364
	{ C_66, NULL, 5, 3, 1, 683 },                             // 365
	{ NULL, NULL, 83, 2, 1, 314 },                            // 366
	{ C_66, NULL, 5, 3, 1, 686 },                             // 367
	{ NULL, NULL, 83, 2, 1, 313 },                            // 368
	{ C_66, NULL, 5, 3, 1, 684 },                             // 369
	{ NULL, NULL, 83, 2, 1, 233 },                            // 370
	{ C_66, NULL, 5, 3, 1, 559 },                             // 371
	{ NULL, NULL, 84, 2, 1, 215 },                            // 372
	{ C_66, NULL, 76, 2, 1, 521 },                            // 373
	{ C_F3, NULL, 76, 2, 1, 522 },                            // 374
	{ C_66, NULL, 5, 3, 1, 689 },                             // 375
	{ C_66, NULL, 5, 3, 1, 685 },                             // 376
	{ NULL, NULL, 102, 2, 1, 545 },                           // 377
	{ NULL, NULL, 103, 2, 1, 551 },                           // 378
	{ C_F3, NULL, 108, 2, 1, 535 },                           // 379
	{ NULL, NULL, 105, 2, 1, 215 },                           // 380
	{ C_66, NULL, 107, 2, 1, 521 },                           // 381
	{ C_F3, NULL, 107, 2, 1, 522 },                           // 382
	{ C_66, NULL, 13, 3, 1, 494 },                            // 383
	{ C_F2, NULL, 12, 3, 1, 495 },                            // 384
	{ C_66, NULL, 13, 3, 1, 496 },                            // 385
	{ C_F2, NULL, 12, 3, 1, 497 },                            // 386
	{ NULL, S_f64, 29, 1, 1, 175 },                           // 387
	{ NULL, S_f64, 29, 1, 1, 169 },                           // 388
	{ NULL, S_f64, 29, 1, 2, 146 },                           // 389
	{ NULL, S_f64, 29, 1, 3, 140 },                           // 390
	{ NULL, S_f64, 29, 1, 2, 150 },                           // 391
	{ NULL, S_f64, 29, 1, 2, 163 },                           // 392
	{ NULL, S_f64, 29, 1, 2, 148 },                           // 393
	{ NULL, S_f64, 29, 1, 2, 138 },                           // 394
	{ NULL, NULL, 22, 1, 1, 369 },                            // 395
	{ NULL, NULL, 22, 1, 1, 365 },                            // 396
	{ NULL, NULL, 22, 1, 3, 348 },                            // 397
	{ NULL, NULL, 22, 1, 3, 345 },                            // 398
	{ NULL, NULL, 22, 1, 2, 353 },                            // 399
	{ NULL, NULL, 22, 1, 2, 359 },                            // 400
	{ NULL, NULL, 22, 1, 2, 351 },                            // 401
	{ NULL, NULL, 22, 1, 2, 343 },                            // 402
	{ NULL, S_d64, 30, 1, 1, 318 },                           // 403
	{ NULL, S_d64, 30, 1, 1, 279 },                           // 404
	{ NULL, NULL, 0, 0, 1, 101 },                             // 405
	{ NULL, NULL, 2, 2, 1, 50 },                              // 406
	{ NULL, NULL, 22, 3, 1, 377 },                            // 407
	{ NULL, NULL, 23, 3, 1, 377 },                            // 408
	{ NULL, NULL, 1, 2, 1, 99 },                              // 409
	{ NULL, NULL, 2, 2, 1, 99 },                              // 410
	{ NULL, NULL, 109, 2, 1, 203 },                           // 411
	{ NULL, NULL, 2, 2, 1, 52 },                              // 412
	{ NULL, NULL, 109, 2, 1, 190 },                           // 413
	{ NULL, NULL, 109, 2, 1, 192 },                           // 414
	{ NULL, NULL, 110, 2, 1, 220 },                           // 415
	{ NULL, NULL, 70, 2, 1, 220 },                            // 416
	{ NULL, NULL, 1, 2, 1, 727 },                             // 417
	{ NULL, NULL, 2, 2, 1, 727 },                             // 418
	{ NULL, NULL, 1, 4, 1, 426 },                             // 419
	{ C_66, NULL, 2, 4, 1, 425 },                             // 420
	{ C_F3, NULL, 4, 4, 1, 428 },                             // 421
	{ C_F2, NULL, 5, 4, 1, 427 },                             // 422
	{ NULL, NULL, 111, 2, 1, 213 },                           // 423
	{ NULL, NULL, 24, 3, 1, 266 },                            // 424
	{ C_66, NULL, 3, 4, 1, 616 },                             // 425
	{ NULL, NULL, 25, 3, 1, 259 },                            // 426
	{ C_66, NULL, 26, 3, 1, 606 },                            // 427
	{ NULL, NULL, 1, 4, 1, 701 },                             // 428
	{ C_66, NULL, 2, 4, 1, 700 },                             // 429
	{ NULL, NULL, 84, 2, 1, 303 },                            // 430
	{ C_66, NULL, 5, 3, 1, 673 },                             // 431
	{ NULL, NULL, 84, 2, 1, 301 },                            // 432
	{ C_66, NULL, 5, 3, 1, 669 },                             // 433
	{ NULL, NULL, 84, 2, 1, 302 },                            // 434
	{ C_66, NULL, 5, 3, 1, 671 },                             // 435
	{ NULL, NULL, 84, 2, 1, 238 },                            // 436
	{ C_66, NULL, 5, 3, 1, 565 },                             // 437
	{ NULL, NULL, 84, 2, 1, 277 },                            // 438
	{ C_66, NULL, 5, 3, 1, 650 },                             // 439
	{ NULL, NULL, 112, 2, 1, 273 },                           // 440
	{ C_66, NULL, 114, 2, 1, 632 },                           // 441
	{ C_66, NULL, 13, 3, 1, 405 },                            // 442
	{ C_F2, NULL, 12, 3, 1, 406 },                            // 443
	{ C_66, NULL, 113, 2, 1, 535 },                           // 444
	{ C_F3, NULL, 115, 2, 1, 216 },                           // 445
	{ C_F2, NULL, 116, 2, 1, 212 },                           // 446
	{ NULL, NULL, 84, 2, 1, 248 },                            // 447
	{ C_66, NULL, 5, 3, 1, 574 },                             // 448
	{ NULL, NULL, 84, 2, 1, 300 },                            // 449
	{ C_66, NULL, 5, 3, 1, 668 },                             // 450
	{ NULL, NULL, 84, 2, 1, 299 },                            // 451
	{ C_66, NULL, 5, 3, 1, 666 },                             // 452
	{ NULL, NULL, 84, 2, 1, 249 },                            // 453
	{ C_66, NULL, 5, 3, 1, 575 },                             // 454
	{ NULL, NULL, 84, 2, 1, 275 },                            // 455
	{ C_66, NULL, 5, 3, 1, 647 },                             // 456
	{ NULL, NULL, 84, 2, 1, 276 },                            // 457
	{ C_66, NULL, 5, 3, 1, 648 },                             // 458
	{ NULL, NULL, 117, 2, 1, 214 },                           // 459
	{ C_66, NULL, 119, 2, 1, 531 },                           // 460
	{ C_66, NULL, 118, 2, 1, 445 },                           // 461
	{ C_F3, NULL, 118, 2, 1, 431 },                           // 462
	{ C_F2, NULL, 118, 2, 1, 433 },                           // 463
	{ NULL, NULL, 84, 2, 1, 298 },                            // 464
	{ C_66, NULL, 5, 3, 1, 665 },                             // 465
	{ NULL, NULL, 84, 2, 1, 296 },                            // 466
	{ C_66, NULL, 5, 3, 1, 661 },                             // 467
	{ NULL, NULL, 84, 2, 1, 297 },                            // 468
	{ C_66, NULL, 5, 3, 1, 663 },                             // 469
	{ NULL, NULL, 84, 2, 1, 278 },                            // 470
	{ C_66, NULL, 5, 3, 1, 651 },                             // 471
	{ NULL, NULL, 84, 2, 1, 268 },                            // 472
	{ C_66, NULL, 5, 3, 1, 618 },                             // 473
	{ NULL, NULL, 84, 2, 1, 290 },                            // 474
	{ C_66, NULL, 5, 3, 1, 653 },                             // 475
	{ NULL, NULL, 120, 2, 1, 206 },                           // 476
	{ C_66, NULL, 121, 2, 1, 502 },                           // 477
	{ C_F2, NULL, 122, 2, 1, 501 },                           // 478
	{ NULL, S_f64, 29, 1, 1, 179 },                           // 479
	{ NULL, S_f64, 29, 1, 1, 172 },                           // 480
	{ NULL, S_f64, 29, 1, 2, 176 },                           // 481
	{ NULL, S_f64, 29, 1, 2, 170 },                           // 482
	{ NULL, S_f64, 29, 1, 2, 152 },                           // 483
	{ NULL, S_f64, 29, 1, 2, 165 },                           // 484
	{ NULL, S_f64, 29, 1, 2, 154 },                           // 485
	{ NULL, S_f64, 29, 1, 2, 167 },                           // 486
	{ NULL, NULL, 22, 1, 1, 372 },                            // 487
	{ NULL, NULL, 22, 1, 1, 368 },                            // 488
	{ NULL, NULL, 22, 1, 2, 370 },                            // 489
	{ NULL, NULL, 22, 1, 2, 366 },                            // 490
	{ NULL, NULL, 22, 1, 2, 355 },                            // 491
	{ NULL, NULL, 22, 1, 2, 361 },                            // 492
	{ NULL, NULL, 22, 1, 2, 357 },                            // 493
	{ NULL, NULL, 22, 1, 2, 363 },                            // 494
	{ NULL, S_d64, 31, 1, 1, 318 },                           // 495
	{ NULL, S_d64, 31, 1, 1, 279 },                           // 496
	{ NULL, NULL, 0, 0, 1, 337 },                             // 497
	{ NULL, NULL, 2, 2, 1, 53 },                              // 498
	{ NULL, NULL, 22, 3, 1, 380 },                            // 499
	{ NULL, NULL, 23, 3, 1, 380 },                            // 500
	{ NULL, NULL, 4, 2, 1, 125 },                             // 501
	{ NULL, NULL, 0, 0, 1, 157 },                             // 502
	{ C_F3, NULL, 4, 2, 1, 282 },                             // 503
	{ NULL, NULL, 2, 2, 1, 51 },                              // 504
	{ NULL, NULL, 4, 2, 1, 47 },                              // 505
	{ C_F3, NULL, 4, 2, 1, 399 },                             // 506
	{ NULL, NULL, 4, 2, 1, 48 },                              // 507
	{ C_F3, NULL, 4, 2, 1, 205 },                             // 508
	{ NULL, NULL, 110, 2, 1, 218 },                           // 509
	{ NULL, NULL, 70, 2, 1, 218 },                            // 510
	{ NULL, NULL, 32, 1, 1, 49 },                             // 511
	{ NULL, NULL, 33, 1, 1, 49 },                             // 512
	{ NULL, NULL, 34, 1, 1, 49 },                             // 513
	{ NULL, NULL, 35, 1, 1, 49 },                             // 514
	{ NULL, NULL, 36, 1, 1, 49 },                             // 515
	{ NULL, NULL, 37, 1, 1, 49 },                             // 516
	{ NULL, NULL, 38, 1, 1, 49 },                             // 517
	{ NULL, NULL, 39, 1, 1, 49 },                             // 518
	{ NULL, NULL, 84, 2, 1, 309 },                            // 519
	{ C_66, NULL, 5, 3, 1, 679 },                             // 520
	{ NULL, NULL, 84, 2, 1, 310 },                            // 521
	{ C_66, NULL, 5, 3, 1, 680 },                             // 522
	{ NULL, NULL, 84, 2, 1, 272 },                            // 523
	{ C_66, NULL, 5, 3, 1, 629 },                             // 524
	{ NULL, NULL, 84, 2, 1, 245 },                            // 525
	{ C_66, NULL, 5, 3, 1, 572 },                             // 526
	{ NULL, NULL, 84, 2, 1, 241 },                            // 527
	{ C_66, NULL, 5, 3, 1, 568 },                             // 528
	{ NULL, NULL, 84, 2, 1, 242 },                            // 529
	{ C_66, NULL, 5, 3, 1, 569 },                             // 530
	{ NULL, NULL, 84, 2, 1, 270 },                            // 531
	{ C_66, NULL, 5, 3, 1, 623 },                             // 532
	{ NULL, NULL, 84, 2, 1, 246 },                            // 533
	{ C_66, NULL, 5, 3, 1, 573 },                             // 534
	{ NULL, NULL, 84, 2, 1, 307 },                            // 535
	{ C_66, NULL, 5, 3, 1, 677 },                             // 536
	{ NULL, NULL, 84, 2, 1, 308 },                            // 537
	{ C_66, NULL, 5, 3, 1, 678 },                             // 538
	{ NULL, NULL, 84, 2, 1, 271 },                            // 539
	{ C_66, NULL, 5, 3, 1, 628 },                             // 540
	{ NULL, NULL, 84, 2, 1, 284 },                            // 541
	{ C_66, NULL, 5, 3, 1, 652 },                             // 542
	{ NULL, NULL, 84, 2, 1, 239 },                            // 543
	{ C_66, NULL, 5, 3, 1, 566 },                             // 544
	{ NULL, NULL, 84, 2, 1, 240 },                            // 545
	{ C_66, NULL, 5, 3, 1, 567 },                             // 546
	{ NULL, NULL, 84, 2, 1, 269 },                            // 547
	{ C_66, NULL, 5, 3, 1, 622 },                             // 548
	{ NULL, NULL, 84, 2, 1, 322 },                            // 549
	{ C_66, NULL, 5, 3, 1, 691 },                             // 550
	{ NULL, NULL, 84, 2, 1, 304 },                            // 551
	{ C_66, NULL, 5, 3, 1, 674 },                             // 552
	{ NULL, NULL, 84, 2, 1, 311 },                            // 553
	{ C_66, NULL, 5, 3, 1, 681 },                             // 554
	{ NULL, NULL, 84, 2, 1, 305 },                            // 555
	{ C_66, NULL, 5, 3, 1, 675 },                             // 556
	{ NULL, NULL, 84, 2, 1, 306 },                            // 557
	{ C_66, NULL, 5, 3, 1, 676 },                             // 558
	{ NULL, NULL, 84, 2, 1, 236 },                            // 559
	{ C_66, NULL, 5, 3, 1, 563 },                             // 560
	{ NULL, NULL, 84, 2, 1, 243 },                            // 561
	{ C_66, NULL, 5, 3, 1, 570 },                             // 562
	{ NULL, NULL, 84, 2, 1, 237 },                            // 563
	{ C_66, NULL, 5, 3, 1, 564 },                             // 564
	{ NULL, NULL, 84, 2, 1, 291 },                            // 565
	{ C_66, NULL, 5, 3, 1, 654 },                             // 566
	{ NULL, NULL, 84, 2, 1, 262 },                            // 567
	{ C_66, NULL, 5, 3, 1, 609 },                             // 568
	{ NULL, NULL, 84, 2, 1, 260 },                            // 569
	{ C_66, NULL, 5, 3, 1, 607 },                             // 570
	{ NULL, NULL, 84, 2, 1, 261 },                            // 571
	{ C_66, NULL, 5, 3, 1, 608 },                             // 572
	{ NULL, NULL, 84, 2, 1, 267 },                            // 573
	{ C_66, NULL, 5, 3, 1, 617 },                             // 574
	{ NULL, NULL, 84, 2, 1, 265 },                            // 575
	{ C_66, NULL, 5, 3, 1, 613 },                             // 576
	{ NULL, NULL, 84, 2, 1, 263 },                            // 577
	{ C_66, NULL, 5, 3, 1, 611 },                             // 578
	{ NULL, NULL, 84, 2, 1, 264 },                            // 579
	{ C_66, NULL, 5, 3, 1, 612 },                             // 580
	{ C_66, NULL, 123, 2, 1, 250 },                           // 581
	{ C_66, S_v, 17, 3, 1, 435 },                             // 582
	{ C_66, NULL, 123, 2, 1, 42 },                            // 583
	{ C_66, NULL, 123, 2, 1, 41 },                            // 584
	{ C_66, S_v, 27, 3, 1, 602 },                             // 585
	{ C_66, NULL, 76, 2, 1, 682 },                            // 586
	{ C_66, NULL, 124, 2, 1, 635 },                           // 587
	{ C_66, NULL, 125, 2, 1, 633 },                           // 588
	{ C_66, NULL, 126, 2, 1, 634 },                           // 589
	{ C_66, NULL, 124, 2, 1, 637 },                           // 590
	{ C_66, NULL, 125, 2, 1, 638 },                           // 591
	{ C_66, NULL, 124, 2, 1, 636 },                           // 592
	{ C_66, NULL, 124, 2, 1, 641 },                           // 593
	{ C_66, NULL, 125, 2, 1, 639 },                           // 594
	{ C_66, NULL, 126, 2, 1, 640 },                           // 595
	{ C_66, NULL, 124, 2, 1, 643 },                           // 596
	{ C_66, NULL, 125, 2, 1, 644 },                           // 597
	{ C_66, NULL, 124, 2, 1, 642 },                           // 598
	{ C_66, S_v, 27, 3, 1, 598 },                             // 599
	{ C_66, NULL, 5, 3, 1, 592 },                             // 600
	{ C_66, NULL, 5, 3, 1, 649 },                             // 601
	{ C_66, NULL, 123, 2, 1, 610 },                           // 602
	{ C_66, S_v, 5, 3, 1, 667 },                              // 603
	{ C_66, NULL, 127, 2, 1, 133 },                           // 604
	{ C_66, NULL, 127, 2, 1, 136 },                           // 605
	{ C_66, NULL, 127, 2, 1, 135 },                           // 606
	{ NULL, NULL, 128, 2, 1, 210 },                           // 607
	{ C_66, NULL, 129, 2, 1, 210 },                           // 608
	{ C_F2, NULL, 131, 2, 1, 102 },                           // 609
	{ C_66 | C_F2, NULL, 131, 2, 1, 102 },                    // 610
	{ NULL, NULL, 111, 2, 1, 210 },                           // 611
	{ C_66, NULL, 130, 2, 1, 210 },                           // 612
	{ C_F2, NULL, 132, 2, 1, 102 },                           // 613
	{ C_66 | C_F2, NULL, 133, 2, 1, 102 },                    // 614
	{ NULL, S_v, 28, 3, 1, 38 },                              // 615
	{ NULL, S_v, 29, 3, 1, 54 },                              // 616
	{ C_F3, S_v, 28, 3, 1, 258 },                             // 617
	{ C_F2, S_v, 28, 3, 1, 257 },                             // 618
	{ NULL, S_v, 29, 3, 1, 40 },                              // 619
	{ C_66, S_v, 29, 3, 1, 378 },                             // 620
	{ C_F3, S_v, 29, 3, 1, 340 },                             // 621
	{ C_F2, S_v, 29, 3, 1, 381 },                             // 622
	{ C_66, NULL, 103, 2, 1, 34 },                            // 623
	{ C_F3, NULL, 103, 2, 1, 36 },                            // 624
	{ C_F2, S_v, 6, 4, 1, 222 },                              // 625
	{ NULL, NULL, 84, 2, 1, 293 },                            // 626
	{ C_66, NULL, 5, 3, 1, 658 },                             // 627
	{ NULL, NULL, 84, 2, 1, 295 },                            // 628
	{ C_66, NULL, 5, 3, 1, 660 },                             // 629
	{ NULL, NULL, 84, 2, 1, 294 },                            // 630
	{ C_66, NULL, 5, 3, 1, 659 },                             // 631
	{ NULL, NULL, 84, 2, 1, 274 },                            // 632
	{ C_66, NULL, 5, 3, 1, 646 },                             // 633
	{ C_66, S_v, 5, 3, 1, 600 },                              // 634
	{ C_66, S_v, 5, 3, 1, 599 },                              // 635
	{ C_66, S_v, 76, 2, 1, 711 },                             // 636
	{ C_66, S_v, 76, 2, 1, 710 },                             // 637
	{ NULL, NULL, 84, 2, 1, 230 },                            // 638
	{ C_66, NULL, 76, 2, 1, 556 },                            // 639
	{ NULL, NULL, 84, 2, 1, 232 },                            // 640
	{ C_66, NULL, 76, 2, 1, 558 },                            // 641
	{ NULL, NULL, 84, 2, 1, 231 },                            // 642
	{ C_66, NULL, 76, 2, 1, 557 },                            // 643
	{ C_66, S_v, 134, 2, 1, 424 },                            // 644
	{ C_66, S_v, 135, 2, 1, 423 },                            // 645
	{ C_66, S_v, 136, 2, 1, 421 },                            // 646
	{ C_66, NULL, 5, 3, 1, 645 },                             // 647
	{ C_66, NULL, 5, 3, 1, 586 },                             // 648
	{ C_66, NULL, 122, 2, 1, 532 },                           // 649
	{ C_66, NULL, 5, 3, 1, 561 },                             // 650
	{ C_66, S_v, 30, 3, 1, 504 },                             // 651
	{ C_66, S_v, 30, 3, 1, 503 },                             // 652
	{ C_66, S_v, 31, 3, 1, 504 },                             // 653
	{ C_66, S_v, 31, 3, 1, 503 },                             // 654
	{ C_66, NULL, 5, 3, 1, 626 },                             // 655
	{ C_66, NULL, 5, 3, 1, 627 },                             // 656
	{ C_66, NULL, 5, 3, 1, 631 },                             // 657
	{ C_66, NULL, 5, 3, 1, 630 },                             // 658
	{ C_66, NULL, 5, 3, 1, 620 },                             // 659
	{ C_66, NULL, 5, 3, 1, 621 },                             // 660
	{ C_66, NULL, 5, 3, 1, 625 },                             // 661
	{ C_66, NULL, 5, 3, 1, 624 },                             // 662
	{ C_66, S_v, 76, 2, 1, 580 },                             // 663
	{ C_66, S_v, 76, 2, 1, 581 },                             // 664
	{ C_66, S_v, 136, 2, 1, 422 },                            // 665
	{ C_66, S_v, 76, 2, 1, 579 },                             // 666
	{ C_66, S_v, 76, 2, 1, 582 },                             // 667
	{ C_66, NULL, 123, 2, 1, 411 },                           // 668
	{ C_66, NULL, 33, 3, 1, 409 },                            // 669
	{ C_66, NULL, 33, 3, 1, 410 },                            // 670
	{ C_66, NULL, 33, 3, 1, 407 },                            // 671
	{ C_66, NULL, 33, 3, 1, 408 },                            // 672
	{ C_66, S_v, 34, 3, 1, 603 },                             // 673
	{ C_66, S_v, 34, 3, 1, 601 },                             // 674
	{ C_66, S_v, 7, 4, 1, 576 },                              // 675
	{ C_66, S_v, 17, 3, 1, 600 },                             // 676
	{ C_66, S_v, 17, 3, 1, 599 },                             // 677
	{ C_66, S_v, 8, 4, 1, 596 },                              // 678
	{ C_66, NULL, 35, 3, 1, 604 },                            // 679
	{ C_66, NULL, 36, 3, 1, 606 },                            // 680
	{ C_66, NULL, 38, 3, 1, 459 },                            // 681
	{ C_66, NULL, 9, 4, 1, 614 },                             // 682
	{ C_66, NULL, 10, 4, 1, 500 },                            // 683
	{ C_66, NULL, 7, 4, 1, 454 },                             // 684
	{ C_66, NULL, 12, 4, 1, 453 },                            // 685
	{ C_66, NULL, 7, 4, 1, 542 },                             // 686
	{ C_66, NULL, 12, 4, 1, 583 },                            // 687
	{ C_66, S_v, 8, 4, 1, 597 },                              // 688
	{ C_66, NULL, 39, 3, 1, 589 },                            // 689
	{ C_66, NULL, 39, 3, 1, 588 },                            // 690
	{ C_66, NULL, 39, 3, 1, 595 },                            // 691
	{ C_66, NULL, 39, 3, 1, 594 },                            // 692
	{ C_F2, S_v, 40, 3, 1, 336 },                             // 693
	{ NULL, NULL, 16, 3, 1, 244 },                            // 694
	{ C_66, NULL, 7, 4, 1, 571 },                             // 695
	{ C_66, NULL, 17, 3, 1, 695 },                            // 696
	{ C_66, S_v, 8, 4, 1, 498 },                              // 697
	{ C_66, NULL, 17, 3, 1, 694 },                            // 698
	{ C_66, S_v, 43, 3, 1, 457 },                             // 699
	{ C_66, NULL, 41, 3, 1, 697 },                            // 700
	{ C_66, NULL, 42, 3, 1, 696 },                            // 701
	{ C_66, NULL, 7, 4, 1, 418 },                             // 702
	{ C_66, NULL, 7, 4, 1, 417 },                             // 703
	{ C_66, S_v, 44, 3, 1, 438 },                             // 704
	{ C_66, NULL, 7, 4, 1, 578 },                             // 705
	{ C_66, S_v, 8, 4, 1, 499 },                              // 706
	{ C_66, S_v, 43, 3, 1, 458 },                             // 707
	{ C_66, S_v, 13, 4, 1, 420 },                             // 708
	{ C_66, S_v, 13, 4, 1, 419 },                             // 709
	{ C_66, S_v, 13, 4, 1, 577 },                             // 710
	{ C_66, NULL, 39, 3, 1, 412 },                            // 711
};
const InstChangeData InstChange[] =
{
	{ NULL, NULL, 24, 2, 1, 217, Ext_B },                     // 0
	{ NULL, NULL, 25, 2, 1, 217, Ext_W | Ext_D | Ext_Q },     // 1
	{ NULL, NULL, 26, 2, 1, 97, Ext_B },                      // 2
	{ NULL, NULL, 27, 2, 1, 97, Ext_W | Ext_D },              // 3
	{ NULL, NULL, 0, 0, 1, 732, Ext_B },                      // 4
	{ NULL, NULL, 44, 2, 1, 128, Ext_B },                     // 5
	{ NULL, NULL, 45, 2, 1, 128, Ext_W | Ext_D },             // 6
	{ NULL, NULL, 46, 2, 1, 229, Ext_B },                     // 7
	{ NULL, NULL, 47, 2, 1, 229, Ext_W | Ext_D },             // 8
	{ NULL, S_d64, 28, 1, 1, 321, Ext_D | Ext_Q },            // 9
	{ NULL, S_d64, 28, 1, 1, 283, Ext_D | Ext_Q },            // 10
	{ NULL, NULL, 51, 2, 1, 390, Ext_B },                     // 11
	{ NULL, NULL, 52, 2, 1, 390, Ext_W | Ext_D | Ext_Q },     // 12
	{ NULL, NULL, 53, 2, 1, 196, Ext_B },                     // 13
	{ NULL, NULL, 54, 2, 1, 196, Ext_W | Ext_D | Ext_Q },     // 14
	{ NULL, NULL, 55, 2, 1, 342, Ext_B },                     // 15
	{ NULL, NULL, 56, 2, 1, 342, Ext_W | Ext_D | Ext_Q },     // 16
	{ NULL, NULL, 0, 0, 1, 137, Ext_D | Ext_Q },              // 17
	{ NULL, NULL, 100, 2, 1, 211, Ext_Q },                    // 18
	{ C_66, NULL, 101, 2, 1, 519, Ext_Q },                    // 19
	{ NULL, NULL, 104, 2, 1, 211, Ext_Q },                    // 20
	{ C_66, NULL, 106, 2, 1, 519, Ext_Q },                    // 21
	{ C_66, S_v, 5, 3, 1, 672, Ext_Q },                       // 22
	{ C_66, S_v, 5, 3, 1, 664, Ext_Q },                       // 23
	{ C_66, S_v, 5, 3, 1, 490, Ext_Q },                       // 24
	{ C_66, S_v, 5, 3, 1, 492, Ext_Q },                       // 25
	{ C_66, S_v, 5, 3, 1, 491, Ext_D },                       // 26
	{ C_66, S_v, 5, 3, 1, 493, Ext_D },                       // 27
	{ C_66, S_v, 5, 3, 1, 466, Ext_D },                       // 28
	{ C_66, S_v, 5, 3, 1, 475, Ext_D },                       // 29
	{ C_66, S_v, 5, 3, 1, 467, Ext_D },                       // 30
	{ C_66, S_v, 5, 3, 1, 476, Ext_D },                       // 31
	{ C_66, S_v, 5, 3, 1, 468, Ext_D },                       // 32
	{ C_66, S_v, 5, 3, 1, 477, Ext_D },                       // 33
	{ C_66, S_v, 30, 3, 1, 619, Ext_Q },                      // 34
	{ C_66, S_v, 32, 3, 1, 619, Ext_Q },                      // 35
	{ C_66, S_v, 5, 3, 1, 460, Ext_D },                       // 36
	{ C_66, S_v, 5, 3, 1, 461, Ext_D },                       // 37
	{ C_66, S_v, 5, 3, 1, 469, Ext_D },                       // 38
	{ C_66, S_v, 5, 3, 1, 470, Ext_D },                       // 39
	{ C_66, S_v, 5, 3, 1, 478, Ext_D },                       // 40
	{ C_66, S_v, 5, 3, 1, 479, Ext_D },                       // 41
	{ C_66, S_v, 5, 3, 1, 484, Ext_D },                       // 42
	{ C_66, S_v, 5, 3, 1, 485, Ext_D },                       // 43
	{ C_66, S_v, 5, 3, 1, 462, Ext_D },                       // 44
	{ C_66, S_v, 5, 3, 1, 463, Ext_D },                       // 45
	{ C_66, S_v, 5, 3, 1, 471, Ext_D },                       // 46
	{ C_66, S_v, 5, 3, 1, 472, Ext_D },                       // 47
	{ C_66, S_v, 5, 3, 1, 480, Ext_D },                       // 48
	{ C_66, S_v, 5, 3, 1, 481, Ext_D },                       // 49
	{ C_66, S_v, 5, 3, 1, 486, Ext_D },                       // 50
	{ C_66, S_v, 5, 3, 1, 487, Ext_D },                       // 51
	{ C_66, S_v, 5, 3, 1, 464, Ext_D },                       // 52
	{ C_66, S_v, 5, 3, 1, 465, Ext_D },                       // 53
	{ C_66, S_v, 5, 3, 1, 473, Ext_D },                       // 54
	{ C_66, S_v, 5, 3, 1, 474, Ext_D },                       // 55
	{ C_66, S_v, 5, 3, 1, 482, Ext_D },                       // 56
	{ C_66, S_v, 5, 3, 1, 483, Ext_D },                       // 57
	{ C_66, S_v, 5, 3, 1, 488, Ext_D },                       // 58
	{ C_66, S_v, 5, 3, 1, 489, Ext_D },                       // 59
	{ C_66, NULL, 37, 3, 1, 605, Ext_Q },                     // 60
	{ C_66, NULL, 11, 4, 1, 615, Ext_Q },                     // 61
};

const PrefixInstData PfxInst[] =
{
	{ NULL, PfxGrp_2, 23 },                                   // 0
	{ NULL, PfxGrp_2, 26 },                                   // 1
	{ S_o64, PfxGrp_Rex, 5 },                                 // 2
	{ S_o64, PfxGrp_Rex, 6 },                                 // 3
	{ S_o64, PfxGrp_Rex, 19 },                                // 4
	{ S_o64, PfxGrp_Rex, 20 },                                // 5
	{ S_o64, PfxGrp_Rex, 7 },                                 // 6
	{ S_o64, PfxGrp_Rex, 8 },                                 // 7
	{ S_o64, PfxGrp_Rex, 9 },                                 // 8
	{ S_o64, PfxGrp_Rex, 10 },                                // 9
	{ NULL, PfxGrp_2, 24 },                                   // 10
	{ NULL, PfxGrp_2, 25 },                                   // 11
	{ NULL, PfxGrp_3, 2 },                                    // 12
	{ NULL, PfxGrp_4, 0 },                                    // 13
	{ NULL, PfxGrp_Vex, 28 },                                 // 14
	{ NULL, PfxGrp_Vex, 27 },                                 // 15
	{ NULL, PfxGrp_1, 1 },                                    // 16
	{ NULL, PfxGrp_1, 3 },                                    // 17
	{ NULL, PfxGrp_1, 4 },                                    // 18
	{ NULL, PfxGrp_2, 21 },                                   // 19
	{ NULL, PfxGrp_2, 22 },                                   // 20
	{ S_o64, PfxGrp_Rex, 11 },                                // 21
	{ S_o64, PfxGrp_Rex, 12 },                                // 22
	{ S_o64, PfxGrp_Rex, 17 },                                // 23
	{ S_o64, PfxGrp_Rex, 18 },                                // 24
	{ S_o64, PfxGrp_Rex, 13 },                                // 25
	{ S_o64, PfxGrp_Rex, 14 },                                // 26
	{ S_o64, PfxGrp_Rex, 15 },                                // 27
	{ S_o64, PfxGrp_Rex, 16 },                                // 28
};

const GrpInstData GrpInst[] =
{
	{ NULL, 9, 2, Grp_1 },                                    // 0
	{ NULL, 10, 2, Grp_1 },                                   // 1
	{ S_i64, 9, 2, Grp_1 },                                   // 2
	{ NULL, 11, 2, Grp_1 },                                   // 3
	{ NULL, 9, 2, Grp_2 },                                    // 4
	{ NULL, 11, 2, Grp_2 },                                   // 5
	{ NULL, 0, 0, Grp_11_C6 },                                // 6
	{ NULL, 0, 0, Grp_11_C7 },                                // 7
	{ NULL, 37, 2, Grp_2 },                                   // 8
	{ NULL, 38, 2, Grp_2 },                                   // 9
	{ NULL, 39, 2, Grp_2 },                                   // 10
	{ NULL, 40, 2, Grp_2 },                                   // 11
	{ NULL, 22, 1, Grp_3 },                                   // 12
	{ NULL, 23, 1, Grp_3 },                                   // 13
	{ NULL, 0, 0, Grp_1A },                                   // 14
	{ NULL, 0, 0, Grp_4 },                                    // 15
	{ NULL, 0, 0, Grp_5 },                                    // 16
	{ NULL, 0, 0, Grp_6 },                                    // 17
	{ NULL, 0, 0, Grp_7 },                                    // 18
	{ NULL, 0, 0, Grp_12 },                                   // 19
	{ NULL, 0, 0, Grp_13 },                                   // 20
	{ NULL, 0, 0, Grp_14 },                                   // 21
	{ NULL, 0, 0, Grp_16 },                                   // 22
	{ NULL, 0, 0, Grp_9 },                                    // 23
	{ S_1C, 0, 0, Grp_15 },                                   // 24
	{ NULL, 0, 0, Grp_10 },                                   // 25
	{ NULL, 11, 2, Grp_8 },                                   // 26
	{ NULL, 0, 0, Grp_17 },                                   // 27
};



