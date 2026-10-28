/* Near miss, not linked. Default game -O2 -G8 -ffunction-sections.
 * 224/224 bytes; USA v1.01 0/1 placements. Callee interfaces were checked
 * against matched definitions. The independent reset stores have the retail
 * order but use reversed address/constant temporaries. Eleven trials include
 * scalar/aggregate views, measured volatile stores, scheduler settings and a
 * reset-pointer lifetime. No changed helper interface or synthetic dependency.
 * Reopen with a measured reset-state lifetime or address form.
 */
#include "common.h"

extern int D_L10_001B13A4 __attribute__((sda));
extern int D_L10_00221CFC[];
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern int *func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L05_0037B280(char *, int);
extern void func_L10_00425798(void);
extern void func_L10_00425410(int, void *);
extern int func_L05_00379ED0(int);
extern int func_L05_0037B3A0(u8 *);
extern void func_L10_00423DC8(void *, int);

void func_L10_00424448(void *object)
{
    int *objects;
    int remaining;
    if (D_L10_001B13A4 == 0) {
        int *resetWord = D_L10_00221CFC;
        D_L10_001B13A4 = 1;
        *resetWord = 0;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        objects = func_L05_00379EB8();
        remaining = func_L00_004272A0();
        if (remaining > 0) {
            do {
                char *entry = (char *)*objects;
                if (*(short *)(entry + 0xAA) == 0xF8E)
                    func_L05_0037B280(entry, 1);
                --remaining;
                ++objects;
            } while (remaining != 0);
        }
        func_L10_00425798();
        func_L10_00425410(0x32, (void *)0xC);
    }
    if (func_L05_0037B3A0((u8 *)func_L05_00379ED0(0xF8E)) == 0)
        func_L10_00423DC8(object, 2);
}
