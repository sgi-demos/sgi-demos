Warning: missing "jr $ra" in last block of __start (initial).

? lbl_400270();                                     /* extern */
s32 lbl_4002ac(s32, s32, s32);                      /* extern */
? lbl_401504();                                     /* extern */
? lbl_401678(s32);                                  /* extern */
? lbl_401a00();                                     /* extern */
? lbl_402098();                                     /* extern */
? lbl_402fbc();                                     /* extern */
? lbl_403440();                                     /* extern */
? lbl_4034f0();                                     /* extern */
? lbl_403584(s32, s8 *);                            /* extern */
? lbl_403684();                                     /* extern */
s32 lbl_40381c(void *);                             /* extern */
s32 lbl_403960(s32);                                /* extern */
s32 lbl_4039f8(?);                                  /* extern */
void **lbl_403a78(u8 *, s32);                       /* extern */
? lbl_403b9c(void **, f32);                         /* extern */
? lbl_403bf8(u8 **);                                /* extern */
? lbl_403e28(void **);                              /* extern */
? lbl_403ffc(?);                                    /* extern */
? lbl_40406c(s32, s32);                             /* extern */
s32 lbl_40408c(u8 *, ?, u8 *, ?);                   /* extern */
s32 lbl_4040d0(u8 ***);                             /* extern */
s32 lbl_404370(u8 ***);                             /* extern */
u8 **lbl_4043bc(u8 *, u8 *, u8 *, u8 *);            /* extern */
s32 *lbl_404460(void *);                            /* extern */
s32 *lbl_4044f0(s32);                               /* extern */
? lbl_404580();                                     /* extern */
s32 lbl_404668(s32, s32);                           /* extern */
s32 lbl_404848(void *, s32);                        /* extern */
? lbl_40493c(s32, s32 *, s32 **, ?);                /* extern */
? lbl_404a4c(s32, s32 *, s32 **, ?);                /* extern */
? lbl_404b60(s32 *, s32, s32);                      /* extern */
s32 *lbl_404e78(s32, s32 *);                        /* extern */
s32 lbl_405590(s32);                                /* extern */
s32 lbl_4055d0(?);                                  /* extern */
s32 lbl_4057d4(void *);                             /* extern */
s32 lbl_405ce8(u8 *);                               /* extern */
? lbl_405dd0(void *, void *);                       /* extern */
? lbl_405de8(s8);                                   /* extern */
s8 lbl_405df8();                                    /* extern */
? lbl_405ed8(?);                                    /* extern */
s32 lbl_4067e4(s32, void *, void *, ? *);           /* extern */
s32 lbl_406d60(s32, ? *);                           /* extern */
s32 lbl_4072ac(s32, ? *);                           /* extern */
s32 lbl_4074fc(s32 *);                              /* extern */
? lbl_408200();                                     /* extern */
? lbl_4082e8(s32);                                  /* extern */
? lbl_4092d4(void *, void *, s32, void **);         /* extern */
s32 lbl_40a400();                                   /* extern */
? lbl_40a6d4(s32, void *);                          /* extern */
void **lbl_40a8e0(s32);                             /* extern */
void **lbl_40a918(s32);                             /* extern */
s32 lbl_40ade4(s32);                                /* extern */
f64 lbl_40d120(f64);                                /* extern */
f64 lbl_40d178(f64, f32, s32, s32);                 /* extern */
? lbl_40d2c0();                                     /* extern */
? lbl_40d2d0(?);                                    /* extern */
? lbl_40d3c0(s32);                                  /* extern */
s32 lbl_40d3f0(s32, s32 *, ?);                      /* extern */
? lbl_40d768(s32, void *, s32);                     /* extern */
s32 lbl_40d7a4(u8 *, void *, s8 *, void *, void *); /* extern */
s32 lbl_40d810(? *);                                /* extern */
f64 lbl_40d830(u8 *, s32 *);                        /* extern */
s32 lbl_40dcc0(u8 *, s32 *, ?);                     /* extern */

void __start(s32 arg0, ? arg1) {
    (void *)0x1000BD70->unk-7A88 = &arg1;
}

void crt_main(s32 arg0, s32 arg2) {
    s32 sp14;

    saved_reg_gp->unk-7A90 = arg2;
    sp14 = 0;
    saved_reg_gp->unk-7A8C = arg0;
    (? (*)())0x40FB3C();
    lbl_40d2c0();
    lbl_40d2d0(0);
    lbl_40d3c0(lbl_4002ac(saved_reg_gp->unk-7A8C, saved_reg_gp->unk-7A88, saved_reg_gp->unk-7A90));
    M2C_BREAK();
}

void exit_handler(void) {
    (? (*)(?, s32, s32, ?))0x0F801150(0x100036B4, saved_reg_gp - 0x7E90, saved_reg_gp - 0x7EA0, 0x100001C0);
    lbl_40d3c0(1);
}

