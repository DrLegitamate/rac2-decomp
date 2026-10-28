/* 28 October 2026: superseded by the C candidate in
 * src/levels/shared/L09_003F9970.c, locally exact in both placements of US,
 * US2 and PAL. Default qcopy reproduces the complete vector transfers;
 * MACRO_ADDR on the scratch symbol retains the final argument setup.
 * The old diagnostic-only note below is historical. Strict linked
 * qualification remains with the maintainer.
 */

/* func_L09_003F9970 (256 bytes, 2 places) - four MMI/INVALID words plus five calls; the
 * biggest INVALID count of this tour.  Classified by pattern only, no C measured.
 *
 * Same triage as the L02 rows: identify whether the four `.word # INVALID` entries are
 * lq/sq (mode(TI) may reach them) or the 0x7000_xxxx MMI family (out of reach without a
 * compiler patch).  The row is otherwise ordinary - no max.s/min.s, no $gp.
 */
