PHP_ARG_ENABLE(xhp, xhp,
[ --enable-xhp   Enable XHP])

PHP_REQUIRE_CXX()
if test "$PHP_XHP" = "yes"; then
	PHP_ADD_LIBRARY(stdc++,, XHP_SHARED_LIBADD)
	PHP_SUBST(XHP_SHARED_LIBADD)
	PHP_NEW_EXTENSION(xhp, xhp_scanner.lex.cpp xhp_parser.yacc.cpp xhp_preprocess.cpp code_rope.cpp ext.cpp, $ext_shared)
fi
