/* 29 October 2026 standalone USA v1.01 replay with the verified
 * func_002FC560(unsigned int, unsigned long long) prototype: 248 bytes vs
 * 240 retail, 0/28. The helper relocations resolve. The first block mismatch
 * is the resident D_001A65EE load and the saved-mode branch target; clamp,
 * floating-point argument setup, and 64-bit helper-call argument layout also
 * differ. Retained plain-C hypothesis from src/game/0027F128.c. */
extern short D_001A65EE;
extern void func_00285030(int, int, int, int);
extern void func_0027B2F8(float, unsigned int, unsigned int, float, float, float);


void func_00280510(int y, int x, int use_saved, float scale)
{
    int mode;
    if (use_saved) {
        mode = D_001A65EE;
    } else {
        int sum = x + y;
        int shift = sum < 17 ? 16 : sum;
        int mask = (0x3FF000 - (4 << shift)) >> 13;
        mode = mask << 13;
    }
    func_00285030(x, y, mode, 0);
    func_0027B2F8(scale, 1u << y, 1u << x, 0.0f, 524288.0f, 255.0f);
    if (use_saved) {
        func_002FC560(0x47, 0);
    } else {
        func_002FC560(0, 0x3000000000000000ULL);
        func_002FC560(0x42, 0x8000000000000044ULL);
    }
}
