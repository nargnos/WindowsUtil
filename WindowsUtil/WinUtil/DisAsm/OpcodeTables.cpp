#include "OpcodeTables.h"
namespace Asm
{
	UINT8 GetAsmCmdLen(PVOID code)
	{
		return 0;
	}
	POpcode Hex2Opcode(BYTE hex, Tables table)
	{
		return (POpcode)&OpcodeMap[table][hex];
	}
	BYTE PrefixByteToGroup(BYTE prefix)
	{
		
		switch (prefix)
		{
		case (BYTE)0xf0:
		case (BYTE)0xf2:
		case (BYTE)0xf3:
			return 1;
		case (BYTE)0x2e:
		case (BYTE)0x36:
		case (BYTE)0x3e:
		case (BYTE)0x26:
		case (BYTE)0x64:
		case (BYTE)0x65:
			return 2;
		case (BYTE)0x66:
			return 3;
		case (BYTE)0x67:
			return 4;
		default:
			return 0; // 非prefix
		}
	}
	const Opcode OneByteOpcodeMap[0x100] =
	{
		// 00-0f
		HEX_CMD(2,0), HEX_CMD(2,1), HEX_CMD(2,2), HEX_CMD(2,3), HEX_CMD(2,4), HEX_CMD(2,5),/* add */HEX_CMD(1,0),/* push es */HEX_CMD(1,1),/* pop es */
		HEX_CMD(2,61), HEX_CMD(2,62), HEX_CMD(2,63),HEX_CMD(2,64), HEX_CMD(2,65), HEX_CMD(2,66),/* or */HEX_CMD(1,35), /* push cs */HEX_TABLE(TwoByteTable),/* 2B */

		// 10-1f

		HEX_CMD(2,6),HEX_CMD(2,7),HEX_CMD(2,8),HEX_CMD(2,9),HEX_CMD(2,10),HEX_CMD(2,11),/* adc */HEX_CMD(1,2),/* push ss */HEX_CMD(1,3),/* pop ss */
		HEX_CMD(2,67),HEX_CMD(2,68), HEX_CMD(2,69), HEX_CMD(2,70), HEX_CMD(2,71),HEX_CMD(2,72),/* sbb */HEX_CMD(1,36),/* push ds */HEX_CMD(1,37),/* pop ds */

		// 20-2f

		HEX_CMD(2,12),HEX_CMD(2,13),HEX_CMD(2,14),HEX_CMD(2,15),HEX_CMD(2,16),HEX_CMD(2,17),/* and */HEX_PREFIX(2,7), HEX_CMD(0,0),
		HEX_CMD(2,73), HEX_CMD(2,74), HEX_CMD(2,75), HEX_CMD(2,76), HEX_CMD(2,77), HEX_CMD(2,78),/* sub */HEX_PREFIX(2,5),/* seg=cs (prefix) */HEX_CMD(0,9),/* das */

		// 30-3f

		HEX_CMD(2,18),HEX_CMD(2,19),HEX_CMD(2,20),HEX_CMD(2,21),HEX_CMD(2,22),HEX_CMD(2,23),/* xor */HEX_PREFIX(2,10), HEX_CMD(0,1),
		HEX_CMD(2,79), HEX_CMD(2,80), HEX_CMD(2,81), HEX_CMD(2,82), HEX_CMD(2,83), HEX_CMD(2,84),/* cmp */HEX_PREFIX(2,6),/* seg=ds (prefix) */HEX_CMD(0,10),/* aas */

		// 40-4f

		HEX_CMD(1,4), HEX_CMD(1,5), HEX_CMD(1,6), HEX_CMD(1,7), HEX_CMD(1,8), HEX_CMD(1,9), HEX_CMD(1,10), HEX_CMD(1,11), /* inc */
		HEX_CMD(1,38), HEX_CMD(1,39), HEX_CMD(1,40), HEX_CMD(1,41), HEX_CMD(1,42), HEX_CMD(1,43), HEX_CMD(1,44), HEX_CMD(1,45),/* dec */

		// 50-5f

		HEX_CMD(1,12), HEX_CMD(1,13), HEX_CMD(1,14), HEX_CMD(1,15), HEX_CMD(1,16), HEX_CMD(1,17), HEX_CMD(1,18), HEX_CMD(1,19), /* push */
		HEX_CMD(1,46), HEX_CMD(1,47), HEX_CMD(1,48), HEX_CMD(1,49), HEX_CMD(1,50), HEX_CMD(1,51), HEX_CMD(1,52), HEX_CMD(1,53),/* pop */

		// 60-6f

		HEX_CMD(0,2),/* pusha */HEX_CMD(0,3),/* popa */HEX_CMD(2,24),/* bound */HEX_ARRAY(2,0),/* arpl / movsxd */HEX_PREFIX(2,8),/* seg=fs (prefix)*/HEX_PREFIX(2,9),/* seg=gs (prefix) */HEX_PREFIX(3,2),/* operand size (prefix) */HEX_PREFIX(4,0),/* address size (prefix) */
		HEX_CMD(1,54), /* push */HEX_CMD(3,0),/* imul */HEX_CMD(1,55),/* push */HEX_CMD(3,1),/* imul */HEX_CMD(2,85),HEX_CMD(2,86),/* ins */HEX_CMD(2,87), HEX_CMD(2,88),/* outs */

		// 70-7f

		HEX_CMD(1,20),/* jo */HEX_CMD(1,21),/* jno */HEX_CMD(1,22),/* jb */HEX_CMD(1,23),/* jnb */HEX_CMD(1,24), /* jz */HEX_CMD(1,25),/* jnz */HEX_CMD(1,26), /* jbe */HEX_CMD(1,27), /* ja */
		HEX_CMD(1,56), /* js */HEX_CMD(1,57),/* jns */HEX_CMD(1,58),/* jp */HEX_CMD(1,59),/* jnp */HEX_CMD(1,60),/* jl */HEX_CMD(1,61),/* jnl */HEX_CMD(1,62),/* jng */HEX_CMD(1,63),/* jg */

		// 80-8f

		HEX_GROUP(1,2,0), HEX_GROUP(1,2,1), HEX_GROUP(1,2,2), HEX_GROUP(1,2,3),/* grp 1 */HEX_CMD(2,27), HEX_CMD(2,28), /* test */HEX_CMD(2,29), HEX_CMD(2,30),/* xchg */
		HEX_CMD(2,89), HEX_CMD(2,90),HEX_CMD(2,91), HEX_CMD(2,92), HEX_CMD(2,93),/* mov */HEX_CMD(2,94),/* lea */HEX_CMD(2,95), /* mov */HEX_GROUP(18,1,2),/* grp1 */

		// 90-9f

		HEX_ARRAY(2,1),/* nop */HEX_CMD(2,32), HEX_CMD(2,33), HEX_CMD(2,34), HEX_CMD(2,35), HEX_CMD(2,36), HEX_CMD(2,37), HEX_CMD(2,38) ,/* xchg */
		HEX_CMD(0,11), /* cbw */HEX_CMD(0,12),/* cwd */HEX_CMD(1,64),/* call */HEX_CMD(0,13),/* wait */HEX_CMD(1,65),/* pushf/d/q */HEX_CMD(1,66),/* popf/d/q */HEX_CMD(0,14),/* sahf */HEX_CMD(0,15),/* lahf */

		// a0-af

		HEX_CMD(2,39), HEX_CMD(2,40), HEX_CMD(2,41), HEX_CMD(2,42), /* mov */HEX_CMD(2,43),/* movs/b */HEX_CMD(2,44),/* movs/w/d/q */HEX_CMD(2,45),/* cmps/b */HEX_CMD(2,46),/* cmps/w/d */
		HEX_CMD(2,96),HEX_CMD(2,97), /* test */HEX_CMD(2,98), /* stos/b */HEX_CMD(2,99),/* stos/w/d/q */HEX_CMD(2,100),/* lods/b */HEX_CMD(2,101),/* lods/w/d/q */HEX_CMD(2,102),/* scas/b */HEX_CMD(2,103),/* scas/w/d/q */

		// b0-bf

		HEX_CMD(2,47), HEX_CMD(2,48), HEX_CMD(2,49), HEX_CMD(2,50), HEX_CMD(2,51), HEX_CMD(2,52), HEX_CMD(2,53), HEX_CMD(2,54),/* mov */
		HEX_CMD(2,104), HEX_CMD(2,105), HEX_CMD(2,106), HEX_CMD(2,107), HEX_CMD(2,108), HEX_CMD(2,109), HEX_CMD(2,110),HEX_CMD(2,111),/* mov */

		// c0-cf

		HEX_GROUP(2,2,0), HEX_GROUP(2,2,3),/* grp2 */HEX_CMD(1,28),HEX_CMD(0,5),/* ret */HEX_CMD(2,55),/* les */HEX_CMD(2,56),/* lds */HEX_GROUP(11,2,0), HEX_GROUP(11,2,1),/* grp 11 */
		HEX_CMD(2,112), /* enter */HEX_CMD(0,16),/* leave */HEX_CMD(1,67), HEX_CMD(0,17),/* ret */HEX_CMD(0,18),/* int 3 */HEX_CMD(1,68),/* int */HEX_CMD(0,19),/* into */HEX_CMD(0,20),/* iret/d/q */

		// d0-df

		HEX_GROUP(2,2,4), HEX_GROUP(2,2,5), HEX_GROUP(2,2,6), HEX_GROUP(2,2,7),/* grp2 */HEX_CMD(1,29),/* aam */HEX_CMD(1,30)/* aad */,{ 0 },/* salc */HEX_CMD(0,6),/* xlat */
		{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },/* esc */

		// e0-ef

		HEX_CMD(1,31),/* loopne */HEX_CMD(1,32),/* loope */HEX_CMD(1,33), /* loop */HEX_CMD(1,34),/* jrcxz */HEX_CMD(2,57), HEX_CMD(2,58),/* in */HEX_CMD(2,59), HEX_CMD(2,60),/* out */
		HEX_CMD(1,69), /* call */HEX_CMD(1,70), HEX_CMD(1,71), HEX_CMD(1,72),/* jmp */HEX_CMD(2,113), HEX_CMD(2,114),/* in */HEX_CMD(2,115), HEX_CMD(2,116),/* out */

		// f0-ff

		HEX_PREFIX(1,1), /* lock(prefix) */{ 0 }, /* int1 */HEX_PREFIX(1,3),/* repne */HEX_PREFIX(1,4), /* rep */HEX_CMD(0,7), /* hlt */HEX_CMD(0,8),/* cmc */HEX_GROUP(3,1,0), HEX_GROUP(3,1,1),/* grp3 */
		HEX_CMD(0,21),/* clc */HEX_CMD(0,22),/* stc */HEX_CMD(0,23), /* cli */HEX_CMD(0,24),/* sti */HEX_CMD(0,25),/* cld */HEX_CMD(0,26),/* std */HEX_GROUP(4,0,0),/* grp4 */HEX_GROUP(4,0,0),/* grp5 */

	};
	const Opcode TwoByteOpcodeMap[0x100] =
	{
		// 00-0f

		{ 0 },/* grp6 */{ 0 },/* grp7 */HEX_CMD(2,117), /* lar */HEX_CMD(2,118),/* lsl */{ 0 },/* ??? */ HEX_CMD(0,27),/* syscall */ HEX_CMD(0,28),/* clts */ HEX_CMD(0,29),/* sysret */
		HEX_CMD(0,39),/* invd */HEX_CMD(0,40),/* wbinvd */{ 0 },/* ??? */{ 0 }, /* ud2 */{ 0 }, /* ??? */HEX_CMD(1,73),/* prefetchw */{ 0 },{ 0 },/* ??? */

		 // 10-1f

		HEX_ARRAY(4,0), HEX_ARRAY(4,1),/* vmovups */ HEX_ARRAY(5,0), HEX_ARRAY(2,3),/* vmovlps */HEX_ARRAY(2,4), /* vunpcklps */HEX_ARRAY(2,5), /* vunpckhps */HEX_ARRAY(4,2), HEX_ARRAY(2,6),/* vmovhps */
		{ 0 },/* grp16 */{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },/* ??? */{ 0 },/* nop 不知道什么情况*/

																			// 20-2f

		HEX_CMD(2,130), HEX_CMD(2,131), HEX_CMD(2,132), HEX_CMD(2,133),/* mov */{ 0 },{ 0 },{ 0 },{ 0 },/* ??? */
		HEX_ARRAY(2,25), HEX_ARRAY(2,26), /* vmovaps */HEX_ARRAY(4,5), /* cvtpi2ps */HEX_ARRAY(2,27),/* vmovntps */HEX_ARRAY(4,6),/* cvttps2pi */HEX_ARRAY(4,7), /* cvtps2pi */HEX_ARRAY(2,28),/* vucomiss */ HEX_ARRAY(2,29),/* vcomiss */

																					 // 30-3f

		HEX_CMD(0,30),/* wrmsr */HEX_CMD(0,31),/* rdtsc */HEX_CMD(0,32),/* rdmsr */HEX_CMD(0,33), /* rdpmc */HEX_CMD(0,34),/* sysenter */ HEX_CMD(0,35),/* sysexit */{ 0 },/* ??? */ HEX_CMD(0,36),/* getsec */
		{ 0 },/* 3B */{ 0 },/* ??? */{ 0 }, /* 3B */{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },/* ??? */

																				  // 40-4f

		{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },/* cmov */
		{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },/* cmov */

														// 50-5f

		HEX_ARRAY(2,7),/* vmovmskps */HEX_ARRAY(4,3),/* vsqrtps */HEX_ARRAY(2,8), /* vrsqrtps */HEX_ARRAY(2,9),/* vrcpps */HEX_ARRAY(2,10),/* vandps */HEX_ARRAY(2,11),/* vandnps */HEX_ARRAY(2,12), /* vorps */HEX_ARRAY(2,13),/* vxorps */
		HEX_ARRAY(4,8), /* vaddps */HEX_ARRAY(4,9),/* vmulps */HEX_ARRAY(4,10),/* vcvtps2pd */HEX_ARRAY(3,0),/* vcvtdq2ps */HEX_ARRAY(4,11),/* vsubps */HEX_ARRAY(4,12),/* vminps */HEX_ARRAY(4,13), /* vdivps */HEX_ARRAY(4,14),/* vmaxps */

																						// 60-6f

		HEX_ARRAY(2,14),/* punpcklbw */HEX_ARRAY(2,15),/* punpcklwd */HEX_ARRAY(2,16),/* punpckldq */HEX_ARRAY(2,17), /* packsswb */HEX_ARRAY(2,18), /* pcmpgtb */HEX_ARRAY(2,19), /* pcmpgtw */HEX_ARRAY(2,20), /* pcmpgtd */HEX_ARRAY(2,21),/* packuswb */
		HEX_ARRAY(2,30),/* punpckhbw */ HEX_ARRAY(2,31),/* punpckhwd */ HEX_ARRAY(2,32),/* punpckhdq */ HEX_ARRAY(2,33),/* packssdw */ HEX_CMD(3,75), HEX_CMD(3,76),/* ??? */  HEX_CMD(2,34),/* movd/q */ HEX_CMD(3,1),/* movq */

																			  // 70-7f

		HEX_ARRAY(4,4), /* pshufw */{ 0 },/* grp12 */{ 0 }, /* grp13 */{ 0 },/* grp14 */ HEX_ARRAY(2,22),/* pcmpeqb */ HEX_ARRAY(2,23),/* pcmpeqw */ HEX_ARRAY(2,24),/* pcmpeqd */ HEX_ARRAY(2,2),/* emms */
		HEX_CMD(2,185), /* vmread */HEX_CMD(2,186),/* vmwrite */{ 0 },{ 0 }, HEX_ARRAY(2,35), HEX_ARRAY(2,36), /* ??? */HEX_ARRAY(3,2), /* movd/q */HEX_ARRAY(3,3),/* movq */

						  // 80-8f

		HEX_CMD(1,74),/* jo */HEX_CMD(1,75),/* jno */HEX_CMD(1,76),/* jb */HEX_CMD(1,77),/* jnb */HEX_CMD(1,78),/* jz */HEX_CMD(1,79), /* jnz */HEX_CMD(1,80),/* jbe */ HEX_CMD(1,81),/* ja */
		HEX_CMD(1,92), /* js */HEX_CMD(1,93),/* jns */HEX_CMD(1,94),/* jp */HEX_CMD(1,95),/* jnp */HEX_CMD(1,96),/* jl */HEX_CMD(1,97), /* jnl */HEX_CMD(1,98),/* jng */ HEX_CMD(1,99),/* jg */

											  // 90-9f

		HEX_CMD(1,82), HEX_CMD(1,83), HEX_CMD(1,84), HEX_CMD(1,85), HEX_CMD(1,86), HEX_CMD(1,87), HEX_CMD(1,88),HEX_CMD(1,89),/* set */
		HEX_CMD(1,100),/* sets */ HEX_CMD(1,101),/* setns */ HEX_CMD(1,102),/* setp */ HEX_CMD(1,103),/* setnp */ HEX_CMD(1,104),/* setl */ HEX_CMD(1,105),/* setnl */ HEX_CMD(1,106),/* setng */ HEX_CMD(1,107),/* setg */

																		// a0-af

		HEX_CMD(1,90),/* push fs */HEX_CMD(1,91),/* pop fs */HEX_CMD(0,41),/* cpuid */HEX_CMD(2,193), /* bt */HEX_CMD(3,81), HEX_CMD(3,82), /* shld */{ 0 },{ 0 },/* ??? */
		HEX_CMD(1,108),/* push gs */ HEX_CMD(1,109),/* pop gs */ HEX_CMD(0,42),/* rsm */ HEX_CMD(2,235),/* bts */ HEX_CMD(3,105), HEX_CMD(3,106),/* shrd */{ 0 },/* grp15 */ HEX_CMD(2,236),/* imul */

																																															// b0-bf

		HEX_CMD(2,194), HEX_CMD(2,195), /* cmpxchg */HEX_CMD(2,196), /* lss */HEX_CMD(2,197), /* btr */HEX_CMD(2,198), /* lfs */HEX_CMD(2,199), /* lgs */HEX_CMD(2,200), HEX_CMD(2,201),/* movzx */
		HEX_CMD(2,237),/* jmpe 不知道什么情况 */{ 0 },/* grp10 */{ 0 },/* grp8 */ HEX_CMD(2,238), /* btc */ HEX_ARRAY(2,61),/* bsf */ HEX_ARRAY(2,62),/* bsr */ HEX_CMD(2,243), HEX_CMD(2,244),/* movsx */

																																														// c0-cf

		HEX_CMD(2,202), HEX_CMD(2,203),/* xadd */HEX_ARRAY(4,15),/* vcmpps */HEX_CMD(2,204), /* movntl */HEX_ARRAY(2,37), /* pinsnw */HEX_ARRAY(2,38),/* pextrw */ HEX_ARRAY(2,39),/* vshufps */{ 0 },/* grp9 */
		HEX_CMD(1,110),HEX_CMD(1,111), HEX_CMD(1,112), HEX_CMD(1,113), HEX_CMD(1,114), HEX_CMD(1,115), HEX_CMD(1,116), HEX_CMD(1,117),/* bswap */

																																	  // d0-df

		HEX_ARRAY(2,40), /* ??? */HEX_ARRAY(2,41),/* psrlw */HEX_ARRAY(2,42), /* psrld */HEX_ARRAY(2,43),/* psrlq */ HEX_ARRAY(2,44),/* paddq */ HEX_ARRAY(2,45),/* pmullw */ HEX_ARRAY(3,4),/* ??? */ HEX_ARRAY(2,46),/* pmovmskb */
		HEX_ARRAY(2,63), /* psubusb */HEX_ARRAY(2,64),/* psubusw */HEX_ARRAY(2,65),/* pminub */HEX_ARRAY(2,66),/* pand */HEX_ARRAY(2,67),/* paddusb */HEX_ARRAY(2,68),/* paddusw */HEX_ARRAY(2,69), /* pmaxub */HEX_ARRAY(2,70),/* pandn */

																																																								// e0-ef

		HEX_ARRAY(2,47),/* pavgb */HEX_ARRAY(2,48),/* psraw */HEX_ARRAY(2,49),/* psrad */HEX_ARRAY(2,50),/* pavgw */HEX_ARRAY(2,51), /* pmulhuw */HEX_ARRAY(2,52), /* pmulhw */HEX_ARRAY(3,5), /* ??? */HEX_ARRAY(2,53),/* movntq */
		HEX_ARRAY(2,71), HEX_ARRAY(2,72), HEX_ARRAY(2,73), HEX_ARRAY(2,74), HEX_ARRAY(2,75), HEX_ARRAY(2,76), HEX_ARRAY(2,77), HEX_ARRAY(2,78),

		// f0-ff

		HEX_CMD(2,226),/* ??? */HEX_CMD(2,54),/* psllw */HEX_CMD(2,55),/* pslld */HEX_CMD(2,56), /* psllq */HEX_CMD(2,57),/* pmuludq */ HEX_CMD(2,58),/* pmaddwd */ HEX_CMD(2,59),/* psadbw */ HEX_CMD(2,60),/* maskmovq */
		HEX_ARRAY(2,79), HEX_ARRAY(2,80), HEX_ARRAY(2,81), HEX_ARRAY(2,82), HEX_ARRAY(2,83), HEX_ARRAY(2,84), HEX_ARRAY(2,85),{ 0 },

	};
	const Opcode* OpcodeMap[] =
	{
		OneByteOpcodeMap,
		TwoByteOpcodeMap,
		0 // 暂空
	};
}