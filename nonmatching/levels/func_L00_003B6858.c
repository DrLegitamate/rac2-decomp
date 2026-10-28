/* Near miss (W1, 28 October 2026): 384/384 bytes, 2 lines off at us (was 380/384, 58 lines).
   Profile: -O2 -G32 -Wa,-G32 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-barrier.
   What closed it: indexed `for (i = 0; i < 2; i++)` over the sda tables instead of eight walking
   pointers (it spills `material` at 0($sp) as retail does), the objects and velocity records as the
   two walking pointers (pre-header order s0 = state, s1 = velocity, s2 = out as retail; retail's
   sq $zero / swc1 +4 pair), and `if (a && b) return 1; return 0;`.
   Left: the loop-tail increments of the two induction pointers run s6 (position table) before
   s2 (positions out) in retail, here s2 before s6. Explicit position/out pointers, all increment
   orders, declaration orders and all permutations of the table pointers tie or lose. */
typedef int Quad __attribute__((mode(TI)));
typedef struct { char *objects[2]; char pad08[8]; Quad positions[2]; Quad velocity[2]; char pad50[0x18]; int seed; } PairState;
extern Quad D_L00_001AFA70[2] __attribute__((sda));
extern Quad D_L00_001AFA50[2] __attribute__((sda));
extern float D_L00_001AFAA0[2] __attribute__((sda));
extern float D_L00_001AFA90[2] __attribute__((sda));
extern int D_L00_001AFA98[2] __attribute__((sda));
extern int func_002A77E0(int);
extern char *func_0029EFD0(int);
extern void func_002B37E8(char *,int);
extern void func_002AEC18(char *,int);

int func_L00_003B6858(char *object)
{
    int i;
    Quad *velocity;
    char **slot;
    PairState *state=*(PairState **)(object+0x68);
    state->seed=func_002A77E0(255);
    slot=state->objects;
    velocity=state->velocity;
    for(i=0;i<2;i++) {
        char *obj;
        obj=func_0029EFD0(i?0xe7d:0xeb0);
        (*slot)=obj;
        func_002B37E8((*slot),0);
        *(unsigned short *)((*slot)+0x34)|=0x4100;
        (*slot)[0xbc]=i;
        *(Quad *)((*slot)+0xf0)=D_L00_001AFA70[i];
        state->positions[i]=D_L00_001AFA50[i];
        *velocity=0;
        ((float *)velocity)[1]=D_L00_001AFAA0[i]*(1.0f/60.0f);
        *(float *)((*slot)+0x2c)=*(float *)(*(char **)((*slot)+0x24)+0x24)*D_L00_001AFA90[i];
        func_002AEC18((*slot),D_L00_001AFA98[i]);
        slot++;
        velocity++;
    }
    if (state->objects[0] && state->objects[1]) return 1;
    return 0;
}
