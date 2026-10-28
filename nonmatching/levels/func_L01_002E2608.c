/* Batch 3 (2026-10-28) handoff notes:
# func_L01_002E2608 (388 B, 4 places) -- w5 handoff, 55 differing lines (380 B vs 388 B)

draft.c is a full structural reconstruction (default flags, in L01_002A7248.c): a quad packet (the QuadPacket layout of src/game/00281EB8.c: matrix[16], color[4], uv[8], state[4]) filled by func_00281DE8(&packet, texture, kind, 0x80), four colours, the unit-square uv {0,0, 0,1, 1,0, 1,1}, then, when the fifth argument (turns) is nonzero, the uv pairs are copied to a temporary (loop 1) and written back rotated by turns modulo 4 (loop 2, signed modulus, retail's slt/movn/sra/sll/subu pattern), then four corner vectors are copied from the first argument with w = 1.0f (loop 3, qcopy + `swc1 f0,0xC(v1)`), then func_00280B90(&packet, 0, 0). Loop 1 and loop 3 now have retail's shape (loop 3: explicit src and row pointers, `row[3] = 1.0f`; loop 1: ascending index so loop.c reverses the counter while pointers ascend; uv as struct {u,v} gives the four separate column pointers).

Open: register numbers in loops 1-2 (retail counter a0 in loop 1, pointer copies t0..t4), retail makes a fourth pointer copy (`daddu t0,t1,zero`) that ours does not, and the nop alignment pads follow the instruction counts. The retail's colour-store order is 0x40,0x4C,0x48,0x44 (ours matches it with the descending color[3..0] source order).

## check.py --diff (masked, differing lines only; ours | retail)
```
01_oozla: 380 bytes, expected 388
  002E2668  beqz        $s1, . + 4 + (0x31 << 2)     | beqz        $s1, . + 4 + (0x33 << 2)
  002E268C  daddu       $a0, $t2, $zero              | daddu       $a1, $t2, $zero
  002E2690  addiu       $a1, $zero, 0x3              | addiu       $a0, $zero, 0x3
  002E2698  lwc1        $f0, 0x0($a0)                | lwc1        $f0, 0x0($a1)
  002E269C  addiu       $a1, $a1, -0x1               | addiu       $a0, $a0, -0x1
  002E26A0  addiu       $a0, $a0, 0x8                | addiu       $a1, $a1, 0x8
  002E26B8  bgez        $a1, . + 4 + (-0x9 << 2)     | bgez        $a0, . + 4 + (-0x9 << 2)
  002E26C0  daddu       $t0, $t2, $zero              | daddu       $t0, $t1, $zero
  002E26CC  daddu       $a3, $zero, $zero            | daddu       $a3, $t2, $zero
  002E26D0  addiu       $t2, $zero, -0x1             | daddu       $a2, $zero, $zero
  002E26D4  addiu       $a2, $s1, 0x3                | addiu       $t1, $zero, -0x1
  002E26D8  addu        $a0, $a3, $s1                | addiu       $a1, $s1, 0x3
  002E26DC  daddu       $v0, $a2, $zero              | nop
  002E26E0  slt         $v1, $t2, $a0                | addu        $v1, $a2, $s1
  002E26E4  addiu       $a3, $a3, 0x1                | daddu       $v0, $a1, $zero
  002E26E8  movn        $v0, $a0, $v1                | slt         $a0, $t1, $v1
  002E26F0  sra         $v0, $v0, 2                  | movn        $v0, $v1, $a0
  002E26F4  slti        $a1, $a3, 0x4                | addiu       $a1, $a1, 0x1
  002E26F8  sll         $v0, $v0, 2                  | sra         $v0, $v0, 2
  002E26FC  subu        $v0, $a0, $v0                | slti        $a0, $a2, 0x4
  002E2700  sll         $v1, $v0, 3                  | sll         $v0, $v0, 2
  002E2704  addu        $v0, $t4, $v1                | subu        $v1, $v1, $v0
  002E2708  lwc1        $f0, 0x0($v0)                | sll         $v1, $v1, 3
  002E270C  addu        $v1, $t3, $v1                | addu        $v0, $t4, $v1
  002E2710  swc1        $f0, 0x0($t0)                | lwc1        $f0, 0x0($v0)
  002E2714  addiu       $t0, $t0, 0x8                | addu        $v1, $t3, $v1
  002E2718  lwc1        $f0, 0x0($v1)                | swc1        $f0, 0x0($a3)
  002E271C  swc1        $f0, 0x0($t1)                | addiu       $a3, $a3, 0x8
  002E2720  bnez        $a1, . + 4 + (-0x13 << 2)    | lwc1        $f0, 0x0($v1)
  002E2724  addiu       $t1, $t1, 0x8                | swc1        $f0, 0x0($t0)
  002E2728  lui         $at, 0x3F80                  | bnez        $a0, . + 4 + (-0x13 << 2)
  002E272C  mtc1        $at, $f0                     | addiu       $t0, $t0, 0x8
  002E2730  daddu       $a0, $s2, $zero              | lui         $at, 0x3F80
  002E2734  daddu       $v1, $sp, $zero              | mtc1        $at, $f0
  002E2738  addiu       $a1, $zero, 0x3              | daddu       $a0, $s2, $zero
  002E273C  nop                                      | daddu       $v1, $sp, $zero
  002E2740  lq          $v0, 0x0($a0)                | addiu       $a1, $zero, 0x3
  002E2744  sq          $v0, 0x0($v1)                | nop
  002E2748  swc1        $f0, 0xC($v1)                | lq          $v0, 0x0($a0)
  002E274C  addiu       $a0, $a0, 0x10               | sq          $v0, 0x0($v1)
02_maktar_nebula: 380 bytes, expected 388
09_dobbo: 380 bytes, expected 388
11_joba: 380 bytes, expected 388
func_L01_002E2608: 0 of 4 places match (src/levels/shared/L01_002A7248.c)
masked diff lines: 55
```
*/

