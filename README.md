
# Status: In development
## This is a learning project implementing Unix-like shell in C.


 This is the grammer for the Mini Shell.

 command         → logical ;

 logical         → pipeline
                  ( ( "&&" | "||" ) pipeline )* ;

 pipeline        → primaryCommand
                  ( "|" primaryCommand )* ;

 primaryCommand  → commandPart
                | "(" command ")" ;

 commandPart    -> ( WORD | ( "<" | ">" | "<<" | ">>") WORD )+;

