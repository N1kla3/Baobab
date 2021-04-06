lexer grammar TLexer;



tokens {
	DUMMY
}

Start: 'start';

Return: 'return';
Continue: 'continue';
Break: 'break';

fragment Digit: [0-9];

fragment LETTER : [a-zA-Z];

If: 'if';
Else: 'else';
Function: 'func';
Variable: 'define';
For: 'for';
While: 'while';
fragment F: 'f';

LessThan: '<';
GreaterThan:  '>';
LessEqualThan: '<=';
GreaterEqualThan: '>=';
Equal: '=';
Equality: '==';
Not: 'not';
And: 'and';
Or: 'or';
FunctionReturn: '>>';

// Types
Bool: 'bool';
Int: 'int';
Float: 'float';
Double: 'double';
Char: 'char';
StringType: 'string';
Set: 'set';
Element: 'element';
Void: 'void';
True: 'true';
False: 'false';

String: '"' .*? '"';
INT: Digit+;

Name: LETTER+;

Colon: ':';
Semicolon: ';';
Plus: '+';
Minus: '-';
Star: '*';
OpenPar: '(';
ClosePar: ')';
OpenCurly: '{';
CloseCurly: '}';
BodyStart: '[';
BodyEnd: ']';
Comma: ',';

Dot: '.';

Comment : '#' .*? '#';//TODO comments
Space: ' ' -> skip;
Newline: '\n' -> skip;

