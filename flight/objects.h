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

/* objects			*/
/* 0 => 8 reserved for plane views	*/
/* 9 => 9+MEXPLODE reserved for explosion	*/
#define EXPLOSION 9

#define FOV_EDIT 40
#define PUSH_IDENTITY 43
#define MTN_RANGE 44

#define DRAW_SKY 48
#define SETUP_WORLD 50
#define WORLD_OBJECT 51
#define CROSS_HAIRS 52
#define CLEAR_TEXT_DISPLAY 53
#define CLEAR_REPORT_CARD 54
#define RUNWAY_STRIPES 55
#define FAKE_STRIPES 56

#define METER_OVERLAY 60
#define HORIZON_METER 61
#define HEADING_METER 62
#define CLEAR_METERS 63
#define CLEAR_FUEL_METER 64
#define SLOW_METERS 65
#define WING_STALL 66
#define CRASH_METERS 67
#define G_LIMIT 68
#define AUTO_PILOT 69
#define LIGHTS 74
#define VASI1 77
#define VASI2 78

#define HEADING_ROTATE_EDIT 100
#define HORIZON_EDIT 101
#define RADAR 102
#define YAW_EDIT 103
#define TEXT_EDIT 104
#define VV_EDIT 105
#define GY_EDIT 106
#define RHAWS_EDIT 107

/* reserve BUILDING_OBJECTS to BUILDING_OBJECTS + MAX_BUILDINGS*4 */
#define MAX_BUILDINGS 20
#define BUILDING_OBJECTS 125
#define WHEEL_ANGLE 960
#define LWHEEL_ANGLE 961
#define RWHEEL_ANGLE 962
#define FWHEEL_ANGLE 963

#define C150 1000
#define B747 1010
#define F15  1020
#define F16  1030
#define F18  1040
#define P38  1050
#define F16W 1060
#define P38W 1070

#define C150_NAME "C-150"
#define B747_NAME "B-747"
#define F15_NAME "F-15"
#define F16_NAME "F-16"
#define F18_NAME "F-18"
#define P38_NAME "P-38"
