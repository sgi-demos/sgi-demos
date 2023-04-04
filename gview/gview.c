#include "gview.h"



void FUN_00000270(void)

{
  int unaff_gp;
  
  func_0x0f801150(0x100036b4,unaff_gp + -0x7e90,unaff_gp + -0x7ea0,0x100001c0);
  func_0x0040d3c0(1);
  return;
}



undefined4 FUN_000002ac(int param_1,undefined4 *param_2)

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
  iVar1 = func_0x0040d3f0(param_1,param_2,0x10000234);
  if (iVar1 != -1) {
    iVar3 = unaff_gp + -0x7ea0;
    do {
      if (iVar1 == 0x6c) {
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 200) = 1;
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd4) = 0;
        iVar1 = func_0x0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e5c,
                                *(int *)(unaff_gp + -0x7e98) + 0xcc,
                                *(int *)(unaff_gp + -0x7e98) + 0xd0);
        if (iVar1 != 2) {
          func_0x00400270();
        }
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xd0) == 0) {
          iVar1 = unaff_gp + -0x7e54;
        }
        else {
          iVar1 = unaff_gp + -0x7e4c;
        }
        func_0x0f801250(0x10000350,iVar3,iVar1);
      }
      else if (iVar1 < 0x6d) {
        if (iVar1 == 0x56) {
          if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x94) != 0) {
            func_0x00400270();
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
              iVar1 = func_0x0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e60,
                                      *(int *)(unaff_gp + -0x7e98) + 0x104);
              if (iVar1 != 1) {
                func_0x00400270();
              }
              func_0x0f801250(0x10000330,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x104));
            }
            else {
              if ((iVar1 < 0x47) || (iVar1 != 0x4c)) goto LAB_000008fc;
              func_0x0f801250(0x10000310);
              *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xb8) = 1;
            }
          }
          else if (iVar1 == 0x52) {
            local_2018 = 1;
            if (local_201c != 0) {
              func_0x00400270();
            }
            local_2020 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          }
          else {
            if ((0x52 < iVar1) || (iVar1 != 0x50)) goto LAB_000008fc;
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
              func_0x00400270();
            }
            local_2020 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          }
          else {
LAB_000008fc:
            func_0x00400270();
          }
        }
        else {
          if (iVar1 != 0x69) goto LAB_000008fc;
          uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x9c) = uVar2;
        }
      }
      else if (iVar1 == 0x73) {
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x78) = 1;
        iVar1 = func_0x0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e64,
                                *(int *)(unaff_gp + -0x7e98) + 0x7c);
        if (iVar1 != 1) {
          func_0x00400270();
        }
        dVar8 = (double)*(float *)(*(int *)(unaff_gp + -0x7e98) + 0x7c);
        func_0x0f801150(0x100036b4,0x100002d4,(int)((ulonglong)dVar8 >> 0x20),SUB84(dVar8,0));
      }
      else if (iVar1 < 0x74) {
        if (iVar1 == 0x6e) {
          local_10 = 1;
        }
        else if (iVar1 < 0x6f) {
          if (iVar1 != 0x6d) goto LAB_000008fc;
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xbc) = 1;
          func_0x004034f0();
          pcVar5 = *(char **)(unaff_gp + -0x7bb4);
          local_2054[0] = 0;
          iVar1 = func_0x0040d7a4(pcVar5,0x10000374,local_2054);
          while (iVar1 == 1) {
            iVar1 = func_0x0f801130(local_2054,unaff_gp + -0x7e44);
            if (iVar1 == 0) {
              func_0x0f801150(0x100036b4,0x100003a0,iVar3,local_2054);
              func_0x00400270();
            }
            else {
              func_0x0f801150(0x100036b4,0x10000380,iVar3,local_2054);
              func_0x00403584(iVar1,local_2054);
            }
            iVar1 = func_0x0f801308(local_2054);
            pcVar5 = pcVar5 + iVar1;
            if (*pcVar5 == ',') {
              pcVar5 = pcVar5 + 1;
            }
            local_2054[0] = 0;
            iVar1 = func_0x0040d7a4(pcVar5,0x100003c0,local_2054);
          }
        }
        else {
          if (iVar1 != 0x6f) goto LAB_000008fc;
          uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
          *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x74) = uVar2;
        }
      }
      else if (iVar1 == 0x76) {
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x90) != 0) {
          func_0x00400270();
        }
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x94) = 1;
        uVar2 = func_0x0f801300(*(undefined4 *)(unaff_gp + -0x7bb4));
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x98) = uVar2;
      }
      else if (iVar1 < 0x77) {
        if (iVar1 != 0x74) goto LAB_000008fc;
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x80) = 1;
        iVar1 = *(int *)(unaff_gp + -0x7e98);
        iVar1 = func_0x0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),0x100002e8,iVar1 + 0x84,
                                iVar1 + 0x88,iVar1 + 0x8c);
        if (iVar1 != 3) {
          func_0x00400270();
        }
        iVar1 = *(int *)(unaff_gp + -0x7e98);
        func_0x0f801150(0x100036b4,0x100002f4,
                        (int)((ulonglong)(double)*(float *)(iVar1 + 0x84) >> 0x20),
                        SUB84((double)*(float *)(iVar1 + 0x84),0),(double)*(float *)(iVar1 + 0x88),
                        (double)*(float *)(iVar1 + 0x8c));
      }
      else {
        if (iVar1 != 0x77) goto LAB_000008fc;
        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x68) = 1;
        iVar1 = func_0x0040d7a4(*(undefined4 *)(unaff_gp + -0x7bb4),unaff_gp + -0x7e6c,
                                *(int *)(unaff_gp + -0x7e98),*(int *)(unaff_gp + -0x7e98) + 4);
        if ((iVar1 != 1) && (iVar1 != 2)) {
          func_0x00400270();
        }
        if (iVar1 == 1) {
          (*(undefined4 **)(unaff_gp + -0x7e98))[1] = **(undefined4 **)(unaff_gp + -0x7e98);
        }
        func_0x0f801150(0x100036b4,0x100002b8,**(undefined4 **)(unaff_gp + -0x7e98),
                        (*(undefined4 **)(unaff_gp + -0x7e98))[1]);
        piVar6 = *(int **)(unaff_gp + -0x7e98);
        piVar6[0x1b] = (int)((float)*piVar6 / (float)piVar6[1]);
      }
      iVar1 = func_0x0040d3f0(param_1,param_2,0x10000234);
    } while (iVar1 != -1);
  }
  iVar1 = unaff_gp + -0x7ea0;
  if (local_2018 == 0) {
    if ((local_201c != 0) && (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x104) == 0)) {
      func_0x0f801150(0x100036b4,0x100003cc,iVar1);
      func_0x0040d3c0(0xffffffff);
    }
    uVar2 = func_0x0f801208(2000000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x108) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x108) == 0) {
      func_0x004092d4(unaff_gp + -0x7e40);
    }
    uVar2 = func_0x0f801208(0xc);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x10c) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x10c) == 0) {
      func_0x004092d4(unaff_gp + -0x7e38);
    }
    uVar2 = func_0x0f801208(300000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x114) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x114) == 0) {
      func_0x004092d4(unaff_gp + -0x7e30);
    }
    uVar2 = func_0x0f801208(4800000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x110) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x110) == 0) {
      func_0x004092d4(unaff_gp + -0x7e28);
    }
    uVar2 = func_0x0f801208(0xe10);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x124) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x124) == 0) {
      func_0x004092d4(unaff_gp + -0x7e20);
    }
    uVar2 = func_0x0f801208(0x140);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x118) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x118) == 0) {
      func_0x004092d4(unaff_gp + -0x7e18);
    }
    uVar2 = func_0x0f801208(0xf0);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x11c) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x11c) == 0) {
      func_0x004092d4(unaff_gp + -0x7e10);
    }
    uVar2 = func_0x0f801208(0xf0);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x120) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x120) == 0) {
      func_0x004092d4(unaff_gp + -0x7e08);
    }
    uVar2 = func_0x0f801208(3200000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x128) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x128) == 0) {
      func_0x004092d4(unaff_gp + -0x7e00);
    }
    uVar2 = func_0x0f801208(1600000);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 300) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 300) == 0) {
      func_0x004092d4(unaff_gp + -0x7df8);
    }
    uVar2 = func_0x0f801208(&DAT_0000fa00);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x130) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x130) == 0) {
      func_0x004092d4(unaff_gp + -0x7df0);
    }
    uVar2 = func_0x0f801208(400);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x138) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x138) == 0) {
      func_0x004092d4(unaff_gp + -0x7de8);
    }
    uVar2 = func_0x0f801208(800);
    *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) = uVar2;
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) == 0) {
      func_0x004092d4(unaff_gp + -0x7de0);
    }
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x104) != 0) {
      uVar2 = func_0x0f801208(800);
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf0) = uVar2;
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf0) == 0) {
        func_0x004092d4(unaff_gp + -0x7dd8);
      }
      func_0x00404580();
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
      func_0x0f801150(0x100036b4,0x1000040c,iVar1);
      iVar3 = func_0x00405590(0x10003694);
      if (iVar3 == 0) {
        func_0x0040d3c0(0xffffffff);
      }
    }
    else if (iVar3 < 1) {
      func_0x00400270();
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
              func_0x004092d4(0x10000450,iVar1,uVar2);
            }
            else {
              func_0x0f801150(0x100036b4,0x1000042c,iVar1,uVar2);
            }
          }
          else {
            func_0x0f801150(0x100036b4,0x1000046c,iVar1,uVar2);
            iVar4 = func_0x00405590(iVar3);
            if (iVar4 == 0) {
              func_0x0040d3c0(0xffffffff);
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
      func_0x0f801250(0x10000484,iVar1);
    }
    if (0 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164)) {
      func_0x0f801250(0x100004a4,iVar1);
    }
    if (0 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168)) {
      func_0x0f801250(0x100004c0,iVar1);
    }
    func_0x0f801250(0x100004e0,iVar1,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x174));
  }
  if (local_2018 != 0) {
    func_0x0f801150(0x100036b4,0x10000500);
    iVar3 = func_0x0f801130(local_2020,unaff_gp + -0x7dcc);
    if (iVar3 == 0) {
      func_0x0f801150(0x100036b4,0x1000051c,iVar1,local_2020);
      func_0x0040d3c0(0xffffffff);
    }
    iVar4 = func_0x00404e78(iVar3,local_206c);
    func_0x0f801150(0x100036b4,unaff_gp + -0x7dc8);
    func_0x0f801120(iVar3);
    if (iVar4 == 0) {
      func_0x0f801150(0x100036b4,0x1000053c,iVar1);
      func_0x0040d3c0(0xffffffff);
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
      uVar2 = func_0x00404668(**(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0x13c));
      **(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xf0) = uVar2;
    }
    else {
      iVar4 = 0;
      if (0 < *(int *)(iVar3 + 0xd4)) {
        iVar3 = 0;
        do {
          uVar2 = func_0x00404668(*(undefined4 *)
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
    func_0x0f801150(0x100036b4,0x1000055c);
    iVar3 = func_0x0f801130(local_2020,unaff_gp + -0x7dc0);
    if (iVar3 == 0) {
      func_0x0f801150(0x100036b4,0x10000578,iVar1,local_2020);
      func_0x0040d3c0(0xffffffff);
    }
    func_0x00404b60(uVar7,uVar2,iVar3);
    func_0x0f801120(iVar3);
    func_0x0f801150(0x100036b4,unaff_gp + -0x7dbc);
  }
  if (local_10 == 0) {
    func_0x00401678(*param_2);
    func_0x00408200();
    if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xbc) == 0) {
      func_0x00403440();
    }
    else {
      func_0x00403684();
      uVar2 = func_0x0040381c(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc0));
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc4) = uVar2;
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xc4) == 0) {
        func_0x0f801150(0x100036b4,0x10000598,iVar1,
                        *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc0));
        func_0x0040d3c0(0xffffffff);
      }
      func_0x0f801150(0x100036b4,0x100005b8,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc0));
    }
    func_0x00402098();
    func_0x00401a00();
  }
  return 0;
}



void FUN_00001504(void)

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
      func_0x004082e8(*(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) + iVar1));
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar3 < *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174));
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
  }
  if ((iVar1 == 0) && (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x104) != 0)) {
    func_0x004082e8(**(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xf0));
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
  }
  if ((iVar1 != 0) && (iVar2 = *(int *)(unaff_gp + -0x7e98), *(int *)(iVar2 + 0x104) == 0)) {
    func_0x004082e8(*(undefined4 *)(*(int *)(iVar2 + 0x13c) + *(int *)(iVar2 + 0xd8) * 4));
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
  }
  if ((iVar1 != 0) && (iVar1 = *(int *)(unaff_gp + -0x7e98), *(int *)(iVar1 + 0x104) != 0)) {
    func_0x004082e8(*(undefined4 *)(*(int *)(iVar1 + 0xf0) + *(int *)(iVar1 + 0xd8) * 4));
  }
  return;
}



void FUN_00001678(int param_1)

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
      func_0x0f801150(0x100036b4,0x100005cc,param_1);
      func_0x0f401290();
      func_0x0040d3c0(1);
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
  uVar5 = func_0x0f4015a8(0x10000254);
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
  func_0x0f402190(0x10000278);
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x48) == 0) {
    func_0x0f402298(0,0);
  }
  return;
}



void FUN_00001a00(void)

{
  int unaff_gp;
  
  func_0x0f401508(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 100));
  return;
}



void FUN_00001a28(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int unaff_gp;
  double dVar4;
  double dVar5;
  undefined auStack_10 [16];
  
  if (param_1 == 0) {
    uVar1 = func_0x0040d810(auStack_10);
    *(undefined4 *)(unaff_gp + -0x7b70) = uVar1;
  }
  else if (param_1 % 100 == 0) {
    iVar2 = func_0x0040d810(auStack_10);
    dVar4 = (double)(iVar2 - *(int *)(unaff_gp + -0x7b70)) / *(double *)(unaff_gp + -0x7fe8);
    dVar5 = *(double *)(unaff_gp + -0x7fe8) / dVar4;
    func_0x0f801250(0x100005ec,param_2,(int)((ulonglong)dVar5 >> 0x20),SUB84(dVar5,0));
    iVar3 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160);
    if (iVar3 != 0) {
      dVar5 = (double)(iVar3 * 100) / dVar4;
      func_0x0f801250(0x10000600,param_2,(int)((ulonglong)dVar5 >> 0x20),SUB84(dVar5,0));
    }
    iVar3 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164);
    if (iVar3 == 0) {
      func_0x0f801250(unaff_gp + -0x7db4);
    }
    else {
      dVar4 = (double)(iVar3 * 100) / dVar4;
      func_0x0f801250(0x10000614,param_2,(int)((ulonglong)dVar4 >> 0x20),SUB84(dVar4,0));
    }
    *(int *)(unaff_gp + -0x7b70) = iVar2;
  }
  return;
}



