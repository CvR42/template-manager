== File: tmlib.icl

IMPLEMENTATION MODULE tmlib;

IMPORT delta;

=============================================================
== Ultra-low level helper functions
=============================================================

== Given a string, return a list of characters.
RULE
:: STRINGtoCHARS STRING -> [CHAR];
   STRINGtoCHARS ""     -> [];
   STRINGtoCHARS s      -> [c|r],
			   c: INDEX s 0,
			   r: STRINGtoCHARS (SLICE s 1 last),
			   last: -- (LENGTH s);

== Given a STRING, return an INT.
== This is a dummy implementation, that (almost) always returns 42.
RULE
:: STOI STRING -> INT;
   STOI "1" -> 1;
   STOI n   -> 42;

== They are nuts! A functional language without Map??
RULE
:: Map (=> ta tb) [ta] -> [tb];
   Map f []            -> [];
   Map f [h|t]         -> [f h|Map f t];

== And no Foldr either?
RULE
:: Foldr t (=> t (=> t t)) [t] -> t;
   Foldr a f []         -> a;
   Foldr a f [h|t]      -> f h (Foldr a f t);

== Given a list of characters, return a string
RULE
:: CHARStoSTRING [CHAR] -> STRING;
   CHARStoSTRING []     -> "";
   CHARStoSTRING [h|t]  -> +S (CTOS h) (CHARStoSTRING t);

== Given a character, return TRUE if it is a digit ('0'..'9')
MACRO Is_digit c           -> AND (<=C c '9') (>=C c '0');

== Given a character, return TRUE if it is a lowercase letter 'a'..'z'
MACRO Is_lowercase c       -> AND (<=C c 'z') (>=C c 'a');

== Given a character, return TRUE if it is a uppercase letter 'A'..'Z'
MACRO Is_uppercase c       -> AND (<=C c 'Z') (>=C c 'A');

== Given a character, return TRUE if it is a lowercase or uppercase letter
MACRO Is_alpha c    -> OR (Is_uppercase c) (Is_lowercase c);

== Given a character, return TRUE if it is a valid constructor character
MACRO Is_conschar c       -> OR (Is_digit c) (Is_alpha c);

== Given a character 'c', ensure that the list of characters starts with this
== 'c', or abort otherwise.
RULE
:: Expect CHAR [CHAR]    -> [CHAR];
   Expect c [c1|r]       -> r, IF =C c c1
                         -> ABORT (+S "Expected \"" (+S (CTOS c) (+S "\" but got \"" (+S (CTOS c1) "\""))));

=============================================================
== Internal parsing functions
=============================================================

== drop all elements from list 'x' up to and including
== element 'e'. If 'x' does not contain 'e', give an
== error message.
RULE
:: Skipuntil CHAR [CHAR] -> [CHAR];
   Skipuntil e []        -> ABORT (+S (CTOS e) " not found");
   Skipuntil e [h|t]     -> t, IF =C e h
                         -> Skipuntil e t;

== Remove all leading comment, tabs, spaces and returns
== from the given string.
RULE
:: Stripspace [CHAR]      -> [CHAR];
   Stripspace [' '|x]     -> Stripspace x;
   Stripspace ['\t'|x]    -> Stripspace x;
   Stripspace ['\n'|x]    -> Stripspace x;
   Stripspace ['\r'|x]    -> Stripspace x;
   Stripspace ['|','|'|x] -> Stripspace (Skipuntil '\n' x);
   Stripspace s           -> s;

== Helper function for Scanconstr
RULE
::  Scanconstr' [CHAR] -> ([CHAR],[CHAR]);
    Scanconstr' []    -> ([],[]);
    Scanconstr' [c|r] -> ([c|nc],nr), IF Is_conschar c
                      -> ([],[c|r]), (nc,nr): Scanconstr' r;

== Skip all leading spaces and comment, and then match a
== string of letters or digits. The matched string may be
== empty.
RULE
:: Scanconstr [CHAR] -> (STRING,[CHAR]);
   Scanconstr s      -> (CHARStoSTRING constr,r),
			(constr,r): Scanconstr' (Stripspace s);

== Given a character and a list of characters, match 'c' to
== the list of characters.
RULE
:: Matchchar CHAR [CHAR] -> (BOOL,[CHAR]);
   Matchchar c [c1|r]    -> (TRUE, r), IF =C c c1;
   Matchchar c s         -> (FALSE, s);

MACRO
   Matchbrac l -> Matchchar '(' l;

== Match any number of open brackets and preceding spaces
== and comments. Return a tuple containing the number of
== matched brackets and the remaining string. To check that
== there is a matching number of close brackets the function
== 'Needcbrac' can be used.
RULE
:: Scanobrac [CHAR] -> (INT,[CHAR]);
   Scanobrac s      -> (++ n, news), IF foundbrac
                    -> (0, s),
                       (foundbrac,rs): Matchbrac (Stripspace s),
                       (n,news): Scanobrac rs;