s32 parse_args_and_init(s32 arg0, s32 *arg1) {
    s32 sp20C0;
    s32 spB8;
    s32 spB4;
    s32 spB0;
    s8 sp7C;
    s32 sp64;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 *temp_s1;
    s32 *var_s1_4;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_s0;
    s32 temp_t2_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 var_fp;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_3;
    s32 var_s2;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;
    s8 *temp_t0;
    s8 *temp_t0_2;
    s8 *temp_t1;
    s8 *temp_t1_2;
    s8 *temp_t2;
    s8 *temp_t2_3;
    s8 *temp_t2_4;
    s8 *temp_t3;
    s8 *temp_t3_2;
    s8 *temp_t3_3;
    s8 *temp_t3_4;
    s8 *temp_t3_5;
    s8 *temp_t4;
    s8 *temp_t4_2;
    s8 *temp_t5;
    s8 *temp_t6;
    s8 *temp_t7;
    s8 *temp_t8;
    s8 *temp_t9;
    s8 *temp_t9_2;
    u8 *temp_a0;
    u8 *var_s1_2;
    void *var_a2;
    void *var_s4;

    var_s0 = saved_reg_s0;
    var_s1 = saved_reg_s1;
    var_s5 = saved_reg_s5;
    var_s6 = saved_reg_s6;
    var_s7 = saved_reg_s7;
    var_fp = saved_reg_fp;
    spB8 = 0;
    spB4 = 0;
    sp20C0 = 0;
    saved_reg_gp->unk-7E98->unk48 = 0;
    saved_reg_gp->unk-7E98->unkC8 = 0;
    saved_reg_gp->unk-7E98->unkD0 = -1;
    saved_reg_gp->unk-7E98->unk38 = 0;
    saved_reg_gp->unk-7E98->unkDC = 0;
    saved_reg_gp->unk-7E98->unk104 = 0;
    saved_reg_gp->unk-7E98->unkBC = 0;
    saved_reg_gp->unk-7E98->unkC0 = (void *) (saved_reg_gp - 0x7E80);
    saved_reg_gp->unk-7E98->unk68 = 0;
    saved_reg_gp->unk-7E98->unk6C = (f32) saved_reg_gp->unk-7EE0;
    saved_reg_gp->unk-7E98->unk90 = 0;
    saved_reg_gp->unk-7E98->unk94 = 0;
    saved_reg_gp->unk-7E98->unk98 = (void *) (saved_reg_gp - 0x7E78);
    saved_reg_gp->unk-7E98->unk9C = (void *) (saved_reg_gp - 0x7E74);
    saved_reg_gp->unk-7E98->unk74 = (void *) (saved_reg_gp - 0x7E70);
    saved_reg_gp->unk-7E98->unk78 = 0;
    saved_reg_gp->unk-7E98->unkA0 = 0;
    saved_reg_gp->unk-7E98->unkB8 = 0;
    saved_reg_gp->unk-7BC0 = 0;
    var_v0 = lbl_40d3f0(arg0, arg1, 0x10000234);
    if (var_v0 == -1) {
        var_s4 = saved_reg_gp - 0x7EA0;
    } else {
        var_s4 = saved_reg_gp - 0x7EA0;
        do {
            switch (var_v0) {                       /* irregular */
            case 0x77:
                saved_reg_gp->unk-7E98->unk68 = 1;
                temp_t0 = saved_reg_gp->unk-7E98;
                temp_v0 = lbl_40d7a4(saved_reg_gp->unk-7BB4, saved_reg_gp - 0x7E6C, temp_t0, temp_t0 + 4);
                if ((temp_v0 != 1) && (temp_v0 != 2)) {
                    lbl_400270();
                }
                if (temp_v0 == 1) {
                    temp_t1 = saved_reg_gp->unk-7E98;
                    temp_t1->unk4 = (s32) temp_t1->unk0;
                }
                temp_t3 = saved_reg_gp->unk-7E98;
                (? (*)(?, ?, s32, s32))0x0F801150(0x100036B4, 0x100002B8, temp_t3->unk0, temp_t3->unk4);
                temp_t4 = saved_reg_gp->unk-7E98;
                temp_t4->unk6C = (f32) ((f64) (f32) temp_t4->unk0 / (f64) temp_t4->unk4);
                break;
            case 0x6F:
                saved_reg_gp->unk-7E98->unk74 = (void *(*)(u8 *))0x0F801300(saved_reg_gp->unk-7BB4);
                break;
            case 0x73:
                saved_reg_gp->unk-7E98->unk78 = 1;
                if (lbl_40d7a4(saved_reg_gp->unk-7BB4, saved_reg_gp - 0x7E64, saved_reg_gp->unk-7E98 + 0x7C) != 1) {
                    lbl_400270();
                }
                (? (*)(?, ?, ?, f64))0x0F801150(0x100036B4, 0x100002D4, second half of f64, (f64) saved_reg_gp->unk-7E98->unk7C);
                break;
            case 0x74:
                saved_reg_gp->unk-7E98->unk80 = 1;
                temp_t2 = saved_reg_gp->unk-7E98;
                if (lbl_40d7a4(saved_reg_gp->unk-7BB4, (void *)0x100002E8, temp_t2 + 0x84, temp_t2 + 0x88, temp_t2 + 0x8C) != 3) {
                    lbl_400270();
                }
                temp_t3_2 = saved_reg_gp->unk-7E98;
                (? (*)(?, ?, ?, f64, f64, f64))0x0F801150(0x100036B4, 0x100002F4, second half of f64, (f64) temp_t3_2->unk84, (f64) temp_t3_2->unk88, (f64) temp_t3_2->unk8C);
                break;
            case 0x57:
                spB4 = 1;
                if (spB8 != 0) {
                    lbl_400270();
                }
                spB0 = (s32 (*)(u8 *))0x0F801300(saved_reg_gp->unk-7BB4);
                break;
            case 0x52:
                spB8 = 1;
                if (spB4 != 0) {
                    lbl_400270();
                }
                spB0 = (s32 (*)(u8 *))0x0F801300(saved_reg_gp->unk-7BB4);
                break;
            case 0x4C:
                (? (*)(?))0x0F801250(0x10000310);
                saved_reg_gp->unk-7E98->unkB8 = 1;
                break;
            case 0x6E:
                sp20C0 = 1;
                break;
            case 0x46:
                if (lbl_40d7a4(saved_reg_gp->unk-7BB4, saved_reg_gp - 0x7E60, saved_reg_gp->unk-7E98 + 0x104) != 1) {
                    lbl_400270();
                }
                (? (*)(?, s32))0x0F801250(0x10000330, saved_reg_gp->unk-7E98->unk104);
                break;
            case 0x66:
                saved_reg_gp->unk-7E98->unk48 = 1;
                break;
            case 0x6C:
                saved_reg_gp->unk-7E98->unkC8 = 1;
                saved_reg_gp->unk-7E98->unkD4 = 0;
                temp_t3_3 = saved_reg_gp->unk-7E98;
                if (lbl_40d7a4(saved_reg_gp->unk-7BB4, saved_reg_gp - 0x7E5C, temp_t3_3 + 0xCC, temp_t3_3 + 0xD0) != 2) {
                    lbl_400270();
                }
                if (saved_reg_gp->unk-7E98->unkD0 == 0) {
                    var_a2 = saved_reg_gp - 0x7E54;
                } else {
                    var_a2 = saved_reg_gp - 0x7E4C;
                }
                (? (*)(?, void *, void *))0x0F801250(0x10000350, var_s4, var_a2);
                break;
            case 0x6D:
                saved_reg_gp->unk-7E98->unkBC = 1;
                lbl_4034f0();
                temp_a0 = saved_reg_gp->unk-7BB4;
                sp7C = 0;
                var_s1_2 = temp_a0;
                if (lbl_40d7a4(temp_a0, (void *)0x10000374, &sp7C) == 1) {
                    do {
                        temp_v0_2 = (s32 (*)(s8 *, void *))0x0F801130(&sp7C, saved_reg_gp - 0x7E44);
                        if (temp_v0_2 != 0) {
                            (? (*)(?, ?, void *, s8 *))0x0F801150(0x100036B4, 0x10000380, var_s4, &sp7C);
                            lbl_403584(temp_v0_2, &sp7C);
                        } else {
                            (? (*)(?, ?, void *, s8 *))0x0F801150(0x100036B4, 0x100003A0, var_s4, &sp7C);
                            lbl_400270();
                        }
                        var_s1_2 = &var_s1_2[(s32 (*)(s8 *))0x0F801308(&sp7C)];
                        if (*var_s1_2 == 0x2C) {
                            var_s1_2 += 1;
                        }
                        sp7C = 0;
                    } while (lbl_40d7a4(var_s1_2, (void *)0x100003C0, &sp7C) == 1);
                }
                break;
            case 0x4D:
                saved_reg_gp->unk-7E98->unkC0 = (void *(*)(u8 *))0x0F801300(saved_reg_gp->unk-7BB4);
                break;
            case 0x50:
                saved_reg_gp->unk-7E94 = 1;
                break;
            case 0x56:
                if (saved_reg_gp->unk-7E98->unk94 != 0) {
                    lbl_400270();
                }
                saved_reg_gp->unk-7E98->unk90 = 1;
                saved_reg_gp->unk-7E98->unk98 = (void *(*)(u8 *))0x0F801300(saved_reg_gp->unk-7BB4);
                break;
            case 0x76:
                if (saved_reg_gp->unk-7E98->unk90 != 0) {
                    lbl_400270();
                }
                saved_reg_gp->unk-7E98->unk94 = 1;
                saved_reg_gp->unk-7E98->unk98 = (void *(*)(u8 *))0x0F801300(saved_reg_gp->unk-7BB4);
                break;
            case 0x69:
                saved_reg_gp->unk-7E98->unk9C = (void *(*)(u8 *))0x0F801300(saved_reg_gp->unk-7BB4);
                break;
            default:
                lbl_400270();
                break;
            }
            var_v0 = lbl_40d3f0(arg0, arg1, 0x10000234);
        } while (var_v0 != -1);
        var_s0 = sp4C;
        var_s1 = sp48;
        var_s5 = sp44;
        var_s6 = sp40;
        var_s7 = sp3C;
        var_fp = sp38;
    }
    if (spB8 == 0) {
        if ((spB4 != 0) && (saved_reg_gp->unk-7E98->unk104 == 0)) {
            (? (*)(?, ?, void *))0x0F801150(0x100036B4, 0x100003CC, var_s4);
            lbl_40d3c0(-1);
        }
        saved_reg_gp->unk-7E98->unk108 = (s32 (*)(?))0x0F801208(0x1E8480);
        if (saved_reg_gp->unk-7E98->unk108 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E40);
        }
        saved_reg_gp->unk-7E98->unk10C = (s32 (*)(?))0x0F801208(0xC);
        if (saved_reg_gp->unk-7E98->unk10C == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E38);
        }
        saved_reg_gp->unk-7E98->unk114 = (s32 (*)(?))0x0F801208(0x493E0);
        if (saved_reg_gp->unk-7E98->unk114 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E30);
        }
        saved_reg_gp->unk-7E98->unk110 = (s32 (*)(?))0x0F801208(0x493E00);
        if (saved_reg_gp->unk-7E98->unk110 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E28);
        }
        saved_reg_gp->unk-7E98->unk124 = (s32 (*)(?))0x0F801208(0xE10);
        if (saved_reg_gp->unk-7E98->unk124 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E20);
        }
        saved_reg_gp->unk-7E98->unk118 = (s32 (*)(?))0x0F801208(0x140);
        if (saved_reg_gp->unk-7E98->unk118 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E18);
        }
        saved_reg_gp->unk-7E98->unk11C = (s32 (*)(?))0x0F801208(0xF0);
        if (saved_reg_gp->unk-7E98->unk11C == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E10);
        }
        saved_reg_gp->unk-7E98->unk120 = (s32 (*)(?))0x0F801208(0xF0);
        if (saved_reg_gp->unk-7E98->unk120 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E08);
        }
        saved_reg_gp->unk-7E98->unk128 = (s32 (*)(?))0x0F801208(0x30D400);
        if (saved_reg_gp->unk-7E98->unk128 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7E00);
        }
        saved_reg_gp->unk-7E98->unk12C = (s32 (*)(?))0x0F801208(0x186A00);
        if (saved_reg_gp->unk-7E98->unk12C == 0) {
            lbl_4092d4(saved_reg_gp - 0x7DF8);
        }
        saved_reg_gp->unk-7E98->unk130 = (s32 (*)(?))0x0F801208(0xFA00);
        if (saved_reg_gp->unk-7E98->unk130 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7DF0);
        }
        saved_reg_gp->unk-7E98->unk138 = (s32 (*)(?))0x0F801208(0x190);
        if (saved_reg_gp->unk-7E98->unk138 == 0) {
            lbl_4092d4(saved_reg_gp - 0x7DE8);
        }
        saved_reg_gp->unk-7E98->unk13C = (s32 *(*)(?))0x0F801208(0x320);
        if (saved_reg_gp->unk-7E98->unk13C == NULL) {
            lbl_4092d4(saved_reg_gp - 0x7DE0);
        }
        if (saved_reg_gp->unk-7E98->unk104 != 0) {
            saved_reg_gp->unk-7E98->unkF0 = (s32 *(*)(?))0x0F801208(0x320);
            if (saved_reg_gp->unk-7E98->unkF0 == NULL) {
                lbl_4092d4(saved_reg_gp - 0x7DD8);
            }
            lbl_404580();
        }
        saved_reg_gp->unk-7E98->unk140 = 0;
        saved_reg_gp->unk-7E98->unk144 = 0;
        saved_reg_gp->unk-7E98->unk148 = 0;
        saved_reg_gp->unk-7E98->unk14C = 0;
        saved_reg_gp->unk-7E98->unk15C = 0;
        saved_reg_gp->unk-7E98->unk150 = 0;
        saved_reg_gp->unk-7E98->unk154 = 0;
        saved_reg_gp->unk-7E98->unk158 = 0;
        saved_reg_gp->unk-7E98->unk160 = 0;
        saved_reg_gp->unk-7E98->unk164 = 0;
        saved_reg_gp->unk-7E98->unk168 = 0;
        saved_reg_gp->unk-7E98->unk170 = 0;
        saved_reg_gp->unk-7E98->unk174 = 0;
        saved_reg_gp->unk-7E98->unk178 = 0;
        saved_reg_gp->unk-7E98->unk17C = 0;
        saved_reg_gp->unk-7E98->unk180 = 0;
        saved_reg_gp->unk-7E98->unk184 = 0;
        saved_reg_gp->unk-7E98->unk188 = 0;
        saved_reg_gp->unk-7E98->unk18C = 0;
        saved_reg_gp->unk-7E98->unk190 = 0;
        saved_reg_gp->unk-7E98->unk194 = 0;
        temp_v0_3 = arg0 - saved_reg_gp->unk-7BBC;
        if (temp_v0_3 == 0) {
            (? (*)(?, ?, void *))0x0F801150(0x100036B4, 0x1000040C, var_s4);
            if (lbl_405590(0x10003694) == 0) {
                lbl_40d3c0(-1);
            }
        } else if (temp_v0_3 > 0) {
            saved_reg_gp->unk-7E98->unkD4 = temp_v0_3;
            if (saved_reg_gp->unk-7BBC < arg0) {
                sp40 = var_s6;
                sp3C = var_s7;
                sp38 = var_fp;
                sp44 = var_s5;
                sp4C = var_s0;
                sp48 = var_s1;
loop_133:
                temp_t2_2 = saved_reg_gp->unk-7BBC;
                temp_s0 = arg1[temp_t2_2];
                saved_reg_gp->unk-7BBC = (s32) (temp_t2_2 + 1);
                temp_v0_4 = (s32 (*)(s32, void *))0x0F801130(temp_s0, saved_reg_gp - 0x7DD0);
                if (temp_v0_4 == 0) {
                    if (saved_reg_gp->unk-7E98->unkD4 >= 2) {
                        (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x1000042C, var_s4, temp_s0);
                    } else {
                        lbl_4092d4((void *)0x10000450, var_s4, temp_s0);
                    }
                } else {
                    (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x1000046C, var_s4, temp_s0);
                    if (lbl_405590(temp_v0_4) == 0) {
                        lbl_40d3c0(-1);
                    }
                    (? (*)(s32))0x0F801120(temp_v0_4);
                }
                temp_t7 = saved_reg_gp->unk-7E98;
                if (temp_t7->unkC8 != 0) {
                    temp_t7->unk178 = (s32) temp_t7->unk140;
                    temp_t0_2 = saved_reg_gp->unk-7E98;
                    temp_t0_2->unk17C = (s32) temp_t0_2->unk148;
                    temp_t3_4 = saved_reg_gp->unk-7E98;
                    temp_t3_4->unk180 = (s32) temp_t3_4->unk14C;
                    temp_t5 = saved_reg_gp->unk-7E98;
                    temp_t5->unk184 = (s32) temp_t5->unk15C;
                    temp_t4_2 = saved_reg_gp->unk-7E98;
                    temp_t4_2->unk188 = (s32) temp_t4_2->unk160;
                    temp_t9 = saved_reg_gp->unk-7E98;
                    temp_t9->unk18C = (s32) temp_t9->unk164;
                    temp_t1_2 = saved_reg_gp->unk-7E98;
                    temp_t1_2->unk190 = (s32) temp_t1_2->unk168;
                    temp_t2_3 = saved_reg_gp->unk-7E98;
                    temp_t2_3->unk194 = (s32) temp_t2_3->unk170;
                }
                var_s0 = sp4C;
                if (saved_reg_gp->unk-7BBC < arg0) {
                    goto loop_133;
                }
                var_s1 = sp48;
            }
        } else {
            lbl_400270();
        }
        temp_a2 = saved_reg_gp->unk-7E98->unk160;
        if (temp_a2 > 0) {
            (? (*)(?, void *, s32))0x0F801250(0x10000484, var_s4, temp_a2);
        }
        temp_a2_2 = saved_reg_gp->unk-7E98->unk164;
        if (temp_a2_2 > 0) {
            (? (*)(?, void *, s32))0x0F801250(0x100004A4, var_s4, temp_a2_2);
        }
        temp_a2_3 = saved_reg_gp->unk-7E98->unk168;
        if (temp_a2_3 > 0) {
            (? (*)(?, void *, s32))0x0F801250(0x100004C0, var_s4, temp_a2_3);
        }
        (? (*)(?, void *, s32))0x0F801250(0x100004E0, var_s4, saved_reg_gp->unk-7E98->unk174);
    }
    if (spB8 != 0) {
        sp4C = var_s0;
        sp48 = var_s1;
        (? (*)(?, ?))0x0F801150(0x100036B4, 0x10000500);
        temp_v0_5 = (s32 (*)(s32, void *))0x0F801130(spB0, saved_reg_gp - 0x7DCC);
        if (temp_v0_5 == 0) {
            (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x1000051C, var_s4, spB0);
            lbl_40d3c0(-1);
        }
        temp_s1 = lbl_404e78(temp_v0_5, &sp64);
        (? (*)(?, void *))0x0F801150(0x100036B4, saved_reg_gp - 0x7DC8);
        (? (*)(s32))0x0F801120(temp_v0_5);
        if (temp_s1 == NULL) {
            (? (*)(?, ?, void *))0x0F801150(0x100036B4, 0x1000053C, var_s4);
            lbl_40d3c0(-1);
        }
        saved_reg_gp->unk-7E98->unk13C = temp_s1;
        saved_reg_gp->unk-7E98->unkD4 = sp64;
        temp_t6 = saved_reg_gp->unk-7E98;
        var_s0 = sp4C;
        if (temp_t6->unkC8 == 0) {
            temp_t6->unk174 = 1;
            var_s0 = sp4C;
        }
        var_s1 = sp48;
    }
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_a1 = temp_t8->unk104;
    if (temp_a1 != 0) {
        if (temp_t8->unkC8 != 0) {
            sp48 = var_s1;
            var_s1_3 = 0;
            if (temp_t8->unkD4 > 0) {
                sp4C = var_s0;
                var_s0_2 = 0;
                do {
                    temp_t9_2 = saved_reg_gp->unk-7E98;
                    var_s1_3 += 1;
                    *(saved_reg_gp->unk-7E98->unkF0 + var_s0_2) = lbl_404668(*(temp_t9_2->unk13C + var_s0_2), temp_t9_2->unk104);
                    var_s0_2 += 4;
                } while (var_s1_3 < saved_reg_gp->unk-7E98->unkD4);
                var_s0 = sp4C;
            }
            var_s1 = sp48;
        } else {
            *saved_reg_gp->unk-7E98->unkF0 = lbl_404668(*saved_reg_gp->unk-7E98->unk13C, temp_a1);
        }
    }
    if (spB4 != 0) {
        temp_t3_5 = saved_reg_gp->unk-7E98;
        sp4C = var_s0;
        sp48 = var_s1;
        var_s2 = 1;
        if (temp_t3_5->unkC8 != 0) {
            var_s2 = temp_t3_5->unkD4;
        }
        if (temp_t3_5->unk104 != 0) {
            var_s1_4 = saved_reg_gp->unk-7E98->unkF0;
        } else {
            var_s1_4 = saved_reg_gp->unk-7E98->unk13C;
        }
        (? (*)(?, ?))0x0F801150(0x100036B4, 0x1000055C);
        temp_v0_6 = (s32 (*)(s32, void *))0x0F801130(spB0, saved_reg_gp - 0x7DC0);
        if (temp_v0_6 == 0) {
            (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x10000578, var_s4, spB0);
            lbl_40d3c0(-1);
        }
        lbl_404b60(var_s1_4, var_s2, temp_v0_6);
        (? (*)(s32))0x0F801120(temp_v0_6);
        (? (*)(?, void *))0x0F801150(0x100036B4, saved_reg_gp - 0x7DBC);
    }
    if (sp20C0 != 0) {

    } else {
        lbl_401678(*arg1);
        lbl_408200();
        if (saved_reg_gp->unk-7E98->unkBC != 0) {
            lbl_403684();
            saved_reg_gp->unk-7E98->unkC4 = lbl_40381c(saved_reg_gp->unk-7E98->unkC0);
            temp_t2_4 = saved_reg_gp->unk-7E98;
            if (temp_t2_4->unkC4 == 0) {
                (? (*)(?, ?, void *, void *))0x0F801150(0x100036B4, 0x10000598, var_s4, temp_t2_4->unkC0);
                lbl_40d3c0(-1);
            }
            (? (*)(?, ?, void *))0x0F801150(0x100036B4, 0x100005B8, saved_reg_gp->unk-7E98->unkC0);
        } else {
            lbl_403440();
        }
        lbl_402098();
        lbl_401a00();
    }
    return 0;
}

void draw_display_list(void) {
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;
    void *temp_t2;
    void *temp_t4;
    void *temp_t4_2;
    void *temp_t6;
    void *temp_t8;

    temp_t6 = saved_reg_gp->unk-7E98;
    var_v0 = temp_t6->unkC8;
    if ((var_v0 == 0) && (temp_t6->unk104 == 0)) {
        var_s1 = 0;
        if (temp_t6->unk174 > 0) {
            var_s0 = 0;
            do {
                lbl_4082e8(*(saved_reg_gp->unk-7E98->unk13C + var_s0));
                temp_t2 = saved_reg_gp->unk-7E98;
                var_s1 += 1;
                var_s0 += 4;
            } while (var_s1 < temp_t2->unk174);
            var_v0 = temp_t2->unkC8;
        }
    }
    if (var_v0 == 0) {
        temp_t4 = saved_reg_gp->unk-7E98;
        if (temp_t4->unk104 != 0) {
            lbl_4082e8(*temp_t4->unkF0);
            var_v0 = saved_reg_gp->unk-7E98->unkC8;
        }
    }
    if (var_v0 != 0) {
        temp_t8 = saved_reg_gp->unk-7E98;
        if (temp_t8->unk104 == 0) {
            lbl_4082e8(*(temp_t8->unk13C + (temp_t8->unkD8 * 4)));
            var_v0 = saved_reg_gp->unk-7E98->unkC8;
        }
    }
    if (var_v0 != 0) {
        temp_t4_2 = saved_reg_gp->unk-7E98;
        if (temp_t4_2->unk104 != 0) {
            lbl_4082e8(*(temp_t4_2->unkF0 + (temp_t4_2->unkD8 * 4)));
        }
    }
}

