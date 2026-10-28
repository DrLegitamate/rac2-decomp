/* Retained reconstruction, USA v1.01.
 * 560/560 bytes with game -O2 -G8. Packet initialization and camera basis match locally up to +0x164, then the GP vertex-index view, absolute texture-index view and output pointer have different GPR allocation. Both index views bind to the same canonical table; pointer-induction rewrites worsen allocation.
 * No strict linked match.
 */
#include "common.h"

typedef struct { s16 vertex, texture; } SpriteIndex;
typedef struct {
    float points[4][4];
    u32 colors[4];
    float uv[4][2];
    u64 primitive, texture, tag, blend;
} SpritePacket;
extern int D_001A79F0;
extern unsigned char D_L05_001B96C0[];
extern float D_L05_002B8850[][4];
extern float D_L05_002B88E0[][2];
extern SpriteIndex D_L05_001B1C40[4][4];
extern SpriteIndex indices_gp[4][4] SDATA(D_L05_001B1C40);
extern int D_L05_001B1C80 SDATA(D_L05_001B1C80);
extern int D_L05_001B1C84 SDATA(D_L05_001B1C84);
extern int D_L05_001B1C88 SDATA(D_L05_001B1C88);
extern int D_L05_001B1C8C SDATA(D_L05_001B1C8C);
extern int D_L05_001B1C90 SDATA(D_L05_001B1C90);
extern u32 D_L05_001B1C94 SDATA(D_L05_001B1C94);
extern float D_L05_001B1C98 SDATA(D_L05_001B1C98);
extern u64 func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

void func_L05_00445D60(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    SpritePacket packet;
    float matrix[4][4];
    int i, j;
    u64 blend;
    s16 *vertices, *textures;
    if (D_001A79F0 == 20)
        packet.texture = func_0027C878(65);
    else
        packet.texture = func_0027C878(63);
    packet.tag = 0xFF9000000260ULL;
    blend = (u64)D_L05_001B1C80;
    blend |= (u64)D_L05_001B1C84 << 2;
    blend |= (u64)D_L05_001B1C88 << 4;
    blend |= (u64)D_L05_001B1C8C << 6;
    blend |= (u64)D_L05_001B1C90 << 32;
    packet.blend = blend;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = D_L05_001B1C94;
    packet.primitive = 0;
    qcopy(matrix[3], state + 0x20);
    func_00282CF0(matrix[0], D_L05_001B96C0, matrix[3]);
    func_00282F20(matrix[0], matrix[0], 1.0f);
    func_00282DD8(matrix[1], matrix[0], D_L05_001B96C0 + 0x250);
    func_00282F20(matrix[1], matrix[1], 1.0f);
    func_00282DD8(matrix[2], matrix[1], matrix[0]);
    for (i = 0; i < 4; i++) {
        textures = &D_L05_001B1C40[i][0].texture;
        vertices = &indices_gp[i][0].vertex;
        for (j = 0; j < 4; j++) {
            int texture = textures[j * 2];
            func_00282D30(packet.points[j], D_L05_002B8850[vertices[j * 2]], D_L05_001B1C98);
            packet.uv[j][0] = D_L05_002B88E0[texture][0];
            packet.uv[j][1] = D_L05_002B88E0[texture][1];
        }
        func_00280B90(&packet, matrix, 0);
    }
}