void FUN_00001ce8(void)

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
    func_0x0f801150(0x100036b4,0x10000668,unaff_gp + -0x7ea0,uVar2);
  }
  else {
    func_0x0f801150(0x100036b4,0x10000624,unaff_gp + -0x7ea0,uVar2);
    func_0x0f402578(1);
    func_0x0f401120(local_48);
    func_0x0f801250(0x10000644);
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



void FUN_00001ebc(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  int unaff_gp;
  
  uVar2 = *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x98);
  if (*(int *)(unaff_gp + -0x7d84) == 0) {
    iVar1 = func_0x0f801130(uVar2,unaff_gp + -0x7d80);
    if (iVar1 == 0) {
      func_0x0f801150(0x100036b4,0x100006d4,unaff_gp + -0x7ea0,uVar2);
      func_0x0040d3c0(0xffffffff);
    }
    else {
      func_0x0f801150(0x100036b4,0x10000688,unaff_gp + -0x7ea0,uVar2);
      puVar3 = &DAT_100044e8;
      do {
        func_0x0040d768(iVar1,unaff_gp + -0x7d7c,puVar3);
        puVar3 = puVar3 + 4;
      } while (puVar3 != (undefined *)0x10004528);
      iVar4 = 0x10004528;
      do {
        func_0x0040d768(iVar1,unaff_gp + -0x7d78,iVar4);
        iVar4 = iVar4 + 4;
      } while (iVar4 != 0x10004568);
      func_0x0f801250(0x100006ac);
      iVar1 = 0;
      do {
        func_0x0f801250(unaff_gp + -0x7d74);
        iVar4 = 0;
        do {
          func_0x0f801250(unaff_gp + -0x7d70);
          iVar4 = iVar4 + 1;
        } while (iVar4 != 4);
        func_0x0f801250(unaff_gp + -0x7d6c);
        iVar1 = iVar1 + 4;
      } while (iVar1 != 0x10);
      *(undefined4 *)(unaff_gp + -0x7d84) = 1;
    }
  }
  func_0x0f402578(1);
  func_0x0f402190(&DAT_100044e8);
  func_0x0f402578(2);
  func_0x0f402190(0x10004528);
  return;
}



void FUN_00002098(void)

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
    func_0x00402f60();
  }
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd8) = 0;
  local_3c = 0;
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x70) = 0;
  local_30 = 0;
LAB_000020f4:
  iVar2 = func_0x0f401200();
  if (iVar2 == 0) goto code_r0x00002680;
  do {
    sVar3 = func_0x0f4011f0(local_10);
    while( true ) {
      if (sVar3 == 0x28) {
        if (local_10[0] != 0) {
          func_0x00409778(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x9c));
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
              func_0x00402f00();
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
          func_0x00402f00();
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
            func_0x00402f00();
          }
        }
      }
      else if (((sVar3 == 0x21c) && (*(int *)(unaff_gp + -0x7e88) != 0)) &&
              (*(int *)(unaff_gp + -0x7e84) != 0)) {
        func_0x00402f00();
      }
      iVar2 = func_0x0f401200();
      if (iVar2 != 0) break;
code_r0x00002680:
      if (local_4 != 0) {
        func_0x0f401570(0x40);
        func_0x0f401fe0(0);
        func_0x0f402120();
        func_0x0f401570(0x10);
        return;
      }
      if ((local_28 != 0) ||
         ((*(int *)(unaff_gp + -0x7e88) != 0 && (*(int *)(unaff_gp + -0x7e84) != 0))))
      goto LAB_000020f4;
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
          func_0x00403938(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xc4));
        }
        iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
        if ((iVar2 != 0) && (local_3c != 0)) {
          func_0x00401c18();
          iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 200);
        }
        if (((iVar2 != 0) && (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x20) != 0)) &&
           (local_3c == 0)) {
          func_0x00401b88(*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x10));
        }
        if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x48) == 0) {
          func_0x0f402230();
          if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x94) == 0) {
            func_0x00402bac();
          }
          else {
            func_0x00401ebc();
          }
          if (local_48 != 0) {
            local_48 = 0;
            func_0x00401ce8();
          }
          func_0x00401504();
          func_0x0f402228();
          iVar2 = local_38;
        }
        else {
          func_0x0f402230();
          if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x94) == 0) {
            func_0x00402fbc();
          }
          else {
            func_0x00401ebc();
          }
          if (local_48 != 0) {
            local_48 = 0;
            func_0x00401ce8();
          }
          func_0x00401504();
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
          func_0x0f402190(0x10000278);
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
          func_0x0f8012c0(auStack_78,0x100006f4,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xd8)
                         );
          func_0x0f402230();
          func_0x0f402190(0x10000278);
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
          func_0x00401a28(iVar2);
        }
        func_0x0f402588(0,0);
        goto LAB_000020f4;
      }
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x18) = 0;
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x1c) = 0;
      *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x20) = 0;
      local_28 = 0;
      sVar3 = func_0x0f4011f0(local_10);
    }
  } while( true );
}



void main(undefined4 param_1)

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



void FUN_00002f00(void)

{
  func_0x0f402098(0);
  func_0x0f402120();
  func_0x0f402518();
  func_0x0f402230();
  func_0x00402fbc();
  func_0x00401504();
  func_0x0f402228();
  func_0x0f402288();
  return;
}



void FUN_00002fbc(void)

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
  ulonglong uVar11;
  
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
  dVar7 = (double)func_0x0040d178(((double)fVar8 * *(double *)(unaff_gp + -0x7f90)) /
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
  dVar7 = (double)func_0x0040d178(((double)*(float *)(unaff_gp + -0x7b20) *
                                  *(double *)(unaff_gp + -0x7f90)) / *(double *)(unaff_gp + -0x7f88)
                                 );
  fVar8 = (float)dVar7 * *(float *)(unaff_gp + -0x7b60);
  dVar10 = ((double)*(float *)(unaff_gp + -0x7b20) * *(double *)(unaff_gp + -0x7f90)) /
           *(double *)(unaff_gp + -0x7f88);
  dVar7 = (double)func_0x0040d120(dVar10);
  fVar1 = (float)dVar7 * *(float *)(unaff_gp + -0x7b60);
  uVar11 = (ulonglong)dVar10 & 0xffffffff00000000 | (ulonglong)*(uint *)(unaff_gp + -0x7b24);
  func_0x0f402558(uVar11);
  uVar11 = uVar11 & 0xffffffff00000000 | (ulonglong)*(uint *)(unaff_gp + -0x7b20);
  func_0x0f402558(uVar11);
  uVar9 = (undefined4)(uVar11 >> 0x20);
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



void FUN_00003440(void)

{
  func_0x0f4015d0(0,1,0x3c,0x10000760);
  func_0x0f4015d0(100,1,0x38,0x10000728);
  func_0x0f4015d0(200,1,0x28,0x10000700);
  func_0x0f402570(1000,1);
  func_0x0f402570(0x44c,1);
  return;
}



void FUN_000034b8(int param_1)

{
  func_0x0f402570(0x4b0,param_1 != 0);
  return;
}



void FUN_000034f0(void)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = func_0x0f801208(2000);
  *(int *)(unaff_gp + -0x7b10) = iVar1;
  if (iVar1 == 0) {
    func_0x004092d4(0x1000094c);
  }
  *(undefined4 *)(unaff_gp + -0x7b0c) = 0;
  iVar1 = func_0x0f801208(1000);
  *(int *)(unaff_gp + -0x7b08) = iVar1;
  if (iVar1 == 0) {
    func_0x004092d4(0x1000095c);
  }
  *(undefined4 *)(unaff_gp + -0x7b04) = *(undefined4 *)(unaff_gp + -0x7b08);
  iVar1 = func_0x0f801208(0x640);
  *(int *)(unaff_gp + -0x7b00) = iVar1;
  if (iVar1 == 0) {
    func_0x004092d4(0x1000096c);
  }
  *(undefined4 *)(unaff_gp + -0x7afc) = *(undefined4 *)(unaff_gp + -0x7b00);
  *(undefined4 *)(unaff_gp + -0x7af8) = 1;
  *(undefined4 *)(unaff_gp + -0x7af4) = 1;
  *(undefined4 *)(unaff_gp + -0x7af0) = 1;
  return;
}



undefined4 FUN_00003584(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_gp;
  int local_4;
  
  if (*(int *)(unaff_gp + -0x7d34) == 0) {
    uVar1 = func_0x004043bc(0x1000097c);
    *(undefined4 *)(unaff_gp + -0x7adc) = uVar1;
    uVar1 = func_0x004043bc(0x10000988);
    *(undefined4 *)(unaff_gp + -0x7ad8) = uVar1;
    uVar1 = func_0x004043bc(0x10000994);
    *(undefined4 *)(unaff_gp + -0x7ad4) = uVar1;
    *(undefined4 *)(unaff_gp + -0x7d34) = 1;
  }
  func_0x0040406c(param_1,param_2);
  iVar2 = func_0x004040d0(&local_4);
  while (iVar2 != 0) {
    iVar2 = *(int *)(local_4 + 4);
    if ((iVar2 == 0) ||
       (((*(int *)(unaff_gp + -0x7adc) != iVar2 && (*(int *)(unaff_gp + -0x7ad8) != iVar2)) &&
        (*(int *)(unaff_gp + -0x7ad4) != iVar2)))) {
      func_0x00403ffc(0x100009a0);
    }
    else {
      func_0x00403bf8(local_4);
    }
    iVar2 = func_0x004040d0(&local_4);
  }
  return 1;
}



void FUN_00003684(void)

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
            func_0x0f801150(0x100036b4,0x100009cc);
          }
        }
        else if (iVar2 == 200) {
          iVar2 = piVar1[4];
          if (iVar2 != 1) {
            func_0x0f801150(0x100036b4,0x100009f4,0x10000a08);
            func_0x0040d3c0(1);
            iVar2 = piVar1[4];
          }
          func_0x0f402570(0x4b0,iVar2);
        }
        else {
          func_0x004092d4(0x10000a18);
        }
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x14;
    } while (iVar4 < *(int *)(unaff_gp + -0x7b0c));
  }
  return;
}



int * FUN_0000381c(undefined4 param_1)

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



void FUN_00003938(int param_1)

{
  func_0x0f402570(1000,*(undefined4 *)(param_1 + 0x10));
  return;
}



undefined4 FUN_00003960(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int unaff_gp;
  
  uVar2 = *(undefined4 *)(unaff_gp + -0x7b04);
  iVar1 = func_0x0f801308(param_1);
  if (999 - (*(int *)(unaff_gp + -0x7b04) - *(int *)(unaff_gp + -0x7b08)) <= iVar1) {
    func_0x0f801150(0x100036b4,0x10000a34,0x10000a48);
    func_0x0040d3c0(1);
  }
  func_0x0f801320(uVar2,param_1,iVar1 + 1);
  *(int *)(unaff_gp + -0x7b04) = *(int *)(unaff_gp + -0x7b04) + iVar1 + 1;
  return uVar2;
}



int * FUN_00003a78(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int unaff_gp;
  
  if (99 < *(int *)(unaff_gp + -0x7b0c)) {
    func_0x0f801150(0x100036b4,0x10000a74,0x10000a88);
    func_0x0040d3c0(1);
  }
  piVar2 = (int *)(*(int *)(unaff_gp + -0x7b10) + *(int *)(unaff_gp + -0x7b0c) * 0x14);
  iVar1 = func_0x00403960(param_1);
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
    func_0x004092d4(0x10000a94,param_2);
  }
  *(int *)(unaff_gp + -0x7b0c) = *(int *)(unaff_gp + -0x7b0c) + 1;
  return piVar2;
}



void FUN_00003b9c(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    uVar1 = func_0x004039f8(param_2);
    *(undefined4 *)(param_1 + 8) = uVar1;
  }
  else {
    func_0x004039f8(param_2);
  }
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  return;
}



