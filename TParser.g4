parser grammar TParser;

options {
	tokenVocab = TLexer;
}

main: Start Semicolon (statement | comment)* EOF;

comment: Comment;

statement:
     (Name Equal expr
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
    | Element
;

condition:
      condition boolBinaryOperators condition
      | condition numericalBoolOperators condition
      | expr
;

boolBinaryOperators:
        And
      | Or
;

numericalBoolOperators:
        LessThan
      | LessEqualThan
      | GreaterThan
      | GreaterEqualThan
      | Equality
;
///////DEAD
//conditionValue:
//    Not?
//    ( INT
//    | boolValue
//    | Name)
//;
//
//numericalCondition:
//    numericalCondition numericalBoolOperators numericalCondition
//    | numericalBoolValue
//;
//
//
//
//numericalBoolValue:
//      floatValue
//    | INT
//    | Name
//;
////////// DEAD

function:
    Function Name OpenPar ((type Name) (Comma type Name)*)* ClosePar
    FunctionReturn (type | Void) body
;

functionCall:
    Name OpenPar (param (Comma param)*)* ClosePar
;

param:
    expr | Name
;

variable:
    Variable type Name (Equal expr)?
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
    bodyPart*
    BodyEnd
;

bodyPart:
    statement | returnState
;

cycleBody:
    BodyStart
    cycleBodyPart*
    BodyEnd
;

cycleBodyPart:
    statement | returnState | stop
;

returnState:
    (Return expr Semicolon| Return Semicolon)
;

stop:
    Break Semicolon| Continue Semicolon
;

floatValue: Floater;

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

cast: OpenPar type ClosePar OpenPar expr ClosePar;


