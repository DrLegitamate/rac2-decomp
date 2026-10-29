/* func_00283CF0 - 16 bytes, 28 places (the boot and every level), retail at
   0x00283cf0: cvt.w.s $f12,$f12 ; mfc1 $v0,$f12 ; jr $ra ; nop.  Only the
   destination register differs: this cc1 always converts into a fresh FPR
   (`cvt.w.s $f0,$f12 ; mfc1 $v0,$f0`).  Nine spellings were measured (the
   cast direct, through a float local, through an int local, through an
   unsigned cast, with the argument used twice, with the argument used in an
   addition): all give $f0.  The SDK compiler in build/compiler/sdk gives
   the same words.  What would unblock it: a source that lets the
   conversion reuse the argument's register. 28 October 2026 current-master
   check of the retained direct cast: 16 bytes, 0/28; only the first word
   differs (`cvt.w.s $f0,$f12` versus `$f12`). */
typedef float f32;

int func_00283CF0(f32 a0) { return (int)a0; }