undefined4 FUN_00003bf8(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_gp;
  double dVar3;
  uint in_fcsr;
  undefined4 *local_res0 [4];
  
  local_res0[0] = param_1;
  if (*(int *)(unaff_gp + -0x7acc) == 0) {
    uVar1 = func_0x004043bc(unaff_gp + -0x7d20);
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
  iVar2 = func_0x004040d0(local_res0);
  if (iVar2 == 0) {
    func_0x00403ffc(0x10000aac);
  }
  uVar1 = func_0x00403a78(*local_res0[0],(int)dVar3);
  iVar2 = func_0x00404370(local_res0);
  if (iVar2 == 0) {
    func_0x00403ffc(0x10000ac8);
  }
  iVar2 = local_res0[0][1];
  if ((iVar2 != 0) && (*(int *)(unaff_gp + -0x7ad0) != iVar2)) {
    do {
      func_0x00403e28(uVar1);
      iVar2 = func_0x00404370(local_res0);
      if (iVar2 == 0) {
        func_0x00403ffc(0x10000ae4);
      }
      iVar2 = local_res0[0][1];
    } while ((iVar2 != 0) && (*(int *)(unaff_gp + -0x7ad0) != iVar2));
  }
  if (iVar2 == 0) {
    func_0x00403ffc(0x10000b00);
  }
  iVar2 = func_0x004040d0(local_res0);
  if (iVar2 == 0) {
    func_0x0f801150(0x100036b4,0x10000b14,0x10000b28);
    func_0x0040d3c0(1);
  }
  iVar2 = local_res0[0][1];
  if (iVar2 == 0) {
    func_0x0f801150(0x100036b4,0x10000b40,0x10000b54);
    func_0x0040d3c0(1);
    iVar2 = local_res0[0][1];
  }
  if (*(float *)(iVar2 + 4) != 0.0) {
    func_0x0f801150(0x100036b4,0x10000b70,0x10000b84);
    func_0x0040d3c0(1);
  }
  func_0x00403b9c(uVar1,0);
  return 1;
}



undefined4 FUN_00003e28(int *param_1)

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
  
  iVar1 = func_0x004040d0(&local_4);
  if (iVar1 == 0) {
    func_0x0f801150(0x100036b4,0x10000b90,0x10000ba4);
    func_0x0040d3c0(1);
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
    func_0x004092d4(0x10000bb0);
  }
  iVar1 = local_4[1];
  if (iVar1 == 0) {
    func_0x00403ffc(0x10000c2c);
  }
  else if ((*(uint *)(iVar1 + 0xc) & local_8) == 0) {
    func_0x00403ffc(0x10000c0c);
  }
  else {
    func_0x00403b9c(param_1,*(undefined4 *)(iVar1 + 4));
    iVar1 = *(int *)(local_4[1] + 8);
    if (iVar1 < 0) {
      func_0x00403ffc(0x10000bc8);
    }
    iVar3 = 0;
    if (0 < iVar1) {
      do {
        iVar2 = func_0x004040d0(&local_4);
        if (iVar2 == 0) {
          func_0x00403ffc(0x10000bd8);
        }
        dVar4 = (double)func_0x0040d830(*local_4,&local_1c);
        fVar5 = (float)dVar4;
        if (local_1c == *local_4) {
          local_18 = (float)dVar4;
          func_0x00403ffc(0x10000bf8);
          fVar5 = local_18;
        }
        func_0x00403b9c(param_1,fVar5);
        iVar3 = iVar3 + 1;
      } while (iVar3 != iVar1);
    }
  }
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00003ffc(undefined4 param_1)

{
  int unaff_gp;
  
  func_0x0f801150(0x100036b4,0x10000c40,*(undefined4 *)(unaff_gp + -0x7ae8),_DAT_10004678,
                  _DAT_1000467c,param_1);
  func_0x0f801150(0x100036b4,0x10000c68,&DAT_10004570);
  func_0x0040d3c0(0xffffffff);
  return;
}



bool FUN_0000408c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = func_0x0f8010d8(param_1,param_2,*(undefined4 *)(unaff_gp + -0x7aec));
  if (iVar1 != 0) {
    *(int *)(unaff_gp + -0x7ae4) = *(int *)(unaff_gp + -0x7ae4) + 1;
  }
  return iVar1 != 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_000040d0(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  byte *pbVar5;
  byte *pbVar6;
  int unaff_gp;
  
  pbVar5 = *(byte **)(unaff_gp + -0x7d38);
  if (pbVar5 == (byte *)0x0) {
    pbVar5 = &DAT_10004570;
    iVar3 = func_0x0040408c(&DAT_10004570,0x100);
    if (iVar3 == 0) {
      _DAT_10004680 = 0;
      return 0;
    }
  }
  if (*(int *)(unaff_gp + -0x7ae0) != 0) {
    *(byte **)(unaff_gp + -0x7d38) = pbVar5;
    *(undefined4 *)(unaff_gp + -0x7ae0) = 0;
    *param_1 = &DAT_10004670;
    return _DAT_10004680;
  }
  uVar2 = (uint)*pbVar5;
  puVar4 = &DAT_100032e0 + uVar2;
  bVar1 = (&DAT_100032e1)[uVar2];
  while ((((bVar1 & 8) != 0 || (uVar2 == 0)) || (uVar2 == 0x23))) {
    if (puVar4 == &DAT_100032e0) {
      *(byte **)(unaff_gp + -0x7d38) = pbVar5;
LAB_000041bc:
      iVar3 = func_0x0040408c(&DAT_10004570,0x100);
      if (iVar3 == 0) {
        _DAT_10004680 = 0;
        return 0;
      }
      pbVar5 = &DAT_10004570;
    }
    else {
      if (puVar4 == (undefined *)0x10003303) {
        *(byte **)(unaff_gp + -0x7d38) = pbVar5;
        goto LAB_000041bc;
      }
      pbVar5 = pbVar5 + 1;
    }
    uVar2 = (uint)*pbVar5;
    puVar4 = &DAT_100032e0 + uVar2;
    bVar1 = (&DAT_100032e1)[uVar2];
  }
  puVar4 = &DAT_10004688;
  if (uVar2 == 0) {
    *(byte **)(unaff_gp + -0x7d38) = pbVar5;
  }
  else {
    pbVar6 = pbVar5;
    if (((&DAT_100032e1)[uVar2] & 8) == 0) {
      do {
        *puVar4 = (char)uVar2;
        uVar2 = (uint)pbVar6[1];
        puVar4 = puVar4 + 1;
        pbVar6 = pbVar6 + 1;
        if (uVar2 == 0) {
          *(byte **)(unaff_gp + -0x7d38) = pbVar6;
          goto LAB_00004290;
        }
      } while (((&DAT_100032e1)[uVar2] & 8) == 0);
      *(byte **)(unaff_gp + -0x7d38) = pbVar6;
    }
    else {
      *(byte **)(unaff_gp + -0x7d38) = pbVar5;
      puVar4 = &DAT_10004688;
    }
  }
LAB_00004290:
  *puVar4 = 0;
  if (uVar2 == 0) {
    iVar3 = func_0x0040408c(&DAT_10004570,0x100);
    if (iVar3 == 0) {
      _DAT_10004680 = 0;
      return 0;
    }
    *(undefined **)(unaff_gp + -0x7d38) = &DAT_10004570;
  }
  _DAT_10004670 = &DAT_10004688;
  _DAT_10004678 = *(undefined4 *)(unaff_gp + -0x7ae4);
  _DAT_1000467c = pbVar5 + -0x1000456f;
  _DAT_10004674 = (undefined4 *)0x0;
  if ((((&DAT_100032e1)[DAT_10004688] & 3) != 0) &&
     (_DAT_10004674 = (undefined4 *)func_0x004043bc(&DAT_10004688),
     _DAT_10004674 != (undefined4 *)0x0)) {
    _DAT_10004670 = (undefined *)*_DAT_10004674;
  }
  _DAT_10004680 = 1;
  *param_1 = &DAT_10004670;
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_00004370(undefined4 *param_1)

{
  undefined4 uVar1;
  int unaff_gp;
  
  if (*(int *)(unaff_gp + -0x7ae0) == 0) {
    uVar1 = func_0x004040d0();
    *(undefined4 *)(unaff_gp + -0x7ae0) = 1;
  }
  else {
    *param_1 = &DAT_10004670;
    uVar1 = _DAT_10004680;
  }
  return uVar1;
}



undefined4 * FUN_000043bc(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  
  bVar1 = false;
  puVar5 = (undefined4 *)&DAT_100007e0;
  iVar4 = 0;
  do {
    iVar2 = func_0x0f8012e8(param_1,*puVar5);
    iVar4 = iVar4 + 1;
    if (iVar2 == 0) {
      bVar1 = true;
      break;
    }
    puVar5 = puVar5 + 4;
  } while (iVar4 != 0xf);
  puVar3 = (undefined4 *)0x0;
  if (bVar1) {
    puVar3 = puVar5;
  }
  return puVar3;
}



undefined4 * FUN_00004460(void)

{
  undefined4 *puVar1;
  int unaff_gp;
  
  puVar1 = *(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xfc);
  *(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xfc) = puVar1 + 3;
  if (0x2de5 < ((int)puVar1 - *(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf4)) / 0xc) {
    func_0x0f801150(0x100036b4,0x10000c80,0x10000c94);
    func_0x0040d3c0(1);
  }
  *puVar1 = 0;
  puVar1[1] = 0;
  return puVar1;
}



int FUN_000044f0(int param_1)

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
    func_0x0f801150(0x100036b4,0x10000ca0,0x10000cb4);
    func_0x0040d3c0(1);
  }
  return iVar1;
}



void FUN_00004580(void)

{
  undefined4 uVar1;
  int unaff_gp;
  
  uVar1 = func_0x0f801208(0x226c8);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf4) = uVar1;
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf4) == 0) {
    func_0x004092d4(0x10000cc0);
  }
  uVar1 = func_0x0f801208(0x225510);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf8) = uVar1;
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xf8) == 0) {
    func_0x004092d4(0x10000cec);
  }
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xfc) =
       *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf4);
  *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x100) =
       *(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0xf8);
  if ((*(uint *)(*(int *)(unaff_gp + -0x7e98) + 0xf8) & 0xf) != 0) {
    func_0x0f801150(0x100036b4,0x10000d18);
  }
  return;
}



undefined4 FUN_00004668(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int unaff_gp;
  undefined4 *local_18 [5];
  undefined4 local_4;
  
  local_4 = func_0x0040a400();
  puVar2 = (undefined4 *)func_0x0f801208(0x10);
  if (puVar2 == (undefined4 *)0x0) {
    func_0x004092d4(unaff_gp + -0x7d10);
  }
  *puVar2 = 0x109;
  puVar2[2] = 0;
  func_0x0040a6d4(local_4,puVar2);
  iVar3 = func_0x0040a8e0(param_1);
  if (*(int *)(iVar3 + 4) == 0x408ab0) {
    puVar2[1] = 0x408ab0;
    puVar2[3] = 4;
  }
  else if (*(int *)(iVar3 + 4) == 0x408840) {
    puVar2[1] = 0x408840;
    puVar2[3] = 2;
  }
  else {
    func_0x0f801150(0x100036b4,0x10000d4c);
    func_0x0040d3c0(0xffffffff);
  }
  puVar4 = (undefined4 *)func_0x00404460();
  *puVar4 = 0;
  local_18[0] = (undefined4 *)0x0;
  iVar3 = func_0x0040a8e0(param_1);
  puVar1 = puVar4;
  while (iVar3 != 0) {
    if (*(int *)(iVar3 + 4) == 0x408ab0) {
      func_0x0040493c(*(undefined4 *)(iVar3 + 8),puVar1,local_18,param_2);
    }
    else if (*(int *)(iVar3 + 4) == 0x408840) {
      func_0x00404a4c(*(undefined4 *)(iVar3 + 8),puVar1,local_18,param_2);
    }
    else {
      func_0x0f801150(0x100036b4,0x10000d80);
      func_0x0040d3c0(0xffffffff);
    }
    puVar1 = local_18[0];
    iVar3 = func_0x0040a918(param_1);
  }
  puVar2[2] = *puVar4;
  return local_4;
}



undefined4 * FUN_00004848(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  
  puVar1 = (undefined4 *)func_0x00404460();
  puVar2 = (undefined4 *)func_0x004044f0(*(undefined4 *)(param_1 + 8));
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



int FUN_0000493c(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != (undefined4 *)0x0) {
    do {
      if (param_1[2] == 0x18) {
        if (param_4 == 1) {
          param_2 = func_0x00404848(param_1,param_2);
          iVar1 = iVar1 + 1;
          param_1 = (undefined4 *)*param_1;
        }
        else {
          func_0x004092d4(0x10000de8);
          param_1 = (undefined4 *)*param_1;
        }
      }
      else {
        func_0x0f801150(0x100036b4,0x10000db0);
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  *param_3 = param_2;
  return iVar1;
}



int FUN_00004a4c(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != (undefined4 *)0x0) {
    do {
      if (param_1[2] == 0x10) {
        if (param_4 == 1) {
          param_2 = func_0x00404848(param_1,param_2);
          iVar1 = iVar1 + 1;
          param_1 = (undefined4 *)*param_1;
        }
        else {
          func_0x004092d4(0x10000e48);
          param_1 = (undefined4 *)*param_1;
        }
      }
      else {
        func_0x0f801150(0x100036b4,0x10000e10);
        param_1 = (undefined4 *)*param_1;
      }
    } while (param_1 != (undefined4 *)0x0);
  }
  *param_3 = param_2;
  return iVar1;
}



void FUN_00004b60(undefined4 *param_1,int param_2,undefined4 param_3)

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
  undefined auStack_344 [800];
  undefined4 local_24;
  undefined *local_20;
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
  local_20 = &DAT_00010002;
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
  func_0x0f801250(0x10000e70);
  func_0x0f801250(0x10000e88,local_14);
  func_0x0f801250(0x10000e98,local_8);
  func_0x0f801250(0x10000eb0,local_4);
  iVar4 = func_0x0f801198(&local_24,0x24,1,param_3);
  if (iVar4 != 1) {
    func_0x0f801150(0x100036b4,0x10000ec4,0x10000ed8);
    func_0x0040d3c0(1);
  }
  iVar4 = 0;
  puVar3 = (undefined *)register0x00000074;
  puVar5 = param_1;
  if (0 < local_14) {
    do {
      uVar1 = func_0x0040ade4(*puVar5);
      iVar4 = iVar4 + 1;
      *(undefined4 *)(puVar3 + -0x344) = uVar1;
      puVar3 = puVar3 + 4;
      puVar5 = puVar5 + 1;
    } while (iVar4 < local_14);
  }
  iVar6 = 0;
  iVar4 = func_0x0f801198(auStack_344,4,local_14,param_3);
  if (iVar4 != local_14) {
    func_0x0f801150(0x100036b4,0x10000ef8,0x10000f0c);
    func_0x0040d3c0(1);
  }
  if (0 < local_14) {
    do {
      iVar4 = func_0x0040a8e0(*param_1);
      while (iVar4 != 0) {
        iVar4 = func_0x0f801198(iVar4,0x10,1,param_3);
        if (iVar4 != 1) {
          func_0x0f801150(0x100036b4,0x10000f1c,0x10000f30);
          func_0x0040d3c0(1);
        }
        iVar4 = func_0x0040a918(*param_1);
      }
      iVar6 = iVar6 + 1;
      param_1 = param_1 + 1;
    } while (iVar6 < local_14);
  }
  iVar4 = func_0x0f801198(local_10,0xc,iVar7,param_3);
  if (iVar4 != iVar7) {
    func_0x0f801150(0x100036b4,0x10000f40,0x10000f54);
    func_0x0040d3c0(1);
  }
  iVar4 = func_0x0f801198(local_c,4,iVar2,param_3);
  if (iVar4 != iVar2) {
    func_0x0f801150(0x100036b4,0x10000f64,0x10000f78);
    func_0x0040d3c0(1);
  }
  return;
}



undefined4 * FUN_00004e78(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int **ppiVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int **ppiVar9;
  undefined4 *puVar10;
  undefined4 local_res0;
  int *local_res4;
  int local_358;
  int local_344 [200];
  int local_24;
  undefined *local_20;
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
    func_0x0f801150(0x100036b4,0x10000f88,0x10000f9c);
    func_0x0040d3c0(1);
  }
  if (local_24 == 0x13577531) {
    if (local_20 == &DAT_00010002) {
      if (local_1c == 0x10) {
        if (local_18 == 0xc) {
          if ((local_14 < 1) || (200 < local_14)) {
            func_0x0f801150(0x100036b4,0x1000106c,0x10001080);
            func_0x0040d3c0(1);
          }
          iVar1 = func_0x0f801168(local_344,4,local_14,local_res0);
          if (iVar1 != local_14) {
            func_0x0f801150(0x100036b4,0x100010a0,0x100010b4);
            func_0x0040d3c0(1);
          }
          puVar2 = (undefined4 *)func_0x0f801208(local_14 << 2);
          if (puVar2 == (undefined4 *)0x0) {
            func_0x004092d4(0x100010d8);
          }
          ppiVar3 = (int **)func_0x0f801208(local_8 * 0xc);
          if (ppiVar3 == (int **)0x0) {
            func_0x004092d4(0x100010ec);
          }
          uVar4 = func_0x0f801208(local_4 * 4 + 0xc);
          if (uVar4 == 0) {
            func_0x004092d4(0x10001100);
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
            func_0x0f801150(0x100036b4,0x10001114,uVar4);
          }
          local_358 = 0;
          puVar10 = puVar2;
          if (0 < local_14) {
            do {
              iVar1 = 0;
              uVar6 = func_0x0040a400();
              *puVar10 = uVar6;
              if (0 < *(int *)((int)register0x00000074 + -0x344)) {
                do {
                  iVar7 = func_0x0f801208(0x10);
                  if (iVar7 == 0) {
                    func_0x004092d4(0x10001144);
                  }
                  iVar8 = func_0x0f801168(iVar7,0x10,1,local_res0);
                  if (iVar8 != 1) {
                    func_0x0f801150(0x100036b4,0x10001150,0x10001164);
                    func_0x0040d3c0(1);
                  }
                  iVar8 = (*(int *)(iVar7 + 8) - local_10) / 0xc;
                  if ((iVar8 < 0) || (local_8 <= iVar8)) {
                    func_0x0f801150(0x100036b4,0x10001184,0x10001198);
                    func_0x0040d3c0(1);
                  }
                  *(int ***)(iVar7 + 8) = ppiVar3 + iVar8 * 3;
                  *(undefined4 *)(iVar7 + 4) = 0xffffffff;
                  func_0x0040a6d4(*puVar10,iVar7);
                  iVar1 = iVar1 + 1;
                } while (iVar1 < *(int *)((int)register0x00000074 + -0x344));
              }
              local_358 = local_358 + 1;
              register0x00000074 = (BADSPACEBASE *)((int)register0x00000074 + 4);
              puVar10 = puVar10 + 1;
            } while (local_358 < local_14);
          }
          local_358 = 0;
          iVar1 = func_0x0f801168(ppiVar3,0xc,local_8,local_res0);
          if (iVar1 != local_8) {
            func_0x0f801150(0x100036b4,0x100011bc,0x100011d0);
            func_0x0040d3c0(1);
          }
          iVar1 = func_0x0f801168(uVar4,4,local_4,local_res0);
          if (iVar1 != local_4) {
            func_0x0f801150(0x100036b4,0x100011f4,0x10001208);
            func_0x0040d3c0(1);
          }
          ppiVar9 = ppiVar3;
          if (0 < local_8) {
            do {
              if (*ppiVar9 != (int *)0x0) {
                iVar1 = ((int)*ppiVar9 - local_10) / 0xc;
                if ((iVar1 < 0) || (local_8 <= iVar1)) {
                  func_0x0f801150(0x100036b4,0x10001228,0x1000123c);
                  func_0x0040d3c0(1);
                }
                *ppiVar9 = (int *)(ppiVar3 + iVar1 * 3);
              }
              if (ppiVar9[1] != (int *)0x0) {
                iVar1 = (int)ppiVar9[1] - local_c;
                if (iVar1 < 0) {
                  iVar1 = iVar1 + 3;
                }
                iVar1 = iVar1 >> 2;
                if ((iVar1 < 0) || (local_4 <= iVar1)) {
                  func_0x0f801150(0x100036b4,0x10001260,0x10001274);
                  func_0x0040d3c0(1);
                }
                ppiVar9[1] = (int *)(uVar4 + iVar1 * 4);
              }
              local_358 = local_358 + 1;
              ppiVar9 = ppiVar9 + 3;
            } while (local_358 < local_8);
          }
          *local_res4 = local_14;
        }
        else {
          func_0x0f801150(0x100036b4,0x1000103c);
          puVar2 = (undefined4 *)0x0;
        }
      }
      else {
        func_0x0f801150(0x100036b4,0x10001010);
        puVar2 = (undefined4 *)0x0;
      }
    }
    else {
      func_0x0f801150(0x100036b4,0x10000fe4);
      puVar2 = (undefined4 *)0x0;
    }
  }
  else {
    func_0x0f801150(0x100036b4,0x10000fbc);
    puVar2 = (undefined4 *)0x0;
  }
  return puVar2;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_000054e0(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = func_0x004055d0(&DAT_10001290);
  uVar2 = 0x101;
  if (iVar1 != 0) {
    uVar2 = _DAT_10001290;
  }
  return uVar2;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00005520(undefined4 param_1)

{
  int unaff_gp;
  
  func_0x0f801150(0x100036b4,unaff_gp + -32000,0x10003ed0,param_1);
  func_0x0f801150(0x100036b4,0x100012a0,_DAT_1000129c,_DAT_10001298);
  func_0x0f801150(0x100036b4,0x100012b8,*(undefined4 *)(unaff_gp + -0x7a80));
  return;
}



bool FUN_00005590(void)

{
  int iVar1;
  
  func_0x00405ec4();
  iVar1 = func_0x00409a00();
  return iVar1 == 0;
}



int FUN_000055d0(int *param_1)

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
    local_4 = func_0x004057d4(param_1);
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
      dVar7 = (double)func_0x0040d830(pcVar6,local_18);
      *(float *)(unaff_gp + -0x7a7c) = (float)dVar7;
      if (local_18[0] == param_1[1]) {
        func_0x0f801150(0x100036b4,0x10001430,0x10003ed0,param_1[1],param_1[3],param_1[2]);
      }
      *param_1 = 0x119;
    }
    else {
      uVar5 = func_0x0040dcc0(pcVar6,local_18,0);
      *(undefined4 *)(unaff_gp + -0x7a7c) = uVar5;
      if (local_18[0] == param_1[1]) {
        func_0x0f801150(0x100036b4,0x10001460,0x10003ed0,param_1[1],param_1[3],param_1[2]);
      }
      *param_1 = 0x118;
    }
  }
  else if (iVar3 == 0x121) {
    iVar3 = func_0x00405ce8(param_1[1]);
    if (iVar3 == 0) {
      func_0x0f801150(0x100036b4,0x100013f4,0x10003ed0,param_1[1],param_1[3],param_1[2]);
    }
    else {
      *param_1 = iVar3;
    }
  }
  return local_4;
}



