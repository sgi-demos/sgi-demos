/**************************************************************************
 *									  *
 *  Copyright (C)  1988 Silicon Graphics, Inc.	  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/* plane name is 'f16' */
/* filename is 'f16_polys.h' */

#include "f16_points.h"

static Coord f16_tip_top[3][3] = { TIP,A5,A4 };
static Coord f16_tip_right_1[3][3] = { TIP,A4,A3 };
static Coord f16_tip_right_2[3][3] = { TIP,A3,A2 };
static Coord f16_tip_right_3[3][3] = { TIP,A2,A1 };
static Coord f16_tip_right_4[3][3] = { TIP,A1,A14 };
static Coord f16_tip_right_5[3][3] = { TIP,A14,A13 };
static Coord f16_tip_right_6[3][3] = { TIP,A13,A12 };
static Coord f16_tip_bottom[3][3] = { TIP,A12,A11 };
static Coord f16_tip_left_1[3][3] = { TIP,A6,A5 };
static Coord f16_tip_left_2[3][3] = { TIP,A7,A6 };
static Coord f16_tip_left_3[3][3] = { TIP,A8,A7 };
static Coord f16_tip_left_4[3][3] = { TIP,A9,A8 };
static Coord f16_tip_left_5[3][3] = { TIP,A10,A9 };
static Coord f16_tip_left_6[3][3] = { TIP,A11,A10 };
static Coord f16_AB_top[4][3] = { A4,A5,B5,B4 };
static Coord f16_AB_right_1[4][3] = { A3,A4,B4,B3 };
static Coord f16_AB_right_2[4][3] = { A2,A3,B3,B2 };
static Coord f16_AB_right_3[4][3] = { A1,A2,B2,B1 };
static Coord f16_AB_right_4[4][3] = { A14,A1,B1,B14 };
static Coord f16_AB_right_5[4][3] = { A13,A14,B14,B13 };
static Coord f16_AB_right_6[4][3] = { A12,A13,B13,B12 };
static Coord f16_AB_bottom[4][3] = { A11,A12,B12,B11 };
static Coord f16_AB_left_1[4][3] = { A5,A6,B6,B5 };
static Coord f16_AB_left_2[4][3] = { A6,A7,B7,B6 };
static Coord f16_AB_left_3[4][3] = { A7,A8,B8,B7 };
static Coord f16_AB_left_4[4][3] = { A8,A9,B9,B8 };
static Coord f16_AB_left_5[4][3] = { A9,A10,B10,B9 };
static Coord f16_AB_left_6[4][3] = { A10,A11,B11,B10 };
static Coord f16_CD_top[4][3] = { C4,C5,D5,D4 };
static Coord f16_CD_right_1[4][3] = { C3,C4,D4,D3 };
static Coord f16_BD_right_2[4][3] = { B2,B3,D3,D2 };
static Coord f16_BD_right_3[4][3] = { B1,B2,D2,D1 };
static Coord f16_BD_right_extra[3][3] = { DM,D8,B8 };
static Coord f16_BD_right_4[3][3] = { DM,B8,B9 };
static Coord f16_BD_right_5[3][3] = { DM,B9,B10 };
static Coord f16_BD_right_6[3][3] = { DM,B10,B11 };
static Coord f16_BD_bottom[3][3] = { DM,B11,B12 };
static Coord f16_CD_left_1[4][3] = { C5,C6,D6,D5 };
static Coord f16_BD_left_2[4][3] = { B6,B7,D7,D6 };
static Coord f16_BD_left_3[4][3] = { B7,B8,D8,D7 };
static Coord f16_BD_left_extra[3][3] = { DM,B1,D1 };
static Coord f16_BD_left_4[3][3] = { DM,B14,B1 };
static Coord f16_BD_left_5[3][3] = { DM,B13,B14 };
static Coord f16_BD_left_6[3][3] = { DM,B12,B13 };
static Coord f16_SCOOP_right_extra[3][3] = { DM,D1,S1 };
static Coord f16_SCOOP_top[3][3] = { DM,S4,S5 };
static Coord f16_SCOOP_right_1[3][3] = { DM,S2,S4 };
static Coord f16_SCOOP_right_2[3][3] = { DM,S1,S2 };
static Coord f16_SCOOP_right_4[4][3] = { S14,S1,D1,D14 };
static Coord f16_SCOOP_right_5[4][3] = { S13,S14,D14,D13 };
static Coord f16_SCOOP_right_6[4][3] = { S12,S13,D13,D12 };
static Coord f16_SCOOP_bottom[4][3] = { S11,S12,D12,D11 };
static Coord f16_SCOOP_left_extra[3][3] = { DM,S8,D8 };
static Coord f16_SCOOP_left_1[3][3] = { DM,S5,S7 };
static Coord f16_SCOOP_left_2[3][3] = { DM,S7,S8 };
static Coord f16_SCOOP_left_4[4][3] = { S8,S9,D9,D8 };
static Coord f16_SCOOP_left_5[4][3] = { S9,S10,D10,D9 };
static Coord f16_SCOOP_left_6[4][3] = { S10,S11,D11,D10 };
static Coord f16_SCOOP_front_right[8][3] = { S5,S4,S2,S1,S14,S13,S12,S11 };
static Coord f16_SCOOP_front_left[6][3] = { S5,S11,S10,S9,S8,S7 };
static Coord f16_DE_top[4][3] = { D4,D5,E5,E4 };
static Coord f16_DE_right_1[4][3] = { D3,D4,E4,E3 };
static Coord f16_DE_right_2[4][3] = { D2,D3,E3,E2 };
static Coord f16_DE_right_3[4][3] = { D1,D2,E2,E1 };
static Coord f16_DE_right_4[4][3] = { D14,D1,E1,E14 };
static Coord f16_DE_right_5[4][3] = { D13,D14,E14,E13 };
static Coord f16_DE_right_6[4][3] = { D12,D13,E13,E12 };
static Coord f16_DE_bottom[4][3] = { D11,D12,E12,E11 };
static Coord f16_ORWA[12][3] = { orwa1,orwa2,orwa3,orwa4,orwa5,orwa6,orwa7,orwa8,orwa9,orwa10,orwa11,orwa12 };
static Coord f16_IRWA[12][3] = { irwa1,irwa2,irwa3,irwa4,irwa5,irwa6,irwa7,irwa8,irwa9,irwa10,irwa11,irwa12 };
static Coord f16_RW1A[4][3] = { orwa3,irwa3,irwa9,orwa9 };
static Coord f16_RW2A[4][3] = { orwa4,orwa10,irwa10,irwa4 };
static Coord f16_RW3A[4][3] = { orwa1,orwa7,irwa7,irwa1 };

