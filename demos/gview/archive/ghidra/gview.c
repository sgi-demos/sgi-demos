typedef unsigned char   undefined;

typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;



void FUN_00400270(void)

{
  int unaff_gp;
  
  func_0x0f801150(&DAT_100036b4,unaff_gp + -0x7e90,unaff_gp + -0x7ea0,
                  s_usage__gview____nfP_____m_f_mat__100001c0);
  FUN_0040d3c0(1);
  return;
}



undefined4 FUN_004002ac(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int *piVar6;
  undefined4 uVar7;
  int unaff_gp;
  double dVar8;
  undefined4 local_206c [6];
  undefined local_2054 [52];
  undefined4 local_2020;
  int local_201c;
  int local_2018;
  int local_10;
  
  local_2018 = 0;
  local_201c = 0;
  local_10 = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x48) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 200) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd0) = 0xffffffff;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x38) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xdc) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x104) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xbc) = 0;
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xc0) = unaff_gp + -0x7e80;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x68) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x6c) = *(undefined4 *)(unaff_gp + -0x7ee0);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x90) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x94) = 0;
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x98) = unaff_gp + -0x7e78;
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x9c) = unaff_gp + -0x7e74;
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x74) = unaff_gp + -0x7e70;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x78) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xa0) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xb8) = 0;
  *(undefined4 *)(unaff_gp + -0x7bc0) = 0;
  iVar1 = FUN_0040d3f0(param_1,param_2,s_fF_i_l_Lm_M_no_PR_s_t_v_V_w_W__10000234);
  if (iVar1 != -1) {
    iVar3 = unaff_gp + -0x7ea0;
    do {
      if (iVar1 == 0x6c) {
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 200) = 1;
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd4) = 0;
        iVar1 = FUN_0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e5c,
                             *(int *)(unaff_gp + -0x7e98) + 0xcc,*(int *)(unaff_gp + -0x7e98) + 0xd0
                            );
        if (iVar1 != 2) {
          FUN_00400270();
        }
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd0) == 0) {
          iVar1 = unaff_gp + -0x7e54;
        }
        else {
          iVar1 = unaff_gp + -0x7e4c;
        }
        func_0x0f801250(s__s__using__s_sequence_for_movie_10000350,iVar3,iVar1);
      }
      else if (iVar1 < 0x6d) {
        if (iVar1 == 0x56) {
          if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x94) != 0) {
            FUN_00400270();
          }
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x90) = 1;
          uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x98) = uVar2;
        }
        else if (iVar1 < 0x57) {
          if (iVar1 == 0x4d) {
            uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc0) = uVar2;
          }
          else if (iVar1 < 0x4e) {
            if (iVar1 == 0x46) {
              iVar1 = FUN_0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e60,
                                   *(int *)(unaff_gp + -0x7e98) + 0x104);
              if (iVar1 != 1) {
                FUN_00400270();
              }
              func_0x0f801250(s_display_list_filter__d_enabled_10000330,
                              *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x104));
            }
            else {
              if ((iVar1 < 0x47) || (iVar1 != 0x4c)) goto LAB_004008fc;
              func_0x0f801250(s_mapping_lines_to_closed_lines_10000310);
              *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xb8) = 1;
            }
          }
          else if (iVar1 == 0x52) {
            local_2018 = 1;
            if (local_201c != 0) {
              FUN_00400270();
            }
            local_2020 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          }
          else {
            if ((0x52 < iVar1) || (iVar1 != 0x50)) goto LAB_004008fc;
            *(undefined4 *)(unaff_gp + -0x7e94) = 1;
          }
        }
        else if (iVar1 == 0x66) {
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x48) = 1;
        }
        else if (iVar1 < 0x67) {
          if (iVar1 == 0x57) {
            local_201c = 1;
            if (local_2018 != 0) {
              FUN_00400270();
            }
            local_2020 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          }
          else {
LAB_004008fc:
            FUN_00400270();
          }
        }
        else {
          if (iVar1 != 0x69) goto LAB_004008fc;
          uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x9c) = uVar2;
        }
      }
      else if (iVar1 == 0x73) {
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x78) = 1;
        iVar1 = FUN_0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e64,
                             *(int *)(unaff_gp + -0x7e98) + 0x7c);
        if (iVar1 != 1) {
          FUN_00400270();
        }
        dVar8 = (double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x7c);
        func_0x0f801150(&DAT_100036b4,s_using_scale___g__100002d4,(int)((ulonglong)dVar8 >> 0x20),
                        SUB84(dVar8,0));
      }
      else if (iVar1 < 0x74) {
        if (iVar1 == 0x6e) {
          local_10 = 1;
        }
        else if (iVar1 < 0x6f) {
          if (iVar1 != 0x6d) goto LAB_004008fc;
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xbc) = 1;
          FUN_004034f0();
          pcVar5 = *(char **)(unaff_gp + -0x7bb4);
          local_2054[0] = 0;
          iVar1 = FUN_0040d7a4(pcVar5,s__40____s_10000374,local_2054);
          while (iVar1 == 1) {
            iVar1 = func_0x0f801130(local_2054,unaff_gp + -0x7e44);
            if (iVar1 == 0) {
              func_0x0f801150(&DAT_100036b4,s__s__cannot_open__s_for_reading_100003a0,iVar3,
                              local_2054);
              FUN_00400270();
            }
            else {
              func_0x0f801150(&DAT_100036b4,s__s__reading_material_file__s_10000380,iVar3,local_2054
                             );
              FUN_00403584(iVar1,local_2054);
            }
            iVar1 = func_0x0f801308(local_2054);
            pcVar5 = pcVar5 + iVar1;
            if (*pcVar5 == ',') {
              pcVar5 = pcVar5 + 1;
            }
            local_2054[0] = 0;
            iVar1 = FUN_0040d7a4(pcVar5,s__40____s_100003c0,local_2054);
          }
        }
        else {
          if (iVar1 != 0x6f) goto LAB_004008fc;
          uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x74) = uVar2;
        }
      }
      else if (iVar1 == 0x76) {
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x90) != 0) {
          FUN_00400270();
        }
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x94) = 1;
        uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x98) = uVar2;
      }
      else if (iVar1 < 0x77) {
        if (iVar1 != 0x74) goto LAB_004008fc;
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x80) = 1;
        iVar1 = *(int *)(unaff_gp + -0x7e98);
        iVar1 = FUN_0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),s__f__f__f_100002e8,iVar1 + 0x84,
                             iVar1 + 0x88,iVar1 + 0x8c);
        if (iVar1 != 3) {
          FUN_00400270();
        }
        iVar1 = *(int *)(unaff_gp + -0x7e98);
        func_0x0f801150(&DAT_100036b4,s_using_translate___g__g__g__100002f4,
                        (int)((ulonglong)(double)*(float *)(iVar1 + 0x84) >> 0x20),
                        SUB84((double)*(float *)(iVar1 + 0x84),0),(double)*(float *)(iVar1 + 0x88),
                        (double)*(float *)(iVar1 + 0x8c));
      }
      else {
        if (iVar1 != 0x77) goto LAB_004008fc;
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x68) = 1;
        iVar1 = FUN_0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e6c,
                             *(int *)(unaff_gp + -0x7e98),*(int *)(unaff_gp + -0x7e98) + 4);
        if ((iVar1 != 1) && (iVar1 != 2)) {
          FUN_00400270();
        }
        if (iVar1 == 1) {
          (*(undefined4 **)(unaff_gp + -0x7e98))[1] = **(undefined4 **)(unaff_gp + -0x7e98);
        }
        func_0x0f801150(&DAT_100036b4,s_using_window_size___d__d__100002b8,
                        **(undefined4 **)(unaff_gp + -0x7e98),
                        (*(undefined4 **)(unaff_gp + -0x7e98))[1]);
        piVar6 = *(int **)(unaff_gp + -0x7e98);
        piVar6[0x1b] = (int)((float)*piVar6 / (float)piVar6[1]);
      }
      iVar1 = FUN_0040d3f0(param_1,param_2,s_fF_i_l_Lm_M_no_PR_s_t_v_V_w_W__10000234);
    } while (iVar1 != -1);
  }
  iVar1 = unaff_gp + -0x7ea0;
  if (local_2018 == 0) {
    if ((local_201c != 0) && (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x104) == 0)) {
      func_0x0f801150(&DAT_100036b4,s__s___W_option_will_not_work_corr_100003cc,iVar1);
      FUN_0040d3c0(0xffffffff);
    }
    uVar2 = func_0x0f801208(2000000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x108) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x108) == 0) {
      FUN_004092d4(unaff_gp + -0x7e40);
    }
    uVar2 = func_0x0f801208(0xc);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x10c) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x10c) == 0) {
      FUN_004092d4(unaff_gp + -0x7e38);
    }
    uVar2 = func_0x0f801208(300000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x114) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x114) == 0) {
      FUN_004092d4(unaff_gp + -0x7e30);
    }
    uVar2 = func_0x0f801208(4800000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x110) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x110) == 0) {
      FUN_004092d4(unaff_gp + -0x7e28);
    }
    uVar2 = func_0x0f801208(0xe10);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x124) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x124) == 0) {
      FUN_004092d4(unaff_gp + -0x7e20);
    }
    uVar2 = func_0x0f801208(0x140);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x118) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x118) == 0) {
      FUN_004092d4(unaff_gp + -0x7e18);
    }
    uVar2 = func_0x0f801208(0xf0);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x11c) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x11c) == 0) {
      FUN_004092d4(unaff_gp + -0x7e10);
    }
    uVar2 = func_0x0f801208(0xf0);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x120) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x120) == 0) {
      FUN_004092d4(unaff_gp + -0x7e08);
    }
    uVar2 = func_0x0f801208(3200000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x128) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x128) == 0) {
      FUN_004092d4(unaff_gp + -0x7e00);
    }
    uVar2 = func_0x0f801208(1600000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 300) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 300) == 0) {
      FUN_004092d4(unaff_gp + -0x7df8);
    }
    uVar2 = func_0x0f801208(64000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x130) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x130) == 0) {
      FUN_004092d4(unaff_gp + -0x7df0);
    }
    uVar2 = func_0x0f801208(400);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x138) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x138) == 0) {
      FUN_004092d4(unaff_gp + -0x7de8);
    }
    uVar2 = func_0x0f801208(800);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) == 0) {
      FUN_004092d4(unaff_gp + -0x7de0);
    }
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x104) != 0) {
      uVar2 = func_0x0f801208(800);
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf0) = uVar2;
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf0) == 0) {
        FUN_004092d4(unaff_gp + -0x7dd8);
      }
      FUN_00404580();
    }
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x140) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x144) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x148) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x14c) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x15c) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x150) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x154) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x158) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x160) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x170) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x174) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x178) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x17c) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x180) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x184) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x188) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x18c) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 400) = 0;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x194) = 0;
    iVar3 = param_1 - *(int *)(unaff_gp + -0x7bbc);
    if (iVar3 == 0) {
      func_0x0f801150(&DAT_100036b4,s__s__reading_input_from_stdin_1000040c,iVar1);
      iVar3 = FUN_00405590(&DAT_10003694);
      if (iVar3 == 0) {
        FUN_0040d3c0(0xffffffff);
      }
    }
    else if (iVar3 < 1) {
      FUN_00400270();
    }
    else {
      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd4) = iVar3;
      if (*(int *)(unaff_gp + -0x7bbc) < param_1) {
        do {
          uVar2 = param_2[*(int *)(unaff_gp + -0x7bbc)];
          *(int *)(unaff_gp + -0x7bbc) = *(int *)(unaff_gp + -0x7bbc) + 1;
          iVar3 = func_0x0f801130(uVar2,unaff_gp + -0x7dd0);
          if (iVar3 == 0) {
            if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd4) < 2) {
              FUN_004092d4(s__s__cannot_open_file__s_10000450,iVar1,uVar2);
            }
            else {
              func_0x0f801150(&DAT_100036b4,s__s__Warning__cannot_open_file__s_1000042c,iVar1,uVar2)
              ;
            }
          }
          else {
            func_0x0f801150(&DAT_100036b4,s__s__reading_file__s_1000046c,iVar1,uVar2);
            iVar4 = FUN_00405590(iVar3);
            if (iVar4 == 0) {
              FUN_0040d3c0(0xffffffff);
            }
            func_0x0f801120(iVar3);
          }
          iVar3 = *(int *)(unaff_gp + -0x7e98);
          if (*(int *)(iVar3 + 200) != 0) {
            *(undefined4 *)(iVar3 + 0x178) = *(undefined4 *)(iVar3 + 0x140);
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x17c) =
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x148);
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x180) =
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x14c);
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x184) =
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x15c);
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x188) =
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x160);
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x18c) =
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164);
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 400) =
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168);
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x194) =
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x170);
          }
        } while (*(int *)(unaff_gp + -0x7bbc) < param_1);
      }
    }
    if (0 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160)) {
      func_0x0f801250(s__s___d_items_in_polygon_table_10000484,iVar1);
    }
    if (0 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164)) {
      func_0x0f801250(s__s___d_items_in_line_table_100004a4,iVar1);
    }
    if (0 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168)) {
      func_0x0f801250(s__s___d_items_in_point_table_100004c0,iVar1);
    }
    func_0x0f801250(s__s___d_items_in_instance_table_100004e0,iVar1,
                    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x174));
  }
  if (local_2018 != 0) {
    func_0x0f801150(&DAT_100036b4,s_reading_in_binary_file____10000500);
    iVar3 = func_0x0f801130(local_2020,unaff_gp + -0x7dcc);
    if (iVar3 == 0) {
      func_0x0f801150(&DAT_100036b4,s__s__cannot_read_from_file__s_1000051c,iVar1,local_2020);
      FUN_0040d3c0(0xffffffff);
    }
    iVar4 = FUN_00404e78(iVar3,local_206c);
    func_0x0f801150(&DAT_100036b4,unaff_gp + -0x7dc8);
    func_0x0f801120(iVar3);
    if (iVar4 == 0) {
      func_0x0f801150(&DAT_100036b4,s__s__binary_file_read_failed_1000053c,iVar1);
      FUN_0040d3c0(0xffffffff);
    }
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) = iVar4;
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd4) = local_206c[0];
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 200) == 0) {
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x174) = 1;
    }
  }
  iVar3 = *(int *)(unaff_gp + -0x7e98);
  if (*(int *)(iVar3 + 0x104) != 0) {
    if (*(int *)(iVar3 + 200) == 0) {
      uVar2 = FUN_00404668(**(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0x13c));
      **(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xf0) = uVar2;
    }
    else {
      iVar4 = 0;
      if (0 < *(int *)(iVar3 + 0xd4)) {
        iVar3 = 0;
        do {
          uVar2 = FUN_00404668(*(undefined4 *)
                                (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) + iVar3),
                               *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x104));
          iVar4 = iVar4 + 1;
          *(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf0) + iVar3) = uVar2;
          iVar3 = iVar3 + 4;
        } while (iVar4 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd4));
      }
    }
  }
  if (local_201c != 0) {
    iVar3 = *(int *)(unaff_gp + -0x7e98);
    uVar2 = 1;
    if (*(int *)(iVar3 + 200) != 0) {
      uVar2 = *(undefined4 *)(iVar3 + 0xd4);
    }
    if (*(int *)(iVar3 + 0x104) == 0) {
      uVar7 = *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x13c);
    }
    else {
      uVar7 = *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf0);
    }
    func_0x0f801150(&DAT_100036b4,s_writing_out_binary_file____1000055c);
    iVar3 = func_0x0f801130(local_2020,unaff_gp + -0x7dc0);
    if (iVar3 == 0) {
      func_0x0f801150(&DAT_100036b4,s__s__cannot_write_to_file__s_10000578,iVar1,local_2020);
      FUN_0040d3c0(0xffffffff);
    }
    FUN_00404b60(uVar7,uVar2,iVar3);
    func_0x0f801120(iVar3);
    func_0x0f801150(&DAT_100036b4,unaff_gp + -0x7dbc);
  }
  if (local_10 == 0) {
    FUN_00401678(*param_2);
    FUN_00408200();
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xbc) == 0) {
      FUN_00403440();
    }
    else {
      FUN_00403684();
      uVar2 = FUN_0040381c(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc0));
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc4) = uVar2;
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xc4) == 0) {
        func_0x0f801150(&DAT_100036b4,s__s__could_not_find_material__s_10000598,iVar1,
                        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc0));
        FUN_0040d3c0(0xffffffff);
      }
      func_0x0f801150(&DAT_100036b4,s_using_material__s_100005b8,
                      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc0));
    }
    FUN_00402098();
    FUN_00401a00();
  }
  return 0;
}



void FUN_00401504(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_gp;
  
  iVar2 = *(int *)(unaff_gp + -0x7e98);
  iVar1 = *(int *)(iVar2 + 200);
  if (((iVar1 == 0) && (*(int *)(iVar2 + 0x104) == 0)) && (iVar3 = 0, 0 < *(int *)(iVar2 + 0x174)))
  {
    iVar1 = 0;
    do {
      FUN_004082e8(*(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) + iVar1));
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar3 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174));
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
  }
  if ((iVar1 == 0) && (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x104) != 0)) {
    FUN_004082e8(**(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xf0));
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
  }
  if ((iVar1 != 0) && (iVar2 = *(int *)(unaff_gp + -0x7e98), *(int *)(iVar2 + 0x104) == 0)) {
    FUN_004082e8(*(undefined4 *)(*(int *)(iVar2 + 0x13c) + *(int *)(iVar2 + 0xd8) * 4));
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
  }
  if ((iVar1 != 0) && (iVar1 = *(int *)(unaff_gp + -0x7e98), *(int *)(iVar1 + 0x104) != 0)) {
    FUN_004082e8(*(undefined4 *)(*(int *)(iVar1 + 0xf0) + *(int *)(iVar1 + 0xd8) * 4));
  }
  return;
}



void FUN_00401678(int param_1)

{
  double dVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int unaff_gp;
  undefined4 uVar5;
  uint in_fcsr;
  
  uVar5 = *(undefined4 *)(unaff_gp + -0x7edc);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x24) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x28) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x30) = *(undefined4 *)(unaff_gp + -0x7ee0);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x10) = uVar5;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x14) = uVar5;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x18) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x1c) = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x2c) = 0;
  puVar4 = *(undefined4 **)(unaff_gp + -0x7e98);
  if (puVar4[0x1a] != 0) {
    func_0x0f401400(*puVar4,puVar4[1]);
  }
  iVar2 = func_0x0f801330(param_1,0x2f);
  iVar3 = param_1;
  if (iVar2 != 0) {
    iVar3 = iVar2 + 1;
  }
  func_0x0f401458(iVar3);
  func_0x0f401440(*(int *)(unaff_gp + -0x7e98) + 8,*(int *)(unaff_gp + -0x7e98) + 0xc);
  func_0x0f401438(*(int *)(unaff_gp + -0x7e98),*(int *)(unaff_gp + -0x7e98) + 4);
  func_0x0f401220();
  func_0x0f401070();
  func_0x0f401098();
  iVar3 = func_0x0f401128();
  if (iVar3 < 0xc) {
    iVar3 = func_0x0f4016b0(6);
    if (iVar3 == 3) {
      *(undefined4 *)(unaff_gp + -0x7e88) = 1;
    }
    else {
      func_0x0f801150(&DAT_100036b4,s_You_need_a_zbufffer_to_run___s_100005cc,param_1);
      func_0x0f401290();
      FUN_0040d3c0(1);
    }
  }
  func_0x0f402098(0);
  func_0x0f402120();
  func_0x0f402288();
  func_0x0f402098(0);
  func_0x0f402120();
  func_0x0f402508(1);
  func_0x0f402ee8(0x7fffff,0x2000);
  func_0x0f401618(6);
  func_0x0f402518();
  func_0x0f401588(2);
  func_0x0f401098();
  func_0x0f401570(0x40);
  func_0x0f4011a8(0,0,0,0);
  func_0x0f4011a8(1,0,0xff,0xff);
  func_0x0f401fe0(0);
  func_0x0f402120();
  func_0x0f401570(0x10);
  func_0x0f4012f0(0x67);
  func_0x0f4012f0(0x66);
  func_0x0f4012f0(0x65);
  func_0x0f4012f0(7);
  func_0x0f4012f0(0x53);
  func_0x0f4012f0(0x21c);
  func_0x0f4012f0(0x19);
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x90) != 0) {
    func_0x0f4012f0(0x1d);
  }
  func_0x0f4012f0(0x28);
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 200) != 0) {
    func_0x0f4012f0(6);
  }
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x48) != 0) {
    func_0x0f4012f0(0xb);
    func_0x0f4012f0(0xc);
    func_0x0f4012f0(10);
    func_0x0f4012f0(0x10);
    func_0x0f4012f0(0x15);
    func_0x0f4012f0(0x20);
    func_0x0f4012f0(0x14);
  }
  uVar5 = func_0x0f4015a8(s_Options__t_Auto_Advance_On_Off_E_10000254);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 100) = uVar5;
  func_0x0f402578(1);
  if ((((in_fcsr | 3) ^ 2) & 3) == 0) {
    dVar1 = ROUND(*(double *)(unaff_gp + -0x7ff0));
  }
  else {
    dVar1 = FLOOR(*(double *)(unaff_gp + -0x7ff0));
  }
  func_0x0f402fa0((int)dVar1,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x6c),0x3e800000,
                  0x41700000);
  func_0x0f402578(2);
  func_0x0f402190(&DAT_10000278);
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x48) == 0) {
    func_0x0f402298(0,0);
  }
  return;
}



void FUN_00401a00(void)

{
  int unaff_gp;
  
  func_0x0f401508(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 100));
  return;
}



void FUN_00401a28(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int unaff_gp;
  double dVar4;
  double dVar5;
  undefined auStack_10 [16];
  
  if (param_1 == 0) {
    uVar1 = FUN_0040d810(auStack_10);
    *(undefined4 *)(unaff_gp + -0x7b70) = uVar1;
  }
  else if (param_1 % 100 == 0) {
    iVar2 = FUN_0040d810(auStack_10);
    dVar4 = (double)(iVar2 - *(int *)(unaff_gp + -0x7b70)) / *(double *)(unaff_gp + -0x7fe8);
    dVar5 = *(double *)(unaff_gp + -0x7fe8) / dVar4;
    func_0x0f801250(s__6_2lf_frames_s__100005ec,param_2,(int)((ulonglong)dVar5 >> 0x20),
                    SUB84(dVar5,0));
    iVar3 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160);
    if (iVar3 != 0) {
      dVar5 = (double)(iVar3 * 100) / dVar4;
      func_0x0f801250(s__9_2lf_polygons_s__10000600,param_2,(int)((ulonglong)dVar5 >> 0x20),
                      SUB84(dVar5,0));
    }
    iVar3 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164);
    if (iVar3 == 0) {
      func_0x0f801250(unaff_gp + -0x7db4);
    }
    else {
      dVar4 = (double)(iVar3 * 100) / dVar4;
      func_0x0f801250(s__9_2lf_lines_s_10000614,param_2,(int)((ulonglong)dVar4 >> 0x20),
                      SUB84(dVar4,0));
    }
    *(int *)(unaff_gp + -0x7b70) = iVar2;
  }
  return;
}



void FUN_00401b88(float param_1)

{
  int iVar1;
  int iVar2;
  int unaff_gp;
  double dVar3;
  int iVar4;
  byte in_fcsr;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd4);
  iVar2 = iVar1 + -1;
  dVar3 = (((double)param_1 - *(double *)(unaff_gp + -0x7fe0)) * *(double *)(unaff_gp + -0x7fd8) +
          *(double *)(unaff_gp + -0x7fe0)) * (double)iVar2;
  if ((((in_fcsr | 3) ^ 2) & 3) == 0) {
    dVar3 = ROUND(dVar3);
  }
  else {
    dVar3 = FLOOR(dVar3);
  }
  iVar4 = (int)dVar3;
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  else if (iVar1 <= iVar4) {
    iVar4 = iVar2;
  }
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd8) = iVar4;
  return;
}



void FUN_00401c18(void)

{
  int iVar1;
  int iVar2;
  int unaff_gp;
  
  iVar2 = *(int *)(unaff_gp + -0x7e98);
  iVar1 = *(int *)(unaff_gp + -0x7da8) + 1;
  if (*(int *)(iVar2 + 0xcc) <= *(int *)(unaff_gp + -0x7da8)) {
    if (*(int *)(iVar2 + 0xd0) == 0) {
      iVar1 = *(int *)(unaff_gp + -0x7dac) + 1;
      if (*(int *)(iVar2 + 0xd4) <= iVar1) {
        iVar1 = 0;
      }
      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd8) = iVar1;
      *(int *)(unaff_gp + -0x7dac) = iVar1;
    }
    else {
      if (*(int *)(unaff_gp + -0x7db0) == 0) {
        iVar1 = *(int *)(unaff_gp + -0x7dac) + -1;
        if (iVar1 < 0) {
          *(undefined4 *)(unaff_gp + -0x7db0) = 1;
          iVar1 = 0;
        }
      }
      else {
        iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd4);
        iVar1 = *(int *)(unaff_gp + -0x7dac) + 1;
        if (iVar2 <= iVar1) {
          *(undefined4 *)(unaff_gp + -0x7db0) = 0;
          iVar1 = iVar2 + -1;
        }
      }
      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd8) = iVar1;
      *(int *)(unaff_gp + -0x7dac) = iVar1;
    }
    iVar1 = 1;
  }
  *(int *)(unaff_gp + -0x7da8) = iVar1;
  return;
}



void FUN_00401ce8(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int unaff_gp;
  undefined auStackX_0 [16];
  float local_48 [18];
  
  uVar2 = *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x98);
  iVar1 = func_0x0f801130(uVar2,unaff_gp + -0x7da4);
  if (iVar1 == 0) {
    func_0x0f801150(&DAT_100036b4,s__s__cannot_open__s_for_writing_10000668,unaff_gp + -0x7ea0,uVar2
                   );
  }
  else {
    func_0x0f801150(&DAT_100036b4,s__s__saving_viewing_to_file__s_10000624,unaff_gp + -0x7ea0,uVar2)
    ;
    func_0x0f402578(1);
    func_0x0f401120(local_48);
    func_0x0f801250(s_SaveViewToFile__projection_matri_10000644);
    iVar5 = 0;
    do {
      func_0x0f801250(unaff_gp + -0x7da0);
      iVar4 = 0;
      do {
        func_0x0f801250(unaff_gp + -0x7d9c);
        iVar4 = iVar4 + 1;
      } while (iVar4 != 4);
      func_0x0f801250(unaff_gp + -0x7d98);
      iVar5 = iVar5 + 4;
    } while (iVar5 < 0x10);
    puVar3 = (undefined *)register0x00000074;
    do {
      func_0x0f801150(iVar1,unaff_gp + -0x7d94,
                      (int)((ulonglong)(double)*(float *)(puVar3 + -0x48) >> 0x20),
                      SUB84((double)*(float *)(puVar3 + -0x48),0));
      puVar3 = puVar3 + 4;
    } while (puVar3 != &stack0x00000040);
    func_0x0f801150(iVar1,unaff_gp + -0x7d90);
    func_0x0f402578(2);
    func_0x0f401120(local_48);
    puVar3 = &stack0x00000040;
    do {
      func_0x0f801150(iVar1,unaff_gp + -0x7d8c,
                      (int)((ulonglong)(double)*(float *)((int)register0x00000074 + -0x48) >> 0x20),
                      SUB84((double)*(float *)((int)register0x00000074 + -0x48),0));
      register0x00000074 = (BADSPACEBASE *)((int)register0x00000074 + 4);
    } while ((undefined *)register0x00000074 != puVar3);
    func_0x0f801150(iVar1,unaff_gp + -0x7d88);
  }
  return;
}



void FUN_00401ebc(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  int iVar5;
  int unaff_gp;
  
  uVar2 = *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x98);
  if (*(int *)(unaff_gp + -0x7d84) == 0) {
    iVar1 = func_0x0f801130(uVar2,unaff_gp + -0x7d80);
    if (iVar1 == 0) {
      func_0x0f801150(&DAT_100036b4,s__s__cannot_open__s_for_reading_100006d4,unaff_gp + -0x7ea0,
                      uVar2);
      FUN_0040d3c0(0xffffffff);
    }
    else {
      func_0x0f801150(&DAT_100036b4,s__s__reading_viewing_from_file__s_10000688,unaff_gp + -0x7ea0,
                      uVar2);
      puVar3 = &DAT_100044e8;
      do {
        FUN_0040d768(iVar1,unaff_gp + -0x7d7c,puVar3);
        puVar3 = puVar3 + 1;
      } while (puVar3 != (undefined4 *)&DAT_10004528);
      puVar4 = &DAT_10004528;
      do {
        FUN_0040d768(iVar1,unaff_gp + -0x7d78,puVar4);
        puVar4 = puVar4 + 4;
      } while (puVar4 != (undefined *)0x10004568);
      func_0x0f801250(s_RestoreViewFromFile__projection_m_100006ac);
      iVar1 = 0;
      do {
        func_0x0f801250(unaff_gp + -0x7d74);
        iVar5 = 0;
        do {
          func_0x0f801250(unaff_gp + -0x7d70);
          iVar5 = iVar5 + 1;
        } while (iVar5 != 4);
        func_0x0f801250(unaff_gp + -0x7d6c);
        iVar1 = iVar1 + 4;
      } while (iVar1 != 0x10);
      *(undefined4 *)(unaff_gp + -0x7d84) = 1;
    }
  }
  func_0x0f402578(1);
  func_0x0f402190(&DAT_100044e8);
  func_0x0f402578(2);
  func_0x0f402190(&DAT_10004528);
  return;
}



void FUN_00402098(void)

{
  double dVar1;
  int iVar2;
  short sVar3;
  int *piVar4;
  int unaff_gp;
  uint in_fcsr;
  undefined auStack_78 [48];
  int local_48;
  uint local_3c;
  int local_38;
  int local_30;
  int local_28;
  int local_14;
  short local_10 [4];
  uint local_8;
  int local_4;
  
  local_4 = 0;
  local_8 = 1;
  local_28 = 0;
  local_38 = 1;
  local_48 = 0;
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x48) != 0) {
    FUN_00402f60();
  }
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd8) = 0;
  local_3c = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x70) = 0;
  local_30 = 0;
LAB_004020f4:
  iVar2 = func_0x0f401200();
  if (iVar2 == 0) goto code_r0x00402680;
  do {
    sVar3 = func_0x0f4011f0(local_10);
    while( true ) {
      if (sVar3 == 0x28) {
        if (local_10[0] != 0) {
          FUN_00409778(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x9c));
        }
      }
      else if (sVar3 < 0x29) {
        if (sVar3 == 0x14) {
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x54) = 3;
        }
        else if (sVar3 < 0x15) {
          if (sVar3 == 0xb) {
            iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x50);
            if ((iVar2 < 1000) && (local_10[0] == 1)) {
              *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x50) = iVar2 + 0x14;
            }
          }
          else if (sVar3 < 0xc) {
            if (sVar3 == 7) {
              if (local_10[0] == 0) {
                local_4 = 1;
              }
            }
            else if (sVar3 < 8) {
              if (sVar3 == 6) {
                if (local_10[0] == 0) {
                  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x20) = 0;
                }
                else {
                  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x20) = 1;
                }
              }
            }
            else if ((sVar3 == 10) && (local_10[0] == 1)) {
              *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x4c) =
                   (float)((double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x4c) /
                          *(double *)(unaff_gp + -0x7fd8));
            }
          }
          else if (sVar3 == 0x10) {
            if (local_10[0] == 1) {
              *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x4c) =
                   *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x4c) * *(float *)(unaff_gp + -0x7ed8);
            }
          }
          else if ((sVar3 < 0x11) && (sVar3 == 0xc)) {
            iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x50);
            if ((200 < iVar2) && (local_10[0] == 1)) {
              *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x50) = iVar2 + -0x14;
            }
          }
        }
        else if (sVar3 == 0x1d) {
          if ((local_10[0] != 0) && (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x90) != 0)) {
            local_48 = 1;
          }
        }
        else if (sVar3 < 0x1e) {
          if (sVar3 == 0x15) {
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x54) = 1;
          }
        }
        else if (sVar3 == 0x20) {
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x54) = 2;
        }
      }
      else if (sVar3 == 0x67) {
        if (local_10[0] == 0) {
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x18) = 0;
        }
        else {
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x18) = 1;
        }
      }
      else if (sVar3 < 0x68) {
        if (sVar3 == 0x65) {
          if (local_10[0] != 0) {
            iVar2 = func_0x0f401500(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 100));
            if (iVar2 == 1) {
              local_3c = (uint)(local_3c == 0);
            }
            else if (iVar2 == 2) {
              local_4 = 1;
            }
          }
        }
        else if (sVar3 < 0x66) {
          if (sVar3 == 0x53) {
            if (*(int *)(unaff_gp + -0x7e88) == 0) {
              if (local_10[0] == 0) {
                local_28 = 0;
              }
              else {
                local_28 = 1;
              }
            }
            else if ((*(int *)(unaff_gp + -0x7e84) == 0) && (local_10[0] == 1)) {
              *(undefined4 *)(unaff_gp + -0x7e84) = 1;
              FUN_00402f00();
            }
            else if ((*(int *)(unaff_gp + -0x7e84) == 1) && (local_10[0] == 1)) {
              *(undefined4 *)(unaff_gp + -0x7e84) = 0;
            }
          }
        }
        else if (sVar3 == 0x66) {
          if (local_10[0] == 0) {
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x1c) = 0;
          }
          else {
            *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x1c) = 1;
          }
        }
      }
      else if (sVar3 == 0x216) {
        local_8 = (uint)(local_10[0] != 0);
        if ((*(int *)(unaff_gp + -0x7e88) != 0) && (*(int *)(unaff_gp + -0x7e84) != 0)) {
          FUN_00402f00();
        }
      }
      else if (sVar3 < 0x217) {
        if (sVar3 == 0x210) {
          local_38 = 1;
          func_0x0f401450();
          func_0x0f401440(*(int *)(unaff_gp + -0x7e98) + 8,*(int *)(unaff_gp + -0x7e98) + 0xc);
          func_0x0f401438(*(int *)(unaff_gp + -0x7e98),*(int *)(unaff_gp + -0x7e98) + 4);
          piVar4 = *(int **)(unaff_gp + -0x7e98);
          piVar4[0x1b] = (int)((float)*piVar4 / (float)piVar4[1]);
          if ((*(int *)(unaff_gp + -0x7e88) != 0) && (*(int *)(unaff_gp + -0x7e84) != 0)) {
            FUN_00402f00();
          }
        }
      }
      else if (((sVar3 == 0x21c) && (*(int *)(unaff_gp + -0x7e88) != 0)) &&
              (*(int *)(unaff_gp + -0x7e84) != 0)) {
        FUN_00402f00();
      }
      iVar2 = func_0x0f401200();
      if (iVar2 != 0) break;
