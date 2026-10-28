/* Retained exact-C attempt: 648/640 bytes.
 * Profile: -O2 -G0 -ffunction-sections.
 * US and US2 0/4; PAL absent. The full hit packet and twenty-particle path retain float(index) inputs, the lifetime multiplication and all stores. The repeated 2.0 upper bound is hoisted into an extra saved FPR. Disabling GCSE or the second loop pass ties.
 * Local checks only; no strict linked match. Reopen with independent
 * source, allocation or assembler evidence for the stated difference.
 */
#include "common.h"
extern void func_00282F20(void *, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_L05_003D1E60(void *, int, int);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern char *func_002BDCE8(void *, int, void *, int, int, float, float, float, float);
extern float D_L05_001AFC58 SDATA(D_L05_001AFC58);
extern float D_L05_001AFC54 SDATA(D_L05_001AFC54);
struct OwnerPrefix { char pad00[0x18]; char *target; };
extern struct OwnerPrefix D_L05_001BFB00;
struct HitPacket {
    float direction[4];
    void *owner;
    int flags;
    unsigned char source;
    unsigned char type;
    unsigned short kind;
    float force;
    int count;
} __attribute__((aligned(16)));
struct HitInput { float direction[4]; char pad10[0x14]; int mode; };

void func_L05_003D1368(char *object, struct HitInput *input, float *destination)
{
    struct HitPacket packet;
    float center[4], rotation[4];
    int i;
    float loopLimit, lifetime;
    packet.flags = 0x810000;
    packet.owner = object;
    packet.force = input->mode ? D_L05_001AFC58 : D_L05_001AFC54;
    packet.count = 1;
    qcopy(packet.direction,input->direction);
    func_00282F20(packet.direction,packet.direction,1.0f);
    packet.direction[3] = 5627.9248046875f;
    packet.source = 3;
    packet.type = 2;
    packet.kind = *(unsigned short *)(object+0xAA);
    if (D_L05_001BFB00.target != 0)
        func_002A8E20(D_L05_001BFB00.target,&packet);
    func_L05_003D1E60(object+0x10,0,0);
    if (D_L05_001BFB00.target == 0 || *(short *)(D_L05_001BFB00.target+0xAA) != 0x956)
        return;
    loopLimit = 20.0f;
    lifetime = 3.0f;
    qcopy(center,object+0x10);
    for (i=0;(float)i<loopLimit;i++) {
        char *particle;
        char *data;
        float angle1,angle2;
        float index = (float)i;
        destination[0]=center[0]+func_002A78D8(index,2.0f);
        destination[1]=center[1]+func_002A78D8(index,2.0f);
        destination[2]=center[2]+func_002A78D8(index,2.0f);
        angle1=func_002A7940();
        angle2=func_002A7940();
        func_002AF000(rotation,0.05000000447034836f,angle1,angle2);
        particle=func_002BDCE8(destination,func_002A7820(-3,3),rotation,0x7FFFFFFF,0,index,1.0f,1.0f,lifetime*210000.0f);
        if (particle != 0) {
            *(unsigned short *)(particle+0xA)=120;
            data=particle+0x20;
            *(unsigned char *)(particle+0x8)=func_002A77E0(255);
            *(unsigned char *)(particle+0x3)=0x44;
            *(int *)(data+4)=2;
            *(unsigned char *)(data+0xA)=127;
            *(unsigned char *)(data+0xB)=*(unsigned char *)(particle+0xA);
        }
    }
}
