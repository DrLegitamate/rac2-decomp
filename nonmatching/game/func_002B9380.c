#include "include_asm.h"

/* func_002B9380: the object's virtual call at offset 0x3C.
 *
 * MEASURED (tools/check.py, level 00 and the boot):
 *   - 16 bytes in the retail: "lw $v0,0x3C($a0) ; nop ; jr $v0 ; nop" -- a tail
 *     call: the callee's return value goes straight back to func_002B9380's caller.
 *   - this body compiles to 32 bytes: the same load, then "jalr $v0" and the
 *     epilogue.  gcc 2.9-ee makes no sibling call for an indirect call, so the
 *     frame and the "jr $ra" are always there.  Five spellings were measured (a
 *     void and an int return, a function pointer in a local, an explicit cast to
 *     int and to void (*)()) and every one of them emits "jal $31,$2".
 *   - the compiler's "-mastra-sibcall" (tools/compiler/patches/0022-sibcall-
 *     default-off.patch) re-enables the Cygnus sibling-call pass, but it does
 *     not change this call either: the indirect target keeps its "jalr".
 *
 * The retail's "jr $v0" is therefore a tail call this compiler does not emit for
 * an indirect target; the body needs a way to spell it that plain C has not
 * found.
 *
 * Current-master computed-goto probe (plain GNU C extension, no asm or barrier):
 *   void func_002B9380(void *a0) {
 *       goto *(void *)(*(unsigned int *)((char *)a0 + 0x3C));
 *   }
 * It emits 12 bytes at all 28 places: `lw $v0,0x3C($a0); jr $v0; nop`.
 * Retail has an additional `nop` between the load and `jr`. The compiler does
 * not retain a no-op there from a source-level empty statement, and an artificial
 * barrier or inline assembly is forbidden. The indirect tail-call shape is now
 * confirmed; the remaining load/jump spacing is unresolved. No exact match.
 */

void func_002B9380(void *a0)
{
    (*(void (**)(void))((char *)a0 + 0x3C))();
}
