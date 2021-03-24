parser grammar TParser;

options {
	tokenVocab = TLexer;
}


// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
/* public parser declarations/members section */
bool myAction() { return true; }
bool doesItBlend() { return true; }
void cleanUp() {}
void doInit() {}
void doAfter() {}
}

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}

// Actual grammar start.


// Unused rule to demonstrate some of the special features.
unused[double input = 111] returns [double calculated] locals [int _a, double _b, int _c] @init{ doInit(); } @after { doAfter(); } :
	stat
;
catch [...] {
  // Replaces the standard exception handling.
}
finally {
  cleanUp();
}

main: Start Semicolon statement* EOF;

statement:
     Name Equal expr Semicolon
    | function Semicolon
    | functionCall Semicolon
    | variable Semicolon
;

type: Int
    | Float
    | StringType
    | Bool
    | Set
    | Char
    | Double
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
      | ExOr
;

function:
    Function OpenPar ((type Name) (Comma type Name)*)* ClosePar
    FunctionReturn (type | Void)
;
//TODO function body
functionCall:
    Name OpenPar ((expr) (Comma expr)*)* ClosePar
;

variable:
    Variable type Name (Equal (Name | expr))?
;

condition:
      condition boolBinaryOperators condition
    | Not? Name
    | INT
;

body:
    BodyStart

    BodyEnd
;

branch:
    If OpenPar condition ClosePar
    //TODO if body
;



floatValue: INT+ Dot INT+ F;
setValue: OpenCurly
              (INT (Comma INT)*)*
            | (floatValue (Comma floatValue)*)*
            | (String (Comma String)*)*
            | (Name (Comma Name)*)*
;


stat: expr Equal expr Semicolon
    | expr Semicolon
;

expr: expr Star expr
    | expr Minus expr
    | expr Plus expr
    | OpenPar expr ClosePar
    | flowControl
    | INT
    | Name
    | String
;

flowControl:
	Return expr # Return
	| Continue # Continue
	| Break # Break
;

array : OpenCurly el += INT (Comma el += INT)* CloseCurly;
any: t = .;
