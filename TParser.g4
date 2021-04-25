parser grammar TParser;

options {
	tokenVocab = TLexer;
}

main: Start Semicolon (statement | comment)* EOF;

comment: Comment;

statement:
     (Name Equal (expr | functionCall | Name)
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
    For OpenPar (variable)? Semicolon
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
    (statement | (Return expr Semicolon | Return Semicolon | Break Semicolon| Continue Semicolon) )*
    BodyEnd
;

floatValue: INT+ Dot INT+ Floater;

boolValue: True | False;

setValue: OpenCurly
            (element (Comma element)*)
           CloseCurly
;

element:
    (INT | floatValue | String | boolValue | Name)
;


expr: expr Star expr
    | expr Minus expr
    | expr Plus expr
    | OpenPar expr ClosePar
    | cast
    | floatValue
    | boolValue
    | setValue
    | functionCall
    | INT
    | Name
    | String
;

cast: OpenPar type ClosePar OpenPar (expr | Name | functionCall) ClosePar;