undefined4 FUN_000057d4(undefined4 *param_1)

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
  iVar4 = func_0x00405df8();
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
        func_0x00405dd0(param_1 + 3,param_1 + 2);
      }
      return 1;
    }
    if (0xff < iVar8) {
      func_0x0f801150(0x100036b4,0x10001494,0x100014a8);
      func_0x0040d3c0(1);
    }
    bVar1 = (&DAT_100032e1)[iVar4];
    uVar7 = (undefined)iVar4;
    if ((bVar1 & 3) == 0) {
      if ((bVar1 & 4) == 0) {
        if ((bVar1 & 0x10) == 0) {
          if ((bVar1 & 8) == 0) {
            func_0x00405dd0(param_1 + 3,param_1 + 2);
            func_0x00405ed8(0x10001580);
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
            func_0x00405de8(iVar4);
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
          func_0x00405dd0(param_1 + 3,param_1 + 2);
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
            func_0x00405ed8(0x1000155c);
            return 0;
          }
          iVar4 = func_0x00405df8();
          if (iVar4 != 0x2a) {
            func_0x00405de8(iVar4);
            *param_1 = 0x11f;
            return 1;
          }
          iVar4 = func_0x00405df8();
          if (iVar4 == -1) {
            func_0x00405ed8(0x10001514);
          }
          iVar5 = func_0x00405df8();
          while (iVar5 != -1) {
            if ((iVar4 == 0x2a) && (iVar5 == 0x2f)) {
              *param_1 = 0x122;
              return 1;
            }
            iVar6 = func_0x00405df8();
            iVar4 = iVar5;
            iVar5 = iVar6;
          }
          func_0x00405ed8(0x10001538);
        }
      }
      else if ((bVar2) || (bVar3)) {
        local_110[iVar8] = uVar7;
        iVar8 = iVar8 + 1;
      }
      else {
        iVar8 = 1;
        bVar3 = true;
        func_0x00405dd0(param_1 + 3,param_1 + 2);
        local_110[0] = uVar7;
      }
    }
    else if (bVar2) {
      local_110[iVar8] = uVar7;
      iVar8 = iVar8 + 1;
    }
    else if (bVar3) {
      if ((((bVar1 & 0x80) == 0) && (iVar4 != 0x78)) && (iVar4 != 0x58)) {
        func_0x0f801250(0x100014c8,iVar4,iVar4);
        func_0x00405ed8(0x100014e8);
        return 0;
      }
      local_110[iVar8] = uVar7;
      iVar8 = iVar8 + 1;
    }
    else {
      bVar2 = true;
      iVar8 = 1;
      func_0x00405dd0(param_1 + 3,param_1 + 2);
      local_110[0] = uVar7;
    }
    iVar4 = func_0x00405df8();
  } while( true );
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

int FUN_00005ce8(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  if (_DAT_100012d4 != 0) {
    piVar3 = (int *)&DAT_100012d0;
    do {
      if ((param_1 == *piVar3) || (iVar2 = func_0x0f8012e8(param_1), iVar2 == 0)) {
        return piVar3[1];
      }
      piVar1 = piVar3 + 3;
      piVar3 = piVar3 + 2;
    } while (*piVar1 != 0);
  }
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

uint FUN_00005df8(void)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int unaff_gp;
  
  if (*(int *)(unaff_gp + -0x7c70) == 0) {
    if (_DAT_100041f0 == 0) {
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



void FUN_00005ed8(undefined4 param_1)

{
  func_0x0f801250(0x100015a0,param_1);
  return;
}



void FUN_00005f00(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140);
  if (499999 < iVar1) {
    func_0x0f801150(0x100036b4,0x100015b0,0x100015c4);
    func_0x0040d3c0(1);
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140);
  }
  *(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x108) + iVar1 * 4) = param_1;
  *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140) =
       *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140) + 1;
  return;
}



void FUN_00005f9c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x144);
  if (0 < iVar1) {
    func_0x0f801150(0x100036b4,0x100015d0,0x100015e4);
    func_0x0040d3c0(1);
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



void FUN_00006054(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x148);
  if (24999 < iVar1) {
    func_0x0f801150(0x100036b4,0x100015f0,0x10001604);
    func_0x0040d3c0(1);
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



void FUN_00006110(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_gp;
  
  iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x14c);
  if (399999 < iVar1) {
    func_0x0f801150(0x100036b4,0x10001610,0x10001624);
    func_0x0040d3c0(1);
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



void FUN_000061d0(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
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
  piVar1 = (int *)func_0x0040a8e0(param_1);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x15c);
      if (99 < iVar2) {
        func_0x0f801150(0x100036b4,0x10001654,0x10001668);
        func_0x0040d3c0(1);
        iVar2 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x15c);
      }
      iVar6 = *(int *)(unaff_gp + -0x7e98);
      puVar3 = (undefined4 *)(*(int *)(iVar6 + 0x124) + iVar2 * 0x24);
      puVar4 = &local_24;
      do {
        puVar5 = puVar4 + 3;
        *puVar3 = *puVar4;
        puVar3[1] = puVar4[1];
        puVar3[2] = puVar4[2];
        puVar3 = puVar3 + 3;
        puVar4 = puVar5;
      } while (puVar5 != auStackX_0);
      *(int *)(iVar6 + 0x15c) = *(int *)(iVar6 + 0x15c) + 1;
      return;
    }
    if (*piVar1 - 0x112U < 5) break;
    func_0x0f801250(0x10001630,*piVar1);
    piVar1 = (int *)func_0x0040a918(param_1);
  }
                    // WARNING: Could not emulate address calculation at 0x0000624c
                    // WARNING: Treating indirect jump as call
  (**(code **)((*piVar1 - 0x112U) * 4 + 0x10000000))();
  return;
}



int FUN_000063a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
    func_0x0f801150(0x100036b4,0x10001678,0x1000168c);
    func_0x0040d3c0(1);
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



int FUN_00006468(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
    func_0x0f801150(0x100036b4,0x1000169c,0x100016b0);
    func_0x0040d3c0(1);
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



int FUN_00006524(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
    func_0x0f801150(0x100036b4,0x100016bc,0x100016d0);
    func_0x0040d3c0(1);
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



void FUN_000065e0(undefined4 param_1)

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
  
  iVar1 = func_0x0040ade4(param_1);
  if (iVar1 < 3) {
    func_0x0f801150(0x100036b4,0x100016e0,0x100016f4);
    func_0x0040d3c0(1);
  }
  local_4 = (int *)func_0x0040a8e0(param_1);
  local_8 = (int *)func_0x0040a918(param_1);
  piVar2 = (int *)func_0x0040a918(param_1);
  iVar5 = 0;
  iVar4 = *local_4;
  iVar6 = 0;
  iVar1 = iVar5;
  if ((iVar4 == 0x103) || (iVar7 = iVar6, iVar4 == 0x107)) {
    if (*local_8 != 0x110) {
      func_0x0f801250(0x10001710,
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
  iVar1 = func_0x004067e4(param_1,iVar1,iVar7,&local_1c);
  if (iVar1 == 0) {
    func_0x0f801250(0x1000173c,
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) -
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160);
    if (199999 < iVar1) {
      func_0x0f801150(0x100036b4,0x1000176c,0x10001780);
      func_0x0040d3c0(1);
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



undefined4 FUN_000067e4(undefined4 *param_1,int param_2,int param_3,undefined4 *param_4)

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
    func_0x0f801150(0x100036b4,0x10001790,0x100017a4);
    func_0x0040d3c0(1);
    param_4 = local_res0[3];
  }
  if ((param_2 == 0) && (param_3 == 0)) {
    *param_4 = 0x408748;
  }
  if (param_2 != 0) {
    if (param_2 == 0x103) {
      *param_4 = 0x4089a0;
      param_4[3] = 3;
    }
    else if (param_2 == 0x107) {
      *param_4 = 0x408bf0;
      param_4[3] = 5;
    }
  }
  if (param_3 != 0) {
    if (param_3 == 0x103) {
      *param_4 = 0x408840;
      param_4[3] = 2;
    }
    else if (param_3 == 0x107) {
      *param_4 = 0x408ab0;
      param_4[3] = 4;
    }
  }
  uVar12 = 0;
  local_res0[3] = param_4;
  piVar2 = (int *)func_0x0040a8e0(local_res0[0]);
  puVar3 = local_2008;
  while (piVar2 != (int *)0x0) {
    if (((uVar12 == 0) && (param_2 != 0)) && (param_2 != *piVar2)) {
      func_0x0f801250(0x100017b4,
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
      func_0x0f801250(0x100017e0,
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
      func_0x004092d4(0x10001864,*piVar2,
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x160) -
                      *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x188));
      puVar7 = puVar3;
    }
    uVar12 = uVar12 + 1;
    piVar2 = (int *)func_0x0040a918(local_res0[0]);
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
    func_0x004092d4(0x1000189c);
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
      if (uVar12 == local_4) goto LAB_00006b60;
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
LAB_00006b60:
  local_res0[3][1] = puVar3;
  local_res0[3][2] = local_4;
  return 1;
}



void FUN_00006b90(undefined4 param_1)

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
  
  iVar1 = func_0x0040ade4(param_1);
  if (2 < iVar1) {
    func_0x0f801150(0x100036b4,0x100018b4,0x100018c8);
    func_0x0040d3c0(1);
  }
  piVar2 = (int *)func_0x0040a8e0(param_1);
  iVar1 = *piVar2;
  if ((iVar1 != 0x103) && (iVar1 != 0x107)) {
    if (iVar1 == 0x110) {
      iVar1 = func_0x0040ade4(param_1);
      if (iVar1 != 1) {
        func_0x0f801150(0x100036b4,0x100018e4,0x100018f8);
        func_0x0040d3c0(1);
      }
    }
    else {
      func_0x004092d4(0x10001924,*piVar2,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168));
    }
  }
  iVar1 = func_0x00406d60(param_1,&local_14);
  if (iVar1 == 0) {
    func_0x0f801250(0x10001954,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x168);
    if (3999 < iVar1) {
      func_0x0f801150(0x100036b4,0x10001980,0x10001994);
      func_0x0040d3c0(1);
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



undefined4 FUN_00006d60(undefined4 *param_1,undefined4 *param_2)

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
  piVar1 = (int *)func_0x0040a8e0(param_1);
  iVar8 = *piVar1;
  if (iVar8 == 0x103) {
    *local_res0[1] = 0x408d94;
    local_res0[1][3] = 8;
  }
  else if (iVar8 == 0x107) {
    *local_res0[1] = 0x408e34;
    local_res0[1][3] = 9;
  }
  else if (iVar8 == 0x110) {
    *local_res0[1] = 0x408d00;
  }
  else {
    func_0x004092d4(0x100019a0,*piVar1,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x168));
  }
  piVar2 = (int *)func_0x0040a8e0(local_res0[0]);
  piVar1 = local_14;
  while (piVar2 != (int *)0x0) {
    iVar8 = *piVar2;
    if (iVar8 == 0x103) {
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x140) <= piVar2[1]) {
        func_0x004092d4(0x100019e0,piVar2[1]);
      }
      piVar12 = piVar1 + 1;
      *piVar1 = *(int *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x108) + piVar2[1] * 4);
    }
    else if (iVar8 == 0x107) {
      if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x148) <= piVar2[1]) {
        func_0x004092d4(0x100019f8,piVar2[1]);
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
          func_0x004092d4(0x100019cc,piVar2[1]);
        }
        *piVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x110) + piVar2[1] * 0xc;
        piVar12 = piVar1 + 1;
      }
    }
    piVar2 = (int *)func_0x0040a918(local_res0[0]);
    piVar1 = piVar12;
  }
  iVar8 = (int)piVar1 - (int)local_14;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 3;
  }
  uVar3 = iVar8 >> 2;
  puVar4 = (undefined4 *)func_0x0f801208(uVar3 << 2);
  if (puVar4 == (undefined4 *)0x0) {
    func_0x004092d4(0x10001a48);
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
      if (uVar10 == uVar3) goto LAB_00007048;
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
LAB_00007048:
  local_res0[1][1] = puVar4;
  local_res0[1][2] = uVar3;
  return 1;
}



