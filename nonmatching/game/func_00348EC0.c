/* Near miss, not linked. Game -O2 -G8 -ffunction-sections.
 * 640/644 bytes; USA v1.01: 0/28. Ten trials recover the frame and widget
 * row/vtable lifetimes. A guarded do/while retains the initial draw-call order.
 * Real integer-return pointer helpers and actual small-data/address views are
 * kept. Float setup/allocation and the remaining scheduling differ.
 * Secondary releases and strict linking were not checked.
 */
#include "common.h"

extern int func_002A9588(int, int, int, int, int);
extern void func_00336320(char *);
extern int func_00335E10(u8 *);
extern int func_00335E20(u8 *);
extern float D_001AE5F0 __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
extern int D_001A7344[] MACRO_ADDR;
extern float D_001AE5D0 __attribute__((sda));
extern float D_001AE5D8 __attribute__((sda));
extern float D_001AE5D4[] MACRO_ADDR;
extern float D_001AE5E0 __attribute__((sda));
extern float D_001AE5E8 __attribute__((sda));
extern float D_001AE5E4[] MACRO_ADDR;

typedef struct {
    u8 prefix[8];
    short adjust;
    u16 reserved;
    void (*draw)(char *);
} WidgetDrawEntry;

void func_00348EC0(char *object)
{
    int flash = func_002A9588(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int origin;
    int spacing;
    int count;
    float increment, half, span;
    int i;
    if (*(int *)(object + 0x440) != 0) {
    func_00336320(object);
    func_00336320(object + 0x130);
    func_00336320(object + 0x4C);
    func_00336320(object + 0x98);
    func_00336320(object + 0xE4);
    increment = D_001AE5F0 * D_001B23A4[0];
    count = *(int *)(object + 0x444);
    half = 0.5f;
    spacing = (int)(increment + half);
    span = (float)count * half;
    origin = (int)((float)(D_001A7344[0] >> 1) - (float)spacing * span);
    if (count > 0) {
      i = 0;
      do {
        char *back = object + 0x17C;
        char *front = object + 0x1C8;
        float row, top;
        float *position;
        int color;
        char *item;
        WidgetDrawEntry *entry;
        if (i == 7 && *(int *)(object + 0x448) == 0)
            continue;
        row = (float)i;
        position = (float *)func_00335E10((u8 *)back);
        top = (float)origin;
        position[0] = D_001AE5D0 + **(float **)(object + 0x434);
        position[1] = D_001AE5D4[0] + row * D_001AE5D8 + top;
        color = 0x55F0C070;
        if (i == *(int *)(object + 0x43C))
            color = flash;
        *(int *)func_00335E20((u8 *)front) = color;
        func_00336320(back);
        position = (float *)func_00335E10((u8 *)front);
        position[0] = D_001AE5D0 + **(float **)(object + 0x434);
        position[1] = D_001AE5D4[0] + row * D_001AE5D8 + top;
        func_00336320(front);
        item = object + i * 0x48 + 0x218;
        position = (float *)func_00335E10((u8 *)item);
        position[0] = D_001AE5E0 + **(float **)(object + 0x434);
        position[1] = D_001AE5E4[0] + row * D_001AE5E8 + top;
        entry = *(WidgetDrawEntry **)(object + i * 0x48 + 0x248);
        entry->draw(item + entry->adjust);
      } while (++i < *(int *)(object + 0x444));
    }
    }
}
