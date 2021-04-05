//
// Created by kolya on 3/25/21.
//

#include <fstream>
#include "TLangVisitor.h"
#include "Elements/MainElement.h"

antlrcpp::Any antlrcpptest::TLangVisitor::visitMain(antlrcpptest::TParser::MainContext* ctx)
{
    m_Tree.AddElement(std::make_unique<MainElement>());
    visitChildren(ctx);
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
        visitType(*(types.end()-1));
        stream << " ";
        stream << names[0]->getText() << "(";
        if (names.size() > 1)
        {
            for (int i = 1; i < names.size(); i++)
            {
                if (i != 1) stream << ",";
                visitType(types[i-1]);
                stream << " " << names[i]->getText();
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
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitVariable(antlrcpptest::TParser::VariableContext* ctx)
{
    visitType(ctx->type());
    if (stream.is_open())
    {
        stream << ctx->Name()[0]->getText();
        if (ctx->Equal())
        {
            stream << " = ";
            if (ctx->expr())
            {
                visitExpr(ctx->expr());
            }
            else
            {
                stream << ctx->Name()[1]->getText();
            }
        }
    }
    return nullptr;
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

antlrcpp::Any antlrcpptest::TLangVisitor::visitType(antlrcpptest::TParser::TypeContext* ctx)
{
    if (ctx->StringType())
    {
        stream << " std::string ";
    }
    else if (ctx->Element())
    {
        stream << " std::variant<char, int, std::string, float, bool> ";
    }
    else if (ctx->Set())
    {
        stream << " std::set<std::variant<char, int, std::string, float, bool> ";
    }
    else
    {
        stream << " " << ctx->getText() << " ";
    }
    return TParserBaseVisitor::visitType(ctx);
}
