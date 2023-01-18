#ifndef DEVICEDEF	/* Release 2.3 */
#define DEVICEDEF
/**************************************************************************
 *									  *
 * 		 Copyright (C) 1984, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/* macros to test valuator and button numbers */

#define ISBUTTON( b )	    ( ((b)>=BUTOFFSET) && ((b)<(BUTCOUNT+BUTOFFSET)) )
#define ISVALUATOR( v )     ( ((v)>=VALOFFSET) && ((v)<(VALCOUNT+VALOFFSET)) )
#define ISTIMER( t )        ( ((t)>=TIMOFFSET) && ((t)<(TIMCOUNT+TIMOFFSET)) )
#define ISDIAL( t )         ( ((t)>=DIAL0    ) && ((t)<=DIAL8		   ) )
#define ISLPEN( t )         ( ((t)==LPENX) || ((t)==LPENY) )
#define ISLPENBUT( t )      ( (t)==LPENBUT )
#define ISBPADBUT( t )      ( ((t)>=BPAD0) && ((t)<=BPAD3) )
#define ISSW( t ) 	    ( ((t)>=SW0) && ((t)<=SW31) )
#define ISINPUT( t )        ( ((t)>=INOFFSET) && ((t)<(INCOUNT+INOFFSET)) )
#define ISOUTPUT( t )       ( ((t)>=OUTOFFSET) && ((t)<(OUTCOUNT+OUTOFFSET)) )
#define ISXKEYBD( t )	    ( ((t)>=XKBDOFFSET) && ((t)<(XKBDCOUNT+XKBDOFFSET)))

/* include file with device definitions */

#define NULLDEV		0
#define BUTOFFSET	1
#define VALOFFSET	256
#define TIMOFFSET	515
#define INOFFSET	1024
#define OUTOFFSET	1033
#define XKBDOFFSET	143

#define BUTCOUNT	172
#define VALCOUNT	20
#define TIMCOUNT	4
#define INCOUNT		8
#define OUTCOUNT	8
#define XKBBDCOUNT	28

/* buttons */

