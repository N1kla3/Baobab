
#include <iostream>

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

    if (stream.is_open())
    {
        ANTLRInputStream input(stream);
        TLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        TParser parser(&tokens);
        TParser::MainContext* tree = parser.main();
        TParserBaseVisitor visitor;
        auto scene = visitor.visitMain(tree);
    }
    stream.close();
    return 0;
}