void draw_entity(s32 arg0) {
    f32 temp_f0;
    s32 temp_v0;
    s32 var_a0;
    void *temp_t4;
    void *temp_v1;
    void *temp_v1_2;

    temp_f0 = saved_reg_gp->unk-7EDC;
    saved_reg_gp->unk-7E98->unk24 = 0.0f;
    saved_reg_gp->unk-7E98->unk28 = 0.0f;
    saved_reg_gp->unk-7E98->unk30 = (f32) saved_reg_gp->unk-7EE0;
    saved_reg_gp->unk-7E98->unk10 = temp_f0;
    saved_reg_gp->unk-7E98->unk14 = temp_f0;
    saved_reg_gp->unk-7E98->unk18 = 0;
    saved_reg_gp->unk-7E98->unk1C = 0;
    saved_reg_gp->unk-7E98->unk2C = 0;
    temp_t4 = saved_reg_gp->unk-7E98;
    if (temp_t4->unk68 != 0) {
        (? (*)(s32, s32))0x0F401400(temp_t4->unk0, temp_t4->unk4);
    }
    temp_v0 = (s32 (*)(s32, ?))0x0F801330(arg0, 0x2F);
    var_a0 = arg0;
    if (temp_v0 != 0) {
        var_a0 = temp_v0 + 1;
    }
    (? (*)(s32))0x0F401458(var_a0);
    temp_v1 = saved_reg_gp->unk-7E98;
    (? (*)(void *, void *))0x0F401440(temp_v1 + 8, temp_v1 + 0xC);
    temp_v1_2 = saved_reg_gp->unk-7E98;
    (? (*)(void *, void *))0x0F401438(temp_v1_2, temp_v1_2 + 4);
    (? (*)())0x0F401220();
    (? (*)())0x0F401070();
    (? (*)())0x0F401098();
    if ((s32 (*)())0x0F401128() < 0xC) {
        if ((s32 (*)(?))0x0F4016B0(6) != 3) {
            (? (*)(?, ?, s32))0x0F801150(0x100036B4, 0x100005CC, arg0);
            (? (*)())0x0F401290();
            lbl_40d3c0(1);
        } else {
            saved_reg_gp->unk-7E88 = 1;
        }
    }
    (? (*)(?))0x0F402098(0);
    (? (*)())0x0F402120();
    (? (*)())0x0F402288();
    (? (*)(?))0x0F402098(0);
    (? (*)())0x0F402120();
    (? (*)(?))0x0F402508(1);
    (? (*)(?, ?))0x0F402EE8(0x7FFFFF, 0x2000);
    (? (*)(?))0x0F401618(6);
    (? (*)())0x0F402518();
    (? (*)(?))0x0F401588(2);
    (? (*)())0x0F401098();
    (? (*)(?))0x0F401570(0x40);
    (? (*)(?, ?, ?, ?))0x0F4011A8(0, 0, 0, 0);
    (? (*)(?, ?, ?, ?))0x0F4011A8(1, 0, 0xFF, 0xFF);
    (? (*)(?))0x0F401FE0(0);
    (? (*)())0x0F402120();
    (? (*)(?))0x0F401570(0x10);
    (? (*)(?))0x0F4012F0(0x67);
    (? (*)(?))0x0F4012F0(0x66);
    (? (*)(?))0x0F4012F0(0x65);
    (? (*)(?))0x0F4012F0(7);
    (? (*)(?))0x0F4012F0(0x53);
    (? (*)(?))0x0F4012F0(0x21C);
    (? (*)(?))0x0F4012F0(0x19);
    if (saved_reg_gp->unk-7E98->unk90 != 0) {
        (? (*)(?))0x0F4012F0(0x1D);
    }
    (? (*)(?))0x0F4012F0(0x28);
    if (saved_reg_gp->unk-7E98->unkC8 != 0) {
        (? (*)(?))0x0F4012F0(6);
    }
    if (saved_reg_gp->unk-7E98->unk48 != 0) {
        (? (*)(?))0x0F4012F0(0xB);
        (? (*)(?))0x0F4012F0(0xC);
        (? (*)(?))0x0F4012F0(0xA);
        (? (*)(?))0x0F4012F0(0x10);
        (? (*)(?))0x0F4012F0(0x15);
        (? (*)(?))0x0F4012F0(0x20);
        (? (*)(?))0x0F4012F0(0x14);
    }
    saved_reg_gp->unk-7E98->unk64 = (s32 (*)(?))0x0F4015A8(0x10000254);
    (? (*)(?))0x0F402578(1);
    (? (*)(s32, s32, ?, ?))0x0F402FA0((s32) saved_reg_gp->unk-7FF0, saved_reg_gp->unk-7E98->unk6C, 0x3E800000, 0x41700000);
    (? (*)(?))0x0F402578(2);
    (? (*)(?))0x0F402190(0x10000278);
    if (saved_reg_gp->unk-7E98->unk48 == 0) {
        (? (*)(?, ?, ?))0x0F402298(0, 0, 0xC0800000);
    }
}

void frame_advance_check(void) {
    (? (*)(s32))0x0F401508(saved_reg_gp->unk-7E98->unk64);
}

void save_frame(s32 arg0) {
    ? sp28;
    s32 sp24;
    f64 sp1C;                                       /* compiler-managed */
    f32 temp_f2;
    f32 var_f12;
    f64 temp_f0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    if (arg0 == 0) {
        saved_reg_gp->unk-7B70 = lbl_40d810(&sp28);
    } else if ((arg0 % 100) == 0) {
        temp_v0 = lbl_40d810(&sp28);
        temp_f2 = saved_reg_gp->unk-7FE4;
        sp24 = temp_v0;
        temp_f0 = (f64) (temp_v0 - saved_reg_gp->unk-7B70) / (bitwise f64) temp_f2;
        sp1C = temp_f0;
        (? (*)(f64, ?, ?, f64))0x0F801250(temp_f0, 0x100005EC, second half of f64, (bitwise f64) temp_f2 / temp_f0);
        temp_v0_2 = saved_reg_gp->unk-7E98->unk160;
        var_f12 = unksp20;
        if (temp_v0_2 != 0) {
            sp1C = (bitwise f32) sp1C;
            (? (*)(f32, ?, ?, f64))0x0F801250(var_f12, 0x10000600, second half of f64, (f64) (temp_v0_2 * 0x64) / (bitwise f64) var_f12);
            var_f12 = (f32) (f64) sp1C;
        }
        temp_v0_3 = saved_reg_gp->unk-7E98->unk164;
        if (temp_v0_3 != 0) {
            (? (*)(f32, ?, ?, f64))0x0F801250(var_f12, 0x10000614, second half of f64, (f64) (temp_v0_3 * 0x64) / (bitwise f64) var_f12);
        } else {
            (? (*)(f32, void *))0x0F801250(var_f12, saved_reg_gp - 0x7DB4);
        }
        saved_reg_gp->unk-7B70 = sp24;
    }
}

void save_image(s32 arg0, ? arg16) {
    ? sp48;
    s32 *var_s0;
    s32 *var_s0_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s4;

    temp_s0 = saved_reg_gp->unk-7E98->unk98;
    temp_v0 = (s32 (*)(s32, void *))0x0F801130(temp_s0, saved_reg_gp - 0x7DA4);
    if (temp_v0 != 0) {
        (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x10000624, saved_reg_gp - 0x7EA0, temp_s0);
        (? (*)(?))0x0F402578(1);
        (? (*)(? *))0x0F401120(&sp48);
        (? (*)(?))0x0F801250(0x10000644);
        var_s4 = 0;
        do {
            (? (*)(void *))0x0F801250(saved_reg_gp - 0x7DA0);
            var_s1 = 0;
loop_3:
            (? (*)(void *))0x0F801250(saved_reg_gp - 0x7D9C);
            var_s1 += 1;
            if (var_s1 != 4) {
                goto loop_3;
            }
            (? (*)(void *))0x0F801250(saved_reg_gp - 0x7D98);
            var_s4 += 4;
        } while (var_s4 < 0x10);
        var_s0 = &arg0;
        do {
            (? (*)(s32, void *, ?, f64))0x0F801150(temp_v0, saved_reg_gp - 0x7D94, second half of f64, (f64) var_s0->unk-48);
            var_s0 += 4;
        } while (var_s0 != &arg16);
        (? (*)(s32, void *))0x0F801150(temp_v0, saved_reg_gp - 0x7D90);
        (? (*)(?))0x0F402578(2);
        (? (*)(? *))0x0F401120(&sp48);
        var_s0_2 = &arg0;
        do {
            (? (*)(s32, void *, ?, f64))0x0F801150(temp_v0, saved_reg_gp - 0x7D8C, second half of f64, (f64) var_s0_2->unk-48);
            var_s0_2 += 4;
        } while (var_s0_2 != &arg16);
        (? (*)(s32, void *))0x0F801150(temp_v0, saved_reg_gp - 0x7D88);
        return;
    }
    (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x10000668, saved_reg_gp - 0x7EA0, temp_s0);
}

void draw_scene_special(void) {
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s4;

    temp_s0 = saved_reg_gp->unk-7E98->unk98;
    if (saved_reg_gp->unk-7D84 == 0) {
        temp_v0 = (s32 (*)(s32, void *))0x0F801130(temp_s0, saved_reg_gp - 0x7D80);
        if (temp_v0 != 0) {
            (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x10000688, saved_reg_gp - 0x7EA0, temp_s0);
            var_s0 = 0x100044E8;
            do {
                lbl_40d768(temp_v0, saved_reg_gp - 0x7D7C, var_s0);
                var_s0 += 4;
            } while (var_s0 != 0x10004528);
            var_s0_2 = 0x10004528;
            do {
                lbl_40d768(temp_v0, saved_reg_gp - 0x7D78, var_s0_2);
                var_s0_2 += 4;
            } while (var_s0_2 != 0x10004568);
            (? (*)(?))0x0F801250(0x100006AC);
            var_s4 = 0;
            do {
                (? (*)(void *))0x0F801250(saved_reg_gp - 0x7D74);
                var_s1 = 0;
loop_8:
                (? (*)(void *))0x0F801250(saved_reg_gp - 0x7D70);
                var_s1 += 1;
                if (var_s1 != 4) {
                    goto loop_8;
                }
                (? (*)(void *))0x0F801250(saved_reg_gp - 0x7D6C);
                var_s4 += 4;
            } while (var_s4 != 0x10);
            saved_reg_gp->unk-7D84 = 1;
        } else {
            (? (*)(?, ?, void *, s32))0x0F801150(0x100036B4, 0x100006D4, saved_reg_gp - 0x7EA0, temp_s0);
            lbl_40d3c0(-1);
        }
    }
    (? (*)(?))0x0F402578(1);
    (? (*)(?))0x0F402190(0x100044E8);
    (? (*)(?))0x0F402578(2);
    (? (*)(?))0x0F402190(0x10004528);
}

/*
Decompilation failure in function event_loop_and_render:

Cannot find branch target lbl_402b7c
*/

/*
Decompilation failure in function update_view_angles:

Unable to parse branch: label lbl_4020f4 does not exist in function update_view_angles
*/

void render_frame_no_zbuf(void) {
    (? (*)(?))0x0F402098(0);
    (? (*)())0x0F402120();
    (? (*)())0x0F402518();
    (? (*)())0x0F402230();
    lbl_402fbc();
    lbl_401504();
    (? (*)())0x0F402228();
    (? (*)())0x0F402288();
}

void init_fly_state(void) {
    f32 temp_f0;

    temp_f0 = saved_reg_gp->unk-7EC8;
    saved_reg_gp->unk-7B28 = temp_f0;
    saved_reg_gp->unk-7E98->unk4C = (f32) ((f64) temp_f0 / saved_reg_gp->unk-7FA8);
    saved_reg_gp->unk-7B58 = 0.0f;
    saved_reg_gp->unk-7B54 = 0.0f;
    saved_reg_gp->unk-7B50 = 0.0f;
    saved_reg_gp->unk-7B5C = (f32) saved_reg_gp->unk-7EC4;
    saved_reg_gp->unk-7E98->unk50 = 0x258;
    saved_reg_gp->unk-7E98->unk54 = 3;
}

void draw_scene_fly(void) {
    f32 sp1C;
    f32 sp18;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 var_f2;
    f64 temp_f0;
    f64 temp_f0_2;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_at;
    s32 var_at_2;
    void *temp_t2;
    void *temp_t4;
    void *temp_t9;

    if (saved_reg_gp->unk-7E98->unk18 == 0) {
        var_f2 = saved_reg_gp->unk-7B60;
    } else {
        var_f2 = (f32) ((f64) saved_reg_gp->unk-7B60 + (f64) saved_reg_gp->unk-7E98->unk4C);
    }
    temp_t9 = saved_reg_gp->unk-7E98;
    if (temp_t9->unk1C != 0) {
        var_f2 = (f32) ((f64) var_f2 - (f64) temp_t9->unk4C);
    }
    temp_f0 = (f64) var_f2;
    saved_reg_gp->unk-7B60 = (f32) (temp_f0 - (temp_f0 * (f64) saved_reg_gp->unk-7B5C));
    saved_reg_gp->unk-7B40 = (s32) ((s32 (*)(?))0x0F401140(0x10A) - saved_reg_gp->unk-7E98->unk8);
    temp_v0 = (s32 (*)(?))0x0F401140(0x10B);
    temp_t4 = saved_reg_gp->unk-7E98;
    temp_v1 = temp_t4->unk0;
    var_at = temp_v1;
    if (temp_v1 < 0) {
        var_at += 1;
    }
    temp_a1 = temp_v0 - temp_t4->unkC;
    saved_reg_gp->unk-7B20 = (f32) ((f64) saved_reg_gp->unk-7B20 + (f64) (f32) (((f64) (f32) (saved_reg_gp->unk-7B40 - (var_at >> 1)) * (bitwise f64) saved_reg_gp->unk-7F9C) / (f64) temp_v1));
    temp_a0 = temp_t4->unk4;
    saved_reg_gp->unk-7B3C = temp_a1;
    var_at_2 = temp_a0;
    if (temp_a0 < 0) {
        var_at_2 += 1;
    }
    temp_f14 = (f32) (((f64) (f32) (temp_a1 - (var_at_2 >> 1)) * (bitwise f64) saved_reg_gp->unk-7F94) / (f64) temp_a0);
    saved_reg_gp->unk-7B24 = temp_f14;
    temp_f0_2 = lbl_40d178(((f64) temp_f14 * saved_reg_gp->unk-7F90) / saved_reg_gp->unk-7F88, temp_f14, temp_a0, temp_a1);
    temp_v0_2 = saved_reg_gp->unk-7E98->unk54;
    switch (temp_v0_2) {                            /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        saved_reg_gp->unk-7B58 = (f32) ((f64) saved_reg_gp->unk-7B58 - (f64) (f32) ((f64) (f32) temp_f0_2 * (f64) saved_reg_gp->unk-7B60));
        break;
    case 2:                                         /* switch 1 */
        saved_reg_gp->unk-7B54 = (f32) ((f64) saved_reg_gp->unk-7B54 - (f64) (f32) ((f64) (f32) temp_f0_2 * (f64) saved_reg_gp->unk-7B60));
        break;
    case 3:                                         /* switch 1 */
        saved_reg_gp->unk-7B50 = (f32) ((f64) saved_reg_gp->unk-7B50 - (f64) (f32) ((f64) (f32) temp_f0_2 * (f64) saved_reg_gp->unk-7B60));
        break;
    }
    temp_t2 = saved_reg_gp->unk-7E98;
    (? (*)(s32, s32, ?, f32))0x0F402FA0(temp_t2->unk50, temp_t2->unk6C, 0x3DCCCCCD, saved_reg_gp->unk-7B28 * saved_reg_gp->unk-7EC0);
    sp1C = (f32) ((f64) (f32) lbl_40d178(((f64) saved_reg_gp->unk-7B20 * saved_reg_gp->unk-7F90) / saved_reg_gp->unk-7F88) * (f64) saved_reg_gp->unk-7B60);
    temp_f14_2 = saved_reg_gp->unk-7B24;
    sp18 = (f32) ((f64) (f32) lbl_40d120(((f64) saved_reg_gp->unk-7B20 * saved_reg_gp->unk-7F90) / saved_reg_gp->unk-7F88) * (f64) saved_reg_gp->unk-7B60);
    (? (*)(f32, f32, ?))0x0F402558(temp_f14_2, temp_f14_2, 0x78);
    (? (*)(f32, ?))0x0F402558(saved_reg_gp->unk-7B20, 0x79);
    temp_v0_3 = saved_reg_gp->unk-7E98->unk54;
    switch (temp_v0_3) {                            /* switch 2; irregular */
    case 1:                                         /* switch 2 */
        (? (*)(?, ?))0x0F402270(0x384, 0x7A);
        saved_reg_gp->unk-7B54 = (f32) ((f64) saved_reg_gp->unk-7B54 - (f64) sp1C);
        saved_reg_gp->unk-7B50 = (f32) ((f64) saved_reg_gp->unk-7B50 - (f64) sp18);
        break;
    case 2:                                         /* switch 2 */
        saved_reg_gp->unk-7B58 = (f32) ((f64) saved_reg_gp->unk-7B58 + (f64) sp1C);
        saved_reg_gp->unk-7B50 = (f32) ((f64) saved_reg_gp->unk-7B50 - (f64) sp18);
        break;
    case 3:                                         /* switch 2 */
        (? (*)(?, ?))0x0F402270(-0x384, 0x78);
        saved_reg_gp->unk-7B58 = (f32) ((f64) saved_reg_gp->unk-7B58 + (f64) sp1C);
        saved_reg_gp->unk-7B54 = (f32) ((f64) saved_reg_gp->unk-7B54 + (f64) sp18);
        break;
    }
    (? (*)(f32, f32, f32))0x0F402298(-saved_reg_gp->unk-7B58, -saved_reg_gp->unk-7B54, -saved_reg_gp->unk-7B50);
    saved_reg_gp->unk-7E98->unk58 = (f32) saved_reg_gp->unk-7B58;
    saved_reg_gp->unk-7E98->unk5C = (f32) saved_reg_gp->unk-7B54;
    saved_reg_gp->unk-7E98->unk60 = (f32) saved_reg_gp->unk-7B50;
}

