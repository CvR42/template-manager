== File: testtop.icl
== Top level test of Miranda support library.

MODULE testtop;

IMPORT tmlib, test;

RULE
:: Start -> STRING;
   Start -> out,
	    (dt,rem): Scanlist Scan_Plot (STRINGtoCHARS s),
	    out: Showlist Show_Plot dt,
	    s: "[TestString \"abc\",TestInt 42]";