typedef struct { float u, v; } UV2608;
typedef struct { float matrix[16]; unsigned int color[4]; UV2608 uv[4]; unsigned long long state[4]; } QuadPacket2608;
extern void func_00281DE8(QuadPacket2608 *packet, int texture, int kind, int a3);
extern void func_00280B90(QuadPacket2608 *packet, int a1, int a2);

/* Fills a quad packet from four corner points, one colour and the unit square's texture coordinates rotated by turns quarter turns, then draws it. */
void func_L01_002E2608(char *corners, int texture, int kind, unsigned int color, int turns)
{
    QuadPacket2608 packet;
    UV2608 saved[4];
    int i;
    int j;
    float *row;
    char *src;

    func_00281DE8(&packet, texture, kind, 0x80);
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    packet.uv[0].u = 0.0f;
    packet.uv[0].v = 0.0f;
    packet.uv[1].u = 0.0f;
    packet.uv[1].v = 1.0f;
    packet.uv[2].u = 1.0f;
    packet.uv[2].v = 0.0f;
    packet.uv[3].u = 1.0f;
    packet.uv[3].v = 1.0f;
    if (turns != 0) {
        for (i = 0; i < 4; i++) {
            saved[i].u = packet.uv[i].u;
            saved[i].v = packet.uv[i].v;
        }
        for (j = 0; j < 4; j++) {
            int k = (j + turns) % 4;
            packet.uv[j].u = saved[k].u;
            packet.uv[j].v = saved[k].v;
        }
    }
    row = packet.matrix;
    src = corners;
    for (i = 0; i < 4; i++) {
        qcopy(row, src);
        row[3] = 1.0f;
        src += 16;
        row += 4;
    }
    func_00280B90(&packet, 0, 0);
}
