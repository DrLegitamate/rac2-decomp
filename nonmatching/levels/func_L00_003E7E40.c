/* func_L00_003E7E40 (particle burst: 0x20 particles, two velocity vectors each). Not matching:
 * 612 of 616 bytes, one instruction short. The code is otherwise identical in order and
 * registers; the difference is the second rand(D_L00_001B0678, D_L00_001B067C) call: retail
 * loads both floats with `lui $at; lwc1 ...($at)` pairs and puts `mov.s $f21,$f0` in the jal
 * delay slot; with the declarations that give retail's non-hoisted `lui $at` form
 * (incomplete `float X[] __attribute__((sda))`) gcc treats the load as one instruction, puts
 * the lwc1 in the delay slot and the assembler turns it into a $gp-relative load (one
 * instruction fewer). Plain incomplete arrays and `nosda` scalars hoist the lui into saved
 * registers instead (632 bytes). Needs a -g8 file for the D_L00_001B16xx $gp words. */
extern char *func_002AB220(char *);
extern int func_002A99A0(char *, int, void *, int, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_00283D38(int, int, float);
extern int func_002A7820(int, int);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern float D_L00_001B1670 __attribute__((sda));
extern int D_L00_001B1674 __attribute__((sda));
extern float D_L00_001B1678 __attribute__((sda));
extern float D_L00_001B1680 __attribute__((sda));
extern float D_L00_001B1690 __attribute__((sda));
extern int D_L00_001B16A0 __attribute__((sda));
extern float D_L00_001B066C[] __attribute__((sda));
extern float D_L00_001B0674[] __attribute__((sda));
extern float D_L00_001B0678[] __attribute__((sda));
extern float D_L00_001B067C[] __attribute__((sda));
extern float D_L00_001B0684[] __attribute__((sda));
extern float D_L00_001B0688[] __attribute__((sda));
extern float D_L00_001B068C[] __attribute__((sda));
extern int D_L00_001B0694[] __attribute__((sda));

void func_L00_003E7E40(char *object, int *config, float scale)
{
    char *info;
    float particle[32][4] __attribute__((aligned(16)));
    float velocity[2][4] __attribute__((aligned(16)));
    int count, i, color, owner, rnd;
    float angle, speed;

    info = func_002AB220(object);
    if (info != 0) {
        count = func_002A99A0(object, 0x20, particle, (unsigned char)info[0x19], D_L00_001B1670);
        for (i = 0; i < count; i++) {
            angle = func_002A7940();
            speed = func_002A7878(D_L00_001B1680, D_L00_001B0674[0]) * 0.016666668f;
            velocity[0][0] = func_00283180(angle) * speed;
            velocity[0][1] = func_00283198(angle) * speed;
            velocity[0][2] = 0.0f;
            velocity[0][2] = func_002A7878(D_L00_001B1690, D_L00_001B0684[0]) * 0.016666668f;
            velocity[0][3] = func_002A7878(0.1f, 0.2f);
            angle = func_00283B98(angle, func_002A7878(120.0f, 240.0f) * 0.017453294f);
            speed = func_002A7878(D_L00_001B0678[0], D_L00_001B067C[0]) * 0.016666668f;
            velocity[1][0] = func_00283180(angle) * speed;
            velocity[1][1] = func_00283198(angle) * speed;
            velocity[1][2] = 0.0f;
            velocity[1][2] = func_002A7878(D_L00_001B0688[0], D_L00_001B068C[0]) * 0.016666668f;
            velocity[1][3] = func_002A7878(0.1f, 0.2f);
            velocity[1][3] = velocity[0][3] = func_002A7878(D_L00_001B1678, D_L00_001B066C[0]);
            color = func_00283D38((config[0] & 0xFFFFFF) | 0x10000000, config[0], scale);
            owner = config[2];
            rnd = func_002A7820(D_L00_001B16A0, D_L00_001B0694[0]);
            func_002BAA28(particle[i], velocity[0], velocity[1], color, owner, 5, rnd, 10, D_L00_001B1674);
        }
    }
}