#define BUT0		1	/* 0+BUTOFFSET */
#define BUT1		2	/* 1+BUTOFFSET */
#define BUT2		3	/* 2+BUTOFFSET */
#define BUT3		4	/* 3+BUTOFFSET */
#define BUT4		5	/* 4+BUTOFFSET */
#define BUT5		6	/* 5+BUTOFFSET */
#define BUT6		7	/* 6+BUTOFFSET */
#define BUT7		8	/* 7+BUTOFFSET */
#define BUT8		9	/* 8+BUTOFFSET */
#define BUT9		10	/* 9+BUTOFFSET */
#define BUT10		11	/* 10+BUTOFFSET, A */
#define BUT11		12	/* 11+BUTOFFSET, B */
#define BUT12		13	/* 12+BUTOFFSET, C */
#define BUT13		14	/* 13+BUTOFFSET, D */
#define BUT14		15	/* 14+BUTOFFSET, E */
#define BUT15		16	/* 15+BUTOFFSET, F */
#define BUT16		17	/* 16+BUTOFFSET, 10 */
#define BUT17		18	/* 17+BUTOFFSET, 11 */
#define BUT18		19	/* 18+BUTOFFSET, 12 */
#define BUT19		20	/* 19+BUTOFFSET, 13 */
#define BUT20		21	/* 20+BUTOFFSET, 14 */
#define BUT21		22	/* 21+BUTOFFSET, 15 */
#define BUT22		23	/* 22+BUTOFFSET, 16 */
#define BUT23		24	/* 23+BUTOFFSET, 17 */
#define BUT24		25	/* 24+BUTOFFSET, 18 */
#define BUT25		26	/* 25+BUTOFFSET, 19 */
#define BUT26		27	/* 26+BUTOFFSET, 1A */
#define BUT27		28	/* 27+BUTOFFSET, 1B */
#define BUT28		29	/* 28+BUTOFFSET, 1C */
#define BUT29		30	/* 29+BUTOFFSET, 1D */
#define BUT30		31	/* 30+BUTOFFSET, 1E */
#define BUT31		32	/* 31+BUTOFFSET, 1F */
#define BUT32		33	/* 32+BUTOFFSET, 20 */
#define BUT33		34	/* 33+BUTOFFSET, 21 */
#define BUT34		35	/* 34+BUTOFFSET, 22 */
#define BUT35		36	/* 35+BUTOFFSET, 23 */
#define BUT36		37	/* 36+BUTOFFSET, 24 */
#define BUT37		38	/* 37+BUTOFFSET, 25 */
#define BUT38		39	/* 38+BUTOFFSET, 26 */
#define BUT39		40	/* 39+BUTOFFSET, 27 */
#define BUT40		41	/* 40+BUTOFFSET, 28 */
#define BUT41		42	/* 41+BUTOFFSET, 29 */
#define BUT42		43	/* 42+BUTOFFSET, 2A */
#define BUT43		44	/* 43+BUTOFFSET, 2B */
#define BUT44		45	/* 44+BUTOFFSET, 2C */
#define BUT45		46	/* 45+BUTOFFSET, 2D */
#define BUT46		47	/* 46+BUTOFFSET, 2E */
#define BUT47		48	/* 47+BUTOFFSET, 2F */
#define BUT48		49	/* 48+BUTOFFSET, 30 */
#define BUT49		50	/* 49+BUTOFFSET, 31 */
#define BUT50		51	/* 50+BUTOFFSET, 32 */
#define BUT51		52	/* 51+BUTOFFSET, 33 */
#define BUT52		53	/* 52+BUTOFFSET, 34 */
#define BUT53		54	/* 53+BUTOFFSET, 35 */
#define BUT54		55	/* 54+BUTOFFSET, 36 */
#define BUT55		56	/* 55+BUTOFFSET, 37 */
#define BUT56		57	/* 56+BUTOFFSET, 38 */
#define BUT57		58	/* 57+BUTOFFSET, 39 */
#define BUT58		59	/* 58+BUTOFFSET, 3A */
#define BUT59		60	/* 59+BUTOFFSET, 3B */
#define BUT60		61	/* 60+BUTOFFSET, 3C */
#define BUT61		62	/* 61+BUTOFFSET, 3D */
#define BUT62		63	/* 62+BUTOFFSET, 3E */
#define BUT63		64	/* 63+BUTOFFSET, 3F */
#define BUT64		65	/* 64+BUTOFFSET, 40 */
#define BUT65		66	/* 65+BUTOFFSET, 41 */
#define BUT66		67	/* 66+BUTOFFSET, 42 */
#define BUT67		68	/* 67+BUTOFFSET, 43 */
#define BUT68		69	/* 68+BUTOFFSET, 44 */
#define BUT69		70	/* 69+BUTOFFSET, 45 */
#define BUT70		71	/* 70+BUTOFFSET, 46 */
#define BUT71		72	/* 71+BUTOFFSET, 47 */
#define BUT72		73	/* 72+BUTOFFSET, 48 */
#define BUT73		74	/* 73+BUTOFFSET, 49 */
#define BUT74		75	/* 74+BUTOFFSET, 4A */
#define BUT75		76	/* 75+BUTOFFSET, 4B */
#define BUT76		77	/* 76+BUTOFFSET, 4C */
#define BUT77		78	/* 77+BUTOFFSET, 4D */
#define BUT78		79	/* 78+BUTOFFSET, 4E */
#define BUT79		80	/* 79+BUTOFFSET, 4F */
#define BUT80		81	/* 80+BUTOFFSET, 50 */
#define BUT81		82	/* 81+BUTOFFSET, 51 */
#define BUT82		83	/* 82+BUTOFFSET, 52 */
#define MAXKBDBUT	83	/* BUT82 */
#define BUT100		101	/* 100+BUTOFFSET, Mouse button 1 */
#define BUT101		102	/* 101+BUTOFFSET, Mouse button 2 */
#define BUT102		103	/* 102+BUTOFFSET, Mouse button 3 */
#define BUT110		111	/* 110+BUTOFFSET */
#define BUT111		112	/* 111+BUTOFFSET */
#define BUT112		113	/* 112+BUTOFFSET */
#define BUT113		114	/* 113+BUTOFFSET */
#define BUT114		115	/* 114+BUTOFFSET */
#define BUT115		116	/* 115+BUTOFFSET */
#define BUT116		117	/* 116+BUTOFFSET */
#define BUT117		118	/* 117+BUTOFFSET */
#define BUT118		119	/* 118+BUTOFFSET */
#define BUT119		120	/* 119+BUTOFFSET */
#define BUT120		121	/* 120+BUTOFFSET */
#define BUT121		122	/* 121+BUTOFFSET */
#define BUT122		123	/* 122+BUTOFFSET */
#define BUT123		124	/* 123+BUTOFFSET */
#define BUT124		125	/* 124+BUTOFFSET */
#define BUT125		126	/* 125+BUTOFFSET */
#define BUT126		127	/* 126+BUTOFFSET */
#define BUT127		128	/* 127+BUTOFFSET */
#define BUT128		129	/* 128+BUTOFFSET */
#define BUT129		130	/* 129+BUTOFFSET */
#define BUT130		131	/* 130+BUTOFFSET */
#define BUT131		132	/* 131+BUTOFFSET */
#define BUT132		133	/* 132+BUTOFFSET */
#define BUT133		134	/* 133+BUTOFFSET */
#define BUT134		135	/* 134+BUTOFFSET */
#define BUT135		136	/* 135+BUTOFFSET */
#define BUT136		137	/* 136+BUTOFFSET */
#define BUT137		138	/* 137+BUTOFFSET */
#define BUT138		139	/* 138+BUTOFFSET */
#define BUT139		140	/* 139+BUTOFFSET */
#define BUT140		141	/* 140+BUTOFFSET */
#define BUT141		142	/* 141+BUTOFFSET */
#define BUT142		143	/* 142+BUTOFFSET */
#define BUT143		144	/* 143+BUTOFFSET */
#define BUT144		145	/* 144+BUTOFFSET */
#define BUT145		146	/* 145+BUTOFFSET */
#define BUT146		147	/* 146+BUTOFFSET */
#define BUT147		148	/* 147+BUTOFFSET */
#define BUT148		149	/* 148+BUTOFFSET */
#define BUT149		150	/* 149+BUTOFFSET */
#define BUT150		151	/* 150+BUTOFFSET */
#define BUT151		152	/* 151+BUTOFFSET */
#define BUT152		153	/* 152+BUTOFFSET */
#define BUT153		154	/* 153+BUTOFFSET */
#define BUT154		155	/* 154+BUTOFFSET */
#define BUT155		156 	/* 155+BUTOFFSET */
#define BUT156		157	/* 156+BUTOFFSET */
#define BUT157		158	/* 157+BUTOFFSET */
#define BUT158		159	/* 158+BUTOFFSET */
#define BUT159		160	/* 159+BUTOFFSET */
#define BUT160		161	/* 160+BUTOFFSET */
#define BUT161		162	/* 161+BUTOFFSET */
#define BUT162		163	/* 162+BUTOFFSET */
#define BUT163		164	/* 163+BUTOFFSET */
#define BUT164		165	/* 164+BUTOFFSET */
#define BUT165		166	/* 165+BUTOFFSET */
#define BUT166		167	/* 166+BUTOFFSET */
#define BUT167		168	/* 167+BUTOFFSET */
#define BUT168		169	/* 168+BUTOFFSET */
#define BUT169		170	/* 169+BUTOFFSET */