static Coord f16_LW1A[4][3] = { olwa3,ilwa3,ilwa9,olwa9 };

static Coord f16_LW2A[4][3] = { ilwa4,olwa4,olwa10,ilwa10 };

static Coord f16_LW3A[4][3] = { ilwa1,olwa1,olwa7,ilwa7 };

static Coord f16_OLWA[12][3] = { olwa1,olwa2,olwa3,olwa4,olwa5,olwa6,olwa7,olwa8,olwa9,olwa10,olwa11,olwa12 };

static Coord f16_ILWA[12][3] = { ilwa1,ilwa2,ilwa3,ilwa4,ilwa5,ilwa6,ilwa7,ilwa8,ilwa9,ilwa10,ilwa11,ilwa12 };

static Coord f16_RFW[12][3] = { rfw1,rfw2,rfw3,rfw4,rfw5,rfw6,rfw7,rfw8,rfw9,rfw10,rfw11,rfw12 };
static Coord f16_LFW[12][3] = { lfw1,lfw2,lfw3,lfw4,lfw5,lfw6,lfw7,lfw8,lfw9,lfw10,lfw11,lfw12 };
static Coord f16_FW1[4][3] = { rfw3,lfw3,lfw9,rfw9 };
static Coord f16_FW2[4][3] = { rfw4,lfw4,lfw10,rfw10 };
static Coord f16_FSPAR1[3][3] = { fspar1,fspar2,fwc };
static Coord f16_FSPAR2[3][3] = { fspar3,fspar4,fwc };
static Coord f16_LSPAR[3][3] = { lspar1,lspar2,lwc };
static Coord f16_RSPAR[3][3] = { rspar1,rspar2,rwc };
static Coord f16_RSPARA[3][3] = { rspar1a,rspar2a,rwca };
static Coord f16_LSPARA[3][3] = { lspar1a,lspar2a,lwca };
static Coord f16_DE_left_1[4][3] = { D5,D6,E6,E5 };
static Coord f16_DE_left_2[4][3] = { D6,D7,E7,E6 };
static Coord f16_DE_left_3[4][3] = { D7,D8,E8,E7 };
static Coord f16_DE_left_4[4][3] = { D8,D9,E9,E8 };
static Coord f16_DE_left_5[4][3] = { D9,D10,E10,E9 };
static Coord f16_DE_left_6[4][3] = { D10,D11,E11,E10 };
static Coord f16_EF_top_left[4][3] = { E45,E5,F5,F45 };
static Coord f16_EF_top_right[4][3] = { E4,E45,F45,F4 };
static Coord f16_EF_right_1[4][3] = { E3,E4,F4,F3 };
static Coord f16_EF_right_2[4][3] = { E2,E3,F3,F2 };
static Coord f16_EF_right_3[4][3] = { E1,E2,F2,F1 };
static Coord f16_EF_right_4[4][3] = { E14,E1,F1,F14 };
static Coord f16_EF_right_5[4][3] = { E13,E14,F14,F13 };
static Coord f16_EF_right_6[4][3] = { E12,E13,F13,F12 };
static Coord f16_EF_bottom[4][3] = { E11,E12,F12,F11 };
static Coord f16_EF_left_1[4][3] = { E5,E6,F6,F5 };
static Coord f16_EF_left_2[4][3] = { E6,E7,F7,F6 };
static Coord f16_EF_left_3[4][3] = { E7,E8,F8,F7 };
static Coord f16_EF_left_4[4][3] = { E8,E9,F9,F8 };
static Coord f16_EF_left_5[4][3] = { E9,E10,F10,F9 };
static Coord f16_EF_left_6[4][3] = { E10,E11,F11,F10 };
static Coord f16_FG_top[4][3] = { F5,F4,G4,G5 };
static Coord f16_FG_right_1[4][3] = { F4,F3,G3,G4 };
static Coord f16_FG_right_2[4][3] = { F3,F2,G2,G3 };
static Coord f16_FG_right_3[4][3] = { F2,F1,G1,G2 };
static Coord f16_FG_right_4[4][3] = { F1,F14,G14,G1 };
static Coord f16_FG_right_5[4][3] = { F14,F13,G13,G14 };
static Coord f16_FG_right_6[4][3] = { F13,F12,G12,G13 };
static Coord f16_FG_bottom[4][3] = { F12,F11,G11,G12 };
static Coord f16_FG_left_1[4][3] = { F6,F5,G5,G6 };
static Coord f16_FG_left_2[4][3] = { F7,F6,G6,G7 };
static Coord f16_FG_left_3[4][3] = { F8,F7,G7,G8 };
static Coord f16_FG_left_4[4][3] = { F9,F8,G8,G9 };
static Coord f16_FG_left_5[4][3] = { F10,F9,G9,G10 };
static Coord f16_FG_left_6[4][3] = { F11,F10,G10,G11 };
static Coord f16_FIRE_right[9][3] = { F5,F11,F12,F13,F14,F1,F2,F3,F4 };
static Coord f16_FIRE_left[7][3] = { F5,F6,F7,F8,F9,F10,F11 };
static Coord f16_TAIL_bottom[5][3] = { T1,T2,T5,T6,F45 };
static Coord f16_TAIL_top[4][3] = { T2,T3,T4,T5 };
static Coord f16_left_front_wing[5][3] = { LFW1,LFW2,LFW3,D8,B8 };
static Coord f16_left_middle_wing[7][3] = { D8,LMW1,LMW2,LMW3,LMW4,LMW5,LMW6 };
static Coord f16_left_middle_wing_chunk[3][3] = { D8,LFW3,LMW1 };
static Coord f16_left_wing_fattener[3][3] = { D8,LMW2,D7 };
static Coord f16_left_outer_wing[4][3] = { LMW3,LOW1,LOW2,LOW3 };
static Coord f16_left_back_wing[4][3] = { LBW1,LBW2,LBW3,LMW4 };
static Coord f16_right_front_wing[5][3] = { RFW1,B1,D1,RFW3,RFW2 };
static Coord f16_right_middle_wing[7][3] = { D1,RMW6,RMW5,RMW4,RMW3,RMW2,RMW1 };
static Coord f16_right_wing_fattener[3][3] = { D1,RMW2,D2 };
static Coord f16_right_wing_chunk[3][3] = { D1,RMW1,RFW3 };
static Coord f16_right_outer_wing[4][3] = { RMW3,ROW3,ROW2,ROW1 };
static Coord f16_right_back_wing[4][3] = { RBW1,RMW4,RBW3,RBW2 };
static Coord f16_cockpit_tip_1[3][3] = { LCYZ1,FCXY1,FCXY2 };
static Coord f16_cockpit_tip_2[3][3] = { LCYZ1,FCXY2,FCXY3 };
static Coord f16_cockpit_tip_3[3][3] = { LCYZ1,FCXY3,FCXY4 };
static Coord f16_cockpit_tip_4[3][3] = { LCYZ1,FCXY4,FCXY5 };
static Coord f16_cockpit_back_tip_1[3][3] = { LCYZ6,BCXY5,BCXY4 };
static Coord f16_cockpit_back_tip_2[3][3] = { LCYZ6,BCXY4,BCXY3 };
static Coord f16_cockpit_back_tip_3[3][3] = { LCYZ6,BCXY3,BCXY2 };
static Coord f16_cockpit_back_tip_4[3][3] = { LCYZ6,BCXY2,BCXY1 };
static Coord f16_cockpit_middle_1[4][3] = { FCXY1,BCXY1,BCXY2,FCXY2 };
static Coord f16_cockpit_middle_2[4][3] = { FCXY2,BCXY2,BCXY3,FCXY3 };
static Coord f16_cockpit_middle_3[4][3] = { FCXY3,BCXY3,BCXY4,FCXY4 };
static Coord f16_cockpit_middle_4[4][3] = { FCXY4,BCXY4,BCXY5,FCXY5 };
static Coord f16_cockpit_cover[4][3] = { B6,C6,C3,B3};
static Coord f16_pilot_head_xy[8][3] = { PHXY1,PHXY2,PHXY3,PHXY4,PHXY5,PHXY6,PHXY7,PHXY8 };
static Coord f16_pilot_head_xz[8][3] = { PHXZ1,PHXZ2,PHXZ3,PHXZ4,PHXZ5,PHXZ6,PHXZ7,PHXZ8 };
static Coord f16_pilot_head_yz[8][3] = { PHYZ1,PHYZ2,PHYZ3,PHYZ4,PHYZ5,PHYZ6,PHYZ7,PHYZ8 };
static Coord f16_left_missle_xz1[3][3] = { LMXZ1,LMXZ2,LMXZ3 };
static Coord f16_left_missle_xz2[4][3] = { LMXZ4,LMXZ5,LMXZ10,LMXZ11 };
static Coord f16_left_missle_xz3[6][3] = { LMXZ5,LMXZ6,LMXZ7,LMXZ8,LMXZ9,LMXZ10 };
static Coord f16_left_missle_yz1[3][3] = { LMYZ1,LMYZ2,LMYZ3 };
static Coord f16_left_missle_yz2[4][3] = { LMYZ4,LMYZ5,LMYZ10,LMYZ11 };
static Coord f16_left_missle_yz3[6][3] = { LMYZ5,LMYZ6,LMYZ7,LMYZ8,LMYZ9,LMYZ10 };
static Coord f16_right_missle_xz1[3][3] = { RMXZ1,RMXZ2,RMXZ3 };
static Coord f16_right_missle_xz2[4][3] = { RMXZ4,RMXZ5,RMXZ10,RMXZ11 };
static Coord f16_right_missle_xz3[6][3] = { RMXZ5,RMXZ6,RMXZ7,RMXZ8,RMXZ9,RMXZ10 };
static Coord f16_right_missle_yz1[3][3] = { RMYZ1,RMYZ2,RMYZ3 };
static Coord f16_right_missle_yz2[4][3] = { RMYZ4,RMYZ5,RMYZ10,RMYZ11 };
static Coord f16_right_missle_yz3[6][3] = { RMYZ5,RMYZ6,RMYZ7,RMYZ8,RMYZ9,RMYZ10 };
static Coord f16_far_away_1[9][3] = { TIP,A1,B1,D1,G1,G8,D8,B8,A8 };
static Coord f16_far_away_2[6][3] = { D8,LOW1,LOW2,ROW2,ROW1,D1 };
static Coord f16_far_away_3[4][3] = { T1,T3,T4,T6 };
static Coord f16_far_away_4[9][3] = { TIP,A4,B4,D4,G4,G12,D12,B12,A12 };
static Coord f16_far_away_5[6][3] = { LBW1,LBW2,LBW3,RBW3,RBW2,RBW1 };
static Coord f16_far_away_6[7][3] = { D1,D3,D5,D7,D9,D11,D13 };


#define Total_polys 164
