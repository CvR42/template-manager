..file: mira.mt
.. Generate Miranda datastructure description.
|| Definition Miranda datastructures and code
||
|| template file:      ${tplfilename}
|| datastructure file: ${dsfilename}
|| tm version:         $(tmvers)

.. Note that <<need_ds>> is required instead of 'want_ds' since
.. Miranda gets upset otherwise
.if ${defined also_export}
.else
.set also_export
.endif
.set xl $(need_ds) $(want_misc)
.foreach cl show scan
.append xl ${prefix $(cl)_ $(want_$(cl))}
.endforeach
%export $(also_export) $(xl)

.foreach t $(need_ds)
.if ${member $t ${ttypelist}}
.set el
.foreach e ${telmlist $t}
.if ${eq list ${ttypeclass $t $e}}
.append el [${ttypename $t $e}]
.else
.append el ${ttypename $t $e}
.endif
.endforeach
$t == (${seplist ", " $(el)});

.else
$t ::=
.set i ${len ${conslist $t}}
.foreach c ${conslist $t}
.set el
.foreach e ${celmlist $t $c}
.if ${eq list ${ctypeclass $t $c $e}}
.append el [${ctypename $t $c $e}]
.else
.append el ${ctypename $t $c $e}
.endif
.endforeach
.if ${< $i 2}
    $c $(el);
.else
    $c $(el) |
.endif
.set i ${- $i 1}
.endforeach

.endif
.endforeach

|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|| Internal parsing functions
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

|| drop all elements from list 'x' up to and including
|| element 'e'. If 'x' does not contain 'e', give an
|| error message.
skipuntil :: char->[char]->[char]
skipuntil e []    = error ((show e) ++ " not found")
skipuntil e (h:t) = t, e=h
                  = skipuntil e t, otherwise

|| Remove all leading comment, tabs, spaces and returns
|| from the given string.
stripspace :: [char]->[char]
stripspace (' ':x)     = stripspace x
stripspace ('\t':x)    = stripspace x
stripspace ('\n':x)    = stripspace x
stripspace ('\r':x)    = stripspace x
stripspace ('|':'|':x) = stripspace (skipuntil '\n' x)
stripspace s           = s

|| Skip all leading spaces and comment, and then match a
|| string of letters or digits. The matched string may be
|| empty.
scanconstr :: [char]->([char],[char])
scanconstr s
= scanconstr' (stripspace s)
  where
  scanconstr' []    = ([],[])
  scanconstr' (c:r) = ((c:nc),nr), letter c \/ digit c
                    = ([],(c:r)), otherwise
                      where
                      (nc,nr) = scanconstr' r

|| Match any number of open brackets and preceding spaces
|| and comments. Return a tuple containing the number of
|| matched brackets and the remaining string. To check that
|| there is a matching number of close brackets the function
|| 'needcbrac' can be used.
scanobrac :: [char]->(num,[char])
scanobrac s = ((n+1), news), foundbrac
            = (0, s), otherwise
              where
              matchbrac ('(':r) = (True, r)
              matchbrac s = (False, s)
              (foundbrac,rs) = matchbrac (stripspace s)
              (n,news) = scanobrac rs

|| Given a number 'n' and a string to scan, ensure that there
|| are 'n' close brackets possibly preceded by spaces and
|| comment. Give an error if not so. This function is intended
|| to check that the brackets that have been scanned by
|| 'scanobrac' are balanced.
needcbrac :: num->[char]->[char]
needcbrac 0 s = s
needcbrac n s = needcbrac (n-1) (skipuntil ')' s)

|| Given a function to a scan single element of a certain type
|| and a string to scan, scan a list of elements of that type.
scanlist :: ([char]->(*,[char]))->[char]->([*],[char])
scanlist f s
= scanlist2 f (stripspace (skipuntil '[' s))
  where
  scanlist2 f (']':r) = ([],r)
  scanlist2 f (',':r) = scanlist2 f (stripspace r)
  scanlist2 f s = (n1:nr,sr)
                  where
                  (n1,s1) = f s
                  (nr,sr) = scanlist2 f (stripspace s1)