#define MOUSE1		101	/* BUT100 */
#define MOUSE2		102	/* BUT101 */
#define MOUSE3		103	/* BUT102 */
#define LEFTMOUSE	103	/* BUT102 */
#define MIDDLEMOUSE	102	/* BUT101 */
#define RIGHTMOUSE	101	/* BUT100 */
#define LPENBUT		104	/* LIGHT PEN BUTTON */
#define BPAD0		105	/* BITPAD BUTTON 0 */
#define BPAD1		106	/* BITPAD BUTTON 1 */
#define BPAD2		107	/* BITPAD BUTTON 2 */
#define BPAD3		108	/* BITPAD BUTTON 3 */
#define LPENVALID	109	/* LIGHT PEN VALID */

#define SWBASE		111	/* BUT110 */
#define SW0		111	/* SWBASE */
#define SW1		112	/* SWBASE+1 */
#define SW2		113	/* SWBASE+2 */
#define SW3		114	/* SWBASE+3 */
#define SW4		115	/* SWBASE+4 */
#define SW5		116	/* SWBASE+5 */
#define SW6		117	/* SWBASE+6 */
#define SW7		118	/* SWBASE+7 */
#define SW8		119	/* SWBASE+8 */
#define SW9		120	/* SWBASE+9 */
#define SW10		121	/* SWBASE+10 */
#define SW11		122	/* SWBASE+11 */
#define SW12		123	/* SWBASE+12 */
#define SW13		124	/* SWBASE+13 */
#define SW14		125	/* SWBASE+14 */
#define SW15		126	/* SWBASE+15 */
#define SW16		127	/* SWBASE+16 */
#define SW17		128	/* SWBASE+17 */
#define SW18		129	/* SWBASE+18 */
#define SW19		130	/* SWBASE+19 */
#define SW20		131	/* SWBASE+20 */
#define SW21		132	/* SWBASE+21 */
#define SW22		133	/* SWBASE+22 */
#define SW23		134	/* SWBASE+23 */
#define SW24		135	/* SWBASE+24 */
#define SW25		136	/* SWBASE+25 */
#define SW26		137	/* SWBASE+26 */
#define SW27		138	/* SWBASE+27 */
#define SW28		139	/* SWBASE+28 */
#define SW29		140	/* SWBASE+29 */
#define SW30		141	/* SWBASE+30 */
#define SW31		142	/* SWBASE+31 */