void FUN_00007068(undefined4 param_1)

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
  
  piVar1 = (int *)func_0x0040a8e0(param_1);
  iVar5 = *piVar1;
  iVar3 = 0;
  iVar6 = 0;
  uVar4 = 0;
  piVar1 = (int *)func_0x0040a8e0(param_1);
  while (piVar1 != (int *)0x0) {
    if (iVar5 == 0x110) {
      iVar3 = iVar3 + 1;
      if (*piVar1 != 0x110) {
        func_0x004092d4(0x10001a5c,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
      }
    }
    else {
      uVar2 = uVar4 & 1;
      if (((int)uVar4 < 0) && (uVar2 != 0)) {
        uVar2 = uVar2 - 2;
      }
      if ((uVar2 == 0) && (iVar6 = iVar6 + 1, iVar5 != *piVar1)) {
        func_0x004092d4(0x10001a88,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
      }
      if ((uVar2 == 1) && (iVar3 = iVar3 + 1, *piVar1 != 0x110)) {
        func_0x004092d4(0x10001ab4,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
      }
    }
    uVar4 = uVar4 + 1;
    piVar1 = (int *)func_0x0040a918(param_1);
  }
  if (((iVar3 < 2) || (0x100 < iVar3)) || ((iVar5 != 0x110 && (iVar3 != iVar6)))) {
    func_0x004092d4(0x10001ae0,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
  }
  iVar3 = func_0x004072ac(param_1,&local_14);
  if (iVar3 == 0) {
    func_0x004092d4(0x10001b0c,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x164));
  }
  iVar3 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x164);
  if (99999 < iVar3) {
    func_0x0f801150(0x100036b4,0x10001b34,0x10001b48);
    func_0x0040d3c0(1);
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



undefined4 FUN_000072ac(undefined4 param_1,undefined4 *param_2)

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
  piVar2 = (int *)func_0x0040a8e0(param_1);
  iVar6 = *piVar2;
  if (iVar6 == 0x103) {
    *local_res4 = 0x408f64;
    local_res4[3] = 6;
  }
  else if (iVar6 == 0x107) {
    *local_res4 = 0x4090fc;
    local_res4[3] = 7;
  }
  else if (iVar6 == 0x110) {
    *local_res4 = 0x408ed0;
  }
  piVar2 = (int *)func_0x0040a8e0(param_1);
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
    piVar2 = (int *)func_0x0040a918(param_1);
    puVar3 = puVar7;
  }
  iVar6 = (int)puVar3 - (int)local_1008;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 3;
  }
  local_4 = iVar6 >> 2;
  puVar3 = (undefined4 *)func_0x0f801208(local_4 << 2);
  if (puVar3 == (undefined4 *)0x0) {
    func_0x004092d4(0x10001bac);
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
      if (uVar8 == local_4) goto LAB_000074dc;
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
LAB_000074dc:
  local_res4[1] = puVar3;
  local_res4[2] = local_4;
  return 1;
}



undefined4 FUN_000074fc(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 uVar3;
  
  uVar1 = func_0x0040a400();
  piVar2 = (int *)func_0x0040a8e0(param_1);
  if (piVar2 == (int *)0x0) {
    uVar3 = 1;
    *param_2 = uVar1;
  }
  else {
    if (*piVar2 - 0x104U < 0xe) {
                    // WARNING: Could not emulate address calculation at 0x00007584
                    // WARNING: Treating indirect jump as call
      uVar1 = (**(code **)((*piVar2 - 0x104U) * 4 + 0x10000014))();
      return uVar1;
    }
    func_0x0f801250(0x10001c70,*piVar2);
    uVar3 = 0;
  }
  return uVar3;
}



void FUN_00007a8c(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  undefined4 local_4;
  
  iVar1 = func_0x004074fc(param_1,&local_4);
  if (iVar1 == 0) {
    func_0x0f801250(0x10001c98,
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) -
                    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x194));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170);
    if (99 < iVar1) {
      func_0x0f801150(0x100036b4,0x10001cc4,0x10001cd8);
      func_0x0040d3c0(1);
      iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170);
    }
    *(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x138) + iVar1 * 4) = local_4;
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x170) + 1;
  }
  return;
}



void FUN_00007b6c(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  undefined4 local_4;
  
  iVar1 = func_0x004074fc(param_1,&local_4);
  if (iVar1 == 0) {
    func_0x0f801250(0x10001ce4,*(undefined4 *)(*(int *)(unaff_gp + -0x7e98) + 0x174));
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) + 1;
  }
  else {
    iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174);
    if (199 < iVar1) {
      func_0x0f801150(0x100036b4,0x10001d14,0x10001d28);
      func_0x0040d3c0(1);
      iVar1 = *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174);
    }
    *(undefined4 *)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0x13c) + iVar1 * 4) = local_4;
    *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) =
         *(int *)(*(int *)(unaff_gp + -0x7e98) + 0x174) + 1;
  }
  return;
}



int * FUN_00007c44(int param_1,int param_2)

{
  int *piVar1;
  int unaff_gp;
  
  piVar1 = (int *)func_0x0f801208(0xc);
  if (piVar1 == (int *)0x0) {
    func_0x004092d4(unaff_gp + -0x7c60);
  }
  if (param_1 - 0x103U < 0xf) {
                    // WARNING: Could not emulate address calculation at 0x00007ca0
                    // WARNING: Treating indirect jump as call
    piVar1 = (int *)(**(code **)((param_1 - 0x103U) * 4 + 0x1000004c))();
    return piVar1;
  }
  func_0x0f801150(0x100036b4,0x10001e14,param_1,param_2);
  piVar1[1] = param_2;
  *piVar1 = param_1;
  return piVar1;
}



void FUN_00008074(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = func_0x0040a8e0(param_1);
  while (iVar1 != 0) {
    func_0x0f801200(iVar1);
    iVar1 = func_0x0040a918(param_1);
  }
  func_0x0040a48c(param_1);
  return;
}



undefined4 * FUN_000080c4(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)func_0x0f801208(0x10);
  if (puVar1 == (undefined4 *)0x0) {
    func_0x004092d4(0x10001e3c);
  }
  *puVar1 = param_1;
  puVar1[1] = param_2;
  return puVar1;
}



undefined4 *
FUN_00008124(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)func_0x0f801208(0x10);
  if (puVar1 == (undefined4 *)0x0) {
    func_0x004092d4(0x10001e48);
  }
  *puVar1 = param_1;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = param_4;
  return puVar1;
}



void FUN_000081a4(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = func_0x0040a8e0(param_1);
  while (iVar1 != 0) {
    func_0x0f801200(iVar1);
    iVar1 = func_0x0040a918(param_1);
  }
  func_0x0040a48c(param_1);
  return;
}



void FUN_00008200(void)

{
  undefined4 *puVar1;
  int unaff_gp;
  
  puVar1 = (undefined4 *)func_0x0f801208(0x28);
  if (puVar1 == (undefined4 *)0x0) {
    func_0x004092d4(0x10001e60);
  }
  *puVar1 = 0xffffffff;
  puVar1[1] = 0x408748;
  puVar1[2] = 0x408840;
  puVar1[3] = 0x4089a0;
  puVar1[4] = 0x408ab0;
  puVar1[5] = 0x408bf0;
  if (*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xb8) == 0) {
    puVar1[6] = 0x408f64;
  }
  else {
    puVar1[6] = 0x409030;
  }
  puVar1[7] = 0x4090fc;
  puVar1[8] = 0x408d94;
  puVar1[9] = 0x408e34;
  *(undefined4 **)(*(int *)(unaff_gp + -0x7e98) + 0xb4) = puVar1;
  return;
}



void FUN_000082e8(void)

{
  func_0x00408308();
  return;
}



void FUN_00008308(undefined4 param_1)

{
  int iVar1;
  int unaff_gp;
  
  func_0x0f402230();
  iVar1 = func_0x0040a8e0(param_1);
  while (iVar1 != 0) {
    if ((*(uint *)(iVar1 + 0xc) == 0xffffffff) || (9 < *(uint *)(iVar1 + 0xc))) {
      func_0x0f801150(0x100036b4,0x10001e78,0x10001e8c);
      func_0x0040d3c0(1);
    }
    (**(code **)(*(int *)(*(int *)(unaff_gp + -0x7e98) + 0xb4) + *(int *)(iVar1 + 0xc) * 4))
              (*(undefined4 *)(iVar1 + 8));
    iVar1 = func_0x0040a918(param_1);
  }
  func_0x0f402228();
  return;
}



void FUN_000083f0(float *param_1)

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



void FUN_00008608(undefined4 *param_1)

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
    func_0x004092d4(0x10001ea8);
  }
  return;
}



void FUN_000086f0(undefined4 *param_1,undefined4 param_2)

{
  func_0x0f402278(*param_1,param_1[1],param_1,param_2,param_1[2]);
  return;
}



void FUN_0000871c(undefined4 *param_1,undefined4 param_2)

{
  func_0x0f402298(*param_1,param_1[1],param_1,param_2,param_1[2]);
  return;
}