void setup_materials(void) {
    (? (*)(?, ?, ?, ?))0x0F4015D0(0, 1, 0x3C, 0x10000760);
    (? (*)(?, ?, ?, ?))0x0F4015D0(0x64, 1, 0x38, 0x10000728);
    (? (*)(?, ?, ?, ?))0x0F4015D0(0xC8, 1, 0x28, 0x10000700);
    (? (*)(?, ?))0x0F402570(0x3E8, 1);
    (? (*)(?, ?))0x0F402570(0x44C, 1);
}

void bind_material(s32 arg0) {
    ? var_a1;

    if (arg0 != 0) {
        var_a1 = 1;
    } else {
        var_a1 = 0;
    }
    (? (*)(?, ?))0x0F402570(0x4B0, var_a1);
}

void init_window_and_gl(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = (s32 (*)(?))0x0F801208(0x7D0);
    saved_reg_gp->unk-7B10 = temp_v0;
    if (temp_v0 == 0) {
        lbl_4092d4((void *)0x1000094C);
    }
    saved_reg_gp->unk-7B0C = 0;
    temp_v0_2 = (s32 (*)(?))0x0F801208(0x3E8);
    saved_reg_gp->unk-7B08 = temp_v0_2;
    if (temp_v0_2 == 0) {
        lbl_4092d4((void *)0x1000095C);
    }
    saved_reg_gp->unk-7B04 = (s32) saved_reg_gp->unk-7B08;
    temp_v0_3 = (s32 (*)(?))0x0F801208(0x640);
    saved_reg_gp->unk-7B00 = temp_v0_3;
    if (temp_v0_3 == 0) {
        lbl_4092d4((void *)0x1000096C);
    }
    saved_reg_gp->unk-7AFC = (s32) saved_reg_gp->unk-7B00;
    saved_reg_gp->unk-7AF8 = 1;
    saved_reg_gp->unk-7AF4 = 1;
    saved_reg_gp->unk-7AF0 = 1;
}

s32 load_material_file(s32 arg0, s32 arg1) {
    u8 **sp2C;
    s32 temp_v0;

    if (saved_reg_gp->unk-7D34 == 0) {
        saved_reg_gp->unk-7ADC = lbl_4043bc((u8 *)0x1000097C);
        saved_reg_gp->unk-7AD8 = lbl_4043bc((u8 *)0x10000988);
        saved_reg_gp->unk-7AD4 = lbl_4043bc((u8 *)0x10000994);
        saved_reg_gp->unk-7D34 = 1;
    }
    lbl_40406c(arg0, arg1);
    if (lbl_4040d0(&sp2C) != 0) {
        do {
            temp_v0 = sp2C->unk4;
            if (temp_v0 != 0) {
                if ((saved_reg_gp->unk-7ADC != temp_v0) && (saved_reg_gp->unk-7AD8 != temp_v0)) {
                    if (saved_reg_gp->unk-7AD4 == temp_v0) {
                        goto block_9;
                    }
                    goto block_10;
                }
block_9:
                lbl_403bf8(sp2C);
            } else {
block_10:
                lbl_403ffc(0x100009A0);
            }
        } while (lbl_4040d0(&sp2C) != 0);
    }
    return 1;
}

void setup_menu(void) {
    s32 temp_a1_2;
    s32 var_s1;
    s32 var_s2;
    void *temp_a1;
    void *temp_v0;

    var_s2 = 0;
    if (saved_reg_gp->unk-7B0C > 0) {
        var_s1 = 0;
        do {
            temp_v0 = saved_reg_gp->unk-7B10 + var_s1;
            if (temp_v0->unk0 != NULL) {

            }
            (? (*)(void *, s32, s32, s32))0x0F4015D0(temp_v0->unk0, temp_v0->unk10, temp_v0->unkC, temp_v0->unk8);
            temp_a1 = temp_v0->unk0;
            switch (temp_a1) {                      /* irregular */
            case 0x0:
                break;
            case 0x64:
                temp_a1_2 = temp_v0->unk10;
                if (temp_a1_2 < 9) {
                    (? (*)(s32, s32))0x0F402570(temp_a1_2 + 0x44B, temp_a1_2);
                } else {
                    (? (*)(?, ?))0x0F801150(0x100036B4, 0x100009CC);
                }
                break;
            case 0xC8:
                if (temp_v0->unk10 != 1) {
                    (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100009F4, 0x10000A08);
                    lbl_40d3c0(1);
                }
                (? (*)(?, s32))0x0F402570(0x4B0, temp_v0->unk10);
                break;
            default:
                lbl_4092d4((void *)0x10000A18, temp_a1);
                break;
            }
            var_s2 += 1;
            var_s1 += 0x14;
        } while (var_s2 < saved_reg_gp->unk-7B0C);
    }
}

void *gfo_new_scope(s32 arg0) {
    s32 var_s0;
    s32 var_s2;
    void *temp_v0;

    var_s2 = 0;
    if (saved_reg_gp->unk-7B0C > 0) {
        var_s0 = 0;
loop_2:
        temp_v0 = saved_reg_gp->unk-7B10 + var_s0;
        if ((temp_v0->unk0 == 0) && ((s32 (*)(s32, s32))0x0F8012E8(arg0, temp_v0->unk4) == 0)) {
            return temp_v0;
        }
        var_s2 += 1;
        var_s0 += 0x14;
        if (var_s2 >= saved_reg_gp->unk-7B0C) {
            goto block_7;
        }
        goto loop_2;
    }
block_7:
    return NULL;
}

void gfo_set_material(void *arg0) {
    (? (*)(?, s32))0x0F402570(0x3E8, arg0->unk10);
}

s32 gfo_parse_keyword(s32 arg0) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp1C = saved_reg_gp->unk-7B04;
    temp_v0 = (s32 (*)(s32))0x0F801308(arg0);
    sp18 = temp_v0 + 1;
    if (temp_v0 >= (0x3E7 - (saved_reg_gp->unk-7B04 - saved_reg_gp->unk-7B08))) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000A34, 0x10000A48);
        lbl_40d3c0(1);
    }
    (? (*)(s32, s32, s32))0x0F801320(sp1C, arg0, sp18);
    saved_reg_gp->unk-7B04 = (s32) (saved_reg_gp->unk-7B04 + sp18);
    return sp1C;
}

void *gfo_parse_polygon(s32 arg0, void *arg1) {
    void *sp1C;
    s32 temp_v0;
    s32 temp_v0_2;
    void *temp_v1;

    if (saved_reg_gp->unk-7B0C >= 0x64) {
        (? (*)(?, ?, ?, void *))0x0F801150(0x100036B4, 0x10000A74, 0x10000A88, arg1);
        lbl_40d3c0(1);
    }
    temp_v1 = saved_reg_gp->unk-7B10 + (saved_reg_gp->unk-7B0C * 0x14);
    sp1C = temp_v1;
    temp_v1->unk4 = lbl_403960(arg0);
    temp_v1->unk8 = 0;
    temp_v1->unkC = 0;
    temp_v1->unk0 = arg1;
    switch (arg1) {                                 /* irregular */
    case 0x0:
        temp_v0 = saved_reg_gp->unk-7AF8;
        temp_v1->unk10 = temp_v0;
        saved_reg_gp->unk-7AF8 = (s32) (temp_v0 + 1);
        break;
    case 0x64:
        temp_v0_2 = saved_reg_gp->unk-7AF4;
        temp_v1->unk10 = temp_v0_2;
        saved_reg_gp->unk-7AF4 = (s32) (temp_v0_2 + 1);
        break;
    case 0xC8:
        temp_v1->unk10 = (s32) saved_reg_gp->unk-7AF0;
        break;
    default:
        sp1C = temp_v1;
        lbl_4092d4((void *)0x10000A94, arg1);
        break;
    }
    saved_reg_gp->unk-7B0C = (s32) (saved_reg_gp->unk-7B0C + 1);
    return temp_v1;
}

void gfo_parse_instance(void *arg0, ? arg1) {
    if (arg0->unkC == 0) {
        arg0->unk8 = lbl_4039f8(arg1);
    } else {
        lbl_4039f8(arg1);
    }
    arg0->unkC = (s32) (arg0->unkC + 1);
}

s32 gfo_parse_vertex(u8 **arg0) {
    s32 sp24;
    void **temp_s0;
    void *var_v0;
    void *var_v0_2;

    if (saved_reg_gp->unk-7ACC == 0) {
        saved_reg_gp->unk-7AD0 = lbl_4043bc(saved_reg_gp - 0x7D20);
        saved_reg_gp->unk-7ACC = 1;
    }
    sp24 = (s32) ((f64) arg0->unk4->unk4 + (bitwise f64) saved_reg_gp->unk-7FDC);
    if (lbl_4040d0(&arg0) == 0) {
        lbl_403ffc(0x10000AAC);
    }
    temp_s0 = lbl_403a78(arg0->unk0, sp24);
    if (lbl_404370(&arg0) == 0) {
        lbl_403ffc(0x10000AC8);
    }
    var_v0 = arg0->unk4;
    if ((var_v0 != NULL) && (saved_reg_gp->unk-7AD0 != var_v0)) {
loop_8:
        lbl_403e28(temp_s0);
        if (lbl_404370(&arg0) == 0) {
            lbl_403ffc(0x10000AE4);
        }
        var_v0 = arg0->unk4;
        if ((var_v0 != NULL) && (saved_reg_gp->unk-7AD0 != var_v0)) {
            goto loop_8;
        }
    }
    if (var_v0 == NULL) {
        lbl_403ffc(0x10000B00);
    }
    if (lbl_4040d0(&arg0) == 0) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000B14, 0x10000B28);
        lbl_40d3c0(1);
    }
    var_v0_2 = arg0->unk4;
    if (var_v0_2 == NULL) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000B40, 0x10000B54);
        lbl_40d3c0(1);
        var_v0_2 = arg0->unk4;
    }
    if ((f64) var_v0_2->unk4 != 0.0) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000B70, 0x10000B84);
        lbl_40d3c0(1);
    }
    lbl_403b9c(temp_s0, 0.0f);
    return 1;
}

s32 gfo_parse_line(void **arg0) {
    u8 **sp54;
    s32 sp50;
    f32 sp40;
    s32 sp3C;
    f32 temp_f2;
    s32 temp_s1;
    s32 var_s0;
    void *temp_a1;
    void *temp_v0;

    if (lbl_4040d0(&sp54) == 0) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000B90, 0x10000BA4);
        lbl_40d3c0(1);
    }
    temp_a1 = *arg0;
    switch (temp_a1) {                              /* irregular */
    case 0x0:
        sp50 = 1;
        break;
    case 0x64:
        sp50 = 2;
        break;
    case 0xC8:
        sp50 = 4;
        break;
    default:
        lbl_4092d4((void *)0x10000BB0, temp_a1);
        break;
    }
    temp_v0 = sp54->unk4;
    if (temp_v0 != NULL) {
        if (temp_v0->unkC & sp50) {
            lbl_403b9c(arg0, temp_v0->unk4);
            temp_s1 = sp54->unk4->unk8;
            if (temp_s1 < 0) {
                lbl_403ffc(0x10000BC8);
            }
            var_s0 = 0;
            if (temp_s1 > 0) {
                do {
                    if (lbl_4040d0(&sp54) == 0) {
                        lbl_403ffc(0x10000BD8);
                    }
                    temp_f2 = (f32) lbl_40d830(sp54->unk0, &sp3C);
                    if (sp3C == sp54->unk0) {
                        sp40 = temp_f2;
                        lbl_403ffc(0x10000BF8);
                    }
                    lbl_403b9c(arg0, temp_f2);
                    var_s0 += 1;
                } while (var_s0 != temp_s1);
            }
        } else {
            lbl_403ffc(0x10000C0C);
        }
    } else {
        lbl_403ffc(0x10000C2C);
    }
    return 1;
}

void gfo_parse_entity(s32 arg0) {
    (? (*)(?, ?, s32, s32, s32, s32))0x0F801150(0x100036B4, 0x10000C40, saved_reg_gp->unk-7AE8, *(s32 *)0x10004678, *(s32 *)0x1000467C, arg0);
    (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000C68, 0x10004570);
    lbl_40d3c0(-1);
}

s32 gfo_parse_scope(s32 *arg0) {
    u8 *sp2C;
    u8 **temp_v0;
    u8 *temp_a2;
    u8 *var_a1;
    u8 *var_v1_2;
    u8 var_v0;
    void *var_v1;

    var_a1 = saved_reg_gp->unk-7D38;
    if (var_a1 != NULL) {
        goto block_5;
    }
    if (lbl_40408c((u8 *)0x10004570, 0x100) == 0) {
        *(s32 *)0x10004680 = 0;
        return 0;
    }
    var_a1 = (u8 *)0x10004570;
block_5:
    if (saved_reg_gp->unk-7AE0 != 0) {
        saved_reg_gp->unk-7D38 = var_a1;
        saved_reg_gp->unk-7AE0 = 0;
        *arg0 = 0x10004670;
        return *(void *)0x10004680;
    }
    var_v0 = *var_a1;
    var_v1 = var_v0 + 0x100032E0;
    if ((var_v1->unk1 & 8) || (var_v0 == 0) || (var_v0 == 0x23)) {
loop_10:
        if (var_v1 == (void *)0x100032E0) {
            goto block_13;
        }
        if (var_v1 == (void *)0x10003303) {
block_13:
            saved_reg_gp->unk-7D38 = var_a1;
            if (lbl_40408c((u8 *)0x10004570, 0x100) == 0) {
                *(void *)0x10004680 = 0;
                return 0;
            }
            var_a1 = (u8 *)0x10004570;
            goto block_17;
        }
        var_a1 += 1;
block_17:
        var_v0 = *var_a1;
        var_v1 = var_v0 + 0x100032E0;
        if (!(var_v1->unk1 & 8) && (var_v0 != 0) && (var_v0 != 0x23)) {
            goto block_20;
        }
        goto loop_10;
    }
block_20:
    temp_a2 = var_a1;
    var_v1_2 = (u8 *)0x10004688;
    if (var_v0 == 0) {

    } else if ((var_v0 + 0x100032E0)->unk1 & 8) {

    } else {
loop_24:
        *var_v1_2 = var_v0;
        var_v0 = var_a1->unk1;
        var_v1_2 += 1;
        var_a1 += 1;
        if (var_v0 == 0) {

        } else if (!((var_v0 + 0x100032E0)->unk1 & 8)) {
            goto loop_24;
        }
    }
    saved_reg_gp->unk-7D38 = var_a1;
    *var_v1_2 = 0;
    if (var_v0 == 0) {
        sp2C = temp_a2;
        if (lbl_40408c((u8 *)0x10004570, 0x100, temp_a2, 0x10004688) == 0) {
            *(void *)0x10004680 = 0;
            return 0;
        }
        var_a1 = (u8 *)0x10004570;
        saved_reg_gp->unk-7D38 = (u8 *)0x10004570;
        goto block_31;
    }
block_31:
    *(u8 **)0x10004670 = (u8 *)0x10004688;
    *(s32 *)0x1000467C = (temp_a2 - 0x10004570) + 1;
    *(s32 *)0x10004678 = saved_reg_gp->unk-7AE4;
    *(u8 ***)0x10004674 = NULL;
    if ((*(u8 *)0x10004688 + 0x100032E0)->unk1 & 3) {
        temp_v0 = lbl_4043bc((u8 *)0x10004688, var_a1, temp_a2, (u8 *)0x10004688);
        *(void *)0x10004674 = temp_v0;
        if (temp_v0 != NULL) {
            *(void *)0x10004670 = (u8 *) *temp_v0;
        }
    }
    *(void *)0x10004680 = 1;
    *arg0 = 0x10004670;
    return 1;
}

