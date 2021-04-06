parser grammar TParser;

options {
	tokenVocab = TLexer;
}

main: Start Semicolon (statement | comment)* EOF;

comment: Comment;

statement:
     (Name Equal cast? expr
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
      | Equal
      | Equality
      | And
      | Or
;

function:
    Function Name OpenPar ((type Name) (Comma type Name)*)* ClosePar
    FunctionReturn (type | Void) body
;
//TODO function body
functionCall:
    Name OpenPar ((expr) (Comma expr)*)* ClosePar
;

variable:
    Variable type Name (Equal (Name | expr))?
;



branch:
    If OpenPar condition ClosePar
    body
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
              (INT (Comma INT)*)*
            | (floatValue (Comma floatValue)*)*
            | (String (Comma String)*)*
            | (Name (Comma Name)*)* CloseCurly
;


expr: expr Star expr
    | expr Minus expr
    | expr Plus expr
    | OpenPar expr ClosePar
    | INT
    | Name
    | String
;

cast: OpenPar type ClosePar;