code_r0x00402680:
      if (local_4 != 0) {
        func_0x0f401570(0x40);
        func_0x0f401fe0(0);
        func_0x0f402120();
        func_0x0f401570(0x10);
        return;
      }
      if ((local_28 != 0) ||
         ((*(int *)(unaff_gp + -0x7e88) != 0 && (*(int *)(unaff_gp + -0x7e84) != 0))))
      goto LAB_004020f4;
      if (local_8 != 0) {
        if (local_8 != 0) {
          local_14 = func_0x0f401140(0x10a);
          iVar2 = func_0x0f401140(0x10b);
          piVar4 = *(int **)(unaff_gp + -0x7e98);
          piVar4[4] = (int)((float)(local_14 - piVar4[2]) / (float)*piVar4);
          *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x14) =
               (float)(iVar2 - piVar4[3]) / (float)*(int *)(*(int *)(unaff_gp + -0x7e98) + 4);
        }
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xbc) != 0) {
          FUN_00403938(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc4));
        }
        iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
        if ((iVar2 != 0) && (local_3c != 0)) {
          FUN_00401c18();
          iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
        }
        if (((iVar2 != 0) && (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x20) != 0)) &&
           (local_3c == 0)) {
          FUN_00401b88(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x10));
        }
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x48) == 0) {
          func_0x0f402230();
          if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x94) == 0) {
            FUN_00402bac();
          }
          else {
            FUN_00401ebc();
          }
          if (local_48 != 0) {
            local_48 = 0;
            FUN_00401ce8();
          }
          FUN_00401504();
          func_0x0f402228();
          iVar2 = local_38;
        }
        else {
          func_0x0f402230();
          if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x94) == 0) {
            FUN_00402fbc();
          }
          else {
            FUN_00401ebc();
          }
          if (local_48 != 0) {
            local_48 = 0;
            FUN_00401ce8();
          }
          FUN_00401504();
          func_0x0f402228();
          iVar2 = local_38;
        }
        local_38 = 0;
        if ((iVar2 != 0) && (**(char **)(*(int *)(unaff_gp + -0x7e98) + 0x74) != '\0')) {
          if ((((in_fcsr | 3) ^ 2) & 3) == 0) {
            dVar1 = ROUND(*(double *)(unaff_gp + -0x7ff0));
          }
          else {
            dVar1 = FLOOR(*(double *)(unaff_gp + -0x7ff0));
          }
          func_0x0f402230();
          func_0x0f402190(&DAT_10000278);
          func_0x0f402fa8(0,(float)**(int **)(unaff_gp + -0x7e98));
          func_0x0f402508(0);
          func_0x0f401570(0x40);
          func_0x0f401fe0(0);
          func_0x0f402120();
          func_0x0f401fe0(1);
          func_0x0f402138(10,10);
          func_0x0f402118(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x74));
          func_0x0f401570(0x10);
          func_0x0f402508(1);
          func_0x0f402228();
          func_0x0f402fa0((int)dVar1,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x6c),0x3e800000
                          ,0x41700000);
        }
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 200) != 0) {
          if ((((in_fcsr | 3) ^ 2) & 3) == 0) {
            dVar1 = ROUND(*(double *)(unaff_gp + -0x7ff0));
          }
          else {
            dVar1 = FLOOR(*(double *)(unaff_gp + -0x7ff0));
          }
          func_0x0f8012c0(auStack_78,s_frame__03d_100006f4,
                          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd8));
          func_0x0f402230();
          func_0x0f402190(&DAT_10000278);
          func_0x0f402fa8(0,(float)**(int **)(unaff_gp + -0x7e98));
          func_0x0f402508(0);
          func_0x0f402098(0xffffff00);
          iVar2 = func_0x0f401250(unaff_gp + -0x7d68);
          func_0x0f402138(**(int **)(unaff_gp + -0x7e98) + iVar2 * -10,10);
          func_0x0f402118(auStack_78);
          func_0x0f402508(1);
          func_0x0f402228();
          func_0x0f402fa0((int)dVar1,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x6c),0x3e800000
                          ,0x41700000);
        }
        func_0x0f402288();
        iVar2 = local_30;
        if (*(int *)(unaff_gp + -0x7e94) != 0) {
          local_30 = local_30 + 1;
          FUN_00401a28(iVar2);
        }
        func_0x0f402588(0,0);
        goto LAB_004020f4;
      }
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x18) = 0;
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x1c) = 0;
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x20) = 0;
      local_28 = 0;
      sVar3 = func_0x0f4011f0(local_10);
    }
  } while( true );
}



void FUN_00402bac(undefined4 param_1)

{
  double *pdVar1;
  int iVar2;
  int unaff_gp;
  double dVar3;
  double dVar4;
  undefined4 uVar5;
  float fVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x20) == 0) {
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x70) == 0) {
      iVar2 = *(int *)(unaff_gp + -0x7e98);
      if (*(int *)(iVar2 + 0x1c) == 0) {
        iVar2 = *(int *)(unaff_gp + -0x7e98);
        dVar4 = *(double *)(unaff_gp + -0x7fe0);
        pdVar1 = (double *)(unaff_gp + -0x7fc8);
        uVar7 = *(undefined4 *)pdVar1;
        uVar5 = *(undefined4 *)(unaff_gp + -0x7fc4);
        dVar3 = *pdVar1;
        *(float *)(iVar2 + 0x24) =
             (float)((double)*(float *)(iVar2 + 0x24) +
                    ((double)*(float *)(iVar2 + 0x14) - dVar4) * *pdVar1);
        iVar2 = *(int *)(unaff_gp + -0x7e98);
        *(float *)(iVar2 + 0x28) =
             (float)((double)*(float *)(iVar2 + 0x28) +
                    ((double)*(float *)(iVar2 + 0x10) - dVar4) * dVar3);
        uVar9 = *(undefined4 *)(unaff_gp + -0x7fcc);
        uVar8 = *(undefined4 *)(unaff_gp + -0x7fd0);
      }
      else {
        dVar4 = *(double *)(unaff_gp + -0x7fe0);
        pdVar1 = (double *)(unaff_gp + -0x7fd0);
        uVar8 = *(undefined4 *)pdVar1;
        uVar9 = *(undefined4 *)(unaff_gp + -0x7fcc);
        dVar3 = *pdVar1;
        *(float *)(iVar2 + 0x24) = (float)(((double)*(float *)(iVar2 + 0x14) - dVar4) * *pdVar1);
        *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x28) =
             (float)(((double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x10) - dVar4) * dVar3);
        uVar5 = *(undefined4 *)(unaff_gp + -0x7fc4);
        uVar7 = *(undefined4 *)(unaff_gp + -0x7fc8);
      }
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x18) != 0) {
        dVar4 = (double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x10) - dVar4;
        if (dVar4 < 0.0) {
          dVar4 = -dVar4;
        }
        *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x30) =
             (float)(dVar4 * (double)CONCAT44(uVar7,uVar5));
        if ((double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x30) <
            *(double *)(unaff_gp + -0x7fc0)) {
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x30) = *(undefined4 *)(unaff_gp + -0x7ed4)
          ;
        }
      }
    }
    else {
      uVar8 = *(undefined4 *)(unaff_gp + -0x7fd0);
      uVar9 = *(undefined4 *)(unaff_gp + -0x7fcc);
    }
  }
  else {
    uVar8 = *(undefined4 *)(unaff_gp + -0x7fd0);
    uVar9 = *(undefined4 *)(unaff_gp + -0x7fcc);
  }
  dVar3 = (double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x24);
  if (dVar3 <= (double)CONCAT44(uVar8,uVar9)) {
    fVar6 = *(float *)(unaff_gp + -0x7ed0);
  }
  else {
    fVar6 = *(float *)(unaff_gp + -0x7ed0);
    *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x24) = (float)(dVar3 - (double)fVar6);
  }
  dVar3 = (double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x28);
  if ((double)CONCAT44(uVar8,uVar9) < dVar3) {
    *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x28) = (float)(dVar3 - (double)fVar6);
  }
  dVar3 = *(double *)(unaff_gp + -0x7fb8);
  dVar4 = (double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x24);
  if (dVar4 < dVar3) {
    *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x24) = (float)(dVar4 + (double)fVar6);
  }
  dVar4 = (double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x28);
  if (dVar4 < dVar3) {
    *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x28) = (float)(dVar4 + (double)fVar6);
  }
  func_0x0f402558(-*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x24),param_1,0x78);
  func_0x0f402558(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x28),param_1,0x79);
  uVar7 = *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x30);
  func_0x0f402278(uVar7,uVar7);
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x78) != 0) {
    uVar7 = *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x7c);
    func_0x0f402278(uVar7,uVar7);
  }
  iVar2 = *(int *)(unaff_gp + -0x7e98);
  if (*(int *)(iVar2 + 0x80) != 0) {
    func_0x0f402298(*(undefined4 *)(iVar2 + 0x84),*(undefined4 *)(iVar2 + 0x88));
  }
  return;
}



void FUN_00402f00(void)

{
  func_0x0f402098(0);
  func_0x0f402120();
  func_0x0f402518();
  func_0x0f402230();
  FUN_00402fbc();
  FUN_00401504();
  func_0x0f402228();
  func_0x0f402288();
  return;
}



void FUN_00402f60(void)

{
  int unaff_gp;
  
  *(float *)(unaff_gp + -0x7b28) = *(float *)(unaff_gp + -0x7ec8);
  *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x4c) =
       (float)((double)*(float *)(unaff_gp + -0x7ec8) / *(double *)(unaff_gp + -0x7fa8));
  *(undefined4 *)(unaff_gp + -0x7b58) = 0;
  *(undefined4 *)(unaff_gp + -0x7b54) = 0;
  *(undefined4 *)(unaff_gp + -0x7b50) = 0;
  *(undefined4 *)(unaff_gp + -0x7b5c) = *(undefined4 *)(unaff_gp + -0x7ec4);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x50) = 600;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x54) = 3;
  return;
}



void FUN_00402fbc(void)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int unaff_gp;
  double dVar7;
  float fVar8;
  undefined4 uVar9;
  double dVar10;
  undefined8 uVar11;
  
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x18) == 0) {
    fVar8 = *(float *)(unaff_gp + -0x7b60);
  }
  else {
    fVar8 = *(float *)(unaff_gp + -0x7b60) + *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x4c);
  }
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x1c) != 0) {
    fVar8 = fVar8 - *(float *)(*(int *)(unaff_gp + -0x7e98) + 0x4c);
  }
  *(float *)(unaff_gp + -0x7b60) = fVar8 - fVar8 * *(float *)(unaff_gp + -0x7b5c);
  iVar2 = func_0x0f401140(0x10a);
  *(int *)(unaff_gp + -0x7b40) = iVar2 - *(int *)(*(int *)(unaff_gp + -0x7e98) + 8);
  iVar3 = func_0x0f401140(0x10b);
  piVar5 = *(int **)(unaff_gp + -0x7e98);
  iVar4 = *piVar5;
  iVar2 = iVar4;
  if (iVar4 < 0) {
    iVar2 = iVar4 + 1;
  }
  iVar6 = piVar5[3];
  *(float *)(unaff_gp + -0x7b20) =
       *(float *)(unaff_gp + -0x7b20) +
       (float)(((double)(*(int *)(unaff_gp + -0x7b40) - (iVar2 >> 1)) *
               (double)CONCAT44(*(undefined4 *)(unaff_gp + -0x7fa0),
                                *(undefined4 *)(unaff_gp + -0x7f9c))) / (double)iVar4);
  iVar4 = piVar5[1];
  *(int *)(unaff_gp + -0x7b3c) = iVar3 - iVar6;
  iVar2 = iVar4;
  if (iVar4 < 0) {
    iVar2 = iVar4 + 1;
  }
  fVar8 = (float)(((double)((iVar3 - iVar6) - (iVar2 >> 1)) * *(double *)(unaff_gp + -0x7f98)) /
                 (double)iVar4);
  *(float *)(unaff_gp + -0x7b24) = fVar8;
  dVar7 = (double)FUN_0040d178(((double)fVar8 * *(double *)(unaff_gp + -0x7f90)) /
                               *(double *)(unaff_gp + -0x7f88));
  iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x54);
  if (iVar2 == 1) {
    *(float *)(unaff_gp + -0x7b58) =
         *(float *)(unaff_gp + -0x7b58) - (float)dVar7 * *(float *)(unaff_gp + -0x7b60);
  }
  else if (iVar2 == 2) {
    *(float *)(unaff_gp + -0x7b54) =
         *(float *)(unaff_gp + -0x7b54) - (float)dVar7 * *(float *)(unaff_gp + -0x7b60);
  }
  else if (iVar2 == 3) {
    *(float *)(unaff_gp + -0x7b50) =
         *(float *)(unaff_gp + -0x7b50) - (float)dVar7 * *(float *)(unaff_gp + -0x7b60);
  }
  func_0x0f402fa0(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x50),
                  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x6c),0x3dcccccd,
                  *(float *)(unaff_gp + -0x7b28) * *(float *)(unaff_gp + -0x7ec0));
  dVar7 = (double)FUN_0040d178(((double)*(float *)(unaff_gp + -0x7b20) *
                               *(double *)(unaff_gp + -0x7f90)) / *(double *)(unaff_gp + -0x7f88));
  fVar8 = (float)dVar7 * *(float *)(unaff_gp + -0x7b60);
  dVar10 = ((double)*(float *)(unaff_gp + -0x7b20) * *(double *)(unaff_gp + -0x7f90)) /
           *(double *)(unaff_gp + -0x7f88);
  dVar7 = (double)FUN_0040d120(dVar10);
  fVar1 = (float)dVar7 * *(float *)(unaff_gp + -0x7b60);
  uVar11 = CONCAT44((int)((ulonglong)dVar10 >> 0x20),*(undefined4 *)(unaff_gp + -0x7b24));
  func_0x0f402558(uVar11);
  uVar11 = CONCAT44((int)((ulonglong)uVar11 >> 0x20),*(undefined4 *)(unaff_gp + -0x7b20));
  func_0x0f402558(uVar11);
  uVar9 = (undefined4)((ulonglong)uVar11 >> 0x20);
  iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x54);
  if (iVar2 == 1) {
    func_0x0f402270(900,0x7a);
    *(float *)(unaff_gp + -0x7b54) = *(float *)(unaff_gp + -0x7b54) - fVar8;
    *(float *)(unaff_gp + -0x7b50) = *(float *)(unaff_gp + -0x7b50) - fVar1;
  }
  else if (iVar2 == 2) {
    *(float *)(unaff_gp + -0x7b58) = *(float *)(unaff_gp + -0x7b58) + fVar8;
    *(float *)(unaff_gp + -0x7b50) = *(float *)(unaff_gp + -0x7b50) - fVar1;
  }
  else if (iVar2 == 3) {
    func_0x0f402270(0xfffffc7c,0x78);
    *(float *)(unaff_gp + -0x7b58) = *(float *)(unaff_gp + -0x7b58) + fVar8;
    *(float *)(unaff_gp + -0x7b54) = *(float *)(unaff_gp + -0x7b54) + fVar1;
  }
  func_0x0f402298(CONCAT44(uVar9,-*(float *)(unaff_gp + -0x7b58)),-*(float *)(unaff_gp + -0x7b54));
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x58) = *(undefined4 *)(unaff_gp + -0x7b58);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x5c) = *(undefined4 *)(unaff_gp + -0x7b54);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x60) = *(undefined4 *)(unaff_gp + -0x7b50);
  return;
}



void FUN_00403440(void)

{
  func_0x0f4015d0(0,1,0x3c,&DAT_10000760);
  func_0x0f4015d0(100,1,0x38,&DAT_10000728);
  func_0x0f4015d0(200,1,0x28,&DAT_10000700);
  func_0x0f402570(1000,1);
  func_0x0f402570(0x44c,1);
  return;
}



void FUN_004034b8(int param_1)

{
  func_0x0f402570(0x4b0,param_1 != 0);
  return;
}



void FUN_004034f0(void)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = func_0x0f801208(2000);
  *(int *)(unaff_gp + -0x7b10) = iVar1;
  if (iVar1 == 0) {
    FUN_004092d4(s_MatInitialize_1000094c);
  }
  *(undefined4 *)(unaff_gp + -0x7b0c) = 0;
  iVar1 = func_0x0f801208(1000);
  *(int *)(unaff_gp + -0x7b08) = iVar1;
  if (iVar1 == 0) {
    FUN_004092d4(s_MatInitialize_1000095c);
  }
  *(undefined4 *)(unaff_gp + -0x7b04) = *(undefined4 *)(unaff_gp + -0x7b08);
  iVar1 = func_0x0f801208(0x640);
  *(int *)(unaff_gp + -0x7b00) = iVar1;
  if (iVar1 == 0) {
    FUN_004092d4(s_MatInitialize_1000096c);
  }
  *(undefined4 *)(unaff_gp + -0x7afc) = *(undefined4 *)(unaff_gp + -0x7b00);
  *(undefined4 *)(unaff_gp + -0x7af8) = 1;
  *(undefined4 *)(unaff_gp + -0x7af4) = 1;
  *(undefined4 *)(unaff_gp + -0x7af0) = 1;
  return;
}



undefined4 FUN_00403584(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_gp;
  int local_4;
  
  if (*(int *)(unaff_gp + -0x7d34) == 0) {
    uVar1 = FUN_004043bc(s_DEFMATERIAL_1000097c);
    *(undefined4 *)(unaff_gp + -0x7adc) = uVar1;
    uVar1 = FUN_004043bc(s_DEFLIGHT_10000988);
    *(undefined4 *)(unaff_gp + -0x7ad8) = uVar1;
    uVar1 = FUN_004043bc(s_DEFLMODEL_10000994);
    *(undefined4 *)(unaff_gp + -0x7ad4) = uVar1;
    *(undefined4 *)(unaff_gp + -0x7d34) = 1;
  }
  FUN_0040406c(param_1,param_2);
  iVar2 = FUN_004040d0(&local_4);
  while (iVar2 != 0) {
    iVar2 = *(int *)(local_4 + 4);
    if ((iVar2 == 0) ||
       (((*(int *)(unaff_gp + -0x7adc) != iVar2 && (*(int *)(unaff_gp + -0x7ad8) != iVar2)) &&
        (*(int *)(unaff_gp + -0x7ad4) != iVar2)))) {
      FUN_00403ffc(s_syntax_error__expected_DEF____100009a0);
    }
    else {
      FUN_00403bf8(local_4);
    }
    iVar2 = FUN_004040d0(&local_4);
  }
  return 1;
}



void FUN_00403684(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_gp;
  
  iVar4 = 0;
  if (0 < *(int *)(unaff_gp + -0x7b0c)) {
    iVar3 = 0;
    do {
      piVar1 = (int *)(*(int *)(unaff_gp + -0x7b10) + iVar3);
      func_0x0f4015d0(*piVar1,piVar1[4],piVar1[3],piVar1[2]);
      iVar2 = *piVar1;
      if (iVar2 != 0) {
        if (iVar2 == 100) {
          if (piVar1[4] < 9) {
            func_0x0f402570(piVar1[4] + 1099);
          }
          else {
            func_0x0f801150(&DAT_100036b4,s_MatDefineAll__only_8_lights_allo_100009cc);
          }
        }
        else if (iVar2 == 200) {
          iVar2 = piVar1[4];
          if (iVar2 != 1) {
            func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100009f4,s_MatDefineAll_10000a08);
            FUN_0040d3c0(1);
            iVar2 = piVar1[4];
          }
          func_0x0f402570(0x4b0,iVar2);
        }
        else {
          FUN_004092d4(s_MatDefineAll__deftype__d_10000a18);
        }
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x14;
    } while (iVar4 < *(int *)(unaff_gp + -0x7b0c));
  }
  return;
}



int * FUN_0040381c(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_gp;
  
  iVar4 = 0;
  if (0 < *(int *)(unaff_gp + -0x7b0c)) {
    iVar3 = 0;
    do {
      piVar1 = (int *)(*(int *)(unaff_gp + -0x7b10) + iVar3);
      if ((*piVar1 == 0) && (iVar2 = func_0x0f8012e8(param_1,piVar1[1]), iVar2 == 0)) {
        return piVar1;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x14;
    } while (iVar4 < *(int *)(unaff_gp + -0x7b0c));
  }
  return (int *)0x0;
}



void FUN_00403938(int param_1)

{
  func_0x0f402570(1000,*(undefined4 *)(param_1 + 0x10));
  return;
}



undefined4 FUN_00403960(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int unaff_gp;
  
  uVar2 = *(undefined4 *)(unaff_gp + -0x7b04);
  iVar1 = func_0x0f801308(param_1);
  if (999 - (*(int *)(unaff_gp + -0x7b04) - *(int *)(unaff_gp + -0x7b08)) <= iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000a34,s_AddString_10000a48);
    FUN_0040d3c0(1);
  }
  func_0x0f801320(uVar2,param_1,iVar1 + 1);
  *(int *)(unaff_gp + -0x7b04) = *(int *)(unaff_gp + -0x7b04) + iVar1 + 1;
  return uVar2;
}



undefined4 * FUN_004039f8(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int unaff_gp;
  
  puVar1 = *(undefined4 **)(unaff_gp + -0x7afc);
  iVar2 = (int)puVar1 - *(int *)(unaff_gp + -0x7b00);
  if (iVar2 < 0) {
    iVar2 = iVar2 + 3;
  }
  if (399 < iVar2 >> 2) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000a54,s_AddFloat_10000a68);
    FUN_0040d3c0(1);
    puVar1 = *(undefined4 **)(unaff_gp + -0x7afc);
  }
  *puVar1 = param_1;
  *(undefined4 **)(unaff_gp + -0x7afc) = puVar1 + 1;
  return puVar1;
}



int * FUN_00403a78(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int unaff_gp;
  
  if (99 < *(int *)(unaff_gp + -0x7b0c)) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000a74,s_AddMaterial_10000a88);
    FUN_0040d3c0(1);
  }
  piVar2 = (int *)(*(int *)(unaff_gp + -0x7b10) + *(int *)(unaff_gp + -0x7b0c) * 0x14);
  iVar1 = FUN_00403960(param_1);
  piVar2[1] = iVar1;
  piVar2[2] = 0;
  piVar2[3] = 0;
  *piVar2 = param_2;
  if (param_2 == 0) {
    iVar1 = *(int *)(unaff_gp + -0x7af8);
    piVar2[4] = iVar1;
    *(int *)(unaff_gp + -0x7af8) = iVar1 + 1;
  }
  else if (param_2 == 100) {
    iVar1 = *(int *)(unaff_gp + -0x7af4);
    piVar2[4] = iVar1;
    *(int *)(unaff_gp + -0x7af4) = iVar1 + 1;
  }
  else if (param_2 == 200) {
    piVar2[4] = *(int *)(unaff_gp + -0x7af0);
  }
  else {
    FUN_004092d4(s_AddMaterial__deftype__d_10000a94,param_2);
  }
  *(int *)(unaff_gp + -0x7b0c) = *(int *)(unaff_gp + -0x7b0c) + 1;
  return piVar2;
}



void FUN_00403b9c(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    uVar1 = FUN_004039f8(param_2);
    *(undefined4 *)(param_1 + 8) = uVar1;
  }
  else {
    FUN_004039f8(param_2);
  }
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  return;
}



undefined4 FUN_00403bf8(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_gp;
  double dVar3;
  uint in_fcsr;
  undefined4 *local_res0 [4];
  
  local_res0[0] = param_1;
  if (*(int *)(unaff_gp + -0x7acc) == 0) {
    uVar1 = FUN_004043bc(unaff_gp + -0x7d20);
    *(undefined4 *)(unaff_gp + -0x7ad0) = uVar1;
    *(undefined4 *)(unaff_gp + -0x7acc) = 1;
  }
  dVar3 = (double)*(float *)(local_res0[0][1] + 4) + *(double *)(unaff_gp + -0x7fe0);
  if ((((in_fcsr | 3) ^ 2) & 3) == 0) {
    dVar3 = ROUND(dVar3);
  }
  else {
    dVar3 = FLOOR(dVar3);
  }
  iVar2 = FUN_004040d0(local_res0);
  if (iVar2 == 0) {
    FUN_00403ffc(s_syntax_error__premature_EOF_10000aac);
  }
  uVar1 = FUN_00403a78(*local_res0[0],(int)dVar3);
  iVar2 = FUN_00404370(local_res0);
  if (iVar2 == 0) {
    FUN_00403ffc(s_syntax_error__premature_EOF_10000ac8);
  }
  iVar2 = local_res0[0][1];
  if ((iVar2 != 0) && (*(int *)(unaff_gp + -0x7ad0) != iVar2)) {
    do {
      FUN_00403e28(uVar1);
      iVar2 = FUN_00404370(local_res0);
      if (iVar2 == 0) {
        FUN_00403ffc(s_syntax_error__premature_EOF_10000ae4);
      }
      iVar2 = local_res0[0][1];
    } while ((iVar2 != 0) && (*(int *)(unaff_gp + -0x7ad0) != iVar2));
  }
  if (iVar2 == 0) {
    FUN_00403ffc(s_expected_a_keyword_10000b00);
  }
  iVar2 = FUN_004040d0(local_res0);
  if (iVar2 == 0) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000b14,s_ParseDef__expected_ok_10000b28);
    FUN_0040d3c0(1);
  }
  iVar2 = local_res0[0][1];
  if (iVar2 == 0) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000b40,s_ParseDef__expected_keyword_10000b54
                   );
    FUN_0040d3c0(1);
    iVar2 = local_res0[0][1];
  }
  if (*(float *)(iVar2 + 4) != 0.0) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000b70,s_ParseDef_10000b84);
    FUN_0040d3c0(1);
  }
  FUN_00403b9c(uVar1,0);
  return 1;
}



undefined4 FUN_00403e28(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  float fVar5;
  int local_1c;
  float local_18;
  uint local_8;
  int *local_4;
  
  iVar1 = FUN_004040d0(&local_4);
  if (iVar1 == 0) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000b90,s_ParseStmt_10000ba4);
    FUN_0040d3c0(1);
  }
  iVar1 = *param_1;
  if (iVar1 == 0) {
    local_8 = 1;
  }
  else if (iVar1 == 100) {
    local_8 = 2;
  }
  else if (iVar1 == 200) {
    local_8 = 4;
  }
  else {
    FUN_004092d4(s_ParseStmt__deftype__d_10000bb0);
  }
  iVar1 = local_4[1];
  if (iVar1 == 0) {
    FUN_00403ffc(s_keyword_expected_10000c2c);
  }
  else if ((*(uint *)(iVar1 + 0xc) & local_8) == 0) {
    FUN_00403ffc(s_this_keyword_not_allowed_here_10000c0c);
  }
  else {
    FUN_00403b9c(param_1,*(undefined4 *)(iVar1 + 4));
    iVar1 = *(int *)(local_4[1] + 8);
    if (iVar1 < 0) {
      FUN_00403ffc(s_syntax_error_10000bc8);
    }
    iVar3 = 0;
    if (0 < iVar1) {
      do {
        iVar2 = FUN_004040d0(&local_4);
        if (iVar2 == 0) {
          FUN_00403ffc(s_premature_EOF__expected_a_float_10000bd8);
        }
        dVar4 = (double)FUN_0040d830(*local_4,&local_1c);
        fVar5 = (float)dVar4;
        if (local_1c == *local_4) {
          local_18 = (float)dVar4;
          FUN_00403ffc(s_expected_a_float_10000bf8);
          fVar5 = local_18;
        }
        FUN_00403b9c(param_1,fVar5);
        iVar3 = iVar3 + 1;
      } while (iVar3 != iVar1);
    }
  }
  return 1;
}



void FUN_00403ffc(undefined4 param_1)

{
  int unaff_gp;
  
  func_0x0f801150(&DAT_100036b4,s_Error__file__s__line__d__char__d_10000c40,
                  *(undefined4 *)(unaff_gp + -0x7ae8),DAT_10004678,DAT_1000467c,param_1);
  func_0x0f801150(&DAT_100036b4,s_________s_10000c68,&DAT_10004570);
  FUN_0040d3c0(0xffffffff);
  return;
}



void FUN_0040406c(undefined4 param_1,undefined4 param_2)

{
  int unaff_gp;
  
  *(undefined4 *)(unaff_gp + -0x7aec) = param_1;
  *(undefined4 *)(unaff_gp + -0x7ae8) = param_2;
  *(undefined4 *)(unaff_gp + -0x7ae4) = 0;
  *(undefined4 *)(unaff_gp + -0x7ae0) = 0;
  DAT_10004570 = 0;
  *(undefined4 *)(unaff_gp + -0x7d38) = 0;
  return;
}



bool FUN_0040408c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = func_0x0f8010d8(param_1,param_2,*(undefined4 *)(unaff_gp + -0x7aec));
  if (iVar1 != 0) {
    *(int *)(unaff_gp + -0x7ae4) = *(int *)(unaff_gp + -0x7ae4) + 1;
  }
  return iVar1 != 0;
}



undefined4 FUN_004040d0(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined *puVar7;
  int unaff_gp;
  
  pbVar5 = *(byte **)(unaff_gp + -0x7d38);
  if (pbVar5 == (byte *)0x0) {
    pbVar5 = &DAT_10004570;
    iVar3 = FUN_0040408c(&DAT_10004570,0x100);
    if (iVar3 == 0) {
      DAT_10004680 = 0;
      return 0;
    }
  }
  if (*(int *)(unaff_gp + -0x7ae0) != 0) {
    *(byte **)(unaff_gp + -0x7d38) = pbVar5;
    *(undefined4 *)(unaff_gp + -0x7ae0) = 0;
    *param_1 = &DAT_10004670;
    return DAT_10004680;
  }
  uVar2 = (uint)*pbVar5;
  puVar4 = &DAT_100032e0 + uVar2;
  bVar1 = (&DAT_100032e1)[uVar2];
  while ((((bVar1 & 8) != 0 || (uVar2 == 0)) || (uVar2 == 0x23))) {
    if (puVar4 == &DAT_100032e0) {
      *(byte **)(unaff_gp + -0x7d38) = pbVar5;
LAB_004041bc:
      iVar3 = FUN_0040408c(&DAT_10004570,0x100);
      if (iVar3 == 0) {
        DAT_10004680 = 0;
        return 0;
      }
      pbVar5 = &DAT_10004570;
    }
    else {
      if (puVar4 == (undefined1 *)0x10003303) {
        *(byte **)(unaff_gp + -0x7d38) = pbVar5;
        goto LAB_004041bc;
      }
      pbVar5 = pbVar5 + 1;
    }
    uVar2 = (uint)*pbVar5;
    puVar4 = &DAT_100032e0 + uVar2;
    bVar1 = (&DAT_100032e1)[uVar2];
  }
  puVar7 = &DAT_10004688;
  if (uVar2 == 0) {
    *(byte **)(unaff_gp + -0x7d38) = pbVar5;
  }
  else {
    pbVar6 = pbVar5;
    if (((&DAT_100032e1)[uVar2] & 8) == 0) {
      do {
        *puVar7 = (char)uVar2;
        uVar2 = (uint)pbVar6[1];
        puVar7 = puVar7 + 1;
        pbVar6 = pbVar6 + 1;
        if (uVar2 == 0) {
          *(byte **)(unaff_gp + -0x7d38) = pbVar6;
          goto LAB_00404290;
        }
      } while (((&DAT_100032e1)[uVar2] & 8) == 0);
      *(byte **)(unaff_gp + -0x7d38) = pbVar6;
    }
    else {
      *(byte **)(unaff_gp + -0x7d38) = pbVar5;
      puVar7 = &DAT_10004688;
    }
  }
LAB_00404290:
  *puVar7 = 0;
  if (uVar2 == 0) {
    iVar3 = FUN_0040408c(&DAT_10004570,0x100);
    if (iVar3 == 0) {
      DAT_10004680 = 0;
      return 0;
    }
    *(undefined1 **)(unaff_gp + -0x7d38) = &DAT_10004570;
  }
  DAT_10004670 = &DAT_10004688;
  DAT_10004678 = *(undefined4 *)(unaff_gp + -0x7ae4);
  DAT_1000467c = pbVar5 + -0x1000456f;
  DAT_10004674 = (undefined4 *)0x0;
  if ((((&DAT_100032e1)[DAT_10004688] & 3) != 0) &&
     (DAT_10004674 = (undefined4 *)FUN_004043bc(&DAT_10004688), DAT_10004674 != (undefined4 *)0x0))
  {
    DAT_10004670 = (undefined1 *)*DAT_10004674;
  }
  DAT_10004680 = 1;
  *param_1 = &DAT_10004670;
  return 1;
}