void FUN_00008748(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  func_0x004034b8(0);
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



void FUN_00008840(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  func_0x004034b8(0);
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



void FUN_000089a0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  func_0x004034b8(0);
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



void FUN_00008ab0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  func_0x004034b8(1);
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



void FUN_00008bf0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  func_0x004034b8(1);
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



void FUN_00008d00(int *param_1)

{
  int iVar1;
  int iVar2;
  
  func_0x004034b8(0);
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



void FUN_00008d94(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  func_0x004034b8(0);
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



void FUN_00008e34(int *param_1)

{
  int iVar1;
  int iVar2;
  
  func_0x004034b8(1);
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



void FUN_00008ed0(int *param_1)

{
  int iVar1;
  int iVar2;
  
  func_0x004034b8(0);
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



void FUN_00008f64(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  func_0x004034b8(0);
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



void FUN_00009030(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  func_0x004034b8(0);
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



void FUN_000090fc(int *param_1)

{
  int iVar1;
  int iVar2;
  
  func_0x004034b8(1);
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



undefined4 FUN_000091e0(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar3;
  undefined4 uVar2;
  
  if ((param_1 == (byte *)0x0) || (param_2 == (byte *)0x0)) {
    func_0x0f801150(0x100036b4,0x10001ee0,0x10001ef4);
    func_0x0040d3c0(1);
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



void FUN_000092d4(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

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
  func_0x0f801150(0x100036b4,&DAT_100047f0);
  func_0x0040d3c0(1);
  return;
}



int * FUN_0000948c(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  piVar1 = (int *)func_0x0f801208(param_1 << 2);
  if (piVar1 == (int *)0x0) {
    func_0x004092d4(0x10001f10,param_4);
  }
  iVar4 = 0;
  if (0 < param_1) {
    piVar3 = piVar1;
    do {
      iVar2 = func_0x0f801208(param_2 * param_3);
      *piVar3 = iVar2;
      if (iVar2 == 0) {
        func_0x004092d4(0x10001f20,param_4);
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar4 != param_1);
  }
  return piVar1;
}



void FUN_00009558(undefined4 *param_1,int param_2)

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



void FUN_00009778(char *param_1)

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
    func_0x0f801250(0x10001f30,param_1);
    iVar2 = func_0x0040ae50(param_1,unaff_gp + -0x7c40,0x101,3,**(undefined4 **)(unaff_gp + -0x7e98)
                            ,(*(undefined4 **)(unaff_gp + -0x7e98))[1],3);
    if (iVar2 == 0) {
      func_0x0f801150(0x100036b4,0x10001f50,param_1);
      func_0x0040d3c0(1);
    }
    iVar3 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 2);
    iVar4 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 1);
    iVar5 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 1);
    iVar6 = func_0x0f801208((uint)*(ushort *)(iVar2 + 6) << 1);
    if ((((iVar3 == 0) || (iVar4 == 0)) || (iVar5 == 0)) || (iVar6 == 0)) {
      func_0x0f801150(0x100036b4,0x10001f78);
      func_0x0040d3c0(1);
    }
    if (*(short *)(iVar2 + 10) != 3) {
      func_0x0f801150(0x100036b4,0x10001f94,0x10001fa8);
      func_0x0040d3c0(1);
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
        func_0x00409610(iVar3,iVar4,iVar5,iVar6,(uint)*(ushort *)(iVar2 + 6));
        func_0x0040b6e0(iVar2,iVar4,uVar8,0);
        func_0x0040b6e0(iVar2,iVar5,uVar8,1);
        func_0x0040b6e0(iVar2,iVar6,uVar8,2);
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(ushort *)(iVar2 + 8));
    }
    if (bVar1) {
      func_0x0f801150(0x100036b4,0x10001fc8,local_2c);
    }
    func_0x0040bee0(iVar2);
    func_0x0f801200(iVar3);
    func_0x0f801200(iVar4);
    func_0x0f801200(iVar5);
    func_0x0f801200(iVar6);
  }
  return;
}



int * FUN_0000a400(void)

{
  int *piVar1;
  int iVar2;
  int unaff_gp;
  
  piVar1 = (int *)func_0x0f801208(0xc);
  if (piVar1 == (int *)0x0) {
    func_0x004092d4(*(undefined4 *)(unaff_gp + -0x7c30));
  }
  piVar1[1] = 0;
  piVar1[2] = 0;
  iVar2 = func_0x0f801208(0x10);
  if (iVar2 == 0) {
    func_0x004092d4(*(undefined4 *)(unaff_gp + -0x7c30));
  }
  *(int *)iVar2 = iVar2;
  *(int *)(iVar2 + 4) = iVar2;
  *(undefined4 *)(iVar2 + 8) = 0;
  *(undefined4 *)(iVar2 + 0xc) = 0;
  *piVar1 = iVar2;
  return piVar1;
}



void FUN_0000a48c(int **param_1)

{
  int **ppiVar1;
  int **ppiVar2;
  int *piVar3;
  
  piVar3 = *param_1;
  ppiVar1 = (int **)0;
  for (ppiVar2 = (int **)*piVar3; ppiVar2 != (int **)piVar3; ppiVar2 = (int **)*ppiVar2) {
    if (ppiVar1 != (int **)0x0) {
      if (*(int *)((int)ppiVar1 + 0xc) == -1) {
        func_0x0040a48c(*(undefined4 *)((int)ppiVar1 + 8));
      }
      func_0x0f801200(ppiVar1);
    }
    ppiVar1 = ppiVar2;
  }
  if (ppiVar1 != (int **)0x0) {
    if (*(int *)((int)ppiVar1 + 0xc) == -1) {
      func_0x0040a48c(*(undefined4 *)((int)ppiVar1 + 8));
    }
    func_0x0f801200(ppiVar1);
  }
  func_0x0f801200(piVar3);
  func_0x0f801200(param_1);
  return;
}



void FUN_0000a570(int **param_1,int param_2)

{
  int *piVar1;
  int **ppiVar2;
  int *piVar3;
  int unaff_gp;
  
  ppiVar2 = (int **)*param_1;
  piVar3 = *ppiVar2;
  piVar1 = (int *)func_0x0040adf0(*(undefined4 *)(unaff_gp + -0x7c20),0x10);
  piVar1[3] = 0;
  piVar1[1] = (int)ppiVar2;
  *piVar1 = (int)piVar3;
  piVar1[2] = param_2;
  *ppiVar2 = piVar1;
  piVar3[1] = (int)piVar1;
  param_1[2] = (int *)((int)param_1[2] + 1);
  return;
}



undefined4 FUN_0000a5e8(int **param_1,int param_2,uint param_3)

{
  int *piVar1;
  uint uVar2;
  int **ppiVar3;
  int *piVar4;
  int unaff_gp;
  
  if ((int)param_1[2] < (int)param_3) {
    return 0;
  }
  ppiVar3 = (int **)*param_1;
  uVar2 = 0;
  if (0 < (int)param_3) {
    if ((param_3 & 3) != 0) {
      do {
        ppiVar3 = (int **)*ppiVar3;
        uVar2 = uVar2 + 1;
      } while ((param_3 & 3) != uVar2);
      if (uVar2 == param_3) goto LAB_0000a66c;
    }
    do {
      uVar2 = uVar2 + 4;
      ppiVar3 = (int **)**(int ***)**ppiVar3;
    } while (uVar2 != param_3);
  }
LAB_0000a66c:
  piVar4 = *ppiVar3;
  piVar1 = (int *)func_0x0040adf0(*(undefined4 *)(unaff_gp + -0x7c1c),0x10);
  piVar1[3] = 0;
  piVar1[1] = (int)ppiVar3;
  *piVar1 = (int)piVar4;
  piVar1[2] = param_2;
  *ppiVar3 = piVar1;
  piVar4[1] = (int)piVar1;
  param_1[2] = (int *)((int)param_1[2] + 1);
  return 1;
}



void FUN_0000a6d4(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int **ppiVar3;
  int unaff_gp;
  
  iVar2 = *param_1;
  ppiVar3 = *(int ***)(iVar2 + 4);
  piVar1 = (int *)func_0x0040adf0(*(undefined4 *)(unaff_gp + -0x7c18),0x10);
  piVar1[3] = 0;
  *piVar1 = iVar2;
  piVar1[1] = (int)ppiVar3;
  piVar1[2] = param_2;
  *ppiVar3 = piVar1;
  *(int **)(iVar2 + 4) = piVar1;
  param_1[2] = param_1[2] + 1;
  return;
}



undefined4 FUN_0000a74c(int **param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int **ppiVar3;
  int iVar4;
  
  piVar1 = *param_1;
  ppiVar3 = (int **)*piVar1;
  piVar1[2] = param_2;
  iVar4 = ((int *)ppiVar3)[2];
  while (param_2 != iVar4) {
    ppiVar3 = (int **)*ppiVar3;
    iVar4 = ((int *)ppiVar3)[2];
  }
  uVar2 = 0;
  if (ppiVar3 != (int **)piVar1) {
    piVar1 = ppiVar3[1];
    iVar4 = (int)*ppiVar3;
    *piVar1 = iVar4;
    *(int **)(iVar4 + 4) = piVar1;
    if (ppiVar3 == (int **)param_1[1]) {
      param_1[1] = (int *)0x0;
    }
    func_0x0f801200(ppiVar3);
    uVar2 = 1;
    param_1[2] = (int *)((int)param_1[2] + -1);
  }
  return uVar2;
}



undefined4 FUN_0000a7fc(int **param_1,uint param_2)

{
  uint uVar1;
  int **ppiVar2;
  int *piVar3;
  int **ppiVar4;
  
  if (((int)param_2 < 1) || ((int)param_1[2] < (int)param_2)) {
    return 0;
  }
  ppiVar4 = (int **)*param_1;
  uVar1 = 0;
  if (0 < (int)param_2) {
    if ((param_2 & 3) != 0) {
      do {
        ppiVar4 = (int **)*ppiVar4;
        uVar1 = uVar1 + 1;
      } while ((param_2 & 3) != uVar1);
      if (uVar1 == param_2) goto LAB_0000a87c;
    }
    do {
      uVar1 = uVar1 + 4;
      ppiVar4 = (int **)**(int ***)**ppiVar4;
    } while (uVar1 != param_2);
  }
LAB_0000a87c:
  ppiVar2 = (int **)ppiVar4[1];
  piVar3 = *ppiVar4;
  *ppiVar2 = piVar3;
  piVar3[1] = (int)ppiVar2;
  if (ppiVar4 == (int **)param_1[1]) {
    param_1[1] = (int *)0x0;
  }
  func_0x0f801200();
  param_1[2] = (int *)((int)param_1[2] + -1);
  return 1;
}



undefined4 FUN_0000aa70(int **param_1)

{
  undefined4 uVar1;
  int **ppiVar2;
  int *piVar3;
  
  uVar1 = func_0x0040a400();
  piVar3 = *param_1;
  for (ppiVar2 = (int **)*piVar3; ppiVar2 != (int **)piVar3; ppiVar2 = (int **)*ppiVar2) {
    func_0x0040a6d4(uVar1,ppiVar2[2]);
  }
  return uVar1;
}



undefined4 FUN_0000aae4(int **param_1)

{
  undefined4 uVar1;
  int **ppiVar2;
  int *piVar3;
  
  uVar1 = func_0x0040a400();
  piVar3 = *param_1;
  for (ppiVar2 = (int **)*piVar3; ppiVar2 != (int **)piVar3; ppiVar2 = (int **)*ppiVar2) {
    func_0x0040a570(uVar1,ppiVar2[2]);
  }
  return uVar1;
}



undefined4 FUN_0000ab58(int **param_1,int **param_2)

{
  undefined4 uVar1;
  int **ppiVar2;
  int *piVar3;
  
  uVar1 = func_0x0040a400();
  piVar3 = *param_1;
  for (ppiVar2 = (int **)*piVar3; ppiVar2 != (int **)piVar3; ppiVar2 = (int **)*ppiVar2) {
    func_0x0040a6d4(uVar1,ppiVar2[2]);
  }
  piVar3 = *param_2;
  for (ppiVar2 = (int **)*piVar3; ppiVar2 != (int **)piVar3; ppiVar2 = (int **)*ppiVar2) {
    func_0x0040a6d4(uVar1,ppiVar2[2]);
  }
  return uVar1;
}



void FUN_0000ac0c(int **param_1,code *param_2)

{
  int **ppiVar1;
  int *piVar2;
  
  piVar2 = *param_1;
  for (ppiVar1 = (int **)*piVar2; ppiVar1 != (int **)piVar2; ppiVar1 = (int **)*ppiVar1) {
    (*param_2)(ppiVar1[2]);
  }
  return;
}



int FUN_0000ac6c(int **param_1,int param_2,code *param_3)

{
  int iVar1;
  int *piVar2;
  int **ppiVar3;
  int unaff_gp;
  
  iVar1 = (*param_3)(param_2,param_2);
  if (iVar1 == 0) {
    func_0x0f801150(0x100036b4,0x10002e80,*(undefined4 *)(unaff_gp + -0x7c10),0x10002e90);
  }
  else {
    piVar2 = *param_1;
    ppiVar3 = (int **)*piVar2;
    piVar2[2] = param_2;
    iVar1 = (*param_3)(param_2,((int *)ppiVar3)[2]);
    while (iVar1 == 0) {
      ppiVar3 = (int **)*ppiVar3;
      iVar1 = (*param_3)(param_2,((int *)ppiVar3)[2]);
    }
    if (ppiVar3 != (int **)piVar2) {
      return (int)ppiVar3[2];
    }
  }
  return 0;
}



int * FUN_0000ad48(undefined4 *param_1,undefined4 param_2,code *param_3)

{
  int iVar1;
  int *piVar2;
  int **ppiVar3;
  int **ppiVar4;
  
  ppiVar4 = (int **)*param_1;
  ppiVar3 = (int **)*ppiVar4;
  if (ppiVar3 != ppiVar4) {
    iVar1 = (*param_3)(param_2,ppiVar3[2]);
    while ((iVar1 == 0 && (ppiVar3 = (int **)*ppiVar3, ppiVar3 != ppiVar4))) {
      iVar1 = (*param_3)(param_2,ppiVar3[2]);
    }
  }
  piVar2 = (int *)0x0;
  if (ppiVar3 != ppiVar4) {
    piVar2 = ppiVar3[2];
  }
  return piVar2;
}



int FUN_0000adf0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = func_0x0f801208(param_2);
  if (iVar1 == 0) {
    func_0x0f801150(0x100036b4,0x10002fc0,param_1,0x10002fd0);
  }
  return iVar1;
}



void FUN_0000ae50(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  func_0x0040aef8(0,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}



void FUN_0000aea8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  func_0x0040aef8(param_1,0,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}



ushort * FUN_0000aef8(int param_1,int param_2,char *param_3,ushort param_4,uint param_5,
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
    func_0x0040b640(0x10002fe0);
    return (ushort *)0x0;
  }
  local_res0 = param_1;
  if (*param_3 == 'w') {
    if (((param_2 != 0) && (local_res0 = func_0x0040df80(param_2,0x1b6), bVar3)) &&
       (-1 < local_res0)) {
      func_0x0040dfa0(local_res0);
      local_res0 = func_0x0040dfc0(param_2,2);
    }
    if (local_res0 < 0) {
      func_0x0040b640(0x10003008,param_2);
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
    *(undefined4 *)(puVar4 + 6) = 10000000;
    *(undefined4 *)(puVar4 + 8) = 0;
    func_0x0040c180(puVar4,unaff_gp + -0x7c00);
    *(undefined4 *)(puVar4 + 10) = 0;
    puVar4[0x39] = 0;
    iVar5 = func_0x0040dfe0(local_res0,puVar4,0x98);
    if (iVar5 != 0x98) {
      func_0x0040b640(0x1000302c);
      return (ushort *)0x0;
    }
  }
  else {
    if (param_2 != 0) {
      uVar6 = 0;
      if (bVar3) {
        uVar6 = 2;
      }
      local_res0 = func_0x0040dfc0(param_2,uVar6);
    }
    if (local_res0 < 0) {
      return (ushort *)0x0;
    }
    iVar5 = func_0x0040e000(local_res0,puVar4,0x98);
    if (iVar5 != 0x98) {
      func_0x0040b640(0x10003054);
      return (ushort *)0x0;
    }
    if (((uint)(*puVar4 >> 8) | (*puVar4 & 0xff) << 8) == 0x1da) {
      puVar4[0x39] = 1;
      func_0x0040b5f8(puVar4);
      uVar1 = *puVar4;
    }
    else {
      puVar4[0x39] = 0;
      uVar1 = *puVar4;
    }
    if (uVar1 != 0x1da) {
      func_0x0040b640(0x1000307c);
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
      func_0x0040b640(0x100030a0);
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
          if (uVar7 == uVar9) goto LAB_0000b480;
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
        goto LAB_0000b484;
      }
    }
    else {
      iVar8 = (uint)puVar4[4] * (uint)puVar4[5] * 4;
      func_0x0040e020(local_res0,0x200,0);
      iVar5 = func_0x0040e000(local_res0,*(undefined4 *)(puVar4 + 0x48),iVar8);
      if (iVar5 != iVar8) {
        func_0x0040b640(0x100030c0);
        return (ushort *)0x0;
      }
      if (puVar4[0x39] != 0) {
        func_0x0040b594(*(undefined4 *)(puVar4 + 0x48),iVar8);
      }
      iVar5 = func_0x0040e000(local_res0,*(undefined4 *)(puVar4 + 0x4a),iVar8);
      if (iVar5 != iVar8) {
        func_0x0040b640(0x100030e4);
        return (ushort *)0x0;
      }
      if (puVar4[0x39] != 0) {
        func_0x0040b594(*(undefined4 *)(puVar4 + 0x4a),iVar8);
      }
    }
  }
LAB_0000b480:
  puVar4[0x3d] = 0;
LAB_0000b484:
  *(undefined4 *)(puVar4 + 0x3e) = 0;
  *(undefined4 *)(puVar4 + 0x40) = 0;
  iVar5 = func_0x0040b4f0(puVar4);
  *(int *)(puVar4 + 0x42) = iVar5;
  if (iVar5 == 0) {
    func_0x0040b640(0x10003108,puVar4[3]);
    puVar4 = (ushort *)0x0;
  }
  else {
    puVar4[0x3a] = 0;
    puVar4[0x3b] = 0;
    puVar4[0x3c] = 0;
    *(undefined4 *)(puVar4 + 0x44) = 0x200;
    *(int *)(puVar4 + 0x36) = local_res0;
    func_0x0040e020(local_res0,0x200,0);
  }
  return puVar4;
}



void FUN_0000b4f0(int param_1)

{
  func_0x0f801208(((uint)*(ushort *)(param_1 + 6) + (uint)(*(ushort *)(param_1 + 6) >> 6)) * 4);
  return;
}



void FUN_0000b5f8(int param_1)

{
  func_0x0040b550(param_1,0xc);
  func_0x0040b594(param_1 + 0xc,0xc);
  func_0x0040b594(param_1 + 0x68,4);
  return;
}



void FUN_0000b640(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int unaff_gp;
  undefined auStack_800 [2048];
  
  if (*(int *)(unaff_gp + -0x7ab0) == 0) {
    func_0x0f801150(0x100036b4,param_1,param_2,param_3,param_4,param_5);
    func_0x0040d3c0(1);
  }
  else {
    func_0x0f8012c0(auStack_800,param_1,param_2,param_3,param_4,param_5);
    (**(code **)(unaff_gp + -0x7ab0))(auStack_800);
  }
  return;
}



uint FUN_0000b6e0(int param_1,ushort *param_2,undefined4 param_3,undefined4 param_4)

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
        func_0x0040c1b0(param_1,param_3,param_4);
        uVar2 = (uint)*(ushort *)(param_1 + 6);
        uVar7 = func_0x0040c3fc(param_1,*(undefined4 *)(param_1 + 0x84),uVar2);
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
        func_0x0040c1b0(param_1,param_3,param_4);
        iVar9 = (uint)*(ushort *)(param_1 + 6) << 1;
        if (*(short *)(param_1 + 0x72) != 0) {
          func_0x0040b550(param_2,iVar9);
        }
        iVar4 = func_0x0040c3fc(param_1,param_2,iVar9);
        if (iVar4 == iVar9) {
          if (*(short *)(param_1 + 0x72) != 0) {
            func_0x0040b550(param_2);
          }
          uVar2 = (uint)*(ushort *)(param_1 + 6);
        }
        else {
          if (*(short *)(param_1 + 0x72) != 0) {
            func_0x0040b550(param_2);
          }
          uVar2 = 0xffffffff;
        }
      }
      else {
        uVar2 = func_0x0040b640(0x10003130);
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
        iVar9 = func_0x0040c6a8(param_2,2,*(undefined4 *)(param_1 + 0x84),1,
                                (uint)*(ushort *)(param_1 + 6));
        func_0x0040c590(param_1,iVar9,param_3,param_4);
        func_0x0040c1b0(param_1,param_3,param_4);
        iVar4 = func_0x0040c3fc(param_1,*(undefined4 *)(param_1 + 0x84),iVar9);
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
        iVar9 = func_0x0040c6a8(param_2,2,*(undefined4 *)(param_1 + 0x84),2,
                                (uint)*(ushort *)(param_1 + 6));
        iVar9 = iVar9 << 1;
        func_0x0040c590(param_1,iVar9,param_3,param_4);
        func_0x0040c1b0(param_1,param_3,param_4);
        if (*(short *)(param_1 + 0x72) != 0) {
          func_0x0040b550(*(undefined4 *)(param_1 + 0x84),iVar9);
        }
        iVar4 = func_0x0040c3fc(param_1,*(undefined4 *)(param_1 + 0x84),iVar9);
        if (iVar4 == iVar9) {
          if (*(short *)(param_1 + 0x72) != 0) {
            func_0x0040b550(*(undefined4 *)(param_1 + 0x84),iVar9);
          }
          uVar2 = (uint)*(ushort *)(param_1 + 6);
        }
        else {
          if (*(short *)(param_1 + 0x72) != 0) {
            func_0x0040b550(*(undefined4 *)(param_1 + 0x84),iVar9);
          }
          uVar2 = 0xffffffff;
        }
      }
      else {
        uVar2 = func_0x0040b640(0x10003144);
      }
    }
    else {
      uVar2 = func_0x0040b640(0x10003158);
    }
  }
  return uVar2;
}



uint FUN_0000bbd8(int param_1,ushort *param_2,undefined4 param_3,undefined4 param_4)

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
    func_0x0040c1b0(param_1,param_3,param_4);
    uVar2 = *(ushort *)(param_1 + 2);
    if ((uVar2 & 0xff00) == 0) {
      if ((uVar2 & 0xff) == 1) {
        uVar4 = func_0x0040c454(param_1,*(undefined4 *)(param_1 + 0x84),*(undefined2 *)(param_1 + 6)
                               );
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
        iVar5 = func_0x0040c454(param_1,param_2,iVar8 >> 0x10);
        iVar8 = (int)(short)((uint)iVar8 >> 0x10);
        if (iVar5 == iVar8) {
          if (*(short *)(param_1 + 0x72) != 0) {
            func_0x0040b550(param_2,iVar8);
          }
          uVar3 = (uint)*(ushort *)(param_1 + 6);
        }
        else {
          uVar3 = 0xffffffff;
        }
      }
      else {
        uVar3 = func_0x0040b640(0x10003174);
      }
    }
    else if ((uVar2 & 0xff00) == 0x100) {
      if ((uVar2 & 0xff) == 1) {
        sVar6 = func_0x0040c500(param_1);
        if (sVar6 == -1) {
          uVar3 = 0xffffffff;
        }
        else {
          iVar5 = func_0x0040c454(param_1,*(undefined4 *)(param_1 + 0x84),(int)sVar6);
          if (iVar5 == sVar6) {
            func_0x0040ce2c(*(undefined4 *)(param_1 + 0x84),1,param_2,2);
            uVar3 = (uint)*(ushort *)(param_1 + 6);
          }
          else {
            uVar3 = 0xffffffff;
          }
        }
      }
      else if ((uVar2 & 0xff) == 2) {
        sVar6 = func_0x0040c500(param_1);
        if (sVar6 == -1) {
          uVar3 = 0xffffffff;
        }
        else {
          iVar5 = func_0x0040c454(param_1,*(undefined4 *)(param_1 + 0x84),(int)sVar6);
          if (sVar6 == iVar5) {
            if (*(short *)(param_1 + 0x72) != 0) {
              func_0x0040b550(*(undefined4 *)(param_1 + 0x84),(int)sVar6);
            }
            func_0x0040ce2c(*(undefined4 *)(param_1 + 0x84),2,param_2,2);
            uVar3 = (uint)*(ushort *)(param_1 + 6);
          }
          else {
            uVar3 = 0xffffffff;
          }
        }
      }
      else {
        uVar3 = func_0x0040b640(0x10003188);
      }
    }
    else {
      uVar3 = func_0x0040b640(0x1000319c);
    }
  }
  return uVar3;
}