#define AKEY		11	/* BUT10 */
#define BKEY		36	/* BUT35 */
#define CKEY		28	/* BUT27 */
#define DKEY		18	/* BUT17 */
#define EKEY		17	/* BUT16 */
#define FKEY		19	/* BUT18 */
#define GKEY		26	/* BUT25 */
#define HKEY		27	/* BUT26 */
#define IKEY		40	/* BUT39 */
#define JKEY		34	/* BUT33 */
#define KKEY		35	/* BUT34 */
#define LKEY		42	/* BUT41 */
#define MKEY		44	/* BUT43 */
#define NKEY		37	/* BUT36 */
#define OKEY		41	/* BUT40 */
#define PKEY		48	/* BUT47 */
#define QKEY		10	/* BUT9 */
#define RKEY		24	/* BUT23 */
#define SKEY		12	/* BUT11 */
#define TKEY		25	/* BUT24 */
#define UKEY		33	/* BUT32 */
#define VKEY		29	/* BUT28 */
#define WKEY		16	/* BUT15 */
#define XKEY		21	/* BUT20 */
#define YKEY		32	/* BUT31 */
#define ZKEY		20	/* BUT19 */
#define ZEROKEY		46	/* BUT45 */
#define ONEKEY		8	/* BUT7 */
#define TWOKEY		14	/* BUT13 */
#define THREEKEY	15	/* BUT14 */
#define FOURKEY		22	/* BUT21 */
#define FIVEKEY		23	/* BUT22 */
#define SIXKEY		30	/* BUT29 */
#define SEVENKEY	31	/* BUT30 */
#define EIGHTKEY	38	/* BUT37 */
#define NINEKEY		39	/* BUT38 */
#define BREAKKEY	1	/* BUT0 */
#define SETUPKEY	2	/* BUT1 */
#define CTRLKEY		3	/* BUT2 */
#define CAPSLOCKKEY	4	/* BUT3 */
#define RIGHTSHIFTKEY	5	/* BUT4 */
#define LEFTSHIFTKEY	6	/* BUT5 */
#define NOSCRLKEY	13	/* BUT12 */
#define ESCKEY		7	/* BUT6 */
#define TABKEY		9	/* BUT8 */
#define RETKEY		51	/* BUT50 */
#define SPACEKEY	83	/* BUT82 */
#define LINEFEEDKEY	60	/* BUT59 */
#define BACKSPACEKEY	61	/* BUT60 */
#define DELKEY		62	/* BUT61 */
#define SEMICOLONKEY	43	/* BUT42 */
#define PERIODKEY	52	/* BUT51 */
#define COMMAKEY	45	/* BUT44 */
#define QUOTEKEY	50	/* BUT49 */
#define ACCENTGRAVEKEY	55	/* BUT54 */
#define MINUSKEY	47	/* BUT46 */
#define VIRGULEKEY	53	/* BUT52 */
#define BACKSLASHKEY	57	/* BUT56 */
#define EQUALKEY	54	/* BUT53 */
#define LEFTBRACKETKEY	49	/* BUT48 */
#define RIGHTBRACKETKEY	56	/* BUT55 */
#define LEFTARROWKEY	73	/* BUT72 */
#define DOWNARROWKEY	74	/* BUT73 */
#define RIGHTARROWKEY	80	/* BUT79 */
#define UPARROWKEY	81	/* BUT80 */
#define PAD0		59	/* BUT58 */
#define PAD1		58	/* BUT57 */
#define PAD2		64	/* BUT63 */
#define PAD3		65	/* BUT64 */
#define PAD4		63	/* BUT62 */
#define PAD5		69	/* BUT68 */
#define PAD6		70	/* BUT69 */
#define PAD7		67	/* BUT66 */
#define PAD8		68	/* BUT67 */
#define PAD9		75	/* BUT74 */
#define PADPF1		72	/* BUT71 */
#define PADPF2		71	/* BUT70 */
#define PADPF3		79	/* BUT78 */
#define PADPF4		78	/* BUT77 */
#define PADPERIOD	66	/* BUT65 */
#define PADMINUS	76	/* BUT75 */
#define PADCOMMA	77	/* BUT76 */
#define PADENTER	82	/* BUT81 */

