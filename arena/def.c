
#include <gl.h>

#include "arena.h"

#define F 0
#define B 1
#define L 2
#define R 3
#define S 2
#define T 3
#define U 4

#define LF 0
#define RF 1
#define LB 2
#define RB 3

Angle r_sh_rot = 300, l_sh_rot = -300;		/* shoulder rotations */
Angle r_el_rot = 600, l_el_rot = 600;		/* elbow rotations */
Angle torso_x_rot = 000, torso_z_rot = 000;	/* torso rotations */

Tag MECH_ROT, MECH_POS, MECH_VIEW;

Coord foot[4][4][3] = {{{ 0.15,  0.00,  0.07},
			{ 0.15,  0.00, -0.07},
			{ 0.07,  0.10, -0.07},
			{ 0.07,  0.10,  0.07}},
		       {{-0.15,  0.00, -0.07},
			{-0.15,  0.00,  0.07},
			{-0.07,  0.10,  0.07},
			{-0.07,  0.10, -0.07}},
		       {{ 0.15,  0.00, -0.07},
			{-0.15,  0.00, -0.07},
			{-0.07,  0.10, -0.07},
			{ 0.07,  0.10, -0.07}},
		       {{-0.15,  0.00,  0.07},
			{ 0.15,  0.00,  0.07},
			{ 0.07,  0.10,  0.07},
			{-0.07,  0.10,  0.07}}};

Coord l_leg[4][4][3] = {{{ 0.06, -0.05,  0.06},
			 { 0.06, -0.05, -0.06},
			 { 0.06,  0.20, -0.06},
			 { 0.06,  0.20,  0.06}},
			{{-0.06, -0.05, -0.06},
			 {-0.06, -0.05,  0.06},
			 {-0.06,  0.20,  0.06},
			 {-0.06,  0.20, -0.06}},
			{{ 0.06, -0.05, -0.06},
			 {-0.06, -0.05, -0.06},
			 {-0.06,  0.20, -0.06},
			 { 0.06,  0.20, -0.06}},
			{{-0.06, -0.05,  0.06},
			 { 0.06, -0.05,  0.06},
			 { 0.06,  0.20,  0.06},
			 {-0.06,  0.20,  0.06}}};

Coord u_leg[4][4][3] = {{{ 0.00,  0.00,  0.06},
			 { 0.00,  0.00, -0.06},
			 { 0.00,  0.25, -0.06},
			 { 0.00,  0.25,  0.06}},
			{{-0.12,  0.00, -0.06},
			 {-0.12,  0.00,  0.06},
			 {-0.12,  0.25,  0.06},
			 {-0.12,  0.25, -0.06}},
			{{ 0.00,  0.00, -0.06},
			 {-0.12,  0.00, -0.06},
			 {-0.12,  0.25, -0.06},
			 { 0.00,  0.25, -0.06}},
			{{-0.12,  0.00,  0.06},
			 { 0.00,  0.00,  0.06},
			 { 0.00,  0.25,  0.06},
			 {-0.12,  0.25,  0.06}}};

Coord torso1[4][4][3] = {{{ 0.15, -0.05,  0.20},
			  { 0.15, -0.05, -0.20},
			  { 0.12,  0.10, -0.17},
			  { 0.12,  0.10,  0.17}},
			 {{-0.15, -0.05, -0.20},
			  {-0.15, -0.05,  0.20},
			  {-0.12,  0.10,  0.17},
			  {-0.12,  0.10, -0.17}},
			 {{ 0.15, -0.05, -0.20},
			  {-0.15, -0.05, -0.20},
			  {-0.12,  0.10, -0.17},
			  { 0.12,  0.10, -0.17}},
			 {{-0.15, -0.05,  0.20},
			  { 0.15, -0.05,  0.20},
			  { 0.12,  0.10,  0.17},
			  {-0.12,  0.10,  0.17}}};

Coord torso2[4][4][3] = {{{ 0.12,  0.10,  0.17},
			  { 0.12,  0.10, -0.17},
			  { 0.12,  0.25, -0.20},
			  { 0.12,  0.25,  0.20}},
			 {{-0.12,  0.10, -0.17},
			  {-0.12,  0.10,  0.17},
			  {-0.15,  0.25,  0.20},
			  {-0.15,  0.25, -0.20}},
			 {{ 0.12,  0.10, -0.17},
			  {-0.12,  0.10, -0.17},
			  {-0.15,  0.25, -0.20},
			  { 0.12,  0.25, -0.20}},
			 {{-0.12,  0.10,  0.17},
			  { 0.12,  0.10,  0.17},
			  { 0.12,  0.25,  0.20},
			  {-0.15,  0.25,  0.20}}};

Coord torso3[4][4][3] = {{{ 0.12,  0.25,  0.20},
			  { 0.12,  0.25, -0.20},
			  { 0.16,  0.35, -0.20},
			  { 0.16,  0.35,  0.20}},
			 {{-0.15,  0.25, -0.20},
			  {-0.15,  0.25,  0.20},
			  {-0.15,  0.35,  0.20},
			  {-0.15,  0.35, -0.20}},
			 {{-0.15,  0.25, -0.20},
			  {-0.15,  0.35, -0.20},
			  { 0.16,  0.35, -0.20},
			  { 0.12,  0.25, -0.20}},
			 {{ 0.12,  0.25,  0.20},
			  { 0.16,  0.35,  0.20},
			  {-0.15,  0.35,  0.20},
			  {-0.15,  0.25,  0.20}}};

