== File: tmlib.dcl

DEFINITION MODULE tmlib;

RULE :: STRINGtoCHARS STRING -> [CHAR];
RULE :: Scanconstr [CHAR] -> (STRING,[CHAR]);
RULE :: Scanobrac [CHAR] -> (INT,[CHAR]);
RULE :: Needcbrac INT [CHAR] -> [CHAR];
RULE :: Scanlist (=> [CHAR] (t,[CHAR])) [CHAR] -> ([t],[CHAR]);
RULE :: Showlist (=> t STRING) [t] -> STRING;
RULE :: Stripspace [CHAR] -> [CHAR];
RULE :: Skipuntil CHAR [CHAR] -> [CHAR];
RULE :: Scan_INT [CHAR] -> (INT,[CHAR]);
RULE :: Scan_REAL [CHAR] -> (REAL,[CHAR]);
RULE :: Scan_BOOL [CHAR] -> (BOOL,[CHAR]);
RULE :: Scan_CHAR [CHAR] -> (CHAR,[CHAR]);
RULE :: Scan_STRING [CHAR] -> (STRING,[CHAR]);
RULE :: Show_CHAR CHAR -> STRING;
RULE :: Show_STRING STRING -> STRING;
RULE :: Show_INT INT -> STRING;
RULE :: Show_REAL REAL -> STRING;
RULE :: Show_BOOL BOOL -> STRING;