s32 gfo_parse_material(s32 *arg0) {
    s32 temp_v0;

    if (saved_reg_gp->unk-7AE0 == 0) {
        temp_v0 = lbl_4040d0();
        saved_reg_gp->unk-7AE0 = 1;
        return temp_v0;
    }
    *arg0 = 0x10004670;
    return *(s32 *)0x10004680;
}

s32 *gfo_alloc_entity(s32 arg0) {
    s32 sp28;
    s32 *var_s1;
    s32 *var_v1;
    s32 var_s0;

    sp28 = 0;
    var_s1 = (s32 *)0x100007E0;
    var_s0 = 0;
loop_1:
    var_s0 += 1;
    if ((s32 (*)(s32, s32))0x0F8012E8(arg0, *var_s1) == 0) {
        sp28 = 1;
    } else {
        var_s1 += 0x10;
        if (var_s0 != 0xF) {
            goto loop_1;
        }
    }
    var_v1 = NULL;
    if (sp28 != 0) {
        var_v1 = var_s1;
    }
    return var_v1;
}

void *gfo_alloc_scope(void) {
    void *sp1C;
    void *temp_t6;
    void *temp_v0;

    temp_t6 = saved_reg_gp->unk-7E98;
    temp_v0 = temp_t6->unkFC;
    temp_t6->unkFC = (void *) (temp_v0 + 0xC);
    if (((s32) (temp_v0 - saved_reg_gp->unk-7E98->unkF4) / 12) >= 0x2DE6) {
        sp1C = temp_v0;
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000C80, 0x10000C94);
        lbl_40d3c0(1);
    }
    temp_v0->unk0 = 0;
    temp_v0->unk4 = 0;
    return temp_v0;
}

s32 gfo_count_elements(s32 arg0) {
    s32 sp1C;
    s32 temp_t2;
    s32 temp_v0;
    s32 var_at;
    void *temp_t6;
    void *temp_t9;

    temp_t6 = saved_reg_gp->unk-7E98;
    temp_v0 = temp_t6->unk100;
    sp1C = temp_v0;
    temp_t6->unk100 = (s32) (temp_v0 + (arg0 * 4));
    temp_t9 = saved_reg_gp->unk-7E98;
    temp_t2 = temp_t9->unk100 - temp_t9->unkF8;
    var_at = temp_t2;
    if (temp_t2 < 0) {
        var_at += 3;
    }
    if ((var_at >> 2) >= 0x89545) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000CA0, 0x10000CB4);
        lbl_40d3c0(1);
    }
    return sp1C;
}

void gfo_build_display_list(void) {
    s32 temp_a2;
    void *temp_t2;
    void *temp_t4;

    saved_reg_gp->unk-7E98->unkF4 = (s32 (*)(?))0x0F801208(0x226C8);
    if (saved_reg_gp->unk-7E98->unkF4 == 0) {
        lbl_4092d4((void *)0x10000CC0);
    }
    saved_reg_gp->unk-7E98->unkF8 = (s32 (*)(?))0x0F801208(0x225510);
    if (saved_reg_gp->unk-7E98->unkF8 == 0) {
        lbl_4092d4((void *)0x10000CEC);
    }
    temp_t2 = saved_reg_gp->unk-7E98;
    temp_t2->unkFC = (s32) temp_t2->unkF4;
    temp_t4 = saved_reg_gp->unk-7E98;
    temp_t4->unk100 = (s32) temp_t4->unkF8;
    temp_a2 = saved_reg_gp->unk-7E98->unkF8;
    if (temp_a2 & 0xF) {
        (? (*)(?, ?, s32))0x0F801150(0x100036B4, 0x10000D18, temp_a2);
    }
}

s32 gfo_load_file(s32 arg0, ? arg1) {
    s32 sp6C;
    s32 *sp58;
    s32 *sp50;
    s32 *temp_v0_2;
    s32 *var_s0;
    s32 temp_v1;
    s32 temp_v1_2;
    void **var_t0;
    void **var_v0;
    void *temp_v0;

    sp6C = lbl_40a400();
    temp_v0 = (void *(*)(?))0x0F801208(0x10);
    if (temp_v0 == NULL) {
        lbl_4092d4(saved_reg_gp - 0x7D10);
    }
    temp_v0->unk0 = 0x109;
    temp_v0->unk8 = 0;
    lbl_40a6d4(sp6C, temp_v0);
    temp_v1 = lbl_40a8e0(arg0)->unk4;
    if (temp_v1 == 0x408AB0) {
        temp_v0->unk4 = 0x408AB0;
        temp_v0->unkC = 4;
    } else if (temp_v1 == 0x408840) {
        temp_v0->unk4 = 0x408840;
        temp_v0->unkC = 2;
    } else {
        (? (*)(?, ?))0x0F801150(0x100036B4, 0x10000D4C);
        lbl_40d3c0(-1);
    }
    temp_v0_2 = lbl_404460();
    sp50 = temp_v0_2;
    *temp_v0_2 = 0;
    var_s0 = temp_v0_2;
    sp58 = NULL;
    var_v0 = lbl_40a8e0(arg0);
    var_t0 = var_v0;
    if (var_v0 != NULL) {
        do {
            temp_v1_2 = var_v0->unk4;
            if (temp_v1_2 == 0x408AB0) {
                lbl_40493c(var_t0->unk8, var_s0, &sp58, arg1);
            } else if (temp_v1_2 == 0x408840) {
                lbl_404a4c(var_t0->unk8, var_s0, &sp58, arg1);
            } else {
                (? (*)(?, ?))0x0F801150(0x100036B4, 0x10000D80);
                lbl_40d3c0(-1);
            }
            var_s0 = sp58;
            var_v0 = lbl_40a918(arg0);
            var_t0 = var_v0;
        } while (var_v0 != NULL);
    }
    temp_v0->unk8 = (s32) *sp50;
    return sp6C;
}

s32 *bin_write_model(void *arg0, s32 **arg1) {
    s32 *sp1C;
    s32 *temp_v0;
    s32 *temp_v0_2;
    s32 *var_a0;
    s32 *var_v1;
    s32 var_a1;

    temp_v0 = lbl_404460(arg0);
    sp1C = temp_v0;
    temp_v0_2 = lbl_4044f0(arg0->unk8);
    var_v1 = temp_v0_2;
    temp_v0->unk4 = temp_v0_2;
    var_a1 = 0;
    temp_v0->unk8 = (s32) arg0->unk8;
    *arg1 = temp_v0;
    temp_v0->unk0 = 0;
    var_a0 = arg0->unk4;
    if (arg0->unk8 > 0) {
        do {
            var_a1 += 1;
            *var_v1 = *var_a0;
            var_a0 += 4;
            var_v1 += 4;
        } while (var_a1 < arg0->unk8);
    }
    return temp_v0;
}

s32 bin_write_array(void *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    s32 var_s1;
    s32 var_s2;
    void *var_s0;

    var_s2 = arg1;
    var_s1 = 0;
    var_s0 = arg0;
    if (arg0 != NULL) {
        do {
            if (var_s0->unk8 != 0x18) {
                (? (*)(?, ?))0x0F801150(0x100036B4, 0x10000DB0);
            } else if (arg3 != 1) {
                lbl_4092d4((void *)0x10000DE8);
            } else {
                var_s2 = lbl_404848(var_s0, var_s2);
                var_s1 += 1;
            }
            var_s0 = var_s0->unk0;
        } while (var_s0 != NULL);
    }
    *arg2 = var_s2;
    return var_s1;
}

s32 bin_read_array(void *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    s32 var_s1;
    s32 var_s2;
    void *var_s0;

    var_s2 = arg1;
    var_s1 = 0;
    var_s0 = arg0;
    if (arg0 != NULL) {
        do {
            if (var_s0->unk8 != 0x10) {
                (? (*)(?, ?))0x0F801150(0x100036B4, 0x10000E10);
            } else if (arg3 != 1) {
                lbl_4092d4((void *)0x10000E48);
            } else {
                var_s2 = lbl_404848(var_s0, var_s2);
                var_s1 += 1;
            }
            var_s0 = var_s0->unk0;
        } while (var_s0 != NULL);
    }
    *arg2 = var_s2;
    return var_s1;
}

void bin_read_model(s32 *arg0, s32 arg1, ? arg2) {
    s32 sp39C;
    s32 sp398;
    s32 sp394;
    s32 sp390;
    s32 sp38C;
    s32 sp388;
    s32 sp384;
    s32 sp380;
    s32 sp37C;
    ? sp5C;
    s32 sp58;
    s32 sp54;
    s32 **sp3C;
    s32 sp38;
    s32 **var_v1;
    s32 *var_s0_2;
    s32 *var_s0_3;
    s32 temp_lo;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_at;
    s32 var_s0;
    s32 var_s6;
    void **temp_v0;
    void **temp_v0_2;
    void **var_a0;
    void *temp_t6;

    var_s0 = saved_reg_s0;
    temp_t6 = saved_reg_gp->unk-7E98;
    temp_lo = (s32) (temp_t6->unkFC - temp_t6->unkF4) / 12;
    sp38C = arg1;
    sp37C = 0x13577531;
    sp380 = 0x10002;
    sp384 = 0x10;
    sp388 = 0xC;
    temp_v1 = temp_t6->unk100 - temp_t6->unkF8;
    sp390 = temp_t6->unkF4;
    sp394 = temp_t6->unkF8;
    var_at = temp_v1;
    if (temp_v1 < 0) {
        var_at += 3;
    }
    temp_v1_2 = var_at >> 2;
    sp39C = temp_v1_2;
    sp54 = temp_v1_2;
    sp398 = temp_lo;
    sp58 = temp_lo;
    (? (*)(?))0x0F801250(0x10000E70);
    (? (*)(?, s32))0x0F801250(0x10000E88, sp38C);
    (? (*)(?, s32))0x0F801250(0x10000E98, sp398);
    (? (*)(?, s32))0x0F801250(0x10000EB0, sp39C);
    if ((s32 (*)(s32 *, ?, ?, ?))0x0F801198(&sp37C, 0x24, 1, arg2) == 1) {

    } else {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000EC4, 0x10000ED8);
        lbl_40d3c0(1);
    }
    var_s6 = 0;
    if (sp38C > 0) {
        var_s0_2 = arg0;
        var_v1 = &arg0;
        do {
            sp3C = var_v1;
            var_s6 += 1;
            var_v1->unk-344 = lbl_40ade4(*var_s0_2);
            var_s0_2 += 4;
            var_v1 += 4;
        } while (var_s6 < sp38C);
        var_s0 = sp38;
        var_s6 = 0;
    }
    if ((s32 (*)(? *, ?, s32, ?))0x0F801198(&sp5C, 4, sp38C, arg2) != sp38C) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000EF8, 0x10000F0C);
        lbl_40d3c0(1);
    }
    if (sp38C > 0) {
        sp38 = var_s0;
        var_s0_3 = arg0;
        do {
            temp_v0 = lbl_40a8e0(*var_s0_3);
            var_a0 = temp_v0;
            if (temp_v0 != NULL) {
                do {
                    if ((s32 (*)(void **, ?, ?, ?))0x0F801198(var_a0, 0x10, 1, arg2) != 1) {
                        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000F1C, 0x10000F30);
                        lbl_40d3c0(1);
                    }
                    temp_v0_2 = lbl_40a918(*var_s0_3);
                    var_a0 = temp_v0_2;
                } while (temp_v0_2 != NULL);
            }
            var_s6 += 1;
            var_s0_3 += 4;
        } while (var_s6 < sp38C);
    }
    if ((s32 (*)(s32, ?, s32, ?))0x0F801198(sp390, 0xC, sp58, arg2) != sp58) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000F40, 0x10000F54);
        lbl_40d3c0(1);
    }
    if ((s32 (*)(s32, ?, s32, ?))0x0F801198(sp394, 4, sp54, arg2) != sp54) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000F64, 0x10000F78);
        lbl_40d3c0(1);
    }
}

