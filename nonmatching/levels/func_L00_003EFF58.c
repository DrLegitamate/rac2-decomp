/* func_L00_003EFF58 (328 bytes, 27 places) - NEAR MISS, worker 6, 28 October 2026.
 * Profile -O2 -G0 -ffunction-sections, in src/levels/shared/L00_003EE100.c in place of the marker
 * (names with a _2/_4 suffix are second prototype names for the same callees; the table pointer is
 * read through `D_L00_001B2BB4_2[0]`, an incomplete sda array, which gives retail's absolute lui/lw).
 * 328/328 bytes, 5 masked diff lines (was 18).
 * Fixed: statement order velocity, record, normal, with velocity/normal formed from `base[slot]`
 * (not from record) gave retail's saved-register order (record s0, velocity s1, counter s2, normal s3).
 * Left: retail loads `daddu $a1,$a3` before `daddu $s0,$v0`; velocity's init is `addiu $s1,$v0,0x20`
 * (ours from $s0); the end-of-loop increments of s0/s1 come in the other order.
 */
typedef int TI128_FF58 __attribute__((mode(TI)));
typedef struct { TI128_FF58 position, normal, velocity; char *owner; int value, phase; float scale; int first, last; } EffectRecord_FF58;
extern EffectRecord_FF58 *D_L00_001B2BB4_2[] __attribute__((sda));
extern void func_00282F20_2(char *, char *, float);
extern void func_00282CC0_2(char *, char *, char *);
extern void func_00282DD8_2(char *, char *, char *);
extern float func_002A7940(void);
extern void func_L00_003F0198_2(char *, int, float, float, int);
extern float func_00283B98_4(float, float);
void func_L00_003EFF58(char *owner, int value, char *direction, char *position, float scale)
{
    TI128_FF58 local;
    EffectRecord_FF58 *base = D_L00_001B2BB4_2[0];
    EffectRecord_FF58 *record;
    char *velocity;
    char *normal;
    int slot, step;
    float angle;
    slot = -1;
    while (++slot <= 0) {
        velocity = (char *)&base[slot].velocity;
        record = base + slot;
        normal = (char *)&base[slot].normal;
        if (record->owner != 0) continue;
        record->value = value;
        record->scale = scale;
        record->owner = owner;
        record->phase = 0;
        qcopy(&record->position,position);
        qcopy(velocity,direction);
        ((float *)&record->velocity)[2] = *(float *)(owner + 0x18);
        func_00282F20_2((char *)&local,position,2.0f);
        func_00282CC0_2((char *)&local,(char *)&local,velocity);
        func_00282DD8_2(normal,velocity,(char *)&local);
        angle = func_002A7940();
        for (step = 99; step >= 0; step--) {
            func_L00_003F0198_2((char *)record,2,angle,0.0f,0);
            func_L00_003F0198_2((char *)record,0,angle,0.0f,0);
            angle = func_00283B98_4(angle,0.06346652f);
        }
        record->first = 0;
        record->last = 0;
        break;
    }
}
