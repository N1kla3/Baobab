//
// Created by kolya on 3/25/21.
//

#include "TLangVisitor.h"
antlrcpp::Any antlrcpptest::TLangVisitor::visitMain(antlrcpptest::TParser::MainContext* ctx)
{
    return TParserBaseVisitor::visitMain(ctx);
}