undefined4 FUN_0000bee0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  func_0x0040c0dc(param_1);
  func_0x0040c4ac(param_1,0);
  if ((*(ushort *)(param_1 + 0x70) & 2) != 0) {
    if (*(short *)(param_1 + 0x72) != 0) {
      func_0x0040b5f8(param_1);
    }
    iVar1 = func_0x0040c3fc(param_1,param_1,0x98);
    if (iVar1 != 0x98) {
      func_0x0040b640(0x100031c0);
      return 0xffffffff;
    }
    if (*(short *)(param_1 + 0x72) != 0) {
      func_0x0040b5f8(param_1);
    }
    if ((*(ushort *)(param_1 + 2) & 0xff00) == 0x100) {
      func_0x0040c4ac(param_1,0x200);
      iVar1 = (uint)*(ushort *)(param_1 + 8) * (uint)*(ushort *)(param_1 + 10) * 4;
      if (*(short *)(param_1 + 0x72) != 0) {
        func_0x0040b594(*(undefined4 *)(param_1 + 0x90),iVar1);
      }
      iVar2 = func_0x0040c3fc(param_1,*(undefined4 *)(param_1 + 0x90),iVar1);
      if (iVar2 != iVar1) {
        func_0x0040b640(0x100031e8);
        return 0xffffffff;
      }
      if (*(short *)(param_1 + 0x72) != 0) {
        func_0x0040b594(*(undefined4 *)(param_1 + 0x94),iVar1);
      }
      iVar2 = func_0x0040c3fc(param_1,*(undefined4 *)(param_1 + 0x94),iVar1);
      if (iVar2 != iVar1) {
        func_0x0040b640(0x1000320c);
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
  uVar3 = func_0x0040dfa0(*(undefined4 *)(param_1 + 0x6c));
  return uVar3;
}



void FUN_0000c0dc(int param_1)

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
      uVar1 = func_0x0040b6e0(param_1,iVar2,(int)*(short *)(param_1 + 0x76),
                              (int)*(short *)(param_1 + 0x78));
      if (uVar1 != *(ushort *)(param_1 + 6)) {
        *(ushort *)(param_1 + 0x70) = *(ushort *)(param_1 + 0x70) | 0x20;
      }
    }
  }
  return;
}



void FUN_0000c180(int param_1,undefined4 param_2)

{
  func_0x0f801320(param_1 + 0x18,param_2,0x50);
  return;
}



undefined4 FUN_0000c1b0(int param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  iVar2 = func_0x0040c3c0(param_1,param_2);
  if (iVar2 == 0) {
    uVar4 = (uint)*(ushort *)(param_1 + 2);
    *(undefined2 *)(param_1 + 0x74) = 0;
    *(short *)(param_1 + 0x76) = (short)param_2;
    *(short *)(param_1 + 0x78) = (short)param_3;
    if ((*(ushort *)(param_1 + 2) & 0xff00) == 0) {
      sVar1 = *(short *)(param_1 + 4);
      if (sVar1 == 1) {
        uVar3 = func_0x0040c4ac(param_1,0x200);
      }
      else if (sVar1 == 2) {
        uVar3 = func_0x0040c4ac(param_1,param_2 * (uint)*(ushort *)(param_1 + 6) * (uVar4 & 0xff) +
                                        0x200);
      }
      else if (sVar1 == 3) {
        uVar3 = func_0x0040c4ac(param_1,(param_2 * (uint)*(ushort *)(param_1 + 6) +
                                        param_3 * (uint)*(ushort *)(param_1 + 6) *
                                        (uint)*(ushort *)(param_1 + 8)) * (uVar4 & 0xff) + 0x200);
      }
      else {
        uVar3 = func_0x0040b640(0x10003254);
      }
    }
    else if ((uVar4 & 0xff00) == 0x100) {
      sVar1 = *(short *)(param_1 + 4);
      if (sVar1 == 1) {
        uVar3 = func_0x0040c4ac(param_1,**(undefined4 **)(param_1 + 0x90));
      }
      else if (sVar1 == 2) {
        uVar3 = func_0x0040c4ac(param_1,*(undefined4 *)(*(int *)(param_1 + 0x90) + param_2 * 4));
      }
      else if (sVar1 == 3) {
        uVar3 = func_0x0040c4ac(param_1,*(undefined4 *)
                                         (*(int *)(param_1 + 0x90) +
                                         (param_2 + param_3 * (uint)*(ushort *)(param_1 + 8)) * 4));
      }
      else {
        uVar3 = func_0x0040b640(0x1000326c);
      }
    }
    else {
      uVar3 = func_0x0040b640(0x10003284);
    }
  }
  else {
    func_0x0040b640(0x10003230);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



int FUN_0000c3fc(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = func_0x0040dfe0(*(undefined4 *)(param_1 + 0x6c));
  if (iVar1 == param_3) {
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + param_3;
  }
  else {
    *(undefined4 *)(param_1 + 0x88) = 0xffffffff;
  }
  return iVar1;
}



int FUN_0000c454(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = func_0x0040e000(*(undefined4 *)(param_1 + 0x6c));
  if (iVar1 == param_3) {
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + param_3;
  }
  else {
    *(undefined4 *)(param_1 + 0x88) = 0xffffffff;
  }
  return iVar1;
}



int FUN_0000c4ac(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x88)) {
    *(int *)(param_1 + 0x88) = param_2;
    param_2 = func_0x0040e020(*(undefined4 *)(param_1 + 0x6c),param_2,0);
  }
  return param_2;
}



