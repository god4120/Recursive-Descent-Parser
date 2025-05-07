# Recursive-Descent-Parser
Teeny Tiny PL/1 Language syntax analysis and lexical analysis using a recursive decent parser

BNF Grammer Rules:
<PROGRAM> → <PROGRAMUNITS> EOI 
<PROGRAMUNITS> → <MAINUNIT> 
<PROGRAMUNITS> → <MAINUNIT> <SUBPROGRAMS> 
<MAINUNIT> → IDENT : procedure ( MAIN ) ; <BLOCK> 
<SUBPROGRAMS> → ε 
<SUBPROGRAMS> → <SUBPROGRAM> <SUBPROGRAMS> 
<SUBPROGRAM> → <HEADER> <BLOCK> 
<HEADER> → IDENT : procedure <PARAMLIST> ; 
<HEADER> → IDENT : procedure <PARAMLIST> returns ( bit ) ; 
<HEADER> → IDENT : procedure <PARAMLIST> returns ( character ) ; 
<HEADER> → IDENT : procedure <PARAMLIST> returns ( fixed ) ; 
<HEADER> → IDENT : procedure <PARAMLIST> returns ( float ) ; 
<PARAMLIST> → ε 
<PARAMLIST> → ( <IDENTLIST> ) 
<IDENTLIST> → IDENT 
<IDENTLIST> → IDENT , <IDENTLIST> 
<BLOCK> → <TYPES> <SEQOFSTMT> end IDENT ; 
<TYPES> → ε 
<TYPES> → <TYPE> <TYPES> 
<TYPE> → declare <IDENTIFIERS> bit ; 
<TYPE> → declare <IDENTIFIERS> character ; 
<TYPE> → declare <IDENTIFIERS> fixed ; 
<TYPE> → declare <IDENTIFIERS> float ; 
<IDENTIFIERS> → IDENT 
<IDENTIFIERS> → ( <IDENTLIST> ) 
<SEQOFSTMT> → <STATEMENT> 
<SEQOFSTMT> → <STATEMENT> <SEQOFSTMT> 
<ARGUMENTS> → ε 
<ARGUMENTS> → <ARGLIST> 
<ARGLIST> → <OR> 
<ARGLIST> → <OR> , <ARGLIST> 
<STATEMENT> → IDENT = <OR> ; 
<STATEMENT> → call IDENT ( <ARGUMENTS> ) ; 
<STATEMENT> → do IDENT = <OR> to <OR> ; <SEQOFSTMT> end ; 
<STATEMENT> → do IDENT = <OR> to <OR> by <OR> ; <SEQOFSTMT> end ; 
<STATEMENT> → do while ( <OR> ) ; <SEQOFSTMT> end ; 
<STATEMENT> → if <OR> then <SEQOFSTMT> end ; 
<STATEMENT> → if <OR> then <SEQOFSTMT> else <SEQOFSTMT> end ; 
<STATEMENT> → get data ( <IDENTLIST> ) ; 
<STATEMENT> → put data ( <IDENTLIST> ) ; 
<OR> → <OR> | <AND> 
<OR> → <AND> 
<AND> → <AND> & <EQUALITY> 
<AND> → <EQUALITY> 
<EQUALITY> → <EQUALITY> = <RELATIONAL> 
<EQUALITY> → <EQUALITY> ~= <RELATIONAL> 
<EQUALITY> → <RELATIONAL> 
<RELATIONAL> → <RELATIONAL> < <ADDSUB> 
<RELATIONAL> → <RELATIONAL> <= <ADDSUB> 
<RELATIONAL> → <RELATIONAL> > <ADDSUB> 
<RELATIONAL> → <RELATIONAL> >= <ADDSUB> 
<RELATIONAL> → <ADDSUB> 
<ADDSUB> → <ADDSUB> + <MULTDIV> 
<ADDSUB> → <ADDSUB> - <MULTDIV> 
<ADDSUB> → <MULTDIV> 
<MULTDIV> → <MULTDIV> * <POW> 
<MULTDIV> → <MULTDIV> / <POW> 
<MULTDIV> → <POW> 
<POW> → <NOT> ** <POW> 
<POW> → <NOT> 
<NOT> → ~ <NOT> 
<NOT> → <PRIMARY> 
<PRIMARY> → ( <OR> ) 
<PRIMARY> → IDENT 
<PRIMARY> → IDENT ( <ARGUMENTS> ) 
<PRIMARY> → INTEGERLIT 
<PRIMARY> → REALLIT 