Coord torso4[4][4][3] = {{{ 0.16,  0.35,  0.20},
			  { 0.16,  0.35, -0.20},
			  {-0.10,  0.45, -0.20},
			  {-0.10,  0.45,  0.20}},
			 {{-0.15,  0.35, -0.20},
			  {-0.15,  0.35,  0.20},
			  {-0.13,  0.45,  0.20},
			  {-0.13,  0.45, -0.20}},
			 {{ 0.16,  0.35, -0.20},
			  {-0.15,  0.35, -0.20},
			  {-0.13,  0.45, -0.20},
			  {-0.10,  0.45, -0.20}},
			 {{-0.15,  0.35,  0.20},
			  { 0.16,  0.35,  0.20},
			  {-0.10,  0.45,  0.20},
			  {-0.13,  0.45,  0.20}}};

Coord head[4][4][3] = {{{ 0.05,  0.39,  0.10},
			{ 0.05,  0.39, -0.10},
			{ 0.05,  0.48, -0.05},
			{ 0.05,  0.48,  0.05}},
		       {{-0.10,  0.45, -0.05},
			{-0.10,  0.45,  0.05},
			{ 0.05,  0.48,  0.05},
			{ 0.05,  0.48, -0.05}},
		       {{ 0.05,  0.39, -0.10},
			{-0.10,  0.45, -0.05},
			{-0.10,  0.45, -0.05},
			{ 0.05,  0.48, -0.05}},
		       {{ 0.05,  0.39,  0.10},
			{ 0.05,  0.48,  0.05},
			{-0.10,  0.45,  0.05},
			{-0.10,  0.45,  0.05}}};

Coord r_shoulder[4][4][3] = {{{ 0.06, -0.12,  0.12},
			      { 0.06, -0.12,  0.00},
			      { 0.06,  0.00,  0.00},
			      { 0.06, -0.02,  0.12}},
			     {{-0.06, -0.12,  0.00},
			      {-0.06, -0.12,  0.12},
			      {-0.06, -0.02,  0.12},
			      {-0.06,  0.00,  0.00}},
			     {{-0.06, -0.12,  0.12},
			      { 0.06, -0.12,  0.12},
			      { 0.06, -0.02,  0.12},
			      {-0.06, -0.02,  0.12}},
			     {{-0.06, -0.02,  0.12},
			      { 0.06, -0.02,  0.12},
			      { 0.06,  0.00,  0.00},
			      {-0.06,  0.00,  0.00}}};

Coord l_shoulder[4][4][3] = {{{ 0.06, -0.12,  0.00},
			      { 0.06, -0.12, -0.12},
			      { 0.06, -0.02, -0.12},
			      { 0.06,  0.00,  0.00}},
			     {{-0.06, -0.12, -0.12},
			      {-0.06, -0.12,  0.00},
			      {-0.06,  0.00,  0.00},
			      {-0.06, -0.02, -0.12}},
			     {{ 0.06, -0.12, -0.12},
			      {-0.06, -0.12, -0.12},
			      {-0.06, -0.02, -0.12},
			      { 0.06, -0.02, -0.12}},
			     {{-0.06,  0.00,  0.00},
			      { 0.06,  0.00,  0.00},
			      { 0.06, -0.02, -0.12},
			      {-0.06, -0.02, -0.12}}};

Coord l_u_arm[4][6][3] = {{{ 0.05, -0.21, -0.01},
			   { 0.05, -0.21, -0.11},
			   { 0.05, -0.08, -0.11},
			   { 0.05, -0.08, -0.01},
			   { 0.00,  0.00,  0.00},
			   { 0.00,  0.00,  0.00}},
			  {{-0.05, -0.25, -0.11},
			   {-0.05, -0.25, -0.01},
			   {-0.05, -0.08, -0.01},
			   {-0.05, -0.08, -0.11},
			   { 0.00,  0.00,  0.00},
			   { 0.00,  0.00,  0.00}},
			  {{ 0.05, -0.25, -0.11},
			   { 0.03, -0.29, -0.11},
			   {-0.03, -0.29, -0.11},
			   {-0.05, -0.25, -0.11},
			   {-0.05, -0.08, -0.11},
			   { 0.05, -0.08, -0.11}},
			  {{-0.05, -0.25, -0.01},
			   {-0.03, -0.29, -0.01},
			   { 0.03, -0.29, -0.01},
			   { 0.05, -0.25, -0.01},
			   { 0.05, -0.08, -0.01},
			   {-0.05, -0.08, -0.01}}};

Coord r_u_arm[4][6][3] = {{{ 0.05, -0.21,  0.11},
			   { 0.05, -0.21,  0.01},
			   { 0.05, -0.08,  0.01},
			   { 0.05, -0.08,  0.11},
			   { 0.00,  0.00,  0.00},
			   { 0.00,  0.00,  0.00}},
			  {{-0.05, -0.25,  0.01},
			   {-0.05, -0.25,  0.11},
			   {-0.05, -0.08,  0.11},
			   {-0.05, -0.08,  0.01},
			   { 0.00,  0.00,  0.00},
			   { 0.00,  0.00,  0.00}},
			  {{ 0.05, -0.25,  0.01},
			   { 0.03, -0.29,  0.01},
			   {-0.03, -0.29,  0.01},
			   {-0.05, -0.25,  0.01},
			   {-0.05, -0.08,  0.01},
			   { 0.05, -0.08,  0.01}},
			  {{-0.05, -0.25,  0.11},
			   {-0.03, -0.29,  0.11},
			   { 0.03, -0.29,  0.11},
			   { 0.05, -0.25,  0.11},
			   { 0.05, -0.08,  0.11},
			   {-0.05, -0.08,  0.11}}};