undefined4 FUN_00404370(undefined4 *param_1)

{
  undefined4 uVar1;
  int unaff_gp;
  
  if (*(int *)(unaff_gp + -0x7ae0) == 0) {
    uVar1 = FUN_004040d0();
    *(undefined4 *)(unaff_gp + -0x7ae0) = 1;
  }
  else {
    *param_1 = &DAT_10004670;
    uVar1 = DAT_10004680;
  }
  return uVar1;
}



undefined ** FUN_004043bc(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  undefined **ppuVar3;
  int iVar4;
  undefined **ppuVar5;
  
  bVar1 = false;
  ppuVar5 = &PTR_s_DEFMATERIAL_100007e0;
  iVar4 = 0;
  do {
    iVar2 = func_0x0f8012e8(param_1,*ppuVar5);
    iVar4 = iVar4 + 1;
    if (iVar2 == 0) {
      bVar1 = true;
      break;
    }
    ppuVar5 = ppuVar5 + 4;
  } while (iVar4 != 0xf);
  ppuVar3 = (undefined **)0x0;
  if (bVar1) {
    ppuVar3 = ppuVar5;
  }
  return ppuVar3;
}



undefined4 * FUN_00404460(void)

{
  undefined4 *puVar1;
  int unaff_gp;
  
  puVar1 = *(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xfc);
  *(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xfc) = puVar1 + 3;
  if (0x2de5 < ((int)puVar1 - *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf4)) / 0xc) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000c80,s_CreateCell_10000c94);
    FUN_0040d3c0(1);
  }
  *puVar1 = 0;
  puVar1[1] = 0;
  return puVar1;
}



int FUN_004044f0(int param_1)

{
  int iVar1;
  int iVar2;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x100);
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x100) = iVar1 + param_1 * 4;
  iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x100) -
          *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf8);
  if (iVar2 < 0) {
    iVar2 = iVar2 + 3;
  }
  if (0x89544 < iVar2 >> 2) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000ca0,s_CreateData_10000cb4);
    FUN_0040d3c0(1);
  }
  return iVar1;
}



void FUN_00404580(void)

{
  undefined4 uVar1;
  int unaff_gp;
  
  uVar1 = func_0x0f801208(0x226c8);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf4) = uVar1;
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf4) == 0) {
    FUN_004092d4(s_SetupFilter__ALLOCN_cullPolygonA_10000cc0);
  }
  uVar1 = func_0x0f801208(0x225510);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf8) = uVar1;
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf8) == 0) {
    FUN_004092d4(s_SetupFilter__ALLOCN_cullDataArra_10000cec);
  }
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xfc) =
       *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf4);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x100) =
       *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf8);
  if ((*(uint *)(*(int *)(unaff_gp + -0x7e98) + 0xf8) & 0xf) != 0) {
    func_0x0f801150(&DAT_100036b4,s_SetupFilter__cullDataArray_not_q_10000d18);
  }
  return;
}



undefined4 FUN_00404668(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int unaff_gp;
  undefined4 *local_18 [5];
  undefined4 local_4;
  
  local_4 = FUN_0040a400();
  puVar2 = (undefined4 *)func_0x0f801208(0x10);
  if (puVar2 == (undefined4 *)0x0) {
    FUN_004092d4(unaff_gp + -0x7d10);
  }
  *puVar2 = 0x109;
  puVar2[2] = 0;
  FUN_0040a6d4(local_4,puVar2);
  iVar3 = FUN_0040a8e0(param_1);
  if (*(code **)(iVar3 + 4) == FUN_00408ab0) {
    puVar2[1] = FUN_00408ab0;
    puVar2[3] = 4;
  }
  else if (*(code **)(iVar3 + 4) == FUN_00408840) {
    puVar2[1] = FUN_00408840;
    puVar2[3] = 2;
  }
  else {
    func_0x0f801150(&DAT_100036b4,s_Filter__only_lighted_or_shaded_p_10000d4c);
    FUN_0040d3c0(0xffffffff);
  }
  puVar4 = (undefined4 *)FUN_00404460();
  *puVar4 = 0;
  local_18[0] = (undefined4 *)0x0;
  iVar3 = FUN_0040a8e0(param_1);
  puVar1 = puVar4;
  while (iVar3 != 0) {
    if (*(code **)(iVar3 + 4) == FUN_00408ab0) {
      FUN_0040493c(*(undefined4 *)(iVar3 + 8),puVar1,local_18,param_2);
    }
    else if (*(code **)(iVar3 + 4) == FUN_00408840) {
      FUN_00404a4c(*(undefined4 *)(iVar3 + 8),puVar1,local_18,param_2);
    }
    else {
      func_0x0f801150(&DAT_100036b4,s_Filter__all_polygons_must_be_the_10000d80);
      FUN_0040d3c0(0xffffffff);
    }
    puVar1 = local_18[0];
    iVar3 = FUN_0040a918(param_1);
  }
  puVar2[2] = *puVar4;
  return local_4;
}



undefined4 * FUN_00404848(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  puVar1 = (undefined4 *)FUN_00404460();
  puVar2 = (undefined4 *)FUN_004044f0(*(undefined4 *)(param_1 + 8));
  puVar1[1] = puVar2;
  iVar4 = 0;
  puVar1[2] = *(undefined4 *)(param_1 + 8);
  *param_2 = puVar1;
  *puVar1 = 0;
  puVar3 = *(undefined4 **)(param_1 + 4);
  if (0 < *(int *)(param_1 + 8)) {
    do {
      iVar4 = iVar4 + 1;
      *puVar2 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar4 < *(int *)(param_1 + 8));
  }
  return puVar1;
}



int FUN_0040493c(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != (undefined4 *)0x0) {
    do {
      if (param_1[2] == 0x18) {
        if (param_4 == 1) {
          param_2 = FUN_00404848(param_1,param_2);
          iVar1 = iVar1 + 1;
          param_1 = (undefined4 *)*param_1;
        }
        else {
          FUN_004092d4(s_FilterLightedPolygon__bad_filter_10000de8);
          param_1 = (undefined4 *)*param_1;
        }
      }
      else {
        func_0x0f801150(&DAT_100036b4,s_FilterLightedPolygon__not_a_4_si_10000db0);
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  *param_3 = param_2;
  return iVar1;
}



int FUN_00404a4c(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != (undefined4 *)0x0) {
    do {
      if (param_1[2] == 0x10) {
        if (param_4 == 1) {
          param_2 = FUN_00404848(param_1,param_2);
          iVar1 = iVar1 + 1;
          param_1 = (undefined4 *)*param_1;
        }
        else {
          FUN_004092d4(s_FilterShadedPolygon__bad_case_10000e48);
          param_1 = (undefined4 *)*param_1;
        }
      }
      else {
        func_0x0f801150(&DAT_100036b4,s_FilterShadedPolygon__not_a_4_sid_10000e10);
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  *param_3 = param_2;
  return iVar1;
}



void FUN_00404b60(undefined4 *param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int unaff_gp;
  int iVar7;
  undefined auStackX_0 [16];
  undefined local_344 [800];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  int local_4;
  
  iVar4 = *(int *)(unaff_gp + -0x7e98);
  iVar7 = (*(int *)(iVar4 + 0xfc) - *(int *)(iVar4 + 0xf4)) / 0xc;
  local_24 = 0x13577531;
  local_20 = 0x10002;
  local_1c = 0x10;
  local_18 = 0xc;
  local_10 = *(undefined4 *)(iVar4 + 0xf4);
  iVar2 = *(int *)(iVar4 + 0x100) - *(int *)(iVar4 + 0xf8);
  local_c = *(undefined4 *)(iVar4 + 0xf8);
  if (iVar2 < 0) {
    iVar2 = iVar2 + 3;
  }
  iVar2 = iVar2 >> 2;
  local_14 = param_2;
  local_8 = iVar7;
  local_4 = iVar2;
  func_0x0f801250(s_Write___File__header__10000e70);
  func_0x0f801250(s_numInst__d_10000e88,local_14);
  func_0x0f801250(s_polygonArraySize__d_10000e98,local_8);
  func_0x0f801250(s_dataArraySize__d_10000eb0,local_4);
  iVar4 = func_0x0f801198(&local_24,0x24,1,param_3);
  if (iVar4 != 1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000ec4,
                    s_Write___File__error_on_header_10000ed8);
    FUN_0040d3c0(1);
  }
  iVar4 = 0;
  puVar3 = (undefined *)register0x00000074;
  puVar5 = param_1;
  if (0 < local_14) {
    do {
      uVar1 = FUN_0040ade4(*puVar5);
      iVar4 = iVar4 + 1;
      *(undefined4 *)(puVar3 + -0x344) = uVar1;
      puVar3 = puVar3 + 4;
      puVar5 = puVar5 + 1;
    } while (iVar4 < local_14);
  }
  iVar6 = 0;
  iVar4 = func_0x0f801198(local_344,4,local_14,param_3);
  if (iVar4 != local_14) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000ef8,s_Write___File_10000f0c);
    FUN_0040d3c0(1);
  }
  if (0 < local_14) {
    do {
      iVar4 = FUN_0040a8e0(*param_1);
      while (iVar4 != 0) {
        iVar4 = func_0x0f801198(iVar4,0x10,1,param_3);
        if (iVar4 != 1) {
          func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000f1c,s_Write___File_10000f30);
          FUN_0040d3c0(1);
        }
        iVar4 = FUN_0040a918(*param_1);
      }
      iVar6 = iVar6 + 1;
      param_1 = param_1 + 1;
    } while (iVar6 < local_14);
  }
  iVar4 = func_0x0f801198(local_10,0xc,iVar7,param_3);
  if (iVar4 != iVar7) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000f40,s_Write___File_10000f54);
    FUN_0040d3c0(1);
  }
  iVar4 = func_0x0f801198(local_c,4,iVar2,param_3);
  if (iVar4 != iVar2) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000f64,s_Write___File_10000f78);
    FUN_0040d3c0(1);
  }
  return;
}



undefined4 * FUN_00404e78(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  undefined4 local_res0;
  int *local_res4;
  int local_358;
  int local_344 [200];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  local_res0 = param_1;
  local_res4 = param_2;
  iVar1 = func_0x0f801168(&local_24,0x24,1,param_1);
  if (iVar1 != 1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10000f88,
                    s_Read___File__error_on_header_10000f9c);
    FUN_0040d3c0(1);
  }
  if (local_24 == 0x13577531) {
    if (local_20 == 0x10002) {
      if (local_1c == 0x10) {
        if (local_18 == 0xc) {
          if ((local_14 < 1) || (200 < local_14)) {
            func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_1000106c,
                            s_Read___File__bad_header_numInst_10001080);
            FUN_0040d3c0(1);
          }
          iVar1 = func_0x0f801168(local_344,4,local_14,local_res0);
          if (iVar1 != local_14) {
            func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100010a0,
                            s_Read___File__error_on_instSizeTa_100010b4);
            FUN_0040d3c0(1);
          }
          puVar2 = (undefined4 *)func_0x0f801208(local_14 << 2);
          if (puVar2 == (undefined4 *)0x0) {
            FUN_004092d4(s_Read___File__ALLOCN_100010d8);
          }
          piVar3 = (int *)func_0x0f801208(local_8 * 0xc);
          if (piVar3 == (int *)0x0) {
            FUN_004092d4(s_Read___File__ALLOCN_100010ec);
          }
          uVar4 = func_0x0f801208(local_4 * 4 + 0xc);
          if (uVar4 == 0) {
            FUN_004092d4(s_Read___File__ALLOCN_10001100);
          }
          uVar5 = uVar4 & 0xf;
          if (uVar5 == 4) {
            uVar4 = uVar4 + 0xc;
            uVar5 = uVar4 & 0xf;
          }
          else if (uVar5 == 8) {
            uVar4 = uVar4 + 8;
            uVar5 = uVar4 & 0xf;
          }
          else if (uVar5 == 0xc) {
            uVar4 = uVar4 + 4;
            uVar5 = uVar4 & 0xf;
          }
          if (uVar5 != 0) {
            func_0x0f801150(&DAT_100036b4,s_Read___File__dataArray_not_quad__10001114,uVar4);
          }
          local_358 = 0;
          puVar10 = puVar2;
          if (0 < local_14) {
            do {
              iVar1 = 0;
              uVar6 = FUN_0040a400();
              *puVar10 = uVar6;
              if (0 < *(int *)((int)register0x00000074 + -0x344)) {
                do {
                  iVar7 = func_0x0f801208(0x10);
                  if (iVar7 == 0) {
                    FUN_004092d4(s_Read__File_10001144);
                  }
                  iVar8 = func_0x0f801168(iVar7,0x10,1,local_res0);
                  if (iVar8 != 1) {
                    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001150,
                                    s_Read___File__error_on_Entity_10001164);
                    FUN_0040d3c0(1);
                  }
                  iVar8 = (*(int *)(iVar7 + 8) - local_10) / 0xc;
                  if ((iVar8 < 0) || (local_8 <= iVar8)) {
                    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001184,
                                    s_Read___File__bad_pIndex_ep_>data_10001198);
                    FUN_0040d3c0(1);
                  }
                  *(int **)(iVar7 + 8) = piVar3 + iVar8 * 3;
                  *(undefined4 *)(iVar7 + 4) = 0xffffffff;
                  FUN_0040a6d4(*puVar10,iVar7);
                  iVar1 = iVar1 + 1;
                } while (iVar1 < *(int *)((int)register0x00000074 + -0x344));
              }
              local_358 = local_358 + 1;
              register0x00000074 = (BADSPACEBASE *)((int)register0x00000074 + 4);
              puVar10 = puVar10 + 1;
            } while (local_358 < local_14);
          }
          local_358 = 0;
          iVar1 = func_0x0f801168(piVar3,0xc,local_8,local_res0);
          if (iVar1 != local_8) {
            func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100011bc,
                            s_Read___File__error_on_polygonArr_100011d0);
            FUN_0040d3c0(1);
          }
          iVar1 = func_0x0f801168(uVar4,4,local_4,local_res0);
          if (iVar1 != local_4) {
            func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100011f4,
                            s_Read___File__error_on_dataArray_10001208);
            FUN_0040d3c0(1);
          }
          piVar9 = piVar3;
          if (0 < local_8) {
            do {
              if (*piVar9 != 0) {
                iVar1 = (*piVar9 - local_10) / 0xc;
                if ((iVar1 < 0) || (local_8 <= iVar1)) {
                  func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001228,
                                  s_Read___File__bad_pIndex_pp_>next_1000123c);
                  FUN_0040d3c0(1);
                }
                *piVar9 = (int)(piVar3 + iVar1 * 3);
              }
              if (piVar9[1] != 0) {
                iVar1 = piVar9[1] - local_c;
                if (iVar1 < 0) {
                  iVar1 = iVar1 + 3;
                }
                iVar1 = iVar1 >> 2;
                if ((iVar1 < 0) || (local_4 <= iVar1)) {
                  func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001260,
                                  s_Read___File__dIndex_10001274);
                  FUN_0040d3c0(1);
                }
                piVar9[1] = uVar4 + iVar1 * 4;
              }
              local_358 = local_358 + 1;
              piVar9 = piVar9 + 3;
            } while (local_358 < local_8);
          }
          *local_res4 = local_14;
        }
        else {
          func_0x0f801150(&DAT_100036b4,s_Read___File__struct_PolygonCell_s_1000103c);
          puVar2 = (undefined4 *)0x0;
        }
      }
      else {
        func_0x0f801150(&DAT_100036b4,s_Read___File__struct_Entity_size_m_10001010);
        puVar2 = (undefined4 *)0x0;
      }
    }
    else {
      func_0x0f801150(&DAT_100036b4,s_Read___File__bad_version_GView_b_10000fe4);
      puVar2 = (undefined4 *)0x0;
    }
  }
  else {
    func_0x0f801150(&DAT_100036b4,s_Read___File__not_a_GView_binary_f_10000fbc);
    puVar2 = (undefined4 *)0x0;
  }
  return puVar2;
}



undefined4 FUN_004054e0(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_004055d0(&DAT_10001290);
  uVar2 = 0x101;
  if (iVar1 != 0) {
    uVar2 = DAT_10001290;
  }
  return uVar2;
}



void FUN_00405520(undefined4 param_1)

{
  int unaff_gp;
  
  func_0x0f801150(&DAT_100036b4,unaff_gp + -32000,s_gview_10003ed0,param_1);
  func_0x0f801150(&DAT_100036b4,s__line__d__char__d__100012a0,DAT_1000129c,DAT_10001298);
  func_0x0f801150(&DAT_100036b4,s__lookahead_token___d__100012b8,*(undefined4 *)(unaff_gp + -0x7a80)
                 );
  return;
}



bool FUN_00405590(void)

{
  int iVar1;
  
  FUN_00405ec4();
  iVar1 = FUN_00409a00();
  return iVar1 == 0;
}



int FUN_004055d0(int *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *pcVar6;
  int unaff_gp;
  double dVar7;
  int local_18 [5];
  int local_4;
  
  do {
    local_4 = FUN_004057d4(param_1);
    if (local_4 == 0) {
      return 0;
    }
    iVar3 = *param_1;
  } while (iVar3 == 0x122);
  if (iVar3 == 0x120) {
    pcVar6 = (char *)param_1[1];
    bVar2 = false;
    cVar1 = *pcVar6;
    pcVar4 = pcVar6;
    while (cVar1 != '\0') {
      pcVar4 = pcVar4 + 1;
      if (cVar1 == '.') {
        bVar2 = true;
        break;
      }
      cVar1 = *pcVar4;
    }
    if (bVar2) {
      dVar7 = (double)FUN_0040d830(pcVar6,local_18);
      *(float *)(unaff_gp + -0x7a7c) = (float)dVar7;
      if (local_18[0] == param_1[1]) {
        func_0x0f801150(&DAT_100036b4,s__s__bad_real_constant___s___line_10001430,s_gview_10003ed0,
                        param_1[1],param_1[3],param_1[2]);
      }
      *param_1 = 0x119;
    }
    else {
      uVar5 = FUN_0040dcc0(pcVar6,local_18,0);
      *(undefined4 *)(unaff_gp + -0x7a7c) = uVar5;
      if (local_18[0] == param_1[1]) {
        func_0x0f801150(&DAT_100036b4,s__s__bad_integer_constant___s___l_10001460,s_gview_10003ed0,
                        param_1[1],param_1[3],param_1[2]);
      }
      *param_1 = 0x118;
    }
  }
  else if (iVar3 == 0x121) {
    iVar3 = FUN_00405ce8(param_1[1]);
    if (iVar3 == 0) {
      func_0x0f801150(&DAT_100036b4,s__s__identifier___s___line__d__ch_100013f4,s_gview_10003ed0,
                      param_1[1],param_1[3],param_1[2]);
    }
    else {
      *param_1 = iVar3;
    }
  }
  return local_4;
}



undefined4 FUN_004057d4(undefined4 *param_1)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined uVar7;
  int iVar8;
  undefined local_110 [272];
  
  bVar2 = false;
  bVar3 = false;
  iVar8 = 0;
  iVar4 = FUN_00405df8();
  do {
    if (iVar4 == -1) {
      if ((bVar2) || (bVar3)) {
        local_110[iVar8] = 0;
        func_0x0f8012f0(param_1[1],local_110);
        if (bVar2) {
          *param_1 = 0x121;
        }
        else if (bVar3) {
          *param_1 = 0x120;
        }
      }
      else {
        *param_1 = 0;
        *(undefined *)param_1[1] = 0;
        FUN_00405dd0(param_1 + 3,param_1 + 2);
      }
      return 1;
    }
    if (0xff < iVar8) {
      func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001494,
                      s_GetSimpleToken__token_too_big_100014a8);
      FUN_0040d3c0(1);
    }
    bVar1 = (&DAT_100032e1)[iVar4];
    uVar7 = (undefined)iVar4;
    if ((bVar1 & 3) == 0) {
      if ((bVar1 & 4) == 0) {
        if ((bVar1 & 0x10) == 0) {
          if ((bVar1 & 8) == 0) {
            FUN_00405dd0(param_1 + 3,param_1 + 2);
            FUN_00405ed8(s_this_character_is_not_permitted_10001580);
            return 0;
          }
          if ((bVar2) || (bVar3)) {
            local_110[iVar8] = 0;
            func_0x0f8012f0(param_1[1],local_110);
            if (bVar2) {
              *param_1 = 0x121;
            }
            else if (bVar3) {
              *param_1 = 0x120;
            }
            return 1;
          }
        }
        else if ((bVar3) && (iVar4 == 0x2e)) {
          local_110[iVar8] = uVar7;
          iVar8 = iVar8 + 1;
        }
        else {
          if ((bVar2) || ((bVar3 && (iVar4 != 0x2e)))) {
            FUN_00405de8(iVar4);
            local_110[iVar8] = 0;
            func_0x0f8012f0(param_1[1],local_110);
            if (bVar2) {
              *param_1 = 0x121;
            }
            else if (bVar3) {
              *param_1 = 0x120;
            }
            return 1;
          }
          FUN_00405dd0(param_1 + 3,param_1 + 2);
          *(undefined *)param_1[1] = uVar7;
          *(undefined *)(param_1[1] + 1) = 0;
          if (iVar4 == 0x2d) {
            *param_1 = 0x117;
            return 1;
          }
          if (iVar4 != 0x2f) {
            if (iVar4 == 0x5b) {
              *param_1 = 0x11d;
              return 1;
            }
            if (iVar4 == 0x5d) {
              *param_1 = 0x11e;
              return 1;
            }
            if (iVar4 == 0x7b) {
              *param_1 = 0x11b;
              return 1;
            }
            if (iVar4 == 0x7d) {
              *param_1 = 0x11c;
              return 1;
            }
            FUN_00405ed8(s_unexpected_punctuation_character_1000155c);
            return 0;
          }
          iVar4 = FUN_00405df8();
          if (iVar4 != 0x2a) {
            FUN_00405de8(iVar4);
            *param_1 = 0x11f;
            return 1;
          }
          iVar4 = FUN_00405df8();
          if (iVar4 == -1) {
            FUN_00405ed8(s_reached_EOF_before_end_of_commen_10001514);
          }
          iVar5 = FUN_00405df8();
          while (iVar5 != -1) {
            if ((iVar4 == 0x2a) && (iVar5 == 0x2f)) {
              *param_1 = 0x122;
              return 1;
            }
            iVar6 = FUN_00405df8();
            iVar4 = iVar5;
            iVar5 = iVar6;
          }
          FUN_00405ed8(s_reached_EOF_before_end_of_commen_10001538);
        }
      }
      else if ((bVar2) || (bVar3)) {
        local_110[iVar8] = uVar7;
        iVar8 = iVar8 + 1;
      }
      else {
        iVar8 = 1;
        bVar3 = true;
        FUN_00405dd0(param_1 + 3,param_1 + 2);
        local_110[0] = uVar7;
      }
    }
    else if (bVar2) {
      local_110[iVar8] = uVar7;
      iVar8 = iVar8 + 1;
    }
    else if (bVar3) {
      if ((((bVar1 & 0x80) == 0) && (iVar4 != 0x78)) && (iVar4 != 0x58)) {
        func_0x0f801250(s_GetSimpleToken__c___c____d__100014c8,iVar4,iVar4);
        FUN_00405ed8(s_a_letter_is_not_permitted_within_100014e8);
        return 0;
      }
      local_110[iVar8] = uVar7;
      iVar8 = iVar8 + 1;
    }
    else {
      bVar2 = true;
      iVar8 = 1;
      FUN_00405dd0(param_1 + 3,param_1 + 2);
      local_110[0] = uVar7;
    }
    iVar4 = FUN_00405df8();
  } while( true );
}



undefined * FUN_00405ce8(undefined *param_1)

{
  undefined **ppuVar1;
  int iVar2;
  undefined **ppuVar3;
  
  if (DAT_100012d4 != 0) {
    ppuVar3 = &PTR_s_cpack_100012d0;
    do {
      if ((param_1 == *ppuVar3) || (iVar2 = func_0x0f8012e8(param_1), iVar2 == 0)) {
        return ppuVar3[1];
      }
      ppuVar1 = ppuVar3 + 3;
      ppuVar3 = ppuVar3 + 2;
    } while (*ppuVar1 != (undefined *)0x0);
  }
  return (undefined *)0x0;
}



void FUN_00405dd0(undefined4 *param_1,undefined4 *param_2)

{
  int unaff_gp;
  
  *param_1 = *(undefined4 *)(unaff_gp + -0x7ab4);
  *param_2 = *(undefined4 *)(unaff_gp + -0x7ab8);
  return;
}



void FUN_00405de8(undefined4 param_1)

{
  int unaff_gp;
  
  *(undefined4 *)(unaff_gp + -0x7abc) = param_1;
  *(undefined4 *)(unaff_gp + -0x7c70) = 1;
  return;
}



uint FUN_00405df8(void)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int unaff_gp;
  
  if (*(int *)(unaff_gp + -0x7c70) == 0) {
    if (DAT_100041f0 == 0) {
      piVar3 = *(int **)(unaff_gp + -0x7ac0);
      iVar2 = *piVar3;
      *piVar3 = iVar2 + -1;
      if (iVar2 + -1 < 0) {
        uVar1 = func_0x0f8010e0();
      }
      else {
        uVar1 = (uint)*(byte *)piVar3[1];
        piVar3[1] = (int)((byte *)piVar3[1] + 1);
      }
    }
    else {
      uVar1 = func_0x0f8014b0(*(undefined4 *)(unaff_gp + -0x7ac0));
    }
    if (uVar1 == 10) {
      *(undefined4 *)(unaff_gp + -0x7ab8) = 0;
      *(int *)(unaff_gp + -0x7ab4) = *(int *)(unaff_gp + -0x7ab4) + 1;
    }
    else {
      *(int *)(unaff_gp + -0x7ab8) = *(int *)(unaff_gp + -0x7ab8) + 1;
    }
  }
  else {
    uVar1 = *(uint *)(unaff_gp + -0x7abc);
    *(undefined4 *)(unaff_gp + -0x7c70) = 0;
  }
  return uVar1;
}



void FUN_00405ec4(undefined4 param_1)

{
  int unaff_gp;
  
  *(undefined4 *)(unaff_gp + -0x7ac0) = param_1;
  *(undefined4 *)(unaff_gp + -0x7ab4) = 1;
  *(undefined4 *)(unaff_gp + -0x7ab8) = 0;
  return;
}



void FUN_00405ed8(undefined4 param_1)

{
  func_0x0f801250(s_ScanError___s_100015a0,param_1);
  return;
}



void FUN_00405f00(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140);
  if (499999 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100015b0,s_AddCPackDef_100015c4);
    FUN_0040d3c0(1);
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140);
  }
  *(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x108) + iVar1 * 4) = param_1;
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140) =
       *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140) + 1;
  return;
}



void FUN_00405f9c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x144);
  if (0 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100015d0,s_AddC3fDef_100015e4);
    FUN_0040d3c0(1);
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x144);
  }
  iVar3 = *(int *)(unaff_gp + -0x7e98);
  puVar2 = (undefined4 *)(*(int *)(iVar3 + 0x10c) + iVar1 * 0xc);
  *puVar2 = param_1;
  puVar2[1] = param_2;
  puVar2[2] = param_5;
  *(int *)(iVar3 + 0x144) = *(int *)(iVar3 + 0x144) + 1;
  return;
}



void FUN_00406054(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x148);
  if (24999 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100015f0,s_AddN3fDef_10001604);
    FUN_0040d3c0(1);
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x148);
  }
  iVar3 = *(int *)(unaff_gp + -0x7e98);
  puVar2 = (undefined4 *)(*(int *)(iVar3 + 0x114) + iVar1 * 0xc);
  *puVar2 = param_1;
  puVar2[1] = param_2;
  puVar2[2] = param_5;
  *(int *)(iVar3 + 0x148) = *(int *)(iVar3 + 0x148) + 1;
  return;
}



void FUN_00406110(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x14c);
  if (399999 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001610,s_AddV3fDef_10001624);
    FUN_0040d3c0(1);
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x14c);
  }
  iVar3 = *(int *)(unaff_gp + -0x7e98);
  puVar2 = (undefined4 *)(*(int *)(iVar3 + 0x110) + iVar1 * 0xc);
  *puVar2 = param_1;
  puVar2[1] = param_2;
  puVar2[2] = param_5;
  *(int *)(iVar3 + 0x14c) = *(int *)(iVar3 + 0x14c) + 1;
  return;
}



void FUN_004061d0(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_gp;
  undefined4 auStackX_0 [4];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_24 = *(undefined4 *)(unaff_gp + -0x7ee0);
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_4 = 0;
  local_20 = local_24;
  local_1c = local_24;
  local_8 = local_24;
  puVar1 = (undefined4 *)FUN_0040a8e0(param_1);
  while (puVar1 != (undefined4 *)0x0) {
    switch(*puVar1) {
    case 0x112:
      local_18 = puVar1[1];
      local_14 = puVar1[2];
      local_10 = puVar1[3];
      break;
    case 0x113:
      local_24 = puVar1[1];
      local_20 = puVar1[2];
      local_1c = puVar1[3];
      break;
    case 0x114:
      local_4 = puVar1[1];
      break;
    case 0x115:
      local_c = puVar1[1];
      break;
    case 0x116:
      local_8 = puVar1[1];
      break;
    default:
      func_0x0f801250(s_AddMaterialDef__unknown_class__d_10001630,*puVar1);
    }
    puVar1 = (undefined4 *)FUN_0040a918(param_1);
  }
  iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x15c);
  if (99 < iVar2) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001654,s_AddMaterialDef_10001668);
    FUN_0040d3c0(1);
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x15c);
  }
  iVar5 = *(int *)(unaff_gp + -0x7e98);
  puVar1 = (undefined4 *)(*(int *)(iVar5 + 0x124) + iVar2 * 0x24);
  puVar3 = &local_24;
  do {
    puVar4 = puVar3 + 3;
    *puVar1 = *puVar3;
    puVar1[1] = puVar3[1];
    puVar1[2] = puVar3[2];
    puVar1 = puVar1 + 3;
    puVar3 = puVar4;
  } while (puVar4 != auStackX_0);
  *(int *)(iVar5 + 0x15c) = *(int *)(iVar5 + 0x15c) + 1;
  return;
}



int FUN_004063a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x150);
  iVar2 = iVar1;
  if (0x13 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001678,s_AddRotateDef_1000168c);
    FUN_0040d3c0(1);
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x150);
  }
  iVar4 = *(int *)(unaff_gp + -0x7e98);
  puVar3 = (undefined4 *)(*(int *)(iVar4 + 0x118) + iVar2 * 0x10);
  *puVar3 = param_1;
  puVar3[1] = param_2;
  puVar3[2] = param_5;
  puVar3[3] = param_6;
  *(int *)(iVar4 + 0x150) = *(int *)(iVar4 + 0x150) + 1;
  return iVar1;
}



int FUN_00406468(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x154);
  iVar2 = iVar1;
  if (0x13 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_1000169c,s_AddScaleDef_100016b0);
    FUN_0040d3c0(1);
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x154);
  }
  iVar4 = *(int *)(unaff_gp + -0x7e98);
  puVar3 = (undefined4 *)(*(int *)(iVar4 + 0x11c) + iVar2 * 0xc);
  *puVar3 = param_1;
  puVar3[1] = param_2;
  puVar3[2] = param_5;
  *(int *)(iVar4 + 0x154) = *(int *)(iVar4 + 0x154) + 1;
  return iVar1;
}



int FUN_00406524(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x158);
  iVar2 = iVar1;
  if (0x13 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100016bc,s_AddTranslateDef_100016d0);
    FUN_0040d3c0(1);
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x158);
  }
  iVar4 = *(int *)(unaff_gp + -0x7e98);
  puVar3 = (undefined4 *)(*(int *)(iVar4 + 0x120) + iVar2 * 0xc);
  *puVar3 = param_1;
  puVar3[1] = param_2;
  puVar3[2] = param_5;
  *(int *)(iVar4 + 0x158) = *(int *)(iVar4 + 0x158) + 1;
  return iVar1;
}