s32 *gfo_read_file(s32 arg0, s32 *arg1) {
    s32 sp394;
    ? sp74;
    s32 *sp70;
    void *sp6C;
    s32 sp68;
    s32 sp60;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 *temp_v0;
    s32 *var_s3_2;
    s32 *var_s4_2;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_t3;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_7;
    s32 var_at;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_t5;
    s32 var_t5_2;
    s32 var_v0;
    s32 var_v1;
    void *temp_v0_2;
    void *temp_v0_5;
    void *temp_v0_6;
    void *var_s2_2;

    var_s1 = saved_reg_s1;
    var_s3 = saved_reg_s3;
    var_s4 = saved_reg_s4;
    var_s5 = saved_reg_s5;
    var_s6 = saved_reg_s6;
    if ((s32 (*)(s32 *, ?, ?, s32))0x0F801168(&sp394, 0x24, 1, arg0) != 1) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10000F88, 0x10000F9C);
        lbl_40d3c0(1);
    }
    if (sp394 != 0x13577531) {
        (? (*)(?, ?))0x0F801150(0x100036B4, 0x10000FBC);
        return NULL;
    }
    if (sp398 != 0x10002) {
        (? (*)(?, ?))0x0F801150(0x100036B4, 0x10000FE4);
        return NULL;
    }
    if (sp39C != 0x10) {
        (? (*)(?, ?))0x0F801150(0x100036B4, 0x10001010);
        return NULL;
    }
    if (sp3A0 != 0xC) {
        (? (*)(?, ?))0x0F801150(0x100036B4, 0x1000103C);
        return NULL;
    }
    if ((sp3A4 <= 0) || (sp3A4 >= 0xC9)) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x1000106C, 0x10001080);
        lbl_40d3c0(1);
    }
    if ((s32 (*)(? *, ?, s32, s32))0x0F801168(&sp74, 4, sp3A4, arg0) != sp3A4) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100010A0, 0x100010B4);
        lbl_40d3c0(1);
    }
    temp_v0 = (s32 *(*)(s32))0x0F801208(sp3A4 * 4);
    sp70 = temp_v0;
    if (temp_v0 == NULL) {
        lbl_4092d4((void *)0x100010D8);
    }
    temp_v0_2 = (void *(*)(s32))0x0F801208(sp3B0 * 0xC);
    sp6C = temp_v0_2;
    if (temp_v0_2 == NULL) {
        lbl_4092d4((void *)0x100010EC);
    }
    temp_v0_3 = (s32 (*)(s32))0x0F801208((sp3B4 * 4) + 0xC);
    var_v1 = temp_v0_3;
    if (temp_v0_3 == 0) {
        sp68 = var_v1;
        lbl_4092d4((void *)0x10001100);
    }
    var_v0 = var_v1 & 0xF;
    if (var_v0 == 4) {
        var_v1 += 0xC;
        goto block_32;
    }
    if (var_v0 == 8) {
        var_v1 += 8;
        goto block_32;
    }
    if (var_v0 == 0xC) {
        var_v1 += 4;
block_32:
        var_v0 = var_v1 & 0xF;
    }
    if (var_v0 == 0) {
        sp68 = var_v1;
    } else {
        sp68 = var_v1;
        (? (*)(?, ?, s32))0x0F801150(0x100036B4, 0x10001114, var_v1);
    }
    sp60 = 0;
    if (sp3A4 > 0) {
        var_s3_2 = sp70;
        var_s4_2 = &arg0;
        do {
            var_s2 = 0;
            *var_s3_2 = lbl_40a400();
            if (var_s4_2->unk-344 > 0) {
                do {
                    temp_v0_5 = (void *(*)(?))0x0F801208(0x10);
                    if (temp_v0_5 == NULL) {
                        lbl_4092d4((void *)0x10001144);
                    }
                    if ((s32 (*)(void *, ?, ?, s32))0x0F801168(temp_v0_5, 0x10, 1, arg0) != 1) {
                        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001150, 0x10001164);
                        lbl_40d3c0(1);
                    }
                    temp_lo = (s32) (temp_v0_5->unk8 - sp3A8) / 12;
                    if ((temp_lo < 0) || (var_t5 = temp_lo * 4, ((temp_lo < sp3B0) == 0))) {
                        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001184, 0x10001198);
                        lbl_40d3c0(1);
                        var_t5 = temp_lo * 4;
                    }
                    temp_v0_5->unk8 = (void *) (sp6C + ((var_t5 - temp_lo) * 4));
                    temp_v0_5->unk4 = -1;
                    lbl_40a6d4(*var_s3_2, temp_v0_5);
                    var_s2 += 1;
                } while (var_s2 < var_s4_2->unk-344);
            }
            temp_v0_4 = sp60 + 1;
            sp60 = temp_v0_4;
            var_s3_2 += 4;
            var_s4_2 += 4;
        } while (temp_v0_4 < sp3A4);
        var_s1 = sp34;
        var_s3 = sp30;
        var_s4 = sp2C;
        var_s5 = sp28;
        var_s6 = sp24;
        sp60 = 0;
    }
    if ((s32 (*)(void *, ?, s32, s32))0x0F801168(sp6C, 0xC, sp3B0, arg0) != sp3B0) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100011BC, 0x100011D0);
        lbl_40d3c0(1);
    }
    if ((s32 (*)(s32, ?, s32, s32))0x0F801168(sp68, 4, sp3B4, arg0) != sp3B4) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100011F4, 0x10001208);
        lbl_40d3c0(1);
    }
    var_s2_2 = sp6C;
    if (sp3B0 > 0) {
        sp30 = var_s3;
        sp2C = var_s4;
        sp28 = var_s5;
        sp24 = var_s6;
        sp34 = var_s1;
        do {
            temp_v0_6 = var_s2_2->unk0;
            if (temp_v0_6 != NULL) {
                temp_lo_2 = (s32) (temp_v0_6 - sp3A8) / 12;
                if ((temp_lo_2 < 0) || (var_t5_2 = temp_lo_2 * 4, ((temp_lo_2 < sp3B0) == 0))) {
                    (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001228, 0x1000123C);
                    lbl_40d3c0(1);
                    var_t5_2 = temp_lo_2 * 4;
                }
                var_s2_2->unk0 = (void *) (sp6C + ((var_t5_2 - temp_lo_2) * 4));
            }
            temp_v0_7 = var_s2_2->unk4;
            if (temp_v0_7 != 0) {
                temp_s0 = temp_v0_7 - sp3AC;
                var_at = temp_s0;
                if (temp_s0 < 0) {
                    var_at += 3;
                }
                temp_s0_2 = var_at >> 2;
                if ((temp_s0_2 < 0) || (temp_s0_2 >= sp3B4)) {
                    (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001260, 0x10001274);
                    lbl_40d3c0(1);
                }
                var_s2_2->unk4 = (s32) (sp68 + (temp_s0_2 * 4));
            }
            temp_t3 = sp60 + 1;
            sp60 = temp_t3;
            var_s2_2 += 0xC;
        } while (temp_t3 < sp3B0);
    }
    *arg1 = sp3A4;
    return sp70;
}

s32 compute_bounding_box(void) {
    s32 var_v0;

    var_v0 = 0x101;
    if (lbl_4055d0(0x10001290) != 0) {
        var_v0 = *(s32 *)0x10001290;
    }
    return var_v0;
}

void compute_entity_bbox(s32 arg0) {
    (? (*)(?, s32, ?, s32))0x0F801150(0x100036B4, saved_reg_gp - 0x7D00, 0x10003ED0, arg0);
    (? (*)(?, ?, s32, s32))0x0F801150(0x100036B4, 0x100012A0, *(s32 *)0x1000129C, *(s32 *)0x10001298);
    (? (*)(?, ?, s32))0x0F801150(0x100036B4, 0x100012B8, saved_reg_gp->unk-7A80);
}

s32 compute_far_clip(void *arg0) {
    s32 sp54;
    s32 sp40;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_t0;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *var_v0;
    u8 var_v1;

case 0x122:
    temp_v0 = lbl_4057d4(arg0);
    var_t0 = temp_v0;
    if (temp_v0 == 0) {
        return 0;
    }
    temp_v0_2 = arg0->unk0;
    switch (temp_v0_2) {                            /* irregular */
    case 0x121:
        sp54 = var_t0;
        temp_v0_3 = lbl_405ce8(arg0->unk4);
        if (temp_v0_3 != 0) {
            arg0->unk0 = temp_v0_3;
        } else {
            sp54 = var_t0;
            (? (*)(?, ?, ?, u8 *, s32, s32))0x0F801150(0x100036B4, 0x100013F4, 0x10003ED0, arg0->unk4, arg0->unkC, arg0->unk8);
        }
block_23:
    default:
        return var_t0;
    case 0x120:
        temp_s0 = arg0->unk4;
        var_a1 = 0;
        var_v1 = *temp_s0;
        var_v0 = temp_s0 + 1;
        if (var_v1 != 0) {
loop_10:
            if (var_v1 == 0x2E) {
                var_a1 = 1;
            } else {
                var_v1 = *var_v0;
                var_v0 += 1;
                if (var_v1 != 0) {
                    goto loop_10;
                }
            }
        }
        if (var_a1 != 0) {
            sp54 = var_t0;
            saved_reg_gp->unk-7A7C = (f32) lbl_40d830(temp_s0, &sp40);
            temp_s0_2 = arg0->unk4;
            var_t0 = sp54;
            if (sp40 == temp_s0_2) {
                (? (*)(?, ?, ?, u8 *, s32, s32))0x0F801150(0x100036B4, 0x10001430, 0x10003ED0, temp_s0_2, arg0->unkC, arg0->unk8);
            }
            arg0->unk0 = 0x119;
        } else {
            sp54 = var_t0;
            saved_reg_gp->unk-7A7C = (bitwise f32) lbl_40dcc0(temp_s0, &sp40, 0);
            temp_s0_3 = arg0->unk4;
            var_t0 = sp54;
            if (sp40 == temp_s0_3) {
                (? (*)(?, ?, ?, u8 *, s32, s32))0x0F801150(0x100036B4, 0x10001460, 0x10003ED0, temp_s0_3, arg0->unkC, arg0->unk8);
            }
            arg0->unk0 = 0x118;
        }
        goto block_23;
    }
}

s32 build_sorted_list(void *arg0) {
    s8 sp48;
    s32 var_fp;
    s32 var_s2;
    s32 var_s7;
    s8 temp_v0;
    s8 temp_v0_3;
    s8 temp_v0_4;
    s8 temp_v0_5;
    s8 var_s0;
    s8 var_s1;
    s8 var_s1_2;
    s8 var_v0;
    u8 temp_v0_2;
    void *var_a0;
    void *var_t0;
    void *var_t1;
    void *var_t7;

    var_fp = 0;
    var_s7 = 0;
    var_s2 = 0;
    temp_v0 = lbl_405df8();
    var_s1 = temp_v0;
    if (temp_v0 != -1) {
loop_2:
        if (var_s2 >= 0x100) {
            (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001494, 0x100014A8);
            lbl_40d3c0(1);
        }
        temp_v0_2 = (var_s1 + 0x10000000)->unk32E1;
        if (temp_v0_2 & 3) {
            if (var_fp != 0) {
                (sp + var_s2)->unk48 = var_s1;
                var_s2 += 1;
                goto block_73;
            }
            if (var_s7 != 0) {
                if ((temp_v0_2 & 0x80) || (var_s1 == 0x78) || (var_s1 == 0x58)) {
                    (sp + var_s2)->unk48 = var_s1;
                    var_s2 += 1;
                    goto block_73;
                }
                (? (*)(?, s8, s8))0x0F801250(0x100014C8, var_s1, var_s1);
                lbl_405ed8(0x100014E8);
                return 0;
            }
            var_fp = 1;
            var_s2 = 1;
            lbl_405dd0(arg0 + 0xC, arg0 + 8);
            sp48 = var_s1;
            goto block_73;
        }
        if (temp_v0_2 & 4) {
            var_t1 = sp + var_s2;
            if (var_fp == 0) {
                if (var_s7 != 0) {
                    var_t1 = sp + var_s2;
                    goto block_19;
                }
                var_s2 = 1;
                var_s7 = 1;
                lbl_405dd0(arg0 + 0xC, arg0 + 8);
                sp48 = var_s1;
            } else {
block_19:
                var_t1->unk48 = var_s1;
                var_s2 += 1;
            }
            goto block_73;
        }
        if (temp_v0_2 & 0x10) {
            if ((var_s7 != 0) && (var_s1 == 0x2E)) {
                (sp + var_s2)->unk48 = var_s1;
                var_s2 += 1;
                goto block_73;
            }
            if (var_fp == 0) {
                if (var_s7 != 0) {
                    var_a0 = arg0 + 0xC;
                    if (var_s1 != 0x2E) {
                        goto block_30;
                    }
                    goto block_37;
                }
                var_a0 = arg0 + 0xC;
block_37:
                lbl_405dd0(var_a0, arg0 + 8);
                arg0->unk4->unk0 = var_s1;
                arg0->unk4->unk1 = 0;
                switch (var_s1) {                   /* irregular */
                case 0x7B:
                    arg0->unk0 = 0x11B;
                    goto block_84;
                case 0x7D:
                    arg0->unk0 = 0x11C;
                    goto block_84;
                case 0x5B:
                    arg0->unk0 = 0x11D;
                    goto block_84;
                case 0x5D:
                    arg0->unk0 = 0x11E;
                    goto block_84;
                case 0x2D:
                    arg0->unk0 = 0x117;
                    goto block_84;
                case 0x2F:
                    temp_v0_3 = lbl_405df8();
                    if (temp_v0_3 != 0x2A) {
                        lbl_405de8(temp_v0_3);
                        arg0->unk0 = 0x11F;
                        goto block_84;
                    }
                    temp_v0_4 = lbl_405df8();
                    var_s0 = temp_v0_4;
                    if (temp_v0_4 == -1) {
                        lbl_405ed8(0x10001514);
                    }
                    var_v0 = lbl_405df8();
                    var_s1_2 = var_v0;
                    if (var_v0 != -1) {
loop_55:
                        if ((var_s0 == 0x2A) && (var_v0 == 0x2F)) {
                            arg0->unk0 = 0x122;
                            goto block_84;
                        }
                        var_s0 = var_s1_2;
                        var_v0 = lbl_405df8();
                        var_s1_2 = var_v0;
                        if (var_v0 == -1) {
                            goto block_59;
                        }
                        goto loop_55;
                    }
block_59:
                    lbl_405ed8(0x10001538);
                    goto block_73;
                default:
                    lbl_405ed8(0x1000155C);
                    return 0;
                }
            } else {
block_30:
                lbl_405de8(var_s1);
                (var_s2 + &arg0)->unk-110 = 0;
                (? (*)(void *, s8 *))0x0F8012F0(arg0->unk4, &sp48);
                if (var_fp != 0) {
                    arg0->unk0 = 0x121;
                } else if (var_s7 != 0) {
                    arg0->unk0 = 0x120;
                }
                goto block_84;
            }
        } else {
            if (temp_v0_2 & 8) {
                var_t7 = sp + var_s2;
                if (var_fp == 0) {
                    if (var_s7 != 0) {
                        var_t7 = sp + var_s2;
                        goto block_66;
                    }
block_73:
                    temp_v0_5 = lbl_405df8();
                    var_s1 = temp_v0_5;
                    if (temp_v0_5 == -1) {
                        goto block_75;
                    }
                    goto loop_2;
                }
block_66:
                var_t7->unk48 = 0;
                (? (*)(void *, s8 *))0x0F8012F0(arg0->unk4, &sp48);
                if (var_fp != 0) {
                    arg0->unk0 = 0x121;
                } else if (var_s7 != 0) {
                    arg0->unk0 = 0x120;
                }
                goto block_84;
            }
            lbl_405dd0(arg0 + 0xC, arg0 + 8);
            lbl_405ed8(0x10001580);
            return 0;
        }
    } else {
block_75:
        var_t0 = sp + var_s2;
        if (var_fp == 0) {
            if (var_s7 != 0) {
                var_t0 = sp + var_s2;
                goto block_78;
            }
            arg0->unk0 = 0;
            arg0->unk4->unk0 = 0;
            lbl_405dd0(arg0 + 0xC, arg0 + 8);
        } else {
block_78:
            var_t0->unk48 = 0;
            (? (*)(void *, s8 *))0x0F8012F0(arg0->unk4, &sp48);
            if (var_fp != 0) {
                arg0->unk0 = 0x121;
            } else if (var_s7 != 0) {
                arg0->unk0 = 0x120;
            }
        }
block_84:
        return 1;
    }
}

s32 filter_display_list(s32 arg0) {
    s32 temp_a1;
    s32 temp_t7;
    void *var_s0;

    if (*(s32 *)0x100012D4 != 0) {
        var_s0 = (void *)0x100012D0;
loop_2:
        temp_a1 = var_s0->unk0;
        if ((arg0 == temp_a1) || ((s32 (*)(s32, s32))0x0F8012E8(arg0, temp_a1) == 0)) {
            return var_s0->unk4;
        }
        temp_t7 = var_s0->unkC;
        var_s0 += 8;
        if (temp_t7 == 0) {
            goto block_7;
        }
        goto loop_2;
    }
block_7:
    return 0;
}

void set_near_far(s32 arg0) {
    (? (*)(?, s32))0x0F801250(0x100015A0, arg0);
}

void set_initial_position(s32 arg0) {
    s32 var_v0;
    void *temp_t3;

    var_v0 = saved_reg_gp->unk-7E98->unk140;
    if (var_v0 >= 0x7A120) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100015B0, 0x100015C4);
        lbl_40d3c0(1);
        var_v0 = saved_reg_gp->unk-7E98->unk140;
    }
    *(saved_reg_gp->unk-7E98->unk108 + (var_v0 * 4)) = arg0;
    temp_t3 = saved_reg_gp->unk-7E98;
    temp_t3->unk140 = (s32) (temp_t3->unk140 + 1);
}