/* valuators */

#define SGIRESERVED	256	/* 0+VALOFFSET */
// Alice 4: Accelerator horizontal (out of 3600 tenths of a degree).
#define DIAL0		257	/* 1+VALOFFSET */
// Alice 4: Accelerator vertical (out of 3600 tenths of a degree).
#define DIAL1		258	/* 2+VALOFFSET */
// Alice 4: Gyro X in degress per second (dps) in 16.16 fixed point format.
#define DIAL2		259	/* 3+VALOFFSET */
// Alice 4: Gyro Y in degress per second (dps) in 16.16 fixed point format.
#define DIAL3		260	/* 4+VALOFFSET */
// Alice 4: Gyro Z in degress per second (dps) in 16.16 fixed point format.
#define DIAL4		261	/* 5+VALOFFSET */
// Alice 4: Accelerator X (-256 to 256).
#define DIAL5		262	/* 6+VALOFFSET */
// Alice 4: Accelerator Y (-256 to 256).
#define DIAL6		263	/* 7+VALOFFSET */
// Alice 4: Accelerator Z (-256 to 256).
#define DIAL7		264	/* 8+VALOFFSET */
#define DIAL8		265	/* 9+VALOFFSET */
#define MOUSEX		266	/* 10+VALOFFSET */
#define MOUSEY		267	/* 11+VALOFFSET */
#define LPENX		268	/* 12+VALOFFSET */
#define LPENY		269	/* 13+VALOFFSET */
#define BPADX		270	/* 14+VALOFFSET */
#define BPADY		271	/* 15+VALOFFSET */
#define CURSORX		272	/* 16+VALOFFSET */
#define CURSORY		273	/* 17+VALOFFSET */
#define GHOSTX		274	/* 18+VALOFFSET */
#define GHOSTY		275	/* 19+VALOFFSET */

/* timer */

#define TIMER0		515	/* 0+TIMOFFSET */
#define TIMER1		516	/* 1+TIMOFFSET */
#define TIMER2		517	/* 2+TIMOFFSET */
#define TIMER3		518	/* 3+TIMOFFSET */

/* misc devices */

#define KEYBD		513	/* keyboard */
#define RAWKEYBD	514	/* raw keyboard for keyboard manager */
#define VALMARK		523	/* valuator mark */
#define GERROR		524	/* errors device */
#define REDRAW		528	/* used by port manager to signal redraws */
#define	WMSEND		529	/* data in proc's shmem */
#define	WMREPLY		530	/* reply from port manager */
#define	WMGFCLOSE	531	/* gf # is no longer being used */
#define	WMTXCLOSE	532	/* tx # is no longer being used */
#define	MODECHANGE	533	/* the display mode has changed */
#define	INPUTCHANGE	534	/* input connected or disconnected */
#define	QFULL		535	/* queue was filled */
#define	PIECECHANGE	536	/* change in the window pieces */
#define WINCLOSE	537	/* window close */

/* the extended keyboard */

#define LEFTALTKEY 	143
#define	RIGHTALTKEY 	144
#define	RIGHTCTRLKEY 	145
#define	F1KEY 		146
#define	F2KEY 		147
#define	F3KEY 		148
#define	F4KEY 		149
#define	F5KEY 		150
#define	F6KEY 		151
#define	F7KEY 		152
#define	F8KEY 		153
#define	F9KEY 		154
#define	F10KEY		155
#define	F11KEY		156
#define	F12KEY		157
#define	PRINTSCREENKEY	158
#define	SCROLLLOCKKEY	159
#define	PAUSEKEY	160
#define	INSERTKEY	161
#define	HOMEKEY 	162
#define	PAGEUPKEY 	163
#define	ENDKEY		164
#define	PAGEDOWNKEY	165
#define	NUMLOCKKEY	166
#define	PADVIRGULEKEY 	167
#define PADASTERKEY 	168
#define PADPLUSKEY 	169

/* input channels */

#define INPUT0		1024	/* input channels */
#define INPUT1		1025
#define INPUT2		1026
#define INPUT3		1027
#define INPUT4		1028
#define INPUT5		1029
#define INPUT6		1030
#define INPUT7		1032

/* output channels */

#define OUTPUT0		1033	/* output channels */
#define OUTPUT1		1034
#define OUTPUT2		1035
#define OUTPUT3		1036
#define OUTPUT4		1037
#define OUTPUT5		1038
#define OUTPUT6		1039
#define OUTPUT7		1040

#define MENUBUTTON	RIGHTMOUSE /* THE menu button */

#endif // DEVICEDEF
