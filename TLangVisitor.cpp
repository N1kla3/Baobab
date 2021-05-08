//
// Created by kolya on 3/25/21.
//

#include "TLangVisitor.h"
#include "Elements/MainElement.h"
#include <Elements/BodyElement.h>
#include <Elements/BoolBinaryElement.h>
#include <Elements/BranchElement.h>
#include <Elements/ConditionElement.h>
#include <Elements/ForElement.h>
#include <Elements/FunctionCallElement.h>
#include <Elements/FunctionElement.h>
#include <Elements/NamespaceBody.h>
#include <Elements/StatementElement.h>
#include <Elements/TypeElement.h>
#include <Elements/VariableElement.h>
#include <Elements/WhileElement.h>
#include <fstream>

antlrcpp::Any antlrcpptest::TLangVisitor::visitMain(antlrcpptest::TParser::MainContext* ctx)
{
    //m_Tree.SetupRoot(std::make_unique<MainElement>());
    MainElement el(m_Tree);
    for (auto statement : ctx->statement())
    {
        try
        {
            visitStatement(statement);
            el.AddElement(std::move(m_Current));
        }
        catch (std::exception e)
        {
            //TODO handling
        }
    }
    std::string text = el.GetText();
    //TODO file write
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitStatement(antlrcpptest::TParser::StatementContext* ctx)
{
    if (ctx->Name()->toString().empty())
    {
        auto el = new StatementElement(m_Tree);
        el->SetName(ctx->Name()->toString());
        visitExpr(ctx->expr());
        el->AddElement(std::move(m_Current));
        m_Current = std::unique_ptr<Element>(el);
    }
    else if (!ctx->function()->isEmpty())
    {
        auto el = new StatementElement(m_Tree);
        visitChildren(ctx);
        el->AddElement(std::move(m_Current));
        m_Current = std::unique_ptr<Element>(el);
    }
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitFunction(antlrcpptest::TParser::FunctionContext* ctx)
{
    auto el = new FunctionElement(m_Tree);
    for (auto type : ctx->type())
    {
        visitType(type);
        el->AddElement(std::move(m_Current));
    }
    visitBody(ctx->body());
    el->AddElement(std::move(m_Current));
    std::vector<std::string> names;
    for (auto name : ctx->Name())
    {
        names.push_back(name->toString());
    }
    el->SetNames(names);
    m_Current = std::unique_ptr<Element>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitFunctionCall(antlrcpptest::TParser::FunctionCallContext* ctx)
{
    auto el = new FunctionCallElement(m_Tree);
    el->SetFunctionName(ctx->Name()->toString());
    for (auto param : ctx->param())
    {
        visitParam(param);
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<FunctionCallElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitVariable(antlrcpptest::TParser::VariableContext* ctx)
{
    auto el = new VariableElement(m_Tree);
    el->SetName(ctx->Name()->toString());
    visitType(ctx->type());
    el->AddElement(std::move(m_Current));
    if (!ctx->Equal()->toString().empty())
    {
        el->SetWithEquality(true);
        visitExpr(ctx->expr());
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<VariableElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitNamespaceBody(antlrcpptest::TParser::NamespaceBodyContext* ctx)
{
    auto el = new NamespaceBody(m_Tree);
    for (auto statement : ctx->statement())
    {
        visitStatement(statement);
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<NamespaceBody>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitBranch(antlrcpptest::TParser::BranchContext* ctx)
{
    auto el = new BranchElement(m_Tree);
    visitCondition(ctx->condition());
    el->AddElement(std::move(m_Current));
    visitBody(ctx->body());
    el->AddElement(std::move(m_Current));
    if (!ctx->branch()->isEmpty())
    {
        visitBranch(ctx->branch());
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<BranchElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitForCycle(antlrcpptest::TParser::ForCycleContext* ctx)
{
    auto el = new ForElement(m_Tree);
    el->SetName(ctx->Name()->toString());
    if (!ctx->variable()->isEmpty())
    {
        visitVariable(ctx->variable());
        el->AddElement(std::move(m_Current));
    }
    visitCondition(ctx->condition());
    el->AddElement(std::move(m_Current));
    visitExpr(ctx->expr());
    el->AddElement(std::move(m_Current));
    visitCycleBody(ctx->cycleBody());
    el->AddElement(std::move(m_Current));
    m_Current = std::unique_ptr<ForElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitWhileCycle(antlrcpptest::TParser::WhileCycleContext* ctx)
{
    auto el = new WhileElement(m_Tree);
    visitCondition(ctx->condition());
    el->AddElement(std::move(m_Current));
    visitCycleBody(ctx->cycleBody());
    el->AddElement(std::move(m_Current));
    m_Current = std::unique_ptr<WhileElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitBody(antlrcpptest::TParser::BodyContext* ctx)
{
    auto el = new BodyElement(m_Tree);
    for (auto state : ctx->statement())
    {
        visitStatement(state);//TODO fix order..
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<BodyElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitType(antlrcpptest::TParser::TypeContext* ctx)
{
    auto el = new TypeElement(m_Tree, ctx->toString());
    m_Current = std::unique_ptr<TypeElement>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitCondition(antlrcpptest::TParser::ConditionContext* ctx)
{
    auto el = new ConditionElement(m_Tree);
    el->name_to_check = ctx->Name()->toString();
    el->negative = ctx->Not()->toString();
    el->num = ctx->INT()->toString();
    if (ctx->Name()->toString().empty()
          && ctx->INT()->toString().empty())
    {
        visitCondition(ctx->condition(0));
        el->AddElement(std::move(m_Current));
        visitBoolBinaryOperators(ctx->boolBinaryOperators());
        el->AddElement(std::move(m_Current));
        visitCondition(ctx->condition(1));
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<ConditionElement>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitBoolBinaryOperators(antlrcpptest::TParser::BoolBinaryOperatorsContext* ctx)
{
    auto el = new BoolBinaryElement(m_Tree);
    el->str = ctx->toString();
    m_Current = std::unique_ptr<BoolBinaryElement>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitParam(antlrcpptest::TParser::ParamContext* ctx)
{
    return TParserBaseVisitor::visitParam(ctx);
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitCycleBody(antlrcpptest::TParser::CycleBodyContext* ctx)
{
    return TParserBaseVisitor::visitCycleBody(ctx);
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitReturnState(TParser::ReturnStateContext* ctx) { return antlrcpp::Any(); }
antlrcpp::Any antlrcpptest::TLangVisitor::visitStop(antlrcpptest::TParser::StopContext* ctx)
{
    return TParserBaseVisitor::visitStop(ctx);
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitFloatValue(antlrcpptest::TParser::FloatValueContext* ctx)
{
    return TParserBaseVisitor::visitFloatValue(ctx);
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitBoolValue(antlrcpptest::TParser::BoolValueContext* ctx)
{
    return TParserBaseVisitor::visitBoolValue(ctx);
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitSetValue(antlrcpptest::TParser::SetValueContext* ctx)
{
    return TParserBaseVisitor::visitSetValue(ctx);
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitElement(antlrcpptest::TParser::ElementContext* ctx)
{
    return TParserBaseVisitor::visitElement(ctx);
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitExpr(TParser::ExprContext* ctx) { return TParserBaseVisitor::visitExpr(ctx); }
antlrcpp::Any antlrcpptest::TLangVisitor::visitCast(TParser::CastContext* ctx) { return TParserBaseVisitor::visitCast(ctx); }