Coord l_l_arm[5][4][3] = {{{ 0.04, -0.21, -0.02},
			   { 0.04, -0.21, -0.10},
			   { 0.05,  0.06, -0.11},
			   { 0.05,  0.06, -0.01}},
			  {{-0.04, -0.21, -0.10},
			   {-0.04, -0.21, -0.02},
			   {-0.05, -0.00, -0.01},
			   {-0.05, -0.00, -0.11}},
			  {{ 0.04, -0.21, -0.10},
			   {-0.04, -0.21, -0.10},
			   {-0.05, -0.00, -0.11},
			   { 0.05,  0.06, -0.11}},
			  {{-0.04, -0.21, -0.02},
			   { 0.04, -0.21, -0.02},
			   { 0.05,  0.06, -0.01},
			   {-0.05, -0.00, -0.01}},
			  {{ 0.05,  0.06, - 0.01},
			   { 0.05,  0.06, - 0.11},
			   {-0.05,  0.00, - 0.11},
			   {-0.05,  0.00, - 0.01}}};

Coord l_hand[4][3][3] =  {{{ 0.04, -0.21, -0.02},
			   { 0.00, -0.32, -0.06},
			   { 0.04, -0.21, -0.10}},
			  {{-0.04, -0.21, -0.10},
			   { 0.00, -0.32, -0.06},
			   {-0.04, -0.21, -0.02}},
			  {{ 0.04, -0.21, -0.10},
			   { 0.00, -0.32, -0.06},
			   {-0.04, -0.21, -0.10}},
			  {{-0.04, -0.21, -0.02},
			   { 0.00, -0.32, -0.06},
			   { 0.04, -0.21, -0.02}}};

Coord r_l_arm[5][4][3] = {{{ 0.04, -0.21,  0.10},
			   { 0.04, -0.21,  0.02},
			   { 0.05,  0.06,  0.01},
			   { 0.05,  0.06,  0.11}},
			  {{-0.04, -0.21,  0.02},
			   {-0.04, -0.21,  0.10},
			   {-0.05, -0.00,  0.11},
			   {-0.05, -0.00,  0.01}},
			  {{ 0.04, -0.21,  0.02},
			   {-0.04, -0.21,  0.02},
			   {-0.05, -0.00,  0.01},
			   { 0.05,  0.06,  0.01}},
			  {{-0.04, -0.21,  0.10},
			   { 0.04, -0.21,  0.10},
			   { 0.05,  0.06,  0.11},
			   {-0.05, -0.00,  0.11}},
			  {{ 0.05,  0.06,  0.11},
			   { 0.05,  0.06,  0.01},
			   {-0.05,  0.00,  0.01},
			   {-0.05,  0.00,  0.11}}};

Coord r_hand[4][3][3] =  {{{ 0.04, -0.21,  0.02},
			   { 0.00, -0.32,  0.06},
			   { 0.04, -0.21,  0.10}},
			  {{-0.04, -0.21,  0.10},
			   { 0.00, -0.32,  0.06},
			   {-0.04, -0.21,  0.02}},
			  {{ 0.04, -0.21,  0.10},
			   { 0.00, -0.32,  0.06},
			   {-0.04, -0.21,  0.10}},
			  {{-0.04, -0.21,  0.02},
			   { 0.00, -0.32,  0.06},
			   { 0.04, -0.21,  0.02}}};

Mech green_mech, blue_mech;