.foreach t $(need_scan)
|| Match a datastructure of type $t.
scan_$t :: [char]->($t,[char])
.if ${member $t ${ttypelist}}
scan_$t s
      = ((${seplist ", " ${prefix e_ ${telmlist $t}}}), remstr )
        where
        rembrac = stripspace (skipuntil '(' s)
.set prevs rembrac
.set first 1
.foreach e ${telmlist $t}
.if $(first)
.set first 0
.else
        c_$e = skipuntil ',' $(prevs)
.set prevs c_$e
.endif
.if ${eq list ${ttypeclass $t $e}}
        (e_$e,r_$e) = scanlist scan_${ttypename $t $e} $(prevs)
.else
        (e_$e,r_$e) = scan_${ttypename $t $e} $(prevs)
.endif
.set prevs r_$e
.endforeach
        remstr = skipuntil ')' $(prevs)
.else
scan_$t s
      = (v,remstr)
        where
.foreach c ${conslist $t}
        scan_$c s
              = (($c ${prefix e_ ${celmlist $t $c}}), cremstr)
                where
.set prevs s
.foreach e ${celmlist $t $c}
.if ${eq list ${ctypeclass $t $c $e}}
                (e_$e,r_$e) = scanlist scan_${ctypename $t $c $e} $(prevs)
.else
                (e_$e,r_$e) = scan_${ctypename $t $c $e} $(prevs)
.endif
.set prevs r_$e
.endforeach
                cremstr = $(prevs)
.endforeach
.foreach c ${conslist $t}
        doascan "$c" r = scan_$c r
.endforeach
        doascan c r = error ("Not a constructor of type $t: "++c)
        (bracs,rembrac) = scanobrac s
        (constr,remcon) = scanconstr rembrac
        (v,remall) = doascan constr remcon
        remstr = needcbrac bracs remall

.endif
.endforeach

|| Given a function to show a single element of a certain
|| type and a list of elements of that type, show the list.
showlist' :: (*->[char])->[*]->[char]
showlist' f [] = ""
showlist' f [e] = f e
showlist' f (a:b) = (f a) ++ "," ++ (showlist' f b)