void FUN_0000c590(int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  int iVar2;
  int *local_4;
  
  iVar2 = func_0x0040c3c0(param_1,param_3,param_4);
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



undefined * FUN_0000c6a8(ushort *param_1,int param_2,ushort *param_3,int param_4,int param_5)

{
  byte *pbVar1;
  ushort *puVar2;
  byte bVar3;
  byte bVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  ushort *puVar13;
  
  if ((param_2 == 1) && (param_4 == 1)) {
    puVar13 = (ushort *)((int)param_1 + param_5);
    puVar10 = param_3;
    if (param_1 < puVar13) {
      do {
        puVar11 = param_1 + 1;
        if ((puVar11 < puVar13) &&
           ((puVar12 = puVar11, *(byte *)((int)param_1 + 1) != *(byte *)param_1 ||
            (*(byte *)puVar11 != *(byte *)((int)param_1 + 1))))) {
          do {
            puVar11 = (ushort *)((int)puVar12 + 1);
            if (puVar13 <= puVar11) break;
            bVar3 = *(byte *)puVar12;
            pbVar1 = (byte *)((int)puVar12 + -1);
            puVar12 = puVar11;
          } while ((bVar3 != *pbVar1) || (*(byte *)puVar11 != bVar3));
        }
        puVar12 = puVar11 + -1;
        iVar7 = (int)puVar12 - (int)param_1;
        while (iVar7 != 0) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          iVar7 = iVar7 - iVar9;
          *(byte *)puVar10 = (byte)iVar9 | 0x80;
          for (; puVar10 = (ushort *)((int)puVar10 + 1), iVar9 != 0;
              iVar9 = (iVar9 + -1) * 0x10000 >> 0x10) {
            bVar3 = *(byte *)param_1;
            param_1 = (ushort *)((int)param_1 + 1);
            *(byte *)puVar10 = bVar3;
          }
        }
        param_1 = (ushort *)((int)puVar11 + -1);
        bVar3 = *(byte *)(puVar11 + -1);
        iVar7 = (int)param_1 - (int)puVar12;
        if (param_1 < puVar13) {
          bVar4 = *(byte *)param_1;
          while ((bVar3 == bVar4 && (param_1 = (ushort *)((int)param_1 + 1), param_1 < puVar13))) {
            bVar4 = *(byte *)param_1;
          }
          iVar7 = (int)param_1 - (int)puVar12;
        }
        for (; iVar7 != 0; iVar7 = iVar7 - iVar9) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          *(char *)puVar10 = (char)iVar9;
          *(byte *)((int)puVar10 + 1) = bVar3;
          puVar10 = puVar10 + 1;
        }
      } while (param_1 < puVar13);
    }
    *(undefined *)puVar10 = 0;
    puVar8 = (undefined *)((int)puVar10 + (1 - (int)param_3));
  }
  else if ((param_2 == 1) && (param_4 == 2)) {
    puVar13 = (ushort *)((int)param_1 + param_5);
    puVar10 = param_3;
    if (param_1 < puVar13) {
      do {
        puVar11 = param_1 + 1;
        if ((puVar11 < puVar13) &&
           ((puVar12 = puVar11, *(byte *)((int)param_1 + 1) != *(byte *)param_1 ||
            (*(byte *)puVar11 != *(byte *)((int)param_1 + 1))))) {
          do {
            puVar11 = (ushort *)((int)puVar12 + 1);
            if (puVar13 <= puVar11) break;
            bVar3 = *(byte *)puVar12;
            pbVar1 = (byte *)((int)puVar12 + -1);
            puVar12 = puVar11;
          } while ((bVar3 != *pbVar1) || (*(byte *)puVar11 != bVar3));
        }
        puVar12 = puVar11 + -1;
        iVar7 = (int)puVar12 - (int)param_1;
        while (iVar7 != 0) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          iVar7 = iVar7 - iVar9;
          *puVar10 = (ushort)iVar9 | 0x80;
          for (; puVar10 = puVar10 + 1, iVar9 != 0; iVar9 = (iVar9 + -1) * 0x10000 >> 0x10) {
            bVar3 = *(byte *)param_1;
            param_1 = (ushort *)((int)param_1 + 1);
            *puVar10 = (ushort)bVar3;
          }
        }
        param_1 = (ushort *)((int)puVar11 + -1);
        bVar3 = *(byte *)(puVar11 + -1);
        iVar7 = (int)param_1 - (int)puVar12;
        if (param_1 < puVar13) {
          bVar4 = *(byte *)param_1;
          while ((bVar3 == bVar4 && (param_1 = (ushort *)((int)param_1 + 1), param_1 < puVar13))) {
            bVar4 = *(byte *)param_1;
          }
          iVar7 = (int)param_1 - (int)puVar12;
        }
        for (; iVar7 != 0; iVar7 = iVar7 - iVar9) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          *puVar10 = (ushort)iVar9;
          puVar10[1] = (ushort)bVar3;
          puVar10 = puVar10 + 2;
        }
      } while (param_1 < puVar13);
    }
    puVar8 = (undefined *)((int)puVar10 + (2 - (int)param_3));
    if ((int)puVar8 < 0) {
      puVar8 = puVar8 + 1;
    }
    puVar8 = (undefined *)((int)puVar8 >> 1);
    *puVar10 = 0;
  }
  else if ((param_2 == 2) && (param_4 == 1)) {
    puVar13 = param_1 + param_5;
    puVar10 = param_3;
    if (param_1 < puVar13) {
      do {
        puVar11 = param_1 + 2;
        if ((puVar11 < puVar13) &&
           ((puVar12 = puVar11, param_1[1] != *param_1 || (*puVar11 != param_1[1])))) {
          do {
            puVar11 = puVar12 + 1;
            if (puVar13 <= puVar11) break;
            uVar5 = *puVar12;
            puVar2 = puVar12 + -1;
            puVar12 = puVar11;
          } while ((uVar5 != *puVar2) || (*puVar11 != uVar5));
        }
        puVar12 = puVar11 + -2;
        iVar7 = (int)puVar12 - (int)param_1;
        if (iVar7 < 0) {
          iVar7 = iVar7 + 1;
        }
        iVar7 = iVar7 >> 1;
        while (iVar7 != 0) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          iVar7 = iVar7 - iVar9;
          *(byte *)puVar10 = (byte)iVar9 | 0x80;
          for (; puVar10 = (ushort *)((int)puVar10 + 1), iVar9 != 0;
              iVar9 = (iVar9 + -1) * 0x10000 >> 0x10) {
            uVar5 = *param_1;
            param_1 = param_1 + 1;
            *(char *)puVar10 = (char)uVar5;
          }
        }
        param_1 = puVar11 + -1;
        uVar5 = puVar11[-2];
        iVar7 = (int)param_1 - (int)puVar12;
        if (param_1 < puVar13) {
          uVar6 = *param_1;
          while (((int)(short)uVar5 == (uint)uVar6 && (param_1 = param_1 + 1, param_1 < puVar13))) {
            uVar6 = *param_1;
          }
          iVar7 = (int)param_1 - (int)puVar12;
        }
        if (iVar7 < 0) {
          iVar7 = iVar7 + 1;
        }
        for (iVar7 = iVar7 >> 1; iVar7 != 0; iVar7 = iVar7 - iVar9) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          *(char *)puVar10 = (char)iVar9;
          *(char *)((int)puVar10 + 1) = (char)uVar5;
          puVar10 = puVar10 + 1;
        }
      } while (param_1 < puVar13);
    }
    *(undefined *)puVar10 = 0;
    puVar8 = (undefined *)((int)puVar10 + (1 - (int)param_3));
  }
  else if ((param_2 == 2) && (param_4 == 2)) {
    puVar13 = param_1 + param_5;
    puVar10 = param_3;
    if (param_1 < puVar13) {
      do {
        puVar11 = param_1 + 2;
        if ((puVar11 < puVar13) &&
           ((puVar12 = puVar11, param_1[1] != *param_1 || (*puVar11 != param_1[1])))) {
          do {
            puVar11 = puVar12 + 1;
            if (puVar13 <= puVar11) break;
            uVar5 = *puVar12;
            puVar2 = puVar12 + -1;
            puVar12 = puVar11;
          } while ((uVar5 != *puVar2) || (*puVar11 != uVar5));
        }
        puVar12 = puVar11 + -2;
        iVar7 = (int)puVar12 - (int)param_1;
        if (iVar7 < 0) {
          iVar7 = iVar7 + 1;
        }
        iVar7 = iVar7 >> 1;
        while (iVar7 != 0) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          iVar7 = iVar7 - iVar9;
          *puVar10 = (ushort)iVar9 | 0x80;
          for (; puVar10 = puVar10 + 1, iVar9 != 0; iVar9 = (iVar9 + -1) * 0x10000 >> 0x10) {
            uVar5 = *param_1;
            param_1 = param_1 + 1;
            *puVar10 = uVar5;
          }
        }
        param_1 = puVar11 + -1;
        uVar5 = puVar11[-2];
        iVar7 = (int)param_1 - (int)puVar12;
        if (param_1 < puVar13) {
          uVar6 = *param_1;
          while (((int)(short)uVar5 == (uint)uVar6 && (param_1 = param_1 + 1, param_1 < puVar13))) {
            uVar6 = *param_1;
          }
          iVar7 = (int)param_1 - (int)puVar12;
        }
        if (iVar7 < 0) {
          iVar7 = iVar7 + 1;
        }
        for (iVar7 = iVar7 >> 1; iVar7 != 0; iVar7 = iVar7 - iVar9) {
          if (iVar7 < 0x7f) {
            iVar9 = (int)(short)iVar7;
          }
          else {
            iVar9 = 0x7e;
          }
          *puVar10 = (ushort)iVar9;
          puVar10[1] = uVar5;
          puVar10 = puVar10 + 2;
        }
      } while (param_1 < puVar13);
    }
    puVar8 = (undefined *)((int)puVar10 + (2 - (int)param_3));
    if ((int)puVar8 < 0) {
      puVar8 = puVar8 + 1;
    }
    puVar8 = (undefined *)((int)puVar8 >> 1);
    *puVar10 = 0;
  }
  else {
    func_0x0040b640(0x100032a0,param_2,param_4);
    puVar8 = (undefined *)0x0;
  }
  return puVar8;
}



void FUN_0000ce2c(ushort *param_1,int param_2,ushort *param_3,int param_4)

{
  byte bVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort uVar4;
  ushort *puVar5;
  
  if ((param_2 != 1) || (param_4 != 1)) {
    if ((param_2 == 1) && (param_4 == 2)) {
LAB_0000cf0c:
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
            if (uVar2 == 0) goto LAB_0000cf0c;
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
LAB_0000cfb8:
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
            if (uVar2 == 0) goto LAB_0000cfb8;
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
      func_0x0040b640(0x100032c0,param_2,param_4);
      return;
    }
LAB_0000d064:
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
          if (uVar2 == 0) goto LAB_0000d064;
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
LAB_0000ce54:
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
        if (uVar2 == 0) goto LAB_0000ce54;
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



undefined4 FUN_0000d2d0(char *param_1)

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
     ((param_1 = (char *)func_0x0f8011b0(0x100034e4), param_1 == (char *)0x0 || (*param_1 == '\0')))
     ) {
    if (*(char *)(unaff_gp + -0x7bf0) != '\0') {
      return 0;
    }
    param_1 = (char *)(unaff_gp + -0x7bec);
  }
  *(undefined *)(unaff_gp + -0x7bf0) = 0;
  func_0x0f8012f0(auStack_80,0x100034f0);
  func_0x0f8012f0(auStack_72,param_1);
  iVar1 = func_0x0040dfc0(auStack_80,0);
  if (-1 < iVar1) {
    iVar2 = func_0x0040e000(iVar1,auStack_284,0x202);
    if (iVar2 == 0x202) {
      func_0x0f801230(&DAT_100032e0,auStack_284,0x202);
      local_28c = 0;
    }
    func_0x0040dfa0(iVar1);
  }
  return local_28c;
}



void FUN_0000d3c0(undefined4 param_1)

{
  func_0x0f8010f8();
  func_0x0040e5c0(param_1);
  return;
}



uint FUN_0000d3f0(int param_1,undefined4 *param_2,undefined4 param_3)

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
            func_0x0040dfe0(2,*param_2,uVar1);
            uVar1 = func_0x0f801308(0x10003ce0);
            func_0x0040dfe0(2,0x10003ce0,uVar1);
            func_0x0040dfe0(2,&local_18,2);
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
    func_0x0040dfe0(2,*param_2,uVar1);
    uVar1 = func_0x0f801308(0x10003d04);
    func_0x0040dfe0(2,0x10003d04,uVar1);
    func_0x0040dfe0(2,&local_10,2);
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



void FUN_0000d720(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_res4;
  undefined4 local_res8;
  undefined4 local_resc;
  
  local_res4 = param_2;
  local_res8 = param_3;
  local_resc = param_4;
  func_0x0040e5d0(0x10003694,param_1,&local_res4);
  return;
}



void FUN_0000d768(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_res8;
  undefined4 local_resc;
  
  local_res8 = param_3;
  local_resc = param_4;
  func_0x0040e5d0(param_1,param_2,&local_res8);
  return;
}



void FUN_0000d7a4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

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
  func_0x0040e5d0(&local_14,param_2,&local_res8);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

double FUN_0000d830(byte *param_1,byte **param_2)

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
  undefined *puVar11;
  int unaff_gp;
  double dVar12;
  double dVar13;
  byte **local_res4;
  byte *pbStack_1c;
  int local_18;
  int local_c;
  
  local_c = 0;
  uVar8 = 0;
  local_18 = 0;
  local_res4 = param_2;
  if (param_2 == (byte **)0x0) {
    local_res4 = &pbStack_1c;
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
LAB_0000d8b8:
    uVar9 = (uint)param_1[1];
    param_1 = param_1 + 1;
  }
  else if (uVar9 == 0x2d) {
    local_c = 1;
    goto LAB_0000d8b8;
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
      goto LAB_0000d920;
    }
  }
  else {
LAB_0000d920:
    param_2 = (byte **)0xccccccc;
    do {
      do {
        if (uVar9 != 0x2e) {
          local_18 = local_18 + 1;
          if (iVar10 != 0) {
            if (uVar9 == 0x30) {
              iVar3 = iVar3 + 1;
              goto LAB_0000da18;
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
LAB_0000da18:
        uVar9 = (uint)*param_1;
        param_1 = param_1 + 1;
        puVar11 = &DAT_100032e0 + uVar9;
      } while (((&DAT_100032e1)[uVar9] & 4) != 0);
      if (uVar9 != 0x2e) goto code_r0x0000da54;
      bVar1 = iVar10 == 0;
      iVar10 = iVar10 + 1;
    } while (bVar1);
    param_2 = (byte **)0xccccccc;
  }
code_r0x0000da54:
  if (local_18 == 0) {
    return 0.0;
  }
  dVar12 = (double)iVar4;
  if (1 < iVar6) {
    dVar12 = (double)iVar6 * dVar12 + (double)iVar7;
  }
  *local_res4 = param_1 + -1;
  if ((puVar11 != (undefined *)0x10003325) && (puVar11 != (undefined *)0x10003345))
  goto LAB_0000db80;
  iVar3 = 0;
  *local_res4 = param_1;
  uVar9 = (uint)*param_1;
  iVar6 = 0;
  if ((uVar9 == 0x20) || (uVar9 == 0x2b)) {
LAB_0000dae0:
    uVar9 = (uint)param_1[1];
    param_1 = param_1 + 1;
  }
  else if (uVar9 == 0x2d) {
    iVar6 = 1;
    goto LAB_0000dae0;
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
LAB_0000db80:
  if (dVar12 != 0.0) {
    if (uVar8 != 0) {
      pdVar5 = (double *)&DAT_10003d20;
      if ((double)CONCAT44(_DAT_10003d20,_DAT_10003d24) == 0.0) {
        _DAT_10003d20 = *(undefined4 *)(unaff_gp + -0x7ef0);
        _DAT_10003d24 = *(undefined4 *)(unaff_gp + -0x7eec);
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



void FUN_0000e040(void)

{
  int iVar1;
  undefined4 uVar2;
  int unaff_gp;
  
  iVar1 = func_0x0040e2b0(6,0);
  if (iVar1 == 0) {
    iVar1 = *(int *)(unaff_gp + -0x7ba0) + 1;
    *(int *)(unaff_gp + -0x7ba0) = iVar1;
    if (iVar1 == 1) {
      func_0x0f8010f8();
    }
  }
  else {
    func_0x0040e2b0(6);
  }
  uVar2 = func_0x0040e270();
  func_0x0040fa10(uVar2,6);
  return;
}



undefined4 * FUN_0000e110(undefined4 param_1,char *param_2)

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
  *(undefined4 *)((uint)*(byte *)((int)puVar2 + 0xd) * 4 + 0x10003500) = 0;
  cVar1 = *param_2;
  if (cVar1 == 'a') {
    func_0x0040e020(param_1,0,2);
  }
  else {
    if (cVar1 == 'r') {
      *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 1;
      goto LAB_0000e1d4;
    }
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
  }
  *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 2;
LAB_0000e1d4:
  if (param_2[1] == '+') {
    *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) & 0xfc;
    *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 0x80;
  }
  return puVar2;
}



void FUN_0000e410(undefined4 param_1,undefined4 param_2)

{
  func_0x0040faa0(0x46d,param_1,param_2);
  return;
}



void FUN_0000e460(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  func_0x0040faa0(0x41c,0,param_1,param_2,param_3);
  return;
}



void FUN_0000e498(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  func_0x0040faa0(0x41c,1,param_1,param_2,param_3);
  return;
}



void FUN_0000e4f4(undefined4 param_1)

{
  func_0x0040faa0(0x41c,2,param_1);
  return;
}



void FUN_0000e51c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  func_0x0040faa0(0x41c,3,param_1,param_2,param_3);
  return;
}



void FUN_0000e580(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  func_0x0040faa0(0x46c,param_1,param_2,param_3);
  return;
}



undefined4 FUN_0000ec04(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 - 100U < 0x15) {
                    // WARNING: Could not emulate address calculation at 0x0000ec58
                    // WARNING: Treating indirect jump as call
    uVar1 = (**(code **)((param_2 - 100U) * 4 + 0x10000160))();
    return uVar1;
  }
  return 0;
}



undefined4 FUN_0000f5f4(int param_1,int param_2,int param_3,int param_4,int *param_5,uint *param_6)

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



byte * FUN_0000f8d8(byte *param_1,int param_2)

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



// WARNING: Control flow encountered bad instruction data

void FUN_0000fa30(undefined4 param_1,undefined4 param_2,undefined4 *param_3,code *param_4)

{
  (*param_4)();
  syscall(0);
  syscall(0);
  if (param_4 != (code *)0x0) {
                    // WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0x3f5;
  }
  return;
}


