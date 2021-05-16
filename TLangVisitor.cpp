//
// Created by kolya on 3/25/21.
//

#include "TLangVisitor.h"
#include "Elements/MainElement.h"
#include <Elements/BodyElement.h>
#include <Elements/BodyPartElement.h>
#include <Elements/BoolBinaryElement.h>
#include <Elements/BoolValueElement.h>
#include <Elements/BranchElement.h>
#include <Elements/CastElement.h>
#include <Elements/ConditionElement.h>
#include <Elements/CycleBody.h>
#include <Elements/CycleBodyPart.h>
#include <Elements/ElementElement.h>
#include <Elements/ExprElement.h>
#include <Elements/FloatValueElement.h>
#include <Elements/ForElement.h>
#include <Elements/FunctionCallElement.h>
#include <Elements/FunctionElement.h>
#include <Elements/NamespaceBody.h>
#include <Elements/NumericalBoolOperators.h>
#include <Elements/ParamElement.h>
#include <Elements/ReturnElement.h>
#include <Elements/SetValueElement.h>
#include <Elements/StatementElement.h>
#include <Elements/StopElement.h>
#include <Elements/TypeElement.h>
#include <Elements/VariableElement.h>
#include <Elements/WhileElement.h>
#include <fstream>

antlrcpp::Any antlrcpptest::TLangVisitor::visitMain(antlrcpptest::TParser::MainContext* ctx)
{
    //m_Tree.SetupRoot(std::make_unique<MainElement>());
    try
    {
        MainElement el(m_Tree);
        for (auto statement : ctx->statement())
        {

            visitStatement(statement);
            el.AddElement(std::move(m_Current));
        }
        std::string text = el.GetText();
        std::ofstream stream_res("res.cpp");
        stream_res << text;
        stream_res.close();
    } catch (const char* message)
    {
        std::cerr << message;
        std::exit(0);
    }
    catch (std::string& message)
    {
        std::cerr << message;
        std::exit(0);
    }
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitStatement(antlrcpptest::TParser::StatementContext* ctx)
{
    if (ctx->Name())
    {
        auto el = new StatementElement(m_Tree);
        el->SetName(ctx->Name()->toString());
        visitExpr(ctx->expr());
        el->AddElement(std::move(m_Current));
        m_Current = std::unique_ptr<Element>(el);
    }
    else
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
    for (auto name : ctx->Name()) { names.push_back(name->toString()); }
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
    if (ctx->Equal())
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
    if (ctx->branch())
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
    if (ctx->variable())
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
    for (auto state : ctx->bodyPart())
    {
        visitBodyPart(state);
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<BodyElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitType(antlrcpptest::TParser::TypeContext* ctx)
{
    auto el = new TypeElement(m_Tree, ctx->getText());
    m_Current = std::unique_ptr<TypeElement>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitCondition(antlrcpptest::TParser::ConditionContext* ctx)
{
    auto el = new ConditionElement(m_Tree);
    if (ctx->boolBinaryOperators())
    {
        visitCondition(ctx->condition(0));
        el->AddElement(std::move(m_Current));
        visitBoolBinaryOperators(ctx->boolBinaryOperators());
        el->AddElement(std::move(m_Current));
        visitCondition(ctx->condition(1));
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->numericalBoolOperators())
    {
        visitCondition(ctx->condition(0));
        el->AddElement(std::move(m_Current));
        visitNumericalBoolOperators(ctx->numericalBoolOperators());
        el->AddElement(std::move(m_Current));
        visitCondition(ctx->condition(1));
        el->AddElement(std::move(m_Current));
    }
    else
    {
        visitExpr(ctx->expr());
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<ConditionElement>(el);
    return nullptr;
}
antlrcpp::Any
antlrcpptest::TLangVisitor::visitBoolBinaryOperators(antlrcpptest::TParser::BoolBinaryOperatorsContext* ctx)
{
    auto el = new BoolBinaryElement(m_Tree);
    el->str = ctx->getText();
    m_Current = std::unique_ptr<BoolBinaryElement>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitParam(antlrcpptest::TParser::ParamContext* ctx)
{
    auto el = new ParamElement(m_Tree);
    if (!ctx->Name())
    {
        visitExpr(ctx->expr());
        el->AddElement(std::move(m_Current));
    }
    else
    {
        el->SetName(ctx->Name()->toString());
    }
    m_Current = std::unique_ptr<ParamElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitCycleBody(antlrcpptest::TParser::CycleBodyContext* ctx)
{
    auto el = new CycleBody(m_Tree);
    for (auto state : ctx->cycleBodyPart())
    {
        visitCycleBodyPart(state);
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<CycleBody>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitReturnState(TParser::ReturnStateContext* ctx)
{
    auto el = new ReturnElement(m_Tree);
    if (ctx->expr())
    {
        visitExpr(ctx->expr());
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<ReturnElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitStop(antlrcpptest::TParser::StopContext* ctx)
{
    auto el = new StopElement(m_Tree);
    if (!ctx->Break()) { el->SetWord(ctx->Continue()->toString()); }
    else
    {
        el->SetWord(ctx->Break()->toString());
    }
    m_Current = std::unique_ptr<StopElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitFloatValue(antlrcpptest::TParser::FloatValueContext* ctx)
{
    auto el = new FloatValueElement(m_Tree);
    el->SetNums(ctx->Floater()->toString());
    m_Current = std::unique_ptr<FloatValueElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitBoolValue(antlrcpptest::TParser::BoolValueContext* ctx)
{
    auto el = new BoolValueElement(m_Tree);
    el->SetValue(ctx->getText());
    m_Current = std::unique_ptr<BoolValueElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitSetValue(antlrcpptest::TParser::SetValueContext* ctx)
{
    auto el = new SetValueElement(m_Tree);
    for (auto& elem : ctx->element())
    {
        visitElement(elem);
        el->AddElement(std::move(m_Current));
    }
    m_Current = std::unique_ptr<SetValueElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitElement(antlrcpptest::TParser::ElementContext* ctx)
{
    auto el = new ElementElement(m_Tree);
    if (ctx->INT()) { el->SetValue(ctx->INT()->toString()); }
    else if (ctx->floatValue())
    {
        visitFloatValue(ctx->floatValue());
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->String())
    {
        el->SetValue(ctx->String()->toString());
    }
    else if (ctx->boolValue())
    {
        visitBoolValue(ctx->boolValue());
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->Name())
    {
        el->SetName(ctx->Name()->toString());
    }
    m_Current = std::unique_ptr<ElementElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitExpr(TParser::ExprContext* ctx)
{
    auto el = new ExprElement(m_Tree);
    if (ctx->Star())
    {
        el->SetSignIfHave(ctx->Star()->toString());
        visitExpr(ctx->expr(0));
        el->AddElement(std::move(m_Current));
        visitExpr(ctx->expr(1));
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->Minus())
    {
        el->SetSignIfHave(ctx->Minus()->toString());
        visitExpr(ctx->expr(0));
        el->AddElement(std::move(m_Current));
        visitExpr(ctx->expr(1));
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->Plus())
    {
        el->SetSignIfHave(ctx->Plus()->toString());
        visitExpr(ctx->expr(0));
        el->AddElement(std::move(m_Current));
        visitExpr(ctx->expr(1));
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->expr(0))
    {
        visitExpr(ctx->expr(0));
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->cast())
    {
        visitCast(ctx->cast());
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->floatValue())
    {
        visitFloatValue(ctx->floatValue());
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->boolValue())
    {
        visitBoolValue(ctx->boolValue());
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->setValue())
    {
        visitSetValue(ctx->setValue());
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->functionCall())
    {
        visitFunctionCall(ctx->functionCall());
        el->AddElement(std::move(m_Current));
    }
    else if (ctx->INT())
    {
        el->SetIntIfHave(ctx->INT()->toString());
    }
    else if (ctx->Name())
    {
        el->SetNameIfHave(ctx->Name()->toString());
    }
    else if (ctx->String())
    {
        el->SetValueIfHave(ctx->String()->toString());
    }
    m_Current = std::unique_ptr<ExprElement>(el);
    return nullptr;
}

antlrcpp::Any antlrcpptest::TLangVisitor::visitCast(TParser::CastContext* ctx)
{
    auto el = new CastElement(m_Tree);
    visitType(ctx->type());
    el->AddElement(std::move(m_Current));
    visitExpr(ctx->expr());
    el->AddElement(std::move(m_Current));
    m_Current = std::unique_ptr<CastElement>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitNumericalBoolOperators(antlrcpptest::TParser::NumericalBoolOperatorsContext* ctx)
{
    auto el = new NumericalBoolOperators(m_Tree);
    el->SetOp(ctx->getText());
    m_Current = std::unique_ptr<NumericalBoolOperators>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitBodyPart(antlrcpptest::TParser::BodyPartContext* ctx)
{
    auto el = new BodyPartElement(m_Tree);
    if (ctx->statement()) visitStatement(ctx->statement());
    else if (ctx->returnState()) visitReturnState(ctx->returnState());
    el->AddElement(std::move(m_Current));
    m_Current = std::unique_ptr<BodyPartElement>(el);
    return nullptr;
}
antlrcpp::Any antlrcpptest::TLangVisitor::visitCycleBodyPart(antlrcpptest::TParser::CycleBodyPartContext* ctx)
{
    auto el = new CycleBodyPart(m_Tree);
    if (ctx->statement()) visitStatement(ctx->statement());
    else if (ctx->returnState()) visitReturnState(ctx->returnState());
    else if (ctx->stop()) visitStop(ctx->stop());
    el->AddElement(std::move(m_Current));
    m_Current = std::unique_ptr<CycleBodyPart>(el);
    return nullptr;
}
