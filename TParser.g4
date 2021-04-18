parser grammar TParser;

options {
	tokenVocab = TLexer;
}

main: Start Semicolon (statement | comment)* EOF;

comment: Comment;

statement:
     (Name Equal cast? (expr | functionCall | Name)
    | function
    | functionCall
    | variable
    | namespaceBody
    | branch
    | forCycle
    | whileCycle) Semicolon
;

type: Int
    | Float
    | StringType
    | Bool
    | Set
    | Char
    | Double
    | Element
;

condition:
      condition boolBinaryOperators condition
    | Not? Name
    | INT
;

boolBinaryOperators:
        LessThan
      | LessEqualThan
      | GreaterThan
      | GreaterEqualThan
      | Equality
      | And
      | Or
;

function:
    Function Name OpenPar ((type Name) (Comma type Name)*)* ClosePar
    FunctionReturn (type | Void) body
;

functionCall:
    Name OpenPar ((expr | Name) (Comma expr | Name)*)* ClosePar
;

variable:
    Variable type Name (Equal (Name | expr | condition))?
;



branch:
    If OpenPar condition ClosePar
    body
    (Else branch)?
;

forCycle:
    For OpenPar (variable | expr)? Semicolon
    condition Semicolon
    Name Equal expr
    ClosePar
    cycleBody
;

whileCycle:
    While OpenPar condition ClosePar
    cycleBody
;


namespaceBody:
    BodyStart
    (statement)*
    BodyEnd
;

body:
    BodyStart
    (statement | (Return expr Semicolon| Return Semicolon))*
    BodyEnd
;

cycleBody:
    BodyStart
    (statement | (Break Semicolon| Continue Semicolon) )*
    BodyEnd
;

floatValue: INT+ Dot INT+ F;

boolValue: True | False;

setValue: OpenCurly
            ((INT | floatValue | String | Name) (Comma (INT | floatValue | String | Name))*)
           CloseCurly
;


expr: expr Star expr
    | expr Minus expr
    | expr Plus expr
    | OpenPar expr ClosePar
    | floatValue
    | boolValue
    | setValue
    | functionCall
    | INT
    | Name
    | String
;

cast: OpenPar type ClosePar;