void mat4_set_translate(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    s32 var_v0;
    void *temp_t1;
    void *temp_t8;

    sp1C = arg0;
    sp20 = arg1;
    sp24 = arg2;
    var_v0 = saved_reg_gp->unk-7E98->unk144;
    if (var_v0 > 0) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100015D0, 0x100015E4);
        lbl_40d3c0(1);
        var_v0 = saved_reg_gp->unk-7E98->unk144;
    }
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_t1 = temp_t8->unk10C + (var_v0 * 0xC);
    temp_t1->unk0 = (f32) sp1C.unk0;
    temp_t1->unk4 = (s32) sp1C.unk4;
    temp_t1->unk8 = (s32) sp1C.unk8;
    temp_t8->unk144 = (s32) (temp_t8->unk144 + 1);
}

void mat4_set_rotate_x(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    s32 var_v0;
    void *temp_t1;
    void *temp_t8;

    sp1C = arg0;
    sp20 = arg1;
    sp24 = arg2;
    var_v0 = saved_reg_gp->unk-7E98->unk148;
    if (var_v0 >= 0x61A8) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100015F0, 0x10001604);
        lbl_40d3c0(1);
        var_v0 = saved_reg_gp->unk-7E98->unk148;
    }
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_t1 = temp_t8->unk114 + (var_v0 * 0xC);
    temp_t1->unk0 = (f32) sp1C.unk0;
    temp_t1->unk4 = (s32) sp1C.unk4;
    temp_t1->unk8 = (s32) sp1C.unk8;
    temp_t8->unk148 = (s32) (temp_t8->unk148 + 1);
}

void mat4_set_rotate_y(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    s32 var_v0;
    void *temp_t1;
    void *temp_t8;

    sp1C = arg0;
    sp20 = arg1;
    sp24 = arg2;
    var_v0 = saved_reg_gp->unk-7E98->unk14C;
    if (var_v0 >= 0x61A80) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001610, 0x10001624);
        lbl_40d3c0(1);
        var_v0 = saved_reg_gp->unk-7E98->unk14C;
    }
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_t1 = temp_t8->unk110 + (var_v0 * 0xC);
    temp_t1->unk0 = (f32) sp1C.unk0;
    temp_t1->unk4 = (s32) sp1C.unk4;
    temp_t1->unk8 = (s32) sp1C.unk8;
    temp_t8->unk14C = (s32) (temp_t8->unk14C + 1);
}

/*
Decompilation failure in function mat4_set_rotate_z:

Unable to determine jump table for jr instruction at stdin line 6331.

There must be a read of a variable before the instruction
which has a name starting with with "jtbl"/"jpt_"/"lbl_"/"jumptable_".
*/

s32 mat4_mul(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    s32 sp1C;
    s32 var_v1;
    void *temp_t1;
    void *temp_t8;

    sp20 = arg0;
    sp24 = arg1;
    sp2C = arg3;
    sp28 = arg2;
    var_v1 = saved_reg_gp->unk-7E98->unk150;
    sp1C = var_v1;
    if (var_v1 >= 0x14) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001678, 0x1000168C);
        lbl_40d3c0(1);
        var_v1 = saved_reg_gp->unk-7E98->unk150;
    }
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_t1 = temp_t8->unk118 + (var_v1 * 0x10);
    temp_t1->unk0 = (f32) sp20.unk0;
    temp_t1->unk4 = (s32) sp20.unk4;
    temp_t1->unk8 = (s32) sp20.unk8;
    temp_t1->unkC = (s32) sp20.unkC;
    temp_t8->unk150 = (s32) (temp_t8->unk150 + 1);
    return sp1C;
}

s32 mat4_transform_point(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s32 sp20;
    s32 var_v1;
    void *temp_t1;
    void *temp_t8;

    sp24 = arg0;
    sp28 = arg1;
    sp2C = arg2;
    var_v1 = saved_reg_gp->unk-7E98->unk154;
    sp20 = var_v1;
    if (var_v1 >= 0x14) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x1000169C, 0x100016B0);
        lbl_40d3c0(1);
        var_v1 = saved_reg_gp->unk-7E98->unk154;
    }
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_t1 = temp_t8->unk11C + (var_v1 * 0xC);
    temp_t1->unk0 = (f32) sp24.unk0;
    temp_t1->unk4 = (s32) sp24.unk4;
    temp_t1->unk8 = (s32) sp24.unk8;
    temp_t8->unk154 = (s32) (temp_t8->unk154 + 1);
    return sp20;
}

s32 mat4_mul2(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s32 sp20;
    s32 var_v1;
    void *temp_t1;
    void *temp_t8;

    sp24 = arg0;
    sp28 = arg1;
    sp2C = arg2;
    var_v1 = saved_reg_gp->unk-7E98->unk158;
    sp20 = var_v1;
    if (var_v1 >= 0x14) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100016BC, 0x100016D0);
        lbl_40d3c0(1);
        var_v1 = saved_reg_gp->unk-7E98->unk158;
    }
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_t1 = temp_t8->unk120 + (var_v1 * 0xC);
    temp_t1->unk0 = (f32) sp24.unk0;
    temp_t1->unk4 = (s32) sp24.unk4;
    temp_t1->unk8 = (s32) sp24.unk8;
    temp_t8->unk158 = (s32) (temp_t8->unk158 + 1);
    return sp20;
}

void build_view_matrix(s32 arg0) {
    void **sp44;
    void **sp40;
    ? sp2C;
    s32 var_v0;
    void **temp_v0;
    void *temp_a0;
    void *temp_t1;
    void *temp_t2;
    void *temp_t4;
    void *temp_t5;
    void *temp_t8;
    void *temp_v1;
    void *var_a1;
    void *var_a2;

    if (lbl_40ade4(arg0) < 3) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100016E0, 0x100016F4);
        lbl_40d3c0(1);
    }
    sp44 = lbl_40a8e0(arg0);
    sp40 = lbl_40a918(arg0);
    temp_v0 = lbl_40a918(arg0);
    var_a1 = NULL;
    temp_a0 = *sp44;
    var_a2 = NULL;
    switch (temp_a0) {                              /* switch 2; irregular */
    case 0x103:                                     /* switch 2 */
        /* fallthrough */
    case 0x107:                                     /* switch 2 */
        if (*sp40 == (void *)0x110) {
            temp_v1 = *temp_v0;
            switch (temp_v1) {                      /* switch 1; irregular */
            case 0x110:                             /* switch 1 */
                var_a1 = temp_a0;
                break;
            case 0x103:                             /* switch 1 */
            case 0x107:                             /* switch 1 */
                var_a2 = temp_a0;
                break;
            }
        default:                                    /* switch 2 */
            if (lbl_4067e4(arg0, var_a1, var_a2, &sp2C) == 0) {
                temp_t2 = saved_reg_gp->unk-7E98;
                (? (*)(?, s32))0x0F801250(0x1000173C, temp_t2->unk160 - temp_t2->unk188);
                temp_t5 = saved_reg_gp->unk-7E98;
                temp_t5->unk160 = (s32) (temp_t5->unk160 + 1);
                return;
            }
            var_v0 = saved_reg_gp->unk-7E98->unk160;
            if (var_v0 >= 0x30D40) {
                (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x1000176C, 0x10001780);
                lbl_40d3c0(1);
                var_v0 = saved_reg_gp->unk-7E98->unk160;
            }
            temp_t1 = saved_reg_gp->unk-7E98;
            temp_t4 = temp_t1->unk128 + (var_v0 * 0x10);
            temp_t4->unk0 = (s32) sp2C.unk0;
            temp_t4->unk4 = (s32) sp2C.unk4;
            temp_t4->unk8 = (s32) sp2C.unk8;
            temp_t4->unkC = (s32) sp2C.unkC;
            temp_t1->unk160 = (s32) (temp_t1->unk160 + 1);
            return;
        }
        temp_t8 = saved_reg_gp->unk-7E98;
        (? (*)(?, s32, ?, ?))0x0F801250(0x10001710, temp_t8->unk160 - temp_t8->unk188, 0, 0x103);
        return;
    }
}

s32 compute_initial_view(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 sp204C;
    ? sp48;
    ? *var_s1;
    s32 *var_v0_2;
    s32 *var_v0_3;
    s32 *var_v1_2;
    s32 temp_a0_2;
    s32 temp_t2;
    s32 temp_t7_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_at;
    s32 var_s0;
    void **var_a3;
    void **var_v0;
    void *temp_a0;
    void *temp_t0;
    void *temp_t1;
    void *temp_t4;
    void *temp_t7;
    void *temp_t8;
    void *var_v1;

    arg3->unkC = -1;
    if ((arg1 != 0) && (arg2 != 0)) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001790, 0x100017A4);
        lbl_40d3c0(1);
    }
    if ((arg1 == 0) && (arg2 == 0)) {
        arg3->unk0 = 0x408748;
    }
    switch (arg1) {                                 /* switch 1; irregular */
    case 0x0:                                       /* switch 1 */
        break;
    case 0x103:                                     /* switch 1 */
        arg3->unk0 = 0x4089A0;
        arg3->unkC = 3;
        break;
    case 0x107:                                     /* switch 1 */
        arg3->unk0 = 0x408BF0;
        arg3->unkC = 5;
        break;
    }
    switch (arg2) {                                 /* switch 2; irregular */
    case 0x0:                                       /* switch 2 */
        break;
    case 0x103:                                     /* switch 2 */
        arg3->unk0 = 0x408840;
        arg3->unkC = 2;
        break;
    case 0x107:                                     /* switch 2 */
        arg3->unk0 = 0x408AB0;
        arg3->unkC = 4;
        break;
    }
    var_s1 = &sp48;
    var_s0 = 0;
    var_v0 = lbl_40a8e0(arg0);
    var_a3 = var_v0;
    if (var_v0 != NULL) {
loop_20:
        if ((var_s0 == 0) && (arg1 != 0) && (arg1 != var_v0->unk0)) {
            temp_t7 = saved_reg_gp->unk-7E98;
            (? (*)(?, s32))0x0F801250(0x100017B4, temp_t7->unk160 - temp_t7->unk188);
            return 0;
        }
        temp_a0 = var_v0->unk0;
        if (((var_s0 % 2) == 0) && (arg2 != 0) && (arg2 != temp_a0)) {
            temp_t1 = saved_reg_gp->unk-7E98;
            (? (*)(?, s32))0x0F801250(0x100017E0, temp_t1->unk160 - temp_t1->unk188);
            return 0;
        }
        switch (temp_a0) {                          /* switch 3; irregular */
        case 0x110:                                 /* switch 3 */
            temp_t4 = var_v0->unk8;
            var_s1 += 0xC;
            var_s1->unk-C = (s32) temp_t4->unk0;
            var_s1->unk-8 = (s32) temp_t4->unk4;
            var_s1->unk-4 = (s32) temp_t4->unk8;
            break;
        case 0x103:                                 /* switch 3 */
            var_s1 += 4;
            var_s1->unk-4 = (s32) var_v0->unk8->unk0;
            break;
        case 0x107:                                 /* switch 3 */
            temp_t8 = var_v0->unk8;
            var_s1 += 0xC;
            var_s1->unk-C = (s32) temp_t8->unk0;
            var_s1->unk-8 = (s32) temp_t8->unk4;
            var_s1->unk-4 = (s32) temp_t8->unk8;
            break;
        default:                                    /* switch 3 */
            temp_t0 = saved_reg_gp->unk-7E98;
            lbl_4092d4((void *)0x10001864, *var_a3, temp_t0->unk160 - temp_t0->unk188, var_a3);
            break;
        }
        var_s0 += 1;
        var_v0 = lbl_40a918(arg0);
        var_a3 = var_v0;
        if (var_v0 == NULL) {
            var_s0 = 0;
            goto block_38;
        }
        goto loop_20;
    }
block_38:
    temp_v0 = var_s1 - &sp48;
    var_at = temp_v0;
    if (temp_v0 < 0) {
        var_at += 3;
    }
    temp_v0_2 = var_at >> 2;
    sp204C = temp_v0_2;
    temp_v0_3 = (s32 (*)(s32, s32))0x0F801208(temp_v0_2 * 4, temp_v0_2);
    if (temp_v0_3 == 0) {
        sp204C = temp_v0_2;
        lbl_4092d4((void *)0x1000189C, (void *) temp_v0_2);
    }
    if (temp_v0_2 > 0) {
        temp_a0_2 = temp_v0_2 & 3;
        if (temp_a0_2 != 0) {
            var_v0_2 = &(&arg0)[0];
            var_v1 = temp_v0_3 + (0 * 4);
            do {
                temp_t7_2 = var_v0_2->unk-2008;
                var_s0 += 1;
                var_v1 += 4;
                var_v0_2 += 4;
                var_v1->unk-4 = temp_t7_2;
            } while (temp_a0_2 != var_s0);
            if (var_s0 != temp_v0_2) {
                goto block_48;
            }
        } else {
block_48:
            var_v0_3 = &(&arg0)[var_s0];
            var_v1_2 = temp_v0_3 + (var_s0 * 4);
            do {
                temp_t2 = var_v0_3->unk-2008;
                var_v0_3 += 0x10;
                *var_v1_2 = temp_t2;
                var_v1_2 += 0x10;
                var_v1_2->unk-C = (s32) var_v0_3->unk-2014;
                var_v1_2->unk-8 = (s32) var_v0_3->unk-2010;
                var_v1_2->unk-4 = (s32) var_v0_3->unk-200C;
            } while (var_v0_3 != &(&arg0)[temp_v0_2]);
        }
    }
    arg3->unk4 = temp_v0_3;
    arg3->unk8 = temp_v0_2;
    return 1;
}

void apply_transforms(s32 arg0) {
    ? sp2C;
    s32 var_v0;
    void **temp_v0;
    void *temp_t3;
    void *temp_t6;
    void *temp_t8;
    void *temp_v1;

    if (lbl_40ade4(arg0) >= 3) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100018B4, 0x100018C8);
        lbl_40d3c0(1);
    }
    temp_v0 = lbl_40a8e0(arg0);
    temp_v1 = *temp_v0;
    switch (temp_v1) {                              /* irregular */
    case 0x110:
        if (lbl_40ade4(arg0) != 1) {
            (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x100018E4, 0x100018F8);
            lbl_40d3c0(1);
        case 0x103:
        case 0x107:
        }
        break;
    default:
        lbl_4092d4((void *)0x10001924, *temp_v0, saved_reg_gp->unk-7E98->unk168, temp_v0);
        break;
    }
    if (lbl_406d60(arg0, &sp2C) == 0) {
        (? (*)(?, s32))0x0F801250(0x10001954, saved_reg_gp->unk-7E98->unk168);
        temp_t8 = saved_reg_gp->unk-7E98;
        temp_t8->unk168 = (s32) (temp_t8->unk168 + 1);
        return;
    }
    var_v0 = saved_reg_gp->unk-7E98->unk168;
    if (var_v0 >= 0xFA0) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001980, 0x10001994);
        lbl_40d3c0(1);
        var_v0 = saved_reg_gp->unk-7E98->unk168;
    }
    temp_t3 = saved_reg_gp->unk-7E98;
    temp_t6 = temp_t3->unk130 + (var_v0 * 0x10);
    temp_t6->unk0 = (s32) sp2C.unk0;
    temp_t6->unk4 = (s32) sp2C.unk4;
    temp_t6->unk8 = (s32) sp2C.unk8;
    temp_t6->unkC = (s32) sp2C.unkC;
    temp_t3->unk168 = (s32) (temp_t3->unk168 + 1);
}