make_mech(m, c1, c2)
    Mech *m;
    int c1, c2;
{
    /*
     * right hand
     */
    makeobj(m->mech_r_hand = genobj());
    {
	pushmatrix();

#ifndef CLOVER
	backface(FALSE);
#endif

	color(c2);
	polf(3, r_hand[B]);
	color(c2);
	polf(3, r_hand[R]);
	color(c2);
	polf(3, r_hand[L]);
	color(c2);
	polf(3, r_hand[F]);

#ifndef CLOVER
	backface(TRUE);
#endif

	popmatrix();
    }
    closeobj();


    /*
     * Left front mech description
     */
    makeobj(m->mech_rl_arm[LF] = genobj());
    {
	/*
	 * right lower arm
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	translate( 0.0, -0.25, 0.0);
	rotate(r_el_rot, 'z');
	color(c1);
	color(c1);
	polf(4, r_l_arm[F]);
	color(c2);
	poly(4, r_l_arm[F]);
	color(c1);
	polf(4, r_l_arm[L]);
	color(c2);
	poly(4, r_l_arm[L]);
	callobj(m->mech_r_hand);
	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ru_arm[LF] = genobj());
    {
	/*
	 * right upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	color(c1);
	polf(4, r_u_arm[F]);
	color(c2);
	poly(4, r_u_arm[F]);
	color(c1);
	polf(6, r_u_arm[L]);
	color(c2);
	poly(6, r_u_arm[L]);
	color(c1);
	polf(4, r_shoulder[T]);
	color(c2);
	poly(4, r_shoulder[T]);
	color(c1);
	polf(4, r_shoulder[F]);
	color(c2);
	poly(4, r_shoulder[F]);
	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rb_foot[LF] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rl_leg[LF] = genobj());
    {
	pushmatrix();

	/*
	 * right lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[L]);
	polf(4, l_leg[F]);
	color(c2);
	poly(4, l_leg[L]);
	poly(4, l_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rf_foot[LF] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[L]);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[L]);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lb_foot[LF] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ll_leg[LF] = genobj());
    {
	pushmatrix();

	/*
	 * left lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[L]);
	polf(4, l_leg[F]);
	color(c2);
	poly(4, l_leg[L]);
	poly(4, l_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lf_foot[LF] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	color(GREEN);
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[L]);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[L]);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ru_leg[LF] = genobj());
    {
	pushmatrix();

	/*
	 * right upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[L]);
	polf(4, u_leg[F]);
	color(c2);
	poly(4, u_leg[L]);
	poly(4, u_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lu_leg[LF] = genobj());
    {
	pushmatrix();

	/*
	 * left upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[L]);
	polf(4, u_leg[F]);
	color(c2);
	poly(4, u_leg[L]);
	poly(4, u_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_torso[LF] = genobj());
    {
	pushmatrix();

	/*
	 * torso
	 */
	/* torso 1 */
	color(c1);
	polf(4, torso1[L]);
	color(c2);
	poly(4, torso1[L]);
	color(c1);
	polf(4, torso1[F]);
	color(c2);
	poly(4, torso1[F]);
	/* torso 2 */
	color(c1);
	polf(4, torso2[L]);
	color(c2);
	poly(4, torso2[L]);
	color(c1);
	polf(4, torso2[F]);
	color(c2);
	poly(4, torso2[F]);
	/* torso 3 */
	color(c1);
	polf(4, torso3[L]);
	color(c2);
	poly(4, torso3[L]);
	color(c1);
	polf(4, torso3[F]);
	color(c2);
	poly(4, torso3[F]);
	/* torso 4 */
	color(c1);
	polf(4, torso4[L]);
	color(c2);
	poly(4, torso4[L]);
	color(c1);
	polf(4, torso4[F]);
	color(c2);
	poly(4, torso4[F]);
	/* head */
	color(c1);
	polf(4, head[L]);
	color(c2);
	poly(4, head[L]);
	color(c1);
	polf(4, head[F]);
	color(c2);
	poly(4, head[F]);

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ll_arm[LF] = genobj());
    {
	/*
	 * left lower arm and hand
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	color(c1);
	polf(6, l_u_arm[R]);
	color(c2);
	poly(6, l_u_arm[R]);
	translate( 0.0, -0.25, 0.0);
	rotate(l_el_rot, 'z');
	/* arm */
	color(c1);
	polf(4, l_l_arm[R]);
	color(c2);
	poly(4, l_l_arm[R]);
	color(c1);
	polf(4, l_l_arm[L]);
	color(c2);
	poly(4, l_l_arm[L]);
	color(c1);
	polf(4, l_l_arm[F]);
	color(c2);
	poly(4, l_l_arm[F]);
        /* hand */
	color(c1);
	polf(3, l_hand[R]);
	color(c2);
	poly(3, l_hand[R]);
	color(c1);
	polf(3, l_hand[L]);
	color(c2);
	poly(3, l_hand[L]);
	color(c1);
	polf(3, l_hand[F]);
	color(c2);
	poly(3, l_hand[F]);
	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lu_arm[LF] = genobj());
    {
	pushmatrix();

	/*
	 * left upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	color(c1);
	polf(6, l_u_arm[L]);
	color(c2);
	poly(6, l_u_arm[L]);
	color(c1);
	polf(4, l_u_arm[F]);
	color(c2);
	poly(4, l_u_arm[F]);
	color(c1);
	polf(4, l_shoulder[T]);
	color(c2);
	poly(4, l_shoulder[T]);
	color(c1);
	polf(4, l_shoulder[S]);
	color(c2);
	poly(4, l_shoulder[S]);
	color(c1);
	polf(4, l_shoulder[F]);
	color(c2);
	poly(4, l_shoulder[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    /*
     * Right front mech description
     */
    makeobj(m->mech_ll_arm[RF] = genobj());
    {
	/*
	 * left lower arm and hand
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	translate( 0.0, -0.25, 0.0);
	rotate(l_el_rot, 'z');
	/* arm */
	color(c1);
	polf(4, l_l_arm[F]);
	color(c2);
	poly(4, l_l_arm[F]);
	color(c1);
	polf(4, l_l_arm[R]);
	color(c2);
	poly(4, l_l_arm[R]);
        /* hand */
	color(c1);
	polf(3, l_hand[F]);
	color(c2);
	poly(3, l_hand[F]);
	color(c1);
	polf(3, l_hand[R]);
	color(c2);
	poly(3, l_hand[R]);
	popmatrix();
    }
    closeobj();


    makeobj(m->mech_lu_arm[RF] = genobj());
    {
	pushmatrix();

	/*
	 * left upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	color(c1);
	polf(4, l_u_arm[F]);
	color(c2);
	poly(4, l_u_arm[F]);
	color(c1);
	polf(6, l_u_arm[R]);
	color(c2);
	poly(6, l_u_arm[R]);
	color(c1);
	polf(4, l_shoulder[T]);
	color(c2);
	poly(4, l_shoulder[T]);
	color(c1);
	polf(4, l_shoulder[F]);
	color(c2);
	poly(4, l_shoulder[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_lb_foot[RF] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_ll_leg[RF] = genobj());
    {
	pushmatrix();

	/*
	 * left lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[R]);
	polf(4, l_leg[F]);
	color(c2);
	poly(4, l_leg[R]);
	poly(4, l_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_lf_foot[RF] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[R]);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[R]);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_rb_foot[RF] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_rl_leg[RF] = genobj());
    {
	pushmatrix();

	/*
	 * right lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[R]);
	polf(4, l_leg[F]);
	color(c2);
	poly(4, l_leg[R]);
	poly(4, l_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_rf_foot[RF] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[R]);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[R]);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_lu_leg[RF] = genobj());
    {
	pushmatrix();

	/*
	 * left upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[R]);
	polf(4, u_leg[F]);
	color(c2);
	poly(4, u_leg[R]);
	poly(4, u_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_ru_leg[RF] = genobj());
    {
	pushmatrix();

	/*
	 * right upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[R]);
	polf(4, u_leg[F]);
	color(c2);
	poly(4, u_leg[R]);
	poly(4, u_leg[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_torso[RF] = genobj());
    {
	pushmatrix();

	/*
	 * torso
	 */
	/* torso 1 */
	color(c1);
	polf(4, torso1[R]);
	color(c2);
	poly(4, torso1[R]);
	color(c1);
	polf(4, torso1[F]);
	color(c2);
	poly(4, torso1[F]);
	/* torso 2 */
	color(c1);
	polf(4, torso2[R]);
	color(c2);
	poly(4, torso2[R]);
	color(c1);
	polf(4, torso2[F]);
	color(c2);
	poly(4, torso2[F]);
	/* torso 3 */
	color(c1);
	polf(4, torso3[R]);
	color(c2);
	poly(4, torso3[R]);
	color(c1);
	polf(4, torso3[F]);
	color(c2);
	poly(4, torso3[F]);
	/* torso 4 */
	color(c1);
	polf(4, torso4[R]);
	color(c2);
	poly(4, torso4[R]);
	color(c1);
	polf(4, torso4[F]);
	color(c2);
	poly(4, torso4[F]);
	/* head */
	color(c1);
	polf(4, head[R]);
	color(c2);
	poly(4, head[R]);
	color(c1);
	polf(4, head[F]);
	color(c2);
	poly(4, head[F]);

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_rl_arm[RF] = genobj());
    {
	pushmatrix();

	/*
	 * right lower arm
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	color(c1);
	polf(6, r_u_arm[L]);
	color(c2);
	poly(6, r_u_arm[L]);
	translate( 0.0, -0.25, 0.0);
	rotate(r_el_rot, 'z');
	color(c1);
	polf(4, r_l_arm[L]);
	color(c2);
	poly(4, r_l_arm[L]);
	color(c1);
	polf(4, r_l_arm[R]);
	color(c2);
	poly(4, r_l_arm[R]);
	color(c1);
	polf(4, r_l_arm[F]);
	color(c2);
	poly(4, r_l_arm[F]);
	callobj(m->mech_r_hand);
	popmatrix();

	popmatrix();
    }
    closeobj();


    makeobj(m->mech_ru_arm[RF] = genobj());
    {
	pushmatrix();

	/*
	 * right upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	color(c1);
	polf(6, r_u_arm[R]);
	color(c2);
	poly(6, r_u_arm[R]);
	color(c1);
	polf(4, r_u_arm[F]);
	color(c2);
	poly(4, r_u_arm[F]);
	color(c1);
	polf(4, r_shoulder[T]);
	color(c2);
	poly(4, r_shoulder[T]);
	color(c1);
	polf(4, r_shoulder[S]);
	color(c2);
	poly(4, r_shoulder[S]);
	color(c1);
	polf(4, r_shoulder[F]);
	color(c2);
	poly(4, r_shoulder[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();


    /*
     * Left back mech description
     */
    makeobj(m->mech_rl_arm[LB] = genobj());
    {
	pushmatrix();

	/*
	 * right lower arm
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	translate( 0.0, -0.25, 0.0);
	rotate(r_el_rot, 'z');
	callobj(m->mech_r_hand);
	color(c1);
	polf(4, r_l_arm[B]);
	color(c2);
	poly(4, r_l_arm[B]);
	color(c1);
	polf(4, r_l_arm[U]);
	color(c2);
	poly(4, r_l_arm[U]);
	color(c1);
	polf(4, r_l_arm[L]);
	color(c2);
	poly(4, r_l_arm[L]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ru_arm[LB] = genobj());
    {
	pushmatrix();

	/*
	 * right upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	color(c1);
	polf(4, r_u_arm[B]);
	color(c2);
	poly(4, r_u_arm[B]);
	color(c1);
	polf(6, r_u_arm[L]);
	color(c2);
	poly(6, r_u_arm[L]);
	color(c1);
	polf(4, r_shoulder[T]);
	color(c2);
	poly(4, r_shoulder[T]);
	color(c1);
	polf(4, r_shoulder[B]);
	color(c2);
	poly(4, r_shoulder[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rf_foot[LB] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rl_leg[LB] = genobj());
    {
	pushmatrix();

	/*
	 * right lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[L]);
	polf(4, l_leg[B]);
	color(c2);
	poly(4, l_leg[L]);
	poly(4, l_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rb_foot[LB] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[L]);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[L]);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lf_foot[LB] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ll_leg[LB] = genobj());
    {
	pushmatrix();

	/*
	 * left lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[L]);
	polf(4, l_leg[B]);
	color(c2);
	poly(4, l_leg[L]);
	poly(4, l_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lb_foot[LB] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[L]);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[L]);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ru_leg[LB] = genobj());
    {
	pushmatrix();

	/*
	 * right upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[L]);
	polf(4, u_leg[B]);
	color(c2);
	poly(4, u_leg[L]);
	poly(4, u_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lu_leg[LB] = genobj());
    {
	pushmatrix();

	/*
	 * left upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[L]);
	polf(4, u_leg[B]);
	color(c2);
	poly(4, u_leg[L]);
	poly(4, u_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_torso[LB] = genobj());
    {
	pushmatrix();

	/*
	 * torso
	 */
	/* torso 1 */
	color(c1);
	polf(4, torso1[L]);
	color(c2);
	poly(4, torso1[L]);
	color(c1);
	polf(4, torso1[B]);
	color(c2);
	poly(4, torso1[B]);
	/* torso 2 */
	color(c1);
	polf(4, torso2[L]);
	color(c2);
	poly(4, torso2[L]);
	color(c1);
	polf(4, torso2[B]);
	color(c2);
	poly(4, torso2[B]);
	/* torso 3 */
	color(c1);
	polf(4, torso3[L]);
	color(c2);
	poly(4, torso3[L]);
	color(c1);
	polf(4, torso3[B]);
	color(c2);
	poly(4, torso3[B]);
	/* torso 4 */
	color(c1);
	polf(4, torso4[F]);
	color(c2);
	poly(4, torso4[F]);
	/* head */
	color(c1);
	polf(4, head[R]);
	color(c2);
	poly(4, head[R]);
	color(c1);
	polf(4, head[B]);
	color(c2);
	poly(4, head[B]);
	color(c1);
	polf(4, head[L]);
	color(c2);
	poly(4, head[L]);
	/* torso 4 */
	color(c1);
	polf(4, torso4[L]);
	color(c2);
	poly(4, torso4[L]);
	color(c1);
	polf(4, torso4[B]);
	color(c2);
	poly(4, torso4[B]);

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ll_arm[LB] = genobj());
    {
	/*
	 * left lower arm and hand
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	color(c1);
	polf(6, l_u_arm[R]);
	color(c2);
	poly(6, l_u_arm[R]);
	translate( 0.0, -0.25, 0.0);
	rotate(l_el_rot, 'z');
        /* hand */
	color(c1);
	polf(3, l_hand[R]);
	color(c2);
	poly(3, l_hand[R]);
	color(c1);
	polf(3, l_hand[L]);
	color(c2);
	poly(3, l_hand[L]);
	color(c1);
	polf(3, l_hand[B]);
	color(c2);
	poly(3, l_hand[B]);
	/* arm */
	color(c1);
	polf(4, l_l_arm[R]);
	color(c2);
	poly(4, l_l_arm[R]);
	color(c1);
	polf(4, l_l_arm[L]);
	color(c2);
	poly(4, l_l_arm[L]);
	color(c1);
	polf(4, l_l_arm[B]);
	color(c2);
	poly(4, l_l_arm[B]);
	color(c1);
	polf(4, l_l_arm[U]);
	color(c2);
	poly(4, l_l_arm[U]);
	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lu_arm[LB] = genobj());
    {
	pushmatrix();

	/*
	 * left upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	color(c1);
	polf(6, l_u_arm[L]);
	color(c2);
	poly(6, l_u_arm[L]);
	color(c1);
	polf(4, l_u_arm[B]);
	color(c2);
	poly(4, l_u_arm[B]);
	color(c1);
	polf(4, l_shoulder[T]);
	color(c2);
	poly(4, l_shoulder[T]);
	color(c1);
	polf(4, l_shoulder[S]);
	color(c2);
	poly(4, l_shoulder[S]);
	color(c1);
	polf(4, l_shoulder[B]);
	color(c2);
	poly(4, l_shoulder[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    /*
     *  Right back mech description
     */
    makeobj(m->mech_ll_arm[RB] = genobj());
    {
	/*
	 * left lower arm and hand
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	translate( 0.0, -0.25, 0.0);
	rotate(l_el_rot, 'z');
        /* hand */
	color(c1);
	polf(3, l_hand[B]);
	color(c2);
	poly(3, l_hand[B]);
	color(c1);
	polf(3, l_hand[R]);
	color(c2);
	poly(3, l_hand[R]);
	/* arm */
	color(c1);
	polf(4, l_l_arm[B]);
	color(c2);
	poly(4, l_l_arm[B]);
	color(c1);
	polf(4, l_l_arm[R]);
	color(c2);
	poly(4, l_l_arm[R]);
	color(c1);
	polf(4, l_l_arm[U]);
	color(c2);
	poly(4, l_l_arm[U]);
	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lu_arm[RB] = genobj());
    {
	pushmatrix();

	/*
	 * left upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, -0.2);
	rotate(l_sh_rot, 'z');
	color(c1);
	polf(4, l_u_arm[B]);
	color(c2);
	poly(4, l_u_arm[B]);
	color(c1);
	polf(6, l_u_arm[R]);
	color(c2);
	poly(6, l_u_arm[R]);
	color(c1);
	polf(4, l_shoulder[T]);
	color(c2);
	poly(4, l_shoulder[T]);
	color(c1);
	polf(4, l_shoulder[B]);
	color(c2);
	poly(4, l_shoulder[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lf_foot[RB] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ll_leg[RB] = genobj());
    {
	pushmatrix();

	/*
	 * left lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[R]);
	polf(4, l_leg[B]);
	color(c2);
	poly(4, l_leg[R]);
	poly(4, l_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lb_foot[RB] = genobj());
    {
	pushmatrix();

	/*
	 * left foot
	 */
	pushmatrix();
	translate(0.0, 0.0, -0.11);
	color(c1);
	polf(4, foot[R]);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[R]);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rf_foot[RB] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[F]);
	color(c2);
	poly(4, foot[F]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rl_leg[RB] = genobj());
    {
	pushmatrix();

	/*
	 * right lower leg
	 */
	pushmatrix();
	color(c1);
	polf(4, l_leg[R]);
	polf(4, l_leg[B]);
	color(c2);
	poly(4, l_leg[R]);
	poly(4, l_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rb_foot[RB] = genobj());
    {
	pushmatrix();

	/*
	 * right foot
	 */
	pushmatrix();
	translate(0.0, 0.0,  0.11);
	color(c1);
	polf(4, foot[R]);
	polf(4, foot[B]);
	color(c2);
	poly(4, foot[R]);
	poly(4, foot[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_lu_leg[RB] = genobj());
    {
	pushmatrix();

	/*
	 * left upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[R]);
	polf(4, u_leg[B]);
	color(c2);
	poly(4, u_leg[R]);
	poly(4, u_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ru_leg[RB] = genobj());
    {
	pushmatrix();

	/*
	 * right upper leg
	 */
	pushmatrix();
	color(c1);
	polf(4, u_leg[R]);
	polf(4, u_leg[B]);
	color(c2);
	poly(4, u_leg[R]);
	poly(4, u_leg[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_torso[RB] = genobj());
    {
	pushmatrix();

	/*
	 * torso
	 */
	/* torso 1 */
	color(c1);
	polf(4, torso1[R]);
	color(c2);
	poly(4, torso1[R]);
	color(c1);
	polf(4, torso1[B]);
	color(c2);
	poly(4, torso1[B]);
	/* torso 2 */
	color(c1);
	polf(4, torso2[R]);
	color(c2);
	poly(4, torso2[R]);
	color(c1);
	polf(4, torso2[B]);
	color(c2);
	poly(4, torso2[B]);
	/* torso 3 */
	color(c1);
	polf(4, torso3[R]);
	color(c2);
	poly(4, torso3[R]);
	color(c1);
	polf(4, torso3[B]);
	color(c2);
	poly(4, torso3[B]);
	/* torso 4 */
	color(c1);
	polf(4, torso4[F]);
	color(c2);
	poly(4, torso4[F]);
	/* head */
	color(c1);
	polf(4, head[L]);
	color(c2);
	poly(4, head[L]);
	color(c1);
	polf(4, head[B]);
	color(c2);
	poly(4, head[B]);
	color(c1);
	polf(4, head[R]);
	color(c2);
	poly(4, head[R]);
	/* torso 4 */
	color(c1);
	polf(4, torso4[R]);
	color(c2);
	poly(4, torso4[R]);
	color(c1);
	polf(4, torso4[B]);
	color(c2);
	poly(4, torso4[B]);

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_rl_arm[RB] = genobj());
    {
	pushmatrix();

	/*
	 * right lower arm
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	color(c1);
	polf(6, r_u_arm[L]);
	color(c2);
	poly(6, r_u_arm[L]);
	translate( 0.0, -0.25, 0.0);
	rotate(r_el_rot, 'z');
	callobj(m->mech_r_hand);
	color(c1);
	polf(4, r_l_arm[L]);
	color(c2);
	poly(4, r_l_arm[L]);
	color(c1);
	polf(4, r_l_arm[R]);
	color(c2);
	poly(4, r_l_arm[R]);
	color(c1);
	polf(4, r_l_arm[B]);
	color(c2);
	poly(4, r_l_arm[B]);
	color(c1);
	polf(4, r_l_arm[U]);
	color(c2);
	poly(4, r_l_arm[U]);
	popmatrix();

	popmatrix();
    }
    closeobj();
    

    makeobj(m->mech_ru_arm[RB] = genobj());
    {
	pushmatrix();

	/*
	 * right upper arm and shoulder
	 */
	pushmatrix();
	translate(-0.03, 0.38, 0.2);
	rotate(r_sh_rot, 'z');
	color(c1);
	polf(6, r_u_arm[R]);
	color(c2);
	poly(6, r_u_arm[R]);
	color(c1);
	polf(4, r_u_arm[B]);
	color(c2);
	poly(4, r_u_arm[B]);
	color(c1);
	polf(4, r_shoulder[T]);
	color(c2);
	poly(4, r_shoulder[T]);
	color(c1);
	polf(4, r_shoulder[S]);
	color(c2);
	poly(4, r_shoulder[S]);
	color(c1);
	polf(4, r_shoulder[B]);
	color(c2);
	poly(4, r_shoulder[B]);
	popmatrix();

	popmatrix();
    }
    closeobj();
}



draw_mech(v)
    struct thing *v;
{
    short fbbuf[20];
    Mech *m;

    pushmatrix();

    translate(v->xpos, v->ypos, -v->zpos);
    rotate(900-v->yrot, 'y');

    feedback(fbbuf, 10);
	move( 0.25, 0.0,  0.25);
	draw(-0.25, 1.0, -0.25);
	move(-0.25, 0.0,  0.25);
	draw( 0.25, 1.0, -0.25);
	move( 0.25, 1.0,  0.25);
	draw(-0.25, 0.0, -0.25);
	move(-0.25, 1.0,  0.25);
	draw( 0.25, 0.0, -0.25);
    if (1 || endfeedback(fbbuf))
    {
	Matrix base_robot;
	getmatrix(base_robot);

	switch(v->type & MECH_TYPE)
	{
	    case GREEN_MECH:
		m = &green_mech;
		break;
	    case BLUE_MECH:
		m = &blue_mech;
		break;
	    default:
		m = &green_mech;
		break;
	}

#ifndef CLOVER
	if (v->type & EXPLODE)
	    backface(FALSE);
#endif

	pushmatrix();
	if (v->rel_rot >= 0 && v->rel_rot < 900)
	{
	    callobj(m->mech_rf_foot[LB]);
	    translate(0.0, 0.1,  0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_rl_leg[LB]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_ru_leg[LB]);
	    loadmatrix(base_robot);
	    callobj(m->mech_rb_foot[LB]);
	    callobj(m->mech_lf_foot[LB]);
	    translate(0.0, 0.1,  -0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_ll_leg[LB]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_lu_leg[LB]);
	    pushmatrix();
	    loadmatrix(base_robot);
	    callobj(m->mech_lb_foot[LB]);
	    popmatrix();
	    translate(-0.06, 0.25, 0.11);
	    rotate(v->torso_x_rot, 'x');
	    rotate(v->torso_z_rot, 'z');
	    callobj(m->mech_rl_arm[LB]);
	    callobj(m->mech_ru_arm[LB]);
	    callobj(m->mech_torso[LB]);
	    callobj(m->mech_ll_arm[LB]);
	    callobj(m->mech_lu_arm[LB]);
	}
	else if (v->rel_rot >= 900 && v->rel_rot < 1800)
	{
	    callobj(m->mech_lf_foot[RB]);
	    translate(0.0, 0.1,  -0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_ll_leg[RB]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_lu_leg[RB]);
	    loadmatrix(base_robot);
	    callobj(m->mech_lb_foot[RB]);
	    callobj(m->mech_rf_foot[RB]);
	    translate(0.0, 0.1,  0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_rl_leg[RB]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_ru_leg[RB]);
	    pushmatrix();
	    loadmatrix(base_robot);
	    callobj(m->mech_rb_foot[RB]);
	    popmatrix();
	    translate(-0.06, 0.25, -0.11);
	    rotate(v->torso_x_rot, 'x');
	    rotate(v->torso_z_rot, 'z');
	    callobj(m->mech_ll_arm[RB]);
	    callobj(m->mech_lu_arm[RB]);
	    callobj(m->mech_torso[RB]);
	    callobj(m->mech_rl_arm[RB]);
	    callobj(m->mech_ru_arm[RB]);
	}
	else if (v->rel_rot >= 1800 && v->rel_rot < 2700)
	{
	    callobj(m->mech_lb_foot[RF]);
	    translate(0.0, 0.1, -0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_ll_leg[RF]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_lu_leg[RF]);
	    loadmatrix(base_robot);
	    callobj(m->mech_lf_foot[RF]);
	    callobj(m->mech_rb_foot[RF]);
	    translate(0.0, 0.1,  0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_rl_leg[RF]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_ru_leg[RF]);
	    pushmatrix();
	    loadmatrix(base_robot);
	    callobj(m->mech_rf_foot[RF]);
	    popmatrix();
	    translate(-0.06, 0.25, -0.11);
	    rotate(v->torso_x_rot, 'x');
	    rotate(v->torso_z_rot, 'z');
	    callobj(m->mech_ll_arm[RF]);
	    callobj(m->mech_lu_arm[RF]);
	    callobj(m->mech_torso[RF]);
	    callobj(m->mech_rl_arm[RF]);
	    callobj(m->mech_ru_arm[RF]);
	}
	else
	{
	    callobj(m->mech_rb_foot[LF]);
	    translate(0.0, 0.1,  0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_rl_leg[LF]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_ru_leg[LF]);
	    loadmatrix(base_robot);
	    callobj(m->mech_rf_foot[LF]);
	    callobj(m->mech_lb_foot[LF]);
	    translate(0.0, 0.1, -0.11);
	    rotate(v->anckle_rot, 'z');
	    callobj(m->mech_ll_leg[LF]);
	    translate(0.06, 0.2,  0.0);
	    rotate(v->knee_rot, 'z');
	    callobj(m->mech_lu_leg[LF]);
	    pushmatrix();
	    loadmatrix(base_robot);
	    callobj(m->mech_lf_foot[LF]);
	    popmatrix();
	    translate(-0.06, 0.25, 0.11);
	    rotate(v->torso_x_rot, 'x');
	    rotate(v->torso_z_rot, 'z');
	    callobj(m->mech_rl_arm[LF]);
	    callobj(m->mech_ru_arm[LF]);
	    callobj(m->mech_torso[LF]);
	    callobj(m->mech_ll_arm[LF]);
	    callobj(m->mech_lu_arm[LF]);
	}
	popmatrix();
	if (v->type & EXPLODE)
	{
#ifndef CLOVER
	    backface(TRUE);
#endif
	    if (!(v->type & DEAD))
		boom();
	}
    }

    popmatrix();
}
