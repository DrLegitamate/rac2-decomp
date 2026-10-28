/* Batch 3 (2026-10-28) handoff notes:
Best C: draft.c, size 576/576 now. New file L00_00325CC0-g8.c needs cflags line: -O2 -G8 -ffunction-sections -frac2-zero-ti-por. Key fix vs old draft: table declared with its real extent via SDATA: extern Vector D_001AA310[4] SDATA(D_001AA310); gives the retail $gp base (same trick as func_L00_00325AE8 which is EXACT). Callee names canonical (func_00282CF0 etc, D_001B8DC0). Remaining: only the save-register permutation s4..s7: retail s4=axis(sp+0xB0) s5=i+1 s6=position(sp+0xD0) s7=color; ours s4=color s5=axis s6=i+1 s7=position. Tried color declared at init, load moved to 5 places, while/for loop, compare operand order, chain vs separate color stores.

Differing lines:
  00325CF4  sd          $s4, 0x120($sp)              | sd          $s7, 0x138($sp)
  00325D10  sd          $s5, 0x128($sp)              | sd          $s4, 0x120($sp)
  00325D14  sd          $s6, 0x130($sp)              | sd          $s5, 0x128($sp)
  00325D18  sd          $s7, 0x138($sp)              | sd          $s6, 0x130($sp)
  00325D44  lw          $s4, 0x0($v1)                | lw          $s7, 0x0($v1)
  00325D88  sw          $s4, 0x4C($sp)               | sw          $s7, 0x4C($sp)
  00325D8C  sw          $s4, 0x48($sp)               | sw          $s7, 0x48($sp)
  00325D90  sw          $s4, 0x44($sp)               | sw          $s7, 0x44($sp)
  00325D98  sw          $s4, 0x40($sp)               | sw          $s7, 0x40($sp)
  00325D9C  addiu       $s7, $sp, 0xD0               | addiu       $s6, $sp, 0xD0
  00325DA4  addiu       $s5, $sp, 0xB0               | addiu       $s4, $sp, 0xB0
  00325DBC  sq          $v0, 0x0($s7)                | sq          $v0, 0x0($s6)
  00325DC4  daddu       $a2, $s7, $zero              | daddu       $a2, $s6, $zero
  00325DE8  daddu       $a0, $s5, $zero              | daddu       $a0, $s4, $zero
  00325DF8  daddu       $a0, $s5, $zero              | daddu       $a0, $s4, $zero
  00325E00  daddu       $a1, $s5, $zero              | daddu       $a1, $s4, $zero
  00325E10  daddu       $a1, $s5, $zero              | daddu       $a1, $s4, $zero
  00325E24  daddu       $a0, $s7, $zero              | daddu       $a0, $s6, $zero
  00325E28  daddu       $a1, $s7, $zero              | daddu       $a1, $s6, $zero
  00325E44  beq         $v0, $s4, . + 4 + (0x6 << 2) | beq         $v0, $s7, . + 4 + (0x6 << 2)
  00325E48  addiu       $s6, $s0, 0x1                | addiu       $s5, $s0, 0x1
  00325E4C  daddu       $s4, $v0, $zero              | sw          $v0, 0x4C($sp)
  00325E50  sw          $v0, 0x4C($sp)               | daddu       $s7, $v0, $zero
  00325E54  sw          $s4, 0x48($sp)               | sw          $v0, 0x48($sp)
  00325E58  sw          $s4, 0x44($sp)               | sw          $v0, 0x44($sp)
  00325E5C  sw          $s4, 0x40($sp)               | sw          $v0, 0x40($sp)
  00325EB0  daddu       $s0, $s6, $zero              | daddu       $s0, $s5, $zero
func_L00_00325CC0: 0 of 12 places match (src/levels/shared/L00_00325CC0-g8.c)
masked diff lines: 27
*/

#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct { float matrix[16]; u32 color[4]; float uv[8]; u64 state[4]; } Packet;
typedef struct { Packet packet; Vector up, axis, cross1, cross2, position, offset; } DrawFrame;
extern u64 func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(Packet *, void *, int);
extern Vector D_001B8DC0;
extern Vector D_001AA310[4] SDATA(D_001AA310);

void func_L00_00325CC0(int count, Vector *points, u32 *colors, float scale, float displacement)
{
    DrawFrame frame;
    int i, j;
    u32 color;
    frame.up.q = 0;
    frame.up.f[2] = 1.0f;
    frame.up.f[3] = 1.0f;
    frame.packet.state[1] = func_0027C878(11);
    color = colors[0];
    frame.packet.state[3] = 0x8000000048ULL;
    frame.packet.state[2] = 0xff9000000260ULL;
    frame.packet.state[0] = 5;
    frame.packet.uv[0] = 0.0f;
    frame.packet.uv[1] = 0.0f;
    frame.packet.uv[2] = 0.0f;
    frame.packet.uv[3] = 1.0f;
    frame.packet.uv[4] = 1.0f;
    frame.packet.uv[5] = 0.0f;
    frame.packet.uv[6] = 1.0f;
    frame.packet.uv[7] = 1.0f;
    frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = color;
    for (i = 0; i < count; ++i) {
        qcopy(&frame.position, &points[i]);
        func_00282CF0(&frame.axis, &D_001B8DC0, &frame.position);
        func_00282F20(&frame.axis, &frame.axis, 1.0f);
        func_00282DD8(&frame.cross1, &frame.axis, &frame.up);
        func_00282F20(&frame.cross1, &frame.cross1, 1.0f);
        func_00282DD8(&frame.cross2, &frame.cross1, &frame.axis);
        func_00282D30(&frame.offset, &frame.axis, displacement);
        func_00282CC0(&frame.position, &frame.position, &frame.offset);
        if (colors[i] != color) {
            color = colors[i];
            frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = color;
        }
        for (j = 0; j < 4; ++j) {
            func_00282D30(&frame.packet.matrix[j * 4], &D_001AA310[j], scale);
            func_002830C0(&frame.packet.matrix[j * 4], &frame.packet.matrix[j * 4], &frame.axis);
        }
        func_00280B90(&frame.packet, 0, 0);
    }
}