== Given a number 'n' and a string to scan, ensure that there
== are 'n' close brackets possibly preceded by spaces and
== comment. Give an error if not so. This function is intended
== to check that the brackets that have been scanned by
== 'Scanobrac' are balanced.
RULE
:: Needcbrac INT [CHAR] -> [CHAR];
   Needcbrac 0 s        -> s;
   Needcbrac n s        -> Needcbrac (-- n) (Skipuntil ')' s);

RULE
== Helper function for `Scanlist'. Given a function 'f' to scan a list
== element and a list of characters, return a list of scanned elements
== plus the remainder of the character list.
:: Scanlist' (=> [CHAR] (t,[CHAR])) [CHAR] -> ([t],[CHAR]);
   Scanlist' f [']'|r]                     -> ([],r);
   Scanlist' f [','|r]                     -> Scanlist' f (Stripspace r);
   Scanlist' f s                           -> ([n1|nr],sr),
                                              (n1,s1): f s,
                                              (nr,sr): Scanlist' f (Stripspace s1);

== Given a function 'f' to a scan single element of a certain type
== and a string to scan, scan a list of elements of that type.
RULE
:: Scanlist (=> [CHAR] (t,[CHAR])) [CHAR] -> ([t],[CHAR]);
   Scanlist f s    -> Scanlist' f (Stripspace (Skipuntil '[' s));

== Helper function for 'Showlist'. Given a function 'f' to show
== an element of the list, and a list, return the 'internals'
== of a list representation. 
RULE
:: Showlist'  (=> t STRING) [t] -> STRING;
   Showlist' f []    -> "";
   Showlist' f [e]   -> f e;
   Showlist' f [a|b] -> +S (f a) (+S "," (Showlist' f b));

== Given a function 'f' to show a single element of a certain
== type and a list of elements of that type, show the list.
RULE
:: Showlist (=> t STRING) [t] -> STRING;
   Showlist f l -> +S "[" (+S (Showlist' f l) "]");

=============================================================
== Library functions for some datatypes
=============================================================

== Helper function for numeric scan functions. Scan a list of digits.
RULE
:: Scandigits [CHAR]->([CHAR],[CHAR]);
   Scandigits []    -> ([],[]);
   Scandigits [c|r] -> ([c|rd],nr), IF Is_digit c
                    -> ([],[c|r]),
                        (rd,nr): Scandigits r;

== Helper function for numeric scan functions. Scan a list of digits,
== possibly preceeded by a sign.
RULE
:: Scansigndigits [CHAR]->([CHAR],[CHAR]);
   Scansigndigits []    -> ([],[]);
   Scansigndigits [c|r] -> ([c|d],nr), IF (=C c '+') || (=C c '-')
                        -> Scandigits [c|r], 
                           (d,nr): Scandigits r;

== Scan an INT
RULE
:: Scan_INT [CHAR]->(INT,[CHAR]);
   Scan_INT s -> (n, s3),
                 (bracs,s1): Scanobrac s,
                 (digs,s2): Scansigndigits (Stripspace s1),
                 s3: Needcbrac bracs s2,
                 n: STOI (CHARStoSTRING digs);

== Helper function for 'Scan_REAL'. Given a list of characters, that
== supposedly starts with the fraction part of a real number, return
== the fraction part (including the leading '.' if there is one), or an
== empty string if there isn't.
RULE
:: Scandotpart [CHAR]  -> ([CHAR],[CHAR]);
   Scandotpart ['.'|r] -> Scandigits r;
   Scandotpart s       -> ([], s);

RULE
:: Scanexppart [CHAR] -> ([CHAR],[CHAR]);
   Scanexppart []     -> ([],[]);
   Scanexppart [c|r]  -> Scansigndigits r, IF =C c 'e' || =C c 'E';
   Scanexppart l      -> ([],l);

== Helper function for Scan_REAL: given an integer part, a fractional
== part and an exponent, return a real that is constructed from these
== parts
RULE
:: Parts_to_REAL [CHAR] [CHAR] [CHAR] -> REAL;
   Parts_to_REAL i fr ex  -> 4.2;

== Scan a REAL
RULE
:: Scan_REAL [CHAR]->(REAL,[CHAR]);
   Scan_REAL s -> (n, s5),
	          (bracs,s1): Scanobrac s,
	          (prepart,s2): Scansigndigits (Stripspace s1),
	          (dotpart,s3): Scandotpart s2,
	          (exppart,s4): Scanexppart s3,
	          s5: Needcbrac bracs s4,
	          n: Parts_to_REAL prepart dotpart exppart;

== Helper function for Scan_bool: given a string containing either
== "True" or "False", return the appropriate boolean value.
RULE
:: Mkbool STRING  -> BOOL;
   Mkbool "True"  -> TRUE;
   Mkbool "False" -> FALSE;
   Mkbool s       -> ABORT (+S "Expected BOOL but got " s);

== Match a boolean.
RULE
:: Scan_BOOL [CHAR] -> (BOOL,[CHAR]);
   Scan_BOOL s      -> (b,remstr),
                       (bracs,rembrac): Scanobrac s,
                       (boolstr,remcon): Scanconstr rembrac,
                       b: Mkbool boolstr,
                       remstr: Needcbrac bracs remcon;

== Low-level helper function: given a character supposedly representing
== a digit, return the integer value.
MACRO
   Dd d    -> - (CTOI d) (CTOI '0');

== A '\' has been encountered, scan and decode the remaining escaped code
RULE
:: Scanbsl [CHAR]       -> (CHAR,[CHAR]);
   Scanbsl [d1,d2,d3|t] -> (cc, t), IF Is_digit d1 && Is_digit d2 && Is_digit d3,
		           cc: ITOC (+ (Dd d3) (* 8 (+ (Dd d2) (* 8 (Dd d1)))));

   Scanbsl [d1,d2|t]    -> (cc, t), IF (Is_digit d1) && (Is_digit d2),
                           cc: ITOC (+ (Dd d2) (* 8 (Dd d1)));

   Scanbsl [d1|t]       -> (ITOC (Dd d1), t), IF (Is_digit d1);
   Scanbsl ['b'|t]      -> ('\b',t);
   Scanbsl ['f'|t]      -> ('\f',t);
   Scanbsl ['n'|t]      -> ('\n',t);
   Scanbsl ['r'|t]      -> ('\r',t);
   Scanbsl ['t'|t]      -> ('\t',t);
   Scanbsl ['v'|t]      -> ('\011',t);
   Scanbsl [c|t]        -> (c, t);
   Scanbsl []           -> ABORT "End of string in escape sequence";

== Helper function for 'Scan_CHAR'. The previous character was a "'",
== now try to match a valid character.
RULE
:: Scancharendquo [CHAR]   -> (CHAR,[CHAR]);
   Scancharendquo ['\\'|t] -> (cc,Expect '\'' st),
		              (cc,st): Scanbsl t;
   Scancharendquo [h|t]    -> (h,Expect '\'' t);
   Scancharendquo []       -> ABORT "Unexpected end of file";

== match a CHAR
RULE
:: Scan_CHAR [CHAR] -> (CHAR,[CHAR]);
   Scan_CHAR s      -> Scancharendquo (Skipuntil '\'' s);

== Helper function for 'Scan_CHAR'. The previous character was a '"',
== now try to match a string up to an unescaped '"'.
== Scan a string until the end quote.
RULE
:: Scanstringendquo [CHAR]     ->  ([CHAR],[CHAR]);
   Scanstringendquo []         -> ABORT "missing \"";
   Scanstringendquo ['"'|t]    -> ([], t);
   Scanstringendquo ['\\'|t]   -> ([cc|rs],nt),
			          (cc,st): Scanbsl t,
			          (rs,nt): Scanstringendquo st;
   Scanstringendquo [h|t]      -> ([h|rs],nt),
			          (rs,nt): Scanstringendquo t;

== match a string. That is, any character from a starting '"' up to
== but not including the next '"'
RULE
:: Scan_STRING [CHAR] -> (STRING,[CHAR]);
   Scan_STRING s      -> (CHARStoSTRING s1,r),
			 (s1,r): Scanstringendquo (Skipuntil '"' s);

== Given an INT, return a string representing it as an octal number with
== 3 digits.
RULE
:: Showoct INT -> STRING;
   Showoct n   -> +S (ITOS d2) (+S (ITOS d1) (ITOS d0)),
		  d0: % n 8,
		  r0: / n 8,
		  d1: % r0 8,
		  d2: / n 8;

== Helper function for string representation. Given a character,
== return a string representation.
RULE
:: Showachar CHAR  -> STRING;
   Showachar '\''  -> "\\'";
   Showachar '\\'  -> "\\\\";
   Showachar '\b'  -> "\\b";
   Showachar '\f'  -> "\\f";
   Showachar '\n'  -> "\\n";
   Showachar '\r'  -> "\\r";
   Showachar '\t'  -> "\\t";
   Showachar '\011' -> "\\v";
   Showachar c     -> CTOS c;

RULE
:: Show_CHAR CHAR -> STRING;
   Show_CHAR c    -> +S "'" (+S (Showachar c) "'");

RULE
:: Show_STRING STRING -> STRING;
   Show_STRING s      -> +S "\"" (+S score "\""),
                         score: Foldr "" +S sl,
			 sl: Map Showachar (STRINGtoCHARS s);

RULE
:: Show_INT INT -> STRING;
   Show_INT n   -> +S "(" (+S (ITOS n) ")\n");

RULE
:: Show_REAL REAL -> STRING;
   Show_REAL n   -> +S "(" (+S (RTOS n) ")\n");

RULE
:: Show_BOOL BOOL  -> STRING;
   Show_BOOL FALSE -> "False";
   Show_BOOL TRUE  -> "True";