s32 parse_transform_string(s32 arg0, void *arg1) {
    ? sp44;
    ? *var_s1;
    s32 *var_v0_2;
    s32 *var_v0_3;
    s32 *var_v1_2;
    s32 temp_a0;
    s32 temp_t2_3;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_a1;
    s32 var_at;
    void **temp_v0;
    void **var_s0;
    void **var_v0;
    void *temp_t0;
    void *temp_t2;
    void *temp_t2_2;
    void *temp_v1;
    void *temp_v1_2;
    void *var_v1;

    arg1->unkC = -1;
    temp_v0 = lbl_40a8e0(arg0);
    temp_v1 = *temp_v0;
    if (temp_v1 != (void *)0x103) {
        if (temp_v1 != (void *)0x107) {
            if (temp_v1 == (void *)0x110) {
                arg1->unk0 = 0x408D00;
            } else {
                lbl_4092d4((void *)0x100019A0, *temp_v0, saved_reg_gp->unk-7E98->unk168);
            }
        } else {
            arg1->unk0 = 0x408E34;
            arg1->unkC = 9;
        }
    } else {
        arg1->unk0 = 0x408D94;
        arg1->unkC = 8;
    }
    var_s1 = &sp44;
    var_v0 = lbl_40a8e0(arg0);
    var_s0 = var_v0;
    if (var_v0 != NULL) {
        do {
            temp_v1_2 = var_v0->unk0;
            switch (temp_v1_2) {                    /* irregular */
            case 0x110:
                if (var_v0->unk4 >= saved_reg_gp->unk-7E98->unk14C) {
                    lbl_4092d4((void *)0x100019CC, var_s0->unk4);
                }
                temp_t2 = var_s0->unk4;
                var_s1->unk0 = (s32) (saved_reg_gp->unk-7E98->unk110 + ((((s32) temp_t2 * 4) - temp_t2) * 4));
                var_s1 += 4;
                break;
            case 0x103:
                if (var_v0->unk4 >= saved_reg_gp->unk-7E98->unk140) {
                    lbl_4092d4((void *)0x100019E0, var_s0->unk4);
                }
                var_s1 += 4;
                var_s1->unk-4 = (s32) *(saved_reg_gp->unk-7E98->unk108 + ((s32) var_s0->unk4 * 4));
                break;
            case 0x107:
                if (var_v0->unk4 >= saved_reg_gp->unk-7E98->unk148) {
                    lbl_4092d4((void *)0x100019F8, var_s0->unk4);
                }
                temp_t0 = var_s0->unk4;
                temp_t2_2 = saved_reg_gp->unk-7E98->unk114 + ((((s32) temp_t0 * 4) - temp_t0) * 4);
                var_s1->unk0 = (s32) temp_t2_2->unk0;
                var_s1->unk4 = (s32) temp_t2_2->unk4;
                var_s1 += 0xC;
                var_s1->unk-4 = (s32) temp_t2_2->unk8;
                break;
            }
            var_v0 = lbl_40a918(arg0);
            var_s0 = var_v0;
        } while (var_v0 != NULL);
    }
    temp_v0_2 = var_s1 - &sp44;
    var_at = temp_v0_2;
    if (temp_v0_2 < 0) {
        var_at += 3;
    }
    temp_v0_3 = var_at >> 2;
    temp_v0_4 = (s32 (*)(s32))0x0F801208(temp_v0_3 * 4);
    if (temp_v0_4 == 0) {
        lbl_4092d4((void *)0x10001A48);
    }
    var_a1 = 0;
    if (temp_v0_3 > 0) {
        temp_a0 = temp_v0_3 & 3;
        if (temp_a0 != 0) {
            var_v0_2 = &(&arg0)[0];
            var_v1 = temp_v0_4 + (0 * 4);
            do {
                temp_t8 = var_v0_2->unk-14;
                var_a1 += 1;
                var_v1 += 4;
                var_v0_2 += 4;
                var_v1->unk-4 = temp_t8;
            } while (temp_a0 != var_a1);
            if (var_a1 != temp_v0_3) {
                goto block_32;
            }
        } else {
block_32:
            var_v0_3 = &(&arg0)[var_a1];
            var_v1_2 = temp_v0_4 + (var_a1 * 4);
            do {
                temp_t2_3 = var_v0_3->unk-14;
                var_v0_3 += 0x10;
                *var_v1_2 = temp_t2_3;
                var_v1_2 += 0x10;
                var_v1_2->unk-C = (s32) var_v0_3->unk-20;
                var_v1_2->unk-8 = (s32) var_v0_3->unk-1C;
                var_v1_2->unk-4 = (s32) var_v0_3->unk-18;
            } while (var_v0_3 != &(&arg0)[temp_v0_3]);
        }
    }
    arg1->unk4 = temp_v0_4;
    arg1->unk8 = temp_v0_3;
    return 1;
}

void apply_material_transforms(s32 arg0) {
    ? sp5C;
    s32 temp_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s6;
    void **var_s1;
    void **var_v0;
    void *temp_s5;
    void *temp_t6;
    void *temp_t9;
    void *var_v0_2;

    temp_s5 = *lbl_40a8e0(arg0);
    var_s2 = 0;
    var_s6 = 0;
    var_s3 = 0;
    var_v0 = lbl_40a8e0(arg0);
    var_s1 = var_v0;
    if (var_v0 == NULL) {

    } else {
        do {
            if (temp_s5 == (void *)0x110) {
                var_s2 += 1;
                if (*var_v0 != (void *)0x110) {
                    lbl_4092d4((void *)0x10001A5C, saved_reg_gp->unk-7E98->unk164);
                }
            } else {
                temp_s0 = var_s3 % 2;
                if (temp_s0 == 0) {
                    var_s6 += 1;
                    if (temp_s5 != *var_v0) {
                        lbl_4092d4((void *)0x10001A88, saved_reg_gp->unk-7E98->unk164);
                    }
                }
                if (temp_s0 == 1) {
                    var_s2 += 1;
                    if (*var_s1 != (void *)0x110) {
                        lbl_4092d4((void *)0x10001AB4, saved_reg_gp->unk-7E98->unk164);
                    }
                }
            }
            var_s3 += 1;
            var_v0 = lbl_40a918(arg0);
            var_s1 = var_v0;
        } while (var_v0 != NULL);
    }
    if ((var_s2 < 2) || (var_s2 >= 0x101) || ((temp_s5 != (void *)0x110) && (var_s2 != var_s6))) {
        lbl_4092d4((void *)0x10001AE0, saved_reg_gp->unk-7E98->unk164);
    }
    if (lbl_4072ac(arg0, &sp5C) == 0) {
        lbl_4092d4((void *)0x10001B0C, saved_reg_gp->unk-7E98->unk164);
    }
    var_v0_2 = saved_reg_gp->unk-7E98->unk164;
    if ((s32) var_v0_2 >= 0x186A0) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001B34, 0x10001B48);
        lbl_40d3c0(1);
        var_v0_2 = saved_reg_gp->unk-7E98->unk164;
    }
    temp_t6 = saved_reg_gp->unk-7E98;
    temp_t9 = temp_t6->unk12C + ((s32) var_v0_2 * 0x10);
    temp_t9->unk0 = (s32) sp5C.unk0;
    temp_t9->unk4 = (s32) sp5C.unk4;
    temp_t9->unk8 = (s32) sp5C.unk8;
    temp_t9->unkC = (s32) sp5C.unkC;
    temp_t6->unk164 = (void *) (temp_t6->unk164 + 1);
}

s32 load_binary_model(s32 arg0, void *arg1) {
    s32 sp1044;
    ? sp40;
    ? *var_s0;
    s32 *var_v0_2;
    s32 *var_v0_3;
    s32 *var_v1_2;
    s32 temp_a0;
    s32 temp_t0_2;
    s32 temp_t7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_at;
    void **var_v0;
    void *temp_t0;
    void *temp_t6;
    void *temp_v1;
    void *temp_v1_2;
    void *var_v1;

    arg1->unkC = -1;
    temp_v1 = *lbl_40a8e0(arg0);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0x110:                                     /* switch 1 */
        arg1->unk0 = 0x408ED0;
        break;
    case 0x103:                                     /* switch 1 */
        arg1->unk0 = 0x408F64;
        arg1->unkC = 6;
        break;
    case 0x107:                                     /* switch 1 */
        arg1->unk0 = 0x4090FC;
        arg1->unkC = 7;
        break;
    }
    var_s0 = &sp40;
    var_v0 = lbl_40a8e0(arg0);
    if (var_v0 != NULL) {
        do {
            temp_v1_2 = var_v0->unk0;
            switch (temp_v1_2) {                    /* switch 2; irregular */
            case 0x110:                             /* switch 2 */
                temp_t6 = var_v0->unk8;
                var_s0 += 0xC;
                var_s0->unk-C = (s32) temp_t6->unk0;
                var_s0->unk-8 = (s32) temp_t6->unk4;
                var_s0->unk-4 = (s32) temp_t6->unk8;
                break;
            case 0x103:                             /* switch 2 */
                var_s0 += 4;
                var_s0->unk-4 = (s32) var_v0->unk8->unk0;
                break;
            case 0x107:                             /* switch 2 */
                temp_t0 = var_v0->unk8;
                var_s0 += 0xC;
                var_s0->unk-C = (s32) temp_t0->unk0;
                var_s0->unk-8 = (s32) temp_t0->unk4;
                var_s0->unk-4 = (s32) temp_t0->unk8;
                break;
            }
            var_v0 = lbl_40a918(arg0);
        } while (var_v0 != NULL);
    }
    temp_v0 = var_s0 - &sp40;
    var_at = temp_v0;
    if (temp_v0 < 0) {
        var_at += 3;
    }
    temp_v0_2 = var_at >> 2;
    sp1044 = temp_v0_2;
    temp_v0_3 = (s32 (*)(s32))0x0F801208(temp_v0_2 * 4);
    if (temp_v0_3 == 0) {
        sp1044 = temp_v0_2;
        lbl_4092d4((void *)0x10001BAC);
    }
    var_a1 = 0;
    if (temp_v0_2 > 0) {
        temp_a0 = temp_v0_2 & 3;
        if (temp_a0 != 0) {
            var_v0_2 = &(&arg0)[0];
            var_v1 = temp_v0_3 + (0 * 4);
            do {
                temp_t7 = var_v0_2->unk-1008;
                var_a1 += 1;
                var_v1 += 4;
                var_v0_2 += 4;
                var_v1->unk-4 = temp_t7;
            } while (temp_a0 != var_a1);
            if (var_a1 != temp_v0_2) {
                goto block_28;
            }
        } else {
block_28:
            var_v0_3 = &(&arg0)[var_a1];
            var_v1_2 = temp_v0_3 + (var_a1 * 4);
            do {
                temp_t0_2 = var_v0_3->unk-1008;
                var_v0_3 += 0x10;
                *var_v1_2 = temp_t0_2;
                var_v1_2 += 0x10;
                var_v1_2->unk-C = (s32) var_v0_3->unk-1014;
                var_v1_2->unk-8 = (s32) var_v0_3->unk-1010;
                var_v1_2->unk-4 = (s32) var_v0_3->unk-100C;
            } while (var_v0_3 != &(&arg0)[temp_v0_2]);
        }
    }
    arg1->unk4 = temp_v0_3;
    arg1->unk8 = temp_v0_2;
    return 1;
}

/*
Decompilation failure in function write_binary_model:

Unable to determine jump table for jr instruction at stdin line 7591.

There must be a read of a variable before the instruction
which has a name starting with with "jtbl"/"jpt_"/"lbl_"/"jumptable_".
*/

void main_init_1(void) {
    s32 sp24;
    s32 var_v0;
    void *temp_t0;
    void *temp_t6;
    void *temp_t9;

    if (lbl_4074fc(&sp24) == 0) {
        temp_t6 = saved_reg_gp->unk-7E98;
        (? (*)(?, s32))0x0F801250(0x10001C98, temp_t6->unk170 - temp_t6->unk194);
        temp_t9 = saved_reg_gp->unk-7E98;
        temp_t9->unk170 = (s32) (temp_t9->unk170 + 1);
        return;
    }
    var_v0 = saved_reg_gp->unk-7E98->unk170;
    if (var_v0 >= 0x64) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001CC4, 0x10001CD8);
        lbl_40d3c0(1);
        var_v0 = saved_reg_gp->unk-7E98->unk170;
    }
    *(saved_reg_gp->unk-7E98->unk138 + (var_v0 * 4)) = sp24;
    temp_t0 = saved_reg_gp->unk-7E98;
    temp_t0->unk170 = (s32) (temp_t0->unk170 + 1);
}

void main_init_2(void) {
    s32 sp24;
    s32 var_v0;
    void *temp_t7;
    void *temp_t8;

    if (lbl_4074fc(&sp24) == 0) {
        (? (*)(?, s32))0x0F801250(0x10001CE4, saved_reg_gp->unk-7E98->unk174);
        temp_t7 = saved_reg_gp->unk-7E98;
        temp_t7->unk174 = (s32) (temp_t7->unk174 + 1);
        return;
    }
    var_v0 = saved_reg_gp->unk-7E98->unk174;
    if (var_v0 >= 0xC8) {
        (? (*)(?, ?, ?))0x0F801150(0x100036B4, 0x10001D14, 0x10001D28);
        lbl_40d3c0(1);
        var_v0 = saved_reg_gp->unk-7E98->unk174;
    }
    *(saved_reg_gp->unk-7E98->unk13C + (var_v0 * 4)) = sp24;
    temp_t8 = saved_reg_gp->unk-7E98;
    temp_t8->unk174 = (s32) (temp_t8->unk174 + 1);
}

/*
Decompilation failure in function cos:

Unable to parse branch: label lbl_40d1d0 does not exist in function cos
*/

f64 sin(f64 arg0) {
    f64 temp_f0;
    f64 temp_f2;
    f64 temp_f2_3;
    f64 temp_f8;
    f64 var_f12;
    s32 temp_f2_2;

    var_f12 = arg0;
    temp_f0 = fabs(var_f12);
    if (!(temp_f0 < saved_reg_gp->unk-7F48)) {
        temp_f8 = saved_reg_gp->unk-7F58;
        if (temp_f0 < temp_f8) {
            temp_f2_2 = (s32) (var_f12 * saved_reg_gp->unk-7F50);
            temp_f2_3 = (f64) temp_f2_2;
            var_f12 = (var_f12 - (temp_f2_3 * saved_reg_gp->unk-7F40)) - (temp_f2_3 * (bitwise f64) saved_reg_gp->unk-7F34);
            if (temp_f2_2 & 1) {
                var_f12 = -var_f12;
            }
            /* Duplicate return node #4. Try simplifying control flow for better match */
            temp_f2 = var_f12 * var_f12;
            return var_f12 + (((((((((((((((temp_f2 * saved_reg_gp->unk-7F30) + saved_reg_gp->unk-7F28) * temp_f2) + saved_reg_gp->unk-7F20) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7F14) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7F0C) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7F04) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7EFC) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7EF4) * temp_f2 * var_f12);
        }
        if (!(temp_f0 < temp_f8)) {
            return 0.0 / 0.0;
        }
        return M2C_ERROR(/* unknown instruction: c.un.d $f12, $f12 */);
    }
    temp_f2 = var_f12 * var_f12;
    return var_f12 + (((((((((((((((temp_f2 * saved_reg_gp->unk-7F30) + saved_reg_gp->unk-7F28) * temp_f2) + saved_reg_gp->unk-7F20) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7F14) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7F0C) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7F04) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7EFC) * temp_f2) + (bitwise f64) saved_reg_gp->unk-7EF4) * temp_f2 * var_f12);
}

