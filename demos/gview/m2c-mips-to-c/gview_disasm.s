.text
.set noreorder
.set gp=0x1000bd70


# === __start ===
glabel __start
/* 004001e0 */  lw         $a0, ($sp)
/* 004001e4 */  lui        $gp, 0x1001
/* 004001e8 */  addiu      $a1, $sp, 4
/* 004001ec */  addiu      $gp, $gp, -0x4290
/* 004001f0 */  addiu      $a2, $a1, 4
/* 004001f4 */  sll        $v0, $a0, 2
/* 004001f8 */  sw         $a1, -0x7a88($gp)                        # .sbss @ 0x100042e8
/* 004001fc */  addu       $a2, $a2, $v0

# === crt_main ===
glabel crt_main
/* 00400200 */  addiu      $sp, $sp, -0x18
/* 00400204 */  sw         $a2, -0x7a90($gp)                        # .sbss @ 0x100042e0
/* 00400208 */  sw         $zero, 0x14($sp)
/* 0040020c */  move       $fp, $zero
/* 00400210 */  jal        0x40fb3c
/* 00400214 */  sw         $a0, -0x7a8c($gp)                        # .sbss @ 0x100042e4
/* 00400218 */  jal        0x40d2c0
/* 0040021c */  nop        
/* 00400220 */  jal        0x40d2d0
/* 00400224 */  move       $a0, $zero
/* 00400228 */  lw         $a0, -0x7a8c($gp)                        # .sbss @ 0x100042e4
/* 0040022c */  lw         $a1, -0x7a88($gp)                        # .sbss @ 0x100042e8
/* 00400230 */  lw         $a2, -0x7a90($gp)                        # .sbss @ 0x100042e0
/* 00400234 */  jal        0x4002ac                                 # parse_args_and_init
/* 00400238 */  nop        
/* 0040023c */  jal        0x40d3c0
/* 00400240 */  move       $a0, $v0
/* 00400244 */  break      
/* 00400248 */  jr         $ra
/* 0040024c */  nop        
/* 00400250 */  addiu      $sp, $sp, 8
/* 00400254 */  jr         $ra
/* 00400258 */  move       $ra, $at
/* 0040025c */  jr         $ra
/* 00400260 */  nop        
/* 00400264 */  nop        
/* 00400268 */  nop        
/* 0040026c */  nop        

# === exit_handler ===
glabel exit_handler
/* 00400270 */  addiu      $sp, $sp, -0x18
/* 00400274 */  sw         $ra, 0x14($sp)
/* 00400278 */  lui        $a0, 0x1000
/* 0040027c */  lui        $a3, 0x1000
/* 00400280 */  addiu      $a3, $a3, 0x1c0
/* 00400284 */  addiu      $a0, $a0, 0x36b4
/* 00400288 */  addiu      $a1, $gp, -0x7e90
/* 0040028c */  jal        0xf801150                                # fclose
/* 00400290 */  addiu      $a2, $gp, -0x7ea0
/* 00400294 */  jal        0x40d3c0
/* 00400298 */  addiu      $a0, $zero, 1
/* 0040029c */  lw         $ra, 0x14($sp)
/* 004002a0 */  addiu      $sp, $sp, 0x18
/* 004002a4 */  jr         $ra
/* 004002a8 */  nop        

# === parse_args_and_init ===
glabel parse_args_and_init
/* 004002ac */  addiu      $sp, $sp, -0x20d0
/* 004002b0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 004002b4 */  sw         $ra, 0x34($sp)
/* 004002b8 */  sw         $s4, 0x30($sp)
/* 004002bc */  sw         $s2, 0x28($sp)
/* 004002c0 */  sw         $s3, 0x2c($sp)
/* 004002c4 */  sw         $a0, 0x20d0($sp)
/* 004002c8 */  sw         $a1, 0x20d4($sp)
/* 004002cc */  sw         $zero, 0xb8($sp)
/* 004002d0 */  sw         $zero, 0xb4($sp)
/* 004002d4 */  sw         $zero, 0x20c0($sp)
/* 004002d8 */  sw         $zero, 0x48($t6)
/* 004002dc */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004002e0 */  addiu      $t8, $zero, -1
/* 004002e4 */  sw         $zero, 0xc8($t7)
/* 004002e8 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 004002ec */  addiu      $t4, $gp, -0x7e80
/* 004002f0 */  sw         $t8, 0xd0($t9)
/* 004002f4 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 004002f8 */  lui        $a2, 0x1000
/* 004002fc */  sw         $zero, 0x38($t0)
/* 00400300 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400304 */  addiu      $t0, $gp, -0x7e78
/* 00400308 */  sw         $zero, 0xdc($t1)
/* 0040030c */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400310 */  addiu      $a2, $a2, 0x234
/* 00400314 */  sw         $zero, 0x104($t2)
/* 00400318 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 0040031c */  addiu      $t2, $gp, -0x7e74
/* 00400320 */  sw         $zero, 0xbc($t3)
/* 00400324 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00400328 */  nop        
/* 0040032c */  sw         $t4, 0xc0($t5)
/* 00400330 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400334 */  addiu      $t4, $gp, -0x7e70
/* 00400338 */  sw         $zero, 0x68($t6)
/* 0040033c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400340 */  lwc1       $f4, -0x7ee0($gp)                        # .lit4: 1
/* 00400344 */  nop        
/* 00400348 */  swc1       $f4, 0x6c($t7)
/* 0040034c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400350 */  nop        
/* 00400354 */  sw         $zero, 0x90($t8)
/* 00400358 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 0040035c */  nop        
/* 00400360 */  sw         $zero, 0x94($t9)
/* 00400364 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400368 */  nop        
/* 0040036c */  sw         $t0, 0x98($t1)
/* 00400370 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400374 */  nop        
/* 00400378 */  sw         $t2, 0x9c($t3)
/* 0040037c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00400380 */  nop        
/* 00400384 */  sw         $t4, 0x74($t5)
/* 00400388 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 0040038c */  nop        
/* 00400390 */  sw         $zero, 0x78($t6)
/* 00400394 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400398 */  nop        
/* 0040039c */  sw         $zero, 0xa0($t7)
/* 004003a0 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004003a4 */  nop        
/* 004003a8 */  sw         $zero, 0xb8($t8)
/* 004003ac */  lw         $a1, 0x20d4($sp)
/* 004003b0 */  lw         $a0, 0x20d0($sp)
/* 004003b4 */  jal        0x40d3f0
/* 004003b8 */  sw         $zero, -0x7bc0($gp)                      # .sdata @ 0x100041b0
/* 004003bc */  addiu      $at, $zero, -1
/* 004003c0 */  bne        $v0, $at, 0x4003dc
/* 004003c4 */  nop        
/* 004003c8 */  lui        $s3, 0x1000
/* 004003cc */  addiu      $s3, $s3, 0x36b4
/* 004003d0 */  addiu      $s4, $gp, -0x7ea0
/* 004003d4 */  b          0x400a24
/* 004003d8 */  addiu      $s2, $zero, 1
/* 004003dc */  sw         $s6, 0x40($sp)
/* 004003e0 */  sw         $fp, 0x38($sp)
/* 004003e4 */  sw         $s5, 0x44($sp)
/* 004003e8 */  sw         $s7, 0x3c($sp)
/* 004003ec */  lui        $fp, 0x1000
/* 004003f0 */  lui        $s6, 0x1000
/* 004003f4 */  lui        $s3, 0x1000
/* 004003f8 */  sw         $s0, 0x4c($sp)
/* 004003fc */  addiu      $s3, $s3, 0x36b4
/* 00400400 */  addiu      $s6, $s6, 0x380
/* 00400404 */  addiu      $fp, $fp, 0x3c0
/* 00400408 */  addiu      $s7, $zero, 0x2c
/* 0040040c */  addiu      $s5, $gp, -0x7e44
/* 00400410 */  sw         $s1, 0x48($sp)
/* 00400414 */  addiu      $s2, $zero, 1
/* 00400418 */  addiu      $s4, $gp, -0x7ea0
/* 0040041c */  b          0x40089c
/* 00400420 */  move       $a2, $v0
/* 00400424 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400428 */  addiu      $a1, $gp, -0x7e6c
/* 0040042c */  sw         $s2, 0x68($t9)
/* 00400430 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400434 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 00400438 */  move       $a2, $t0
/* 0040043c */  jal        0x40d7a4
/* 00400440 */  addiu      $a3, $t0, 4
/* 00400444 */  beq        $v0, $s2, 0x400460
/* 00400448 */  move       $s0, $v0
/* 0040044c */  addiu      $at, $zero, 2
/* 00400450 */  beq        $v0, $at, 0x400460
/* 00400454 */  nop        
/* 00400458 */  jal        0x400270                                 # exit_handler
/* 0040045c */  nop        
/* 00400460 */  bne        $s0, $s2, 0x40047c
/* 00400464 */  nop        
/* 00400468 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 0040046c */  nop        
/* 00400470 */  lw         $t2, ($t1)
/* 00400474 */  nop        
/* 00400478 */  sw         $t2, 4($t1)
/* 0040047c */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400480 */  lui        $a1, 0x1000
/* 00400484 */  lw         $a2, ($t3)
/* 00400488 */  lw         $a3, 4($t3)
/* 0040048c */  addiu      $a1, $a1, 0x2b8
/* 00400490 */  jal        0xf801150                                # fclose
/* 00400494 */  move       $a0, $s3
/* 00400498 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 0040049c */  nop        
/* 004004a0 */  lw         $t5, ($t4)
/* 004004a4 */  lw         $t6, 4($t4)
/* 004004a8 */  mtc1       $t5, $f6
/* 004004ac */  mtc1       $t6, $f16
/* 004004b0 */  cvt.s.w    $f8, $f6
/* 004004b4 */  cvt.d.w    $f18, $f16
/* 004004b8 */  cvt.d.s    $f10, $f8
/* 004004bc */  nop        
/* 004004c0 */  div.d      $f4, $f10, $f18
/* 004004c4 */  cvt.s.d    $f6, $f4
/* 004004c8 */  b          0x4009e8
/* 004004cc */  swc1       $f6, 0x6c($t4)
/* 004004d0 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 004004d4 */  jal        0xf801300                                # open
/* 004004d8 */  nop        
/* 004004dc */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004004e0 */  b          0x4009e8
/* 004004e4 */  sw         $v0, 0x74($t7)
/* 004004e8 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004004ec */  addiu      $a1, $gp, -0x7e64
/* 004004f0 */  sw         $s2, 0x78($t8)
/* 004004f4 */  lw         $a2, -0x7e98($gp)                        # view_state_ptr
/* 004004f8 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 004004fc */  jal        0x40d7a4
/* 00400500 */  addiu      $a2, $a2, 0x7c
/* 00400504 */  beq        $v0, $s2, 0x400514
/* 00400508 */  nop        
/* 0040050c */  jal        0x400270                                 # exit_handler
/* 00400510 */  nop        
/* 00400514 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400518 */  lui        $a1, 0x1000
/* 0040051c */  lwc1       $f8, 0x7c($t9)
/* 00400520 */  addiu      $a1, $a1, 0x2d4
/* 00400524 */  cvt.d.s    $f16, $f8
/* 00400528 */  mfc1       $a3, $f16
/* 0040052c */  mfc1       $a2, $f17
/* 00400530 */  jal        0xf801150                                # fclose
/* 00400534 */  move       $a0, $s3
/* 00400538 */  b          0x4009ec
/* 0040053c */  lw         $a0, 0x20d0($sp)
/* 00400540 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400544 */  lui        $a1, 0x1000
/* 00400548 */  sw         $s2, 0x80($t0)
/* 0040054c */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400550 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 00400554 */  addiu      $t1, $t2, 0x8c
/* 00400558 */  sw         $t1, 0x10($sp)
/* 0040055c */  addiu      $a1, $a1, 0x2e8
/* 00400560 */  addiu      $a2, $t2, 0x84
/* 00400564 */  jal        0x40d7a4
/* 00400568 */  addiu      $a3, $t2, 0x88
/* 0040056c */  addiu      $at, $zero, 3
/* 00400570 */  beq        $v0, $at, 0x400580
/* 00400574 */  nop        
/* 00400578 */  jal        0x400270                                 # exit_handler
/* 0040057c */  nop        
/* 00400580 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400584 */  lui        $a1, 0x1000
/* 00400588 */  lwc1       $f4, 0x88($t3)
/* 0040058c */  lwc1       $f10, 0x84($t3)
/* 00400590 */  cvt.d.s    $f6, $f4
/* 00400594 */  swc1       $f6, 0x14($sp)
/* 00400598 */  swc1       $f7, 0x10($sp)
/* 0040059c */  lwc1       $f8, 0x8c($t3)
/* 004005a0 */  cvt.d.s    $f18, $f10
/* 004005a4 */  mfc1       $a3, $f18
/* 004005a8 */  mfc1       $a2, $f19
/* 004005ac */  cvt.d.s    $f16, $f8
/* 004005b0 */  swc1       $f16, 0x1c($sp)
/* 004005b4 */  swc1       $f17, 0x18($sp)
/* 004005b8 */  addiu      $a1, $a1, 0x2f4
/* 004005bc */  jal        0xf801150                                # fclose
/* 004005c0 */  move       $a0, $s3
/* 004005c4 */  b          0x4009ec
/* 004005c8 */  lw         $a0, 0x20d0($sp)
/* 004005cc */  lw         $t6, 0xb8($sp)
/* 004005d0 */  addiu      $t5, $zero, 1
/* 004005d4 */  beqz       $t6, 0x4005e4
/* 004005d8 */  sw         $t5, 0xb4($sp)
/* 004005dc */  jal        0x400270                                 # exit_handler
/* 004005e0 */  nop        
/* 004005e4 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 004005e8 */  jal        0xf801300                                # open
/* 004005ec */  nop        
/* 004005f0 */  b          0x4009e8
/* 004005f4 */  sw         $v0, 0xb0($sp)
/* 004005f8 */  lw         $t7, 0xb4($sp)
/* 004005fc */  addiu      $t4, $zero, 1
/* 00400600 */  beqz       $t7, 0x400610
/* 00400604 */  sw         $t4, 0xb8($sp)
/* 00400608 */  jal        0x400270                                 # exit_handler
/* 0040060c */  nop        
/* 00400610 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 00400614 */  jal        0xf801300                                # open
/* 00400618 */  nop        
/* 0040061c */  b          0x4009e8
/* 00400620 */  sw         $v0, 0xb0($sp)
/* 00400624 */  lui        $a0, 0x1000
/* 00400628 */  jal        0xf801250                                # getopt
/* 0040062c */  addiu      $a0, $a0, 0x310
/* 00400630 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400634 */  b          0x4009e8
/* 00400638 */  sw         $s2, 0xb8($t8)
/* 0040063c */  b          0x4009e8
/* 00400640 */  sw         $s2, 0x20c0($sp)
/* 00400644 */  lw         $a2, -0x7e98($gp)                        # view_state_ptr
/* 00400648 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 0040064c */  addiu      $a1, $gp, -0x7e60
/* 00400650 */  jal        0x40d7a4
/* 00400654 */  addiu      $a2, $a2, 0x104
/* 00400658 */  beq        $v0, $s2, 0x400668
/* 0040065c */  nop        
/* 00400660 */  jal        0x400270                                 # exit_handler
/* 00400664 */  nop        
/* 00400668 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 0040066c */  lui        $a0, 0x1000
/* 00400670 */  lw         $a1, 0x104($t9)
/* 00400674 */  jal        0xf801250                                # getopt
/* 00400678 */  addiu      $a0, $a0, 0x330
/* 0040067c */  b          0x4009ec
/* 00400680 */  lw         $a0, 0x20d0($sp)
/* 00400684 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400688 */  b          0x4009e8
/* 0040068c */  sw         $s2, 0x48($t0)
/* 00400690 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400694 */  addiu      $a1, $gp, -0x7e5c
/* 00400698 */  sw         $s2, 0xc8($t2)
/* 0040069c */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 004006a0 */  nop        
/* 004006a4 */  sw         $zero, 0xd4($t1)
/* 004006a8 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 004006ac */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 004006b0 */  addiu      $a2, $t3, 0xcc
/* 004006b4 */  jal        0x40d7a4
/* 004006b8 */  addiu      $a3, $t3, 0xd0
/* 004006bc */  addiu      $at, $zero, 2
/* 004006c0 */  beq        $v0, $at, 0x4006d0
/* 004006c4 */  nop        
/* 004006c8 */  jal        0x400270                                 # exit_handler
/* 004006cc */  nop        
/* 004006d0 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 004006d4 */  nop        
/* 004006d8 */  lw         $t6, 0xd0($t5)
/* 004006dc */  nop        
/* 004006e0 */  bnez       $t6, 0x4006f0
/* 004006e4 */  nop        
/* 004006e8 */  b          0x4006f4
/* 004006ec */  addiu      $a2, $gp, -0x7e54
/* 004006f0 */  addiu      $a2, $gp, -0x7e4c
/* 004006f4 */  lui        $a0, 0x1000
/* 004006f8 */  addiu      $a0, $a0, 0x350
/* 004006fc */  jal        0xf801250                                # getopt
/* 00400700 */  move       $a1, $s4
/* 00400704 */  b          0x4009ec
/* 00400708 */  lw         $a0, 0x20d0($sp)
/* 0040070c */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00400710 */  jal        0x4034f0                                 # init_window_and_gl
/* 00400714 */  sw         $s2, 0xbc($t4)
/* 00400718 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 0040071c */  lui        $a1, 0x1000
/* 00400720 */  sb         $zero, 0x7c($sp)
/* 00400724 */  addiu      $a1, $a1, 0x374
/* 00400728 */  addiu      $a2, $sp, 0x7c
/* 0040072c */  jal        0x40d7a4
/* 00400730 */  move       $s1, $a0
/* 00400734 */  bne        $v0, $s2, 0x4009ec
/* 00400738 */  lw         $a0, 0x20d0($sp)
/* 0040073c */  addiu      $a0, $sp, 0x7c
/* 00400740 */  jal        0xf801130                                # fgets
/* 00400744 */  move       $a1, $s5
/* 00400748 */  beqz       $v0, 0x400778
/* 0040074c */  move       $s0, $v0
/* 00400750 */  move       $a0, $s3
/* 00400754 */  move       $a1, $s6
/* 00400758 */  move       $a2, $s4
/* 0040075c */  jal        0xf801150                                # fclose
/* 00400760 */  addiu      $a3, $sp, 0x7c
/* 00400764 */  move       $a0, $s0
/* 00400768 */  jal        0x403584                                 # load_material_file
/* 0040076c */  addiu      $a1, $sp, 0x7c
/* 00400770 */  b          0x400798
/* 00400774 */  nop        
/* 00400778 */  lui        $a1, 0x1000
/* 0040077c */  addiu      $a1, $a1, 0x3a0
/* 00400780 */  move       $a0, $s3
/* 00400784 */  move       $a2, $s4
/* 00400788 */  jal        0xf801150                                # fclose
/* 0040078c */  addiu      $a3, $sp, 0x7c
/* 00400790 */  jal        0x400270                                 # exit_handler
/* 00400794 */  nop        
/* 00400798 */  jal        0xf801308                                # close
/* 0040079c */  addiu      $a0, $sp, 0x7c
/* 004007a0 */  addu       $s1, $s1, $v0
/* 004007a4 */  lbu        $t7, ($s1)
/* 004007a8 */  nop        
/* 004007ac */  bne        $s7, $t7, 0x4007b8
/* 004007b0 */  nop        
/* 004007b4 */  addiu      $s1, $s1, 1
/* 004007b8 */  sb         $zero, 0x7c($sp)
/* 004007bc */  move       $a0, $s1
/* 004007c0 */  move       $a1, $fp
/* 004007c4 */  jal        0x40d7a4
/* 004007c8 */  addiu      $a2, $sp, 0x7c
/* 004007cc */  beq        $v0, $s2, 0x400740
/* 004007d0 */  addiu      $a0, $sp, 0x7c
/* 004007d4 */  b          0x4009ec
/* 004007d8 */  lw         $a0, 0x20d0($sp)
/* 004007dc */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 004007e0 */  jal        0xf801300                                # open
/* 004007e4 */  nop        
/* 004007e8 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004007ec */  b          0x4009e8
/* 004007f0 */  sw         $v0, 0xc0($t8)
/* 004007f4 */  b          0x4009e8
/* 004007f8 */  sw         $s2, -0x7e94($gp)                        # .sdata @ 0x10003edc
/* 004007fc */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400800 */  nop        
/* 00400804 */  lw         $t0, 0x94($t9)
/* 00400808 */  nop        
/* 0040080c */  beqz       $t0, 0x40081c
/* 00400810 */  nop        
/* 00400814 */  jal        0x400270                                 # exit_handler
/* 00400818 */  nop        
/* 0040081c */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400820 */  nop        
/* 00400824 */  sw         $s2, 0x90($t2)
/* 00400828 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 0040082c */  jal        0xf801300                                # open
/* 00400830 */  nop        
/* 00400834 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400838 */  b          0x4009e8
/* 0040083c */  sw         $v0, 0x98($t1)
/* 00400840 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400844 */  nop        
/* 00400848 */  lw         $t5, 0x90($t3)
/* 0040084c */  nop        
/* 00400850 */  beqz       $t5, 0x400860
/* 00400854 */  nop        
/* 00400858 */  jal        0x400270                                 # exit_handler
/* 0040085c */  nop        
/* 00400860 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400864 */  nop        
/* 00400868 */  sw         $s2, 0x94($t6)
/* 0040086c */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 00400870 */  jal        0xf801300                                # open
/* 00400874 */  nop        
/* 00400878 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 0040087c */  b          0x4009e8
/* 00400880 */  sw         $v0, 0x98($t4)
/* 00400884 */  lw         $a0, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 00400888 */  jal        0xf801300                                # open
/* 0040088c */  nop        
/* 00400890 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400894 */  b          0x4009e8
/* 00400898 */  sw         $v0, 0x9c($t7)
/* 0040089c */  addiu      $at, $zero, 0x6c
/* 004008a0 */  beq        $a2, $at, 0x400690
/* 004008a4 */  slti       $at, $a2, 0x6d
/* 004008a8 */  beqz       $at, 0x400968
/* 004008ac */  addiu      $at, $zero, 0x56
/* 004008b0 */  beq        $a2, $at, 0x4007fc
/* 004008b4 */  slti       $at, $a2, 0x57
/* 004008b8 */  beqz       $at, 0x400930
/* 004008bc */  addiu      $at, $zero, 0x4d
/* 004008c0 */  beq        $a2, $at, 0x4007dc
/* 004008c4 */  slti       $at, $a2, 0x4e
/* 004008c8 */  beqz       $at, 0x40090c
/* 004008cc */  addiu      $at, $zero, 0x46
/* 004008d0 */  beq        $a2, $at, 0x400644
/* 004008d4 */  slti       $at, $a2, 0x47
/* 004008d8 */  beqz       $at, 0x4008f0
/* 004008dc */  addiu      $at, $zero, 0x3f
/* 004008e0 */  beq        $a2, $at, 0x4008fc
/* 004008e4 */  nop        
/* 004008e8 */  b          0x4008fc
/* 004008ec */  nop        
/* 004008f0 */  addiu      $at, $zero, 0x4c
/* 004008f4 */  beq        $a2, $at, 0x400624
/* 004008f8 */  nop        
/* 004008fc */  jal        0x400270                                 # exit_handler
/* 00400900 */  nop        
/* 00400904 */  b          0x4009ec
/* 00400908 */  lw         $a0, 0x20d0($sp)
/* 0040090c */  addiu      $at, $zero, 0x52
/* 00400910 */  beq        $a2, $at, 0x4005f8
/* 00400914 */  slti       $at, $a2, 0x53
/* 00400918 */  beqz       $at, 0x4008fc
/* 0040091c */  addiu      $at, $zero, 0x50
/* 00400920 */  beq        $a2, $at, 0x4007f4
/* 00400924 */  nop        
/* 00400928 */  b          0x4008fc
/* 0040092c */  nop        
/* 00400930 */  addiu      $at, $zero, 0x66
/* 00400934 */  beq        $a2, $at, 0x400684
/* 00400938 */  slti       $at, $a2, 0x67
/* 0040093c */  beqz       $at, 0x400954
/* 00400940 */  addiu      $at, $zero, 0x57
/* 00400944 */  beq        $a2, $at, 0x4005d0
/* 00400948 */  lw         $t6, 0xb8($sp)
/* 0040094c */  b          0x4008fc
/* 00400950 */  nop        
/* 00400954 */  addiu      $at, $zero, 0x69
/* 00400958 */  beq        $a2, $at, 0x400884
/* 0040095c */  nop        
/* 00400960 */  b          0x4008fc
/* 00400964 */  nop        
/* 00400968 */  addiu      $at, $zero, 0x73
/* 0040096c */  beq        $a2, $at, 0x4004e8
/* 00400970 */  slti       $at, $a2, 0x74
/* 00400974 */  beqz       $at, 0x4009b0
/* 00400978 */  addiu      $at, $zero, 0x6e
/* 0040097c */  beq        $a2, $at, 0x40063c
/* 00400980 */  slti       $at, $a2, 0x6f
/* 00400984 */  beqz       $at, 0x40099c
/* 00400988 */  addiu      $at, $zero, 0x6d
/* 0040098c */  beq        $a2, $at, 0x40070c
/* 00400990 */  nop        
/* 00400994 */  b          0x4008fc
/* 00400998 */  nop        
/* 0040099c */  addiu      $at, $zero, 0x6f
/* 004009a0 */  beq        $a2, $at, 0x4004d0
/* 004009a4 */  nop        
/* 004009a8 */  b          0x4008fc
/* 004009ac */  nop        
/* 004009b0 */  addiu      $at, $zero, 0x76
/* 004009b4 */  beq        $a2, $at, 0x400840
/* 004009b8 */  slti       $at, $a2, 0x77
/* 004009bc */  beqz       $at, 0x4009d4
/* 004009c0 */  addiu      $at, $zero, 0x74
/* 004009c4 */  beq        $a2, $at, 0x400540
/* 004009c8 */  nop        
/* 004009cc */  b          0x4008fc
/* 004009d0 */  nop        
/* 004009d4 */  addiu      $at, $zero, 0x77
/* 004009d8 */  beq        $a2, $at, 0x400424
/* 004009dc */  nop        
/* 004009e0 */  b          0x4008fc
/* 004009e4 */  nop        
/* 004009e8 */  lw         $a0, 0x20d0($sp)
/* 004009ec */  lw         $a1, 0x20d4($sp)
/* 004009f0 */  lui        $a2, 0x1000
/* 004009f4 */  jal        0x40d3f0
/* 004009f8 */  addiu      $a2, $a2, 0x234
/* 004009fc */  addiu      $at, $zero, -1
/* 00400a00 */  bne        $v0, $at, 0x40041c
/* 00400a04 */  nop        
/* 00400a08 */  lw         $s0, 0x4c($sp)
/* 00400a0c */  lw         $s1, 0x48($sp)
/* 00400a10 */  lw         $s5, 0x44($sp)
/* 00400a14 */  lw         $s6, 0x40($sp)
/* 00400a18 */  lw         $s7, 0x3c($sp)
/* 00400a1c */  lw         $fp, 0x38($sp)
/* 00400a20 */  nop        
/* 00400a24 */  lw         $t8, 0xb8($sp)
/* 00400a28 */  nop        
/* 00400a2c */  bnez       $t8, 0x401168
/* 00400a30 */  lw         $t0, 0xb8($sp)
/* 00400a34 */  lw         $t9, 0xb4($sp)
/* 00400a38 */  nop        
/* 00400a3c */  beqz       $t9, 0x400a7c
/* 00400a40 */  lui        $a0, 0x1e
/* 00400a44 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400a48 */  nop        
/* 00400a4c */  lw         $t2, 0x104($t0)
/* 00400a50 */  nop        
/* 00400a54 */  bnez       $t2, 0x400a7c
/* 00400a58 */  lui        $a0, 0x1e
/* 00400a5c */  lui        $a1, 0x1000
/* 00400a60 */  addiu      $a1, $a1, 0x3cc
/* 00400a64 */  move       $a0, $s3
/* 00400a68 */  jal        0xf801150                                # fclose
/* 00400a6c */  move       $a2, $s4
/* 00400a70 */  jal        0x40d3c0
/* 00400a74 */  addiu      $a0, $zero, -1
/* 00400a78 */  lui        $a0, 0x1e
/* 00400a7c */  jal        0xf801208                                # free
/* 00400a80 */  ori        $a0, $a0, 0x8480
/* 00400a84 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400a88 */  nop        
/* 00400a8c */  sw         $v0, 0x108($t1)
/* 00400a90 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400a94 */  nop        
/* 00400a98 */  lw         $t5, 0x108($t3)
/* 00400a9c */  nop        
/* 00400aa0 */  bnez       $t5, 0x400ab0
/* 00400aa4 */  nop        
/* 00400aa8 */  jal        0x4092d4
/* 00400aac */  addiu      $a0, $gp, -0x7e40
/* 00400ab0 */  jal        0xf801208                                # free
/* 00400ab4 */  addiu      $a0, $zero, 0xc
/* 00400ab8 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400abc */  nop        
/* 00400ac0 */  sw         $v0, 0x10c($t6)
/* 00400ac4 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00400ac8 */  nop        
/* 00400acc */  lw         $t7, 0x10c($t4)
/* 00400ad0 */  nop        
/* 00400ad4 */  bnez       $t7, 0x400ae8
/* 00400ad8 */  lui        $a0, 4
/* 00400adc */  jal        0x4092d4
/* 00400ae0 */  addiu      $a0, $gp, -0x7e38
/* 00400ae4 */  lui        $a0, 4
/* 00400ae8 */  jal        0xf801208                                # free
/* 00400aec */  ori        $a0, $a0, 0x93e0
/* 00400af0 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400af4 */  nop        
/* 00400af8 */  sw         $v0, 0x114($t8)
/* 00400afc */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400b00 */  nop        
/* 00400b04 */  lw         $t0, 0x114($t9)
/* 00400b08 */  nop        
/* 00400b0c */  bnez       $t0, 0x400b20
/* 00400b10 */  lui        $a0, 0x49
/* 00400b14 */  jal        0x4092d4
/* 00400b18 */  addiu      $a0, $gp, -0x7e30
/* 00400b1c */  lui        $a0, 0x49
/* 00400b20 */  jal        0xf801208                                # free
/* 00400b24 */  ori        $a0, $a0, 0x3e00
/* 00400b28 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400b2c */  nop        
/* 00400b30 */  sw         $v0, 0x110($t2)
/* 00400b34 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400b38 */  nop        
/* 00400b3c */  lw         $t3, 0x110($t1)
/* 00400b40 */  nop        
/* 00400b44 */  bnez       $t3, 0x400b54
/* 00400b48 */  nop        
/* 00400b4c */  jal        0x4092d4
/* 00400b50 */  addiu      $a0, $gp, -0x7e28
/* 00400b54 */  jal        0xf801208                                # free
/* 00400b58 */  addiu      $a0, $zero, 0xe10
/* 00400b5c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00400b60 */  nop        
/* 00400b64 */  sw         $v0, 0x124($t5)
/* 00400b68 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400b6c */  nop        
/* 00400b70 */  lw         $t4, 0x124($t6)
/* 00400b74 */  nop        
/* 00400b78 */  bnez       $t4, 0x400b88
/* 00400b7c */  nop        
/* 00400b80 */  jal        0x4092d4
/* 00400b84 */  addiu      $a0, $gp, -0x7e20
/* 00400b88 */  jal        0xf801208                                # free
/* 00400b8c */  addiu      $a0, $zero, 0x140
/* 00400b90 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400b94 */  nop        
/* 00400b98 */  sw         $v0, 0x118($t7)
/* 00400b9c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400ba0 */  nop        
/* 00400ba4 */  lw         $t9, 0x118($t8)
/* 00400ba8 */  nop        
/* 00400bac */  bnez       $t9, 0x400bbc
/* 00400bb0 */  nop        
/* 00400bb4 */  jal        0x4092d4
/* 00400bb8 */  addiu      $a0, $gp, -0x7e18
/* 00400bbc */  jal        0xf801208                                # free
/* 00400bc0 */  addiu      $a0, $zero, 0xf0
/* 00400bc4 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400bc8 */  nop        
/* 00400bcc */  sw         $v0, 0x11c($t0)
/* 00400bd0 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400bd4 */  nop        
/* 00400bd8 */  lw         $t1, 0x11c($t2)
/* 00400bdc */  nop        
/* 00400be0 */  bnez       $t1, 0x400bf0
/* 00400be4 */  nop        
/* 00400be8 */  jal        0x4092d4
/* 00400bec */  addiu      $a0, $gp, -0x7e10
/* 00400bf0 */  jal        0xf801208                                # free
/* 00400bf4 */  addiu      $a0, $zero, 0xf0
/* 00400bf8 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400bfc */  nop        
/* 00400c00 */  sw         $v0, 0x120($t3)
/* 00400c04 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00400c08 */  nop        
/* 00400c0c */  lw         $t6, 0x120($t5)
/* 00400c10 */  nop        
/* 00400c14 */  bnez       $t6, 0x400c28
/* 00400c18 */  lui        $a0, 0x30
/* 00400c1c */  jal        0x4092d4
/* 00400c20 */  addiu      $a0, $gp, -0x7e08
/* 00400c24 */  lui        $a0, 0x30
/* 00400c28 */  jal        0xf801208                                # free
/* 00400c2c */  ori        $a0, $a0, 0xd400
/* 00400c30 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00400c34 */  nop        
/* 00400c38 */  sw         $v0, 0x128($t4)
/* 00400c3c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400c40 */  nop        
/* 00400c44 */  lw         $t8, 0x128($t7)
/* 00400c48 */  nop        
/* 00400c4c */  bnez       $t8, 0x400c60
/* 00400c50 */  lui        $a0, 0x18
/* 00400c54 */  jal        0x4092d4
/* 00400c58 */  addiu      $a0, $gp, -0x7e00
/* 00400c5c */  lui        $a0, 0x18
/* 00400c60 */  jal        0xf801208                                # free
/* 00400c64 */  ori        $a0, $a0, 0x6a00
/* 00400c68 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400c6c */  nop        
/* 00400c70 */  sw         $v0, 0x12c($t9)
/* 00400c74 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400c78 */  nop        
/* 00400c7c */  lw         $t2, 0x12c($t0)
/* 00400c80 */  nop        
/* 00400c84 */  bnez       $t2, 0x400c94
/* 00400c88 */  nop        
/* 00400c8c */  jal        0x4092d4
/* 00400c90 */  addiu      $a0, $gp, -0x7df8
/* 00400c94 */  jal        0xf801208                                # free
/* 00400c98 */  ori        $a0, $zero, 0xfa00
/* 00400c9c */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400ca0 */  nop        
/* 00400ca4 */  sw         $v0, 0x130($t1)
/* 00400ca8 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400cac */  nop        
/* 00400cb0 */  lw         $t5, 0x130($t3)
/* 00400cb4 */  nop        
/* 00400cb8 */  bnez       $t5, 0x400cc8
/* 00400cbc */  nop        
/* 00400cc0 */  jal        0x4092d4
/* 00400cc4 */  addiu      $a0, $gp, -0x7df0
/* 00400cc8 */  jal        0xf801208                                # free
/* 00400ccc */  addiu      $a0, $zero, 0x190
/* 00400cd0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400cd4 */  nop        
/* 00400cd8 */  sw         $v0, 0x138($t6)
/* 00400cdc */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00400ce0 */  nop        
/* 00400ce4 */  lw         $t7, 0x138($t4)
/* 00400ce8 */  nop        
/* 00400cec */  bnez       $t7, 0x400cfc
/* 00400cf0 */  nop        
/* 00400cf4 */  jal        0x4092d4
/* 00400cf8 */  addiu      $a0, $gp, -0x7de8
/* 00400cfc */  jal        0xf801208                                # free
/* 00400d00 */  addiu      $a0, $zero, 0x320
/* 00400d04 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400d08 */  nop        
/* 00400d0c */  sw         $v0, 0x13c($t8)
/* 00400d10 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400d14 */  nop        
/* 00400d18 */  lw         $t0, 0x13c($t9)
/* 00400d1c */  nop        
/* 00400d20 */  bnez       $t0, 0x400d30
/* 00400d24 */  nop        
/* 00400d28 */  jal        0x4092d4
/* 00400d2c */  addiu      $a0, $gp, -0x7de0
/* 00400d30 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400d34 */  nop        
/* 00400d38 */  lw         $t1, 0x104($t2)
/* 00400d3c */  nop        
/* 00400d40 */  beqz       $t1, 0x400d84
/* 00400d44 */  nop        
/* 00400d48 */  jal        0xf801208                                # free
/* 00400d4c */  addiu      $a0, $zero, 0x320
/* 00400d50 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400d54 */  nop        
/* 00400d58 */  sw         $v0, 0xf0($t3)
/* 00400d5c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00400d60 */  nop        
/* 00400d64 */  lw         $t6, 0xf0($t5)
/* 00400d68 */  nop        
/* 00400d6c */  bnez       $t6, 0x400d7c
/* 00400d70 */  nop        
/* 00400d74 */  jal        0x4092d4
/* 00400d78 */  addiu      $a0, $gp, -0x7dd8
/* 00400d7c */  jal        0x404580                                 # gfo_build_display_list
/* 00400d80 */  nop        
/* 00400d84 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00400d88 */  lw         $v1, 0x20d0($sp)
/* 00400d8c */  sw         $zero, 0x140($t4)
/* 00400d90 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400d94 */  nop        
/* 00400d98 */  sw         $zero, 0x144($t7)
/* 00400d9c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400da0 */  nop        
/* 00400da4 */  sw         $zero, 0x148($t8)
/* 00400da8 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400dac */  nop        
/* 00400db0 */  sw         $zero, 0x14c($t9)
/* 00400db4 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400db8 */  nop        
/* 00400dbc */  sw         $zero, 0x15c($t0)
/* 00400dc0 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400dc4 */  nop        
/* 00400dc8 */  sw         $zero, 0x150($t2)
/* 00400dcc */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400dd0 */  nop        
/* 00400dd4 */  sw         $zero, 0x154($t1)
/* 00400dd8 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400ddc */  nop        
/* 00400de0 */  sw         $zero, 0x158($t3)
/* 00400de4 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00400de8 */  nop        
/* 00400dec */  sw         $zero, 0x160($t5)
/* 00400df0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400df4 */  nop        
/* 00400df8 */  sw         $zero, 0x164($t6)
/* 00400dfc */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00400e00 */  nop        
/* 00400e04 */  sw         $zero, 0x168($t4)
/* 00400e08 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400e0c */  nop        
/* 00400e10 */  sw         $zero, 0x170($t7)
/* 00400e14 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400e18 */  nop        
/* 00400e1c */  sw         $zero, 0x174($t8)
/* 00400e20 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00400e24 */  nop        
/* 00400e28 */  sw         $zero, 0x178($t9)
/* 00400e2c */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00400e30 */  nop        
/* 00400e34 */  sw         $zero, 0x17c($t0)
/* 00400e38 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00400e3c */  nop        
/* 00400e40 */  sw         $zero, 0x180($t2)
/* 00400e44 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00400e48 */  nop        
/* 00400e4c */  sw         $zero, 0x184($t1)
/* 00400e50 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00400e54 */  nop        
/* 00400e58 */  sw         $zero, 0x188($t3)
/* 00400e5c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00400e60 */  nop        
/* 00400e64 */  sw         $zero, 0x18c($t5)
/* 00400e68 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400e6c */  nop        
/* 00400e70 */  sw         $zero, 0x190($t6)
/* 00400e74 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00400e78 */  nop        
/* 00400e7c */  sw         $zero, 0x194($t4)
/* 00400e80 */  lw         $t7, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 00400e84 */  nop        
/* 00400e88 */  subu       $v0, $v1, $t7
/* 00400e8c */  bnez       $v0, 0x400ecc
/* 00400e90 */  nop        
/* 00400e94 */  lui        $a1, 0x1000
/* 00400e98 */  addiu      $a1, $a1, 0x40c
/* 00400e9c */  move       $a0, $s3
/* 00400ea0 */  jal        0xf801150                                # fclose
/* 00400ea4 */  move       $a2, $s4
/* 00400ea8 */  lui        $a0, 0x1000
/* 00400eac */  jal        0x405590
/* 00400eb0 */  addiu      $a0, $a0, 0x3694
/* 00400eb4 */  bnez       $v0, 0x4010d4
/* 00400eb8 */  nop        
/* 00400ebc */  jal        0x40d3c0
/* 00400ec0 */  addiu      $a0, $zero, -1
/* 00400ec4 */  b          0x4010d4
/* 00400ec8 */  nop        
/* 00400ecc */  blez       $v0, 0x4010cc
/* 00400ed0 */  nop        
/* 00400ed4 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00400ed8 */  nop        
/* 00400edc */  sw         $v0, 0xd4($t8)
/* 00400ee0 */  lw         $t9, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 00400ee4 */  nop        
/* 00400ee8 */  slt        $at, $t9, $v1
/* 00400eec */  beqz       $at, 0x4010d4
/* 00400ef0 */  nop        
/* 00400ef4 */  sw         $s6, 0x40($sp)
/* 00400ef8 */  sw         $s7, 0x3c($sp)
/* 00400efc */  sw         $fp, 0x38($sp)
/* 00400f00 */  sw         $s5, 0x44($sp)
/* 00400f04 */  lui        $fp, 0x1000
/* 00400f08 */  lui        $s7, 0x1000
/* 00400f0c */  lui        $s6, 0x1000
/* 00400f10 */  sw         $s0, 0x4c($sp)
/* 00400f14 */  addiu      $s6, $s6, 0x42c
/* 00400f18 */  addiu      $s7, $s7, 0x450
/* 00400f1c */  addiu      $fp, $fp, 0x46c
/* 00400f20 */  addiu      $s5, $gp, -0x7dd0
/* 00400f24 */  sw         $s1, 0x48($sp)
/* 00400f28 */  lw         $t2, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 00400f2c */  lw         $t0, 0x20d4($sp)
/* 00400f30 */  sll        $t1, $t2, 2
/* 00400f34 */  addu       $t3, $t0, $t1
/* 00400f38 */  lw         $s0, ($t3)
/* 00400f3c */  addiu      $t5, $t2, 1
/* 00400f40 */  sw         $t5, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 00400f44 */  move       $a1, $s5
/* 00400f48 */  jal        0xf801130                                # fgets
/* 00400f4c */  move       $a0, $s0
/* 00400f50 */  bnez       $v0, 0x400fa8
/* 00400f54 */  move       $s1, $v0
/* 00400f58 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00400f5c */  nop        
/* 00400f60 */  lw         $t4, 0xd4($t6)
/* 00400f64 */  nop        
/* 00400f68 */  slti       $at, $t4, 2
/* 00400f6c */  bnez       $at, 0x400f94
/* 00400f70 */  move       $a0, $s7
/* 00400f74 */  move       $a0, $s3
/* 00400f78 */  move       $a1, $s6
/* 00400f7c */  move       $a2, $s4
/* 00400f80 */  jal        0xf801150                                # fclose
/* 00400f84 */  move       $a3, $s0
/* 00400f88 */  b          0x400fdc
/* 00400f8c */  nop        
/* 00400f90 */  move       $a0, $s7
/* 00400f94 */  move       $a1, $s4
/* 00400f98 */  jal        0x4092d4
/* 00400f9c */  move       $a2, $s0
/* 00400fa0 */  b          0x400fdc
/* 00400fa4 */  nop        
/* 00400fa8 */  move       $a0, $s3
/* 00400fac */  move       $a1, $fp
/* 00400fb0 */  move       $a2, $s4
/* 00400fb4 */  jal        0xf801150                                # fclose
/* 00400fb8 */  move       $a3, $s0
/* 00400fbc */  jal        0x405590
/* 00400fc0 */  move       $a0, $s1
/* 00400fc4 */  bnez       $v0, 0x400fd4
/* 00400fc8 */  nop        
/* 00400fcc */  jal        0x40d3c0
/* 00400fd0 */  addiu      $a0, $zero, -1
/* 00400fd4 */  jal        0xf801120                                # sscanf
/* 00400fd8 */  move       $a0, $s1
/* 00400fdc */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00400fe0 */  nop        
/* 00400fe4 */  lw         $t8, 0xc8($t7)
/* 00400fe8 */  nop        
/* 00400fec */  beqz       $t8, 0x40108c
/* 00400ff0 */  nop        
/* 00400ff4 */  lw         $t9, 0x140($t7)
/* 00400ff8 */  nop        
/* 00400ffc */  sw         $t9, 0x178($t7)
/* 00401000 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00401004 */  nop        
/* 00401008 */  lw         $t1, 0x148($t0)
/* 0040100c */  nop        
/* 00401010 */  sw         $t1, 0x17c($t0)
/* 00401014 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00401018 */  nop        
/* 0040101c */  lw         $t2, 0x14c($t3)
/* 00401020 */  nop        
/* 00401024 */  sw         $t2, 0x180($t3)
/* 00401028 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 0040102c */  nop        
/* 00401030 */  lw         $t6, 0x15c($t5)
/* 00401034 */  nop        
/* 00401038 */  sw         $t6, 0x184($t5)
/* 0040103c */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00401040 */  nop        
/* 00401044 */  lw         $t8, 0x160($t4)
/* 00401048 */  nop        
/* 0040104c */  sw         $t8, 0x188($t4)
/* 00401050 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00401054 */  nop        
/* 00401058 */  lw         $t7, 0x164($t9)
/* 0040105c */  nop        
/* 00401060 */  sw         $t7, 0x18c($t9)
/* 00401064 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00401068 */  nop        
/* 0040106c */  lw         $t0, 0x168($t1)
/* 00401070 */  nop        
/* 00401074 */  sw         $t0, 0x190($t1)
/* 00401078 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 0040107c */  nop        
/* 00401080 */  lw         $t3, 0x170($t2)
/* 00401084 */  nop        
/* 00401088 */  sw         $t3, 0x194($t2)
/* 0040108c */  lw         $t6, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 00401090 */  lw         $t5, 0x20d0($sp)
/* 00401094 */  nop        
/* 00401098 */  slt        $at, $t6, $t5
/* 0040109c */  beqz       $at, 0x4010b0
/* 004010a0 */  lw         $s0, 0x4c($sp)
/* 004010a4 */  b          0x400f28
/* 004010a8 */  move       $v1, $t5
/* 004010ac */  lw         $s0, 0x4c($sp)
/* 004010b0 */  lw         $s1, 0x48($sp)
/* 004010b4 */  lw         $s5, 0x44($sp)
/* 004010b8 */  lw         $s6, 0x40($sp)
/* 004010bc */  lw         $s7, 0x3c($sp)
/* 004010c0 */  lw         $fp, 0x38($sp)
/* 004010c4 */  b          0x4010d4
/* 004010c8 */  nop        
/* 004010cc */  jal        0x400270                                 # exit_handler
/* 004010d0 */  nop        
/* 004010d4 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004010d8 */  nop        
/* 004010dc */  lw         $a2, 0x160($t8)
/* 004010e0 */  nop        
/* 004010e4 */  blez       $a2, 0x4010fc
/* 004010e8 */  nop        
/* 004010ec */  lui        $a0, 0x1000
/* 004010f0 */  addiu      $a0, $a0, 0x484
/* 004010f4 */  jal        0xf801250                                # getopt
/* 004010f8 */  move       $a1, $s4
/* 004010fc */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00401100 */  nop        
/* 00401104 */  lw         $a2, 0x164($t4)
/* 00401108 */  nop        
/* 0040110c */  blez       $a2, 0x401124
/* 00401110 */  nop        
/* 00401114 */  lui        $a0, 0x1000
/* 00401118 */  addiu      $a0, $a0, 0x4a4
/* 0040111c */  jal        0xf801250                                # getopt
/* 00401120 */  move       $a1, $s4
/* 00401124 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00401128 */  nop        
/* 0040112c */  lw         $a2, 0x168($t7)
/* 00401130 */  nop        
/* 00401134 */  blez       $a2, 0x40114c
/* 00401138 */  nop        
/* 0040113c */  lui        $a0, 0x1000
/* 00401140 */  addiu      $a0, $a0, 0x4c0
/* 00401144 */  jal        0xf801250                                # getopt
/* 00401148 */  move       $a1, $s4
/* 0040114c */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00401150 */  lui        $a0, 0x1000
/* 00401154 */  lw         $a2, 0x174($t9)
/* 00401158 */  addiu      $a0, $a0, 0x4e0
/* 0040115c */  jal        0xf801250                                # getopt
/* 00401160 */  move       $a1, $s4
/* 00401164 */  lw         $t0, 0xb8($sp)
/* 00401168 */  nop        
/* 0040116c */  beqz       $t0, 0x40124c
/* 00401170 */  nop        
/* 00401174 */  lui        $a1, 0x1000
/* 00401178 */  sw         $s0, 0x4c($sp)
/* 0040117c */  sw         $s1, 0x48($sp)
/* 00401180 */  addiu      $a1, $a1, 0x500
/* 00401184 */  jal        0xf801150                                # fclose
/* 00401188 */  move       $a0, $s3
/* 0040118c */  lw         $a0, 0xb0($sp)
/* 00401190 */  jal        0xf801130                                # fgets
/* 00401194 */  addiu      $a1, $gp, -0x7dcc
/* 00401198 */  bnez       $v0, 0x4011c0
/* 0040119c */  move       $s0, $v0
/* 004011a0 */  lui        $a1, 0x1000
/* 004011a4 */  lw         $a3, 0xb0($sp)
/* 004011a8 */  addiu      $a1, $a1, 0x51c
/* 004011ac */  move       $a0, $s3
/* 004011b0 */  jal        0xf801150                                # fclose
/* 004011b4 */  move       $a2, $s4
/* 004011b8 */  jal        0x40d3c0
/* 004011bc */  addiu      $a0, $zero, -1
/* 004011c0 */  move       $a0, $s0
/* 004011c4 */  jal        0x404e78                                 # gfo_read_file
/* 004011c8 */  addiu      $a1, $sp, 0x64
/* 004011cc */  move       $s1, $v0
/* 004011d0 */  move       $a0, $s3
/* 004011d4 */  jal        0xf801150                                # fclose
/* 004011d8 */  addiu      $a1, $gp, -0x7dc8
/* 004011dc */  jal        0xf801120                                # sscanf
/* 004011e0 */  move       $a0, $s0
/* 004011e4 */  bnez       $s1, 0x401208
/* 004011e8 */  nop        
/* 004011ec */  lui        $a1, 0x1000
/* 004011f0 */  addiu      $a1, $a1, 0x53c
/* 004011f4 */  move       $a0, $s3
/* 004011f8 */  jal        0xf801150                                # fclose
/* 004011fc */  move       $a2, $s4
/* 00401200 */  jal        0x40d3c0
/* 00401204 */  addiu      $a0, $zero, -1
/* 00401208 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 0040120c */  nop        
/* 00401210 */  sw         $s1, 0x13c($t1)
/* 00401214 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00401218 */  lw         $t3, 0x64($sp)
/* 0040121c */  nop        
/* 00401220 */  sw         $t3, 0xd4($t2)
/* 00401224 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401228 */  nop        
/* 0040122c */  lw         $t5, 0xc8($t6)
/* 00401230 */  nop        
/* 00401234 */  bnez       $t5, 0x401244
/* 00401238 */  lw         $s0, 0x4c($sp)
/* 0040123c */  sw         $s2, 0x174($t6)
/* 00401240 */  lw         $s0, 0x4c($sp)
/* 00401244 */  lw         $s1, 0x48($sp)
/* 00401248 */  nop        
/* 0040124c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00401250 */  nop        
/* 00401254 */  lw         $a1, 0x104($t8)
/* 00401258 */  nop        
/* 0040125c */  beqz       $a1, 0x40132c
/* 00401260 */  lw         $t9, 0xb4($sp)
/* 00401264 */  lw         $t4, 0xc8($t8)
/* 00401268 */  nop        
/* 0040126c */  beqz       $t4, 0x4012f8
/* 00401270 */  nop        
/* 00401274 */  sw         $s1, 0x48($sp)
/* 00401278 */  lw         $t7, 0xd4($t8)
/* 0040127c */  move       $s1, $zero
/* 00401280 */  blez       $t7, 0x4012ec
/* 00401284 */  nop        
/* 00401288 */  sw         $s0, 0x4c($sp)
/* 0040128c */  move       $s0, $zero
/* 00401290 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00401294 */  nop        
/* 00401298 */  lw         $t0, 0x13c($t9)
/* 0040129c */  lw         $a1, 0x104($t9)
/* 004012a0 */  addu       $t1, $t0, $s0
/* 004012a4 */  lw         $a0, ($t1)
/* 004012a8 */  jal        0x404668                                 # gfo_load_file
/* 004012ac */  nop        
/* 004012b0 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 004012b4 */  addiu      $s1, $s1, 1
/* 004012b8 */  lw         $t2, 0xf0($t3)
/* 004012bc */  nop        
/* 004012c0 */  addu       $t5, $t2, $s0
/* 004012c4 */  sw         $v0, ($t5)
/* 004012c8 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 004012cc */  addiu      $s0, $s0, 4
/* 004012d0 */  lw         $t4, 0xd4($t6)
/* 004012d4 */  nop        
/* 004012d8 */  slt        $at, $s1, $t4
/* 004012dc */  bnez       $at, 0x401290
/* 004012e0 */  nop        
/* 004012e4 */  lw         $s0, 0x4c($sp)
/* 004012e8 */  nop        
/* 004012ec */  lw         $s1, 0x48($sp)
/* 004012f0 */  b          0x40132c
/* 004012f4 */  lw         $t9, 0xb4($sp)
/* 004012f8 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004012fc */  nop        
/* 00401300 */  lw         $t7, 0x13c($t8)
/* 00401304 */  nop        
/* 00401308 */  lw         $a0, ($t7)
/* 0040130c */  jal        0x404668                                 # gfo_load_file
/* 00401310 */  nop        
/* 00401314 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00401318 */  nop        
/* 0040131c */  lw         $t1, 0xf0($t0)
/* 00401320 */  nop        
/* 00401324 */  sw         $v0, ($t1)
/* 00401328 */  lw         $t9, 0xb4($sp)
/* 0040132c */  nop        
/* 00401330 */  beqz       $t9, 0x401408
/* 00401334 */  lw         $t4, 0x20c0($sp)
/* 00401338 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 0040133c */  sw         $s0, 0x4c($sp)
/* 00401340 */  sw         $s1, 0x48($sp)
/* 00401344 */  lw         $t2, 0xc8($t3)
/* 00401348 */  lw         $a1, 0x104($t3)
/* 0040134c */  beqz       $t2, 0x401364
/* 00401350 */  addiu      $s2, $zero, 1
/* 00401354 */  lw         $s2, 0xd4($t3)
/* 00401358 */  b          0x401364
/* 0040135c */  nop        
/* 00401360 */  addiu      $s2, $zero, 1
/* 00401364 */  beqz       $a1, 0x401380
/* 00401368 */  nop        
/* 0040136c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00401370 */  nop        
/* 00401374 */  lw         $s1, 0xf0($t5)
/* 00401378 */  b          0x401390
/* 0040137c */  nop        
/* 00401380 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401384 */  nop        
/* 00401388 */  lw         $s1, 0x13c($t6)
/* 0040138c */  nop        
/* 00401390 */  lui        $a1, 0x1000
/* 00401394 */  addiu      $a1, $a1, 0x55c
/* 00401398 */  jal        0xf801150                                # fclose
/* 0040139c */  move       $a0, $s3
/* 004013a0 */  lw         $a0, 0xb0($sp)
/* 004013a4 */  jal        0xf801130                                # fgets
/* 004013a8 */  addiu      $a1, $gp, -0x7dc0
/* 004013ac */  bnez       $v0, 0x4013d4
/* 004013b0 */  move       $s0, $v0
/* 004013b4 */  lui        $a1, 0x1000
/* 004013b8 */  lw         $a3, 0xb0($sp)
/* 004013bc */  addiu      $a1, $a1, 0x578
/* 004013c0 */  move       $a0, $s3
/* 004013c4 */  jal        0xf801150                                # fclose
/* 004013c8 */  move       $a2, $s4
/* 004013cc */  jal        0x40d3c0
/* 004013d0 */  addiu      $a0, $zero, -1
/* 004013d4 */  move       $a0, $s1
/* 004013d8 */  move       $a1, $s2
/* 004013dc */  jal        0x404b60                                 # bin_read_model
/* 004013e0 */  move       $a2, $s0
/* 004013e4 */  jal        0xf801120                                # sscanf
/* 004013e8 */  move       $a0, $s0
/* 004013ec */  move       $a0, $s3
/* 004013f0 */  jal        0xf801150                                # fclose
/* 004013f4 */  addiu      $a1, $gp, -0x7dbc
/* 004013f8 */  lw         $s0, 0x4c($sp)
/* 004013fc */  lw         $s1, 0x48($sp)
/* 00401400 */  nop        
/* 00401404 */  lw         $t4, 0x20c0($sp)
/* 00401408 */  nop        
/* 0040140c */  beqz       $t4, 0x401420
/* 00401410 */  lw         $t8, 0x20d4($sp)
/* 00401414 */  b          0x4014ec
/* 00401418 */  move       $v0, $zero
/* 0040141c */  lw         $t8, 0x20d4($sp)
/* 00401420 */  nop        
/* 00401424 */  lw         $a0, ($t8)
/* 00401428 */  jal        0x401678                                 # draw_entity
/* 0040142c */  nop        
/* 00401430 */  jal        0x408200
/* 00401434 */  nop        
/* 00401438 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 0040143c */  nop        
/* 00401440 */  lw         $t0, 0xbc($t7)
/* 00401444 */  nop        
/* 00401448 */  beqz       $t0, 0x4014d0
/* 0040144c */  nop        
/* 00401450 */  jal        0x403684                                 # setup_menu
/* 00401454 */  nop        
/* 00401458 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 0040145c */  nop        
/* 00401460 */  lw         $a0, 0xc0($t1)
/* 00401464 */  jal        0x40381c                                 # gfo_new_scope
/* 00401468 */  nop        
/* 0040146c */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00401470 */  nop        
/* 00401474 */  sw         $v0, 0xc4($t9)
/* 00401478 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 0040147c */  nop        
/* 00401480 */  lw         $t3, 0xc4($t2)
/* 00401484 */  nop        
/* 00401488 */  bnez       $t3, 0x4014b0
/* 0040148c */  nop        
/* 00401490 */  lui        $a1, 0x1000
/* 00401494 */  lw         $a3, 0xc0($t2)
/* 00401498 */  addiu      $a1, $a1, 0x598
/* 0040149c */  move       $a0, $s3
/* 004014a0 */  jal        0xf801150                                # fclose
/* 004014a4 */  move       $a2, $s4
/* 004014a8 */  jal        0x40d3c0
/* 004014ac */  addiu      $a0, $zero, -1
/* 004014b0 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 004014b4 */  lui        $a1, 0x1000
/* 004014b8 */  lw         $a2, 0xc0($t5)
/* 004014bc */  addiu      $a1, $a1, 0x5b8
/* 004014c0 */  jal        0xf801150                                # fclose
/* 004014c4 */  move       $a0, $s3
/* 004014c8 */  b          0x4014d8
/* 004014cc */  nop        
/* 004014d0 */  jal        0x403440                                 # setup_materials
/* 004014d4 */  nop        
/* 004014d8 */  jal        0x402098                                 # event_loop_and_render
/* 004014dc */  nop        
/* 004014e0 */  jal        0x401a00                                 # frame_advance_check
/* 004014e4 */  nop        
/* 004014e8 */  move       $v0, $zero
/* 004014ec */  lw         $ra, 0x34($sp)
/* 004014f0 */  lw         $s2, 0x28($sp)
/* 004014f4 */  lw         $s3, 0x2c($sp)
/* 004014f8 */  lw         $s4, 0x30($sp)
/* 004014fc */  jr         $ra
/* 00401500 */  addiu      $sp, $sp, 0x20d0

# === draw_display_list ===
glabel draw_display_list
/* 00401504 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401508 */  addiu      $sp, $sp, -0x28
/* 0040150c */  sw         $ra, 0x14($sp)
/* 00401510 */  lw         $v0, 0xc8($t6)
/* 00401514 */  nop        
/* 00401518 */  bnez       $v0, 0x40159c
/* 0040151c */  nop        
/* 00401520 */  lw         $t7, 0x104($t6)
/* 00401524 */  nop        
/* 00401528 */  bnez       $t7, 0x40159c
/* 0040152c */  nop        
/* 00401530 */  sw         $s1, 0x1c($sp)
/* 00401534 */  lw         $t8, 0x174($t6)
/* 00401538 */  move       $s1, $zero
/* 0040153c */  blez       $t8, 0x401594
/* 00401540 */  nop        
/* 00401544 */  sw         $s0, 0x18($sp)
/* 00401548 */  move       $s0, $zero
/* 0040154c */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00401550 */  nop        
/* 00401554 */  lw         $t0, 0x13c($t9)
/* 00401558 */  nop        
/* 0040155c */  addu       $t1, $t0, $s0
/* 00401560 */  lw         $a0, ($t1)
/* 00401564 */  jal        0x4082e8
/* 00401568 */  nop        
/* 0040156c */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00401570 */  addiu      $s1, $s1, 1
/* 00401574 */  lw         $t3, 0x174($t2)
/* 00401578 */  addiu      $s0, $s0, 4
/* 0040157c */  slt        $at, $s1, $t3
/* 00401580 */  bnez       $at, 0x40154c
/* 00401584 */  nop        
/* 00401588 */  lw         $v0, 0xc8($t2)
/* 0040158c */  lw         $s0, 0x18($sp)
/* 00401590 */  nop        
/* 00401594 */  lw         $s1, 0x1c($sp)
/* 00401598 */  nop        
/* 0040159c */  bnez       $v0, 0x4015e0
/* 004015a0 */  nop        
/* 004015a4 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 004015a8 */  nop        
/* 004015ac */  lw         $t5, 0x104($t4)
/* 004015b0 */  nop        
/* 004015b4 */  beqz       $t5, 0x4015e0
/* 004015b8 */  nop        
/* 004015bc */  lw         $t7, 0xf0($t4)
/* 004015c0 */  nop        
/* 004015c4 */  lw         $a0, ($t7)
/* 004015c8 */  jal        0x4082e8
/* 004015cc */  nop        
/* 004015d0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 004015d4 */  nop        
/* 004015d8 */  lw         $v0, 0xc8($t6)
/* 004015dc */  nop        
/* 004015e0 */  beqz       $v0, 0x40162c
/* 004015e4 */  nop        
/* 004015e8 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004015ec */  nop        
/* 004015f0 */  lw         $t9, 0x104($t8)
/* 004015f4 */  nop        
/* 004015f8 */  bnez       $t9, 0x40162c
/* 004015fc */  nop        
/* 00401600 */  lw         $t1, 0xd8($t8)
/* 00401604 */  lw         $t0, 0x13c($t8)
/* 00401608 */  sll        $t3, $t1, 2
/* 0040160c */  addu       $t2, $t0, $t3
/* 00401610 */  lw         $a0, ($t2)
/* 00401614 */  jal        0x4082e8
/* 00401618 */  nop        
/* 0040161c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00401620 */  nop        
/* 00401624 */  lw         $v0, 0xc8($t5)
/* 00401628 */  nop        
/* 0040162c */  beqz       $v0, 0x40166c
/* 00401630 */  lw         $ra, 0x14($sp)
/* 00401634 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00401638 */  nop        
/* 0040163c */  lw         $t7, 0x104($t4)
/* 00401640 */  nop        
/* 00401644 */  beqz       $t7, 0x40166c
/* 00401648 */  lw         $ra, 0x14($sp)
/* 0040164c */  lw         $t9, 0xd8($t4)
/* 00401650 */  lw         $t6, 0xf0($t4)
/* 00401654 */  sll        $t8, $t9, 2
/* 00401658 */  addu       $t1, $t6, $t8
/* 0040165c */  lw         $a0, ($t1)
/* 00401660 */  jal        0x4082e8
/* 00401664 */  nop        
/* 00401668 */  lw         $ra, 0x14($sp)
/* 0040166c */  addiu      $sp, $sp, 0x28
/* 00401670 */  jr         $ra
/* 00401674 */  nop        

# === draw_entity ===
glabel draw_entity
/* 00401678 */  addiu      $sp, $sp, -0x18
/* 0040167c */  mtc1       $zero, $f4
/* 00401680 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401684 */  lwc1       $f0, -0x7edc($gp)                        # .lit4: 0.5
/* 00401688 */  sw         $ra, 0x14($sp)
/* 0040168c */  sw         $a0, 0x18($sp)
/* 00401690 */  swc1       $f4, 0x24($t6)
/* 00401694 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00401698 */  mtc1       $zero, $f6
/* 0040169c */  nop        
/* 004016a0 */  swc1       $f6, 0x28($t7)
/* 004016a4 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004016a8 */  lwc1       $f8, -0x7ee0($gp)                        # .lit4: 1
/* 004016ac */  nop        
/* 004016b0 */  swc1       $f8, 0x30($t8)
/* 004016b4 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 004016b8 */  nop        
/* 004016bc */  swc1       $f0, 0x10($t9)
/* 004016c0 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 004016c4 */  nop        
/* 004016c8 */  swc1       $f0, 0x14($t0)
/* 004016cc */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 004016d0 */  nop        
/* 004016d4 */  sw         $zero, 0x18($t1)
/* 004016d8 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 004016dc */  nop        
/* 004016e0 */  sw         $zero, 0x1c($t2)
/* 004016e4 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 004016e8 */  nop        
/* 004016ec */  sw         $zero, 0x2c($t3)
/* 004016f0 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 004016f4 */  nop        
/* 004016f8 */  lw         $t5, 0x68($t4)
/* 004016fc */  nop        
/* 00401700 */  beqz       $t5, 0x40171c
/* 00401704 */  lw         $a0, 0x18($sp)
/* 00401708 */  lw         $a0, ($t4)
/* 0040170c */  lw         $a1, 4($t4)
/* 00401710 */  jal        0xf401400                                # getcolor
/* 00401714 */  nop        
/* 00401718 */  lw         $a0, 0x18($sp)
/* 0040171c */  jal        0xf801330                                # write
/* 00401720 */  addiu      $a1, $zero, 0x2f
/* 00401724 */  beqz       $v0, 0x401738
/* 00401728 */  lw         $a0, 0x18($sp)
/* 0040172c */  b          0x40173c
/* 00401730 */  addiu      $a0, $v0, 1
/* 00401734 */  lw         $a0, 0x18($sp)
/* 00401738 */  nop        
/* 0040173c */  jal        0xf401458                                # winposition
/* 00401740 */  nop        
/* 00401744 */  lw         $v1, -0x7e98($gp)                        # view_state_ptr
/* 00401748 */  nop        
/* 0040174c */  addiu      $a0, $v1, 8
/* 00401750 */  jal        0xf401440                                # getorigin
/* 00401754 */  addiu      $a1, $v1, 0xc
/* 00401758 */  lw         $v1, -0x7e98($gp)                        # view_state_ptr
/* 0040175c */  nop        
/* 00401760 */  move       $a0, $v1
/* 00401764 */  jal        0xf401438                                # getsize
/* 00401768 */  addiu      $a1, $v1, 4
/* 0040176c */  jal        0xf401220                                # qenter
/* 00401770 */  nop        
/* 00401774 */  jal        0xf401070                                # winclose
/* 00401778 */  nop        
/* 0040177c */  jal        0xf401098                                # winopen
/* 00401780 */  nop        
/* 00401784 */  jal        0xf401128                                # tie
/* 00401788 */  nop        
/* 0040178c */  slti       $at, $v0, 0xc
/* 00401790 */  beqz       $at, 0x4017e4
/* 00401794 */  nop        
/* 00401798 */  jal        0xf4016b0                                # makeobj
/* 0040179c */  addiu      $a0, $zero, 6
/* 004017a0 */  addiu      $at, $zero, 3
/* 004017a4 */  beq        $v0, $at, 0x4017e0
/* 004017a8 */  addiu      $t6, $zero, 1
/* 004017ac */  lui        $a0, 0x1000
/* 004017b0 */  lui        $a1, 0x1000
/* 004017b4 */  lw         $a2, 0x18($sp)
/* 004017b8 */  addiu      $a1, $a1, 0x5cc
/* 004017bc */  jal        0xf801150                                # fclose
/* 004017c0 */  addiu      $a0, $a0, 0x36b4
/* 004017c4 */  jal        0xf401290                                # getdisplaymode
/* 004017c8 */  nop        
/* 004017cc */  jal        0x40d3c0
/* 004017d0 */  addiu      $a0, $zero, 1
/* 004017d4 */  b          0x4017e4
/* 004017d8 */  nop        
/* 004017dc */  addiu      $t6, $zero, 1
/* 004017e0 */  sw         $t6, -0x7e88($gp)                        # .sdata @ 0x10003ee8
/* 004017e4 */  jal        0xf402098                                # color
/* 004017e8 */  move       $a0, $zero
/* 004017ec */  jal        0xf402120                                # gconfig
/* 004017f0 */  nop        
/* 004017f4 */  jal        0xf402288                                # swapbuffers
/* 004017f8 */  nop        
/* 004017fc */  jal        0xf402098                                # color
/* 00401800 */  move       $a0, $zero
/* 00401804 */  jal        0xf402120                                # gconfig
/* 00401808 */  nop        
/* 0040180c */  jal        0xf402508                                # zbuffer
/* 00401810 */  addiu      $a0, $zero, 1
/* 00401814 */  lui        $a0, 0x7f
/* 00401818 */  ori        $a0, $a0, 0xffff
/* 0040181c */  jal        0xf402ee8                                # lrectwrite
/* 00401820 */  addiu      $a1, $zero, 0x2000
/* 00401824 */  jal        0xf401618                                # shademodel
/* 00401828 */  addiu      $a0, $zero, 6
/* 0040182c */  jal        0xf402518                                # backface
/* 00401830 */  nop        
/* 00401834 */  jal        0xf401588                                # doublebuffer
/* 00401838 */  addiu      $a0, $zero, 2
/* 0040183c */  jal        0xf401098                                # winopen
/* 00401840 */  nop        
/* 00401844 */  jal        0xf401570                                # mmode
/* 00401848 */  addiu      $a0, $zero, 0x40
/* 0040184c */  move       $a0, $zero
/* 00401850 */  move       $a1, $zero
/* 00401854 */  move       $a2, $zero
/* 00401858 */  jal        0xf4011a8                                # winset
/* 0040185c */  move       $a3, $zero
/* 00401860 */  addiu      $a0, $zero, 1
/* 00401864 */  move       $a1, $zero
/* 00401868 */  addiu      $a2, $zero, 0xff
/* 0040186c */  jal        0xf4011a8                                # winset
/* 00401870 */  addiu      $a3, $zero, 0xff
/* 00401874 */  jal        0xf401fe0                                # gconfig
/* 00401878 */  move       $a0, $zero
/* 0040187c */  jal        0xf402120                                # gconfig
/* 00401880 */  nop        
/* 00401884 */  jal        0xf401570                                # mmode
/* 00401888 */  addiu      $a0, $zero, 0x10
/* 0040188c */  jal        0xf4012f0                                # getgdesc
/* 00401890 */  addiu      $a0, $zero, 0x67
/* 00401894 */  jal        0xf4012f0                                # getgdesc
/* 00401898 */  addiu      $a0, $zero, 0x66
/* 0040189c */  jal        0xf4012f0                                # getgdesc
/* 004018a0 */  addiu      $a0, $zero, 0x65
/* 004018a4 */  jal        0xf4012f0                                # getgdesc
/* 004018a8 */  addiu      $a0, $zero, 7
/* 004018ac */  jal        0xf4012f0                                # getgdesc
/* 004018b0 */  addiu      $a0, $zero, 0x53
/* 004018b4 */  jal        0xf4012f0                                # getgdesc
/* 004018b8 */  addiu      $a0, $zero, 0x21c
/* 004018bc */  jal        0xf4012f0                                # getgdesc
/* 004018c0 */  addiu      $a0, $zero, 0x19
/* 004018c4 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004018c8 */  nop        
/* 004018cc */  lw         $t8, 0x90($t7)
/* 004018d0 */  nop        
/* 004018d4 */  beqz       $t8, 0x4018e4
/* 004018d8 */  nop        
/* 004018dc */  jal        0xf4012f0                                # getgdesc
/* 004018e0 */  addiu      $a0, $zero, 0x1d
/* 004018e4 */  jal        0xf4012f0                                # getgdesc
/* 004018e8 */  addiu      $a0, $zero, 0x28
/* 004018ec */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 004018f0 */  nop        
/* 004018f4 */  lw         $t0, 0xc8($t9)
/* 004018f8 */  nop        
/* 004018fc */  beqz       $t0, 0x40190c
/* 00401900 */  nop        
/* 00401904 */  jal        0xf4012f0                                # getgdesc
/* 00401908 */  addiu      $a0, $zero, 6
/* 0040190c */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00401910 */  nop        
/* 00401914 */  lw         $t2, 0x48($t1)
/* 00401918 */  nop        
/* 0040191c */  beqz       $t2, 0x40195c
/* 00401920 */  nop        
/* 00401924 */  jal        0xf4012f0                                # getgdesc
/* 00401928 */  addiu      $a0, $zero, 0xb
/* 0040192c */  jal        0xf4012f0                                # getgdesc
/* 00401930 */  addiu      $a0, $zero, 0xc
/* 00401934 */  jal        0xf4012f0                                # getgdesc
/* 00401938 */  addiu      $a0, $zero, 0xa
/* 0040193c */  jal        0xf4012f0                                # getgdesc
/* 00401940 */  addiu      $a0, $zero, 0x10
/* 00401944 */  jal        0xf4012f0                                # getgdesc
/* 00401948 */  addiu      $a0, $zero, 0x15
/* 0040194c */  jal        0xf4012f0                                # getgdesc
/* 00401950 */  addiu      $a0, $zero, 0x20
/* 00401954 */  jal        0xf4012f0                                # getgdesc
/* 00401958 */  addiu      $a0, $zero, 0x14
/* 0040195c */  lui        $a0, 0x1000
/* 00401960 */  jal        0xf4015a8                                # RGBmode
/* 00401964 */  addiu      $a0, $a0, 0x254
/* 00401968 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 0040196c */  addiu      $a0, $zero, 1
/* 00401970 */  jal        0xf402578                                # depthcue
/* 00401974 */  sw         $v0, 0x64($t3)
/* 00401978 */  cfc1       $t5, $31
/* 0040197c */  cfc1       $t5, $31
/* 00401980 */  lwc1       $f11, -0x7ff0($gp)                       # .lit8: 600
/* 00401984 */  lwc1       $f10, -0x7fec($gp)                       # .lit8 @ 0x10003d84
/* 00401988 */  ori        $at, $t5, 3
/* 0040198c */  xori       $at, $at, 2
/* 00401990 */  ctc1       $at, $31
/* 00401994 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00401998 */  cvt.w.d    $f16, $f10
/* 0040199c */  lw         $a1, 0x6c($t4)
/* 004019a0 */  mfc1       $a0, $f16
/* 004019a4 */  ctc1       $t5, $31
/* 004019a8 */  lui        $a2, 0x3e80
/* 004019ac */  jal        0xf402fa0                                # perspective
/* 004019b0 */  lui        $a3, 0x4170
/* 004019b4 */  jal        0xf402578                                # depthcue
/* 004019b8 */  addiu      $a0, $zero, 2
/* 004019bc */  lui        $a0, 0x1000
/* 004019c0 */  jal        0xf402190                                # font
/* 004019c4 */  addiu      $a0, $a0, 0x278
/* 004019c8 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 004019cc */  nop        
/* 004019d0 */  lw         $t7, 0x48($t6)
/* 004019d4 */  nop        
/* 004019d8 */  bnez       $t7, 0x4019f4
/* 004019dc */  lw         $ra, 0x14($sp)
/* 004019e0 */  mtc1       $zero, $f12
/* 004019e4 */  mtc1       $zero, $f14
/* 004019e8 */  jal        0xf402298                                # translate
/* 004019ec */  lui        $a2, 0xc080
/* 004019f0 */  lw         $ra, 0x14($sp)
/* 004019f4 */  addiu      $sp, $sp, 0x18
/* 004019f8 */  jr         $ra
/* 004019fc */  nop        

# === frame_advance_check ===
glabel frame_advance_check
/* 00401a00 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401a04 */  addiu      $sp, $sp, -0x18
/* 00401a08 */  sw         $ra, 0x14($sp)
/* 00401a0c */  lw         $a0, 0x64($t6)
/* 00401a10 */  jal        0xf401508                                # defpup
/* 00401a14 */  nop        
/* 00401a18 */  lw         $ra, 0x14($sp)
/* 00401a1c */  addiu      $sp, $sp, 0x18
/* 00401a20 */  jr         $ra
/* 00401a24 */  nop        

# === save_frame ===
glabel save_frame
/* 00401a28 */  addiu      $sp, $sp, -0x38
/* 00401a2c */  bnez       $a0, 0x401a44
/* 00401a30 */  sw         $ra, 0x14($sp)
/* 00401a34 */  jal        0x40d810
/* 00401a38 */  addiu      $a0, $sp, 0x28
/* 00401a3c */  b          0x401b78
/* 00401a40 */  sw         $v0, -0x7b70($gp)                        # .sbss @ 0x10004200
/* 00401a44 */  addiu      $at, $zero, 0x64
/* 00401a48 */  div        $zero, $a0, $at
/* 00401a4c */  mfhi       $t6
/* 00401a50 */  bnez       $t6, 0x401b7c
/* 00401a54 */  lw         $ra, 0x14($sp)
/* 00401a58 */  jal        0x40d810
/* 00401a5c */  addiu      $a0, $sp, 0x28
/* 00401a60 */  lw         $t7, -0x7b70($gp)                        # .sbss @ 0x10004200
/* 00401a64 */  lwc1       $f3, -0x7fe8($gp)                        # .lit8: 100
/* 00401a68 */  subu       $t8, $v0, $t7
/* 00401a6c */  mtc1       $t8, $f4
/* 00401a70 */  lwc1       $f2, -0x7fe4($gp)                        # .lit8 @ 0x10003d8c
/* 00401a74 */  cvt.d.w    $f6, $f4
/* 00401a78 */  lui        $a0, 0x1000
/* 00401a7c */  sw         $v0, 0x24($sp)
/* 00401a80 */  div.d      $f0, $f6, $f2
/* 00401a84 */  addiu      $a0, $a0, 0x5ec
/* 00401a88 */  div.d      $f8, $f2, $f0
/* 00401a8c */  mov.d      $f12, $f0
/* 00401a90 */  swc1       $f12, 0x20($sp)
/* 00401a94 */  swc1       $f13, 0x1c($sp)
/* 00401a98 */  mfc1       $a3, $f8
/* 00401a9c */  mfc1       $a2, $f9
/* 00401aa0 */  jal        0xf801250                                # getopt
/* 00401aa4 */  nop        
/* 00401aa8 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00401aac */  lwc1       $f13, 0x1c($sp)
/* 00401ab0 */  lw         $v0, 0x160($t9)
/* 00401ab4 */  lwc1       $f12, 0x20($sp)
/* 00401ab8 */  beqz       $v0, 0x401b0c
/* 00401abc */  nop        
/* 00401ac0 */  sll        $t0, $v0, 2
/* 00401ac4 */  subu       $t0, $t0, $v0
/* 00401ac8 */  sll        $t0, $t0, 3
/* 00401acc */  addu       $t0, $t0, $v0
/* 00401ad0 */  sll        $t0, $t0, 2
/* 00401ad4 */  mtc1       $t0, $f10
/* 00401ad8 */  lui        $a0, 0x1000
/* 00401adc */  cvt.d.w    $f16, $f10
/* 00401ae0 */  swc1       $f13, 0x1c($sp)
/* 00401ae4 */  addiu      $a0, $a0, 0x600
/* 00401ae8 */  div.d      $f18, $f16, $f12
/* 00401aec */  swc1       $f12, 0x20($sp)
/* 00401af0 */  mfc1       $a3, $f18
/* 00401af4 */  mfc1       $a2, $f19
/* 00401af8 */  jal        0xf801250                                # getopt
/* 00401afc */  nop        
/* 00401b00 */  lwc1       $f13, 0x1c($sp)
/* 00401b04 */  lwc1       $f12, 0x20($sp)
/* 00401b08 */  nop        
/* 00401b0c */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00401b10 */  nop        
/* 00401b14 */  lw         $v0, 0x164($t1)
/* 00401b18 */  nop        
/* 00401b1c */  beqz       $v0, 0x401b64
/* 00401b20 */  nop        
/* 00401b24 */  sll        $t2, $v0, 2
/* 00401b28 */  subu       $t2, $t2, $v0
/* 00401b2c */  sll        $t2, $t2, 3
/* 00401b30 */  addu       $t2, $t2, $v0
/* 00401b34 */  sll        $t2, $t2, 2
/* 00401b38 */  mtc1       $t2, $f4
/* 00401b3c */  lui        $a0, 0x1000
/* 00401b40 */  cvt.d.w    $f6, $f4
/* 00401b44 */  addiu      $a0, $a0, 0x614
/* 00401b48 */  div.d      $f8, $f6, $f12
/* 00401b4c */  mfc1       $a3, $f8
/* 00401b50 */  mfc1       $a2, $f9
/* 00401b54 */  jal        0xf801250                                # getopt
/* 00401b58 */  nop        
/* 00401b5c */  b          0x401b70
/* 00401b60 */  lw         $t3, 0x24($sp)
/* 00401b64 */  jal        0xf801250                                # getopt
/* 00401b68 */  addiu      $a0, $gp, -0x7db4
/* 00401b6c */  lw         $t3, 0x24($sp)
/* 00401b70 */  nop        
/* 00401b74 */  sw         $t3, -0x7b70($gp)                        # .sbss @ 0x10004200
/* 00401b78 */  lw         $ra, 0x14($sp)
/* 00401b7c */  addiu      $sp, $sp, 0x38
/* 00401b80 */  jr         $ra
/* 00401b84 */  nop        
/* 00401b88 */  lwc1       $f1, -0x7fe0($gp)                        # .lit8: 0.5
/* 00401b8c */  lwc1       $f0, -0x7fdc($gp)                        # .lit8 @ 0x10003d94
/* 00401b90 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401b94 */  cvt.d.s    $f4, $f12
/* 00401b98 */  lwc1       $f9, -0x7fd8($gp)                        # .lit8: 1.2
/* 00401b9c */  lwc1       $f8, -0x7fd4($gp)                        # .lit8 @ 0x10003d9c
/* 00401ba0 */  sub.d      $f6, $f4, $f0
/* 00401ba4 */  lw         $v1, 0xd4($t6)
/* 00401ba8 */  mul.d      $f10, $f6, $f8
/* 00401bac */  addiu      $a0, $v1, -1
/* 00401bb0 */  mtc1       $a0, $f18
/* 00401bb4 */  nop        
/* 00401bb8 */  cvt.d.w    $f4, $f18
/* 00401bbc */  add.d      $f16, $f10, $f0
/* 00401bc0 */  mul.d      $f6, $f16, $f4
/* 00401bc4 */  cfc1       $t7, $31
/* 00401bc8 */  cfc1       $t7, $31
/* 00401bcc */  nop        
/* 00401bd0 */  ori        $at, $t7, 3
/* 00401bd4 */  xori       $at, $at, 2
/* 00401bd8 */  ctc1       $at, $31
/* 00401bdc */  nop        
/* 00401be0 */  cvt.w.d    $f8, $f6
/* 00401be4 */  mfc1       $v0, $f8
/* 00401be8 */  ctc1       $t7, $31
/* 00401bec */  bgez       $v0, 0x401c00
/* 00401bf0 */  slt        $at, $v0, $v1
/* 00401bf4 */  b          0x401c0c
/* 00401bf8 */  move       $v0, $zero
/* 00401bfc */  slt        $at, $v0, $v1
/* 00401c00 */  bnez       $at, 0x401c0c
/* 00401c04 */  nop        
/* 00401c08 */  move       $v0, $a0
/* 00401c0c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00401c10 */  jr         $ra
/* 00401c14 */  sw         $v0, 0xd8($t8)
/* 00401c18 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401c1c */  lw         $v0, -0x7da8($gp)                        # .sdata @ 0x10003fc8
/* 00401c20 */  lw         $t7, 0xcc($t6)
/* 00401c24 */  nop        
/* 00401c28 */  slt        $at, $v0, $t7
/* 00401c2c */  bnez       $at, 0x401ce0
/* 00401c30 */  addiu      $v0, $v0, 1
/* 00401c34 */  lw         $t8, 0xd0($t6)
/* 00401c38 */  move       $v0, $zero
/* 00401c3c */  bnez       $t8, 0x401c74
/* 00401c40 */  nop        
/* 00401c44 */  lw         $v1, -0x7dac($gp)                        # .sdata @ 0x10003fc4
/* 00401c48 */  lw         $t9, 0xd4($t6)
/* 00401c4c */  addiu      $v1, $v1, 1
/* 00401c50 */  slt        $at, $v1, $t9
/* 00401c54 */  bnez       $at, 0x401c60
/* 00401c58 */  nop        
/* 00401c5c */  move       $v1, $zero
/* 00401c60 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00401c64 */  nop        
/* 00401c68 */  sw         $v1, 0xd8($t0)
/* 00401c6c */  b          0x401cdc
/* 00401c70 */  sw         $v1, -0x7dac($gp)                        # .sdata @ 0x10003fc4
/* 00401c74 */  lw         $t1, -0x7db0($gp)                        # .sdata @ 0x10003fc0
/* 00401c78 */  nop        
/* 00401c7c */  beqz       $t1, 0x401cac
/* 00401c80 */  nop        
/* 00401c84 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00401c88 */  lw         $v1, -0x7dac($gp)                        # .sdata @ 0x10003fc4
/* 00401c8c */  lw         $a0, 0xd4($t2)
/* 00401c90 */  addiu      $v1, $v1, 1
/* 00401c94 */  slt        $at, $v1, $a0
/* 00401c98 */  bnez       $at, 0x401ccc
/* 00401c9c */  nop        
/* 00401ca0 */  sw         $zero, -0x7db0($gp)                      # .sdata @ 0x10003fc0
/* 00401ca4 */  b          0x401ccc
/* 00401ca8 */  addiu      $v1, $a0, -1
/* 00401cac */  lw         $v1, -0x7dac($gp)                        # .sdata @ 0x10003fc4
/* 00401cb0 */  nop        
/* 00401cb4 */  addiu      $v1, $v1, -1
/* 00401cb8 */  bgez       $v1, 0x401ccc
/* 00401cbc */  nop        
/* 00401cc0 */  addiu      $t3, $zero, 1
/* 00401cc4 */  sw         $t3, -0x7db0($gp)                        # .sdata @ 0x10003fc0
/* 00401cc8 */  move       $v1, $zero
/* 00401ccc */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00401cd0 */  nop        
/* 00401cd4 */  sw         $v1, 0xd8($t4)
/* 00401cd8 */  sw         $v1, -0x7dac($gp)                        # .sdata @ 0x10003fc4
/* 00401cdc */  addiu      $v0, $v0, 1
/* 00401ce0 */  jr         $ra
/* 00401ce4 */  sw         $v0, -0x7da8($gp)                        # .sdata @ 0x10003fc8

# === save_image ===
glabel save_image
/* 00401ce8 */  addiu      $sp, $sp, -0x90
/* 00401cec */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401cf0 */  sw         $ra, 0x1c($sp)
/* 00401cf4 */  sw         $s7, 0x18($sp)
/* 00401cf8 */  sw         $s0, 0x14($sp)
/* 00401cfc */  lw         $s0, 0x98($t6)
/* 00401d00 */  addiu      $a1, $gp, -0x7da4
/* 00401d04 */  jal        0xf801130                                # fgets
/* 00401d08 */  move       $a0, $s0
/* 00401d0c */  beqz       $v0, 0x401e8c
/* 00401d10 */  move       $s7, $v0
/* 00401d14 */  sw         $s1, 0x34($sp)
/* 00401d18 */  sw         $s2, 0x30($sp)
/* 00401d1c */  sw         $s3, 0x2c($sp)
/* 00401d20 */  lui        $a0, 0x1000
/* 00401d24 */  lui        $a1, 0x1000
/* 00401d28 */  sw         $s4, 0x28($sp)
/* 00401d2c */  sw         $s5, 0x24($sp)
/* 00401d30 */  sw         $s6, 0x20($sp)
/* 00401d34 */  addiu      $a1, $a1, 0x624
/* 00401d38 */  addiu      $a0, $a0, 0x36b4
/* 00401d3c */  addiu      $a2, $gp, -0x7ea0
/* 00401d40 */  jal        0xf801150                                # fclose
/* 00401d44 */  move       $a3, $s0
/* 00401d48 */  jal        0xf402578                                # depthcue
/* 00401d4c */  addiu      $a0, $zero, 1
/* 00401d50 */  jal        0xf401120                                # qdevice
/* 00401d54 */  addiu      $a0, $sp, 0x48
/* 00401d58 */  lui        $a0, 0x1000
/* 00401d5c */  jal        0xf801250                                # getopt
/* 00401d60 */  addiu      $a0, $a0, 0x644
/* 00401d64 */  move       $v0, $zero
/* 00401d68 */  move       $s4, $zero
/* 00401d6c */  addiu      $s2, $gp, -0x7d9c
/* 00401d70 */  addiu      $s3, $zero, 4
/* 00401d74 */  addiu      $s5, $gp, -0x7da0
/* 00401d78 */  addiu      $s6, $gp, -0x7d98
/* 00401d7c */  jal        0xf801250                                # getopt
/* 00401d80 */  move       $a0, $s5
/* 00401d84 */  sll        $t7, $s4, 2
/* 00401d88 */  addiu      $t8, $sp, 0x90
/* 00401d8c */  addu       $s0, $t7, $t8
/* 00401d90 */  move       $s1, $zero
/* 00401d94 */  lwc1       $f4, -0x48($s0)
/* 00401d98 */  move       $a0, $s2
/* 00401d9c */  cvt.d.s    $f6, $f4
/* 00401da0 */  mfc1       $a3, $f6
/* 00401da4 */  mfc1       $a2, $f7
/* 00401da8 */  jal        0xf801250                                # getopt
/* 00401dac */  nop        
/* 00401db0 */  addiu      $s1, $s1, 1
/* 00401db4 */  bne        $s1, $s3, 0x401d94
/* 00401db8 */  addiu      $s0, $s0, 4
/* 00401dbc */  jal        0xf801250                                # getopt
/* 00401dc0 */  move       $a0, $s6
/* 00401dc4 */  addiu      $s4, $s4, 4
/* 00401dc8 */  slti       $at, $s4, 0x10
/* 00401dcc */  bnez       $at, 0x401d7c
/* 00401dd0 */  nop        
/* 00401dd4 */  move       $s1, $zero
/* 00401dd8 */  addiu      $s1, $gp, -0x7d94
/* 00401ddc */  addiu      $s0, $sp, 0x90
/* 00401de0 */  addiu      $s2, $sp, 0xd0
/* 00401de4 */  lwc1       $f8, -0x48($s0)
/* 00401de8 */  move       $a0, $s7
/* 00401dec */  cvt.d.s    $f10, $f8
/* 00401df0 */  mfc1       $a3, $f10
/* 00401df4 */  mfc1       $a2, $f11
/* 00401df8 */  jal        0xf801150                                # fclose
/* 00401dfc */  move       $a1, $s1
/* 00401e00 */  addiu      $s0, $s0, 4
/* 00401e04 */  bne        $s0, $s2, 0x401de4
/* 00401e08 */  nop        
/* 00401e0c */  move       $a0, $s7
/* 00401e10 */  jal        0xf801150                                # fclose
/* 00401e14 */  addiu      $a1, $gp, -0x7d90
/* 00401e18 */  jal        0xf402578                                # depthcue
/* 00401e1c */  addiu      $a0, $zero, 2
/* 00401e20 */  jal        0xf401120                                # qdevice
/* 00401e24 */  addiu      $a0, $sp, 0x48
/* 00401e28 */  move       $s1, $zero
/* 00401e2c */  addiu      $s1, $gp, -0x7d8c
/* 00401e30 */  addiu      $s0, $sp, 0x90
/* 00401e34 */  addiu      $s2, $sp, 0xd0
/* 00401e38 */  lwc1       $f16, -0x48($s0)
/* 00401e3c */  move       $a0, $s7
/* 00401e40 */  cvt.d.s    $f18, $f16
/* 00401e44 */  mfc1       $a3, $f18
/* 00401e48 */  mfc1       $a2, $f19
/* 00401e4c */  jal        0xf801150                                # fclose
/* 00401e50 */  move       $a1, $s1
/* 00401e54 */  addiu      $s0, $s0, 4
/* 00401e58 */  bne        $s0, $s2, 0x401e38
/* 00401e5c */  nop        
/* 00401e60 */  move       $a0, $s7
/* 00401e64 */  jal        0xf801150                                # fclose
/* 00401e68 */  addiu      $a1, $gp, -0x7d88
/* 00401e6c */  lw         $s1, 0x34($sp)
/* 00401e70 */  lw         $s2, 0x30($sp)
/* 00401e74 */  lw         $s3, 0x2c($sp)
/* 00401e78 */  lw         $s4, 0x28($sp)
/* 00401e7c */  lw         $s5, 0x24($sp)
/* 00401e80 */  lw         $s6, 0x20($sp)
/* 00401e84 */  b          0x401eac
/* 00401e88 */  lw         $ra, 0x1c($sp)
/* 00401e8c */  lui        $a0, 0x1000
/* 00401e90 */  lui        $a1, 0x1000
/* 00401e94 */  addiu      $a1, $a1, 0x668
/* 00401e98 */  addiu      $a0, $a0, 0x36b4
/* 00401e9c */  addiu      $a2, $gp, -0x7ea0
/* 00401ea0 */  jal        0xf801150                                # fclose
/* 00401ea4 */  move       $a3, $s0
/* 00401ea8 */  lw         $ra, 0x1c($sp)
/* 00401eac */  lw         $s0, 0x14($sp)
/* 00401eb0 */  lw         $s7, 0x18($sp)
/* 00401eb4 */  jr         $ra
/* 00401eb8 */  addiu      $sp, $sp, 0x90

# === draw_scene_special ===
glabel draw_scene_special
/* 00401ebc */  addiu      $sp, $sp, -0x58
/* 00401ec0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00401ec4 */  lw         $t7, -0x7d84($gp)                        # .sdata @ 0x10003fec
/* 00401ec8 */  sw         $ra, 0x1c($sp)
/* 00401ecc */  sw         $s0, 0x18($sp)
/* 00401ed0 */  lw         $s0, 0x98($t6)
/* 00401ed4 */  bnez       $t7, 0x402060
/* 00401ed8 */  nop        
/* 00401edc */  sw         $s3, 0x3c($sp)
/* 00401ee0 */  move       $a0, $s0
/* 00401ee4 */  jal        0xf801130                                # fgets
/* 00401ee8 */  addiu      $a1, $gp, -0x7d80
/* 00401eec */  beqz       $v0, 0x402034
/* 00401ef0 */  move       $s3, $v0
/* 00401ef4 */  sw         $s1, 0x38($sp)
/* 00401ef8 */  sw         $s2, 0x34($sp)
/* 00401efc */  sw         $s4, 0x30($sp)
/* 00401f00 */  lui        $a0, 0x1000
/* 00401f04 */  lui        $a1, 0x1000
/* 00401f08 */  sw         $s5, 0x2c($sp)
/* 00401f0c */  sw         $s6, 0x28($sp)
/* 00401f10 */  sw         $s7, 0x24($sp)
/* 00401f14 */  addiu      $a1, $a1, 0x688
/* 00401f18 */  addiu      $a0, $a0, 0x36b4
/* 00401f1c */  addiu      $a2, $gp, -0x7ea0
/* 00401f20 */  jal        0xf801150                                # fclose
/* 00401f24 */  move       $a3, $s0
/* 00401f28 */  move       $s1, $zero
/* 00401f2c */  lui        $s0, 0x1000
/* 00401f30 */  lui        $s2, 0x1000
/* 00401f34 */  addiu      $s2, $s2, 0x4528
/* 00401f38 */  addiu      $s0, $s0, 0x44e8
/* 00401f3c */  addiu      $s1, $gp, -0x7d7c
/* 00401f40 */  move       $a0, $s3
/* 00401f44 */  move       $a1, $s1
/* 00401f48 */  jal        0x40d768
/* 00401f4c */  move       $a2, $s0
/* 00401f50 */  addiu      $s0, $s0, 4
/* 00401f54 */  bne        $s0, $s2, 0x401f44
/* 00401f58 */  move       $a0, $s3
/* 00401f5c */  move       $s1, $zero
/* 00401f60 */  lui        $s0, 0x1000
/* 00401f64 */  lui        $s2, 0x1000
/* 00401f68 */  addiu      $s2, $s2, 0x4568
/* 00401f6c */  addiu      $s0, $s0, 0x4528
/* 00401f70 */  addiu      $s1, $gp, -0x7d78
/* 00401f74 */  move       $a0, $s3
/* 00401f78 */  move       $a1, $s1
/* 00401f7c */  jal        0x40d768
/* 00401f80 */  move       $a2, $s0
/* 00401f84 */  addiu      $s0, $s0, 4
/* 00401f88 */  bne        $s0, $s2, 0x401f78
/* 00401f8c */  move       $a0, $s3
/* 00401f90 */  lui        $a0, 0x1000
/* 00401f94 */  jal        0xf801250                                # getopt
/* 00401f98 */  addiu      $a0, $a0, 0x6ac
/* 00401f9c */  move       $v0, $zero
/* 00401fa0 */  move       $s4, $zero
/* 00401fa4 */  addiu      $s2, $gp, -0x7d70
/* 00401fa8 */  addiu      $s3, $zero, 4
/* 00401fac */  addiu      $s5, $gp, -0x7d74
/* 00401fb0 */  addiu      $s6, $gp, -0x7d6c
/* 00401fb4 */  addiu      $s7, $zero, 0x10
/* 00401fb8 */  jal        0xf801250                                # getopt
/* 00401fbc */  move       $a0, $s5
/* 00401fc0 */  lui        $t9, 0x1000
/* 00401fc4 */  addiu      $t9, $t9, 0x44e8
/* 00401fc8 */  sll        $t8, $s4, 2
/* 00401fcc */  addu       $s0, $t8, $t9
/* 00401fd0 */  move       $s1, $zero
/* 00401fd4 */  lwc1       $f4, ($s0)
/* 00401fd8 */  move       $a0, $s2
/* 00401fdc */  cvt.d.s    $f6, $f4
/* 00401fe0 */  mfc1       $a3, $f6
/* 00401fe4 */  mfc1       $a2, $f7
/* 00401fe8 */  jal        0xf801250                                # getopt
/* 00401fec */  nop        
/* 00401ff0 */  addiu      $s1, $s1, 1
/* 00401ff4 */  bne        $s1, $s3, 0x401fd4
/* 00401ff8 */  addiu      $s0, $s0, 4
/* 00401ffc */  jal        0xf801250                                # getopt
/* 00402000 */  move       $a0, $s6
/* 00402004 */  addiu      $s4, $s4, 4
/* 00402008 */  bne        $s4, $s7, 0x401fb8
/* 0040200c */  nop        
/* 00402010 */  addiu      $t0, $zero, 1
/* 00402014 */  lw         $s1, 0x38($sp)
/* 00402018 */  lw         $s2, 0x34($sp)
/* 0040201c */  lw         $s4, 0x30($sp)
/* 00402020 */  lw         $s5, 0x2c($sp)
/* 00402024 */  lw         $s6, 0x28($sp)
/* 00402028 */  lw         $s7, 0x24($sp)
/* 0040202c */  b          0x402058
/* 00402030 */  sw         $t0, -0x7d84($gp)                        # .sdata @ 0x10003fec
/* 00402034 */  lui        $a0, 0x1000
/* 00402038 */  lui        $a1, 0x1000
/* 0040203c */  addiu      $a1, $a1, 0x6d4
/* 00402040 */  addiu      $a0, $a0, 0x36b4
/* 00402044 */  addiu      $a2, $gp, -0x7ea0
/* 00402048 */  jal        0xf801150                                # fclose
/* 0040204c */  move       $a3, $s0
/* 00402050 */  jal        0x40d3c0
/* 00402054 */  addiu      $a0, $zero, -1
/* 00402058 */  lw         $s3, 0x3c($sp)
/* 0040205c */  nop        
/* 00402060 */  jal        0xf402578                                # depthcue
/* 00402064 */  addiu      $a0, $zero, 1
/* 00402068 */  lui        $a0, 0x1000
/* 0040206c */  jal        0xf402190                                # font
/* 00402070 */  addiu      $a0, $a0, 0x44e8
/* 00402074 */  jal        0xf402578                                # depthcue
/* 00402078 */  addiu      $a0, $zero, 2
/* 0040207c */  lui        $a0, 0x1000
/* 00402080 */  jal        0xf402190                                # font
/* 00402084 */  addiu      $a0, $a0, 0x4528
/* 00402088 */  lw         $ra, 0x1c($sp)
/* 0040208c */  lw         $s0, 0x18($sp)
/* 00402090 */  jr         $ra
/* 00402094 */  addiu      $sp, $sp, 0x58

# === event_loop_and_render ===
glabel event_loop_and_render
/* 00402098 */  addiu      $sp, $sp, -0x98
/* 0040209c */  sw         $ra, 0x14($sp)
/* 004020a0 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004020a4 */  addiu      $t6, $zero, 1
/* 004020a8 */  addiu      $t7, $zero, 1
/* 004020ac */  sw         $zero, 0x94($sp)
/* 004020b0 */  sw         $t6, 0x90($sp)
/* 004020b4 */  sw         $zero, 0x70($sp)
/* 004020b8 */  sw         $t7, 0x60($sp)
/* 004020bc */  sw         $zero, 0x50($sp)
/* 004020c0 */  lw         $t9, 0x48($t8)
/* 004020c4 */  nop        
/* 004020c8 */  beqz       $t9, 0x4020d8
/* 004020cc */  nop        
/* 004020d0 */  jal        0x402f60
/* 004020d4 */  nop        
/* 004020d8 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 004020dc */  nop        
/* 004020e0 */  sw         $zero, 0xd8($t0)
/* 004020e4 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 004020e8 */  sw         $zero, 0x5c($sp)
/* 004020ec */  sw         $zero, 0x70($t1)
/* 004020f0 */  sw         $zero, 0x68($sp)
/* 004020f4 */  jal        0xf401200                                # qtest
/* 004020f8 */  nop        
/* 004020fc */  beqz       $v0, 0x40267c
/* 00402100 */  lw         $t3, 0x94($sp)
/* 00402104 */  jal        0xf4011f0                                # qread
/* 00402108 */  addiu      $a0, $sp, 0x88
/* 0040210c */  sll        $v1, $v0, 0x10
/* 00402110 */  b          0x40252c
/* 00402114 */  sra        $v1, $v1, 0x10
/* 00402118 */  lh         $t2, 0x88($sp)
/* 0040211c */  nop        
/* 00402120 */  beqz       $t2, 0x402138
/* 00402124 */  nop        
/* 00402128 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 0040212c */  addiu      $t3, $zero, 1
/* 00402130 */  b          0x402668
/* 00402134 */  sw         $t3, 0x20($t4)
/* 00402138 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 0040213c */  b          0x402668
/* 00402140 */  sw         $zero, 0x20($t5)
/* 00402144 */  lh         $t6, 0x88($sp)
/* 00402148 */  nop        
/* 0040214c */  beqz       $t6, 0x402164
/* 00402150 */  nop        
/* 00402154 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00402158 */  addiu      $t7, $zero, 1
/* 0040215c */  b          0x402668
/* 00402160 */  sw         $t7, 0x18($t8)
/* 00402164 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00402168 */  b          0x402668
/* 0040216c */  sw         $zero, 0x18($t9)
/* 00402170 */  lh         $t0, 0x88($sp)
/* 00402174 */  nop        
/* 00402178 */  beqz       $t0, 0x402190
/* 0040217c */  nop        
/* 00402180 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00402184 */  addiu      $t1, $zero, 1
/* 00402188 */  b          0x402668
/* 0040218c */  sw         $t1, 0x1c($t2)
/* 00402190 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00402194 */  b          0x402668
/* 00402198 */  sw         $zero, 0x1c($t3)
/* 0040219c */  lh         $t4, 0x88($sp)
/* 004021a0 */  nop        
/* 004021a4 */  beqz       $t4, 0x402668
/* 004021a8 */  nop        
/* 004021ac */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 004021b0 */  nop        
/* 004021b4 */  lw         $a0, 0x64($t5)
/* 004021b8 */  jal        0xf401500                                # dopup
/* 004021bc */  nop        
/* 004021c0 */  addiu      $at, $zero, 1
/* 004021c4 */  beq        $v0, $at, 0x4021dc
/* 004021c8 */  addiu      $at, $zero, 2
/* 004021cc */  beq        $v0, $at, 0x4021f4
/* 004021d0 */  addiu      $t8, $zero, 1
/* 004021d4 */  b          0x402668
/* 004021d8 */  nop        
/* 004021dc */  lw         $t6, 0x5c($sp)
/* 004021e0 */  nop        
/* 004021e4 */  sltiu      $t7, $t6, 1
/* 004021e8 */  b          0x402668
/* 004021ec */  sw         $t7, 0x5c($sp)
/* 004021f0 */  addiu      $t8, $zero, 1
/* 004021f4 */  b          0x402668
/* 004021f8 */  sw         $t8, 0x94($sp)
/* 004021fc */  lw         $t9, -0x7e88($gp)                        # .sdata @ 0x10003ee8
/* 00402200 */  nop        
/* 00402204 */  beqz       $t9, 0x40226c
/* 00402208 */  lh         $t5, 0x88($sp)
/* 0040220c */  lw         $t0, -0x7e84($gp)                        # .sdata @ 0x10003eec
/* 00402210 */  nop        
/* 00402214 */  bnez       $t0, 0x402240
/* 00402218 */  nop        
/* 0040221c */  lh         $t1, 0x88($sp)
/* 00402220 */  addiu      $at, $zero, 1
/* 00402224 */  bne        $t1, $at, 0x402240
/* 00402228 */  nop        
/* 0040222c */  addiu      $t2, $zero, 1
/* 00402230 */  jal        0x402f00                                 # render_frame_no_zbuf
/* 00402234 */  sw         $t2, -0x7e84($gp)                        # .sdata @ 0x10003eec
/* 00402238 */  b          0x402668
/* 0040223c */  nop        
/* 00402240 */  lw         $t3, -0x7e84($gp)                        # .sdata @ 0x10003eec
/* 00402244 */  addiu      $at, $zero, 1
/* 00402248 */  bne        $t3, $at, 0x402668
/* 0040224c */  nop        
/* 00402250 */  lh         $t4, 0x88($sp)
/* 00402254 */  addiu      $at, $zero, 1
/* 00402258 */  bne        $t4, $at, 0x402668
/* 0040225c */  nop        
/* 00402260 */  b          0x402668
/* 00402264 */  sw         $zero, -0x7e84($gp)                      # .sdata @ 0x10003eec
/* 00402268 */  lh         $t5, 0x88($sp)
/* 0040226c */  nop        
/* 00402270 */  beqz       $t5, 0x402284
/* 00402274 */  nop        
/* 00402278 */  addiu      $t6, $zero, 1
/* 0040227c */  b          0x402668
/* 00402280 */  sw         $t6, 0x70($sp)
/* 00402284 */  b          0x402668
/* 00402288 */  sw         $zero, 0x70($sp)
/* 0040228c */  lh         $t7, 0x88($sp)
/* 00402290 */  nop        
/* 00402294 */  bnez       $t7, 0x402668
/* 00402298 */  nop        
/* 0040229c */  addiu      $t8, $zero, 1
/* 004022a0 */  b          0x402668
/* 004022a4 */  sw         $t8, 0x94($sp)
/* 004022a8 */  addiu      $t9, $zero, 1
/* 004022ac */  jal        0xf401450                                # reshapeviewport
/* 004022b0 */  sw         $t9, 0x60($sp)
/* 004022b4 */  lw         $v1, -0x7e98($gp)                        # view_state_ptr
/* 004022b8 */  nop        
/* 004022bc */  addiu      $a0, $v1, 8
/* 004022c0 */  jal        0xf401440                                # getorigin
/* 004022c4 */  addiu      $a1, $v1, 0xc
/* 004022c8 */  lw         $v1, -0x7e98($gp)                        # view_state_ptr
/* 004022cc */  nop        
/* 004022d0 */  move       $a0, $v1
/* 004022d4 */  jal        0xf401438                                # getsize
/* 004022d8 */  addiu      $a1, $v1, 4
/* 004022dc */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 004022e0 */  nop        
/* 004022e4 */  lw         $t1, ($t0)
/* 004022e8 */  lw         $t2, 4($t0)
/* 004022ec */  mtc1       $t1, $f4
/* 004022f0 */  mtc1       $t2, $f10
/* 004022f4 */  cvt.s.w    $f6, $f4
/* 004022f8 */  cvt.d.w    $f16, $f10
/* 004022fc */  cvt.d.s    $f8, $f6
/* 00402300 */  nop        
/* 00402304 */  div.d      $f18, $f8, $f16
/* 00402308 */  cvt.s.d    $f4, $f18
/* 0040230c */  swc1       $f4, 0x6c($t0)
/* 00402310 */  lw         $t3, -0x7e88($gp)                        # .sdata @ 0x10003ee8
/* 00402314 */  nop        
/* 00402318 */  beqz       $t3, 0x402668
/* 0040231c */  nop        
/* 00402320 */  lw         $t4, -0x7e84($gp)                        # .sdata @ 0x10003eec
/* 00402324 */  nop        
/* 00402328 */  beqz       $t4, 0x402668
/* 0040232c */  nop        
/* 00402330 */  jal        0x402f00                                 # render_frame_no_zbuf
/* 00402334 */  nop        
/* 00402338 */  b          0x402668
/* 0040233c */  nop        
/* 00402340 */  lw         $t5, -0x7e88($gp)                        # .sdata @ 0x10003ee8
/* 00402344 */  nop        
/* 00402348 */  beqz       $t5, 0x402668
/* 0040234c */  nop        
/* 00402350 */  lw         $t6, -0x7e84($gp)                        # .sdata @ 0x10003eec
/* 00402354 */  nop        
/* 00402358 */  beqz       $t6, 0x402668
/* 0040235c */  nop        
/* 00402360 */  jal        0x402f00                                 # render_frame_no_zbuf
/* 00402364 */  nop        
/* 00402368 */  b          0x402668
/* 0040236c */  nop        
/* 00402370 */  lh         $t7, 0x88($sp)
/* 00402374 */  nop        
/* 00402378 */  beqz       $t7, 0x40238c
/* 0040237c */  nop        
/* 00402380 */  addiu      $t8, $zero, 1
/* 00402384 */  b          0x402390
/* 00402388 */  sw         $t8, 0x90($sp)
/* 0040238c */  sw         $zero, 0x90($sp)
/* 00402390 */  lw         $t9, -0x7e88($gp)                        # .sdata @ 0x10003ee8
/* 00402394 */  nop        
/* 00402398 */  beqz       $t9, 0x402668
/* 0040239c */  nop        
/* 004023a0 */  lw         $t1, -0x7e84($gp)                        # .sdata @ 0x10003eec
/* 004023a4 */  nop        
/* 004023a8 */  beqz       $t1, 0x402668
/* 004023ac */  nop        
/* 004023b0 */  jal        0x402f00                                 # render_frame_no_zbuf
/* 004023b4 */  nop        
/* 004023b8 */  b          0x402668
/* 004023bc */  nop        
/* 004023c0 */  lh         $t2, 0x88($sp)
/* 004023c4 */  nop        
/* 004023c8 */  beqz       $t2, 0x402668
/* 004023cc */  nop        
/* 004023d0 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 004023d4 */  nop        
/* 004023d8 */  lw         $a0, 0x9c($t0)
/* 004023dc */  jal        0x409778
/* 004023e0 */  nop        
/* 004023e4 */  b          0x402668
/* 004023e8 */  nop        
/* 004023ec */  lh         $t3, 0x88($sp)
/* 004023f0 */  nop        
/* 004023f4 */  beqz       $t3, 0x402668
/* 004023f8 */  nop        
/* 004023fc */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00402400 */  nop        
/* 00402404 */  lw         $t5, 0x90($t4)
/* 00402408 */  nop        
/* 0040240c */  beqz       $t5, 0x402668
/* 00402410 */  nop        
/* 00402414 */  addiu      $t6, $zero, 1
/* 00402418 */  b          0x402668
/* 0040241c */  sw         $t6, 0x50($sp)
/* 00402420 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00402424 */  nop        
/* 00402428 */  lw         $v0, 0x50($t7)
/* 0040242c */  nop        
/* 00402430 */  slti       $at, $v0, 0x3e8
/* 00402434 */  beqz       $at, 0x402668
/* 00402438 */  nop        
/* 0040243c */  lh         $t8, 0x88($sp)
/* 00402440 */  addiu      $at, $zero, 1
/* 00402444 */  bne        $t8, $at, 0x402668
/* 00402448 */  nop        
/* 0040244c */  addiu      $t9, $v0, 0x14
/* 00402450 */  b          0x402668
/* 00402454 */  sw         $t9, 0x50($t7)
/* 00402458 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 0040245c */  nop        
/* 00402460 */  lw         $v0, 0x50($t1)
/* 00402464 */  nop        
/* 00402468 */  slti       $at, $v0, 0xc9
/* 0040246c */  bnez       $at, 0x402668
/* 00402470 */  nop        
/* 00402474 */  lh         $t2, 0x88($sp)
/* 00402478 */  addiu      $at, $zero, 1
/* 0040247c */  bne        $t2, $at, 0x402668
/* 00402480 */  nop        
/* 00402484 */  addiu      $t0, $v0, -0x14
/* 00402488 */  b          0x402668
/* 0040248c */  sw         $t0, 0x50($t1)
/* 00402490 */  lh         $t3, 0x88($sp)
/* 00402494 */  addiu      $at, $zero, 1
/* 00402498 */  bne        $t3, $at, 0x402668
/* 0040249c */  nop        
/* 004024a0 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 004024a4 */  lwc1       $f8, -0x7ed8($gp)                        # .lit4: 1.2
/* 004024a8 */  lwc1       $f6, 0x4c($t4)
/* 004024ac */  cvt.d.s    $f16, $f8
/* 004024b0 */  cvt.d.s    $f10, $f6
/* 004024b4 */  mul.d      $f18, $f10, $f16
/* 004024b8 */  cvt.s.d    $f4, $f18
/* 004024bc */  b          0x402668
/* 004024c0 */  swc1       $f4, 0x4c($t4)
/* 004024c4 */  lh         $t5, 0x88($sp)
/* 004024c8 */  addiu      $at, $zero, 1
/* 004024cc */  bne        $t5, $at, 0x402668
/* 004024d0 */  nop        
/* 004024d4 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 004024d8 */  lwc1       $f11, -0x7fd8($gp)                       # .lit8: 1.2
/* 004024dc */  lwc1       $f6, 0x4c($t6)
/* 004024e0 */  lwc1       $f10, -0x7fd4($gp)                       # .lit8 @ 0x10003d9c
/* 004024e4 */  cvt.d.s    $f8, $f6
/* 004024e8 */  nop        
/* 004024ec */  div.d      $f16, $f8, $f10
/* 004024f0 */  cvt.s.d    $f18, $f16
/* 004024f4 */  b          0x402668
/* 004024f8 */  swc1       $f18, 0x4c($t6)
/* 004024fc */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00402500 */  addiu      $t8, $zero, 1
/* 00402504 */  b          0x402668
/* 00402508 */  sw         $t8, 0x54($t9)
/* 0040250c */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00402510 */  addiu      $t7, $zero, 2
/* 00402514 */  b          0x402668
/* 00402518 */  sw         $t7, 0x54($t2)
/* 0040251c */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00402520 */  addiu      $t0, $zero, 3
/* 00402524 */  b          0x402668
/* 00402528 */  sw         $t0, 0x54($t1)
/* 0040252c */  addiu      $at, $zero, 0x28
/* 00402530 */  beq        $v1, $at, 0x4023c0
/* 00402534 */  slti       $at, $v1, 0x29
/* 00402538 */  beqz       $at, 0x4025f0
/* 0040253c */  addiu      $at, $zero, 0x14
/* 00402540 */  beq        $v1, $at, 0x40251c
/* 00402544 */  slti       $at, $v1, 0x15
/* 00402548 */  beqz       $at, 0x4025b8
/* 0040254c */  addiu      $at, $zero, 0xb
/* 00402550 */  beq        $v1, $at, 0x402420
/* 00402554 */  slti       $at, $v1, 0xc
/* 00402558 */  beqz       $at, 0x402594
/* 0040255c */  addiu      $at, $zero, 7
/* 00402560 */  beq        $v1, $at, 0x40228c
/* 00402564 */  slti       $at, $v1, 8
/* 00402568 */  beqz       $at, 0x402580
/* 0040256c */  addiu      $at, $zero, 6
/* 00402570 */  beq        $v1, $at, 0x40211c
/* 00402574 */  lh         $t2, 0x88($sp)
/* 00402578 */  b          0x402668
/* 0040257c */  nop        
/* 00402580 */  addiu      $at, $zero, 0xa
/* 00402584 */  beq        $v1, $at, 0x4024c8
/* 00402588 */  lh         $t5, 0x88($sp)
/* 0040258c */  b          0x402668
/* 00402590 */  nop        
/* 00402594 */  addiu      $at, $zero, 0x10
/* 00402598 */  beq        $v1, $at, 0x402490
/* 0040259c */  slti       $at, $v1, 0x11
/* 004025a0 */  beqz       $at, 0x402668
/* 004025a4 */  addiu      $at, $zero, 0xc
/* 004025a8 */  beq        $v1, $at, 0x402458
/* 004025ac */  nop        
/* 004025b0 */  b          0x402668
/* 004025b4 */  nop        
/* 004025b8 */  addiu      $at, $zero, 0x1d
/* 004025bc */  beq        $v1, $at, 0x4023ec
/* 004025c0 */  slti       $at, $v1, 0x1e
/* 004025c4 */  beqz       $at, 0x4025dc
/* 004025c8 */  addiu      $at, $zero, 0x15
/* 004025cc */  beq        $v1, $at, 0x4024fc
/* 004025d0 */  nop        
/* 004025d4 */  b          0x402668
/* 004025d8 */  nop        
/* 004025dc */  addiu      $at, $zero, 0x20
/* 004025e0 */  beq        $v1, $at, 0x40250c
/* 004025e4 */  nop        
/* 004025e8 */  b          0x402668
/* 004025ec */  nop        
/* 004025f0 */  addiu      $at, $zero, 0x67
/* 004025f4 */  beq        $v1, $at, 0x402144
/* 004025f8 */  slti       $at, $v1, 0x68
/* 004025fc */  beqz       $at, 0x402638
/* 00402600 */  addiu      $at, $zero, 0x65
/* 00402604 */  beq        $v1, $at, 0x40219c
/* 00402608 */  slti       $at, $v1, 0x66
/* 0040260c */  beqz       $at, 0x402624
/* 00402610 */  addiu      $at, $zero, 0x53
/* 00402614 */  beq        $v1, $at, 0x4021fc
/* 00402618 */  nop        
/* 0040261c */  b          0x402668
/* 00402620 */  nop        
/* 00402624 */  addiu      $at, $zero, 0x66
/* 00402628 */  beq        $v1, $at, 0x402174
/* 0040262c */  lh         $t0, 0x88($sp)
/* 00402630 */  b          0x402668
/* 00402634 */  nop        
/* 00402638 */  addiu      $at, $zero, 0x216
/* 0040263c */  beq        $v1, $at, 0x402370
/* 00402640 */  slti       $at, $v1, 0x217
/* 00402644 */  beqz       $at, 0x40265c
/* 00402648 */  addiu      $at, $zero, 0x210
/* 0040264c */  beq        $v1, $at, 0x4022ac
/* 00402650 */  addiu      $t9, $zero, 1
/* 00402654 */  b          0x402668
/* 00402658 */  nop        
/* 0040265c */  addiu      $at, $zero, 0x21c
/* 00402660 */  beq        $v1, $at, 0x402340
/* 00402664 */  nop        
/* 00402668 */  jal        0xf401200                                # qtest
/* 0040266c */  nop        
/* 00402670 */  bnez       $v0, 0x402104
/* 00402674 */  nop        
/* 00402678 */  lw         $t3, 0x94($sp)
/* 0040267c */  nop        
/* 00402680 */  bnez       $t3, 0x402b7c
/* 00402684 */  nop        
/* 00402688 */  lw         $t4, 0x70($sp)
/* 0040268c */  nop        
/* 00402690 */  bnez       $t4, 0x4020f4
/* 00402694 */  nop        
/* 00402698 */  lw         $t5, -0x7e88($gp)                        # .sdata @ 0x10003ee8
/* 0040269c */  nop        
/* 004026a0 */  beqz       $t5, 0x4026bc
/* 004026a4 */  lw         $t8, 0x90($sp)
/* 004026a8 */  lw         $t6, -0x7e84($gp)                        # .sdata @ 0x10003eec
/* 004026ac */  nop        
/* 004026b0 */  bnez       $t6, 0x4020f4
/* 004026b4 */  nop        
/* 004026b8 */  lw         $t8, 0x90($sp)
/* 004026bc */  nop        
/* 004026c0 */  bnez       $t8, 0x402700
/* 004026c4 */  lw         $t0, 0x90($sp)
/* 004026c8 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 004026cc */  addiu      $a0, $sp, 0x88
/* 004026d0 */  sw         $zero, 0x18($t9)
/* 004026d4 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004026d8 */  nop        
/* 004026dc */  sw         $zero, 0x1c($t7)
/* 004026e0 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 004026e4 */  nop        
/* 004026e8 */  sw         $zero, 0x20($t2)
/* 004026ec */  jal        0xf4011f0                                # qread
/* 004026f0 */  sw         $zero, 0x70($sp)
/* 004026f4 */  b          0x402110
/* 004026f8 */  sll        $v1, $v0, 0x10
/* 004026fc */  lw         $t0, 0x90($sp)
/* 00402700 */  nop        
/* 00402704 */  beqz       $t0, 0x4027a0
/* 00402708 */  nop        
/* 0040270c */  jal        0xf401140                                # getvaluator
/* 00402710 */  addiu      $a0, $zero, 0x10a
/* 00402714 */  move       $v1, $v0
/* 00402718 */  sw         $v1, 0x84($sp)
/* 0040271c */  jal        0xf401140                                # getvaluator
/* 00402720 */  addiu      $a0, $zero, 0x10b
/* 00402724 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00402728 */  lw         $v1, 0x84($sp)
/* 0040272c */  lw         $t3, 8($t1)
/* 00402730 */  lw         $t5, ($t1)
/* 00402734 */  subu       $v1, $v1, $t3
/* 00402738 */  mtc1       $v1, $f4
/* 0040273c */  mtc1       $t5, $f10
/* 00402740 */  cvt.s.w    $f6, $f4
/* 00402744 */  lw         $t4, 0xc($t1)
/* 00402748 */  cvt.d.w    $f16, $f10
/* 0040274c */  subu       $a0, $v0, $t4
/* 00402750 */  cvt.d.s    $f8, $f6
/* 00402754 */  nop        
/* 00402758 */  div.d      $f18, $f8, $f16
/* 0040275c */  mtc1       $a0, $f6
/* 00402760 */  nop        
/* 00402764 */  cvt.s.w    $f10, $f6
/* 00402768 */  cvt.d.s    $f8, $f10
/* 0040276c */  cvt.s.d    $f4, $f18
/* 00402770 */  swc1       $f4, 0x10($t1)
/* 00402774 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00402778 */  nop        
/* 0040277c */  lw         $t8, 4($t6)
/* 00402780 */  nop        
/* 00402784 */  mtc1       $t8, $f16
/* 00402788 */  nop        
/* 0040278c */  cvt.d.w    $f18, $f16
/* 00402790 */  nop        
/* 00402794 */  div.d      $f4, $f8, $f18
/* 00402798 */  cvt.s.d    $f6, $f4
/* 0040279c */  swc1       $f6, 0x14($t6)
/* 004027a0 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 004027a4 */  nop        
/* 004027a8 */  lw         $t7, 0xbc($t9)
/* 004027ac */  nop        
/* 004027b0 */  beqz       $t7, 0x4027c4
/* 004027b4 */  nop        
/* 004027b8 */  lw         $a0, 0xc4($t9)
/* 004027bc */  jal        0x403938                                 # gfo_set_material
/* 004027c0 */  nop        
/* 004027c4 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 004027c8 */  nop        
/* 004027cc */  lw         $v0, 0xc8($t2)
/* 004027d0 */  nop        
/* 004027d4 */  beqz       $v0, 0x402804
/* 004027d8 */  nop        
/* 004027dc */  lw         $t0, 0x5c($sp)
/* 004027e0 */  nop        
/* 004027e4 */  beqz       $t0, 0x402804
/* 004027e8 */  nop        
/* 004027ec */  jal        0x401c18
/* 004027f0 */  nop        
/* 004027f4 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 004027f8 */  nop        
/* 004027fc */  lw         $v0, 0xc8($t3)
/* 00402800 */  nop        
/* 00402804 */  beqz       $v0, 0x402840
/* 00402808 */  nop        
/* 0040280c */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00402810 */  nop        
/* 00402814 */  lw         $t5, 0x20($t4)
/* 00402818 */  nop        
/* 0040281c */  beqz       $t5, 0x402840
/* 00402820 */  nop        
/* 00402824 */  lw         $t1, 0x5c($sp)
/* 00402828 */  nop        
/* 0040282c */  bnez       $t1, 0x402840
/* 00402830 */  nop        
/* 00402834 */  lwc1       $f12, 0x10($t4)
/* 00402838 */  jal        0x401b88
/* 0040283c */  nop        
/* 00402840 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00402844 */  nop        
/* 00402848 */  lw         $t6, 0x48($t8)
/* 0040284c */  nop        
/* 00402850 */  beqz       $t6, 0x4028c0
/* 00402854 */  nop        
/* 00402858 */  jal        0xf402230                                # pushmatrix
/* 0040285c */  nop        
/* 00402860 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00402864 */  nop        
/* 00402868 */  lw         $t9, 0x94($t7)
/* 0040286c */  nop        
/* 00402870 */  beqz       $t9, 0x402888
/* 00402874 */  nop        
/* 00402878 */  jal        0x401ebc                                 # draw_scene_special
/* 0040287c */  nop        
/* 00402880 */  b          0x402894
/* 00402884 */  lw         $t2, 0x50($sp)
/* 00402888 */  jal        0x402fbc                                 # draw_scene_fly
/* 0040288c */  nop        
/* 00402890 */  lw         $t2, 0x50($sp)
/* 00402894 */  nop        
/* 00402898 */  beqz       $t2, 0x4028a8
/* 0040289c */  nop        
/* 004028a0 */  jal        0x401ce8                                 # save_image
/* 004028a4 */  sw         $zero, 0x50($sp)
/* 004028a8 */  jal        0x401504                                 # draw_display_list
/* 004028ac */  nop        
/* 004028b0 */  jal        0xf402228                                # popmatrix
/* 004028b4 */  nop        
/* 004028b8 */  b          0x402924
/* 004028bc */  lw         $v0, 0x60($sp)
/* 004028c0 */  jal        0xf402230                                # pushmatrix
/* 004028c4 */  nop        
/* 004028c8 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 004028cc */  nop        
/* 004028d0 */  lw         $t3, 0x94($t0)
/* 004028d4 */  nop        
/* 004028d8 */  beqz       $t3, 0x4028f0
/* 004028dc */  nop        
/* 004028e0 */  jal        0x401ebc                                 # draw_scene_special
/* 004028e4 */  nop        
/* 004028e8 */  b          0x4028fc
/* 004028ec */  lw         $t5, 0x50($sp)
/* 004028f0 */  jal        0x402bac
/* 004028f4 */  nop        
/* 004028f8 */  lw         $t5, 0x50($sp)
/* 004028fc */  nop        
/* 00402900 */  beqz       $t5, 0x402910
/* 00402904 */  nop        
/* 00402908 */  jal        0x401ce8                                 # save_image
/* 0040290c */  sw         $zero, 0x50($sp)
/* 00402910 */  jal        0x401504                                 # draw_display_list
/* 00402914 */  nop        
/* 00402918 */  jal        0xf402228                                # popmatrix
/* 0040291c */  nop        
/* 00402920 */  lw         $v0, 0x60($sp)
/* 00402924 */  sw         $zero, 0x60($sp)
/* 00402928 */  sltu       $v0, $zero, $v0
/* 0040292c */  beqz       $v0, 0x402a38
/* 00402930 */  nop        
/* 00402934 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00402938 */  nop        
/* 0040293c */  lw         $t4, 0x74($t1)
/* 00402940 */  nop        
/* 00402944 */  lbu        $t8, ($t4)
/* 00402948 */  nop        
/* 0040294c */  beqz       $t8, 0x402a38
/* 00402950 */  nop        
/* 00402954 */  cfc1       $t6, $31
/* 00402958 */  cfc1       $t6, $31
/* 0040295c */  lwc1       $f11, -0x7ff0($gp)                       # .lit8: 600
/* 00402960 */  lwc1       $f10, -0x7fec($gp)                       # .lit8 @ 0x10003d84
/* 00402964 */  ori        $at, $t6, 3
/* 00402968 */  xori       $at, $at, 2
/* 0040296c */  ctc1       $at, $31
/* 00402970 */  nop        
/* 00402974 */  cvt.w.d    $f16, $f10
/* 00402978 */  mfc1       $t7, $f16
/* 0040297c */  ctc1       $t6, $31
/* 00402980 */  jal        0xf402230                                # pushmatrix
/* 00402984 */  sw         $t7, 0x1c($sp)
/* 00402988 */  lui        $a0, 0x1000
/* 0040298c */  jal        0xf402190                                # font
/* 00402990 */  addiu      $a0, $a0, 0x278
/* 00402994 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00402998 */  mtc1       $zero, $f12
/* 0040299c */  lw         $t0, 4($t9)
/* 004029a0 */  lw         $t2, ($t9)
/* 004029a4 */  mtc1       $t0, $f18
/* 004029a8 */  mtc1       $t2, $f8
/* 004029ac */  cvt.s.w    $f18, $f18
/* 004029b0 */  mfc1       $a2, $f12
/* 004029b4 */  mfc1       $a3, $f18
/* 004029b8 */  jal        0xf402fa8                                # ortho2
/* 004029bc */  cvt.s.w    $f14, $f8
/* 004029c0 */  jal        0xf402508                                # zbuffer
/* 004029c4 */  move       $a0, $zero
/* 004029c8 */  jal        0xf401570                                # mmode
/* 004029cc */  addiu      $a0, $zero, 0x40
/* 004029d0 */  jal        0xf401fe0                                # gconfig
/* 004029d4 */  move       $a0, $zero
/* 004029d8 */  jal        0xf402120                                # gconfig
/* 004029dc */  nop        

# === update_view_angles ===
glabel update_view_angles
/* 004029e0 */  jal        0xf401fe0                                # gconfig
/* 004029e4 */  addiu      $a0, $zero, 1
/* 004029e8 */  addiu      $a0, $zero, 0xa
/* 004029ec */  jal        0xf402138                                # cmov2i
/* 004029f0 */  addiu      $a1, $zero, 0xa
/* 004029f4 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 004029f8 */  nop        
/* 004029fc */  lw         $a0, 0x74($t3)
/* 00402a00 */  jal        0xf402118                                # charstr
/* 00402a04 */  nop        
/* 00402a08 */  jal        0xf401570                                # mmode
/* 00402a0c */  addiu      $a0, $zero, 0x10
/* 00402a10 */  jal        0xf402508                                # zbuffer
/* 00402a14 */  addiu      $a0, $zero, 1
/* 00402a18 */  jal        0xf402228                                # popmatrix
/* 00402a1c */  nop        
/* 00402a20 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00402a24 */  lw         $a0, 0x1c($sp)
/* 00402a28 */  lw         $a1, 0x6c($t5)
/* 00402a2c */  lui        $a2, 0x3e80
/* 00402a30 */  jal        0xf402fa0                                # perspective
/* 00402a34 */  lui        $a3, 0x4170
/* 00402a38 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00402a3c */  nop        
/* 00402a40 */  lw         $t4, 0xc8($t1)
/* 00402a44 */  nop        
/* 00402a48 */  beqz       $t4, 0x402b38
/* 00402a4c */  nop        
/* 00402a50 */  cfc1       $t8, $31
/* 00402a54 */  cfc1       $t8, $31
/* 00402a58 */  lwc1       $f5, -0x7ff0($gp)                        # .lit8: 600
/* 00402a5c */  lwc1       $f4, -0x7fec($gp)                        # .lit8 @ 0x10003d84
/* 00402a60 */  ori        $at, $t8, 3
/* 00402a64 */  xori       $at, $at, 2
/* 00402a68 */  ctc1       $at, $31
/* 00402a6c */  lui        $a1, 0x1000
/* 00402a70 */  cvt.w.d    $f6, $f4
/* 00402a74 */  lw         $a2, 0xd8($t1)
/* 00402a78 */  mfc1       $t6, $f6
/* 00402a7c */  ctc1       $t8, $31
/* 00402a80 */  addiu      $a1, $a1, 0x6f4
/* 00402a84 */  addiu      $a0, $sp, 0x20
/* 00402a88 */  jal        0xf8012c0                                # sprintf
/* 00402a8c */  sw         $t6, 0x1c($sp)
/* 00402a90 */  jal        0xf402230                                # pushmatrix
/* 00402a94 */  nop        
/* 00402a98 */  lui        $a0, 0x1000
/* 00402a9c */  jal        0xf402190                                # font
/* 00402aa0 */  addiu      $a0, $a0, 0x278
/* 00402aa4 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00402aa8 */  mtc1       $zero, $f12
/* 00402aac */  lw         $t9, 4($t7)
/* 00402ab0 */  lw         $t2, ($t7)
/* 00402ab4 */  mtc1       $t9, $f16
/* 00402ab8 */  mtc1       $t2, $f10
/* 00402abc */  cvt.s.w    $f16, $f16
/* 00402ac0 */  addiu      $a2, $zero, 0
/* 00402ac4 */  mfc1       $a3, $f16
/* 00402ac8 */  jal        0xf402fa8                                # ortho2
/* 00402acc */  cvt.s.w    $f14, $f10
/* 00402ad0 */  jal        0xf402508                                # zbuffer
/* 00402ad4 */  move       $a0, $zero
/* 00402ad8 */  jal        0xf402098                                # color
/* 00402adc */  addiu      $a0, $zero, -0x100
/* 00402ae0 */  jal        0xf401250                                # strwidth
/* 00402ae4 */  addiu      $a0, $gp, -0x7d68
/* 00402ae8 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00402aec */  sll        $t5, $v0, 2
/* 00402af0 */  lw         $t3, ($t0)
/* 00402af4 */  addu       $t5, $t5, $v0
/* 00402af8 */  sll        $t5, $t5, 1
/* 00402afc */  addiu      $a1, $zero, 0xa
/* 00402b00 */  jal        0xf402138                                # cmov2i
/* 00402b04 */  subu       $a0, $t3, $t5
/* 00402b08 */  jal        0xf402118                                # charstr
/* 00402b0c */  addiu      $a0, $sp, 0x20
/* 00402b10 */  jal        0xf402508                                # zbuffer
/* 00402b14 */  addiu      $a0, $zero, 1
/* 00402b18 */  jal        0xf402228                                # popmatrix
/* 00402b1c */  nop        
/* 00402b20 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00402b24 */  lw         $a0, 0x1c($sp)
/* 00402b28 */  lw         $a1, 0x6c($t4)
/* 00402b2c */  lui        $a2, 0x3e80
/* 00402b30 */  jal        0xf402fa0                                # perspective
/* 00402b34 */  lui        $a3, 0x4170
/* 00402b38 */  jal        0xf402288                                # swapbuffers
/* 00402b3c */  nop        
/* 00402b40 */  lw         $t1, -0x7e94($gp)                        # .sdata @ 0x10003edc
/* 00402b44 */  nop        
/* 00402b48 */  beqz       $t1, 0x402b6c
/* 00402b4c */  move       $a0, $zero
/* 00402b50 */  lw         $t8, 0x68($sp)
/* 00402b54 */  nop        
/* 00402b58 */  addiu      $t6, $t8, 1
/* 00402b5c */  sw         $t6, 0x68($sp)
/* 00402b60 */  jal        0x401a28                                 # save_frame
/* 00402b64 */  move       $a0, $t8
/* 00402b68 */  move       $a0, $zero
/* 00402b6c */  jal        0xf402588                                # czclear
/* 00402b70 */  move       $a1, $zero
/* 00402b74 */  b          0x4020f4
/* 00402b78 */  nop        
/* 00402b7c */  jal        0xf401570                                # mmode
/* 00402b80 */  addiu      $a0, $zero, 0x40
/* 00402b84 */  jal        0xf401fe0                                # gconfig
/* 00402b88 */  move       $a0, $zero
/* 00402b8c */  jal        0xf402120                                # gconfig
/* 00402b90 */  nop        
/* 00402b94 */  jal        0xf401570                                # mmode
/* 00402b98 */  addiu      $a0, $zero, 0x10
/* 00402b9c */  lw         $ra, 0x14($sp)
/* 00402ba0 */  addiu      $sp, $sp, 0x98
/* 00402ba4 */  jr         $ra
/* 00402ba8 */  nop        
/* 00402bac */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00402bb0 */  addiu      $sp, $sp, -0x18
/* 00402bb4 */  sw         $ra, 0x14($sp)
/* 00402bb8 */  lw         $t7, 0x20($t6)
/* 00402bbc */  nop        
/* 00402bc0 */  beqz       $t7, 0x402bd8
/* 00402bc4 */  nop        
/* 00402bc8 */  lwc1       $f15, -0x7fd0($gp)                       # .lit8: 360
/* 00402bcc */  lwc1       $f14, -0x7fcc($gp)                       # .lit8 @ 0x10003da4
/* 00402bd0 */  b          0x402d70
/* 00402bd4 */  nop        
/* 00402bd8 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00402bdc */  nop        
/* 00402be0 */  lw         $t9, 0x70($t8)
/* 00402be4 */  nop        
/* 00402be8 */  beqz       $t9, 0x402c00
/* 00402bec */  nop        
/* 00402bf0 */  lwc1       $f15, -0x7fd0($gp)                       # .lit8: 360
/* 00402bf4 */  lwc1       $f14, -0x7fcc($gp)                       # .lit8 @ 0x10003da4
/* 00402bf8 */  b          0x402d70
/* 00402bfc */  nop        
/* 00402c00 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00402c04 */  nop        
/* 00402c08 */  lw         $t1, 0x1c($t0)
/* 00402c0c */  nop        
/* 00402c10 */  beqz       $t1, 0x402c74
/* 00402c14 */  nop        
/* 00402c18 */  lwc1       $f4, 0x14($t0)
/* 00402c1c */  lwc1       $f3, -0x7fe0($gp)                        # .lit8: 0.5
/* 00402c20 */  lwc1       $f2, -0x7fdc($gp)                        # .lit8 @ 0x10003d94
/* 00402c24 */  cvt.d.s    $f6, $f4
/* 00402c28 */  lwc1       $f15, -0x7fd0($gp)                       # .lit8: 360
/* 00402c2c */  lwc1       $f14, -0x7fcc($gp)                       # .lit8 @ 0x10003da4
/* 00402c30 */  sub.d      $f8, $f6, $f2
/* 00402c34 */  mul.d      $f10, $f8, $f14
/* 00402c38 */  cvt.s.d    $f16, $f10
/* 00402c3c */  swc1       $f16, 0x24($t0)
/* 00402c40 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00402c44 */  nop        
/* 00402c48 */  lwc1       $f18, 0x10($t2)
/* 00402c4c */  nop        
/* 00402c50 */  cvt.d.s    $f4, $f18
/* 00402c54 */  sub.d      $f6, $f4, $f2
/* 00402c58 */  mul.d      $f8, $f6, $f14
/* 00402c5c */  cvt.s.d    $f10, $f8
/* 00402c60 */  swc1       $f10, 0x28($t2)
/* 00402c64 */  lwc1       $f12, -0x7fc4($gp)                       # .lit8 @ 0x10003dac
/* 00402c68 */  lwc1       $f13, -0x7fc8($gp)                       # .lit8: 10
/* 00402c6c */  b          0x402ce4
/* 00402c70 */  nop        
/* 00402c74 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00402c78 */  lwc1       $f3, -0x7fe0($gp)                        # .lit8: 0.5
/* 00402c7c */  lwc1       $f4, 0x14($t3)
/* 00402c80 */  lwc1       $f2, -0x7fdc($gp)                        # .lit8 @ 0x10003d94
/* 00402c84 */  cvt.d.s    $f6, $f4
/* 00402c88 */  lwc1       $f13, -0x7fc8($gp)                       # .lit8: 10
/* 00402c8c */  lwc1       $f12, -0x7fc4($gp)                       # .lit8 @ 0x10003dac
/* 00402c90 */  sub.d      $f8, $f6, $f2
/* 00402c94 */  lwc1       $f16, 0x24($t3)
/* 00402c98 */  mul.d      $f10, $f8, $f12
/* 00402c9c */  cvt.d.s    $f18, $f16
/* 00402ca0 */  add.d      $f16, $f18, $f10
/* 00402ca4 */  cvt.s.d    $f4, $f16
/* 00402ca8 */  swc1       $f4, 0x24($t3)
/* 00402cac */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00402cb0 */  nop        
/* 00402cb4 */  lwc1       $f18, 0x10($t4)
/* 00402cb8 */  lwc1       $f6, 0x28($t4)
/* 00402cbc */  cvt.d.s    $f10, $f18
/* 00402cc0 */  sub.d      $f16, $f10, $f2
/* 00402cc4 */  mul.d      $f4, $f16, $f12
/* 00402cc8 */  cvt.d.s    $f8, $f6
/* 00402ccc */  add.d      $f6, $f8, $f4
/* 00402cd0 */  cvt.s.d    $f18, $f6
/* 00402cd4 */  swc1       $f18, 0x28($t4)
/* 00402cd8 */  lwc1       $f14, -0x7fcc($gp)                       # .lit8 @ 0x10003da4
/* 00402cdc */  lwc1       $f15, -0x7fd0($gp)                       # .lit8: 360
/* 00402ce0 */  nop        
/* 00402ce4 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00402ce8 */  nop        
/* 00402cec */  lw         $t6, 0x18($t5)
/* 00402cf0 */  nop        
/* 00402cf4 */  beqz       $t6, 0x402d70
/* 00402cf8 */  nop        
/* 00402cfc */  lwc1       $f10, 0x10($t5)
/* 00402d00 */  mtc1       $zero, $f8
/* 00402d04 */  cvt.d.s    $f16, $f10
/* 00402d08 */  sub.d      $f0, $f16, $f2
/* 00402d0c */  mtc1       $zero, $f9
/* 00402d10 */  nop        
/* 00402d14 */  c.lt.d     $f0, $f8
/* 00402d18 */  nop        
/* 00402d1c */  bc1t       0x402d2c
/* 00402d20 */  nop        
/* 00402d24 */  b          0x402d30
/* 00402d28 */  mov.d      $f2, $f0
/* 00402d2c */  neg.d      $f2, $f0
/* 00402d30 */  mul.d      $f4, $f2, $f12
/* 00402d34 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00402d38 */  cvt.s.d    $f6, $f4
/* 00402d3c */  swc1       $f6, 0x30($t7)
/* 00402d40 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00402d44 */  lwc1       $f16, -0x7fbc($gp)                       # .lit8 @ 0x10003db4
/* 00402d48 */  lwc1       $f18, 0x30($t8)
/* 00402d4c */  lwc1       $f17, -0x7fc0($gp)                       # .lit8: 0.01
/* 00402d50 */  cvt.d.s    $f10, $f18
/* 00402d54 */  c.lt.d     $f10, $f16
/* 00402d58 */  nop        
/* 00402d5c */  bc1f       0x402d70
/* 00402d60 */  nop        
/* 00402d64 */  lwc1       $f8, -0x7ed4($gp)                        # .lit4: 0.01
/* 00402d68 */  nop        
/* 00402d6c */  swc1       $f8, 0x30($t8)
/* 00402d70 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00402d74 */  nop        
/* 00402d78 */  lwc1       $f4, 0x24($t9)
/* 00402d7c */  nop        
/* 00402d80 */  cvt.d.s    $f0, $f4
/* 00402d84 */  c.le.d     $f0, $f14
/* 00402d88 */  nop        
/* 00402d8c */  bc1f       0x402da0
/* 00402d90 */  nop        
/* 00402d94 */  lwc1       $f12, -0x7ed0($gp)                       # .lit4: 360
/* 00402d98 */  b          0x402db8
/* 00402d9c */  nop        
/* 00402da0 */  lwc1       $f12, -0x7ed0($gp)                       # .lit4: 360
/* 00402da4 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00402da8 */  cvt.d.s    $f6, $f12
/* 00402dac */  sub.d      $f18, $f0, $f6
/* 00402db0 */  cvt.s.d    $f10, $f18
/* 00402db4 */  swc1       $f10, 0x24($t1)
/* 00402db8 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00402dbc */  nop        
/* 00402dc0 */  lwc1       $f16, 0x28($t0)
/* 00402dc4 */  nop        
/* 00402dc8 */  cvt.d.s    $f0, $f16
/* 00402dcc */  c.le.d     $f0, $f14
/* 00402dd0 */  nop        
/* 00402dd4 */  bc1t       0x402dec
/* 00402dd8 */  nop        
/* 00402ddc */  cvt.d.s    $f8, $f12
/* 00402de0 */  sub.d      $f4, $f0, $f8
/* 00402de4 */  cvt.s.d    $f6, $f4
/* 00402de8 */  swc1       $f6, 0x28($t0)
/* 00402dec */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00402df0 */  lwc1       $f3, -0x7fb8($gp)                        # .lit8: -360
/* 00402df4 */  lwc1       $f18, 0x24($t2)
/* 00402df8 */  lwc1       $f2, -0x7fb4($gp)                        # .lit8 @ 0x10003dbc
/* 00402dfc */  cvt.d.s    $f0, $f18
/* 00402e00 */  c.lt.d     $f0, $f2
/* 00402e04 */  nop        
/* 00402e08 */  bc1f       0x402e20
/* 00402e0c */  nop        
/* 00402e10 */  cvt.d.s    $f10, $f12
/* 00402e14 */  add.d      $f16, $f0, $f10
/* 00402e18 */  cvt.s.d    $f8, $f16
/* 00402e1c */  swc1       $f8, 0x24($t2)
/* 00402e20 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00402e24 */  nop        
/* 00402e28 */  lwc1       $f4, 0x28($t3)
/* 00402e2c */  nop        
/* 00402e30 */  cvt.d.s    $f0, $f4
/* 00402e34 */  c.lt.d     $f0, $f2
/* 00402e38 */  nop        
/* 00402e3c */  bc1f       0x402e54
/* 00402e40 */  nop        
/* 00402e44 */  cvt.d.s    $f6, $f12
/* 00402e48 */  add.d      $f18, $f0, $f6
/* 00402e4c */  cvt.s.d    $f10, $f18
/* 00402e50 */  swc1       $f10, 0x28($t3)
/* 00402e54 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00402e58 */  addiu      $a1, $zero, 0x78
/* 00402e5c */  lwc1       $f12, 0x24($t4)
/* 00402e60 */  jal        0xf402558                                # rot
/* 00402e64 */  neg.s      $f12, $f12
/* 00402e68 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00402e6c */  addiu      $a1, $zero, 0x79
/* 00402e70 */  lwc1       $f12, 0x28($t6)
/* 00402e74 */  jal        0xf402558                                # rot
/* 00402e78 */  nop        
/* 00402e7c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00402e80 */  nop        
/* 00402e84 */  lwc1       $f12, 0x30($t5)
/* 00402e88 */  nop        
/* 00402e8c */  mfc1       $a2, $f12
/* 00402e90 */  jal        0xf402278                                # scale
/* 00402e94 */  mov.s      $f14, $f12
/* 00402e98 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00402e9c */  nop        
/* 00402ea0 */  lw         $t8, 0x78($t7)
/* 00402ea4 */  nop        
/* 00402ea8 */  beqz       $t8, 0x402ec4
/* 00402eac */  nop        
/* 00402eb0 */  lwc1       $f12, 0x7c($t7)
/* 00402eb4 */  nop        
/* 00402eb8 */  mfc1       $a2, $f12
/* 00402ebc */  jal        0xf402278                                # scale
/* 00402ec0 */  mov.s      $f14, $f12
/* 00402ec4 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00402ec8 */  nop        
/* 00402ecc */  lw         $t1, 0x80($t9)
/* 00402ed0 */  nop        
/* 00402ed4 */  beqz       $t1, 0x402ef4
/* 00402ed8 */  lw         $ra, 0x14($sp)
/* 00402edc */  lwc1       $f12, 0x84($t9)
/* 00402ee0 */  lwc1       $f14, 0x88($t9)
/* 00402ee4 */  lw         $a2, 0x8c($t9)
/* 00402ee8 */  jal        0xf402298                                # translate
/* 00402eec */  nop        
/* 00402ef0 */  lw         $ra, 0x14($sp)
/* 00402ef4 */  addiu      $sp, $sp, 0x18
/* 00402ef8 */  jr         $ra
/* 00402efc */  nop        

# === render_frame_no_zbuf ===
glabel render_frame_no_zbuf
/* 00402f00 */  addiu      $sp, $sp, -0x18
/* 00402f04 */  sw         $ra, 0x14($sp)
/* 00402f08 */  jal        0xf402098                                # color
/* 00402f0c */  move       $a0, $zero
/* 00402f10 */  jal        0xf402120                                # gconfig
/* 00402f14 */  nop        
/* 00402f18 */  jal        0xf402518                                # backface
/* 00402f1c */  nop        
/* 00402f20 */  jal        0xf402230                                # pushmatrix
/* 00402f24 */  nop        
/* 00402f28 */  jal        0x402fbc                                 # draw_scene_fly
/* 00402f2c */  nop        
/* 00402f30 */  jal        0x401504                                 # draw_display_list
/* 00402f34 */  nop        
/* 00402f38 */  jal        0xf402228                                # popmatrix
/* 00402f3c */  nop        
/* 00402f40 */  jal        0xf402288                                # swapbuffers
/* 00402f44 */  nop        
/* 00402f48 */  lw         $ra, 0x14($sp)
/* 00402f4c */  addiu      $sp, $sp, 0x18
/* 00402f50 */  jr         $ra
/* 00402f54 */  nop        
/* 00402f58 */  nop        

# === init_fly_state ===
glabel init_fly_state
/* 00402f5c */  nop        
/* 00402f60 */  lwc1       $f0, -0x7ec8($gp)                        # .lit4: 100
/* 00402f64 */  lwc1       $f7, -0x7fa8($gp)                        # .lit8: 1000
/* 00402f68 */  lwc1       $f6, -0x7fa4($gp)                        # .lit8 @ 0x10003dcc
/* 00402f6c */  cvt.d.s    $f4, $f0
/* 00402f70 */  nop        
/* 00402f74 */  div.d      $f8, $f4, $f6
/* 00402f78 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00402f7c */  swc1       $f0, -0x7b28($gp)                        # far_dist
/* 00402f80 */  mtc1       $zero, $f2
/* 00402f84 */  addiu      $t7, $zero, 0x258
/* 00402f88 */  addiu      $t9, $zero, 3
/* 00402f8c */  cvt.s.d    $f10, $f8
/* 00402f90 */  swc1       $f10, 0x4c($t6)
/* 00402f94 */  lwc1       $f16, -0x7ec4($gp)                       # .lit4: 0.3
/* 00402f98 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00402f9c */  swc1       $f2, -0x7b58($gp)                        # cam_x
/* 00402fa0 */  swc1       $f2, -0x7b54($gp)                        # cam_y
/* 00402fa4 */  swc1       $f2, -0x7b50($gp)                        # cam_z
/* 00402fa8 */  swc1       $f16, -0x7b5c($gp)                       # speed_drag
/* 00402fac */  sw         $t7, 0x50($t8)
/* 00402fb0 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00402fb4 */  jr         $ra
/* 00402fb8 */  sw         $t9, 0x54($t0)

# === draw_scene_fly ===
glabel draw_scene_fly
/* 00402fbc */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00402fc0 */  addiu      $sp, $sp, -0x20
/* 00402fc4 */  sw         $ra, 0x14($sp)
/* 00402fc8 */  lw         $t7, 0x18($t6)
/* 00402fcc */  nop        
/* 00402fd0 */  bnez       $t7, 0x402fe4
/* 00402fd4 */  nop        
/* 00402fd8 */  lwc1       $f2, -0x7b60($gp)                        # fly_speed
/* 00402fdc */  b          0x403000
/* 00402fe0 */  nop        
/* 00402fe4 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00402fe8 */  lwc1       $f2, -0x7b60($gp)                        # fly_speed
/* 00402fec */  lwc1       $f6, 0x4c($t8)
/* 00402ff0 */  cvt.d.s    $f4, $f2
/* 00402ff4 */  cvt.d.s    $f8, $f6
/* 00402ff8 */  add.d      $f10, $f4, $f8
/* 00402ffc */  cvt.s.d    $f2, $f10
/* 00403000 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00403004 */  nop        
/* 00403008 */  lw         $t0, 0x1c($t9)
/* 0040300c */  nop        
/* 00403010 */  beqz       $t0, 0x40302c
/* 00403014 */  nop        
/* 00403018 */  lwc1       $f18, 0x4c($t9)
/* 0040301c */  cvt.d.s    $f16, $f2
/* 00403020 */  cvt.d.s    $f6, $f18
/* 00403024 */  sub.d      $f4, $f16, $f6
/* 00403028 */  cvt.s.d    $f2, $f4
/* 0040302c */  lwc1       $f8, -0x7b5c($gp)                        # speed_drag
/* 00403030 */  cvt.d.s    $f0, $f2
/* 00403034 */  cvt.d.s    $f10, $f8
/* 00403038 */  mul.d      $f18, $f0, $f10
/* 0040303c */  addiu      $a0, $zero, 0x10a
/* 00403040 */  sub.d      $f16, $f0, $f18
/* 00403044 */  cvt.s.d    $f2, $f16
/* 00403048 */  jal        0xf401140                                # getvaluator
/* 0040304c */  swc1       $f2, -0x7b60($gp)                        # fly_speed
/* 00403050 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00403054 */  addiu      $a0, $zero, 0x10b
/* 00403058 */  lw         $t2, 8($t1)
/* 0040305c */  nop        
/* 00403060 */  subu       $t3, $v0, $t2
/* 00403064 */  jal        0xf401140                                # getvaluator
/* 00403068 */  sw         $t3, -0x7b40($gp)                        # mouse_rx
/* 0040306c */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00403070 */  lw         $t6, -0x7b40($gp)                        # mouse_rx
/* 00403074 */  lw         $v1, ($t4)
/* 00403078 */  lwc1       $f11, -0x7fa0($gp)                       # .lit8: 15
/* 0040307c */  bgez       $v1, 0x403088
/* 00403080 */  move       $at, $v1
/* 00403084 */  addiu      $at, $at, 1
/* 00403088 */  sra        $t7, $at, 1
/* 0040308c */  subu       $t8, $t6, $t7
/* 00403090 */  mtc1       $t8, $f6
/* 00403094 */  lwc1       $f10, -0x7f9c($gp)                       # .lit8 @ 0x10003dd4
/* 00403098 */  cvt.s.w    $f4, $f6
/* 0040309c */  mtc1       $v1, $f16
/* 004030a0 */  lw         $t5, 0xc($t4)
/* 004030a4 */  cvt.d.s    $f8, $f4
/* 004030a8 */  mul.d      $f18, $f8, $f10
/* 004030ac */  cvt.d.w    $f6, $f16
/* 004030b0 */  lwc1       $f8, -0x7b20($gp)                        # yaw_accum
/* 004030b4 */  subu       $a1, $v0, $t5
/* 004030b8 */  div.d      $f4, $f18, $f6
/* 004030bc */  cvt.d.s    $f10, $f8
/* 004030c0 */  cvt.s.d    $f0, $f4
/* 004030c4 */  cvt.d.s    $f16, $f0
/* 004030c8 */  add.d      $f18, $f10, $f16
/* 004030cc */  lwc1       $f16, -0x7f94($gp)                       # .lit8 @ 0x10003ddc
/* 004030d0 */  cvt.s.d    $f6, $f18
/* 004030d4 */  lwc1       $f17, -0x7f98($gp)                       # .lit8: 126
/* 004030d8 */  swc1       $f6, -0x7b20($gp)                        # yaw_accum
/* 004030dc */  lw         $a0, 4($t4)
/* 004030e0 */  sw         $a1, -0x7b3c($gp)                        # mouse_ry
/* 004030e4 */  nop        
/* 004030e8 */  bgez       $a0, 0x4030f4
/* 004030ec */  move       $at, $a0
/* 004030f0 */  addiu      $at, $at, 1
/* 004030f4 */  sra        $t0, $at, 1
/* 004030f8 */  subu       $t9, $a1, $t0
/* 004030fc */  mtc1       $t9, $f4
/* 00403100 */  mtc1       $a0, $f6
/* 00403104 */  cvt.s.w    $f8, $f4
/* 00403108 */  cvt.d.s    $f10, $f8
/* 0040310c */  mul.d      $f18, $f10, $f16
/* 00403110 */  cvt.d.w    $f4, $f6
/* 00403114 */  lwc1       $f16, -0x7f8c($gp)                       # .lit8 @ 0x10003de4
/* 00403118 */  lwc1       $f17, -0x7f90($gp)                       # .lit8: 3.1415
/* 0040311c */  div.d      $f8, $f18, $f4
/* 00403120 */  lwc1       $f18, -0x7f84($gp)                       # .lit8 @ 0x10003dec
/* 00403124 */  lwc1       $f19, -0x7f88($gp)                       # .lit8: 180
/* 00403128 */  cvt.s.d    $f14, $f8
/* 0040312c */  cvt.d.s    $f10, $f14
/* 00403130 */  mul.d      $f6, $f10, $f16
/* 00403134 */  swc1       $f14, -0x7b24($gp)                       # pitch_val
/* 00403138 */  jal        0x40d178                                 # sin
/* 0040313c */  div.d      $f12, $f6, $f18
/* 00403140 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00403144 */  nop        
/* 00403148 */  lw         $v0, 0x54($t1)
/* 0040314c */  b          0x403200
/* 00403150 */  addiu      $at, $zero, 1
/* 00403154 */  lwc1       $f2, -0x7b60($gp)                        # fly_speed
/* 00403158 */  cvt.s.d    $f4, $f0
/* 0040315c */  cvt.d.s    $f8, $f4
/* 00403160 */  cvt.d.s    $f10, $f2
/* 00403164 */  mul.d      $f16, $f8, $f10
/* 00403168 */  lwc1       $f4, -0x7b58($gp)                        # cam_x
/* 0040316c */  nop        
/* 00403170 */  cvt.d.s    $f8, $f4
/* 00403174 */  cvt.s.d    $f6, $f16
/* 00403178 */  cvt.d.s    $f18, $f6
/* 0040317c */  sub.d      $f10, $f8, $f18
/* 00403180 */  cvt.s.d    $f16, $f10
/* 00403184 */  b          0x403218
/* 00403188 */  swc1       $f16, -0x7b58($gp)                       # cam_x
/* 0040318c */  lwc1       $f2, -0x7b60($gp)                        # fly_speed
/* 00403190 */  cvt.s.d    $f6, $f0
/* 00403194 */  cvt.d.s    $f4, $f6
/* 00403198 */  cvt.d.s    $f8, $f2
/* 0040319c */  mul.d      $f18, $f4, $f8
/* 004031a0 */  lwc1       $f6, -0x7b54($gp)                        # cam_y
/* 004031a4 */  nop        
/* 004031a8 */  cvt.d.s    $f4, $f6
/* 004031ac */  cvt.s.d    $f10, $f18
/* 004031b0 */  cvt.d.s    $f16, $f10
/* 004031b4 */  sub.d      $f8, $f4, $f16
/* 004031b8 */  cvt.s.d    $f18, $f8
/* 004031bc */  b          0x403218
/* 004031c0 */  swc1       $f18, -0x7b54($gp)                       # cam_y
/* 004031c4 */  lwc1       $f2, -0x7b60($gp)                        # fly_speed
/* 004031c8 */  cvt.s.d    $f10, $f0
/* 004031cc */  cvt.d.s    $f6, $f10
/* 004031d0 */  cvt.d.s    $f4, $f2
/* 004031d4 */  mul.d      $f16, $f6, $f4
/* 004031d8 */  lwc1       $f10, -0x7b50($gp)                       # cam_z
/* 004031dc */  nop        
/* 004031e0 */  cvt.d.s    $f6, $f10
/* 004031e4 */  cvt.s.d    $f8, $f16
/* 004031e8 */  cvt.d.s    $f18, $f8
/* 004031ec */  sub.d      $f4, $f6, $f18
/* 004031f0 */  cvt.s.d    $f16, $f4
/* 004031f4 */  b          0x403218
/* 004031f8 */  swc1       $f16, -0x7b50($gp)                       # cam_z
/* 004031fc */  addiu      $at, $zero, 1
/* 00403200 */  beq        $v0, $at, 0x403154
/* 00403204 */  addiu      $at, $zero, 2
/* 00403208 */  beq        $v0, $at, 0x40318c
/* 0040320c */  addiu      $at, $zero, 3
/* 00403210 */  beq        $v0, $at, 0x4031c4
/* 00403214 */  nop        
/* 00403218 */  lwc1       $f8, -0x7b28($gp)                        # far_dist
/* 0040321c */  lwc1       $f10, -0x7ec0($gp)                       # .lit4: 1.5
/* 00403220 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00403224 */  mul.s      $f6, $f8, $f10
/* 00403228 */  lui        $a2, 0x3dcc
/* 0040322c */  lw         $a0, 0x50($t2)
/* 00403230 */  lw         $a1, 0x6c($t2)
/* 00403234 */  mfc1       $a3, $f6
/* 00403238 */  jal        0xf402fa0                                # perspective
/* 0040323c */  ori        $a2, $a2, 0xcccd
/* 00403240 */  lwc1       $f18, -0x7b20($gp)                       # yaw_accum
/* 00403244 */  lwc1       $f17, -0x7f90($gp)                       # .lit8: 3.1415
/* 00403248 */  lwc1       $f16, -0x7f8c($gp)                       # .lit8 @ 0x10003de4
/* 0040324c */  cvt.d.s    $f4, $f18
/* 00403250 */  mul.d      $f8, $f4, $f16
/* 00403254 */  lwc1       $f11, -0x7f88($gp)                       # .lit8: 180
/* 00403258 */  lwc1       $f10, -0x7f84($gp)                       # .lit8 @ 0x10003dec
/* 0040325c */  jal        0x40d178                                 # sin
/* 00403260 */  div.d      $f12, $f8, $f10
/* 00403264 */  lwc1       $f2, -0x7b60($gp)                        # fly_speed
/* 00403268 */  cvt.s.d    $f6, $f0
/* 0040326c */  lwc1       $f10, -0x7b20($gp)                       # yaw_accum
/* 00403270 */  cvt.d.s    $f18, $f6
/* 00403274 */  cvt.d.s    $f4, $f2
/* 00403278 */  mul.d      $f16, $f18, $f4
/* 0040327c */  cvt.d.s    $f6, $f10
/* 00403280 */  lwc1       $f18, -0x7f8c($gp)                       # .lit8 @ 0x10003de4
/* 00403284 */  lwc1       $f19, -0x7f90($gp)                       # .lit8: 3.1415
/* 00403288 */  nop        
/* 0040328c */  mul.d      $f4, $f6, $f18
/* 00403290 */  cvt.s.d    $f8, $f16
/* 00403294 */  lwc1       $f16, -0x7f84($gp)                       # .lit8 @ 0x10003dec
/* 00403298 */  lwc1       $f17, -0x7f88($gp)                       # .lit8: 180
/* 0040329c */  swc1       $f8, 0x1c($sp)
/* 004032a0 */  jal        0x40d120                                 # cos
/* 004032a4 */  div.d      $f12, $f4, $f16
/* 004032a8 */  lwc1       $f2, -0x7b60($gp)                        # fly_speed
/* 004032ac */  cvt.s.d    $f8, $f0
/* 004032b0 */  lwc1       $f14, -0x7b24($gp)                       # pitch_val
/* 004032b4 */  cvt.d.s    $f10, $f8
/* 004032b8 */  cvt.d.s    $f6, $f2
/* 004032bc */  mul.d      $f18, $f10, $f6
/* 004032c0 */  mov.s      $f12, $f14
/* 004032c4 */  addiu      $a1, $zero, 0x78
/* 004032c8 */  cvt.s.d    $f4, $f18
/* 004032cc */  jal        0xf402558                                # rot
/* 004032d0 */  swc1       $f4, 0x18($sp)
/* 004032d4 */  lwc1       $f12, -0x7b20($gp)                       # yaw_accum
/* 004032d8 */  jal        0xf402558                                # rot
/* 004032dc */  addiu      $a1, $zero, 0x79
/* 004032e0 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 004032e4 */  nop        
/* 004032e8 */  lw         $v0, 0x54($t3)
/* 004032ec */  b          0x4033c4
/* 004032f0 */  addiu      $at, $zero, 1
/* 004032f4 */  addiu      $a0, $zero, 0x384
/* 004032f8 */  jal        0xf402270                                # rotate
/* 004032fc */  addiu      $a1, $zero, 0x7a
/* 00403300 */  lwc1       $f16, -0x7b54($gp)                       # cam_y
/* 00403304 */  lwc1       $f10, 0x1c($sp)
/* 00403308 */  cvt.d.s    $f8, $f16
/* 0040330c */  cvt.d.s    $f6, $f10
/* 00403310 */  sub.d      $f18, $f8, $f6
/* 00403314 */  lwc1       $f8, 0x18($sp)
/* 00403318 */  lwc1       $f16, -0x7b50($gp)                       # cam_z
/* 0040331c */  cvt.d.s    $f6, $f8
/* 00403320 */  cvt.s.d    $f4, $f18
/* 00403324 */  cvt.d.s    $f10, $f16
/* 00403328 */  sub.d      $f18, $f10, $f6
/* 0040332c */  swc1       $f4, -0x7b54($gp)                        # cam_y
/* 00403330 */  cvt.s.d    $f4, $f18
/* 00403334 */  b          0x4033dc
/* 00403338 */  swc1       $f4, -0x7b50($gp)                        # cam_z
/* 0040333c */  lwc1       $f16, -0x7b58($gp)                       # cam_x
/* 00403340 */  lwc1       $f10, 0x1c($sp)
/* 00403344 */  cvt.d.s    $f8, $f16
/* 00403348 */  cvt.d.s    $f6, $f10
/* 0040334c */  add.d      $f18, $f8, $f6
/* 00403350 */  lwc1       $f8, 0x18($sp)
/* 00403354 */  lwc1       $f16, -0x7b50($gp)                       # cam_z
/* 00403358 */  cvt.d.s    $f6, $f8
/* 0040335c */  cvt.s.d    $f4, $f18
/* 00403360 */  cvt.d.s    $f10, $f16
/* 00403364 */  sub.d      $f18, $f10, $f6
/* 00403368 */  swc1       $f4, -0x7b58($gp)                        # cam_x
/* 0040336c */  cvt.s.d    $f4, $f18
/* 00403370 */  b          0x4033dc
/* 00403374 */  swc1       $f4, -0x7b50($gp)                        # cam_z
/* 00403378 */  addiu      $a0, $zero, -0x384
/* 0040337c */  jal        0xf402270                                # rotate
/* 00403380 */  addiu      $a1, $zero, 0x78
/* 00403384 */  lwc1       $f16, -0x7b58($gp)                       # cam_x
/* 00403388 */  lwc1       $f10, 0x1c($sp)
/* 0040338c */  cvt.d.s    $f8, $f16
/* 00403390 */  cvt.d.s    $f6, $f10
/* 00403394 */  add.d      $f18, $f8, $f6
/* 00403398 */  lwc1       $f8, 0x18($sp)
/* 0040339c */  lwc1       $f16, -0x7b54($gp)                       # cam_y
/* 004033a0 */  cvt.d.s    $f6, $f8
/* 004033a4 */  cvt.s.d    $f4, $f18
/* 004033a8 */  cvt.d.s    $f10, $f16
/* 004033ac */  add.d      $f18, $f10, $f6
/* 004033b0 */  swc1       $f4, -0x7b58($gp)                        # cam_x
/* 004033b4 */  cvt.s.d    $f4, $f18
/* 004033b8 */  b          0x4033dc
/* 004033bc */  swc1       $f4, -0x7b54($gp)                        # cam_y
/* 004033c0 */  addiu      $at, $zero, 1
/* 004033c4 */  beq        $v0, $at, 0x4032f4
/* 004033c8 */  addiu      $at, $zero, 2
/* 004033cc */  beq        $v0, $at, 0x40333c
/* 004033d0 */  addiu      $at, $zero, 3
/* 004033d4 */  beq        $v0, $at, 0x403378
/* 004033d8 */  nop        
/* 004033dc */  lwc1       $f16, -0x7b50($gp)                       # cam_z
/* 004033e0 */  lwc1       $f12, -0x7b58($gp)                       # cam_x
/* 004033e4 */  lwc1       $f14, -0x7b54($gp)                       # cam_y
/* 004033e8 */  neg.s      $f8, $f16
/* 004033ec */  mfc1       $a2, $f8
/* 004033f0 */  neg.s      $f12, $f12
/* 004033f4 */  jal        0xf402298                                # translate
/* 004033f8 */  neg.s      $f14, $f14
/* 004033fc */  lwc1       $f10, -0x7b58($gp)                       # cam_x
/* 00403400 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00403404 */  nop        
/* 00403408 */  swc1       $f10, 0x58($t5)
/* 0040340c */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00403410 */  lwc1       $f6, -0x7b54($gp)                        # cam_y
/* 00403414 */  nop        
/* 00403418 */  swc1       $f6, 0x5c($t6)
/* 0040341c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00403420 */  lwc1       $f18, -0x7b50($gp)                       # cam_z
/* 00403424 */  nop        
/* 00403428 */  swc1       $f18, 0x60($t7)
/* 0040342c */  lw         $ra, 0x14($sp)
/* 00403430 */  addiu      $sp, $sp, 0x20
/* 00403434 */  jr         $ra
/* 00403438 */  nop        
/* 0040343c */  nop        

# === setup_materials ===
glabel setup_materials
/* 00403440 */  addiu      $sp, $sp, -0x18
/* 00403444 */  sw         $ra, 0x14($sp)
/* 00403448 */  lui        $a3, 0x1000
/* 0040344c */  addiu      $a3, $a3, 0x760
/* 00403450 */  move       $a0, $zero
/* 00403454 */  addiu      $a1, $zero, 1
/* 00403458 */  jal        0xf4015d0                                # lmdef
/* 0040345c */  addiu      $a2, $zero, 0x3c
/* 00403460 */  lui        $a3, 0x1000
/* 00403464 */  addiu      $a3, $a3, 0x728
/* 00403468 */  addiu      $a0, $zero, 0x64
/* 0040346c */  addiu      $a1, $zero, 1
/* 00403470 */  jal        0xf4015d0                                # lmdef
/* 00403474 */  addiu      $a2, $zero, 0x38
/* 00403478 */  lui        $a3, 0x1000
/* 0040347c */  addiu      $a3, $a3, 0x700
/* 00403480 */  addiu      $a0, $zero, 0xc8
/* 00403484 */  addiu      $a1, $zero, 1
/* 00403488 */  jal        0xf4015d0                                # lmdef
/* 0040348c */  addiu      $a2, $zero, 0x28
/* 00403490 */  addiu      $a0, $zero, 0x3e8
/* 00403494 */  jal        0xf402570                                # lsetdepth
/* 00403498 */  addiu      $a1, $zero, 1
/* 0040349c */  addiu      $a0, $zero, 0x44c
/* 004034a0 */  jal        0xf402570                                # lsetdepth
/* 004034a4 */  addiu      $a1, $zero, 1
/* 004034a8 */  lw         $ra, 0x14($sp)
/* 004034ac */  addiu      $sp, $sp, 0x18
/* 004034b0 */  jr         $ra
/* 004034b4 */  nop        

# === bind_material ===
glabel bind_material
/* 004034b8 */  addiu      $sp, $sp, -0x18
/* 004034bc */  beqz       $a0, 0x4034cc
/* 004034c0 */  sw         $ra, 0x14($sp)
/* 004034c4 */  b          0x4034d0
/* 004034c8 */  addiu      $a1, $zero, 1
/* 004034cc */  move       $a1, $zero
/* 004034d0 */  jal        0xf402570                                # lsetdepth
/* 004034d4 */  addiu      $a0, $zero, 0x4b0
/* 004034d8 */  lw         $ra, 0x14($sp)
/* 004034dc */  addiu      $sp, $sp, 0x18
/* 004034e0 */  jr         $ra
/* 004034e4 */  nop        
/* 004034e8 */  nop        
/* 004034ec */  nop        

# === init_window_and_gl ===
glabel init_window_and_gl
/* 004034f0 */  addiu      $sp, $sp, -0x18
/* 004034f4 */  sw         $ra, 0x14($sp)
/* 004034f8 */  jal        0xf801208                                # free
/* 004034fc */  addiu      $a0, $zero, 0x7d0
/* 00403500 */  bnez       $v0, 0x403514
/* 00403504 */  sw         $v0, -0x7b10($gp)                        # .sbss @ 0x10004260
/* 00403508 */  lui        $a0, 0x1000
/* 0040350c */  jal        0x4092d4
/* 00403510 */  addiu      $a0, $a0, 0x94c
/* 00403514 */  sw         $zero, -0x7b0c($gp)                      # .sbss @ 0x10004264
/* 00403518 */  jal        0xf801208                                # free
/* 0040351c */  addiu      $a0, $zero, 0x3e8
/* 00403520 */  bnez       $v0, 0x403534
/* 00403524 */  sw         $v0, -0x7b08($gp)                        # .sbss @ 0x10004268
/* 00403528 */  lui        $a0, 0x1000
/* 0040352c */  jal        0x4092d4
/* 00403530 */  addiu      $a0, $a0, 0x95c
/* 00403534 */  lw         $t6, -0x7b08($gp)                        # .sbss @ 0x10004268
/* 00403538 */  addiu      $a0, $zero, 0x640
/* 0040353c */  jal        0xf801208                                # free
/* 00403540 */  sw         $t6, -0x7b04($gp)                        # .sbss @ 0x1000426c
/* 00403544 */  bnez       $v0, 0x403558
/* 00403548 */  sw         $v0, -0x7b00($gp)                        # .sbss @ 0x10004270
/* 0040354c */  lui        $a0, 0x1000
/* 00403550 */  jal        0x4092d4
/* 00403554 */  addiu      $a0, $a0, 0x96c
/* 00403558 */  lw         $t7, -0x7b00($gp)                        # .sbss @ 0x10004270
/* 0040355c */  lw         $ra, 0x14($sp)
/* 00403560 */  sw         $t7, -0x7afc($gp)                        # .sbss @ 0x10004274
/* 00403564 */  addiu      $t8, $zero, 1
/* 00403568 */  addiu      $t9, $zero, 1
/* 0040356c */  addiu      $t0, $zero, 1
/* 00403570 */  sw         $t8, -0x7af8($gp)                        # .sbss @ 0x10004278
/* 00403574 */  sw         $t9, -0x7af4($gp)                        # .sbss @ 0x1000427c
/* 00403578 */  sw         $t0, -0x7af0($gp)                        # .sbss @ 0x10004280
/* 0040357c */  jr         $ra
/* 00403580 */  addiu      $sp, $sp, 0x18

# === load_material_file ===
glabel load_material_file
/* 00403584 */  lw         $t6, -0x7d34($gp)                        # .sdata @ 0x1000403c
/* 00403588 */  addiu      $sp, $sp, -0x30
/* 0040358c */  sw         $s0, 0x18($sp)
/* 00403590 */  sw         $ra, 0x1c($sp)
/* 00403594 */  move       $s0, $a0
/* 00403598 */  bnez       $t6, 0x4035d8
/* 0040359c */  sw         $a1, 0x34($sp)
/* 004035a0 */  lui        $a0, 0x1000
/* 004035a4 */  jal        0x4043bc                                 # gfo_alloc_entity
/* 004035a8 */  addiu      $a0, $a0, 0x97c
/* 004035ac */  lui        $a0, 0x1000
/* 004035b0 */  sw         $v0, -0x7adc($gp)                        # .sbss @ 0x10004294
/* 004035b4 */  jal        0x4043bc                                 # gfo_alloc_entity
/* 004035b8 */  addiu      $a0, $a0, 0x988
/* 004035bc */  lui        $a0, 0x1000
/* 004035c0 */  sw         $v0, -0x7ad8($gp)                        # .sbss @ 0x10004298
/* 004035c4 */  jal        0x4043bc                                 # gfo_alloc_entity
/* 004035c8 */  addiu      $a0, $a0, 0x994
/* 004035cc */  addiu      $t7, $zero, 1
/* 004035d0 */  sw         $v0, -0x7ad4($gp)                        # .sbss @ 0x1000429c
/* 004035d4 */  sw         $t7, -0x7d34($gp)                        # .sdata @ 0x1000403c
/* 004035d8 */  lw         $a1, 0x34($sp)
/* 004035dc */  jal        0x40406c
/* 004035e0 */  move       $a0, $s0
/* 004035e4 */  jal        0x4040d0                                 # gfo_parse_scope
/* 004035e8 */  addiu      $a0, $sp, 0x2c
/* 004035ec */  beqz       $v0, 0x403674
/* 004035f0 */  lw         $ra, 0x1c($sp)
/* 004035f4 */  lui        $s0, 0x1000
/* 004035f8 */  addiu      $s0, $s0, 0x9a0
/* 004035fc */  lw         $t8, 0x2c($sp)
/* 00403600 */  nop        
/* 00403604 */  lw         $v0, 4($t8)
/* 00403608 */  nop        
/* 0040360c */  beqz       $v0, 0x403658
/* 00403610 */  nop        
/* 00403614 */  lw         $t9, -0x7adc($gp)                        # .sbss @ 0x10004294
/* 00403618 */  nop        
/* 0040361c */  beq        $t9, $v0, 0x403648
/* 00403620 */  lw         $a0, 0x2c($sp)
/* 00403624 */  lw         $t0, -0x7ad8($gp)                        # .sbss @ 0x10004298
/* 00403628 */  nop        
/* 0040362c */  beq        $t0, $v0, 0x403648
/* 00403630 */  lw         $a0, 0x2c($sp)
/* 00403634 */  lw         $t1, -0x7ad4($gp)                        # .sbss @ 0x1000429c
/* 00403638 */  nop        
/* 0040363c */  bne        $t1, $v0, 0x403658
/* 00403640 */  nop        
/* 00403644 */  lw         $a0, 0x2c($sp)
/* 00403648 */  jal        0x403bf8                                 # gfo_parse_vertex
/* 0040364c */  nop        
/* 00403650 */  b          0x403660
/* 00403654 */  nop        
/* 00403658 */  jal        0x403ffc                                 # gfo_parse_entity
/* 0040365c */  move       $a0, $s0
/* 00403660 */  jal        0x4040d0                                 # gfo_parse_scope
/* 00403664 */  addiu      $a0, $sp, 0x2c
/* 00403668 */  bnez       $v0, 0x403600
/* 0040366c */  lw         $t8, 0x2c($sp)
/* 00403670 */  lw         $ra, 0x1c($sp)
/* 00403674 */  lw         $s0, 0x18($sp)
/* 00403678 */  addiu      $sp, $sp, 0x30
/* 0040367c */  jr         $ra
/* 00403680 */  addiu      $v0, $zero, 1

# === setup_menu ===
glabel setup_menu
/* 00403684 */  lw         $t6, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 00403688 */  addiu      $sp, $sp, -0x58
/* 0040368c */  sw         $s2, 0x18($sp)
/* 00403690 */  sw         $ra, 0x1c($sp)
/* 00403694 */  blez       $t6, 0x40380c
/* 00403698 */  move       $s2, $zero
/* 0040369c */  sw         $s5, 0x2c($sp)
/* 004036a0 */  sw         $s6, 0x28($sp)
/* 004036a4 */  sw         $fp, 0x20($sp)
/* 004036a8 */  sw         $s1, 0x38($sp)
/* 004036ac */  sw         $s3, 0x34($sp)
/* 004036b0 */  sw         $s4, 0x30($sp)
/* 004036b4 */  lui        $fp, 0x1000
/* 004036b8 */  lui        $s6, 0x1000
/* 004036bc */  lui        $s5, 0x1000
/* 004036c0 */  sw         $s7, 0x24($sp)
/* 004036c4 */  addiu      $s7, $zero, 1
/* 004036c8 */  addiu      $s5, $s5, 0x36b4
/* 004036cc */  addiu      $s6, $s6, 0xa18
/* 004036d0 */  addiu      $fp, $fp, 0x9f4
/* 004036d4 */  addiu      $s4, $zero, 0xc8
/* 004036d8 */  addiu      $s3, $zero, 0x64
/* 004036dc */  move       $s1, $zero
/* 004036e0 */  sw         $s0, 0x3c($sp)
/* 004036e4 */  lw         $t7, -0x7b10($gp)                        # .sbss @ 0x10004260
/* 004036e8 */  nop        
/* 004036ec */  addu       $v0, $t7, $s1
/* 004036f0 */  lw         $v1, ($v0)
/* 004036f4 */  move       $s0, $v0
/* 004036f8 */  beqz       $v1, 0x403700
/* 004036fc */  nop        
/* 00403700 */  lw         $a0, ($s0)
/* 00403704 */  lw         $a1, 0x10($s0)
/* 00403708 */  lw         $a2, 0xc($s0)
/* 0040370c */  lw         $a3, 8($s0)
/* 00403710 */  jal        0xf4015d0                                # lmdef
/* 00403714 */  nop        
/* 00403718 */  lw         $a1, ($s0)
/* 0040371c */  b          0x4037b4
/* 00403720 */  move       $v1, $a1
/* 00403724 */  lw         $a1, 0x10($s0)
/* 00403728 */  nop        
/* 0040372c */  slti       $at, $a1, 9
/* 00403730 */  beqz       $at, 0x403748
/* 00403734 */  nop        
/* 00403738 */  jal        0xf402570                                # lsetdepth
/* 0040373c */  addiu      $a0, $a1, 0x44b
/* 00403740 */  b          0x4037d4
/* 00403744 */  nop        
/* 00403748 */  lui        $a1, 0x1000
/* 0040374c */  addiu      $a1, $a1, 0x9cc
/* 00403750 */  jal        0xf801150                                # fclose
/* 00403754 */  move       $a0, $s5
/* 00403758 */  b          0x4037d4
/* 0040375c */  nop        
/* 00403760 */  lw         $a1, 0x10($s0)
/* 00403764 */  nop        
/* 00403768 */  beq        $s7, $a1, 0x403794
/* 0040376c */  nop        
/* 00403770 */  lui        $a2, 0x1000
/* 00403774 */  addiu      $a2, $a2, 0xa08
/* 00403778 */  move       $a0, $s5
/* 0040377c */  jal        0xf801150                                # fclose
/* 00403780 */  move       $a1, $fp
/* 00403784 */  jal        0x40d3c0
/* 00403788 */  move       $a0, $s7
/* 0040378c */  lw         $a1, 0x10($s0)
/* 00403790 */  nop        
/* 00403794 */  jal        0xf402570                                # lsetdepth
/* 00403798 */  addiu      $a0, $zero, 0x4b0
/* 0040379c */  b          0x4037d4
/* 004037a0 */  nop        
/* 004037a4 */  jal        0x4092d4
/* 004037a8 */  move       $a0, $s6
/* 004037ac */  b          0x4037d4
/* 004037b0 */  nop        
/* 004037b4 */  beqz       $v1, 0x4037d4
/* 004037b8 */  nop        
/* 004037bc */  beq        $v1, $s3, 0x403724
/* 004037c0 */  nop        
/* 004037c4 */  beq        $v1, $s4, 0x403760
/* 004037c8 */  nop        
/* 004037cc */  b          0x4037a4
/* 004037d0 */  nop        
/* 004037d4 */  lw         $t8, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 004037d8 */  addiu      $s2, $s2, 1
/* 004037dc */  slt        $at, $s2, $t8
/* 004037e0 */  bnez       $at, 0x4036e4
/* 004037e4 */  addiu      $s1, $s1, 0x14
/* 004037e8 */  lw         $s0, 0x3c($sp)
/* 004037ec */  lw         $s1, 0x38($sp)
/* 004037f0 */  lw         $s3, 0x34($sp)
/* 004037f4 */  lw         $s4, 0x30($sp)
/* 004037f8 */  lw         $s5, 0x2c($sp)
/* 004037fc */  lw         $s6, 0x28($sp)
/* 00403800 */  lw         $s7, 0x24($sp)
/* 00403804 */  lw         $fp, 0x20($sp)
/* 00403808 */  nop        
/* 0040380c */  lw         $ra, 0x1c($sp)
/* 00403810 */  lw         $s2, 0x18($sp)
/* 00403814 */  jr         $ra
/* 00403818 */  addiu      $sp, $sp, 0x58

# === gfo_new_scope ===
glabel gfo_new_scope
/* 0040381c */  addiu      $sp, $sp, -0x38
/* 00403820 */  lw         $t6, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 00403824 */  sw         $s3, 0x18($sp)
/* 00403828 */  sw         $s2, 0x14($sp)
/* 0040382c */  move       $s3, $a0
/* 00403830 */  sw         $ra, 0x1c($sp)
/* 00403834 */  blez       $t6, 0x4038ac
/* 00403838 */  move       $s2, $zero
/* 0040383c */  sw         $s0, 0x24($sp)
/* 00403840 */  move       $s0, $zero
/* 00403844 */  sw         $s1, 0x20($sp)
/* 00403848 */  lw         $t7, -0x7b10($gp)                        # .sbss @ 0x10004260
/* 0040384c */  nop        
/* 00403850 */  addu       $v0, $t7, $s0
/* 00403854 */  lw         $t8, ($v0)
/* 00403858 */  move       $s1, $v0
/* 0040385c */  bnez       $t8, 0x40388c
/* 00403860 */  nop        
/* 00403864 */  lw         $a1, 4($s1)
/* 00403868 */  jal        0xf8012e8                                # fwrite
/* 0040386c */  move       $a0, $s3
/* 00403870 */  bnez       $v0, 0x40388c
/* 00403874 */  nop        
/* 00403878 */  move       $v0, $s1
/* 0040387c */  lw         $s1, 0x20($sp)
/* 00403880 */  lw         $s0, 0x24($sp)
/* 00403884 */  b          0x4038b4
/* 00403888 */  lw         $ra, 0x1c($sp)
/* 0040388c */  lw         $t9, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 00403890 */  addiu      $s2, $s2, 1
/* 00403894 */  slt        $at, $s2, $t9
/* 00403898 */  bnez       $at, 0x403848
/* 0040389c */  addiu      $s0, $s0, 0x14
/* 004038a0 */  lw         $s0, 0x24($sp)
/* 004038a4 */  lw         $s1, 0x20($sp)
/* 004038a8 */  nop        
/* 004038ac */  move       $v0, $zero
/* 004038b0 */  lw         $ra, 0x1c($sp)
/* 004038b4 */  lw         $s2, 0x14($sp)
/* 004038b8 */  lw         $s3, 0x18($sp)
/* 004038bc */  jr         $ra
/* 004038c0 */  addiu      $sp, $sp, 0x38
/* 004038c4 */  lw         $t6, -0x7af8($gp)                        # .sbss @ 0x10004278
/* 004038c8 */  nop        
/* 004038cc */  slt        $at, $a0, $t6
/* 004038d0 */  beqz       $at, 0x403930
/* 004038d4 */  move       $v0, $zero
/* 004038d8 */  lw         $v1, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 004038dc */  move       $v0, $zero
/* 004038e0 */  blez       $v1, 0x403924
/* 004038e4 */  nop        
/* 004038e8 */  lw         $a1, -0x7b10($gp)                        # .sbss @ 0x10004260
/* 004038ec */  nop        
/* 004038f0 */  lw         $t7, ($a1)
/* 004038f4 */  nop        
/* 004038f8 */  bnez       $t7, 0x403918
/* 004038fc */  nop        
/* 00403900 */  lw         $t8, 0x10($a1)
/* 00403904 */  nop        
/* 00403908 */  bne        $a0, $t8, 0x40391c
/* 0040390c */  addiu      $v0, $v0, 1
/* 00403910 */  jr         $ra
/* 00403914 */  move       $v0, $a1
/* 00403918 */  addiu      $v0, $v0, 1
/* 0040391c */  bne        $v0, $v1, 0x4038f0
/* 00403920 */  addiu      $a1, $a1, 0x14
/* 00403924 */  jr         $ra
/* 00403928 */  move       $v0, $zero
/* 0040392c */  move       $v0, $zero
/* 00403930 */  jr         $ra
/* 00403934 */  nop        

# === gfo_set_material ===
glabel gfo_set_material
/* 00403938 */  addiu      $sp, $sp, -0x18
/* 0040393c */  sw         $ra, 0x14($sp)
/* 00403940 */  move       $v1, $a0
/* 00403944 */  lw         $a1, 0x10($v1)
/* 00403948 */  jal        0xf402570                                # lsetdepth
/* 0040394c */  addiu      $a0, $zero, 0x3e8
/* 00403950 */  lw         $ra, 0x14($sp)
/* 00403954 */  addiu      $sp, $sp, 0x18
/* 00403958 */  jr         $ra
/* 0040395c */  nop        

# === gfo_parse_keyword ===
glabel gfo_parse_keyword
/* 00403960 */  addiu      $sp, $sp, -0x20
/* 00403964 */  lw         $t6, -0x7b04($gp)                        # .sbss @ 0x1000426c
/* 00403968 */  sw         $a0, 0x20($sp)
/* 0040396c */  sw         $ra, 0x14($sp)
/* 00403970 */  lw         $a0, 0x20($sp)
/* 00403974 */  jal        0xf801308                                # close
/* 00403978 */  sw         $t6, 0x1c($sp)
/* 0040397c */  lw         $t8, -0x7b04($gp)                        # .sbss @ 0x1000426c
/* 00403980 */  lw         $t9, -0x7b08($gp)                        # .sbss @ 0x10004268
/* 00403984 */  addiu      $t1, $zero, 0x3e7
/* 00403988 */  subu       $t0, $t8, $t9
/* 0040398c */  subu       $t2, $t1, $t0
/* 00403990 */  addiu      $t7, $v0, 1
/* 00403994 */  slt        $at, $v0, $t2
/* 00403998 */  bnez       $at, 0x4039c4
/* 0040399c */  sw         $t7, 0x18($sp)
/* 004039a0 */  lui        $a0, 0x1000
/* 004039a4 */  lui        $a1, 0x1000
/* 004039a8 */  lui        $a2, 0x1000
/* 004039ac */  addiu      $a2, $a2, 0xa48
/* 004039b0 */  addiu      $a1, $a1, 0xa34
/* 004039b4 */  jal        0xf801150                                # fclose
/* 004039b8 */  addiu      $a0, $a0, 0x36b4
/* 004039bc */  jal        0x40d3c0
/* 004039c0 */  addiu      $a0, $zero, 1
/* 004039c4 */  lw         $a0, 0x1c($sp)
/* 004039c8 */  lw         $a1, 0x20($sp)
/* 004039cc */  lw         $a2, 0x18($sp)
/* 004039d0 */  jal        0xf801320                                # read
/* 004039d4 */  nop        
/* 004039d8 */  lw         $t3, -0x7b04($gp)                        # .sbss @ 0x1000426c
/* 004039dc */  lw         $t4, 0x18($sp)
/* 004039e0 */  lw         $ra, 0x14($sp)
/* 004039e4 */  lw         $v0, 0x1c($sp)
/* 004039e8 */  addu       $t5, $t3, $t4
/* 004039ec */  sw         $t5, -0x7b04($gp)                        # .sbss @ 0x1000426c
/* 004039f0 */  jr         $ra
/* 004039f4 */  addiu      $sp, $sp, 0x20
/* 004039f8 */  lw         $a0, -0x7afc($gp)                        # .sbss @ 0x10004274
/* 004039fc */  lw         $t6, -0x7b00($gp)                        # .sbss @ 0x10004270
/* 00403a00 */  addiu      $sp, $sp, -0x18
/* 00403a04 */  subu       $t7, $a0, $t6
/* 00403a08 */  bgez       $t7, 0x403a14
/* 00403a0c */  move       $at, $t7
/* 00403a10 */  addiu      $at, $at, 3
/* 00403a14 */  sra        $t8, $at, 2
/* 00403a18 */  slti       $at, $t8, 0x190
/* 00403a1c */  sw         $ra, 0x14($sp)
/* 00403a20 */  bnez       $at, 0x403a54
/* 00403a24 */  swc1       $f12, 0x18($sp)
/* 00403a28 */  lui        $a0, 0x1000
/* 00403a2c */  lui        $a1, 0x1000
/* 00403a30 */  lui        $a2, 0x1000
/* 00403a34 */  addiu      $a2, $a2, 0xa68
/* 00403a38 */  addiu      $a1, $a1, 0xa54
/* 00403a3c */  jal        0xf801150                                # fclose
/* 00403a40 */  addiu      $a0, $a0, 0x36b4
/* 00403a44 */  jal        0x40d3c0
/* 00403a48 */  addiu      $a0, $zero, 1
/* 00403a4c */  lw         $a0, -0x7afc($gp)                        # .sbss @ 0x10004274
/* 00403a50 */  nop        
/* 00403a54 */  lwc1       $f4, 0x18($sp)
/* 00403a58 */  move       $v1, $a0
/* 00403a5c */  swc1       $f4, ($a0)
/* 00403a60 */  lw         $ra, 0x14($sp)
/* 00403a64 */  addiu      $a0, $a0, 4
/* 00403a68 */  sw         $a0, -0x7afc($gp)                        # .sbss @ 0x10004274
/* 00403a6c */  addiu      $sp, $sp, 0x18
/* 00403a70 */  jr         $ra
/* 00403a74 */  move       $v0, $v1

# === gfo_parse_polygon ===
glabel gfo_parse_polygon
/* 00403a78 */  lw         $t6, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 00403a7c */  addiu      $sp, $sp, -0x20
/* 00403a80 */  slti       $at, $t6, 0x64
/* 00403a84 */  sw         $ra, 0x14($sp)
/* 00403a88 */  sw         $a0, 0x20($sp)
/* 00403a8c */  bnez       $at, 0x403ac8
/* 00403a90 */  move       $a3, $a1
/* 00403a94 */  lui        $a0, 0x1000
/* 00403a98 */  lui        $a1, 0x1000
/* 00403a9c */  lui        $a2, 0x1000
/* 00403aa0 */  addiu      $a2, $a2, 0xa88
/* 00403aa4 */  addiu      $a1, $a1, 0xa74
/* 00403aa8 */  addiu      $a0, $a0, 0x36b4
/* 00403aac */  jal        0xf801150                                # fclose
/* 00403ab0 */  sw         $a3, 0x24($sp)
/* 00403ab4 */  lw         $a3, 0x24($sp)
/* 00403ab8 */  jal        0x40d3c0
/* 00403abc */  addiu      $a0, $zero, 1
/* 00403ac0 */  lw         $a3, 0x24($sp)
/* 00403ac4 */  nop        
/* 00403ac8 */  lw         $t8, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 00403acc */  lw         $t7, -0x7b10($gp)                        # .sbss @ 0x10004260
/* 00403ad0 */  sll        $t9, $t8, 2
/* 00403ad4 */  addu       $t9, $t9, $t8
/* 00403ad8 */  sll        $t9, $t9, 2
/* 00403adc */  lw         $a0, 0x20($sp)
/* 00403ae0 */  addu       $v1, $t7, $t9
/* 00403ae4 */  sw         $v1, 0x1c($sp)
/* 00403ae8 */  jal        0x403960                                 # gfo_parse_keyword
/* 00403aec */  sw         $a3, 0x24($sp)
/* 00403af0 */  lw         $v1, 0x1c($sp)
/* 00403af4 */  lw         $a3, 0x24($sp)
/* 00403af8 */  sw         $v0, 4($v1)
/* 00403afc */  sw         $zero, 8($v1)
/* 00403b00 */  sw         $zero, 0xc($v1)
/* 00403b04 */  beqz       $a3, 0x403b28
/* 00403b08 */  sw         $a3, ($v1)
/* 00403b0c */  addiu      $at, $zero, 0x64
/* 00403b10 */  beq        $a3, $at, 0x403b40
/* 00403b14 */  addiu      $at, $zero, 0xc8
/* 00403b18 */  beq        $a3, $at, 0x403b58
/* 00403b1c */  nop        
/* 00403b20 */  b          0x403b64
/* 00403b24 */  nop        
/* 00403b28 */  lw         $v0, -0x7af8($gp)                        # .sbss @ 0x10004278
/* 00403b2c */  nop        
/* 00403b30 */  sw         $v0, 0x10($v1)
/* 00403b34 */  addiu      $v0, $v0, 1
/* 00403b38 */  b          0x403b80
/* 00403b3c */  sw         $v0, -0x7af8($gp)                        # .sbss @ 0x10004278
/* 00403b40 */  lw         $v0, -0x7af4($gp)                        # .sbss @ 0x1000427c
/* 00403b44 */  nop        
/* 00403b48 */  sw         $v0, 0x10($v1)
/* 00403b4c */  addiu      $v0, $v0, 1
/* 00403b50 */  b          0x403b80
/* 00403b54 */  sw         $v0, -0x7af4($gp)                        # .sbss @ 0x1000427c
/* 00403b58 */  lw         $t0, -0x7af0($gp)                        # .sbss @ 0x10004280
/* 00403b5c */  b          0x403b80
/* 00403b60 */  sw         $t0, 0x10($v1)
/* 00403b64 */  lui        $a0, 0x1000
/* 00403b68 */  addiu      $a0, $a0, 0xa94
/* 00403b6c */  move       $a1, $a3
/* 00403b70 */  jal        0x4092d4
/* 00403b74 */  sw         $v1, 0x1c($sp)
/* 00403b78 */  lw         $v1, 0x1c($sp)
/* 00403b7c */  nop        
/* 00403b80 */  lw         $t1, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 00403b84 */  lw         $ra, 0x14($sp)
/* 00403b88 */  addiu      $t2, $t1, 1
/* 00403b8c */  sw         $t2, -0x7b0c($gp)                        # .sbss @ 0x10004264
/* 00403b90 */  addiu      $sp, $sp, 0x20
/* 00403b94 */  jr         $ra
/* 00403b98 */  move       $v0, $v1

# === gfo_parse_instance ===
glabel gfo_parse_instance
/* 00403b9c */  addiu      $sp, $sp, -0x18
/* 00403ba0 */  sw         $ra, 0x14($sp)
/* 00403ba4 */  lw         $t6, 0xc($a0)
/* 00403ba8 */  mtc1       $a1, $f12
/* 00403bac */  bnez       $t6, 0x403bc8
/* 00403bb0 */  nop        
/* 00403bb4 */  jal        0x4039f8
/* 00403bb8 */  sw         $a0, 0x18($sp)
/* 00403bbc */  lw         $a0, 0x18($sp)
/* 00403bc0 */  b          0x403bd8
/* 00403bc4 */  sw         $v0, 8($a0)
/* 00403bc8 */  jal        0x4039f8
/* 00403bcc */  sw         $a0, 0x18($sp)
/* 00403bd0 */  lw         $a0, 0x18($sp)
/* 00403bd4 */  nop        
/* 00403bd8 */  lw         $t7, 0xc($a0)
/* 00403bdc */  nop        
/* 00403be0 */  addiu      $t8, $t7, 1
/* 00403be4 */  sw         $t8, 0xc($a0)
/* 00403be8 */  lw         $ra, 0x14($sp)
/* 00403bec */  addiu      $sp, $sp, 0x18
/* 00403bf0 */  jr         $ra
/* 00403bf4 */  nop        

# === gfo_parse_vertex ===
glabel gfo_parse_vertex
/* 00403bf8 */  lw         $t6, -0x7acc($gp)                        # .sbss @ 0x100042a4
/* 00403bfc */  addiu      $sp, $sp, -0x30
/* 00403c00 */  sw         $ra, 0x1c($sp)
/* 00403c04 */  sw         $s0, 0x18($sp)
/* 00403c08 */  bnez       $t6, 0x403c24
/* 00403c0c */  sw         $a0, 0x30($sp)
/* 00403c10 */  jal        0x4043bc                                 # gfo_alloc_entity
/* 00403c14 */  addiu      $a0, $gp, -0x7d20
/* 00403c18 */  addiu      $t7, $zero, 1
/* 00403c1c */  sw         $v0, -0x7ad0($gp)                        # .sbss @ 0x100042a0
/* 00403c20 */  sw         $t7, -0x7acc($gp)                        # .sbss @ 0x100042a4
/* 00403c24 */  lw         $t8, 0x30($sp)
/* 00403c28 */  lwc1       $f9, -0x7fe0($gp)                        # .lit8: 0.5
/* 00403c2c */  lw         $t9, 4($t8)
/* 00403c30 */  lwc1       $f8, -0x7fdc($gp)                        # .lit8 @ 0x10003d94
/* 00403c34 */  lwc1       $f4, 4($t9)
/* 00403c38 */  addiu      $a0, $sp, 0x30
/* 00403c3c */  cvt.d.s    $f6, $f4
/* 00403c40 */  add.d      $f10, $f6, $f8
/* 00403c44 */  cfc1       $t0, $31
/* 00403c48 */  cfc1       $t0, $31
/* 00403c4c */  nop        
/* 00403c50 */  ori        $at, $t0, 3
/* 00403c54 */  xori       $at, $at, 2
/* 00403c58 */  ctc1       $at, $31
/* 00403c5c */  nop        
/* 00403c60 */  cvt.w.d    $f16, $f10
/* 00403c64 */  mfc1       $t1, $f16
/* 00403c68 */  ctc1       $t0, $31
/* 00403c6c */  jal        0x4040d0                                 # gfo_parse_scope
/* 00403c70 */  sw         $t1, 0x24($sp)
/* 00403c74 */  bnez       $v0, 0x403c8c
/* 00403c78 */  lw         $t2, 0x30($sp)
/* 00403c7c */  lui        $a0, 0x1000
/* 00403c80 */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403c84 */  addiu      $a0, $a0, 0xaac
/* 00403c88 */  lw         $t2, 0x30($sp)
/* 00403c8c */  lw         $a1, 0x24($sp)
/* 00403c90 */  lw         $a0, ($t2)
/* 00403c94 */  jal        0x403a78                                 # gfo_parse_polygon
/* 00403c98 */  nop        
/* 00403c9c */  move       $s0, $v0
/* 00403ca0 */  jal        0x404370                                 # gfo_parse_material
/* 00403ca4 */  addiu      $a0, $sp, 0x30
/* 00403ca8 */  bnez       $v0, 0x403cc0
/* 00403cac */  lw         $t3, 0x30($sp)
/* 00403cb0 */  lui        $a0, 0x1000
/* 00403cb4 */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403cb8 */  addiu      $a0, $a0, 0xac8
/* 00403cbc */  lw         $t3, 0x30($sp)
/* 00403cc0 */  nop        
/* 00403cc4 */  lw         $v0, 4($t3)
/* 00403cc8 */  nop        
/* 00403ccc */  beqz       $v0, 0x403d30
/* 00403cd0 */  nop        
/* 00403cd4 */  lw         $t4, -0x7ad0($gp)                        # .sbss @ 0x100042a0
/* 00403cd8 */  nop        
/* 00403cdc */  beq        $t4, $v0, 0x403d30
/* 00403ce0 */  nop        
/* 00403ce4 */  jal        0x403e28                                 # gfo_parse_line
/* 00403ce8 */  move       $a0, $s0
/* 00403cec */  jal        0x404370                                 # gfo_parse_material
/* 00403cf0 */  addiu      $a0, $sp, 0x30
/* 00403cf4 */  bnez       $v0, 0x403d0c
/* 00403cf8 */  lw         $t5, 0x30($sp)
/* 00403cfc */  lui        $a0, 0x1000
/* 00403d00 */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403d04 */  addiu      $a0, $a0, 0xae4
/* 00403d08 */  lw         $t5, 0x30($sp)
/* 00403d0c */  nop        
/* 00403d10 */  lw         $v0, 4($t5)
/* 00403d14 */  nop        
/* 00403d18 */  beqz       $v0, 0x403d30
/* 00403d1c */  nop        
/* 00403d20 */  lw         $t6, -0x7ad0($gp)                        # .sbss @ 0x100042a0
/* 00403d24 */  nop        
/* 00403d28 */  bne        $t6, $v0, 0x403ce4
/* 00403d2c */  nop        
/* 00403d30 */  bnez       $v0, 0x403d44
/* 00403d34 */  nop        
/* 00403d38 */  lui        $a0, 0x1000
/* 00403d3c */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403d40 */  addiu      $a0, $a0, 0xb00
/* 00403d44 */  jal        0x4040d0                                 # gfo_parse_scope
/* 00403d48 */  addiu      $a0, $sp, 0x30
/* 00403d4c */  bnez       $v0, 0x403d7c
/* 00403d50 */  lw         $t7, 0x30($sp)
/* 00403d54 */  lui        $a0, 0x1000
/* 00403d58 */  lui        $a1, 0x1000
/* 00403d5c */  lui        $a2, 0x1000
/* 00403d60 */  addiu      $a2, $a2, 0xb28
/* 00403d64 */  addiu      $a1, $a1, 0xb14
/* 00403d68 */  jal        0xf801150                                # fclose
/* 00403d6c */  addiu      $a0, $a0, 0x36b4
/* 00403d70 */  jal        0x40d3c0
/* 00403d74 */  addiu      $a0, $zero, 1
/* 00403d78 */  lw         $t7, 0x30($sp)
/* 00403d7c */  nop        
/* 00403d80 */  lw         $v0, 4($t7)
/* 00403d84 */  nop        
/* 00403d88 */  bnez       $v0, 0x403dc4
/* 00403d8c */  nop        
/* 00403d90 */  lui        $a0, 0x1000
/* 00403d94 */  lui        $a1, 0x1000
/* 00403d98 */  lui        $a2, 0x1000
/* 00403d9c */  addiu      $a2, $a2, 0xb54
/* 00403da0 */  addiu      $a1, $a1, 0xb40
/* 00403da4 */  jal        0xf801150                                # fclose
/* 00403da8 */  addiu      $a0, $a0, 0x36b4
/* 00403dac */  jal        0x40d3c0
/* 00403db0 */  addiu      $a0, $zero, 1
/* 00403db4 */  lw         $t8, 0x30($sp)
/* 00403db8 */  nop        
/* 00403dbc */  lw         $v0, 4($t8)
/* 00403dc0 */  nop        
/* 00403dc4 */  lwc1       $f4, 4($v0)
/* 00403dc8 */  mtc1       $zero, $f18
/* 00403dcc */  mtc1       $zero, $f19
/* 00403dd0 */  cvt.d.s    $f6, $f4
/* 00403dd4 */  c.eq.d     $f18, $f6
/* 00403dd8 */  nop        
/* 00403ddc */  bc1t       0x403e0c
/* 00403de0 */  move       $a0, $s0
/* 00403de4 */  lui        $a0, 0x1000
/* 00403de8 */  lui        $a1, 0x1000
/* 00403dec */  lui        $a2, 0x1000
/* 00403df0 */  addiu      $a2, $a2, 0xb84
/* 00403df4 */  addiu      $a1, $a1, 0xb70
/* 00403df8 */  jal        0xf801150                                # fclose
/* 00403dfc */  addiu      $a0, $a0, 0x36b4
/* 00403e00 */  jal        0x40d3c0
/* 00403e04 */  addiu      $a0, $zero, 1
/* 00403e08 */  move       $a0, $s0
/* 00403e0c */  jal        0x403b9c                                 # gfo_parse_instance
/* 00403e10 */  addiu      $a1, $zero, 0
/* 00403e14 */  lw         $ra, 0x1c($sp)
/* 00403e18 */  lw         $s0, 0x18($sp)
/* 00403e1c */  addiu      $sp, $sp, 0x30
/* 00403e20 */  jr         $ra
/* 00403e24 */  addiu      $v0, $zero, 1

# === gfo_parse_line ===
glabel gfo_parse_line
/* 00403e28 */  addiu      $sp, $sp, -0x58
/* 00403e2c */  sw         $s2, 0x18($sp)
/* 00403e30 */  move       $s2, $a0
/* 00403e34 */  sw         $ra, 0x1c($sp)
/* 00403e38 */  jal        0x4040d0                                 # gfo_parse_scope
/* 00403e3c */  addiu      $a0, $sp, 0x54
/* 00403e40 */  bnez       $v0, 0x403e6c
/* 00403e44 */  nop        
/* 00403e48 */  lui        $a0, 0x1000
/* 00403e4c */  lui        $a1, 0x1000
/* 00403e50 */  lui        $a2, 0x1000
/* 00403e54 */  addiu      $a2, $a2, 0xba4
/* 00403e58 */  addiu      $a1, $a1, 0xb90
/* 00403e5c */  jal        0xf801150                                # fclose
/* 00403e60 */  addiu      $a0, $a0, 0x36b4
/* 00403e64 */  jal        0x40d3c0
/* 00403e68 */  addiu      $a0, $zero, 1
/* 00403e6c */  lw         $a1, ($s2)
/* 00403e70 */  nop        
/* 00403e74 */  move       $v0, $a1
/* 00403e78 */  beqz       $v0, 0x403e98
/* 00403e7c */  addiu      $at, $zero, 0x64
/* 00403e80 */  beq        $v0, $at, 0x403ea4
/* 00403e84 */  addiu      $at, $zero, 0xc8
/* 00403e88 */  beq        $v0, $at, 0x403eb4
/* 00403e8c */  addiu      $t8, $zero, 4
/* 00403e90 */  b          0x403ebc
/* 00403e94 */  nop        
/* 00403e98 */  addiu      $t6, $zero, 1
/* 00403e9c */  b          0x403ec8
/* 00403ea0 */  sw         $t6, 0x50($sp)
/* 00403ea4 */  addiu      $t7, $zero, 2
/* 00403ea8 */  b          0x403ec8
/* 00403eac */  sw         $t7, 0x50($sp)
/* 00403eb0 */  addiu      $t8, $zero, 4
/* 00403eb4 */  b          0x403ec8
/* 00403eb8 */  sw         $t8, 0x50($sp)
/* 00403ebc */  lui        $a0, 0x1000
/* 00403ec0 */  jal        0x4092d4
/* 00403ec4 */  addiu      $a0, $a0, 0xbb0
/* 00403ec8 */  lw         $t9, 0x54($sp)
/* 00403ecc */  nop        
/* 00403ed0 */  lw         $v0, 4($t9)
/* 00403ed4 */  nop        
/* 00403ed8 */  beqz       $v0, 0x403fdc
/* 00403edc */  nop        
/* 00403ee0 */  lw         $t0, 0xc($v0)
/* 00403ee4 */  lw         $t1, 0x50($sp)
/* 00403ee8 */  nop        
/* 00403eec */  and        $t2, $t0, $t1
/* 00403ef0 */  beqz       $t2, 0x403fc8
/* 00403ef4 */  nop        
/* 00403ef8 */  sw         $s0, 0x28($sp)
/* 00403efc */  sw         $s1, 0x24($sp)
/* 00403f00 */  lw         $a1, 4($v0)
/* 00403f04 */  jal        0x403b9c                                 # gfo_parse_instance
/* 00403f08 */  move       $a0, $s2
/* 00403f0c */  lw         $t3, 0x54($sp)
/* 00403f10 */  nop        
/* 00403f14 */  lw         $t4, 4($t3)
/* 00403f18 */  nop        
/* 00403f1c */  lw         $s1, 8($t4)
/* 00403f20 */  nop        
/* 00403f24 */  bgez       $s1, 0x403f38
/* 00403f28 */  nop        
/* 00403f2c */  lui        $a0, 0x1000
/* 00403f30 */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403f34 */  addiu      $a0, $a0, 0xbc8
/* 00403f38 */  blez       $s1, 0x403fb8
/* 00403f3c */  move       $s0, $zero
/* 00403f40 */  jal        0x4040d0                                 # gfo_parse_scope
/* 00403f44 */  addiu      $a0, $sp, 0x54
/* 00403f48 */  bnez       $v0, 0x403f60
/* 00403f4c */  lw         $t5, 0x54($sp)
/* 00403f50 */  lui        $a0, 0x1000
/* 00403f54 */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403f58 */  addiu      $a0, $a0, 0xbd8
/* 00403f5c */  lw         $t5, 0x54($sp)
/* 00403f60 */  addiu      $a1, $sp, 0x3c
/* 00403f64 */  lw         $a0, ($t5)
/* 00403f68 */  jal        0x40d830
/* 00403f6c */  nop        
/* 00403f70 */  lw         $t7, 0x54($sp)
/* 00403f74 */  lw         $t6, 0x3c($sp)
/* 00403f78 */  lw         $t8, ($t7)
/* 00403f7c */  cvt.s.d    $f2, $f0
/* 00403f80 */  bne        $t6, $t8, 0x403fa0
/* 00403f84 */  nop        
/* 00403f88 */  lui        $a0, 0x1000
/* 00403f8c */  addiu      $a0, $a0, 0xbf8
/* 00403f90 */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403f94 */  swc1       $f2, 0x40($sp)
/* 00403f98 */  lwc1       $f2, 0x40($sp)
/* 00403f9c */  nop        
/* 00403fa0 */  mfc1       $a1, $f2
/* 00403fa4 */  jal        0x403b9c                                 # gfo_parse_instance
/* 00403fa8 */  move       $a0, $s2
/* 00403fac */  addiu      $s0, $s0, 1
/* 00403fb0 */  bne        $s0, $s1, 0x403f40
/* 00403fb4 */  nop        
/* 00403fb8 */  lw         $s0, 0x28($sp)
/* 00403fbc */  lw         $s1, 0x24($sp)
/* 00403fc0 */  b          0x403fec
/* 00403fc4 */  lw         $ra, 0x1c($sp)
/* 00403fc8 */  lui        $a0, 0x1000
/* 00403fcc */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403fd0 */  addiu      $a0, $a0, 0xc0c
/* 00403fd4 */  b          0x403fec
/* 00403fd8 */  lw         $ra, 0x1c($sp)
/* 00403fdc */  lui        $a0, 0x1000
/* 00403fe0 */  jal        0x403ffc                                 # gfo_parse_entity
/* 00403fe4 */  addiu      $a0, $a0, 0xc2c
/* 00403fe8 */  lw         $ra, 0x1c($sp)
/* 00403fec */  lw         $s2, 0x18($sp)
/* 00403ff0 */  addiu      $sp, $sp, 0x58
/* 00403ff4 */  jr         $ra
/* 00403ff8 */  addiu      $v0, $zero, 1

# === gfo_parse_entity ===
glabel gfo_parse_entity
/* 00403ffc */  lui        $t6, 0x1000
/* 00404000 */  lw         $t6, 0x467c($t6)
/* 00404004 */  addiu      $sp, $sp, -0x20
/* 00404008 */  move       $v1, $a0
/* 0040400c */  lui        $a3, 0x1000
/* 00404010 */  sw         $ra, 0x1c($sp)
/* 00404014 */  lw         $a3, 0x4678($a3)
/* 00404018 */  lui        $a0, 0x1000
/* 0040401c */  lui        $a1, 0x1000
/* 00404020 */  lw         $a2, -0x7ae8($gp)                        # .sbss @ 0x10004288
/* 00404024 */  sw         $v1, 0x14($sp)
/* 00404028 */  addiu      $a1, $a1, 0xc40
/* 0040402c */  addiu      $a0, $a0, 0x36b4
/* 00404030 */  jal        0xf801150                                # fclose
/* 00404034 */  sw         $t6, 0x10($sp)
/* 00404038 */  lui        $a0, 0x1000
/* 0040403c */  lui        $a1, 0x1000
/* 00404040 */  lui        $a2, 0x1000
/* 00404044 */  addiu      $a2, $a2, 0x4570
/* 00404048 */  addiu      $a1, $a1, 0xc68
/* 0040404c */  jal        0xf801150                                # fclose
/* 00404050 */  addiu      $a0, $a0, 0x36b4
/* 00404054 */  jal        0x40d3c0
/* 00404058 */  addiu      $a0, $zero, -1
/* 0040405c */  lw         $ra, 0x1c($sp)
/* 00404060 */  addiu      $sp, $sp, 0x20
/* 00404064 */  jr         $ra
/* 00404068 */  nop        
/* 0040406c */  sw         $a0, -0x7aec($gp)                        # .sbss @ 0x10004284
/* 00404070 */  sw         $a1, -0x7ae8($gp)                        # .sbss @ 0x10004288
/* 00404074 */  sw         $zero, -0x7ae4($gp)                      # .sbss @ 0x1000428c
/* 00404078 */  lui        $at, 0x1000
/* 0040407c */  sw         $zero, -0x7ae0($gp)                      # .sbss @ 0x10004290
/* 00404080 */  sb         $zero, 0x4570($at)
/* 00404084 */  jr         $ra
/* 00404088 */  sw         $zero, -0x7d38($gp)                      # .sdata @ 0x10004038
/* 0040408c */  addiu      $sp, $sp, -0x18
/* 00404090 */  sw         $ra, 0x14($sp)
/* 00404094 */  lw         $a2, -0x7aec($gp)                        # .sbss @ 0x10004284
/* 00404098 */  jal        0xf8010d8                                # strlen
/* 0040409c */  nop        
/* 004040a0 */  bnez       $v0, 0x4040b0
/* 004040a4 */  nop        
/* 004040a8 */  b          0x4040c0
/* 004040ac */  move       $v0, $zero
/* 004040b0 */  lw         $t6, -0x7ae4($gp)                        # .sbss @ 0x1000428c
/* 004040b4 */  addiu      $v0, $zero, 1
/* 004040b8 */  addiu      $t7, $t6, 1
/* 004040bc */  sw         $t7, -0x7ae4($gp)                        # .sbss @ 0x1000428c
/* 004040c0 */  lw         $ra, 0x14($sp)
/* 004040c4 */  addiu      $sp, $sp, 0x18
/* 004040c8 */  jr         $ra
/* 004040cc */  nop        

# === gfo_parse_scope ===
glabel gfo_parse_scope
/* 004040d0 */  lw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 004040d4 */  addiu      $sp, $sp, -0x38
/* 004040d8 */  sw         $ra, 0x1c($sp)
/* 004040dc */  sw         $s1, 0x18($sp)
/* 004040e0 */  beqz       $a1, 0x4040f4
/* 004040e4 */  sw         $a0, 0x38($sp)
/* 004040e8 */  lui        $s1, 0x1000
/* 004040ec */  b          0x404120
/* 004040f0 */  addiu      $s1, $s1, 0x4570
/* 004040f4 */  lui        $s1, 0x1000
/* 004040f8 */  addiu      $s1, $s1, 0x4570
/* 004040fc */  move       $a0, $s1
/* 00404100 */  jal        0x40408c
/* 00404104 */  addiu      $a1, $zero, 0x100
/* 00404108 */  bnez       $v0, 0x40411c
/* 0040410c */  lui        $at, 0x1000
/* 00404110 */  sw         $zero, 0x4680($at)
/* 00404114 */  b          0x404360
/* 00404118 */  move       $v0, $zero
/* 0040411c */  move       $a1, $s1
/* 00404120 */  lw         $t6, -0x7ae0($gp)                        # .sbss @ 0x10004290
/* 00404124 */  nop        
/* 00404128 */  beqz       $t6, 0x404158
/* 0040412c */  nop        
/* 00404130 */  lw         $t8, 0x38($sp)
/* 00404134 */  lui        $t7, 0x1000
/* 00404138 */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 0040413c */  sw         $zero, -0x7ae0($gp)                      # .sbss @ 0x10004290
/* 00404140 */  addiu      $t7, $t7, 0x4670
/* 00404144 */  lui        $v0, 0x1000
/* 00404148 */  sw         $t7, ($t8)
/* 0040414c */  lw         $v0, 0x4680($v0)
/* 00404150 */  b          0x404364
/* 00404154 */  lw         $ra, 0x1c($sp)
/* 00404158 */  sw         $s0, 0x20($sp)
/* 0040415c */  lbu        $v0, ($a1)
/* 00404160 */  lui        $s0, 0x1000
/* 00404164 */  addiu      $s0, $s0, 0x32e0
/* 00404168 */  addu       $v1, $s0, $v0
/* 0040416c */  lbu        $t9, 1($v1)
/* 00404170 */  nop        
/* 00404174 */  andi       $t0, $t9, 8
/* 00404178 */  bnez       $t0, 0x404190
/* 0040417c */  nop        
/* 00404180 */  beqz       $v0, 0x404190
/* 00404184 */  addiu      $at, $zero, 0x23
/* 00404188 */  bne        $v0, $at, 0x40421c
/* 0040418c */  nop        
/* 00404190 */  lui        $t1, 0x1000
/* 00404194 */  addiu      $t1, $t1, 0x32e0
/* 00404198 */  bne        $v1, $t1, 0x4041a8
/* 0040419c */  nop        
/* 004041a0 */  b          0x4041bc
/* 004041a4 */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 004041a8 */  lui        $t2, 0x1000
/* 004041ac */  addiu      $t2, $t2, 0x3303
/* 004041b0 */  bne        $v1, $t2, 0x4041e8
/* 004041b4 */  nop        
/* 004041b8 */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 004041bc */  move       $a0, $s1
/* 004041c0 */  jal        0x40408c
/* 004041c4 */  addiu      $a1, $zero, 0x100
/* 004041c8 */  bnez       $v0, 0x4041e0
/* 004041cc */  lui        $at, 0x1000
/* 004041d0 */  lw         $s0, 0x20($sp)
/* 004041d4 */  sw         $zero, 0x4680($at)
/* 004041d8 */  b          0x404360
/* 004041dc */  move       $v0, $zero
/* 004041e0 */  b          0x4041ec
/* 004041e4 */  move       $a1, $s1
/* 004041e8 */  addiu      $a1, $a1, 1
/* 004041ec */  lbu        $v0, ($a1)
/* 004041f0 */  nop        
/* 004041f4 */  addu       $v1, $s0, $v0
/* 004041f8 */  lbu        $t3, 1($v1)
/* 004041fc */  nop        
/* 00404200 */  andi       $t4, $t3, 8
/* 00404204 */  bnez       $t4, 0x404190
/* 00404208 */  nop        
/* 0040420c */  beqz       $v0, 0x404190
/* 00404210 */  addiu      $at, $zero, 0x23
/* 00404214 */  beq        $v0, $at, 0x404190
/* 00404218 */  nop        
/* 0040421c */  lui        $a3, 0x1000
/* 00404220 */  addiu      $a3, $a3, 0x4688
/* 00404224 */  move       $a2, $a1
/* 00404228 */  bnez       $v0, 0x404238
/* 0040422c */  move       $v1, $a3
/* 00404230 */  b          0x404290
/* 00404234 */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 00404238 */  addu       $t5, $s0, $v0
/* 0040423c */  lbu        $t6, 1($t5)
/* 00404240 */  nop        
/* 00404244 */  andi       $t7, $t6, 8
/* 00404248 */  beqz       $t7, 0x404258
/* 0040424c */  nop        
/* 00404250 */  b          0x404290
/* 00404254 */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 00404258 */  sb         $v0, ($v1)
/* 0040425c */  lbu        $v0, 1($a1)
/* 00404260 */  addiu      $v1, $v1, 1
/* 00404264 */  bnez       $v0, 0x404274
/* 00404268 */  addiu      $a1, $a1, 1
/* 0040426c */  b          0x404290
/* 00404270 */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 00404274 */  addu       $t8, $s0, $v0
/* 00404278 */  lbu        $t9, 1($t8)
/* 0040427c */  nop        
/* 00404280 */  andi       $t0, $t9, 8
/* 00404284 */  beqz       $t0, 0x404258
/* 00404288 */  nop        
/* 0040428c */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 00404290 */  bnez       $v0, 0x4042d4
/* 00404294 */  sb         $zero, ($v1)
/* 00404298 */  move       $a0, $s1
/* 0040429c */  addiu      $a1, $zero, 0x100
/* 004042a0 */  jal        0x40408c
/* 004042a4 */  sw         $a2, 0x2c($sp)
/* 004042a8 */  lw         $a2, 0x2c($sp)
/* 004042ac */  lui        $a3, 0x1000
/* 004042b0 */  bnez       $v0, 0x4042cc
/* 004042b4 */  addiu      $a3, $a3, 0x4688
/* 004042b8 */  lui        $at, 0x1000
/* 004042bc */  lw         $s0, 0x20($sp)
/* 004042c0 */  sw         $zero, 0x4680($at)
/* 004042c4 */  b          0x404360
/* 004042c8 */  move       $v0, $zero
/* 004042cc */  move       $a1, $s1
/* 004042d0 */  sw         $a1, -0x7d38($gp)                        # .sdata @ 0x10004038
/* 004042d4 */  lui        $at, 0x1000
/* 004042d8 */  sw         $a3, 0x4670($at)
/* 004042dc */  lw         $t1, -0x7ae4($gp)                        # .sbss @ 0x1000428c
/* 004042e0 */  lui        $at, 0x1000
/* 004042e4 */  subu       $t2, $a2, $s1
/* 004042e8 */  addiu      $t3, $t2, 1
/* 004042ec */  lui        $t4, 0x1000
/* 004042f0 */  lbu        $t4, 0x4688($t4)
/* 004042f4 */  sw         $t3, 0x467c($at)
/* 004042f8 */  sw         $t1, 0x4678($at)
/* 004042fc */  lui        $at, 0x1000
/* 00404300 */  sw         $zero, 0x4674($at)
/* 00404304 */  addu       $t5, $s0, $t4
/* 00404308 */  lbu        $t6, 1($t5)
/* 0040430c */  nop        
/* 00404310 */  andi       $t7, $t6, 3
/* 00404314 */  beqz       $t7, 0x404340
/* 00404318 */  lw         $t1, 0x38($sp)
/* 0040431c */  jal        0x4043bc                                 # gfo_alloc_entity
/* 00404320 */  move       $a0, $a3
/* 00404324 */  lui        $at, 0x1000
/* 00404328 */  beqz       $v0, 0x40433c
/* 0040432c */  sw         $v0, 0x4674($at)
/* 00404330 */  lw         $t8, ($v0)
/* 00404334 */  lui        $at, 0x1000
/* 00404338 */  sw         $t8, 0x4670($at)
/* 0040433c */  lw         $t1, 0x38($sp)
/* 00404340 */  addiu      $t9, $zero, 1
/* 00404344 */  lui        $at, 0x1000
/* 00404348 */  lui        $t0, 0x1000
/* 0040434c */  sw         $t9, 0x4680($at)
/* 00404350 */  addiu      $t0, $t0, 0x4670
/* 00404354 */  sw         $t0, ($t1)
/* 00404358 */  lw         $s0, 0x20($sp)
/* 0040435c */  addiu      $v0, $zero, 1
/* 00404360 */  lw         $ra, 0x1c($sp)
/* 00404364 */  lw         $s1, 0x18($sp)
/* 00404368 */  jr         $ra
/* 0040436c */  addiu      $sp, $sp, 0x38

# === gfo_parse_material ===
glabel gfo_parse_material
/* 00404370 */  lw         $t6, -0x7ae0($gp)                        # .sbss @ 0x10004290
/* 00404374 */  addiu      $sp, $sp, -0x18
/* 00404378 */  bnez       $t6, 0x404394
/* 0040437c */  sw         $ra, 0x14($sp)
/* 00404380 */  jal        0x4040d0                                 # gfo_parse_scope
/* 00404384 */  nop        
/* 00404388 */  addiu      $t7, $zero, 1
/* 0040438c */  b          0x4043ac
/* 00404390 */  sw         $t7, -0x7ae0($gp)                        # .sbss @ 0x10004290
/* 00404394 */  lui        $t8, 0x1000
/* 00404398 */  addiu      $t8, $t8, 0x4670
/* 0040439c */  sw         $t8, ($a0)
/* 004043a0 */  lui        $v0, 0x1000
/* 004043a4 */  lw         $v0, 0x4680($v0)
/* 004043a8 */  nop        
/* 004043ac */  lw         $ra, 0x14($sp)
/* 004043b0 */  addiu      $sp, $sp, 0x18
/* 004043b4 */  jr         $ra
/* 004043b8 */  nop        

# === gfo_alloc_entity ===
glabel gfo_alloc_entity
/* 004043bc */  addiu      $sp, $sp, -0x30
/* 004043c0 */  sw         $s1, 0x18($sp)
/* 004043c4 */  sw         $s3, 0x20($sp)
/* 004043c8 */  sw         $s2, 0x1c($sp)
/* 004043cc */  sw         $s0, 0x14($sp)
/* 004043d0 */  lui        $s1, 0x1000
/* 004043d4 */  sw         $ra, 0x24($sp)
/* 004043d8 */  move       $s3, $a0
/* 004043dc */  sw         $zero, 0x28($sp)
/* 004043e0 */  addiu      $s1, $s1, 0x7e0
/* 004043e4 */  move       $s0, $zero
/* 004043e8 */  addiu      $s2, $zero, 0xf
/* 004043ec */  lw         $a1, ($s1)
/* 004043f0 */  jal        0xf8012e8                                # fwrite
/* 004043f4 */  move       $a0, $s3
/* 004043f8 */  bnez       $v0, 0x404410
/* 004043fc */  addiu      $s0, $s0, 1
/* 00404400 */  addiu      $t6, $zero, 1
/* 00404404 */  b          0x404418
/* 00404408 */  sw         $t6, 0x28($sp)
/* 0040440c */  addiu      $s0, $s0, 1
/* 00404410 */  bne        $s0, $s2, 0x4043ec
/* 00404414 */  addiu      $s1, $s1, 0x10
/* 00404418 */  lw         $t7, 0x28($sp)
/* 0040441c */  nop        
/* 00404420 */  beqz       $t7, 0x404434
/* 00404424 */  move       $v1, $zero
/* 00404428 */  b          0x404434
/* 0040442c */  move       $v1, $s1
/* 00404430 */  move       $v1, $zero
/* 00404434 */  lw         $ra, 0x24($sp)
/* 00404438 */  lw         $s0, 0x14($sp)
/* 0040443c */  lw         $s1, 0x18($sp)
/* 00404440 */  lw         $s2, 0x1c($sp)
/* 00404444 */  lw         $s3, 0x20($sp)
/* 00404448 */  addiu      $sp, $sp, 0x30
/* 0040444c */  jr         $ra
/* 00404450 */  move       $v0, $v1
/* 00404454 */  nop        
/* 00404458 */  nop        
/* 0040445c */  nop        

# === gfo_alloc_scope ===
glabel gfo_alloc_scope
/* 00404460 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00404464 */  addiu      $sp, $sp, -0x20
/* 00404468 */  sw         $ra, 0x14($sp)
/* 0040446c */  lw         $v0, 0xfc($t6)
/* 00404470 */  addiu      $at, $zero, 0xc
/* 00404474 */  addiu      $t7, $v0, 0xc
/* 00404478 */  sw         $t7, 0xfc($t6)
/* 0040447c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00404480 */  move       $v1, $v0
/* 00404484 */  lw         $t9, 0xf4($t8)
/* 00404488 */  nop        
/* 0040448c */  subu       $t0, $v1, $t9
/* 00404490 */  div        $zero, $t0, $at
/* 00404494 */  mflo       $t1
/* 00404498 */  slti       $at, $t1, 0x2de6
/* 0040449c */  bnez       $at, 0x4044d8
/* 004044a0 */  nop        
/* 004044a4 */  lui        $a0, 0x1000
/* 004044a8 */  lui        $a1, 0x1000
/* 004044ac */  lui        $a2, 0x1000
/* 004044b0 */  addiu      $a2, $a2, 0xc94
/* 004044b4 */  addiu      $a1, $a1, 0xc80
/* 004044b8 */  addiu      $a0, $a0, 0x36b4
/* 004044bc */  jal        0xf801150                                # fclose
/* 004044c0 */  sw         $v1, 0x1c($sp)
/* 004044c4 */  lw         $v1, 0x1c($sp)
/* 004044c8 */  jal        0x40d3c0
/* 004044cc */  addiu      $a0, $zero, 1
/* 004044d0 */  lw         $v1, 0x1c($sp)
/* 004044d4 */  nop        
/* 004044d8 */  sw         $zero, ($v1)
/* 004044dc */  sw         $zero, 4($v1)
/* 004044e0 */  lw         $ra, 0x14($sp)
/* 004044e4 */  addiu      $sp, $sp, 0x20
/* 004044e8 */  jr         $ra
/* 004044ec */  move       $v0, $v1

# === gfo_count_elements ===
glabel gfo_count_elements
/* 004044f0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 004044f4 */  addiu      $sp, $sp, -0x20
/* 004044f8 */  sw         $ra, 0x14($sp)
/* 004044fc */  lw         $v0, 0x100($t6)
/* 00404500 */  sll        $t7, $a0, 2
/* 00404504 */  sw         $v0, 0x1c($sp)
/* 00404508 */  addu       $t8, $v0, $t7
/* 0040450c */  sw         $t8, 0x100($t6)
/* 00404510 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00404514 */  nop        
/* 00404518 */  lw         $t0, 0x100($t9)
/* 0040451c */  lw         $t1, 0xf8($t9)
/* 00404520 */  nop        
/* 00404524 */  subu       $t2, $t0, $t1
/* 00404528 */  bgez       $t2, 0x404534
/* 0040452c */  move       $at, $t2
/* 00404530 */  addiu      $at, $at, 3
/* 00404534 */  sra        $t3, $at, 2
/* 00404538 */  lui        $at, 8
/* 0040453c */  ori        $at, $at, 0x9545
/* 00404540 */  slt        $at, $t3, $at
/* 00404544 */  bnez       $at, 0x404574
/* 00404548 */  lw         $ra, 0x14($sp)
/* 0040454c */  lui        $a0, 0x1000
/* 00404550 */  lui        $a1, 0x1000
/* 00404554 */  lui        $a2, 0x1000
/* 00404558 */  addiu      $a2, $a2, 0xcb4
/* 0040455c */  addiu      $a1, $a1, 0xca0
/* 00404560 */  jal        0xf801150                                # fclose
/* 00404564 */  addiu      $a0, $a0, 0x36b4
/* 00404568 */  jal        0x40d3c0
/* 0040456c */  addiu      $a0, $zero, 1
/* 00404570 */  lw         $ra, 0x14($sp)
/* 00404574 */  lw         $v0, 0x1c($sp)
/* 00404578 */  jr         $ra
/* 0040457c */  addiu      $sp, $sp, 0x20

# === gfo_build_display_list ===
glabel gfo_build_display_list
/* 00404580 */  addiu      $sp, $sp, -0x18
/* 00404584 */  sw         $ra, 0x14($sp)
/* 00404588 */  lui        $a0, 2
/* 0040458c */  jal        0xf801208                                # free
/* 00404590 */  ori        $a0, $a0, 0x26c8
/* 00404594 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00404598 */  nop        
/* 0040459c */  sw         $v0, 0xf4($t6)
/* 004045a0 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004045a4 */  nop        
/* 004045a8 */  lw         $t8, 0xf4($t7)
/* 004045ac */  nop        
/* 004045b0 */  bnez       $t8, 0x4045c8
/* 004045b4 */  lui        $a0, 0x22
/* 004045b8 */  lui        $a0, 0x1000
/* 004045bc */  jal        0x4092d4
/* 004045c0 */  addiu      $a0, $a0, 0xcc0
/* 004045c4 */  lui        $a0, 0x22
/* 004045c8 */  jal        0xf801208                                # free
/* 004045cc */  ori        $a0, $a0, 0x5510
/* 004045d0 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 004045d4 */  nop        
/* 004045d8 */  sw         $v0, 0xf8($t9)
/* 004045dc */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 004045e0 */  nop        
/* 004045e4 */  lw         $t1, 0xf8($t0)
/* 004045e8 */  nop        
/* 004045ec */  bnez       $t1, 0x404600
/* 004045f0 */  nop        
/* 004045f4 */  lui        $a0, 0x1000
/* 004045f8 */  jal        0x4092d4
/* 004045fc */  addiu      $a0, $a0, 0xcec
/* 00404600 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00404604 */  nop        
/* 00404608 */  lw         $t3, 0xf4($t2)
/* 0040460c */  nop        
/* 00404610 */  sw         $t3, 0xfc($t2)
/* 00404614 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 00404618 */  nop        
/* 0040461c */  lw         $t5, 0xf8($t4)
/* 00404620 */  nop        
/* 00404624 */  sw         $t5, 0x100($t4)
/* 00404628 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 0040462c */  nop        
/* 00404630 */  lw         $a2, 0xf8($t6)
/* 00404634 */  nop        
/* 00404638 */  andi       $t7, $a2, 0xf
/* 0040463c */  beqz       $t7, 0x40465c
/* 00404640 */  lw         $ra, 0x14($sp)
/* 00404644 */  lui        $a0, 0x1000
/* 00404648 */  lui        $a1, 0x1000
/* 0040464c */  addiu      $a1, $a1, 0xd18
/* 00404650 */  jal        0xf801150                                # fclose
/* 00404654 */  addiu      $a0, $a0, 0x36b4
/* 00404658 */  lw         $ra, 0x14($sp)
/* 0040465c */  addiu      $sp, $sp, 0x18
/* 00404660 */  jr         $ra
/* 00404664 */  nop        

# === gfo_load_file ===
glabel gfo_load_file
/* 00404668 */  addiu      $sp, $sp, -0x70
/* 0040466c */  sw         $ra, 0x34($sp)
/* 00404670 */  sw         $s7, 0x2c($sp)
/* 00404674 */  sw         $s4, 0x20($sp)
/* 00404678 */  sw         $s2, 0x18($sp)
/* 0040467c */  sw         $s3, 0x1c($sp)
/* 00404680 */  sw         $fp, 0x30($sp)
/* 00404684 */  sw         $s6, 0x28($sp)
/* 00404688 */  sw         $s5, 0x24($sp)
/* 0040468c */  move       $s4, $a1
/* 00404690 */  move       $s7, $a0
/* 00404694 */  sw         $s0, 0x14($sp)
/* 00404698 */  move       $s3, $zero
/* 0040469c */  jal        0x40a400
/* 004046a0 */  move       $s2, $zero
/* 004046a4 */  sw         $v0, 0x6c($sp)
/* 004046a8 */  jal        0xf801208                                # free
/* 004046ac */  addiu      $a0, $zero, 0x10
/* 004046b0 */  bnez       $v0, 0x4046c0
/* 004046b4 */  move       $fp, $v0
/* 004046b8 */  jal        0x4092d4
/* 004046bc */  addiu      $a0, $gp, -0x7d10
/* 004046c0 */  addiu      $t6, $zero, 0x109
/* 004046c4 */  sw         $t6, ($fp)
/* 004046c8 */  sw         $zero, 8($fp)
/* 004046cc */  lw         $a0, 0x6c($sp)
/* 004046d0 */  jal        0x40a6d4
/* 004046d4 */  move       $a1, $fp
/* 004046d8 */  jal        0x40a8e0
/* 004046dc */  move       $a0, $s7
/* 004046e0 */  lw         $v1, 4($v0)
/* 004046e4 */  lui        $s5, 0x41
/* 004046e8 */  addiu      $s5, $s5, -0x7550
/* 004046ec */  bne        $s5, $v1, 0x40470c
/* 004046f0 */  nop        
/* 004046f4 */  addiu      $t7, $zero, 4
/* 004046f8 */  lui        $s6, 0x41
/* 004046fc */  sw         $s5, 4($fp)
/* 00404700 */  sw         $t7, 0xc($fp)
/* 00404704 */  b          0x40474c
/* 00404708 */  addiu      $s6, $s6, -0x77c0
/* 0040470c */  lui        $s6, 0x41
/* 00404710 */  addiu      $s6, $s6, -0x77c0
/* 00404714 */  move       $a0, $s6
/* 00404718 */  bne        $a0, $v1, 0x404730
/* 0040471c */  nop        
/* 00404720 */  addiu      $t8, $zero, 2
/* 00404724 */  sw         $a0, 4($fp)
/* 00404728 */  b          0x40474c
/* 0040472c */  sw         $t8, 0xc($fp)
/* 00404730 */  lui        $a0, 0x1000
/* 00404734 */  lui        $a1, 0x1000
/* 00404738 */  addiu      $a1, $a1, 0xd4c
/* 0040473c */  jal        0xf801150                                # fclose
/* 00404740 */  addiu      $a0, $a0, 0x36b4
/* 00404744 */  jal        0x40d3c0
/* 00404748 */  addiu      $a0, $zero, -1
/* 0040474c */  jal        0x404460                                 # gfo_alloc_scope
/* 00404750 */  nop        
/* 00404754 */  sw         $v0, 0x50($sp)
/* 00404758 */  sw         $zero, ($v0)
/* 0040475c */  move       $s0, $v0
/* 00404760 */  sw         $zero, 0x58($sp)
/* 00404764 */  jal        0x40a8e0
/* 00404768 */  move       $a0, $s7
/* 0040476c */  beqz       $v0, 0x404804
/* 00404770 */  move       $t0, $v0
/* 00404774 */  sw         $s1, 0x3c($sp)
/* 00404778 */  lui        $s1, 0x1000
/* 0040477c */  addiu      $s1, $s1, 0xd80
/* 00404780 */  lw         $v1, 4($v0)
/* 00404784 */  nop        
/* 00404788 */  bne        $s5, $v1, 0x4047ac
/* 0040478c */  nop        
/* 00404790 */  lw         $a0, 8($t0)
/* 00404794 */  move       $a1, $s0
/* 00404798 */  addiu      $a2, $sp, 0x58
/* 0040479c */  jal        0x40493c                                 # bin_write_array
/* 004047a0 */  move       $a3, $s4
/* 004047a4 */  b          0x4047e8
/* 004047a8 */  addu       $s3, $s3, $v0
/* 004047ac */  bne        $s6, $v1, 0x4047d0
/* 004047b0 */  nop        
/* 004047b4 */  lw         $a0, 8($t0)
/* 004047b8 */  move       $a1, $s0
/* 004047bc */  addiu      $a2, $sp, 0x58
/* 004047c0 */  jal        0x404a4c                                 # bin_read_array
/* 004047c4 */  move       $a3, $s4
/* 004047c8 */  b          0x4047e8
/* 004047cc */  addu       $s2, $s2, $v0
/* 004047d0 */  lui        $a0, 0x1000
/* 004047d4 */  addiu      $a0, $a0, 0x36b4
/* 004047d8 */  jal        0xf801150                                # fclose
/* 004047dc */  move       $a1, $s1
/* 004047e0 */  jal        0x40d3c0
/* 004047e4 */  addiu      $a0, $zero, -1
/* 004047e8 */  lw         $s0, 0x58($sp)
/* 004047ec */  jal        0x40a918
/* 004047f0 */  move       $a0, $s7
/* 004047f4 */  bnez       $v0, 0x404780
/* 004047f8 */  move       $t0, $v0
/* 004047fc */  lw         $s1, 0x3c($sp)
/* 00404800 */  nop        
/* 00404804 */  lw         $t9, 0x50($sp)
/* 00404808 */  nop        
/* 0040480c */  lw         $t1, ($t9)
/* 00404810 */  nop        
/* 00404814 */  sw         $t1, 8($fp)
/* 00404818 */  lw         $ra, 0x34($sp)
/* 0040481c */  lw         $fp, 0x30($sp)
/* 00404820 */  lw         $s7, 0x2c($sp)
/* 00404824 */  lw         $s6, 0x28($sp)
/* 00404828 */  lw         $s5, 0x24($sp)
/* 0040482c */  lw         $s4, 0x20($sp)
/* 00404830 */  lw         $s3, 0x1c($sp)
/* 00404834 */  lw         $s2, 0x18($sp)
/* 00404838 */  lw         $s0, 0x14($sp)
/* 0040483c */  lw         $v0, 0x6c($sp)
/* 00404840 */  jr         $ra
/* 00404844 */  addiu      $sp, $sp, 0x70

# === bin_write_model ===
glabel bin_write_model
/* 00404848 */  addiu      $sp, $sp, -0x28
/* 0040484c */  sw         $ra, 0x14($sp)
/* 00404850 */  move       $a2, $a0
/* 00404854 */  sw         $a1, 0x2c($sp)
/* 00404858 */  jal        0x404460                                 # gfo_alloc_scope
/* 0040485c */  sw         $a2, 0x28($sp)
/* 00404860 */  lw         $a2, 0x28($sp)
/* 00404864 */  move       $a3, $v0
/* 00404868 */  lw         $a0, 8($a2)
/* 0040486c */  jal        0x4044f0                                 # gfo_count_elements
/* 00404870 */  sw         $a3, 0x1c($sp)
/* 00404874 */  lw         $a2, 0x28($sp)
/* 00404878 */  lw         $a3, 0x1c($sp)
/* 0040487c */  move       $v1, $v0
/* 00404880 */  sw         $v0, 4($a3)
/* 00404884 */  lw         $t6, 8($a2)
/* 00404888 */  move       $a1, $zero
/* 0040488c */  sw         $t6, 8($a3)
/* 00404890 */  lw         $t7, 0x2c($sp)
/* 00404894 */  nop        
/* 00404898 */  sw         $a3, ($t7)
/* 0040489c */  sw         $zero, ($a3)
/* 004048a0 */  lw         $t8, 8($a2)
/* 004048a4 */  lw         $a0, 4($a2)
/* 004048a8 */  blez       $t8, 0x4048d4
/* 004048ac */  lw         $ra, 0x14($sp)
/* 004048b0 */  lw         $t9, ($a0)
/* 004048b4 */  addiu      $a1, $a1, 1
/* 004048b8 */  sw         $t9, ($v1)
/* 004048bc */  lw         $t0, 8($a2)
/* 004048c0 */  addiu      $a0, $a0, 4
/* 004048c4 */  slt        $at, $a1, $t0
/* 004048c8 */  bnez       $at, 0x4048b0
/* 004048cc */  addiu      $v1, $v1, 4
/* 004048d0 */  lw         $ra, 0x14($sp)
/* 004048d4 */  addiu      $sp, $sp, 0x28
/* 004048d8 */  jr         $ra
/* 004048dc */  move       $v0, $a3
/* 004048e0 */  andi       $t6, $a0, 0xff
/* 004048e4 */  mtc1       $t6, $f4
/* 004048e8 */  lwc1       $f1, -0x7f80($gp)                        # .lit8: 0.00392157
/* 004048ec */  cvt.d.w    $f6, $f4
/* 004048f0 */  lwc1       $f0, -0x7f7c($gp)                        # .lit8 @ 0x10003df4
/* 004048f4 */  sra        $t7, $a0, 8
/* 004048f8 */  mul.d      $f8, $f6, $f0
/* 004048fc */  sra        $t9, $a0, 0x10
/* 00404900 */  andi       $t8, $t7, 0xff
/* 00404904 */  andi       $t0, $t9, 0xff
/* 00404908 */  mtc1       $t8, $f16
/* 0040490c */  cvt.s.d    $f10, $f8
/* 00404910 */  mtc1       $t0, $f8
/* 00404914 */  swc1       $f10, ($a1)
/* 00404918 */  cvt.d.w    $f18, $f16
/* 0040491c */  cvt.d.w    $f10, $f8
/* 00404920 */  mul.d      $f4, $f18, $f0
/* 00404924 */  mul.d      $f16, $f10, $f0
/* 00404928 */  cvt.s.d    $f6, $f4
/* 0040492c */  swc1       $f6, 4($a1)
/* 00404930 */  cvt.s.d    $f18, $f16
/* 00404934 */  jr         $ra
/* 00404938 */  swc1       $f18, 8($a1)

# === bin_write_array ===
glabel bin_write_array
/* 0040493c */  addiu      $sp, $sp, -0x80
/* 00404940 */  sw         $fp, 0x20($sp)
/* 00404944 */  sw         $s2, 0x1c($sp)
/* 00404948 */  sw         $s1, 0x18($sp)
/* 0040494c */  sw         $s0, 0x14($sp)
/* 00404950 */  sw         $ra, 0x24($sp)
/* 00404954 */  move       $s2, $a1
/* 00404958 */  move       $fp, $a3
/* 0040495c */  sw         $a2, 0x88($sp)
/* 00404960 */  move       $s1, $zero
/* 00404964 */  beqz       $a0, 0x404a24
/* 00404968 */  move       $s0, $a0
/* 0040496c */  sw         $s4, 0x34($sp)
/* 00404970 */  sw         $s5, 0x30($sp)
/* 00404974 */  sw         $s7, 0x28($sp)
/* 00404978 */  lui        $s7, 0x1000
/* 0040497c */  lui        $s5, 0x1000
/* 00404980 */  lui        $s4, 0x1000
/* 00404984 */  sw         $s3, 0x38($sp)
/* 00404988 */  sw         $s6, 0x2c($sp)
/* 0040498c */  addiu      $s6, $zero, 1
/* 00404990 */  addiu      $s3, $zero, 0x18
/* 00404994 */  addiu      $s4, $s4, 0x36b4
/* 00404998 */  addiu      $s5, $s5, 0xdb0
/* 0040499c */  addiu      $s7, $s7, 0xde8
/* 004049a0 */  lw         $t6, 8($s0)
/* 004049a4 */  nop        
/* 004049a8 */  beq        $s3, $t6, 0x4049ec
/* 004049ac */  nop        
/* 004049b0 */  move       $a0, $s4
/* 004049b4 */  jal        0xf801150                                # fclose
/* 004049b8 */  move       $a1, $s5
/* 004049bc */  b          0x404a00
/* 004049c0 */  lw         $s0, ($s0)
/* 004049c4 */  move       $a0, $s0
/* 004049c8 */  jal        0x404848                                 # bin_write_model
/* 004049cc */  move       $a1, $s2
/* 004049d0 */  move       $s2, $v0
/* 004049d4 */  b          0x4049fc
/* 004049d8 */  addiu      $s1, $s1, 1
/* 004049dc */  jal        0x4092d4
/* 004049e0 */  move       $a0, $s7
/* 004049e4 */  b          0x404a00
/* 004049e8 */  lw         $s0, ($s0)
/* 004049ec */  beq        $fp, $s6, 0x4049c8
/* 004049f0 */  move       $a0, $s0
/* 004049f4 */  b          0x4049dc
/* 004049f8 */  nop        
/* 004049fc */  lw         $s0, ($s0)
/* 00404a00 */  nop        
/* 00404a04 */  bnez       $s0, 0x4049a0
/* 00404a08 */  nop        
/* 00404a0c */  lw         $s3, 0x38($sp)
/* 00404a10 */  lw         $s4, 0x34($sp)
/* 00404a14 */  lw         $s5, 0x30($sp)
/* 00404a18 */  lw         $s6, 0x2c($sp)
/* 00404a1c */  lw         $s7, 0x28($sp)
/* 00404a20 */  nop        
/* 00404a24 */  lw         $t7, 0x88($sp)
/* 00404a28 */  move       $v0, $s1
/* 00404a2c */  sw         $s2, ($t7)
/* 00404a30 */  lw         $ra, 0x24($sp)
/* 00404a34 */  lw         $fp, 0x20($sp)
/* 00404a38 */  lw         $s2, 0x1c($sp)
/* 00404a3c */  lw         $s1, 0x18($sp)
/* 00404a40 */  lw         $s0, 0x14($sp)
/* 00404a44 */  jr         $ra
/* 00404a48 */  addiu      $sp, $sp, 0x80

# === bin_read_array ===
glabel bin_read_array
/* 00404a4c */  addiu      $sp, $sp, -0x70
/* 00404a50 */  sw         $fp, 0x20($sp)
/* 00404a54 */  sw         $s2, 0x1c($sp)
/* 00404a58 */  sw         $s1, 0x18($sp)
/* 00404a5c */  sw         $s0, 0x14($sp)
/* 00404a60 */  sw         $ra, 0x24($sp)
/* 00404a64 */  move       $s2, $a1
/* 00404a68 */  move       $fp, $a3
/* 00404a6c */  sw         $a2, 0x78($sp)
/* 00404a70 */  move       $s1, $zero
/* 00404a74 */  beqz       $a0, 0x404b34
/* 00404a78 */  move       $s0, $a0
/* 00404a7c */  sw         $s4, 0x34($sp)
/* 00404a80 */  sw         $s5, 0x30($sp)
/* 00404a84 */  sw         $s7, 0x28($sp)
/* 00404a88 */  lui        $s7, 0x1000
/* 00404a8c */  lui        $s5, 0x1000
/* 00404a90 */  lui        $s4, 0x1000
/* 00404a94 */  sw         $s3, 0x38($sp)
/* 00404a98 */  sw         $s6, 0x2c($sp)
/* 00404a9c */  addiu      $s6, $zero, 1
/* 00404aa0 */  addiu      $s3, $zero, 0x10
/* 00404aa4 */  addiu      $s4, $s4, 0x36b4
/* 00404aa8 */  addiu      $s5, $s5, 0xe10
/* 00404aac */  addiu      $s7, $s7, 0xe48
/* 00404ab0 */  lw         $t6, 8($s0)
/* 00404ab4 */  nop        
/* 00404ab8 */  beq        $s3, $t6, 0x404afc
/* 00404abc */  nop        
/* 00404ac0 */  move       $a0, $s4
/* 00404ac4 */  jal        0xf801150                                # fclose
/* 00404ac8 */  move       $a1, $s5
/* 00404acc */  b          0x404b10
/* 00404ad0 */  lw         $s0, ($s0)
/* 00404ad4 */  move       $a0, $s0
/* 00404ad8 */  jal        0x404848                                 # bin_write_model
/* 00404adc */  move       $a1, $s2
/* 00404ae0 */  move       $s2, $v0
/* 00404ae4 */  b          0x404b0c
/* 00404ae8 */  addiu      $s1, $s1, 1
/* 00404aec */  jal        0x4092d4
/* 00404af0 */  move       $a0, $s7
/* 00404af4 */  b          0x404b10
/* 00404af8 */  lw         $s0, ($s0)
/* 00404afc */  beq        $fp, $s6, 0x404ad8
/* 00404b00 */  move       $a0, $s0
/* 00404b04 */  b          0x404aec
/* 00404b08 */  nop        
/* 00404b0c */  lw         $s0, ($s0)
/* 00404b10 */  nop        
/* 00404b14 */  bnez       $s0, 0x404ab0
/* 00404b18 */  nop        
/* 00404b1c */  lw         $s3, 0x38($sp)
/* 00404b20 */  lw         $s4, 0x34($sp)
/* 00404b24 */  lw         $s5, 0x30($sp)
/* 00404b28 */  lw         $s6, 0x2c($sp)
/* 00404b2c */  lw         $s7, 0x28($sp)
/* 00404b30 */  nop        
/* 00404b34 */  lw         $t7, 0x78($sp)
/* 00404b38 */  move       $v0, $s1
/* 00404b3c */  sw         $s2, ($t7)
/* 00404b40 */  lw         $ra, 0x24($sp)
/* 00404b44 */  lw         $fp, 0x20($sp)
/* 00404b48 */  lw         $s2, 0x1c($sp)
/* 00404b4c */  lw         $s1, 0x18($sp)
/* 00404b50 */  lw         $s0, 0x14($sp)
/* 00404b54 */  jr         $ra
/* 00404b58 */  addiu      $sp, $sp, 0x70
/* 00404b5c */  nop        

# === bin_read_model ===
glabel bin_read_model
/* 00404b60 */  addiu      $sp, $sp, -0x3a0
/* 00404b64 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00404b68 */  sw         $ra, 0x2c($sp)
/* 00404b6c */  sw         $s6, 0x28($sp)
/* 00404b70 */  sw         $s4, 0x20($sp)
/* 00404b74 */  sw         $s5, 0x24($sp)
/* 00404b78 */  sw         $s3, 0x1c($sp)
/* 00404b7c */  sw         $s1, 0x18($sp)
/* 00404b80 */  lw         $t8, 0xf4($t6)
/* 00404b84 */  lw         $t7, 0xfc($t6)
/* 00404b88 */  addiu      $at, $zero, 0xc
/* 00404b8c */  subu       $v0, $t7, $t8
/* 00404b90 */  div        $zero, $v0, $at
/* 00404b94 */  lw         $t0, 0xf8($t6)
/* 00404b98 */  lw         $t9, 0x100($t6)
/* 00404b9c */  sw         $a1, 0x38c($sp)
/* 00404ba0 */  lui        $t1, 0x1357
/* 00404ba4 */  lui        $t2, 1
/* 00404ba8 */  ori        $t1, $t1, 0x7531
/* 00404bac */  sw         $t1, 0x37c($sp)
/* 00404bb0 */  ori        $t2, $t2, 2
/* 00404bb4 */  sw         $t2, 0x380($sp)
/* 00404bb8 */  addiu      $t3, $zero, 0x10
/* 00404bbc */  addiu      $t4, $zero, 0xc
/* 00404bc0 */  sw         $t3, 0x384($sp)
/* 00404bc4 */  sw         $t4, 0x388($sp)
/* 00404bc8 */  lw         $t5, 0xf4($t6)
/* 00404bcc */  subu       $v1, $t9, $t0
/* 00404bd0 */  sw         $t5, 0x390($sp)
/* 00404bd4 */  lw         $t7, 0xf8($t6)
/* 00404bd8 */  move       $s1, $a0
/* 00404bdc */  sw         $t7, 0x394($sp)
/* 00404be0 */  bgez       $v1, 0x404bec
/* 00404be4 */  move       $at, $v1
/* 00404be8 */  addiu      $at, $at, 3
/* 00404bec */  sra        $v1, $at, 2
/* 00404bf0 */  sw         $v1, 0x39c($sp)
/* 00404bf4 */  lui        $a0, 0x1000
/* 00404bf8 */  sw         $v1, 0x54($sp)
/* 00404bfc */  move       $s5, $a2
/* 00404c00 */  addiu      $a0, $a0, 0xe70
/* 00404c04 */  mflo       $v0
/* 00404c08 */  sw         $v0, 0x398($sp)
/* 00404c0c */  jal        0xf801250                                # getopt
/* 00404c10 */  sw         $v0, 0x58($sp)
/* 00404c14 */  lui        $a0, 0x1000
/* 00404c18 */  lw         $a1, 0x38c($sp)
/* 00404c1c */  jal        0xf801250                                # getopt
/* 00404c20 */  addiu      $a0, $a0, 0xe88
/* 00404c24 */  lui        $a0, 0x1000
/* 00404c28 */  lw         $a1, 0x398($sp)
/* 00404c2c */  jal        0xf801250                                # getopt
/* 00404c30 */  addiu      $a0, $a0, 0xe98
/* 00404c34 */  lui        $a0, 0x1000
/* 00404c38 */  lw         $a1, 0x39c($sp)
/* 00404c3c */  jal        0xf801250                                # getopt
/* 00404c40 */  addiu      $a0, $a0, 0xeb0
/* 00404c44 */  addiu      $a0, $sp, 0x37c
/* 00404c48 */  addiu      $a1, $zero, 0x24
/* 00404c4c */  addiu      $a2, $zero, 1
/* 00404c50 */  jal        0xf801198                                # printf
/* 00404c54 */  move       $a3, $s5
/* 00404c58 */  addiu      $s3, $zero, 1
/* 00404c5c */  bne        $v0, $s3, 0x404c70
/* 00404c60 */  nop        
/* 00404c64 */  lui        $s4, 0x1000
/* 00404c68 */  b          0x404c98
/* 00404c6c */  addiu      $s4, $s4, 0x36b4
/* 00404c70 */  lui        $s4, 0x1000
/* 00404c74 */  addiu      $s4, $s4, 0x36b4
/* 00404c78 */  lui        $a1, 0x1000
/* 00404c7c */  lui        $a2, 0x1000
/* 00404c80 */  addiu      $a2, $a2, 0xed8
/* 00404c84 */  addiu      $a1, $a1, 0xec4
/* 00404c88 */  jal        0xf801150                                # fclose
/* 00404c8c */  move       $a0, $s4
/* 00404c90 */  jal        0x40d3c0
/* 00404c94 */  move       $a0, $s3
/* 00404c98 */  lw         $t8, 0x38c($sp)
/* 00404c9c */  move       $s6, $zero
/* 00404ca0 */  blez       $t8, 0x404ce8
/* 00404ca4 */  nop        
/* 00404ca8 */  sw         $s0, 0x38($sp)
/* 00404cac */  move       $s0, $s1
/* 00404cb0 */  addiu      $v1, $sp, 0x3a0
/* 00404cb4 */  lw         $a0, ($s0)
/* 00404cb8 */  jal        0x40ade4
/* 00404cbc */  sw         $v1, 0x3c($sp)
/* 00404cc0 */  lw         $v1, 0x3c($sp)
/* 00404cc4 */  addiu      $s6, $s6, 1
/* 00404cc8 */  sw         $v0, -0x344($v1)
/* 00404ccc */  lw         $t9, 0x38c($sp)
/* 00404cd0 */  addiu      $s0, $s0, 4
/* 00404cd4 */  slt        $at, $s6, $t9
/* 00404cd8 */  bnez       $at, 0x404cb4
/* 00404cdc */  addiu      $v1, $v1, 4
/* 00404ce0 */  lw         $s0, 0x38($sp)
/* 00404ce4 */  move       $s6, $zero
/* 00404ce8 */  lw         $a2, 0x38c($sp)
/* 00404cec */  addiu      $a0, $sp, 0x5c
/* 00404cf0 */  addiu      $a1, $zero, 4
/* 00404cf4 */  jal        0xf801198                                # printf
/* 00404cf8 */  move       $a3, $s5
/* 00404cfc */  lw         $t0, 0x38c($sp)
/* 00404d00 */  nop        
/* 00404d04 */  beq        $v0, $t0, 0x404d30
/* 00404d08 */  lw         $t1, 0x38c($sp)
/* 00404d0c */  lui        $a1, 0x1000
/* 00404d10 */  lui        $a2, 0x1000
/* 00404d14 */  addiu      $a2, $a2, 0xf0c
/* 00404d18 */  addiu      $a1, $a1, 0xef8
/* 00404d1c */  jal        0xf801150                                # fclose
/* 00404d20 */  move       $a0, $s4
/* 00404d24 */  jal        0x40d3c0
/* 00404d28 */  move       $a0, $s3
/* 00404d2c */  lw         $t1, 0x38c($sp)
/* 00404d30 */  nop        
/* 00404d34 */  blez       $t1, 0x404dd4
/* 00404d38 */  lw         $a0, 0x390($sp)
/* 00404d3c */  sw         $s0, 0x38($sp)
/* 00404d40 */  move       $s0, $s1
/* 00404d44 */  sw         $s2, 0x34($sp)
/* 00404d48 */  lui        $s2, 0x1000
/* 00404d4c */  lui        $s1, 0x1000
/* 00404d50 */  addiu      $s1, $s1, 0xf1c
/* 00404d54 */  addiu      $s2, $s2, 0xf30
/* 00404d58 */  lw         $a0, ($s0)
/* 00404d5c */  jal        0x40a8e0
/* 00404d60 */  nop        
/* 00404d64 */  beqz       $v0, 0x404db0
/* 00404d68 */  move       $a0, $v0
/* 00404d6c */  addiu      $a1, $zero, 0x10
/* 00404d70 */  addiu      $a2, $zero, 1
/* 00404d74 */  jal        0xf801198                                # printf
/* 00404d78 */  move       $a3, $s5
/* 00404d7c */  beq        $v0, $s3, 0x404d9c
/* 00404d80 */  nop        
/* 00404d84 */  move       $a0, $s4
/* 00404d88 */  move       $a1, $s1
/* 00404d8c */  jal        0xf801150                                # fclose
/* 00404d90 */  move       $a2, $s2
/* 00404d94 */  jal        0x40d3c0
/* 00404d98 */  move       $a0, $s3
/* 00404d9c */  lw         $a0, ($s0)
/* 00404da0 */  jal        0x40a918
/* 00404da4 */  nop        
/* 00404da8 */  bnez       $v0, 0x404d6c
/* 00404dac */  move       $a0, $v0
/* 00404db0 */  lw         $t2, 0x38c($sp)
/* 00404db4 */  addiu      $s6, $s6, 1
/* 00404db8 */  slt        $at, $s6, $t2
/* 00404dbc */  bnez       $at, 0x404d58
/* 00404dc0 */  addiu      $s0, $s0, 4
/* 00404dc4 */  lw         $s0, 0x38($sp)
/* 00404dc8 */  lw         $s2, 0x34($sp)
/* 00404dcc */  nop        
/* 00404dd0 */  lw         $a0, 0x390($sp)
/* 00404dd4 */  lw         $a2, 0x58($sp)
/* 00404dd8 */  addiu      $a1, $zero, 0xc
/* 00404ddc */  jal        0xf801198                                # printf
/* 00404de0 */  move       $a3, $s5
/* 00404de4 */  lw         $t3, 0x58($sp)
/* 00404de8 */  nop        
/* 00404dec */  beq        $v0, $t3, 0x404e18
/* 00404df0 */  lw         $a0, 0x394($sp)
/* 00404df4 */  lui        $a1, 0x1000
/* 00404df8 */  lui        $a2, 0x1000
/* 00404dfc */  addiu      $a2, $a2, 0xf54
/* 00404e00 */  addiu      $a1, $a1, 0xf40
/* 00404e04 */  jal        0xf801150                                # fclose
/* 00404e08 */  move       $a0, $s4
/* 00404e0c */  jal        0x40d3c0
/* 00404e10 */  addiu      $a0, $zero, 1
/* 00404e14 */  lw         $a0, 0x394($sp)
/* 00404e18 */  lw         $a2, 0x54($sp)
/* 00404e1c */  addiu      $a1, $zero, 4
/* 00404e20 */  jal        0xf801198                                # printf
/* 00404e24 */  move       $a3, $s5
/* 00404e28 */  lw         $t4, 0x54($sp)
/* 00404e2c */  nop        
/* 00404e30 */  beq        $v0, $t4, 0x404e5c
/* 00404e34 */  lw         $ra, 0x2c($sp)
/* 00404e38 */  lui        $a1, 0x1000
/* 00404e3c */  lui        $a2, 0x1000
/* 00404e40 */  addiu      $a2, $a2, 0xf78
/* 00404e44 */  addiu      $a1, $a1, 0xf64
/* 00404e48 */  jal        0xf801150                                # fclose
/* 00404e4c */  move       $a0, $s4
/* 00404e50 */  jal        0x40d3c0
/* 00404e54 */  addiu      $a0, $zero, 1
/* 00404e58 */  lw         $ra, 0x2c($sp)
/* 00404e5c */  lw         $s1, 0x18($sp)
/* 00404e60 */  lw         $s3, 0x1c($sp)
/* 00404e64 */  lw         $s4, 0x20($sp)
/* 00404e68 */  lw         $s5, 0x24($sp)
/* 00404e6c */  lw         $s6, 0x28($sp)
/* 00404e70 */  jr         $ra
/* 00404e74 */  addiu      $sp, $sp, 0x3a0

# === gfo_read_file ===
glabel gfo_read_file
/* 00404e78 */  addiu      $sp, $sp, -0x3b8
/* 00404e7c */  sw         $a0, 0x3b8($sp)
/* 00404e80 */  sw         $ra, 0x14($sp)
/* 00404e84 */  sw         $a1, 0x3bc($sp)
/* 00404e88 */  lw         $a3, 0x3b8($sp)
/* 00404e8c */  addiu      $a1, $zero, 0x24
/* 00404e90 */  addiu      $a0, $sp, 0x394
/* 00404e94 */  jal        0xf801168                                # fprintf
/* 00404e98 */  addiu      $a2, $zero, 1
/* 00404e9c */  addiu      $at, $zero, 1
/* 00404ea0 */  beq        $v0, $at, 0x404ed0
/* 00404ea4 */  lw         $t6, 0x394($sp)
/* 00404ea8 */  lui        $a0, 0x1000
/* 00404eac */  lui        $a1, 0x1000
/* 00404eb0 */  lui        $a2, 0x1000
/* 00404eb4 */  addiu      $a2, $a2, 0xf9c
/* 00404eb8 */  addiu      $a1, $a1, 0xf88
/* 00404ebc */  jal        0xf801150                                # fclose
/* 00404ec0 */  addiu      $a0, $a0, 0x36b4
/* 00404ec4 */  jal        0x40d3c0
/* 00404ec8 */  addiu      $a0, $zero, 1
/* 00404ecc */  lw         $t6, 0x394($sp)
/* 00404ed0 */  lui        $at, 0x1357
/* 00404ed4 */  ori        $at, $at, 0x7531
/* 00404ed8 */  beq        $t6, $at, 0x404f00
/* 00404edc */  lw         $t7, 0x398($sp)
/* 00404ee0 */  lui        $a0, 0x1000
/* 00404ee4 */  lui        $a1, 0x1000
/* 00404ee8 */  addiu      $a1, $a1, 0xfbc
/* 00404eec */  jal        0xf801150                                # fclose
/* 00404ef0 */  addiu      $a0, $a0, 0x36b4
/* 00404ef4 */  b          0x4054c4
/* 00404ef8 */  move       $v0, $zero
/* 00404efc */  lw         $t7, 0x398($sp)
/* 00404f00 */  lui        $at, 1
/* 00404f04 */  ori        $at, $at, 2
/* 00404f08 */  beq        $t7, $at, 0x404f30
/* 00404f0c */  lw         $t8, 0x39c($sp)
/* 00404f10 */  lui        $a0, 0x1000
/* 00404f14 */  lui        $a1, 0x1000
/* 00404f18 */  addiu      $a1, $a1, 0xfe4
/* 00404f1c */  jal        0xf801150                                # fclose
/* 00404f20 */  addiu      $a0, $a0, 0x36b4
/* 00404f24 */  b          0x4054c4
/* 00404f28 */  move       $v0, $zero
/* 00404f2c */  lw         $t8, 0x39c($sp)
/* 00404f30 */  addiu      $at, $zero, 0x10
/* 00404f34 */  beq        $t8, $at, 0x404f5c
/* 00404f38 */  lw         $t9, 0x3a0($sp)
/* 00404f3c */  lui        $a0, 0x1000
/* 00404f40 */  lui        $a1, 0x1000
/* 00404f44 */  addiu      $a1, $a1, 0x1010
/* 00404f48 */  jal        0xf801150                                # fclose
/* 00404f4c */  addiu      $a0, $a0, 0x36b4
/* 00404f50 */  b          0x4054c4
/* 00404f54 */  move       $v0, $zero
/* 00404f58 */  lw         $t9, 0x3a0($sp)
/* 00404f5c */  addiu      $at, $zero, 0xc
/* 00404f60 */  beq        $t9, $at, 0x404f84
/* 00404f64 */  nop        
/* 00404f68 */  lui        $a0, 0x1000
/* 00404f6c */  lui        $a1, 0x1000
/* 00404f70 */  addiu      $a1, $a1, 0x103c
/* 00404f74 */  jal        0xf801150                                # fclose
/* 00404f78 */  addiu      $a0, $a0, 0x36b4
/* 00404f7c */  b          0x4054c4
/* 00404f80 */  move       $v0, $zero
/* 00404f84 */  sw         $s0, 0x3c($sp)
/* 00404f88 */  lw         $s0, 0x3a4($sp)
/* 00404f8c */  sw         $s2, 0x38($sp)
/* 00404f90 */  blez       $s0, 0x404fa0
/* 00404f94 */  slti       $at, $s0, 0xc9
/* 00404f98 */  bnez       $at, 0x404fcc
/* 00404f9c */  nop        
/* 00404fa0 */  lui        $a0, 0x1000
/* 00404fa4 */  lui        $a1, 0x1000
/* 00404fa8 */  lui        $a2, 0x1000
/* 00404fac */  addiu      $a2, $a2, 0x1080
/* 00404fb0 */  addiu      $a1, $a1, 0x106c
/* 00404fb4 */  jal        0xf801150                                # fclose
/* 00404fb8 */  addiu      $a0, $a0, 0x36b4
/* 00404fbc */  jal        0x40d3c0
/* 00404fc0 */  addiu      $a0, $zero, 1
/* 00404fc4 */  lw         $s0, 0x3a4($sp)
/* 00404fc8 */  nop        
/* 00404fcc */  lw         $a3, 0x3b8($sp)
/* 00404fd0 */  addiu      $a0, $sp, 0x74
/* 00404fd4 */  addiu      $a1, $zero, 4
/* 00404fd8 */  jal        0xf801168                                # fprintf
/* 00404fdc */  move       $a2, $s0
/* 00404fe0 */  lw         $s0, 0x3a4($sp)
/* 00404fe4 */  nop        
/* 00404fe8 */  beq        $v0, $s0, 0x40501c
/* 00404fec */  nop        
/* 00404ff0 */  lui        $a0, 0x1000
/* 00404ff4 */  lui        $a1, 0x1000
/* 00404ff8 */  lui        $a2, 0x1000
/* 00404ffc */  addiu      $a2, $a2, 0x10b4
/* 00405000 */  addiu      $a1, $a1, 0x10a0
/* 00405004 */  jal        0xf801150                                # fclose
/* 00405008 */  addiu      $a0, $a0, 0x36b4
/* 0040500c */  jal        0x40d3c0
/* 00405010 */  addiu      $a0, $zero, 1
/* 00405014 */  lw         $s0, 0x3a4($sp)
/* 00405018 */  nop        
/* 0040501c */  jal        0xf801208                                # free
/* 00405020 */  sll        $a0, $s0, 2
/* 00405024 */  bnez       $v0, 0x405038
/* 00405028 */  sw         $v0, 0x70($sp)
/* 0040502c */  lui        $a0, 0x1000
/* 00405030 */  jal        0x4092d4
/* 00405034 */  addiu      $a0, $a0, 0x10d8
/* 00405038 */  lw         $a0, 0x3b0($sp)
/* 0040503c */  nop        
/* 00405040 */  move       $at, $a0
/* 00405044 */  sll        $a0, $at, 2
/* 00405048 */  subu       $a0, $a0, $at
/* 0040504c */  jal        0xf801208                                # free
/* 00405050 */  sll        $a0, $a0, 2
/* 00405054 */  bnez       $v0, 0x405068
/* 00405058 */  sw         $v0, 0x6c($sp)
/* 0040505c */  lui        $a0, 0x1000
/* 00405060 */  jal        0x4092d4
/* 00405064 */  addiu      $a0, $a0, 0x10ec
/* 00405068 */  lw         $a0, 0x3b4($sp)
/* 0040506c */  nop        
/* 00405070 */  sll        $a0, $a0, 2
/* 00405074 */  jal        0xf801208                                # free
/* 00405078 */  addiu      $a0, $a0, 0xc
/* 0040507c */  bnez       $v0, 0x40509c
/* 00405080 */  move       $v1, $v0
/* 00405084 */  lui        $a0, 0x1000
/* 00405088 */  addiu      $a0, $a0, 0x1100
/* 0040508c */  jal        0x4092d4
/* 00405090 */  sw         $v1, 0x68($sp)
/* 00405094 */  lw         $v1, 0x68($sp)
/* 00405098 */  nop        
/* 0040509c */  andi       $v0, $v1, 0xf
/* 004050a0 */  addiu      $at, $zero, 4
/* 004050a4 */  bne        $v0, $at, 0x4050bc
/* 004050a8 */  addiu      $at, $zero, 8
/* 004050ac */  addiu      $v1, $v1, 0xc
/* 004050b0 */  b          0x4050e4
/* 004050b4 */  andi       $v0, $v1, 0xf
/* 004050b8 */  addiu      $at, $zero, 8
/* 004050bc */  bne        $v0, $at, 0x4050d4
/* 004050c0 */  addiu      $at, $zero, 0xc
/* 004050c4 */  addiu      $v1, $v1, 8
/* 004050c8 */  b          0x4050e4
/* 004050cc */  andi       $v0, $v1, 0xf
/* 004050d0 */  addiu      $at, $zero, 0xc
/* 004050d4 */  bne        $v0, $at, 0x4050e4
/* 004050d8 */  nop        
/* 004050dc */  addiu      $v1, $v1, 4
/* 004050e0 */  andi       $v0, $v1, 0xf
/* 004050e4 */  bnez       $v0, 0x4050f4
/* 004050e8 */  nop        
/* 004050ec */  b          0x405110
/* 004050f0 */  sw         $v1, 0x68($sp)
/* 004050f4 */  lui        $a0, 0x1000
/* 004050f8 */  lui        $a1, 0x1000
/* 004050fc */  addiu      $a1, $a1, 0x1114
/* 00405100 */  addiu      $a0, $a0, 0x36b4
/* 00405104 */  move       $a2, $v1
/* 00405108 */  jal        0xf801150                                # fclose
/* 0040510c */  sw         $v1, 0x68($sp)
/* 00405110 */  lw         $s0, 0x3a4($sp)
/* 00405114 */  lw         $v1, 0x68($sp)
/* 00405118 */  blez       $s0, 0x4052b0
/* 0040511c */  sw         $zero, 0x60($sp)
/* 00405120 */  sw         $s3, 0x30($sp)
/* 00405124 */  sw         $s5, 0x28($sp)
/* 00405128 */  sw         $s6, 0x24($sp)
/* 0040512c */  sw         $s7, 0x20($sp)
/* 00405130 */  sw         $fp, 0x1c($sp)
/* 00405134 */  sw         $s4, 0x2c($sp)
/* 00405138 */  lui        $fp, 0x1000
/* 0040513c */  lui        $s7, 0x1000
/* 00405140 */  lui        $s6, 0x1000
/* 00405144 */  lui        $s5, 0x1000
/* 00405148 */  lw         $s3, 0x70($sp)
/* 0040514c */  sw         $s1, 0x34($sp)
/* 00405150 */  addiu      $s5, $s5, 0x1144
/* 00405154 */  addiu      $s6, $s6, 0x1150
/* 00405158 */  addiu      $s7, $s7, 0x1164
/* 0040515c */  addiu      $fp, $fp, 0x1184
/* 00405160 */  addiu      $s4, $sp, 0x3b8
/* 00405164 */  sw         $v1, 0x68($sp)
/* 00405168 */  lw         $v1, 0x68($sp)
/* 0040516c */  jal        0x40a400
/* 00405170 */  move       $s2, $zero
/* 00405174 */  sw         $v0, ($s3)
/* 00405178 */  lw         $t0, -0x344($s4)
/* 0040517c */  nop        
/* 00405180 */  blez       $t0, 0x405274
/* 00405184 */  lw         $v0, 0x60($sp)
/* 00405188 */  jal        0xf801208                                # free
/* 0040518c */  addiu      $a0, $zero, 0x10
/* 00405190 */  bnez       $v0, 0x4051a0
/* 00405194 */  move       $s0, $v0
/* 00405198 */  jal        0x4092d4
/* 0040519c */  move       $a0, $s5
/* 004051a0 */  lw         $a3, 0x3b8($sp)
/* 004051a4 */  move       $a0, $s0
/* 004051a8 */  addiu      $a1, $zero, 0x10
/* 004051ac */  jal        0xf801168                                # fprintf
/* 004051b0 */  addiu      $a2, $zero, 1
/* 004051b4 */  addiu      $at, $zero, 1
/* 004051b8 */  beq        $v0, $at, 0x4051dc
/* 004051bc */  nop        
/* 004051c0 */  lui        $a0, 0x1000
/* 004051c4 */  addiu      $a0, $a0, 0x36b4
/* 004051c8 */  move       $a1, $s6
/* 004051cc */  jal        0xf801150                                # fclose
/* 004051d0 */  move       $a2, $s7
/* 004051d4 */  jal        0x40d3c0
/* 004051d8 */  addiu      $a0, $zero, 1
/* 004051dc */  lw         $t1, 8($s0)
/* 004051e0 */  lw         $t2, 0x3a8($sp)
/* 004051e4 */  addiu      $at, $zero, 0xc
/* 004051e8 */  subu       $s1, $t1, $t2
/* 004051ec */  div        $zero, $s1, $at
/* 004051f0 */  mflo       $s1
/* 004051f4 */  bltz       $s1, 0x405210
/* 004051f8 */  nop        
/* 004051fc */  lw         $t3, 0x3b0($sp)
/* 00405200 */  nop        
/* 00405204 */  slt        $at, $s1, $t3
/* 00405208 */  bnez       $at, 0x405234
/* 0040520c */  sll        $t5, $s1, 2
/* 00405210 */  lui        $a0, 0x1000
/* 00405214 */  lui        $a2, 0x1000
/* 00405218 */  addiu      $a2, $a2, 0x1198
/* 0040521c */  addiu      $a0, $a0, 0x36b4
/* 00405220 */  jal        0xf801150                                # fclose
/* 00405224 */  move       $a1, $fp
/* 00405228 */  jal        0x40d3c0
/* 0040522c */  addiu      $a0, $zero, 1
/* 00405230 */  sll        $t5, $s1, 2
/* 00405234 */  lw         $t4, 0x6c($sp)
/* 00405238 */  subu       $t5, $t5, $s1
/* 0040523c */  sll        $t5, $t5, 2
/* 00405240 */  addiu      $t7, $zero, -1
/* 00405244 */  addu       $t6, $t4, $t5
/* 00405248 */  sw         $t6, 8($s0)
/* 0040524c */  sw         $t7, 4($s0)
/* 00405250 */  lw         $a0, ($s3)
/* 00405254 */  jal        0x40a6d4
/* 00405258 */  move       $a1, $s0
/* 0040525c */  lw         $t8, -0x344($s4)
/* 00405260 */  addiu      $s2, $s2, 1
/* 00405264 */  slt        $at, $s2, $t8
/* 00405268 */  bnez       $at, 0x405188
/* 0040526c */  nop        
/* 00405270 */  lw         $v0, 0x60($sp)
/* 00405274 */  lw         $s0, 0x3a4($sp)
/* 00405278 */  addiu      $v0, $v0, 1
/* 0040527c */  slt        $at, $v0, $s0
/* 00405280 */  sw         $v0, 0x60($sp)
/* 00405284 */  addiu      $s3, $s3, 4
/* 00405288 */  bnez       $at, 0x405168
/* 0040528c */  addiu      $s4, $s4, 4
/* 00405290 */  lw         $s1, 0x34($sp)
/* 00405294 */  lw         $s3, 0x30($sp)
/* 00405298 */  lw         $s4, 0x2c($sp)
/* 0040529c */  lw         $s5, 0x28($sp)
/* 004052a0 */  lw         $s6, 0x24($sp)
/* 004052a4 */  lw         $s7, 0x20($sp)
/* 004052a8 */  lw         $fp, 0x1c($sp)
/* 004052ac */  sw         $zero, 0x60($sp)
/* 004052b0 */  lw         $v1, 0x68($sp)
/* 004052b4 */  lw         $a0, 0x6c($sp)
/* 004052b8 */  lw         $a2, 0x3b0($sp)
/* 004052bc */  lw         $a3, 0x3b8($sp)
/* 004052c0 */  jal        0xf801168                                # fprintf
/* 004052c4 */  addiu      $a1, $zero, 0xc
/* 004052c8 */  lw         $t9, 0x3b0($sp)
/* 004052cc */  nop        
/* 004052d0 */  beq        $v0, $t9, 0x405300
/* 004052d4 */  lw         $a0, 0x68($sp)
/* 004052d8 */  lui        $a0, 0x1000
/* 004052dc */  lui        $a1, 0x1000
/* 004052e0 */  lui        $a2, 0x1000
/* 004052e4 */  addiu      $a2, $a2, 0x11d0
/* 004052e8 */  addiu      $a1, $a1, 0x11bc
/* 004052ec */  jal        0xf801150                                # fclose
/* 004052f0 */  addiu      $a0, $a0, 0x36b4
/* 004052f4 */  jal        0x40d3c0
/* 004052f8 */  addiu      $a0, $zero, 1
/* 004052fc */  lw         $a0, 0x68($sp)
/* 00405300 */  lw         $a2, 0x3b4($sp)
/* 00405304 */  lw         $a3, 0x3b8($sp)
/* 00405308 */  jal        0xf801168                                # fprintf
/* 0040530c */  addiu      $a1, $zero, 4
/* 00405310 */  lw         $t0, 0x3b4($sp)
/* 00405314 */  nop        
/* 00405318 */  beq        $v0, $t0, 0x405348
/* 0040531c */  lw         $t1, 0x3b0($sp)
/* 00405320 */  lui        $a0, 0x1000
/* 00405324 */  lui        $a1, 0x1000
/* 00405328 */  lui        $a2, 0x1000
/* 0040532c */  addiu      $a2, $a2, 0x1208
/* 00405330 */  addiu      $a1, $a1, 0x11f4
/* 00405334 */  jal        0xf801150                                # fclose
/* 00405338 */  addiu      $a0, $a0, 0x36b4
/* 0040533c */  jal        0x40d3c0
/* 00405340 */  addiu      $a0, $zero, 1
/* 00405344 */  lw         $t1, 0x3b0($sp)
/* 00405348 */  lw         $s2, 0x6c($sp)
/* 0040534c */  blez       $t1, 0x4054a8
/* 00405350 */  lw         $t5, 0x3a4($sp)
/* 00405354 */  sw         $s3, 0x30($sp)
/* 00405358 */  sw         $s4, 0x2c($sp)
/* 0040535c */  sw         $s5, 0x28($sp)
/* 00405360 */  sw         $s6, 0x24($sp)
/* 00405364 */  lui        $s6, 0x1000
/* 00405368 */  lui        $s5, 0x1000
/* 0040536c */  lui        $s4, 0x1000
/* 00405370 */  lui        $s3, 0x1000
/* 00405374 */  addiu      $s3, $s3, 0x1228
/* 00405378 */  addiu      $s4, $s4, 0x123c
/* 0040537c */  addiu      $s5, $s5, 0x1260
/* 00405380 */  addiu      $s6, $s6, 0x1274
/* 00405384 */  sw         $s1, 0x34($sp)
/* 00405388 */  lw         $v0, ($s2)
/* 0040538c */  nop        
/* 00405390 */  beqz       $v0, 0x4053fc
/* 00405394 */  nop        
/* 00405398 */  lw         $t2, 0x3a8($sp)
/* 0040539c */  addiu      $at, $zero, 0xc
/* 004053a0 */  subu       $s1, $v0, $t2
/* 004053a4 */  div        $zero, $s1, $at
/* 004053a8 */  mflo       $s1
/* 004053ac */  bltz       $s1, 0x4053c8
/* 004053b0 */  nop        
/* 004053b4 */  lw         $t3, 0x3b0($sp)
/* 004053b8 */  nop        
/* 004053bc */  slt        $at, $s1, $t3
/* 004053c0 */  bnez       $at, 0x4053e8
/* 004053c4 */  sll        $t5, $s1, 2
/* 004053c8 */  lui        $a0, 0x1000
/* 004053cc */  addiu      $a0, $a0, 0x36b4
/* 004053d0 */  move       $a1, $s3
/* 004053d4 */  jal        0xf801150                                # fclose
/* 004053d8 */  move       $a2, $s4
/* 004053dc */  jal        0x40d3c0
/* 004053e0 */  addiu      $a0, $zero, 1
/* 004053e4 */  sll        $t5, $s1, 2
/* 004053e8 */  lw         $t4, 0x6c($sp)
/* 004053ec */  subu       $t5, $t5, $s1
/* 004053f0 */  sll        $t5, $t5, 2
/* 004053f4 */  addu       $t6, $t4, $t5
/* 004053f8 */  sw         $t6, ($s2)
/* 004053fc */  lw         $v0, 4($s2)
/* 00405400 */  nop        
/* 00405404 */  beqz       $v0, 0x405474
/* 00405408 */  lw         $t2, 0x60($sp)
/* 0040540c */  lw         $t7, 0x3ac($sp)
/* 00405410 */  nop        
/* 00405414 */  subu       $s0, $v0, $t7
/* 00405418 */  bgez       $s0, 0x405424
/* 0040541c */  move       $at, $s0
/* 00405420 */  addiu      $at, $at, 3
/* 00405424 */  sra        $s0, $at, 2
/* 00405428 */  bltz       $s0, 0x405444
/* 0040542c */  nop        
/* 00405430 */  lw         $t8, 0x3b4($sp)
/* 00405434 */  nop        
/* 00405438 */  slt        $at, $s0, $t8
/* 0040543c */  bnez       $at, 0x405464
/* 00405440 */  lw         $t9, 0x68($sp)
/* 00405444 */  lui        $a0, 0x1000
/* 00405448 */  addiu      $a0, $a0, 0x36b4
/* 0040544c */  move       $a1, $s5
/* 00405450 */  jal        0xf801150                                # fclose
/* 00405454 */  move       $a2, $s6
/* 00405458 */  jal        0x40d3c0
/* 0040545c */  addiu      $a0, $zero, 1
/* 00405460 */  lw         $t9, 0x68($sp)
/* 00405464 */  sll        $t0, $s0, 2
/* 00405468 */  addu       $t1, $t9, $t0
/* 0040546c */  sw         $t1, 4($s2)
/* 00405470 */  lw         $t2, 0x60($sp)
/* 00405474 */  lw         $t4, 0x3b0($sp)
/* 00405478 */  addiu      $t3, $t2, 1
/* 0040547c */  slt        $at, $t3, $t4
/* 00405480 */  sw         $t3, 0x60($sp)
/* 00405484 */  bnez       $at, 0x405388
/* 00405488 */  addiu      $s2, $s2, 0xc
/* 0040548c */  lw         $s1, 0x34($sp)
/* 00405490 */  lw         $s3, 0x30($sp)
/* 00405494 */  lw         $s4, 0x2c($sp)
/* 00405498 */  lw         $s5, 0x28($sp)
/* 0040549c */  lw         $s6, 0x24($sp)
/* 004054a0 */  nop        
/* 004054a4 */  lw         $t5, 0x3a4($sp)
/* 004054a8 */  lw         $t6, 0x3bc($sp)
/* 004054ac */  nop        
/* 004054b0 */  sw         $t5, ($t6)
/* 004054b4 */  lw         $s2, 0x38($sp)
/* 004054b8 */  lw         $s0, 0x3c($sp)
/* 004054bc */  lw         $v0, 0x70($sp)
/* 004054c0 */  nop        
/* 004054c4 */  lw         $ra, 0x14($sp)
/* 004054c8 */  addiu      $sp, $sp, 0x3b8
/* 004054cc */  jr         $ra
/* 004054d0 */  nop        
/* 004054d4 */  nop        
/* 004054d8 */  nop        
/* 004054dc */  nop        

# === compute_bounding_box ===
glabel compute_bounding_box
/* 004054e0 */  addiu      $sp, $sp, -0x18
/* 004054e4 */  sw         $ra, 0x14($sp)
/* 004054e8 */  lui        $a0, 0x1000
/* 004054ec */  jal        0x4055d0                                 # compute_far_clip
/* 004054f0 */  addiu      $a0, $a0, 0x1290
/* 004054f4 */  beqz       $v0, 0x405510
/* 004054f8 */  addiu      $v0, $zero, 0x101
/* 004054fc */  lui        $v0, 0x1000
/* 00405500 */  lw         $v0, 0x1290($v0)
/* 00405504 */  b          0x405514
/* 00405508 */  lw         $ra, 0x14($sp)
/* 0040550c */  addiu      $v0, $zero, 0x101
/* 00405510 */  lw         $ra, 0x14($sp)
/* 00405514 */  addiu      $sp, $sp, 0x18
/* 00405518 */  jr         $ra
/* 0040551c */  nop        

# === compute_entity_bbox ===
glabel compute_entity_bbox
/* 00405520 */  addiu      $sp, $sp, -0x18
/* 00405524 */  move       $a3, $a0
/* 00405528 */  sw         $ra, 0x14($sp)
/* 0040552c */  lui        $a0, 0x1000
/* 00405530 */  lui        $a2, 0x1000
/* 00405534 */  addiu      $a2, $a2, 0x3ed0
/* 00405538 */  addiu      $a0, $a0, 0x36b4
/* 0040553c */  jal        0xf801150                                # fclose
/* 00405540 */  addiu      $a1, $gp, -0x7d00
/* 00405544 */  lui        $a2, 0x1000
/* 00405548 */  lui        $a3, 0x1000
/* 0040554c */  lw         $a3, 0x1298($a3)
/* 00405550 */  lw         $a2, 0x129c($a2)
/* 00405554 */  lui        $a0, 0x1000
/* 00405558 */  lui        $a1, 0x1000
/* 0040555c */  addiu      $a1, $a1, 0x12a0
/* 00405560 */  jal        0xf801150                                # fclose
/* 00405564 */  addiu      $a0, $a0, 0x36b4
/* 00405568 */  lui        $a0, 0x1000
/* 0040556c */  lui        $a1, 0x1000
/* 00405570 */  lw         $a2, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00405574 */  addiu      $a1, $a1, 0x12b8
/* 00405578 */  jal        0xf801150                                # fclose
/* 0040557c */  addiu      $a0, $a0, 0x36b4
/* 00405580 */  lw         $ra, 0x14($sp)
/* 00405584 */  addiu      $sp, $sp, 0x18
/* 00405588 */  jr         $ra
/* 0040558c */  nop        
/* 00405590 */  addiu      $sp, $sp, -0x18
/* 00405594 */  sw         $ra, 0x14($sp)
/* 00405598 */  jal        0x405ec4
/* 0040559c */  nop        
/* 004055a0 */  jal        0x409a00
/* 004055a4 */  nop        
/* 004055a8 */  beqz       $v0, 0x4055bc
/* 004055ac */  addiu      $v1, $zero, 1
/* 004055b0 */  b          0x4055bc
/* 004055b4 */  move       $v1, $zero
/* 004055b8 */  addiu      $v1, $zero, 1
/* 004055bc */  lw         $ra, 0x14($sp)
/* 004055c0 */  addiu      $sp, $sp, 0x18
/* 004055c4 */  jr         $ra
/* 004055c8 */  move       $v0, $v1
/* 004055cc */  nop        

# === compute_far_clip ===
glabel compute_far_clip
/* 004055d0 */  addiu      $sp, $sp, -0x58
/* 004055d4 */  sw         $s1, 0x20($sp)
/* 004055d8 */  sw         $s0, 0x1c($sp)
/* 004055dc */  addiu      $s0, $zero, 0x122
/* 004055e0 */  move       $s1, $a0
/* 004055e4 */  sw         $ra, 0x24($sp)
/* 004055e8 */  jal        0x4057d4                                 # build_sorted_list
/* 004055ec */  move       $a0, $s1
/* 004055f0 */  bnez       $v0, 0x405600
/* 004055f4 */  move       $t0, $v0
/* 004055f8 */  b          0x4057c0
/* 004055fc */  move       $v0, $zero
/* 00405600 */  lw         $v0, ($s1)
/* 00405604 */  nop        
/* 00405608 */  beq        $s0, $v0, 0x4055e8
/* 0040560c */  nop        
/* 00405610 */  b          0x4057a8
/* 00405614 */  move       $v1, $v0
/* 00405618 */  lw         $a0, 4($s1)
/* 0040561c */  jal        0x405ce8                                 # filter_display_list
/* 00405620 */  sw         $t0, 0x54($sp)
/* 00405624 */  lw         $t0, 0x54($sp)
/* 00405628 */  beqz       $v0, 0x405638
/* 0040562c */  nop        
/* 00405630 */  b          0x4057bc
/* 00405634 */  sw         $v0, ($s1)
/* 00405638 */  lw         $t6, 0xc($s1)
/* 0040563c */  lw         $a3, 4($s1)
/* 00405640 */  sw         $t6, 0x10($sp)
/* 00405644 */  lw         $t7, 8($s1)
/* 00405648 */  lui        $a0, 0x1000
/* 0040564c */  lui        $a1, 0x1000
/* 00405650 */  lui        $a2, 0x1000
/* 00405654 */  sw         $t0, 0x54($sp)
/* 00405658 */  addiu      $a2, $a2, 0x3ed0
/* 0040565c */  addiu      $a1, $a1, 0x13f4
/* 00405660 */  addiu      $a0, $a0, 0x36b4
/* 00405664 */  jal        0xf801150                                # fclose
/* 00405668 */  sw         $t7, 0x14($sp)
/* 0040566c */  lw         $t0, 0x54($sp)
/* 00405670 */  b          0x4057c0
/* 00405674 */  move       $v0, $t0
/* 00405678 */  lw         $s0, 4($s1)
/* 0040567c */  move       $a1, $zero
/* 00405680 */  move       $v0, $s0
/* 00405684 */  lbu        $v1, ($v0)
/* 00405688 */  addiu      $v0, $v0, 1
/* 0040568c */  beqz       $v1, 0x4056b8
/* 00405690 */  nop        
/* 00405694 */  addiu      $a0, $zero, 0x2e
/* 00405698 */  bne        $v1, $a0, 0x4056a8
/* 0040569c */  nop        
/* 004056a0 */  b          0x4056b8
/* 004056a4 */  addiu      $a1, $zero, 1
/* 004056a8 */  lbu        $v1, ($v0)
/* 004056ac */  addiu      $v0, $v0, 1
/* 004056b0 */  bnez       $v1, 0x405698
/* 004056b4 */  nop        
/* 004056b8 */  beqz       $a1, 0x405738
/* 004056bc */  move       $a0, $s0
/* 004056c0 */  move       $a0, $s0
/* 004056c4 */  addiu      $a1, $sp, 0x40
/* 004056c8 */  jal        0x40d830
/* 004056cc */  sw         $t0, 0x54($sp)
/* 004056d0 */  cvt.s.d    $f4, $f0
/* 004056d4 */  lw         $t8, 0x40($sp)
/* 004056d8 */  swc1       $f4, -0x7a7c($gp)                        # .sbss @ 0x100042f4
/* 004056dc */  lw         $s0, 4($s1)
/* 004056e0 */  lw         $t0, 0x54($sp)
/* 004056e4 */  bne        $t8, $s0, 0x40572c
/* 004056e8 */  addiu      $t2, $zero, 0x119
/* 004056ec */  lw         $t9, 0xc($s1)
/* 004056f0 */  lui        $a0, 0x1000
/* 004056f4 */  sw         $t9, 0x10($sp)
/* 004056f8 */  lw         $t1, 8($s1)
/* 004056fc */  lui        $a1, 0x1000
/* 00405700 */  lui        $a2, 0x1000
/* 00405704 */  sw         $t0, 0x54($sp)
/* 00405708 */  addiu      $a2, $a2, 0x3ed0
/* 0040570c */  addiu      $a1, $a1, 0x1430
/* 00405710 */  addiu      $a0, $a0, 0x36b4
/* 00405714 */  move       $a3, $s0
/* 00405718 */  jal        0xf801150                                # fclose
/* 0040571c */  sw         $t1, 0x14($sp)
/* 00405720 */  lw         $t0, 0x54($sp)
/* 00405724 */  nop        
/* 00405728 */  addiu      $t2, $zero, 0x119
/* 0040572c */  b          0x4057bc
/* 00405730 */  sw         $t2, ($s1)
/* 00405734 */  move       $a0, $s0
/* 00405738 */  addiu      $a1, $sp, 0x40
/* 0040573c */  move       $a2, $zero
/* 00405740 */  jal        0x40dcc0
/* 00405744 */  sw         $t0, 0x54($sp)
/* 00405748 */  sw         $v0, -0x7a7c($gp)                        # .sbss @ 0x100042f4
/* 0040574c */  lw         $s0, 4($s1)
/* 00405750 */  lw         $t3, 0x40($sp)
/* 00405754 */  lw         $t0, 0x54($sp)
/* 00405758 */  bne        $t3, $s0, 0x4057a0
/* 0040575c */  addiu      $t6, $zero, 0x118
/* 00405760 */  lw         $t4, 0xc($s1)
/* 00405764 */  lui        $a0, 0x1000
/* 00405768 */  sw         $t4, 0x10($sp)
/* 0040576c */  lw         $t5, 8($s1)
/* 00405770 */  lui        $a1, 0x1000
/* 00405774 */  lui        $a2, 0x1000
/* 00405778 */  sw         $t0, 0x54($sp)
/* 0040577c */  addiu      $a2, $a2, 0x3ed0
/* 00405780 */  addiu      $a1, $a1, 0x1460
/* 00405784 */  addiu      $a0, $a0, 0x36b4
/* 00405788 */  move       $a3, $s0
/* 0040578c */  jal        0xf801150                                # fclose
/* 00405790 */  sw         $t5, 0x14($sp)
/* 00405794 */  lw         $t0, 0x54($sp)
/* 00405798 */  nop        
/* 0040579c */  addiu      $t6, $zero, 0x118
/* 004057a0 */  b          0x4057bc
/* 004057a4 */  sw         $t6, ($s1)
/* 004057a8 */  addiu      $at, $zero, 0x120
/* 004057ac */  beq        $v1, $at, 0x405678
/* 004057b0 */  addiu      $at, $zero, 0x121
/* 004057b4 */  beq        $v1, $at, 0x405618
/* 004057b8 */  nop        
/* 004057bc */  move       $v0, $t0
/* 004057c0 */  lw         $ra, 0x24($sp)
/* 004057c4 */  lw         $s0, 0x1c($sp)
/* 004057c8 */  lw         $s1, 0x20($sp)
/* 004057cc */  jr         $ra
/* 004057d0 */  addiu      $sp, $sp, 0x58

# === build_sorted_list ===
glabel build_sorted_list
/* 004057d4 */  addiu      $sp, $sp, -0x158
/* 004057d8 */  sw         $fp, 0x28($sp)
/* 004057dc */  sw         $ra, 0x2c($sp)
/* 004057e0 */  sw         $s6, 0x20($sp)
/* 004057e4 */  sw         $s7, 0x24($sp)
/* 004057e8 */  sw         $s2, 0x18($sp)
/* 004057ec */  sw         $s3, 0x1c($sp)
/* 004057f0 */  move       $s6, $a0
/* 004057f4 */  sw         $s1, 0x14($sp)
/* 004057f8 */  move       $fp, $zero
/* 004057fc */  move       $s7, $zero
/* 00405800 */  jal        0x405df8
/* 00405804 */  move       $s2, $zero
/* 00405808 */  addiu      $s3, $zero, -1
/* 0040580c */  beq        $v0, $s3, 0x405c58
/* 00405810 */  move       $s1, $v0
/* 00405814 */  sw         $s4, 0x34($sp)
/* 00405818 */  sw         $s5, 0x30($sp)
/* 0040581c */  addiu      $s5, $zero, 0x2a
/* 00405820 */  addiu      $s4, $zero, 0x2f
/* 00405824 */  sw         $s0, 0x38($sp)
/* 00405828 */  slti       $at, $s2, 0x100
/* 0040582c */  bnez       $at, 0x405858
/* 00405830 */  nop        
/* 00405834 */  lui        $a0, 0x1000
/* 00405838 */  lui        $a1, 0x1000
/* 0040583c */  lui        $a2, 0x1000
/* 00405840 */  addiu      $a2, $a2, 0x14a8
/* 00405844 */  addiu      $a1, $a1, 0x1494
/* 00405848 */  jal        0xf801150                                # fclose
/* 0040584c */  addiu      $a0, $a0, 0x36b4
/* 00405850 */  jal        0x40d3c0
/* 00405854 */  addiu      $a0, $zero, 1
/* 00405858 */  lui        $v0, 0x1000
/* 0040585c */  addu       $v0, $v0, $s1
/* 00405860 */  lbu        $v0, 0x32e1($v0)
/* 00405864 */  nop        
/* 00405868 */  andi       $t6, $v0, 3
/* 0040586c */  beqz       $t6, 0x405914
/* 00405870 */  andi       $t0, $v0, 4
/* 00405874 */  beqz       $fp, 0x40588c
/* 00405878 */  nop        
/* 0040587c */  addu       $t7, $sp, $s2
/* 00405880 */  sb         $s1, 0x48($t7)
/* 00405884 */  b          0x405c38
/* 00405888 */  addiu      $s2, $s2, 1
/* 0040588c */  beqz       $s7, 0x4058f4
/* 00405890 */  nop        
/* 00405894 */  andi       $t8, $v0, 0x80
/* 00405898 */  bnez       $t8, 0x4058b0
/* 0040589c */  addiu      $at, $zero, 0x78
/* 004058a0 */  beq        $s1, $at, 0x4058b0
/* 004058a4 */  addiu      $at, $zero, 0x58
/* 004058a8 */  bne        $s1, $at, 0x4058c0
/* 004058ac */  nop        
/* 004058b0 */  addu       $t9, $sp, $s2
/* 004058b4 */  sb         $s1, 0x48($t9)
/* 004058b8 */  b          0x405c38
/* 004058bc */  addiu      $s2, $s2, 1
/* 004058c0 */  lui        $a0, 0x1000
/* 004058c4 */  addiu      $a0, $a0, 0x14c8
/* 004058c8 */  move       $a1, $s1
/* 004058cc */  jal        0xf801250                                # getopt
/* 004058d0 */  move       $a2, $s1
/* 004058d4 */  lui        $a0, 0x1000
/* 004058d8 */  jal        0x405ed8                                 # set_near_far
/* 004058dc */  addiu      $a0, $a0, 0x14e8
/* 004058e0 */  lw         $s0, 0x38($sp)
/* 004058e4 */  lw         $s4, 0x34($sp)
/* 004058e8 */  lw         $s5, 0x30($sp)
/* 004058ec */  b          0x405cc4
/* 004058f0 */  move       $v0, $zero
/* 004058f4 */  addiu      $a0, $s6, 0xc
/* 004058f8 */  addiu      $a1, $s6, 8
/* 004058fc */  addiu      $fp, $zero, 1
/* 00405900 */  jal        0x405dd0
/* 00405904 */  addiu      $s2, $zero, 1
/* 00405908 */  b          0x405c38
/* 0040590c */  sb         $s1, 0x48($sp)
/* 00405910 */  andi       $t0, $v0, 4
/* 00405914 */  beqz       $t0, 0x40595c
/* 00405918 */  andi       $t2, $v0, 0x10
/* 0040591c */  bnez       $fp, 0x405930
/* 00405920 */  addu       $t1, $sp, $s2
/* 00405924 */  beqz       $s7, 0x40593c
/* 00405928 */  nop        
/* 0040592c */  addu       $t1, $sp, $s2
/* 00405930 */  sb         $s1, 0x48($t1)
/* 00405934 */  b          0x405c38
/* 00405938 */  addiu      $s2, $s2, 1
/* 0040593c */  addiu      $a0, $s6, 0xc
/* 00405940 */  addiu      $a1, $s6, 8
/* 00405944 */  addiu      $s2, $zero, 1
/* 00405948 */  jal        0x405dd0
/* 0040594c */  addiu      $s7, $zero, 1
/* 00405950 */  b          0x405c38
/* 00405954 */  sb         $s1, 0x48($sp)
/* 00405958 */  andi       $t2, $v0, 0x10
/* 0040595c */  beqz       $t2, 0x405ba8
/* 00405960 */  andi       $t6, $v0, 8
/* 00405964 */  beqz       $s7, 0x405984
/* 00405968 */  addiu      $at, $zero, 0x2e
/* 0040596c */  bne        $s1, $at, 0x405984
/* 00405970 */  nop        
/* 00405974 */  addu       $t3, $sp, $s2
/* 00405978 */  sb         $s1, 0x48($t3)
/* 0040597c */  b          0x405c38
/* 00405980 */  addiu      $s2, $s2, 1
/* 00405984 */  bnez       $fp, 0x4059a0
/* 00405988 */  addiu      $t4, $sp, 0x158
/* 0040598c */  beqz       $s7, 0x4059f4
/* 00405990 */  addiu      $at, $zero, 0x2e
/* 00405994 */  beq        $s1, $at, 0x4059f8
/* 00405998 */  addiu      $a0, $s6, 0xc
/* 0040599c */  addiu      $t4, $sp, 0x158
/* 004059a0 */  addu       $s0, $s2, $t4
/* 004059a4 */  jal        0x405de8
/* 004059a8 */  move       $a0, $s1
/* 004059ac */  sb         $zero, -0x110($s0)
/* 004059b0 */  lw         $a0, 4($s6)
/* 004059b4 */  jal        0xf8012f0                                # exit
/* 004059b8 */  addiu      $a1, $sp, 0x48
/* 004059bc */  beqz       $fp, 0x4059d0
/* 004059c0 */  nop        
/* 004059c4 */  addiu      $t5, $zero, 0x121
/* 004059c8 */  b          0x4059e0
/* 004059cc */  sw         $t5, ($s6)
/* 004059d0 */  beqz       $s7, 0x4059e4
/* 004059d4 */  lw         $s0, 0x38($sp)
/* 004059d8 */  addiu      $t6, $zero, 0x120
/* 004059dc */  sw         $t6, ($s6)
/* 004059e0 */  lw         $s0, 0x38($sp)
/* 004059e4 */  lw         $s4, 0x34($sp)
/* 004059e8 */  lw         $s5, 0x30($sp)
/* 004059ec */  b          0x405cc4
/* 004059f0 */  addiu      $v0, $zero, 1
/* 004059f4 */  addiu      $a0, $s6, 0xc
/* 004059f8 */  jal        0x405dd0
/* 004059fc */  addiu      $a1, $s6, 8
/* 00405a00 */  lw         $t7, 4($s6)
/* 00405a04 */  addiu      $at, $zero, 0x2d
/* 00405a08 */  sb         $s1, ($t7)
/* 00405a0c */  lw         $t8, 4($s6)
/* 00405a10 */  beq        $s1, $at, 0x405ab8
/* 00405a14 */  sb         $zero, 1($t8)
/* 00405a18 */  beq        $s1, $s4, 0x405ad4
/* 00405a1c */  addiu      $at, $zero, 0x5b
/* 00405a20 */  beq        $s1, $at, 0x405a80
/* 00405a24 */  addiu      $at, $zero, 0x5d
/* 00405a28 */  beq        $s1, $at, 0x405a9c
/* 00405a2c */  addiu      $at, $zero, 0x7b
/* 00405a30 */  beq        $s1, $at, 0x405a48
/* 00405a34 */  addiu      $at, $zero, 0x7d
/* 00405a38 */  beq        $s1, $at, 0x405a68
/* 00405a3c */  addiu      $t0, $zero, 0x11c
/* 00405a40 */  b          0x405b84
/* 00405a44 */  nop        
/* 00405a48 */  addiu      $t9, $zero, 0x11b
/* 00405a4c */  sw         $t9, ($s6)
/* 00405a50 */  lw         $s5, 0x30($sp)
/* 00405a54 */  lw         $s4, 0x34($sp)
/* 00405a58 */  lw         $s0, 0x38($sp)
/* 00405a5c */  b          0x405cc4
/* 00405a60 */  addiu      $v0, $zero, 1
/* 00405a64 */  addiu      $t0, $zero, 0x11c
/* 00405a68 */  sw         $t0, ($s6)
/* 00405a6c */  lw         $s5, 0x30($sp)
/* 00405a70 */  lw         $s4, 0x34($sp)
/* 00405a74 */  lw         $s0, 0x38($sp)
/* 00405a78 */  b          0x405cc4
/* 00405a7c */  addiu      $v0, $zero, 1
/* 00405a80 */  addiu      $t1, $zero, 0x11d
/* 00405a84 */  sw         $t1, ($s6)
/* 00405a88 */  lw         $s5, 0x30($sp)
/* 00405a8c */  lw         $s4, 0x34($sp)
/* 00405a90 */  lw         $s0, 0x38($sp)
/* 00405a94 */  b          0x405cc4
/* 00405a98 */  addiu      $v0, $zero, 1
/* 00405a9c */  addiu      $t2, $zero, 0x11e
/* 00405aa0 */  sw         $t2, ($s6)
/* 00405aa4 */  lw         $s5, 0x30($sp)
/* 00405aa8 */  lw         $s4, 0x34($sp)
/* 00405aac */  lw         $s0, 0x38($sp)
/* 00405ab0 */  b          0x405cc4
/* 00405ab4 */  addiu      $v0, $zero, 1
/* 00405ab8 */  addiu      $t3, $zero, 0x117
/* 00405abc */  sw         $t3, ($s6)
/* 00405ac0 */  lw         $s5, 0x30($sp)
/* 00405ac4 */  lw         $s4, 0x34($sp)
/* 00405ac8 */  lw         $s0, 0x38($sp)
/* 00405acc */  b          0x405cc4
/* 00405ad0 */  addiu      $v0, $zero, 1
/* 00405ad4 */  jal        0x405df8
/* 00405ad8 */  nop        
/* 00405adc */  beq        $v0, $s5, 0x405b08
/* 00405ae0 */  move       $s1, $v0
/* 00405ae4 */  jal        0x405de8
/* 00405ae8 */  move       $a0, $s1
/* 00405aec */  addiu      $t4, $zero, 0x11f
/* 00405af0 */  sw         $t4, ($s6)
/* 00405af4 */  lw         $s5, 0x30($sp)
/* 00405af8 */  lw         $s4, 0x34($sp)
/* 00405afc */  lw         $s0, 0x38($sp)
/* 00405b00 */  b          0x405cc4
/* 00405b04 */  addiu      $v0, $zero, 1
/* 00405b08 */  jal        0x405df8
/* 00405b0c */  nop        
/* 00405b10 */  bne        $v0, $s3, 0x405b24
/* 00405b14 */  move       $s0, $v0
/* 00405b18 */  lui        $a0, 0x1000
/* 00405b1c */  jal        0x405ed8                                 # set_near_far
/* 00405b20 */  addiu      $a0, $a0, 0x1514
/* 00405b24 */  jal        0x405df8
/* 00405b28 */  nop        
/* 00405b2c */  beq        $v0, $s3, 0x405b70
/* 00405b30 */  move       $s1, $v0
/* 00405b34 */  bne        $s0, $s5, 0x405b60
/* 00405b38 */  nop        
/* 00405b3c */  bne        $v0, $s4, 0x405b60
/* 00405b40 */  nop        
/* 00405b44 */  addiu      $t5, $zero, 0x122
/* 00405b48 */  sw         $t5, ($s6)
/* 00405b4c */  lw         $s5, 0x30($sp)
/* 00405b50 */  lw         $s4, 0x34($sp)
/* 00405b54 */  lw         $s0, 0x38($sp)
/* 00405b58 */  b          0x405cc4
/* 00405b5c */  addiu      $v0, $zero, 1
/* 00405b60 */  jal        0x405df8
/* 00405b64 */  move       $s0, $s1
/* 00405b68 */  bne        $v0, $s3, 0x405b34
/* 00405b6c */  move       $s1, $v0
/* 00405b70 */  lui        $a0, 0x1000
/* 00405b74 */  jal        0x405ed8                                 # set_near_far
/* 00405b78 */  addiu      $a0, $a0, 0x1538
/* 00405b7c */  b          0x405c38
/* 00405b80 */  nop        
/* 00405b84 */  lui        $a0, 0x1000
/* 00405b88 */  jal        0x405ed8                                 # set_near_far
/* 00405b8c */  addiu      $a0, $a0, 0x155c
/* 00405b90 */  lw         $s0, 0x38($sp)
/* 00405b94 */  lw         $s4, 0x34($sp)
/* 00405b98 */  lw         $s5, 0x30($sp)
/* 00405b9c */  b          0x405cc4
/* 00405ba0 */  move       $v0, $zero
/* 00405ba4 */  andi       $t6, $v0, 8
/* 00405ba8 */  beqz       $t6, 0x405c0c
/* 00405bac */  nop        
/* 00405bb0 */  bnez       $fp, 0x405bc4
/* 00405bb4 */  addu       $t7, $sp, $s2
/* 00405bb8 */  beqz       $s7, 0x405c38
/* 00405bbc */  nop        
/* 00405bc0 */  addu       $t7, $sp, $s2
/* 00405bc4 */  sb         $zero, 0x48($t7)
/* 00405bc8 */  lw         $a0, 4($s6)
/* 00405bcc */  jal        0xf8012f0                                # exit
/* 00405bd0 */  addiu      $a1, $sp, 0x48
/* 00405bd4 */  beqz       $fp, 0x405be8
/* 00405bd8 */  nop        
/* 00405bdc */  addiu      $t8, $zero, 0x121
/* 00405be0 */  b          0x405bf8
/* 00405be4 */  sw         $t8, ($s6)
/* 00405be8 */  beqz       $s7, 0x405bfc
/* 00405bec */  lw         $s0, 0x38($sp)
/* 00405bf0 */  addiu      $t9, $zero, 0x120
/* 00405bf4 */  sw         $t9, ($s6)
/* 00405bf8 */  lw         $s0, 0x38($sp)
/* 00405bfc */  lw         $s4, 0x34($sp)
/* 00405c00 */  lw         $s5, 0x30($sp)
/* 00405c04 */  b          0x405cc4
/* 00405c08 */  addiu      $v0, $zero, 1
/* 00405c0c */  addiu      $a0, $s6, 0xc
/* 00405c10 */  jal        0x405dd0
/* 00405c14 */  addiu      $a1, $s6, 8
/* 00405c18 */  lui        $a0, 0x1000
/* 00405c1c */  jal        0x405ed8                                 # set_near_far
/* 00405c20 */  addiu      $a0, $a0, 0x1580
/* 00405c24 */  lw         $s0, 0x38($sp)
/* 00405c28 */  lw         $s4, 0x34($sp)
/* 00405c2c */  lw         $s5, 0x30($sp)
/* 00405c30 */  b          0x405cc4
/* 00405c34 */  move       $v0, $zero
/* 00405c38 */  jal        0x405df8
/* 00405c3c */  nop        
/* 00405c40 */  bne        $v0, $s3, 0x405828
/* 00405c44 */  move       $s1, $v0
/* 00405c48 */  lw         $s0, 0x38($sp)
/* 00405c4c */  lw         $s4, 0x34($sp)
/* 00405c50 */  lw         $s5, 0x30($sp)
/* 00405c54 */  nop        
/* 00405c58 */  bnez       $fp, 0x405c6c
/* 00405c5c */  addu       $t0, $sp, $s2
/* 00405c60 */  beqz       $s7, 0x405ca8
/* 00405c64 */  nop        
/* 00405c68 */  addu       $t0, $sp, $s2
/* 00405c6c */  sb         $zero, 0x48($t0)
/* 00405c70 */  lw         $a0, 4($s6)
/* 00405c74 */  jal        0xf8012f0                                # exit
/* 00405c78 */  addiu      $a1, $sp, 0x48
/* 00405c7c */  beqz       $fp, 0x405c90
/* 00405c80 */  nop        
/* 00405c84 */  addiu      $t1, $zero, 0x121
/* 00405c88 */  b          0x405ca0
/* 00405c8c */  sw         $t1, ($s6)
/* 00405c90 */  beqz       $s7, 0x405ca0
/* 00405c94 */  nop        
/* 00405c98 */  addiu      $t2, $zero, 0x120
/* 00405c9c */  sw         $t2, ($s6)
/* 00405ca0 */  b          0x405cc4
/* 00405ca4 */  addiu      $v0, $zero, 1
/* 00405ca8 */  lw         $t3, 4($s6)
/* 00405cac */  sw         $zero, ($s6)
/* 00405cb0 */  addiu      $a0, $s6, 0xc
/* 00405cb4 */  addiu      $a1, $s6, 8
/* 00405cb8 */  jal        0x405dd0
/* 00405cbc */  sb         $zero, ($t3)
/* 00405cc0 */  addiu      $v0, $zero, 1
/* 00405cc4 */  lw         $ra, 0x2c($sp)
/* 00405cc8 */  lw         $s1, 0x14($sp)
/* 00405ccc */  lw         $s2, 0x18($sp)
/* 00405cd0 */  lw         $s3, 0x1c($sp)
/* 00405cd4 */  lw         $s6, 0x20($sp)
/* 00405cd8 */  lw         $s7, 0x24($sp)
/* 00405cdc */  lw         $fp, 0x28($sp)
/* 00405ce0 */  jr         $ra
/* 00405ce4 */  addiu      $sp, $sp, 0x158

# === filter_display_list ===
glabel filter_display_list
/* 00405ce8 */  lui        $t6, 0x1000
/* 00405cec */  lw         $t6, 0x12d4($t6)
/* 00405cf0 */  addiu      $sp, $sp, -0x38
/* 00405cf4 */  sw         $s1, 0x18($sp)
/* 00405cf8 */  move       $s1, $a0
/* 00405cfc */  sw         $ra, 0x1c($sp)
/* 00405d00 */  beqz       $t6, 0x405d5c
/* 00405d04 */  move       $v0, $zero
/* 00405d08 */  sw         $s0, 0x24($sp)
/* 00405d0c */  lui        $s0, 0x1000
/* 00405d10 */  addiu      $s0, $s0, 0x12d0
/* 00405d14 */  lw         $a1, ($s0)
/* 00405d18 */  nop        
/* 00405d1c */  beq        $s1, $a1, 0x405d34
/* 00405d20 */  nop        
/* 00405d24 */  jal        0xf8012e8                                # fwrite
/* 00405d28 */  move       $a0, $s1
/* 00405d2c */  bnez       $v0, 0x405d44
/* 00405d30 */  nop        
/* 00405d34 */  lw         $v0, 4($s0)
/* 00405d38 */  lw         $s0, 0x24($sp)
/* 00405d3c */  b          0x405d64
/* 00405d40 */  lw         $ra, 0x1c($sp)
/* 00405d44 */  lw         $t7, 0xc($s0)
/* 00405d48 */  addiu      $s0, $s0, 8
/* 00405d4c */  bnez       $t7, 0x405d14
/* 00405d50 */  nop        
/* 00405d54 */  lw         $s0, 0x24($sp)
/* 00405d58 */  nop        
/* 00405d5c */  move       $v0, $zero
/* 00405d60 */  lw         $ra, 0x1c($sp)
/* 00405d64 */  lw         $s1, 0x18($sp)
/* 00405d68 */  jr         $ra
/* 00405d6c */  addiu      $sp, $sp, 0x38
/* 00405d70 */  lui        $t6, 0x1000
/* 00405d74 */  lw         $t6, 0x12d4($t6)
/* 00405d78 */  move       $v0, $zero
/* 00405d7c */  beqz       $t6, 0x405db8
/* 00405d80 */  nop        
/* 00405d84 */  lui        $t7, 0x1000
/* 00405d88 */  addiu      $t7, $t7, 0x12d0
/* 00405d8c */  lw         $v0, 4($t7)
/* 00405d90 */  move       $v1, $t7
/* 00405d94 */  bne        $a0, $v0, 0x405da8
/* 00405d98 */  nop        
/* 00405d9c */  lw         $v0, ($v1)
/* 00405da0 */  jr         $ra
/* 00405da4 */  nop        
/* 00405da8 */  lw         $v0, 0xc($v1)
/* 00405dac */  addiu      $v1, $v1, 8
/* 00405db0 */  bnez       $v0, 0x405d94
/* 00405db4 */  nop        
/* 00405db8 */  lw         $v0, -0x7c7c($gp)                        # .sdata @ 0x100040f4
/* 00405dbc */  nop        
/* 00405dc0 */  jr         $ra
/* 00405dc4 */  nop        
/* 00405dc8 */  nop        
/* 00405dcc */  nop        
/* 00405dd0 */  lw         $t6, -0x7ab4($gp)                        # .sbss @ 0x100042bc
/* 00405dd4 */  nop        
/* 00405dd8 */  sw         $t6, ($a0)
/* 00405ddc */  lw         $t7, -0x7ab8($gp)                        # .sbss @ 0x100042b8
/* 00405de0 */  jr         $ra
/* 00405de4 */  sw         $t7, ($a1)
/* 00405de8 */  addiu      $t6, $zero, 1
/* 00405dec */  sw         $a0, -0x7abc($gp)                        # .sbss @ 0x100042b4
/* 00405df0 */  jr         $ra
/* 00405df4 */  sw         $t6, -0x7c70($gp)                        # .sdata @ 0x10004100
/* 00405df8 */  lw         $t6, -0x7c70($gp)                        # .sdata @ 0x10004100
/* 00405dfc */  addiu      $sp, $sp, -0x18
/* 00405e00 */  beqz       $t6, 0x405e14
/* 00405e04 */  sw         $ra, 0x14($sp)
/* 00405e08 */  lw         $v0, -0x7abc($gp)                        # .sbss @ 0x100042b4
/* 00405e0c */  b          0x405eb4
/* 00405e10 */  sw         $zero, -0x7c70($gp)                      # .sdata @ 0x10004100
/* 00405e14 */  lui        $t7, 0x1000
/* 00405e18 */  lw         $t7, 0x41f0($t7)
/* 00405e1c */  nop        
/* 00405e20 */  beqz       $t7, 0x405e3c
/* 00405e24 */  nop        
/* 00405e28 */  lw         $a0, -0x7ac0($gp)                        # .sbss @ 0x100042b0
/* 00405e2c */  jal        0xf8014b0                                # getenv
/* 00405e30 */  nop        
/* 00405e34 */  b          0x405e80
/* 00405e38 */  move       $a0, $v0
/* 00405e3c */  lw         $a0, -0x7ac0($gp)                        # .sbss @ 0x100042b0
/* 00405e40 */  nop        
/* 00405e44 */  lw         $v0, ($a0)
/* 00405e48 */  nop        
/* 00405e4c */  addiu      $v0, $v0, -1
/* 00405e50 */  bgez       $v0, 0x405e68
/* 00405e54 */  sw         $v0, ($a0)
/* 00405e58 */  jal        0xf8010e0                                # strcpy
/* 00405e5c */  nop        
/* 00405e60 */  b          0x405e7c
/* 00405e64 */  move       $v1, $v0
/* 00405e68 */  lw         $v0, 4($a0)
/* 00405e6c */  nop        
/* 00405e70 */  lbu        $v1, ($v0)
/* 00405e74 */  addiu      $t8, $v0, 1
/* 00405e78 */  sw         $t8, 4($a0)
/* 00405e7c */  move       $a0, $v1
/* 00405e80 */  addiu      $at, $zero, 0xa
/* 00405e84 */  bne        $a0, $at, 0x405ea0
/* 00405e88 */  nop        
/* 00405e8c */  lw         $t9, -0x7ab4($gp)                        # .sbss @ 0x100042bc
/* 00405e90 */  sw         $zero, -0x7ab8($gp)                      # .sbss @ 0x100042b8
/* 00405e94 */  addiu      $t0, $t9, 1
/* 00405e98 */  b          0x405eb0
/* 00405e9c */  sw         $t0, -0x7ab4($gp)                        # .sbss @ 0x100042bc
/* 00405ea0 */  lw         $t1, -0x7ab8($gp)                        # .sbss @ 0x100042b8
/* 00405ea4 */  nop        
/* 00405ea8 */  addiu      $t2, $t1, 1
/* 00405eac */  sw         $t2, -0x7ab8($gp)                        # .sbss @ 0x100042b8
/* 00405eb0 */  move       $v0, $a0
/* 00405eb4 */  lw         $ra, 0x14($sp)
/* 00405eb8 */  addiu      $sp, $sp, 0x18
/* 00405ebc */  jr         $ra
/* 00405ec0 */  nop        
/* 00405ec4 */  addiu      $t6, $zero, 1
/* 00405ec8 */  sw         $a0, -0x7ac0($gp)                        # .sbss @ 0x100042b0
/* 00405ecc */  sw         $t6, -0x7ab4($gp)                        # .sbss @ 0x100042bc
/* 00405ed0 */  jr         $ra
/* 00405ed4 */  sw         $zero, -0x7ab8($gp)                      # .sbss @ 0x100042b8

# === set_near_far ===
glabel set_near_far
/* 00405ed8 */  addiu      $sp, $sp, -0x18
/* 00405edc */  move       $a1, $a0
/* 00405ee0 */  sw         $ra, 0x14($sp)
/* 00405ee4 */  lui        $a0, 0x1000
/* 00405ee8 */  jal        0xf801250                                # getopt
/* 00405eec */  addiu      $a0, $a0, 0x15a0
/* 00405ef0 */  lw         $ra, 0x14($sp)
/* 00405ef4 */  addiu      $sp, $sp, 0x18
/* 00405ef8 */  jr         $ra
/* 00405efc */  nop        

# === set_initial_position ===
glabel set_initial_position
/* 00405f00 */  addiu      $sp, $sp, -0x18
/* 00405f04 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00405f08 */  sw         $ra, 0x14($sp)
/* 00405f0c */  sw         $a0, 0x18($sp)
/* 00405f10 */  lw         $v0, 0x140($t6)
/* 00405f14 */  lui        $at, 7
/* 00405f18 */  ori        $at, $at, 0xa120
/* 00405f1c */  slt        $at, $v0, $at
/* 00405f20 */  bnez       $at, 0x405f5c
/* 00405f24 */  nop        
/* 00405f28 */  lui        $a0, 0x1000
/* 00405f2c */  lui        $a1, 0x1000
/* 00405f30 */  lui        $a2, 0x1000
/* 00405f34 */  addiu      $a2, $a2, 0x15c4
/* 00405f38 */  addiu      $a1, $a1, 0x15b0
/* 00405f3c */  jal        0xf801150                                # fclose
/* 00405f40 */  addiu      $a0, $a0, 0x36b4
/* 00405f44 */  jal        0x40d3c0
/* 00405f48 */  addiu      $a0, $zero, 1
/* 00405f4c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00405f50 */  nop        
/* 00405f54 */  lw         $v0, 0x140($t7)
/* 00405f58 */  nop        
/* 00405f5c */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00405f60 */  lw         $t8, 0x18($sp)
/* 00405f64 */  lw         $t0, 0x108($t9)
/* 00405f68 */  sll        $t1, $v0, 2
/* 00405f6c */  addu       $t2, $t0, $t1
/* 00405f70 */  sw         $t8, ($t2)
/* 00405f74 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00405f78 */  nop        
/* 00405f7c */  lw         $t4, 0x140($t3)
/* 00405f80 */  nop        
/* 00405f84 */  addiu      $t5, $t4, 1
/* 00405f88 */  sw         $t5, 0x140($t3)
/* 00405f8c */  lw         $ra, 0x14($sp)
/* 00405f90 */  addiu      $sp, $sp, 0x18
/* 00405f94 */  jr         $ra
/* 00405f98 */  nop        

# === mat4_set_translate ===
glabel mat4_set_translate
/* 00405f9c */  addiu      $sp, $sp, -0x28
/* 00405fa0 */  sw         $a2, 0x30($sp)
/* 00405fa4 */  lwc1       $f4, 0x30($sp)
/* 00405fa8 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00405fac */  sw         $ra, 0x14($sp)
/* 00405fb0 */  swc1       $f12, 0x1c($sp)
/* 00405fb4 */  swc1       $f14, 0x20($sp)
/* 00405fb8 */  swc1       $f4, 0x24($sp)
/* 00405fbc */  lw         $v0, 0x144($t6)
/* 00405fc0 */  nop        
/* 00405fc4 */  blez       $v0, 0x406000
/* 00405fc8 */  nop        
/* 00405fcc */  lui        $a0, 0x1000
/* 00405fd0 */  lui        $a1, 0x1000
/* 00405fd4 */  lui        $a2, 0x1000
/* 00405fd8 */  addiu      $a2, $a2, 0x15e4
/* 00405fdc */  addiu      $a1, $a1, 0x15d0
/* 00405fe0 */  jal        0xf801150                                # fclose
/* 00405fe4 */  addiu      $a0, $a0, 0x36b4
/* 00405fe8 */  jal        0x40d3c0
/* 00405fec */  addiu      $a0, $zero, 1
/* 00405ff0 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00405ff4 */  nop        
/* 00405ff8 */  lw         $v0, 0x144($t7)
/* 00405ffc */  nop        
/* 00406000 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406004 */  sll        $t0, $v0, 2
/* 00406008 */  lw         $t9, 0x10c($t8)
/* 0040600c */  subu       $t0, $t0, $v0
/* 00406010 */  addiu      $t2, $sp, 0x1c
/* 00406014 */  lw         $at, ($t2)
/* 00406018 */  sll        $t0, $t0, 2
/* 0040601c */  lw         $t3, 4($t2)
/* 00406020 */  addu       $t1, $t9, $t0
/* 00406024 */  sw         $at, ($t1)
/* 00406028 */  lw         $at, 8($t2)
/* 0040602c */  sw         $t3, 4($t1)
/* 00406030 */  sw         $at, 8($t1)
/* 00406034 */  lw         $t4, 0x144($t8)
/* 00406038 */  nop        
/* 0040603c */  addiu      $t5, $t4, 1
/* 00406040 */  sw         $t5, 0x144($t8)
/* 00406044 */  lw         $ra, 0x14($sp)
/* 00406048 */  addiu      $sp, $sp, 0x28
/* 0040604c */  jr         $ra
/* 00406050 */  nop        

# === mat4_set_rotate_x ===
glabel mat4_set_rotate_x
/* 00406054 */  addiu      $sp, $sp, -0x28
/* 00406058 */  sw         $a2, 0x30($sp)
/* 0040605c */  lwc1       $f4, 0x30($sp)
/* 00406060 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406064 */  sw         $ra, 0x14($sp)
/* 00406068 */  swc1       $f12, 0x1c($sp)
/* 0040606c */  swc1       $f14, 0x20($sp)
/* 00406070 */  swc1       $f4, 0x24($sp)
/* 00406074 */  lw         $v0, 0x148($t6)
/* 00406078 */  nop        
/* 0040607c */  slti       $at, $v0, 0x61a8
/* 00406080 */  bnez       $at, 0x4060bc
/* 00406084 */  nop        
/* 00406088 */  lui        $a0, 0x1000
/* 0040608c */  lui        $a1, 0x1000
/* 00406090 */  lui        $a2, 0x1000
/* 00406094 */  addiu      $a2, $a2, 0x1604
/* 00406098 */  addiu      $a1, $a1, 0x15f0
/* 0040609c */  jal        0xf801150                                # fclose
/* 004060a0 */  addiu      $a0, $a0, 0x36b4
/* 004060a4 */  jal        0x40d3c0
/* 004060a8 */  addiu      $a0, $zero, 1
/* 004060ac */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004060b0 */  nop        
/* 004060b4 */  lw         $v0, 0x148($t7)
/* 004060b8 */  nop        
/* 004060bc */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004060c0 */  sll        $t0, $v0, 2
/* 004060c4 */  lw         $t9, 0x114($t8)
/* 004060c8 */  subu       $t0, $t0, $v0
/* 004060cc */  addiu      $t2, $sp, 0x1c
/* 004060d0 */  lw         $at, ($t2)
/* 004060d4 */  sll        $t0, $t0, 2
/* 004060d8 */  lw         $t3, 4($t2)
/* 004060dc */  addu       $t1, $t9, $t0
/* 004060e0 */  sw         $at, ($t1)
/* 004060e4 */  lw         $at, 8($t2)
/* 004060e8 */  sw         $t3, 4($t1)
/* 004060ec */  sw         $at, 8($t1)
/* 004060f0 */  lw         $t4, 0x148($t8)
/* 004060f4 */  nop        
/* 004060f8 */  addiu      $t5, $t4, 1
/* 004060fc */  sw         $t5, 0x148($t8)
/* 00406100 */  lw         $ra, 0x14($sp)
/* 00406104 */  addiu      $sp, $sp, 0x28
/* 00406108 */  jr         $ra
/* 0040610c */  nop        

# === mat4_set_rotate_y ===
glabel mat4_set_rotate_y
/* 00406110 */  addiu      $sp, $sp, -0x28
/* 00406114 */  sw         $a2, 0x30($sp)
/* 00406118 */  lwc1       $f4, 0x30($sp)
/* 0040611c */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406120 */  sw         $ra, 0x14($sp)
/* 00406124 */  swc1       $f12, 0x1c($sp)
/* 00406128 */  swc1       $f14, 0x20($sp)
/* 0040612c */  swc1       $f4, 0x24($sp)
/* 00406130 */  lw         $v0, 0x14c($t6)
/* 00406134 */  lui        $at, 6
/* 00406138 */  ori        $at, $at, 0x1a80
/* 0040613c */  slt        $at, $v0, $at
/* 00406140 */  bnez       $at, 0x40617c
/* 00406144 */  nop        
/* 00406148 */  lui        $a0, 0x1000
/* 0040614c */  lui        $a1, 0x1000
/* 00406150 */  lui        $a2, 0x1000
/* 00406154 */  addiu      $a2, $a2, 0x1624
/* 00406158 */  addiu      $a1, $a1, 0x1610
/* 0040615c */  jal        0xf801150                                # fclose
/* 00406160 */  addiu      $a0, $a0, 0x36b4
/* 00406164 */  jal        0x40d3c0
/* 00406168 */  addiu      $a0, $zero, 1
/* 0040616c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00406170 */  nop        
/* 00406174 */  lw         $v0, 0x14c($t7)
/* 00406178 */  nop        
/* 0040617c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406180 */  sll        $t0, $v0, 2
/* 00406184 */  lw         $t9, 0x110($t8)
/* 00406188 */  subu       $t0, $t0, $v0
/* 0040618c */  addiu      $t2, $sp, 0x1c
/* 00406190 */  lw         $at, ($t2)
/* 00406194 */  sll        $t0, $t0, 2
/* 00406198 */  lw         $t3, 4($t2)
/* 0040619c */  addu       $t1, $t9, $t0
/* 004061a0 */  sw         $at, ($t1)
/* 004061a4 */  lw         $at, 8($t2)
/* 004061a8 */  sw         $t3, 4($t1)
/* 004061ac */  sw         $at, 8($t1)
/* 004061b0 */  lw         $t4, 0x14c($t8)
/* 004061b4 */  nop        
/* 004061b8 */  addiu      $t5, $t4, 1
/* 004061bc */  sw         $t5, 0x14c($t8)
/* 004061c0 */  lw         $ra, 0x14($sp)
/* 004061c4 */  addiu      $sp, $sp, 0x28
/* 004061c8 */  jr         $ra
/* 004061cc */  nop        

# === mat4_set_rotate_z ===
glabel mat4_set_rotate_z
/* 004061d0 */  addiu      $sp, $sp, -0x58
/* 004061d4 */  sw         $s1, 0x18($sp)
/* 004061d8 */  sw         $ra, 0x1c($sp)
/* 004061dc */  mtc1       $zero, $f0
/* 004061e0 */  lwc1       $f2, -0x7ee0($gp)                        # .lit4: 1
/* 004061e4 */  swc1       $f0, 0x40($sp)
/* 004061e8 */  swc1       $f0, 0x44($sp)
/* 004061ec */  swc1       $f0, 0x48($sp)
/* 004061f0 */  swc1       $f0, 0x4c($sp)
/* 004061f4 */  swc1       $f0, 0x54($sp)
/* 004061f8 */  swc1       $f2, 0x34($sp)
/* 004061fc */  move       $s1, $a0
/* 00406200 */  swc1       $f2, 0x38($sp)
/* 00406204 */  swc1       $f2, 0x3c($sp)
/* 00406208 */  move       $a0, $s1
/* 0040620c */  jal        0x40a8e0
/* 00406210 */  swc1       $f2, 0x50($sp)
/* 00406214 */  beqz       $v0, 0x4062ec
/* 00406218 */  move       $a2, $v0
/* 0040621c */  sw         $s0, 0x24($sp)
/* 00406220 */  lui        $s0, 0x1000
/* 00406224 */  addiu      $s0, $s0, 0x1630
/* 00406228 */  lw         $v1, ($v0)
/* 0040622c */  nop        
/* 00406230 */  addiu      $t6, $v1, -0x112
/* 00406234 */  sltiu      $at, $t6, 5
/* 00406238 */  beqz       $at, 0x4062c8
/* 0040623c */  nop        
/* 00406240 */  sll        $t6, $t6, 2
/* 00406244 */  lui        $at, 0x1000
/* 00406248 */  addu       $at, $at, $t6
/* 0040624c */  lw         $t6, ($at)
/* 00406250 */  nop        
/* 00406254 */  jr         $t6
/* 00406258 */  nop        
/* 0040625c */  lwc1       $f4, 4($v0)
/* 00406260 */  nop        
/* 00406264 */  swc1       $f4, 0x34($sp)
/* 00406268 */  lwc1       $f6, 8($v0)
/* 0040626c */  nop        
/* 00406270 */  swc1       $f6, 0x38($sp)
/* 00406274 */  lwc1       $f8, 0xc($v0)
/* 00406278 */  b          0x4062d4
/* 0040627c */  swc1       $f8, 0x3c($sp)
/* 00406280 */  lwc1       $f10, 4($v0)
/* 00406284 */  nop        
/* 00406288 */  swc1       $f10, 0x40($sp)
/* 0040628c */  lwc1       $f16, 8($v0)
/* 00406290 */  nop        
/* 00406294 */  swc1       $f16, 0x44($sp)
/* 00406298 */  lwc1       $f18, 0xc($v0)
/* 0040629c */  b          0x4062d4
/* 004062a0 */  swc1       $f18, 0x48($sp)
/* 004062a4 */  lwc1       $f4, 4($v0)
/* 004062a8 */  b          0x4062d4
/* 004062ac */  swc1       $f4, 0x4c($sp)
/* 004062b0 */  lwc1       $f6, 4($v0)
/* 004062b4 */  b          0x4062d4
/* 004062b8 */  swc1       $f6, 0x50($sp)
/* 004062bc */  lwc1       $f8, 4($v0)
/* 004062c0 */  b          0x4062d4
/* 004062c4 */  swc1       $f8, 0x54($sp)
/* 004062c8 */  lw         $a1, ($a2)
/* 004062cc */  jal        0xf801250                                # getopt
/* 004062d0 */  move       $a0, $s0
/* 004062d4 */  jal        0x40a918
/* 004062d8 */  move       $a0, $s1
/* 004062dc */  bnez       $v0, 0x406228
/* 004062e0 */  move       $a2, $v0
/* 004062e4 */  lw         $s0, 0x24($sp)
/* 004062e8 */  nop        
/* 004062ec */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004062f0 */  nop        
/* 004062f4 */  lw         $v0, 0x15c($t7)
/* 004062f8 */  nop        
/* 004062fc */  slti       $at, $v0, 0x64
/* 00406300 */  bnez       $at, 0x40633c
/* 00406304 */  nop        
/* 00406308 */  lui        $a0, 0x1000
/* 0040630c */  lui        $a1, 0x1000
/* 00406310 */  lui        $a2, 0x1000
/* 00406314 */  addiu      $a2, $a2, 0x1668
/* 00406318 */  addiu      $a1, $a1, 0x1654
/* 0040631c */  jal        0xf801150                                # fclose
/* 00406320 */  addiu      $a0, $a0, 0x36b4
/* 00406324 */  jal        0x40d3c0
/* 00406328 */  addiu      $a0, $zero, 1
/* 0040632c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406330 */  nop        
/* 00406334 */  lw         $v0, 0x15c($t8)
/* 00406338 */  nop        
/* 0040633c */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00406340 */  sll        $t1, $v0, 3
/* 00406344 */  lw         $t0, 0x124($t9)
/* 00406348 */  addu       $t1, $t1, $v0
/* 0040634c */  sll        $t1, $t1, 2
/* 00406350 */  addiu      $t3, $sp, 0x34
/* 00406354 */  addiu      $t4, $t3, 0x24
/* 00406358 */  addu       $t2, $t0, $t1
/* 0040635c */  lw         $at, ($t3)
/* 00406360 */  addiu      $t3, $t3, 0xc
/* 00406364 */  sw         $at, ($t2)
/* 00406368 */  lw         $at, -8($t3)
/* 0040636c */  addiu      $t2, $t2, 0xc
/* 00406370 */  sw         $at, -8($t2)
/* 00406374 */  lw         $at, -4($t3)
/* 00406378 */  bne        $t3, $t4, 0x40635c
/* 0040637c */  sw         $at, -4($t2)
/* 00406380 */  lw         $t5, 0x15c($t9)
/* 00406384 */  nop        
/* 00406388 */  addiu      $t6, $t5, 1
/* 0040638c */  sw         $t6, 0x15c($t9)
/* 00406390 */  lw         $ra, 0x1c($sp)
/* 00406394 */  lw         $s1, 0x18($sp)
/* 00406398 */  jr         $ra
/* 0040639c */  addiu      $sp, $sp, 0x58

# === mat4_mul ===
glabel mat4_mul
/* 004063a0 */  addiu      $sp, $sp, -0x30
/* 004063a4 */  sw         $a2, 0x38($sp)
/* 004063a8 */  sw         $a3, 0x3c($sp)
/* 004063ac */  lwc1       $f6, 0x3c($sp)
/* 004063b0 */  lwc1       $f4, 0x38($sp)
/* 004063b4 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 004063b8 */  sw         $ra, 0x14($sp)
/* 004063bc */  swc1       $f12, 0x20($sp)
/* 004063c0 */  swc1       $f14, 0x24($sp)
/* 004063c4 */  swc1       $f6, 0x2c($sp)
/* 004063c8 */  swc1       $f4, 0x28($sp)
/* 004063cc */  lw         $v1, 0x150($t6)
/* 004063d0 */  nop        
/* 004063d4 */  slti       $at, $v1, 0x14
/* 004063d8 */  bnez       $at, 0x406414
/* 004063dc */  sw         $v1, 0x1c($sp)
/* 004063e0 */  lui        $a0, 0x1000
/* 004063e4 */  lui        $a1, 0x1000
/* 004063e8 */  lui        $a2, 0x1000
/* 004063ec */  addiu      $a2, $a2, 0x168c
/* 004063f0 */  addiu      $a1, $a1, 0x1678
/* 004063f4 */  jal        0xf801150                                # fclose
/* 004063f8 */  addiu      $a0, $a0, 0x36b4
/* 004063fc */  jal        0x40d3c0
/* 00406400 */  addiu      $a0, $zero, 1
/* 00406404 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00406408 */  nop        
/* 0040640c */  lw         $v1, 0x150($t7)
/* 00406410 */  nop        
/* 00406414 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406418 */  addiu      $t2, $sp, 0x20
/* 0040641c */  lw         $t9, 0x118($t8)
/* 00406420 */  lw         $at, ($t2)
/* 00406424 */  sll        $t0, $v1, 4
/* 00406428 */  lw         $t3, 4($t2)
/* 0040642c */  addu       $t1, $t9, $t0
/* 00406430 */  sw         $at, ($t1)
/* 00406434 */  lw         $at, 8($t2)
/* 00406438 */  sw         $t3, 4($t1)
/* 0040643c */  lw         $t3, 0xc($t2)
/* 00406440 */  sw         $at, 8($t1)
/* 00406444 */  sw         $t3, 0xc($t1)
/* 00406448 */  lw         $t4, 0x150($t8)
/* 0040644c */  nop        
/* 00406450 */  addiu      $t5, $t4, 1
/* 00406454 */  sw         $t5, 0x150($t8)
/* 00406458 */  lw         $ra, 0x14($sp)
/* 0040645c */  lw         $v0, 0x1c($sp)
/* 00406460 */  jr         $ra
/* 00406464 */  addiu      $sp, $sp, 0x30

# === mat4_transform_point ===
glabel mat4_transform_point
/* 00406468 */  addiu      $sp, $sp, -0x30
/* 0040646c */  sw         $a2, 0x38($sp)
/* 00406470 */  lwc1       $f4, 0x38($sp)
/* 00406474 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406478 */  sw         $ra, 0x14($sp)
/* 0040647c */  swc1       $f12, 0x24($sp)
/* 00406480 */  swc1       $f14, 0x28($sp)
/* 00406484 */  swc1       $f4, 0x2c($sp)
/* 00406488 */  lw         $v1, 0x154($t6)
/* 0040648c */  nop        
/* 00406490 */  slti       $at, $v1, 0x14
/* 00406494 */  bnez       $at, 0x4064d0
/* 00406498 */  sw         $v1, 0x20($sp)
/* 0040649c */  lui        $a0, 0x1000
/* 004064a0 */  lui        $a1, 0x1000
/* 004064a4 */  lui        $a2, 0x1000
/* 004064a8 */  addiu      $a2, $a2, 0x16b0
/* 004064ac */  addiu      $a1, $a1, 0x169c
/* 004064b0 */  jal        0xf801150                                # fclose
/* 004064b4 */  addiu      $a0, $a0, 0x36b4
/* 004064b8 */  jal        0x40d3c0
/* 004064bc */  addiu      $a0, $zero, 1
/* 004064c0 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004064c4 */  nop        
/* 004064c8 */  lw         $v1, 0x154($t7)
/* 004064cc */  nop        
/* 004064d0 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004064d4 */  sll        $t0, $v1, 2
/* 004064d8 */  lw         $t9, 0x11c($t8)
/* 004064dc */  subu       $t0, $t0, $v1
/* 004064e0 */  addiu      $t2, $sp, 0x24
/* 004064e4 */  lw         $at, ($t2)
/* 004064e8 */  sll        $t0, $t0, 2
/* 004064ec */  lw         $t3, 4($t2)
/* 004064f0 */  addu       $t1, $t9, $t0
/* 004064f4 */  sw         $at, ($t1)
/* 004064f8 */  lw         $at, 8($t2)
/* 004064fc */  sw         $t3, 4($t1)
/* 00406500 */  sw         $at, 8($t1)
/* 00406504 */  lw         $t4, 0x154($t8)
/* 00406508 */  nop        
/* 0040650c */  addiu      $t5, $t4, 1
/* 00406510 */  sw         $t5, 0x154($t8)
/* 00406514 */  lw         $ra, 0x14($sp)
/* 00406518 */  lw         $v0, 0x20($sp)
/* 0040651c */  jr         $ra
/* 00406520 */  addiu      $sp, $sp, 0x30

# === mat4_mul2 ===
glabel mat4_mul2
/* 00406524 */  addiu      $sp, $sp, -0x30
/* 00406528 */  sw         $a2, 0x38($sp)
/* 0040652c */  lwc1       $f4, 0x38($sp)
/* 00406530 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406534 */  sw         $ra, 0x14($sp)
/* 00406538 */  swc1       $f12, 0x24($sp)
/* 0040653c */  swc1       $f14, 0x28($sp)
/* 00406540 */  swc1       $f4, 0x2c($sp)
/* 00406544 */  lw         $v1, 0x158($t6)
/* 00406548 */  nop        
/* 0040654c */  slti       $at, $v1, 0x14
/* 00406550 */  bnez       $at, 0x40658c
/* 00406554 */  sw         $v1, 0x20($sp)
/* 00406558 */  lui        $a0, 0x1000
/* 0040655c */  lui        $a1, 0x1000
/* 00406560 */  lui        $a2, 0x1000
/* 00406564 */  addiu      $a2, $a2, 0x16d0
/* 00406568 */  addiu      $a1, $a1, 0x16bc
/* 0040656c */  jal        0xf801150                                # fclose
/* 00406570 */  addiu      $a0, $a0, 0x36b4
/* 00406574 */  jal        0x40d3c0
/* 00406578 */  addiu      $a0, $zero, 1
/* 0040657c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00406580 */  nop        
/* 00406584 */  lw         $v1, 0x158($t7)
/* 00406588 */  nop        
/* 0040658c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406590 */  sll        $t0, $v1, 2
/* 00406594 */  lw         $t9, 0x120($t8)
/* 00406598 */  subu       $t0, $t0, $v1
/* 0040659c */  addiu      $t2, $sp, 0x24
/* 004065a0 */  lw         $at, ($t2)
/* 004065a4 */  sll        $t0, $t0, 2
/* 004065a8 */  lw         $t3, 4($t2)
/* 004065ac */  addu       $t1, $t9, $t0
/* 004065b0 */  sw         $at, ($t1)
/* 004065b4 */  lw         $at, 8($t2)
/* 004065b8 */  sw         $t3, 4($t1)
/* 004065bc */  sw         $at, 8($t1)
/* 004065c0 */  lw         $t4, 0x158($t8)
/* 004065c4 */  nop        
/* 004065c8 */  addiu      $t5, $t4, 1
/* 004065cc */  sw         $t5, 0x158($t8)
/* 004065d0 */  lw         $ra, 0x14($sp)
/* 004065d4 */  lw         $v0, 0x20($sp)
/* 004065d8 */  jr         $ra
/* 004065dc */  addiu      $sp, $sp, 0x30

# === build_view_matrix ===
glabel build_view_matrix
/* 004065e0 */  addiu      $sp, $sp, -0x48
/* 004065e4 */  sw         $a0, 0x48($sp)
/* 004065e8 */  sw         $ra, 0x14($sp)
/* 004065ec */  lw         $a0, 0x48($sp)
/* 004065f0 */  jal        0x40ade4
/* 004065f4 */  nop        
/* 004065f8 */  slti       $at, $v0, 3
/* 004065fc */  beqz       $at, 0x40662c
/* 00406600 */  lw         $a0, 0x48($sp)
/* 00406604 */  lui        $a0, 0x1000
/* 00406608 */  lui        $a1, 0x1000
/* 0040660c */  lui        $a2, 0x1000
/* 00406610 */  addiu      $a2, $a2, 0x16f4
/* 00406614 */  addiu      $a1, $a1, 0x16e0
/* 00406618 */  jal        0xf801150                                # fclose
/* 0040661c */  addiu      $a0, $a0, 0x36b4
/* 00406620 */  jal        0x40d3c0
/* 00406624 */  addiu      $a0, $zero, 1
/* 00406628 */  lw         $a0, 0x48($sp)
/* 0040662c */  jal        0x40a8e0
/* 00406630 */  nop        
/* 00406634 */  lw         $a0, 0x48($sp)
/* 00406638 */  jal        0x40a918
/* 0040663c */  sw         $v0, 0x44($sp)
/* 00406640 */  lw         $a0, 0x48($sp)
/* 00406644 */  jal        0x40a918
/* 00406648 */  sw         $v0, 0x40($sp)
/* 0040664c */  lw         $t6, 0x44($sp)
/* 00406650 */  move       $a1, $zero
/* 00406654 */  lw         $a0, ($t6)
/* 00406658 */  move       $a2, $zero
/* 0040665c */  b          0x4066dc
/* 00406660 */  move       $v1, $a0
/* 00406664 */  lw         $t7, 0x40($sp)
/* 00406668 */  addiu      $t0, $zero, 0x110
/* 0040666c */  lw         $v1, ($t7)
/* 00406670 */  nop        
/* 00406674 */  bne        $v1, $t0, 0x4066b8
/* 00406678 */  nop        
/* 0040667c */  lw         $v1, ($v0)
/* 00406680 */  b          0x406698
/* 00406684 */  nop        
/* 00406688 */  b          0x4066f4
/* 0040668c */  move       $a1, $a0
/* 00406690 */  b          0x4066f4
/* 00406694 */  move       $a2, $a0
/* 00406698 */  beq        $v1, $a3, 0x406690
/* 0040669c */  addiu      $at, $zero, 0x107
/* 004066a0 */  beq        $v1, $at, 0x406690
/* 004066a4 */  nop        
/* 004066a8 */  beq        $v1, $t0, 0x406688
/* 004066ac */  nop        
/* 004066b0 */  b          0x4066f8
/* 004066b4 */  lw         $a0, 0x48($sp)
/* 004066b8 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004066bc */  lui        $a0, 0x1000
/* 004066c0 */  lw         $t9, 0x160($t8)
/* 004066c4 */  lw         $t1, 0x188($t8)
/* 004066c8 */  addiu      $a0, $a0, 0x1710
/* 004066cc */  jal        0xf801250                                # getopt
/* 004066d0 */  subu       $a1, $t9, $t1
/* 004066d4 */  b          0x4067d8
/* 004066d8 */  lw         $ra, 0x14($sp)
/* 004066dc */  addiu      $a3, $zero, 0x103
/* 004066e0 */  beq        $v1, $a3, 0x406664
/* 004066e4 */  addiu      $at, $zero, 0x107
/* 004066e8 */  beq        $v1, $at, 0x406668
/* 004066ec */  lw         $t7, 0x40($sp)
/* 004066f0 */  addiu      $t0, $zero, 0x110
/* 004066f4 */  lw         $a0, 0x48($sp)
/* 004066f8 */  jal        0x4067e4                                 # compute_initial_view
/* 004066fc */  addiu      $a3, $sp, 0x2c
/* 00406700 */  bnez       $v0, 0x406740
/* 00406704 */  nop        
/* 00406708 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 0040670c */  lui        $a0, 0x1000
/* 00406710 */  lw         $t3, 0x160($t2)
/* 00406714 */  lw         $t4, 0x188($t2)
/* 00406718 */  addiu      $a0, $a0, 0x173c
/* 0040671c */  jal        0xf801250                                # getopt
/* 00406720 */  subu       $a1, $t3, $t4
/* 00406724 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00406728 */  nop        
/* 0040672c */  lw         $t6, 0x160($t5)
/* 00406730 */  nop        
/* 00406734 */  addiu      $t7, $t6, 1
/* 00406738 */  b          0x4067d4
/* 0040673c */  sw         $t7, 0x160($t5)
/* 00406740 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406744 */  lui        $at, 3
/* 00406748 */  lw         $v0, 0x160($t8)
/* 0040674c */  ori        $at, $at, 0xd40
/* 00406750 */  slt        $at, $v0, $at
/* 00406754 */  bnez       $at, 0x406790
/* 00406758 */  nop        
/* 0040675c */  lui        $a0, 0x1000
/* 00406760 */  lui        $a1, 0x1000
/* 00406764 */  lui        $a2, 0x1000
/* 00406768 */  addiu      $a2, $a2, 0x1780
/* 0040676c */  addiu      $a1, $a1, 0x176c
/* 00406770 */  jal        0xf801150                                # fclose
/* 00406774 */  addiu      $a0, $a0, 0x36b4
/* 00406778 */  jal        0x40d3c0
/* 0040677c */  addiu      $a0, $zero, 1
/* 00406780 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00406784 */  nop        
/* 00406788 */  lw         $v0, 0x160($t9)
/* 0040678c */  nop        
/* 00406790 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00406794 */  addiu      $t6, $sp, 0x2c
/* 00406798 */  lw         $t2, 0x128($t1)
/* 0040679c */  lw         $at, ($t6)
/* 004067a0 */  sll        $t3, $v0, 4
/* 004067a4 */  lw         $t7, 4($t6)
/* 004067a8 */  addu       $t4, $t2, $t3
/* 004067ac */  sw         $at, ($t4)
/* 004067b0 */  lw         $at, 8($t6)
/* 004067b4 */  sw         $t7, 4($t4)
/* 004067b8 */  lw         $t7, 0xc($t6)
/* 004067bc */  sw         $at, 8($t4)
/* 004067c0 */  sw         $t7, 0xc($t4)
/* 004067c4 */  lw         $t5, 0x160($t1)
/* 004067c8 */  nop        
/* 004067cc */  addiu      $t8, $t5, 1
/* 004067d0 */  sw         $t8, 0x160($t1)
/* 004067d4 */  lw         $ra, 0x14($sp)
/* 004067d8 */  addiu      $sp, $sp, 0x48
/* 004067dc */  jr         $ra
/* 004067e0 */  nop        

# === compute_initial_view ===
glabel compute_initial_view
/* 004067e4 */  addiu      $sp, $sp, -0x2050
/* 004067e8 */  sw         $s2, 0x1c($sp)
/* 004067ec */  sw         $ra, 0x24($sp)
/* 004067f0 */  sw         $s3, 0x20($sp)
/* 004067f4 */  sw         $s1, 0x18($sp)
/* 004067f8 */  move       $s2, $a1
/* 004067fc */  sw         $s0, 0x14($sp)
/* 00406800 */  sw         $a0, 0x2050($sp)
/* 00406804 */  addiu      $t6, $zero, -1
/* 00406808 */  move       $s3, $a2
/* 0040680c */  beqz       $s2, 0x40684c
/* 00406810 */  sw         $t6, 0xc($a3)
/* 00406814 */  beqz       $s3, 0x40684c
/* 00406818 */  nop        
/* 0040681c */  lui        $a0, 0x1000
/* 00406820 */  lui        $a1, 0x1000
/* 00406824 */  lui        $a2, 0x1000
/* 00406828 */  addiu      $a2, $a2, 0x17a4
/* 0040682c */  addiu      $a1, $a1, 0x1790
/* 00406830 */  addiu      $a0, $a0, 0x36b4
/* 00406834 */  jal        0xf801150                                # fclose
/* 00406838 */  sw         $a3, 0x205c($sp)
/* 0040683c */  jal        0x40d3c0
/* 00406840 */  addiu      $a0, $zero, 1
/* 00406844 */  lw         $a3, 0x205c($sp)
/* 00406848 */  nop        
/* 0040684c */  bnez       $s2, 0x406868
/* 00406850 */  nop        
/* 00406854 */  bnez       $s3, 0x406868
/* 00406858 */  nop        
/* 0040685c */  lui        $t7, 0x41
/* 00406860 */  addiu      $t7, $t7, -0x78b8
/* 00406864 */  sw         $t7, ($a3)
/* 00406868 */  beqz       $s2, 0x4068bc
/* 0040686c */  nop        
/* 00406870 */  b          0x4068ac
/* 00406874 */  addiu      $at, $zero, 0x103
/* 00406878 */  lui        $t8, 0x41
/* 0040687c */  addiu      $t8, $t8, -0x7660
/* 00406880 */  addiu      $t9, $zero, 3
/* 00406884 */  sw         $t8, ($a3)
/* 00406888 */  b          0x4068bc
/* 0040688c */  sw         $t9, 0xc($a3)
/* 00406890 */  lui        $t0, 0x41
/* 00406894 */  addiu      $t0, $t0, -0x7410
/* 00406898 */  addiu      $t1, $zero, 5
/* 0040689c */  sw         $t0, ($a3)
/* 004068a0 */  b          0x4068bc
/* 004068a4 */  sw         $t1, 0xc($a3)
/* 004068a8 */  addiu      $at, $zero, 0x103
/* 004068ac */  beq        $s2, $at, 0x406878
/* 004068b0 */  addiu      $at, $zero, 0x107
/* 004068b4 */  beq        $s2, $at, 0x406890
/* 004068b8 */  nop        
/* 004068bc */  beqz       $s3, 0x406914
/* 004068c0 */  lw         $a0, 0x2050($sp)
/* 004068c4 */  b          0x406900
/* 004068c8 */  addiu      $at, $zero, 0x103
/* 004068cc */  lui        $t2, 0x41
/* 004068d0 */  addiu      $t2, $t2, -0x77c0
/* 004068d4 */  addiu      $t3, $zero, 2
/* 004068d8 */  sw         $t2, ($a3)
/* 004068dc */  b          0x406910
/* 004068e0 */  sw         $t3, 0xc($a3)
/* 004068e4 */  lui        $t4, 0x41
/* 004068e8 */  addiu      $t4, $t4, -0x7550
/* 004068ec */  addiu      $t5, $zero, 4
/* 004068f0 */  sw         $t4, ($a3)
/* 004068f4 */  b          0x406910
/* 004068f8 */  sw         $t5, 0xc($a3)
/* 004068fc */  addiu      $at, $zero, 0x103
/* 00406900 */  beq        $s3, $at, 0x4068cc
/* 00406904 */  addiu      $at, $zero, 0x107
/* 00406908 */  beq        $s3, $at, 0x4068e4
/* 0040690c */  nop        
/* 00406910 */  lw         $a0, 0x2050($sp)
/* 00406914 */  addiu      $s1, $sp, 0x48
/* 00406918 */  move       $s0, $zero
/* 0040691c */  jal        0x40a8e0
/* 00406920 */  sw         $a3, 0x205c($sp)
/* 00406924 */  beqz       $v0, 0x406a7c
/* 00406928 */  move       $a3, $v0
/* 0040692c */  bnez       $s0, 0x406970
/* 00406930 */  nop        
/* 00406934 */  beqz       $s2, 0x406970
/* 00406938 */  nop        
/* 0040693c */  lw         $t6, ($v0)
/* 00406940 */  nop        
/* 00406944 */  beq        $s2, $t6, 0x406970
/* 00406948 */  nop        
/* 0040694c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00406950 */  lui        $a0, 0x1000
/* 00406954 */  lw         $t8, 0x160($t7)
/* 00406958 */  lw         $t9, 0x188($t7)
/* 0040695c */  addiu      $a0, $a0, 0x17b4
/* 00406960 */  jal        0xf801250                                # getopt
/* 00406964 */  subu       $a1, $t8, $t9
/* 00406968 */  b          0x406b74
/* 0040696c */  move       $v0, $zero
/* 00406970 */  lw         $a0, ($v0)
/* 00406974 */  bgez       $s0, 0x406988
/* 00406978 */  andi       $t0, $s0, 1
/* 0040697c */  beqz       $t0, 0x406988
/* 00406980 */  nop        
/* 00406984 */  addiu      $t0, $t0, -2
/* 00406988 */  bnez       $t0, 0x4069c4
/* 0040698c */  nop        
/* 00406990 */  beqz       $s3, 0x4069c4
/* 00406994 */  nop        
/* 00406998 */  beq        $s3, $a0, 0x4069c4
/* 0040699c */  nop        
/* 004069a0 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 004069a4 */  lui        $a0, 0x1000
/* 004069a8 */  lw         $t2, 0x160($t1)
/* 004069ac */  lw         $t3, 0x188($t1)
/* 004069b0 */  addiu      $a0, $a0, 0x17e0
/* 004069b4 */  jal        0xf801250                                # getopt
/* 004069b8 */  subu       $a1, $t2, $t3
/* 004069bc */  b          0x406b74
/* 004069c0 */  move       $v0, $zero
/* 004069c4 */  b          0x406a28
/* 004069c8 */  move       $v1, $a0
/* 004069cc */  lw         $t4, 8($v0)
/* 004069d0 */  addiu      $s1, $s1, 0xc
/* 004069d4 */  lw         $at, ($t4)
/* 004069d8 */  lw         $t5, 4($t4)
/* 004069dc */  sw         $at, -0xc($s1)
/* 004069e0 */  lw         $at, 8($t4)
/* 004069e4 */  sw         $t5, -8($s1)
/* 004069e8 */  b          0x406a64
/* 004069ec */  sw         $at, -4($s1)
/* 004069f0 */  lw         $t6, 8($v0)
/* 004069f4 */  addiu      $s1, $s1, 4
/* 004069f8 */  lw         $t7, ($t6)
/* 004069fc */  b          0x406a64
/* 00406a00 */  sw         $t7, -4($s1)
/* 00406a04 */  lw         $t8, 8($v0)
/* 00406a08 */  addiu      $s1, $s1, 0xc
/* 00406a0c */  lw         $at, ($t8)
/* 00406a10 */  lw         $t9, 4($t8)
/* 00406a14 */  sw         $at, -0xc($s1)
/* 00406a18 */  lw         $at, 8($t8)
/* 00406a1c */  sw         $t9, -8($s1)
/* 00406a20 */  b          0x406a64
/* 00406a24 */  sw         $at, -4($s1)
/* 00406a28 */  addiu      $at, $zero, 0x103
/* 00406a2c */  beq        $v1, $at, 0x4069f0
/* 00406a30 */  addiu      $at, $zero, 0x107
/* 00406a34 */  beq        $v1, $at, 0x406a04
/* 00406a38 */  addiu      $at, $zero, 0x110
/* 00406a3c */  beq        $v1, $at, 0x4069cc
/* 00406a40 */  nop        
/* 00406a44 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00406a48 */  lui        $a0, 0x1000
/* 00406a4c */  lw         $t1, 0x160($t0)
/* 00406a50 */  lw         $t2, 0x188($t0)
/* 00406a54 */  lw         $a1, ($a3)
/* 00406a58 */  addiu      $a0, $a0, 0x1864
/* 00406a5c */  jal        0x4092d4
/* 00406a60 */  subu       $a2, $t1, $t2
/* 00406a64 */  lw         $a0, 0x2050($sp)
/* 00406a68 */  jal        0x40a918
/* 00406a6c */  addiu      $s0, $s0, 1
/* 00406a70 */  bnez       $v0, 0x40692c
/* 00406a74 */  move       $a3, $v0
/* 00406a78 */  move       $s0, $zero
/* 00406a7c */  addiu      $t3, $sp, 0x48
/* 00406a80 */  subu       $v0, $s1, $t3
/* 00406a84 */  bgez       $v0, 0x406a90
/* 00406a88 */  move       $at, $v0
/* 00406a8c */  addiu      $at, $at, 3
/* 00406a90 */  sra        $v0, $at, 2
/* 00406a94 */  move       $a1, $v0
/* 00406a98 */  sw         $a1, 0x204c($sp)
/* 00406a9c */  jal        0xf801208                                # free
/* 00406aa0 */  sll        $a0, $v0, 2
/* 00406aa4 */  lw         $a1, 0x204c($sp)
/* 00406aa8 */  bnez       $v0, 0x406ac8
/* 00406aac */  move       $s1, $v0
/* 00406ab0 */  lui        $a0, 0x1000
/* 00406ab4 */  addiu      $a0, $a0, 0x189c
/* 00406ab8 */  jal        0x4092d4
/* 00406abc */  sw         $a1, 0x204c($sp)
/* 00406ac0 */  lw         $a1, 0x204c($sp)
/* 00406ac4 */  nop        
/* 00406ac8 */  blez       $a1, 0x406b60
/* 00406acc */  lw         $t6, 0x205c($sp)
/* 00406ad0 */  andi       $a0, $a1, 3
/* 00406ad4 */  beqz       $a0, 0x406b14
/* 00406ad8 */  addiu      $t0, $sp, 0x2050
/* 00406adc */  sll        $t5, $s0, 2
/* 00406ae0 */  sll        $t4, $s0, 2
/* 00406ae4 */  addiu      $t6, $sp, 0x2050
/* 00406ae8 */  addu       $v0, $t4, $t6
/* 00406aec */  addu       $v1, $s1, $t5
/* 00406af0 */  lw         $t7, -0x2008($v0)
/* 00406af4 */  addiu      $s0, $s0, 1
/* 00406af8 */  addiu      $v1, $v1, 4
/* 00406afc */  addiu      $v0, $v0, 4
/* 00406b00 */  bne        $a0, $s0, 0x406af0
/* 00406b04 */  sw         $t7, -4($v1)
/* 00406b08 */  beq        $s0, $a1, 0x406b60
/* 00406b0c */  lw         $t6, 0x205c($sp)
/* 00406b10 */  addiu      $t0, $sp, 0x2050
/* 00406b14 */  sll        $t9, $s0, 2
/* 00406b18 */  sll        $t8, $s0, 2
/* 00406b1c */  sll        $t1, $a1, 2
/* 00406b20 */  addu       $a0, $t1, $t0
/* 00406b24 */  addu       $v0, $t8, $t0
/* 00406b28 */  addu       $v1, $s1, $t9
/* 00406b2c */  lw         $t2, -0x2008($v0)
/* 00406b30 */  addiu      $v0, $v0, 0x10
/* 00406b34 */  sw         $t2, ($v1)
/* 00406b38 */  lw         $t3, -0x2014($v0)
/* 00406b3c */  addiu      $v1, $v1, 0x10
/* 00406b40 */  sw         $t3, -0xc($v1)
/* 00406b44 */  lw         $t5, -0x2010($v0)
/* 00406b48 */  nop        
/* 00406b4c */  sw         $t5, -8($v1)
/* 00406b50 */  lw         $t4, -0x200c($v0)
/* 00406b54 */  bne        $v0, $a0, 0x406b2c
/* 00406b58 */  sw         $t4, -4($v1)
/* 00406b5c */  lw         $t6, 0x205c($sp)
/* 00406b60 */  addiu      $v0, $zero, 1
/* 00406b64 */  sw         $s1, 4($t6)
/* 00406b68 */  lw         $t7, 0x205c($sp)
/* 00406b6c */  nop        
/* 00406b70 */  sw         $a1, 8($t7)
/* 00406b74 */  lw         $ra, 0x24($sp)
/* 00406b78 */  lw         $s0, 0x14($sp)
/* 00406b7c */  lw         $s1, 0x18($sp)
/* 00406b80 */  lw         $s2, 0x1c($sp)
/* 00406b84 */  lw         $s3, 0x20($sp)
/* 00406b88 */  jr         $ra
/* 00406b8c */  addiu      $sp, $sp, 0x2050

# === apply_transforms ===
glabel apply_transforms
/* 00406b90 */  addiu      $sp, $sp, -0x40
/* 00406b94 */  sw         $a0, 0x40($sp)
/* 00406b98 */  sw         $ra, 0x14($sp)
/* 00406b9c */  lw         $a0, 0x40($sp)
/* 00406ba0 */  jal        0x40ade4
/* 00406ba4 */  nop        
/* 00406ba8 */  slti       $at, $v0, 3
/* 00406bac */  bnez       $at, 0x406bdc
/* 00406bb0 */  lw         $a0, 0x40($sp)
/* 00406bb4 */  lui        $a0, 0x1000
/* 00406bb8 */  lui        $a1, 0x1000
/* 00406bbc */  lui        $a2, 0x1000
/* 00406bc0 */  addiu      $a2, $a2, 0x18c8
/* 00406bc4 */  addiu      $a1, $a1, 0x18b4
/* 00406bc8 */  jal        0xf801150                                # fclose
/* 00406bcc */  addiu      $a0, $a0, 0x36b4
/* 00406bd0 */  jal        0x40d3c0
/* 00406bd4 */  addiu      $a0, $zero, 1
/* 00406bd8 */  lw         $a0, 0x40($sp)
/* 00406bdc */  jal        0x40a8e0
/* 00406be0 */  nop        
/* 00406be4 */  lw         $v1, ($v0)
/* 00406be8 */  b          0x406c54
/* 00406bec */  move       $a3, $v0
/* 00406bf0 */  lw         $a0, 0x40($sp)
/* 00406bf4 */  jal        0x40ade4
/* 00406bf8 */  nop        
/* 00406bfc */  addiu      $at, $zero, 1
/* 00406c00 */  beq        $v0, $at, 0x406c7c
/* 00406c04 */  lw         $a0, 0x40($sp)
/* 00406c08 */  lui        $a0, 0x1000
/* 00406c0c */  lui        $a1, 0x1000
/* 00406c10 */  lui        $a2, 0x1000
/* 00406c14 */  addiu      $a2, $a2, 0x18f8
/* 00406c18 */  addiu      $a1, $a1, 0x18e4
/* 00406c1c */  jal        0xf801150                                # fclose
/* 00406c20 */  addiu      $a0, $a0, 0x36b4
/* 00406c24 */  jal        0x40d3c0
/* 00406c28 */  addiu      $a0, $zero, 1
/* 00406c2c */  b          0x406c7c
/* 00406c30 */  lw         $a0, 0x40($sp)
/* 00406c34 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406c38 */  lui        $a0, 0x1000
/* 00406c3c */  lw         $a1, ($a3)
/* 00406c40 */  lw         $a2, 0x168($t6)
/* 00406c44 */  jal        0x4092d4
/* 00406c48 */  addiu      $a0, $a0, 0x1924
/* 00406c4c */  b          0x406c7c
/* 00406c50 */  lw         $a0, 0x40($sp)
/* 00406c54 */  addiu      $at, $zero, 0x103
/* 00406c58 */  beq        $v1, $at, 0x406c78
/* 00406c5c */  addiu      $at, $zero, 0x107
/* 00406c60 */  beq        $v1, $at, 0x406c78
/* 00406c64 */  addiu      $at, $zero, 0x110
/* 00406c68 */  beq        $v1, $at, 0x406bf4
/* 00406c6c */  lw         $a0, 0x40($sp)
/* 00406c70 */  b          0x406c34
/* 00406c74 */  nop        
/* 00406c78 */  lw         $a0, 0x40($sp)
/* 00406c7c */  jal        0x406d60                                 # parse_transform_string
/* 00406c80 */  addiu      $a1, $sp, 0x2c
/* 00406c84 */  bnez       $v0, 0x406cbc
/* 00406c88 */  nop        
/* 00406c8c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00406c90 */  lui        $a0, 0x1000
/* 00406c94 */  lw         $a1, 0x168($t7)
/* 00406c98 */  jal        0xf801250                                # getopt
/* 00406c9c */  addiu      $a0, $a0, 0x1954
/* 00406ca0 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406ca4 */  nop        
/* 00406ca8 */  lw         $t9, 0x168($t8)
/* 00406cac */  nop        
/* 00406cb0 */  addiu      $t0, $t9, 1
/* 00406cb4 */  b          0x406d50
/* 00406cb8 */  sw         $t0, 0x168($t8)
/* 00406cbc */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00406cc0 */  nop        
/* 00406cc4 */  lw         $v0, 0x168($t1)
/* 00406cc8 */  nop        
/* 00406ccc */  slti       $at, $v0, 0xfa0
/* 00406cd0 */  bnez       $at, 0x406d0c
/* 00406cd4 */  nop        
/* 00406cd8 */  lui        $a0, 0x1000
/* 00406cdc */  lui        $a1, 0x1000
/* 00406ce0 */  lui        $a2, 0x1000
/* 00406ce4 */  addiu      $a2, $a2, 0x1994
/* 00406ce8 */  addiu      $a1, $a1, 0x1980
/* 00406cec */  jal        0xf801150                                # fclose
/* 00406cf0 */  addiu      $a0, $a0, 0x36b4
/* 00406cf4 */  jal        0x40d3c0
/* 00406cf8 */  addiu      $a0, $zero, 1
/* 00406cfc */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00406d00 */  nop        
/* 00406d04 */  lw         $v0, 0x168($t2)
/* 00406d08 */  nop        
/* 00406d0c */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00406d10 */  addiu      $t7, $sp, 0x2c
/* 00406d14 */  lw         $t4, 0x130($t3)
/* 00406d18 */  lw         $at, ($t7)
/* 00406d1c */  sll        $t5, $v0, 4
/* 00406d20 */  lw         $t9, 4($t7)
/* 00406d24 */  addu       $t6, $t4, $t5
/* 00406d28 */  sw         $at, ($t6)
/* 00406d2c */  lw         $at, 8($t7)
/* 00406d30 */  sw         $t9, 4($t6)
/* 00406d34 */  lw         $t9, 0xc($t7)
/* 00406d38 */  sw         $at, 8($t6)
/* 00406d3c */  sw         $t9, 0xc($t6)
/* 00406d40 */  lw         $t0, 0x168($t3)
/* 00406d44 */  nop        
/* 00406d48 */  addiu      $t8, $t0, 1
/* 00406d4c */  sw         $t8, 0x168($t3)
/* 00406d50 */  lw         $ra, 0x14($sp)
/* 00406d54 */  addiu      $sp, $sp, 0x40
/* 00406d58 */  jr         $ra
/* 00406d5c */  nop        

# === parse_transform_string ===
glabel parse_transform_string
/* 00406d60 */  addiu      $sp, $sp, -0x58
/* 00406d64 */  sw         $a1, 0x5c($sp)
/* 00406d68 */  lw         $t7, 0x5c($sp)
/* 00406d6c */  sw         $ra, 0x1c($sp)
/* 00406d70 */  sw         $s1, 0x18($sp)
/* 00406d74 */  sw         $s0, 0x14($sp)
/* 00406d78 */  sw         $a0, 0x58($sp)
/* 00406d7c */  addiu      $t6, $zero, -1
/* 00406d80 */  sw         $t6, 0xc($t7)
/* 00406d84 */  lw         $a0, 0x58($sp)
/* 00406d88 */  jal        0x40a8e0
/* 00406d8c */  nop        
/* 00406d90 */  lw         $v1, ($v0)
/* 00406d94 */  addiu      $at, $zero, 0x103
/* 00406d98 */  beq        $v1, $at, 0x406dc8
/* 00406d9c */  move       $s0, $v0
/* 00406da0 */  addiu      $at, $zero, 0x107
/* 00406da4 */  beq        $v1, $at, 0x406de8
/* 00406da8 */  addiu      $at, $zero, 0x110
/* 00406dac */  bne        $v1, $at, 0x406e04
/* 00406db0 */  nop        
/* 00406db4 */  lw         $t9, 0x5c($sp)
/* 00406db8 */  lui        $t8, 0x41
/* 00406dbc */  addiu      $t8, $t8, -0x7300
/* 00406dc0 */  b          0x406e1c
/* 00406dc4 */  sw         $t8, ($t9)
/* 00406dc8 */  lw         $t1, 0x5c($sp)
/* 00406dcc */  lui        $t0, 0x41
/* 00406dd0 */  addiu      $t0, $t0, -0x726c
/* 00406dd4 */  sw         $t0, ($t1)
/* 00406dd8 */  lw         $t3, 0x5c($sp)
/* 00406ddc */  addiu      $t2, $zero, 8
/* 00406de0 */  b          0x406e1c
/* 00406de4 */  sw         $t2, 0xc($t3)
/* 00406de8 */  lw         $v0, 0x5c($sp)
/* 00406dec */  lui        $t4, 0x41
/* 00406df0 */  addiu      $t4, $t4, -0x71cc
/* 00406df4 */  addiu      $t5, $zero, 9
/* 00406df8 */  sw         $t4, ($v0)
/* 00406dfc */  b          0x406e1c
/* 00406e00 */  sw         $t5, 0xc($v0)
/* 00406e04 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406e08 */  lui        $a0, 0x1000
/* 00406e0c */  lw         $a1, ($s0)
/* 00406e10 */  lw         $a2, 0x168($t6)
/* 00406e14 */  jal        0x4092d4
/* 00406e18 */  addiu      $a0, $a0, 0x19a0
/* 00406e1c */  lw         $a0, 0x58($sp)
/* 00406e20 */  jal        0x40a8e0
/* 00406e24 */  addiu      $s1, $sp, 0x44
/* 00406e28 */  beqz       $v0, 0x406f78
/* 00406e2c */  move       $s0, $v0
/* 00406e30 */  lw         $v1, ($v0)
/* 00406e34 */  b          0x406f4c
/* 00406e38 */  addiu      $at, $zero, 0x103
/* 00406e3c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406e40 */  lw         $t7, 4($v0)
/* 00406e44 */  lw         $t9, 0x14c($t8)
/* 00406e48 */  nop        
/* 00406e4c */  slt        $at, $t7, $t9
/* 00406e50 */  bnez       $at, 0x406e68
/* 00406e54 */  nop        
/* 00406e58 */  lui        $a0, 0x1000
/* 00406e5c */  lw         $a1, 4($s0)
/* 00406e60 */  jal        0x4092d4
/* 00406e64 */  addiu      $a0, $a0, 0x19cc
/* 00406e68 */  lw         $t2, 4($s0)
/* 00406e6c */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00406e70 */  sll        $t3, $t2, 2
/* 00406e74 */  lw         $t1, 0x110($t0)
/* 00406e78 */  subu       $t3, $t3, $t2
/* 00406e7c */  sll        $t3, $t3, 2
/* 00406e80 */  addu       $t4, $t1, $t3
/* 00406e84 */  sw         $t4, ($s1)
/* 00406e88 */  b          0x406f64
/* 00406e8c */  addiu      $s1, $s1, 4
/* 00406e90 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406e94 */  lw         $t5, 4($v0)
/* 00406e98 */  lw         $t8, 0x140($t6)
/* 00406e9c */  nop        
/* 00406ea0 */  slt        $at, $t5, $t8
/* 00406ea4 */  bnez       $at, 0x406ebc
/* 00406ea8 */  nop        
/* 00406eac */  lui        $a0, 0x1000
/* 00406eb0 */  lw         $a1, 4($s0)
/* 00406eb4 */  jal        0x4092d4
/* 00406eb8 */  addiu      $a0, $a0, 0x19e0
/* 00406ebc */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00406ec0 */  lw         $t0, 4($s0)
/* 00406ec4 */  lw         $t9, 0x108($t7)
/* 00406ec8 */  sll        $t2, $t0, 2
/* 00406ecc */  addu       $t1, $t9, $t2
/* 00406ed0 */  lw         $t3, ($t1)
/* 00406ed4 */  addiu      $s1, $s1, 4
/* 00406ed8 */  b          0x406f64
/* 00406edc */  sw         $t3, -4($s1)
/* 00406ee0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00406ee4 */  lw         $t4, 4($v0)
/* 00406ee8 */  lw         $t5, 0x148($t6)
/* 00406eec */  nop        
/* 00406ef0 */  slt        $at, $t4, $t5
/* 00406ef4 */  bnez       $at, 0x406f0c
/* 00406ef8 */  nop        
/* 00406efc */  lui        $a0, 0x1000
/* 00406f00 */  lw         $a1, 4($s0)
/* 00406f04 */  jal        0x4092d4
/* 00406f08 */  addiu      $a0, $a0, 0x19f8
/* 00406f0c */  lw         $t0, 4($s0)
/* 00406f10 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00406f14 */  sll        $t9, $t0, 2
/* 00406f18 */  lw         $t7, 0x114($t8)
/* 00406f1c */  subu       $t9, $t9, $t0
/* 00406f20 */  sll        $t9, $t9, 2
/* 00406f24 */  addu       $t2, $t7, $t9
/* 00406f28 */  lw         $at, ($t2)
/* 00406f2c */  lw         $t1, 4($t2)
/* 00406f30 */  sw         $at, ($s1)
/* 00406f34 */  lw         $at, 8($t2)
/* 00406f38 */  sw         $t1, 4($s1)
/* 00406f3c */  addiu      $s1, $s1, 0xc
/* 00406f40 */  b          0x406f64
/* 00406f44 */  sw         $at, -4($s1)
/* 00406f48 */  addiu      $at, $zero, 0x103
/* 00406f4c */  beq        $v1, $at, 0x406e90
/* 00406f50 */  addiu      $at, $zero, 0x107
/* 00406f54 */  beq        $v1, $at, 0x406ee0
/* 00406f58 */  addiu      $at, $zero, 0x110
/* 00406f5c */  beq        $v1, $at, 0x406e3c
/* 00406f60 */  nop        
/* 00406f64 */  lw         $a0, 0x58($sp)
/* 00406f68 */  jal        0x40a918
/* 00406f6c */  nop        
/* 00406f70 */  bnez       $v0, 0x406e30
/* 00406f74 */  move       $s0, $v0
/* 00406f78 */  addiu      $t3, $sp, 0x44
/* 00406f7c */  subu       $v0, $s1, $t3
/* 00406f80 */  bgez       $v0, 0x406f8c
/* 00406f84 */  move       $at, $v0
/* 00406f88 */  addiu      $at, $at, 3
/* 00406f8c */  sra        $v0, $at, 2
/* 00406f90 */  move       $s0, $v0
/* 00406f94 */  jal        0xf801208                                # free
/* 00406f98 */  sll        $a0, $v0, 2
/* 00406f9c */  bnez       $v0, 0x406fb0
/* 00406fa0 */  move       $s1, $v0
/* 00406fa4 */  lui        $a0, 0x1000
/* 00406fa8 */  jal        0x4092d4
/* 00406fac */  addiu      $a0, $a0, 0x1a48
/* 00406fb0 */  blez       $s0, 0x407044
/* 00406fb4 */  move       $a1, $zero
/* 00406fb8 */  andi       $a0, $s0, 3
/* 00406fbc */  beqz       $a0, 0x406ffc
/* 00406fc0 */  addiu      $t9, $sp, 0x58
/* 00406fc4 */  sll        $t6, $a1, 2
/* 00406fc8 */  sll        $t4, $a1, 2
/* 00406fcc */  addiu      $t5, $sp, 0x58
/* 00406fd0 */  addu       $v0, $t4, $t5
/* 00406fd4 */  addu       $v1, $s1, $t6
/* 00406fd8 */  lw         $t8, -0x14($v0)
/* 00406fdc */  addiu      $a1, $a1, 1
/* 00406fe0 */  addiu      $v1, $v1, 4
/* 00406fe4 */  addiu      $v0, $v0, 4
/* 00406fe8 */  bne        $a0, $a1, 0x406fd8
/* 00406fec */  sw         $t8, -4($v1)
/* 00406ff0 */  beq        $a1, $s0, 0x407048
/* 00406ff4 */  lw         $v1, 0x5c($sp)
/* 00406ff8 */  addiu      $t9, $sp, 0x58
/* 00406ffc */  sll        $t0, $a1, 2
/* 00407000 */  sll        $t7, $a1, 2
/* 00407004 */  sll        $t1, $s0, 2
/* 00407008 */  addu       $a0, $t1, $t9
/* 0040700c */  addu       $v0, $t7, $t9
/* 00407010 */  addu       $v1, $s1, $t0
/* 00407014 */  lw         $t2, -0x14($v0)
/* 00407018 */  addiu      $v0, $v0, 0x10
/* 0040701c */  sw         $t2, ($v1)
/* 00407020 */  lw         $t3, -0x20($v0)
/* 00407024 */  addiu      $v1, $v1, 0x10
/* 00407028 */  sw         $t3, -0xc($v1)
/* 0040702c */  lw         $t6, -0x1c($v0)
/* 00407030 */  nop        
/* 00407034 */  sw         $t6, -8($v1)
/* 00407038 */  lw         $t4, -0x18($v0)
/* 0040703c */  bne        $v0, $a0, 0x407014
/* 00407040 */  sw         $t4, -4($v1)
/* 00407044 */  lw         $v1, 0x5c($sp)
/* 00407048 */  addiu      $v0, $zero, 1
/* 0040704c */  sw         $s1, 4($v1)
/* 00407050 */  sw         $s0, 8($v1)
/* 00407054 */  lw         $ra, 0x1c($sp)
/* 00407058 */  lw         $s1, 0x18($sp)
/* 0040705c */  lw         $s0, 0x14($sp)
/* 00407060 */  jr         $ra
/* 00407064 */  addiu      $sp, $sp, 0x58

# === apply_material_transforms ===
glabel apply_material_transforms
/* 00407068 */  addiu      $sp, $sp, -0x70
/* 0040706c */  sw         $fp, 0x30($sp)
/* 00407070 */  sw         $ra, 0x34($sp)
/* 00407074 */  sw         $s6, 0x2c($sp)
/* 00407078 */  sw         $s5, 0x28($sp)
/* 0040707c */  sw         $s4, 0x24($sp)
/* 00407080 */  move       $fp, $a0
/* 00407084 */  sw         $s3, 0x20($sp)
/* 00407088 */  sw         $s2, 0x1c($sp)
/* 0040708c */  sw         $s1, 0x18($sp)
/* 00407090 */  jal        0x40a8e0
/* 00407094 */  move       $a0, $fp
/* 00407098 */  lw         $s5, ($v0)
/* 0040709c */  move       $s2, $zero
/* 004070a0 */  move       $s6, $zero
/* 004070a4 */  move       $s3, $zero
/* 004070a8 */  jal        0x40a8e0
/* 004070ac */  move       $a0, $fp
/* 004070b0 */  bnez       $v0, 0x4070c0
/* 004070b4 */  move       $s1, $v0
/* 004070b8 */  b          0x407190
/* 004070bc */  addiu      $s4, $zero, 0x110
/* 004070c0 */  sw         $s7, 0x3c($sp)
/* 004070c4 */  addiu      $s7, $zero, 1
/* 004070c8 */  sw         $s0, 0x40($sp)
/* 004070cc */  addiu      $s4, $zero, 0x110
/* 004070d0 */  bne        $s5, $s4, 0x407104
/* 004070d4 */  nop        
/* 004070d8 */  lw         $t6, ($v0)
/* 004070dc */  addiu      $s2, $s2, 1
/* 004070e0 */  beq        $s4, $t6, 0x407170
/* 004070e4 */  nop        
/* 004070e8 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004070ec */  lui        $a0, 0x1000
/* 004070f0 */  lw         $a1, 0x164($t7)
/* 004070f4 */  jal        0x4092d4
/* 004070f8 */  addiu      $a0, $a0, 0x1a5c
/* 004070fc */  b          0x407174
/* 00407100 */  addiu      $s3, $s3, 1
/* 00407104 */  bgez       $s3, 0x407118
/* 00407108 */  andi       $s0, $s3, 1
/* 0040710c */  beqz       $s0, 0x407118
/* 00407110 */  nop        
/* 00407114 */  addiu      $s0, $s0, -2
/* 00407118 */  bnez       $s0, 0x407144
/* 0040711c */  nop        
/* 00407120 */  lw         $t8, ($v0)
/* 00407124 */  addiu      $s6, $s6, 1
/* 00407128 */  beq        $s5, $t8, 0x407144
/* 0040712c */  nop        
/* 00407130 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00407134 */  lui        $a0, 0x1000
/* 00407138 */  lw         $a1, 0x164($t9)
/* 0040713c */  jal        0x4092d4
/* 00407140 */  addiu      $a0, $a0, 0x1a88
/* 00407144 */  bne        $s7, $s0, 0x407170
/* 00407148 */  nop        
/* 0040714c */  lw         $t0, ($s1)
/* 00407150 */  addiu      $s2, $s2, 1
/* 00407154 */  beq        $s4, $t0, 0x407170
/* 00407158 */  nop        
/* 0040715c */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00407160 */  lui        $a0, 0x1000
/* 00407164 */  lw         $a1, 0x164($t1)
/* 00407168 */  jal        0x4092d4
/* 0040716c */  addiu      $a0, $a0, 0x1ab4
/* 00407170 */  addiu      $s3, $s3, 1
/* 00407174 */  jal        0x40a918
/* 00407178 */  move       $a0, $fp
/* 0040717c */  bnez       $v0, 0x4070d0
/* 00407180 */  move       $s1, $v0
/* 00407184 */  lw         $s0, 0x40($sp)
/* 00407188 */  lw         $s7, 0x3c($sp)
/* 0040718c */  nop        
/* 00407190 */  slti       $at, $s2, 2
/* 00407194 */  bnez       $at, 0x4071b4
/* 00407198 */  slti       $at, $s2, 0x101
/* 0040719c */  beqz       $at, 0x4071b4
/* 004071a0 */  nop        
/* 004071a4 */  beq        $s5, $s4, 0x4071cc
/* 004071a8 */  move       $a0, $fp
/* 004071ac */  beq        $s2, $s6, 0x4071cc
/* 004071b0 */  move       $a0, $fp
/* 004071b4 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 004071b8 */  lui        $a0, 0x1000
/* 004071bc */  lw         $a1, 0x164($t2)
/* 004071c0 */  jal        0x4092d4
/* 004071c4 */  addiu      $a0, $a0, 0x1ae0
/* 004071c8 */  move       $a0, $fp
/* 004071cc */  jal        0x4072ac                                 # load_binary_model
/* 004071d0 */  addiu      $a1, $sp, 0x5c
/* 004071d4 */  bnez       $v0, 0x4071f0
/* 004071d8 */  nop        
/* 004071dc */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 004071e0 */  lui        $a0, 0x1000
/* 004071e4 */  lw         $a1, 0x164($t3)
/* 004071e8 */  jal        0x4092d4
/* 004071ec */  addiu      $a0, $a0, 0x1b0c
/* 004071f0 */  lw         $t4, -0x7e98($gp)                        # view_state_ptr
/* 004071f4 */  lui        $at, 1
/* 004071f8 */  lw         $v0, 0x164($t4)
/* 004071fc */  ori        $at, $at, 0x86a0
/* 00407200 */  slt        $at, $v0, $at
/* 00407204 */  bnez       $at, 0x407240
/* 00407208 */  nop        
/* 0040720c */  lui        $a0, 0x1000
/* 00407210 */  lui        $a1, 0x1000
/* 00407214 */  lui        $a2, 0x1000
/* 00407218 */  addiu      $a2, $a2, 0x1b48
/* 0040721c */  addiu      $a1, $a1, 0x1b34
/* 00407220 */  jal        0xf801150                                # fclose
/* 00407224 */  addiu      $a0, $a0, 0x36b4
/* 00407228 */  jal        0x40d3c0
/* 0040722c */  addiu      $a0, $zero, 1
/* 00407230 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00407234 */  nop        
/* 00407238 */  lw         $v0, 0x164($t5)
/* 0040723c */  nop        
/* 00407240 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00407244 */  addiu      $t0, $sp, 0x5c
/* 00407248 */  lw         $t7, 0x12c($t6)
/* 0040724c */  lw         $at, ($t0)
/* 00407250 */  sll        $t8, $v0, 4
/* 00407254 */  lw         $t1, 4($t0)
/* 00407258 */  addu       $t9, $t7, $t8
/* 0040725c */  sw         $at, ($t9)
/* 00407260 */  lw         $at, 8($t0)
/* 00407264 */  sw         $t1, 4($t9)
/* 00407268 */  lw         $t1, 0xc($t0)
/* 0040726c */  sw         $at, 8($t9)
/* 00407270 */  sw         $t1, 0xc($t9)
/* 00407274 */  lw         $t2, 0x164($t6)
/* 00407278 */  nop        
/* 0040727c */  addiu      $t3, $t2, 1
/* 00407280 */  sw         $t3, 0x164($t6)
/* 00407284 */  lw         $ra, 0x34($sp)
/* 00407288 */  lw         $fp, 0x30($sp)
/* 0040728c */  lw         $s6, 0x2c($sp)
/* 00407290 */  lw         $s5, 0x28($sp)
/* 00407294 */  lw         $s4, 0x24($sp)
/* 00407298 */  lw         $s3, 0x20($sp)
/* 0040729c */  lw         $s2, 0x1c($sp)
/* 004072a0 */  lw         $s1, 0x18($sp)
/* 004072a4 */  jr         $ra
/* 004072a8 */  addiu      $sp, $sp, 0x70

# === load_binary_model ===
glabel load_binary_model
/* 004072ac */  addiu      $sp, $sp, -0x1048
/* 004072b0 */  sw         $a1, 0x104c($sp)
/* 004072b4 */  lw         $t7, 0x104c($sp)
/* 004072b8 */  sw         $s1, 0x18($sp)
/* 004072bc */  move       $s1, $a0
/* 004072c0 */  sw         $ra, 0x1c($sp)
/* 004072c4 */  sw         $s0, 0x14($sp)
/* 004072c8 */  addiu      $t6, $zero, -1
/* 004072cc */  move       $a0, $s1
/* 004072d0 */  jal        0x40a8e0
/* 004072d4 */  sw         $t6, 0xc($t7)
/* 004072d8 */  lw         $v1, ($v0)
/* 004072dc */  b          0x407338
/* 004072e0 */  addiu      $at, $zero, 0x103
/* 004072e4 */  lw         $t9, 0x104c($sp)
/* 004072e8 */  lui        $t8, 0x41
/* 004072ec */  addiu      $t8, $t8, -0x7130
/* 004072f0 */  b          0x407350
/* 004072f4 */  sw         $t8, ($t9)
/* 004072f8 */  lw         $t1, 0x104c($sp)
/* 004072fc */  lui        $t0, 0x41
/* 00407300 */  addiu      $t0, $t0, -0x709c
/* 00407304 */  sw         $t0, ($t1)
/* 00407308 */  lw         $t3, 0x104c($sp)
/* 0040730c */  addiu      $t2, $zero, 6
/* 00407310 */  b          0x407350
/* 00407314 */  sw         $t2, 0xc($t3)
/* 00407318 */  lw         $v0, 0x104c($sp)
/* 0040731c */  lui        $t4, 0x41
/* 00407320 */  addiu      $t4, $t4, -0x6f04
/* 00407324 */  addiu      $t5, $zero, 7
/* 00407328 */  sw         $t4, ($v0)
/* 0040732c */  b          0x407350
/* 00407330 */  sw         $t5, 0xc($v0)
/* 00407334 */  addiu      $at, $zero, 0x103
/* 00407338 */  beq        $v1, $at, 0x4072f8
/* 0040733c */  addiu      $at, $zero, 0x107
/* 00407340 */  beq        $v1, $at, 0x407318
/* 00407344 */  addiu      $at, $zero, 0x110
/* 00407348 */  beq        $v1, $at, 0x4072e8
/* 0040734c */  lw         $t9, 0x104c($sp)
/* 00407350 */  addiu      $s0, $sp, 0x40
/* 00407354 */  jal        0x40a8e0
/* 00407358 */  move       $a0, $s1
/* 0040735c */  beqz       $v0, 0x4073fc
/* 00407360 */  addiu      $t2, $sp, 0x40
/* 00407364 */  lw         $v1, ($v0)
/* 00407368 */  b          0x4073d0
/* 0040736c */  addiu      $at, $zero, 0x103
/* 00407370 */  lw         $t6, 8($v0)
/* 00407374 */  addiu      $s0, $s0, 0xc
/* 00407378 */  lw         $at, ($t6)
/* 0040737c */  lw         $t7, 4($t6)
/* 00407380 */  sw         $at, -0xc($s0)
/* 00407384 */  lw         $at, 8($t6)
/* 00407388 */  sw         $t7, -8($s0)
/* 0040738c */  b          0x4073e8
/* 00407390 */  sw         $at, -4($s0)
/* 00407394 */  lw         $t8, 8($v0)
/* 00407398 */  addiu      $s0, $s0, 4
/* 0040739c */  lw         $t9, ($t8)
/* 004073a0 */  b          0x4073e8
/* 004073a4 */  sw         $t9, -4($s0)
/* 004073a8 */  lw         $t0, 8($v0)
/* 004073ac */  addiu      $s0, $s0, 0xc
/* 004073b0 */  lw         $at, ($t0)
/* 004073b4 */  lw         $t1, 4($t0)
/* 004073b8 */  sw         $at, -0xc($s0)
/* 004073bc */  lw         $at, 8($t0)
/* 004073c0 */  sw         $t1, -8($s0)
/* 004073c4 */  b          0x4073e8
/* 004073c8 */  sw         $at, -4($s0)
/* 004073cc */  addiu      $at, $zero, 0x103
/* 004073d0 */  beq        $v1, $at, 0x407394
/* 004073d4 */  addiu      $at, $zero, 0x107
/* 004073d8 */  beq        $v1, $at, 0x4073a8
/* 004073dc */  addiu      $at, $zero, 0x110
/* 004073e0 */  beq        $v1, $at, 0x407370
/* 004073e4 */  nop        
/* 004073e8 */  jal        0x40a918
/* 004073ec */  move       $a0, $s1
/* 004073f0 */  bnez       $v0, 0x407364
/* 004073f4 */  nop        
/* 004073f8 */  addiu      $t2, $sp, 0x40
/* 004073fc */  subu       $v0, $s0, $t2
/* 00407400 */  bgez       $v0, 0x40740c
/* 00407404 */  move       $at, $v0
/* 00407408 */  addiu      $at, $at, 3
/* 0040740c */  sra        $v0, $at, 2
/* 00407410 */  move       $a2, $v0
/* 00407414 */  sw         $a2, 0x1044($sp)
/* 00407418 */  jal        0xf801208                                # free
/* 0040741c */  sll        $a0, $v0, 2
/* 00407420 */  lw         $a2, 0x1044($sp)
/* 00407424 */  bnez       $v0, 0x407444
/* 00407428 */  move       $s0, $v0
/* 0040742c */  lui        $a0, 0x1000
/* 00407430 */  addiu      $a0, $a0, 0x1bac
/* 00407434 */  jal        0x4092d4
/* 00407438 */  sw         $a2, 0x1044($sp)
/* 0040743c */  lw         $a2, 0x1044($sp)
/* 00407440 */  nop        
/* 00407444 */  blez       $a2, 0x4074d8
/* 00407448 */  move       $a1, $zero
/* 0040744c */  andi       $a0, $a2, 3
/* 00407450 */  beqz       $a0, 0x407490
/* 00407454 */  addiu      $t9, $sp, 0x1048
/* 00407458 */  sll        $t3, $a1, 2
/* 0040745c */  sll        $t4, $a1, 2
/* 00407460 */  addiu      $t5, $sp, 0x1048
/* 00407464 */  addu       $v0, $t4, $t5
/* 00407468 */  addu       $v1, $s0, $t3
/* 0040746c */  lw         $t7, -0x1008($v0)
/* 00407470 */  addiu      $a1, $a1, 1
/* 00407474 */  addiu      $v1, $v1, 4
/* 00407478 */  addiu      $v0, $v0, 4
/* 0040747c */  bne        $a0, $a1, 0x40746c
/* 00407480 */  sw         $t7, -4($v1)
/* 00407484 */  beq        $a1, $a2, 0x4074dc
/* 00407488 */  lw         $v1, 0x104c($sp)
/* 0040748c */  addiu      $t9, $sp, 0x1048
/* 00407490 */  sll        $t6, $a1, 2
/* 00407494 */  sll        $t8, $a1, 2
/* 00407498 */  sll        $t1, $a2, 2
/* 0040749c */  addu       $a0, $t1, $t9
/* 004074a0 */  addu       $v0, $t8, $t9
/* 004074a4 */  addu       $v1, $s0, $t6
/* 004074a8 */  lw         $t0, -0x1008($v0)
/* 004074ac */  addiu      $v0, $v0, 0x10
/* 004074b0 */  sw         $t0, ($v1)
/* 004074b4 */  lw         $t2, -0x1014($v0)
/* 004074b8 */  addiu      $v1, $v1, 0x10
/* 004074bc */  sw         $t2, -0xc($v1)
/* 004074c0 */  lw         $t3, -0x1010($v0)
/* 004074c4 */  nop        
/* 004074c8 */  sw         $t3, -8($v1)
/* 004074cc */  lw         $t4, -0x100c($v0)
/* 004074d0 */  bne        $v0, $a0, 0x4074a8
/* 004074d4 */  sw         $t4, -4($v1)
/* 004074d8 */  lw         $v1, 0x104c($sp)
/* 004074dc */  addiu      $v0, $zero, 1
/* 004074e0 */  sw         $s0, 4($v1)
/* 004074e4 */  sw         $a2, 8($v1)
/* 004074e8 */  lw         $ra, 0x1c($sp)
/* 004074ec */  lw         $s1, 0x18($sp)
/* 004074f0 */  lw         $s0, 0x14($sp)
/* 004074f4 */  jr         $ra
/* 004074f8 */  addiu      $sp, $sp, 0x1048

# === write_binary_model ===
glabel write_binary_model
/* 004074fc */  addiu      $sp, $sp, -0x88
/* 00407500 */  sw         $fp, 0x28($sp)
/* 00407504 */  sw         $ra, 0x2c($sp)
/* 00407508 */  sw         $s7, 0x24($sp)
/* 0040750c */  sw         $s3, 0x18($sp)
/* 00407510 */  sw         $s5, 0x20($sp)
/* 00407514 */  sw         $s4, 0x1c($sp)
/* 00407518 */  sw         $a0, 0x88($sp)
/* 0040751c */  sw         $a1, 0x8c($sp)
/* 00407520 */  move       $s3, $zero
/* 00407524 */  move       $s7, $zero
/* 00407528 */  move       $fp, $zero
/* 0040752c */  jal        0x40a400
/* 00407530 */  sw         $zero, 0x6c($sp)
/* 00407534 */  lw         $a0, 0x88($sp)
/* 00407538 */  jal        0x40a8e0
/* 0040753c */  move       $s5, $v0
/* 00407540 */  beqz       $v0, 0x407a60
/* 00407544 */  move       $s4, $v0
/* 00407548 */  sw         $s0, 0x3c($sp)
/* 0040754c */  sw         $s6, 0x30($sp)
/* 00407550 */  lw         $s0, 0x7c($sp)
/* 00407554 */  sw         $s1, 0x38($sp)
/* 00407558 */  addiu      $s6, $zero, -1
/* 0040755c */  sw         $s2, 0x34($sp)
/* 00407560 */  lw         $v1, ($v0)
/* 00407564 */  nop        
/* 00407568 */  addiu      $t6, $v1, -0x104
/* 0040756c */  sltiu      $at, $t6, 0xe
/* 00407570 */  beqz       $at, 0x407a0c
/* 00407574 */  nop        
/* 00407578 */  sll        $t6, $t6, 2
/* 0040757c */  lui        $at, 0x1000
/* 00407580 */  addu       $at, $at, $t6
/* 00407584 */  lw         $t6, 0x14($at)
/* 00407588 */  nop        
/* 0040758c */  jr         $t6
/* 00407590 */  nop        
/* 00407594 */  lw         $s2, 8($s4)
/* 00407598 */  jal        0xf801208                                # free
/* 0040759c */  addiu      $a0, $zero, 0xc
/* 004075a0 */  bnez       $v0, 0x4075b4
/* 004075a4 */  move       $s1, $v0
/* 004075a8 */  lui        $a0, 0x1000
/* 004075ac */  jal        0x4092d4
/* 004075b0 */  addiu      $a0, $a0, 0x1bc0
/* 004075b4 */  sw         $zero, ($s1)
/* 004075b8 */  lw         $t7, 4($s2)
/* 004075bc */  nop        
/* 004075c0 */  sw         $t7, 4($s1)
/* 004075c4 */  lw         $t8, 8($s2)
/* 004075c8 */  beqz       $s3, 0x407608
/* 004075cc */  sw         $t8, 8($s1)
/* 004075d0 */  lw         $t9, ($s4)
/* 004075d4 */  lw         $t0, ($s3)
/* 004075d8 */  nop        
/* 004075dc */  bne        $t9, $t0, 0x407608
/* 004075e0 */  nop        
/* 004075e4 */  lw         $t1, ($s2)
/* 004075e8 */  lw         $t2, 4($s3)
/* 004075ec */  nop        
/* 004075f0 */  bne        $t1, $t2, 0x407608
/* 004075f4 */  nop        
/* 004075f8 */  sw         $s1, ($s7)
/* 004075fc */  move       $s7, $s1
/* 00407600 */  b          0x407a34
/* 00407604 */  move       $s3, $s0
/* 00407608 */  jal        0xf801208                                # free
/* 0040760c */  addiu      $a0, $zero, 0x10
/* 00407610 */  bnez       $v0, 0x407624
/* 00407614 */  move       $s0, $v0
/* 00407618 */  lui        $a0, 0x1000
/* 0040761c */  jal        0x4092d4
/* 00407620 */  addiu      $a0, $a0, 0x1bd0
/* 00407624 */  lw         $t3, ($s4)
/* 00407628 */  move       $a0, $s5
/* 0040762c */  sw         $t3, ($s0)
/* 00407630 */  lw         $t4, ($s2)
/* 00407634 */  move       $a1, $s0
/* 00407638 */  sw         $t4, 4($s0)
/* 0040763c */  lw         $t5, 0xc($s2)
/* 00407640 */  sw         $s1, 8($s0)
/* 00407644 */  jal        0x40a6d4
/* 00407648 */  sw         $t5, 0xc($s0)
/* 0040764c */  move       $s7, $s1
/* 00407650 */  b          0x407a34
/* 00407654 */  move       $s3, $s0
/* 00407658 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 0040765c */  lw         $t9, 4($s4)
/* 00407660 */  lw         $t8, 0x130($t7)
/* 00407664 */  sll        $t0, $t9, 4
/* 00407668 */  addu       $t1, $t8, $t0
/* 0040766c */  lw         $at, ($t1)
/* 00407670 */  lw         $t2, 4($t1)
/* 00407674 */  addiu      $t6, $sp, 0x50
/* 00407678 */  sw         $at, ($t6)
/* 0040767c */  lw         $at, 8($t1)
/* 00407680 */  sw         $t2, 4($t6)
/* 00407684 */  lw         $t2, 0xc($t1)
/* 00407688 */  sw         $at, 8($t6)
/* 0040768c */  addiu      $a0, $zero, 0xc
/* 00407690 */  jal        0xf801208                                # free
/* 00407694 */  sw         $t2, 0xc($t6)
/* 00407698 */  bnez       $v0, 0x4076ac
/* 0040769c */  move       $s1, $v0
/* 004076a0 */  lui        $a0, 0x1000
/* 004076a4 */  jal        0x4092d4
/* 004076a8 */  addiu      $a0, $a0, 0x1be0
/* 004076ac */  sw         $zero, ($s1)
/* 004076b0 */  lw         $t3, 0x54($sp)
/* 004076b4 */  nop        
/* 004076b8 */  sw         $t3, 4($s1)
/* 004076bc */  lw         $t4, 0x58($sp)
/* 004076c0 */  beqz       $s3, 0x407704
/* 004076c4 */  sw         $t4, 8($s1)
/* 004076c8 */  lw         $t5, ($s4)
/* 004076cc */  lw         $t7, ($s3)
/* 004076d0 */  nop        
/* 004076d4 */  bne        $t5, $t7, 0x407704
/* 004076d8 */  nop        
/* 004076dc */  lw         $t9, 0x50($sp)
/* 004076e0 */  lw         $t8, 4($s3)
/* 004076e4 */  nop        
/* 004076e8 */  bne        $t9, $t8, 0x407704
/* 004076ec */  nop        
/* 004076f0 */  lw         $t0, 0x6c($sp)
/* 004076f4 */  move       $s3, $s0
/* 004076f8 */  sw         $s1, ($t0)
/* 004076fc */  b          0x407a34
/* 00407700 */  sw         $s1, 0x6c($sp)
/* 00407704 */  jal        0xf801208                                # free
/* 00407708 */  addiu      $a0, $zero, 0x10
/* 0040770c */  bnez       $v0, 0x407720
/* 00407710 */  move       $s0, $v0
/* 00407714 */  lui        $a0, 0x1000
/* 00407718 */  jal        0x4092d4
/* 0040771c */  addiu      $a0, $a0, 0x1bf0
/* 00407720 */  lw         $t2, ($s4)
/* 00407724 */  move       $a0, $s5
/* 00407728 */  sw         $t2, ($s0)
/* 0040772c */  lw         $t6, 0x50($sp)
/* 00407730 */  sw         $s1, 8($s0)
/* 00407734 */  move       $a1, $s0
/* 00407738 */  jal        0x40a6d4
/* 0040773c */  sw         $t6, 4($s0)
/* 00407740 */  sw         $s1, 0x6c($sp)
/* 00407744 */  b          0x407a34
/* 00407748 */  move       $s3, $s0
/* 0040774c */  lw         $s2, 8($s4)
/* 00407750 */  jal        0xf801208                                # free
/* 00407754 */  addiu      $a0, $zero, 0xc
/* 00407758 */  bnez       $v0, 0x40776c
/* 0040775c */  move       $s1, $v0
/* 00407760 */  lui        $a0, 0x1000
/* 00407764 */  jal        0x4092d4
/* 00407768 */  addiu      $a0, $a0, 0x1c00
/* 0040776c */  sw         $zero, ($s1)
/* 00407770 */  lw         $t1, 4($s2)
/* 00407774 */  nop        
/* 00407778 */  sw         $t1, 4($s1)
/* 0040777c */  lw         $t3, 8($s2)
/* 00407780 */  beqz       $s3, 0x4077c0
/* 00407784 */  sw         $t3, 8($s1)
/* 00407788 */  lw         $t4, ($s4)
/* 0040778c */  lw         $t5, ($s3)
/* 00407790 */  nop        
/* 00407794 */  bne        $t4, $t5, 0x4077c0
/* 00407798 */  nop        
/* 0040779c */  lw         $t7, ($s2)
/* 004077a0 */  lw         $t9, 4($s3)
/* 004077a4 */  nop        
/* 004077a8 */  bne        $t7, $t9, 0x4077c0
/* 004077ac */  nop        
/* 004077b0 */  sw         $s1, ($fp)
/* 004077b4 */  move       $fp, $s1
/* 004077b8 */  b          0x407a34
/* 004077bc */  move       $s3, $s0
/* 004077c0 */  jal        0xf801208                                # free
/* 004077c4 */  addiu      $a0, $zero, 0x10
/* 004077c8 */  bnez       $v0, 0x4077dc
/* 004077cc */  move       $s0, $v0
/* 004077d0 */  lui        $a0, 0x1000
/* 004077d4 */  jal        0x4092d4
/* 004077d8 */  addiu      $a0, $a0, 0x1c10
/* 004077dc */  lw         $t8, ($s4)
/* 004077e0 */  move       $a0, $s5
/* 004077e4 */  sw         $t8, ($s0)
/* 004077e8 */  lw         $t0, ($s2)
/* 004077ec */  move       $a1, $s0
/* 004077f0 */  sw         $t0, 4($s0)
/* 004077f4 */  lw         $t2, 0xc($s2)
/* 004077f8 */  sw         $s1, 8($s0)
/* 004077fc */  jal        0x40a6d4
/* 00407800 */  sw         $t2, 0xc($s0)
/* 00407804 */  move       $fp, $s1
/* 00407808 */  b          0x407a34
/* 0040780c */  move       $s3, $s0
/* 00407810 */  lui        $s1, 0x41
/* 00407814 */  addiu      $s1, $s1, -0x7c10
/* 00407818 */  jal        0xf801208                                # free
/* 0040781c */  addiu      $a0, $zero, 0x10
/* 00407820 */  bnez       $v0, 0x407834
/* 00407824 */  move       $s0, $v0
/* 00407828 */  lui        $a0, 0x1000
/* 0040782c */  jal        0x4092d4
/* 00407830 */  addiu      $a0, $a0, 0x1c20
/* 00407834 */  lw         $t6, ($s4)
/* 00407838 */  sw         $s1, 4($s0)
/* 0040783c */  sw         $s6, 0xc($s0)
/* 00407840 */  sw         $t6, ($s0)
/* 00407844 */  lw         $t4, 4($s4)
/* 00407848 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 0040784c */  sll        $t5, $t4, 3
/* 00407850 */  lw         $t3, 0x124($t1)
/* 00407854 */  addu       $t5, $t5, $t4
/* 00407858 */  sll        $t5, $t5, 2
/* 0040785c */  addu       $t7, $t3, $t5
/* 00407860 */  sw         $t7, 8($s0)
/* 00407864 */  move       $a0, $s5
/* 00407868 */  jal        0x40a6d4
/* 0040786c */  move       $a1, $s0
/* 00407870 */  b          0x407a34
/* 00407874 */  move       $s3, $s0
/* 00407878 */  lui        $s1, 0x41
/* 0040787c */  addiu      $s1, $s1, -0x79f8
/* 00407880 */  jal        0xf801208                                # free
/* 00407884 */  addiu      $a0, $zero, 0x10
/* 00407888 */  bnez       $v0, 0x40789c
/* 0040788c */  move       $s0, $v0
/* 00407890 */  lui        $a0, 0x1000
/* 00407894 */  jal        0x4092d4
/* 00407898 */  addiu      $a0, $a0, 0x1c30
/* 0040789c */  lw         $t9, ($s4)
/* 004078a0 */  sw         $s1, 4($s0)
/* 004078a4 */  sw         $s6, 0xc($s0)
/* 004078a8 */  sw         $t9, ($s0)
/* 004078ac */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 004078b0 */  lw         $t2, 4($s4)
/* 004078b4 */  lw         $t0, 0x118($t8)
/* 004078b8 */  sll        $t6, $t2, 4
/* 004078bc */  addu       $t1, $t0, $t6
/* 004078c0 */  sw         $t1, 8($s0)
/* 004078c4 */  move       $a0, $s5
/* 004078c8 */  jal        0x40a6d4
/* 004078cc */  move       $a1, $s0
/* 004078d0 */  b          0x407a34
/* 004078d4 */  move       $s3, $s0
/* 004078d8 */  lui        $s1, 0x41
/* 004078dc */  addiu      $s1, $s1, -0x7910
/* 004078e0 */  jal        0xf801208                                # free
/* 004078e4 */  addiu      $a0, $zero, 0x10
/* 004078e8 */  bnez       $v0, 0x4078fc
/* 004078ec */  move       $s0, $v0
/* 004078f0 */  lui        $a0, 0x1000
/* 004078f4 */  jal        0x4092d4
/* 004078f8 */  addiu      $a0, $a0, 0x1c40
/* 004078fc */  lw         $t4, ($s4)
/* 00407900 */  sw         $s1, 4($s0)
/* 00407904 */  sw         $s6, 0xc($s0)
/* 00407908 */  sw         $t4, ($s0)
/* 0040790c */  lw         $t7, 4($s4)
/* 00407910 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00407914 */  sll        $t9, $t7, 2
/* 00407918 */  lw         $t5, 0x11c($t3)
/* 0040791c */  subu       $t9, $t9, $t7
/* 00407920 */  sll        $t9, $t9, 2
/* 00407924 */  addu       $t8, $t5, $t9
/* 00407928 */  sw         $t8, 8($s0)
/* 0040792c */  move       $a0, $s5
/* 00407930 */  jal        0x40a6d4
/* 00407934 */  move       $a1, $s0
/* 00407938 */  b          0x407a34
/* 0040793c */  move       $s3, $s0
/* 00407940 */  lui        $s1, 0x41
/* 00407944 */  addiu      $s1, $s1, -0x78e4
/* 00407948 */  jal        0xf801208                                # free
/* 0040794c */  addiu      $a0, $zero, 0x10
/* 00407950 */  bnez       $v0, 0x407964
/* 00407954 */  move       $s0, $v0
/* 00407958 */  lui        $a0, 0x1000
/* 0040795c */  jal        0x4092d4
/* 00407960 */  addiu      $a0, $a0, 0x1c50
/* 00407964 */  lw         $t2, ($s4)
/* 00407968 */  sw         $s1, 4($s0)
/* 0040796c */  sw         $s6, 0xc($s0)
/* 00407970 */  sw         $t2, ($s0)
/* 00407974 */  lw         $t1, 4($s4)
/* 00407978 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 0040797c */  sll        $t4, $t1, 2
/* 00407980 */  lw         $t6, 0x120($t0)
/* 00407984 */  subu       $t4, $t4, $t1
/* 00407988 */  sll        $t4, $t4, 2
/* 0040798c */  addu       $t3, $t6, $t4
/* 00407990 */  sw         $t3, 8($s0)
/* 00407994 */  move       $a0, $s5
/* 00407998 */  jal        0x40a6d4
/* 0040799c */  move       $a1, $s0
/* 004079a0 */  b          0x407a34
/* 004079a4 */  move       $s3, $s0
/* 004079a8 */  lui        $s1, 0x41
/* 004079ac */  addiu      $s1, $s1, -0x7cf8
/* 004079b0 */  jal        0xf801208                                # free
/* 004079b4 */  addiu      $a0, $zero, 0x10
/* 004079b8 */  bnez       $v0, 0x4079cc
/* 004079bc */  move       $s0, $v0
/* 004079c0 */  lui        $a0, 0x1000
/* 004079c4 */  jal        0x4092d4
/* 004079c8 */  addiu      $a0, $a0, 0x1c60
/* 004079cc */  lw         $t7, ($s4)
/* 004079d0 */  sw         $s1, 4($s0)
/* 004079d4 */  sw         $s6, 0xc($s0)
/* 004079d8 */  sw         $t7, ($s0)
/* 004079dc */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 004079e0 */  lw         $t8, 4($s4)
/* 004079e4 */  lw         $t9, 0x138($t5)
/* 004079e8 */  sll        $t2, $t8, 2
/* 004079ec */  addu       $t0, $t9, $t2
/* 004079f0 */  lw         $t1, ($t0)
/* 004079f4 */  move       $a0, $s5
/* 004079f8 */  move       $a1, $s0
/* 004079fc */  jal        0x40a6d4
/* 00407a00 */  sw         $t1, 8($s0)
/* 00407a04 */  b          0x407a34
/* 00407a08 */  move       $s3, $s0
/* 00407a0c */  lui        $a0, 0x1000
/* 00407a10 */  lw         $a1, ($s4)
/* 00407a14 */  jal        0xf801250                                # getopt
/* 00407a18 */  addiu      $a0, $a0, 0x1c70
/* 00407a1c */  lw         $s0, 0x3c($sp)
/* 00407a20 */  lw         $s1, 0x38($sp)
/* 00407a24 */  lw         $s2, 0x34($sp)
/* 00407a28 */  lw         $s6, 0x30($sp)
/* 00407a2c */  b          0x407a6c
/* 00407a30 */  move       $v0, $zero
/* 00407a34 */  lw         $a0, 0x88($sp)
/* 00407a38 */  jal        0x40a918
/* 00407a3c */  nop        
/* 00407a40 */  bnez       $v0, 0x407560
/* 00407a44 */  move       $s4, $v0
/* 00407a48 */  sw         $s0, 0x7c($sp)
/* 00407a4c */  lw         $s0, 0x3c($sp)
/* 00407a50 */  lw         $s1, 0x38($sp)
/* 00407a54 */  lw         $s2, 0x34($sp)
/* 00407a58 */  lw         $s6, 0x30($sp)
/* 00407a5c */  nop        
/* 00407a60 */  lw         $t6, 0x8c($sp)
/* 00407a64 */  addiu      $v0, $zero, 1
/* 00407a68 */  sw         $s5, ($t6)
/* 00407a6c */  lw         $ra, 0x2c($sp)
/* 00407a70 */  lw         $s3, 0x18($sp)
/* 00407a74 */  lw         $s4, 0x1c($sp)
/* 00407a78 */  lw         $s5, 0x20($sp)
/* 00407a7c */  lw         $s7, 0x24($sp)
/* 00407a80 */  lw         $fp, 0x28($sp)
/* 00407a84 */  jr         $ra
/* 00407a88 */  addiu      $sp, $sp, 0x88

# === main_init_1 ===
glabel main_init_1
/* 00407a8c */  addiu      $sp, $sp, -0x28
/* 00407a90 */  sw         $ra, 0x14($sp)
/* 00407a94 */  jal        0x4074fc                                 # write_binary_model
/* 00407a98 */  addiu      $a1, $sp, 0x24
/* 00407a9c */  bnez       $v0, 0x407adc
/* 00407aa0 */  nop        
/* 00407aa4 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00407aa8 */  lui        $a0, 0x1000
/* 00407aac */  lw         $t7, 0x170($t6)
/* 00407ab0 */  lw         $t8, 0x194($t6)
/* 00407ab4 */  addiu      $a0, $a0, 0x1c98
/* 00407ab8 */  jal        0xf801250                                # getopt
/* 00407abc */  subu       $a1, $t7, $t8
/* 00407ac0 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00407ac4 */  nop        
/* 00407ac8 */  lw         $t0, 0x170($t9)
/* 00407acc */  nop        
/* 00407ad0 */  addiu      $t1, $t0, 1
/* 00407ad4 */  b          0x407b5c
/* 00407ad8 */  sw         $t1, 0x170($t9)
/* 00407adc */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00407ae0 */  nop        
/* 00407ae4 */  lw         $v0, 0x170($t2)
/* 00407ae8 */  nop        
/* 00407aec */  slti       $at, $v0, 0x64
/* 00407af0 */  bnez       $at, 0x407b2c
/* 00407af4 */  nop        
/* 00407af8 */  lui        $a0, 0x1000
/* 00407afc */  lui        $a1, 0x1000
/* 00407b00 */  lui        $a2, 0x1000
/* 00407b04 */  addiu      $a2, $a2, 0x1cd8
/* 00407b08 */  addiu      $a1, $a1, 0x1cc4
/* 00407b0c */  jal        0xf801150                                # fclose
/* 00407b10 */  addiu      $a0, $a0, 0x36b4
/* 00407b14 */  jal        0x40d3c0
/* 00407b18 */  addiu      $a0, $zero, 1
/* 00407b1c */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00407b20 */  nop        
/* 00407b24 */  lw         $v0, 0x170($t3)
/* 00407b28 */  nop        
/* 00407b2c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00407b30 */  lw         $t4, 0x24($sp)
/* 00407b34 */  lw         $t6, 0x138($t5)
/* 00407b38 */  sll        $t7, $v0, 2
/* 00407b3c */  addu       $t8, $t6, $t7
/* 00407b40 */  sw         $t4, ($t8)
/* 00407b44 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00407b48 */  nop        
/* 00407b4c */  lw         $t1, 0x170($t0)
/* 00407b50 */  nop        
/* 00407b54 */  addiu      $t9, $t1, 1
/* 00407b58 */  sw         $t9, 0x170($t0)
/* 00407b5c */  lw         $ra, 0x14($sp)
/* 00407b60 */  addiu      $sp, $sp, 0x28
/* 00407b64 */  jr         $ra
/* 00407b68 */  nop        

# === main_init_2 ===
glabel main_init_2
/* 00407b6c */  addiu      $sp, $sp, -0x28
/* 00407b70 */  sw         $ra, 0x14($sp)
/* 00407b74 */  jal        0x4074fc                                 # write_binary_model
/* 00407b78 */  addiu      $a1, $sp, 0x24
/* 00407b7c */  bnez       $v0, 0x407bb4
/* 00407b80 */  nop        
/* 00407b84 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00407b88 */  lui        $a0, 0x1000
/* 00407b8c */  lw         $a1, 0x174($t6)
/* 00407b90 */  jal        0xf801250                                # getopt
/* 00407b94 */  addiu      $a0, $a0, 0x1ce4
/* 00407b98 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00407b9c */  nop        
/* 00407ba0 */  lw         $t8, 0x174($t7)
/* 00407ba4 */  nop        
/* 00407ba8 */  addiu      $t9, $t8, 1
/* 00407bac */  b          0x407c34
/* 00407bb0 */  sw         $t9, 0x174($t7)
/* 00407bb4 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00407bb8 */  nop        
/* 00407bbc */  lw         $v0, 0x174($t0)
/* 00407bc0 */  nop        
/* 00407bc4 */  slti       $at, $v0, 0xc8
/* 00407bc8 */  bnez       $at, 0x407c04
/* 00407bcc */  nop        
/* 00407bd0 */  lui        $a0, 0x1000
/* 00407bd4 */  lui        $a1, 0x1000
/* 00407bd8 */  lui        $a2, 0x1000
/* 00407bdc */  addiu      $a2, $a2, 0x1d28
/* 00407be0 */  addiu      $a1, $a1, 0x1d14
/* 00407be4 */  jal        0xf801150                                # fclose
/* 00407be8 */  addiu      $a0, $a0, 0x36b4
/* 00407bec */  jal        0x40d3c0
/* 00407bf0 */  addiu      $a0, $zero, 1
/* 00407bf4 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00407bf8 */  nop        
/* 00407bfc */  lw         $v0, 0x174($t1)
/* 00407c00 */  nop        
/* 00407c04 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00407c08 */  lw         $t2, 0x24($sp)
/* 00407c0c */  lw         $t4, 0x13c($t3)
/* 00407c10 */  sll        $t5, $v0, 2
/* 00407c14 */  addu       $t6, $t4, $t5
/* 00407c18 */  sw         $t2, ($t6)
/* 00407c1c */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00407c20 */  nop        
/* 00407c24 */  lw         $t9, 0x174($t8)
/* 00407c28 */  nop        
/* 00407c2c */  addiu      $t7, $t9, 1
/* 00407c30 */  sw         $t7, 0x174($t8)
/* 00407c34 */  lw         $ra, 0x14($sp)
/* 00407c38 */  addiu      $sp, $sp, 0x28
/* 00407c3c */  jr         $ra
/* 00407c40 */  nop        
/* 00407c44 */  addiu      $sp, $sp, -0x28
/* 00407c48 */  sw         $ra, 0x1c($sp)
/* 00407c4c */  sw         $s0, 0x18($sp)
/* 00407c50 */  sw         $a0, 0x28($sp)
/* 00407c54 */  move       $s0, $a1
/* 00407c58 */  jal        0xf801208                                # free
/* 00407c5c */  addiu      $a0, $zero, 0xc
/* 00407c60 */  bnez       $v0, 0x407c7c
/* 00407c64 */  move       $v1, $v0
/* 00407c68 */  addiu      $a0, $gp, -0x7c60
/* 00407c6c */  jal        0x4092d4
/* 00407c70 */  sw         $v1, 0x24($sp)
/* 00407c74 */  lw         $v1, 0x24($sp)
/* 00407c78 */  nop        
/* 00407c7c */  lw         $t6, 0x28($sp)
/* 00407c80 */  nop        
/* 00407c84 */  addiu      $t7, $t6, -0x103
/* 00407c88 */  sltiu      $at, $t7, 0xf
/* 00407c8c */  beqz       $at, 0x40802c
/* 00407c90 */  nop        
/* 00407c94 */  sll        $t7, $t7, 2
/* 00407c98 */  lui        $at, 0x1000
/* 00407c9c */  addu       $at, $at, $t7
/* 00407ca0 */  lw         $t7, 0x4c($at)
/* 00407ca4 */  nop        
/* 00407ca8 */  jr         $t7
/* 00407cac */  nop        
/* 00407cb0 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00407cb4 */  nop        
/* 00407cb8 */  lw         $v0, 0x178($t8)
/* 00407cbc */  lw         $t9, 0x140($t8)
/* 00407cc0 */  nop        
/* 00407cc4 */  subu       $t0, $t9, $v0
/* 00407cc8 */  slt        $at, $s0, $t0
/* 00407ccc */  bnez       $at, 0x407d00
/* 00407cd0 */  nop        
/* 00407cd4 */  lui        $a0, 0x1000
/* 00407cd8 */  lui        $a1, 0x1000
/* 00407cdc */  addiu      $a1, $a1, 0x3ed0
/* 00407ce0 */  addiu      $a0, $a0, 0x1d38
/* 00407ce4 */  move       $a2, $s0
/* 00407ce8 */  jal        0x4092d4
/* 00407cec */  sw         $v1, 0x24($sp)
/* 00407cf0 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00407cf4 */  lw         $v1, 0x24($sp)
/* 00407cf8 */  lw         $v0, 0x178($t1)
/* 00407cfc */  nop        
/* 00407d00 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00407d04 */  addu       $t4, $v0, $s0
/* 00407d08 */  lw         $t3, 0x108($t2)
/* 00407d0c */  sll        $t5, $t4, 2
/* 00407d10 */  addu       $t6, $t3, $t5
/* 00407d14 */  b          0x408054
/* 00407d18 */  sw         $t6, 8($v1)
/* 00407d1c */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00407d20 */  nop        
/* 00407d24 */  lw         $v0, 0x17c($t7)
/* 00407d28 */  lw         $t8, 0x148($t7)
/* 00407d2c */  nop        
/* 00407d30 */  subu       $t9, $t8, $v0
/* 00407d34 */  slt        $at, $s0, $t9
/* 00407d38 */  bnez       $at, 0x407d6c
/* 00407d3c */  nop        
/* 00407d40 */  lui        $a0, 0x1000
/* 00407d44 */  lui        $a1, 0x1000
/* 00407d48 */  addiu      $a1, $a1, 0x3ed0
/* 00407d4c */  addiu      $a0, $a0, 0x1d54
/* 00407d50 */  move       $a2, $s0
/* 00407d54 */  jal        0x4092d4
/* 00407d58 */  sw         $v1, 0x24($sp)
/* 00407d5c */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00407d60 */  lw         $v1, 0x24($sp)
/* 00407d64 */  lw         $v0, 0x17c($t0)
/* 00407d68 */  nop        
/* 00407d6c */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00407d70 */  addu       $t4, $v0, $s0
/* 00407d74 */  sll        $t3, $t4, 2
/* 00407d78 */  lw         $t2, 0x114($t1)
/* 00407d7c */  subu       $t3, $t3, $t4
/* 00407d80 */  sll        $t3, $t3, 2
/* 00407d84 */  addu       $t5, $t2, $t3
/* 00407d88 */  b          0x408054
/* 00407d8c */  sw         $t5, 8($v1)
/* 00407d90 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00407d94 */  nop        
/* 00407d98 */  lw         $v0, 0x180($t6)
/* 00407d9c */  lw         $t7, 0x14c($t6)
/* 00407da0 */  nop        
/* 00407da4 */  subu       $t8, $t7, $v0
/* 00407da8 */  slt        $at, $s0, $t8
/* 00407dac */  bnez       $at, 0x407de0
/* 00407db0 */  nop        
/* 00407db4 */  lui        $a0, 0x1000
/* 00407db8 */  lui        $a1, 0x1000
/* 00407dbc */  addiu      $a1, $a1, 0x3ed0
/* 00407dc0 */  addiu      $a0, $a0, 0x1d6c
/* 00407dc4 */  move       $a2, $s0
/* 00407dc8 */  jal        0x4092d4
/* 00407dcc */  sw         $v1, 0x24($sp)
/* 00407dd0 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00407dd4 */  lw         $v1, 0x24($sp)
/* 00407dd8 */  lw         $v0, 0x180($t9)
/* 00407ddc */  nop        
/* 00407de0 */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00407de4 */  addu       $t4, $v0, $s0
/* 00407de8 */  sll        $t2, $t4, 2
/* 00407dec */  lw         $t1, 0x110($t0)
/* 00407df0 */  subu       $t2, $t2, $t4
/* 00407df4 */  sll        $t2, $t2, 2
/* 00407df8 */  addu       $t3, $t1, $t2
/* 00407dfc */  b          0x408054
/* 00407e00 */  sw         $t3, 8($v1)
/* 00407e04 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00407e08 */  nop        
/* 00407e0c */  lw         $v0, 0x184($t5)
/* 00407e10 */  lw         $t6, 0x15c($t5)
/* 00407e14 */  nop        
/* 00407e18 */  subu       $t7, $t6, $v0
/* 00407e1c */  slt        $at, $s0, $t7
/* 00407e20 */  bnez       $at, 0x407e54
/* 00407e24 */  nop        
/* 00407e28 */  lui        $a0, 0x1000
/* 00407e2c */  lui        $a1, 0x1000
/* 00407e30 */  addiu      $a1, $a1, 0x3ed0
/* 00407e34 */  addiu      $a0, $a0, 0x1d84
/* 00407e38 */  move       $a2, $s0
/* 00407e3c */  jal        0x4092d4
/* 00407e40 */  sw         $v1, 0x24($sp)
/* 00407e44 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00407e48 */  lw         $v1, 0x24($sp)
/* 00407e4c */  lw         $v0, 0x184($t8)
/* 00407e50 */  nop        
/* 00407e54 */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 00407e58 */  addu       $t4, $v0, $s0
/* 00407e5c */  sll        $t1, $t4, 3
/* 00407e60 */  lw         $t0, 0x124($t9)
/* 00407e64 */  addu       $t1, $t1, $t4
/* 00407e68 */  sll        $t1, $t1, 2
/* 00407e6c */  addu       $t2, $t0, $t1
/* 00407e70 */  b          0x408054
/* 00407e74 */  sw         $t2, 8($v1)
/* 00407e78 */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00407e7c */  nop        
/* 00407e80 */  lw         $v0, 0x188($t3)
/* 00407e84 */  lw         $t5, 0x160($t3)
/* 00407e88 */  nop        
/* 00407e8c */  subu       $t6, $t5, $v0
/* 00407e90 */  slt        $at, $s0, $t6
/* 00407e94 */  bnez       $at, 0x407ec8
/* 00407e98 */  nop        
/* 00407e9c */  lui        $a0, 0x1000
/* 00407ea0 */  lui        $a1, 0x1000
/* 00407ea4 */  addiu      $a1, $a1, 0x3ed0
/* 00407ea8 */  addiu      $a0, $a0, 0x1da4
/* 00407eac */  move       $a2, $s0
/* 00407eb0 */  jal        0x4092d4
/* 00407eb4 */  sw         $v1, 0x24($sp)
/* 00407eb8 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00407ebc */  lw         $v1, 0x24($sp)
/* 00407ec0 */  lw         $v0, 0x188($t7)
/* 00407ec4 */  nop        
/* 00407ec8 */  lw         $t8, -0x7e98($gp)                        # view_state_ptr
/* 00407ecc */  addu       $t4, $v0, $s0
/* 00407ed0 */  lw         $t9, 0x128($t8)
/* 00407ed4 */  sll        $t0, $t4, 4
/* 00407ed8 */  addu       $t1, $t9, $t0
/* 00407edc */  b          0x408054
/* 00407ee0 */  sw         $t1, 8($v1)
/* 00407ee4 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00407ee8 */  nop        
/* 00407eec */  lw         $v0, 0x18c($t2)
/* 00407ef0 */  lw         $t3, 0x164($t2)
/* 00407ef4 */  nop        
/* 00407ef8 */  subu       $t5, $t3, $v0
/* 00407efc */  slt        $at, $s0, $t5
/* 00407f00 */  bnez       $at, 0x407f34
/* 00407f04 */  nop        
/* 00407f08 */  lui        $a0, 0x1000
/* 00407f0c */  lui        $a1, 0x1000
/* 00407f10 */  addiu      $a1, $a1, 0x3ed0
/* 00407f14 */  addiu      $a0, $a0, 0x1dc0
/* 00407f18 */  move       $a2, $s0
/* 00407f1c */  jal        0x4092d4
/* 00407f20 */  sw         $v1, 0x24($sp)
/* 00407f24 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00407f28 */  lw         $v1, 0x24($sp)
/* 00407f2c */  lw         $v0, 0x18c($t6)
/* 00407f30 */  nop        
/* 00407f34 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 00407f38 */  addu       $t4, $v0, $s0
/* 00407f3c */  lw         $t8, 0x12c($t7)
/* 00407f40 */  sll        $t9, $t4, 4
/* 00407f44 */  addu       $t0, $t8, $t9
/* 00407f48 */  b          0x408054
/* 00407f4c */  sw         $t0, 8($v1)
/* 00407f50 */  lw         $t1, -0x7e98($gp)                        # view_state_ptr
/* 00407f54 */  nop        
/* 00407f58 */  lw         $v0, 0x190($t1)
/* 00407f5c */  lw         $t2, 0x168($t1)
/* 00407f60 */  nop        
/* 00407f64 */  subu       $t3, $t2, $v0
/* 00407f68 */  slt        $at, $s0, $t3
/* 00407f6c */  bnez       $at, 0x407fa0
/* 00407f70 */  nop        
/* 00407f74 */  lui        $a0, 0x1000
/* 00407f78 */  lui        $a1, 0x1000
/* 00407f7c */  addiu      $a1, $a1, 0x3ed0
/* 00407f80 */  addiu      $a0, $a0, 0x1ddc
/* 00407f84 */  move       $a2, $s0
/* 00407f88 */  jal        0x4092d4
/* 00407f8c */  sw         $v1, 0x24($sp)
/* 00407f90 */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00407f94 */  lw         $v1, 0x24($sp)
/* 00407f98 */  lw         $v0, 0x190($t5)
/* 00407f9c */  nop        
/* 00407fa0 */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00407fa4 */  addu       $t4, $v0, $s0
/* 00407fa8 */  lw         $t7, 0x130($t6)
/* 00407fac */  sll        $t8, $t4, 4
/* 00407fb0 */  addu       $t9, $t7, $t8
/* 00407fb4 */  b          0x408054
/* 00407fb8 */  sw         $t9, 8($v1)
/* 00407fbc */  lw         $t0, -0x7e98($gp)                        # view_state_ptr
/* 00407fc0 */  nop        
/* 00407fc4 */  lw         $v0, 0x194($t0)
/* 00407fc8 */  lw         $t1, 0x170($t0)
/* 00407fcc */  nop        
/* 00407fd0 */  subu       $t2, $t1, $v0
/* 00407fd4 */  slt        $at, $s0, $t2
/* 00407fd8 */  bnez       $at, 0x40800c
/* 00407fdc */  nop        
/* 00407fe0 */  lui        $a0, 0x1000
/* 00407fe4 */  lui        $a1, 0x1000
/* 00407fe8 */  addiu      $a1, $a1, 0x3ed0
/* 00407fec */  addiu      $a0, $a0, 0x1df8
/* 00407ff0 */  move       $a2, $s0
/* 00407ff4 */  jal        0x4092d4
/* 00407ff8 */  sw         $v1, 0x24($sp)
/* 00407ffc */  lw         $t3, -0x7e98($gp)                        # view_state_ptr
/* 00408000 */  lw         $v1, 0x24($sp)
/* 00408004 */  lw         $v0, 0x194($t3)
/* 00408008 */  nop        
/* 0040800c */  lw         $t5, -0x7e98($gp)                        # view_state_ptr
/* 00408010 */  addu       $t4, $v0, $s0
/* 00408014 */  lw         $t6, 0x138($t5)
/* 00408018 */  sll        $t7, $t4, 2
/* 0040801c */  addu       $t8, $t6, $t7
/* 00408020 */  lw         $t9, ($t8)
/* 00408024 */  b          0x408054
/* 00408028 */  sw         $t9, 8($v1)
/* 0040802c */  lui        $a0, 0x1000
/* 00408030 */  lui        $a1, 0x1000
/* 00408034 */  lw         $a2, 0x28($sp)
/* 00408038 */  addiu      $a1, $a1, 0x1e14
/* 0040803c */  addiu      $a0, $a0, 0x36b4
/* 00408040 */  move       $a3, $s0
/* 00408044 */  jal        0xf801150                                # fclose
/* 00408048 */  sw         $v1, 0x24($sp)
/* 0040804c */  lw         $v1, 0x24($sp)
/* 00408050 */  nop        
/* 00408054 */  lw         $t0, 0x28($sp)
/* 00408058 */  sw         $s0, 4($v1)
/* 0040805c */  sw         $t0, ($v1)
/* 00408060 */  lw         $ra, 0x1c($sp)
/* 00408064 */  lw         $s0, 0x18($sp)
/* 00408068 */  addiu      $sp, $sp, 0x28
/* 0040806c */  jr         $ra
/* 00408070 */  move       $v0, $v1
/* 00408074 */  addiu      $sp, $sp, -0x20
/* 00408078 */  sw         $s0, 0x18($sp)
/* 0040807c */  move       $s0, $a0
/* 00408080 */  sw         $ra, 0x1c($sp)
/* 00408084 */  jal        0x40a8e0
/* 00408088 */  move       $a0, $s0
/* 0040808c */  beqz       $v0, 0x4080ac
/* 00408090 */  move       $a0, $v0
/* 00408094 */  jal        0xf801200                                # malloc
/* 00408098 */  nop        
/* 0040809c */  jal        0x40a918
/* 004080a0 */  move       $a0, $s0
/* 004080a4 */  bnez       $v0, 0x408094
/* 004080a8 */  move       $a0, $v0
/* 004080ac */  jal        0x40a48c
/* 004080b0 */  move       $a0, $s0
/* 004080b4 */  lw         $ra, 0x1c($sp)
/* 004080b8 */  lw         $s0, 0x18($sp)
/* 004080bc */  jr         $ra
/* 004080c0 */  addiu      $sp, $sp, 0x20
/* 004080c4 */  addiu      $sp, $sp, -0x20
/* 004080c8 */  sw         $ra, 0x14($sp)
/* 004080cc */  sw         $a0, 0x20($sp)
/* 004080d0 */  sw         $a1, 0x24($sp)
/* 004080d4 */  jal        0xf801208                                # free
/* 004080d8 */  addiu      $a0, $zero, 0x10
/* 004080dc */  bnez       $v0, 0x4080fc
/* 004080e0 */  move       $v1, $v0
/* 004080e4 */  lui        $a0, 0x1000
/* 004080e8 */  addiu      $a0, $a0, 0x1e3c
/* 004080ec */  jal        0x4092d4
/* 004080f0 */  sw         $v1, 0x1c($sp)
/* 004080f4 */  lw         $v1, 0x1c($sp)
/* 004080f8 */  nop        
/* 004080fc */  lw         $t6, 0x20($sp)
/* 00408100 */  move       $v0, $v1
/* 00408104 */  sw         $t6, ($v1)
/* 00408108 */  lwc1       $f4, 0x24($sp)
/* 0040810c */  nop        
/* 00408110 */  swc1       $f4, 4($v1)
/* 00408114 */  lw         $ra, 0x14($sp)
/* 00408118 */  addiu      $sp, $sp, 0x20
/* 0040811c */  jr         $ra
/* 00408120 */  nop        
/* 00408124 */  addiu      $sp, $sp, -0x20
/* 00408128 */  sw         $ra, 0x14($sp)
/* 0040812c */  sw         $a0, 0x20($sp)
/* 00408130 */  sw         $a1, 0x24($sp)
/* 00408134 */  sw         $a2, 0x28($sp)
/* 00408138 */  sw         $a3, 0x2c($sp)
/* 0040813c */  jal        0xf801208                                # free
/* 00408140 */  addiu      $a0, $zero, 0x10
/* 00408144 */  bnez       $v0, 0x408164
/* 00408148 */  move       $v1, $v0
/* 0040814c */  lui        $a0, 0x1000
/* 00408150 */  addiu      $a0, $a0, 0x1e48
/* 00408154 */  jal        0x4092d4
/* 00408158 */  sw         $v1, 0x1c($sp)
/* 0040815c */  lw         $v1, 0x1c($sp)
/* 00408160 */  nop        
/* 00408164 */  lw         $t6, 0x20($sp)
/* 00408168 */  move       $v0, $v1
/* 0040816c */  sw         $t6, ($v1)
/* 00408170 */  lwc1       $f4, 0x24($sp)
/* 00408174 */  nop        
/* 00408178 */  swc1       $f4, 4($v1)
/* 0040817c */  lwc1       $f6, 0x28($sp)
/* 00408180 */  nop        
/* 00408184 */  swc1       $f6, 8($v1)
/* 00408188 */  lwc1       $f8, 0x2c($sp)
/* 0040818c */  nop        
/* 00408190 */  swc1       $f8, 0xc($v1)
/* 00408194 */  lw         $ra, 0x14($sp)
/* 00408198 */  addiu      $sp, $sp, 0x20
/* 0040819c */  jr         $ra
/* 004081a0 */  nop        
/* 004081a4 */  addiu      $sp, $sp, -0x20
/* 004081a8 */  sw         $s0, 0x18($sp)
/* 004081ac */  move       $s0, $a0
/* 004081b0 */  sw         $ra, 0x1c($sp)
/* 004081b4 */  jal        0x40a8e0
/* 004081b8 */  move       $a0, $s0
/* 004081bc */  beqz       $v0, 0x4081dc
/* 004081c0 */  move       $a0, $v0
/* 004081c4 */  jal        0xf801200                                # malloc
/* 004081c8 */  nop        
/* 004081cc */  jal        0x40a918
/* 004081d0 */  move       $a0, $s0
/* 004081d4 */  bnez       $v0, 0x4081c4
/* 004081d8 */  move       $a0, $v0
/* 004081dc */  jal        0x40a48c
/* 004081e0 */  move       $a0, $s0
/* 004081e4 */  lw         $ra, 0x1c($sp)
/* 004081e8 */  lw         $s0, 0x18($sp)
/* 004081ec */  jr         $ra
/* 004081f0 */  addiu      $sp, $sp, 0x20
/* 004081f4 */  nop        
/* 004081f8 */  nop        
/* 004081fc */  nop        
/* 00408200 */  addiu      $sp, $sp, -0x20
/* 00408204 */  sw         $ra, 0x14($sp)
/* 00408208 */  jal        0xf801208                                # free
/* 0040820c */  addiu      $a0, $zero, 0x28
/* 00408210 */  bnez       $v0, 0x408230
/* 00408214 */  move       $v1, $v0
/* 00408218 */  lui        $a0, 0x1000
/* 0040821c */  addiu      $a0, $a0, 0x1e60
/* 00408220 */  jal        0x4092d4
/* 00408224 */  sw         $v1, 0x1c($sp)
/* 00408228 */  lw         $v1, 0x1c($sp)
/* 0040822c */  nop        
/* 00408230 */  lui        $t7, 0x41
/* 00408234 */  lui        $t8, 0x41
/* 00408238 */  lui        $t9, 0x41
/* 0040823c */  lui        $t0, 0x41
/* 00408240 */  lui        $t1, 0x41
/* 00408244 */  addiu      $t6, $zero, -1
/* 00408248 */  addiu      $t7, $t7, -0x78b8
/* 0040824c */  addiu      $t8, $t8, -0x77c0
/* 00408250 */  addiu      $t9, $t9, -0x7660
/* 00408254 */  addiu      $t0, $t0, -0x7550
/* 00408258 */  addiu      $t1, $t1, -0x7410
/* 0040825c */  sw         $t6, ($v1)
/* 00408260 */  sw         $t7, 4($v1)
/* 00408264 */  sw         $t8, 8($v1)
/* 00408268 */  sw         $t9, 0xc($v1)
/* 0040826c */  sw         $t0, 0x10($v1)
/* 00408270 */  sw         $t1, 0x14($v1)
/* 00408274 */  lw         $t2, -0x7e98($gp)                        # view_state_ptr
/* 00408278 */  nop        
/* 0040827c */  lw         $t3, 0xb8($t2)
/* 00408280 */  nop        
/* 00408284 */  beqz       $t3, 0x40829c
/* 00408288 */  nop        
/* 0040828c */  lui        $t4, 0x41
/* 00408290 */  addiu      $t4, $t4, -0x6fd0
/* 00408294 */  b          0x4082a8
/* 00408298 */  sw         $t4, 0x18($v1)
/* 0040829c */  lui        $t5, 0x41
/* 004082a0 */  addiu      $t5, $t5, -0x709c
/* 004082a4 */  sw         $t5, 0x18($v1)
/* 004082a8 */  lui        $t6, 0x41
/* 004082ac */  lui        $t7, 0x41
/* 004082b0 */  lui        $t8, 0x41
/* 004082b4 */  addiu      $t6, $t6, -0x6f04
/* 004082b8 */  addiu      $t7, $t7, -0x726c
/* 004082bc */  addiu      $t8, $t8, -0x71cc
/* 004082c0 */  sw         $t6, 0x1c($v1)
/* 004082c4 */  sw         $t7, 0x20($v1)
/* 004082c8 */  sw         $t8, 0x24($v1)
/* 004082cc */  lw         $t9, -0x7e98($gp)                        # view_state_ptr
/* 004082d0 */  nop        
/* 004082d4 */  sw         $v1, 0xb4($t9)
/* 004082d8 */  lw         $ra, 0x14($sp)
/* 004082dc */  addiu      $sp, $sp, 0x20
/* 004082e0 */  jr         $ra
/* 004082e4 */  nop        
/* 004082e8 */  addiu      $sp, $sp, -0x18
/* 004082ec */  sw         $ra, 0x14($sp)
/* 004082f0 */  jal        0x408308
/* 004082f4 */  nop        
/* 004082f8 */  lw         $ra, 0x14($sp)
/* 004082fc */  addiu      $sp, $sp, 0x18
/* 00408300 */  jr         $ra
/* 00408304 */  nop        
/* 00408308 */  addiu      $sp, $sp, -0x38
/* 0040830c */  sw         $ra, 0x1c($sp)
/* 00408310 */  sw         $s5, 0x18($sp)
/* 00408314 */  move       $s5, $a0
/* 00408318 */  jal        0xf402230                                # pushmatrix
/* 0040831c */  sw         $s0, 0x14($sp)
/* 00408320 */  jal        0x40a8e0
/* 00408324 */  move       $a0, $s5
/* 00408328 */  beqz       $v0, 0x4083d4
/* 0040832c */  move       $s0, $v0
/* 00408330 */  sw         $s2, 0x28($sp)
/* 00408334 */  sw         $s3, 0x24($sp)
/* 00408338 */  sw         $s4, 0x20($sp)
/* 0040833c */  lui        $s4, 0x1000
/* 00408340 */  lui        $s3, 0x1000
/* 00408344 */  lui        $s2, 0x1000
/* 00408348 */  sw         $s1, 0x2c($sp)
/* 0040834c */  addiu      $s1, $zero, -1
/* 00408350 */  addiu      $s2, $s2, 0x36b4
/* 00408354 */  addiu      $s3, $s3, 0x1e78
/* 00408358 */  addiu      $s4, $s4, 0x1e8c
/* 0040835c */  lw         $v1, 0xc($v0)
/* 00408360 */  nop        
/* 00408364 */  beq        $s1, $v1, 0x408374
/* 00408368 */  sltiu      $at, $v1, 0xa
/* 0040836c */  bnez       $at, 0x40838c
/* 00408370 */  nop        
/* 00408374 */  move       $a0, $s2
/* 00408378 */  move       $a1, $s3
/* 0040837c */  jal        0xf801150                                # fclose
/* 00408380 */  move       $a2, $s4
/* 00408384 */  jal        0x40d3c0
/* 00408388 */  addiu      $a0, $zero, 1
/* 0040838c */  lw         $t6, -0x7e98($gp)                        # view_state_ptr
/* 00408390 */  lw         $t8, 0xc($s0)
/* 00408394 */  lw         $t7, 0xb4($t6)
/* 00408398 */  sll        $t9, $t8, 2
/* 0040839c */  addu       $t0, $t7, $t9
/* 004083a0 */  lw         $t1, ($t0)
/* 004083a4 */  lw         $a0, 8($s0)
/* 004083a8 */  jalr       $t1
/* 004083ac */  nop        
/* 004083b0 */  jal        0x40a918
/* 004083b4 */  move       $a0, $s5
/* 004083b8 */  bnez       $v0, 0x40835c
/* 004083bc */  move       $s0, $v0
/* 004083c0 */  lw         $s1, 0x2c($sp)
/* 004083c4 */  lw         $s2, 0x28($sp)
/* 004083c8 */  lw         $s3, 0x24($sp)
/* 004083cc */  lw         $s4, 0x20($sp)
/* 004083d0 */  nop        
/* 004083d4 */  jal        0xf402228                                # popmatrix
/* 004083d8 */  nop        
/* 004083dc */  lw         $ra, 0x1c($sp)
/* 004083e0 */  lw         $s0, 0x14($sp)
/* 004083e4 */  lw         $s5, 0x18($sp)
/* 004083e8 */  jr         $ra
/* 004083ec */  addiu      $sp, $sp, 0x38
/* 004083f0 */  addiu      $sp, $sp, -0x180
/* 004083f4 */  swc1       $f25, 0x20($sp)
/* 004083f8 */  swc1       $f24, 0x24($sp)
/* 004083fc */  sw         $ra, 0x2c($sp)
/* 00408400 */  swc1       $f23, 0x18($sp)
/* 00408404 */  swc1       $f22, 0x1c($sp)
/* 00408408 */  swc1       $f21, 0x10($sp)
/* 0040840c */  swc1       $f20, 0x14($sp)
/* 00408410 */  lw         $at, ($a0)
/* 00408414 */  lwc1       $f24, -0x7f74($gp)                       # .lit8 @ 0x10003dfc
/* 00408418 */  lwc1       $f25, -0x7f78($gp)                       # .lit8: 1
/* 0040841c */  lw         $t7, 4($a0)
/* 00408420 */  addiu      $t6, $sp, 0x84
/* 00408424 */  sw         $at, ($t6)
/* 00408428 */  lw         $at, 8($a0)
/* 0040842c */  sw         $t7, 4($t6)
/* 00408430 */  sw         $at, 8($t6)
/* 00408434 */  lwc1       $f4, 0x18($a0)
/* 00408438 */  lwc1       $f6, 0x84($sp)
/* 0040843c */  swc1       $f4, 0x74($sp)
/* 00408440 */  lwc1       $f20, 0x20($a0)
/* 00408444 */  cvt.d.s    $f12, $f6
/* 00408448 */  cvt.d.s    $f18, $f20
/* 0040844c */  sub.d      $f22, $f24, $f18
/* 00408450 */  lwc1       $f6, 0x88($sp)
/* 00408454 */  cvt.s.d    $f8, $f22
/* 00408458 */  cvt.d.s    $f0, $f8
/* 0040845c */  mul.d      $f10, $f12, $f0
/* 00408460 */  cvt.d.s    $f14, $f6
/* 00408464 */  mul.d      $f8, $f14, $f0
/* 00408468 */  cvt.s.d    $f4, $f10
/* 0040846c */  swc1       $f4, 0xa8($sp)
/* 00408470 */  lwc1       $f4, 0x8c($sp)
/* 00408474 */  cvt.s.d    $f10, $f8
/* 00408478 */  lwc1       $f11, -0x7f70($gp)                       # .lit8: 0.001
/* 0040847c */  cvt.d.s    $f16, $f4
/* 00408480 */  mul.d      $f6, $f16, $f0
/* 00408484 */  swc1       $f10, 0xac($sp)
/* 00408488 */  lwc1       $f10, -0x7f6c($gp)                       # .lit8 @ 0x10003e04
/* 0040848c */  nop        
/* 00408490 */  c.le.d     $f18, $f10
/* 00408494 */  cvt.s.d    $f8, $f6
/* 00408498 */  bc1t       0x408514
/* 0040849c */  swc1       $f8, 0xb0($sp)
/* 004084a0 */  add.d      $f6, $f12, $f14
/* 004084a4 */  lwc1       $f4, 0x74($sp)
/* 004084a8 */  add.d      $f8, $f6, $f16
/* 004084ac */  lwc1       $f11, -0x7f68($gp)                       # .lit8: 3
/* 004084b0 */  lwc1       $f10, -0x7f64($gp)                       # .lit8 @ 0x10003e0c
/* 004084b4 */  cvt.d.s    $f0, $f4
/* 004084b8 */  nop        
/* 004084bc */  div.d      $f4, $f8, $f10
/* 004084c0 */  sub.d      $f10, $f24, $f0
/* 004084c4 */  cvt.s.d    $f6, $f4
/* 004084c8 */  mul.d      $f4, $f0, $f12
/* 004084cc */  cvt.d.s    $f8, $f6
/* 004084d0 */  mul.d      $f2, $f10, $f8
/* 004084d4 */  add.d      $f6, $f4, $f2
/* 004084d8 */  mul.d      $f4, $f0, $f14
/* 004084dc */  mul.d      $f10, $f18, $f6
/* 004084e0 */  add.d      $f6, $f4, $f2
/* 004084e4 */  mul.d      $f4, $f0, $f16
/* 004084e8 */  cvt.s.d    $f8, $f10
/* 004084ec */  mtc1       $zero, $f0
/* 004084f0 */  swc1       $f8, 0x9c($sp)
/* 004084f4 */  mul.d      $f10, $f18, $f6
/* 004084f8 */  add.d      $f6, $f4, $f2
/* 004084fc */  cvt.s.d    $f8, $f10
/* 00408500 */  mul.d      $f10, $f18, $f6
/* 00408504 */  swc1       $f8, 0xa0($sp)
/* 00408508 */  cvt.s.d    $f8, $f10
/* 0040850c */  b          0x408528
/* 00408510 */  swc1       $f8, 0xa4($sp)
/* 00408514 */  mtc1       $zero, $f0
/* 00408518 */  nop        
/* 0040851c */  swc1       $f0, 0xa4($sp)
/* 00408520 */  swc1       $f0, 0xa0($sp)
/* 00408524 */  swc1       $f0, 0x9c($sp)
/* 00408528 */  lwc1       $f5, -0x7f60($gp)                        # .lit8: 0.992248
/* 0040852c */  lwc1       $f4, -0x7f5c($gp)                        # .lit8 @ 0x10003e14
/* 00408530 */  nop        
/* 00408534 */  c.le.d     $f18, $f4
/* 00408538 */  nop        
/* 0040853c */  bc1t       0x408554
/* 00408540 */  nop        
/* 00408544 */  lwc1       $f20, -0x7ebc($gp)                       # .lit4: 0.992248
/* 00408548 */  nop        
/* 0040854c */  cvt.d.s    $f6, $f20
/* 00408550 */  sub.d      $f22, $f24, $f6
/* 00408554 */  lwc1       $f4, 0xa8($sp)
/* 00408558 */  swc1       $f0, 0xbc($sp)
/* 0040855c */  swc1       $f4, 0xcc($sp)
/* 00408560 */  lwc1       $f4, 0x9c($sp)
/* 00408564 */  swc1       $f0, 0xc0($sp)
/* 00408568 */  swc1       $f4, 0xdc($sp)
/* 0040856c */  div.d      $f4, $f24, $f22
/* 00408570 */  swc1       $f0, 0xc4($sp)
/* 00408574 */  swc1       $f0, 0xf0($sp)
/* 00408578 */  lwc1       $f10, -0x7eb8($gp)                       # .lit4: 2
/* 0040857c */  lwc1       $f6, 0xac($sp)
/* 00408580 */  swc1       $f10, 0xb8($sp)
/* 00408584 */  swc1       $f6, 0xd0($sp)
/* 00408588 */  lwc1       $f8, -0x7eb4($gp)                        # .lit4: 3
/* 0040858c */  lwc1       $f10, 0xb0($sp)
/* 00408590 */  swc1       $f8, 0xc8($sp)
/* 00408594 */  lwc1       $f6, 0xa0($sp)
/* 00408598 */  lwc1       $f8, -0x7eb0($gp)                        # .lit4: 4
/* 0040859c */  swc1       $f10, 0xd4($sp)
/* 004085a0 */  lwc1       $f10, 0xa4($sp)
/* 004085a4 */  swc1       $f6, 0xe0($sp)
/* 004085a8 */  swc1       $f8, 0xd8($sp)
/* 004085ac */  lwc1       $f8, -0x7eac($gp)                        # .lit4: 5
/* 004085b0 */  swc1       $f10, 0xe4($sp)
/* 004085b4 */  swc1       $f8, 0xe8($sp)
/* 004085b8 */  sub.d      $f6, $f4, $f24
/* 004085bc */  move       $a0, $zero
/* 004085c0 */  cvt.s.d    $f10, $f6
/* 004085c4 */  addiu      $a1, $zero, 1
/* 004085c8 */  swc1       $f10, 0xec($sp)
/* 004085cc */  addiu      $a2, $zero, 0xf
/* 004085d0 */  jal        0xf4015d0                                # lmdef
/* 004085d4 */  addiu      $a3, $sp, 0xb8
/* 004085d8 */  addiu      $a0, $zero, 0x3e8
/* 004085dc */  jal        0xf402570                                # lsetdepth
/* 004085e0 */  addiu      $a1, $zero, 1
/* 004085e4 */  lw         $ra, 0x2c($sp)
/* 004085e8 */  lwc1       $f21, 0x10($sp)
/* 004085ec */  lwc1       $f20, 0x14($sp)
/* 004085f0 */  lwc1       $f23, 0x18($sp)
/* 004085f4 */  lwc1       $f22, 0x1c($sp)
/* 004085f8 */  lwc1       $f25, 0x20($sp)
/* 004085fc */  lwc1       $f24, 0x24($sp)
/* 00408600 */  jr         $ra
/* 00408604 */  addiu      $sp, $sp, 0x180
/* 00408608 */  addiu      $sp, $sp, -0x18
/* 0040860c */  sw         $ra, 0x14($sp)
/* 00408610 */  lwc1       $f4, 4($a0)
/* 00408614 */  mtc1       $zero, $f0
/* 00408618 */  mtc1       $zero, $f1
/* 0040861c */  cvt.d.s    $f6, $f4
/* 00408620 */  c.eq.d     $f0, $f6
/* 00408624 */  move       $v0, $zero
/* 00408628 */  bc1t       0x408634
/* 0040862c */  nop        
/* 00408630 */  addiu      $v0, $zero, 1
/* 00408634 */  lwc1       $f8, 8($a0)
/* 00408638 */  nop        
/* 0040863c */  cvt.d.s    $f10, $f8
/* 00408640 */  c.eq.d     $f0, $f10
/* 00408644 */  nop        
/* 00408648 */  bc1t       0x408654
/* 0040864c */  nop        
/* 00408650 */  ori        $v0, $v0, 2
/* 00408654 */  lwc1       $f16, 0xc($a0)
/* 00408658 */  nop        
/* 0040865c */  cvt.d.s    $f18, $f16
/* 00408660 */  c.eq.d     $f0, $f18
/* 00408664 */  nop        
/* 00408668 */  bc1t       0x408678
/* 0040866c */  addiu      $at, $zero, 1
/* 00408670 */  ori        $v0, $v0, 4
/* 00408674 */  addiu      $at, $zero, 1
/* 00408678 */  beq        $v0, $at, 0x408698
/* 0040867c */  addiu      $at, $zero, 2
/* 00408680 */  beq        $v0, $at, 0x4086ac
/* 00408684 */  addiu      $at, $zero, 4
/* 00408688 */  beq        $v0, $at, 0x4086c0
/* 0040868c */  nop        
/* 00408690 */  b          0x4086d4
/* 00408694 */  nop        
/* 00408698 */  lwc1       $f12, ($a0)
/* 0040869c */  jal        0xf402558                                # rot
/* 004086a0 */  addiu      $a1, $zero, 0x78
/* 004086a4 */  b          0x4086e4
/* 004086a8 */  lw         $ra, 0x14($sp)
/* 004086ac */  lwc1       $f12, ($a0)
/* 004086b0 */  jal        0xf402558                                # rot
/* 004086b4 */  addiu      $a1, $zero, 0x79
/* 004086b8 */  b          0x4086e4
/* 004086bc */  lw         $ra, 0x14($sp)
/* 004086c0 */  lwc1       $f12, ($a0)
/* 004086c4 */  jal        0xf402558                                # rot
/* 004086c8 */  addiu      $a1, $zero, 0x7a
/* 004086cc */  b          0x4086e4
/* 004086d0 */  lw         $ra, 0x14($sp)
/* 004086d4 */  lui        $a0, 0x1000
/* 004086d8 */  jal        0x4092d4
/* 004086dc */  addiu      $a0, $a0, 0x1ea8
/* 004086e0 */  lw         $ra, 0x14($sp)
/* 004086e4 */  addiu      $sp, $sp, 0x18
/* 004086e8 */  jr         $ra
/* 004086ec */  nop        
/* 004086f0 */  addiu      $sp, $sp, -0x18
/* 004086f4 */  sw         $ra, 0x14($sp)
/* 004086f8 */  lw         $a2, 8($a0)
/* 004086fc */  lwc1       $f14, 4($a0)
/* 00408700 */  lwc1       $f12, ($a0)
/* 00408704 */  jal        0xf402278                                # scale
/* 00408708 */  nop        
/* 0040870c */  lw         $ra, 0x14($sp)
/* 00408710 */  addiu      $sp, $sp, 0x18
/* 00408714 */  jr         $ra
/* 00408718 */  nop        
/* 0040871c */  addiu      $sp, $sp, -0x18
/* 00408720 */  sw         $ra, 0x14($sp)
/* 00408724 */  lw         $a2, 8($a0)
/* 00408728 */  lwc1       $f14, 4($a0)
/* 0040872c */  lwc1       $f12, ($a0)
/* 00408730 */  jal        0xf402298                                # translate
/* 00408734 */  nop        
/* 00408738 */  lw         $ra, 0x14($sp)
/* 0040873c */  addiu      $sp, $sp, 0x18
/* 00408740 */  jr         $ra
/* 00408744 */  nop        
/* 00408748 */  addiu      $sp, $sp, -0x38
/* 0040874c */  sw         $s0, 0x14($sp)
/* 00408750 */  move       $s0, $a0
/* 00408754 */  sw         $ra, 0x1c($sp)
/* 00408758 */  sw         $s2, 0x18($sp)
/* 0040875c */  jal        0x4034b8                                 # bind_material
/* 00408760 */  move       $a0, $zero
/* 00408764 */  beqz       $s0, 0x40882c
/* 00408768 */  move       $s2, $s0
/* 0040876c */  sw         $s3, 0x24($sp)
/* 00408770 */  addiu      $s3, $zero, 4
/* 00408774 */  sw         $s1, 0x28($sp)
/* 00408778 */  lw         $t6, 8($s2)
/* 0040877c */  lw         $s1, 4($s2)
/* 00408780 */  bne        $s3, $t6, 0x4087d0
/* 00408784 */  nop        
/* 00408788 */  jal        0xf4020d8                                # endpolygon
/* 0040878c */  nop        
/* 00408790 */  lw         $a0, ($s1)
/* 00408794 */  jal        0xf402030                                # bgnpolygon
/* 00408798 */  nop        
/* 0040879c */  lw         $a0, 4($s1)
/* 004087a0 */  jal        0xf402030                                # bgnpolygon
/* 004087a4 */  addiu      $s1, $s1, 4
/* 004087a8 */  lw         $a0, 4($s1)
/* 004087ac */  jal        0xf402030                                # bgnpolygon
/* 004087b0 */  addiu      $s1, $s1, 4
/* 004087b4 */  lw         $a0, 4($s1)
/* 004087b8 */  jal        0xf402030                                # bgnpolygon
/* 004087bc */  addiu      $s1, $s1, 4
/* 004087c0 */  jal        0xf402078                                # n3f
/* 004087c4 */  nop        
/* 004087c8 */  b          0x408814
/* 004087cc */  lw         $s2, ($s2)
/* 004087d0 */  jal        0xf4020d8                                # endpolygon
/* 004087d4 */  move       $s0, $zero
/* 004087d8 */  lw         $t7, 8($s2)
/* 004087dc */  nop        
/* 004087e0 */  blez       $t7, 0x408808
/* 004087e4 */  nop        
/* 004087e8 */  lw         $a0, ($s1)
/* 004087ec */  jal        0xf402030                                # bgnpolygon
/* 004087f0 */  nop        
/* 004087f4 */  lw         $t8, 8($s2)
/* 004087f8 */  addiu      $s0, $s0, 1
/* 004087fc */  slt        $at, $s0, $t8
/* 00408800 */  bnez       $at, 0x4087e8
/* 00408804 */  addiu      $s1, $s1, 4
/* 00408808 */  jal        0xf402078                                # n3f
/* 0040880c */  nop        
/* 00408810 */  lw         $s2, ($s2)
/* 00408814 */  nop        
/* 00408818 */  bnez       $s2, 0x408778
/* 0040881c */  nop        
/* 00408820 */  lw         $s1, 0x28($sp)
/* 00408824 */  lw         $s3, 0x24($sp)
/* 00408828 */  nop        
/* 0040882c */  lw         $ra, 0x1c($sp)
/* 00408830 */  lw         $s0, 0x14($sp)
/* 00408834 */  lw         $s2, 0x18($sp)
/* 00408838 */  jr         $ra
/* 0040883c */  addiu      $sp, $sp, 0x38
/* 00408840 */  addiu      $sp, $sp, -0x38
/* 00408844 */  sw         $s0, 0x14($sp)
/* 00408848 */  move       $s0, $a0
/* 0040884c */  sw         $ra, 0x1c($sp)
/* 00408850 */  sw         $s2, 0x18($sp)
/* 00408854 */  jal        0x4034b8                                 # bind_material
/* 00408858 */  move       $a0, $zero
/* 0040885c */  beqz       $s0, 0x40898c
/* 00408860 */  move       $s2, $s0
/* 00408864 */  sw         $s3, 0x24($sp)
/* 00408868 */  addiu      $s3, $zero, 0x10
/* 0040886c */  sw         $s1, 0x28($sp)
/* 00408870 */  lw         $t6, 8($s2)
/* 00408874 */  lw         $s0, 4($s2)
/* 00408878 */  bne        $s3, $t6, 0x4088e8
/* 0040887c */  nop        
/* 00408880 */  jal        0xf4020d8                                # endpolygon
/* 00408884 */  nop        
/* 00408888 */  lw         $a0, ($s0)
/* 0040888c */  jal        0xf402098                                # color
/* 00408890 */  nop        
/* 00408894 */  jal        0xf402030                                # bgnpolygon
/* 00408898 */  addiu      $a0, $s0, 4
/* 0040889c */  lw         $a0, 0x10($s0)
/* 004088a0 */  jal        0xf402098                                # color
/* 004088a4 */  nop        
/* 004088a8 */  jal        0xf402030                                # bgnpolygon
/* 004088ac */  addiu      $a0, $s0, 0x14
/* 004088b0 */  lw         $a0, 0x20($s0)
/* 004088b4 */  jal        0xf402098                                # color
/* 004088b8 */  nop        
/* 004088bc */  jal        0xf402030                                # bgnpolygon
/* 004088c0 */  addiu      $a0, $s0, 0x24
/* 004088c4 */  lw         $a0, 0x30($s0)
/* 004088c8 */  jal        0xf402098                                # color
/* 004088cc */  nop        
/* 004088d0 */  jal        0xf402030                                # bgnpolygon
/* 004088d4 */  addiu      $a0, $s0, 0x34
/* 004088d8 */  jal        0xf402078                                # n3f
/* 004088dc */  nop        
/* 004088e0 */  b          0x408974
/* 004088e4 */  lw         $s2, ($s2)
/* 004088e8 */  jal        0xf4020d8                                # endpolygon
/* 004088ec */  addiu      $s1, $zero, 0xc
/* 004088f0 */  lw         $a0, ($s0)
/* 004088f4 */  jal        0xf402098                                # color
/* 004088f8 */  nop        
/* 004088fc */  jal        0xf402030                                # bgnpolygon
/* 00408900 */  addiu      $a0, $s0, 4
/* 00408904 */  lw         $a0, 0x10($s0)
/* 00408908 */  jal        0xf402098                                # color
/* 0040890c */  nop        
/* 00408910 */  jal        0xf402030                                # bgnpolygon
/* 00408914 */  addiu      $a0, $s0, 0x14
/* 00408918 */  lw         $a0, 0x20($s0)
/* 0040891c */  jal        0xf402098                                # color
/* 00408920 */  nop        
/* 00408924 */  jal        0xf402030                                # bgnpolygon
/* 00408928 */  addiu      $a0, $s0, 0x24
/* 0040892c */  lw         $t7, 8($s2)
/* 00408930 */  addiu      $s0, $s0, 0x30
/* 00408934 */  slti       $at, $t7, 0xd
/* 00408938 */  bnez       $at, 0x408968
/* 0040893c */  nop        
/* 00408940 */  lw         $a0, ($s0)
/* 00408944 */  jal        0xf402098                                # color
/* 00408948 */  nop        
/* 0040894c */  jal        0xf402030                                # bgnpolygon
/* 00408950 */  addiu      $a0, $s0, 4
/* 00408954 */  lw         $t8, 8($s2)
/* 00408958 */  addiu      $s1, $s1, 4
/* 0040895c */  slt        $at, $s1, $t8
/* 00408960 */  bnez       $at, 0x408940
/* 00408964 */  addiu      $s0, $s0, 0x10
/* 00408968 */  jal        0xf402078                                # n3f
/* 0040896c */  nop        
/* 00408970 */  lw         $s2, ($s2)
/* 00408974 */  nop        
/* 00408978 */  bnez       $s2, 0x408870
/* 0040897c */  nop        
/* 00408980 */  lw         $s1, 0x28($sp)
/* 00408984 */  lw         $s3, 0x24($sp)
/* 00408988 */  nop        
/* 0040898c */  lw         $ra, 0x1c($sp)
/* 00408990 */  lw         $s0, 0x14($sp)
/* 00408994 */  lw         $s2, 0x18($sp)
/* 00408998 */  jr         $ra
/* 0040899c */  addiu      $sp, $sp, 0x38
/* 004089a0 */  addiu      $sp, $sp, -0x38
/* 004089a4 */  sw         $s0, 0x14($sp)
/* 004089a8 */  move       $s0, $a0
/* 004089ac */  sw         $ra, 0x1c($sp)
/* 004089b0 */  sw         $s2, 0x18($sp)
/* 004089b4 */  jal        0x4034b8                                 # bind_material
/* 004089b8 */  move       $a0, $zero
/* 004089bc */  beqz       $s0, 0x408a9c
/* 004089c0 */  move       $s2, $s0
/* 004089c4 */  sw         $s3, 0x24($sp)
/* 004089c8 */  addiu      $s3, $zero, 0xd
/* 004089cc */  sw         $s1, 0x28($sp)
/* 004089d0 */  lw         $t6, 8($s2)
/* 004089d4 */  lw         $s1, 4($s2)
/* 004089d8 */  bne        $s3, $t6, 0x408a34
/* 004089dc */  nop        
/* 004089e0 */  jal        0xf4020d8                                # endpolygon
/* 004089e4 */  nop        
/* 004089e8 */  lw         $a0, ($s1)
/* 004089ec */  jal        0xf402098                                # color
/* 004089f0 */  nop        
/* 004089f4 */  addiu      $s1, $s1, 4
/* 004089f8 */  jal        0xf402030                                # bgnpolygon
/* 004089fc */  move       $a0, $s1
/* 00408a00 */  addiu      $s1, $s1, 0xc
/* 00408a04 */  jal        0xf402030                                # bgnpolygon
/* 00408a08 */  move       $a0, $s1
/* 00408a0c */  addiu      $s1, $s1, 0xc
/* 00408a10 */  jal        0xf402030                                # bgnpolygon
/* 00408a14 */  move       $a0, $s1
/* 00408a18 */  addiu      $s1, $s1, 0xc
/* 00408a1c */  jal        0xf402030                                # bgnpolygon
/* 00408a20 */  move       $a0, $s1
/* 00408a24 */  jal        0xf402078                                # n3f
/* 00408a28 */  nop        
/* 00408a2c */  b          0x408a84
/* 00408a30 */  lw         $s2, ($s2)
/* 00408a34 */  jal        0xf4020d8                                # endpolygon
/* 00408a38 */  addiu      $s0, $zero, 1
/* 00408a3c */  lw         $a0, ($s1)
/* 00408a40 */  jal        0xf402098                                # color
/* 00408a44 */  nop        
/* 00408a48 */  lw         $t7, 8($s2)
/* 00408a4c */  addiu      $s1, $s1, 4
/* 00408a50 */  slti       $at, $t7, 2
/* 00408a54 */  bnez       $at, 0x408a78
/* 00408a58 */  nop        
/* 00408a5c */  jal        0xf402030                                # bgnpolygon
/* 00408a60 */  move       $a0, $s1
/* 00408a64 */  lw         $t8, 8($s2)
/* 00408a68 */  addiu      $s0, $s0, 3
/* 00408a6c */  slt        $at, $s0, $t8
/* 00408a70 */  bnez       $at, 0x408a5c
/* 00408a74 */  addiu      $s1, $s1, 0xc
/* 00408a78 */  jal        0xf402078                                # n3f
/* 00408a7c */  nop        
/* 00408a80 */  lw         $s2, ($s2)
/* 00408a84 */  nop        
/* 00408a88 */  bnez       $s2, 0x4089d0
/* 00408a8c */  nop        
/* 00408a90 */  lw         $s1, 0x28($sp)
/* 00408a94 */  lw         $s3, 0x24($sp)
/* 00408a98 */  nop        
/* 00408a9c */  lw         $ra, 0x1c($sp)
/* 00408aa0 */  lw         $s0, 0x14($sp)
/* 00408aa4 */  lw         $s2, 0x18($sp)
/* 00408aa8 */  jr         $ra
/* 00408aac */  addiu      $sp, $sp, 0x38
/* 00408ab0 */  addiu      $sp, $sp, -0x38
/* 00408ab4 */  sw         $s0, 0x14($sp)
/* 00408ab8 */  move       $s0, $a0
/* 00408abc */  sw         $ra, 0x1c($sp)
/* 00408ac0 */  sw         $s2, 0x18($sp)
/* 00408ac4 */  jal        0x4034b8                                 # bind_material
/* 00408ac8 */  addiu      $a0, $zero, 1
/* 00408acc */  beqz       $s0, 0x408bdc
/* 00408ad0 */  move       $s2, $s0
/* 00408ad4 */  sw         $s3, 0x24($sp)
/* 00408ad8 */  addiu      $s3, $zero, 0x18
/* 00408adc */  sw         $s1, 0x28($sp)
/* 00408ae0 */  lw         $t6, 8($s2)
/* 00408ae4 */  lw         $s0, 4($s2)
/* 00408ae8 */  bne        $s3, $t6, 0x408b48
/* 00408aec */  nop        
/* 00408af0 */  jal        0xf4020d8                                # endpolygon
/* 00408af4 */  nop        
/* 00408af8 */  jal        0xf402068                                # v3f
/* 00408afc */  move       $a0, $s0
/* 00408b00 */  jal        0xf402030                                # bgnpolygon
/* 00408b04 */  addiu      $a0, $s0, 0xc
/* 00408b08 */  jal        0xf402068                                # v3f
/* 00408b0c */  addiu      $a0, $s0, 0x18
/* 00408b10 */  jal        0xf402030                                # bgnpolygon
/* 00408b14 */  addiu      $a0, $s0, 0x24
/* 00408b18 */  jal        0xf402068                                # v3f
/* 00408b1c */  addiu      $a0, $s0, 0x30
/* 00408b20 */  jal        0xf402030                                # bgnpolygon
/* 00408b24 */  addiu      $a0, $s0, 0x3c
/* 00408b28 */  jal        0xf402068                                # v3f
/* 00408b2c */  addiu      $a0, $s0, 0x48
/* 00408b30 */  jal        0xf402030                                # bgnpolygon
/* 00408b34 */  addiu      $a0, $s0, 0x54
/* 00408b38 */  jal        0xf402078                                # n3f
/* 00408b3c */  nop        
/* 00408b40 */  b          0x408bc4
/* 00408b44 */  lw         $s2, ($s2)
/* 00408b48 */  jal        0xf4020d8                                # endpolygon
/* 00408b4c */  addiu      $s1, $zero, 0x12
/* 00408b50 */  jal        0xf402068                                # v3f
/* 00408b54 */  move       $a0, $s0
/* 00408b58 */  jal        0xf402030                                # bgnpolygon
/* 00408b5c */  addiu      $a0, $s0, 0xc
/* 00408b60 */  jal        0xf402068                                # v3f
/* 00408b64 */  addiu      $a0, $s0, 0x18
/* 00408b68 */  jal        0xf402030                                # bgnpolygon
/* 00408b6c */  addiu      $a0, $s0, 0x24
/* 00408b70 */  jal        0xf402068                                # v3f
/* 00408b74 */  addiu      $a0, $s0, 0x30
/* 00408b78 */  jal        0xf402030                                # bgnpolygon
/* 00408b7c */  addiu      $a0, $s0, 0x3c
/* 00408b80 */  lw         $t7, 8($s2)
/* 00408b84 */  addiu      $s0, $s0, 0x48
/* 00408b88 */  slti       $at, $t7, 0x13
/* 00408b8c */  bnez       $at, 0x408bb8
/* 00408b90 */  nop        
/* 00408b94 */  jal        0xf402068                                # v3f
/* 00408b98 */  move       $a0, $s0
/* 00408b9c */  jal        0xf402030                                # bgnpolygon
/* 00408ba0 */  addiu      $a0, $s0, 0xc
/* 00408ba4 */  lw         $t8, 8($s2)
/* 00408ba8 */  addiu      $s1, $s1, 6
/* 00408bac */  slt        $at, $s1, $t8
/* 00408bb0 */  bnez       $at, 0x408b94
/* 00408bb4 */  addiu      $s0, $s0, 0x18
/* 00408bb8 */  jal        0xf402078                                # n3f
/* 00408bbc */  nop        
/* 00408bc0 */  lw         $s2, ($s2)
/* 00408bc4 */  nop        
/* 00408bc8 */  bnez       $s2, 0x408ae0
/* 00408bcc */  nop        
/* 00408bd0 */  lw         $s1, 0x28($sp)
/* 00408bd4 */  lw         $s3, 0x24($sp)
/* 00408bd8 */  nop        
/* 00408bdc */  lw         $ra, 0x1c($sp)
/* 00408be0 */  lw         $s0, 0x14($sp)
/* 00408be4 */  lw         $s2, 0x18($sp)
/* 00408be8 */  jr         $ra
/* 00408bec */  addiu      $sp, $sp, 0x38
/* 00408bf0 */  addiu      $sp, $sp, -0x38
/* 00408bf4 */  sw         $s0, 0x14($sp)
/* 00408bf8 */  move       $s0, $a0
/* 00408bfc */  sw         $ra, 0x1c($sp)
/* 00408c00 */  sw         $s2, 0x18($sp)
/* 00408c04 */  jal        0x4034b8                                 # bind_material
/* 00408c08 */  addiu      $a0, $zero, 1
/* 00408c0c */  beqz       $s0, 0x408cec
/* 00408c10 */  move       $s2, $s0
/* 00408c14 */  sw         $s3, 0x24($sp)
/* 00408c18 */  addiu      $s3, $zero, 0xf
/* 00408c1c */  sw         $s1, 0x28($sp)
/* 00408c20 */  lw         $t6, 8($s2)
/* 00408c24 */  lw         $s1, 4($s2)
/* 00408c28 */  bne        $s3, $t6, 0x408c70
/* 00408c2c */  nop        
/* 00408c30 */  jal        0xf4020d8                                # endpolygon
/* 00408c34 */  nop        
/* 00408c38 */  jal        0xf402068                                # v3f
/* 00408c3c */  move       $a0, $s1
/* 00408c40 */  jal        0xf402030                                # bgnpolygon
/* 00408c44 */  addiu      $a0, $s1, 0xc
/* 00408c48 */  jal        0xf402030                                # bgnpolygon
/* 00408c4c */  addiu      $a0, $s1, 0x18
/* 00408c50 */  jal        0xf402030                                # bgnpolygon
/* 00408c54 */  addiu      $a0, $s1, 0x24
/* 00408c58 */  jal        0xf402030                                # bgnpolygon
/* 00408c5c */  addiu      $a0, $s1, 0x30
/* 00408c60 */  jal        0xf402078                                # n3f
/* 00408c64 */  nop        
/* 00408c68 */  b          0x408cd4
/* 00408c6c */  lw         $s2, ($s2)
/* 00408c70 */  jal        0xf4020d8                                # endpolygon
/* 00408c74 */  addiu      $s0, $zero, 0xc
/* 00408c78 */  jal        0xf402068                                # v3f
/* 00408c7c */  move       $a0, $s1
/* 00408c80 */  jal        0xf402030                                # bgnpolygon
/* 00408c84 */  addiu      $a0, $s1, 0xc
/* 00408c88 */  jal        0xf402030                                # bgnpolygon
/* 00408c8c */  addiu      $a0, $s1, 0x18
/* 00408c90 */  jal        0xf402030                                # bgnpolygon
/* 00408c94 */  addiu      $a0, $s1, 0x24
/* 00408c98 */  lw         $t7, 8($s2)
/* 00408c9c */  addiu      $s1, $s1, 0x30
/* 00408ca0 */  slti       $at, $t7, 0xd
/* 00408ca4 */  bnez       $at, 0x408cc8
/* 00408ca8 */  nop        
/* 00408cac */  jal        0xf402030                                # bgnpolygon
/* 00408cb0 */  move       $a0, $s1
/* 00408cb4 */  lw         $t8, 8($s2)
/* 00408cb8 */  addiu      $s0, $s0, 3
/* 00408cbc */  slt        $at, $s0, $t8
/* 00408cc0 */  bnez       $at, 0x408cac
/* 00408cc4 */  addiu      $s1, $s1, 0xc
/* 00408cc8 */  jal        0xf402078                                # n3f
/* 00408ccc */  nop        
/* 00408cd0 */  lw         $s2, ($s2)
/* 00408cd4 */  nop        
/* 00408cd8 */  bnez       $s2, 0x408c20
/* 00408cdc */  nop        
/* 00408ce0 */  lw         $s1, 0x28($sp)
/* 00408ce4 */  lw         $s3, 0x24($sp)
/* 00408ce8 */  nop        
/* 00408cec */  lw         $ra, 0x1c($sp)
/* 00408cf0 */  lw         $s0, 0x14($sp)
/* 00408cf4 */  lw         $s2, 0x18($sp)
/* 00408cf8 */  jr         $ra
/* 00408cfc */  addiu      $sp, $sp, 0x38
/* 00408d00 */  addiu      $sp, $sp, -0x30
/* 00408d04 */  sw         $s0, 0x14($sp)
/* 00408d08 */  move       $s0, $a0
/* 00408d0c */  sw         $ra, 0x1c($sp)
/* 00408d10 */  sw         $s2, 0x18($sp)
/* 00408d14 */  jal        0x4034b8                                 # bind_material
/* 00408d18 */  move       $a0, $zero
/* 00408d1c */  beqz       $s0, 0x408d80
/* 00408d20 */  move       $s2, $s0
/* 00408d24 */  sw         $s1, 0x20($sp)
/* 00408d28 */  lw         $s0, 4($s2)
/* 00408d2c */  jal        0xf4020e0                                # bgnclosedline
/* 00408d30 */  move       $s1, $zero
/* 00408d34 */  lw         $t6, 8($s2)
/* 00408d38 */  nop        
/* 00408d3c */  blez       $t6, 0x408d60
/* 00408d40 */  nop        
/* 00408d44 */  jal        0xf402030                                # bgnpolygon
/* 00408d48 */  move       $a0, $s0
/* 00408d4c */  lw         $t7, 8($s2)
/* 00408d50 */  addiu      $s1, $s1, 3
/* 00408d54 */  slt        $at, $s1, $t7
/* 00408d58 */  bnez       $at, 0x408d44
/* 00408d5c */  addiu      $s0, $s0, 0xc
/* 00408d60 */  jal        0xf402080                                # c3f
/* 00408d64 */  nop        
/* 00408d68 */  lw         $s2, ($s2)
/* 00408d6c */  nop        
/* 00408d70 */  bnez       $s2, 0x408d28
/* 00408d74 */  nop        
/* 00408d78 */  lw         $s1, 0x20($sp)
/* 00408d7c */  nop        
/* 00408d80 */  lw         $ra, 0x1c($sp)
/* 00408d84 */  lw         $s0, 0x14($sp)
/* 00408d88 */  lw         $s2, 0x18($sp)
/* 00408d8c */  jr         $ra
/* 00408d90 */  addiu      $sp, $sp, 0x30
/* 00408d94 */  addiu      $sp, $sp, -0x30
/* 00408d98 */  sw         $s0, 0x14($sp)
/* 00408d9c */  move       $s0, $a0
/* 00408da0 */  sw         $ra, 0x1c($sp)
/* 00408da4 */  sw         $s2, 0x18($sp)
/* 00408da8 */  jal        0x4034b8                                 # bind_material
/* 00408dac */  move       $a0, $zero
/* 00408db0 */  beqz       $s0, 0x408e20
/* 00408db4 */  move       $s2, $s0
/* 00408db8 */  sw         $s1, 0x20($sp)
/* 00408dbc */  lw         $s0, 4($s2)
/* 00408dc0 */  jal        0xf4020e0                                # bgnclosedline
/* 00408dc4 */  move       $s1, $zero
/* 00408dc8 */  lw         $t6, 8($s2)
/* 00408dcc */  nop        
/* 00408dd0 */  blez       $t6, 0x408e00
/* 00408dd4 */  nop        
/* 00408dd8 */  lw         $a0, ($s0)
/* 00408ddc */  jal        0xf402098                                # color
/* 00408de0 */  nop        
/* 00408de4 */  jal        0xf402030                                # bgnpolygon
/* 00408de8 */  addiu      $a0, $s0, 4
/* 00408dec */  lw         $t7, 8($s2)
/* 00408df0 */  addiu      $s1, $s1, 4
/* 00408df4 */  slt        $at, $s1, $t7
/* 00408df8 */  bnez       $at, 0x408dd8
/* 00408dfc */  addiu      $s0, $s0, 0x10
/* 00408e00 */  jal        0xf402080                                # c3f
/* 00408e04 */  nop        
/* 00408e08 */  lw         $s2, ($s2)
/* 00408e0c */  nop        
/* 00408e10 */  bnez       $s2, 0x408dbc
/* 00408e14 */  nop        
/* 00408e18 */  lw         $s1, 0x20($sp)
/* 00408e1c */  nop        
/* 00408e20 */  lw         $ra, 0x1c($sp)
/* 00408e24 */  lw         $s0, 0x14($sp)
/* 00408e28 */  lw         $s2, 0x18($sp)
/* 00408e2c */  jr         $ra
/* 00408e30 */  addiu      $sp, $sp, 0x30
/* 00408e34 */  addiu      $sp, $sp, -0x30
/* 00408e38 */  sw         $s0, 0x14($sp)
/* 00408e3c */  move       $s0, $a0
/* 00408e40 */  sw         $ra, 0x1c($sp)
/* 00408e44 */  sw         $s2, 0x18($sp)
/* 00408e48 */  jal        0x4034b8                                 # bind_material
/* 00408e4c */  addiu      $a0, $zero, 1
/* 00408e50 */  beqz       $s0, 0x408ebc
/* 00408e54 */  move       $s2, $s0
/* 00408e58 */  sw         $s1, 0x20($sp)
/* 00408e5c */  lw         $s0, 4($s2)
/* 00408e60 */  jal        0xf4020e0                                # bgnclosedline
/* 00408e64 */  move       $s1, $zero
/* 00408e68 */  lw         $t6, 8($s2)
/* 00408e6c */  nop        
/* 00408e70 */  blez       $t6, 0x408e9c
/* 00408e74 */  nop        
/* 00408e78 */  jal        0xf402068                                # v3f
/* 00408e7c */  move       $a0, $s0
/* 00408e80 */  jal        0xf402030                                # bgnpolygon
/* 00408e84 */  addiu      $a0, $s0, 0xc
/* 00408e88 */  lw         $t7, 8($s2)
/* 00408e8c */  addiu      $s1, $s1, 6
/* 00408e90 */  slt        $at, $s1, $t7
/* 00408e94 */  bnez       $at, 0x408e78
/* 00408e98 */  addiu      $s0, $s0, 0x18
/* 00408e9c */  jal        0xf402080                                # c3f
/* 00408ea0 */  nop        
/* 00408ea4 */  lw         $s2, ($s2)
/* 00408ea8 */  nop        
/* 00408eac */  bnez       $s2, 0x408e5c
/* 00408eb0 */  nop        
/* 00408eb4 */  lw         $s1, 0x20($sp)
/* 00408eb8 */  nop        
/* 00408ebc */  lw         $ra, 0x1c($sp)
/* 00408ec0 */  lw         $s0, 0x14($sp)
/* 00408ec4 */  lw         $s2, 0x18($sp)
/* 00408ec8 */  jr         $ra
/* 00408ecc */  addiu      $sp, $sp, 0x30
/* 00408ed0 */  addiu      $sp, $sp, -0x30
/* 00408ed4 */  sw         $s0, 0x14($sp)
/* 00408ed8 */  move       $s0, $a0
/* 00408edc */  sw         $ra, 0x1c($sp)
/* 00408ee0 */  sw         $s2, 0x18($sp)
/* 00408ee4 */  jal        0x4034b8                                 # bind_material
/* 00408ee8 */  move       $a0, $zero
/* 00408eec */  beqz       $s0, 0x408f50
/* 00408ef0 */  move       $s2, $s0
/* 00408ef4 */  sw         $s1, 0x20($sp)
/* 00408ef8 */  lw         $s0, 4($s2)
/* 00408efc */  jal        0xf4020e8                                # endclosedline
/* 00408f00 */  move       $s1, $zero
/* 00408f04 */  lw         $t6, 8($s2)
/* 00408f08 */  nop        
/* 00408f0c */  blez       $t6, 0x408f30
/* 00408f10 */  nop        
/* 00408f14 */  jal        0xf402030                                # bgnpolygon
/* 00408f18 */  move       $a0, $s0
/* 00408f1c */  lw         $t7, 8($s2)
/* 00408f20 */  addiu      $s1, $s1, 1
/* 00408f24 */  slt        $at, $s1, $t7
/* 00408f28 */  bnez       $at, 0x408f14
/* 00408f2c */  addiu      $s0, $s0, 0xc
/* 00408f30 */  jal        0xf402088                                # c3i
/* 00408f34 */  nop        
/* 00408f38 */  lw         $s2, ($s2)
/* 00408f3c */  nop        
/* 00408f40 */  bnez       $s2, 0x408ef8
/* 00408f44 */  nop        
/* 00408f48 */  lw         $s1, 0x20($sp)
/* 00408f4c */  nop        
/* 00408f50 */  lw         $ra, 0x1c($sp)
/* 00408f54 */  lw         $s0, 0x14($sp)
/* 00408f58 */  lw         $s2, 0x18($sp)
/* 00408f5c */  jr         $ra
/* 00408f60 */  addiu      $sp, $sp, 0x30
/* 00408f64 */  addiu      $sp, $sp, -0x30
/* 00408f68 */  sw         $s0, 0x14($sp)
/* 00408f6c */  move       $s0, $a0
/* 00408f70 */  sw         $ra, 0x1c($sp)
/* 00408f74 */  sw         $s2, 0x18($sp)
/* 00408f78 */  jal        0x4034b8                                 # bind_material
/* 00408f7c */  move       $a0, $zero
/* 00408f80 */  beqz       $s0, 0x40901c
/* 00408f84 */  move       $s2, $s0
/* 00408f88 */  sw         $s1, 0x20($sp)
/* 00408f8c */  lw         $s0, 4($s2)
/* 00408f90 */  jal        0xf4020e8                                # endclosedline
/* 00408f94 */  addiu      $s1, $zero, 8
/* 00408f98 */  lw         $a0, ($s0)
/* 00408f9c */  jal        0xf402098                                # color
/* 00408fa0 */  nop        
/* 00408fa4 */  jal        0xf402030                                # bgnpolygon
/* 00408fa8 */  addiu      $a0, $s0, 4
/* 00408fac */  lw         $a0, 0x10($s0)
/* 00408fb0 */  jal        0xf402098                                # color
/* 00408fb4 */  nop        
/* 00408fb8 */  jal        0xf402030                                # bgnpolygon
/* 00408fbc */  addiu      $a0, $s0, 0x14
/* 00408fc0 */  lw         $t6, 8($s2)
/* 00408fc4 */  addiu      $s0, $s0, 0x20
/* 00408fc8 */  slti       $at, $t6, 9
/* 00408fcc */  bnez       $at, 0x408ffc
/* 00408fd0 */  nop        
/* 00408fd4 */  lw         $a0, ($s0)
/* 00408fd8 */  jal        0xf402098                                # color
/* 00408fdc */  nop        
/* 00408fe0 */  jal        0xf402030                                # bgnpolygon
/* 00408fe4 */  addiu      $a0, $s0, 4
/* 00408fe8 */  lw         $t7, 8($s2)
/* 00408fec */  addiu      $s1, $s1, 4
/* 00408ff0 */  slt        $at, $s1, $t7
/* 00408ff4 */  bnez       $at, 0x408fd4
/* 00408ff8 */  addiu      $s0, $s0, 0x10
/* 00408ffc */  jal        0xf402088                                # c3i
/* 00409000 */  nop        
/* 00409004 */  lw         $s2, ($s2)
/* 00409008 */  nop        
/* 0040900c */  bnez       $s2, 0x408f8c
/* 00409010 */  nop        
/* 00409014 */  lw         $s1, 0x20($sp)
/* 00409018 */  nop        
/* 0040901c */  lw         $ra, 0x1c($sp)
/* 00409020 */  lw         $s0, 0x14($sp)
/* 00409024 */  lw         $s2, 0x18($sp)
/* 00409028 */  jr         $ra
/* 0040902c */  addiu      $sp, $sp, 0x30
/* 00409030 */  addiu      $sp, $sp, -0x30
/* 00409034 */  sw         $s0, 0x14($sp)
/* 00409038 */  move       $s0, $a0
/* 0040903c */  sw         $ra, 0x1c($sp)
/* 00409040 */  sw         $s2, 0x18($sp)
/* 00409044 */  jal        0x4034b8                                 # bind_material
/* 00409048 */  move       $a0, $zero
/* 0040904c */  beqz       $s0, 0x4090e8
/* 00409050 */  move       $s2, $s0
/* 00409054 */  sw         $s1, 0x20($sp)
/* 00409058 */  lw         $s0, 4($s2)
/* 0040905c */  jal        0xf4020f0                                # bgnline
/* 00409060 */  addiu      $s1, $zero, 8
/* 00409064 */  lw         $a0, ($s0)
/* 00409068 */  jal        0xf402098                                # color
/* 0040906c */  nop        
/* 00409070 */  jal        0xf402030                                # bgnpolygon
/* 00409074 */  addiu      $a0, $s0, 4
/* 00409078 */  lw         $a0, 0x10($s0)
/* 0040907c */  jal        0xf402098                                # color
/* 00409080 */  nop        
/* 00409084 */  jal        0xf402030                                # bgnpolygon
/* 00409088 */  addiu      $a0, $s0, 0x14
/* 0040908c */  lw         $t6, 8($s2)
/* 00409090 */  addiu      $s0, $s0, 0x20
/* 00409094 */  slti       $at, $t6, 9
/* 00409098 */  bnez       $at, 0x4090c8
/* 0040909c */  nop        
/* 004090a0 */  lw         $a0, ($s0)
/* 004090a4 */  jal        0xf402098                                # color
/* 004090a8 */  nop        
/* 004090ac */  jal        0xf402030                                # bgnpolygon
/* 004090b0 */  addiu      $a0, $s0, 4
/* 004090b4 */  lw         $t7, 8($s2)
/* 004090b8 */  addiu      $s1, $s1, 4
/* 004090bc */  slt        $at, $s1, $t7
/* 004090c0 */  bnez       $at, 0x4090a0
/* 004090c4 */  addiu      $s0, $s0, 0x10
/* 004090c8 */  jal        0xf402090                                # cpack
/* 004090cc */  nop        
/* 004090d0 */  lw         $s2, ($s2)
/* 004090d4 */  nop        
/* 004090d8 */  bnez       $s2, 0x409058
/* 004090dc */  nop        
/* 004090e0 */  lw         $s1, 0x20($sp)
/* 004090e4 */  nop        
/* 004090e8 */  lw         $ra, 0x1c($sp)
/* 004090ec */  lw         $s0, 0x14($sp)
/* 004090f0 */  lw         $s2, 0x18($sp)
/* 004090f4 */  jr         $ra
/* 004090f8 */  addiu      $sp, $sp, 0x30
/* 004090fc */  addiu      $sp, $sp, -0x40
/* 00409100 */  sw         $s0, 0x14($sp)
/* 00409104 */  move       $s0, $a0
/* 00409108 */  sw         $ra, 0x1c($sp)
/* 0040910c */  sw         $s4, 0x18($sp)
/* 00409110 */  jal        0x4034b8                                 # bind_material
/* 00409114 */  addiu      $a0, $zero, 1
/* 00409118 */  beqz       $s0, 0x4091c0
/* 0040911c */  move       $s4, $s0
/* 00409120 */  sw         $s1, 0x28($sp)
/* 00409124 */  sw         $s2, 0x24($sp)
/* 00409128 */  sw         $s3, 0x20($sp)
/* 0040912c */  lw         $s2, 4($s4)
/* 00409130 */  jal        0xf4020e8                                # endclosedline
/* 00409134 */  addiu      $s3, $zero, 0xc
/* 00409138 */  jal        0xf402068                                # v3f
/* 0040913c */  move       $a0, $s2
/* 00409140 */  jal        0xf402030                                # bgnpolygon
/* 00409144 */  addiu      $a0, $s2, 0xc
/* 00409148 */  jal        0xf402068                                # v3f
/* 0040914c */  addiu      $a0, $s2, 0x18
/* 00409150 */  jal        0xf402030                                # bgnpolygon
/* 00409154 */  addiu      $a0, $s2, 0x24
/* 00409158 */  lw         $t6, 8($s4)
/* 0040915c */  nop        
/* 00409160 */  slti       $at, $t6, 0xd
/* 00409164 */  bnez       $at, 0x409198
/* 00409168 */  nop        
/* 0040916c */  move       $a0, $s2
/* 00409170 */  addiu      $s0, $s2, 0xc
/* 00409174 */  jal        0xf402068                                # v3f
/* 00409178 */  addiu      $s1, $s2, 0x18
/* 0040917c */  jal        0xf402030                                # bgnpolygon
/* 00409180 */  move       $a0, $s0
/* 00409184 */  lw         $t7, 8($s4)
/* 00409188 */  addiu      $s3, $s3, 6
/* 0040918c */  slt        $at, $s3, $t7
/* 00409190 */  bnez       $at, 0x40916c
/* 00409194 */  move       $s2, $s1
/* 00409198 */  jal        0xf402088                                # c3i
/* 0040919c */  nop        
/* 004091a0 */  lw         $s4, ($s4)
/* 004091a4 */  nop        
/* 004091a8 */  bnez       $s4, 0x40912c
/* 004091ac */  nop        
/* 004091b0 */  lw         $s1, 0x28($sp)
/* 004091b4 */  lw         $s2, 0x24($sp)
/* 004091b8 */  lw         $s3, 0x20($sp)
/* 004091bc */  nop        
/* 004091c0 */  lw         $ra, 0x1c($sp)
/* 004091c4 */  lw         $s0, 0x14($sp)
/* 004091c8 */  lw         $s4, 0x18($sp)
/* 004091cc */  jr         $ra
/* 004091d0 */  addiu      $sp, $sp, 0x40
/* 004091d4 */  nop        
/* 004091d8 */  nop        
/* 004091dc */  nop        
/* 004091e0 */  addiu      $sp, $sp, -0x18
/* 004091e4 */  move       $a3, $a0
/* 004091e8 */  sw         $ra, 0x14($sp)
/* 004091ec */  beqz       $a3, 0x4091fc
/* 004091f0 */  move       $t0, $a1
/* 004091f4 */  bnez       $t0, 0x40923c
/* 004091f8 */  nop        
/* 004091fc */  lui        $a0, 0x1000
/* 00409200 */  lui        $a1, 0x1000
/* 00409204 */  lui        $a2, 0x1000
/* 00409208 */  sw         $a3, 0x18($sp)
/* 0040920c */  addiu      $a2, $a2, 0x1ef4
/* 00409210 */  addiu      $a1, $a1, 0x1ee0
/* 00409214 */  addiu      $a0, $a0, 0x36b4
/* 00409218 */  jal        0xf801150                                # fclose
/* 0040921c */  sw         $t0, 0x1c($sp)
/* 00409220 */  lw         $a3, 0x18($sp)
/* 00409224 */  lw         $t0, 0x1c($sp)
/* 00409228 */  jal        0x40d3c0
/* 0040922c */  addiu      $a0, $zero, 1
/* 00409230 */  lw         $a3, 0x18($sp)
/* 00409234 */  lw         $t0, 0x1c($sp)
/* 00409238 */  nop        
/* 0040923c */  lbu        $v0, ($a3)
/* 00409240 */  lbu        $v1, ($t0)
/* 00409244 */  sltiu      $at, $v0, 0x41
/* 00409248 */  addiu      $a3, $a3, 1
/* 0040924c */  bnez       $at, 0x409268
/* 00409250 */  addiu      $t0, $t0, 1
/* 00409254 */  sltiu      $at, $v0, 0x5b
/* 00409258 */  beqz       $at, 0x40926c
/* 0040925c */  sltiu      $at, $v1, 0x41
/* 00409260 */  addiu      $v0, $v0, 0x20
/* 00409264 */  andi       $v0, $v0, 0xff
/* 00409268 */  sltiu      $at, $v1, 0x41
/* 0040926c */  bnez       $at, 0x409284
/* 00409270 */  sltiu      $at, $v1, 0x5b
/* 00409274 */  beqz       $at, 0x409284
/* 00409278 */  nop        
/* 0040927c */  addiu      $v1, $v1, 0x20
/* 00409280 */  andi       $v1, $v1, 0xff
/* 00409284 */  beq        $v0, $v1, 0x409294
/* 00409288 */  nop        
/* 0040928c */  b          0x4092c4
/* 00409290 */  move       $v0, $zero
/* 00409294 */  beqz       $v0, 0x4092a4
/* 00409298 */  nop        
/* 0040929c */  bnez       $v1, 0x40923c
/* 004092a0 */  nop        
/* 004092a4 */  bnez       $v0, 0x4092bc
/* 004092a8 */  nop        
/* 004092ac */  bnez       $v1, 0x4092c0
/* 004092b0 */  move       $v1, $zero
/* 004092b4 */  b          0x4092c0
/* 004092b8 */  addiu      $v1, $zero, 1
/* 004092bc */  move       $v1, $zero
/* 004092c0 */  move       $v0, $v1
/* 004092c4 */  lw         $ra, 0x14($sp)
/* 004092c8 */  addiu      $sp, $sp, 0x18
/* 004092cc */  jr         $ra
/* 004092d0 */  nop        
/* 004092d4 */  addiu      $sp, $sp, -0x58
/* 004092d8 */  sw         $s2, 0x20($sp)
/* 004092dc */  sw         $ra, 0x24($sp)
/* 004092e0 */  move       $s2, $a0
/* 004092e4 */  sw         $s0, 0x18($sp)
/* 004092e8 */  sw         $s1, 0x1c($sp)
/* 004092ec */  sw         $a1, 0x5c($sp)
/* 004092f0 */  sw         $a2, 0x60($sp)
/* 004092f4 */  sw         $a3, 0x64($sp)
/* 004092f8 */  lbu        $v0, ($s2)
/* 004092fc */  lui        $s1, 0x1000
/* 00409300 */  addiu      $s0, $sp, 0x5c
/* 00409304 */  addiu      $s1, $s1, 0x47f0
/* 00409308 */  beqz       $v0, 0x409448
/* 0040930c */  addiu      $s2, $s2, 1
/* 00409310 */  sw         $s3, 0x40($sp)
/* 00409314 */  sw         $s4, 0x3c($sp)
/* 00409318 */  sw         $s5, 0x38($sp)
/* 0040931c */  sw         $s6, 0x34($sp)
/* 00409320 */  sw         $s7, 0x30($sp)
/* 00409324 */  sw         $fp, 0x2c($sp)
/* 00409328 */  addiu      $fp, $zero, 0x78
/* 0040932c */  addiu      $s7, $zero, 0x73
/* 00409330 */  addiu      $s6, $zero, 0x64
/* 00409334 */  addiu      $s5, $zero, 0x63
/* 00409338 */  addiu      $s4, $zero, 0x25
/* 0040933c */  addiu      $s3, $zero, -4
/* 00409340 */  beq        $v0, $s4, 0x409354
/* 00409344 */  nop        
/* 00409348 */  sb         $v0, ($s1)
/* 0040934c */  b          0x40941c
/* 00409350 */  addiu      $s1, $s1, 1
/* 00409354 */  sb         $zero, ($s1)
/* 00409358 */  lbu        $v0, ($s2)
/* 0040935c */  addiu      $s2, $s2, 1
/* 00409360 */  beq        $v0, $s5, 0x4093ac
/* 00409364 */  addiu      $t7, $s0, 7
/* 00409368 */  beq        $v0, $s6, 0x4093cc
/* 0040936c */  addiu      $t8, $s0, 7
/* 00409370 */  beq        $v0, $s7, 0x40938c
/* 00409374 */  addiu      $t6, $s0, 7
/* 00409378 */  beq        $v0, $fp, 0x4093ec
/* 0040937c */  addiu      $t9, $s0, 7
/* 00409380 */  b          0x40940c
/* 00409384 */  addiu      $t0, $s0, 7
/* 00409388 */  addiu      $t6, $s0, 7
/* 0040938c */  and        $s0, $t6, $s3
/* 00409390 */  lw         $a2, -4($s0)
/* 00409394 */  move       $a0, $s1
/* 00409398 */  jal        0xf8012c0                                # sprintf
/* 0040939c */  addiu      $a1, $gp, -0x7c50
/* 004093a0 */  b          0x409410
/* 004093a4 */  nop        
/* 004093a8 */  addiu      $t7, $s0, 7
/* 004093ac */  and        $s0, $t7, $s3
/* 004093b0 */  lw         $a2, -4($s0)
/* 004093b4 */  move       $a0, $s1
/* 004093b8 */  jal        0xf8012c0                                # sprintf
/* 004093bc */  addiu      $a1, $gp, -0x7c4c
/* 004093c0 */  b          0x409410
/* 004093c4 */  nop        
/* 004093c8 */  addiu      $t8, $s0, 7
/* 004093cc */  and        $s0, $t8, $s3
/* 004093d0 */  lw         $a2, -4($s0)
/* 004093d4 */  move       $a0, $s1
/* 004093d8 */  jal        0xf8012c0                                # sprintf
/* 004093dc */  addiu      $a1, $gp, -0x7c48
/* 004093e0 */  b          0x409410
/* 004093e4 */  nop        
/* 004093e8 */  addiu      $t9, $s0, 7
/* 004093ec */  and        $s0, $t9, $s3
/* 004093f0 */  lw         $a2, -4($s0)
/* 004093f4 */  move       $a0, $s1
/* 004093f8 */  jal        0xf8012c0                                # sprintf
/* 004093fc */  addiu      $a1, $gp, -0x7c44
/* 00409400 */  b          0x409410
/* 00409404 */  nop        
/* 00409408 */  addiu      $t0, $s0, 7
/* 0040940c */  and        $s0, $t0, $s3
/* 00409410 */  jal        0xf801308                                # close
/* 00409414 */  move       $a0, $s1
/* 00409418 */  addu       $s1, $s1, $v0
/* 0040941c */  lbu        $v0, ($s2)
/* 00409420 */  addiu      $s2, $s2, 1
/* 00409424 */  bnez       $v0, 0x409340
/* 00409428 */  nop        
/* 0040942c */  lw         $s3, 0x40($sp)
/* 00409430 */  lw         $s4, 0x3c($sp)
/* 00409434 */  lw         $s5, 0x38($sp)
/* 00409438 */  lw         $s6, 0x34($sp)
/* 0040943c */  lw         $s7, 0x30($sp)
/* 00409440 */  lw         $fp, 0x2c($sp)
/* 00409444 */  nop        
/* 00409448 */  addiu      $t1, $zero, 0xa
/* 0040944c */  lui        $a0, 0x1000
/* 00409450 */  lui        $a1, 0x1000
/* 00409454 */  sb         $t1, ($s1)
/* 00409458 */  addiu      $s1, $s1, 1
/* 0040945c */  sb         $zero, ($s1)
/* 00409460 */  addiu      $a1, $a1, 0x47f0
/* 00409464 */  jal        0xf801150                                # fclose
/* 00409468 */  addiu      $a0, $a0, 0x36b4
/* 0040946c */  jal        0x40d3c0
/* 00409470 */  addiu      $a0, $zero, 1
/* 00409474 */  lw         $ra, 0x24($sp)
/* 00409478 */  lw         $s0, 0x18($sp)
/* 0040947c */  lw         $s1, 0x1c($sp)
/* 00409480 */  lw         $s2, 0x20($sp)
/* 00409484 */  jr         $ra
/* 00409488 */  addiu      $sp, $sp, 0x58
/* 0040948c */  addiu      $sp, $sp, -0x48
/* 00409490 */  sw         $s4, 0x1c($sp)
/* 00409494 */  sw         $ra, 0x24($sp)
/* 00409498 */  sw         $s5, 0x20($sp)
/* 0040949c */  move       $s4, $a0
/* 004094a0 */  sw         $s2, 0x18($sp)
/* 004094a4 */  sw         $s1, 0x14($sp)
/* 004094a8 */  move       $s2, $a1
/* 004094ac */  move       $s5, $a3
/* 004094b0 */  sw         $a2, 0x50($sp)
/* 004094b4 */  jal        0xf801208                                # free
/* 004094b8 */  sll        $a0, $s4, 2
/* 004094bc */  bnez       $v0, 0x4094d4
/* 004094c0 */  sw         $v0, 0x3c($sp)
/* 004094c4 */  lui        $a0, 0x1000
/* 004094c8 */  addiu      $a0, $a0, 0x1f10
/* 004094cc */  jal        0x4092d4
/* 004094d0 */  move       $a1, $s5
/* 004094d4 */  blez       $s4, 0x409538
/* 004094d8 */  move       $s1, $zero
/* 004094dc */  lw         $t6, 0x50($sp)
/* 004094e0 */  sw         $s3, 0x28($sp)
/* 004094e4 */  multu      $s2, $t6
/* 004094e8 */  sw         $s0, 0x2c($sp)
/* 004094ec */  lui        $s2, 0x1000
/* 004094f0 */  lw         $s0, 0x3c($sp)
/* 004094f4 */  addiu      $s2, $s2, 0x1f20
/* 004094f8 */  mflo       $s3
/* 004094fc */  nop        
/* 00409500 */  nop        
/* 00409504 */  jal        0xf801208                                # free
/* 00409508 */  move       $a0, $s3
/* 0040950c */  bnez       $v0, 0x409520
/* 00409510 */  sw         $v0, ($s0)
/* 00409514 */  move       $a0, $s2
/* 00409518 */  jal        0x4092d4
/* 0040951c */  move       $a1, $s5
/* 00409520 */  addiu      $s1, $s1, 1
/* 00409524 */  bne        $s1, $s4, 0x409504
/* 00409528 */  addiu      $s0, $s0, 4
/* 0040952c */  lw         $s0, 0x2c($sp)
/* 00409530 */  lw         $s3, 0x28($sp)
/* 00409534 */  nop        
/* 00409538 */  lw         $ra, 0x24($sp)
/* 0040953c */  lw         $v0, 0x3c($sp)
/* 00409540 */  lw         $s1, 0x14($sp)
/* 00409544 */  lw         $s2, 0x18($sp)
/* 00409548 */  lw         $s4, 0x1c($sp)
/* 0040954c */  lw         $s5, 0x20($sp)
/* 00409550 */  jr         $ra
/* 00409554 */  addiu      $sp, $sp, 0x48
/* 00409558 */  addiu      $sp, $sp, -0x30
/* 0040955c */  sw         $s2, 0x18($sp)
/* 00409560 */  move       $s2, $a1
/* 00409564 */  sw         $s1, 0x14($sp)
/* 00409568 */  sw         $ra, 0x1c($sp)
/* 0040956c */  sw         $a0, 0x30($sp)
/* 00409570 */  blez       $s2, 0x4095a4
/* 00409574 */  move       $s1, $zero
/* 00409578 */  sw         $s0, 0x24($sp)
/* 0040957c */  lw         $s0, 0x30($sp)
/* 00409580 */  nop        
/* 00409584 */  lw         $a0, ($s0)
/* 00409588 */  jal        0xf801200                                # malloc
/* 0040958c */  nop        
/* 00409590 */  addiu      $s1, $s1, 1
/* 00409594 */  bne        $s1, $s2, 0x409584
/* 00409598 */  addiu      $s0, $s0, 4
/* 0040959c */  lw         $s0, 0x24($sp)
/* 004095a0 */  nop        
/* 004095a4 */  lw         $a0, 0x30($sp)
/* 004095a8 */  jal        0xf801200                                # malloc
/* 004095ac */  nop        
/* 004095b0 */  lw         $ra, 0x1c($sp)
/* 004095b4 */  lw         $s1, 0x14($sp)
/* 004095b8 */  lw         $s2, 0x18($sp)
/* 004095bc */  jr         $ra
/* 004095c0 */  addiu      $sp, $sp, 0x30
/* 004095c4 */  lw         $v0, ($a0)
/* 004095c8 */  addiu      $a1, $zero, 9
/* 004095cc */  addiu      $a2, $zero, 0xa
/* 004095d0 */  addiu      $a3, $zero, 0x20
/* 004095d4 */  lbu        $v1, ($v0)
/* 004095d8 */  b          0x4095e8
/* 004095dc */  nop        
/* 004095e0 */  jr         $ra
/* 004095e4 */  sw         $v0, ($a0)
/* 004095e8 */  beq        $v1, $a1, 0x409600
/* 004095ec */  nop        
/* 004095f0 */  beq        $v1, $a2, 0x409600
/* 004095f4 */  nop        
/* 004095f8 */  bne        $v1, $a3, 0x4095e0
/* 004095fc */  nop        
/* 00409600 */  b          0x4095d4
/* 00409604 */  addiu      $v0, $v0, 1
/* 00409608 */  jr         $ra
/* 0040960c */  nop        
/* 00409610 */  lw         $v1, 0x10($sp)
/* 00409614 */  move       $v0, $zero
/* 00409618 */  blez       $v1, 0x409770
/* 0040961c */  nop        
/* 00409620 */  andi       $t0, $v1, 3
/* 00409624 */  beqz       $t0, 0x409678
/* 00409628 */  nop        
/* 0040962c */  lw         $t6, ($a0)
/* 00409630 */  addiu      $v0, $v0, 1
/* 00409634 */  andi       $t7, $t6, 0xff
/* 00409638 */  sh         $t7, ($a1)
/* 0040963c */  lw         $t8, ($a0)
/* 00409640 */  addiu      $a1, $a1, 2
/* 00409644 */  srl        $t9, $t8, 8
/* 00409648 */  andi       $t1, $t9, 0xff
/* 0040964c */  sh         $t1, ($a2)
/* 00409650 */  lw         $t2, ($a0)
/* 00409654 */  addiu      $a2, $a2, 2
/* 00409658 */  srl        $t3, $t2, 0x10
/* 0040965c */  andi       $t4, $t3, 0xff
/* 00409660 */  sh         $t4, ($a3)
/* 00409664 */  addiu      $a3, $a3, 2
/* 00409668 */  bne        $t0, $v0, 0x40962c
/* 0040966c */  addiu      $a0, $a0, 4
/* 00409670 */  beq        $v0, $v1, 0x409770
/* 00409674 */  nop        
/* 00409678 */  lw         $t5, ($a0)
/* 0040967c */  addiu      $a1, $a1, 2
/* 00409680 */  andi       $t6, $t5, 0xff
/* 00409684 */  sh         $t6, -2($a1)
/* 00409688 */  lw         $t7, ($a0)
/* 0040968c */  addiu      $a2, $a2, 2
/* 00409690 */  srl        $t8, $t7, 8
/* 00409694 */  andi       $t9, $t8, 0xff
/* 00409698 */  sh         $t9, -2($a2)
/* 0040969c */  lw         $t1, ($a0)
/* 004096a0 */  addiu      $a3, $a3, 2
/* 004096a4 */  srl        $t2, $t1, 0x10
/* 004096a8 */  andi       $t3, $t2, 0xff
/* 004096ac */  sh         $t3, -2($a3)
/* 004096b0 */  lw         $t4, 4($a0)
/* 004096b4 */  addiu      $a0, $a0, 4
/* 004096b8 */  andi       $t5, $t4, 0xff
/* 004096bc */  sh         $t5, ($a1)
/* 004096c0 */  lw         $t6, ($a0)
/* 004096c4 */  addiu      $a0, $a0, 4
/* 004096c8 */  srl        $t7, $t6, 8
/* 004096cc */  andi       $t8, $t7, 0xff
/* 004096d0 */  sh         $t8, ($a2)
/* 004096d4 */  lw         $t9, -4($a0)
/* 004096d8 */  addiu      $a3, $a3, 2
/* 004096dc */  srl        $t1, $t9, 0x10
/* 004096e0 */  andi       $t2, $t1, 0xff
/* 004096e4 */  sh         $t2, -2($a3)
/* 004096e8 */  lw         $t3, ($a0)
/* 004096ec */  addiu      $a2, $a2, 2
/* 004096f0 */  andi       $t4, $t3, 0xff
/* 004096f4 */  sh         $t4, 2($a1)
/* 004096f8 */  lw         $t5, ($a0)
/* 004096fc */  addiu      $a1, $a1, 2
/* 00409700 */  srl        $t6, $t5, 8
/* 00409704 */  andi       $t7, $t6, 0xff
/* 00409708 */  sh         $t7, ($a2)
/* 0040970c */  lw         $t8, ($a0)
/* 00409710 */  addiu      $a1, $a1, 2
/* 00409714 */  srl        $t9, $t8, 0x10
/* 00409718 */  andi       $t1, $t9, 0xff
/* 0040971c */  sh         $t1, ($a3)
/* 00409720 */  lw         $t2, 4($a0)
/* 00409724 */  addiu      $a2, $a2, 2
/* 00409728 */  andi       $t3, $t2, 0xff
/* 0040972c */  sh         $t3, ($a1)
/* 00409730 */  lw         $t4, 4($a0)
/* 00409734 */  addiu      $a3, $a3, 2
/* 00409738 */  srl        $t5, $t4, 8
/* 0040973c */  andi       $t6, $t5, 0xff
/* 00409740 */  sh         $t6, ($a2)
/* 00409744 */  lw         $t7, 4($a0)
/* 00409748 */  addiu      $a0, $a0, 4
/* 0040974c */  srl        $t8, $t7, 0x10
/* 00409750 */  andi       $t9, $t8, 0xff
/* 00409754 */  addiu      $v0, $v0, 4
/* 00409758 */  sh         $t9, ($a3)
/* 0040975c */  addiu      $a0, $a0, 4
/* 00409760 */  addiu      $a3, $a3, 2
/* 00409764 */  addiu      $a2, $a2, 2
/* 00409768 */  bne        $v0, $v1, 0x409678
/* 0040976c */  addiu      $a1, $a1, 2
/* 00409770 */  jr         $ra
/* 00409774 */  nop        
/* 00409778 */  addiu      $sp, $sp, -0x78
/* 0040977c */  sw         $s0, 0x24($sp)
/* 00409780 */  move       $s0, $a0
/* 00409784 */  sw         $ra, 0x2c($sp)
/* 00409788 */  sw         $s6, 0x28($sp)
/* 0040978c */  lbu        $t6, ($s0)
/* 00409790 */  move       $s6, $zero
/* 00409794 */  beqz       $t6, 0x4099e4
/* 00409798 */  lw         $ra, 0x2c($sp)
/* 0040979c */  sw         $s1, 0x40($sp)
/* 004097a0 */  sw         $s2, 0x3c($sp)
/* 004097a4 */  lui        $a0, 0x1000
/* 004097a8 */  sw         $s3, 0x38($sp)
/* 004097ac */  sw         $s4, 0x34($sp)
/* 004097b0 */  sw         $s5, 0x30($sp)
/* 004097b4 */  addiu      $a0, $a0, 0x1f30
/* 004097b8 */  jal        0xf801250                                # getopt
/* 004097bc */  move       $a1, $s0
/* 004097c0 */  lw         $t7, -0x7e98($gp)                        # view_state_ptr
/* 004097c4 */  addiu      $t8, $zero, 3
/* 004097c8 */  lw         $v0, ($t7)
/* 004097cc */  lw         $v1, 4($t7)
/* 004097d0 */  sw         $t8, 0x18($sp)
/* 004097d4 */  sw         $v0, 0x10($sp)
/* 004097d8 */  move       $a0, $s0
/* 004097dc */  addiu      $a1, $gp, -0x7c40
/* 004097e0 */  addiu      $a2, $zero, 0x101
/* 004097e4 */  addiu      $a3, $zero, 3
/* 004097e8 */  jal        0x40ae50
/* 004097ec */  sw         $v1, 0x14($sp)
/* 004097f0 */  bnez       $v0, 0x409818
/* 004097f4 */  move       $s1, $v0
/* 004097f8 */  lui        $a0, 0x1000
/* 004097fc */  lui        $a1, 0x1000
/* 00409800 */  addiu      $a1, $a1, 0x1f50
/* 00409804 */  addiu      $a0, $a0, 0x36b4
/* 00409808 */  jal        0xf801150                                # fclose
/* 0040980c */  move       $a2, $s0
/* 00409810 */  jal        0x40d3c0
/* 00409814 */  addiu      $a0, $zero, 1
/* 00409818 */  lhu        $a0, 6($s1)
/* 0040981c */  jal        0xf801208                                # free
/* 00409820 */  sll        $a0, $a0, 2
/* 00409824 */  lhu        $a0, 6($s1)
/* 00409828 */  move       $s2, $v0
/* 0040982c */  jal        0xf801208                                # free
/* 00409830 */  sll        $a0, $a0, 1
/* 00409834 */  lhu        $a0, 6($s1)
/* 00409838 */  move       $s3, $v0
/* 0040983c */  jal        0xf801208                                # free
/* 00409840 */  sll        $a0, $a0, 1
/* 00409844 */  lhu        $a0, 6($s1)
/* 00409848 */  move       $s4, $v0
/* 0040984c */  jal        0xf801208                                # free
/* 00409850 */  sll        $a0, $a0, 1
/* 00409854 */  beqz       $s2, 0x409874
/* 00409858 */  move       $s5, $v0
/* 0040985c */  beqz       $s3, 0x409874
/* 00409860 */  nop        
/* 00409864 */  beqz       $s4, 0x409874
/* 00409868 */  nop        
/* 0040986c */  bnez       $v0, 0x409890
/* 00409870 */  nop        
/* 00409874 */  lui        $a0, 0x1000
/* 00409878 */  lui        $a1, 0x1000
/* 0040987c */  addiu      $a1, $a1, 0x1f78
/* 00409880 */  jal        0xf801150                                # fclose
/* 00409884 */  addiu      $a0, $a0, 0x36b4
/* 00409888 */  jal        0x40d3c0
/* 0040988c */  addiu      $a0, $zero, 1
/* 00409890 */  lhu        $t9, 0xa($s1)
/* 00409894 */  addiu      $at, $zero, 3
/* 00409898 */  beq        $t9, $at, 0x4098c4
/* 0040989c */  nop        
/* 004098a0 */  lui        $a0, 0x1000
/* 004098a4 */  lui        $a1, 0x1000
/* 004098a8 */  lui        $a2, 0x1000
/* 004098ac */  addiu      $a2, $a2, 0x1fa8
/* 004098b0 */  addiu      $a1, $a1, 0x1f94
/* 004098b4 */  jal        0xf801150                                # fclose
/* 004098b8 */  addiu      $a0, $a0, 0x36b4
/* 004098bc */  jal        0x40d3c0
/* 004098c0 */  addiu      $a0, $zero, 1
/* 004098c4 */  jal        0xf4015f8                                # lmcolor
/* 004098c8 */  addiu      $a0, $zero, 1
/* 004098cc */  lhu        $t0, 8($s1)
/* 004098d0 */  move       $s0, $zero
/* 004098d4 */  beqz       $t0, 0x409980
/* 004098d8 */  nop        
/* 004098dc */  lhu        $a2, 6($s1)
/* 004098e0 */  sw         $s2, 0x10($sp)
/* 004098e4 */  addiu      $a2, $a2, -1
/* 004098e8 */  sll        $a2, $a2, 0x10
/* 004098ec */  sra        $a2, $a2, 0x10
/* 004098f0 */  move       $a0, $zero
/* 004098f4 */  move       $a1, $s0
/* 004098f8 */  jal        0xf4015e8                                # lmbind
/* 004098fc */  move       $a3, $s0
/* 00409900 */  lhu        $v1, 6($s1)
/* 00409904 */  nop        
/* 00409908 */  beq        $v0, $v1, 0x40991c
/* 0040990c */  move       $a0, $s2
/* 00409910 */  addiu      $s6, $zero, 1
/* 00409914 */  sw         $v0, 0x4c($sp)
/* 00409918 */  move       $a0, $s2
/* 0040991c */  move       $a1, $s3
/* 00409920 */  move       $a2, $s4
/* 00409924 */  move       $a3, $s5
/* 00409928 */  jal        0x409610
/* 0040992c */  sw         $v1, 0x10($sp)
/* 00409930 */  move       $a0, $s1
/* 00409934 */  move       $a1, $s3
/* 00409938 */  move       $a2, $s0
/* 0040993c */  jal        0x40b6e0
/* 00409940 */  move       $a3, $zero
/* 00409944 */  move       $a0, $s1
/* 00409948 */  move       $a1, $s4
/* 0040994c */  move       $a2, $s0
/* 00409950 */  jal        0x40b6e0
/* 00409954 */  addiu      $a3, $zero, 1
/* 00409958 */  move       $a0, $s1
/* 0040995c */  move       $a1, $s5
/* 00409960 */  move       $a2, $s0
/* 00409964 */  jal        0x40b6e0
/* 00409968 */  addiu      $a3, $zero, 2
/* 0040996c */  lhu        $t1, 8($s1)
/* 00409970 */  addiu      $s0, $s0, 1
/* 00409974 */  sltu       $at, $s0, $t1
/* 00409978 */  bnez       $at, 0x4098dc
/* 0040997c */  nop        
/* 00409980 */  beqz       $s6, 0x4099a0
/* 00409984 */  nop        
/* 00409988 */  lui        $a0, 0x1000
/* 0040998c */  lui        $a1, 0x1000
/* 00409990 */  lw         $a2, 0x4c($sp)
/* 00409994 */  addiu      $a1, $a1, 0x1fc8
/* 00409998 */  jal        0xf801150                                # fclose
/* 0040999c */  addiu      $a0, $a0, 0x36b4
/* 004099a0 */  jal        0x40bee0
/* 004099a4 */  move       $a0, $s1
/* 004099a8 */  jal        0xf801200                                # malloc
/* 004099ac */  move       $a0, $s2
/* 004099b0 */  jal        0xf801200                                # malloc
/* 004099b4 */  move       $a0, $s3
/* 004099b8 */  jal        0xf801200                                # malloc
/* 004099bc */  move       $a0, $s4
/* 004099c0 */  jal        0xf801200                                # malloc
/* 004099c4 */  move       $a0, $s5
/* 004099c8 */  lw         $s1, 0x40($sp)
/* 004099cc */  lw         $s2, 0x3c($sp)
/* 004099d0 */  lw         $s3, 0x38($sp)
/* 004099d4 */  lw         $s4, 0x34($sp)
/* 004099d8 */  lw         $s5, 0x30($sp)
/* 004099dc */  nop        
/* 004099e0 */  lw         $ra, 0x2c($sp)
/* 004099e4 */  lw         $s0, 0x24($sp)
/* 004099e8 */  lw         $s6, 0x28($sp)
/* 004099ec */  jr         $ra
/* 004099f0 */  addiu      $sp, $sp, 0x78
/* 004099f4 */  nop        
/* 004099f8 */  nop        
/* 004099fc */  nop        
/* 00409a00 */  sw         $zero, -0x7a64($gp)                      # .sbss @ 0x1000430c
/* 00409a04 */  sw         $zero, -0x7a60($gp)                      # .sbss @ 0x10004310
/* 00409a08 */  sw         $zero, -0x7a5c($gp)                      # .sbss @ 0x10004314
/* 00409a0c */  sw         $zero, -0x7a78($gp)                      # .sbss @ 0x100042f8
/* 00409a10 */  addiu      $sp, $sp, -0x40
/* 00409a14 */  sw         $fp, 0x38($sp)
/* 00409a18 */  sw         $s7, 0x34($sp)
/* 00409a1c */  sw         $s4, 0x28($sp)
/* 00409a20 */  sw         $ra, 0x3c($sp)
/* 00409a24 */  sw         $s6, 0x30($sp)
/* 00409a28 */  sw         $s5, 0x2c($sp)
/* 00409a2c */  sw         $s2, 0x20($sp)
/* 00409a30 */  sw         $s3, 0x24($sp)
/* 00409a34 */  sw         $s0, 0x18($sp)
/* 00409a38 */  sw         $s1, 0x1c($sp)
/* 00409a3c */  lui        $t6, 0x1000
/* 00409a40 */  lui        $t7, 0x1000
/* 00409a44 */  addiu      $t6, $t6, 0x485c
/* 00409a48 */  sw         $t6, -0x7a6c($gp)                        # .sbss @ 0x10004304
/* 00409a4c */  addiu      $t7, $t7, 0x4ab4
/* 00409a50 */  addiu      $t8, $zero, -1
/* 00409a54 */  lui        $s7, 0x1000
/* 00409a58 */  lui        $fp, 0x1000
/* 00409a5c */  sw         $t7, -0x7a68($gp)                        # .sbss @ 0x10004308
/* 00409a60 */  sw         $t8, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409a64 */  addiu      $fp, $fp, 0x2938
/* 00409a68 */  addiu      $s7, $s7, 0x2018
/* 00409a6c */  addiu      $s4, $zero, -1
/* 00409a70 */  lw         $s5, -0x7a6c($gp)                        # .sbss @ 0x10004304
/* 00409a74 */  lw         $s2, -0x7a68($gp)                        # .sbss @ 0x10004308
/* 00409a78 */  lw         $s1, -0x7a64($gp)                        # .sbss @ 0x1000430c
/* 00409a7c */  nop        
/* 00409a80 */  lui        $t9, 0x1000
/* 00409a84 */  addiu      $t9, $t9, 0x4d10
/* 00409a88 */  addiu      $s2, $s2, 4
/* 00409a8c */  sltu       $at, $s2, $t9
/* 00409a90 */  bnez       $at, 0x409aac
/* 00409a94 */  nop        
/* 00409a98 */  lui        $a0, 0x1000
/* 00409a9c */  jal        0x405520                                 # compute_entity_bbox
/* 00409aa0 */  addiu      $a0, $a0, 0x2e08
/* 00409aa4 */  b          0x40a3b4
/* 00409aa8 */  addiu      $v0, $zero, 1
/* 00409aac */  sw         $s1, ($s2)
/* 00409ab0 */  addiu      $t0, $gp, -0x7a74
/* 00409ab4 */  lw         $at, ($t0)
/* 00409ab8 */  lui        $t2, 0x1000
/* 00409abc */  addiu      $t2, $t2, 0x245c
/* 00409ac0 */  sll        $s3, $s1, 2
/* 00409ac4 */  addu       $s6, $s3, $t2
/* 00409ac8 */  sw         $at, 4($s5)
/* 00409acc */  lw         $v0, ($s6)
/* 00409ad0 */  addiu      $s5, $s5, 4
/* 00409ad4 */  move       $s0, $v0
/* 00409ad8 */  slti       $at, $s0, -0x3e7
/* 00409adc */  beqz       $at, 0x409af8
/* 00409ae0 */  nop        
/* 00409ae4 */  lui        $v0, 0x1000
/* 00409ae8 */  addu       $v0, $v0, $s3
/* 00409aec */  lw         $v0, 0x2ba0($v0)
/* 00409af0 */  b          0x409bb0
/* 00409af4 */  move       $s0, $v0
/* 00409af8 */  lw         $t3, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409afc */  nop        
/* 00409b00 */  bgez       $t3, 0x409b1c
/* 00409b04 */  nop        
/* 00409b08 */  jal        0x4054e0                                 # compute_bounding_box
/* 00409b0c */  nop        
/* 00409b10 */  bgez       $v0, 0x409b1c
/* 00409b14 */  sw         $v0, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409b18 */  sw         $zero, -0x7a80($gp)                      # .sbss @ 0x100042f0
/* 00409b1c */  lw         $t4, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409b20 */  nop        
/* 00409b24 */  addu       $s0, $s0, $t4
/* 00409b28 */  bltz       $s0, 0x409b38
/* 00409b2c */  slti       $at, $s0, 0x111
/* 00409b30 */  bnez       $at, 0x409b4c
/* 00409b34 */  nop        
/* 00409b38 */  lui        $v0, 0x1000
/* 00409b3c */  addu       $v0, $v0, $s3
/* 00409b40 */  lw         $v0, 0x2ba0($v0)
/* 00409b44 */  b          0x409bb0
/* 00409b48 */  move       $s0, $v0
/* 00409b4c */  sll        $t5, $s0, 2
/* 00409b50 */  addu       $t6, $s7, $t5
/* 00409b54 */  lw         $s0, ($t6)
/* 00409b58 */  nop        
/* 00409b5c */  sll        $t8, $s0, 2
/* 00409b60 */  addu       $t9, $fp, $t8
/* 00409b64 */  lw         $t1, ($t9)
/* 00409b68 */  lw         $t7, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409b6c */  nop        
/* 00409b70 */  bne        $t7, $t1, 0x409b9c
/* 00409b74 */  nop        
/* 00409b78 */  lw         $t0, -0x7a7c($gp)                        # .sbss @ 0x100042f4
/* 00409b7c */  lw         $t2, -0x7a78($gp)                        # .sbss @ 0x100042f8
/* 00409b80 */  sw         $s4, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409b84 */  move       $s1, $s0
/* 00409b88 */  blez       $t2, 0x409a80
/* 00409b8c */  sw         $t0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 00409b90 */  addiu      $t3, $t2, -1
/* 00409b94 */  b          0x409a80
/* 00409b98 */  sw         $t3, -0x7a78($gp)                        # .sbss @ 0x100042f8
/* 00409b9c */  lui        $v0, 0x1000
/* 00409ba0 */  addu       $v0, $v0, $s3
/* 00409ba4 */  lw         $v0, 0x2ba0($v0)
/* 00409ba8 */  nop        
/* 00409bac */  move       $s0, $v0
/* 00409bb0 */  addiu      $at, $zero, -2
/* 00409bb4 */  bne        $s0, $at, 0x409c80
/* 00409bb8 */  nop        
/* 00409bbc */  lw         $t4, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409bc0 */  nop        
/* 00409bc4 */  bgez       $t4, 0x409be0
/* 00409bc8 */  nop        
/* 00409bcc */  jal        0x4054e0                                 # compute_bounding_box
/* 00409bd0 */  nop        
/* 00409bd4 */  bgez       $v0, 0x409be0
/* 00409bd8 */  sw         $v0, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409bdc */  sw         $zero, -0x7a80($gp)                      # .sbss @ 0x100042f0
/* 00409be0 */  lui        $t5, 0x1000
/* 00409be4 */  lw         $t5, 0x2000($t5)
/* 00409be8 */  lui        $v1, 0x1000
/* 00409bec */  bne        $s4, $t5, 0x409c08
/* 00409bf0 */  addiu      $v1, $v1, 0x2000
/* 00409bf4 */  lui        $t6, 0x1000
/* 00409bf8 */  lw         $t6, 0x2004($t6)
/* 00409bfc */  nop        
/* 00409c00 */  beq        $s1, $t6, 0x409c28
/* 00409c04 */  nop        
/* 00409c08 */  lw         $t8, 8($v1)
/* 00409c0c */  addiu      $v1, $v1, 8
/* 00409c10 */  bne        $s4, $t8, 0x409c08
/* 00409c14 */  nop        
/* 00409c18 */  lw         $t9, 4($v1)
/* 00409c1c */  nop        
/* 00409c20 */  bne        $s1, $t9, 0x409c08
/* 00409c24 */  nop        
/* 00409c28 */  lw         $v0, 8($v1)
/* 00409c2c */  addiu      $v1, $v1, 8
/* 00409c30 */  bltz       $v0, 0x409c68
/* 00409c34 */  nop        
/* 00409c38 */  lw         $t7, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409c3c */  nop        
/* 00409c40 */  beq        $t7, $v0, 0x409c68
/* 00409c44 */  nop        
/* 00409c48 */  lw         $v0, 8($v1)
/* 00409c4c */  addiu      $v1, $v1, 8
/* 00409c50 */  bltz       $v0, 0x409c68
/* 00409c54 */  nop        
/* 00409c58 */  lw         $t1, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409c5c */  nop        
/* 00409c60 */  bne        $t1, $v0, 0x409c48
/* 00409c64 */  nop        
/* 00409c68 */  lw         $s0, 4($v1)
/* 00409c6c */  nop        
/* 00409c70 */  bgez       $s0, 0x409c80
/* 00409c74 */  nop        
/* 00409c78 */  b          0x40a3b4
/* 00409c7c */  move       $v0, $zero
/* 00409c80 */  bnez       $s0, 0x409d84
/* 00409c84 */  nop        
/* 00409c88 */  lw         $v0, -0x7a78($gp)                        # .sbss @ 0x100042f8
/* 00409c8c */  nop        
/* 00409c90 */  sltiu      $at, $v0, 4
/* 00409c94 */  beqz       $at, 0x409d84
/* 00409c98 */  nop        
/* 00409c9c */  sll        $t0, $v0, 2
/* 00409ca0 */  lui        $at, 0x1000
/* 00409ca4 */  addu       $at, $at, $t0
/* 00409ca8 */  lw         $t0, 0x90($at)
/* 00409cac */  nop        
/* 00409cb0 */  jr         $t0
/* 00409cb4 */  nop        
/* 00409cb8 */  lui        $a0, 0x1000
/* 00409cbc */  jal        0x405520                                 # compute_entity_bbox
/* 00409cc0 */  addiu      $a0, $a0, 0x2e1c
/* 00409cc4 */  lui        $t3, 0x1000
/* 00409cc8 */  addiu      $t3, $t3, 0x4ab8
/* 00409ccc */  addiu      $t2, $zero, 3
/* 00409cd0 */  sltu       $at, $s2, $t3
/* 00409cd4 */  bnez       $at, 0x409d54
/* 00409cd8 */  sw         $t2, -0x7a78($gp)                        # .sbss @ 0x100042f8
/* 00409cdc */  lw         $t4, ($s2)
/* 00409ce0 */  lui        $s0, 0x1000
/* 00409ce4 */  sll        $t5, $t4, 2
/* 00409ce8 */  addu       $s0, $s0, $t5
/* 00409cec */  lw         $s0, 0x245c($s0)
/* 00409cf0 */  nop        
/* 00409cf4 */  addiu      $s0, $s0, 0x100
/* 00409cf8 */  bltz       $s0, 0x409d3c
/* 00409cfc */  slti       $at, $s0, 0x111
/* 00409d00 */  beqz       $at, 0x409d3c
/* 00409d04 */  nop        
/* 00409d08 */  sll        $t6, $s0, 2
/* 00409d0c */  addu       $t8, $s7, $t6
/* 00409d10 */  lw         $v0, ($t8)
/* 00409d14 */  nop        
/* 00409d18 */  sll        $t9, $v0, 2
/* 00409d1c */  addu       $t7, $fp, $t9
/* 00409d20 */  lw         $t1, ($t7)
/* 00409d24 */  nop        
/* 00409d28 */  addiu      $at, $zero, 0x100
/* 00409d2c */  bne        $t1, $at, 0x409d3c
/* 00409d30 */  nop        
/* 00409d34 */  b          0x409a80
/* 00409d38 */  move       $s1, $v0
/* 00409d3c */  lui        $t0, 0x1000
/* 00409d40 */  addiu      $s2, $s2, -4
/* 00409d44 */  addiu      $t0, $t0, 0x4ab8
/* 00409d48 */  sltu       $at, $s2, $t0
/* 00409d4c */  beqz       $at, 0x409cdc
/* 00409d50 */  addiu      $s5, $s5, -4
/* 00409d54 */  b          0x40a3b4
/* 00409d58 */  addiu      $v0, $zero, 1
/* 00409d5c */  lw         $t2, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409d60 */  nop        
/* 00409d64 */  bnez       $t2, 0x409d74
/* 00409d68 */  nop        
/* 00409d6c */  b          0x40a3b4
/* 00409d70 */  addiu      $v0, $zero, 1
/* 00409d74 */  sw         $s4, -0x7a80($gp)                        # .sbss @ 0x100042f0
/* 00409d78 */  lw         $v0, ($s6)
/* 00409d7c */  b          0x409ad8
/* 00409d80 */  move       $s0, $v0
/* 00409d84 */  sll        $a0, $s0, 2
/* 00409d88 */  lui        $v0, 0x1000
/* 00409d8c */  addu       $v0, $v0, $a0
/* 00409d90 */  lw         $v0, 0x2838($v0)
/* 00409d94 */  sw         $s0, -0x7a60($gp)                        # .sbss @ 0x10004310
/* 00409d98 */  andi       $t3, $v0, 1
/* 00409d9c */  bnez       $t3, 0x409e3c
/* 00409da0 */  move       $s3, $s5
/* 00409da4 */  sra        $v0, $v0, 1
/* 00409da8 */  negu       $v1, $v0
/* 00409dac */  sll        $v1, $v1, 2
/* 00409db0 */  addu       $s5, $s5, $v1
/* 00409db4 */  lw         $at, 4($s5)
/* 00409db8 */  addiu      $t4, $gp, -0x7a74
/* 00409dbc */  lui        $s0, 0x1000
/* 00409dc0 */  addu       $s0, $s0, $a0
/* 00409dc4 */  sw         $at, ($t4)
/* 00409dc8 */  lw         $s0, 0x2738($s0)
/* 00409dcc */  lui        $a1, 0x1000
/* 00409dd0 */  sll        $t6, $s0, 2
/* 00409dd4 */  addu       $a1, $a1, $t6
/* 00409dd8 */  addu       $s2, $s2, $v1
/* 00409ddc */  lw         $t8, ($s2)
/* 00409de0 */  lw         $a1, 0x26c4($a1)
/* 00409de4 */  nop        
/* 00409de8 */  addu       $s1, $a1, $t8
/* 00409dec */  addiu      $s1, $s1, 1
/* 00409df0 */  slti       $at, $s1, 0x111
/* 00409df4 */  beqz       $at, 0x409e24
/* 00409df8 */  nop        
/* 00409dfc */  sll        $t9, $s1, 2
/* 00409e00 */  addu       $t7, $s7, $t9
/* 00409e04 */  lw         $s1, ($t7)
/* 00409e08 */  negu       $t1, $s0
/* 00409e0c */  sll        $t0, $s1, 2
/* 00409e10 */  addu       $t2, $fp, $t0
/* 00409e14 */  lw         $t3, ($t2)
/* 00409e18 */  nop        
/* 00409e1c */  beq        $t1, $t3, 0x409a80
/* 00409e20 */  nop        
/* 00409e24 */  sll        $t5, $a1, 2
/* 00409e28 */  addu       $t4, $s7, $t5
/* 00409e2c */  lw         $s1, ($t4)
/* 00409e30 */  nop        
/* 00409e34 */  b          0x409a80
/* 00409e38 */  nop        
/* 00409e3c */  sra        $v0, $v0, 1
/* 00409e40 */  negu       $v1, $v0
/* 00409e44 */  sll        $v1, $v1, 2
/* 00409e48 */  addu       $s5, $s5, $v1
/* 00409e4c */  lw         $at, 4($s5)
/* 00409e50 */  addiu      $t6, $gp, -0x7a74
/* 00409e54 */  lui        $s0, 0x1000
/* 00409e58 */  addu       $s0, $s0, $a0
/* 00409e5c */  sw         $at, ($t6)
/* 00409e60 */  lw         $s0, 0x2738($s0)
/* 00409e64 */  lui        $a1, 0x1000
/* 00409e68 */  sll        $t9, $s0, 2
/* 00409e6c */  addu       $a1, $a1, $t9
/* 00409e70 */  addu       $s2, $s2, $v1
/* 00409e74 */  lw         $t7, ($s2)
/* 00409e78 */  lw         $a1, 0x26c4($a1)
/* 00409e7c */  nop        
/* 00409e80 */  addu       $s1, $a1, $t7
/* 00409e84 */  addiu      $s1, $s1, 1
/* 00409e88 */  slti       $at, $s1, 0x111
/* 00409e8c */  beqz       $at, 0x409ec0
/* 00409e90 */  sll        $t8, $a1, 2
/* 00409e94 */  sll        $t0, $s1, 2
/* 00409e98 */  addu       $t2, $s7, $t0
/* 00409e9c */  lw         $s1, ($t2)
/* 00409ea0 */  nop        
/* 00409ea4 */  sll        $t3, $s1, 2
/* 00409ea8 */  addu       $t5, $fp, $t3
/* 00409eac */  lw         $t4, ($t5)
/* 00409eb0 */  negu       $t1, $s0
/* 00409eb4 */  beq        $t1, $t4, 0x409ecc
/* 00409eb8 */  nop        
/* 00409ebc */  sll        $t8, $a1, 2
/* 00409ec0 */  addu       $t6, $s7, $t8
/* 00409ec4 */  lw         $s1, ($t6)
/* 00409ec8 */  nop        
/* 00409ecc */  sw         $s1, -0x7a64($gp)                        # .sbss @ 0x1000430c
/* 00409ed0 */  sw         $s2, -0x7a68($gp)                        # .sbss @ 0x10004308
/* 00409ed4 */  b          0x40a380
/* 00409ed8 */  sw         $s5, -0x7a6c($gp)                        # .sbss @ 0x10004304
/* 00409edc */  lwc1       $f12, -0xc($s3)
/* 00409ee0 */  lwc1       $f14, -8($s3)
/* 00409ee4 */  lw         $a2, -4($s3)
/* 00409ee8 */  jal        0x405f9c                                 # mat4_set_translate
/* 00409eec */  nop        
/* 00409ef0 */  b          0x409a70
/* 00409ef4 */  nop        
/* 00409ef8 */  lw         $a0, -4($s3)
/* 00409efc */  jal        0x405f00                                 # set_initial_position
/* 00409f00 */  nop        
/* 00409f04 */  b          0x409a70
/* 00409f08 */  nop        
/* 00409f0c */  lwc1       $f12, -0xc($s3)
/* 00409f10 */  lwc1       $f14, -8($s3)
/* 00409f14 */  lw         $a2, -4($s3)
/* 00409f18 */  jal        0x406054                                 # mat4_set_rotate_x
/* 00409f1c */  nop        
/* 00409f20 */  b          0x409a70
/* 00409f24 */  nop        
/* 00409f28 */  lw         $a0, -4($s3)
/* 00409f2c */  jal        0x4065e0                                 # build_view_matrix
/* 00409f30 */  nop        
/* 00409f34 */  lw         $a0, -4($s3)
/* 00409f38 */  jal        0x408074
/* 00409f3c */  nop        
/* 00409f40 */  b          0x409a70
/* 00409f44 */  nop        
/* 00409f48 */  lw         $a0, -4($s3)
/* 00409f4c */  jal        0x406b90                                 # apply_transforms
/* 00409f50 */  nop        
/* 00409f54 */  lw         $a0, -4($s3)
/* 00409f58 */  jal        0x408074
/* 00409f5c */  nop        
/* 00409f60 */  b          0x409a70
/* 00409f64 */  nop        
/* 00409f68 */  lw         $a0, -4($s3)
/* 00409f6c */  jal        0x407068                                 # apply_material_transforms
/* 00409f70 */  nop        
/* 00409f74 */  lw         $a0, -4($s3)
/* 00409f78 */  jal        0x408074
/* 00409f7c */  nop        
/* 00409f80 */  b          0x409a70
/* 00409f84 */  nop        
/* 00409f88 */  lwc1       $f12, -0xc($s3)
/* 00409f8c */  lwc1       $f14, -8($s3)
/* 00409f90 */  lw         $a2, -4($s3)
/* 00409f94 */  jal        0x406110                                 # mat4_set_rotate_y
/* 00409f98 */  nop        
/* 00409f9c */  b          0x409a70
/* 00409fa0 */  nop        
/* 00409fa4 */  lw         $a0, -4($s3)
/* 00409fa8 */  jal        0x407a8c                                 # main_init_1
/* 00409fac */  nop        
/* 00409fb0 */  lw         $a0, -4($s3)
/* 00409fb4 */  jal        0x408074
/* 00409fb8 */  nop        
/* 00409fbc */  b          0x409a70
/* 00409fc0 */  nop        
/* 00409fc4 */  lw         $a0, -4($s3)
/* 00409fc8 */  jal        0x407b6c                                 # main_init_2
/* 00409fcc */  nop        
/* 00409fd0 */  lw         $a0, -4($s3)
/* 00409fd4 */  jal        0x408074
/* 00409fd8 */  nop        
/* 00409fdc */  b          0x409a70
/* 00409fe0 */  nop        
/* 00409fe4 */  jal        0x40a400
/* 00409fe8 */  nop        
/* 00409fec */  lw         $a1, ($s3)
/* 00409ff0 */  move       $s0, $v0
/* 00409ff4 */  jal        0x40a6d4
/* 00409ff8 */  move       $a0, $v0
/* 00409ffc */  b          0x409a70
/* 0040a000 */  sw         $s0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a004 */  lw         $a0, -4($s3)
/* 0040a008 */  lw         $a1, ($s3)
/* 0040a00c */  jal        0x40a6d4
/* 0040a010 */  nop        
/* 0040a014 */  lw         $t9, -4($s3)
/* 0040a018 */  b          0x409a70
/* 0040a01c */  sw         $t9, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a020 */  jal        0x40a400
/* 0040a024 */  nop        
/* 0040a028 */  lw         $a1, ($s3)
/* 0040a02c */  move       $s0, $v0
/* 0040a030 */  jal        0x40a6d4
/* 0040a034 */  move       $a0, $v0
/* 0040a038 */  b          0x409a70
/* 0040a03c */  sw         $s0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a040 */  jal        0x40a400
/* 0040a044 */  nop        
/* 0040a048 */  lw         $a1, -4($s3)
/* 0040a04c */  move       $s0, $v0
/* 0040a050 */  jal        0x40a6d4
/* 0040a054 */  move       $a0, $v0
/* 0040a058 */  lw         $a1, ($s3)
/* 0040a05c */  jal        0x40a6d4
/* 0040a060 */  move       $a0, $s0
/* 0040a064 */  b          0x409a70
/* 0040a068 */  sw         $s0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a06c */  jal        0x40a400
/* 0040a070 */  nop        
/* 0040a074 */  lw         $a1, ($s3)
/* 0040a078 */  move       $s0, $v0
/* 0040a07c */  jal        0x40a6d4
/* 0040a080 */  move       $a0, $v0
/* 0040a084 */  b          0x409a70
/* 0040a088 */  sw         $s0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a08c */  jal        0x40a400
/* 0040a090 */  nop        
/* 0040a094 */  lw         $a1, -4($s3)
/* 0040a098 */  move       $s0, $v0
/* 0040a09c */  jal        0x40a6d4
/* 0040a0a0 */  move       $a0, $v0
/* 0040a0a4 */  lw         $a1, ($s3)
/* 0040a0a8 */  jal        0x40a6d4
/* 0040a0ac */  move       $a0, $s0
/* 0040a0b0 */  b          0x409a70
/* 0040a0b4 */  sw         $s0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a0b8 */  lw         $a0, -4($s3)
/* 0040a0bc */  lw         $a1, ($s3)
/* 0040a0c0 */  jal        0x40a6d4
/* 0040a0c4 */  nop        
/* 0040a0c8 */  lw         $t7, -4($s3)
/* 0040a0cc */  b          0x409a70
/* 0040a0d0 */  sw         $t7, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a0d4 */  lw         $a0, -8($s3)
/* 0040a0d8 */  lw         $a1, -4($s3)
/* 0040a0dc */  jal        0x40a6d4
/* 0040a0e0 */  nop        
/* 0040a0e4 */  lw         $a0, -8($s3)
/* 0040a0e8 */  lw         $a1, ($s3)
/* 0040a0ec */  jal        0x40a6d4
/* 0040a0f0 */  nop        
/* 0040a0f4 */  lw         $t0, -8($s3)
/* 0040a0f8 */  b          0x409a70
/* 0040a0fc */  sw         $t0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a100 */  lw         $t2, ($s3)
/* 0040a104 */  b          0x409a70
/* 0040a108 */  sw         $t2, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a10c */  lw         $t3, ($s3)
/* 0040a110 */  b          0x409a70
/* 0040a114 */  sw         $t3, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a118 */  lw         $a1, -4($s3)
/* 0040a11c */  jal        0x407c44
/* 0040a120 */  addiu      $a0, $zero, 0x110
/* 0040a124 */  b          0x409a70
/* 0040a128 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a12c */  lw         $a1, -4($s3)
/* 0040a130 */  jal        0x407c44
/* 0040a134 */  addiu      $a0, $zero, 0x103
/* 0040a138 */  b          0x409a70
/* 0040a13c */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a140 */  lw         $a1, -4($s3)
/* 0040a144 */  jal        0x407c44
/* 0040a148 */  addiu      $a0, $zero, 0x107
/* 0040a14c */  b          0x409a70
/* 0040a150 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a154 */  lw         $a0, -0xc($s3)
/* 0040a158 */  lw         $a1, -4($s3)
/* 0040a15c */  jal        0x407c44
/* 0040a160 */  nop        
/* 0040a164 */  b          0x409a70
/* 0040a168 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a16c */  lwc1       $f12, -0x10($s3)
/* 0040a170 */  lwc1       $f14, -0xc($s3)
/* 0040a174 */  lw         $a2, -8($s3)
/* 0040a178 */  lw         $a3, -4($s3)
/* 0040a17c */  jal        0x4063a0                                 # mat4_mul
/* 0040a180 */  nop        
/* 0040a184 */  addiu      $a0, $zero, 0x10c
/* 0040a188 */  jal        0x407c44
/* 0040a18c */  move       $a1, $v0
/* 0040a190 */  b          0x409a70
/* 0040a194 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a198 */  lwc1       $f12, -4($s3)
/* 0040a19c */  nop        
/* 0040a1a0 */  mfc1       $a2, $f12
/* 0040a1a4 */  jal        0x406468                                 # mat4_transform_point
/* 0040a1a8 */  mov.s      $f14, $f12
/* 0040a1ac */  addiu      $a0, $zero, 0x10d
/* 0040a1b0 */  jal        0x407c44
/* 0040a1b4 */  move       $a1, $v0
/* 0040a1b8 */  b          0x409a70
/* 0040a1bc */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a1c0 */  lwc1       $f12, -0xc($s3)
/* 0040a1c4 */  lwc1       $f14, -8($s3)
/* 0040a1c8 */  lw         $a2, -4($s3)
/* 0040a1cc */  jal        0x406524                                 # mat4_mul2
/* 0040a1d0 */  nop        
/* 0040a1d4 */  addiu      $a0, $zero, 0x10f
/* 0040a1d8 */  jal        0x407c44
/* 0040a1dc */  move       $a1, $v0
/* 0040a1e0 */  b          0x409a70
/* 0040a1e4 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a1e8 */  addiu      $t5, $zero, 0x103
/* 0040a1ec */  b          0x409a70
/* 0040a1f0 */  sw         $t5, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a1f4 */  addiu      $t1, $zero, 0x104
/* 0040a1f8 */  b          0x409a70
/* 0040a1fc */  sw         $t1, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a200 */  addiu      $t4, $zero, 0x111
/* 0040a204 */  b          0x409a70
/* 0040a208 */  sw         $t4, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a20c */  addiu      $t8, $zero, 0x107
/* 0040a210 */  b          0x409a70
/* 0040a214 */  sw         $t8, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a218 */  addiu      $t6, $zero, 0x109
/* 0040a21c */  b          0x409a70
/* 0040a220 */  sw         $t6, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a224 */  addiu      $t9, $zero, 0x10a
/* 0040a228 */  b          0x409a70
/* 0040a22c */  sw         $t9, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a230 */  addiu      $t7, $zero, 0x10b
/* 0040a234 */  b          0x409a70
/* 0040a238 */  sw         $t7, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a23c */  addiu      $t0, $zero, 0x110
/* 0040a240 */  b          0x409a70
/* 0040a244 */  sw         $t0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a248 */  lw         $a0, -4($s3)
/* 0040a24c */  jal        0x4061d0                                 # mat4_set_rotate_z
/* 0040a250 */  nop        
/* 0040a254 */  lw         $a0, -4($s3)
/* 0040a258 */  jal        0x4081a4
/* 0040a25c */  nop        
/* 0040a260 */  b          0x409a70
/* 0040a264 */  nop        
/* 0040a268 */  jal        0x40a400
/* 0040a26c */  nop        
/* 0040a270 */  lw         $a1, ($s3)
/* 0040a274 */  move       $s0, $v0
/* 0040a278 */  jal        0x40a6d4
/* 0040a27c */  move       $a0, $v0
/* 0040a280 */  b          0x409a70
/* 0040a284 */  sw         $s0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a288 */  lw         $a0, -4($s3)
/* 0040a28c */  lw         $a1, ($s3)
/* 0040a290 */  jal        0x40a6d4
/* 0040a294 */  nop        
/* 0040a298 */  lw         $t2, -4($s3)
/* 0040a29c */  b          0x409a70
/* 0040a2a0 */  sw         $t2, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a2a4 */  lw         $a1, -0xc($s3)
/* 0040a2a8 */  lw         $a2, -8($s3)
/* 0040a2ac */  lw         $a3, -4($s3)
/* 0040a2b0 */  jal        0x408124
/* 0040a2b4 */  addiu      $a0, $zero, 0x113
/* 0040a2b8 */  b          0x409a70
/* 0040a2bc */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a2c0 */  lw         $a1, -0xc($s3)
/* 0040a2c4 */  lw         $a2, -8($s3)
/* 0040a2c8 */  lw         $a3, -4($s3)
/* 0040a2cc */  jal        0x408124
/* 0040a2d0 */  addiu      $a0, $zero, 0x112
/* 0040a2d4 */  b          0x409a70
/* 0040a2d8 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a2dc */  lw         $a1, -4($s3)
/* 0040a2e0 */  jal        0x4080c4
/* 0040a2e4 */  addiu      $a0, $zero, 0x115
/* 0040a2e8 */  b          0x409a70
/* 0040a2ec */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a2f0 */  lw         $a1, -4($s3)
/* 0040a2f4 */  jal        0x4080c4
/* 0040a2f8 */  addiu      $a0, $zero, 0x116
/* 0040a2fc */  b          0x409a70
/* 0040a300 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a304 */  lw         $a1, -4($s3)
/* 0040a308 */  jal        0x4080c4
/* 0040a30c */  addiu      $a0, $zero, 0x114
/* 0040a310 */  b          0x409a70
/* 0040a314 */  sw         $v0, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a318 */  lw         $t3, ($s3)
/* 0040a31c */  b          0x409a70
/* 0040a320 */  sw         $t3, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a324 */  lw         $t5, ($s3)
/* 0040a328 */  nop        
/* 0040a32c */  negu       $t1, $t5
/* 0040a330 */  b          0x409a70
/* 0040a334 */  sw         $t1, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a338 */  lwc1       $f4, ($s3)
/* 0040a33c */  b          0x409a70
/* 0040a340 */  swc1       $f4, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a344 */  lwc1       $f6, ($s3)
/* 0040a348 */  nop        
/* 0040a34c */  neg.s      $f8, $f6
/* 0040a350 */  b          0x409a70
/* 0040a354 */  swc1       $f8, -0x7a74($gp)                        # .sbss @ 0x100042fc
/* 0040a358 */  lwc1       $f10, ($s3)
/* 0040a35c */  b          0x409a70
/* 0040a360 */  swc1       $f10, -0x7a74($gp)                       # .sbss @ 0x100042fc
/* 0040a364 */  lw         $t4, ($s3)
/* 0040a368 */  nop        
/* 0040a36c */  mtc1       $t4, $f16
/* 0040a370 */  nop        
/* 0040a374 */  cvt.s.w    $f18, $f16
/* 0040a378 */  b          0x409a70
/* 0040a37c */  swc1       $f18, -0x7a74($gp)                       # .sbss @ 0x100042fc
/* 0040a380 */  lw         $t8, -0x7a60($gp)                        # .sbss @ 0x10004310
/* 0040a384 */  nop        
/* 0040a388 */  addiu      $t6, $t8, -0x10
/* 0040a38c */  sltiu      $at, $t6, 0x30
/* 0040a390 */  beqz       $at, 0x409a70
/* 0040a394 */  nop        
/* 0040a398 */  sll        $t6, $t6, 2
/* 0040a39c */  lui        $at, 0x1000
/* 0040a3a0 */  addu       $at, $at, $t6
/* 0040a3a4 */  lw         $t6, 0xa0($at)
/* 0040a3a8 */  nop        
/* 0040a3ac */  jr         $t6
/* 0040a3b0 */  nop        
/* 0040a3b4 */  lw         $ra, 0x3c($sp)
/* 0040a3b8 */  lw         $s0, 0x18($sp)
/* 0040a3bc */  lw         $s1, 0x1c($sp)
/* 0040a3c0 */  lw         $s2, 0x20($sp)
/* 0040a3c4 */  lw         $s3, 0x24($sp)
/* 0040a3c8 */  lw         $s4, 0x28($sp)
/* 0040a3cc */  lw         $s5, 0x2c($sp)
/* 0040a3d0 */  lw         $s6, 0x30($sp)
/* 0040a3d4 */  lw         $s7, 0x34($sp)
/* 0040a3d8 */  lw         $fp, 0x38($sp)
/* 0040a3dc */  jr         $ra
/* 0040a3e0 */  addiu      $sp, $sp, 0x40
/* 0040a3e4 */  nop        
/* 0040a3e8 */  nop        
/* 0040a3ec */  nop        
/* 0040a3f0 */  jr         $ra
/* 0040a3f4 */  nop        
/* 0040a3f8 */  jr         $ra
/* 0040a3fc */  nop        
/* 0040a400 */  addiu      $sp, $sp, -0x20
/* 0040a404 */  sw         $ra, 0x14($sp)
/* 0040a408 */  jal        0xf801208                                # free
/* 0040a40c */  addiu      $a0, $zero, 0xc
/* 0040a410 */  bnez       $v0, 0x40a42c
/* 0040a414 */  move       $a1, $v0
/* 0040a418 */  lw         $a0, -0x7c30($gp)                        # .sdata @ 0x10004140
/* 0040a41c */  jal        0x4092d4
/* 0040a420 */  sw         $a1, 0x18($sp)
/* 0040a424 */  lw         $a1, 0x18($sp)
/* 0040a428 */  nop        
/* 0040a42c */  sw         $zero, 4($a1)
/* 0040a430 */  sw         $zero, 8($a1)
/* 0040a434 */  sw         $a1, 0x18($sp)
/* 0040a438 */  jal        0xf801208                                # free
/* 0040a43c */  addiu      $a0, $zero, 0x10
/* 0040a440 */  lw         $a1, 0x18($sp)
/* 0040a444 */  bnez       $v0, 0x40a468
/* 0040a448 */  move       $v1, $v0
/* 0040a44c */  lw         $a0, -0x7c30($gp)                        # .sdata @ 0x10004140
/* 0040a450 */  sw         $v1, 0x1c($sp)
/* 0040a454 */  jal        0x4092d4
/* 0040a458 */  sw         $a1, 0x18($sp)
/* 0040a45c */  lw         $v1, 0x1c($sp)
/* 0040a460 */  lw         $a1, 0x18($sp)
/* 0040a464 */  nop        
/* 0040a468 */  sw         $v1, ($v1)
/* 0040a46c */  sw         $v1, 4($v1)
/* 0040a470 */  sw         $zero, 8($v1)
/* 0040a474 */  sw         $zero, 0xc($v1)
/* 0040a478 */  sw         $v1, ($a1)
/* 0040a47c */  lw         $ra, 0x14($sp)
/* 0040a480 */  addiu      $sp, $sp, 0x20
/* 0040a484 */  jr         $ra
/* 0040a488 */  move       $v0, $a1
/* 0040a48c */  addiu      $sp, $sp, -0x28
/* 0040a490 */  sw         $a0, 0x28($sp)
/* 0040a494 */  lw         $t6, 0x28($sp)
/* 0040a498 */  sw         $ra, 0x24($sp)
/* 0040a49c */  sw         $s3, 0x20($sp)
/* 0040a4a0 */  sw         $s2, 0x1c($sp)
/* 0040a4a4 */  sw         $s1, 0x18($sp)
/* 0040a4a8 */  sw         $s0, 0x14($sp)
/* 0040a4ac */  lw         $s3, ($t6)
/* 0040a4b0 */  move       $s1, $zero
/* 0040a4b4 */  lw         $s0, ($s3)
/* 0040a4b8 */  nop        
/* 0040a4bc */  bne        $s0, $s3, 0x40a4d0
/* 0040a4c0 */  addiu      $s2, $zero, -1
/* 0040a4c4 */  b          0x40a510
/* 0040a4c8 */  addiu      $s2, $zero, -1
/* 0040a4cc */  addiu      $s2, $zero, -1
/* 0040a4d0 */  beqz       $s1, 0x40a4fc
/* 0040a4d4 */  nop        
/* 0040a4d8 */  lw         $t7, 0xc($s1)
/* 0040a4dc */  nop        
/* 0040a4e0 */  bne        $s2, $t7, 0x40a4f4
/* 0040a4e4 */  nop        
/* 0040a4e8 */  lw         $a0, 8($s1)
/* 0040a4ec */  jal        0x40a48c
/* 0040a4f0 */  nop        
/* 0040a4f4 */  jal        0xf801200                                # malloc
/* 0040a4f8 */  move       $a0, $s1
/* 0040a4fc */  move       $s1, $s0
/* 0040a500 */  lw         $s0, ($s0)
/* 0040a504 */  nop        
/* 0040a508 */  bne        $s0, $s3, 0x40a4d0
/* 0040a50c */  nop        
/* 0040a510 */  beqz       $s1, 0x40a53c
/* 0040a514 */  nop        
/* 0040a518 */  lw         $t8, 0xc($s1)
/* 0040a51c */  nop        
/* 0040a520 */  bne        $s2, $t8, 0x40a534
/* 0040a524 */  nop        
/* 0040a528 */  lw         $a0, 8($s1)
/* 0040a52c */  jal        0x40a48c
/* 0040a530 */  nop        
/* 0040a534 */  jal        0xf801200                                # malloc
/* 0040a538 */  move       $a0, $s1
/* 0040a53c */  jal        0xf801200                                # malloc
/* 0040a540 */  move       $a0, $s3
/* 0040a544 */  lw         $a0, 0x28($sp)
/* 0040a548 */  jal        0xf801200                                # malloc
/* 0040a54c */  nop        
/* 0040a550 */  lw         $ra, 0x24($sp)
/* 0040a554 */  lw         $s0, 0x14($sp)
/* 0040a558 */  lw         $s1, 0x18($sp)
/* 0040a55c */  lw         $s2, 0x1c($sp)
/* 0040a560 */  lw         $s3, 0x20($sp)
/* 0040a564 */  jr         $ra
/* 0040a568 */  addiu      $sp, $sp, 0x28
/* 0040a56c */  nop        
/* 0040a570 */  addiu      $sp, $sp, -0x28
/* 0040a574 */  sw         $ra, 0x14($sp)
/* 0040a578 */  sw         $a1, 0x2c($sp)
/* 0040a57c */  move       $a2, $a0
/* 0040a580 */  lw         $v1, ($a2)
/* 0040a584 */  lw         $a0, -0x7c20($gp)                        # .sdata @ 0x10004150
/* 0040a588 */  lw         $a3, ($v1)
/* 0040a58c */  sw         $a2, 0x28($sp)
/* 0040a590 */  sw         $v1, 0x24($sp)
/* 0040a594 */  addiu      $a1, $zero, 0x10
/* 0040a598 */  jal        0x40adf0
/* 0040a59c */  sw         $a3, 0x18($sp)
/* 0040a5a0 */  lw         $v1, 0x24($sp)
/* 0040a5a4 */  lw         $a2, 0x28($sp)
/* 0040a5a8 */  lw         $a3, 0x18($sp)
/* 0040a5ac */  lw         $t6, 0x2c($sp)
/* 0040a5b0 */  sw         $zero, 0xc($v0)
/* 0040a5b4 */  sw         $v1, 4($v0)
/* 0040a5b8 */  sw         $a3, ($v0)
/* 0040a5bc */  sw         $t6, 8($v0)
/* 0040a5c0 */  sw         $v0, ($v1)
/* 0040a5c4 */  sw         $v0, 4($a3)
/* 0040a5c8 */  lw         $t7, 8($a2)
/* 0040a5cc */  nop        
/* 0040a5d0 */  addiu      $t8, $t7, 1
/* 0040a5d4 */  sw         $t8, 8($a2)
/* 0040a5d8 */  lw         $ra, 0x14($sp)
/* 0040a5dc */  addiu      $sp, $sp, 0x28
/* 0040a5e0 */  jr         $ra
/* 0040a5e4 */  nop        
/* 0040a5e8 */  addiu      $sp, $sp, -0x28
/* 0040a5ec */  sw         $ra, 0x14($sp)
/* 0040a5f0 */  sw         $a1, 0x2c($sp)
/* 0040a5f4 */  move       $a3, $a0
/* 0040a5f8 */  lw         $t6, 8($a3)
/* 0040a5fc */  nop        
/* 0040a600 */  slt        $at, $t6, $a2
/* 0040a604 */  beqz       $at, 0x40a614
/* 0040a608 */  nop        
/* 0040a60c */  b          0x40a6c4
/* 0040a610 */  move       $v0, $zero
/* 0040a614 */  lw         $a0, ($a3)
/* 0040a618 */  move       $v1, $zero
/* 0040a61c */  blez       $a2, 0x40a66c
/* 0040a620 */  move       $v0, $a0
/* 0040a624 */  andi       $a0, $a2, 3
/* 0040a628 */  beqz       $a0, 0x40a648
/* 0040a62c */  nop        
/* 0040a630 */  lw         $v0, ($v0)
/* 0040a634 */  addiu      $v1, $v1, 1
/* 0040a638 */  bne        $a0, $v1, 0x40a630
/* 0040a63c */  nop        
/* 0040a640 */  beq        $v1, $a2, 0x40a66c
/* 0040a644 */  nop        
/* 0040a648 */  lw         $v0, ($v0)
/* 0040a64c */  addiu      $v1, $v1, 4
/* 0040a650 */  lw         $v0, ($v0)
/* 0040a654 */  nop        
/* 0040a658 */  lw         $v0, ($v0)
/* 0040a65c */  nop        
/* 0040a660 */  lw         $v0, ($v0)
/* 0040a664 */  bne        $v1, $a2, 0x40a648
/* 0040a668 */  nop        
/* 0040a66c */  lw         $a2, ($v0)
/* 0040a670 */  move       $v1, $v0
/* 0040a674 */  lw         $a0, -0x7c1c($gp)                        # .sdata @ 0x10004154
/* 0040a678 */  sw         $v1, 0x1c($sp)
/* 0040a67c */  sw         $a3, 0x28($sp)
/* 0040a680 */  addiu      $a1, $zero, 0x10
/* 0040a684 */  jal        0x40adf0
/* 0040a688 */  sw         $a2, 0x18($sp)
/* 0040a68c */  lw         $v1, 0x1c($sp)
/* 0040a690 */  lw         $a2, 0x18($sp)
/* 0040a694 */  lw         $a3, 0x28($sp)
/* 0040a698 */  lw         $t7, 0x2c($sp)
/* 0040a69c */  sw         $zero, 0xc($v0)
/* 0040a6a0 */  sw         $v1, 4($v0)
/* 0040a6a4 */  sw         $a2, ($v0)
/* 0040a6a8 */  sw         $t7, 8($v0)
/* 0040a6ac */  sw         $v0, ($v1)
/* 0040a6b0 */  sw         $v0, 4($a2)
/* 0040a6b4 */  lw         $t8, 8($a3)
/* 0040a6b8 */  addiu      $v0, $zero, 1
/* 0040a6bc */  addiu      $t9, $t8, 1
/* 0040a6c0 */  sw         $t9, 8($a3)
/* 0040a6c4 */  lw         $ra, 0x14($sp)
/* 0040a6c8 */  addiu      $sp, $sp, 0x28
/* 0040a6cc */  jr         $ra
/* 0040a6d0 */  nop        
/* 0040a6d4 */  addiu      $sp, $sp, -0x28
/* 0040a6d8 */  sw         $ra, 0x14($sp)
/* 0040a6dc */  sw         $a1, 0x2c($sp)
/* 0040a6e0 */  move       $a2, $a0
/* 0040a6e4 */  lw         $v1, ($a2)
/* 0040a6e8 */  lw         $a0, -0x7c18($gp)                        # .sdata @ 0x10004158
/* 0040a6ec */  lw         $a3, 4($v1)
/* 0040a6f0 */  sw         $a2, 0x28($sp)
/* 0040a6f4 */  sw         $v1, 0x24($sp)
/* 0040a6f8 */  addiu      $a1, $zero, 0x10
/* 0040a6fc */  jal        0x40adf0
/* 0040a700 */  sw         $a3, 0x1c($sp)
/* 0040a704 */  lw         $v1, 0x24($sp)
/* 0040a708 */  lw         $a2, 0x28($sp)
/* 0040a70c */  lw         $a3, 0x1c($sp)
/* 0040a710 */  lw         $t6, 0x2c($sp)
/* 0040a714 */  sw         $zero, 0xc($v0)
/* 0040a718 */  sw         $v1, ($v0)
/* 0040a71c */  sw         $a3, 4($v0)
/* 0040a720 */  sw         $t6, 8($v0)
/* 0040a724 */  sw         $v0, ($a3)
/* 0040a728 */  sw         $v0, 4($v1)
/* 0040a72c */  lw         $t7, 8($a2)
/* 0040a730 */  nop        
/* 0040a734 */  addiu      $t8, $t7, 1
/* 0040a738 */  sw         $t8, 8($a2)
/* 0040a73c */  lw         $ra, 0x14($sp)
/* 0040a740 */  addiu      $sp, $sp, 0x28
/* 0040a744 */  jr         $ra
/* 0040a748 */  nop        
/* 0040a74c */  addiu      $sp, $sp, -0x18
/* 0040a750 */  sw         $ra, 0x14($sp)
/* 0040a754 */  move       $a2, $a0
/* 0040a758 */  lw         $v0, ($a2)
/* 0040a75c */  nop        
/* 0040a760 */  lw         $v1, ($v0)
/* 0040a764 */  sw         $a1, 8($v0)
/* 0040a768 */  lw         $t6, 8($v1)
/* 0040a76c */  nop        
/* 0040a770 */  beq        $a1, $t6, 0x40a790
/* 0040a774 */  nop        
/* 0040a778 */  lw         $v1, ($v1)
/* 0040a77c */  nop        
/* 0040a780 */  lw         $t7, 8($v1)
/* 0040a784 */  nop        
/* 0040a788 */  bne        $a1, $t7, 0x40a778
/* 0040a78c */  nop        
/* 0040a790 */  beq        $v1, $v0, 0x40a7ec
/* 0040a794 */  move       $v0, $zero
/* 0040a798 */  lw         $v0, 4($v1)
/* 0040a79c */  lw         $a0, ($v1)
/* 0040a7a0 */  nop        
/* 0040a7a4 */  sw         $a0, ($v0)
/* 0040a7a8 */  sw         $v0, 4($a0)
/* 0040a7ac */  lw         $t8, 4($a2)
/* 0040a7b0 */  nop        
/* 0040a7b4 */  bne        $v1, $t8, 0x40a7c4
/* 0040a7b8 */  move       $a0, $v1
/* 0040a7bc */  sw         $zero, 4($a2)
/* 0040a7c0 */  move       $a0, $v1
/* 0040a7c4 */  jal        0xf801200                                # malloc
/* 0040a7c8 */  sw         $a2, 0x18($sp)
/* 0040a7cc */  lw         $a2, 0x18($sp)
/* 0040a7d0 */  addiu      $v0, $zero, 1
/* 0040a7d4 */  lw         $t9, 8($a2)
/* 0040a7d8 */  nop        
/* 0040a7dc */  addiu      $t0, $t9, -1
/* 0040a7e0 */  b          0x40a7ec
/* 0040a7e4 */  sw         $t0, 8($a2)
/* 0040a7e8 */  move       $v0, $zero
/* 0040a7ec */  lw         $ra, 0x14($sp)
/* 0040a7f0 */  addiu      $sp, $sp, 0x18
/* 0040a7f4 */  jr         $ra
/* 0040a7f8 */  nop        
/* 0040a7fc */  addiu      $sp, $sp, -0x18
/* 0040a800 */  sw         $ra, 0x14($sp)
/* 0040a804 */  blez       $a1, 0x40a820
/* 0040a808 */  move       $a2, $a0
/* 0040a80c */  lw         $t6, 8($a2)
/* 0040a810 */  nop        
/* 0040a814 */  slt        $at, $t6, $a1
/* 0040a818 */  beqz       $at, 0x40a828
/* 0040a81c */  nop        
/* 0040a820 */  b          0x40a8c4
/* 0040a824 */  move       $v0, $zero
/* 0040a828 */  lw         $a0, ($a2)
/* 0040a82c */  blez       $a1, 0x40a87c
/* 0040a830 */  move       $v0, $zero
/* 0040a834 */  andi       $v1, $a1, 3
/* 0040a838 */  beqz       $v1, 0x40a858
/* 0040a83c */  nop        
/* 0040a840 */  lw         $a0, ($a0)
/* 0040a844 */  addiu      $v0, $v0, 1
/* 0040a848 */  bne        $v1, $v0, 0x40a840
/* 0040a84c */  nop        
/* 0040a850 */  beq        $v0, $a1, 0x40a87c
/* 0040a854 */  nop        
/* 0040a858 */  lw         $a0, ($a0)
/* 0040a85c */  addiu      $v0, $v0, 4
/* 0040a860 */  lw         $a0, ($a0)
/* 0040a864 */  nop        
/* 0040a868 */  lw         $a0, ($a0)
/* 0040a86c */  nop        
/* 0040a870 */  lw         $a0, ($a0)
/* 0040a874 */  bne        $v0, $a1, 0x40a858
/* 0040a878 */  nop        
/* 0040a87c */  lw         $v0, 4($a0)
/* 0040a880 */  lw         $v1, ($a0)
/* 0040a884 */  nop        
/* 0040a888 */  sw         $v1, ($v0)
/* 0040a88c */  sw         $v0, 4($v1)
/* 0040a890 */  lw         $t7, 4($a2)
/* 0040a894 */  nop        
/* 0040a898 */  bne        $a0, $t7, 0x40a8a4
/* 0040a89c */  nop        
/* 0040a8a0 */  sw         $zero, 4($a2)
/* 0040a8a4 */  jal        0xf801200                                # malloc
/* 0040a8a8 */  sw         $a2, 0x18($sp)
/* 0040a8ac */  lw         $a2, 0x18($sp)
/* 0040a8b0 */  addiu      $v0, $zero, 1
/* 0040a8b4 */  lw         $t8, 8($a2)
/* 0040a8b8 */  nop        
/* 0040a8bc */  addiu      $t9, $t8, -1
/* 0040a8c0 */  sw         $t9, 8($a2)
/* 0040a8c4 */  lw         $ra, 0x14($sp)
/* 0040a8c8 */  addiu      $sp, $sp, 0x18
/* 0040a8cc */  jr         $ra
/* 0040a8d0 */  nop        
/* 0040a8d4 */  nop        
/* 0040a8d8 */  nop        
/* 0040a8dc */  nop        
/* 0040a8e0 */  lw         $v0, ($a0)
/* 0040a8e4 */  nop        
/* 0040a8e8 */  lw         $v1, ($v0)
/* 0040a8ec */  nop        
/* 0040a8f0 */  bne        $v1, $v0, 0x40a904
/* 0040a8f4 */  nop        
/* 0040a8f8 */  sw         $zero, 4($a0)
/* 0040a8fc */  b          0x40a910
/* 0040a900 */  move       $a1, $zero
/* 0040a904 */  sw         $v1, 4($a0)
/* 0040a908 */  lw         $a1, 8($v1)
/* 0040a90c */  nop        
/* 0040a910 */  jr         $ra
/* 0040a914 */  move       $v0, $a1
/* 0040a918 */  lw         $v0, 4($a0)
/* 0040a91c */  move       $v1, $zero
/* 0040a920 */  beqz       $v0, 0x40a944
/* 0040a924 */  nop        
/* 0040a928 */  lw         $v0, ($v0)
/* 0040a92c */  lw         $t6, ($a0)
/* 0040a930 */  nop        
/* 0040a934 */  beq        $v0, $t6, 0x40a944
/* 0040a938 */  nop        
/* 0040a93c */  lw         $v1, 8($v0)
/* 0040a940 */  sw         $v0, 4($a0)
/* 0040a944 */  jr         $ra
/* 0040a948 */  move       $v0, $v1
/* 0040a94c */  lw         $v0, 4($a0)
/* 0040a950 */  move       $v1, $zero
/* 0040a954 */  beqz       $v0, 0x40a978
/* 0040a958 */  nop        
/* 0040a95c */  lw         $v0, 4($v0)
/* 0040a960 */  lw         $t6, ($a0)
/* 0040a964 */  nop        
/* 0040a968 */  beq        $v0, $t6, 0x40a978
/* 0040a96c */  nop        
/* 0040a970 */  lw         $v1, 8($v0)
/* 0040a974 */  sw         $v0, 4($a0)
/* 0040a978 */  jr         $ra
/* 0040a97c */  move       $v0, $v1
/* 0040a980 */  lw         $v0, ($a0)
/* 0040a984 */  nop        
/* 0040a988 */  lw         $v1, 4($v0)
/* 0040a98c */  nop        
/* 0040a990 */  bne        $v1, $v0, 0x40a9a4
/* 0040a994 */  nop        
/* 0040a998 */  sw         $zero, 4($a0)
/* 0040a99c */  b          0x40a9b0
/* 0040a9a0 */  move       $a1, $zero
/* 0040a9a4 */  sw         $v1, 4($a0)
/* 0040a9a8 */  lw         $a1, 8($v1)
/* 0040a9ac */  nop        
/* 0040a9b0 */  jr         $ra
/* 0040a9b4 */  move       $v0, $a1
/* 0040a9b8 */  lw         $v0, 4($a0)
/* 0040a9bc */  nop        
/* 0040a9c0 */  bnez       $v0, 0x40a9d0
/* 0040a9c4 */  nop        
/* 0040a9c8 */  b          0x40a9d8
/* 0040a9cc */  move       $v1, $zero
/* 0040a9d0 */  lw         $v1, 8($v0)
/* 0040a9d4 */  nop        
/* 0040a9d8 */  jr         $ra
/* 0040a9dc */  move       $v0, $v1
/* 0040a9e0 */  lw         $t6, 8($a0)
/* 0040a9e4 */  nop        
/* 0040a9e8 */  slt        $at, $t6, $a1
/* 0040a9ec */  beqz       $at, 0x40a9fc
/* 0040a9f0 */  nop        
/* 0040a9f4 */  jr         $ra
/* 0040a9f8 */  move       $v0, $zero
/* 0040a9fc */  lw         $v0, ($a0)
/* 0040aa00 */  move       $a2, $zero
/* 0040aa04 */  lw         $v1, ($v0)
/* 0040aa08 */  blez       $a1, 0x40aa58
/* 0040aa0c */  nop        
/* 0040aa10 */  andi       $v0, $a1, 3
/* 0040aa14 */  beqz       $v0, 0x40aa34
/* 0040aa18 */  nop        
/* 0040aa1c */  lw         $v1, ($v1)
/* 0040aa20 */  addiu      $a2, $a2, 1
/* 0040aa24 */  bne        $v0, $a2, 0x40aa1c
/* 0040aa28 */  nop        
/* 0040aa2c */  beq        $a2, $a1, 0x40aa58
/* 0040aa30 */  nop        
/* 0040aa34 */  lw         $v1, ($v1)
/* 0040aa38 */  addiu      $a2, $a2, 4
/* 0040aa3c */  lw         $v1, ($v1)
/* 0040aa40 */  nop        
/* 0040aa44 */  lw         $v1, ($v1)
/* 0040aa48 */  nop        
/* 0040aa4c */  lw         $v1, ($v1)
/* 0040aa50 */  bne        $a2, $a1, 0x40aa34
/* 0040aa54 */  nop        
/* 0040aa58 */  sw         $v1, 4($a0)
/* 0040aa5c */  lw         $v0, 8($v1)
/* 0040aa60 */  nop        
/* 0040aa64 */  jr         $ra
/* 0040aa68 */  nop        
/* 0040aa6c */  nop        
/* 0040aa70 */  addiu      $sp, $sp, -0x28
/* 0040aa74 */  sw         $ra, 0x24($sp)
/* 0040aa78 */  sw         $s2, 0x20($sp)
/* 0040aa7c */  sw         $s0, 0x18($sp)
/* 0040aa80 */  sw         $s1, 0x1c($sp)
/* 0040aa84 */  jal        0x40a400
/* 0040aa88 */  sw         $a0, 0x28($sp)
/* 0040aa8c */  lw         $t6, 0x28($sp)
/* 0040aa90 */  move       $s2, $v0
/* 0040aa94 */  lw         $s1, ($t6)
/* 0040aa98 */  nop        
/* 0040aa9c */  lw         $s0, ($s1)
/* 0040aaa0 */  nop        
/* 0040aaa4 */  beq        $s0, $s1, 0x40aacc
/* 0040aaa8 */  lw         $ra, 0x24($sp)
/* 0040aaac */  lw         $a1, 8($s0)
/* 0040aab0 */  jal        0x40a6d4
/* 0040aab4 */  move       $a0, $s2
/* 0040aab8 */  lw         $s0, ($s0)
/* 0040aabc */  nop        
/* 0040aac0 */  bne        $s0, $s1, 0x40aaac
/* 0040aac4 */  nop        
/* 0040aac8 */  lw         $ra, 0x24($sp)
/* 0040aacc */  move       $v0, $s2
/* 0040aad0 */  lw         $s2, 0x20($sp)
/* 0040aad4 */  lw         $s0, 0x18($sp)
/* 0040aad8 */  lw         $s1, 0x1c($sp)
/* 0040aadc */  jr         $ra
/* 0040aae0 */  addiu      $sp, $sp, 0x28
/* 0040aae4 */  addiu      $sp, $sp, -0x28
/* 0040aae8 */  sw         $ra, 0x24($sp)
/* 0040aaec */  sw         $s2, 0x20($sp)
/* 0040aaf0 */  sw         $s0, 0x18($sp)
/* 0040aaf4 */  sw         $s1, 0x1c($sp)
/* 0040aaf8 */  jal        0x40a400
/* 0040aafc */  sw         $a0, 0x28($sp)
/* 0040ab00 */  lw         $t6, 0x28($sp)
/* 0040ab04 */  move       $s2, $v0
/* 0040ab08 */  lw         $s1, ($t6)
/* 0040ab0c */  nop        
/* 0040ab10 */  lw         $s0, ($s1)
/* 0040ab14 */  nop        
/* 0040ab18 */  beq        $s0, $s1, 0x40ab40
/* 0040ab1c */  lw         $ra, 0x24($sp)
/* 0040ab20 */  lw         $a1, 8($s0)
/* 0040ab24 */  jal        0x40a570
/* 0040ab28 */  move       $a0, $s2
/* 0040ab2c */  lw         $s0, ($s0)
/* 0040ab30 */  nop        
/* 0040ab34 */  bne        $s0, $s1, 0x40ab20
/* 0040ab38 */  nop        
/* 0040ab3c */  lw         $ra, 0x24($sp)
/* 0040ab40 */  move       $v0, $s2
/* 0040ab44 */  lw         $s2, 0x20($sp)
/* 0040ab48 */  lw         $s0, 0x18($sp)
/* 0040ab4c */  lw         $s1, 0x1c($sp)
/* 0040ab50 */  jr         $ra
/* 0040ab54 */  addiu      $sp, $sp, 0x28
/* 0040ab58 */  addiu      $sp, $sp, -0x28
/* 0040ab5c */  sw         $ra, 0x24($sp)
/* 0040ab60 */  sw         $s2, 0x20($sp)
/* 0040ab64 */  sw         $s0, 0x18($sp)
/* 0040ab68 */  sw         $s1, 0x1c($sp)
/* 0040ab6c */  sw         $a0, 0x28($sp)
/* 0040ab70 */  jal        0x40a400
/* 0040ab74 */  sw         $a1, 0x2c($sp)
/* 0040ab78 */  lw         $t6, 0x28($sp)
/* 0040ab7c */  move       $s2, $v0
/* 0040ab80 */  lw         $s1, ($t6)
/* 0040ab84 */  nop        
/* 0040ab88 */  lw         $s0, ($s1)
/* 0040ab8c */  nop        
/* 0040ab90 */  beq        $s0, $s1, 0x40abb8
/* 0040ab94 */  lw         $t7, 0x2c($sp)
/* 0040ab98 */  lw         $a1, 8($s0)
/* 0040ab9c */  jal        0x40a6d4
/* 0040aba0 */  move       $a0, $s2
/* 0040aba4 */  lw         $s0, ($s0)
/* 0040aba8 */  nop        
/* 0040abac */  bne        $s0, $s1, 0x40ab98
/* 0040abb0 */  nop        
/* 0040abb4 */  lw         $t7, 0x2c($sp)
/* 0040abb8 */  nop        
/* 0040abbc */  lw         $s1, ($t7)
/* 0040abc0 */  nop        
/* 0040abc4 */  lw         $s0, ($s1)
/* 0040abc8 */  nop        
/* 0040abcc */  beq        $s0, $s1, 0x40abf4
/* 0040abd0 */  lw         $ra, 0x24($sp)
/* 0040abd4 */  lw         $a1, 8($s0)
/* 0040abd8 */  jal        0x40a6d4
/* 0040abdc */  move       $a0, $s2
/* 0040abe0 */  lw         $s0, ($s0)
/* 0040abe4 */  nop        
/* 0040abe8 */  bne        $s0, $s1, 0x40abd4
/* 0040abec */  nop        
/* 0040abf0 */  lw         $ra, 0x24($sp)
/* 0040abf4 */  move       $v0, $s2
/* 0040abf8 */  lw         $s2, 0x20($sp)
/* 0040abfc */  lw         $s0, 0x18($sp)
/* 0040ac00 */  lw         $s1, 0x1c($sp)
/* 0040ac04 */  jr         $ra
/* 0040ac08 */  addiu      $sp, $sp, 0x28
/* 0040ac0c */  addiu      $sp, $sp, -0x28
/* 0040ac10 */  sw         $ra, 0x24($sp)
/* 0040ac14 */  sw         $s2, 0x20($sp)
/* 0040ac18 */  sw         $s0, 0x18($sp)
/* 0040ac1c */  sw         $s1, 0x1c($sp)
/* 0040ac20 */  lw         $s1, ($a0)
/* 0040ac24 */  move       $s2, $a1
/* 0040ac28 */  lw         $s0, ($s1)
/* 0040ac2c */  nop        
/* 0040ac30 */  beq        $s0, $s1, 0x40ac58
/* 0040ac34 */  lw         $ra, 0x24($sp)
/* 0040ac38 */  lw         $a0, 8($s0)
/* 0040ac3c */  jalr       $s2
/* 0040ac40 */  nop        
/* 0040ac44 */  lw         $s0, ($s0)
/* 0040ac48 */  nop        
/* 0040ac4c */  bne        $s0, $s1, 0x40ac38
/* 0040ac50 */  nop        
/* 0040ac54 */  lw         $ra, 0x24($sp)
/* 0040ac58 */  lw         $s0, 0x18($sp)
/* 0040ac5c */  lw         $s1, 0x1c($sp)
/* 0040ac60 */  lw         $s2, 0x20($sp)
/* 0040ac64 */  jr         $ra
/* 0040ac68 */  addiu      $sp, $sp, 0x28
/* 0040ac6c */  addiu      $sp, $sp, -0x30
/* 0040ac70 */  sw         $s2, 0x18($sp)
/* 0040ac74 */  sw         $s1, 0x14($sp)
/* 0040ac78 */  move       $s1, $a1
/* 0040ac7c */  move       $s2, $a2
/* 0040ac80 */  sw         $ra, 0x1c($sp)
/* 0040ac84 */  sw         $a0, 0x30($sp)
/* 0040ac88 */  move       $a0, $s1
/* 0040ac8c */  jalr       $s2
/* 0040ac90 */  move       $a1, $s1
/* 0040ac94 */  bnez       $v0, 0x40acc8
/* 0040ac98 */  lw         $t6, 0x30($sp)
/* 0040ac9c */  lui        $a0, 0x1000
/* 0040aca0 */  lui        $a1, 0x1000
/* 0040aca4 */  lw         $a2, -0x7c10($gp)                        # .sdata @ 0x10004160
/* 0040aca8 */  lui        $a3, 0x1000
/* 0040acac */  addiu      $a3, $a3, 0x2e90
/* 0040acb0 */  addiu      $a1, $a1, 0x2e80
/* 0040acb4 */  jal        0xf801150                                # fclose
/* 0040acb8 */  addiu      $a0, $a0, 0x36b4
/* 0040acbc */  b          0x40ad34
/* 0040acc0 */  move       $v0, $zero
/* 0040acc4 */  lw         $t6, 0x30($sp)
/* 0040acc8 */  sw         $s0, 0x24($sp)
/* 0040accc */  lw         $v0, ($t6)
/* 0040acd0 */  move       $a0, $s1
/* 0040acd4 */  lw         $s0, ($v0)
/* 0040acd8 */  sw         $s1, 8($v0)
/* 0040acdc */  lw         $a1, 8($s0)
/* 0040ace0 */  jalr       $s2
/* 0040ace4 */  sw         $v0, 0x2c($sp)
/* 0040ace8 */  bnez       $v0, 0x40ad10
/* 0040acec */  lw         $t7, 0x2c($sp)
/* 0040acf0 */  lw         $s0, ($s0)
/* 0040acf4 */  move       $a0, $s1
/* 0040acf8 */  lw         $a1, 8($s0)
/* 0040acfc */  jalr       $s2
/* 0040ad00 */  nop        
/* 0040ad04 */  beqz       $v0, 0x40acf0
/* 0040ad08 */  nop        
/* 0040ad0c */  lw         $t7, 0x2c($sp)
/* 0040ad10 */  nop        
/* 0040ad14 */  beq        $s0, $t7, 0x40ad2c
/* 0040ad18 */  nop        
/* 0040ad1c */  lw         $v0, 8($s0)
/* 0040ad20 */  lw         $s0, 0x24($sp)
/* 0040ad24 */  b          0x40ad38
/* 0040ad28 */  lw         $ra, 0x1c($sp)
/* 0040ad2c */  lw         $s0, 0x24($sp)
/* 0040ad30 */  move       $v0, $zero
/* 0040ad34 */  lw         $ra, 0x1c($sp)
/* 0040ad38 */  lw         $s1, 0x14($sp)
/* 0040ad3c */  lw         $s2, 0x18($sp)
/* 0040ad40 */  jr         $ra
/* 0040ad44 */  addiu      $sp, $sp, 0x30
/* 0040ad48 */  addiu      $sp, $sp, -0x28
/* 0040ad4c */  sw         $ra, 0x24($sp)
/* 0040ad50 */  sw         $s3, 0x20($sp)
/* 0040ad54 */  sw         $s2, 0x1c($sp)
/* 0040ad58 */  sw         $s1, 0x18($sp)
/* 0040ad5c */  sw         $s0, 0x14($sp)
/* 0040ad60 */  lw         $s3, ($a0)
/* 0040ad64 */  move       $s1, $a1
/* 0040ad68 */  lw         $s0, ($s3)
/* 0040ad6c */  move       $s2, $a2
/* 0040ad70 */  beq        $s0, $s3, 0x40adb0
/* 0040ad74 */  nop        
/* 0040ad78 */  lw         $a1, 8($s0)
/* 0040ad7c */  jalr       $s2
/* 0040ad80 */  move       $a0, $s1
/* 0040ad84 */  bnez       $v0, 0x40adb0
/* 0040ad88 */  nop        
/* 0040ad8c */  lw         $s0, ($s0)
/* 0040ad90 */  nop        
/* 0040ad94 */  beq        $s0, $s3, 0x40adb0
/* 0040ad98 */  nop        
/* 0040ad9c */  lw         $a1, 8($s0)
/* 0040ada0 */  jalr       $s2
/* 0040ada4 */  move       $a0, $s1
/* 0040ada8 */  beqz       $v0, 0x40ad8c
/* 0040adac */  nop        
/* 0040adb0 */  beq        $s0, $s3, 0x40adc8
/* 0040adb4 */  move       $v0, $zero
/* 0040adb8 */  lw         $v0, 8($s0)
/* 0040adbc */  b          0x40adcc
/* 0040adc0 */  lw         $ra, 0x24($sp)
/* 0040adc4 */  move       $v0, $zero
/* 0040adc8 */  lw         $ra, 0x24($sp)
/* 0040adcc */  lw         $s0, 0x14($sp)
/* 0040add0 */  lw         $s1, 0x18($sp)
/* 0040add4 */  lw         $s2, 0x1c($sp)
/* 0040add8 */  lw         $s3, 0x20($sp)
/* 0040addc */  jr         $ra
/* 0040ade0 */  addiu      $sp, $sp, 0x28
/* 0040ade4 */  lw         $v0, 8($a0)
/* 0040ade8 */  jr         $ra
/* 0040adec */  nop        
/* 0040adf0 */  addiu      $sp, $sp, -0x20
/* 0040adf4 */  sw         $ra, 0x14($sp)
/* 0040adf8 */  sw         $a0, 0x20($sp)
/* 0040adfc */  jal        0xf801208                                # free
/* 0040ae00 */  move       $a0, $a1
/* 0040ae04 */  bnez       $v0, 0x40ae38
/* 0040ae08 */  move       $v1, $v0
/* 0040ae0c */  lui        $a0, 0x1000
/* 0040ae10 */  lui        $a1, 0x1000
/* 0040ae14 */  lw         $a2, 0x20($sp)
/* 0040ae18 */  lui        $a3, 0x1000
/* 0040ae1c */  addiu      $a3, $a3, 0x2fd0
/* 0040ae20 */  addiu      $a1, $a1, 0x2fc0
/* 0040ae24 */  addiu      $a0, $a0, 0x36b4
/* 0040ae28 */  jal        0xf801150                                # fclose
/* 0040ae2c */  sw         $v1, 0x1c($sp)
/* 0040ae30 */  lw         $v1, 0x1c($sp)
/* 0040ae34 */  nop        
/* 0040ae38 */  lw         $ra, 0x14($sp)
/* 0040ae3c */  addiu      $sp, $sp, 0x20
/* 0040ae40 */  jr         $ra
/* 0040ae44 */  move       $v0, $v1
/* 0040ae48 */  nop        
/* 0040ae4c */  nop        
/* 0040ae50 */  addiu      $sp, $sp, -0x28
/* 0040ae54 */  sw         $a1, 0x2c($sp)
/* 0040ae58 */  sw         $a2, 0x30($sp)
/* 0040ae5c */  sw         $a0, 0x28($sp)
/* 0040ae60 */  sw         $ra, 0x24($sp)
/* 0040ae64 */  lw         $t6, 0x38($sp)
/* 0040ae68 */  lw         $t7, 0x3c($sp)
/* 0040ae6c */  lw         $t8, 0x40($sp)
/* 0040ae70 */  move       $v1, $a3
/* 0040ae74 */  sw         $v1, 0x10($sp)
/* 0040ae78 */  lw         $a3, 0x30($sp)
/* 0040ae7c */  lw         $a1, 0x28($sp)
/* 0040ae80 */  lw         $a2, 0x2c($sp)
/* 0040ae84 */  sw         $t6, 0x14($sp)
/* 0040ae88 */  sw         $t7, 0x18($sp)
/* 0040ae8c */  move       $a0, $zero
/* 0040ae90 */  jal        0x40aef8
/* 0040ae94 */  sw         $t8, 0x1c($sp)
/* 0040ae98 */  lw         $ra, 0x24($sp)
/* 0040ae9c */  addiu      $sp, $sp, 0x28
/* 0040aea0 */  jr         $ra
/* 0040aea4 */  nop        
/* 0040aea8 */  addiu      $sp, $sp, -0x28
/* 0040aeac */  sw         $a2, 0x30($sp)
/* 0040aeb0 */  sw         $a1, 0x2c($sp)
/* 0040aeb4 */  sw         $ra, 0x24($sp)
/* 0040aeb8 */  lw         $t6, 0x38($sp)
/* 0040aebc */  lw         $t7, 0x3c($sp)
/* 0040aec0 */  lw         $t8, 0x40($sp)
/* 0040aec4 */  move       $v1, $a3
/* 0040aec8 */  sw         $v1, 0x10($sp)
/* 0040aecc */  lw         $a3, 0x30($sp)
/* 0040aed0 */  lw         $a2, 0x2c($sp)
/* 0040aed4 */  sw         $t6, 0x14($sp)
/* 0040aed8 */  sw         $t7, 0x18($sp)
/* 0040aedc */  move       $a1, $zero
/* 0040aee0 */  jal        0x40aef8
/* 0040aee4 */  sw         $t8, 0x1c($sp)
/* 0040aee8 */  lw         $ra, 0x24($sp)
/* 0040aeec */  addiu      $sp, $sp, 0x28
/* 0040aef0 */  jr         $ra
/* 0040aef4 */  nop        
/* 0040aef8 */  addiu      $sp, $sp, -0x30
/* 0040aefc */  sw         $ra, 0x1c($sp)
/* 0040af00 */  sw         $a0, 0x30($sp)
/* 0040af04 */  sw         $s0, 0x18($sp)
/* 0040af08 */  sw         $a1, 0x34($sp)
/* 0040af0c */  sw         $a2, 0x38($sp)
/* 0040af10 */  sw         $a3, 0x3c($sp)
/* 0040af14 */  jal        0xf801208                                # free
/* 0040af18 */  addiu      $a0, $zero, 0x98
/* 0040af1c */  move       $s0, $v0
/* 0040af20 */  move       $a0, $v0
/* 0040af24 */  jal        0xf801040                                # fopen
/* 0040af28 */  addiu      $a1, $zero, 0x98
/* 0040af2c */  lw         $t6, 0x38($sp)
/* 0040af30 */  nop        
/* 0040af34 */  lbu        $t7, 1($t6)
/* 0040af38 */  nop        
/* 0040af3c */  xori       $t8, $t7, 0x2b
/* 0040af40 */  sltiu      $t8, $t8, 1
/* 0040af44 */  beqz       $t8, 0x40af60
/* 0040af48 */  sw         $t8, 0x28($sp)
/* 0040af4c */  lui        $a0, 0x1000
/* 0040af50 */  jal        0x40b640
/* 0040af54 */  addiu      $a0, $a0, 0x2fe0
/* 0040af58 */  b          0x40b4e0
/* 0040af5c */  move       $v0, $zero
/* 0040af60 */  lw         $t9, 0x38($sp)
/* 0040af64 */  addiu      $at, $zero, 0x77
/* 0040af68 */  lbu        $t0, ($t9)
/* 0040af6c */  nop        
/* 0040af70 */  bne        $t0, $at, 0x40b0d8
/* 0040af74 */  lw         $t3, 0x34($sp)
/* 0040af78 */  lw         $v1, 0x34($sp)
/* 0040af7c */  nop        
/* 0040af80 */  beqz       $v1, 0x40afd4
/* 0040af84 */  lw         $t2, 0x30($sp)
/* 0040af88 */  move       $a0, $v1
/* 0040af8c */  jal        0x40df80
/* 0040af90 */  addiu      $a1, $zero, 0x1b6
/* 0040af94 */  lw         $t1, 0x28($sp)
/* 0040af98 */  sw         $v0, 0x30($sp)
/* 0040af9c */  beqz       $t1, 0x40afcc
/* 0040afa0 */  lw         $v1, 0x34($sp)
/* 0040afa4 */  bltz       $v0, 0x40afcc
/* 0040afa8 */  lw         $v1, 0x34($sp)
/* 0040afac */  lw         $a0, 0x30($sp)
/* 0040afb0 */  jal        0x40dfa0
/* 0040afb4 */  nop        
/* 0040afb8 */  lw         $a0, 0x34($sp)
/* 0040afbc */  jal        0x40dfc0
/* 0040afc0 */  addiu      $a1, $zero, 2
/* 0040afc4 */  sw         $v0, 0x30($sp)
/* 0040afc8 */  lw         $v1, 0x34($sp)
/* 0040afcc */  nop        
/* 0040afd0 */  lw         $t2, 0x30($sp)
/* 0040afd4 */  nop        
/* 0040afd8 */  bgez       $t2, 0x40affc
/* 0040afdc */  lw         $v0, 0x40($sp)
/* 0040afe0 */  lui        $a0, 0x1000
/* 0040afe4 */  addiu      $a0, $a0, 0x3008
/* 0040afe8 */  jal        0x40b640
/* 0040afec */  move       $a1, $v1
/* 0040aff0 */  b          0x40b4e0
/* 0040aff4 */  move       $v0, $zero
/* 0040aff8 */  lw         $v0, 0x40($sp)
/* 0040affc */  addiu      $t3, $zero, 0x1da
/* 0040b000 */  sh         $t3, ($s0)
/* 0040b004 */  lw         $t4, 0x3c($sp)
/* 0040b008 */  addiu      $v1, $zero, 1
/* 0040b00c */  sh         $t4, 2($s0)
/* 0040b010 */  lw         $t5, 0x44($sp)
/* 0040b014 */  sltiu      $at, $v0, 2
/* 0040b018 */  sh         $v1, 8($s0)
/* 0040b01c */  sh         $v1, 0xa($s0)
/* 0040b020 */  bnez       $at, 0x40b034
/* 0040b024 */  sh         $t5, 6($s0)
/* 0040b028 */  lw         $t6, 0x48($sp)
/* 0040b02c */  nop        
/* 0040b030 */  sh         $t6, 8($s0)
/* 0040b034 */  sltiu      $at, $v0, 3
/* 0040b038 */  bnez       $at, 0x40b04c
/* 0040b03c */  nop        
/* 0040b040 */  lw         $t7, 0x4c($sp)
/* 0040b044 */  nop        
/* 0040b048 */  sh         $t7, 0xa($s0)
/* 0040b04c */  lhu        $t8, 0xa($s0)
/* 0040b050 */  nop        
/* 0040b054 */  bne        $v1, $t8, 0x40b078
/* 0040b058 */  addiu      $t1, $zero, 3
/* 0040b05c */  lhu        $t0, 8($s0)
/* 0040b060 */  addiu      $t9, $zero, 2
/* 0040b064 */  bne        $v1, $t0, 0x40b07c
/* 0040b068 */  sh         $t9, 4($s0)
/* 0040b06c */  b          0x40b07c
/* 0040b070 */  sh         $v1, 4($s0)
/* 0040b074 */  addiu      $t1, $zero, 3
/* 0040b078 */  sh         $t1, 4($s0)
/* 0040b07c */  lui        $t2, 0x98
/* 0040b080 */  ori        $t2, $t2, 0x9680
/* 0040b084 */  sw         $t2, 0xc($s0)
/* 0040b088 */  sw         $zero, 0x10($s0)
/* 0040b08c */  move       $a0, $s0
/* 0040b090 */  jal        0x40c180
/* 0040b094 */  addiu      $a1, $gp, -0x7c00
/* 0040b098 */  sw         $zero, 0x14($s0)
/* 0040b09c */  sh         $zero, 0x72($s0)
/* 0040b0a0 */  lw         $a0, 0x30($sp)
/* 0040b0a4 */  addiu      $v1, $zero, 1
/* 0040b0a8 */  move       $a1, $s0
/* 0040b0ac */  jal        0x40dfe0
/* 0040b0b0 */  addiu      $a2, $zero, 0x98
/* 0040b0b4 */  addiu      $at, $zero, 0x98
/* 0040b0b8 */  beq        $v0, $at, 0x40b1bc
/* 0040b0bc */  addiu      $v1, $zero, 1
/* 0040b0c0 */  lui        $a0, 0x1000
/* 0040b0c4 */  jal        0x40b640
/* 0040b0c8 */  addiu      $a0, $a0, 0x302c
/* 0040b0cc */  b          0x40b4e0
/* 0040b0d0 */  move       $v0, $zero
/* 0040b0d4 */  lw         $t3, 0x34($sp)
/* 0040b0d8 */  nop        
/* 0040b0dc */  beqz       $t3, 0x40b114
/* 0040b0e0 */  lw         $t5, 0x30($sp)
/* 0040b0e4 */  lw         $t4, 0x28($sp)
/* 0040b0e8 */  nop        
/* 0040b0ec */  beqz       $t4, 0x40b100
/* 0040b0f0 */  move       $a1, $zero
/* 0040b0f4 */  b          0x40b100
/* 0040b0f8 */  addiu      $a1, $zero, 2
/* 0040b0fc */  move       $a1, $zero
/* 0040b100 */  lw         $a0, 0x34($sp)
/* 0040b104 */  jal        0x40dfc0
/* 0040b108 */  nop        
/* 0040b10c */  sw         $v0, 0x30($sp)
/* 0040b110 */  lw         $t5, 0x30($sp)
/* 0040b114 */  nop        
/* 0040b118 */  bgez       $t5, 0x40b12c
/* 0040b11c */  lw         $a0, 0x30($sp)
/* 0040b120 */  b          0x40b4e0
/* 0040b124 */  move       $v0, $zero
/* 0040b128 */  lw         $a0, 0x30($sp)
/* 0040b12c */  move       $a1, $s0
/* 0040b130 */  jal        0x40e000
/* 0040b134 */  addiu      $a2, $zero, 0x98
/* 0040b138 */  addiu      $at, $zero, 0x98
/* 0040b13c */  beq        $v0, $at, 0x40b158
/* 0040b140 */  nop        
/* 0040b144 */  lui        $a0, 0x1000
/* 0040b148 */  jal        0x40b640
/* 0040b14c */  addiu      $a0, $a0, 0x3054
/* 0040b150 */  b          0x40b4e0
/* 0040b154 */  move       $v0, $zero
/* 0040b158 */  lhu        $a1, ($s0)
/* 0040b15c */  addiu      $at, $zero, 0x1da
/* 0040b160 */  andi       $t7, $a1, 0xff
/* 0040b164 */  sll        $t8, $t7, 8
/* 0040b168 */  srl        $t6, $a1, 8
/* 0040b16c */  or         $t9, $t6, $t8
/* 0040b170 */  bne        $t9, $at, 0x40b190
/* 0040b174 */  nop        
/* 0040b178 */  addiu      $t0, $zero, 1
/* 0040b17c */  sh         $t0, 0x72($s0)
/* 0040b180 */  jal        0x40b5f8
/* 0040b184 */  move       $a0, $s0
/* 0040b188 */  b          0x40b198
/* 0040b18c */  lhu        $a1, ($s0)
/* 0040b190 */  sh         $zero, 0x72($s0)
/* 0040b194 */  lhu        $a1, ($s0)
/* 0040b198 */  addiu      $at, $zero, 0x1da
/* 0040b19c */  beq        $a1, $at, 0x40b1bc
/* 0040b1a0 */  addiu      $v1, $zero, 1
/* 0040b1a4 */  lui        $a0, 0x1000
/* 0040b1a8 */  jal        0x40b640
/* 0040b1ac */  addiu      $a0, $a0, 0x307c
/* 0040b1b0 */  b          0x40b4e0
/* 0040b1b4 */  move       $v0, $zero
/* 0040b1b8 */  addiu      $v1, $zero, 1
/* 0040b1bc */  lw         $t1, 0x28($sp)
/* 0040b1c0 */  nop        
/* 0040b1c4 */  beqz       $t1, 0x40b1dc
/* 0040b1c8 */  lw         $t3, 0x38($sp)
/* 0040b1cc */  addiu      $t2, $zero, 0x80
/* 0040b1d0 */  b          0x40b200
/* 0040b1d4 */  sh         $t2, 0x70($s0)
/* 0040b1d8 */  lw         $t3, 0x38($sp)
/* 0040b1dc */  addiu      $at, $zero, 0x72
/* 0040b1e0 */  lbu        $t4, ($t3)
/* 0040b1e4 */  nop        
/* 0040b1e8 */  beq        $t4, $at, 0x40b1fc
/* 0040b1ec */  nop        
/* 0040b1f0 */  addiu      $t5, $zero, 2
/* 0040b1f4 */  b          0x40b200
/* 0040b1f8 */  sh         $t5, 0x70($s0)
/* 0040b1fc */  sh         $v1, 0x70($s0)
/* 0040b200 */  lhu        $t7, 2($s0)
/* 0040b204 */  addiu      $at, $zero, 0x100
/* 0040b208 */  andi       $t6, $t7, 0xff00
/* 0040b20c */  bne        $t6, $at, 0x40b480
/* 0040b210 */  nop        
/* 0040b214 */  lhu        $t8, 8($s0)
/* 0040b218 */  lhu        $t9, 0xa($s0)
/* 0040b21c */  nop        
/* 0040b220 */  multu      $t8, $t9
/* 0040b224 */  mflo       $v0
/* 0040b228 */  sll        $v0, $v0, 2
/* 0040b22c */  move       $a0, $v0
/* 0040b230 */  jal        0xf801208                                # free
/* 0040b234 */  sw         $v0, 0x24($sp)
/* 0040b238 */  sw         $v0, 0x90($s0)
/* 0040b23c */  lw         $a0, 0x24($sp)
/* 0040b240 */  jal        0xf801208                                # free
/* 0040b244 */  nop        
/* 0040b248 */  lw         $t0, 0x90($s0)
/* 0040b24c */  sw         $v0, 0x94($s0)
/* 0040b250 */  beqz       $t0, 0x40b268
/* 0040b254 */  nop        
/* 0040b258 */  lw         $t1, 0x94($s0)
/* 0040b25c */  nop        
/* 0040b260 */  bnez       $t1, 0x40b280
/* 0040b264 */  lw         $t2, 0x24($sp)
/* 0040b268 */  lui        $a0, 0x1000
/* 0040b26c */  jal        0x40b640
/* 0040b270 */  addiu      $a0, $a0, 0x30a0
/* 0040b274 */  b          0x40b4e0
/* 0040b278 */  move       $v0, $zero
/* 0040b27c */  lw         $t2, 0x24($sp)
/* 0040b280 */  addiu      $at, $zero, 0x77
/* 0040b284 */  sll        $t3, $t2, 1
/* 0040b288 */  addiu      $t4, $t3, 0x200
/* 0040b28c */  sw         $t4, 0x8c($s0)
/* 0040b290 */  lw         $t5, 0x38($sp)
/* 0040b294 */  nop        
/* 0040b298 */  lbu        $t7, ($t5)
/* 0040b29c */  nop        
/* 0040b2a0 */  bne        $t7, $at, 0x40b3a8
/* 0040b2a4 */  nop        
/* 0040b2a8 */  lhu        $t6, 8($s0)
/* 0040b2ac */  lhu        $t8, 0xa($s0)
/* 0040b2b0 */  move       $a1, $zero
/* 0040b2b4 */  multu      $t6, $t8
/* 0040b2b8 */  mflo       $a2
/* 0040b2bc */  blez       $a2, 0x40b480
/* 0040b2c0 */  nop        
/* 0040b2c4 */  andi       $v1, $a2, 3
/* 0040b2c8 */  bnez       $v1, 0x40b2dc
/* 0040b2cc */  sll        $v0, $a1, 2
/* 0040b2d0 */  b          0x40b310
/* 0040b2d4 */  addiu      $a0, $zero, -1
/* 0040b2d8 */  sll        $v0, $a1, 2
/* 0040b2dc */  addiu      $a0, $zero, -1
/* 0040b2e0 */  lw         $t9, 0x90($s0)
/* 0040b2e4 */  addiu      $a1, $a1, 1
/* 0040b2e8 */  addu       $t0, $t9, $v0
/* 0040b2ec */  sw         $zero, ($t0)
/* 0040b2f0 */  lw         $t1, 0x94($s0)
/* 0040b2f4 */  nop        
/* 0040b2f8 */  addu       $t2, $t1, $v0
/* 0040b2fc */  sw         $a0, ($t2)
/* 0040b300 */  bne        $v1, $a1, 0x40b2e0
/* 0040b304 */  addiu      $v0, $v0, 4
/* 0040b308 */  beq        $a1, $a2, 0x40b480
/* 0040b30c */  nop        
/* 0040b310 */  sll        $v0, $a1, 2
/* 0040b314 */  sll        $v1, $a2, 2
/* 0040b318 */  lw         $t3, 0x90($s0)
/* 0040b31c */  nop        
/* 0040b320 */  addu       $t4, $t3, $v0
/* 0040b324 */  sw         $zero, ($t4)
/* 0040b328 */  lw         $t5, 0x94($s0)
/* 0040b32c */  nop        
/* 0040b330 */  addu       $t7, $t5, $v0
/* 0040b334 */  sw         $a0, ($t7)
/* 0040b338 */  lw         $t6, 0x90($s0)
/* 0040b33c */  nop        
/* 0040b340 */  addu       $t8, $t6, $v0
/* 0040b344 */  sw         $zero, 4($t8)
/* 0040b348 */  lw         $t9, 0x94($s0)
/* 0040b34c */  nop        
/* 0040b350 */  addu       $t0, $t9, $v0
/* 0040b354 */  sw         $a0, 4($t0)
/* 0040b358 */  lw         $t1, 0x90($s0)
/* 0040b35c */  nop        
/* 0040b360 */  addu       $t2, $t1, $v0
/* 0040b364 */  sw         $zero, 8($t2)
/* 0040b368 */  lw         $t3, 0x94($s0)
/* 0040b36c */  nop        
/* 0040b370 */  addu       $t4, $t3, $v0
/* 0040b374 */  sw         $a0, 8($t4)
/* 0040b378 */  lw         $t5, 0x90($s0)
/* 0040b37c */  nop        
/* 0040b380 */  addu       $t7, $t5, $v0
/* 0040b384 */  sw         $zero, 0xc($t7)
/* 0040b388 */  lw         $t6, 0x94($s0)
/* 0040b38c */  nop        
/* 0040b390 */  addu       $t8, $t6, $v0
/* 0040b394 */  addiu      $v0, $v0, 0x10
/* 0040b398 */  bne        $v0, $v1, 0x40b318
/* 0040b39c */  sw         $a0, 0xc($t8)
/* 0040b3a0 */  b          0x40b484
/* 0040b3a4 */  sh         $zero, 0x7a($s0)
/* 0040b3a8 */  lhu        $t9, 8($s0)
/* 0040b3ac */  lhu        $t0, 0xa($s0)
/* 0040b3b0 */  lw         $a0, 0x30($sp)
/* 0040b3b4 */  multu      $t9, $t0
/* 0040b3b8 */  addiu      $a1, $zero, 0x200
/* 0040b3bc */  move       $a2, $zero
/* 0040b3c0 */  mflo       $t1
/* 0040b3c4 */  sll        $t2, $t1, 2
/* 0040b3c8 */  jal        0x40e020
/* 0040b3cc */  sw         $t2, 0x24($sp)
/* 0040b3d0 */  lw         $a0, 0x30($sp)
/* 0040b3d4 */  lw         $a1, 0x90($s0)
/* 0040b3d8 */  lw         $a2, 0x24($sp)
/* 0040b3dc */  jal        0x40e000
/* 0040b3e0 */  nop        
/* 0040b3e4 */  lw         $a2, 0x24($sp)
/* 0040b3e8 */  nop        
/* 0040b3ec */  beq        $v0, $a2, 0x40b408
/* 0040b3f0 */  nop        
/* 0040b3f4 */  lui        $a0, 0x1000
/* 0040b3f8 */  jal        0x40b640
/* 0040b3fc */  addiu      $a0, $a0, 0x30c0
/* 0040b400 */  b          0x40b4e0
/* 0040b404 */  move       $v0, $zero
/* 0040b408 */  lh         $t3, 0x72($s0)
/* 0040b40c */  nop        
/* 0040b410 */  beqz       $t3, 0x40b430
/* 0040b414 */  lw         $a0, 0x30($sp)
/* 0040b418 */  lw         $a0, 0x90($s0)
/* 0040b41c */  jal        0x40b594
/* 0040b420 */  move       $a1, $a2
/* 0040b424 */  lw         $a2, 0x24($sp)
/* 0040b428 */  nop        
/* 0040b42c */  lw         $a0, 0x30($sp)
/* 0040b430 */  lw         $a1, 0x94($s0)
/* 0040b434 */  jal        0x40e000
/* 0040b438 */  nop        
/* 0040b43c */  lw         $t4, 0x24($sp)
/* 0040b440 */  nop        
/* 0040b444 */  beq        $v0, $t4, 0x40b460
/* 0040b448 */  nop        
/* 0040b44c */  lui        $a0, 0x1000
/* 0040b450 */  jal        0x40b640
/* 0040b454 */  addiu      $a0, $a0, 0x30e4
/* 0040b458 */  b          0x40b4e0
/* 0040b45c */  move       $v0, $zero
/* 0040b460 */  lh         $t5, 0x72($s0)
/* 0040b464 */  nop        
/* 0040b468 */  beqz       $t5, 0x40b480
/* 0040b46c */  nop        
/* 0040b470 */  lw         $a0, 0x94($s0)
/* 0040b474 */  lw         $a1, 0x24($sp)
/* 0040b478 */  jal        0x40b594
/* 0040b47c */  nop        
/* 0040b480 */  sh         $zero, 0x7a($s0)
/* 0040b484 */  sw         $zero, 0x7c($s0)
/* 0040b488 */  sw         $zero, 0x80($s0)
/* 0040b48c */  jal        0x40b4f0
/* 0040b490 */  move       $a0, $s0
/* 0040b494 */  bnez       $v0, 0x40b4b4
/* 0040b498 */  sw         $v0, 0x84($s0)
/* 0040b49c */  lui        $a0, 0x1000
/* 0040b4a0 */  lhu        $a1, 6($s0)
/* 0040b4a4 */  jal        0x40b640
/* 0040b4a8 */  addiu      $a0, $a0, 0x3108
/* 0040b4ac */  b          0x40b4e0
/* 0040b4b0 */  move       $v0, $zero
/* 0040b4b4 */  lw         $a0, 0x30($sp)
/* 0040b4b8 */  sh         $zero, 0x74($s0)
/* 0040b4bc */  sh         $zero, 0x76($s0)
/* 0040b4c0 */  addiu      $t7, $zero, 0x200
/* 0040b4c4 */  sh         $zero, 0x78($s0)
/* 0040b4c8 */  sw         $t7, 0x88($s0)
/* 0040b4cc */  addiu      $a1, $zero, 0x200
/* 0040b4d0 */  move       $a2, $zero
/* 0040b4d4 */  jal        0x40e020
/* 0040b4d8 */  sw         $a0, 0x6c($s0)
/* 0040b4dc */  move       $v0, $s0
/* 0040b4e0 */  lw         $ra, 0x1c($sp)
/* 0040b4e4 */  lw         $s0, 0x18($sp)
/* 0040b4e8 */  jr         $ra
/* 0040b4ec */  addiu      $sp, $sp, 0x30
/* 0040b4f0 */  addiu      $sp, $sp, -0x18
/* 0040b4f4 */  sw         $ra, 0x14($sp)
/* 0040b4f8 */  move       $v1, $a0
/* 0040b4fc */  lhu        $v0, 6($v1)
/* 0040b500 */  nop        
/* 0040b504 */  srl        $t6, $v0, 6
/* 0040b508 */  addu       $a0, $v0, $t6
/* 0040b50c */  jal        0xf801208                                # free
/* 0040b510 */  sll        $a0, $a0, 2
/* 0040b514 */  lw         $ra, 0x14($sp)
/* 0040b518 */  addiu      $sp, $sp, 0x18
/* 0040b51c */  jr         $ra
/* 0040b520 */  nop        
/* 0040b524 */  srl        $t7, $a0, 8
/* 0040b528 */  andi       $t8, $t7, 0xff00
/* 0040b52c */  srl        $t6, $a0, 0x18
/* 0040b530 */  sll        $t0, $a0, 8
/* 0040b534 */  lui        $at, 0xff
/* 0040b538 */  and        $t1, $t0, $at
/* 0040b53c */  or         $t9, $t6, $t8
/* 0040b540 */  or         $t2, $t9, $t1
/* 0040b544 */  sll        $t3, $a0, 0x18
/* 0040b548 */  jr         $ra
/* 0040b54c */  or         $v0, $t2, $t3
/* 0040b550 */  sra        $v0, $a1, 1
/* 0040b554 */  move       $a2, $a0
/* 0040b558 */  blez       $v0, 0x40b58c
/* 0040b55c */  move       $v1, $zero
/* 0040b560 */  lhu        $a0, ($a2)
/* 0040b564 */  addiu      $v1, $v1, 1
/* 0040b568 */  sll        $v1, $v1, 0x10
/* 0040b56c */  sra        $v1, $v1, 0x10
/* 0040b570 */  srl        $t6, $a0, 8
/* 0040b574 */  sll        $t7, $a0, 8
/* 0040b578 */  or         $t8, $t6, $t7
/* 0040b57c */  slt        $at, $v1, $v0
/* 0040b580 */  sh         $t8, ($a2)
/* 0040b584 */  bnez       $at, 0x40b560
/* 0040b588 */  addiu      $a2, $a2, 2
/* 0040b58c */  jr         $ra
/* 0040b590 */  nop        
/* 0040b594 */  sra        $v0, $a1, 2
/* 0040b598 */  move       $a2, $a0
/* 0040b59c */  blez       $v0, 0x40b5f0
/* 0040b5a0 */  move       $v1, $zero
/* 0040b5a4 */  lui        $a3, 0xff
/* 0040b5a8 */  sll        $t6, $v1, 2
/* 0040b5ac */  addu       $a1, $a2, $t6
/* 0040b5b0 */  lw         $a0, ($a1)
/* 0040b5b4 */  addiu      $v1, $v1, 1
/* 0040b5b8 */  srl        $t8, $a0, 8
/* 0040b5bc */  andi       $t9, $t8, 0xff00
/* 0040b5c0 */  srl        $t7, $a0, 0x18
/* 0040b5c4 */  sll        $t1, $a0, 8
/* 0040b5c8 */  and        $t2, $t1, $a3
/* 0040b5cc */  or         $t0, $t7, $t9
/* 0040b5d0 */  sll        $v1, $v1, 0x10
/* 0040b5d4 */  or         $t3, $t0, $t2
/* 0040b5d8 */  sra        $v1, $v1, 0x10
/* 0040b5dc */  sll        $t4, $a0, 0x18
/* 0040b5e0 */  or         $t5, $t3, $t4
/* 0040b5e4 */  slt        $at, $v1, $v0
/* 0040b5e8 */  bnez       $at, 0x40b5a8
/* 0040b5ec */  sw         $t5, ($a1)
/* 0040b5f0 */  jr         $ra
/* 0040b5f4 */  nop        
/* 0040b5f8 */  addiu      $sp, $sp, -0x18
/* 0040b5fc */  sw         $a0, 0x18($sp)
/* 0040b600 */  sw         $ra, 0x14($sp)
/* 0040b604 */  lw         $a0, 0x18($sp)
/* 0040b608 */  jal        0x40b550
/* 0040b60c */  addiu      $a1, $zero, 0xc
/* 0040b610 */  lw         $a0, 0x18($sp)
/* 0040b614 */  addiu      $a1, $zero, 0xc
/* 0040b618 */  jal        0x40b594
/* 0040b61c */  addiu      $a0, $a0, 0xc
/* 0040b620 */  lw         $a0, 0x18($sp)
/* 0040b624 */  addiu      $a1, $zero, 4
/* 0040b628 */  jal        0x40b594
/* 0040b62c */  addiu      $a0, $a0, 0x68
/* 0040b630 */  lw         $ra, 0x14($sp)
/* 0040b634 */  addiu      $sp, $sp, 0x18
/* 0040b638 */  jr         $ra
/* 0040b63c */  nop        
/* 0040b640 */  lw         $t6, -0x7ab0($gp)                        # .sbss @ 0x100042c0
/* 0040b644 */  addiu      $sp, $sp, -0x820
/* 0040b648 */  sw         $ra, 0x1c($sp)
/* 0040b64c */  move       $v1, $a0
/* 0040b650 */  move       $t0, $a1
/* 0040b654 */  move       $t1, $a2
/* 0040b658 */  beqz       $t6, 0x40b698
/* 0040b65c */  move       $t2, $a3
/* 0040b660 */  lw         $t7, 0x830($sp)
/* 0040b664 */  sw         $t2, 0x10($sp)
/* 0040b668 */  addiu      $a0, $sp, 0x20
/* 0040b66c */  move       $a1, $v1
/* 0040b670 */  move       $a2, $t0
/* 0040b674 */  move       $a3, $t1
/* 0040b678 */  jal        0xf8012c0                                # sprintf
/* 0040b67c */  sw         $t7, 0x14($sp)
/* 0040b680 */  lw         $t8, -0x7ab0($gp)                        # .sbss @ 0x100042c0
/* 0040b684 */  addiu      $a0, $sp, 0x20
/* 0040b688 */  jalr       $t8
/* 0040b68c */  nop        
/* 0040b690 */  b          0x40b6c8
/* 0040b694 */  lw         $ra, 0x1c($sp)
/* 0040b698 */  lw         $t9, 0x830($sp)
/* 0040b69c */  lui        $a0, 0x1000
/* 0040b6a0 */  sw         $t2, 0x10($sp)
/* 0040b6a4 */  addiu      $a0, $a0, 0x36b4
/* 0040b6a8 */  move       $a1, $v1
/* 0040b6ac */  move       $a2, $t0
/* 0040b6b0 */  move       $a3, $t1
/* 0040b6b4 */  jal        0xf801150                                # fclose
/* 0040b6b8 */  sw         $t9, 0x14($sp)
/* 0040b6bc */  jal        0x40d3c0
/* 0040b6c0 */  addiu      $a0, $zero, 1
/* 0040b6c4 */  lw         $ra, 0x1c($sp)
/* 0040b6c8 */  addiu      $sp, $sp, 0x820
/* 0040b6cc */  jr         $ra
/* 0040b6d0 */  nop        
/* 0040b6d4 */  jr         $ra
/* 0040b6d8 */  sw         $a0, -0x7ab0($gp)                        # .sbss @ 0x100042c0
/* 0040b6dc */  nop        
/* 0040b6e0 */  addiu      $sp, $sp, -0x40
/* 0040b6e4 */  sw         $s0, 0x20($sp)
/* 0040b6e8 */  move       $s0, $a0
/* 0040b6ec */  sw         $ra, 0x24($sp)
/* 0040b6f0 */  lhu        $t6, 0x70($s0)
/* 0040b6f4 */  move       $t2, $a1
/* 0040b6f8 */  andi       $t7, $t6, 0x82
/* 0040b6fc */  move       $t4, $a2
/* 0040b700 */  bnez       $t7, 0x40b710
/* 0040b704 */  move       $t3, $a3
/* 0040b708 */  b          0x40bbc8
/* 0040b70c */  addiu      $v0, $zero, -1
/* 0040b710 */  lhu        $v0, 4($s0)
/* 0040b714 */  nop        
/* 0040b718 */  sltiu      $at, $v0, 3
/* 0040b71c */  beqz       $at, 0x40b72c
/* 0040b720 */  sltiu      $at, $v0, 2
/* 0040b724 */  move       $t3, $zero
/* 0040b728 */  sltiu      $at, $v0, 2
/* 0040b72c */  beqz       $at, 0x40b738
/* 0040b730 */  nop        
/* 0040b734 */  move       $t4, $zero
/* 0040b738 */  lhu        $v1, 2($s0)
/* 0040b73c */  nop        
/* 0040b740 */  andi       $v0, $v1, 0xff00
/* 0040b744 */  bnez       $v0, 0x40b948
/* 0040b748 */  addiu      $at, $zero, 0x100
/* 0040b74c */  andi       $v0, $v1, 0xff
/* 0040b750 */  addiu      $at, $zero, 1
/* 0040b754 */  beq        $v0, $at, 0x40b76c
/* 0040b758 */  addiu      $at, $zero, 2
/* 0040b75c */  beq        $v0, $at, 0x40b820
/* 0040b760 */  nop        
/* 0040b764 */  b          0x40b930
/* 0040b768 */  nop        
/* 0040b76c */  lhu        $a0, 6($s0)
/* 0040b770 */  lw         $t0, 0xc($s0)
/* 0040b774 */  lw         $t1, 0x10($s0)
/* 0040b778 */  lw         $v1, 0x84($s0)
/* 0040b77c */  move       $v0, $a0
/* 0040b780 */  move       $a1, $t2
/* 0040b784 */  beqz       $v0, 0x40b7d0
/* 0040b788 */  addiu      $a0, $a0, -1
/* 0040b78c */  lhu        $t8, ($a1)
/* 0040b790 */  addiu      $a1, $a1, 2
/* 0040b794 */  sb         $t8, ($v1)
/* 0040b798 */  lbu        $v0, ($v1)
/* 0040b79c */  nop        
/* 0040b7a0 */  sltu       $at, $t1, $v0
/* 0040b7a4 */  beqz       $at, 0x40b7b4
/* 0040b7a8 */  sltu       $at, $v0, $t0
/* 0040b7ac */  move       $t1, $v0
/* 0040b7b0 */  sltu       $at, $v0, $t0
/* 0040b7b4 */  beqz       $at, 0x40b7c0
/* 0040b7b8 */  nop        
/* 0040b7bc */  move       $t0, $v0
/* 0040b7c0 */  move       $v0, $a0
/* 0040b7c4 */  addiu      $v1, $v1, 1
/* 0040b7c8 */  bnez       $v0, 0x40b78c
/* 0040b7cc */  addiu      $a0, $a0, -1
/* 0040b7d0 */  sw         $t0, 0xc($s0)
/* 0040b7d4 */  sw         $t1, 0x10($s0)
/* 0040b7d8 */  move       $a0, $s0
/* 0040b7dc */  move       $a1, $t4
/* 0040b7e0 */  jal        0x40c1b0
/* 0040b7e4 */  move       $a2, $t3
/* 0040b7e8 */  lhu        $v0, 6($s0)
/* 0040b7ec */  lw         $a1, 0x84($s0)
/* 0040b7f0 */  move       $a0, $s0
/* 0040b7f4 */  sw         $v0, 0x28($sp)
/* 0040b7f8 */  jal        0x40c3fc
/* 0040b7fc */  move       $a2, $v0
/* 0040b800 */  lw         $v1, 0x28($sp)
/* 0040b804 */  nop        
/* 0040b808 */  beq        $v0, $v1, 0x40b818
/* 0040b80c */  nop        
/* 0040b810 */  b          0x40bbc8
/* 0040b814 */  addiu      $v0, $zero, -1
/* 0040b818 */  b          0x40bbc8
/* 0040b81c */  move       $v0, $v1
/* 0040b820 */  lhu        $a0, 6($s0)
/* 0040b824 */  lw         $t0, 0xc($s0)
/* 0040b828 */  lw         $t1, 0x10($s0)
/* 0040b82c */  move       $v0, $a0
/* 0040b830 */  move       $a1, $t2
/* 0040b834 */  beqz       $v0, 0x40b874
/* 0040b838 */  addiu      $a0, $a0, -1
/* 0040b83c */  lhu        $v0, ($a1)
/* 0040b840 */  nop        
/* 0040b844 */  sltu       $at, $t1, $v0
/* 0040b848 */  beqz       $at, 0x40b858
/* 0040b84c */  sltu       $at, $v0, $t0
/* 0040b850 */  move       $t1, $v0
/* 0040b854 */  sltu       $at, $v0, $t0
/* 0040b858 */  beqz       $at, 0x40b864
/* 0040b85c */  nop        
/* 0040b860 */  move       $t0, $v0
/* 0040b864 */  move       $v0, $a0
/* 0040b868 */  addiu      $a1, $a1, 2
/* 0040b86c */  bnez       $v0, 0x40b83c
/* 0040b870 */  addiu      $a0, $a0, -1
/* 0040b874 */  sw         $t0, 0xc($s0)
/* 0040b878 */  sw         $t1, 0x10($s0)
/* 0040b87c */  sw         $t2, 0x44($sp)
/* 0040b880 */  move       $a0, $s0
/* 0040b884 */  move       $a1, $t4
/* 0040b888 */  jal        0x40c1b0
/* 0040b88c */  move       $a2, $t3
/* 0040b890 */  lhu        $t9, 6($s0)
/* 0040b894 */  lw         $t2, 0x44($sp)
/* 0040b898 */  sll        $t5, $t9, 1
/* 0040b89c */  sw         $t5, 0x28($sp)
/* 0040b8a0 */  lh         $t6, 0x72($s0)
/* 0040b8a4 */  nop        
/* 0040b8a8 */  beqz       $t6, 0x40b8c8
/* 0040b8ac */  nop        
/* 0040b8b0 */  move       $a0, $t2
/* 0040b8b4 */  move       $a1, $t5
/* 0040b8b8 */  jal        0x40b550
/* 0040b8bc */  sw         $t2, 0x44($sp)
/* 0040b8c0 */  lw         $t2, 0x44($sp)
/* 0040b8c4 */  nop        
/* 0040b8c8 */  lw         $a2, 0x28($sp)
/* 0040b8cc */  move       $a0, $s0
/* 0040b8d0 */  move       $a1, $t2
/* 0040b8d4 */  jal        0x40c3fc
/* 0040b8d8 */  sw         $t2, 0x44($sp)
/* 0040b8dc */  lw         $a1, 0x28($sp)
/* 0040b8e0 */  lw         $t2, 0x44($sp)
/* 0040b8e4 */  beq        $v0, $a1, 0x40b90c
/* 0040b8e8 */  nop        
/* 0040b8ec */  lh         $t7, 0x72($s0)
/* 0040b8f0 */  nop        
/* 0040b8f4 */  beqz       $t7, 0x40b904
/* 0040b8f8 */  nop        
/* 0040b8fc */  jal        0x40b550
/* 0040b900 */  move       $a0, $t2
/* 0040b904 */  b          0x40bbc8
/* 0040b908 */  addiu      $v0, $zero, -1
/* 0040b90c */  lh         $t8, 0x72($s0)
/* 0040b910 */  nop        
/* 0040b914 */  beqz       $t8, 0x40b924
/* 0040b918 */  nop        
/* 0040b91c */  jal        0x40b550
/* 0040b920 */  move       $a0, $t2
/* 0040b924 */  lhu        $v0, 6($s0)
/* 0040b928 */  b          0x40bbcc
/* 0040b92c */  lw         $ra, 0x24($sp)
/* 0040b930 */  lui        $a0, 0x1000
/* 0040b934 */  jal        0x40b640
/* 0040b938 */  addiu      $a0, $a0, 0x3130
/* 0040b93c */  b          0x40bbcc
/* 0040b940 */  lw         $ra, 0x24($sp)
/* 0040b944 */  addiu      $at, $zero, 0x100
/* 0040b948 */  bne        $v0, $at, 0x40bbbc
/* 0040b94c */  nop        
/* 0040b950 */  b          0x40bba0
/* 0040b954 */  andi       $v0, $v1, 0xff
/* 0040b958 */  lhu        $v1, 6($s0)
/* 0040b95c */  lw         $t0, 0xc($s0)
/* 0040b960 */  move       $a0, $v1
/* 0040b964 */  lw         $t1, 0x10($s0)
/* 0040b968 */  move       $v0, $a0
/* 0040b96c */  move       $a1, $t2
/* 0040b970 */  beqz       $v0, 0x40b9b0
/* 0040b974 */  addiu      $a0, $a0, -1
/* 0040b978 */  lhu        $v0, ($a1)
/* 0040b97c */  nop        
/* 0040b980 */  sltu       $at, $t1, $v0
/* 0040b984 */  beqz       $at, 0x40b994
/* 0040b988 */  sltu       $at, $v0, $t0
/* 0040b98c */  move       $t1, $v0
/* 0040b990 */  sltu       $at, $v0, $t0
/* 0040b994 */  beqz       $at, 0x40b9a0
/* 0040b998 */  nop        
/* 0040b99c */  move       $t0, $v0
/* 0040b9a0 */  move       $v0, $a0
/* 0040b9a4 */  addiu      $a1, $a1, 2
/* 0040b9a8 */  bnez       $v0, 0x40b978
/* 0040b9ac */  addiu      $a0, $a0, -1
/* 0040b9b0 */  lw         $a2, 0x84($s0)
/* 0040b9b4 */  sw         $t0, 0xc($s0)
/* 0040b9b8 */  sw         $t1, 0x10($s0)
/* 0040b9bc */  sw         $t4, 0x48($sp)
/* 0040b9c0 */  sw         $t3, 0x4c($sp)
/* 0040b9c4 */  sw         $v1, 0x10($sp)
/* 0040b9c8 */  move       $a0, $t2
/* 0040b9cc */  addiu      $a1, $zero, 2
/* 0040b9d0 */  jal        0x40c6a8
/* 0040b9d4 */  addiu      $a3, $zero, 1
/* 0040b9d8 */  lw         $t3, 0x4c($sp)
/* 0040b9dc */  lw         $t4, 0x48($sp)
/* 0040b9e0 */  sw         $v0, 0x28($sp)
/* 0040b9e4 */  move       $a0, $s0
/* 0040b9e8 */  move       $a1, $v0
/* 0040b9ec */  move       $a3, $t3
/* 0040b9f0 */  jal        0x40c590
/* 0040b9f4 */  move       $a2, $t4
/* 0040b9f8 */  lw         $t3, 0x4c($sp)
/* 0040b9fc */  lw         $t4, 0x48($sp)
/* 0040ba00 */  move       $a0, $s0
/* 0040ba04 */  move       $a2, $t3
/* 0040ba08 */  jal        0x40c1b0
/* 0040ba0c */  move       $a1, $t4
/* 0040ba10 */  lw         $a1, 0x84($s0)
/* 0040ba14 */  lw         $a2, 0x28($sp)
/* 0040ba18 */  jal        0x40c3fc
/* 0040ba1c */  move       $a0, $s0
/* 0040ba20 */  lw         $t9, 0x28($sp)
/* 0040ba24 */  nop        
/* 0040ba28 */  beq        $v0, $t9, 0x40ba38
/* 0040ba2c */  nop        
/* 0040ba30 */  b          0x40bbc8
/* 0040ba34 */  addiu      $v0, $zero, -1
/* 0040ba38 */  lhu        $v0, 6($s0)
/* 0040ba3c */  b          0x40bbcc
/* 0040ba40 */  lw         $ra, 0x24($sp)
/* 0040ba44 */  lhu        $v1, 6($s0)
/* 0040ba48 */  lw         $t0, 0xc($s0)
/* 0040ba4c */  move       $a0, $v1
/* 0040ba50 */  lw         $t1, 0x10($s0)
/* 0040ba54 */  move       $v0, $a0
/* 0040ba58 */  move       $a1, $t2
/* 0040ba5c */  beqz       $v0, 0x40ba9c
/* 0040ba60 */  addiu      $a0, $a0, -1
/* 0040ba64 */  lhu        $v0, ($a1)
/* 0040ba68 */  nop        
/* 0040ba6c */  sltu       $at, $t1, $v0
/* 0040ba70 */  beqz       $at, 0x40ba80
/* 0040ba74 */  sltu       $at, $v0, $t0
/* 0040ba78 */  move       $t1, $v0
/* 0040ba7c */  sltu       $at, $v0, $t0
/* 0040ba80 */  beqz       $at, 0x40ba8c
/* 0040ba84 */  nop        
/* 0040ba88 */  move       $t0, $v0
/* 0040ba8c */  move       $v0, $a0
/* 0040ba90 */  addiu      $a1, $a1, 2
/* 0040ba94 */  bnez       $v0, 0x40ba64
/* 0040ba98 */  addiu      $a0, $a0, -1
/* 0040ba9c */  lw         $a2, 0x84($s0)
/* 0040baa0 */  sw         $t0, 0xc($s0)
/* 0040baa4 */  sw         $t1, 0x10($s0)
/* 0040baa8 */  sw         $t4, 0x48($sp)
/* 0040baac */  sw         $t3, 0x4c($sp)
/* 0040bab0 */  sw         $v1, 0x10($sp)
/* 0040bab4 */  move       $a0, $t2
/* 0040bab8 */  addiu      $a1, $zero, 2
/* 0040babc */  jal        0x40c6a8
/* 0040bac0 */  addiu      $a3, $zero, 2
/* 0040bac4 */  lw         $t3, 0x4c($sp)
/* 0040bac8 */  lw         $t4, 0x48($sp)
/* 0040bacc */  sll        $a1, $v0, 1
/* 0040bad0 */  sw         $a1, 0x28($sp)
/* 0040bad4 */  move       $a0, $s0
/* 0040bad8 */  move       $a3, $t3
/* 0040badc */  jal        0x40c590
/* 0040bae0 */  move       $a2, $t4
/* 0040bae4 */  lw         $t3, 0x4c($sp)
/* 0040bae8 */  lw         $t4, 0x48($sp)
/* 0040baec */  move       $a0, $s0
/* 0040baf0 */  move       $a2, $t3
/* 0040baf4 */  jal        0x40c1b0
/* 0040baf8 */  move       $a1, $t4
/* 0040bafc */  lh         $t6, 0x72($s0)
/* 0040bb00 */  nop        
/* 0040bb04 */  beqz       $t6, 0x40bb1c
/* 0040bb08 */  nop        
/* 0040bb0c */  lw         $a0, 0x84($s0)
/* 0040bb10 */  lw         $a1, 0x28($sp)
/* 0040bb14 */  jal        0x40b550
/* 0040bb18 */  nop        
/* 0040bb1c */  lw         $a1, 0x84($s0)
/* 0040bb20 */  lw         $a2, 0x28($sp)
/* 0040bb24 */  jal        0x40c3fc
/* 0040bb28 */  move       $a0, $s0
/* 0040bb2c */  lw         $t5, 0x28($sp)
/* 0040bb30 */  nop        
/* 0040bb34 */  beq        $v0, $t5, 0x40bb60
/* 0040bb38 */  nop        
/* 0040bb3c */  lh         $t7, 0x72($s0)
/* 0040bb40 */  nop        
/* 0040bb44 */  beqz       $t7, 0x40bb58
/* 0040bb48 */  nop        
/* 0040bb4c */  lw         $a0, 0x84($s0)
/* 0040bb50 */  jal        0x40b550
/* 0040bb54 */  move       $a1, $t5
/* 0040bb58 */  b          0x40bbc8
/* 0040bb5c */  addiu      $v0, $zero, -1
/* 0040bb60 */  lh         $t8, 0x72($s0)
/* 0040bb64 */  nop        
/* 0040bb68 */  beqz       $t8, 0x40bb80
/* 0040bb6c */  nop        
/* 0040bb70 */  lw         $a0, 0x84($s0)
/* 0040bb74 */  lw         $a1, 0x28($sp)
/* 0040bb78 */  jal        0x40b550
/* 0040bb7c */  nop        
/* 0040bb80 */  lhu        $v0, 6($s0)
/* 0040bb84 */  b          0x40bbcc
/* 0040bb88 */  lw         $ra, 0x24($sp)
/* 0040bb8c */  lui        $a0, 0x1000
/* 0040bb90 */  jal        0x40b640
/* 0040bb94 */  addiu      $a0, $a0, 0x3144
/* 0040bb98 */  b          0x40bbcc
/* 0040bb9c */  lw         $ra, 0x24($sp)
/* 0040bba0 */  addiu      $at, $zero, 1
/* 0040bba4 */  beq        $v0, $at, 0x40b958
/* 0040bba8 */  addiu      $at, $zero, 2
/* 0040bbac */  beq        $v0, $at, 0x40ba44
/* 0040bbb0 */  nop        
/* 0040bbb4 */  b          0x40bb8c
/* 0040bbb8 */  nop        
/* 0040bbbc */  lui        $a0, 0x1000
/* 0040bbc0 */  jal        0x40b640
/* 0040bbc4 */  addiu      $a0, $a0, 0x3158
/* 0040bbc8 */  lw         $ra, 0x24($sp)
/* 0040bbcc */  lw         $s0, 0x20($sp)
/* 0040bbd0 */  jr         $ra
/* 0040bbd4 */  addiu      $sp, $sp, 0x40
/* 0040bbd8 */  addiu      $sp, $sp, -0x30
/* 0040bbdc */  sw         $s0, 0x18($sp)
/* 0040bbe0 */  move       $s0, $a0
/* 0040bbe4 */  sw         $ra, 0x1c($sp)
/* 0040bbe8 */  sw         $a1, 0x34($sp)
/* 0040bbec */  lhu        $t6, 0x70($s0)
/* 0040bbf0 */  move       $v1, $a2
/* 0040bbf4 */  andi       $t7, $t6, 0x81
/* 0040bbf8 */  bnez       $t7, 0x40bc08
/* 0040bbfc */  nop        
/* 0040bc00 */  b          0x40bec4
/* 0040bc04 */  addiu      $v0, $zero, -1
/* 0040bc08 */  lhu        $v0, 4($s0)
/* 0040bc0c */  nop        
/* 0040bc10 */  sltiu      $at, $v0, 3
/* 0040bc14 */  beqz       $at, 0x40bc24
/* 0040bc18 */  sltiu      $at, $v0, 2
/* 0040bc1c */  move       $a3, $zero
/* 0040bc20 */  sltiu      $at, $v0, 2
/* 0040bc24 */  beqz       $at, 0x40bc34
/* 0040bc28 */  move       $a0, $s0
/* 0040bc2c */  move       $v1, $zero
/* 0040bc30 */  move       $a0, $s0
/* 0040bc34 */  move       $a1, $v1
/* 0040bc38 */  jal        0x40c1b0
/* 0040bc3c */  move       $a2, $a3
/* 0040bc40 */  lhu        $v1, 2($s0)
/* 0040bc44 */  nop        
/* 0040bc48 */  andi       $v0, $v1, 0xff00
/* 0040bc4c */  bnez       $v0, 0x40bd74
/* 0040bc50 */  addiu      $at, $zero, 0x100
/* 0040bc54 */  andi       $a1, $v1, 0xff
/* 0040bc58 */  addiu      $at, $zero, 1
/* 0040bc5c */  beq        $a1, $at, 0x40bc74
/* 0040bc60 */  addiu      $at, $zero, 2
/* 0040bc64 */  beq        $a1, $at, 0x40bcf8
/* 0040bc68 */  nop        
/* 0040bc6c */  b          0x40bd5c
/* 0040bc70 */  nop        
/* 0040bc74 */  lw         $a1, 0x84($s0)
/* 0040bc78 */  lhu        $a2, 6($s0)
/* 0040bc7c */  jal        0x40c454
/* 0040bc80 */  move       $a0, $s0
/* 0040bc84 */  lhu        $a2, 6($s0)
/* 0040bc88 */  nop        
/* 0040bc8c */  beq        $v0, $a2, 0x40bca0
/* 0040bc90 */  move       $a3, $a2
/* 0040bc94 */  b          0x40bec4
/* 0040bc98 */  addiu      $v0, $zero, -1
/* 0040bc9c */  move       $a3, $a2
/* 0040bca0 */  sll        $v0, $a3, 0x10
/* 0040bca4 */  sra        $v0, $v0, 0x10
/* 0040bca8 */  move       $a1, $v0
/* 0040bcac */  addiu      $v0, $v0, -1
/* 0040bcb0 */  lw         $v1, 0x84($s0)
/* 0040bcb4 */  lw         $a0, 0x34($sp)
/* 0040bcb8 */  sll        $v0, $v0, 0x10
/* 0040bcbc */  beqz       $a1, 0x40bcf0
/* 0040bcc0 */  sra        $v0, $v0, 0x10
/* 0040bcc4 */  move       $a1, $v0
/* 0040bcc8 */  lbu        $t8, ($v1)
/* 0040bccc */  addiu      $v0, $v0, -1
/* 0040bcd0 */  sll        $v0, $v0, 0x10
/* 0040bcd4 */  sra        $v0, $v0, 0x10
/* 0040bcd8 */  addiu      $v1, $v1, 1
/* 0040bcdc */  addiu      $a0, $a0, 2
/* 0040bce0 */  bnez       $a1, 0x40bcc4
/* 0040bce4 */  sh         $t8, -2($a0)
/* 0040bce8 */  lhu        $a3, 6($s0)
/* 0040bcec */  nop        
/* 0040bcf0 */  b          0x40bec4
/* 0040bcf4 */  move       $v0, $a3
/* 0040bcf8 */  lhu        $v1, 6($s0)
/* 0040bcfc */  lw         $a1, 0x34($sp)
/* 0040bd00 */  sll        $v1, $v1, 1
/* 0040bd04 */  sll        $v1, $v1, 0x10
/* 0040bd08 */  sra        $v1, $v1, 0x10
/* 0040bd0c */  move       $a2, $v1
/* 0040bd10 */  sh         $v1, 0x20($sp)
/* 0040bd14 */  jal        0x40c454
/* 0040bd18 */  move       $a0, $s0
/* 0040bd1c */  lh         $v1, 0x20($sp)
/* 0040bd20 */  nop        
/* 0040bd24 */  beq        $v0, $v1, 0x40bd34
/* 0040bd28 */  nop        
/* 0040bd2c */  b          0x40bec4
/* 0040bd30 */  addiu      $v0, $zero, -1
/* 0040bd34 */  lh         $t9, 0x72($s0)
/* 0040bd38 */  nop        
/* 0040bd3c */  beqz       $t9, 0x40bd50
/* 0040bd40 */  nop        
/* 0040bd44 */  lw         $a0, 0x34($sp)
/* 0040bd48 */  jal        0x40b550
/* 0040bd4c */  move       $a1, $v1
/* 0040bd50 */  lhu        $v0, 6($s0)
/* 0040bd54 */  b          0x40bec8
/* 0040bd58 */  lw         $ra, 0x1c($sp)
/* 0040bd5c */  lui        $a0, 0x1000
/* 0040bd60 */  jal        0x40b640
/* 0040bd64 */  addiu      $a0, $a0, 0x3174
/* 0040bd68 */  b          0x40bec8
/* 0040bd6c */  lw         $ra, 0x1c($sp)
/* 0040bd70 */  addiu      $at, $zero, 0x100
/* 0040bd74 */  bne        $v0, $at, 0x40beb8
/* 0040bd78 */  nop        
/* 0040bd7c */  b          0x40be9c
/* 0040bd80 */  andi       $a1, $v1, 0xff
/* 0040bd84 */  jal        0x40c500
/* 0040bd88 */  move       $a0, $s0
/* 0040bd8c */  sll        $t0, $v0, 0x10
/* 0040bd90 */  sra        $t1, $t0, 0x10
/* 0040bd94 */  sll        $v1, $v0, 0x10
/* 0040bd98 */  addiu      $at, $zero, -1
/* 0040bd9c */  bne        $t1, $at, 0x40bdac
/* 0040bda0 */  sra        $v1, $v1, 0x10
/* 0040bda4 */  b          0x40bec4
/* 0040bda8 */  addiu      $v0, $zero, -1
/* 0040bdac */  lw         $a1, 0x84($s0)
/* 0040bdb0 */  sh         $v1, 0x20($sp)
/* 0040bdb4 */  move       $a0, $s0
/* 0040bdb8 */  jal        0x40c454
/* 0040bdbc */  move       $a2, $v1
/* 0040bdc0 */  lh         $v1, 0x20($sp)
/* 0040bdc4 */  nop        
/* 0040bdc8 */  beq        $v0, $v1, 0x40bdd8
/* 0040bdcc */  nop        
/* 0040bdd0 */  b          0x40bec4
/* 0040bdd4 */  addiu      $v0, $zero, -1
/* 0040bdd8 */  lw         $a0, 0x84($s0)
/* 0040bddc */  lw         $a2, 0x34($sp)
/* 0040bde0 */  addiu      $a1, $zero, 1
/* 0040bde4 */  jal        0x40ce2c
/* 0040bde8 */  addiu      $a3, $zero, 2
/* 0040bdec */  lhu        $v0, 6($s0)
/* 0040bdf0 */  b          0x40bec8
/* 0040bdf4 */  lw         $ra, 0x1c($sp)
/* 0040bdf8 */  jal        0x40c500
/* 0040bdfc */  move       $a0, $s0
/* 0040be00 */  sll        $t2, $v0, 0x10
/* 0040be04 */  sra        $t3, $t2, 0x10
/* 0040be08 */  sll        $v1, $v0, 0x10
/* 0040be0c */  addiu      $at, $zero, -1
/* 0040be10 */  bne        $t3, $at, 0x40be20
/* 0040be14 */  sra        $v1, $v1, 0x10
/* 0040be18 */  b          0x40bec4
/* 0040be1c */  addiu      $v0, $zero, -1
/* 0040be20 */  lw         $a1, 0x84($s0)
/* 0040be24 */  sh         $v1, 0x20($sp)
/* 0040be28 */  move       $a0, $s0
/* 0040be2c */  jal        0x40c454
/* 0040be30 */  move       $a2, $v1
/* 0040be34 */  lh         $v1, 0x20($sp)
/* 0040be38 */  nop        
/* 0040be3c */  beq        $v1, $v0, 0x40be4c
/* 0040be40 */  nop        
/* 0040be44 */  b          0x40bec4
/* 0040be48 */  addiu      $v0, $zero, -1
/* 0040be4c */  lh         $t4, 0x72($s0)
/* 0040be50 */  nop        
/* 0040be54 */  beqz       $t4, 0x40be68
/* 0040be58 */  nop        
/* 0040be5c */  lw         $a0, 0x84($s0)
/* 0040be60 */  jal        0x40b550
/* 0040be64 */  move       $a1, $v1
/* 0040be68 */  lw         $a0, 0x84($s0)
/* 0040be6c */  lw         $a2, 0x34($sp)
/* 0040be70 */  addiu      $a1, $zero, 2
/* 0040be74 */  jal        0x40ce2c
/* 0040be78 */  addiu      $a3, $zero, 2
/* 0040be7c */  lhu        $v0, 6($s0)
/* 0040be80 */  b          0x40bec8
/* 0040be84 */  lw         $ra, 0x1c($sp)
/* 0040be88 */  lui        $a0, 0x1000
/* 0040be8c */  jal        0x40b640
/* 0040be90 */  addiu      $a0, $a0, 0x3188
/* 0040be94 */  b          0x40bec8
/* 0040be98 */  lw         $ra, 0x1c($sp)
/* 0040be9c */  addiu      $at, $zero, 1
/* 0040bea0 */  beq        $a1, $at, 0x40bd84
/* 0040bea4 */  addiu      $at, $zero, 2
/* 0040bea8 */  beq        $a1, $at, 0x40bdf8
/* 0040beac */  nop        
/* 0040beb0 */  b          0x40be88
/* 0040beb4 */  nop        
/* 0040beb8 */  lui        $a0, 0x1000
/* 0040bebc */  jal        0x40b640
/* 0040bec0 */  addiu      $a0, $a0, 0x319c
/* 0040bec4 */  lw         $ra, 0x1c($sp)
/* 0040bec8 */  lw         $s0, 0x18($sp)
/* 0040becc */  jr         $ra
/* 0040bed0 */  addiu      $sp, $sp, 0x30
/* 0040bed4 */  nop        
/* 0040bed8 */  nop        
/* 0040bedc */  nop        
/* 0040bee0 */  addiu      $sp, $sp, -0x28
/* 0040bee4 */  sw         $s0, 0x18($sp)
/* 0040bee8 */  move       $s0, $a0
/* 0040beec */  sw         $ra, 0x1c($sp)
/* 0040bef0 */  jal        0x40c0dc
/* 0040bef4 */  move       $a0, $s0
/* 0040bef8 */  move       $a0, $s0
/* 0040befc */  jal        0x40c4ac
/* 0040bf00 */  move       $a1, $zero
/* 0040bf04 */  lhu        $t6, 0x70($s0)
/* 0040bf08 */  nop        
/* 0040bf0c */  andi       $t7, $t6, 2
/* 0040bf10 */  beqz       $t7, 0x40c058
/* 0040bf14 */  nop        
/* 0040bf18 */  lh         $t8, 0x72($s0)
/* 0040bf1c */  nop        
/* 0040bf20 */  beqz       $t8, 0x40bf34
/* 0040bf24 */  move       $a0, $s0
/* 0040bf28 */  jal        0x40b5f8
/* 0040bf2c */  move       $a0, $s0
/* 0040bf30 */  move       $a0, $s0
/* 0040bf34 */  move       $a1, $s0
/* 0040bf38 */  jal        0x40c3fc
/* 0040bf3c */  addiu      $a2, $zero, 0x98
/* 0040bf40 */  addiu      $at, $zero, 0x98
/* 0040bf44 */  beq        $v0, $at, 0x40bf60
/* 0040bf48 */  nop        
/* 0040bf4c */  lui        $a0, 0x1000
/* 0040bf50 */  jal        0x40b640
/* 0040bf54 */  addiu      $a0, $a0, 0x31c0
/* 0040bf58 */  b          0x40c0cc
/* 0040bf5c */  addiu      $v0, $zero, -1
/* 0040bf60 */  lh         $t9, 0x72($s0)
/* 0040bf64 */  nop        
/* 0040bf68 */  beqz       $t9, 0x40bf78
/* 0040bf6c */  nop        
/* 0040bf70 */  jal        0x40b5f8
/* 0040bf74 */  move       $a0, $s0
/* 0040bf78 */  lhu        $t0, 2($s0)
/* 0040bf7c */  addiu      $at, $zero, 0x100
/* 0040bf80 */  andi       $t1, $t0, 0xff00
/* 0040bf84 */  bne        $t1, $at, 0x40c058
/* 0040bf88 */  nop        
/* 0040bf8c */  move       $a0, $s0
/* 0040bf90 */  jal        0x40c4ac
/* 0040bf94 */  addiu      $a1, $zero, 0x200
/* 0040bf98 */  lhu        $t2, 8($s0)
/* 0040bf9c */  lhu        $t3, 0xa($s0)
/* 0040bfa0 */  nop        
/* 0040bfa4 */  multu      $t2, $t3
/* 0040bfa8 */  mflo       $t4
/* 0040bfac */  sll        $t5, $t4, 2
/* 0040bfb0 */  sw         $t5, 0x24($sp)
/* 0040bfb4 */  lh         $t6, 0x72($s0)
/* 0040bfb8 */  nop        
/* 0040bfbc */  beqz       $t6, 0x40bfd0
/* 0040bfc0 */  nop        
/* 0040bfc4 */  lw         $a0, 0x90($s0)
/* 0040bfc8 */  jal        0x40b594
/* 0040bfcc */  move       $a1, $t5
/* 0040bfd0 */  lw         $a1, 0x90($s0)
/* 0040bfd4 */  lw         $a2, 0x24($sp)
/* 0040bfd8 */  jal        0x40c3fc
/* 0040bfdc */  move       $a0, $s0
/* 0040bfe0 */  lw         $a2, 0x24($sp)
/* 0040bfe4 */  nop        
/* 0040bfe8 */  beq        $v0, $a2, 0x40c004
/* 0040bfec */  nop        
/* 0040bff0 */  lui        $a0, 0x1000
/* 0040bff4 */  jal        0x40b640
/* 0040bff8 */  addiu      $a0, $a0, 0x31e8
/* 0040bffc */  b          0x40c0cc
/* 0040c000 */  addiu      $v0, $zero, -1
/* 0040c004 */  lh         $t7, 0x72($s0)
/* 0040c008 */  nop        
/* 0040c00c */  beqz       $t7, 0x40c028
/* 0040c010 */  nop        
/* 0040c014 */  lw         $a0, 0x94($s0)
/* 0040c018 */  jal        0x40b594
/* 0040c01c */  move       $a1, $a2
/* 0040c020 */  lw         $a2, 0x24($sp)
/* 0040c024 */  nop        
/* 0040c028 */  lw         $a1, 0x94($s0)
/* 0040c02c */  jal        0x40c3fc
/* 0040c030 */  move       $a0, $s0
/* 0040c034 */  lw         $t8, 0x24($sp)
/* 0040c038 */  nop        
/* 0040c03c */  beq        $v0, $t8, 0x40c058
/* 0040c040 */  nop        
/* 0040c044 */  lui        $a0, 0x1000
/* 0040c048 */  jal        0x40b640
/* 0040c04c */  addiu      $a0, $a0, 0x320c
/* 0040c050 */  b          0x40c0cc
/* 0040c054 */  addiu      $v0, $zero, -1
/* 0040c058 */  lw         $a0, 0x80($s0)
/* 0040c05c */  nop        
/* 0040c060 */  beqz       $a0, 0x40c074
/* 0040c064 */  nop        
/* 0040c068 */  jal        0xf801200                                # malloc
/* 0040c06c */  nop        
/* 0040c070 */  sw         $zero, 0x80($s0)
/* 0040c074 */  lw         $a0, 0x84($s0)
/* 0040c078 */  nop        
/* 0040c07c */  beqz       $a0, 0x40c090
/* 0040c080 */  nop        
/* 0040c084 */  jal        0xf801200                                # malloc
/* 0040c088 */  nop        
/* 0040c08c */  sw         $zero, 0x84($s0)
/* 0040c090 */  lhu        $t9, 2($s0)
/* 0040c094 */  addiu      $at, $zero, 0x100
/* 0040c098 */  andi       $t0, $t9, 0xff00
/* 0040c09c */  bne        $t0, $at, 0x40c0c0
/* 0040c0a0 */  nop        
/* 0040c0a4 */  lw         $a0, 0x90($s0)
/* 0040c0a8 */  jal        0xf801200                                # malloc
/* 0040c0ac */  nop        
/* 0040c0b0 */  lw         $a0, 0x94($s0)
/* 0040c0b4 */  jal        0xf801200                                # malloc
/* 0040c0b8 */  sw         $zero, 0x90($s0)
/* 0040c0bc */  sw         $zero, 0x94($s0)
/* 0040c0c0 */  lw         $a0, 0x6c($s0)
/* 0040c0c4 */  jal        0x40dfa0
/* 0040c0c8 */  nop        
/* 0040c0cc */  lw         $ra, 0x1c($sp)
/* 0040c0d0 */  lw         $s0, 0x18($sp)
/* 0040c0d4 */  jr         $ra
/* 0040c0d8 */  addiu      $sp, $sp, 0x28
/* 0040c0dc */  addiu      $sp, $sp, -0x18
/* 0040c0e0 */  sw         $ra, 0x14($sp)
/* 0040c0e4 */  lhu        $t6, 0x70($a0)
/* 0040c0e8 */  nop        
/* 0040c0ec */  andi       $t7, $t6, 2
/* 0040c0f0 */  beqz       $t7, 0x40c168
/* 0040c0f4 */  lw         $ra, 0x14($sp)
/* 0040c0f8 */  lw         $a1, 0x80($a0)
/* 0040c0fc */  nop        
/* 0040c100 */  beqz       $a1, 0x40c168
/* 0040c104 */  lw         $ra, 0x14($sp)
/* 0040c108 */  lw         $t8, 0x7c($a0)
/* 0040c10c */  nop        
/* 0040c110 */  subu       $t9, $t8, $a1
/* 0040c114 */  bgez       $t9, 0x40c120
/* 0040c118 */  move       $at, $t9
/* 0040c11c */  addiu      $at, $at, 1
/* 0040c120 */  sra        $t0, $at, 1
/* 0040c124 */  blez       $t0, 0x40c168
/* 0040c128 */  lw         $ra, 0x14($sp)
/* 0040c12c */  lh         $a2, 0x76($a0)
/* 0040c130 */  lh         $a3, 0x78($a0)
/* 0040c134 */  jal        0x40b6e0
/* 0040c138 */  sw         $a0, 0x18($sp)
/* 0040c13c */  lw         $a0, 0x18($sp)
/* 0040c140 */  nop        
/* 0040c144 */  lhu        $t1, 6($a0)
/* 0040c148 */  nop        
/* 0040c14c */  beq        $v0, $t1, 0x40c168
/* 0040c150 */  lw         $ra, 0x14($sp)
/* 0040c154 */  lhu        $t2, 0x70($a0)
/* 0040c158 */  addiu      $v0, $zero, -1
/* 0040c15c */  ori        $t3, $t2, 0x20
/* 0040c160 */  sh         $t3, 0x70($a0)
/* 0040c164 */  lw         $ra, 0x14($sp)
/* 0040c168 */  addiu      $sp, $sp, 0x18
/* 0040c16c */  jr         $ra
/* 0040c170 */  nop        
/* 0040c174 */  nop        
/* 0040c178 */  nop        
/* 0040c17c */  nop        
/* 0040c180 */  addiu      $sp, $sp, -0x18
/* 0040c184 */  sw         $ra, 0x14($sp)
/* 0040c188 */  move       $v1, $a0
/* 0040c18c */  addiu      $a0, $v1, 0x18
/* 0040c190 */  jal        0xf801320                                # read
/* 0040c194 */  addiu      $a2, $zero, 0x50
/* 0040c198 */  lw         $ra, 0x14($sp)
/* 0040c19c */  addiu      $sp, $sp, 0x18
/* 0040c1a0 */  jr         $ra
/* 0040c1a4 */  nop        
/* 0040c1a8 */  jr         $ra
/* 0040c1ac */  sw         $a1, 0x68($a0)
/* 0040c1b0 */  addiu      $sp, $sp, -0x18
/* 0040c1b4 */  sw         $ra, 0x14($sp)
/* 0040c1b8 */  move       $a3, $a1
/* 0040c1bc */  sw         $a3, 0x1c($sp)
/* 0040c1c0 */  sw         $a0, 0x18($sp)
/* 0040c1c4 */  move       $a1, $a3
/* 0040c1c8 */  jal        0x40c3c0
/* 0040c1cc */  sw         $a2, 0x20($sp)
/* 0040c1d0 */  lw         $a0, 0x18($sp)
/* 0040c1d4 */  lw         $a2, 0x20($sp)
/* 0040c1d8 */  lw         $a3, 0x1c($sp)
/* 0040c1dc */  beqz       $v0, 0x40c1f8
/* 0040c1e0 */  nop        
/* 0040c1e4 */  lui        $a0, 0x1000
/* 0040c1e8 */  jal        0x40b640
/* 0040c1ec */  addiu      $a0, $a0, 0x3230
/* 0040c1f0 */  b          0x40c3b0
/* 0040c1f4 */  addiu      $v0, $zero, -1
/* 0040c1f8 */  lhu        $v1, 2($a0)
/* 0040c1fc */  sh         $zero, 0x74($a0)
/* 0040c200 */  andi       $v0, $v1, 0xff00
/* 0040c204 */  sh         $a3, 0x76($a0)
/* 0040c208 */  bnez       $v0, 0x40c2e8
/* 0040c20c */  sh         $a2, 0x78($a0)
/* 0040c210 */  lhu        $v0, 4($a0)
/* 0040c214 */  addiu      $at, $zero, 1
/* 0040c218 */  beq        $v0, $at, 0x40c238
/* 0040c21c */  addiu      $at, $zero, 2
/* 0040c220 */  beq        $v0, $at, 0x40c248
/* 0040c224 */  addiu      $at, $zero, 3
/* 0040c228 */  beq        $v0, $at, 0x40c27c
/* 0040c22c */  nop        
/* 0040c230 */  b          0x40c2d4
/* 0040c234 */  nop        
/* 0040c238 */  jal        0x40c4ac
/* 0040c23c */  addiu      $a1, $zero, 0x200
/* 0040c240 */  b          0x40c3b4
/* 0040c244 */  lw         $ra, 0x14($sp)
/* 0040c248 */  lhu        $t6, 6($a0)
/* 0040c24c */  andi       $t8, $v1, 0xff
/* 0040c250 */  multu      $a3, $t6
/* 0040c254 */  mflo       $t7
/* 0040c258 */  nop        
/* 0040c25c */  nop        
/* 0040c260 */  multu      $t7, $t8
/* 0040c264 */  mflo       $a1
/* 0040c268 */  addiu      $a1, $a1, 0x200
/* 0040c26c */  jal        0x40c4ac
/* 0040c270 */  nop        
/* 0040c274 */  b          0x40c3b4
/* 0040c278 */  lw         $ra, 0x14($sp)
/* 0040c27c */  lhu        $v0, 6($a0)
/* 0040c280 */  lhu        $t0, 8($a0)
/* 0040c284 */  multu      $a2, $v0
/* 0040c288 */  andi       $t4, $v1, 0xff
/* 0040c28c */  mflo       $t9
/* 0040c290 */  nop        
/* 0040c294 */  nop        
/* 0040c298 */  multu      $t9, $t0
/* 0040c29c */  mflo       $t1
/* 0040c2a0 */  nop        
/* 0040c2a4 */  nop        
/* 0040c2a8 */  multu      $a3, $v0
/* 0040c2ac */  mflo       $t2
/* 0040c2b0 */  addu       $t3, $t2, $t1
/* 0040c2b4 */  nop        
/* 0040c2b8 */  multu      $t3, $t4
/* 0040c2bc */  mflo       $a1
/* 0040c2c0 */  addiu      $a1, $a1, 0x200
/* 0040c2c4 */  jal        0x40c4ac
/* 0040c2c8 */  nop        
/* 0040c2cc */  b          0x40c3b4
/* 0040c2d0 */  lw         $ra, 0x14($sp)
/* 0040c2d4 */  lui        $a0, 0x1000
/* 0040c2d8 */  jal        0x40b640
/* 0040c2dc */  addiu      $a0, $a0, 0x3254
/* 0040c2e0 */  b          0x40c3b4
/* 0040c2e4 */  lw         $ra, 0x14($sp)
/* 0040c2e8 */  addiu      $at, $zero, 0x100
/* 0040c2ec */  bne        $v0, $at, 0x40c3a4
/* 0040c2f0 */  nop        
/* 0040c2f4 */  lhu        $v0, 4($a0)
/* 0040c2f8 */  b          0x40c384
/* 0040c2fc */  addiu      $at, $zero, 1
/* 0040c300 */  lw         $t5, 0x90($a0)
/* 0040c304 */  nop        
/* 0040c308 */  lw         $a1, ($t5)
/* 0040c30c */  jal        0x40c4ac
/* 0040c310 */  nop        
/* 0040c314 */  b          0x40c3b4
/* 0040c318 */  lw         $ra, 0x14($sp)
/* 0040c31c */  lw         $t6, 0x90($a0)
/* 0040c320 */  sll        $t7, $a3, 2
/* 0040c324 */  addu       $t8, $t6, $t7
/* 0040c328 */  lw         $a1, ($t8)
/* 0040c32c */  jal        0x40c4ac
/* 0040c330 */  nop        
/* 0040c334 */  b          0x40c3b4
/* 0040c338 */  lw         $ra, 0x14($sp)
/* 0040c33c */  lhu        $t0, 8($a0)
/* 0040c340 */  lw         $t9, 0x90($a0)
/* 0040c344 */  multu      $a2, $t0
/* 0040c348 */  mflo       $t2
/* 0040c34c */  addu       $t1, $a3, $t2
/* 0040c350 */  sll        $t3, $t1, 2
/* 0040c354 */  addu       $t4, $t9, $t3
/* 0040c358 */  lw         $a1, ($t4)
/* 0040c35c */  jal        0x40c4ac
/* 0040c360 */  nop        
/* 0040c364 */  b          0x40c3b4
/* 0040c368 */  lw         $ra, 0x14($sp)
/* 0040c36c */  lui        $a0, 0x1000
/* 0040c370 */  jal        0x40b640
/* 0040c374 */  addiu      $a0, $a0, 0x326c
/* 0040c378 */  b          0x40c3b4
/* 0040c37c */  lw         $ra, 0x14($sp)
/* 0040c380 */  addiu      $at, $zero, 1
/* 0040c384 */  beq        $v0, $at, 0x40c300
/* 0040c388 */  addiu      $at, $zero, 2
/* 0040c38c */  beq        $v0, $at, 0x40c31c
/* 0040c390 */  addiu      $at, $zero, 3
/* 0040c394 */  beq        $v0, $at, 0x40c33c
/* 0040c398 */  nop        
/* 0040c39c */  b          0x40c36c
/* 0040c3a0 */  nop        
/* 0040c3a4 */  lui        $a0, 0x1000
/* 0040c3a8 */  jal        0x40b640
/* 0040c3ac */  addiu      $a0, $a0, 0x3284
/* 0040c3b0 */  lw         $ra, 0x14($sp)
/* 0040c3b4 */  addiu      $sp, $sp, 0x18
/* 0040c3b8 */  jr         $ra
/* 0040c3bc */  nop        
/* 0040c3c0 */  lhu        $t6, 8($a0)
/* 0040c3c4 */  nop        
/* 0040c3c8 */  sltu       $at, $a1, $t6
/* 0040c3cc */  beqz       $at, 0x40c3e8
/* 0040c3d0 */  nop        
/* 0040c3d4 */  lhu        $t7, 0xa($a0)
/* 0040c3d8 */  nop        
/* 0040c3dc */  sltu       $at, $a2, $t7
/* 0040c3e0 */  bnez       $at, 0x40c3f4
/* 0040c3e4 */  move       $v0, $zero
/* 0040c3e8 */  jr         $ra
/* 0040c3ec */  addiu      $v0, $zero, 1
/* 0040c3f0 */  move       $v0, $zero
/* 0040c3f4 */  jr         $ra
/* 0040c3f8 */  nop        
/* 0040c3fc */  addiu      $sp, $sp, -0x18
/* 0040c400 */  sw         $ra, 0x14($sp)
/* 0040c404 */  move       $v1, $a0
/* 0040c408 */  lw         $a0, 0x6c($v1)
/* 0040c40c */  sw         $a2, 0x20($sp)
/* 0040c410 */  jal        0x40dfe0
/* 0040c414 */  sw         $v1, 0x18($sp)
/* 0040c418 */  lw         $a2, 0x20($sp)
/* 0040c41c */  lw         $v1, 0x18($sp)
/* 0040c420 */  bne        $v0, $a2, 0x40c43c
/* 0040c424 */  move       $a0, $v0
/* 0040c428 */  lw         $t6, 0x88($v1)
/* 0040c42c */  nop        
/* 0040c430 */  addu       $t7, $t6, $a2
/* 0040c434 */  b          0x40c444
/* 0040c438 */  sw         $t7, 0x88($v1)
/* 0040c43c */  addiu      $t8, $zero, -1
/* 0040c440 */  sw         $t8, 0x88($v1)
/* 0040c444 */  lw         $ra, 0x14($sp)
/* 0040c448 */  addiu      $sp, $sp, 0x18
/* 0040c44c */  jr         $ra
/* 0040c450 */  move       $v0, $a0
/* 0040c454 */  addiu      $sp, $sp, -0x18
/* 0040c458 */  sw         $ra, 0x14($sp)
/* 0040c45c */  move       $v1, $a0
/* 0040c460 */  lw         $a0, 0x6c($v1)
/* 0040c464 */  sw         $a2, 0x20($sp)
/* 0040c468 */  jal        0x40e000
/* 0040c46c */  sw         $v1, 0x18($sp)
/* 0040c470 */  lw         $a2, 0x20($sp)
/* 0040c474 */  lw         $v1, 0x18($sp)
/* 0040c478 */  bne        $v0, $a2, 0x40c494
/* 0040c47c */  move       $a0, $v0
/* 0040c480 */  lw         $t6, 0x88($v1)
/* 0040c484 */  nop        
/* 0040c488 */  addu       $t7, $t6, $a2
/* 0040c48c */  b          0x40c49c
/* 0040c490 */  sw         $t7, 0x88($v1)
/* 0040c494 */  addiu      $t8, $zero, -1
/* 0040c498 */  sw         $t8, 0x88($v1)
/* 0040c49c */  lw         $ra, 0x14($sp)
/* 0040c4a0 */  addiu      $sp, $sp, 0x18
/* 0040c4a4 */  jr         $ra
/* 0040c4a8 */  move       $v0, $a0
/* 0040c4ac */  addiu      $sp, $sp, -0x18
/* 0040c4b0 */  sw         $ra, 0x14($sp)
/* 0040c4b4 */  move       $v1, $a0
/* 0040c4b8 */  lw         $t6, 0x88($v1)
/* 0040c4bc */  nop        
/* 0040c4c0 */  beq        $a1, $t6, 0x40c4e4
/* 0040c4c4 */  move       $v0, $a1
/* 0040c4c8 */  lw         $a0, 0x6c($v1)
/* 0040c4cc */  sw         $a1, 0x88($v1)
/* 0040c4d0 */  jal        0x40e020
/* 0040c4d4 */  move       $a2, $zero
/* 0040c4d8 */  b          0x40c4e8
/* 0040c4dc */  lw         $ra, 0x14($sp)
/* 0040c4e0 */  move       $v0, $a1
/* 0040c4e4 */  lw         $ra, 0x14($sp)
/* 0040c4e8 */  addiu      $sp, $sp, 0x18
/* 0040c4ec */  jr         $ra
/* 0040c4f0 */  nop        
/* 0040c4f4 */  nop        
/* 0040c4f8 */  nop        
/* 0040c4fc */  nop        
/* 0040c500 */  lhu        $v0, 4($a0)
/* 0040c504 */  b          0x40c570
/* 0040c508 */  addiu      $at, $zero, 1
/* 0040c50c */  lw         $t6, 0x94($a0)
/* 0040c510 */  nop        
/* 0040c514 */  lw         $v0, ($t6)
/* 0040c518 */  jr         $ra
/* 0040c51c */  nop        
/* 0040c520 */  lh         $t8, 0x76($a0)
/* 0040c524 */  lw         $t7, 0x94($a0)
/* 0040c528 */  sll        $t9, $t8, 2
/* 0040c52c */  addu       $t0, $t7, $t9
/* 0040c530 */  lw         $v0, ($t0)
/* 0040c534 */  jr         $ra
/* 0040c538 */  nop        
/* 0040c53c */  lh         $t1, 0x78($a0)
/* 0040c540 */  lhu        $t2, 8($a0)
/* 0040c544 */  lh         $t4, 0x76($a0)
/* 0040c548 */  multu      $t1, $t2
/* 0040c54c */  lw         $t8, 0x94($a0)
/* 0040c550 */  mflo       $t3
/* 0040c554 */  addu       $t5, $t4, $t3
/* 0040c558 */  sll        $t6, $t5, 2
/* 0040c55c */  addu       $t7, $t8, $t6
/* 0040c560 */  lw         $v0, ($t7)
/* 0040c564 */  jr         $ra
/* 0040c568 */  nop        
/* 0040c56c */  addiu      $at, $zero, 1
/* 0040c570 */  beq        $v0, $at, 0x40c50c
/* 0040c574 */  addiu      $at, $zero, 2
/* 0040c578 */  beq        $v0, $at, 0x40c520
/* 0040c57c */  addiu      $at, $zero, 3
/* 0040c580 */  beq        $v0, $at, 0x40c53c
/* 0040c584 */  nop        
/* 0040c588 */  jr         $ra
/* 0040c58c */  nop        
/* 0040c590 */  addiu      $sp, $sp, -0x20
/* 0040c594 */  sw         $a3, 0x2c($sp)
/* 0040c598 */  move       $v1, $a2
/* 0040c59c */  sw         $ra, 0x14($sp)
/* 0040c5a0 */  sw         $a1, 0x24($sp)
/* 0040c5a4 */  lw         $a2, 0x2c($sp)
/* 0040c5a8 */  sw         $v1, 0x28($sp)
/* 0040c5ac */  move       $a1, $v1
/* 0040c5b0 */  jal        0x40c3c0
/* 0040c5b4 */  sw         $a0, 0x20($sp)
/* 0040c5b8 */  lw         $v1, 0x28($sp)
/* 0040c5bc */  lw         $a0, 0x20($sp)
/* 0040c5c0 */  lw         $a2, 0x24($sp)
/* 0040c5c4 */  bnez       $v0, 0x40c69c
/* 0040c5c8 */  lw         $ra, 0x14($sp)
/* 0040c5cc */  lhu        $v0, 4($a0)
/* 0040c5d0 */  b          0x40c644
/* 0040c5d4 */  addiu      $at, $zero, 1
/* 0040c5d8 */  lw         $t6, 0x8c($a0)
/* 0040c5dc */  lw         $t7, 0x90($a0)
/* 0040c5e0 */  lw         $a1, 0x94($a0)
/* 0040c5e4 */  b          0x40c664
/* 0040c5e8 */  sw         $t6, ($t7)
/* 0040c5ec */  lw         $t0, 0x90($a0)
/* 0040c5f0 */  lw         $t8, 0x94($a0)
/* 0040c5f4 */  lw         $t9, 0x8c($a0)
/* 0040c5f8 */  sll        $v0, $v1, 2
/* 0040c5fc */  addu       $t1, $t0, $v0
/* 0040c600 */  addu       $a1, $t8, $v0
/* 0040c604 */  b          0x40c664
/* 0040c608 */  sw         $t9, ($t1)
/* 0040c60c */  lw         $t2, 0x2c($sp)
/* 0040c610 */  lhu        $t3, 8($a0)
/* 0040c614 */  lw         $t7, 0x90($a0)
/* 0040c618 */  multu      $t2, $t3
/* 0040c61c */  lw         $t5, 0x94($a0)
/* 0040c620 */  lw         $t6, 0x8c($a0)
/* 0040c624 */  mflo       $t4
/* 0040c628 */  addu       $v0, $v1, $t4
/* 0040c62c */  sll        $v0, $v0, 2
/* 0040c630 */  addu       $t8, $t7, $v0
/* 0040c634 */  addu       $a1, $t5, $v0
/* 0040c638 */  b          0x40c664
/* 0040c63c */  sw         $t6, ($t8)
/* 0040c640 */  addiu      $at, $zero, 1
/* 0040c644 */  beq        $v0, $at, 0x40c5d8
/* 0040c648 */  addiu      $at, $zero, 2
/* 0040c64c */  beq        $v0, $at, 0x40c5ec
/* 0040c650 */  addiu      $at, $zero, 3
/* 0040c654 */  beq        $v0, $at, 0x40c610
/* 0040c658 */  lw         $t2, 0x2c($sp)
/* 0040c65c */  lw         $a1, 0x1c($sp)
/* 0040c660 */  nop        
/* 0040c664 */  lw         $v0, ($a1)
/* 0040c668 */  addiu      $at, $zero, -1
/* 0040c66c */  beq        $v0, $at, 0x40c684
/* 0040c670 */  nop        
/* 0040c674 */  lw         $t0, 0x14($a0)
/* 0040c678 */  nop        
/* 0040c67c */  addu       $t9, $t0, $v0
/* 0040c680 */  sw         $t9, 0x14($a0)
/* 0040c684 */  sw         $a2, ($a1)
/* 0040c688 */  lw         $t1, 0x8c($a0)
/* 0040c68c */  nop        
/* 0040c690 */  addu       $t2, $t1, $a2
/* 0040c694 */  sw         $t2, 0x8c($a0)
/* 0040c698 */  lw         $ra, 0x14($sp)
/* 0040c69c */  addiu      $sp, $sp, 0x20
/* 0040c6a0 */  jr         $ra
/* 0040c6a4 */  nop        
/* 0040c6a8 */  addiu      $sp, $sp, -0x18
/* 0040c6ac */  addiu      $v0, $zero, 1
/* 0040c6b0 */  sw         $ra, 0x14($sp)
/* 0040c6b4 */  bne        $a1, $v0, 0x40c86c
/* 0040c6b8 */  move       $t1, $a2
/* 0040c6bc */  bne        $a3, $v0, 0x40c86c
/* 0040c6c0 */  nop        
/* 0040c6c4 */  lw         $t6, 0x28($sp)
/* 0040c6c8 */  move       $a3, $a0
/* 0040c6cc */  addu       $t0, $a0, $t6
/* 0040c6d0 */  sltu       $at, $a0, $t0
/* 0040c6d4 */  beqz       $at, 0x40c85c
/* 0040c6d8 */  move       $a1, $t1
/* 0040c6dc */  move       $a0, $a3
/* 0040c6e0 */  addiu      $a3, $a3, 2
/* 0040c6e4 */  sltu       $at, $a3, $t0
/* 0040c6e8 */  beqz       $at, 0x40c748
/* 0040c6ec */  nop        
/* 0040c6f0 */  lbu        $v0, -1($a3)
/* 0040c6f4 */  lbu        $t7, -2($a3)
/* 0040c6f8 */  nop        
/* 0040c6fc */  bne        $v0, $t7, 0x40c714
/* 0040c700 */  nop        
/* 0040c704 */  lbu        $t8, ($a3)
/* 0040c708 */  nop        
/* 0040c70c */  beq        $t8, $v0, 0x40c748
/* 0040c710 */  nop        
/* 0040c714 */  addiu      $a3, $a3, 1
/* 0040c718 */  sltu       $at, $a3, $t0
/* 0040c71c */  beqz       $at, 0x40c748
/* 0040c720 */  nop        
/* 0040c724 */  lbu        $v0, -1($a3)
/* 0040c728 */  lbu        $t9, -2($a3)
/* 0040c72c */  nop        
/* 0040c730 */  bne        $v0, $t9, 0x40c714
/* 0040c734 */  nop        
/* 0040c738 */  lbu        $t2, ($a3)
/* 0040c73c */  nop        
/* 0040c740 */  bne        $t2, $v0, 0x40c714
/* 0040c744 */  nop        
/* 0040c748 */  addiu      $a3, $a3, -2
/* 0040c74c */  subu       $v0, $a3, $a0
/* 0040c750 */  beqz       $v0, 0x40c7c4
/* 0040c754 */  move       $a2, $v0
/* 0040c758 */  slti       $at, $a2, 0x7f
/* 0040c75c */  bnez       $at, 0x40c770
/* 0040c760 */  sll        $v1, $a2, 0x10
/* 0040c764 */  b          0x40c774
/* 0040c768 */  addiu      $v1, $zero, 0x7e
/* 0040c76c */  sll        $v1, $a2, 0x10
/* 0040c770 */  sra        $v1, $v1, 0x10
/* 0040c774 */  subu       $a2, $a2, $v1
/* 0040c778 */  ori        $t3, $v1, 0x80
/* 0040c77c */  move       $v0, $v1
/* 0040c780 */  addiu      $v1, $v1, -1
/* 0040c784 */  sll        $v1, $v1, 0x10
/* 0040c788 */  sra        $v1, $v1, 0x10
/* 0040c78c */  sb         $t3, ($a1)
/* 0040c790 */  beqz       $v0, 0x40c7bc
/* 0040c794 */  addiu      $a1, $a1, 1
/* 0040c798 */  move       $v0, $v1
/* 0040c79c */  lbu        $t4, ($a0)
/* 0040c7a0 */  addiu      $v1, $v1, -1
/* 0040c7a4 */  sll        $v1, $v1, 0x10
/* 0040c7a8 */  sra        $v1, $v1, 0x10
/* 0040c7ac */  addiu      $a0, $a0, 1
/* 0040c7b0 */  addiu      $a1, $a1, 1
/* 0040c7b4 */  bnez       $v0, 0x40c798
/* 0040c7b8 */  sb         $t4, -1($a1)
/* 0040c7bc */  bnez       $a2, 0x40c75c
/* 0040c7c0 */  slti       $at, $a2, 0x7f
/* 0040c7c4 */  move       $a0, $a3
/* 0040c7c8 */  addiu      $a3, $a3, 1
/* 0040c7cc */  sltu       $at, $a3, $t0
/* 0040c7d0 */  lbu        $v1, -1($a3)
/* 0040c7d4 */  beqz       $at, 0x40c810
/* 0040c7d8 */  subu       $v0, $a3, $a0
/* 0040c7dc */  lbu        $t5, ($a3)
/* 0040c7e0 */  move       $v0, $v1
/* 0040c7e4 */  bne        $v0, $t5, 0x40c80c
/* 0040c7e8 */  nop        
/* 0040c7ec */  addiu      $a3, $a3, 1
/* 0040c7f0 */  sltu       $at, $a3, $t0
/* 0040c7f4 */  beqz       $at, 0x40c80c
/* 0040c7f8 */  nop        
/* 0040c7fc */  lbu        $t6, ($a3)
/* 0040c800 */  nop        
/* 0040c804 */  beq        $v0, $t6, 0x40c7ec
/* 0040c808 */  nop        
/* 0040c80c */  subu       $v0, $a3, $a0
/* 0040c810 */  beqz       $v0, 0x40c850
/* 0040c814 */  move       $a2, $v0
/* 0040c818 */  move       $v0, $v1
/* 0040c81c */  slti       $at, $a2, 0x7f
/* 0040c820 */  bnez       $at, 0x40c834
/* 0040c824 */  sll        $v1, $a2, 0x10
/* 0040c828 */  b          0x40c838
/* 0040c82c */  addiu      $v1, $zero, 0x7e
/* 0040c830 */  sll        $v1, $a2, 0x10
/* 0040c834 */  sra        $v1, $v1, 0x10
/* 0040c838 */  subu       $a2, $a2, $v1
/* 0040c83c */  sb         $v1, ($a1)
/* 0040c840 */  addiu      $a1, $a1, 1
/* 0040c844 */  addiu      $a1, $a1, 1
/* 0040c848 */  bnez       $a2, 0x40c81c
/* 0040c84c */  sb         $v0, -1($a1)
/* 0040c850 */  sltu       $at, $a3, $t0
/* 0040c854 */  bnez       $at, 0x40c6e0
/* 0040c858 */  move       $a0, $a3
/* 0040c85c */  addiu      $a1, $a1, 1
/* 0040c860 */  sb         $zero, -1($a1)
/* 0040c864 */  b          0x40ce1c
/* 0040c868 */  subu       $v0, $a1, $t1
/* 0040c86c */  beq        $a1, $v0, 0x40c880
/* 0040c870 */  addiu      $v1, $zero, 2
/* 0040c874 */  b          0x40ca40
/* 0040c878 */  addiu      $v1, $zero, 2
/* 0040c87c */  addiu      $v1, $zero, 2
/* 0040c880 */  bne        $a3, $v1, 0x40ca40
/* 0040c884 */  nop        
/* 0040c888 */  lw         $t7, 0x28($sp)
/* 0040c88c */  move       $a3, $a0
/* 0040c890 */  addu       $t0, $a0, $t7
/* 0040c894 */  sltu       $at, $a0, $t0
/* 0040c898 */  beqz       $at, 0x40ca20
/* 0040c89c */  move       $a1, $t1
/* 0040c8a0 */  move       $a0, $a3
/* 0040c8a4 */  addiu      $a3, $a3, 2
/* 0040c8a8 */  sltu       $at, $a3, $t0
/* 0040c8ac */  beqz       $at, 0x40c90c
/* 0040c8b0 */  nop        
/* 0040c8b4 */  lbu        $v0, -1($a3)
/* 0040c8b8 */  lbu        $t8, -2($a3)
/* 0040c8bc */  nop        
/* 0040c8c0 */  bne        $v0, $t8, 0x40c8d8
/* 0040c8c4 */  nop        
/* 0040c8c8 */  lbu        $t9, ($a3)
/* 0040c8cc */  nop        
/* 0040c8d0 */  beq        $t9, $v0, 0x40c90c
/* 0040c8d4 */  nop        
/* 0040c8d8 */  addiu      $a3, $a3, 1
/* 0040c8dc */  sltu       $at, $a3, $t0
/* 0040c8e0 */  beqz       $at, 0x40c90c
/* 0040c8e4 */  nop        
/* 0040c8e8 */  lbu        $v0, -1($a3)
/* 0040c8ec */  lbu        $t2, -2($a3)
/* 0040c8f0 */  nop        
/* 0040c8f4 */  bne        $v0, $t2, 0x40c8d8
/* 0040c8f8 */  nop        
/* 0040c8fc */  lbu        $t3, ($a3)
/* 0040c900 */  nop        
/* 0040c904 */  bne        $t3, $v0, 0x40c8d8
/* 0040c908 */  nop        
/* 0040c90c */  addiu      $a3, $a3, -2
/* 0040c910 */  subu       $v0, $a3, $a0
/* 0040c914 */  beqz       $v0, 0x40c988
/* 0040c918 */  move       $a2, $v0
/* 0040c91c */  slti       $at, $a2, 0x7f
/* 0040c920 */  bnez       $at, 0x40c934
/* 0040c924 */  sll        $v1, $a2, 0x10
/* 0040c928 */  b          0x40c938
/* 0040c92c */  addiu      $v1, $zero, 0x7e
/* 0040c930 */  sll        $v1, $a2, 0x10
/* 0040c934 */  sra        $v1, $v1, 0x10
/* 0040c938 */  subu       $a2, $a2, $v1
/* 0040c93c */  ori        $t4, $v1, 0x80
/* 0040c940 */  move       $v0, $v1
/* 0040c944 */  addiu      $v1, $v1, -1
/* 0040c948 */  sll        $v1, $v1, 0x10
/* 0040c94c */  sra        $v1, $v1, 0x10
/* 0040c950 */  sh         $t4, ($a1)
/* 0040c954 */  beqz       $v0, 0x40c980
/* 0040c958 */  addiu      $a1, $a1, 2
/* 0040c95c */  move       $v0, $v1
/* 0040c960 */  lbu        $t5, ($a0)
/* 0040c964 */  addiu      $v1, $v1, -1
/* 0040c968 */  sll        $v1, $v1, 0x10
/* 0040c96c */  sra        $v1, $v1, 0x10
/* 0040c970 */  addiu      $a0, $a0, 1
/* 0040c974 */  addiu      $a1, $a1, 2
/* 0040c978 */  bnez       $v0, 0x40c95c
/* 0040c97c */  sh         $t5, -2($a1)
/* 0040c980 */  bnez       $a2, 0x40c920
/* 0040c984 */  slti       $at, $a2, 0x7f
/* 0040c988 */  move       $a0, $a3
/* 0040c98c */  addiu      $a3, $a3, 1
/* 0040c990 */  sltu       $at, $a3, $t0
/* 0040c994 */  lbu        $v1, -1($a3)
/* 0040c998 */  beqz       $at, 0x40c9d4
/* 0040c99c */  subu       $v0, $a3, $a0
/* 0040c9a0 */  lbu        $t6, ($a3)
/* 0040c9a4 */  move       $v0, $v1
/* 0040c9a8 */  bne        $v0, $t6, 0x40c9d0
/* 0040c9ac */  nop        
/* 0040c9b0 */  addiu      $a3, $a3, 1
/* 0040c9b4 */  sltu       $at, $a3, $t0
/* 0040c9b8 */  beqz       $at, 0x40c9d0
/* 0040c9bc */  nop        
/* 0040c9c0 */  lbu        $t7, ($a3)
/* 0040c9c4 */  nop        
/* 0040c9c8 */  beq        $v0, $t7, 0x40c9b0
/* 0040c9cc */  nop        
/* 0040c9d0 */  subu       $v0, $a3, $a0
/* 0040c9d4 */  beqz       $v0, 0x40ca14
/* 0040c9d8 */  move       $a2, $v0
/* 0040c9dc */  move       $v0, $v1
/* 0040c9e0 */  slti       $at, $a2, 0x7f
/* 0040c9e4 */  bnez       $at, 0x40c9f8
/* 0040c9e8 */  sll        $v1, $a2, 0x10
/* 0040c9ec */  b          0x40c9fc
/* 0040c9f0 */  addiu      $v1, $zero, 0x7e
/* 0040c9f4 */  sll        $v1, $a2, 0x10
/* 0040c9f8 */  sra        $v1, $v1, 0x10
/* 0040c9fc */  subu       $a2, $a2, $v1
/* 0040ca00 */  sh         $v1, ($a1)
/* 0040ca04 */  addiu      $a1, $a1, 2
/* 0040ca08 */  addiu      $a1, $a1, 2
/* 0040ca0c */  bnez       $a2, 0x40c9e0
/* 0040ca10 */  sh         $v0, -2($a1)
/* 0040ca14 */  sltu       $at, $a3, $t0
/* 0040ca18 */  bnez       $at, 0x40c8a4
/* 0040ca1c */  move       $a0, $a3
/* 0040ca20 */  addiu      $a1, $a1, 2
/* 0040ca24 */  subu       $v0, $a1, $t1
/* 0040ca28 */  bgez       $v0, 0x40ca34
/* 0040ca2c */  move       $at, $v0
/* 0040ca30 */  addiu      $at, $at, 1
/* 0040ca34 */  sra        $v0, $at, 1
/* 0040ca38 */  b          0x40ce1c
/* 0040ca3c */  sh         $zero, -2($a1)
/* 0040ca40 */  bne        $a1, $v1, 0x40cc1c
/* 0040ca44 */  nop        
/* 0040ca48 */  bne        $a3, $v0, 0x40cc1c
/* 0040ca4c */  nop        
/* 0040ca50 */  lw         $t8, 0x28($sp)
/* 0040ca54 */  move       $a3, $a0
/* 0040ca58 */  sll        $t9, $t8, 1
/* 0040ca5c */  addu       $t0, $a0, $t9
/* 0040ca60 */  sltu       $at, $a0, $t0
/* 0040ca64 */  beqz       $at, 0x40cc0c
/* 0040ca68 */  move       $a1, $t1
/* 0040ca6c */  move       $a0, $a3
/* 0040ca70 */  addiu      $a3, $a3, 4
/* 0040ca74 */  sltu       $at, $a3, $t0
/* 0040ca78 */  beqz       $at, 0x40cad8
/* 0040ca7c */  nop        
/* 0040ca80 */  lhu        $v0, -2($a3)
/* 0040ca84 */  lhu        $t2, -4($a3)
/* 0040ca88 */  nop        
/* 0040ca8c */  bne        $v0, $t2, 0x40caa4
/* 0040ca90 */  nop        
/* 0040ca94 */  lhu        $t3, ($a3)
/* 0040ca98 */  nop        
/* 0040ca9c */  beq        $t3, $v0, 0x40cad8
/* 0040caa0 */  nop        
/* 0040caa4 */  addiu      $a3, $a3, 2
/* 0040caa8 */  sltu       $at, $a3, $t0
/* 0040caac */  beqz       $at, 0x40cad8
/* 0040cab0 */  nop        
/* 0040cab4 */  lhu        $v0, -2($a3)
/* 0040cab8 */  lhu        $t4, -4($a3)
/* 0040cabc */  nop        
/* 0040cac0 */  bne        $v0, $t4, 0x40caa4
/* 0040cac4 */  nop        
/* 0040cac8 */  lhu        $t5, ($a3)
/* 0040cacc */  nop        
/* 0040cad0 */  bne        $t5, $v0, 0x40caa4
/* 0040cad4 */  nop        
/* 0040cad8 */  addiu      $a3, $a3, -4
/* 0040cadc */  subu       $v0, $a3, $a0
/* 0040cae0 */  bgez       $v0, 0x40caec
/* 0040cae4 */  move       $at, $v0
/* 0040cae8 */  addiu      $at, $at, 1
/* 0040caec */  sra        $v0, $at, 1
/* 0040caf0 */  beqz       $v0, 0x40cb64
/* 0040caf4 */  move       $a2, $v0
/* 0040caf8 */  slti       $at, $a2, 0x7f
/* 0040cafc */  bnez       $at, 0x40cb10
/* 0040cb00 */  sll        $v1, $a2, 0x10
/* 0040cb04 */  b          0x40cb14
/* 0040cb08 */  addiu      $v1, $zero, 0x7e
/* 0040cb0c */  sll        $v1, $a2, 0x10
/* 0040cb10 */  sra        $v1, $v1, 0x10
/* 0040cb14 */  subu       $a2, $a2, $v1
/* 0040cb18 */  ori        $t6, $v1, 0x80
/* 0040cb1c */  move       $v0, $v1
/* 0040cb20 */  addiu      $v1, $v1, -1
/* 0040cb24 */  sll        $v1, $v1, 0x10
/* 0040cb28 */  sra        $v1, $v1, 0x10
/* 0040cb2c */  sb         $t6, ($a1)
/* 0040cb30 */  beqz       $v0, 0x40cb5c
/* 0040cb34 */  addiu      $a1, $a1, 1
/* 0040cb38 */  move       $v0, $v1
/* 0040cb3c */  lhu        $t7, ($a0)
/* 0040cb40 */  addiu      $v1, $v1, -1
/* 0040cb44 */  sll        $v1, $v1, 0x10
/* 0040cb48 */  sra        $v1, $v1, 0x10
/* 0040cb4c */  addiu      $a0, $a0, 2
/* 0040cb50 */  addiu      $a1, $a1, 1
/* 0040cb54 */  bnez       $v0, 0x40cb38
/* 0040cb58 */  sb         $t7, -1($a1)
/* 0040cb5c */  bnez       $a2, 0x40cafc
/* 0040cb60 */  slti       $at, $a2, 0x7f
/* 0040cb64 */  move       $a0, $a3
/* 0040cb68 */  addiu      $a3, $a3, 2
/* 0040cb6c */  sltu       $at, $a3, $t0
/* 0040cb70 */  lh         $v1, -2($a3)
/* 0040cb74 */  beqz       $at, 0x40cbb0
/* 0040cb78 */  subu       $v0, $a3, $a0
/* 0040cb7c */  lhu        $t8, ($a3)
/* 0040cb80 */  move       $v0, $v1
/* 0040cb84 */  bne        $v0, $t8, 0x40cbac
/* 0040cb88 */  nop        
/* 0040cb8c */  addiu      $a3, $a3, 2
/* 0040cb90 */  sltu       $at, $a3, $t0
/* 0040cb94 */  beqz       $at, 0x40cbac
/* 0040cb98 */  nop        
/* 0040cb9c */  lhu        $t9, ($a3)
/* 0040cba0 */  nop        
/* 0040cba4 */  beq        $v0, $t9, 0x40cb8c
/* 0040cba8 */  nop        
/* 0040cbac */  subu       $v0, $a3, $a0
/* 0040cbb0 */  bgez       $v0, 0x40cbbc
/* 0040cbb4 */  move       $at, $v0
/* 0040cbb8 */  addiu      $at, $at, 1
/* 0040cbbc */  sra        $v0, $at, 1
/* 0040cbc0 */  beqz       $v0, 0x40cc00
/* 0040cbc4 */  move       $a2, $v0
/* 0040cbc8 */  move       $v0, $v1
/* 0040cbcc */  slti       $at, $a2, 0x7f
/* 0040cbd0 */  bnez       $at, 0x40cbe4
/* 0040cbd4 */  sll        $v1, $a2, 0x10
/* 0040cbd8 */  b          0x40cbe8
/* 0040cbdc */  addiu      $v1, $zero, 0x7e
/* 0040cbe0 */  sll        $v1, $a2, 0x10
/* 0040cbe4 */  sra        $v1, $v1, 0x10
/* 0040cbe8 */  subu       $a2, $a2, $v1
/* 0040cbec */  sb         $v1, ($a1)
/* 0040cbf0 */  addiu      $a1, $a1, 1
/* 0040cbf4 */  addiu      $a1, $a1, 1
/* 0040cbf8 */  bnez       $a2, 0x40cbcc
/* 0040cbfc */  sb         $v0, -1($a1)
/* 0040cc00 */  sltu       $at, $a3, $t0
/* 0040cc04 */  bnez       $at, 0x40ca70
/* 0040cc08 */  move       $a0, $a3
/* 0040cc0c */  addiu      $a1, $a1, 1
/* 0040cc10 */  sb         $zero, -1($a1)
/* 0040cc14 */  b          0x40ce1c
/* 0040cc18 */  subu       $v0, $a1, $t1
/* 0040cc1c */  bne        $a1, $v1, 0x40ce08
/* 0040cc20 */  nop        
/* 0040cc24 */  bne        $a3, $v1, 0x40ce08
/* 0040cc28 */  nop        
/* 0040cc2c */  lw         $t2, 0x28($sp)
/* 0040cc30 */  move       $a3, $a0
/* 0040cc34 */  sll        $t3, $t2, 1
/* 0040cc38 */  addu       $t0, $a0, $t3
/* 0040cc3c */  sltu       $at, $a0, $t0
/* 0040cc40 */  beqz       $at, 0x40cde8
/* 0040cc44 */  move       $a1, $t1
/* 0040cc48 */  move       $a0, $a3
/* 0040cc4c */  addiu      $a3, $a3, 4
/* 0040cc50 */  sltu       $at, $a3, $t0
/* 0040cc54 */  beqz       $at, 0x40ccb4
/* 0040cc58 */  nop        
/* 0040cc5c */  lhu        $v0, -2($a3)
/* 0040cc60 */  lhu        $t4, -4($a3)
/* 0040cc64 */  nop        
/* 0040cc68 */  bne        $v0, $t4, 0x40cc80
/* 0040cc6c */  nop        
/* 0040cc70 */  lhu        $t5, ($a3)
/* 0040cc74 */  nop        
/* 0040cc78 */  beq        $t5, $v0, 0x40ccb4
/* 0040cc7c */  nop        
/* 0040cc80 */  addiu      $a3, $a3, 2
/* 0040cc84 */  sltu       $at, $a3, $t0
/* 0040cc88 */  beqz       $at, 0x40ccb4
/* 0040cc8c */  nop        
/* 0040cc90 */  lhu        $v0, -2($a3)
/* 0040cc94 */  lhu        $t6, -4($a3)
/* 0040cc98 */  nop        
/* 0040cc9c */  bne        $v0, $t6, 0x40cc80
/* 0040cca0 */  nop        
/* 0040cca4 */  lhu        $t7, ($a3)
/* 0040cca8 */  nop        
/* 0040ccac */  bne        $t7, $v0, 0x40cc80
/* 0040ccb0 */  nop        
/* 0040ccb4 */  addiu      $a3, $a3, -4
/* 0040ccb8 */  subu       $v0, $a3, $a0
/* 0040ccbc */  bgez       $v0, 0x40ccc8
/* 0040ccc0 */  move       $at, $v0
/* 0040ccc4 */  addiu      $at, $at, 1
/* 0040ccc8 */  sra        $v0, $at, 1
/* 0040cccc */  beqz       $v0, 0x40cd40
/* 0040ccd0 */  move       $a2, $v0
/* 0040ccd4 */  slti       $at, $a2, 0x7f
/* 0040ccd8 */  bnez       $at, 0x40ccec
/* 0040ccdc */  sll        $v1, $a2, 0x10
/* 0040cce0 */  b          0x40ccf0
/* 0040cce4 */  addiu      $v1, $zero, 0x7e
/* 0040cce8 */  sll        $v1, $a2, 0x10
/* 0040ccec */  sra        $v1, $v1, 0x10
/* 0040ccf0 */  subu       $a2, $a2, $v1
/* 0040ccf4 */  ori        $t8, $v1, 0x80
/* 0040ccf8 */  move       $v0, $v1
/* 0040ccfc */  addiu      $v1, $v1, -1
/* 0040cd00 */  sll        $v1, $v1, 0x10
/* 0040cd04 */  sra        $v1, $v1, 0x10
/* 0040cd08 */  sh         $t8, ($a1)
/* 0040cd0c */  beqz       $v0, 0x40cd38
/* 0040cd10 */  addiu      $a1, $a1, 2
/* 0040cd14 */  move       $v0, $v1
/* 0040cd18 */  lhu        $t9, ($a0)
/* 0040cd1c */  addiu      $v1, $v1, -1
/* 0040cd20 */  sll        $v1, $v1, 0x10
/* 0040cd24 */  sra        $v1, $v1, 0x10
/* 0040cd28 */  addiu      $a0, $a0, 2
/* 0040cd2c */  addiu      $a1, $a1, 2
/* 0040cd30 */  bnez       $v0, 0x40cd14
/* 0040cd34 */  sh         $t9, -2($a1)
/* 0040cd38 */  bnez       $a2, 0x40ccd8
/* 0040cd3c */  slti       $at, $a2, 0x7f
/* 0040cd40 */  move       $a0, $a3
/* 0040cd44 */  addiu      $a3, $a3, 2
/* 0040cd48 */  sltu       $at, $a3, $t0
/* 0040cd4c */  lh         $v1, -2($a3)
/* 0040cd50 */  beqz       $at, 0x40cd8c
/* 0040cd54 */  subu       $v0, $a3, $a0
/* 0040cd58 */  lhu        $t2, ($a3)
/* 0040cd5c */  move       $v0, $v1
/* 0040cd60 */  bne        $v0, $t2, 0x40cd88
/* 0040cd64 */  nop        
/* 0040cd68 */  addiu      $a3, $a3, 2
/* 0040cd6c */  sltu       $at, $a3, $t0
/* 0040cd70 */  beqz       $at, 0x40cd88
/* 0040cd74 */  nop        
/* 0040cd78 */  lhu        $t3, ($a3)
/* 0040cd7c */  nop        
/* 0040cd80 */  beq        $v0, $t3, 0x40cd68
/* 0040cd84 */  nop        
/* 0040cd88 */  subu       $v0, $a3, $a0
/* 0040cd8c */  bgez       $v0, 0x40cd98
/* 0040cd90 */  move       $at, $v0
/* 0040cd94 */  addiu      $at, $at, 1
/* 0040cd98 */  sra        $v0, $at, 1
/* 0040cd9c */  beqz       $v0, 0x40cddc
/* 0040cda0 */  move       $a2, $v0
/* 0040cda4 */  move       $v0, $v1
/* 0040cda8 */  slti       $at, $a2, 0x7f
/* 0040cdac */  bnez       $at, 0x40cdc0
/* 0040cdb0 */  sll        $v1, $a2, 0x10
/* 0040cdb4 */  b          0x40cdc4
/* 0040cdb8 */  addiu      $v1, $zero, 0x7e
/* 0040cdbc */  sll        $v1, $a2, 0x10
/* 0040cdc0 */  sra        $v1, $v1, 0x10
/* 0040cdc4 */  subu       $a2, $a2, $v1
/* 0040cdc8 */  sh         $v1, ($a1)
/* 0040cdcc */  addiu      $a1, $a1, 2
/* 0040cdd0 */  addiu      $a1, $a1, 2
/* 0040cdd4 */  bnez       $a2, 0x40cda8
/* 0040cdd8 */  sh         $v0, -2($a1)
/* 0040cddc */  sltu       $at, $a3, $t0
/* 0040cde0 */  bnez       $at, 0x40cc4c
/* 0040cde4 */  move       $a0, $a3
/* 0040cde8 */  addiu      $a1, $a1, 2
/* 0040cdec */  subu       $v0, $a1, $t1
/* 0040cdf0 */  bgez       $v0, 0x40cdfc
/* 0040cdf4 */  move       $at, $v0
/* 0040cdf8 */  addiu      $at, $at, 1
/* 0040cdfc */  sra        $v0, $at, 1
/* 0040ce00 */  b          0x40ce1c
/* 0040ce04 */  sh         $zero, -2($a1)
/* 0040ce08 */  lui        $a0, 0x1000
/* 0040ce0c */  addiu      $a0, $a0, 0x32a0
/* 0040ce10 */  jal        0x40b640
/* 0040ce14 */  move       $a2, $a3
/* 0040ce18 */  move       $v0, $zero
/* 0040ce1c */  lw         $ra, 0x14($sp)
/* 0040ce20 */  addiu      $sp, $sp, 0x18
/* 0040ce24 */  jr         $ra
/* 0040ce28 */  nop        
/* 0040ce2c */  addiu      $sp, $sp, -0x18
/* 0040ce30 */  addiu      $v0, $zero, 1
/* 0040ce34 */  sw         $ra, 0x14($sp)
/* 0040ce38 */  move       $t0, $a0
/* 0040ce3c */  bne        $a1, $v0, 0x40cee8
/* 0040ce40 */  move       $t1, $a2
/* 0040ce44 */  bne        $a3, $v0, 0x40cee8
/* 0040ce48 */  nop        
/* 0040ce4c */  move       $a2, $t0
/* 0040ce50 */  move       $a0, $t1
/* 0040ce54 */  lbu        $a1, ($a2)
/* 0040ce58 */  addiu      $a2, $a2, 1
/* 0040ce5c */  andi       $v0, $a1, 0x7f
/* 0040ce60 */  andi       $a3, $v0, 0xffff
/* 0040ce64 */  beqz       $a3, 0x40d108
/* 0040ce68 */  andi       $v1, $v0, 0xffff
/* 0040ce6c */  andi       $t6, $a1, 0x80
/* 0040ce70 */  beqz       $t6, 0x40ceb4
/* 0040ce74 */  move       $v0, $v1
/* 0040ce78 */  move       $v0, $a3
/* 0040ce7c */  addiu      $v1, $a3, -1
/* 0040ce80 */  beqz       $v0, 0x40ce54
/* 0040ce84 */  andi       $v1, $v1, 0xffff
/* 0040ce88 */  lbu        $t7, ($a2)
/* 0040ce8c */  move       $v0, $v1
/* 0040ce90 */  addiu      $v1, $v1, -1
/* 0040ce94 */  andi       $v1, $v1, 0xffff
/* 0040ce98 */  addiu      $a2, $a2, 1
/* 0040ce9c */  addiu      $a0, $a0, 1
/* 0040cea0 */  bnez       $v0, 0x40ce88
/* 0040cea4 */  sb         $t7, -1($a0)
/* 0040cea8 */  b          0x40ce58
/* 0040ceac */  lbu        $a1, ($a2)
/* 0040ceb0 */  move       $v0, $v1
/* 0040ceb4 */  addiu      $v1, $v1, -1
/* 0040ceb8 */  lbu        $a1, ($a2)
/* 0040cebc */  andi       $v1, $v1, 0xffff
/* 0040cec0 */  beqz       $v0, 0x40ce54
/* 0040cec4 */  addiu      $a2, $a2, 1
/* 0040cec8 */  move       $v0, $v1
/* 0040cecc */  addiu      $v1, $v1, -1
/* 0040ced0 */  andi       $v1, $v1, 0xffff
/* 0040ced4 */  sb         $a1, ($a0)
/* 0040ced8 */  bnez       $v0, 0x40cec8
/* 0040cedc */  addiu      $a0, $a0, 1
/* 0040cee0 */  b          0x40ce58
/* 0040cee4 */  lbu        $a1, ($a2)
/* 0040cee8 */  beq        $a1, $v0, 0x40cefc
/* 0040ceec */  addiu      $v1, $zero, 2
/* 0040cef0 */  b          0x40cfa0
/* 0040cef4 */  addiu      $v1, $zero, 2
/* 0040cef8 */  addiu      $v1, $zero, 2
/* 0040cefc */  bne        $a3, $v1, 0x40cfa0
/* 0040cf00 */  nop        
/* 0040cf04 */  move       $a2, $t0
/* 0040cf08 */  move       $a0, $t1
/* 0040cf0c */  lbu        $a1, ($a2)
/* 0040cf10 */  addiu      $a2, $a2, 1
/* 0040cf14 */  andi       $v0, $a1, 0x7f
/* 0040cf18 */  andi       $a3, $v0, 0xffff
/* 0040cf1c */  beqz       $a3, 0x40d108
/* 0040cf20 */  andi       $v1, $v0, 0xffff
/* 0040cf24 */  andi       $t8, $a1, 0x80
/* 0040cf28 */  beqz       $t8, 0x40cf6c
/* 0040cf2c */  move       $v0, $v1
/* 0040cf30 */  move       $v0, $a3
/* 0040cf34 */  addiu      $v1, $a3, -1
/* 0040cf38 */  beqz       $v0, 0x40cf0c
/* 0040cf3c */  andi       $v1, $v1, 0xffff
/* 0040cf40 */  lbu        $t9, ($a2)
/* 0040cf44 */  move       $v0, $v1
/* 0040cf48 */  addiu      $v1, $v1, -1
/* 0040cf4c */  andi       $v1, $v1, 0xffff
/* 0040cf50 */  addiu      $a2, $a2, 1
/* 0040cf54 */  addiu      $a0, $a0, 2
/* 0040cf58 */  bnez       $v0, 0x40cf40
/* 0040cf5c */  sh         $t9, -2($a0)
/* 0040cf60 */  b          0x40cf10
/* 0040cf64 */  lbu        $a1, ($a2)
/* 0040cf68 */  move       $v0, $v1
/* 0040cf6c */  addiu      $v1, $v1, -1
/* 0040cf70 */  lbu        $a1, ($a2)
/* 0040cf74 */  andi       $v1, $v1, 0xffff
/* 0040cf78 */  beqz       $v0, 0x40cf0c
/* 0040cf7c */  addiu      $a2, $a2, 1
/* 0040cf80 */  move       $v0, $v1
/* 0040cf84 */  addiu      $v1, $v1, -1
/* 0040cf88 */  andi       $v1, $v1, 0xffff
/* 0040cf8c */  sh         $a1, ($a0)
/* 0040cf90 */  bnez       $v0, 0x40cf80
/* 0040cf94 */  addiu      $a0, $a0, 2
/* 0040cf98 */  b          0x40cf10
/* 0040cf9c */  lbu        $a1, ($a2)
/* 0040cfa0 */  bne        $a1, $v1, 0x40d04c
/* 0040cfa4 */  nop        
/* 0040cfa8 */  bne        $a3, $v0, 0x40d04c
/* 0040cfac */  nop        
/* 0040cfb0 */  move       $a2, $t0
/* 0040cfb4 */  move       $a0, $t1
/* 0040cfb8 */  lhu        $a1, ($a2)
/* 0040cfbc */  addiu      $a2, $a2, 2
/* 0040cfc0 */  andi       $v0, $a1, 0x7f
/* 0040cfc4 */  andi       $a3, $v0, 0xffff
/* 0040cfc8 */  beqz       $a3, 0x40d108
/* 0040cfcc */  andi       $v1, $v0, 0xffff
/* 0040cfd0 */  andi       $t2, $a1, 0x80
/* 0040cfd4 */  beqz       $t2, 0x40d018
/* 0040cfd8 */  move       $v0, $v1
/* 0040cfdc */  move       $v0, $a3
/* 0040cfe0 */  addiu      $v1, $a3, -1
/* 0040cfe4 */  beqz       $v0, 0x40cfb8
/* 0040cfe8 */  andi       $v1, $v1, 0xffff
/* 0040cfec */  lhu        $t3, ($a2)
/* 0040cff0 */  move       $v0, $v1
/* 0040cff4 */  addiu      $v1, $v1, -1
/* 0040cff8 */  andi       $v1, $v1, 0xffff
/* 0040cffc */  addiu      $a2, $a2, 2
/* 0040d000 */  addiu      $a0, $a0, 1
/* 0040d004 */  bnez       $v0, 0x40cfec
/* 0040d008 */  sb         $t3, -1($a0)
/* 0040d00c */  b          0x40cfbc
/* 0040d010 */  lhu        $a1, ($a2)
/* 0040d014 */  move       $v0, $v1
/* 0040d018 */  addiu      $v1, $v1, -1
/* 0040d01c */  lhu        $a1, ($a2)
/* 0040d020 */  andi       $v1, $v1, 0xffff
/* 0040d024 */  beqz       $v0, 0x40cfb8
/* 0040d028 */  addiu      $a2, $a2, 2
/* 0040d02c */  move       $v0, $v1
/* 0040d030 */  addiu      $v1, $v1, -1
/* 0040d034 */  andi       $v1, $v1, 0xffff
/* 0040d038 */  sb         $a1, ($a0)
/* 0040d03c */  bnez       $v0, 0x40d02c
/* 0040d040 */  addiu      $a0, $a0, 1
/* 0040d044 */  b          0x40cfbc
/* 0040d048 */  lhu        $a1, ($a2)
/* 0040d04c */  bne        $a1, $v1, 0x40d0f8
/* 0040d050 */  nop        
/* 0040d054 */  bne        $a3, $v1, 0x40d0f8
/* 0040d058 */  nop        
/* 0040d05c */  move       $a2, $t0
/* 0040d060 */  move       $a0, $t1
/* 0040d064 */  lhu        $a1, ($a2)
/* 0040d068 */  addiu      $a2, $a2, 2
/* 0040d06c */  andi       $v0, $a1, 0x7f
/* 0040d070 */  andi       $a3, $v0, 0xffff
/* 0040d074 */  beqz       $a3, 0x40d108
/* 0040d078 */  andi       $v1, $v0, 0xffff
/* 0040d07c */  andi       $t4, $a1, 0x80
/* 0040d080 */  beqz       $t4, 0x40d0c4
/* 0040d084 */  move       $v0, $v1
/* 0040d088 */  move       $v0, $a3
/* 0040d08c */  addiu      $v1, $a3, -1
/* 0040d090 */  beqz       $v0, 0x40d064
/* 0040d094 */  andi       $v1, $v1, 0xffff
/* 0040d098 */  lhu        $t5, ($a2)
/* 0040d09c */  move       $v0, $v1
/* 0040d0a0 */  addiu      $v1, $v1, -1
/* 0040d0a4 */  andi       $v1, $v1, 0xffff
/* 0040d0a8 */  addiu      $a2, $a2, 2
/* 0040d0ac */  addiu      $a0, $a0, 2
/* 0040d0b0 */  bnez       $v0, 0x40d098
/* 0040d0b4 */  sh         $t5, -2($a0)
/* 0040d0b8 */  b          0x40d068
/* 0040d0bc */  lhu        $a1, ($a2)
/* 0040d0c0 */  move       $v0, $v1
/* 0040d0c4 */  addiu      $v1, $v1, -1
/* 0040d0c8 */  lhu        $a1, ($a2)
/* 0040d0cc */  andi       $v1, $v1, 0xffff
/* 0040d0d0 */  beqz       $v0, 0x40d064
/* 0040d0d4 */  addiu      $a2, $a2, 2
/* 0040d0d8 */  move       $v0, $v1
/* 0040d0dc */  addiu      $v1, $v1, -1
/* 0040d0e0 */  andi       $v1, $v1, 0xffff
/* 0040d0e4 */  sh         $a1, ($a0)
/* 0040d0e8 */  bnez       $v0, 0x40d0d8
/* 0040d0ec */  addiu      $a0, $a0, 2
/* 0040d0f0 */  b          0x40d068
/* 0040d0f4 */  lhu        $a1, ($a2)
/* 0040d0f8 */  lui        $a0, 0x1000
/* 0040d0fc */  addiu      $a0, $a0, 0x32c0
/* 0040d100 */  jal        0x40b640
/* 0040d104 */  move       $a2, $a3
/* 0040d108 */  lw         $ra, 0x14($sp)
/* 0040d10c */  addiu      $sp, $sp, 0x18
/* 0040d110 */  jr         $ra
/* 0040d114 */  nop        
/* 0040d118 */  nop        
/* 0040d11c */  nop        

# === cos ===
glabel cos
/* 0040d120 */  lwc1       $f7, -0x7f58($gp)                        # .lit8: 6.74652e+09
/* 0040d124 */  lwc1       $f6, -0x7f54($gp)                        # .lit8 @ 0x10003e1c
/* 0040d128 */  abs.d      $f12, $f12
/* 0040d12c */  cfc1       $t1, $31
/* 0040d130 */  cfc1       $t1, $31
/* 0040d134 */  c.olt.d    $f12, $f6
/* 0040d138 */  lwc1       $f6, -0x7f4c($gp)                        # .lit8 @ 0x10003e24
/* 0040d13c */  lwc1       $f7, -0x7f50($gp)                        # .lit8: 0.31831
/* 0040d140 */  addiu      $at, $zero, -4
/* 0040d144 */  bc1f       0x40d294
/* 0040d148 */  and        $t0, $t1, $at
/* 0040d14c */  ctc1       $t0, $31
/* 0040d150 */  lwc1       $f9, -0x7fe0($gp)                        # .lit8: 0.5
/* 0040d154 */  mul.d      $f2, $f12, $f6
/* 0040d158 */  lwc1       $f8, -0x7fdc($gp)                        # .lit8 @ 0x10003d94
/* 0040d15c */  nop        
/* 0040d160 */  add.d      $f2, $f2, $f8
/* 0040d164 */  cvt.w.d    $f4, $f2
/* 0040d168 */  cvt.d.w    $f2, $f4
/* 0040d16c */  mfc1       $t0, $f4
/* 0040d170 */  b          0x40d1d0
/* 0040d174 */  sub.d      $f2, $f2, $f8

# === sin ===
glabel sin
/* 0040d178 */  lwc1       $f9, -0x7f48($gp)                        # .lit8: 1.5708
/* 0040d17c */  lwc1       $f8, -0x7f44($gp)                        # .lit8 @ 0x10003e2c
/* 0040d180 */  abs.d      $f0, $f12
/* 0040d184 */  c.olt.d    $f0, $f8
/* 0040d188 */  cfc1       $t1, $31
/* 0040d18c */  cfc1       $t1, $31
/* 0040d190 */  bc1t       0x40d1fc
/* 0040d194 */  nop        
/* 0040d198 */  lwc1       $f9, -0x7f58($gp)                        # .lit8: 6.74652e+09
/* 0040d19c */  lwc1       $f8, -0x7f54($gp)                        # .lit8 @ 0x10003e1c
/* 0040d1a0 */  addiu      $at, $zero, -4
/* 0040d1a4 */  c.olt.d    $f0, $f8
/* 0040d1a8 */  lwc1       $f7, -0x7f50($gp)                        # .lit8: 0.31831
/* 0040d1ac */  lwc1       $f6, -0x7f4c($gp)                        # .lit8 @ 0x10003e24
/* 0040d1b0 */  bc1f       0x40d294
/* 0040d1b4 */  and        $t0, $t1, $at
/* 0040d1b8 */  ctc1       $t0, $31
/* 0040d1bc */  nop        
/* 0040d1c0 */  mul.d      $f2, $f12, $f6
/* 0040d1c4 */  cvt.w.d    $f2, $f2
/* 0040d1c8 */  mfc1       $t0, $f2
/* 0040d1cc */  cvt.d.w    $f2, $f2
/* 0040d1d0 */  lwc1       $f7, -0x7f40($gp)                        # .lit8: 3.14159
/* 0040d1d4 */  lwc1       $f6, -0x7f3c($gp)                        # .lit8 @ 0x10003e34
/* 0040d1d8 */  lwc1       $f9, -0x7f38($gp)                        # .lit8: 6.27833e-07
/* 0040d1dc */  mul.d      $f4, $f2, $f6
/* 0040d1e0 */  lwc1       $f8, -0x7f34($gp)                        # .lit8 @ 0x10003e3c
/* 0040d1e4 */  andi       $t0, $t0, 1
/* 0040d1e8 */  mul.d      $f2, $f2, $f8
/* 0040d1ec */  sub.d      $f12, $f12, $f4
/* 0040d1f0 */  beqz       $t0, 0x40d1fc
/* 0040d1f4 */  sub.d      $f12, $f12, $f2
/* 0040d1f8 */  neg.d      $f12, $f12
/* 0040d1fc */  mul.d      $f2, $f12, $f12
/* 0040d200 */  lwc1       $f7, -0x7f30($gp)                        # .lit8: 2.72048e-15
/* 0040d204 */  lwc1       $f6, -0x7f2c($gp)                        # .lit8 @ 0x10003e44
/* 0040d208 */  lwc1       $f9, -0x7f28($gp)                        # .lit8: -7.64292e-13
/* 0040d20c */  lwc1       $f8, -0x7f24($gp)                        # .lit8 @ 0x10003e4c
/* 0040d210 */  mul.d      $f4, $f2, $f6
/* 0040d214 */  lwc1       $f6, -0x7f1c($gp)                        # .lit8 @ 0x10003e54
/* 0040d218 */  lwc1       $f7, -0x7f20($gp)                        # .lit8: 1.60589e-10
/* 0040d21c */  add.d      $f4, $f4, $f8
/* 0040d220 */  lwc1       $f8, -0x7f14($gp)                        # .lit8 @ 0x10003e5c
/* 0040d224 */  mul.d      $f4, $f4, $f2
/* 0040d228 */  lwc1       $f9, -0x7f18($gp)                        # .lit8: -2.50521e-08
/* 0040d22c */  add.d      $f4, $f4, $f6
/* 0040d230 */  lwc1       $f6, -0x7f0c($gp)                        # .lit8 @ 0x10003e64
/* 0040d234 */  mul.d      $f4, $f4, $f2
/* 0040d238 */  lwc1       $f7, -0x7f10($gp)                        # .lit8: 2.75573e-06
/* 0040d23c */  add.d      $f4, $f4, $f8
/* 0040d240 */  lwc1       $f8, -0x7f04($gp)                        # .lit8 @ 0x10003e6c
/* 0040d244 */  mul.d      $f4, $f4, $f2
/* 0040d248 */  lwc1       $f9, -0x7f08($gp)                        # .lit8: -0.000198413
/* 0040d24c */  add.d      $f4, $f4, $f6
/* 0040d250 */  lwc1       $f6, -0x7efc($gp)                        # .lit8 @ 0x10003e74
/* 0040d254 */  mul.d      $f4, $f4, $f2
/* 0040d258 */  lwc1       $f7, -0x7f00($gp)                        # .lit8: 0.00833333
/* 0040d25c */  add.d      $f4, $f4, $f8
/* 0040d260 */  lwc1       $f8, -0x7ef4($gp)                        # .lit8 @ 0x10003e7c
/* 0040d264 */  mul.d      $f4, $f4, $f2
/* 0040d268 */  lwc1       $f9, -0x7ef8($gp)                        # .lit8: -0.166667
/* 0040d26c */  add.d      $f4, $f4, $f6
/* 0040d270 */  mul.d      $f4, $f4, $f2
/* 0040d274 */  add.d      $f4, $f4, $f8
/* 0040d278 */  mul.d      $f4, $f4, $f2
/* 0040d27c */  mul.d      $f4, $f4, $f12
/* 0040d280 */  ctc1       $t1, $31
/* 0040d284 */  jr         $ra
/* 0040d288 */  add.d      $f0, $f12, $f4
/* 0040d28c */  jr         $ra
/* 0040d290 */  mov.d      $f0, $f12
/* 0040d294 */  c.un.d     $f12, $f12
/* 0040d298 */  mtc1       $zero, $f0
/* 0040d29c */  mtc1       $zero, $f1
/* 0040d2a0 */  bc1t       0x40d2b0
/* 0040d2a4 */  nop        
/* 0040d2a8 */  jr         $ra
/* 0040d2ac */  div.d      $f0, $f0, $f0
/* 0040d2b0 */  jr         $ra
/* 0040d2b4 */  mov.d      $f0, $f12
/* 0040d2b8 */  nop        
/* 0040d2bc */  nop        
/* 0040d2c0 */  jr         $ra
/* 0040d2c4 */  nop        
/* 0040d2c8 */  nop        
/* 0040d2cc */  nop        
/* 0040d2d0 */  addiu      $sp, $sp, -0x2a8
/* 0040d2d4 */  move       $v1, $a0
/* 0040d2d8 */  addiu      $t6, $zero, -1
/* 0040d2dc */  sw         $ra, 0x14($sp)
/* 0040d2e0 */  bnez       $v1, 0x40d328
/* 0040d2e4 */  sw         $t6, 0x1c($sp)
/* 0040d2e8 */  lui        $a0, 0x1000
/* 0040d2ec */  jal        0xf8011b0                                # atof
/* 0040d2f0 */  addiu      $a0, $a0, 0x34e4
/* 0040d2f4 */  beqz       $v0, 0x40d30c
/* 0040d2f8 */  move       $v1, $v0
/* 0040d2fc */  lbu        $t7, ($v0)
/* 0040d300 */  nop        
/* 0040d304 */  bnez       $t7, 0x40d328
/* 0040d308 */  nop        
/* 0040d30c */  lbu        $t8, -0x7bf0($gp)                        # .sdata @ 0x10004180
/* 0040d310 */  nop        
/* 0040d314 */  beqz       $t8, 0x40d324
/* 0040d318 */  nop        
/* 0040d31c */  b          0x40d3ac
/* 0040d320 */  move       $v0, $zero
/* 0040d324 */  addiu      $v1, $gp, -0x7bec
/* 0040d328 */  lui        $a1, 0x1000
/* 0040d32c */  sb         $zero, -0x7bf0($gp)                      # .sdata @ 0x10004180
/* 0040d330 */  addiu      $a1, $a1, 0x34f0
/* 0040d334 */  addiu      $a0, $sp, 0x228
/* 0040d338 */  jal        0xf8012f0                                # exit
/* 0040d33c */  sw         $v1, 0x2a8($sp)
/* 0040d340 */  lw         $v1, 0x2a8($sp)
/* 0040d344 */  addiu      $a0, $sp, 0x236
/* 0040d348 */  jal        0xf8012f0                                # exit
/* 0040d34c */  move       $a1, $v1
/* 0040d350 */  addiu      $a0, $sp, 0x228
/* 0040d354 */  jal        0x40dfc0
/* 0040d358 */  move       $a1, $zero
/* 0040d35c */  bltz       $v0, 0x40d3a4
/* 0040d360 */  move       $a0, $v0
/* 0040d364 */  addiu      $a1, $sp, 0x24
/* 0040d368 */  addiu      $a2, $zero, 0x202
/* 0040d36c */  jal        0x40e000
/* 0040d370 */  sw         $a0, 0x20($sp)
/* 0040d374 */  addiu      $at, $zero, 0x202
/* 0040d378 */  bne        $v0, $at, 0x40d39c
/* 0040d37c */  lw         $a0, 0x20($sp)
/* 0040d380 */  lui        $a0, 0x1000
/* 0040d384 */  addiu      $a0, $a0, 0x32e0
/* 0040d388 */  addiu      $a1, $sp, 0x24
/* 0040d38c */  jal        0xf801230                                # realloc
/* 0040d390 */  addiu      $a2, $zero, 0x202
/* 0040d394 */  sw         $zero, 0x1c($sp)
/* 0040d398 */  lw         $a0, 0x20($sp)
/* 0040d39c */  jal        0x40dfa0
/* 0040d3a0 */  nop        
/* 0040d3a4 */  lw         $v0, 0x1c($sp)
/* 0040d3a8 */  nop        
/* 0040d3ac */  lw         $ra, 0x14($sp)
/* 0040d3b0 */  addiu      $sp, $sp, 0x2a8
/* 0040d3b4 */  jr         $ra
/* 0040d3b8 */  nop        
/* 0040d3bc */  nop        
/* 0040d3c0 */  addiu      $sp, $sp, -0x18
/* 0040d3c4 */  sw         $ra, 0x14($sp)
/* 0040d3c8 */  jal        0xf8010f8                                # strcmp
/* 0040d3cc */  sw         $a0, 0x18($sp)
/* 0040d3d0 */  lw         $a0, 0x18($sp)
/* 0040d3d4 */  jal        0x40e5c0
/* 0040d3d8 */  nop        
/* 0040d3dc */  lw         $ra, 0x14($sp)
/* 0040d3e0 */  addiu      $sp, $sp, 0x18
/* 0040d3e4 */  jr         $ra
/* 0040d3e8 */  nop        
/* 0040d3ec */  nop        
/* 0040d3f0 */  addiu      $sp, $sp, -0x38
/* 0040d3f4 */  lw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d3f8 */  sw         $ra, 0x14($sp)
/* 0040d3fc */  addiu      $at, $zero, 1
/* 0040d400 */  sw         $a0, 0x38($sp)
/* 0040d404 */  sw         $a1, 0x3c($sp)
/* 0040d408 */  bne        $a3, $at, 0x40d490
/* 0040d40c */  sw         $a2, 0x40($sp)
/* 0040d410 */  lw         $t6, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d414 */  lw         $t7, 0x38($sp)
/* 0040d418 */  move       $v1, $t6
/* 0040d41c */  slt        $at, $v1, $t7
/* 0040d420 */  beqz       $at, 0x40d45c
/* 0040d424 */  nop        
/* 0040d428 */  lw         $t8, 0x3c($sp)
/* 0040d42c */  sll        $t9, $t6, 2
/* 0040d430 */  addu       $t0, $t8, $t9
/* 0040d434 */  lw         $a0, ($t0)
/* 0040d438 */  addiu      $at, $zero, 0x2d
/* 0040d43c */  lbu        $t1, ($a0)
/* 0040d440 */  nop        
/* 0040d444 */  bne        $t1, $at, 0x40d45c
/* 0040d448 */  nop        
/* 0040d44c */  lbu        $t2, 1($a0)
/* 0040d450 */  nop        
/* 0040d454 */  bnez       $t2, 0x40d464
/* 0040d458 */  nop        
/* 0040d45c */  b          0x40d70c
/* 0040d460 */  addiu      $v0, $zero, -1
/* 0040d464 */  jal        0xf8012e8                                # fwrite
/* 0040d468 */  addiu      $a1, $gp, -0x7bac
/* 0040d46c */  bnez       $v0, 0x40d488
/* 0040d470 */  nop        
/* 0040d474 */  lw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d478 */  addiu      $v0, $zero, -1
/* 0040d47c */  addiu      $v1, $v1, 1
/* 0040d480 */  b          0x40d70c
/* 0040d484 */  sw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d488 */  lw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d48c */  nop        
/* 0040d490 */  lw         $t4, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d494 */  lw         $t3, 0x3c($sp)
/* 0040d498 */  sll        $t5, $t4, 2
/* 0040d49c */  addu       $t7, $t3, $t5
/* 0040d4a0 */  lw         $t6, ($t7)
/* 0040d4a4 */  addiu      $at, $zero, 0x3a
/* 0040d4a8 */  addu       $t8, $t6, $a3
/* 0040d4ac */  lbu        $a1, ($t8)
/* 0040d4b0 */  nop        
/* 0040d4b4 */  beq        $a1, $at, 0x40d4dc
/* 0040d4b8 */  sw         $a1, -0x7bb8($gp)                        # .sdata @ 0x100041b8
/* 0040d4bc */  lw         $a0, 0x40($sp)
/* 0040d4c0 */  jal        0xf8012e0                                # fread
/* 0040d4c4 */  sw         $a1, 0x34($sp)
/* 0040d4c8 */  lw         $a1, 0x34($sp)
/* 0040d4cc */  bnez       $v0, 0x40d5a4
/* 0040d4d0 */  move       $v1, $v0
/* 0040d4d4 */  lw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d4d8 */  nop        
/* 0040d4dc */  lw         $t9, -0x7bc0($gp)                        # .sdata @ 0x100041b0
/* 0040d4e0 */  nop        
/* 0040d4e4 */  beqz       $t9, 0x40d554
/* 0040d4e8 */  nop        
/* 0040d4ec */  lw         $t1, 0x3c($sp)
/* 0040d4f0 */  addiu      $t0, $zero, 0xa
/* 0040d4f4 */  sb         $t0, 0x29($sp)
/* 0040d4f8 */  sb         $a1, 0x28($sp)
/* 0040d4fc */  lw         $a0, ($t1)
/* 0040d500 */  jal        0xf801308                                # close
/* 0040d504 */  nop        
/* 0040d508 */  lw         $t2, 0x3c($sp)
/* 0040d50c */  addiu      $a0, $zero, 2
/* 0040d510 */  lw         $a1, ($t2)
/* 0040d514 */  jal        0x40dfe0
/* 0040d518 */  move       $a2, $v0
/* 0040d51c */  lui        $a0, 0x1000
/* 0040d520 */  jal        0xf801308                                # close
/* 0040d524 */  addiu      $a0, $a0, 0x3d04
/* 0040d528 */  lui        $a1, 0x1000
/* 0040d52c */  addiu      $a1, $a1, 0x3d04
/* 0040d530 */  addiu      $a0, $zero, 2
/* 0040d534 */  jal        0x40dfe0
/* 0040d538 */  move       $a2, $v0
/* 0040d53c */  addiu      $a0, $zero, 2
/* 0040d540 */  addiu      $a1, $sp, 0x28
/* 0040d544 */  jal        0x40dfe0
/* 0040d548 */  addiu      $a2, $zero, 2
/* 0040d54c */  lw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d550 */  nop        
/* 0040d554 */  lw         $t3, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d558 */  lw         $t4, 0x3c($sp)
/* 0040d55c */  sll        $t5, $t3, 2
/* 0040d560 */  addu       $t7, $t4, $t5
/* 0040d564 */  lw         $t6, ($t7)
/* 0040d568 */  addiu      $a3, $a3, 1
/* 0040d56c */  addu       $t8, $t6, $a3
/* 0040d570 */  lbu        $t9, ($t8)
/* 0040d574 */  nop        
/* 0040d578 */  beqz       $t9, 0x40d588
/* 0040d57c */  nop        
/* 0040d580 */  b          0x40d59c
/* 0040d584 */  sw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d588 */  lw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d58c */  addiu      $a3, $zero, 1
/* 0040d590 */  addiu      $v1, $v1, 1
/* 0040d594 */  sw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d598 */  sw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d59c */  b          0x40d70c
/* 0040d5a0 */  addiu      $v0, $zero, 0x3f
/* 0040d5a4 */  addiu      $v1, $v0, 1
/* 0040d5a8 */  lbu        $t0, ($v1)
/* 0040d5ac */  addiu      $at, $zero, 0x3a
/* 0040d5b0 */  bne        $t0, $at, 0x40d6b8
/* 0040d5b4 */  nop        
/* 0040d5b8 */  lw         $t1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d5bc */  lw         $a2, 0x3c($sp)
/* 0040d5c0 */  sll        $t2, $t1, 2
/* 0040d5c4 */  addu       $v0, $a2, $t2
/* 0040d5c8 */  lw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d5cc */  lw         $t3, ($v0)
/* 0040d5d0 */  nop        
/* 0040d5d4 */  addu       $v1, $t3, $a3
/* 0040d5d8 */  lbu        $t4, 1($v1)
/* 0040d5dc */  nop        
/* 0040d5e0 */  beqz       $t4, 0x40d5fc
/* 0040d5e4 */  nop        
/* 0040d5e8 */  addiu      $t5, $v1, 1
/* 0040d5ec */  addiu      $t7, $t1, 1
/* 0040d5f0 */  sw         $t7, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d5f4 */  b          0x40d6ac
/* 0040d5f8 */  sw         $t5, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 0040d5fc */  lw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d600 */  lw         $t6, 0x38($sp)
/* 0040d604 */  addiu      $v1, $v1, 1
/* 0040d608 */  slt        $at, $v1, $t6
/* 0040d60c */  sw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d610 */  bnez       $at, 0x40d694
/* 0040d614 */  addiu      $v0, $v0, 4
/* 0040d618 */  lw         $t8, -0x7bc0($gp)                        # .sdata @ 0x100041b0
/* 0040d61c */  nop        
/* 0040d620 */  beqz       $t8, 0x40d684
/* 0040d624 */  nop        
/* 0040d628 */  addiu      $t9, $zero, 0xa
/* 0040d62c */  sb         $t9, 0x21($sp)
/* 0040d630 */  sb         $a1, 0x20($sp)
/* 0040d634 */  lw         $a0, ($a2)
/* 0040d638 */  jal        0xf801308                                # close
/* 0040d63c */  nop        
/* 0040d640 */  lw         $t0, 0x3c($sp)
/* 0040d644 */  addiu      $a0, $zero, 2
/* 0040d648 */  lw         $a1, ($t0)
/* 0040d64c */  jal        0x40dfe0
/* 0040d650 */  move       $a2, $v0
/* 0040d654 */  lui        $a0, 0x1000
/* 0040d658 */  jal        0xf801308                                # close
/* 0040d65c */  addiu      $a0, $a0, 0x3ce0
/* 0040d660 */  lui        $a1, 0x1000
/* 0040d664 */  addiu      $a1, $a1, 0x3ce0
/* 0040d668 */  addiu      $a0, $zero, 2
/* 0040d66c */  jal        0x40dfe0
/* 0040d670 */  move       $a2, $v0
/* 0040d674 */  addiu      $a0, $zero, 2
/* 0040d678 */  addiu      $a1, $sp, 0x20
/* 0040d67c */  jal        0x40dfe0
/* 0040d680 */  addiu      $a2, $zero, 2
/* 0040d684 */  addiu      $a3, $zero, 1
/* 0040d688 */  sw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d68c */  b          0x40d70c
/* 0040d690 */  addiu      $v0, $zero, 0x3f
/* 0040d694 */  lw         $t3, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d698 */  lw         $t2, ($v0)
/* 0040d69c */  addiu      $t4, $t3, 1
/* 0040d6a0 */  sw         $t4, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d6a4 */  addiu      $v0, $v0, 4
/* 0040d6a8 */  sw         $t2, -0x7bb4($gp)                        # .sdata @ 0x100041bc
/* 0040d6ac */  addiu      $a3, $zero, 1
/* 0040d6b0 */  b          0x40d708
/* 0040d6b4 */  sw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d6b8 */  lw         $t1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d6bc */  lw         $t5, 0x3c($sp)
/* 0040d6c0 */  sll        $t7, $t1, 2
/* 0040d6c4 */  lw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d6c8 */  addu       $t6, $t5, $t7
/* 0040d6cc */  lw         $t8, ($t6)
/* 0040d6d0 */  addiu      $a3, $a3, 1
/* 0040d6d4 */  addu       $t9, $t8, $a3
/* 0040d6d8 */  lbu        $t0, ($t9)
/* 0040d6dc */  nop        
/* 0040d6e0 */  beqz       $t0, 0x40d6f0
/* 0040d6e4 */  nop        
/* 0040d6e8 */  b          0x40d704
/* 0040d6ec */  sw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d6f0 */  lw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d6f4 */  addiu      $a3, $zero, 1
/* 0040d6f8 */  addiu      $v1, $v1, 1
/* 0040d6fc */  sw         $v1, -0x7bbc($gp)                        # .sdata @ 0x100041b4
/* 0040d700 */  sw         $a3, -0x7bb0($gp)                        # .sdata @ 0x100041c0
/* 0040d704 */  sw         $zero, -0x7bb4($gp)                      # .sdata @ 0x100041bc
/* 0040d708 */  move       $v0, $a1
/* 0040d70c */  lw         $ra, 0x14($sp)
/* 0040d710 */  addiu      $sp, $sp, 0x38
/* 0040d714 */  jr         $ra
/* 0040d718 */  nop        
/* 0040d71c */  nop        
/* 0040d720 */  addiu      $sp, $sp, -0x18
/* 0040d724 */  sw         $a0, 0x18($sp)
/* 0040d728 */  sw         $a2, 0x20($sp)
/* 0040d72c */  sw         $a1, 0x1c($sp)
/* 0040d730 */  addiu      $a2, $sp, 0x18
/* 0040d734 */  sw         $ra, 0x14($sp)
/* 0040d738 */  addiu      $a2, $a2, 7
/* 0040d73c */  lw         $a1, 0x18($sp)
/* 0040d740 */  lui        $a0, 0x1000
/* 0040d744 */  addiu      $at, $zero, -4
/* 0040d748 */  sw         $a3, 0x24($sp)
/* 0040d74c */  and        $a2, $a2, $at
/* 0040d750 */  jal        0x40e5d0
/* 0040d754 */  addiu      $a0, $a0, 0x3694
/* 0040d758 */  lw         $ra, 0x14($sp)
/* 0040d75c */  addiu      $sp, $sp, 0x18
/* 0040d760 */  jr         $ra
/* 0040d764 */  nop        
/* 0040d768 */  addiu      $sp, $sp, -0x18
/* 0040d76c */  sw         $a2, 0x20($sp)
/* 0040d770 */  sw         $a1, 0x1c($sp)
/* 0040d774 */  addiu      $a2, $sp, 0x1c
/* 0040d778 */  sw         $ra, 0x14($sp)
/* 0040d77c */  addiu      $a2, $a2, 7
/* 0040d780 */  lw         $a1, 0x1c($sp)
/* 0040d784 */  addiu      $at, $zero, -4
/* 0040d788 */  sw         $a3, 0x24($sp)
/* 0040d78c */  jal        0x40e5d0
/* 0040d790 */  and        $a2, $a2, $at
/* 0040d794 */  lw         $ra, 0x14($sp)
/* 0040d798 */  addiu      $sp, $sp, 0x18
/* 0040d79c */  jr         $ra
/* 0040d7a0 */  nop        
/* 0040d7a4 */  addiu      $sp, $sp, -0x30
/* 0040d7a8 */  sw         $ra, 0x14($sp)
/* 0040d7ac */  sw         $a1, 0x34($sp)
/* 0040d7b0 */  sw         $a2, 0x38($sp)
/* 0040d7b4 */  sw         $a3, 0x3c($sp)
/* 0040d7b8 */  addiu      $t6, $zero, 1
/* 0040d7bc */  sb         $t6, 0x28($sp)
/* 0040d7c0 */  sw         $a0, 0x24($sp)
/* 0040d7c4 */  jal        0xf801308                                # close
/* 0040d7c8 */  sw         $a0, 0x20($sp)
/* 0040d7cc */  addiu      $a2, $sp, 0x34
/* 0040d7d0 */  addiu      $t7, $zero, 0x64
/* 0040d7d4 */  addiu      $a2, $a2, 7
/* 0040d7d8 */  lw         $a1, 0x34($sp)
/* 0040d7dc */  addiu      $at, $zero, -4
/* 0040d7e0 */  sw         $v0, 0x1c($sp)
/* 0040d7e4 */  sb         $t7, 0x29($sp)
/* 0040d7e8 */  and        $a2, $a2, $at
/* 0040d7ec */  jal        0x40e5d0
/* 0040d7f0 */  addiu      $a0, $sp, 0x1c
/* 0040d7f4 */  lw         $ra, 0x14($sp)
/* 0040d7f8 */  addiu      $sp, $sp, 0x30
/* 0040d7fc */  jr         $ra
/* 0040d800 */  nop        
/* 0040d804 */  nop        
/* 0040d808 */  nop        
/* 0040d80c */  nop        
/* 0040d810 */  addiu      $v0, $zero, 0x413
/* 0040d814 */  syscall    
/* 0040d818 */  beqz       $a3, 0x40d828
/* 0040d81c */  nop        
/* 0040d820 */  j          0x40fa00
/* 0040d824 */  nop        
/* 0040d828 */  jr         $ra
/* 0040d82c */  nop        
/* 0040d830 */  addiu      $sp, $sp, -0x78
/* 0040d834 */  sw         $a1, 0x7c($sp)
/* 0040d838 */  lw         $t6, 0x7c($sp)
/* 0040d83c */  sw         $ra, 0x14($sp)
/* 0040d840 */  sw         $zero, 0x6c($sp)
/* 0040d844 */  move       $t2, $a0
/* 0040d848 */  move       $a3, $zero
/* 0040d84c */  bnez       $t6, 0x40d85c
/* 0040d850 */  sw         $zero, 0x60($sp)
/* 0040d854 */  addiu      $t7, $sp, 0x5c
/* 0040d858 */  sw         $t7, 0x7c($sp)
/* 0040d85c */  lw         $t8, 0x7c($sp)
/* 0040d860 */  lui        $ra, 0x1000
/* 0040d864 */  sw         $t2, ($t8)
/* 0040d868 */  lbu        $t1, ($t2)
/* 0040d86c */  addiu      $ra, $ra, 0x32e0
/* 0040d870 */  addu       $t9, $ra, $t1
/* 0040d874 */  lbu        $t6, 1($t9)
/* 0040d878 */  nop        
/* 0040d87c */  andi       $t7, $t6, 8
/* 0040d880 */  beqz       $t7, 0x40d8c8
/* 0040d884 */  addiu      $at, $zero, 0x2b
/* 0040d888 */  lbu        $t1, 1($t2)
/* 0040d88c */  addiu      $t2, $t2, 1
/* 0040d890 */  addu       $t8, $ra, $t1
/* 0040d894 */  lbu        $t9, 1($t8)
/* 0040d898 */  nop        
/* 0040d89c */  andi       $t6, $t9, 8
/* 0040d8a0 */  bnez       $t6, 0x40d888
/* 0040d8a4 */  nop        
/* 0040d8a8 */  b          0x40d8c8
/* 0040d8ac */  addiu      $at, $zero, 0x2b
/* 0040d8b0 */  addiu      $t7, $zero, 1
/* 0040d8b4 */  sw         $t7, 0x6c($sp)
/* 0040d8b8 */  lbu        $t1, 1($t2)
/* 0040d8bc */  b          0x40d8d8
/* 0040d8c0 */  addiu      $t2, $t2, 1
/* 0040d8c4 */  addiu      $at, $zero, 0x2b
/* 0040d8c8 */  beq        $t1, $at, 0x40d8b8
/* 0040d8cc */  addiu      $at, $zero, 0x2d
/* 0040d8d0 */  beq        $t1, $at, 0x40d8b4
/* 0040d8d4 */  addiu      $t7, $zero, 1
/* 0040d8d8 */  addu       $t4, $ra, $t1
/* 0040d8dc */  lbu        $t8, 1($t4)
/* 0040d8e0 */  move       $v1, $zero
/* 0040d8e4 */  andi       $t9, $t8, 4
/* 0040d8e8 */  move       $a2, $zero
/* 0040d8ec */  addiu      $a0, $zero, 1
/* 0040d8f0 */  move       $t3, $zero
/* 0040d8f4 */  move       $v0, $zero
/* 0040d8f8 */  beqz       $t9, 0x40d908
/* 0040d8fc */  addiu      $t2, $t2, 1
/* 0040d900 */  b          0x40d920
/* 0040d904 */  addiu      $t5, $zero, 0x2e
/* 0040d908 */  addiu      $t5, $zero, 0x2e
/* 0040d90c */  bne        $t1, $t5, 0x40da50
/* 0040d910 */  lw         $t6, 0x60($sp)
/* 0040d914 */  move       $t0, $zero
/* 0040d918 */  bnez       $t0, 0x40da4c
/* 0040d91c */  addiu      $t3, $zero, 1
/* 0040d920 */  lui        $a1, 0xccc
/* 0040d924 */  ori        $a1, $a1, 0xcccc
/* 0040d928 */  beq        $t1, $t5, 0x40da18
/* 0040d92c */  nop        
/* 0040d930 */  lw         $t6, 0x60($sp)
/* 0040d934 */  nop        
/* 0040d938 */  addiu      $t7, $t6, 1
/* 0040d93c */  beqz       $t3, 0x40d9bc
/* 0040d940 */  sw         $t7, 0x60($sp)
/* 0040d944 */  addiu      $at, $zero, 0x30
/* 0040d948 */  bne        $t1, $at, 0x40d958
/* 0040d94c */  nop        
/* 0040d950 */  b          0x40da18
/* 0040d954 */  addiu      $v0, $v0, 1
/* 0040d958 */  blez       $v0, 0x40d9b8
/* 0040d95c */  slt        $at, $v1, $a1
/* 0040d960 */  beqz       $at, 0x40d97c
/* 0040d964 */  addiu      $a3, $a3, -1
/* 0040d968 */  move       $at, $v1
/* 0040d96c */  sll        $v1, $at, 2
/* 0040d970 */  addu       $v1, $v1, $at
/* 0040d974 */  b          0x40d9ac
/* 0040d978 */  sll        $v1, $v1, 1
/* 0040d97c */  slt        $at, $a0, $a1
/* 0040d980 */  beqz       $at, 0x40d9a8
/* 0040d984 */  move       $at, $a0
/* 0040d988 */  sll        $a0, $at, 2
/* 0040d98c */  addu       $a0, $a0, $at
/* 0040d990 */  move       $at, $a2
/* 0040d994 */  sll        $a2, $at, 2
/* 0040d998 */  addu       $a2, $a2, $at
/* 0040d99c */  sll        $a0, $a0, 1
/* 0040d9a0 */  b          0x40d9ac
/* 0040d9a4 */  sll        $a2, $a2, 1
/* 0040d9a8 */  addiu      $a3, $a3, 1
/* 0040d9ac */  addiu      $v0, $v0, -1
/* 0040d9b0 */  bgtz       $v0, 0x40d960
/* 0040d9b4 */  slt        $at, $v1, $a1
/* 0040d9b8 */  addiu      $a3, $a3, -1
/* 0040d9bc */  slt        $at, $v1, $a1
/* 0040d9c0 */  beqz       $at, 0x40d9e0
/* 0040d9c4 */  move       $at, $v1
/* 0040d9c8 */  sll        $v1, $at, 2
/* 0040d9cc */  addu       $v1, $v1, $at
/* 0040d9d0 */  sll        $v1, $v1, 1
/* 0040d9d4 */  addu       $v1, $v1, $t1
/* 0040d9d8 */  b          0x40da18
/* 0040d9dc */  addiu      $v1, $v1, -0x30
/* 0040d9e0 */  slt        $at, $a0, $a1
/* 0040d9e4 */  beqz       $at, 0x40da14
/* 0040d9e8 */  move       $at, $a0
/* 0040d9ec */  sll        $a0, $at, 2
/* 0040d9f0 */  addu       $a0, $a0, $at
/* 0040d9f4 */  move       $at, $a2
/* 0040d9f8 */  sll        $a2, $at, 2
/* 0040d9fc */  addu       $a2, $a2, $at
/* 0040da00 */  sll        $a2, $a2, 1
/* 0040da04 */  addu       $a2, $a2, $t1
/* 0040da08 */  sll        $a0, $a0, 1
/* 0040da0c */  b          0x40da18
/* 0040da10 */  addiu      $a2, $a2, -0x30
/* 0040da14 */  addiu      $a3, $a3, 1
/* 0040da18 */  lbu        $t1, ($t2)
/* 0040da1c */  addiu      $t2, $t2, 1
/* 0040da20 */  addu       $t4, $ra, $t1
/* 0040da24 */  lbu        $t8, 1($t4)
/* 0040da28 */  nop        
/* 0040da2c */  andi       $t9, $t8, 4
/* 0040da30 */  bnez       $t9, 0x40d928
/* 0040da34 */  nop        
/* 0040da38 */  bne        $t1, $t5, 0x40da50
/* 0040da3c */  lw         $t6, 0x60($sp)
/* 0040da40 */  move       $t0, $t3
/* 0040da44 */  beqz       $t0, 0x40d928
/* 0040da48 */  addiu      $t3, $t3, 1
/* 0040da4c */  lw         $t6, 0x60($sp)
/* 0040da50 */  nop        
/* 0040da54 */  bnez       $t6, 0x40da6c
/* 0040da58 */  nop        
/* 0040da5c */  mtc1       $zero, $f0
/* 0040da60 */  mtc1       $zero, $f1
/* 0040da64 */  b          0x40dcb0
/* 0040da68 */  lw         $ra, 0x14($sp)
/* 0040da6c */  mtc1       $v1, $f4
/* 0040da70 */  slti       $at, $a0, 2
/* 0040da74 */  cvt.d.w    $f0, $f4
/* 0040da78 */  bnez       $at, 0x40da98
/* 0040da7c */  mov.d      $f14, $f0
/* 0040da80 */  mtc1       $a0, $f6
/* 0040da84 */  mtc1       $a2, $f16
/* 0040da88 */  cvt.d.w    $f8, $f6
/* 0040da8c */  mul.d      $f10, $f8, $f0
/* 0040da90 */  cvt.d.w    $f18, $f16
/* 0040da94 */  add.d      $f14, $f10, $f18
/* 0040da98 */  lw         $t8, 0x7c($sp)
/* 0040da9c */  lui        $t9, 0x1000
/* 0040daa0 */  addiu      $t7, $t2, -1
/* 0040daa4 */  addiu      $t9, $t9, 0x3325
/* 0040daa8 */  beq        $t4, $t9, 0x40dac0
/* 0040daac */  sw         $t7, ($t8)
/* 0040dab0 */  lui        $t6, 0x1000
/* 0040dab4 */  addiu      $t6, $t6, 0x3345
/* 0040dab8 */  bne        $t4, $t6, 0x40db80
/* 0040dabc */  nop        
/* 0040dac0 */  lw         $t7, 0x7c($sp)
/* 0040dac4 */  move       $v0, $zero
/* 0040dac8 */  sw         $t2, ($t7)
/* 0040dacc */  lbu        $v1, ($t2)
/* 0040dad0 */  move       $a0, $zero
/* 0040dad4 */  b          0x40daec
/* 0040dad8 */  move       $t0, $v1
/* 0040dadc */  addiu      $a0, $zero, 1
/* 0040dae0 */  lbu        $v1, 1($t2)
/* 0040dae4 */  b          0x40db08
/* 0040dae8 */  addiu      $t2, $t2, 1
/* 0040daec */  addiu      $at, $zero, 0x20
/* 0040daf0 */  beq        $t0, $at, 0x40dae0
/* 0040daf4 */  addiu      $at, $zero, 0x2b
/* 0040daf8 */  beq        $t0, $at, 0x40dae0
/* 0040dafc */  addiu      $at, $zero, 0x2d
/* 0040db00 */  beq        $t0, $at, 0x40dadc
/* 0040db04 */  nop        
/* 0040db08 */  move       $t1, $v1
/* 0040db0c */  addu       $t8, $ra, $t1
/* 0040db10 */  lbu        $t9, 1($t8)
/* 0040db14 */  nop        
/* 0040db18 */  andi       $t6, $t9, 4
/* 0040db1c */  beqz       $t6, 0x40db80
/* 0040db20 */  slti       $at, $v0, 0x400
/* 0040db24 */  beqz       $at, 0x40db40
/* 0040db28 */  nop        
/* 0040db2c */  sll        $t7, $v0, 2
/* 0040db30 */  addu       $t7, $t7, $v0
/* 0040db34 */  sll        $t7, $t7, 1
/* 0040db38 */  addu       $v0, $t7, $t1
/* 0040db3c */  addiu      $v0, $v0, -0x30
/* 0040db40 */  lbu        $t1, 1($t2)
/* 0040db44 */  addiu      $t2, $t2, 1
/* 0040db48 */  addu       $t8, $ra, $t1
/* 0040db4c */  lbu        $t9, 1($t8)
/* 0040db50 */  nop        
/* 0040db54 */  andi       $t6, $t9, 4
/* 0040db58 */  bnez       $t6, 0x40db24
/* 0040db5c */  slti       $at, $v0, 0x400
/* 0040db60 */  beqz       $a0, 0x40db70
/* 0040db64 */  nop        
/* 0040db68 */  b          0x40db74
/* 0040db6c */  subu       $a3, $a3, $v0
/* 0040db70 */  addu       $a3, $a3, $v0
/* 0040db74 */  lw         $t7, 0x7c($sp)
/* 0040db78 */  nop        
/* 0040db7c */  sw         $t2, ($t7)
/* 0040db80 */  mtc1       $zero, $f4
/* 0040db84 */  mtc1       $zero, $f5
/* 0040db88 */  nop        
/* 0040db8c */  c.eq.d     $f14, $f4
/* 0040db90 */  nop        
/* 0040db94 */  bc1f       0x40dba4
/* 0040db98 */  nop        
/* 0040db9c */  b          0x40dcac
/* 0040dba0 */  mov.d      $f0, $f14
/* 0040dba4 */  beqz       $a3, 0x40dc8c
/* 0040dba8 */  lui        $at, 0x1000
/* 0040dbac */  lwc1       $f9, 0x3d20($at)
/* 0040dbb0 */  lwc1       $f8, 0x3d24($at)
/* 0040dbb4 */  mtc1       $zero, $f6
/* 0040dbb8 */  mtc1       $zero, $f7
/* 0040dbbc */  lui        $v1, 0x1000
/* 0040dbc0 */  c.eq.d     $f6, $f8
/* 0040dbc4 */  addiu      $v1, $v1, 0x3d20
/* 0040dbc8 */  bc1f       0x40dc14
/* 0040dbcc */  mov.d      $f2, $f14
/* 0040dbd0 */  lwc1       $f17, -0x7ef0($gp)                       # .lit8: 1.25
/* 0040dbd4 */  lwc1       $f16, -0x7eec($gp)                       # .lit8 @ 0x10003e84
/* 0040dbd8 */  lui        $at, 0x1000
/* 0040dbdc */  lui        $v0, 0x1000
/* 0040dbe0 */  swc1       $f17, 0x3d20($at)
/* 0040dbe4 */  addiu      $v0, $v0, 0x3d60
/* 0040dbe8 */  swc1       $f16, 0x3d24($at)
/* 0040dbec */  lwc1       $f1, ($v1)
/* 0040dbf0 */  lwc1       $f0, 4($v1)
/* 0040dbf4 */  addiu      $v1, $v1, 8
/* 0040dbf8 */  mul.d      $f10, $f0, $f0
/* 0040dbfc */  sltu       $at, $v1, $v0
/* 0040dc00 */  swc1       $f10, 4($v1)
/* 0040dc04 */  bnez       $at, 0x40dbec
/* 0040dc08 */  swc1       $f11, ($v1)
/* 0040dc0c */  lui        $v1, 0x1000
/* 0040dc10 */  addiu      $v1, $v1, 0x3d20
/* 0040dc14 */  bgez       $a3, 0x40dc28
/* 0040dc18 */  move       $t1, $a3
/* 0040dc1c */  lwc1       $f3, -0x7f78($gp)                        # .lit8: 1
/* 0040dc20 */  lwc1       $f2, -0x7f74($gp)                        # .lit8 @ 0x10003dfc
/* 0040dc24 */  negu       $t1, $a3
/* 0040dc28 */  slti       $at, $t1, 0x201
/* 0040dc2c */  bnez       $at, 0x40dc3c
/* 0040dc30 */  andi       $t8, $t1, 1
/* 0040dc34 */  addiu      $t1, $zero, 0x200
/* 0040dc38 */  andi       $t8, $t1, 1
/* 0040dc3c */  beqz       $t8, 0x40dc54
/* 0040dc40 */  nop        
/* 0040dc44 */  lwc1       $f19, ($v1)
/* 0040dc48 */  lwc1       $f18, 4($v1)
/* 0040dc4c */  nop        
/* 0040dc50 */  mul.d      $f2, $f2, $f18
/* 0040dc54 */  sra        $t1, $t1, 1
/* 0040dc58 */  beqz       $t1, 0x40dc68
/* 0040dc5c */  nop        
/* 0040dc60 */  b          0x40dc38
/* 0040dc64 */  addiu      $v1, $v1, 8
/* 0040dc68 */  bgez       $a3, 0x40dc78
/* 0040dc6c */  nop        
/* 0040dc70 */  b          0x40dc7c
/* 0040dc74 */  div.d      $f12, $f14, $f2
/* 0040dc78 */  mov.d      $f12, $f2
/* 0040dc7c */  sll        $a2, $a3, 2
/* 0040dc80 */  jal        0xf8011e0                                # atoi
/* 0040dc84 */  subu       $a2, $a2, $a3
/* 0040dc88 */  mov.d      $f14, $f0
/* 0040dc8c */  lw         $t9, 0x6c($sp)
/* 0040dc90 */  nop        
/* 0040dc94 */  beqz       $t9, 0x40dca4
/* 0040dc98 */  nop        
/* 0040dc9c */  b          0x40dca8
/* 0040dca0 */  neg.d      $f12, $f14
/* 0040dca4 */  mov.d      $f12, $f14
/* 0040dca8 */  mov.d      $f0, $f12
/* 0040dcac */  lw         $ra, 0x14($sp)
/* 0040dcb0 */  addiu      $sp, $sp, 0x78
/* 0040dcb4 */  jr         $ra
/* 0040dcb8 */  nop        
/* 0040dcbc */  nop        
/* 0040dcc0 */  beqz       $a1, 0x40dccc
/* 0040dcc4 */  move       $v0, $zero
/* 0040dcc8 */  sw         $a0, ($a1)
/* 0040dccc */  bltz       $a2, 0x40dcdc
/* 0040dcd0 */  slti       $at, $a2, 0x25
/* 0040dcd4 */  bnez       $at, 0x40dce4
/* 0040dcd8 */  nop        
/* 0040dcdc */  jr         $ra
/* 0040dce0 */  move       $v0, $zero
/* 0040dce4 */  lbu        $v1, ($a0)
/* 0040dce8 */  lui        $t3, 0x1000
/* 0040dcec */  addiu      $t3, $t3, 0x32e0
/* 0040dcf0 */  addu       $t6, $t3, $v1
/* 0040dcf4 */  lbu        $a3, 1($t6)
/* 0040dcf8 */  nop        
/* 0040dcfc */  andi       $t0, $a3, 7
/* 0040dd00 */  bnez       $t0, 0x40dd70
/* 0040dd04 */  nop        
/* 0040dd08 */  andi       $t7, $a3, 8
/* 0040dd0c */  beqz       $t7, 0x40dd5c
/* 0040dd10 */  addiu      $at, $zero, 0x2b
/* 0040dd14 */  lbu        $v1, 1($a0)
/* 0040dd18 */  addiu      $a0, $a0, 1
/* 0040dd1c */  addu       $t8, $t3, $v1
/* 0040dd20 */  lbu        $a3, 1($t8)
/* 0040dd24 */  nop        
/* 0040dd28 */  andi       $t9, $a3, 8
/* 0040dd2c */  bnez       $t9, 0x40dd14
/* 0040dd30 */  nop        
/* 0040dd34 */  b          0x40dd5c
/* 0040dd38 */  addiu      $at, $zero, 0x2b
/* 0040dd3c */  addiu      $v0, $zero, 1
/* 0040dd40 */  lbu        $v1, 1($a0)
/* 0040dd44 */  addiu      $a0, $a0, 1
/* 0040dd48 */  addu       $t4, $t3, $v1
/* 0040dd4c */  lbu        $a3, 1($t4)
/* 0040dd50 */  b          0x40dd70
/* 0040dd54 */  andi       $t0, $a3, 7
/* 0040dd58 */  addiu      $at, $zero, 0x2b
/* 0040dd5c */  beq        $v1, $at, 0x40dd40
/* 0040dd60 */  addiu      $at, $zero, 0x2d
/* 0040dd64 */  beq        $v1, $at, 0x40dd3c
/* 0040dd68 */  nop        
/* 0040dd6c */  andi       $t0, $a3, 7
/* 0040dd70 */  bnez       $a2, 0x40ddac
/* 0040dd74 */  addiu      $at, $zero, 0x30
/* 0040dd78 */  beq        $v1, $at, 0x40dd88
/* 0040dd7c */  nop        
/* 0040dd80 */  b          0x40ddac
/* 0040dd84 */  addiu      $a2, $zero, 0xa
/* 0040dd88 */  lbu        $t1, 1($a0)
/* 0040dd8c */  addiu      $at, $zero, 0x78
/* 0040dd90 */  beq        $t1, $at, 0x40dda0
/* 0040dd94 */  addiu      $at, $zero, 0x58
/* 0040dd98 */  bne        $t1, $at, 0x40ddac
/* 0040dd9c */  addiu      $a2, $zero, 8
/* 0040dda0 */  b          0x40ddac
/* 0040dda4 */  addiu      $a2, $zero, 0x10
/* 0040dda8 */  addiu      $a2, $zero, 8
/* 0040ddac */  beqz       $t0, 0x40ddf0
/* 0040ddb0 */  nop        
/* 0040ddb4 */  andi       $t2, $a3, 4
/* 0040ddb8 */  beqz       $t2, 0x40ddcc
/* 0040ddbc */  andi       $t5, $a3, 2
/* 0040ddc0 */  b          0x40dde4
/* 0040ddc4 */  addiu      $t1, $v1, -0x30
/* 0040ddc8 */  andi       $t5, $a3, 2
/* 0040ddcc */  beqz       $t5, 0x40dde0
/* 0040ddd0 */  addiu      $t0, $v1, -0x37
/* 0040ddd4 */  b          0x40dde0
/* 0040ddd8 */  addiu      $t0, $v1, -0x57
/* 0040dddc */  addiu      $t0, $v1, -0x37
/* 0040dde0 */  move       $t1, $t0
/* 0040dde4 */  slt        $at, $t1, $a2
/* 0040dde8 */  bnez       $at, 0x40ddfc
/* 0040ddec */  addiu      $at, $zero, 0x10
/* 0040ddf0 */  jr         $ra
/* 0040ddf4 */  move       $v0, $zero
/* 0040ddf8 */  addiu      $at, $zero, 0x10
/* 0040ddfc */  bne        $a2, $at, 0x40de5c
/* 0040de00 */  addiu      $at, $zero, 0x30
/* 0040de04 */  bne        $v1, $at, 0x40de5c
/* 0040de08 */  nop        
/* 0040de0c */  lbu        $t6, 2($a0)
/* 0040de10 */  nop        
/* 0040de14 */  addu       $t7, $t3, $t6
/* 0040de18 */  lbu        $t8, 1($t7)
/* 0040de1c */  nop        
/* 0040de20 */  andi       $t9, $t8, 0x80
/* 0040de24 */  beqz       $t9, 0x40de5c
/* 0040de28 */  nop        
/* 0040de2c */  lbu        $t1, 1($a0)
/* 0040de30 */  addiu      $at, $zero, 0x78
/* 0040de34 */  beq        $t1, $at, 0x40de44
/* 0040de38 */  addiu      $at, $zero, 0x58
/* 0040de3c */  bne        $t1, $at, 0x40de5c
/* 0040de40 */  nop        
/* 0040de44 */  lbu        $v1, 2($a0)
/* 0040de48 */  addiu      $a0, $a0, 2
/* 0040de4c */  addu       $t4, $t3, $v1
/* 0040de50 */  lbu        $a3, 1($t4)
/* 0040de54 */  nop        
/* 0040de58 */  andi       $t2, $a3, 4
/* 0040de5c */  beqz       $t2, 0x40de70
/* 0040de60 */  andi       $t5, $a3, 2
/* 0040de64 */  b          0x40de88
/* 0040de68 */  addiu      $t0, $v1, -0x30
/* 0040de6c */  andi       $t5, $a3, 2
/* 0040de70 */  beqz       $t5, 0x40de84
/* 0040de74 */  addiu      $a3, $v1, -0x37
/* 0040de78 */  b          0x40de84
/* 0040de7c */  addiu      $a3, $v1, -0x57
/* 0040de80 */  addiu      $a3, $v1, -0x37
/* 0040de84 */  move       $t0, $a3
/* 0040de88 */  lbu        $v1, 1($a0)
/* 0040de8c */  negu       $t2, $t0
/* 0040de90 */  addu       $t6, $t3, $v1
/* 0040de94 */  lbu        $a3, 1($t6)
/* 0040de98 */  addiu      $a0, $a0, 1
/* 0040de9c */  andi       $t7, $a3, 7
/* 0040dea0 */  beqz       $t7, 0x40df4c
/* 0040dea4 */  nop        
/* 0040dea8 */  andi       $t8, $a3, 4
/* 0040deac */  beqz       $t8, 0x40dec0
/* 0040deb0 */  andi       $t9, $a3, 2
/* 0040deb4 */  b          0x40ded8
/* 0040deb8 */  addiu      $t1, $v1, -0x30
/* 0040debc */  andi       $t9, $a3, 2
/* 0040dec0 */  beqz       $t9, 0x40ded4
/* 0040dec4 */  addiu      $t0, $v1, -0x37
/* 0040dec8 */  b          0x40ded4
/* 0040decc */  addiu      $t0, $v1, -0x57
/* 0040ded0 */  addiu      $t0, $v1, -0x37
/* 0040ded4 */  move       $t1, $t0
/* 0040ded8 */  slt        $at, $t1, $a2
/* 0040dedc */  beqz       $at, 0x40df4c
/* 0040dee0 */  nop        
/* 0040dee4 */  multu      $a2, $t2
/* 0040dee8 */  lbu        $v1, 1($a0)
/* 0040deec */  addiu      $a0, $a0, 1
/* 0040def0 */  addu       $t5, $t3, $v1
/* 0040def4 */  lbu        $a3, 1($t5)
/* 0040def8 */  nop        
/* 0040defc */  andi       $t6, $a3, 7
/* 0040df00 */  mflo       $t4
/* 0040df04 */  subu       $t2, $t4, $t1
/* 0040df08 */  beqz       $t6, 0x40df4c
/* 0040df0c */  nop        
/* 0040df10 */  andi       $t7, $a3, 4
/* 0040df14 */  beqz       $t7, 0x40df28
/* 0040df18 */  andi       $t8, $a3, 2
/* 0040df1c */  b          0x40df40
/* 0040df20 */  addiu      $t1, $v1, -0x30
/* 0040df24 */  andi       $t8, $a3, 2
/* 0040df28 */  beqz       $t8, 0x40df3c
/* 0040df2c */  addiu      $t0, $v1, -0x37
/* 0040df30 */  b          0x40df3c
/* 0040df34 */  addiu      $t0, $v1, -0x57
/* 0040df38 */  addiu      $t0, $v1, -0x37
/* 0040df3c */  move       $t1, $t0
/* 0040df40 */  slt        $at, $t1, $a2
/* 0040df44 */  bnez       $at, 0x40dee4
/* 0040df48 */  nop        
/* 0040df4c */  beqz       $a1, 0x40df58
/* 0040df50 */  nop        
/* 0040df54 */  sw         $a0, ($a1)
/* 0040df58 */  beqz       $v0, 0x40df6c
/* 0040df5c */  negu       $t0, $t2
/* 0040df60 */  b          0x40df6c
/* 0040df64 */  move       $t0, $t2
/* 0040df68 */  negu       $t0, $t2
/* 0040df6c */  move       $v0, $t0
/* 0040df70 */  jr         $ra
/* 0040df74 */  nop        
/* 0040df78 */  nop        
/* 0040df7c */  nop        
/* 0040df80 */  addiu      $v0, $zero, 0x3f0
/* 0040df84 */  syscall    
/* 0040df88 */  beqz       $a3, 0x40df98
/* 0040df8c */  nop        
/* 0040df90 */  j          0x40fa00
/* 0040df94 */  nop        
/* 0040df98 */  jr         $ra
/* 0040df9c */  nop        
/* 0040dfa0 */  addiu      $v0, $zero, 0x3ee
/* 0040dfa4 */  syscall    
/* 0040dfa8 */  beqz       $a3, 0x40dfb8
/* 0040dfac */  nop        
/* 0040dfb0 */  j          0x40fa00
/* 0040dfb4 */  nop        
/* 0040dfb8 */  jr         $ra
/* 0040dfbc */  move       $v0, $zero
/* 0040dfc0 */  addiu      $v0, $zero, 0x3ed
/* 0040dfc4 */  syscall    
/* 0040dfc8 */  beqz       $a3, 0x40dfd8
/* 0040dfcc */  nop        
/* 0040dfd0 */  j          0x40fa00
/* 0040dfd4 */  nop        
/* 0040dfd8 */  jr         $ra
/* 0040dfdc */  nop        
/* 0040dfe0 */  addiu      $v0, $zero, 0x3ec
/* 0040dfe4 */  syscall    
/* 0040dfe8 */  beqz       $a3, 0x40dff8
/* 0040dfec */  nop        
/* 0040dff0 */  j          0x40fa00
/* 0040dff4 */  nop        
/* 0040dff8 */  jr         $ra
/* 0040dffc */  nop        
/* 0040e000 */  addiu      $v0, $zero, 0x3eb
/* 0040e004 */  syscall    
/* 0040e008 */  beqz       $a3, 0x40e018
/* 0040e00c */  nop        
/* 0040e010 */  j          0x40fa00
/* 0040e014 */  nop        
/* 0040e018 */  jr         $ra
/* 0040e01c */  nop        
/* 0040e020 */  addiu      $v0, $zero, 0x3fb
/* 0040e024 */  syscall    
/* 0040e028 */  beqz       $a3, 0x40e038
/* 0040e02c */  nop        
/* 0040e030 */  j          0x40fa00
/* 0040e034 */  nop        
/* 0040e038 */  jr         $ra
/* 0040e03c */  nop        
/* 0040e040 */  addiu      $sp, $sp, -0x18
/* 0040e044 */  sw         $ra, 0x14($sp)
/* 0040e048 */  addiu      $a0, $zero, 6
/* 0040e04c */  jal        0x40e2b0
/* 0040e050 */  move       $a1, $zero
/* 0040e054 */  beqz       $v0, 0x40e06c
/* 0040e058 */  move       $a1, $v0
/* 0040e05c */  jal        0x40e2b0
/* 0040e060 */  addiu      $a0, $zero, 6
/* 0040e064 */  b          0x40e088
/* 0040e068 */  nop        
/* 0040e06c */  lw         $v0, -0x7ba0($gp)                        # .sdata @ 0x100041d0
/* 0040e070 */  addiu      $at, $zero, 1
/* 0040e074 */  addiu      $v0, $v0, 1
/* 0040e078 */  bne        $v0, $at, 0x40e088
/* 0040e07c */  sw         $v0, -0x7ba0($gp)                        # .sdata @ 0x100041d0
/* 0040e080 */  jal        0xf8010f8                                # strcmp
/* 0040e084 */  nop        
/* 0040e088 */  jal        0x40e270
/* 0040e08c */  nop        
/* 0040e090 */  move       $a0, $v0
/* 0040e094 */  jal        0x40fa10
/* 0040e098 */  addiu      $a1, $zero, 6
/* 0040e09c */  lw         $ra, 0x14($sp)
/* 0040e0a0 */  addiu      $sp, $sp, 0x18
/* 0040e0a4 */  jr         $ra
/* 0040e0a8 */  nop        
/* 0040e0ac */  nop        
/* 0040e0b0 */  addiu      $v0, $zero, 0x409
/* 0040e0b4 */  syscall    
/* 0040e0b8 */  beqz       $a3, 0x40e0c8
/* 0040e0bc */  nop        
/* 0040e0c0 */  j          0x40fa00
/* 0040e0c4 */  nop        
/* 0040e0c8 */  jr         $ra
/* 0040e0cc */  nop        
/* 0040e0d0 */  addiu      $v0, $zero, 0x443
/* 0040e0d4 */  syscall    
/* 0040e0d8 */  beqz       $a3, 0x40e0e8
/* 0040e0dc */  nop        
/* 0040e0e0 */  j          0x40fa00
/* 0040e0e4 */  nop        
/* 0040e0e8 */  jr         $ra
/* 0040e0ec */  nop        
/* 0040e0f0 */  addiu      $v0, $zero, 0x426
/* 0040e0f4 */  syscall    
/* 0040e0f8 */  beqz       $a3, 0x40e108
/* 0040e0fc */  nop        
/* 0040e100 */  j          0x40fa00
/* 0040e104 */  nop        
/* 0040e108 */  jr         $ra
/* 0040e10c */  nop        
/* 0040e110 */  addiu      $sp, $sp, -0x20
/* 0040e114 */  sw         $ra, 0x14($sp)
/* 0040e118 */  sw         $a0, 0x20($sp)
/* 0040e11c */  jal        0xf8010e8                                # strcat
/* 0040e120 */  sw         $a1, 0x24($sp)
/* 0040e124 */  lw         $a0, 0x20($sp)
/* 0040e128 */  bnez       $v0, 0x40e138
/* 0040e12c */  move       $a3, $v0
/* 0040e130 */  b          0x40e210
/* 0040e134 */  move       $v0, $zero
/* 0040e138 */  sb         $a0, 0xd($v0)
/* 0040e13c */  lbu        $t6, 0xd($v0)
/* 0040e140 */  sw         $zero, ($v0)
/* 0040e144 */  sb         $zero, 0xc($v0)
/* 0040e148 */  sw         $zero, 4($v0)
/* 0040e14c */  sw         $zero, 8($v0)
/* 0040e150 */  lui        $at, 0x1000
/* 0040e154 */  sll        $t7, $t6, 2
/* 0040e158 */  lw         $t8, 0x24($sp)
/* 0040e15c */  addu       $at, $at, $t7
/* 0040e160 */  sw         $zero, 0x3500($at)
/* 0040e164 */  lbu        $v1, ($t8)
/* 0040e168 */  addiu      $at, $zero, 0x61
/* 0040e16c */  beq        $v1, $at, 0x40e1a0
/* 0040e170 */  addiu      $at, $zero, 0x72
/* 0040e174 */  beq        $v1, $at, 0x40e18c
/* 0040e178 */  addiu      $at, $zero, 0x77
/* 0040e17c */  beq        $v1, $at, 0x40e1b8
/* 0040e180 */  nop        
/* 0040e184 */  b          0x40e1cc
/* 0040e188 */  nop        
/* 0040e18c */  lbu        $t9, 0xc($v0)
/* 0040e190 */  nop        
/* 0040e194 */  ori        $t0, $t9, 1
/* 0040e198 */  b          0x40e1d4
/* 0040e19c */  sb         $t0, 0xc($v0)
/* 0040e1a0 */  move       $a1, $zero
/* 0040e1a4 */  addiu      $a2, $zero, 2
/* 0040e1a8 */  jal        0x40e020
/* 0040e1ac */  sw         $a3, 0x1c($sp)
/* 0040e1b0 */  lw         $a3, 0x1c($sp)
/* 0040e1b4 */  nop        
/* 0040e1b8 */  lbu        $t1, 0xc($a3)
/* 0040e1bc */  nop        
/* 0040e1c0 */  ori        $t2, $t1, 2
/* 0040e1c4 */  b          0x40e1d4
/* 0040e1c8 */  sb         $t2, 0xc($a3)
/* 0040e1cc */  b          0x40e210
/* 0040e1d0 */  move       $v0, $zero
/* 0040e1d4 */  lw         $t3, 0x24($sp)
/* 0040e1d8 */  addiu      $at, $zero, 0x2b
/* 0040e1dc */  lbu        $t4, 1($t3)
/* 0040e1e0 */  nop        
/* 0040e1e4 */  bne        $t4, $at, 0x40e210
/* 0040e1e8 */  move       $v0, $a3
/* 0040e1ec */  lbu        $t5, 0xc($a3)
/* 0040e1f0 */  nop        
/* 0040e1f4 */  andi       $t6, $t5, 0xfc
/* 0040e1f8 */  sb         $t6, 0xc($a3)
/* 0040e1fc */  lbu        $t7, 0xc($a3)
/* 0040e200 */  nop        
/* 0040e204 */  ori        $t8, $t7, 0x80
/* 0040e208 */  sb         $t8, 0xc($a3)
/* 0040e20c */  move       $v0, $a3
/* 0040e210 */  lw         $ra, 0x14($sp)
/* 0040e214 */  addiu      $sp, $sp, 0x20
/* 0040e218 */  jr         $ra
/* 0040e21c */  nop        
/* 0040e220 */  addiu      $v0, $zero, 0x3ea
/* 0040e224 */  syscall    
/* 0040e228 */  beqz       $a3, 0x40e238
/* 0040e22c */  nop        
/* 0040e230 */  j          0x40fa00
/* 0040e234 */  nop        
/* 0040e238 */  beqz       $v1, 0x40e244
/* 0040e23c */  nop        
/* 0040e240 */  move       $v0, $zero
/* 0040e244 */  jr         $ra
/* 0040e248 */  nop        
/* 0040e24c */  nop        
/* 0040e250 */  addiu      $v0, $zero, 0x404
/* 0040e254 */  syscall    
/* 0040e258 */  beqz       $a3, 0x40e268
/* 0040e25c */  nop        
/* 0040e260 */  j          0x40fa00
/* 0040e264 */  nop        
/* 0040e268 */  jr         $ra
/* 0040e26c */  move       $v0, $zero
/* 0040e270 */  addiu      $v0, $zero, 0x3fc
/* 0040e274 */  syscall    
/* 0040e278 */  beqz       $a3, 0x40e288
/* 0040e27c */  nop        
/* 0040e280 */  j          0x40fa00
/* 0040e284 */  nop        
/* 0040e288 */  jr         $ra
/* 0040e28c */  nop        
/* 0040e290 */  addiu      $v0, $zero, 0x41e
/* 0040e294 */  syscall    
/* 0040e298 */  beqz       $a3, 0x40e2a8
/* 0040e29c */  nop        
/* 0040e2a0 */  j          0x40fa00
/* 0040e2a4 */  nop        
/* 0040e2a8 */  jr         $ra
/* 0040e2ac */  nop        
/* 0040e2b0 */  blez       $a0, 0x40e2e8
/* 0040e2b4 */  slti       $at, $a0, 0x21
/* 0040e2b8 */  beqz       $at, 0x40e2e8
/* 0040e2bc */  nop        
/* 0040e2c0 */  lui        $a2, 0x41
/* 0040e2c4 */  addiu      $a2, $a2, -0x5d0
/* 0040e2c8 */  addiu      $v0, $zero, 0x418
/* 0040e2cc */  syscall    
/* 0040e2d0 */  beqz       $a3, 0x40e2e0
/* 0040e2d4 */  nop        
/* 0040e2d8 */  j          0x40fa00
/* 0040e2dc */  nop        
/* 0040e2e0 */  jr         $ra
/* 0040e2e4 */  nop        
/* 0040e2e8 */  j          0x40fa00
/* 0040e2ec */  addiu      $v0, $zero, 0x16
/* 0040e2f0 */  addiu      $sp, $sp, -0x20
/* 0040e2f4 */  sw         $a0, 0x20($sp)
/* 0040e2f8 */  lw         $t6, 0x20($sp)
/* 0040e2fc */  sw         $ra, 0x14($sp)
/* 0040e300 */  bnez       $t6, 0x40e310
/* 0040e304 */  nop        
/* 0040e308 */  b          0x40e380
/* 0040e30c */  move       $v0, $zero
/* 0040e310 */  jal        0x40fa50
/* 0040e314 */  move       $a0, $zero
/* 0040e318 */  lw         $a0, 0x20($sp)
/* 0040e31c */  sw         $v0, 0x1c($sp)
/* 0040e320 */  move       $at, $a0
/* 0040e324 */  sll        $a0, $at, 2
/* 0040e328 */  subu       $a0, $a0, $at
/* 0040e32c */  sll        $a0, $a0, 3
/* 0040e330 */  addu       $a0, $a0, $at
/* 0040e334 */  jal        0x40fa80
/* 0040e338 */  sll        $a0, $a0, 2
/* 0040e33c */  jal        0x40fa50
/* 0040e340 */  move       $a0, $zero
/* 0040e344 */  lw         $t7, 0x1c($sp)
/* 0040e348 */  nop        
/* 0040e34c */  subu       $v1, $v0, $t7
/* 0040e350 */  bnez       $v1, 0x40e35c
/* 0040e354 */  move       $a0, $v1
/* 0040e358 */  addiu      $a0, $zero, 1
/* 0040e35c */  lw         $v0, 0x20($sp)
/* 0040e360 */  nop        
/* 0040e364 */  sltu       $at, $a0, $v0
/* 0040e368 */  beqz       $at, 0x40e37c
/* 0040e36c */  move       $v1, $zero
/* 0040e370 */  b          0x40e37c
/* 0040e374 */  subu       $v1, $v0, $a0
/* 0040e378 */  move       $v1, $zero
/* 0040e37c */  move       $v0, $v1
/* 0040e380 */  lw         $ra, 0x14($sp)
/* 0040e384 */  addiu      $sp, $sp, 0x20
/* 0040e388 */  jr         $ra
/* 0040e38c */  nop        
/* 0040e390 */  addiu      $v0, $zero, 0x453
/* 0040e394 */  syscall    
/* 0040e398 */  beqz       $a3, 0x40e3a8
/* 0040e39c */  nop        
/* 0040e3a0 */  j          0x40fa00
/* 0040e3a4 */  nop        
/* 0040e3a8 */  jr         $ra
/* 0040e3ac */  nop        
/* 0040e3b0 */  lbu        $v0, ($a0)
/* 0040e3b4 */  move       $v1, $a0
/* 0040e3b8 */  beqz       $v0, 0x40e3d0
/* 0040e3bc */  addiu      $a0, $a0, 1
/* 0040e3c0 */  lbu        $v0, ($a0)
/* 0040e3c4 */  addiu      $a0, $a0, 1
/* 0040e3c8 */  bnez       $v0, 0x40e3c0
/* 0040e3cc */  nop        
/* 0040e3d0 */  lbu        $v0, ($a1)
/* 0040e3d4 */  addiu      $a0, $a0, -1
/* 0040e3d8 */  addiu      $a0, $a0, 1
/* 0040e3dc */  addiu      $a1, $a1, 1
/* 0040e3e0 */  beqz       $v0, 0x40e3fc
/* 0040e3e4 */  sb         $v0, -1($a0)
/* 0040e3e8 */  lbu        $v0, ($a1)
/* 0040e3ec */  addiu      $a0, $a0, 1
/* 0040e3f0 */  addiu      $a1, $a1, 1
/* 0040e3f4 */  bnez       $v0, 0x40e3e8
/* 0040e3f8 */  sb         $v0, -1($a0)
/* 0040e3fc */  jr         $ra
/* 0040e400 */  move       $v0, $v1
/* 0040e404 */  nop        
/* 0040e408 */  nop        
/* 0040e40c */  nop        
/* 0040e410 */  addiu      $sp, $sp, -0x18
/* 0040e414 */  sw         $a0, 0x18($sp)
/* 0040e418 */  move       $a2, $a1
/* 0040e41c */  lw         $a1, 0x18($sp)
/* 0040e420 */  sw         $ra, 0x14($sp)
/* 0040e424 */  jal        0x40faa0
/* 0040e428 */  addiu      $a0, $zero, 0x46d
/* 0040e42c */  lw         $ra, 0x14($sp)
/* 0040e430 */  addiu      $sp, $sp, 0x18
/* 0040e434 */  jr         $ra
/* 0040e438 */  nop        
/* 0040e43c */  nop        
/* 0040e440 */  addiu      $v0, $zero, 0x442
/* 0040e444 */  syscall    
/* 0040e448 */  beqz       $a3, 0x40e458
/* 0040e44c */  nop        
/* 0040e450 */  j          0x40fa00
/* 0040e454 */  nop        
/* 0040e458 */  jr         $ra
/* 0040e45c */  nop        
/* 0040e460 */  addiu      $sp, $sp, -0x20
/* 0040e464 */  sw         $a0, 0x20($sp)
/* 0040e468 */  move       $v1, $a2
/* 0040e46c */  lw         $a2, 0x20($sp)
/* 0040e470 */  sw         $ra, 0x1c($sp)
/* 0040e474 */  move       $a3, $a1
/* 0040e478 */  move       $a1, $zero
/* 0040e47c */  sw         $v1, 0x10($sp)
/* 0040e480 */  jal        0x40faa0
/* 0040e484 */  addiu      $a0, $zero, 0x41c
/* 0040e488 */  lw         $ra, 0x1c($sp)
/* 0040e48c */  addiu      $sp, $sp, 0x20
/* 0040e490 */  jr         $ra
/* 0040e494 */  nop        
/* 0040e498 */  addiu      $sp, $sp, -0x20
/* 0040e49c */  addiu      $t6, $sp, 0x24
/* 0040e4a0 */  addiu      $v1, $zero, -4
/* 0040e4a4 */  addiu      $t7, $t6, 7
/* 0040e4a8 */  and        $t8, $t7, $v1
/* 0040e4ac */  sw         $ra, 0x1c($sp)
/* 0040e4b0 */  addiu      $t9, $t8, 7
/* 0040e4b4 */  sw         $a0, 0x20($sp)
/* 0040e4b8 */  sw         $a1, 0x24($sp)
/* 0040e4bc */  sw         $a2, 0x28($sp)
/* 0040e4c0 */  sw         $a3, 0x2c($sp)
/* 0040e4c4 */  and        $t0, $t9, $v1
/* 0040e4c8 */  lw         $v0, -4($t0)
/* 0040e4cc */  lw         $a2, 0x20($sp)
/* 0040e4d0 */  lw         $a3, 0x24($sp)
/* 0040e4d4 */  addiu      $a1, $zero, 1
/* 0040e4d8 */  addiu      $a0, $zero, 0x41c
/* 0040e4dc */  jal        0x40faa0
/* 0040e4e0 */  sw         $v0, 0x10($sp)
/* 0040e4e4 */  lw         $ra, 0x1c($sp)
/* 0040e4e8 */  addiu      $sp, $sp, 0x20
/* 0040e4ec */  jr         $ra
/* 0040e4f0 */  nop        
/* 0040e4f4 */  addiu      $sp, $sp, -0x18
/* 0040e4f8 */  sw         $ra, 0x14($sp)
/* 0040e4fc */  move       $a2, $a0
/* 0040e500 */  addiu      $a0, $zero, 0x41c
/* 0040e504 */  jal        0x40faa0
/* 0040e508 */  addiu      $a1, $zero, 2
/* 0040e50c */  lw         $ra, 0x14($sp)
/* 0040e510 */  addiu      $sp, $sp, 0x18
/* 0040e514 */  jr         $ra
/* 0040e518 */  nop        
/* 0040e51c */  addiu      $sp, $sp, -0x20
/* 0040e520 */  sw         $a0, 0x20($sp)
/* 0040e524 */  move       $v1, $a2
/* 0040e528 */  lw         $a2, 0x20($sp)
/* 0040e52c */  sw         $ra, 0x1c($sp)
/* 0040e530 */  move       $a3, $a1
/* 0040e534 */  addiu      $a1, $zero, 3
/* 0040e538 */  sw         $v1, 0x10($sp)
/* 0040e53c */  jal        0x40faa0
/* 0040e540 */  addiu      $a0, $zero, 0x41c
/* 0040e544 */  lw         $ra, 0x1c($sp)
/* 0040e548 */  addiu      $sp, $sp, 0x20
/* 0040e54c */  jr         $ra
/* 0040e550 */  nop        
/* 0040e554 */  nop        
/* 0040e558 */  nop        
/* 0040e55c */  nop        
/* 0040e560 */  addiu      $v0, $zero, 0x47e
/* 0040e564 */  syscall    
/* 0040e568 */  beqz       $a3, 0x40e578
/* 0040e56c */  nop        
/* 0040e570 */  j          0x40fa00
/* 0040e574 */  nop        
/* 0040e578 */  jr         $ra
/* 0040e57c */  nop        
/* 0040e580 */  addiu      $sp, $sp, -0x18
/* 0040e584 */  sw         $a1, 0x1c($sp)
/* 0040e588 */  sw         $a0, 0x18($sp)
/* 0040e58c */  move       $a3, $a2
/* 0040e590 */  lw         $a2, 0x1c($sp)
/* 0040e594 */  lw         $a1, 0x18($sp)
/* 0040e598 */  sw         $ra, 0x14($sp)
/* 0040e59c */  jal        0x40faa0
/* 0040e5a0 */  addiu      $a0, $zero, 0x46c
/* 0040e5a4 */  lw         $ra, 0x14($sp)
/* 0040e5a8 */  addiu      $sp, $sp, 0x18
/* 0040e5ac */  jr         $ra
/* 0040e5b0 */  nop        
/* 0040e5b4 */  nop        
/* 0040e5b8 */  nop        
/* 0040e5bc */  nop        
/* 0040e5c0 */  addiu      $v0, $zero, 0x3e9
/* 0040e5c4 */  syscall    
/* 0040e5c8 */  jr         $ra
/* 0040e5cc */  nop        
/* 0040e5d0 */  sw         $zero, -0x7aa0($gp)                      # .sbss @ 0x100042d0
/* 0040e5d4 */  sw         $zero, -0x7a9c($gp)                      # .sbss @ 0x100042d4
/* 0040e5d8 */  addiu      $sp, $sp, -0x170
/* 0040e5dc */  sw         $s4, 0x2c($sp)
/* 0040e5e0 */  sw         $s5, 0x30($sp)
/* 0040e5e4 */  sw         $s3, 0x28($sp)
/* 0040e5e8 */  sw         $s0, 0x1c($sp)
/* 0040e5ec */  sw         $ra, 0x3c($sp)
/* 0040e5f0 */  sw         $s7, 0x38($sp)
/* 0040e5f4 */  sw         $s6, 0x34($sp)
/* 0040e5f8 */  sw         $s2, 0x24($sp)
/* 0040e5fc */  sw         $s1, 0x20($sp)
/* 0040e600 */  sw         $a2, 0x178($sp)
/* 0040e604 */  lui        $s4, 0x1000
/* 0040e608 */  sw         $a3, 0x17c($sp)
/* 0040e60c */  move       $s0, $a0
/* 0040e610 */  move       $s3, $a1
/* 0040e614 */  sw         $zero, 0x68($sp)
/* 0040e618 */  addiu      $s4, $s4, 0x32e0
/* 0040e61c */  addiu      $s5, $zero, 0x64
/* 0040e620 */  lbu        $s1, ($s3)
/* 0040e624 */  addiu      $s3, $s3, 1
/* 0040e628 */  bnez       $s1, 0x40e640
/* 0040e62c */  addu       $t6, $s4, $s1
/* 0040e630 */  lw         $v0, 0x68($sp)
/* 0040e634 */  b          0x40ebdc
/* 0040e638 */  lw         $ra, 0x3c($sp)
/* 0040e63c */  addu       $t6, $s4, $s1
/* 0040e640 */  lbu        $t7, 1($t6)
/* 0040e644 */  nop        
/* 0040e648 */  andi       $t8, $t7, 8
/* 0040e64c */  beqz       $t8, 0x40e78c
/* 0040e650 */  addiu      $at, $zero, 0x25
/* 0040e654 */  lw         $t9, -0x7a9c($gp)                        # .sbss @ 0x100042d4
/* 0040e658 */  nop        
/* 0040e65c */  bnez       $t9, 0x40e620
/* 0040e660 */  nop        
/* 0040e664 */  lw         $t0, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e668 */  nop        
/* 0040e66c */  addiu      $t1, $t0, 1
/* 0040e670 */  sw         $t1, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e674 */  lbu        $t2, 0xd($s0)
/* 0040e678 */  lw         $v1, ($s0)
/* 0040e67c */  bne        $s5, $t2, 0x40e698
/* 0040e680 */  addiu      $v0, $v1, -1
/* 0040e684 */  bnez       $v1, 0x40e698
/* 0040e688 */  addiu      $v0, $v1, -1
/* 0040e68c */  b          0x40e6c8
/* 0040e690 */  addiu      $a0, $zero, -1
/* 0040e694 */  addiu      $v0, $v1, -1
/* 0040e698 */  bgez       $v0, 0x40e6b0
/* 0040e69c */  sw         $v0, ($s0)
/* 0040e6a0 */  jal        0xf8010e0                                # strcpy
/* 0040e6a4 */  move       $a0, $s0
/* 0040e6a8 */  b          0x40e6c4
/* 0040e6ac */  move       $v1, $v0
/* 0040e6b0 */  lw         $v0, 4($s0)
/* 0040e6b4 */  nop        
/* 0040e6b8 */  lbu        $v1, ($v0)
/* 0040e6bc */  addiu      $t3, $v0, 1
/* 0040e6c0 */  sw         $t3, 4($s0)
/* 0040e6c4 */  move       $a0, $v1
/* 0040e6c8 */  addu       $t4, $s4, $a0
/* 0040e6cc */  lbu        $t5, 1($t4)
/* 0040e6d0 */  nop        
/* 0040e6d4 */  andi       $t6, $t5, 8
/* 0040e6d8 */  beqz       $t6, 0x40e75c
/* 0040e6dc */  nop        
/* 0040e6e0 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e6e4 */  nop        
/* 0040e6e8 */  addiu      $t8, $t7, 1
/* 0040e6ec */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e6f0 */  lbu        $t9, 0xd($s0)
/* 0040e6f4 */  lw         $v1, ($s0)
/* 0040e6f8 */  bne        $s5, $t9, 0x40e714
/* 0040e6fc */  addiu      $v0, $v1, -1
/* 0040e700 */  bnez       $v1, 0x40e714
/* 0040e704 */  addiu      $v0, $v1, -1
/* 0040e708 */  b          0x40e744
/* 0040e70c */  addiu      $a0, $zero, -1
/* 0040e710 */  addiu      $v0, $v1, -1
/* 0040e714 */  bgez       $v0, 0x40e72c
/* 0040e718 */  sw         $v0, ($s0)
/* 0040e71c */  jal        0xf8010e0                                # strcpy
/* 0040e720 */  move       $a0, $s0
/* 0040e724 */  b          0x40e740
/* 0040e728 */  move       $v1, $v0
/* 0040e72c */  lw         $v0, 4($s0)
/* 0040e730 */  nop        
/* 0040e734 */  lbu        $v1, ($v0)
/* 0040e738 */  addiu      $t0, $v0, 1
/* 0040e73c */  sw         $t0, 4($s0)
/* 0040e740 */  move       $a0, $v1
/* 0040e744 */  addu       $t1, $s4, $a0
/* 0040e748 */  lbu        $t2, 1($t1)
/* 0040e74c */  nop        
/* 0040e750 */  andi       $t3, $t2, 8
/* 0040e754 */  bnez       $t3, 0x40e6e0
/* 0040e758 */  nop        
/* 0040e75c */  lw         $t4, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e760 */  move       $a1, $s0
/* 0040e764 */  addiu      $t5, $t4, -1
/* 0040e768 */  jal        0xf801378                                # sleep
/* 0040e76c */  sw         $t5, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e770 */  addiu      $at, $zero, -1
/* 0040e774 */  bne        $v0, $at, 0x40e620
/* 0040e778 */  nop        
/* 0040e77c */  addiu      $t6, $zero, 1
/* 0040e780 */  b          0x40e620
/* 0040e784 */  sw         $t6, -0x7a9c($gp)                        # .sbss @ 0x100042d4
/* 0040e788 */  addiu      $at, $zero, 0x25
/* 0040e78c */  bne        $s1, $at, 0x40e7a4
/* 0040e790 */  nop        
/* 0040e794 */  lbu        $s1, ($s3)
/* 0040e798 */  addiu      $at, $zero, 0x25
/* 0040e79c */  bne        $s1, $at, 0x40e83c
/* 0040e7a0 */  addiu      $s3, $s3, 1
/* 0040e7a4 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e7a8 */  nop        
/* 0040e7ac */  addiu      $t8, $t7, 1
/* 0040e7b0 */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e7b4 */  lbu        $t9, 0xd($s0)
/* 0040e7b8 */  lw         $v1, ($s0)
/* 0040e7bc */  bne        $s5, $t9, 0x40e7d8
/* 0040e7c0 */  addiu      $v0, $v1, -1
/* 0040e7c4 */  bnez       $v1, 0x40e7d8
/* 0040e7c8 */  addiu      $v0, $v1, -1
/* 0040e7cc */  b          0x40e808
/* 0040e7d0 */  addiu      $a0, $zero, -1
/* 0040e7d4 */  addiu      $v0, $v1, -1
/* 0040e7d8 */  bgez       $v0, 0x40e7f0
/* 0040e7dc */  sw         $v0, ($s0)
/* 0040e7e0 */  jal        0xf8010e0                                # strcpy
/* 0040e7e4 */  move       $a0, $s0
/* 0040e7e8 */  b          0x40e804
/* 0040e7ec */  move       $v1, $v0
/* 0040e7f0 */  lw         $v0, 4($s0)
/* 0040e7f4 */  nop        
/* 0040e7f8 */  lbu        $v1, ($v0)
/* 0040e7fc */  addiu      $t0, $v0, 1
/* 0040e800 */  sw         $t0, 4($s0)
/* 0040e804 */  move       $a0, $v1
/* 0040e808 */  beq        $a0, $s1, 0x40e620
/* 0040e80c */  nop        
/* 0040e810 */  lw         $t1, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e814 */  move       $a1, $s0
/* 0040e818 */  addiu      $t2, $t1, -1
/* 0040e81c */  jal        0xf801378                                # sleep
/* 0040e820 */  sw         $t2, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e824 */  addiu      $at, $zero, -1
/* 0040e828 */  beq        $v0, $at, 0x40ebbc
/* 0040e82c */  lw         $t0, 0x68($sp)
/* 0040e830 */  lw         $v0, 0x68($sp)
/* 0040e834 */  b          0x40ebdc
/* 0040e838 */  lw         $ra, 0x3c($sp)
/* 0040e83c */  addiu      $at, $zero, 0x2a
/* 0040e840 */  bne        $s1, $at, 0x40e858
/* 0040e844 */  move       $s2, $zero
/* 0040e848 */  lbu        $s1, ($s3)
/* 0040e84c */  move       $s7, $zero
/* 0040e850 */  b          0x40e85c
/* 0040e854 */  addiu      $s3, $s3, 1
/* 0040e858 */  addiu      $s7, $zero, 1
/* 0040e85c */  addu       $t3, $s4, $s1
/* 0040e860 */  lbu        $t4, 1($t3)
/* 0040e864 */  nop        
/* 0040e868 */  andi       $t5, $t4, 4
/* 0040e86c */  beqz       $t5, 0x40e8a4
/* 0040e870 */  nop        
/* 0040e874 */  sll        $t6, $s2, 2
/* 0040e878 */  addu       $t6, $t6, $s2
/* 0040e87c */  sll        $t6, $t6, 1
/* 0040e880 */  addu       $s2, $t6, $s1
/* 0040e884 */  lbu        $s1, ($s3)
/* 0040e888 */  addiu      $s2, $s2, -0x30
/* 0040e88c */  addu       $t7, $s4, $s1
/* 0040e890 */  lbu        $t8, 1($t7)
/* 0040e894 */  addiu      $s3, $s3, 1
/* 0040e898 */  andi       $t9, $t8, 4
/* 0040e89c */  bnez       $t9, 0x40e878
/* 0040e8a0 */  sll        $t6, $s2, 2
/* 0040e8a4 */  bnez       $s2, 0x40e8b8
/* 0040e8a8 */  addiu      $at, $zero, 0x6c
/* 0040e8ac */  lui        $s2, 0x7fff
/* 0040e8b0 */  ori        $s2, $s2, 0xffff
/* 0040e8b4 */  addiu      $at, $zero, 0x6c
/* 0040e8b8 */  beq        $s1, $at, 0x40e8cc
/* 0040e8bc */  move       $s6, $s1
/* 0040e8c0 */  addiu      $at, $zero, 0x68
/* 0040e8c4 */  bne        $s1, $at, 0x40e8d4
/* 0040e8c8 */  nop        
/* 0040e8cc */  lbu        $s1, ($s3)
/* 0040e8d0 */  addiu      $s3, $s3, 1
/* 0040e8d4 */  beqz       $s1, 0x40e8f8
/* 0040e8d8 */  addiu      $at, $zero, 0x5b
/* 0040e8dc */  bne        $s1, $at, 0x40e904
/* 0040e8e0 */  addu       $v0, $s4, $s1
/* 0040e8e4 */  move       $a0, $s3
/* 0040e8e8 */  jal        0x40f8d8
/* 0040e8ec */  addiu      $a1, $sp, 0x70
/* 0040e8f0 */  bnez       $v0, 0x40e900
/* 0040e8f4 */  move       $s3, $v0
/* 0040e8f8 */  b          0x40ebd8
/* 0040e8fc */  addiu      $v0, $zero, -1
/* 0040e900 */  addu       $v0, $s4, $s1
/* 0040e904 */  lbu        $t0, 1($v0)
/* 0040e908 */  nop        
/* 0040e90c */  andi       $t1, $t0, 1
/* 0040e910 */  beqz       $t1, 0x40e924
/* 0040e914 */  addiu      $at, $zero, 0x6e
/* 0040e918 */  lbu        $s1, 0x102($v0)
/* 0040e91c */  addiu      $s6, $zero, 0x6c
/* 0040e920 */  addiu      $at, $zero, 0x6e
/* 0040e924 */  beq        $s1, $at, 0x40eb1c
/* 0040e928 */  addiu      $at, $zero, 0x5b
/* 0040e92c */  lw         $t2, -0x7a9c($gp)                        # .sbss @ 0x100042d4
/* 0040e930 */  nop        
/* 0040e934 */  bnez       $t2, 0x40eb18
/* 0040e938 */  addiu      $at, $zero, 0x63
/* 0040e93c */  beq        $s1, $at, 0x40eb18
/* 0040e940 */  addiu      $at, $zero, 0x5b
/* 0040e944 */  beq        $s1, $at, 0x40eb1c
/* 0040e948 */  addiu      $at, $zero, 0x5b
/* 0040e94c */  lw         $t3, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e950 */  nop        
/* 0040e954 */  addiu      $t4, $t3, 1
/* 0040e958 */  sw         $t4, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e95c */  lbu        $t5, 0xd($s0)
/* 0040e960 */  lw         $v1, ($s0)
/* 0040e964 */  bne        $s5, $t5, 0x40e980
/* 0040e968 */  addiu      $v0, $v1, -1
/* 0040e96c */  bnez       $v1, 0x40e980
/* 0040e970 */  addiu      $v0, $v1, -1
/* 0040e974 */  b          0x40e9b0
/* 0040e978 */  addiu      $a0, $zero, -1
/* 0040e97c */  addiu      $v0, $v1, -1
/* 0040e980 */  bgez       $v0, 0x40e998
/* 0040e984 */  sw         $v0, ($s0)
/* 0040e988 */  jal        0xf8010e0                                # strcpy
/* 0040e98c */  move       $a0, $s0
/* 0040e990 */  b          0x40e9ac
/* 0040e994 */  move       $v1, $v0
/* 0040e998 */  lw         $v0, 4($s0)
/* 0040e99c */  nop        
/* 0040e9a0 */  lbu        $v1, ($v0)
/* 0040e9a4 */  addiu      $t6, $v0, 1
/* 0040e9a8 */  sw         $t6, 4($s0)
/* 0040e9ac */  move       $a0, $v1
/* 0040e9b0 */  addu       $t7, $s4, $a0
/* 0040e9b4 */  lbu        $t8, 1($t7)
/* 0040e9b8 */  nop        
/* 0040e9bc */  andi       $t9, $t8, 8
/* 0040e9c0 */  beqz       $t9, 0x40ea44
/* 0040e9c4 */  nop        
/* 0040e9c8 */  lw         $t0, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e9cc */  nop        
/* 0040e9d0 */  addiu      $t1, $t0, 1
/* 0040e9d4 */  sw         $t1, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040e9d8 */  lbu        $t2, 0xd($s0)
/* 0040e9dc */  lw         $v1, ($s0)
/* 0040e9e0 */  bne        $s5, $t2, 0x40e9fc
/* 0040e9e4 */  addiu      $v0, $v1, -1
/* 0040e9e8 */  bnez       $v1, 0x40e9fc
/* 0040e9ec */  addiu      $v0, $v1, -1
/* 0040e9f0 */  b          0x40ea2c
/* 0040e9f4 */  addiu      $a0, $zero, -1
/* 0040e9f8 */  addiu      $v0, $v1, -1
/* 0040e9fc */  bgez       $v0, 0x40ea14
/* 0040ea00 */  sw         $v0, ($s0)
/* 0040ea04 */  jal        0xf8010e0                                # strcpy
/* 0040ea08 */  move       $a0, $s0
/* 0040ea0c */  b          0x40ea28
/* 0040ea10 */  move       $v1, $v0
/* 0040ea14 */  lw         $v0, 4($s0)
/* 0040ea18 */  nop        
/* 0040ea1c */  lbu        $v1, ($v0)
/* 0040ea20 */  addiu      $t3, $v0, 1
/* 0040ea24 */  sw         $t3, 4($s0)
/* 0040ea28 */  move       $a0, $v1
/* 0040ea2c */  addu       $t4, $s4, $a0
/* 0040ea30 */  lbu        $t5, 1($t4)
/* 0040ea34 */  nop        
/* 0040ea38 */  andi       $t6, $t5, 8
/* 0040ea3c */  bnez       $t6, 0x40e9c8
/* 0040ea40 */  nop        
/* 0040ea44 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040ea48 */  move       $a1, $s0
/* 0040ea4c */  addiu      $t8, $t7, -1
/* 0040ea50 */  jal        0xf801378                                # sleep
/* 0040ea54 */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040ea58 */  addiu      $at, $zero, -1
/* 0040ea5c */  bne        $v0, $at, 0x40eb1c
/* 0040ea60 */  addiu      $at, $zero, 0x5b
/* 0040ea64 */  b          0x40ebbc
/* 0040ea68 */  lw         $t0, 0x68($sp)
/* 0040ea6c */  addiu      $t9, $sp, 0x178
/* 0040ea70 */  sw         $t9, 0x14($sp)
/* 0040ea74 */  move       $a0, $s7
/* 0040ea78 */  move       $a1, $s1
/* 0040ea7c */  move       $a2, $s2
/* 0040ea80 */  addiu      $a3, $sp, 0x70
/* 0040ea84 */  jal        0x40f5f4
/* 0040ea88 */  sw         $s0, 0x10($sp)
/* 0040ea8c */  b          0x40eb64
/* 0040ea90 */  nop        
/* 0040ea94 */  addiu      $at, $zero, 0x68
/* 0040ea98 */  bne        $s6, $at, 0x40eac8
/* 0040ea9c */  addiu      $at, $zero, 0x6c
/* 0040eaa0 */  lw         $t0, 0x178($sp)
/* 0040eaa4 */  addiu      $at, $zero, -4
/* 0040eaa8 */  addiu      $t1, $t0, 7
/* 0040eaac */  and        $t2, $t1, $at
/* 0040eab0 */  sw         $t2, 0x178($sp)
/* 0040eab4 */  lw         $t4, -4($t2)
/* 0040eab8 */  lw         $t3, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040eabc */  b          0x40e620
/* 0040eac0 */  sh         $t3, ($t4)
/* 0040eac4 */  addiu      $at, $zero, 0x6c
/* 0040eac8 */  bne        $s6, $at, 0x40eaf8
/* 0040eacc */  lw         $t0, 0x178($sp)
/* 0040ead0 */  lw         $t5, 0x178($sp)
/* 0040ead4 */  addiu      $at, $zero, -4
/* 0040ead8 */  addiu      $t6, $t5, 7
/* 0040eadc */  and        $t7, $t6, $at
/* 0040eae0 */  sw         $t7, 0x178($sp)
/* 0040eae4 */  lw         $t9, -4($t7)
/* 0040eae8 */  lw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040eaec */  b          0x40e620
/* 0040eaf0 */  sw         $t8, ($t9)
/* 0040eaf4 */  lw         $t0, 0x178($sp)
/* 0040eaf8 */  addiu      $at, $zero, -4
/* 0040eafc */  addiu      $t1, $t0, 7
/* 0040eb00 */  and        $t2, $t1, $at
/* 0040eb04 */  sw         $t2, 0x178($sp)
/* 0040eb08 */  lw         $t4, -4($t2)
/* 0040eb0c */  lw         $t3, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040eb10 */  b          0x40e620
/* 0040eb14 */  sw         $t3, ($t4)
/* 0040eb18 */  addiu      $at, $zero, 0x5b
/* 0040eb1c */  beq        $s1, $at, 0x40ea6c
/* 0040eb20 */  addiu      $at, $zero, 0x63
/* 0040eb24 */  beq        $s1, $at, 0x40ea6c
/* 0040eb28 */  addiu      $at, $zero, 0x69
/* 0040eb2c */  beq        $s1, $at, 0x40eb44
/* 0040eb30 */  addiu      $at, $zero, 0x6e
/* 0040eb34 */  beq        $s1, $at, 0x40ea94
/* 0040eb38 */  addiu      $at, $zero, 0x73
/* 0040eb3c */  beq        $s1, $at, 0x40ea70
/* 0040eb40 */  addiu      $t9, $sp, 0x178
/* 0040eb44 */  addiu      $t5, $sp, 0x178
/* 0040eb48 */  sw         $t5, 0x14($sp)
/* 0040eb4c */  move       $a0, $s7
/* 0040eb50 */  move       $a1, $s1
/* 0040eb54 */  move       $a2, $s2
/* 0040eb58 */  move       $a3, $s6
/* 0040eb5c */  jal        0x40ec04
/* 0040eb60 */  sw         $s0, 0x10($sp)
/* 0040eb64 */  beqz       $v0, 0x40eb80
/* 0040eb68 */  nop        
/* 0040eb6c */  lw         $t6, 0x68($sp)
/* 0040eb70 */  nop        
/* 0040eb74 */  addu       $t7, $t6, $s7
/* 0040eb78 */  b          0x40e620
/* 0040eb7c */  sw         $t7, 0x68($sp)
/* 0040eb80 */  lw         $t8, -0x7a9c($gp)                        # .sbss @ 0x100042d4
/* 0040eb84 */  nop        
/* 0040eb88 */  beqz       $t8, 0x40ebac
/* 0040eb8c */  lw         $a0, 0x68($sp)
/* 0040eb90 */  lw         $t9, 0x68($sp)
/* 0040eb94 */  nop        
/* 0040eb98 */  bnez       $t9, 0x40ebac
/* 0040eb9c */  lw         $a0, 0x68($sp)
/* 0040eba0 */  b          0x40ebb0
/* 0040eba4 */  addiu      $a0, $zero, -1
/* 0040eba8 */  lw         $a0, 0x68($sp)
/* 0040ebac */  nop        
/* 0040ebb0 */  b          0x40ebd8
/* 0040ebb4 */  move       $v0, $a0
/* 0040ebb8 */  lw         $t0, 0x68($sp)
/* 0040ebbc */  nop        
/* 0040ebc0 */  beqz       $t0, 0x40ebd4
/* 0040ebc4 */  addiu      $a0, $zero, -1
/* 0040ebc8 */  b          0x40ebd4
/* 0040ebcc */  move       $a0, $t0
/* 0040ebd0 */  addiu      $a0, $zero, -1
/* 0040ebd4 */  move       $v0, $a0
/* 0040ebd8 */  lw         $ra, 0x3c($sp)
/* 0040ebdc */  lw         $s0, 0x1c($sp)
/* 0040ebe0 */  lw         $s1, 0x20($sp)
/* 0040ebe4 */  lw         $s2, 0x24($sp)
/* 0040ebe8 */  lw         $s3, 0x28($sp)
/* 0040ebec */  lw         $s4, 0x2c($sp)
/* 0040ebf0 */  lw         $s5, 0x30($sp)
/* 0040ebf4 */  lw         $s6, 0x34($sp)
/* 0040ebf8 */  lw         $s7, 0x38($sp)
/* 0040ebfc */  jr         $ra
/* 0040ec00 */  addiu      $sp, $sp, 0x170
/* 0040ec04 */  addiu      $sp, $sp, -0xb8
/* 0040ec08 */  sw         $a1, 0xbc($sp)
/* 0040ec0c */  sw         $ra, 0x1c($sp)
/* 0040ec10 */  sw         $s0, 0x18($sp)
/* 0040ec14 */  lw         $t6, 0xbc($sp)
/* 0040ec18 */  sw         $a0, 0xb8($sp)
/* 0040ec1c */  addiu      $t7, $t6, -0x64
/* 0040ec20 */  sw         $a3, 0xc4($sp)
/* 0040ec24 */  sltiu      $at, $t7, 0x15
/* 0040ec28 */  sw         $zero, 0x54($sp)
/* 0040ec2c */  sw         $zero, 0x50($sp)
/* 0040ec30 */  move       $t1, $a2
/* 0040ec34 */  addiu      $t0, $sp, 0x78
/* 0040ec38 */  move       $t5, $zero
/* 0040ec3c */  move       $t3, $zero
/* 0040ec40 */  move       $t4, $zero
/* 0040ec44 */  beqz       $at, 0x40ec88
/* 0040ec48 */  sw         $zero, 0x4c($sp)
/* 0040ec4c */  sll        $t7, $t7, 2
/* 0040ec50 */  lui        $at, 0x1000
/* 0040ec54 */  addu       $at, $at, $t7
/* 0040ec58 */  lw         $t7, 0x160($at)
/* 0040ec5c */  nop        
/* 0040ec60 */  jr         $t7
/* 0040ec64 */  nop        
/* 0040ec68 */  addiu      $t8, $zero, 1
/* 0040ec6c */  sw         $t8, 0x54($sp)
/* 0040ec70 */  b          0x40ec90
/* 0040ec74 */  addiu      $t2, $zero, 0xa
/* 0040ec78 */  b          0x40ec90
/* 0040ec7c */  addiu      $t2, $zero, 8
/* 0040ec80 */  b          0x40ec90
/* 0040ec84 */  addiu      $t2, $zero, 0x10
/* 0040ec88 */  b          0x40f5e4
/* 0040ec8c */  move       $v0, $zero
/* 0040ec90 */  lw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040ec94 */  lw         $s0, 0xc8($sp)
/* 0040ec98 */  addiu      $t6, $t9, 1
/* 0040ec9c */  sw         $t6, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040eca0 */  lbu        $t7, 0xd($s0)
/* 0040eca4 */  addiu      $at, $zero, 0x64
/* 0040eca8 */  bne        $t7, $at, 0x40ecc8
/* 0040ecac */  nop        
/* 0040ecb0 */  lw         $t8, ($s0)
/* 0040ecb4 */  nop        
/* 0040ecb8 */  bnez       $t8, 0x40ecc8
/* 0040ecbc */  nop        
/* 0040ecc0 */  b          0x40ed34
/* 0040ecc4 */  addiu      $v0, $zero, -1
/* 0040ecc8 */  lw         $v0, ($s0)
/* 0040eccc */  nop        
/* 0040ecd0 */  addiu      $v0, $v0, -1
/* 0040ecd4 */  bgez       $v0, 0x40ed1c
/* 0040ecd8 */  sw         $v0, ($s0)
/* 0040ecdc */  sw         $t0, 0x6c($sp)
/* 0040ece0 */  sw         $t1, 0xc0($sp)
/* 0040ece4 */  sw         $t2, 0x64($sp)
/* 0040ece8 */  sw         $t3, 0x5c($sp)
/* 0040ecec */  sw         $t4, 0x58($sp)
/* 0040ecf0 */  move       $a0, $s0
/* 0040ecf4 */  jal        0xf8010e0                                # strcpy
/* 0040ecf8 */  sw         $t5, 0x60($sp)
/* 0040ecfc */  lw         $t0, 0x6c($sp)
/* 0040ed00 */  lw         $t1, 0xc0($sp)
/* 0040ed04 */  lw         $t2, 0x64($sp)
/* 0040ed08 */  lw         $t3, 0x5c($sp)
/* 0040ed0c */  lw         $t4, 0x58($sp)
/* 0040ed10 */  lw         $t5, 0x60($sp)
/* 0040ed14 */  b          0x40ed30
/* 0040ed18 */  move       $v1, $v0
/* 0040ed1c */  lw         $v0, 4($s0)
/* 0040ed20 */  nop        
/* 0040ed24 */  lbu        $v1, ($v0)
/* 0040ed28 */  addiu      $t9, $v0, 1
/* 0040ed2c */  sw         $t9, 4($s0)
/* 0040ed30 */  move       $v0, $v1
/* 0040ed34 */  b          0x40f154
/* 0040ed38 */  move       $a3, $v0
/* 0040ed3c */  addiu      $t6, $zero, 1
/* 0040ed40 */  sw         $t6, 0x50($sp)
/* 0040ed44 */  addiu      $t1, $t1, -1
/* 0040ed48 */  blez       $t1, 0x40f170
/* 0040ed4c */  nop        
/* 0040ed50 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040ed54 */  addiu      $at, $zero, 0x64
/* 0040ed58 */  addiu      $t8, $t7, 1
/* 0040ed5c */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040ed60 */  lbu        $t9, 0xd($s0)
/* 0040ed64 */  lw         $v1, ($s0)
/* 0040ed68 */  bne        $t9, $at, 0x40ed84
/* 0040ed6c */  addiu      $v0, $v1, -1
/* 0040ed70 */  bnez       $v1, 0x40ed84
/* 0040ed74 */  addiu      $v0, $v1, -1
/* 0040ed78 */  b          0x40ede4
/* 0040ed7c */  addiu      $v0, $zero, -1
/* 0040ed80 */  addiu      $v0, $v1, -1
/* 0040ed84 */  bgez       $v0, 0x40edcc
/* 0040ed88 */  sw         $v0, ($s0)
/* 0040ed8c */  sw         $t0, 0x6c($sp)
/* 0040ed90 */  sw         $t1, 0xc0($sp)
/* 0040ed94 */  sw         $t2, 0x64($sp)
/* 0040ed98 */  sw         $t3, 0x5c($sp)
/* 0040ed9c */  sw         $t4, 0x58($sp)
/* 0040eda0 */  move       $a0, $s0
/* 0040eda4 */  jal        0xf8010e0                                # strcpy
/* 0040eda8 */  sw         $t5, 0x60($sp)
/* 0040edac */  lw         $t0, 0x6c($sp)
/* 0040edb0 */  lw         $t1, 0xc0($sp)
/* 0040edb4 */  lw         $t2, 0x64($sp)
/* 0040edb8 */  lw         $t3, 0x5c($sp)
/* 0040edbc */  lw         $t4, 0x58($sp)
/* 0040edc0 */  lw         $t5, 0x60($sp)
/* 0040edc4 */  b          0x40ede0
/* 0040edc8 */  move       $v1, $v0
/* 0040edcc */  lw         $v0, 4($s0)
/* 0040edd0 */  nop        
/* 0040edd4 */  lbu        $v1, ($v0)
/* 0040edd8 */  addiu      $t6, $v0, 1
/* 0040eddc */  sw         $t6, 4($s0)
/* 0040ede0 */  move       $v0, $v1
/* 0040ede4 */  addiu      $at, $zero, 0x30
/* 0040ede8 */  bne        $v0, $at, 0x40f170
/* 0040edec */  move       $a3, $v0
/* 0040edf0 */  lw         $t7, 0xbc($sp)
/* 0040edf4 */  addiu      $at, $zero, 0x69
/* 0040edf8 */  bne        $t7, $at, 0x40f170
/* 0040edfc */  slti       $at, $t1, 2
/* 0040ee00 */  bnez       $at, 0x40f170
/* 0040ee04 */  nop        
/* 0040ee08 */  lw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040ee0c */  addiu      $at, $zero, 0x64
/* 0040ee10 */  addiu      $t9, $t8, 1
/* 0040ee14 */  sw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040ee18 */  lbu        $t6, 0xd($s0)
/* 0040ee1c */  lw         $v1, ($s0)
/* 0040ee20 */  bne        $t6, $at, 0x40ee3c
/* 0040ee24 */  addiu      $v0, $v1, -1
/* 0040ee28 */  bnez       $v1, 0x40ee3c
/* 0040ee2c */  addiu      $v0, $v1, -1
/* 0040ee30 */  b          0x40eea4
/* 0040ee34 */  addiu      $v0, $zero, -1
/* 0040ee38 */  addiu      $v0, $v1, -1
/* 0040ee3c */  bgez       $v0, 0x40ee8c
/* 0040ee40 */  sw         $v0, ($s0)
/* 0040ee44 */  sw         $a3, 0x68($sp)
/* 0040ee48 */  sw         $t0, 0x6c($sp)
/* 0040ee4c */  sw         $t1, 0xc0($sp)
/* 0040ee50 */  sw         $t2, 0x64($sp)
/* 0040ee54 */  sw         $t3, 0x5c($sp)
/* 0040ee58 */  sw         $t4, 0x58($sp)
/* 0040ee5c */  move       $a0, $s0
/* 0040ee60 */  jal        0xf8010e0                                # strcpy
/* 0040ee64 */  sw         $t5, 0x60($sp)
/* 0040ee68 */  lw         $a3, 0x68($sp)
/* 0040ee6c */  lw         $t0, 0x6c($sp)
/* 0040ee70 */  lw         $t1, 0xc0($sp)
/* 0040ee74 */  lw         $t2, 0x64($sp)
/* 0040ee78 */  lw         $t3, 0x5c($sp)
/* 0040ee7c */  lw         $t4, 0x58($sp)
/* 0040ee80 */  lw         $t5, 0x60($sp)
/* 0040ee84 */  b          0x40eea0
/* 0040ee88 */  move       $v1, $v0
/* 0040ee8c */  lw         $v0, 4($s0)
/* 0040ee90 */  nop        
/* 0040ee94 */  lbu        $v1, ($v0)
/* 0040ee98 */  addiu      $t7, $v0, 1
/* 0040ee9c */  sw         $t7, 4($s0)
/* 0040eea0 */  move       $v0, $v1
/* 0040eea4 */  andi       $v1, $v0, 0xff
/* 0040eea8 */  addiu      $at, $zero, 0x78
/* 0040eeac */  beq        $v1, $at, 0x40eec0
/* 0040eeb0 */  sb         $v0, 0x74($sp)
/* 0040eeb4 */  addiu      $at, $zero, 0x58
/* 0040eeb8 */  bne        $v1, $at, 0x40f0f8
/* 0040eebc */  nop        
/* 0040eec0 */  lbu        $a0, 0xd($s0)
/* 0040eec4 */  lw         $v1, ($s0)
/* 0040eec8 */  addiu      $at, $zero, 0x64
/* 0040eecc */  beq        $a0, $at, 0x40eedc
/* 0040eed0 */  nop        
/* 0040eed4 */  beqz       $v1, 0x40ef74
/* 0040eed8 */  nop        
/* 0040eedc */  lw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040eee0 */  addiu      $at, $zero, 0x64
/* 0040eee4 */  addiu      $t9, $t8, 1
/* 0040eee8 */  bne        $a0, $at, 0x40ef00
/* 0040eeec */  sw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040eef0 */  bnez       $v1, 0x40ef04
/* 0040eef4 */  addiu      $v0, $v1, -1
/* 0040eef8 */  b          0x40ef6c
/* 0040eefc */  addiu      $v0, $zero, -1
/* 0040ef00 */  addiu      $v0, $v1, -1
/* 0040ef04 */  bgez       $v0, 0x40ef54
/* 0040ef08 */  sw         $v0, ($s0)
/* 0040ef0c */  sw         $a3, 0x68($sp)
/* 0040ef10 */  sw         $t0, 0x6c($sp)
/* 0040ef14 */  sw         $t1, 0xc0($sp)
/* 0040ef18 */  sw         $t2, 0x64($sp)
/* 0040ef1c */  sw         $t3, 0x5c($sp)
/* 0040ef20 */  sw         $t4, 0x58($sp)
/* 0040ef24 */  move       $a0, $s0
/* 0040ef28 */  jal        0xf8010e0                                # strcpy
/* 0040ef2c */  sw         $t5, 0x60($sp)
/* 0040ef30 */  lw         $a3, 0x68($sp)
/* 0040ef34 */  lw         $t0, 0x6c($sp)
/* 0040ef38 */  lw         $t1, 0xc0($sp)
/* 0040ef3c */  lw         $t2, 0x64($sp)
/* 0040ef40 */  lw         $t3, 0x5c($sp)
/* 0040ef44 */  lw         $t4, 0x58($sp)
/* 0040ef48 */  lw         $t5, 0x60($sp)
/* 0040ef4c */  b          0x40ef68
/* 0040ef50 */  move       $v1, $v0
/* 0040ef54 */  lw         $v0, 4($s0)
/* 0040ef58 */  nop        
/* 0040ef5c */  lbu        $v1, ($v0)
/* 0040ef60 */  addiu      $t6, $v0, 1
/* 0040ef64 */  sw         $t6, 4($s0)
/* 0040ef68 */  move       $v0, $v1
/* 0040ef6c */  b          0x40efe4
/* 0040ef70 */  andi       $v1, $v0, 0xff
/* 0040ef74 */  sw         $a3, 0x68($sp)
/* 0040ef78 */  sw         $t0, 0x6c($sp)
/* 0040ef7c */  sw         $t1, 0xc0($sp)
/* 0040ef80 */  sw         $t2, 0x64($sp)
/* 0040ef84 */  sw         $t3, 0x5c($sp)
/* 0040ef88 */  sw         $t4, 0x58($sp)
/* 0040ef8c */  addiu      $a1, $sp, 0x78
/* 0040ef90 */  addiu      $a2, $zero, 1
/* 0040ef94 */  jal        0x40e000
/* 0040ef98 */  sw         $t5, 0x60($sp)
/* 0040ef9c */  lw         $a3, 0x68($sp)
/* 0040efa0 */  lw         $t0, 0x6c($sp)
/* 0040efa4 */  lw         $t1, 0xc0($sp)
/* 0040efa8 */  lw         $t2, 0x64($sp)
/* 0040efac */  lw         $t3, 0x5c($sp)
/* 0040efb0 */  lw         $t4, 0x58($sp)
/* 0040efb4 */  lw         $t5, 0x60($sp)
/* 0040efb8 */  addiu      $at, $zero, 1
/* 0040efbc */  bne        $v0, $at, 0x40efd4
/* 0040efc0 */  addiu      $v1, $zero, 0xff
/* 0040efc4 */  lbu        $v1, 0x78($sp)
/* 0040efc8 */  b          0x40efd4
/* 0040efcc */  nop        
/* 0040efd0 */  addiu      $v1, $zero, 0xff
/* 0040efd4 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040efd8 */  nop        
/* 0040efdc */  addiu      $t8, $t7, 1
/* 0040efe0 */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040efe4 */  lui        $t9, 0x1000
/* 0040efe8 */  addu       $t9, $t9, $v1
/* 0040efec */  lbu        $t9, 0x32e1($t9)
/* 0040eff0 */  nop        
/* 0040eff4 */  andi       $t6, $t9, 0x80
/* 0040eff8 */  beqz       $t6, 0x40f06c
/* 0040effc */  slti       $at, $t1, 3
/* 0040f000 */  beqz       $at, 0x40f060
/* 0040f004 */  addiu      $t2, $zero, 0x10
/* 0040f008 */  sw         $a3, 0x68($sp)
/* 0040f00c */  sw         $t0, 0x6c($sp)
/* 0040f010 */  sw         $t1, 0xc0($sp)
/* 0040f014 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f018 */  sw         $t2, 0x64($sp)
/* 0040f01c */  sw         $t3, 0x5c($sp)
/* 0040f020 */  addiu      $t8, $t7, -1
/* 0040f024 */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f028 */  sw         $t4, 0x58($sp)
/* 0040f02c */  move       $a0, $v1
/* 0040f030 */  move       $a1, $s0
/* 0040f034 */  jal        0xf801378                                # sleep
/* 0040f038 */  sw         $t5, 0x60($sp)
/* 0040f03c */  lw         $t1, 0xc0($sp)
/* 0040f040 */  lw         $a3, 0x68($sp)
/* 0040f044 */  lw         $t0, 0x6c($sp)
/* 0040f048 */  lw         $t2, 0x64($sp)
/* 0040f04c */  lw         $t3, 0x5c($sp)
/* 0040f050 */  lw         $t4, 0x58($sp)
/* 0040f054 */  lw         $t5, 0x60($sp)
/* 0040f058 */  b          0x40f170
/* 0040f05c */  addiu      $t1, $t1, -1
/* 0040f060 */  move       $a3, $v1
/* 0040f064 */  b          0x40f170
/* 0040f068 */  addiu      $t1, $t1, -2
/* 0040f06c */  sw         $a3, 0x68($sp)
/* 0040f070 */  sw         $t0, 0x6c($sp)
/* 0040f074 */  sw         $t1, 0xc0($sp)
/* 0040f078 */  lw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f07c */  sw         $t2, 0x64($sp)
/* 0040f080 */  sw         $t3, 0x5c($sp)
/* 0040f084 */  addiu      $t6, $t9, -1
/* 0040f088 */  sw         $t6, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f08c */  sw         $t4, 0x58($sp)
/* 0040f090 */  move       $a0, $v1
/* 0040f094 */  move       $a1, $s0
/* 0040f098 */  jal        0xf801378                                # sleep
/* 0040f09c */  sw         $t5, 0x60($sp)
/* 0040f0a0 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f0a4 */  lw         $a3, 0x68($sp)
/* 0040f0a8 */  lw         $t0, 0x6c($sp)
/* 0040f0ac */  lw         $t1, 0xc0($sp)
/* 0040f0b0 */  lw         $t2, 0x64($sp)
/* 0040f0b4 */  lw         $t3, 0x5c($sp)
/* 0040f0b8 */  lw         $t4, 0x58($sp)
/* 0040f0bc */  lw         $t5, 0x60($sp)
/* 0040f0c0 */  lbu        $a0, 0x74($sp)
/* 0040f0c4 */  addiu      $t8, $t7, -1
/* 0040f0c8 */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f0cc */  jal        0xf801378                                # sleep
/* 0040f0d0 */  move       $a1, $s0
/* 0040f0d4 */  lw         $a3, 0x68($sp)
/* 0040f0d8 */  lw         $t0, 0x6c($sp)
/* 0040f0dc */  lw         $t1, 0xc0($sp)
/* 0040f0e0 */  lw         $t2, 0x64($sp)
/* 0040f0e4 */  lw         $t3, 0x5c($sp)
/* 0040f0e8 */  lw         $t4, 0x58($sp)
/* 0040f0ec */  lw         $t5, 0x60($sp)
/* 0040f0f0 */  b          0x40f174
/* 0040f0f4 */  addiu      $t1, $t1, -1
/* 0040f0f8 */  sw         $a3, 0x68($sp)
/* 0040f0fc */  sw         $t0, 0x6c($sp)
/* 0040f100 */  sw         $t1, 0xc0($sp)
/* 0040f104 */  lw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f108 */  sw         $t3, 0x5c($sp)
/* 0040f10c */  sw         $t4, 0x58($sp)
/* 0040f110 */  addiu      $t2, $zero, 8
/* 0040f114 */  addiu      $t6, $t9, -1
/* 0040f118 */  sw         $t6, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f11c */  sw         $t2, 0x64($sp)
/* 0040f120 */  move       $a0, $v1
/* 0040f124 */  move       $a1, $s0
/* 0040f128 */  jal        0xf801378                                # sleep
/* 0040f12c */  sw         $t5, 0x60($sp)
/* 0040f130 */  lw         $a3, 0x68($sp)
/* 0040f134 */  lw         $t0, 0x6c($sp)
/* 0040f138 */  lw         $t1, 0xc0($sp)
/* 0040f13c */  lw         $t2, 0x64($sp)
/* 0040f140 */  lw         $t3, 0x5c($sp)
/* 0040f144 */  lw         $t4, 0x58($sp)
/* 0040f148 */  lw         $t5, 0x60($sp)
/* 0040f14c */  b          0x40f174
/* 0040f150 */  addiu      $t1, $t1, -1
/* 0040f154 */  addiu      $at, $zero, 0x2b
/* 0040f158 */  beq        $v0, $at, 0x40ed44
/* 0040f15c */  addiu      $at, $zero, 0x2d
/* 0040f160 */  beq        $v0, $at, 0x40ed3c
/* 0040f164 */  addiu      $at, $zero, 0x30
/* 0040f168 */  beq        $v0, $at, 0x40edf4
/* 0040f16c */  lw         $t7, 0xbc($sp)
/* 0040f170 */  addiu      $t1, $t1, -1
/* 0040f174 */  bltz       $t1, 0x40f42c
/* 0040f178 */  lw         $t9, 0xb8($sp)
/* 0040f17c */  addiu      $t7, $sp, 0xb7
/* 0040f180 */  sltu       $at, $t0, $t7
/* 0040f184 */  bnez       $at, 0x40f19c
/* 0040f188 */  nop        
/* 0040f18c */  addiu      $t8, $zero, 0x22
/* 0040f190 */  sw         $t8, -0x7a84($gp)                        # .sbss @ 0x100042ec
/* 0040f194 */  b          0x40f5e4
/* 0040f198 */  move       $v0, $zero
/* 0040f19c */  lui        $v0, 0x1000
/* 0040f1a0 */  addu       $v0, $v0, $a3
/* 0040f1a4 */  lbu        $v0, 0x32e1($v0)
/* 0040f1a8 */  nop        
/* 0040f1ac */  andi       $v1, $v0, 4
/* 0040f1b0 */  bnez       $v1, 0x40f1cc
/* 0040f1b4 */  addiu      $at, $zero, 0x10
/* 0040f1b8 */  bne        $t2, $at, 0x40f24c
/* 0040f1bc */  lw         $t8, 0x54($sp)
/* 0040f1c0 */  andi       $t9, $v0, 0x80
/* 0040f1c4 */  beqz       $t9, 0x40f24c
/* 0040f1c8 */  lw         $t8, 0x54($sp)
/* 0040f1cc */  beqz       $v1, 0x40f1e0
/* 0040f1d0 */  andi       $t6, $v0, 1
/* 0040f1d4 */  b          0x40f1f8
/* 0040f1d8 */  addiu      $v0, $zero, 0x30
/* 0040f1dc */  andi       $t6, $v0, 1
/* 0040f1e0 */  beqz       $t6, 0x40f1f4
/* 0040f1e4 */  addiu      $v1, $zero, 0x57
/* 0040f1e8 */  b          0x40f1f4
/* 0040f1ec */  addiu      $v1, $zero, 0x37
/* 0040f1f0 */  addiu      $v1, $zero, 0x57
/* 0040f1f4 */  move       $v0, $v1
/* 0040f1f8 */  subu       $v1, $a3, $v0
/* 0040f1fc */  slt        $at, $v1, $t2
/* 0040f200 */  beqz       $at, 0x40f42c
/* 0040f204 */  lw         $t9, 0xb8($sp)
/* 0040f208 */  lw         $t7, 0xb8($sp)
/* 0040f20c */  nop        
/* 0040f210 */  beqz       $t7, 0x40f240
/* 0040f214 */  nop        
/* 0040f218 */  lw         $t8, 0x54($sp)
/* 0040f21c */  nop        
/* 0040f220 */  bnez       $t8, 0x40f240
/* 0040f224 */  nop        
/* 0040f228 */  lw         $t9, 0x4c($sp)
/* 0040f22c */  nop        
/* 0040f230 */  multu      $t2, $t9
/* 0040f234 */  mflo       $t6
/* 0040f238 */  addu       $t7, $t6, $v1
/* 0040f23c */  sw         $t7, 0x4c($sp)
/* 0040f240 */  b          0x40f374
/* 0040f244 */  addiu      $t5, $t5, 1
/* 0040f248 */  lw         $t8, 0x54($sp)
/* 0040f24c */  nop        
/* 0040f250 */  beqz       $t8, 0x40f428
/* 0040f254 */  addiu      $at, $zero, 0x2e
/* 0040f258 */  bne        $a3, $at, 0x40f270
/* 0040f25c */  addiu      $at, $zero, 0x65
/* 0040f260 */  move       $v0, $t3
/* 0040f264 */  beqz       $v0, 0x40f374
/* 0040f268 */  addiu      $t3, $t3, 1
/* 0040f26c */  addiu      $at, $zero, 0x65
/* 0040f270 */  beq        $a3, $at, 0x40f280
/* 0040f274 */  addiu      $at, $zero, 0x45
/* 0040f278 */  bne        $a3, $at, 0x40f42c
/* 0040f27c */  lw         $t9, 0xb8($sp)
/* 0040f280 */  beqz       $t5, 0x40f42c
/* 0040f284 */  lw         $t9, 0xb8($sp)
/* 0040f288 */  move       $v0, $t4
/* 0040f28c */  bnez       $v0, 0x40f428
/* 0040f290 */  addiu      $t4, $t4, 1
/* 0040f294 */  sb         $a3, ($t0)
/* 0040f298 */  lw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f29c */  addiu      $at, $zero, 0x64
/* 0040f2a0 */  addiu      $t6, $t9, 1
/* 0040f2a4 */  sw         $t6, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f2a8 */  lbu        $t7, 0xd($s0)
/* 0040f2ac */  addiu      $t0, $t0, 1
/* 0040f2b0 */  bne        $t7, $at, 0x40f2d0
/* 0040f2b4 */  nop        
/* 0040f2b8 */  lw         $t8, ($s0)
/* 0040f2bc */  nop        
/* 0040f2c0 */  bnez       $t8, 0x40f2d0
/* 0040f2c4 */  nop        
/* 0040f2c8 */  b          0x40f33c
/* 0040f2cc */  addiu      $v0, $zero, -1
/* 0040f2d0 */  lw         $v0, ($s0)
/* 0040f2d4 */  nop        
/* 0040f2d8 */  addiu      $v0, $v0, -1
/* 0040f2dc */  bgez       $v0, 0x40f324
/* 0040f2e0 */  sw         $v0, ($s0)
/* 0040f2e4 */  sw         $t0, 0x6c($sp)
/* 0040f2e8 */  sw         $t1, 0xc0($sp)
/* 0040f2ec */  sw         $t2, 0x64($sp)
/* 0040f2f0 */  sw         $t3, 0x5c($sp)
/* 0040f2f4 */  sw         $t4, 0x58($sp)
/* 0040f2f8 */  move       $a0, $s0
/* 0040f2fc */  jal        0xf8010e0                                # strcpy
/* 0040f300 */  sw         $t5, 0x60($sp)
/* 0040f304 */  lw         $t0, 0x6c($sp)
/* 0040f308 */  lw         $t1, 0xc0($sp)
/* 0040f30c */  lw         $t2, 0x64($sp)
/* 0040f310 */  lw         $t3, 0x5c($sp)
/* 0040f314 */  lw         $t4, 0x58($sp)
/* 0040f318 */  lw         $t5, 0x60($sp)
/* 0040f31c */  b          0x40f338
/* 0040f320 */  move       $v1, $v0
/* 0040f324 */  lw         $v0, 4($s0)
/* 0040f328 */  nop        
/* 0040f32c */  lbu        $v1, ($v0)
/* 0040f330 */  addiu      $t9, $v0, 1
/* 0040f334 */  sw         $t9, 4($s0)
/* 0040f338 */  move       $v0, $v1
/* 0040f33c */  lui        $v1, 0x1000
/* 0040f340 */  addu       $v1, $v1, $v0
/* 0040f344 */  lbu        $v1, 0x32e1($v1)
/* 0040f348 */  move       $a3, $v0
/* 0040f34c */  andi       $t6, $v1, 4
/* 0040f350 */  bnez       $t6, 0x40f374
/* 0040f354 */  addiu      $at, $zero, 0x2b
/* 0040f358 */  beq        $v0, $at, 0x40f374
/* 0040f35c */  addiu      $at, $zero, 0x2d
/* 0040f360 */  beq        $v0, $at, 0x40f374
/* 0040f364 */  nop        
/* 0040f368 */  andi       $t7, $v1, 8
/* 0040f36c */  beqz       $t7, 0x40f42c
/* 0040f370 */  lw         $t9, 0xb8($sp)
/* 0040f374 */  sb         $a3, ($t0)
/* 0040f378 */  lw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f37c */  addiu      $at, $zero, 0x64
/* 0040f380 */  addiu      $t9, $t8, 1
/* 0040f384 */  sw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f388 */  lbu        $t6, 0xd($s0)
/* 0040f38c */  addiu      $t0, $t0, 1
/* 0040f390 */  bne        $t6, $at, 0x40f3b0
/* 0040f394 */  nop        
/* 0040f398 */  lw         $t7, ($s0)
/* 0040f39c */  nop        
/* 0040f3a0 */  bnez       $t7, 0x40f3b0
/* 0040f3a4 */  nop        
/* 0040f3a8 */  b          0x40f41c
/* 0040f3ac */  addiu      $v0, $zero, -1
/* 0040f3b0 */  lw         $v0, ($s0)
/* 0040f3b4 */  nop        
/* 0040f3b8 */  addiu      $v0, $v0, -1
/* 0040f3bc */  bgez       $v0, 0x40f404
/* 0040f3c0 */  sw         $v0, ($s0)
/* 0040f3c4 */  sw         $t0, 0x6c($sp)
/* 0040f3c8 */  sw         $t1, 0xc0($sp)
/* 0040f3cc */  sw         $t2, 0x64($sp)
/* 0040f3d0 */  sw         $t3, 0x5c($sp)
/* 0040f3d4 */  sw         $t4, 0x58($sp)
/* 0040f3d8 */  move       $a0, $s0
/* 0040f3dc */  jal        0xf8010e0                                # strcpy
/* 0040f3e0 */  sw         $t5, 0x60($sp)
/* 0040f3e4 */  lw         $t0, 0x6c($sp)
/* 0040f3e8 */  lw         $t1, 0xc0($sp)
/* 0040f3ec */  lw         $t2, 0x64($sp)
/* 0040f3f0 */  lw         $t3, 0x5c($sp)
/* 0040f3f4 */  lw         $t4, 0x58($sp)
/* 0040f3f8 */  lw         $t5, 0x60($sp)
/* 0040f3fc */  b          0x40f418
/* 0040f400 */  move       $v1, $v0
/* 0040f404 */  lw         $v0, 4($s0)
/* 0040f408 */  nop        
/* 0040f40c */  lbu        $v1, ($v0)
/* 0040f410 */  addiu      $t8, $v0, 1
/* 0040f414 */  sw         $t8, 4($s0)
/* 0040f418 */  move       $v0, $v1
/* 0040f41c */  addiu      $t1, $t1, -1
/* 0040f420 */  bgez       $t1, 0x40f17c
/* 0040f424 */  move       $a3, $v0
/* 0040f428 */  lw         $t9, 0xb8($sp)
/* 0040f42c */  nop        
/* 0040f430 */  beqz       $t9, 0x40f5ac
/* 0040f434 */  nop        
/* 0040f438 */  beqz       $t5, 0x40f5ac
/* 0040f43c */  nop        
/* 0040f440 */  lw         $t6, 0x54($sp)
/* 0040f444 */  nop        
/* 0040f448 */  beqz       $t6, 0x40f4e8
/* 0040f44c */  lw         $t7, 0x50($sp)
/* 0040f450 */  sb         $zero, ($t0)
/* 0040f454 */  sw         $t5, 0x60($sp)
/* 0040f458 */  sw         $a3, 0x68($sp)
/* 0040f45c */  jal        0xf801010
/* 0040f460 */  addiu      $a0, $sp, 0x78
/* 0040f464 */  lw         $t7, 0x50($sp)
/* 0040f468 */  lw         $a3, 0x68($sp)
/* 0040f46c */  lw         $t5, 0x60($sp)
/* 0040f470 */  beqz       $t7, 0x40f47c
/* 0040f474 */  mov.d      $f2, $f0
/* 0040f478 */  neg.d      $f2, $f0
/* 0040f47c */  lw         $t8, 0xc4($sp)
/* 0040f480 */  addiu      $at, $zero, 0x6c
/* 0040f484 */  bne        $t8, $at, 0x40f4c0
/* 0040f488 */  lw         $v1, 0xcc($sp)
/* 0040f48c */  lw         $v1, 0xcc($sp)
/* 0040f490 */  addiu      $at, $zero, -4
/* 0040f494 */  lw         $v0, ($v1)
/* 0040f498 */  nop        
/* 0040f49c */  addiu      $v0, $v0, 7
/* 0040f4a0 */  and        $v0, $v0, $at
/* 0040f4a4 */  sw         $v0, ($v1)
/* 0040f4a8 */  lw         $t9, -4($v0)
/* 0040f4ac */  nop        
/* 0040f4b0 */  swc1       $f3, ($t9)
/* 0040f4b4 */  b          0x40f5ac
/* 0040f4b8 */  swc1       $f2, 4($t9)
/* 0040f4bc */  lw         $v1, 0xcc($sp)
/* 0040f4c0 */  addiu      $at, $zero, -4
/* 0040f4c4 */  lw         $v0, ($v1)
/* 0040f4c8 */  cvt.s.d    $f4, $f2
/* 0040f4cc */  addiu      $v0, $v0, 7
/* 0040f4d0 */  and        $v0, $v0, $at
/* 0040f4d4 */  sw         $v0, ($v1)
/* 0040f4d8 */  lw         $t6, -4($v0)
/* 0040f4dc */  b          0x40f5ac
/* 0040f4e0 */  swc1       $f4, ($t6)
/* 0040f4e4 */  lw         $t7, 0x50($sp)
/* 0040f4e8 */  nop        
/* 0040f4ec */  bnez       $t7, 0x40f504
/* 0040f4f0 */  lw         $a0, 0x4c($sp)
/* 0040f4f4 */  lw         $a0, 0x4c($sp)
/* 0040f4f8 */  b          0x40f518
/* 0040f4fc */  lw         $t8, 0xc4($sp)
/* 0040f500 */  lw         $a0, 0x4c($sp)
/* 0040f504 */  lui        $at, 0x8000
/* 0040f508 */  beq        $a0, $at, 0x40f518
/* 0040f50c */  lw         $t8, 0xc4($sp)
/* 0040f510 */  negu       $a0, $a0
/* 0040f514 */  lw         $t8, 0xc4($sp)
/* 0040f518 */  addiu      $at, $zero, 0x6c
/* 0040f51c */  bne        $t8, $at, 0x40f550
/* 0040f520 */  lw         $t6, 0xc4($sp)
/* 0040f524 */  lw         $v1, 0xcc($sp)
/* 0040f528 */  addiu      $at, $zero, -4
/* 0040f52c */  lw         $v0, ($v1)
/* 0040f530 */  nop        
/* 0040f534 */  addiu      $v0, $v0, 7
/* 0040f538 */  and        $v0, $v0, $at
/* 0040f53c */  sw         $v0, ($v1)
/* 0040f540 */  lw         $t9, -4($v0)
/* 0040f544 */  b          0x40f5ac
/* 0040f548 */  sw         $a0, ($t9)
/* 0040f54c */  lw         $t6, 0xc4($sp)
/* 0040f550 */  addiu      $at, $zero, 0x68
/* 0040f554 */  bne        $t6, $at, 0x40f588
/* 0040f558 */  lw         $v1, 0xcc($sp)
/* 0040f55c */  lw         $v1, 0xcc($sp)
/* 0040f560 */  addiu      $at, $zero, -4
/* 0040f564 */  lw         $v0, ($v1)
/* 0040f568 */  nop        
/* 0040f56c */  addiu      $v0, $v0, 7
/* 0040f570 */  and        $v0, $v0, $at
/* 0040f574 */  sw         $v0, ($v1)
/* 0040f578 */  lw         $t7, -4($v0)
/* 0040f57c */  b          0x40f5ac
/* 0040f580 */  sh         $a0, ($t7)
/* 0040f584 */  lw         $v1, 0xcc($sp)
/* 0040f588 */  addiu      $at, $zero, -4
/* 0040f58c */  lw         $v0, ($v1)
/* 0040f590 */  nop        
/* 0040f594 */  addiu      $v0, $v0, 7
/* 0040f598 */  and        $v0, $v0, $at
/* 0040f59c */  sw         $v0, ($v1)
/* 0040f5a0 */  lw         $t8, -4($v0)
/* 0040f5a4 */  nop        
/* 0040f5a8 */  sw         $a0, ($t8)
/* 0040f5ac */  lw         $t9, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f5b0 */  sw         $t5, 0x60($sp)
/* 0040f5b4 */  addiu      $t6, $t9, -1
/* 0040f5b8 */  sw         $t6, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f5bc */  move       $a0, $a3
/* 0040f5c0 */  jal        0xf801378                                # sleep
/* 0040f5c4 */  move       $a1, $s0
/* 0040f5c8 */  lw         $t5, 0x60($sp)
/* 0040f5cc */  addiu      $at, $zero, -1
/* 0040f5d0 */  bne        $v0, $at, 0x40f5e4
/* 0040f5d4 */  move       $v0, $t5
/* 0040f5d8 */  addiu      $t7, $zero, 1
/* 0040f5dc */  sw         $t7, -0x7a9c($gp)                        # .sbss @ 0x100042d4
/* 0040f5e0 */  move       $v0, $t5
/* 0040f5e4 */  lw         $ra, 0x1c($sp)
/* 0040f5e8 */  lw         $s0, 0x18($sp)
/* 0040f5ec */  jr         $ra
/* 0040f5f0 */  addiu      $sp, $sp, 0xb8
/* 0040f5f4 */  addiu      $sp, $sp, -0x30
/* 0040f5f8 */  sw         $a0, 0x30($sp)
/* 0040f5fc */  lw         $t6, 0x30($sp)
/* 0040f600 */  sw         $ra, 0x1c($sp)
/* 0040f604 */  sw         $s0, 0x18($sp)
/* 0040f608 */  sw         $a3, 0x3c($sp)
/* 0040f60c */  beqz       $t6, 0x40f63c
/* 0040f610 */  move       $t0, $a1
/* 0040f614 */  lw         $v0, 0x44($sp)
/* 0040f618 */  addiu      $at, $zero, -4
/* 0040f61c */  lw         $a0, ($v0)
/* 0040f620 */  nop        
/* 0040f624 */  addiu      $a0, $a0, 7
/* 0040f628 */  and        $a0, $a0, $at
/* 0040f62c */  sw         $a0, ($v0)
/* 0040f630 */  lw         $a3, -4($a0)
/* 0040f634 */  b          0x40f644
/* 0040f638 */  sw         $a3, 0x24($sp)
/* 0040f63c */  move       $a3, $zero
/* 0040f640 */  sw         $zero, 0x24($sp)
/* 0040f644 */  addiu      $at, $zero, 0x63
/* 0040f648 */  bne        $t0, $at, 0x40f660
/* 0040f64c */  lui        $at, 0x7fff
/* 0040f650 */  ori        $at, $at, 0xffff
/* 0040f654 */  bne        $a2, $at, 0x40f660
/* 0040f658 */  nop        
/* 0040f65c */  addiu      $a2, $zero, 1
/* 0040f660 */  lw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f664 */  lw         $s0, 0x40($sp)
/* 0040f668 */  addiu      $t8, $t7, 1
/* 0040f66c */  sw         $t8, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f670 */  lbu        $t9, 0xd($s0)
/* 0040f674 */  addiu      $at, $zero, 0x64
/* 0040f678 */  bne        $t9, $at, 0x40f698
/* 0040f67c */  nop        
/* 0040f680 */  lw         $t2, ($s0)
/* 0040f684 */  nop        
/* 0040f688 */  bnez       $t2, 0x40f698
/* 0040f68c */  nop        
/* 0040f690 */  b          0x40f6ec
/* 0040f694 */  addiu      $a0, $zero, -1
/* 0040f698 */  lw         $v0, ($s0)
/* 0040f69c */  nop        
/* 0040f6a0 */  addiu      $v0, $v0, -1
/* 0040f6a4 */  bgez       $v0, 0x40f6d4
/* 0040f6a8 */  sw         $v0, ($s0)
/* 0040f6ac */  sw         $a2, 0x38($sp)
/* 0040f6b0 */  sw         $a3, 0x28($sp)
/* 0040f6b4 */  move       $a0, $s0
/* 0040f6b8 */  jal        0xf8010e0                                # strcpy
/* 0040f6bc */  sw         $t0, 0x34($sp)
/* 0040f6c0 */  lw         $a2, 0x38($sp)
/* 0040f6c4 */  lw         $a3, 0x28($sp)
/* 0040f6c8 */  lw         $t0, 0x34($sp)
/* 0040f6cc */  b          0x40f6e8
/* 0040f6d0 */  move       $v1, $v0
/* 0040f6d4 */  lw         $v0, 4($s0)
/* 0040f6d8 */  nop        
/* 0040f6dc */  lbu        $v1, ($v0)
/* 0040f6e0 */  addiu      $t3, $v0, 1
/* 0040f6e4 */  sw         $t3, 4($s0)
/* 0040f6e8 */  move       $a0, $v1
/* 0040f6ec */  addiu      $t1, $zero, -1
/* 0040f6f0 */  beq        $a0, $t1, 0x40f830
/* 0040f6f4 */  addiu      $at, $zero, 0x73
/* 0040f6f8 */  bne        $t0, $at, 0x40f71c
/* 0040f6fc */  addiu      $at, $zero, 0x5b
/* 0040f700 */  lui        $t4, 0x1000
/* 0040f704 */  addu       $t4, $t4, $a0
/* 0040f708 */  lbu        $t4, 0x32e1($t4)
/* 0040f70c */  nop        
/* 0040f710 */  andi       $t5, $t4, 8
/* 0040f714 */  bnez       $t5, 0x40f830
/* 0040f718 */  addiu      $at, $zero, 0x5b
/* 0040f71c */  bne        $t0, $at, 0x40f744
/* 0040f720 */  lw         $t9, 0x30($sp)
/* 0040f724 */  lw         $t6, 0x3c($sp)
/* 0040f728 */  nop        
/* 0040f72c */  addu       $t7, $t6, $a0
/* 0040f730 */  lbu        $t8, ($t7)
/* 0040f734 */  nop        
/* 0040f738 */  bnez       $t8, 0x40f830
/* 0040f73c */  nop        
/* 0040f740 */  lw         $t9, 0x30($sp)
/* 0040f744 */  nop        
/* 0040f748 */  beqz       $t9, 0x40f754
/* 0040f74c */  nop        
/* 0040f750 */  sb         $a0, ($a3)
/* 0040f754 */  addiu      $a2, $a2, -1
/* 0040f758 */  blez       $a2, 0x40f830
/* 0040f75c */  addiu      $a3, $a3, 1
/* 0040f760 */  lw         $t2, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f764 */  addiu      $at, $zero, 0x64
/* 0040f768 */  addiu      $t3, $t2, 1
/* 0040f76c */  sw         $t3, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f770 */  lbu        $t4, 0xd($s0)
/* 0040f774 */  lw         $v1, ($s0)
/* 0040f778 */  bne        $t4, $at, 0x40f794
/* 0040f77c */  addiu      $v0, $v1, -1
/* 0040f780 */  bnez       $v1, 0x40f794
/* 0040f784 */  addiu      $v0, $v1, -1
/* 0040f788 */  b          0x40f7e0
/* 0040f78c */  move       $a0, $t1
/* 0040f790 */  addiu      $v0, $v1, -1
/* 0040f794 */  bgez       $v0, 0x40f7c8
/* 0040f798 */  sw         $v0, ($s0)
/* 0040f79c */  sw         $a2, 0x38($sp)
/* 0040f7a0 */  sw         $a3, 0x28($sp)
/* 0040f7a4 */  move       $a0, $s0
/* 0040f7a8 */  jal        0xf8010e0                                # strcpy
/* 0040f7ac */  sw         $t0, 0x34($sp)
/* 0040f7b0 */  lw         $a2, 0x38($sp)
/* 0040f7b4 */  lw         $a3, 0x28($sp)
/* 0040f7b8 */  lw         $t0, 0x34($sp)
/* 0040f7bc */  addiu      $t1, $zero, -1
/* 0040f7c0 */  b          0x40f7dc
/* 0040f7c4 */  move       $v1, $v0
/* 0040f7c8 */  lw         $v0, 4($s0)
/* 0040f7cc */  nop        
/* 0040f7d0 */  lbu        $v1, ($v0)
/* 0040f7d4 */  addiu      $t5, $v0, 1
/* 0040f7d8 */  sw         $t5, 4($s0)
/* 0040f7dc */  move       $a0, $v1
/* 0040f7e0 */  beq        $a0, $t1, 0x40f830
/* 0040f7e4 */  addiu      $at, $zero, 0x73
/* 0040f7e8 */  bne        $t0, $at, 0x40f80c
/* 0040f7ec */  addiu      $at, $zero, 0x5b
/* 0040f7f0 */  lui        $t6, 0x1000
/* 0040f7f4 */  addu       $t6, $t6, $a0
/* 0040f7f8 */  lbu        $t6, 0x32e1($t6)
/* 0040f7fc */  nop        
/* 0040f800 */  andi       $t7, $t6, 8
/* 0040f804 */  bnez       $t7, 0x40f830
/* 0040f808 */  addiu      $at, $zero, 0x5b
/* 0040f80c */  bne        $t0, $at, 0x40f744
/* 0040f810 */  lw         $t9, 0x30($sp)
/* 0040f814 */  lw         $t8, 0x3c($sp)
/* 0040f818 */  nop        
/* 0040f81c */  addu       $t9, $t8, $a0
/* 0040f820 */  lbu        $t2, ($t9)
/* 0040f824 */  nop        
/* 0040f828 */  beqz       $t2, 0x40f744
/* 0040f82c */  lw         $t9, 0x30($sp)
/* 0040f830 */  bne        $a0, $t1, 0x40f850
/* 0040f834 */  nop        
/* 0040f838 */  lw         $t4, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f83c */  addiu      $t3, $zero, 1
/* 0040f840 */  addiu      $t5, $t4, -1
/* 0040f844 */  sw         $t3, -0x7a9c($gp)                        # .sbss @ 0x100042d4
/* 0040f848 */  b          0x40f890
/* 0040f84c */  sw         $t5, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f850 */  blez       $a2, 0x40f894
/* 0040f854 */  lw         $t9, 0x24($sp)
/* 0040f858 */  lw         $t6, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f85c */  sw         $a3, 0x28($sp)
/* 0040f860 */  addiu      $t7, $t6, -1
/* 0040f864 */  sw         $t7, -0x7aa0($gp)                        # .sbss @ 0x100042d0
/* 0040f868 */  move       $a1, $s0
/* 0040f86c */  jal        0xf801378                                # sleep
/* 0040f870 */  sw         $t0, 0x34($sp)
/* 0040f874 */  lw         $a3, 0x28($sp)
/* 0040f878 */  lw         $t0, 0x34($sp)
/* 0040f87c */  addiu      $t1, $zero, -1
/* 0040f880 */  bne        $v0, $t1, 0x40f894
/* 0040f884 */  lw         $t9, 0x24($sp)
/* 0040f888 */  addiu      $t8, $zero, 1
/* 0040f88c */  sw         $t8, -0x7a9c($gp)                        # .sbss @ 0x100042d4
/* 0040f890 */  lw         $t9, 0x24($sp)
/* 0040f894 */  nop        
/* 0040f898 */  bne        $a3, $t9, 0x40f8ac
/* 0040f89c */  lw         $t2, 0x30($sp)
/* 0040f8a0 */  b          0x40f8c8
/* 0040f8a4 */  move       $v0, $zero
/* 0040f8a8 */  lw         $t2, 0x30($sp)
/* 0040f8ac */  nop        
/* 0040f8b0 */  beqz       $t2, 0x40f8c4
/* 0040f8b4 */  addiu      $at, $zero, 0x63
/* 0040f8b8 */  beq        $t0, $at, 0x40f8c8
/* 0040f8bc */  addiu      $v0, $zero, 1
/* 0040f8c0 */  sb         $zero, ($a3)
/* 0040f8c4 */  addiu      $v0, $zero, 1
/* 0040f8c8 */  lw         $ra, 0x1c($sp)
/* 0040f8cc */  lw         $s0, 0x18($sp)
/* 0040f8d0 */  jr         $ra
/* 0040f8d4 */  addiu      $sp, $sp, 0x30
/* 0040f8d8 */  addiu      $sp, $sp, -0x30
/* 0040f8dc */  sw         $s0, 0x18($sp)
/* 0040f8e0 */  move       $s0, $a0
/* 0040f8e4 */  sw         $ra, 0x2c($sp)
/* 0040f8e8 */  sw         $s4, 0x28($sp)
/* 0040f8ec */  sw         $s2, 0x20($sp)
/* 0040f8f0 */  sw         $s3, 0x24($sp)
/* 0040f8f4 */  sw         $s1, 0x1c($sp)
/* 0040f8f8 */  lbu        $t6, ($s0)
/* 0040f8fc */  addiu      $at, $zero, 0x5e
/* 0040f900 */  move       $s3, $a1
/* 0040f904 */  bne        $t6, $at, 0x40f914
/* 0040f908 */  move       $s2, $zero
/* 0040f90c */  addiu      $s2, $zero, 1
/* 0040f910 */  addiu      $s0, $s0, 1
/* 0040f914 */  move       $a0, $s3
/* 0040f918 */  sltiu      $a1, $s2, 1
/* 0040f91c */  jal        0xf801238                                # calloc
/* 0040f920 */  addiu      $a2, $zero, 0x100
/* 0040f924 */  lbu        $a0, ($s0)
/* 0040f928 */  addiu      $s1, $zero, 0x5d
/* 0040f92c */  bne        $a0, $s1, 0x40f940
/* 0040f930 */  addiu      $s4, $zero, 0x2d
/* 0040f934 */  b          0x40f948
/* 0040f938 */  addiu      $s4, $zero, 0x2d
/* 0040f93c */  addiu      $s4, $zero, 0x2d
/* 0040f940 */  bne        $a0, $s4, 0x40f958
/* 0040f944 */  nop        
/* 0040f948 */  addu       $t7, $s3, $a0
/* 0040f94c */  sb         $s2, ($t7)
/* 0040f950 */  lbu        $a0, 1($s0)
/* 0040f954 */  addiu      $s0, $s0, 1
/* 0040f958 */  beq        $a0, $s1, 0x40f9d0
/* 0040f95c */  addiu      $s0, $s0, 1
/* 0040f960 */  bnez       $a0, 0x40f970
/* 0040f964 */  nop        
/* 0040f968 */  b          0x40f9d4
/* 0040f96c */  move       $v0, $zero
/* 0040f970 */  bne        $a0, $s4, 0x40f9bc
/* 0040f974 */  addu       $t8, $s3, $a0
/* 0040f978 */  lbu        $v1, ($s0)
/* 0040f97c */  nop        
/* 0040f980 */  beq        $v1, $s1, 0x40f9bc
/* 0040f984 */  addu       $t8, $s3, $a0
/* 0040f988 */  lbu        $v0, -2($s0)
/* 0040f98c */  nop        
/* 0040f990 */  slt        $at, $v0, $v1
/* 0040f994 */  beqz       $at, 0x40f9bc
/* 0040f998 */  addu       $t8, $s3, $a0
/* 0040f99c */  subu       $a2, $v1, $v0
/* 0040f9a0 */  addiu      $a2, $a2, 1
/* 0040f9a4 */  addu       $a0, $s3, $v0
/* 0040f9a8 */  jal        0xf801238                                # calloc
/* 0040f9ac */  move       $a1, $s2
/* 0040f9b0 */  b          0x40f9c0
/* 0040f9b4 */  addiu      $s0, $s0, 1
/* 0040f9b8 */  addu       $t8, $s3, $a0
/* 0040f9bc */  sb         $s2, ($t8)
/* 0040f9c0 */  lbu        $a0, ($s0)
/* 0040f9c4 */  addiu      $s0, $s0, 1
/* 0040f9c8 */  bne        $a0, $s1, 0x40f960
/* 0040f9cc */  nop        
/* 0040f9d0 */  move       $v0, $s0
/* 0040f9d4 */  lw         $ra, 0x2c($sp)
/* 0040f9d8 */  lw         $s0, 0x18($sp)
/* 0040f9dc */  lw         $s1, 0x1c($sp)
/* 0040f9e0 */  lw         $s2, 0x20($sp)
/* 0040f9e4 */  lw         $s3, 0x24($sp)
/* 0040f9e8 */  lw         $s4, 0x28($sp)
/* 0040f9ec */  jr         $ra
/* 0040f9f0 */  addiu      $sp, $sp, 0x30
/* 0040f9f4 */  nop        
/* 0040f9f8 */  nop        
/* 0040f9fc */  nop        
/* 0040fa00 */  lui        $at, 0x1000
/* 0040fa04 */  sw         $v0, 0x42ec($at)
/* 0040fa08 */  jr         $ra
/* 0040fa0c */  addiu      $v0, $zero, -1
/* 0040fa10 */  addiu      $v0, $zero, 0x40d
/* 0040fa14 */  syscall    
/* 0040fa18 */  beqz       $a3, 0x40fa28
/* 0040fa1c */  nop        
/* 0040fa20 */  j          0x40fa00
/* 0040fa24 */  nop        
/* 0040fa28 */  jr         $ra
/* 0040fa2c */  move       $v0, $zero
/* 0040fa30 */  addiu      $sp, $sp, -0x18
/* 0040fa34 */  jalr       $a3
/* 0040fa38 */  sw         $a2, 0x10($sp)
/* 0040fa3c */  lw         $a0, 0x10($sp)
/* 0040fa40 */  addiu      $v0, $zero, 0x440
/* 0040fa44 */  syscall    
/* 0040fa48 */  nop        
/* 0040fa4c */  nop        
/* 0040fa50 */  addiu      $v0, $zero, 0x3f5
/* 0040fa54 */  syscall    
/* 0040fa58 */  beqz       $a3, 0x40fa68
/* 0040fa5c */  nop        
/* 0040fa60 */  j          0x40fa00
/* 0040fa64 */  nop        
/* 0040fa68 */  beqz       $a0, 0x40fa74
/* 0040fa6c */  nop        
/* 0040fa70 */  sw         $v0, ($a0)
/* 0040fa74 */  jr         $ra
/* 0040fa78 */  nop        
/* 0040fa7c */  nop        
/* 0040fa80 */  addiu      $v0, $zero, 0x43a
/* 0040fa84 */  syscall    
/* 0040fa88 */  beqz       $a3, 0x40fa98
/* 0040fa8c */  nop        
/* 0040fa90 */  j          0x40fa00
/* 0040fa94 */  nop        
/* 0040fa98 */  jr         $ra
/* 0040fa9c */  move       $v0, $zero
/* 0040faa0 */  addiu      $v0, $zero, 0x3e8
/* 0040faa4 */  syscall    
/* 0040faa8 */  beqz       $a3, 0x40fab8
/* 0040faac */  nop        
/* 0040fab0 */  j          0x40fa00
/* 0040fab4 */  nop        
/* 0040fab8 */  jr         $ra
/* 0040fabc */  nop        
/* 0040fac0 */  lui        $v1, 0x1000
/* 0040fac4 */  lw         $v1, 0x3d74($v1)
/* 0040fac8 */  addiu      $v0, $zero, 0x3f9
/* 0040facc */  addu       $a0, $a0, $v1
/* 0040fad0 */  syscall    
/* 0040fad4 */  bnez       $a3, 0x40fae8
/* 0040fad8 */  lui        $at, 0x1000
/* 0040fadc */  move       $v0, $v1
/* 0040fae0 */  jr         $ra
/* 0040fae4 */  sw         $a0, 0x3d74($at)
/* 0040fae8 */  j          0x40fa00
/* 0040faec */  nop        
/* 0040faf0 */  lui        $v0, 0x1000
/* 0040faf4 */  lw         $v0, 0x3d70($v0)
/* 0040faf8 */  nop        
/* 0040fafc */  sltu       $at, $a0, $v0
/* 0040fb00 */  beqz       $at, 0x40fb0c
/* 0040fb04 */  nop        
/* 0040fb08 */  move       $a0, $v0
/* 0040fb0c */  addiu      $v0, $zero, 0x3f9
/* 0040fb10 */  syscall    
/* 0040fb14 */  bnez       $a3, 0x40fae8
/* 0040fb18 */  lui        $at, 0x1000
/* 0040fb1c */  sw         $a0, 0x3d74($at)
/* 0040fb20 */  jr         $ra
/* 0040fb24 */  move       $v0, $zero
/* 0040fb28 */  nop        
/* 0040fb2c */  nop        