void FUN_004065e0(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int unaff_gp;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int *local_8;
  int *local_4;
  
  iVar1 = FUN_0040ade4(param_1);
  if (iVar1 < 3) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100016e0,
                    s_AddPolygonDef__too_few_refs_100016f4);
    FUN_0040d3c0(1);
  }
  local_4 = (int *)FUN_0040a8e0(param_1);
  local_8 = (int *)FUN_0040a918(param_1);
  piVar2 = (int *)FUN_0040a918(param_1);
  iVar5 = 0;
  iVar4 = *local_4;
  iVar6 = 0;
  iVar1 = iVar5;
  if ((iVar4 == 0x103) || (iVar7 = iVar6, iVar4 == 0x107)) {
    if (*local_8 != 0x110) {
      func_0x0f801250(s_AddPolygonDef__error__2nd_ref__p_10001710,
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) -
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188),0);
      return;
    }
    iVar3 = *piVar2;
    iVar7 = iVar4;
    if (((iVar3 != 0x103) && (iVar3 != 0x107)) && (iVar1 = iVar4, iVar7 = iVar6, iVar3 != 0x110)) {
      iVar1 = iVar5;
    }
  }
  iVar1 = FUN_004067e4(param_1,iVar1,iVar7,&local_1c);
  if (iVar1 == 0) {
    func_0x0f801250(s_AddPolygonDef__error__gen_failed_1000173c,
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) -
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160);
    if (199999 < iVar1) {
      func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_1000176c,s_AddPolygonDef_10001780);
      FUN_0040d3c0(1);
      iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160);
    }
    iVar4 = *(int *)(unaff_gp + -0x7e98);
    puVar8 = (undefined4 *)(*(int *)(iVar4 + 0x128) + iVar1 * 0x10);
    *puVar8 = local_1c;
    puVar8[1] = local_18;
    puVar8[2] = local_14;
    puVar8[3] = local_10;
    *(int *)(iVar4 + 0x160) = *(int *)(iVar4 + 0x160) + 1;
  }
  return;
}



undefined4 FUN_004067e4(undefined4 *param_1,int param_2,int param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  undefined4 **ppuVar5;
  undefined4 **ppuVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  uint uVar12;
  int unaff_gp;
  undefined4 *local_res0 [4];
  undefined4 local_2008 [2049];
  uint local_4;
  
  param_4[3] = 0xffffffff;
  local_res0[0] = param_1;
  if ((param_2 != 0) && (param_3 != 0)) {
    local_res0[3] = param_4;
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001790,s_GenPolygonDef_100017a4);
    FUN_0040d3c0(1);
    param_4 = local_res0[3];
  }
  if ((param_2 == 0) && (param_3 == 0)) {
    *param_4 = FUN_00408748;
  }
  if (param_2 != 0) {
    if (param_2 == 0x103) {
      *param_4 = FUN_004089a0;
      param_4[3] = 3;
    }
    else if (param_2 == 0x107) {
      *param_4 = FUN_00408bf0;
      param_4[3] = 5;
    }
  }
  if (param_3 != 0) {
    if (param_3 == 0x103) {
      *param_4 = FUN_00408840;
      param_4[3] = 2;
    }
    else if (param_3 == 0x107) {
      *param_4 = FUN_00408ab0;
      param_4[3] = 4;
    }
  }
  uVar12 = 0;
  local_res0[3] = param_4;
  piVar2 = (int *)FUN_0040a8e0(local_res0[0]);
  puVar3 = local_2008;
  while (piVar2 != (int *)0x0) {
    if (((uVar12 == 0) && (param_2 != 0)) && (param_2 != *piVar2)) {
      func_0x0f801250(s_GenPolygonDef__error__pp_mods__p_100017b4,
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) -
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188));
      return 0;
    }
    iVar8 = *piVar2;
    uVar9 = uVar12 & 1;
    if (((int)uVar12 < 0) && (uVar9 != 0)) {
      uVar9 = uVar9 - 2;
    }
    if (((uVar9 == 0) && (param_3 != 0)) && (param_3 != iVar8)) {
      func_0x0f801250(s_GenPolygonDef__error__pv_mods__p_100017e0,
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) -
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188));
      return 0;
    }
    if (iVar8 == 0x103) {
      puVar7 = puVar3 + 1;
      *puVar3 = *(undefined4 *)piVar2[2];
    }
    else if (iVar8 == 0x107) {
      puVar10 = (undefined4 *)piVar2[2];
      puVar7 = puVar3 + 3;
      uVar11 = puVar10[1];
      *puVar3 = *puVar10;
      uVar1 = puVar10[2];
      puVar3[1] = uVar11;
      puVar3[2] = uVar1;
    }
    else if (iVar8 == 0x110) {
      puVar10 = (undefined4 *)piVar2[2];
      puVar7 = puVar3 + 3;
      uVar11 = puVar10[1];
      *puVar3 = *puVar10;
      uVar1 = puVar10[2];
      puVar3[1] = uVar11;
      puVar3[2] = uVar1;
    }
    else {
      FUN_004092d4(s_GenPolygonDef__bad_class_referen_10001864,*piVar2,
                   *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) -
                   *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188));
      puVar7 = puVar3;
    }
    uVar12 = uVar12 + 1;
    piVar2 = (int *)FUN_0040a918(local_res0[0]);
    puVar3 = puVar7;
  }
  uVar12 = 0;
  iVar8 = (int)puVar3 - (int)local_2008;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 3;
  }
  local_4 = iVar8 >> 2;
  puVar3 = (undefined4 *)func_0x0f801208(local_4 << 2);
  if (puVar3 == (undefined4 *)0x0) {
    FUN_004092d4(s_AddPolygonDef__ALLOCN_1000189c);
  }
  if (0 < (int)local_4) {
    puVar4 = (undefined *)register0x00000074;
    puVar7 = puVar3;
    if ((local_4 & 3) != 0) {
      do {
        uVar12 = uVar12 + 1;
        *puVar7 = *(undefined4 *)(puVar4 + -0x2008);
        puVar4 = puVar4 + 4;
        puVar7 = puVar7 + 1;
      } while ((local_4 & 3) != uVar12);
      if (uVar12 == local_4) goto LAB_00406b60;
    }
    ppuVar5 = local_res0 + uVar12;
    puVar7 = puVar3 + uVar12;
    do {
      ppuVar6 = ppuVar5 + 4;
      *puVar7 = ppuVar5[-0x802];
      puVar7[1] = ppuVar5[-0x801];
      puVar7[2] = ppuVar5[-0x800];
      puVar7[3] = ppuVar5[-0x7ff];
      ppuVar5 = ppuVar6;
      puVar7 = puVar7 + 4;
    } while (ppuVar6 != local_res0 + local_4);
  }
LAB_00406b60:
  local_res0[3][1] = puVar3;
  local_res0[3][2] = local_4;
  return 1;
}



void FUN_00406b90(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int unaff_gp;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = FUN_0040ade4(param_1);
  if (2 < iVar1) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100018b4,s_AddPointDef__too_many_refs_100018c8
                   );
    FUN_0040d3c0(1);
  }
  piVar2 = (int *)FUN_0040a8e0(param_1);
  iVar1 = *piVar2;
  if ((iVar1 != 0x103) && (iVar1 != 0x107)) {
    if (iVar1 == 0x110) {
      iVar1 = FUN_0040ade4(param_1);
      if (iVar1 != 1) {
        func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_100018e4,
                        s_AddPointDef__a_point_must_have_o_100018f8);
        FUN_0040d3c0(1);
      }
    }
    else {
      FUN_004092d4(s_AddPointDef__bad_attribute___d__f_10001924,*piVar2,
                   *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168));
    }
  }
  iVar1 = FUN_00406d60(param_1,&local_14);
  if (iVar1 == 0) {
    func_0x0f801250(s_AddPointDef__error__gen_failed__p_10001954,
                    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168);
    if (3999 < iVar1) {
      func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001980,s_AddPointDef_10001994);
      FUN_0040d3c0(1);
      iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168);
    }
    iVar3 = *(int *)(unaff_gp + -0x7e98);
    puVar4 = (undefined4 *)(*(int *)(iVar3 + 0x130) + iVar1 * 0x10);
    *puVar4 = local_14;
    puVar4[1] = local_10;
    puVar4[2] = local_c;
    puVar4[3] = local_8;
    *(int *)(iVar3 + 0x168) = *(int *)(iVar3 + 0x168) + 1;
  }
  return;
}



undefined4 FUN_00406d60(undefined4 *param_1,undefined4 *param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined *puVar5;
  undefined4 **ppuVar6;
  undefined4 **ppuVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  int iVar11;
  int *piVar12;
  int unaff_gp;
  undefined4 *local_res0 [4];
  int local_14 [5];
  
  param_2[3] = 0xffffffff;
  local_res0[0] = param_1;
  local_res0[1] = param_2;
  piVar1 = (int *)FUN_0040a8e0(param_1);
  iVar8 = *piVar1;
  if (iVar8 == 0x103) {
    *local_res0[1] = FUN_00408d94;
    local_res0[1][3] = 8;
  }
  else if (iVar8 == 0x107) {
    *local_res0[1] = FUN_00408e34;
    local_res0[1][3] = 9;
  }
  else if (iVar8 == 0x110) {
    *local_res0[1] = FUN_00408d00;
  }
  else {
    FUN_004092d4(s_GenPointDef__bad_modifier___d__i_100019a0,*piVar1,
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168));
  }
  piVar2 = (int *)FUN_0040a8e0(local_res0[0]);
  piVar1 = local_14;
  while (piVar2 != (int *)0x0) {
    iVar8 = *piVar2;
    if (iVar8 == 0x103) {
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140) <= piVar2[1]) {
        FUN_004092d4(s_cpack__d__not_defined_100019e0,piVar2[1]);
      }
      piVar12 = piVar1 + 1;
      *piVar1 = *(int *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x108) + piVar2[1] * 4);
    }
    else if (iVar8 == 0x107) {
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x148) <= piVar2[1]) {
        FUN_004092d4(s_n3f__d__not_defined_100019f8,piVar2[1]);
      }
      piVar2 = (int *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x114) + piVar2[1] * 0xc);
      iVar11 = piVar2[1];
      *piVar1 = *piVar2;
      iVar8 = piVar2[2];
      piVar1[1] = iVar11;
      piVar12 = piVar1 + 3;
      piVar1[2] = iVar8;
    }
    else {
      piVar12 = piVar1;
      if (iVar8 == 0x110) {
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x14c) <= piVar2[1]) {
          FUN_004092d4(s_v3f__d__not_defined_100019cc,piVar2[1]);
        }
        *piVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x110) + piVar2[1] * 0xc;
        piVar12 = piVar1 + 1;
      }
    }
    piVar2 = (int *)FUN_0040a918(local_res0[0]);
    piVar1 = piVar12;
  }
  iVar8 = (int)piVar1 - (int)local_14;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 3;
  }
  uVar3 = iVar8 >> 2;
  puVar4 = (undefined4 *)func_0x0f801208(uVar3 << 2);
  if (puVar4 == (undefined4 *)0x0) {
    FUN_004092d4(s_AddPointDef__ALLOCN_10001a48);
  }
  uVar10 = 0;
  if (0 < (int)uVar3) {
    puVar5 = (undefined *)register0x00000074;
    puVar9 = puVar4;
    if ((uVar3 & 3) != 0) {
      do {
        uVar10 = uVar10 + 1;
        *puVar9 = *(undefined4 *)(puVar5 + -0x14);
        puVar5 = puVar5 + 4;
        puVar9 = puVar9 + 1;
      } while ((uVar3 & 3) != uVar10);
      if (uVar10 == uVar3) goto LAB_00407048;
    }
    ppuVar6 = local_res0 + uVar10;
    puVar9 = puVar4 + uVar10;
    do {
      ppuVar7 = ppuVar6 + 4;
      *puVar9 = ppuVar6[-5];
      puVar9[1] = ppuVar6[-4];
      puVar9[2] = ppuVar6[-3];
      puVar9[3] = ppuVar6[-2];
      ppuVar6 = ppuVar7;
      puVar9 = puVar9 + 4;
    } while (ppuVar7 != local_res0 + uVar3);
  }
LAB_00407048:
  local_res0[1][1] = puVar4;
  local_res0[1][2] = uVar3;
  return 1;
}



void FUN_00407068(undefined4 param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int unaff_gp;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  piVar1 = (int *)FUN_0040a8e0(param_1);
  iVar5 = *piVar1;
  iVar3 = 0;
  iVar6 = 0;
  uVar4 = 0;
  piVar1 = (int *)FUN_0040a8e0(param_1);
  while (piVar1 != (int *)0x0) {
    if (iVar5 == 0x110) {
      iVar3 = iVar3 + 1;
      if (*piVar1 != 0x110) {
        FUN_004092d4(s_AddLineDef__semantic_error__1__i_10001a5c,
                     *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
      }
    }
    else {
      uVar2 = uVar4 & 1;
      if (((int)uVar4 < 0) && (uVar2 != 0)) {
        uVar2 = uVar2 - 2;
      }
      if ((uVar2 == 0) && (iVar6 = iVar6 + 1, iVar5 != *piVar1)) {
        FUN_004092d4(s_AddLineDef__semantic_error__2__i_10001a88,
                     *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
      }
      if ((uVar2 == 1) && (iVar3 = iVar3 + 1, *piVar1 != 0x110)) {
        FUN_004092d4(s_AddLineDef__semantic_error__3__i_10001ab4,
                     *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
      }
    }
    uVar4 = uVar4 + 1;
    piVar1 = (int *)FUN_0040a918(param_1);
  }
  if (((iVar3 < 2) || (0x100 < iVar3)) || ((iVar5 != 0x110 && (iVar3 != iVar6)))) {
    FUN_004092d4(s_AddLineDef__semantic_error__4__i_10001ae0,
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
  }
  iVar3 = FUN_004072ac(param_1,&local_14);
  if (iVar3 == 0) {
    FUN_004092d4(s_AddLineDef__error__gen_failed__L_10001b0c,
                 *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
  }
  iVar3 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164);
  if (99999 < iVar3) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001b34,s_AddLineDef_10001b48);
    FUN_0040d3c0(1);
    iVar3 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164);
  }
  iVar6 = *(int *)(unaff_gp + -0x7e98);
  puVar7 = (undefined4 *)(*(int *)(iVar6 + 300) + iVar3 * 0x10);
  *puVar7 = local_14;
  puVar7[1] = local_10;
  puVar7[2] = local_c;
  puVar7[3] = local_8;
  *(int *)(iVar6 + 0x164) = *(int *)(iVar6 + 0x164) + 1;
  return;
}



undefined4 FUN_004072ac(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined auStackX_0 [4];
  undefined4 *local_res4;
  undefined4 local_1008 [1025];
  uint local_4;
  
  param_2[3] = 0xffffffff;
  local_res4 = param_2;
  piVar2 = (int *)FUN_0040a8e0(param_1);
  iVar6 = *piVar2;
  if (iVar6 == 0x103) {
    *local_res4 = FUN_00408f64;
    local_res4[3] = 6;
  }
  else if (iVar6 == 0x107) {
    *local_res4 = FUN_004090fc;
    local_res4[3] = 7;
  }
  else if (iVar6 == 0x110) {
    *local_res4 = FUN_00408ed0;
  }
  piVar2 = (int *)FUN_0040a8e0(param_1);
  puVar3 = local_1008;
  while (piVar2 != (int *)0x0) {
    iVar6 = *piVar2;
    if (iVar6 == 0x103) {
      puVar7 = puVar3 + 1;
      *puVar3 = *(undefined4 *)piVar2[2];
    }
    else if (iVar6 == 0x107) {
      puVar9 = (undefined4 *)piVar2[2];
      puVar7 = puVar3 + 3;
      uVar10 = puVar9[1];
      *puVar3 = *puVar9;
      uVar1 = puVar9[2];
      puVar3[1] = uVar10;
      puVar3[2] = uVar1;
    }
    else {
      puVar7 = puVar3;
      if (iVar6 == 0x110) {
        puVar9 = (undefined4 *)piVar2[2];
        puVar7 = puVar3 + 3;
        uVar10 = puVar9[1];
        *puVar3 = *puVar9;
        uVar1 = puVar9[2];
        puVar3[1] = uVar10;
        puVar3[2] = uVar1;
      }
    }
    piVar2 = (int *)FUN_0040a918(param_1);
    puVar3 = puVar7;
  }
  iVar6 = (int)puVar3 - (int)local_1008;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 3;
  }
  local_4 = iVar6 >> 2;
  puVar3 = (undefined4 *)func_0x0f801208(local_4 << 2);
  if (puVar3 == (undefined4 *)0x0) {
    FUN_004092d4(s_AddLineDef__ALLOCN_10001bac);
  }
  uVar8 = 0;
  if (0 < (int)local_4) {
    puVar4 = (undefined *)register0x00000074;
    puVar7 = puVar3;
    if ((local_4 & 3) != 0) {
      do {
        uVar8 = uVar8 + 1;
        *puVar7 = *(undefined4 *)(puVar4 + -0x1008);
        puVar4 = puVar4 + 4;
        puVar7 = puVar7 + 1;
      } while ((local_4 & 3) != uVar8);
      if (uVar8 == local_4) goto LAB_004074dc;
    }
    puVar4 = auStackX_0 + uVar8 * 4;
    puVar7 = puVar3 + uVar8;
    do {
      puVar5 = puVar4 + 0x10;
      *puVar7 = *(undefined4 *)(puVar4 + -0x1008);
      puVar7[1] = *(undefined4 *)(puVar4 + -0x1004);
      puVar7[2] = *(undefined4 *)(puVar4 + -0x1000);
      puVar7[3] = *(undefined4 *)(puVar4 + -0xffc);
      puVar4 = puVar5;
      puVar7 = puVar7 + 4;
    } while (puVar5 != auStackX_0 + local_4 * 4);
  }
LAB_004074dc:
  local_res4[1] = puVar3;
  local_res4[2] = local_4;
  return 1;
}



undefined4 FUN_004074fc(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 *puVar9;
  int unaff_gp;
  undefined4 *puVar10;
  undefined4 *local_1c;
  int *local_c;
  
  puVar9 = (undefined4 *)0x0;
  puVar10 = (undefined4 *)0x0;
  local_1c = (undefined4 *)0x0;
  uVar3 = FUN_0040a400();
  piVar4 = (int *)FUN_0040a8e0(param_1);
  piVar1 = (int *)0x0;
  while (piVar4 != (int *)0x0) {
    switch(*piVar4) {
    case 0x104:
      local_c = (int *)func_0x0f801208(0x10);
      if (local_c == (int *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001c60);
      }
      iVar7 = *piVar4;
      local_c[1] = (int)FUN_00408308;
      local_c[3] = -1;
      *local_c = iVar7;
      local_c[2] = *(int *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x138) + piVar4[1] * 4);
      FUN_0040a6d4(uVar3,local_c);
      break;
    default:
      func_0x0f801250(s_GenGroupDef__class__d_not_allowe_10001c70,*piVar4);
      return 0;
    case 0x109:
      piVar8 = (int *)piVar4[2];
      puVar5 = (undefined4 *)func_0x0f801208(0xc);
      if (puVar5 == (undefined4 *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001bc0);
      }
      *puVar5 = 0;
      puVar5[1] = piVar8[1];
      puVar5[2] = piVar8[2];
      if (((piVar1 == (int *)0x0) || (*piVar4 != *piVar1)) || (*piVar8 != piVar1[1])) {
        local_c = (int *)func_0x0f801208(0x10);
        if (local_c == (int *)0x0) {
          FUN_004092d4(s_GenGroupDef__10001bd0);
        }
        *local_c = *piVar4;
        local_c[1] = *piVar8;
        iVar7 = piVar8[3];
        local_c[2] = (int)puVar5;
        local_c[3] = iVar7;
        FUN_0040a6d4(uVar3,local_c);
        puVar9 = puVar5;
      }
      else {
        *puVar9 = puVar5;
        puVar9 = puVar5;
      }
      break;
    case 0x10a:
      piVar8 = (int *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x130) + piVar4[1] * 0x10);
      iVar7 = *piVar8;
      iVar6 = piVar8[1];
      iVar2 = piVar8[2];
      puVar5 = (undefined4 *)func_0x0f801208(0xc);
      if (puVar5 == (undefined4 *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001be0);
      }
      *puVar5 = 0;
      puVar5[1] = iVar6;
      puVar5[2] = iVar2;
      if (((piVar1 == (int *)0x0) || (*piVar4 != *piVar1)) || (iVar7 != piVar1[1])) {
        local_c = (int *)func_0x0f801208(0x10);
        if (local_c == (int *)0x0) {
          FUN_004092d4(s_GenGroupDef__10001bf0);
        }
        *local_c = *piVar4;
        local_c[2] = (int)puVar5;
        local_c[1] = iVar7;
        FUN_0040a6d4(uVar3,local_c);
        local_1c = puVar5;
      }
      else {
        *local_1c = puVar5;
        local_1c = puVar5;
      }
      break;
    case 0x10b:
      piVar8 = (int *)piVar4[2];
      puVar5 = (undefined4 *)func_0x0f801208(0xc);
      if (puVar5 == (undefined4 *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001c00);
      }
      *puVar5 = 0;
      puVar5[1] = piVar8[1];
      puVar5[2] = piVar8[2];
      if (((piVar1 == (int *)0x0) || (*piVar4 != *piVar1)) || (*piVar8 != piVar1[1])) {
        local_c = (int *)func_0x0f801208(0x10);
        if (local_c == (int *)0x0) {
          FUN_004092d4(s_GenGroupDef__10001c10);
        }
        *local_c = *piVar4;
        local_c[1] = *piVar8;
        iVar7 = piVar8[3];
        local_c[2] = (int)puVar5;
        local_c[3] = iVar7;
        FUN_0040a6d4(uVar3,local_c);
        puVar10 = puVar5;
      }
      else {
        *puVar10 = puVar5;
        puVar10 = puVar5;
      }
      break;
    case 0x10c:
      local_c = (int *)func_0x0f801208(0x10);
      if (local_c == (int *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001c30);
      }
      iVar7 = *piVar4;
      local_c[1] = (int)FUN_00408608;
      local_c[3] = -1;
      *local_c = iVar7;
      local_c[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x118) + piVar4[1] * 0x10;
      FUN_0040a6d4(uVar3,local_c);
      break;
    case 0x10d:
      local_c = (int *)func_0x0f801208(0x10);
      if (local_c == (int *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001c40);
      }
      iVar7 = *piVar4;
      local_c[1] = (int)FUN_004086f0;
      local_c[3] = -1;
      *local_c = iVar7;
      local_c[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x11c) + piVar4[1] * 0xc;
      FUN_0040a6d4(uVar3,local_c);
      break;
    case 0x10f:
      local_c = (int *)func_0x0f801208(0x10);
      if (local_c == (int *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001c50);
      }
      iVar7 = *piVar4;
      local_c[1] = (int)FUN_0040871c;
      local_c[3] = -1;
      *local_c = iVar7;
      local_c[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x120) + piVar4[1] * 0xc;
      FUN_0040a6d4(uVar3,local_c);
      break;
    case 0x111:
      local_c = (int *)func_0x0f801208(0x10);
      if (local_c == (int *)0x0) {
        FUN_004092d4(s_GenGroupDef__10001c20);
      }
      iVar7 = *piVar4;
      local_c[1] = (int)FUN_004083f0;
      local_c[3] = -1;
      *local_c = iVar7;
      local_c[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x124) + piVar4[1] * 0x24;
      FUN_0040a6d4(uVar3,local_c);
    }
    piVar4 = (int *)FUN_0040a918(param_1);
    piVar1 = local_c;
  }
  *param_2 = uVar3;
  return 1;
}



void FUN_00407a8c(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  undefined4 local_4;
  
  iVar1 = FUN_004074fc(param_1,&local_4);
  if (iVar1 == 0) {
    func_0x0f801250(s_AddGroupDef__error__gen_failed__g_10001c98,
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) -
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x194));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170);
    if (99 < iVar1) {
      func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001cc4,s_AddGroupDef_10001cd8);
      FUN_0040d3c0(1);
      iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170);
    }
    *(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x138) + iVar1 * 4) = local_4;
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) + 1;
  }
  return;
}



void FUN_00407b6c(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  undefined4 local_4;
  
  iVar1 = FUN_004074fc(param_1,&local_4);
  if (iVar1 == 0) {
    func_0x0f801250(s_AddInstanceDef__error__gen_faile_10001ce4,
                    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x174));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174);
    if (199 < iVar1) {
      func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001d14,s_AddInstanceDef_10001d28);
      FUN_0040d3c0(1);
      iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174);
    }
    *(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) + iVar1 * 4) = local_4;
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) + 1;
  }
  return;
}



undefined4 * FUN_00407c44(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int unaff_gp;
  
  puVar1 = (undefined4 *)func_0x0f801208(0xc);
  if (puVar1 == (undefined4 *)0x0) {
    FUN_004092d4(unaff_gp + -0x7c60);
  }
  switch(param_1) {
  case 0x103:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x178);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140) - iVar2 <= param_2) {
      FUN_004092d4(s__s__cpack__d__not_defined_10001d38,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x178);
    }
    puVar1[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x108) + (iVar2 + param_2) * 4;
    break;
  case 0x104:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x194);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) - iVar2 <= param_2) {
      FUN_004092d4(s__s__group__d__not_defined_10001df8,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x194);
    }
    puVar1[2] = *(undefined4 *)
                 (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x138) + (iVar2 + param_2) * 4);
    break;
  default:
    func_0x0f801150(&DAT_100036b4,s_GenRef__cannot_reference_class___10001e14,param_1,param_2);
    break;
  case 0x107:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x17c);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x148) - iVar2 <= param_2) {
      FUN_004092d4(s__s__n3f__d__not_defined_10001d54,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x17c);
    }
    puVar1[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x114) + (iVar2 + param_2) * 0xc;
    break;
  case 0x109:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) - iVar2 <= param_2) {
      FUN_004092d4(s__s__polygon__d__not_defined_10001da4,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188);
    }
    puVar1[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x128) + (iVar2 + param_2) * 0x10;
    break;
  case 0x10a:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 400);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168) - iVar2 <= param_2) {
      FUN_004092d4(s__s__point__d__not_defined_10001ddc,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 400);
    }
    puVar1[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x130) + (iVar2 + param_2) * 0x10;
    break;
  case 0x10b:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x18c);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164) - iVar2 <= param_2) {
      FUN_004092d4(s__s__line__d__not_defined_10001dc0,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x18c);
    }
    puVar1[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 300) + (iVar2 + param_2) * 0x10;
    break;
  case 0x110:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x180);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x14c) - iVar2 <= param_2) {
      FUN_004092d4(s__s__v3f__d__not_defined_10001d6c,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x180);
    }
    puVar1[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x110) + (iVar2 + param_2) * 0xc;
    break;
  case 0x111:
    iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x184);
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x15c) - iVar2 <= param_2) {
      FUN_004092d4(s__s__material__d__not_defined_10001d84,s_gview_10003ed0,param_2);
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x184);
    }
    puVar1[2] = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x124) + (iVar2 + param_2) * 0x24;
  }
  puVar1[1] = param_2;
  *puVar1 = param_1;
  return puVar1;
}



void FUN_00408074(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0040a8e0(param_1);
  while (iVar1 != 0) {
    func_0x0f801200(iVar1);
    iVar1 = FUN_0040a918(param_1);
  }
  FUN_0040a48c(param_1);
  return;
}



undefined4 * FUN_004080c4(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)func_0x0f801208(0x10);
  if (puVar1 == (undefined4 *)0x0) {
    FUN_004092d4(s_GenDef1f__10001e3c);
  }
  *puVar1 = param_1;
  puVar1[1] = param_2;
  return puVar1;
}



undefined4 *
FUN_00408124(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)func_0x0f801208(0x10);
  if (puVar1 == (undefined4 *)0x0) {
    FUN_004092d4(s_GenDef3f__10001e48);
  }
  *puVar1 = param_1;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = param_4;
  return puVar1;
}



void FUN_004081a4(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0040a8e0(param_1);
  while (iVar1 != 0) {
    func_0x0f801200(iVar1);
    iVar1 = FUN_0040a918(param_1);
  }
  FUN_0040a48c(param_1);
  return;
}



void FUN_00408200(void)

{
  undefined4 *puVar1;
  int unaff_gp;
  
  puVar1 = (undefined4 *)func_0x0f801208(0x28);
  if (puVar1 == (undefined4 *)0x0) {
    FUN_004092d4(s_SetupFuncTable__ALLOC_10001e60);
  }
  *puVar1 = 0xffffffff;
  puVar1[1] = FUN_00408748;
  puVar1[2] = FUN_00408840;
  puVar1[3] = FUN_004089a0;
  puVar1[4] = FUN_00408ab0;
  puVar1[5] = FUN_00408bf0;
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xb8) == 0) {
    puVar1[6] = FUN_00408f64;
  }
  else {
    puVar1[6] = FUN_00409030;
  }
  puVar1[7] = FUN_004090fc;
  puVar1[8] = FUN_00408d94;
  puVar1[9] = FUN_00408e34;
  *(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xb4) = puVar1;
  return;
}



void FUN_004082e8(void)

{
  FUN_00408308();
  return;
}



void FUN_00408308(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  
  func_0x0f402230();
  iVar1 = FUN_0040a8e0(param_1);
  while (iVar1 != 0) {
    if ((*(uint *)(iVar1 + 0xc) == 0xffffffff) || (9 < *(uint *)(iVar1 + 0xc))) {
      func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001e78,s_DrawGroup__bad_funcIndex_10001e8c
                     );
      FUN_0040d3c0(1);
    }
    (**(code **)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xb4) + *(int *)(iVar1 + 0xc) * 4))
              (*(undefined4 *)(iVar1 + 8));
    iVar1 = FUN_0040a918(param_1);
  }
  func_0x0f402228();
  return;
}



void FUN_004083f0(float *param_1)

{
  double *pdVar1;
  int unaff_gp;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_e4;
  float local_e0;
  float local_dc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  undefined4 local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  undefined4 local_98;
  float local_94;
  undefined4 local_90;
  
  pdVar1 = (double *)(unaff_gp + -0x7f78);
  dVar4 = (double)*param_1;
  dVar7 = (double)param_1[8];
  dVar8 = *pdVar1 - dVar7;
  dVar2 = (double)(float)dVar8;
  dVar5 = (double)param_1[1];
  local_b4 = (float)(dVar4 * dVar2);
  local_b0 = (float)(dVar5 * dVar2);
  dVar6 = (double)param_1[2];
  local_ac = (float)(dVar6 * dVar2);
  if (*(double *)(unaff_gp + -0x7f70) < dVar7) {
    dVar2 = (double)param_1[6];
    dVar3 = (*pdVar1 - dVar2) *
            (double)(float)((dVar4 + dVar5 + dVar6) / *(double *)(unaff_gp + -0x7f68));
    local_e4 = (float)(dVar7 * (dVar2 * dVar4 + dVar3));
    local_e0 = (float)(dVar7 * (dVar2 * dVar5 + dVar3));
    local_dc = (float)(dVar7 * (dVar2 * dVar6 + dVar3));
  }
  else {
    local_dc = 0.0;
    local_e0 = 0.0;
    local_e4 = 0.0;
  }
  if (*(double *)(unaff_gp + -0x7f60) < dVar7) {
    dVar8 = *pdVar1 - (double)*(float *)(unaff_gp + -0x7ebc);
  }
  local_c4 = 0;
  local_c0 = 0;
  local_a4 = local_e4;
  local_bc = 0;
  local_90 = 0;
  local_c8 = *(undefined4 *)(unaff_gp + -0x7eb8);
  local_b8 = *(undefined4 *)(unaff_gp + -0x7eb4);
  local_a8 = *(undefined4 *)(unaff_gp + -0x7eb0);
  local_a0 = local_e0;
  local_98 = *(undefined4 *)(unaff_gp + -0x7eac);
  local_9c = local_dc;
  local_94 = (float)(*pdVar1 / dVar8 - *pdVar1);
  func_0x0f4015d0(0,1,0xf,&local_c8);
  func_0x0f402570(1000,1);
  return;
}



void FUN_00408608(undefined4 *param_1)

{
  byte bVar1;
  
  bVar1 = (float)param_1[1] != 0.0;
  if ((float)param_1[2] != 0.0) {
    bVar1 = bVar1 | 2;
  }
  if ((float)param_1[3] != 0.0) {
    bVar1 = bVar1 | 4;
  }
  if (bVar1 == 1) {
    func_0x0f402558(*param_1,param_1,0x78);
  }
  else if (bVar1 == 2) {
    func_0x0f402558(*param_1,param_1,0x79);
  }
  else if (bVar1 == 4) {
    func_0x0f402558(*param_1,param_1,0x7a);
  }
  else {
    FUN_004092d4(s_SetRotate__rotate_not_about_x__y_10001ea8);
  }
  return;
}



void FUN_004086f0(undefined4 *param_1,undefined4 param_2)

{
  func_0x0f402278(*param_1,param_1[1],param_1,param_2,param_1[2]);
  return;
}



void FUN_0040871c(undefined4 *param_1,undefined4 param_2)

