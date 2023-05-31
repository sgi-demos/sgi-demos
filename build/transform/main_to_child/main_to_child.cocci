//
// main_to_child.cocci
//
// Rename main() to child_main()
//
// Install: brew install coccinelle
// Script:  spatch --sp-file main_to_child.cocci main.c -o child.c
//
@m2c@
identifier main_func=main;
@@
- main_func
+ child_main
  (...)
  { 
      ... 
  }
