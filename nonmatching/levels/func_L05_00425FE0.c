/* Batch 3 (2026-10-28) handoff notes:
see ../func_L05_00426B08 (twin, same fix)
*/

#include "common.h"
/* replaces the INCLUDE_ASM marker in src/levels/shared/L05_003D33E8-g8.c (-G8 unit, default flags; the file also needs its TI128/D_L05_001B1504/D_L05_001B2528 externs replaced by these) */
typedef int TI128 __attribute__((mode(TI)));

typedef struct Moby_426B08 {
    char pad0[0x10];
    TI128 pos;
    char pad20[0x24 - 0x20];
    float *cls;
    struct Moby_426B08 *next;
    float f2C;
    unsigned char b30;
    unsigned char b31;
    unsigned short h32;
    char pad34[0xAA - 0x34];
    short oclass;
    char padAC[0xF0 - 0xAC];
    float vF0[2];
    float fF8;
} Moby_426B08;

extern Moby_426B08 *func_0029EFD0(int);
extern void func_00282C88(void *);
extern float func_002A7940(void);
extern Moby_426B08 *D_L05_001B1504 __attribute__((sda));
extern Moby_426B08 *D_L05_001B2528 __attribute__((section(".sdata")));
extern void func_L05_00426D98(Moby_426B08 *);

Moby_426B08 *func_L05_00426B08(Moby_426B08 *src)
{
    Moby_426B08 *m = func_0029EFD0(0x117F);

    if (m != 0) {
        m->b30 = 0xFF;
        m->h32 = 0xFF;
        m->b31 = 1;
        qcopy(&m->pos, &src->pos);
        func_00282C88(m->vF0);
        m->fF8 = func_002A7940();
        if (D_L05_001B1504 == 0) {
            Moby_426B08 *p = D_L05_001B2528;

            if (p != 0) {
                Moby_426B08 *r = 0;
                int id = 0xFBF;

                do {
                    if (p->oclass == id)
                        r = p;
                    p = p->next;
                } while (p != 0);
                D_L05_001B1504 = r;
            }
        }
        func_L05_00426D98(m);
        m->f2C = m->cls[9];
        return m;
    }
    return 0;
}
