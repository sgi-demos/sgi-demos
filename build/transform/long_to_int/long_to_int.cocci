//
// long_to_int.cocci
//
// Convert all long type declarations to int
// NOTE: This removes const qualifiers, might fix later
//
// Install: brew install coccinelle
// Script:  spatch --sp-file long_to_int.cocci long.c -o int.c
//
@l2i@
type T = long;
@@
- T
+ int