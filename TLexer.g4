lexer grammar TLexer;


channels { CommentsChannel, DirectiveChannel }

tokens {
	DUMMY
}

Start: 'start';

Return: 'return';
Continue: 'continue';
Break: 'break';

INT: Digit+;
fragment Digit: [0-9];

fragment LETTER : [a-zA-Z\u0080-\u{10FFFF}];

If: 'if';
Else: 'else';
Function: 'func';
Variable: 'define';
For: 'for';
While: 'while';
F: 'f';

Space: ' ' -> skip;
Newline: '\n' -> skip;
LessThan: '<';
LessEqualThan: '<=';
GreaterThan:  '>';
GreaterEqualThan: '>=';
Equal: '=';
Equality: '==';
And: 'and';
Not: 'not';
Or: 'or';
ExOr: '||';
FunctionReturn: '>>';

// Types
Bool: 'bool';
Int: 'int';
Float: 'float';
Double: 'double';
Char: 'char';
StringType: 'string';
Set: 'set';
Void: 'void';

String: '"' .*? '"';

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
QuestionMark: '?';
Comma: ',';
Ampersand: '&' -> type(DUMMY);


Comment : '#' ~[\r\n]* '\r'? '\n' -> channel(CommentsChannel);

Dot: '.';
