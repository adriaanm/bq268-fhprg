.syntax unified
.thumb

/* Declare external function symbols as Thumb functions at their original addresses.
 * This ensures BL (not BLX) is used for interworking. */

.global FUN_08032b94
.thumb_set FUN_08032b94, 0x08032b95

.global FUN_08033656
.thumb_set FUN_08033656, 0x08033657

.global FUN_08034fb0
.thumb_set FUN_08034fb0, 0x08034fb1
