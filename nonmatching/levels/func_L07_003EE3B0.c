/* Retained exact-C attempt: 656/656 bytes.
 * Profile: -O2 -G8 -ffunction-sections -Wa,-G2.
 * US and US2 0/1; PAL absent. The four-state dispatcher and nine-child burst are complete. Four setup words for the last random call remain scheduled differently. Volatile absolute limit reads retain the measured access sequence; GP views preserve incomplete vector extents.
 * Local checks only; no strict linked match. Reopen with independent
 * source, allocation or assembler evidence for the stated difference.
 */
#include "common.h"
extern int func_002B38B8(void *);
extern int func_002B3868(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern char *func_0032DA58(int, void *, void *, float);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_0029F338(void *);
extern int func_002A7820(int, int);
extern int func_00273B70(void *);
extern float D_L07_001B0C20[] SDATA(D_L07_001B0C20);
extern float D_L07_001B0C00 SDATA(D_L07_001B0C00);
extern volatile float D_L07_001B0C10 MACRO_ADDR;
extern volatile float D_L07_001B0C04 MACRO_ADDR;
extern volatile float D_L07_001B0C14 MACRO_ADDR;
extern volatile float D_L07_001B0C08 MACRO_ADDR;
extern volatile float D_L07_001B0C18 MACRO_ADDR;
extern float D_L07_001B0C30 SDATA(D_L07_001B0C30);
extern volatile float D_L07_001B0C34 MACRO_ADDR;
extern float D_L07_001B0C38 SDATA(D_L07_001B0C38);
extern volatile float D_L07_001B0C3C MACRO_ADDR;

void func_L07_003EE3B0(char *object)
{
    float vector[4];
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002B38B8(object)) {
            func_00283098(vector, D_L07_001B0C20, object + 0xC0);
            func_00282CC0(vector, vector, object + 0x10);
            func_0032DA58((int)object, vector, object + 0xD0, 0.0f);
            func_002A7750(object, 2, -1);
        }
        break;
    case 2:
        {
            int i;
            if (func_002B3868(object))
                func_002E5CF8(0, 0, object);
            for (i = 0; i < 9; i++) {
                char *child;
                float a, c;
                float upper;
                upper = D_L07_001B0C10;
                vector[0] = func_002A7878(D_L07_001B0C00,upper) * 0.01666666753590107f;
                vector[1] = func_002A7878(D_L07_001B0C04,D_L07_001B0C14) * 0.01666666753590107f;
                vector[2] = func_002A7878(D_L07_001B0C08,D_L07_001B0C18) * 0.01666666753590107f;
                func_00283098(vector, vector, object + 0xC0);
                upper = D_L07_001B0C34;
                {
                    float first = func_002A78D8(D_L07_001B0C30,upper);
                    float lower = D_L07_001B0C38;
                    float lastUpper = D_L07_001B0C3C;
                    a = first;
                    c = func_002A7878(lower,lastUpper);
                }
                child = func_00273730(object,2,*(short *)(object+0xAA),i,object+0x10,object+0xF0,vector,255,a,c);
                if (child) {
                    *(void (**)(char *))(child + 0x64) = func_L07_003EE3B0;
                    *(unsigned short *)(child+0x34) |= 0x2000;
                    func_002A7750(child,3,-1);
                }
            }
            func_0029F338(object);
        }
        break;
    case 3:
        if (func_002B3868(object))
            *(unsigned short *)(object+0x96)=func_002A7820(0,60);
        func_00273B70(object);
        if (*(unsigned short *)(object+0x96) != 0) {
            *(unsigned short *)(object+0x96) -= 1;
            if (*(unsigned short *)(object+0x96) != 0)
                break;
        }
        if (*(unsigned char *)(object+0x23) >= 4)
            *(unsigned char *)(object+0x23) -= 4;
        else
            func_0029F338(object);
        break;
    }
}
