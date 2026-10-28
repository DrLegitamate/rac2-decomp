/* Retained exact-C reconstruction: 912/928 bytes.
 * Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * US, US2 and PAL each 0/27. Complete ordered box, cylinder, sphere and capsule tests preserve the 16-byte point snapshot. Reusing the actual position parameter for the local snapshot recovers the retail prologue. Explicit faithful dispatch recovers the first case head; return-tail/branch-slot shape and later allocation remain different.
 * No strict linked match. Reopen with independent source, allocation or
 * compiler evidence for the remaining difference; do not repeat tied forms.
 */
#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern char *D_L00_001B1F8C NOT_SDA;
extern char *D_L00_001B1F9C NOT_SDA;
extern char *D_L00_001B1F94 NOT_SDA;
extern char *D_L00_001B1F84 NOT_SDA;
typedef int QuadVolume __attribute__((mode(TI)));
struct VolumeRef { char pad00[0x10]; int kind; int index; };

int func_L00_002DB4B8(void *position, struct VolumeRef *volume, float padding)
{
    float point[4] __attribute__((aligned(16)));
    float cap[4], delta[4], local[4];
    int kind = volume->kind;
    *(QuadVolume *)point = *(QuadVolume *)position;
    position = point;
    if (kind == 5) goto sphere;
    if (kind < 6) {
        if (kind == 3) goto box;
        return 0;
    }
    if (kind == 6) goto cylinder;
    if (kind == 7) goto capsule;
    return 0;
box: {
        char *record = D_L00_001B1F8C + volume->index * 128;
        func_00282CF0(delta,position,record+0x30);
        delta[3]=0.0f;
        func_00283098(local,delta,record+0x40);
        if (!(-1.0f <= local[0])) return 0;
        if (!(local[0] <= 1.0f)) return 0;
        if (!(-1.0f <= local[1])) return 0;
        if (!(local[1] <= 1.0f)) return 0;
        if (!(-1.0f <= local[2])) return 0;
        if (local[2] <= 1.0f) return 1;
        return 0;
    }
cylinder: {
        int inside = 0;
        char *record = D_L00_001B1F9C + volume->index * 128;
        func_00282CF0(delta,position,record+0x30);
        delta[3]=0.0f;
        func_00283098(local,delta,record+0x40);
        if (func_00282E20(local) < 1.0f && -1.0f <= local[2] && local[2] <= 1.0f)
            inside=1;
        return inside;
    }
sphere: {
        char *record = D_L00_001B1F94 + volume->index * 128;
        float radius = func_00282DF0(record) + padding;
        if (func_00282E48(position,record+0x30) < radius) return 1;
        return 0;
    }
capsule: {
        char *record = D_L00_001B1F84 + volume->index * 144;
        char *center;
        func_00282CF0(delta,position,record+0x30);
        delta[3]=0.0f;
        func_00283098(local,delta,record+0x40);
        if (func_00282E20(local) < 1.0f && -1.0f <= local[2] && local[2] <= 1.0f)
            return 1;
        padding = 1.0f;
        *(int *)&cap[0]=0; *(int *)&cap[1]=0; cap[2]=cap[3]=padding;
        center=record+0x30;
        func_00283098(local,cap,record);
        func_00282CC0(local,local,center);
        func_00282CF0(cap,position,local);
        if (func_00282DF0(cap) < *(float *)(record+0x80)) return 1;
        cap[2]=-1.0f; cap[3]=padding; *(int *)&cap[0]=0; *(int *)&cap[1]=0;
        func_00283098(local,cap,record);
        func_00282CC0(local,local,center);
        func_00282CF0(cap,position,local);
        if (func_00282DF0(cap) < *(float *)(record+0x80)) return 1;
        return 0;
    }
    return 0;
}
