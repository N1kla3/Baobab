
#include <iostream>

#include "TLangVisitor.h"
#include "TLexer.h"
#include "TParser.h"
#include "TParserBaseVisitor.h"
#include "antlr4-runtime.h"

using namespace antlrcpptest;
using namespace antlr4;

int main(int argc, const char** argv)
{
    if (argc != 2) return -1;
    std::ifstream stream;
    stream.open(argv[1]);
    std::string in = "", temp;
    while (!stream.eof())
    {
        std::getline(stream, temp);
        in += temp;
    }
    stream.close();
    ANTLRInputStream input(in);
    TLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    TParser parser(&tokens);
    TParser::MainContext* tree = parser.main();
    TLangVisitor visitor;
    visitor.SetTree();
    visitor.visitMain(tree);
    return 0;
}