showlist :: (*->[char])->[*]->[char]
showlist f l = "[" ++ (showlist' f l) ++ "]"

.foreach t $(need_show)
|| Show a datastructure of type $t
show_$t :: $t->[char]
.if ${member $t ${ttypelist}}
show_$t (${seplist ", " ${telmlist $t}})
= "(" ++
.set first 1
.foreach e ${telmlist $t}
.if $(first)
.set first 0
.else
        "," ++
.endif
.if ${eq list ${ttypeclass $t $e}}
        (showlist show_${ttypename $t $e} $e) ++
.else
        (show_${ttypename $t $e} $e) ++
.endif
.endforeach
        ")\n"
.else
.foreach c ${conslist $t}
show_$t ($c ${celmlist $t $c})
= "($c " ++
.foreach e ${celmlist $t $c}
.if ${eq list ${ctypeclass $t $c $e}}
        (showlist show_${ctypename $t $c $e} $e) ++
.else
        (show_${ctypename $t $c $e} $e) ++
.endif
.endforeach
        ")\n"
.endforeach
.endif

.endforeach
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|| Library functions for some special datatypes
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

.if ${or ${index scan_int $(want_misc)} ${index scan_num $(want_misc)}}
scandigits :: [char]->([char],[char])
scandigits []    = ([],[])
scandigits (c:r) = (c:rd,nr), digit c
                 = ([],c:r), otherwise
                   where
                   (rd,nr) = scandigits r

scansigndigits :: [char]->([char],[char])
scansigndigits []    = ([],[])
scansigndigits (c:r) = (c:d,nr), c = '+' \/ c = '-'
                     = scandigits (c:r), otherwise
                       where
                       (d,nr) = scandigits r

.endif
|| Match a num
.if ${index scan_num $(want_misc)}
scan_num :: [char]->(num,[char])
scan_num s
      = (n, s5)
        where
        scandotpart ('.':r) = ('.':d,nr)
                              where
                              (d,nr) = scandigits r
        scandotpart s       = ("", s)
        scanexppart []      = ("","")
        scanexppart (c:r)   = (c:e,nr), c = 'e' \/ c = 'E'
                            = ("",(c:r)), otherwise
                              where
                              (e,nr) = scansigndigits r
        (bracs,s1) = scanobrac s
        (prepart,s2) = scansigndigits (stripspace s1)
        (dotpart,s3) = scandotpart s2
        (exppart,s4) = scanexppart s3
        s5 = needcbrac bracs s4
        n = numval (prepart ++ dotpart ++ exppart)

.endif
.if ${index scan_bool $(want_misc)}
|| Match a boolean.
scan_bool :: [char]->(bool,[char])
scan_bool s = (b,remstr)
              where
              (bracs,rembrac) = scanobrac s
              (boolstr,remcon) = scanconstr rembrac
              mkbool "True" = True
              mkbool "False" = False
              mkbool c = error ("Expected bool but got " ++ (show c))
              b = mkbool boolstr
              remstr = needcbrac bracs remcon

.endif
.if ${or ${index scan_string $(want_misc)} ${index scan_char $(want_misc)}}
dd :: char->num
dd d = (numval [d])

|| A '\' has been encountered, scan the remaining escaped code
scanbsl :: [char]->(char,[char])
scanbsl (d1:d2:d3:t)
= (cc, t), digit d1 & digit d2 & digit d3
  where
  cc = decode ((dd d3) + 8*((dd d2) + 8*(dd d1)))

scanbsl (d1:d2:t) = (cc, t), digit d1 & digit d2
                    where
                    cc = decode ((dd d2) + 8*((dd d1)))

scanbsl (d1:t) = ((decode (dd d1)), t), digit d1
scanbsl ('b':t) = ('\b',t)
scanbsl ('f':t) = ('\f',t)
scanbsl ('n':t) = ('\n',t)
scanbsl ('r':t) = ('\r',t)
scanbsl ('t':t) = ('\t',t)
scanbsl ('v':t) = ('\11',t)     || octal 13
scanbsl (c:t)   = (c, t), otherwise

.endif
.if ${index scan_char $(want_misc)}
|| match a character
scan_char :: [char]->(char,[char])
scan_char s = scanendquo (skipuntil '\'' s)
              where
              terminate ('\'':r)    = r
              terminate (c:r)
                  = error ("Expected \"'\" but got \"" ++ (show c) ++ "\"")
              scanendquo []         = error "Unexpected end of file"
              scanendquo ('\\':t)   = (cc,terminate st)
                                      where
                                      (cc,st) = scanbsl t

              scanendquo (h:t)      = (h,terminate t)

.endif
.if ${index scan_string $(want_misc)}
|| match a string. That is, any character from a starting '"' up to
|| but not including the next '"'
scan_string :: [char]->([char],[char])
scan_string s = scanendquo (skipuntil '"' s)
                where
                scanendquo []         = error "missing \""
                scanendquo ('"':t)    = ([], t)
                scanendquo ('\\':t)   = (cc:rs,nt)
                                        where
                                        (cc,st) = scanbsl t
                                        (rs,nt) = scanendquo st

                scanendquo (h:t)      = ((h:rs),nt)
                                        where
                                        (rs,nt) = scanendquo t

.endif
.if ${or ${index show_char $(want_misc)} ${index show_string $(want_misc)}}
showoct :: num->[char]
showoct n = shownum n, n<8
          = (showoct (n div 8)) ++ (shownum (n mod 8)), otherwise 

showchar :: char->[char]
showchar '"'  = "\\\""
showchar '\'' = "\\'"
showchar '\\' = "\\\\"
showchar '\b' = "\\b"
showchar '\f' = "\\f"
showchar '\n' = "\\n"
showchar '\r' = "\\r"
showchar '\t' = "\\t"
showchar '\11' = "\\v"
showchar c    = '\\':(showoct (code c)), c<' ' \/ c>'~'
              = [c], otherwise

.endif
.if ${index show_char $(want_misc)}
show_char :: char->[char]
show_char c = '\'':(showchar c) ++ "'"

.endif
.if ${index show_string $(want_misc)}
show_string :: [char]->[char]
show_string s = '"':(concat (map showchar s)) ++ "\""

.endif
.if ${index show_num $(want_misc)}
show_num :: num->[char]
show_num n = "("++ (shownum n) ++ ")\n"

.endif
.if ${index show_bool $(want_misc)}
show_bool :: bool->[char]
show_bool b = "("++ (show b) ++ ")\n"

.endif