{
  func_0x0f402298(*param_1,param_1[1],param_1,param_2,param_1[2]);
  return;
}



void FUN_00408748(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_004034b8(0);
  if (param_1 != (undefined4 *)0x0) {
    do {
      puVar2 = (undefined4 *)param_1[1];
      if (param_1[2] == 4) {
        func_0x0f4020d8();
        func_0x0f402030(*puVar2);
        func_0x0f402030(puVar2[1]);
        func_0x0f402030(puVar2[2]);
        func_0x0f402030(puVar2[3]);
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
      else {
        iVar1 = 0;
        func_0x0f4020d8();
        if (0 < (int)param_1[2]) {
          do {
            func_0x0f402030(*puVar2);
            iVar1 = iVar1 + 1;
            puVar2 = puVar2 + 1;
          } while (iVar1 < (int)param_1[2]);
        }
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  return;
}



void FUN_00408840(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  FUN_004034b8(0);
  if (param_1 != (undefined4 *)0x0) {
    do {
      puVar1 = (undefined4 *)param_1[1];
      if (param_1[2] == 0x10) {
        func_0x0f4020d8();
        func_0x0f402098(*puVar1);
        func_0x0f402030(puVar1 + 1);
        func_0x0f402098(puVar1[4]);
        func_0x0f402030(puVar1 + 5);
        func_0x0f402098(puVar1[8]);
        func_0x0f402030(puVar1 + 9);
        func_0x0f402098(puVar1[0xc]);
        func_0x0f402030(puVar1 + 0xd);
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
      else {
        iVar2 = 0xc;
        func_0x0f4020d8();
        func_0x0f402098(*puVar1);
        func_0x0f402030(puVar1 + 1);
        func_0x0f402098(puVar1[4]);
        func_0x0f402030(puVar1 + 5);
        func_0x0f402098(puVar1[8]);
        func_0x0f402030(puVar1 + 9);
        puVar1 = puVar1 + 0xc;
        if (0xc < (int)param_1[2]) {
          do {
            func_0x0f402098(*puVar1);
            func_0x0f402030(puVar1 + 1);
            iVar2 = iVar2 + 4;
            puVar1 = puVar1 + 4;
          } while (iVar2 < (int)param_1[2]);
        }
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  return;
}



void FUN_004089a0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_004034b8(0);
  if (param_1 != (undefined4 *)0x0) {
    do {
      puVar2 = (undefined4 *)param_1[1];
      if (param_1[2] == 0xd) {
        func_0x0f4020d8();
        func_0x0f402098(*puVar2);
        func_0x0f402030(puVar2 + 1);
        func_0x0f402030(puVar2 + 4);
        func_0x0f402030(puVar2 + 7);
        func_0x0f402030(puVar2 + 10);
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
      else {
        iVar1 = 1;
        func_0x0f4020d8();
        func_0x0f402098(*puVar2);
        puVar2 = puVar2 + 1;
        if (1 < (int)param_1[2]) {
          do {
            func_0x0f402030(puVar2);
            iVar1 = iVar1 + 3;
            puVar2 = puVar2 + 3;
          } while (iVar1 < (int)param_1[2]);
        }
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  return;
}



void FUN_00408ab0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_004034b8(1);
  if (param_1 != (undefined4 *)0x0) {
    do {
      iVar1 = param_1[1];
      if (param_1[2] == 0x18) {
        func_0x0f4020d8();
        func_0x0f402068(iVar1);
        func_0x0f402030(iVar1 + 0xc);
        func_0x0f402068(iVar1 + 0x18);
        func_0x0f402030(iVar1 + 0x24);
        func_0x0f402068(iVar1 + 0x30);
        func_0x0f402030(iVar1 + 0x3c);
        func_0x0f402068(iVar1 + 0x48);
        func_0x0f402030(iVar1 + 0x54);
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
      else {
        iVar2 = 0x12;
        func_0x0f4020d8();
        func_0x0f402068(iVar1);
        func_0x0f402030(iVar1 + 0xc);
        func_0x0f402068(iVar1 + 0x18);
        func_0x0f402030(iVar1 + 0x24);
        func_0x0f402068(iVar1 + 0x30);
        func_0x0f402030(iVar1 + 0x3c);
        iVar1 = iVar1 + 0x48;
        if (0x12 < (int)param_1[2]) {
          do {
            func_0x0f402068(iVar1);
            func_0x0f402030(iVar1 + 0xc);
            iVar2 = iVar2 + 6;
            iVar1 = iVar1 + 0x18;
          } while (iVar2 < (int)param_1[2]);
        }
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  return;
}



void FUN_00408bf0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_004034b8(1);
  if (param_1 != (undefined4 *)0x0) {
    do {
      iVar2 = param_1[1];
      if (param_1[2] == 0xf) {
        func_0x0f4020d8();
        func_0x0f402068(iVar2);
        func_0x0f402030(iVar2 + 0xc);
        func_0x0f402030(iVar2 + 0x18);
        func_0x0f402030(iVar2 + 0x24);
        func_0x0f402030(iVar2 + 0x30);
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
      else {
        iVar1 = 0xc;
        func_0x0f4020d8();
        func_0x0f402068(iVar2);
        func_0x0f402030(iVar2 + 0xc);
        func_0x0f402030(iVar2 + 0x18);
        func_0x0f402030(iVar2 + 0x24);
        iVar2 = iVar2 + 0x30;
        if (0xc < (int)param_1[2]) {
          do {
            func_0x0f402030(iVar2);
            iVar1 = iVar1 + 3;
            iVar2 = iVar2 + 0xc;
          } while (iVar1 < (int)param_1[2]);
        }
        func_0x0f402078();
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  return;
}



void FUN_00408d00(int *param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_004034b8(0);
  if (param_1 != (int *)0x0) {
    do {
      iVar1 = param_1[1];
      iVar2 = 0;
      func_0x0f4020e0();
      if (0 < param_1[2]) {
        do {
          func_0x0f402030(iVar1);
          iVar2 = iVar2 + 3;
          iVar1 = iVar1 + 0xc;
        } while (iVar2 < param_1[2]);
      }
      func_0x0f402080();
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}



void FUN_00408d94(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  FUN_004034b8(0);
  if (param_1 != (int *)0x0) {
    do {
      puVar1 = (undefined4 *)param_1[1];
      iVar2 = 0;
      func_0x0f4020e0();
      if (0 < param_1[2]) {
        do {
          func_0x0f402098(*puVar1);
          func_0x0f402030(puVar1 + 1);
          iVar2 = iVar2 + 4;
          puVar1 = puVar1 + 4;
        } while (iVar2 < param_1[2]);
      }
      func_0x0f402080();
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}



void FUN_00408e34(int *param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_004034b8(1);
  if (param_1 != (int *)0x0) {
    do {
      iVar1 = param_1[1];
      iVar2 = 0;
      func_0x0f4020e0();
      if (0 < param_1[2]) {
        do {
          func_0x0f402068(iVar1);
          func_0x0f402030(iVar1 + 0xc);
          iVar2 = iVar2 + 6;
          iVar1 = iVar1 + 0x18;
        } while (iVar2 < param_1[2]);
      }
      func_0x0f402080();
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}



void FUN_00408ed0(int *param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_004034b8(0);
  if (param_1 != (int *)0x0) {
    do {
      iVar1 = param_1[1];
      iVar2 = 0;
      func_0x0f4020e8();
      if (0 < param_1[2]) {
        do {
          func_0x0f402030(iVar1);
          iVar2 = iVar2 + 1;
          iVar1 = iVar1 + 0xc;
        } while (iVar2 < param_1[2]);
      }
      func_0x0f402088();
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}



void FUN_00408f64(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  FUN_004034b8(0);
  if (param_1 != (int *)0x0) {
    do {
      puVar1 = (undefined4 *)param_1[1];
      iVar2 = 8;
      func_0x0f4020e8();
      func_0x0f402098(*puVar1);
      func_0x0f402030(puVar1 + 1);
      func_0x0f402098(puVar1[4]);
      func_0x0f402030(puVar1 + 5);
      puVar1 = puVar1 + 8;
      if (8 < param_1[2]) {
        do {
          func_0x0f402098(*puVar1);
          func_0x0f402030(puVar1 + 1);
          iVar2 = iVar2 + 4;
          puVar1 = puVar1 + 4;
        } while (iVar2 < param_1[2]);
      }
      func_0x0f402088();
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}



void FUN_00409030(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  FUN_004034b8(0);
  if (param_1 != (int *)0x0) {
    do {
      puVar1 = (undefined4 *)param_1[1];
      iVar2 = 8;
      func_0x0f4020f0();
      func_0x0f402098(*puVar1);
      func_0x0f402030(puVar1 + 1);
      func_0x0f402098(puVar1[4]);
      func_0x0f402030(puVar1 + 5);
      puVar1 = puVar1 + 8;
      if (8 < param_1[2]) {
        do {
          func_0x0f402098(*puVar1);
          func_0x0f402030(puVar1 + 1);
          iVar2 = iVar2 + 4;
          puVar1 = puVar1 + 4;
        } while (iVar2 < param_1[2]);
      }
      func_0x0f402090();
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}



void FUN_004090fc(int *param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_004034b8(1);
  if (param_1 != (int *)0x0) {
    do {
      iVar1 = param_1[1];
      iVar2 = 0xc;
      func_0x0f4020e8();
      func_0x0f402068(iVar1);
      func_0x0f402030(iVar1 + 0xc);
      func_0x0f402068(iVar1 + 0x18);
      func_0x0f402030(iVar1 + 0x24);
      if (0xc < param_1[2]) {
        do {
          func_0x0f402068(iVar1);
          func_0x0f402030(iVar1 + 0xc);
          iVar2 = iVar2 + 6;
          iVar1 = iVar1 + 0x18;
        } while (iVar2 < param_1[2]);
      }
      func_0x0f402088();
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}



undefined4 FUN_004091e0(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar3;
  undefined4 uVar2;
  
  if ((param_1 == (byte *)0x0) || (param_2 == (byte *)0x0)) {
    func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001ee0,s_cistrequal__string_is_NULL_10001ef4
                   );
    FUN_0040d3c0(1);
  }
  while( true ) {
    bVar1 = *param_1;
    bVar3 = *param_2;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    if ((0x40 < bVar1) && (bVar1 < 0x5b)) {
      bVar1 = bVar1 + 0x20;
    }
    if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
      bVar3 = bVar3 + 0x20;
    }
    if (bVar1 != bVar3) break;
    if ((bVar1 == 0) || (bVar3 == 0)) {
      if (bVar1 == 0) {
        uVar2 = 0;
        if (bVar3 == 0) {
          uVar2 = 1;
        }
      }
      else {
        uVar2 = 0;
      }
      return uVar2;
    }
  }
  return 0;
}



void FUN_004092d4(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  char *pcVar5;
  int unaff_gp;
  undefined4 local_res4 [3];
  
  local_res4[0] = param_2;
  local_res4[1] = param_3;
  local_res4[2] = param_4;
  puVar3 = local_res4;
  pcVar4 = &DAT_100047f0;
  cVar1 = *param_1;
  pcVar5 = param_1 + 1;
  while (cVar1 != '\0') {
    if (cVar1 == '%') {
      *pcVar4 = '\0';
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      if (cVar1 == 'c') {
        func_0x0f8012c0(pcVar4,unaff_gp + -0x7c4c,*puVar3);
      }
      else if (cVar1 == 'd') {
        func_0x0f8012c0(pcVar4,unaff_gp + -0x7c48,*puVar3);
      }
      else if (cVar1 == 's') {
        func_0x0f8012c0(pcVar4,unaff_gp + -0x7c50,*puVar3);
      }
      else if (cVar1 == 'x') {
        func_0x0f8012c0(pcVar4,unaff_gp + -0x7c44,*puVar3);
      }
      puVar3 = puVar3 + 1;
      iVar2 = func_0x0f801308(pcVar4);
      pcVar4 = pcVar4 + iVar2;
    }
    else {
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    }
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  }
  *pcVar4 = '\n';
  pcVar4[1] = '\0';
  func_0x0f801150(&DAT_100036b4,&DAT_100047f0);
  FUN_0040d3c0(1);
  return;
}



int * FUN_0040948c(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  piVar1 = (int *)func_0x0f801208(param_1 << 2);
  if (piVar1 == (int *)0x0) {
    FUN_004092d4(s_ArrayAlloc___s_10001f10,param_4);
  }
  iVar4 = 0;
  if (0 < param_1) {
    piVar3 = piVar1;
    do {
      iVar2 = func_0x0f801208(param_2 * param_3);
      *piVar3 = iVar2;
      if (iVar2 == 0) {
        FUN_004092d4(s_ArrayAlloc___s_10001f20,param_4);
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar4 != param_1);
  }
  return piVar1;
}



void FUN_00409558(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = param_1;
  if (0 < param_2) {
    do {
      func_0x0f801200(*puVar1);
      iVar2 = iVar2 + 1;
      puVar1 = puVar1 + 1;
    } while (iVar2 != param_2);
  }
  func_0x0f801200(param_1);
  return;
}



void FUN_00409610(undefined4 *param_1,ushort *param_2,ushort *param_3,ushort *param_4,uint param_5)

{
  uint uVar1;
  undefined4 *puVar2;
  
  uVar1 = 0;
  if (0 < (int)param_5) {
    if ((param_5 & 3) != 0) {
      do {
        uVar1 = uVar1 + 1;
        *param_2 = (ushort)*param_1 & 0xff;
        param_2 = param_2 + 1;
        *param_3 = (ushort)((uint)*param_1 >> 8) & 0xff;
        param_3 = param_3 + 1;
        *param_4 = (ushort)((uint)*param_1 >> 0x10) & 0xff;
        param_4 = param_4 + 1;
        param_1 = param_1 + 1;
      } while ((param_5 & 3) != uVar1);
      if (uVar1 == param_5) {
        return;
      }
    }
    do {
      *param_2 = (ushort)*param_1 & 0xff;
      *param_3 = (ushort)((uint)*param_1 >> 8) & 0xff;
      *param_4 = (ushort)((uint)*param_1 >> 0x10) & 0xff;
      param_2[1] = (ushort)param_1[1] & 0xff;
      puVar2 = param_1 + 2;
      param_3[1] = (ushort)((uint)param_1[1] >> 8) & 0xff;
      param_4[1] = (ushort)((uint)param_1[1] >> 0x10) & 0xff;
      param_2[2] = (ushort)*puVar2 & 0xff;
      param_3[2] = (ushort)((uint)*puVar2 >> 8) & 0xff;
      param_4[2] = (ushort)((uint)*puVar2 >> 0x10) & 0xff;
      param_2[3] = (ushort)param_1[3] & 0xff;
      param_3[3] = (ushort)((uint)param_1[3] >> 8) & 0xff;
      uVar1 = uVar1 + 4;
      param_4[3] = (ushort)((uint)param_1[3] >> 0x10) & 0xff;
      param_1 = param_1 + 4;
      param_4 = param_4 + 4;
      param_3 = param_3 + 4;
      param_2 = param_2 + 4;
    } while (uVar1 != param_5);
  }
  return;
}



void FUN_00409778(char *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int unaff_gp;
  uint local_2c;
  
  bVar1 = false;
  if (*param_1 != '\0') {
    func_0x0f801250(s_SaveImage__saving_image_to__s_10001f30,param_1);
    iVar2 = FUN_0040ae50(param_1,unaff_gp + -0x7c40,0x101,3,**(undefined4 **)(unaff_gp + -0x7e98),
                         (*(undefined4 **)(unaff_gp + -0x7e98))[1],3);
    if (iVar2 == 0) {
      func_0x0f801150(&DAT_100036b4,s_SaveImage__can_t_open_image_file_10001f50,param_1);
      FUN_0040d3c0(1);
    }
    iVar3 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 2);
    iVar4 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 1);
    iVar5 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 1);
    iVar6 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 1);
    if ((((iVar3 == 0) || (iVar4 == 0)) || (iVar5 == 0)) || (iVar6 == 0)) {
      func_0x0f801150(&DAT_100036b4,s_SaveImage__malloc_failed_10001f78);
      FUN_0040d3c0(1);
    }
    if (*(short *)(iVar2 + 10) != 3) {
      func_0x0f801150(&DAT_100036b4,s_Assert_failed___s_10001f94,
                      s_SaveImage__expected_zsize__3_10001fa8);
      FUN_0040d3c0(1);
    }
    func_0x0f4015f8(1);
    uVar8 = 0;
    if (*(short *)(iVar2 + 8) != 0) {
      do {
        uVar7 = func_0x0f4015e8(0,uVar8,(int)((*(ushort *)(iVar2 + 6) - 1) * 0x10000) >> 0x10,uVar8,
                                iVar3);
        if (uVar7 != *(ushort *)(iVar2 + 6)) {
          bVar1 = true;
          local_2c = uVar7;
        }
        FUN_00409610(iVar3,iVar4,iVar5,iVar6,(uint)*(ushort *)(iVar2 + 6));
        FUN_0040b6e0(iVar2,iVar4,uVar8,0);
        FUN_0040b6e0(iVar2,iVar5,uVar8,1);
        FUN_0040b6e0(iVar2,iVar6,uVar8,2);
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(ushort *)(iVar2 + 8));
    }
    if (bVar1) {
      func_0x0f801150(&DAT_100036b4,s_SaveImage__bad_lrectread_return_v_10001fc8,local_2c);
    }
    FUN_0040bee0(iVar2);
    func_0x0f801200(iVar3);
    func_0x0f801200(iVar4);
    func_0x0f801200(iVar5);
    func_0x0f801200(iVar6);
  }
  return;
}



undefined4 FUN_00409a00(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  int unaff_gp;
  float fVar13;
  
  *(undefined4 *)(unaff_gp + -0x7a64) = 0;
  *(undefined4 *)(unaff_gp + -0x7a60) = 0;
  *(undefined4 *)(unaff_gp + -0x7a5c) = 0;
  *(undefined4 *)(unaff_gp + -0x7a78) = 0;
  *(undefined4 **)(unaff_gp + -0x7a6c) = &DAT_1000485c;
  *(undefined4 **)(unaff_gp + -0x7a68) = &DAT_10004ab4;
  *(undefined4 *)(unaff_gp + -0x7a80) = 0xffffffff;
switchD_0040a3ac_caseD_30:
  piVar9 = *(int **)(unaff_gp + -0x7a68);
  iVar7 = *(int *)(unaff_gp + -0x7a64);
  pfVar11 = *(float **)(unaff_gp + -0x7a6c);
LAB_00409a80:
  piVar9 = piVar9 + 1;
  if (&DAT_10004d10 <= piVar9) {
    FUN_00405520(s__yacc_stack_overflow_10002e07 + 1);
    return 1;
  }
  *piVar9 = iVar7;
  iVar10 = iVar7 * 4;
  pfVar11[1] = *(float *)(unaff_gp + -0x7a74);
  iVar2 = *(int *)(&DAT_1000245c + iVar10);
  pfVar12 = pfVar11 + 1;
  do {
    if (iVar2 < -999) {
      iVar2 = *(int *)(&DAT_10002ba0 + iVar10);
    }
    else {
      if (*(int *)(unaff_gp + -0x7a80) < 0) {
        iVar8 = FUN_004054e0();
        *(int *)(unaff_gp + -0x7a80) = iVar8;
        if (iVar8 < 0) {
          *(undefined4 *)(unaff_gp + -0x7a80) = 0;
        }
      }
      iVar2 = iVar2 + *(int *)(unaff_gp + -0x7a80);
      if ((iVar2 < 0) || (0x110 < iVar2)) {
        iVar2 = *(int *)(&DAT_10002ba0 + iVar10);
      }
      else {
        iVar2 = (&DAT_10002018)[iVar2];
        if (*(int *)(unaff_gp + -0x7a80) == *(int *)(&DAT_10002938 + iVar2 * 4)) {
          *(undefined4 *)(unaff_gp + -0x7a80) = 0xffffffff;
          *(undefined4 *)(unaff_gp + -0x7a74) = *(undefined4 *)(unaff_gp + -0x7a7c);
          iVar7 = iVar2;
          pfVar11 = pfVar12;
          if (0 < *(int *)(unaff_gp + -0x7a78)) {
            *(int *)(unaff_gp + -0x7a78) = *(int *)(unaff_gp + -0x7a78) + -1;
          }
          goto LAB_00409a80;
        }
        iVar2 = *(int *)(&DAT_10002ba0 + iVar10);
      }
    }
    if (iVar2 == -2) {
      if (*(int *)(unaff_gp + -0x7a80) < 0) {
        iVar2 = FUN_004054e0();
        *(int *)(unaff_gp + -0x7a80) = iVar2;
        if (iVar2 < 0) {
          *(undefined4 *)(unaff_gp + -0x7a80) = 0;
        }
      }
      puVar5 = &DAT_10002000;
      iVar2 = DAT_10002004;
      if (DAT_10002000 != -1) goto LAB_00409c08;
      while (iVar7 != iVar2) {
LAB_00409c08:
        do {
          puVar6 = puVar5;
          puVar5 = puVar6 + 2;
        } while (puVar6[2] != -1);
        iVar2 = puVar6[3];
      }
      puVar6 = puVar5 + 2;
      if ((-1 < (int)puVar5[2]) && (*(int *)(unaff_gp + -0x7a80) != puVar5[2])) {
        do {
          piVar1 = puVar6 + 2;
          puVar6 = puVar6 + 2;
          if (*piVar1 < 0) break;
        } while (*(int *)(unaff_gp + -0x7a80) != *piVar1);
      }
      iVar2 = puVar6[1];
      if (iVar2 < 0) {
        return 0;
      }
    }
    if (iVar2 != 0) {
switchD_00409cb0_caseD_4:
      iVar10 = iVar2 * 4;
      uVar3 = *(uint *)(iVar10 + 0x10002838);
      *(int *)(unaff_gp + -0x7a60) = iVar2;
      iVar7 = (int)uVar3 >> 1;
      if ((uVar3 & 1) == 0) {
        pfVar11 = pfVar12 + -iVar7;
        *(float *)(unaff_gp + -0x7a74) = pfVar11[1];
        piVar9 = piVar9 + -iVar7;
        iVar2 = *(int *)(*(int *)(iVar10 + 0x10002738) * 4 + 0x100026c4);
        iVar8 = iVar2 + *piVar9 + 1;
        if ((0x110 < iVar8) ||
           (iVar7 = (&DAT_10002018)[iVar8],
           -*(int *)(iVar10 + 0x10002738) != *(int *)(&DAT_10002938 + (&DAT_10002018)[iVar8] * 4)))
        {
          iVar7 = (&DAT_10002018)[iVar2];
        }
        goto LAB_00409a80;
      }
      *(float *)(unaff_gp + -0x7a74) = (pfVar12 + -iVar7)[1];
      iVar2 = *(int *)(*(int *)(iVar10 + 0x10002738) * 4 + 0x100026c4);
      iVar8 = iVar2 + piVar9[-iVar7] + 1;
      if ((0x110 < iVar8) ||
         (iVar8 = (&DAT_10002018)[iVar8],
         -*(int *)(iVar10 + 0x10002738) != *(int *)(&DAT_10002938 + iVar8 * 4))) {
        iVar8 = (&DAT_10002018)[iVar2];
      }
      *(int *)(unaff_gp + -0x7a64) = iVar8;
      *(int **)(unaff_gp + -0x7a68) = piVar9 + -iVar7;
      *(float **)(unaff_gp + -0x7a6c) = pfVar12 + -iVar7;
      switch(*(undefined4 *)(unaff_gp + -0x7a60)) {
      case 0x10:
        FUN_00405f9c(pfVar11[-2],pfVar11[-1],iVar10,iVar2,*pfVar11);
        break;
      case 0x11:
        FUN_00405f00(*pfVar11);
        break;
      case 0x12:
        FUN_00406054(pfVar11[-2],pfVar11[-1],iVar10,iVar2,*pfVar11);
        break;
      case 0x13:
        FUN_004065e0(*pfVar11);
        FUN_00408074(*pfVar11);
        break;
      case 0x14:
        FUN_00406b90(*pfVar11);
        FUN_00408074(*pfVar11);
        break;
      case 0x15:
        FUN_00407068(*pfVar11);
        FUN_00408074(*pfVar11);
        break;
      case 0x16:
        FUN_00406110(pfVar11[-2],pfVar11[-1],iVar10,iVar2,*pfVar11);
        break;
      case 0x17:
        FUN_00407a8c(*pfVar11);
        FUN_00408074(*pfVar11);
        break;
      case 0x18:
        FUN_00407b6c(*pfVar11);
        FUN_00408074(*pfVar11);
        break;
      case 0x19:
        uVar4 = FUN_0040a400();
        FUN_0040a6d4(uVar4,*pfVar12);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x1a:
        FUN_0040a6d4(*pfVar11,*pfVar12);
        *(float *)(unaff_gp + -0x7a74) = *pfVar11;
        break;
      case 0x1b:
        uVar4 = FUN_0040a400();
        FUN_0040a6d4(uVar4,*pfVar12);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x1c:
        uVar4 = FUN_0040a400();
        FUN_0040a6d4(uVar4,*pfVar11);
        FUN_0040a6d4(uVar4,*pfVar12);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x1d:
        uVar4 = FUN_0040a400();
        FUN_0040a6d4(uVar4,*pfVar12);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x1e:
        uVar4 = FUN_0040a400();
        FUN_0040a6d4(uVar4,*pfVar11);
        FUN_0040a6d4(uVar4,*pfVar12);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x1f:
        FUN_0040a6d4(*pfVar11,*pfVar12);
        *(float *)(unaff_gp + -0x7a74) = *pfVar11;
        break;
      case 0x20:
        FUN_0040a6d4(pfVar11[-1],*pfVar11);
        FUN_0040a6d4(pfVar11[-1],*pfVar12);
        *(float *)(unaff_gp + -0x7a74) = pfVar11[-1];
        break;
      case 0x21:
        *(float *)(unaff_gp + -0x7a74) = *pfVar12;
        break;
      case 0x22:
        *(float *)(unaff_gp + -0x7a74) = *pfVar12;
        break;
      case 0x23:
        uVar4 = FUN_00407c44(0x110,*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x24:
        uVar4 = FUN_00407c44(0x103,*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x25:
        uVar4 = FUN_00407c44(0x107,*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x26:
        uVar4 = FUN_00407c44(pfVar11[-2],*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x27:
        uVar4 = FUN_004063a0(pfVar11[-3],pfVar11[-2],iVar10,iVar2,pfVar11[-1],*pfVar11);
        uVar4 = FUN_00407c44(0x10c,uVar4);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x28:
        fVar13 = *pfVar11;
        uVar4 = FUN_00406468(fVar13,fVar13,iVar10,iVar2,fVar13);
        uVar4 = FUN_00407c44(0x10d,uVar4);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x29:
        uVar4 = FUN_00406524(pfVar11[-2],pfVar11[-1],iVar10,iVar2,*pfVar11);
        uVar4 = FUN_00407c44(0x10f,uVar4);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x2a:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x103;
        break;
      case 0x2b:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x104;
        break;
      case 0x2c:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x111;
        break;
      case 0x2d:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x107;
        break;
      case 0x2e:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x109;
        break;
      case 0x2f:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x10a;
        break;
      case 0x30:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x10b;
        break;
      case 0x31:
        *(undefined4 *)(unaff_gp + -0x7a74) = 0x110;
        break;
      case 0x32:
        FUN_004061d0(*pfVar11);
        FUN_004081a4(*pfVar11);
        break;
      case 0x33:
        uVar4 = FUN_0040a400();
        FUN_0040a6d4(uVar4,*pfVar12);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x34:
        FUN_0040a6d4(*pfVar11,*pfVar12);
        *(float *)(unaff_gp + -0x7a74) = *pfVar11;
        break;
      case 0x35:
        uVar4 = FUN_00408124(0x113,pfVar11[-2],pfVar11[-1],*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x36:
        uVar4 = FUN_00408124(0x112,pfVar11[-2],pfVar11[-1],*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x37:
        uVar4 = FUN_004080c4(0x115,*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x38:
        uVar4 = FUN_004080c4(0x116,*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x39:
        uVar4 = FUN_004080c4(0x114,*pfVar11);
        *(undefined4 *)(unaff_gp + -0x7a74) = uVar4;
        break;
      case 0x3a:
        *(float *)(unaff_gp + -0x7a74) = *pfVar12;
        break;
      case 0x3b:
        *(int *)(unaff_gp + -0x7a74) = -(int)*pfVar12;
        break;
      case 0x3c:
        *(float *)(unaff_gp + -0x7a74) = *pfVar12;
        break;
      case 0x3d:
        *(float *)(unaff_gp + -0x7a74) = -*pfVar12;
        break;
      case 0x3e:
        *(float *)(unaff_gp + -0x7a74) = *pfVar12;
        break;
      case 0x3f:
        *(float *)(unaff_gp + -0x7a74) = (float)(int)*pfVar12;
      }
      goto switchD_0040a3ac_caseD_30;
    }
    switch(*(undefined4 *)(unaff_gp + -0x7a78)) {
    case 0:
      FUN_00405520(s_syntax_error_10002e1c);
    case 1:
    case 2:
      goto switchD_00409cb0_caseD_1;
    case 3:
      if (*(int *)(unaff_gp + -0x7a80) == 0) {
        return 1;
      }
      *(undefined4 *)(unaff_gp + -0x7a80) = 0xffffffff;
      iVar2 = *(int *)(&DAT_1000245c + iVar10);
      break;
    default:
      goto switchD_00409cb0_caseD_4;
    }
  } while( true );
switchD_00409cb0_caseD_1:
  *(undefined4 *)(unaff_gp + -0x7a78) = 3;
  pfVar11 = pfVar12;
  while( true ) {
    if (piVar9 < &DAT_10004ab8) {
      return 1;
    }
    iVar7 = *(int *)(&DAT_1000245c + *piVar9 * 4) + 0x100;
    if (((-1 < iVar7) && (iVar7 < 0x111)) &&
       (iVar7 = (&DAT_10002018)[iVar7], *(int *)(&DAT_10002938 + iVar7 * 4) == 0x100)) break;
    piVar9 = piVar9 + -1;
    pfVar11 = pfVar11 + -1;
  }
  goto LAB_00409a80;
}



int * FUN_0040a400(void)

{
  int *piVar1;
  int iVar2;
  int unaff_gp;
  
  piVar1 = (int *)func_0x0f801208(0xc);
  if (piVar1 == (int *)0x0) {
    FUN_004092d4(*(undefined4 *)(unaff_gp + -0x7c30));
  }
  piVar1[1] = 0;
  piVar1[2] = 0;
  iVar2 = func_0x0f801208(0x10);
  if (iVar2 == 0) {
    FUN_004092d4(*(undefined4 *)(unaff_gp + -0x7c30));
  }
  *(int *)iVar2 = iVar2;
  *(int *)(iVar2 + 4) = iVar2;
  *(undefined4 *)(iVar2 + 8) = 0;
  *(undefined4 *)(iVar2 + 0xc) = 0;
  *piVar1 = iVar2;
  return piVar1;
}



void FUN_0040a48c(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = (int *)*param_1;
  piVar1 = (int *)0;
  for (piVar2 = (int *)*piVar3; piVar2 != piVar3; piVar2 = (int *)*piVar2) {
    if (piVar1 != (int *)0x0) {
      if (*(int *)((int)piVar1 + 0xc) == -1) {
        FUN_0040a48c(*(undefined4 *)((int)piVar1 + 8));
      }
      func_0x0f801200(piVar1);
    }
    piVar1 = piVar2;
  }
  if (piVar1 != (int *)0x0) {
    if (*(int *)((int)piVar1 + 0xc) == -1) {
      FUN_0040a48c(*(undefined4 *)((int)piVar1 + 8));
    }
    func_0x0f801200(piVar1);
  }
  func_0x0f801200(piVar3);
  func_0x0f801200(param_1);
  return;
}



void FUN_0040a570(undefined4 *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int unaff_gp;
  
  piVar2 = (int *)*param_1;
  iVar3 = *piVar2;
  piVar1 = (int *)FUN_0040adf0(*(undefined4 *)(unaff_gp + -0x7c20),0x10);
  piVar1[3] = 0;
  piVar1[1] = (int)piVar2;
  *piVar1 = iVar3;
  piVar1[2] = param_2;
  *piVar2 = (int)piVar1;
  *(int **)(iVar3 + 4) = piVar1;
  param_1[2] = param_1[2] + 1;
  return;
}



undefined4 FUN_0040a5e8(undefined4 *param_1,int param_2,uint param_3)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int unaff_gp;
  
  if ((int)param_1[2] < (int)param_3) {
    return 0;
  }
  piVar3 = (int *)*param_1;
  uVar2 = 0;
  if (0 < (int)param_3) {
    if ((param_3 & 3) != 0) {
      do {
        piVar3 = (int *)*piVar3;
        uVar2 = uVar2 + 1;
      } while ((param_3 & 3) != uVar2);
      if (uVar2 == param_3) goto LAB_0040a66c;
    }
    do {
      uVar2 = uVar2 + 4;
      piVar3 = *(int **)**(undefined4 **)*piVar3;
    } while (uVar2 != param_3);
  }
LAB_0040a66c:
  iVar4 = *piVar3;
  piVar1 = (int *)FUN_0040adf0(*(undefined4 *)(unaff_gp + -0x7c1c),0x10);
  piVar1[3] = 0;
  piVar1[1] = (int)piVar3;
  *piVar1 = iVar4;
  piVar1[2] = param_2;
  *piVar3 = (int)piVar1;
  *(int **)(iVar4 + 4) = piVar1;
  param_1[2] = param_1[2] + 1;
  return 1;
}



void FUN_0040a6d4(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int unaff_gp;
  
  iVar2 = *param_1;
  piVar3 = *(int **)(iVar2 + 4);
  piVar1 = (int *)FUN_0040adf0(*(undefined4 *)(unaff_gp + -0x7c18),0x10);
  piVar1[3] = 0;
  *piVar1 = iVar2;
  piVar1[1] = (int)piVar3;
  piVar1[2] = param_2;
  *piVar3 = (int)piVar1;
  *(int **)(iVar2 + 4) = piVar1;
  param_1[2] = param_1[2] + 1;
  return;
}



undefined4 FUN_0040a74c(int *param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  
  piVar1 = (int *)*param_1;
  piVar3 = (int *)*piVar1;
  piVar1[2] = param_2;
  iVar4 = piVar3[2];
  while (param_2 != iVar4) {
    piVar3 = (int *)*piVar3;
    iVar4 = piVar3[2];
  }
  uVar2 = 0;
  if (piVar3 != piVar1) {
    piVar1 = (int *)piVar3[1];
    iVar4 = *piVar3;
    *piVar1 = iVar4;
    *(int **)(iVar4 + 4) = piVar1;
    if (piVar3 == (int *)param_1[1]) {
      param_1[1] = 0;
    }
    func_0x0f801200(piVar3);
    uVar2 = 1;
    param_1[2] = param_1[2] + -1;
  }
  return uVar2;
}



undefined4 FUN_0040a7fc(undefined4 *param_1,uint param_2)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  if (((int)param_2 < 1) || ((int)param_1[2] < (int)param_2)) {
    return 0;
  }
  piVar4 = (int *)*param_1;
  uVar1 = 0;
  if (0 < (int)param_2) {
    if ((param_2 & 3) != 0) {
      do {
        piVar4 = (int *)*piVar4;
        uVar1 = uVar1 + 1;
      } while ((param_2 & 3) != uVar1);
      if (uVar1 == param_2) goto LAB_0040a87c;
    }
    do {
      uVar1 = uVar1 + 4;
      piVar4 = *(int **)**(undefined4 **)*piVar4;
    } while (uVar1 != param_2);
  }
LAB_0040a87c:
  piVar2 = (int *)piVar4[1];
  iVar3 = *piVar4;
  *piVar2 = iVar3;
  *(int **)(iVar3 + 4) = piVar2;
  if (piVar4 == (int *)param_1[1]) {
    param_1[1] = 0;
  }
  func_0x0f801200();
  param_1[2] = param_1[2] + -1;
  return 1;
}



undefined4 FUN_0040a8e0(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = *(int **)*param_1;
  if (piVar1 == (int *)*param_1) {
    param_1[1] = 0;
    uVar2 = 0;
  }
  else {
    param_1[1] = (int)piVar1;
    uVar2 = piVar1[2];
  }
  return uVar2;
}



undefined4 FUN_0040a918(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (((int *)param_1[1] != (int *)0x0) && (iVar1 = *(int *)param_1[1], iVar1 != *param_1)) {
    uVar2 = *(undefined4 *)(iVar1 + 8);
    param_1[1] = iVar1;
  }
  return uVar2;
}



undefined4 FUN_0040aa70(undefined4 *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  
  uVar1 = FUN_0040a400();
  piVar3 = (int *)*param_1;
  for (piVar2 = (int *)*piVar3; piVar2 != piVar3; piVar2 = (int *)*piVar2) {
    FUN_0040a6d4(uVar1,piVar2[2]);
  }
  return uVar1;
}



undefined4 FUN_0040aae4(undefined4 *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  
  uVar1 = FUN_0040a400();
  piVar3 = (int *)*param_1;
  for (piVar2 = (int *)*piVar3; piVar2 != piVar3; piVar2 = (int *)*piVar2) {
    FUN_0040a570(uVar1,piVar2[2]);
  }
  return uVar1;
}



undefined4 FUN_0040ab58(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  
  uVar1 = FUN_0040a400();
  piVar3 = (int *)*param_1;
  for (piVar2 = (int *)*piVar3; piVar2 != piVar3; piVar2 = (int *)*piVar2) {
    FUN_0040a6d4(uVar1,piVar2[2]);
  }
  piVar3 = (int *)*param_2;
  for (piVar2 = (int *)*piVar3; piVar2 != piVar3; piVar2 = (int *)*piVar2) {
    FUN_0040a6d4(uVar1,piVar2[2]);
  }
  return uVar1;
}



void FUN_0040ac0c(undefined4 *param_1,code *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = (int *)*param_1;
  for (piVar1 = (int *)*piVar2; piVar1 != piVar2; piVar1 = (int *)*piVar1) {
    (*param_2)(piVar1[2]);
  }
  return;
}



int FUN_0040ac6c(int *param_1,int param_2,code *param_3)

{
  int iVar1;
  int *piVar2;
  int unaff_gp;
  
  iVar1 = (*param_3)(param_2,param_2);
  if (iVar1 == 0) {
    func_0x0f801150(&DAT_100036b4,s_ERROR___s___s_10002e80,*(undefined4 *)(unaff_gp + -0x7c10),
                    s_compare_function_never_returns_T_10002e90);
  }
  else {
    param_1 = (int *)*param_1;
    piVar2 = (int *)*param_1;
    param_1[2] = param_2;
    iVar1 = (*param_3)(param_2,piVar2[2]);
    while (iVar1 == 0) {
      piVar2 = (int *)*piVar2;
      iVar1 = (*param_3)(param_2,piVar2[2]);
    }
    if (piVar2 != param_1) {
      return piVar2[2];
    }
  }
  return 0;
}



int FUN_0040ad48(undefined4 *param_1,undefined4 param_2,code *param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = (int *)*param_1;
  piVar2 = (int *)*piVar3;
  if (piVar2 != piVar3) {
    iVar1 = (*param_3)(param_2,piVar2[2]);
    while ((iVar1 == 0 && (piVar2 = (int *)*piVar2, piVar2 != piVar3))) {
      iVar1 = (*param_3)(param_2,piVar2[2]);
    }
  }
  iVar1 = 0;
  if (piVar2 != piVar3) {
    iVar1 = piVar2[2];
  }
  return iVar1;
}



undefined4 FUN_0040ade4(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}



int FUN_0040adf0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = func_0x0f801208(param_2);
  if (iVar1 == 0) {
    func_0x0f801150(&DAT_100036b4,s_ERROR___s___s_10002fc0,param_1,s_out_of_memory__10002fd0);
  }
  return iVar1;
}



void FUN_0040ae50(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  FUN_0040aef8(0,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}



void FUN_0040aea8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  FUN_0040aef8(param_1,0,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}



ushort * FUN_0040aef8(int param_1,int param_2,char *param_3,ushort param_4,uint param_5,
                     ushort param_6,ushort param_7,ushort param_8)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  ushort *puVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int unaff_gp;
  uint uVar9;
  int local_res0;
  
  puVar4 = (ushort *)func_0x0f801208(0x98);
  func_0x0f801040(puVar4,0x98);
  bVar3 = param_3[1] == '+';
  if (bVar3) {
    FUN_0040b640(s_iopen__read_write_mode_not_suppo_10002fe0);
    return (ushort *)0x0;
  }
  local_res0 = param_1;
  if (*param_3 == 'w') {
    if (((param_2 != 0) && (local_res0 = FUN_0040df80(param_2,0x1b6), bVar3)) && (-1 < local_res0))
    {
      FUN_0040dfa0(local_res0);
      local_res0 = FUN_0040dfc0(param_2,2);
    }
    if (local_res0 < 0) {
      FUN_0040b640(s_iopen__can_t_open_output_file__s_10003008,param_2);
      return (ushort *)0x0;
    }
    *puVar4 = 0x1da;
    puVar4[1] = param_4;
    puVar4[4] = 1;
    puVar4[5] = 1;
    puVar4[3] = param_6;
    if (1 < param_5) {
      puVar4[4] = param_7;
    }
    if (2 < param_5) {
      puVar4[5] = param_8;
    }
    if (puVar4[5] == 1) {
      puVar4[2] = 2;
      if (puVar4[4] == 1) {
        puVar4[2] = 1;
      }
    }
    else {
      puVar4[2] = 3;
    }
    puVar4[6] = 0x98;
    puVar4[7] = 0x9680;
    puVar4[8] = 0;
    puVar4[9] = 0;
    FUN_0040c180(puVar4,unaff_gp + -0x7c00);
    puVar4[10] = 0;
    puVar4[0xb] = 0;
    puVar4[0x39] = 0;
    iVar5 = FUN_0040dfe0(local_res0,puVar4,0x98);
    if (iVar5 != 0x98) {
      FUN_0040b640(s_iopen__error_on_write_of_image_h_1000302c);
      return (ushort *)0x0;
    }
  }
  else {
    if (param_2 != 0) {
      uVar6 = 0;
      if (bVar3) {
        uVar6 = 2;
      }
      local_res0 = FUN_0040dfc0(param_2,uVar6);
    }
    if (local_res0 < 0) {
      return (ushort *)0x0;
    }
    iVar5 = FUN_0040e000(local_res0,puVar4,0x98);
    if (iVar5 != 0x98) {
      FUN_0040b640(s_iopen__error_on_read_of_image_he_10003054);
      return (ushort *)0x0;
    }
    if (((uint)(*puVar4 >> 8) | (*puVar4 & 0xff) << 8) == 0x1da) {
      puVar4[0x39] = 1;
      FUN_0040b5f8(puVar4);
      uVar1 = *puVar4;
    }
    else {
      puVar4[0x39] = 0;
      uVar1 = *puVar4;
    }
    if (uVar1 != 0x1da) {
      FUN_0040b640(s_iopen__bad_magic_in_image_file___1000307c);
      return (ushort *)0x0;
    }
  }
  if (bVar3) {
    puVar4[0x38] = 0x80;
  }
  else if (*param_3 == 'r') {
    puVar4[0x38] = 1;
  }
  else {
    puVar4[0x38] = 2;
  }
  if ((puVar4[1] & 0xff00) == 0x100) {
    uVar1 = puVar4[4];
    uVar2 = puVar4[5];
    iVar5 = (uint)uVar1 * (uint)uVar2 * 4;
    uVar6 = func_0x0f801208(iVar5);
    *(undefined4 *)(puVar4 + 0x48) = uVar6;
    uVar6 = func_0x0f801208(iVar5);
    *(undefined4 *)(puVar4 + 0x4a) = uVar6;
    if ((*(int *)(puVar4 + 0x48) == 0) || (*(int *)(puVar4 + 0x4a) == 0)) {
      FUN_0040b640(s_iopen__error_on_table_alloc_100030a0);
      return (ushort *)0x0;
    }
    *(uint *)(puVar4 + 0x46) = (uint)uVar1 * (uint)uVar2 * 8 + 0x200;
    if (*param_3 == 'w') {
      uVar7 = 0;
      uVar9 = (uint)puVar4[4] * (uint)puVar4[5];
      if (0 < (int)uVar9) {
        iVar5 = 0;
        if ((uVar9 & 3) != 0) {
          do {
            uVar7 = uVar7 + 1;
            *(undefined4 *)(*(int *)(puVar4 + 0x48) + iVar5) = 0;
            *(undefined4 *)(*(int *)(puVar4 + 0x4a) + iVar5) = 0xffffffff;
            iVar5 = iVar5 + 4;
          } while ((uVar9 & 3) != uVar7);
          if (uVar7 == uVar9) goto LAB_0040b480;
        }
        iVar5 = uVar7 << 2;
        do {
          *(undefined4 *)(*(int *)(puVar4 + 0x48) + iVar5) = 0;
          *(undefined4 *)(*(int *)(puVar4 + 0x4a) + iVar5) = 0xffffffff;
          *(undefined4 *)(*(int *)(puVar4 + 0x48) + iVar5 + 4) = 0;
          *(undefined4 *)(*(int *)(puVar4 + 0x4a) + iVar5 + 4) = 0xffffffff;
          *(undefined4 *)(*(int *)(puVar4 + 0x48) + iVar5 + 8) = 0;
          *(undefined4 *)(*(int *)(puVar4 + 0x4a) + iVar5 + 8) = 0xffffffff;
          *(undefined4 *)(*(int *)(puVar4 + 0x48) + iVar5 + 0xc) = 0;
          iVar8 = *(int *)(puVar4 + 0x4a) + iVar5;
          iVar5 = iVar5 + 0x10;
          *(undefined4 *)(iVar8 + 0xc) = 0xffffffff;
        } while (iVar5 != uVar9 * 4);
        puVar4[0x3d] = 0;
        goto LAB_0040b484;
      }
    }
    else {
      iVar8 = (uint)puVar4[4] * (uint)puVar4[5] * 4;
      FUN_0040e020(local_res0,0x200,0);
      iVar5 = FUN_0040e000(local_res0,*(undefined4 *)(puVar4 + 0x48),iVar8);
      if (iVar5 != iVar8) {
        FUN_0040b640(s_iopen__error_on_read_of_rowstart_100030c0);
        return (ushort *)0x0;
      }
      if (puVar4[0x39] != 0) {
        FUN_0040b594(*(undefined4 *)(puVar4 + 0x48),iVar8);
      }
      iVar5 = FUN_0040e000(local_res0,*(undefined4 *)(puVar4 + 0x4a),iVar8);
      if (iVar5 != iVar8) {
        FUN_0040b640(s_iopen__error_on_read_of_rowsize_100030e4);
        return (ushort *)0x0;
      }
      if (puVar4[0x39] != 0) {
        FUN_0040b594(*(undefined4 *)(puVar4 + 0x4a),iVar8);
      }
    }
  }
LAB_0040b480:
  puVar4[0x3d] = 0;
LAB_0040b484:
  puVar4[0x3e] = 0;
  puVar4[0x3f] = 0;
  puVar4[0x40] = 0;
  puVar4[0x41] = 0;
  iVar5 = FUN_0040b4f0(puVar4);
  *(int *)(puVar4 + 0x42) = iVar5;
  if (iVar5 == 0) {
    FUN_0040b640(s_iopen__error_on_tmpbuf_alloc__d_10003108,puVar4[3]);
    puVar4 = (ushort *)0x0;
  }
  else {
    puVar4[0x3a] = 0;
    puVar4[0x3b] = 0;
    puVar4[0x3c] = 0;
    puVar4[0x44] = 0;
    puVar4[0x45] = 0x200;
    *(int *)(puVar4 + 0x36) = local_res0;
    FUN_0040e020(local_res0,0x200,0);
  }
  return puVar4;
}



void FUN_0040b4f0(int param_1)

{
  func_0x0f801208(((uint)*(ushort *)(param_1 + 6) + (uint)(*(ushort *)(param_1 + 6) >> 6)) * 4);
  return;
}



void FUN_0040b550(ushort *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < param_2 >> 1) {
    do {
      iVar1 = (iVar1 + 1) * 0x10000 >> 0x10;
      *param_1 = *param_1 >> 8 | *param_1 << 8;
      param_1 = param_1 + 1;
    } while (iVar1 < param_2 >> 1);
  }
  return;
}



void FUN_0040b594(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  
  iVar1 = 0;
  if (0 < param_2 >> 2) {
    do {
      puVar3 = (uint *)(param_1 + iVar1 * 4);
      uVar2 = *puVar3;
      iVar1 = (iVar1 + 1) * 0x10000 >> 0x10;
      *puVar3 = uVar2 >> 0x18 | uVar2 >> 8 & 0xff00 | (uVar2 & 0xff00) << 8 | uVar2 << 0x18;
    } while (iVar1 < param_2 >> 2);
  }
  return;
}



void FUN_0040b5f8(int param_1)

{
  FUN_0040b550(param_1,0xc);
  FUN_0040b594(param_1 + 0xc,0xc);
  FUN_0040b594(param_1 + 0x68,4);
  return;
}



void FUN_0040b640(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int unaff_gp;
  undefined auStack_800 [2048];
  
  if (*(int *)(unaff_gp + -0x7ab0) == 0) {
    func_0x0f801150(&DAT_100036b4,param_1,param_2,param_3,param_4,param_5);
    FUN_0040d3c0(1);
  }
  else {
    func_0x0f8012c0(auStack_800,param_1,param_2,param_3,param_4,param_5);
    (**(code **)(unaff_gp + -0x7ab0))(auStack_800);
  }
  return;
}



uint FUN_0040b6e0(int param_1,ushort *param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  ushort *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  if ((*(ushort *)(param_1 + 0x70) & 0x82) == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    if (*(ushort *)(param_1 + 4) < 3) {
      param_4 = 0;
    }
    if (*(ushort *)(param_1 + 4) < 2) {
      param_3 = 0;
    }
    uVar1 = *(ushort *)(param_1 + 2);
    if ((uVar1 & 0xff00) == 0) {
      if ((uVar1 & 0xff) == 1) {
        uVar2 = (uint)*(ushort *)(param_1 + 6);
        uVar7 = *(uint *)(param_1 + 0xc);
        uVar8 = *(uint *)(param_1 + 0x10);
        pbVar5 = *(byte **)(param_1 + 0x84);
        while (uVar2 != 0) {
          uVar2 = uVar2 - 1;
          uVar1 = *param_2;
          param_2 = param_2 + 1;
          *pbVar5 = (byte)uVar1;
          uVar3 = (uint)*pbVar5;
          if (uVar8 < uVar3) {
            uVar8 = uVar3;
          }
          if (uVar3 < uVar7) {
            uVar7 = uVar3;
          }
          pbVar5 = pbVar5 + 1;
        }
        *(uint *)(param_1 + 0xc) = uVar7;
        *(uint *)(param_1 + 0x10) = uVar8;
        FUN_0040c1b0(param_1,param_3,param_4);
        uVar2 = (uint)*(ushort *)(param_1 + 6);
        uVar7 = FUN_0040c3fc(param_1,*(undefined4 *)(param_1 + 0x84),uVar2);
        if (uVar7 != uVar2) {
          uVar2 = 0xffffffff;
        }
      }
      else if ((uVar1 & 0xff) == 2) {
        uVar2 = (uint)*(ushort *)(param_1 + 6);
        uVar7 = *(uint *)(param_1 + 0xc);
        uVar8 = *(uint *)(param_1 + 0x10);
        puVar6 = param_2;
        while (uVar2 != 0) {
          uVar2 = uVar2 - 1;
          uVar3 = (uint)*puVar6;
          if (uVar8 < uVar3) {
            uVar8 = uVar3;
          }
          if (uVar3 < uVar7) {
            uVar7 = uVar3;
          }
          puVar6 = puVar6 + 1;
        }
        *(uint *)(param_1 + 0xc) = uVar7;
        *(uint *)(param_1 + 0x10) = uVar8;
        FUN_0040c1b0(param_1,param_3,param_4);
        iVar9 = (uint)*(ushort *)(param_1 + 6) << 1;
        if (*(short *)(param_1 + 0x72) != 0) {
          FUN_0040b550(param_2,iVar9);
        }
        iVar4 = FUN_0040c3fc(param_1,param_2,iVar9);
        if (iVar4 == iVar9) {
          if (*(short *)(param_1 + 0x72) != 0) {
            FUN_0040b550(param_2);
          }
          uVar2 = (uint)*(ushort *)(param_1 + 6);
        }
        else {
          if (*(short *)(param_1 + 0x72) != 0) {
            FUN_0040b550(param_2);
          }
          uVar2 = 0xffffffff;
        }
      }
      else {
        uVar2 = FUN_0040b640(s_putrow__wierd_bpp_10003130);
      }
    }
    else if ((uVar1 & 0xff00) == 0x100) {
      if ((uVar1 & 0xff) == 1) {
        uVar7 = *(uint *)(param_1 + 0xc);
        uVar8 = *(uint *)(param_1 + 0x10);
        uVar2 = (uint)*(ushort *)(param_1 + 6);
        puVar6 = param_2;
        while (uVar2 != 0) {
          uVar2 = uVar2 - 1;
          uVar3 = (uint)*puVar6;
          if (uVar8 < uVar3) {
            uVar8 = uVar3;
          }
          if (uVar3 < uVar7) {
            uVar7 = uVar3;
          }
          puVar6 = puVar6 + 1;
        }
        *(uint *)(param_1 + 0xc) = uVar7;
        *(uint *)(param_1 + 0x10) = uVar8;
        iVar9 = FUN_0040c6a8(param_2,2,*(undefined4 *)(param_1 + 0x84),1,
                             (uint)*(ushort *)(param_1 + 6));
        FUN_0040c590(param_1,iVar9,param_3,param_4);
        FUN_0040c1b0(param_1,param_3,param_4);
        iVar4 = FUN_0040c3fc(param_1,*(undefined4 *)(param_1 + 0x84),iVar9);
        if (iVar4 == iVar9) {
          uVar2 = (uint)*(ushort *)(param_1 + 6);
        }
        else {
          uVar2 = 0xffffffff;
        }
      }
      else if ((uVar1 & 0xff) == 2) {
        uVar7 = *(uint *)(param_1 + 0xc);
        uVar8 = *(uint *)(param_1 + 0x10);
        uVar2 = (uint)*(ushort *)(param_1 + 6);
        puVar6 = param_2;
        while (uVar2 != 0) {
          uVar2 = uVar2 - 1;
          uVar3 = (uint)*puVar6;
          if (uVar8 < uVar3) {
            uVar8 = uVar3;
          }
          if (uVar3 < uVar7) {
            uVar7 = uVar3;
          }
          puVar6 = puVar6 + 1;
        }
        *(uint *)(param_1 + 0xc) = uVar7;
        *(uint *)(param_1 + 0x10) = uVar8;
        iVar9 = FUN_0040c6a8(param_2,2,*(undefined4 *)(param_1 + 0x84),2,
                             (uint)*(ushort *)(param_1 + 6));
        iVar9 = iVar9 << 1;
        FUN_0040c590(param_1,iVar9,param_3,param_4);
        FUN_0040c1b0(param_1,param_3,param_4);
        if (*(short *)(param_1 + 0x72) != 0) {
          FUN_0040b550(*(undefined4 *)(param_1 + 0x84),iVar9);
        }
        iVar4 = FUN_0040c3fc(param_1,*(undefined4 *)(param_1 + 0x84),iVar9);
        if (iVar4 == iVar9) {
          if (*(short *)(param_1 + 0x72) != 0) {
            FUN_0040b550(*(undefined4 *)(param_1 + 0x84),iVar9);
          }
          uVar2 = (uint)*(ushort *)(param_1 + 6);
        }
        else {
          if (*(short *)(param_1 + 0x72) != 0) {
            FUN_0040b550(*(undefined4 *)(param_1 + 0x84),iVar9);
          }
          uVar2 = 0xffffffff;
        }
      }
      else {
        uVar2 = FUN_0040b640(s_putrow__wierd_bpp_10003144);
      }
    }
    else {
      uVar2 = FUN_0040b640(s_putrow__wierd_image_type_10003158);
    }
  }
  return uVar2;
}



uint FUN_0040bbd8(int param_1,ushort *param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  short sVar6;
  byte *pbVar7;
  int iVar8;
  
  if ((*(ushort *)(param_1 + 0x70) & 0x81) == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    if (*(ushort *)(param_1 + 4) < 3) {
      param_4 = 0;
    }
    if (*(ushort *)(param_1 + 4) < 2) {
      param_3 = 0;
    }
    FUN_0040c1b0(param_1,param_3,param_4);
    uVar2 = *(ushort *)(param_1 + 2);
    if ((uVar2 & 0xff00) == 0) {
      if ((uVar2 & 0xff) == 1) {
        uVar4 = FUN_0040c454(param_1,*(undefined4 *)(param_1 + 0x84),*(undefined2 *)(param_1 + 6));
        uVar3 = (uint)*(ushort *)(param_1 + 6);
        if (uVar4 == uVar3) {
          iVar5 = (int)(short)*(ushort *)(param_1 + 6);
          pbVar7 = *(byte **)(param_1 + 0x84);
          if (iVar5 != 0) {
            do {
              iVar5 = (iVar5 + -1) * 0x10000 >> 0x10;
              bVar1 = *pbVar7;
              pbVar7 = pbVar7 + 1;
              *param_2 = (ushort)bVar1;
              param_2 = param_2 + 1;
            } while (iVar5 != 0);
            uVar3 = (uint)*(ushort *)(param_1 + 6);
          }
        }
        else {
          uVar3 = 0xffffffff;
        }
      }
      else if ((uVar2 & 0xff) == 2) {
        iVar8 = (uint)*(ushort *)(param_1 + 6) << 0x11;
        iVar5 = FUN_0040c454(param_1,param_2,iVar8 >> 0x10);
        iVar8 = (int)(short)((uint)iVar8 >> 0x10);
        if (iVar5 == iVar8) {
          if (*(short *)(param_1 + 0x72) != 0) {
            FUN_0040b550(param_2,iVar8);
          }
          uVar3 = (uint)*(ushort *)(param_1 + 6);
        }
        else {
          uVar3 = 0xffffffff;
        }
      }
      else {
        uVar3 = FUN_0040b640(s_getrow__wierd_bpp_10003174);
      }
    }
    else if ((uVar2 & 0xff00) == 0x100) {
      if ((uVar2 & 0xff) == 1) {
        sVar6 = FUN_0040c500(param_1);
        if (sVar6 == -1) {
          uVar3 = 0xffffffff;
        }
        else {
          iVar5 = FUN_0040c454(param_1,*(undefined4 *)(param_1 + 0x84),(int)sVar6);
          if (iVar5 == sVar6) {
            FUN_0040ce2c(*(undefined4 *)(param_1 + 0x84),1,param_2,2);
            uVar3 = (uint)*(ushort *)(param_1 + 6);
          }
          else {
            uVar3 = 0xffffffff;
          }
        }
      }
      else if ((uVar2 & 0xff) == 2) {
        sVar6 = FUN_0040c500(param_1);
        if (sVar6 == -1) {
          uVar3 = 0xffffffff;
        }
        else {
          iVar5 = FUN_0040c454(param_1,*(undefined4 *)(param_1 + 0x84),(int)sVar6);
          if (sVar6 == iVar5) {
            if (*(short *)(param_1 + 0x72) != 0) {
              FUN_0040b550(*(undefined4 *)(param_1 + 0x84),(int)sVar6);
            }
            FUN_0040ce2c(*(undefined4 *)(param_1 + 0x84),2,param_2,2);
            uVar3 = (uint)*(ushort *)(param_1 + 6);
          }
          else {
            uVar3 = 0xffffffff;
          }
        }
      }
      else {
        uVar3 = FUN_0040b640(s_getrow__wierd_bpp_10003188);
      }
    }
    else {
      uVar3 = FUN_0040b640(s_getrow__wierd_image_type_1000319c);
    }
  }
  return uVar3;
}



undefined4 FUN_0040bee0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0040c0dc(param_1);
  FUN_0040c4ac(param_1,0);
  if ((*(ushort *)(param_1 + 0x70) & 2) != 0) {
    if (*(short *)(param_1 + 0x72) != 0) {
      FUN_0040b5f8(param_1);
    }
    iVar1 = FUN_0040c3fc(param_1,param_1,0x98);
    if (iVar1 != 0x98) {
      FUN_0040b640(s_iflush__error_on_write_of_image_h_100031c0);
      return 0xffffffff;
    }
    if (*(short *)(param_1 + 0x72) != 0) {
      FUN_0040b5f8(param_1);
    }
    if ((*(ushort *)(param_1 + 2) & 0xff00) == 0x100) {
      FUN_0040c4ac(param_1,0x200);
      iVar1 = (uint)*(ushort *)(param_1 + 8) * (uint)*(ushort *)(param_1 + 10) * 4;
      if (*(short *)(param_1 + 0x72) != 0) {
        FUN_0040b594(*(undefined4 *)(param_1 + 0x90),iVar1);
      }
      iVar2 = FUN_0040c3fc(param_1,*(undefined4 *)(param_1 + 0x90),iVar1);
      if (iVar2 != iVar1) {
        FUN_0040b640(s_iflush__error_on_write_of_rowsta_100031e8);
        return 0xffffffff;
      }
      if (*(short *)(param_1 + 0x72) != 0) {
        FUN_0040b594(*(undefined4 *)(param_1 + 0x94),iVar1);
      }
      iVar2 = FUN_0040c3fc(param_1,*(undefined4 *)(param_1 + 0x94),iVar1);
      if (iVar2 != iVar1) {
        FUN_0040b640(s_iflush__error_on_write_of_rowsiz_1000320c);
        return 0xffffffff;
      }
    }
  }
  if (*(int *)(param_1 + 0x80) != 0) {
    func_0x0f801200();
    *(undefined4 *)(param_1 + 0x80) = 0;
  }
  if (*(int *)(param_1 + 0x84) != 0) {
    func_0x0f801200();
    *(undefined4 *)(param_1 + 0x84) = 0;
  }
  if ((*(ushort *)(param_1 + 2) & 0xff00) == 0x100) {
    func_0x0f801200(*(undefined4 *)(param_1 + 0x90));
    *(undefined4 *)(param_1 + 0x90) = 0;
    func_0x0f801200(*(undefined4 *)(param_1 + 0x94));
    *(undefined4 *)(param_1 + 0x94) = 0;
  }
  uVar3 = FUN_0040dfa0(*(undefined4 *)(param_1 + 0x6c));
  return uVar3;
}



void FUN_0040c0dc(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (((*(ushort *)(param_1 + 0x70) & 2) != 0) && (iVar2 = *(int *)(param_1 + 0x80), iVar2 != 0)) {
    iVar3 = *(int *)(param_1 + 0x7c) - iVar2;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 1;
    }
    if (0 < iVar3 >> 1) {
      uVar1 = FUN_0040b6e0(param_1,iVar2,(int)*(short *)(param_1 + 0x76),
                           (int)*(short *)(param_1 + 0x78));
      if (uVar1 != *(ushort *)(param_1 + 6)) {
        *(ushort *)(param_1 + 0x70) = *(ushort *)(param_1 + 0x70) | 0x20;
      }
    }
  }
  return;
}



void FUN_0040c180(int param_1,undefined4 param_2)

{
  func_0x0f801320(param_1 + 0x18,param_2,0x50);
  return;
}



undefined4 FUN_0040c1b0(int param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  iVar2 = FUN_0040c3c0(param_1,param_2);
  if (iVar2 == 0) {
    uVar4 = (uint)*(ushort *)(param_1 + 2);
    *(undefined2 *)(param_1 + 0x74) = 0;
    *(short *)(param_1 + 0x76) = (short)param_2;
    *(short *)(param_1 + 0x78) = (short)param_3;
    if ((*(ushort *)(param_1 + 2) & 0xff00) == 0) {
      sVar1 = *(short *)(param_1 + 4);
      if (sVar1 == 1) {
        uVar3 = FUN_0040c4ac(param_1,0x200);
      }
      else if (sVar1 == 2) {
        uVar3 = FUN_0040c4ac(param_1,param_2 * (uint)*(ushort *)(param_1 + 6) * (uVar4 & 0xff) +
                                     0x200);
      }
      else if (sVar1 == 3) {
        uVar3 = FUN_0040c4ac(param_1,(param_2 * (uint)*(ushort *)(param_1 + 6) +
                                     param_3 * (uint)*(ushort *)(param_1 + 6) *
                                     (uint)*(ushort *)(param_1 + 8)) * (uVar4 & 0xff) + 0x200);
      }
      else {
        uVar3 = FUN_0040b640(s_img_seek__wierd_dim_10003254);
      }
    }
    else if ((uVar4 & 0xff00) == 0x100) {
      sVar1 = *(short *)(param_1 + 4);
      if (sVar1 == 1) {
        uVar3 = FUN_0040c4ac(param_1,**(undefined4 **)(param_1 + 0x90));
      }
      else if (sVar1 == 2) {
        uVar3 = FUN_0040c4ac(param_1,*(undefined4 *)(*(int *)(param_1 + 0x90) + param_2 * 4));
      }
      else if (sVar1 == 3) {
        uVar3 = FUN_0040c4ac(param_1,*(undefined4 *)
                                      (*(int *)(param_1 + 0x90) +
                                      (param_2 + param_3 * (uint)*(ushort *)(param_1 + 8)) * 4));
      }
      else {
        uVar3 = FUN_0040b640(s_img_seek__wierd_dim_1000326c);
      }
    }
    else {
      uVar3 = FUN_0040b640(s_img_seek__wierd_image_type_10003284);
    }
  }
  else {
    FUN_0040b640(s_imglib__row_number_out_of_range_10003230);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



undefined4 FUN_0040c3c0(int param_1,uint param_2,uint param_3)

{
  if ((param_2 < *(ushort *)(param_1 + 8)) && (param_3 < *(ushort *)(param_1 + 10))) {
    return 0;
  }
  return 1;
}



int FUN_0040c3fc(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = FUN_0040dfe0(*(undefined4 *)(param_1 + 0x6c));
  if (iVar1 == param_3) {
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + param_3;
  }
  else {
    *(undefined4 *)(param_1 + 0x88) = 0xffffffff;
  }
  return iVar1;
}



int FUN_0040c454(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = FUN_0040e000(*(undefined4 *)(param_1 + 0x6c));
  if (iVar1 == param_3) {
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + param_3;
  }
  else {
    *(undefined4 *)(param_1 + 0x88) = 0xffffffff;
  }
  return iVar1;
}



int FUN_0040c4ac(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x88)) {
    *(int *)(param_1 + 0x88) = param_2;
    param_2 = FUN_0040e020(*(undefined4 *)(param_1 + 0x6c),param_2,0);
  }
  return param_2;
}



uint FUN_0040c500(int param_1)

{
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)(param_1 + 4);
  if (uVar1 == 1) {
    return **(uint **)(param_1 + 0x94);
  }
  if (uVar1 != 2) {
    if (uVar1 != 3) {
      return uVar1;
    }
    return *(uint *)(*(int *)(param_1 + 0x94) +
                    ((int)*(short *)(param_1 + 0x76) +
                    (int)*(short *)(param_1 + 0x78) * (uint)*(ushort *)(param_1 + 8)) * 4);
  }
  return *(uint *)(*(int *)(param_1 + 0x94) + *(short *)(param_1 + 0x76) * 4);
}



void FUN_0040c590(int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  int iVar2;
  undefined4 local_4;
  
  iVar2 = FUN_0040c3c0(param_1,param_3,param_4);
  if (iVar2 == 0) {
    sVar1 = *(short *)(param_1 + 4);
    if (sVar1 == 1) {
      local_4 = *(int **)(param_1 + 0x94);
      **(undefined4 **)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0x8c);
    }
    else if (sVar1 == 2) {
      local_4 = (int *)(*(int *)(param_1 + 0x94) + param_3 * 4);
      *(undefined4 *)(*(int *)(param_1 + 0x90) + param_3 * 4) = *(undefined4 *)(param_1 + 0x8c);
    }
    else if (sVar1 == 3) {
      iVar2 = (param_3 + param_4 * (uint)*(ushort *)(param_1 + 8)) * 4;
      local_4 = (int *)(*(int *)(param_1 + 0x94) + iVar2);
      *(undefined4 *)(*(int *)(param_1 + 0x90) + iVar2) = *(undefined4 *)(param_1 + 0x8c);
    }
    if (*local_4 != -1) {
      *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + *local_4;
    }
    *local_4 = param_2;
    *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + param_2;
  }
  return;
}



byte * FUN_0040c6a8(ushort *param_1,int param_2,ushort *param_3,int param_4,int param_5)

{
  ushort *puVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  
  if ((param_2 == 1) && (param_4 == 1)) {
    puVar12 = (ushort *)((int)param_1 + param_5);
    puVar9 = param_3;
    if (param_1 < puVar12) {
      do {
        puVar10 = param_1 + 1;
        if ((puVar10 < puVar12) &&
           ((puVar11 = puVar10, *(byte *)((int)param_1 + 1) != *(byte *)param_1 ||
            (*(byte *)puVar10 != *(byte *)((int)param_1 + 1))))) {
          do {
            puVar10 = (ushort *)((int)puVar11 + 1);
            if (puVar12 <= puVar10) break;
            bVar2 = *(byte *)puVar11;
            pbVar7 = (byte *)((int)puVar11 + -1);
            puVar11 = puVar10;
          } while ((bVar2 != *pbVar7) || (*(byte *)puVar10 != bVar2));
        }
        puVar11 = puVar10 + -1;
        iVar6 = (int)puVar11 - (int)param_1;
        while (iVar6 != 0) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          iVar6 = iVar6 - iVar8;
          *(byte *)puVar9 = (byte)iVar8 | 0x80;
          for (; puVar9 = (ushort *)((int)puVar9 + 1), iVar8 != 0;
              iVar8 = (iVar8 + -1) * 0x10000 >> 0x10) {
            bVar2 = *(byte *)param_1;
            param_1 = (ushort *)((int)param_1 + 1);
            *(byte *)puVar9 = bVar2;
          }
        }
        param_1 = (ushort *)((int)puVar10 + -1);
        bVar2 = *(byte *)(puVar10 + -1);
        iVar6 = (int)param_1 - (int)puVar11;
        if (param_1 < puVar12) {
          bVar3 = *(byte *)param_1;
          while ((bVar2 == bVar3 && (param_1 = (ushort *)((int)param_1 + 1), param_1 < puVar12))) {
            bVar3 = *(byte *)param_1;
          }
          iVar6 = (int)param_1 - (int)puVar11;
        }
        for (; iVar6 != 0; iVar6 = iVar6 - iVar8) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          *(byte *)puVar9 = (byte)iVar8;
          *(byte *)((int)puVar9 + 1) = bVar2;
          puVar9 = puVar9 + 1;
        }
      } while (param_1 < puVar12);
    }
    *(byte *)puVar9 = 0;
    pbVar7 = (byte *)((int)puVar9 + (1 - (int)param_3));
  }
  else if ((param_2 == 1) && (param_4 == 2)) {
    puVar12 = (ushort *)((int)param_1 + param_5);
    puVar9 = param_3;
    if (param_1 < puVar12) {
      do {
        puVar10 = param_1 + 1;
        if ((puVar10 < puVar12) &&
           ((puVar11 = puVar10, *(byte *)((int)param_1 + 1) != *(byte *)param_1 ||
            (*(byte *)puVar10 != *(byte *)((int)param_1 + 1))))) {
          do {
            puVar10 = (ushort *)((int)puVar11 + 1);
            if (puVar12 <= puVar10) break;
            bVar2 = *(byte *)puVar11;
            pbVar7 = (byte *)((int)puVar11 + -1);
            puVar11 = puVar10;
          } while ((bVar2 != *pbVar7) || (*(byte *)puVar10 != bVar2));
        }
        puVar11 = puVar10 + -1;
        iVar6 = (int)puVar11 - (int)param_1;
        while (iVar6 != 0) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          iVar6 = iVar6 - iVar8;
          *puVar9 = (ushort)iVar8 | 0x80;
          for (; puVar9 = puVar9 + 1, iVar8 != 0; iVar8 = (iVar8 + -1) * 0x10000 >> 0x10) {
            bVar2 = *(byte *)param_1;
            param_1 = (ushort *)((int)param_1 + 1);
            *puVar9 = (ushort)bVar2;
          }
        }
        param_1 = (ushort *)((int)puVar10 + -1);
        bVar2 = *(byte *)(puVar10 + -1);
        iVar6 = (int)param_1 - (int)puVar11;
        if (param_1 < puVar12) {
          bVar3 = *(byte *)param_1;
          while ((bVar2 == bVar3 && (param_1 = (ushort *)((int)param_1 + 1), param_1 < puVar12))) {
            bVar3 = *(byte *)param_1;
          }
          iVar6 = (int)param_1 - (int)puVar11;
        }
        for (; iVar6 != 0; iVar6 = iVar6 - iVar8) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          *puVar9 = (ushort)iVar8;
          puVar9[1] = (ushort)bVar2;
          puVar9 = puVar9 + 2;
        }
      } while (param_1 < puVar12);
    }
    pbVar7 = (byte *)((int)puVar9 + (2 - (int)param_3));
    if ((int)pbVar7 < 0) {
      pbVar7 = pbVar7 + 1;
    }
    pbVar7 = (byte *)((int)pbVar7 >> 1);
    *puVar9 = 0;
  }
  else if ((param_2 == 2) && (param_4 == 1)) {
    puVar12 = param_1 + param_5;
    puVar9 = param_3;
    if (param_1 < puVar12) {
      do {
        puVar10 = param_1 + 2;
        if ((puVar10 < puVar12) &&
           ((puVar11 = puVar10, param_1[1] != *param_1 || (*puVar10 != param_1[1])))) {
          do {
            puVar10 = puVar11 + 1;
            if (puVar12 <= puVar10) break;
            uVar4 = *puVar11;
            puVar1 = puVar11 + -1;
            puVar11 = puVar10;
          } while ((uVar4 != *puVar1) || (*puVar10 != uVar4));
        }
        puVar11 = puVar10 + -2;
        iVar6 = (int)puVar11 - (int)param_1;
        if (iVar6 < 0) {
          iVar6 = iVar6 + 1;
        }
        iVar6 = iVar6 >> 1;
        while (iVar6 != 0) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          iVar6 = iVar6 - iVar8;
          *(byte *)puVar9 = (byte)iVar8 | 0x80;
          for (; puVar9 = (ushort *)((int)puVar9 + 1), iVar8 != 0;
              iVar8 = (iVar8 + -1) * 0x10000 >> 0x10) {
            uVar4 = *param_1;
            param_1 = param_1 + 1;
            *(byte *)puVar9 = (byte)uVar4;
          }
        }
        param_1 = puVar10 + -1;
        uVar4 = puVar10[-2];
        iVar6 = (int)param_1 - (int)puVar11;
        if (param_1 < puVar12) {
          uVar5 = *param_1;
          while (((int)(short)uVar4 == (uint)uVar5 && (param_1 = param_1 + 1, param_1 < puVar12))) {
            uVar5 = *param_1;
          }
          iVar6 = (int)param_1 - (int)puVar11;
        }
        if (iVar6 < 0) {
          iVar6 = iVar6 + 1;
        }
        for (iVar6 = iVar6 >> 1; iVar6 != 0; iVar6 = iVar6 - iVar8) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          *(byte *)puVar9 = (byte)iVar8;
          *(byte *)((int)puVar9 + 1) = (byte)uVar4;
          puVar9 = puVar9 + 1;
        }
      } while (param_1 < puVar12);
    }
    *(byte *)puVar9 = 0;
    pbVar7 = (byte *)((int)puVar9 + (1 - (int)param_3));
  }
  else if ((param_2 == 2) && (param_4 == 2)) {
    puVar12 = param_1 + param_5;
    puVar9 = param_3;
    if (param_1 < puVar12) {
      do {
        puVar10 = param_1 + 2;
        if ((puVar10 < puVar12) &&
           ((puVar11 = puVar10, param_1[1] != *param_1 || (*puVar10 != param_1[1])))) {
          do {
            puVar10 = puVar11 + 1;
            if (puVar12 <= puVar10) break;
            uVar4 = *puVar11;
            puVar1 = puVar11 + -1;
            puVar11 = puVar10;
          } while ((uVar4 != *puVar1) || (*puVar10 != uVar4));
        }
        puVar11 = puVar10 + -2;
        iVar6 = (int)puVar11 - (int)param_1;
        if (iVar6 < 0) {
          iVar6 = iVar6 + 1;
        }
        iVar6 = iVar6 >> 1;
        while (iVar6 != 0) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          iVar6 = iVar6 - iVar8;
          *puVar9 = (ushort)iVar8 | 0x80;
          for (; puVar9 = puVar9 + 1, iVar8 != 0; iVar8 = (iVar8 + -1) * 0x10000 >> 0x10) {
            uVar4 = *param_1;
            param_1 = param_1 + 1;
            *puVar9 = uVar4;
          }
        }
        param_1 = puVar10 + -1;
        uVar4 = puVar10[-2];
        iVar6 = (int)param_1 - (int)puVar11;
        if (param_1 < puVar12) {
          uVar5 = *param_1;
          while (((int)(short)uVar4 == (uint)uVar5 && (param_1 = param_1 + 1, param_1 < puVar12))) {
            uVar5 = *param_1;
          }
          iVar6 = (int)param_1 - (int)puVar11;
        }
        if (iVar6 < 0) {
          iVar6 = iVar6 + 1;
        }
        for (iVar6 = iVar6 >> 1; iVar6 != 0; iVar6 = iVar6 - iVar8) {
          if (iVar6 < 0x7f) {
            iVar8 = (int)(short)iVar6;
          }
          else {
            iVar8 = 0x7e;
          }
          *puVar9 = (ushort)iVar8;
          puVar9[1] = uVar4;
          puVar9 = puVar9 + 2;
        }
      } while (param_1 < puVar12);
    }
    pbVar7 = (byte *)((int)puVar9 + (2 - (int)param_3));
    if ((int)pbVar7 < 0) {
      pbVar7 = pbVar7 + 1;
    }
    pbVar7 = (byte *)((int)pbVar7 >> 1);
    *puVar9 = 0;
  }
  else {
    FUN_0040b640(s_rle_compact__bad_bpp___d__d_100032a0,param_2,param_4);
    pbVar7 = (byte *)0x0;
  }
  return pbVar7;
}



void FUN_0040ce2c(ushort *param_1,int param_2,ushort *param_3,int param_4)

{
  byte bVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort uVar4;
  ushort *puVar5;
  
  if ((param_2 != 1) || (param_4 != 1)) {
    if ((param_2 == 1) && (param_4 == 2)) {
LAB_0040cf0c:
      do {
        uVar4 = (ushort)*(byte *)param_1;
        while( true ) {
          while( true ) {
            puVar5 = (ushort *)((int)param_1 + 1);
            uVar2 = uVar4 & 0x7f;
            if (uVar2 == 0) {
              return;
            }
            if ((uVar4 & 0x80) != 0) break;
            bVar1 = *(byte *)puVar5;
            param_1 = param_1 + 1;
            if (uVar2 == 0) goto LAB_0040cf0c;
            do {
              uVar2 = uVar2 - 1;
              *param_3 = (ushort)bVar1;
              param_3 = param_3 + 1;
            } while (uVar2 != 0);
            uVar4 = (ushort)*(byte *)param_1;
          }
          puVar3 = param_3;
          param_1 = puVar5;
          if (uVar2 == 0) break;
          do {
            uVar2 = uVar2 - 1;
            bVar1 = *(byte *)puVar5;
            puVar5 = (ushort *)((int)puVar5 + 1);
            param_3 = puVar3 + 1;
            *puVar3 = (ushort)bVar1;
            puVar3 = param_3;
          } while (uVar2 != 0);
          uVar4 = (ushort)*(byte *)puVar5;
          param_1 = puVar5;
        }
      } while( true );
    }
    if ((param_2 == 2) && (param_4 == 1)) {
LAB_0040cfb8:
      do {
        uVar4 = *param_1;
        while( true ) {
          while( true ) {
            puVar5 = param_1 + 1;
            uVar2 = uVar4 & 0x7f;
            if (uVar2 == 0) {
              return;
            }
            if ((uVar4 & 0x80) != 0) break;
            uVar4 = *puVar5;
            param_1 = param_1 + 2;
            if (uVar2 == 0) goto LAB_0040cfb8;
            do {
              uVar2 = uVar2 - 1;
              *(byte *)param_3 = (byte)uVar4;
              param_3 = (ushort *)((int)param_3 + 1);
            } while (uVar2 != 0);
            uVar4 = *param_1;
          }
          puVar3 = param_3;
          param_1 = puVar5;
          if (uVar2 == 0) break;
          do {
            uVar2 = uVar2 - 1;
            uVar4 = *puVar5;
            puVar5 = puVar5 + 1;
            param_3 = (ushort *)((int)puVar3 + 1);
            *(byte *)puVar3 = (byte)uVar4;
            puVar3 = param_3;
          } while (uVar2 != 0);
          uVar4 = *puVar5;
          param_1 = puVar5;
        }
      } while( true );
    }
    if ((param_2 != 2) || (param_4 != 2)) {
      FUN_0040b640(s_rle_expand__bad_bpp___d__d_100032c0,param_2,param_4);
      return;
    }
LAB_0040d064:
    do {
      uVar4 = *param_1;
      while( true ) {
        while( true ) {
          puVar5 = param_1 + 1;
          uVar2 = uVar4 & 0x7f;
          if (uVar2 == 0) {
            return;
          }
          if ((uVar4 & 0x80) != 0) break;
          uVar4 = *puVar5;
          param_1 = param_1 + 2;
          if (uVar2 == 0) goto LAB_0040d064;
          do {
            uVar2 = uVar2 - 1;
            *param_3 = uVar4;
            param_3 = param_3 + 1;
          } while (uVar2 != 0);
          uVar4 = *param_1;
        }
        puVar3 = param_3;
        param_1 = puVar5;
        if (uVar2 == 0) break;
        do {
          uVar2 = uVar2 - 1;
          uVar4 = *puVar5;
          puVar5 = puVar5 + 1;
          param_3 = puVar3 + 1;
          *puVar3 = uVar4;
          puVar3 = param_3;
        } while (uVar2 != 0);
        uVar4 = *puVar5;
        param_1 = puVar5;
      }
    } while( true );
  }
LAB_0040ce54:
  do {
    uVar4 = (ushort)*(byte *)param_1;
    while( true ) {
      while( true ) {
        puVar5 = (ushort *)((int)param_1 + 1);
        uVar2 = uVar4 & 0x7f;
        if (uVar2 == 0) {
          return;
        }
        if ((uVar4 & 0x80) != 0) break;
        bVar1 = *(byte *)puVar5;
        param_1 = param_1 + 1;
        if (uVar2 == 0) goto LAB_0040ce54;
        do {
          uVar2 = uVar2 - 1;
          *(byte *)param_3 = bVar1;
          param_3 = (ushort *)((int)param_3 + 1);
        } while (uVar2 != 0);
        uVar4 = (ushort)*(byte *)param_1;
      }
      puVar3 = param_3;
      param_1 = puVar5;
      if (uVar2 == 0) break;
      do {
        uVar2 = uVar2 - 1;
        bVar1 = *(byte *)puVar5;
        puVar5 = (ushort *)((int)puVar5 + 1);
        param_3 = (ushort *)((int)puVar3 + 1);
        *(byte *)puVar3 = bVar1;
        puVar3 = param_3;
      } while (uVar2 != 0);
      uVar4 = (ushort)*(byte *)puVar5;
      param_1 = puVar5;
    }
  } while( true );
}



/* WARNING: Removing unreachable block (ram,0x0040d164) */

double FUN_0040d120(double param_1)

{
  int unaff_gp;
  double dVar1;
  double dVar2;
  uint uVar3;
  
  param_1 = ABS(param_1);
  if (param_1 < *(double *)(unaff_gp + -0x7f58)) {
    uVar3 = (uint)ROUND(param_1 * *(double *)(unaff_gp + -0x7f50) + *(double *)(unaff_gp + -0x7fe0))
    ;
    dVar1 = (double)(int)uVar3 - *(double *)(unaff_gp + -0x7fe0);
    dVar1 = (param_1 - dVar1 * *(double *)(unaff_gp + -0x7f40)) -
            dVar1 * *(double *)(unaff_gp + -0x7f38);
    if ((uVar3 & 1) != 0) {
      dVar1 = -dVar1;
    }
    dVar2 = dVar1 * dVar1;
    return dVar1 + (((((((dVar2 * *(double *)(unaff_gp + -0x7f30) + *(double *)(unaff_gp + -0x7f28))
                         * dVar2 + *(double *)(unaff_gp + -0x7f20)) * dVar2 +
                       *(double *)(unaff_gp + -0x7f18)) * dVar2 + *(double *)(unaff_gp + -0x7f10)) *
                      dVar2 + *(double *)(unaff_gp + -0x7f08)) * dVar2 +
                    *(double *)(unaff_gp + -0x7f00)) * dVar2 + *(double *)(unaff_gp + -0x7ef8)) *
                   dVar2 * dVar1;
  }
  if (!NAN(param_1)) {
    return NAN;
  }
  return param_1;
}



/* WARNING: Removing unreachable block (ram,0x0040d1c4) */

double FUN_0040d178(double param_1)

{
  int unaff_gp;
  uint uVar2;
  double dVar1;
  
  if (*(double *)(unaff_gp + -0x7f48) <= ABS(param_1)) {
    if (*(double *)(unaff_gp + -0x7f58) <= ABS(param_1)) {
      if (NAN(param_1)) {
        return param_1;
      }
      return NAN;
    }
    uVar2 = (uint)ROUND(param_1 * *(double *)(unaff_gp + -0x7f50));
    dVar1 = (double)(int)uVar2;
    param_1 = (param_1 - dVar1 * *(double *)(unaff_gp + -0x7f40)) -
              dVar1 * *(double *)(unaff_gp + -0x7f38);
    if ((uVar2 & 1) != 0) {
      param_1 = -param_1;
    }
  }
  dVar1 = param_1 * param_1;
  return param_1 + (((((((dVar1 * *(double *)(unaff_gp + -0x7f30) + *(double *)(unaff_gp + -0x7f28))
                         * dVar1 + *(double *)(unaff_gp + -0x7f20)) * dVar1 +
                       *(double *)(unaff_gp + -0x7f18)) * dVar1 + *(double *)(unaff_gp + -0x7f10)) *
                      dVar1 + *(double *)(unaff_gp + -0x7f08)) * dVar1 +
                    *(double *)(unaff_gp + -0x7f00)) * dVar1 + *(double *)(unaff_gp + -0x7ef8)) *
                   dVar1 * param_1;
}



void FUN_0040d2c0(void)

{
  return;
}



undefined4 FUN_0040d2d0(char *param_1)

{
  int iVar1;
  int iVar2;
  int unaff_gp;
  undefined4 local_28c;
  undefined auStack_284 [516];
  undefined auStack_80 [14];
  undefined auStack_72 [114];
  
  local_28c = 0xffffffff;
  if ((param_1 == (char *)0x0) &&
     ((param_1 = (char *)func_0x0f8011b0(s_CHRCLASS_100034e4), param_1 == (char *)0x0 ||
      (*param_1 == '\0')))) {
    if (*(char *)(unaff_gp + -0x7bf0) != '\0') {
      return 0;
    }
    param_1 = (char *)(unaff_gp + -0x7bec);
  }
  *(undefined *)(unaff_gp + -0x7bf0) = 0;
  func_0x0f8012f0(auStack_80,s__lib_chrclass__100034f0);
  func_0x0f8012f0(auStack_72,param_1);
  iVar1 = FUN_0040dfc0(auStack_80,0);
  if (-1 < iVar1) {
    iVar2 = FUN_0040e000(iVar1,auStack_284,0x202);
    if (iVar2 == 0x202) {
      func_0x0f801230(&DAT_100032e0,auStack_284,0x202);
      local_28c = 0;
    }
    FUN_0040dfa0(iVar1);
  }
  return local_28c;
}



void FUN_0040d3c0(undefined4 param_1)

{
  func_0x0f8010f8();
  FUN_0040e5c0(param_1);
  return;
}



uint FUN_0040d3f0(int param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int unaff_gp;
  undefined local_18;
  undefined local_17;
  undefined local_10;
  undefined local_f;
  uint local_4;
  
  iVar4 = *(int *)(unaff_gp + -0x7bb0);
  if (iVar4 == 1) {
    if (((param_1 <= *(int *)(unaff_gp + -0x7bbc)) ||
        (pcVar2 = (char *)param_2[*(int *)(unaff_gp + -0x7bbc)], *pcVar2 != '-')) ||
       (pcVar2[1] == '\0')) {
      return 0xffffffff;
    }
    iVar4 = func_0x0f8012e8(pcVar2,unaff_gp + -0x7bac);
    if (iVar4 == 0) {
      *(int *)(unaff_gp + -0x7bbc) = *(int *)(unaff_gp + -0x7bbc) + 1;
      return 0xffffffff;
    }
    iVar4 = *(int *)(unaff_gp + -0x7bb0);
  }
  uVar3 = (uint)*(byte *)(param_2[*(int *)(unaff_gp + -0x7bbc)] + iVar4);
  *(uint *)(unaff_gp + -0x7bb8) = uVar3;
  if (uVar3 != 0x3a) {
    local_4 = uVar3;
    iVar4 = func_0x0f8012e0(param_3);
    if (iVar4 != 0) {
      if (*(char *)(iVar4 + 1) != ':') {
        iVar4 = *(int *)(unaff_gp + -0x7bb0) + 1;
        if (*(char *)(param_2[*(int *)(unaff_gp + -0x7bbc)] + iVar4) == '\0') {
          *(int *)(unaff_gp + -0x7bbc) = *(int *)(unaff_gp + -0x7bbc) + 1;
          *(undefined4 *)(unaff_gp + -0x7bb0) = 1;
        }
        else {
          *(int *)(unaff_gp + -0x7bb0) = iVar4;
        }
        *(undefined4 *)(unaff_gp + -0x7bb4) = 0;
        return local_4;
      }
      iVar5 = *(int *)(unaff_gp + -0x7bbc);
      iVar4 = param_2[iVar5] + *(int *)(unaff_gp + -0x7bb0);
      if (*(char *)(iVar4 + 1) == '\0') {
        iVar4 = *(int *)(unaff_gp + -0x7bbc) + 1;
        *(int *)(unaff_gp + -0x7bbc) = iVar4;
        if (param_1 <= iVar4) {
          if (*(int *)(unaff_gp + -0x7bc0) != 0) {
            local_17 = 10;
            local_18 = (undefined)local_4;
            uVar1 = func_0x0f801308(*param_2);
            FUN_0040dfe0(2,*param_2,uVar1);
            uVar1 = func_0x0f801308(s___option_requires_an_argument____10003ce0);
            FUN_0040dfe0(2,s___option_requires_an_argument____10003ce0,uVar1);
            FUN_0040dfe0(2,&local_18,2);
          }
          *(undefined4 *)(unaff_gp + -0x7bb0) = 1;
          return 0x3f;
        }
        iVar4 = (param_2 + iVar5)[1];
        *(int *)(unaff_gp + -0x7bbc) = *(int *)(unaff_gp + -0x7bbc) + 1;
        *(int *)(unaff_gp + -0x7bb4) = iVar4;
      }
      else {
        *(int *)(unaff_gp + -0x7bbc) = iVar5 + 1;
        *(int *)(unaff_gp + -0x7bb4) = iVar4 + 1;
      }
      *(undefined4 *)(unaff_gp + -0x7bb0) = 1;
      return local_4;
    }
    iVar4 = *(int *)(unaff_gp + -0x7bb0);
    uVar3 = local_4;
  }
  if (*(int *)(unaff_gp + -0x7bc0) != 0) {
    local_f = 10;
    local_10 = (undefined)uVar3;
    uVar1 = func_0x0f801308(*param_2);
    FUN_0040dfe0(2,*param_2,uVar1);
    uVar1 = func_0x0f801308(s___illegal_option____10003d04);
    FUN_0040dfe0(2,s___illegal_option____10003d04,uVar1);
    FUN_0040dfe0(2,&local_10,2);
    iVar4 = *(int *)(unaff_gp + -0x7bb0);
  }
  if (*(char *)(param_2[*(int *)(unaff_gp + -0x7bbc)] + iVar4 + 1) == '\0') {
    *(int *)(unaff_gp + -0x7bbc) = *(int *)(unaff_gp + -0x7bbc) + 1;
    *(undefined4 *)(unaff_gp + -0x7bb0) = 1;
  }
  else {
    *(int *)(unaff_gp + -0x7bb0) = iVar4 + 1;
  }
  return 0x3f;
}



void FUN_0040d720(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_res4;
  undefined4 local_res8;
  undefined4 local_resc;
  
  local_res4 = param_2;
  local_res8 = param_3;
  local_resc = param_4;
  FUN_0040e5d0(&DAT_10003694,param_1,&local_res4);
  return;
}



void FUN_0040d768(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_res8;
  undefined4 local_resc;
  
  local_res8 = param_3;
  local_resc = param_4;
  FUN_0040e5d0(param_1,param_2,&local_res8);
  return;
}



void FUN_0040d7a4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_res8;
  undefined4 local_resc;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined local_8;
  undefined local_7;
  
  local_8 = 1;
  local_res8 = param_3;
  local_resc = param_4;
  local_10 = param_1;
  local_c = param_1;
  local_14 = func_0x0f801308();
  local_7 = 100;
  FUN_0040e5d0(&local_14,param_2,&local_res8);
  return;
}



undefined4 FUN_0040d810(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0x413;
}



double FUN_0040d830(byte *param_1,undefined4 *param_2)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  double *pdVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined1 *puVar11;
  int unaff_gp;
  double dVar12;
  double dVar13;
  undefined4 *local_res4;
  undefined4 local_1c;
  int local_18;
  int local_c;
  
  local_c = 0;
  uVar8 = 0;
  local_18 = 0;
  local_res4 = param_2;
  if (param_2 == (undefined4 *)0x0) {
    local_res4 = &local_1c;
  }
  *local_res4 = param_1;
  uVar9 = (uint)*param_1;
  bVar2 = (&DAT_100032e1)[uVar9];
  while ((bVar2 & 8) != 0) {
    uVar9 = (uint)param_1[1];
    param_1 = param_1 + 1;
    bVar2 = (&DAT_100032e1)[uVar9];
  }
  if (uVar9 == 0x2b) {
LAB_0040d8b8:
    uVar9 = (uint)param_1[1];
    param_1 = param_1 + 1;
  }
  else if (uVar9 == 0x2d) {
    local_c = 1;
    goto LAB_0040d8b8;
  }
  puVar11 = &DAT_100032e0 + uVar9;
  iVar4 = 0;
  iVar7 = 0;
  iVar6 = 1;
  iVar10 = 0;
  iVar3 = 0;
  param_1 = param_1 + 1;
  if (((&DAT_100032e1)[uVar9] & 4) == 0) {
    if (uVar9 == 0x2e) {
      iVar10 = 1;
      goto LAB_0040d920;
    }
  }
  else {
LAB_0040d920:
    param_2 = (undefined4 *)0xccccccc;
    do {
      do {
        if (uVar9 != 0x2e) {
          local_18 = local_18 + 1;
          if (iVar10 != 0) {
            if (uVar9 == 0x30) {
              iVar3 = iVar3 + 1;
              goto LAB_0040da18;
            }
            for (; 0 < iVar3; iVar3 = iVar3 + -1) {
              if (iVar4 < 0xccccccc) {
                iVar4 = iVar4 * 10;
                uVar8 = uVar8 - 1;
              }
              else if (iVar6 < 0xccccccc) {
                iVar6 = iVar6 * 10;
                iVar7 = iVar7 * 10;
                uVar8 = uVar8 - 1;
              }
            }
            uVar8 = uVar8 - 1;
          }
          if (iVar4 < 0xccccccc) {
            iVar4 = iVar4 * 10 + uVar9 + -0x30;
          }
          else if (iVar6 < 0xccccccc) {
            iVar6 = iVar6 * 10;
            iVar7 = iVar7 * 10 + uVar9 + -0x30;
          }
          else {
            uVar8 = uVar8 + 1;
          }
        }
LAB_0040da18:
        uVar9 = (uint)*param_1;
        param_1 = param_1 + 1;
        puVar11 = &DAT_100032e0 + uVar9;
      } while (((&DAT_100032e1)[uVar9] & 4) != 0);
      if (uVar9 != 0x2e) goto code_r0x0040da54;
      bVar1 = iVar10 == 0;
      iVar10 = iVar10 + 1;
    } while (bVar1);
    param_2 = (undefined4 *)0xccccccc;
  }
code_r0x0040da54:
  if (local_18 == 0) {
    return 0.0;
  }
  dVar12 = (double)iVar4;
  if (1 < iVar6) {
    dVar12 = (double)iVar6 * dVar12 + (double)iVar7;
  }
  *local_res4 = param_1 + -1;
  if ((puVar11 != (undefined1 *)0x10003325) && (puVar11 != (undefined1 *)0x10003345))
  goto LAB_0040db80;
  iVar3 = 0;
  *local_res4 = param_1;
  uVar9 = (uint)*param_1;
  iVar6 = 0;
  if ((uVar9 == 0x20) || (uVar9 == 0x2b)) {
LAB_0040dae0:
    uVar9 = (uint)param_1[1];
    param_1 = param_1 + 1;
  }
  else if (uVar9 == 0x2d) {
    iVar6 = 1;
    goto LAB_0040dae0;
  }
  bVar1 = true;
  if (((&DAT_100032e1)[uVar9] & 4) != 0) {
    do {
      if (bVar1) {
        iVar3 = iVar3 * 10 + uVar9 + -0x30;
      }
      uVar9 = (uint)param_1[1];
      param_1 = param_1 + 1;
      bVar1 = iVar3 < 0x400;
    } while (((&DAT_100032e1)[uVar9] & 4) != 0);
    if (iVar6 != 0) {
      iVar3 = -iVar3;
    }
    uVar8 = uVar8 + iVar3;
    *local_res4 = param_1;
  }
LAB_0040db80:
  if (dVar12 != 0.0) {
    if (uVar8 != 0) {
      pdVar5 = (double *)&DAT_10003d20;
      if ((double)CONCAT44(DAT_10003d20,DAT_10003d24) == 0.0) {
        DAT_10003d20 = *(undefined4 *)(unaff_gp + -0x7ef0);
        DAT_10003d24 = *(undefined4 *)(unaff_gp + -0x7eec);
        do {
          dVar13 = *pdVar5;
          pdVar5 = pdVar5 + 1;
          *pdVar5 = dVar13 * dVar13;
        } while (pdVar5 < (double *)0x10003d60);
      }
      pdVar5 = (double *)&DAT_10003d20;
      uVar9 = uVar8;
      dVar13 = dVar12;
      if ((int)uVar8 < 0) {
        dVar13 = *(double *)(unaff_gp + -0x7f78);
        uVar9 = -uVar8;
      }
      if (0x200 < (int)uVar9) {
        uVar9 = 0x200;
      }
      while( true ) {
        if ((uVar9 & 1) != 0) {
          dVar13 = dVar13 * *pdVar5;
        }
        uVar9 = (int)uVar9 >> 1;
        if (uVar9 == 0) break;
        pdVar5 = pdVar5 + 1;
      }
      if ((int)uVar8 < 0) {
        dVar13 = dVar12 / dVar13;
      }
      dVar12 = (double)func_0x0f8011e0(dVar13,iVar6,param_2,uVar8 * 3);
    }
    if (local_c != 0) {
      dVar12 = -dVar12;
    }
  }
  return dVar12;
}



int FUN_0040dcc0(byte *param_1,undefined4 *param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  
  bVar1 = false;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_1;
  }
  if ((param_3 < 0) || (0x24 < param_3)) {
    return 0;
  }
  uVar2 = (uint)*param_1;
  bVar3 = (&DAT_100032e1)[uVar2];
  bVar4 = bVar3 & 7;
  if ((bVar3 & 7) == 0) {
    while ((bVar3 & 8) != 0) {
      uVar2 = (uint)param_1[1];
      param_1 = param_1 + 1;
      bVar3 = (&DAT_100032e1)[uVar2];
    }
    if (uVar2 != 0x2b) {
      if (uVar2 != 0x2d) {
        bVar4 = bVar3 & 7;
        goto LAB_0040dd70;
      }
      bVar1 = true;
    }
    uVar2 = (uint)param_1[1];
    param_1 = param_1 + 1;
    bVar3 = (&DAT_100032e1)[uVar2];
    bVar4 = bVar3 & 7;
  }
LAB_0040dd70:
  if (param_3 == 0) {
    if (uVar2 == 0x30) {
      if ((param_1[1] == 0x78) || (param_3 = 8, param_1[1] == 0x58)) {
        param_3 = 0x10;
      }
    }
    else {
      param_3 = 10;
    }
  }
  if (bVar4 != 0) {
    bVar4 = bVar3 & 4;
    if (bVar4 == 0) {
      iVar5 = uVar2 - 0x37;
      if ((bVar3 & 2) != 0) {
        iVar5 = uVar2 - 0x57;
      }
    }
    else {
      iVar5 = uVar2 - 0x30;
    }
    if (iVar5 < param_3) {
      if ((((param_3 == 0x10) && (uVar2 == 0x30)) && (((&DAT_100032e1)[param_1[2]] & 0x80) != 0)) &&
         ((param_1[1] == 0x78 || (param_1[1] == 0x58)))) {
        uVar2 = (uint)param_1[2];
        param_1 = param_1 + 2;
        bVar3 = (&DAT_100032e1)[uVar2];
        bVar4 = bVar3 & 4;
      }
      if (bVar4 == 0) {
        iVar5 = uVar2 - 0x37;
        if ((bVar3 & 2) != 0) {
          iVar5 = uVar2 - 0x57;
        }
      }
      else {
        iVar5 = uVar2 - 0x30;
      }
      uVar2 = (uint)param_1[1];
      iVar5 = -iVar5;
      bVar3 = (&DAT_100032e1)[uVar2];
      param_1 = param_1 + 1;
      if ((bVar3 & 7) != 0) {
        if ((bVar3 & 4) == 0) {
          iVar6 = uVar2 - 0x37;
          if ((bVar3 & 2) != 0) {
            iVar6 = uVar2 - 0x57;
          }
        }
        else {
          iVar6 = uVar2 - 0x30;
        }
        while (iVar6 < param_3) {
          uVar2 = (uint)param_1[1];
          param_1 = param_1 + 1;
          bVar3 = (&DAT_100032e1)[uVar2];
          iVar5 = param_3 * iVar5 - iVar6;
          if ((bVar3 & 7) == 0) break;
          if ((bVar3 & 4) == 0) {
            iVar6 = uVar2 - 0x37;
            if ((bVar3 & 2) != 0) {
              iVar6 = uVar2 - 0x57;
            }
          }
          else {
            iVar6 = uVar2 - 0x30;
          }
        }
      }
      if (param_2 != (undefined4 *)0x0) {
        *param_2 = param_1;
      }
      iVar6 = -iVar5;
      if (bVar1) {
        iVar6 = iVar5;
      }
      return iVar6;
    }
  }
  return 0;
}



undefined4 FUN_0040df80(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0x3f0;
}



undefined4 FUN_0040dfa0(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0;
}



undefined4 FUN_0040dfc0(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0x3ed;
}



undefined4 FUN_0040dfe0(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0x3ec;
}



undefined4 FUN_0040e000(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0x3eb;
}



undefined4 FUN_0040e020(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0x3fb;
}



void FUN_0040e040(void)

{
  int iVar1;
  undefined4 uVar2;
  int unaff_gp;
  
  iVar1 = FUN_0040e2b0(6,0);
  if (iVar1 == 0) {
    iVar1 = *(int *)(unaff_gp + -0x7ba0) + 1;
    *(int *)(unaff_gp + -0x7ba0) = iVar1;
    if (iVar1 == 1) {
      func_0x0f8010f8();
    }
  }
  else {
    FUN_0040e2b0(6);
  }
  uVar2 = FUN_0040e270();
  FUN_0040fa10(uVar2,6);
  return;
}



undefined4 * FUN_0040e110(undefined4 param_1,char *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)func_0x0f8010e8();
  if (puVar2 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  *(char *)((int)puVar2 + 0xd) = (char)param_1;
  *puVar2 = 0;
  *(undefined *)(puVar2 + 3) = 0;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *(undefined4 *)(&DAT_10003500 + (uint)*(byte *)((int)puVar2 + 0xd) * 4) = 0;
  cVar1 = *param_2;
  if (cVar1 == 'a') {
    FUN_0040e020(param_1,0,2);
  }
  else {
    if (cVar1 == 'r') {
      *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 1;
      goto LAB_0040e1d4;
    }
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
  }
  *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 2;
LAB_0040e1d4:
  if (param_2[1] == '+') {
    *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) & 0xfc;
    *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 0x80;
  }
  return puVar2;
}



undefined4 FUN_0040e270(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0x3fc;
}



undefined4 FUN_0040e2b0(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  
  if ((0 < param_1) && (param_1 < 0x21)) {
    syscall(0);
    if (param_4 != 0) {
      uVar1 = FUN_0040fa00(param_1,param_2,FUN_0040fa30);
      return uVar1;
    }
    return 0x418;
  }
  uVar1 = FUN_0040fa00();
  return uVar1;
}



void FUN_0040e410(undefined4 param_1,undefined4 param_2)

{
  FUN_0040faa0(0x46d,param_1,param_2);
  return;
}



void FUN_0040e460(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0040faa0(0x41c,0,param_1,param_2,param_3);
  return;
}



void FUN_0040e498(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0040faa0(0x41c,1,param_1,param_2,param_3);
  return;
}



void FUN_0040e4f4(undefined4 param_1)

{
  FUN_0040faa0(0x41c,2,param_1);
  return;
}



void FUN_0040e51c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0040faa0(0x41c,3,param_1,param_2,param_3);
  return;
}



void FUN_0040e580(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0040faa0(0x46c,param_1,param_2,param_3);
  return;
}



undefined4 FUN_0040e5c0(void)

{
  syscall(0);
  return 0x3e9;
}



int FUN_0040e5d0(int *param_1,byte *param_2,uint param_3,undefined4 param_4)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  int unaff_gp;
  uint local_res8;
  undefined4 local_resc;
  int local_108;
  undefined auStack_100 [256];
  
  *(undefined4 *)(unaff_gp + -0x7aa0) = 0;
  *(undefined4 *)(unaff_gp + -0x7a9c) = 0;
  local_108 = 0;
  local_res8 = param_3;
  local_resc = param_4;
LAB_0040e620:
  do {
    while( true ) {
      uVar7 = (uint)*param_2;
      pbVar9 = param_2 + 1;
      if (uVar7 == 0) {
        return local_108;
      }
      if (((&DAT_100032e1)[uVar7] & 8) == 0) break;
      param_2 = pbVar9;
      if (*(int *)(unaff_gp + -0x7a9c) == 0) {
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
        if ((*(char *)((int)param_1 + 0xd) == 'd') && (*param_1 == 0)) {
          uVar7 = 0xffffffff;
        }
        else {
          iVar3 = *param_1 + -1;
          *param_1 = iVar3;
          if (iVar3 < 0) {
            uVar7 = func_0x0f8010e0(param_1);
          }
          else {
            uVar7 = (uint)*(byte *)param_1[1];
            param_1[1] = (int)((byte *)param_1[1] + 1);
          }
        }
        bVar2 = (&DAT_100032e1)[uVar7];
        while ((bVar2 & 8) != 0) {
          *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
          if ((*(char *)((int)param_1 + 0xd) == 'd') && (*param_1 == 0)) {
            uVar7 = 0xffffffff;
          }
          else {
            iVar3 = *param_1 + -1;
            *param_1 = iVar3;
            if (iVar3 < 0) {
              uVar7 = func_0x0f8010e0(param_1);
            }
            else {
              uVar7 = (uint)*(byte *)param_1[1];
              param_1[1] = (int)((byte *)param_1[1] + 1);
            }
          }
          bVar2 = (&DAT_100032e1)[uVar7];
        }
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
        iVar3 = func_0x0f801378(uVar7,param_1);
        if (iVar3 == -1) {
          *(undefined4 *)(unaff_gp + -0x7a9c) = 1;
        }
      }
    }
    if (uVar7 == 0x25) {
      uVar7 = (uint)*pbVar9;
      pbVar9 = param_2 + 2;
      if (uVar7 != 0x25) {
        bVar1 = uVar7 != 0x2a;
        iVar3 = 0;
        if (!bVar1) {
          uVar7 = (uint)*pbVar9;
          pbVar9 = param_2 + 3;
        }
        param_2 = pbVar9;
        uVar5 = (uint)bVar1;
        if (((&DAT_100032e1)[uVar7] & 4) != 0) {
          iVar4 = 0;
          do {
            iVar3 = (iVar4 + iVar3) * 2 + uVar7;
            uVar7 = (uint)*param_2;
            iVar3 = iVar3 + -0x30;
            param_2 = param_2 + 1;
            iVar4 = iVar3 * 4;
          } while (((&DAT_100032e1)[uVar7] & 4) != 0);
        }
        if (iVar3 == 0) {
          iVar3 = 0x7fffffff;
        }
        if ((uVar7 == 0x6c) || (uVar8 = uVar7, uVar7 == 0x68)) {
          uVar8 = (uint)*param_2;
          param_2 = param_2 + 1;
        }
        if ((uVar8 == 0) ||
           ((uVar8 == 0x5b &&
            (param_2 = (byte *)FUN_0040f8d8(param_2,auStack_100), param_2 == (byte *)0x0)))) {
          return -1;
        }
        if (((&DAT_100032e1)[uVar8] & 1) != 0) {
          uVar8 = (uint)(byte)(&DAT_100033e2)[uVar8];
          uVar7 = 0x6c;
        }
        if ((((uVar8 != 0x6e) && (*(int *)(unaff_gp + -0x7a9c) == 0)) && (uVar8 != 99)) &&
           (uVar8 != 0x5b)) {
          *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
          if ((*(char *)((int)param_1 + 0xd) == 'd') && (*param_1 == 0)) {
            uVar6 = 0xffffffff;
          }
          else {
            iVar4 = *param_1 + -1;
            *param_1 = iVar4;
            if (iVar4 < 0) {
              uVar6 = func_0x0f8010e0(param_1);
            }
            else {
              uVar6 = (uint)*(byte *)param_1[1];
              param_1[1] = (int)((byte *)param_1[1] + 1);
            }
          }
          bVar2 = (&DAT_100032e1)[uVar6];
          while ((bVar2 & 8) != 0) {
            *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
            if ((*(char *)((int)param_1 + 0xd) == 'd') && (*param_1 == 0)) {
              uVar6 = 0xffffffff;
            }
            else {
              iVar4 = *param_1 + -1;
              *param_1 = iVar4;
              if (iVar4 < 0) {
                uVar6 = func_0x0f8010e0(param_1);
              }
              else {
                uVar6 = (uint)*(byte *)param_1[1];
                param_1[1] = (int)((byte *)param_1[1] + 1);
              }
            }
            bVar2 = (&DAT_100032e1)[uVar6];
          }
          *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
          iVar4 = func_0x0f801378(uVar6,param_1);
          if (iVar4 == -1) goto code_r0x0040ebc0;
        }
        if ((uVar8 == 0x5b) || (uVar8 == 99)) {
LAB_0040ea70:
          iVar3 = FUN_0040f5f4(uVar5,uVar8,iVar3,auStack_100,param_1,&local_res8);
        }
        else {
          if (uVar8 != 0x69) {
            if (uVar8 == 0x6e) {
              if (uVar7 == 0x68) {
                local_res8 = local_res8 + 7 & 0xfffffffc;
                **(undefined2 **)(local_res8 - 4) = (short)*(undefined4 *)(unaff_gp + -0x7aa0);
              }
              else if (uVar7 == 0x6c) {
                local_res8 = local_res8 + 7 & 0xfffffffc;
                **(undefined4 **)(local_res8 - 4) = *(undefined4 *)(unaff_gp + -0x7aa0);
              }
              else {
                local_res8 = local_res8 + 7 & 0xfffffffc;
                **(undefined4 **)(local_res8 - 4) = *(undefined4 *)(unaff_gp + -0x7aa0);
              }
              goto LAB_0040e620;
            }
            if (uVar8 == 0x73) goto LAB_0040ea70;
          }
          iVar3 = FUN_0040ec04(uVar5,uVar8,iVar3,uVar7,param_1,&local_res8);
        }
        if (iVar3 == 0) {
          if (*(int *)(unaff_gp + -0x7a9c) == 0) {
            return local_108;
          }
          if (local_108 != 0) {
            return local_108;
          }
          return -1;
        }
        local_108 = local_108 + uVar5;
        goto LAB_0040e620;
      }
    }
    param_2 = pbVar9;
    *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
    if ((*(char *)((int)param_1 + 0xd) == 'd') && (*param_1 == 0)) {
      uVar5 = 0xffffffff;
    }
    else {
      iVar3 = *param_1 + -1;
      *param_1 = iVar3;
      if (iVar3 < 0) {
        uVar5 = func_0x0f8010e0(param_1);
      }
      else {
        uVar5 = (uint)*(byte *)param_1[1];
        param_1[1] = (int)((byte *)param_1[1] + 1);
      }
    }
    if (uVar5 != uVar7) {
      *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
      iVar4 = func_0x0f801378(uVar5,param_1);
      iVar3 = local_108;
      if (iVar4 == -1) {
code_r0x0040ebc0:
        iVar3 = -1;
        if (local_108 != 0) {
          iVar3 = local_108;
        }
      }
      return iVar3;
    }
  } while( true );
}



int FUN_0040ec04(int param_1,int param_2,int param_3,int param_4,int *param_5,uint *param_6)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  bool bVar4;
  bool bVar5;
  uint uVar6;
  char cVar9;
  int iVar7;
  uint uVar8;
  byte *pbVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  int unaff_gp;
  double dVar16;
  int local_6c;
  byte local_40 [63];
  byte bStack_1;
  
  bVar4 = false;
  bVar5 = false;
  pbVar10 = local_40;
  local_6c = 0;
  switch(param_2) {
  case 0x65:
  case 0x66:
  case 0x67:
    bVar4 = true;
  case 100:
  case 0x69:
  case 0x75:
    iVar11 = 10;
    break;
  default:
    return 0;
  case 0x6f:
    iVar11 = 8;
    break;
  case 0x78:
    iVar11 = 0x10;
  }
  *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
  if ((*(char *)((int)param_5 + 0xd) == 'd') && (*param_5 == 0)) {
    uVar6 = 0xffffffff;
  }
  else {
    iVar12 = *param_5;
    *param_5 = iVar12 + -1;
    if (iVar12 + -1 < 0) {
      uVar6 = func_0x0f8010e0(param_5);
    }
    else {
      uVar6 = (uint)*(byte *)param_5[1];
      param_5[1] = (int)((byte *)param_5[1] + 1);
    }
  }
  if (uVar6 == 0x2b) {
LAB_0040ed44:
    param_3 = param_3 + -1;
    if (0 < param_3) {
      *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
      if ((*(char *)((int)param_5 + 0xd) == 'd') && (*param_5 == 0)) {
        uVar8 = 0xffffffff;
      }
      else {
        iVar12 = *param_5 + -1;
        *param_5 = iVar12;
        if (iVar12 < 0) {
          uVar8 = func_0x0f8010e0(param_5);
        }
        else {
          bVar3 = *(byte *)param_5[1];
          param_5[1] = (int)((byte *)param_5[1] + 1);
          uVar8 = (uint)bVar3;
        }
      }
      goto joined_r0x0040ede8;
    }
  }
  else {
    uVar8 = uVar6;
    if (uVar6 == 0x2d) {
      bVar5 = true;
      goto LAB_0040ed44;
    }
joined_r0x0040ede8:
    uVar6 = uVar8;
    if (((uVar8 == 0x30) && (param_2 == 0x69)) && (1 < param_3)) {
      *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
      if ((*(char *)((int)param_5 + 0xd) == 'd') && (*param_5 == 0)) {
        cVar9 = -1;
      }
      else {
        iVar12 = *param_5 + -1;
        *param_5 = iVar12;
        if (iVar12 < 0) {
          cVar9 = func_0x0f8010e0(param_5);
        }
        else {
          cVar9 = *(char *)param_5[1];
          param_5[1] = (int)((char *)param_5[1] + 1);
        }
      }
      if ((cVar9 != 'x') && (cVar9 != 'X')) {
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
        func_0x0f801378(cVar9,param_5);
        iVar11 = 8;
        param_3 = param_3 + -1;
        goto LAB_0040f174;
      }
      cVar2 = *(char *)((int)param_5 + 0xd);
      iVar12 = *param_5;
      if ((cVar2 == 'd') || (iVar12 != 0)) {
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
        if ((cVar2 == 'd') && (iVar12 == 0)) {
          uVar6 = 0xffffffff;
        }
        else {
          *param_5 = iVar12 + -1;
          if (iVar12 + -1 < 0) {
            uVar6 = func_0x0f8010e0(param_5);
          }
          else {
            uVar6 = (uint)*(byte *)param_5[1];
            param_5[1] = (int)((byte *)param_5[1] + 1);
          }
        }
        uVar6 = uVar6 & 0xff;
      }
      else {
        iVar12 = FUN_0040e000(cVar2,local_40,1);
        uVar6 = 0xff;
        if (iVar12 == 1) {
          uVar6 = (uint)local_40[0];
        }
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
      }
      if (((&DAT_100032e1)[uVar6] & 0x80) == 0) {
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
        func_0x0f801378(uVar6,param_5);
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
        func_0x0f801378(cVar9,param_5);
        param_3 = param_3 + -1;
        goto LAB_0040f174;
      }
      iVar11 = 0x10;
      if (param_3 < 3) {
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
        func_0x0f801378(uVar6,param_5);
        iVar11 = 0x10;
        param_3 = param_3 + -1;
        uVar6 = uVar8;
      }
      else {
        param_3 = param_3 + -2;
      }
    }
  }
  param_3 = param_3 + -1;
  uVar8 = uVar6;
LAB_0040f174:
  iVar14 = 0;
  iVar13 = 0;
  iVar12 = 0;
  for (; -1 < param_3; param_3 = param_3 + -1) {
    if (&bStack_1 <= pbVar10) {
      *(undefined4 *)(unaff_gp + -0x7a84) = 0x22;
      return 0;
    }
    bVar3 = (&DAT_100032e1)[uVar8];
    if (((bVar3 & 4) == 0) && ((iVar11 != 0x10 || ((bVar3 & 0x80) == 0)))) {
      if (!bVar4) break;
      if ((uVar8 != 0x2e) || (bVar1 = iVar12 != 0, iVar12 = iVar12 + 1, bVar1)) {
        if (((uVar8 != 0x65) && (uVar8 != 0x45)) ||
           ((iVar14 == 0 || (bVar1 = iVar13 != 0, iVar13 = iVar13 + 1, bVar1)))) break;
        *pbVar10 = (byte)uVar8;
        *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
        pbVar10 = pbVar10 + 1;
        if ((*(char *)((int)param_5 + 0xd) == 'd') && (*param_5 == 0)) {
          uVar8 = 0xffffffff;
        }
        else {
          iVar7 = *param_5;
          *param_5 = iVar7 + -1;
          if (iVar7 + -1 < 0) {
            uVar8 = func_0x0f8010e0(param_5);
          }
          else {
            uVar8 = (uint)*(byte *)param_5[1];
            param_5[1] = (int)((byte *)param_5[1] + 1);
          }
        }
        if ((((((&DAT_100032e1)[uVar8] & 4) == 0) && (uVar8 != 0x2b)) && (uVar8 != 0x2d)) &&
           (((&DAT_100032e1)[uVar8] & 8) == 0)) break;
      }
    }
    else {
      if ((bVar3 & 4) == 0) {
        iVar7 = 0x57;
        if ((bVar3 & 1) != 0) {
          iVar7 = 0x37;
        }
      }
      else {
        iVar7 = 0x30;
      }
      if (iVar11 <= (int)(uVar8 - iVar7)) break;
      if ((param_1 != 0) && (!bVar4)) {
        local_6c = iVar11 * local_6c + (uVar8 - iVar7);
      }
      iVar14 = iVar14 + 1;
    }
    *pbVar10 = (byte)uVar8;
    *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
    pbVar10 = pbVar10 + 1;
    if ((*(char *)((int)param_5 + 0xd) == 'd') && (*param_5 == 0)) {
      uVar8 = 0xffffffff;
    }
    else {
      iVar7 = *param_5;
      *param_5 = iVar7 + -1;
      if (iVar7 + -1 < 0) {
        uVar8 = func_0x0f8010e0(param_5);
      }
      else {
        uVar8 = (uint)*(byte *)param_5[1];
        param_5[1] = (int)((byte *)param_5[1] + 1);
      }
    }
  }
  if ((param_1 != 0) && (iVar14 != 0)) {
    if (bVar4) {
      *pbVar10 = 0;
      dVar16 = (double)func_0x0f801010(local_40);
      if (bVar5) {
        dVar16 = -dVar16;
      }
      if (param_4 == 0x6c) {
        uVar6 = *param_6 + 7 & 0xfffffffc;
        *param_6 = uVar6;
        puVar15 = *(undefined4 **)(uVar6 - 4);
        *puVar15 = (int)((ulonglong)dVar16 >> 0x20);
        puVar15[1] = SUB84(dVar16,0);
      }
      else {
        uVar6 = *param_6 + 7 & 0xfffffffc;
        *param_6 = uVar6;
        **(float **)(uVar6 - 4) = (float)dVar16;
      }
    }
    else {
      if ((bVar5) && (local_6c != -0x80000000)) {
        local_6c = -local_6c;
      }
      if (param_4 == 0x6c) {
        uVar6 = *param_6 + 7 & 0xfffffffc;
        *param_6 = uVar6;
        **(int **)(uVar6 - 4) = local_6c;
      }
      else if (param_4 == 0x68) {
        uVar6 = *param_6 + 7 & 0xfffffffc;
        *param_6 = uVar6;
        **(undefined2 **)(uVar6 - 4) = (short)local_6c;
      }
      else {
        uVar6 = *param_6 + 7 & 0xfffffffc;
        *param_6 = uVar6;
        **(int **)(uVar6 - 4) = local_6c;
      }
    }
  }
  *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
  iVar11 = func_0x0f801378(uVar8,param_5);
  if (iVar11 == -1) {
    *(undefined4 *)(unaff_gp + -0x7a9c) = 1;
  }
  return iVar14;
}



undefined4 FUN_0040f5f4(int param_1,int param_2,int param_3,int param_4,int *param_5,uint *param_6)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined *puVar4;
  int unaff_gp;
  undefined *local_c;
  
  if (param_1 == 0) {
    local_c = (undefined *)0x0;
  }
  else {
    uVar3 = *param_6 + 7 & 0xfffffffc;
    *param_6 = uVar3;
    local_c = *(undefined **)(uVar3 - 4);
  }
  if ((param_2 == 99) && (param_3 == 0x7fffffff)) {
    param_3 = 1;
  }
  *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
  if ((*(char *)((int)param_5 + 0xd) == 'd') && (*param_5 == 0)) {
    uVar3 = 0xffffffff;
  }
  else {
    iVar1 = *param_5;
    *param_5 = iVar1 + -1;
    if (iVar1 + -1 < 0) {
      uVar3 = func_0x0f8010e0(param_5);
    }
    else {
      uVar3 = (uint)*(byte *)param_5[1];
      param_5[1] = (int)((byte *)param_5[1] + 1);
    }
  }
  puVar4 = local_c;
  if (((uVar3 != 0xffffffff) && ((param_2 != 0x73 || (((&DAT_100032e1)[uVar3] & 8) == 0)))) &&
     ((param_2 != 0x5b || (*(char *)(param_4 + uVar3) == '\0')))) {
    while( true ) {
      if (param_1 != 0) {
        *puVar4 = (char)uVar3;
      }
      param_3 = param_3 + -1;
      puVar4 = puVar4 + 1;
      if (param_3 < 1) break;
      *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + 1;
      if ((*(char *)((int)param_5 + 0xd) == 'd') && (*param_5 == 0)) {
        uVar3 = 0xffffffff;
      }
      else {
        iVar1 = *param_5 + -1;
        *param_5 = iVar1;
        if (iVar1 < 0) {
          uVar3 = func_0x0f8010e0(param_5);
        }
        else {
          uVar3 = (uint)*(byte *)param_5[1];
          param_5[1] = (int)((byte *)param_5[1] + 1);
        }
      }
      if (((uVar3 == 0xffffffff) || ((param_2 == 0x73 && (((&DAT_100032e1)[uVar3] & 8) != 0)))) ||
         ((param_2 == 0x5b && (*(char *)(param_4 + uVar3) != '\0')))) break;
    }
  }
  if (uVar3 == 0xffffffff) {
    *(undefined4 *)(unaff_gp + -0x7a9c) = 1;
    *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
  }
  else if (0 < param_3) {
    *(int *)(unaff_gp + -0x7aa0) = *(int *)(unaff_gp + -0x7aa0) + -1;
    iVar1 = func_0x0f801378(uVar3,param_5);
    if (iVar1 == -1) {
      *(undefined4 *)(unaff_gp + -0x7a9c) = 1;
    }
  }
  if (puVar4 == local_c) {
    uVar2 = 0;
  }
  else {
    if (param_1 != 0) {
      if (param_2 == 99) {
        return 1;
      }
      *puVar4 = 0;
    }
    uVar2 = 1;
  }
  return uVar2;
}



byte * FUN_0040f8d8(byte *param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  
  bVar1 = *param_1 == 0x5e;
  if (bVar1) {
    param_1 = param_1 + 1;
  }
  func_0x0f801238(param_2,!bVar1,0x100);
  uVar4 = (uint)*param_1;
  if ((uVar4 == 0x5d) || (uVar4 == 0x2d)) {
    *(bool *)(param_2 + uVar4) = bVar1;
    uVar4 = (uint)param_1[1];
    param_1 = param_1 + 1;
  }
  while( true ) {
    pbVar5 = param_1 + 1;
    if (uVar4 == 0x5d) {
      return pbVar5;
    }
    if (uVar4 == 0) break;
    if (((uVar4 == 0x2d) && (uVar3 = (uint)*pbVar5, uVar3 != 0x5d)) &&
       (uVar2 = (uint)param_1[-1], uVar2 < uVar3)) {
      func_0x0f801238(param_2 + uVar2,bVar1,(uVar3 - uVar2) + 1);
      pbVar5 = param_1 + 2;
    }
    else {
      *(bool *)(param_2 + uVar4) = bVar1;
    }
    uVar4 = (uint)*pbVar5;
    param_1 = pbVar5;
  }
  return (byte *)0x0;
}



undefined4 FUN_0040fa00(void)

{
  undefined4 in_v0;
  
  DAT_100042ec = in_v0;
  return 0xffffffff;
}



undefined4 FUN_0040fa10(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0;
}



void FUN_0040fa30(undefined4 param_1,undefined4 param_2,undefined4 *param_3,code *param_4)

{
  (*param_4)();
  syscall(0);
  syscall(0);
  if (param_4 != (code *)0x0) {
    FUN_0040fa00();
    return;
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0x3f5;
  }
  return;
}



void FUN_0040fa50(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  syscall(0);
  if (param_4 != 0) {
    FUN_0040fa00();
    return;
  }
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = 0x3f5;
  }
  return;
}



undefined4 FUN_0040fa80(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 0;
}



undefined4 FUN_0040faa0(void)

{
  undefined4 uVar1;
  int in_a3;
  
  syscall(0);
  if (in_a3 != 0) {
    uVar1 = FUN_0040fa00();
    return uVar1;
  }
  return 1000;
}



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040fb3c(void)

{
  _DAT_0f400000 = &DAT_100042ec;
  _DAT_0f400004 = &DAT_100032e0;
  _DAT_0f400008 = 0xf801108;
  _DAT_0f40000c = &DAT_10003694;
  _DAT_0f400010 = FUN_0040e040;
  _DAT_0f400014 = &LAB_0040e0b0;
  _DAT_0f400018 = 0xf801018;
  _DAT_0f40001c = 0xf801030;
  _DAT_0f400020 = 0xf801048;
  _DAT_0f400024 = FUN_0040dfa0;
  _DAT_0f400028 = &LAB_0040e0d0;
  _DAT_0f40002c = FUN_0040d3c0;
  _DAT_0f400030 = &SUB_0f801120;
  _DAT_0f400034 = &LAB_0040e0f0;
  _DAT_0f400038 = FUN_0040e110;
  _DAT_0f40003c = 0xf801128;
  _DAT_0f400040 = &SUB_0f801130;
  _DAT_0f400044 = &LAB_0040e220;
  _DAT_0f400048 = &SUB_0f801150;
  _DAT_0f40004c = &SUB_0f801168;
  _DAT_0f400050 = &SUB_0f801200;
  _DAT_0f400054 = &LAB_0040e250;
  _DAT_0f400058 = &SUB_0f8011b0;
  _DAT_0f40005c = FUN_0040e270;
  _DAT_0f400060 = &LAB_0040e290;
  _DAT_0f400064 = &SUB_0f801208;
  _DAT_0f400068 = FUN_0040dfc0;
  _DAT_0f40006c = 0xf8013b0;
  _DAT_0f400070 = &SUB_0f801250;
  _DAT_0f400074 = FUN_0040e000;
  _DAT_0f400078 = 0xf801210;
  _DAT_0f40007c = 0xf8012a8;
  _DAT_0f400080 = FUN_0040e2b0;
  _DAT_0f400084 = &LAB_0040e2f0;
  _DAT_0f400088 = &LAB_0040e390;
  _DAT_0f40008c = &SUB_0f8012c0;
  _DAT_0f400090 = &LAB_0040e3b0;
  _DAT_0f400094 = &SUB_0f8012e8;
  _DAT_0f400098 = &SUB_0f8012f0;
  _DAT_0f40009c = &SUB_0f801308;
  _DAT_0f4000a0 = 0xf801318;
  _DAT_0f4000a4 = &SUB_0f801320;
  _DAT_0f4000a8 = FUN_0040dcc0;
  _DAT_0f4000ac = 0xf801368;
  _DAT_0f4000b0 = FUN_0040dfe0;
  _DAT_0f4000b4 = FUN_0040e410;
  _DAT_0f4000b8 = &LAB_0040e440;
  _DAT_0f4000bc = FUN_0040e51c;
  _DAT_0f4000c0 = FUN_0040e460;
  _DAT_0f4000c4 = FUN_0040e498;
  _DAT_0f4000c8 = &SUB_0f801040;
  _DAT_0f4000cc = &DAT_10004318;
  _DAT_0f4000d0 = &DAT_1000431c;
  _DAT_0f4000d4 = &LAB_0040e560;
  _DAT_0f4000d8 = FUN_0040e580;
  func_0x0f4016e0(0xf401000);
  _DAT_0fc00020 = &SUB_0f801208;
  _DAT_0fc00024 = 0xf801210;
  _DAT_0fc00028 = &SUB_0f801200;
  _DAT_0fc00040 = &DAT_10004d10;
  _DAT_0fc00044 = &DAT_10006d18;
  _DAT_0fc00048 = &DAT_10008d20;
  _DAT_0fc0004c = &DAT_10003694;
  _DAT_0fc00050 = &PTR_DAT_100041a0;
  _DAT_0fc00054 = &DAT_10003500;
  _DAT_0fc00014 = &LAB_0040fac0;
  _DAT_0fc00018 = &LAB_0040faf0;
  _DAT_0fc00010 = &DAT_100042e0;
  _DAT_0fc0001c = &DAT_100042ec;
  _DAT_0fc00000 = &DAT_100032e0;
  _DAT_0fc00038 = 0xf8013b0;
  _DAT_0fc00034 = &DAT_100041e0;
  _DAT_0fc00030 = 0xfc00060;
  return;
}


