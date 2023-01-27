//
// em.cocci - Convert main() to child_main()
//
// To use coccinelle to rename/modify functions, first must convert 
// functions from K&R to ANSI format using cproto -a (cproto -t to reverse).  
//
// Help:
// https://teuben.github.io/nemo/man_html/cproto.l.html
// https://coccinelle.gitlabpages.inria.fr/website/papers/ols07-padioleau.pdf
// https://coccinelle.gitlabpages.inria.fr/website/docs/main_grammar.pdf
//
// Install:
//
// brew install cproto
// brew install coccinelle
//
// Script:
//
// cp orig.c orig_ansi.c
// cproto -a orig_ansi.c
// spatch --sp-file em.cocci orig_ansi.c -o orig_ansi_em.c && cat orig_ansi_em.c
//
// Semantic patch:
//
@@
identifier argc, argv;
@@
-main(
+child_main(
int argc,char* argv[])
{...}
