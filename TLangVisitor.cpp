//
// Created by kolya on 3/25/21.
//

#include <fstream>
#include "TLangVisitor.h"

antlrcpp::Any antlrcpptest::TLangVisitor::visitMain(antlrcpptest::TParser::MainContext* ctx)
{
    stream.open(m_FilePath);
    if (stream.is_open())
    {
        stream << "#include \"smth\"";
        stream << "\nint main(){";
        TLangVisitor::visitChildren(ctx);
        stream << "\n}";
    }
    stream.close();
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitStatement(antlrcpptest::TParser::StatementContext* ctx)
{
    if (ctx->Name())
    {
        if (stream.is_open())
        {
            stream << ctx->getText();
        }
    }
    else
    {
        TLangVisitor::visitChildren(ctx);
    }
    if (stream.is_open()) stream << ";\n";
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitFunction(antlrcpptest::TParser::FunctionContext* ctx)
{
    if (stream.is_open())
    {//TODO remake in another file
        auto names = ctx->Name();
        auto types = ctx->type();
        stream << (*(types.end()-1))->getText() << " ";
        stream << names[0]->getText() << "(";
        if (names.size() > 1)
        {
            for (int i = 1; i < names.size(); i++)
            {
                if (i != 1) stream << ",";
                stream << types[i-1]->getText() << " " << names[i]->getText();
            }
        }
        stream << ")";
        TLangVisitor::visitBody(ctx->body());
    }
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitFunctionCall(antlrcpptest::TParser::FunctionCallContext* ctx)
{
    //TODO remake in another file
    if (stream.is_open())
    {
        auto expressions = ctx->expr();
        stream << ctx->Name()->getText() << "(";
        for (int i = 0; i < expressions.size(); i++)
        {
            if (i != 0) stream << ",";
            TLangVisitor::visitExpr(expressions[i]);
        }
        stream << ")";
    }
    return TParserBaseVisitor::visitFunctionCall(ctx);
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitVariable(antlrcpptest::TParser::VariableContext* ctx)
{
    return TParserBaseVisitor::visitVariable(ctx);
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitNamespaceBody(antlrcpptest::TParser::NamespaceBodyContext* ctx)
{
    return TParserBaseVisitor::visitNamespaceBody(ctx);
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitBranch(antlrcpptest::TParser::BranchContext* ctx)
{
    return TParserBaseVisitor::visitBranch(ctx);
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitForCycle(antlrcpptest::TParser::ForCycleContext* ctx)
{
    return TParserBaseVisitor::visitForCycle(ctx);
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitWhileCycle(antlrcpptest::TParser::WhileCycleContext* ctx)
{
    return TParserBaseVisitor::visitWhileCycle(ctx);
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitBody(antlrcpptest::TParser::BodyContext* ctx)
{
    return TParserBaseVisitor::visitBody(ctx);
}
