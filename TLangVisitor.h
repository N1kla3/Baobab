//
// Created by kolya on 3/25/21.
//
#pragma once

#include "TParserBaseVisitor.h"
#include "Elements/Baobab.h"

namespace antlrcpptest
{
    class TLangVisitor : public TParserBaseVisitor
    {
    public:
        virtual antlrcpp::Any visitMain(TParser::MainContext* ctx) override;

        virtual antlrcpp::Any visitStatement(TParser::StatementContext* ctx) override;

        virtual antlrcpp::Any visitType(TParser::TypeContext* ctx) override;

        virtual antlrcpp::Any visitCondition(TParser::ConditionContext* ctx) override;
        virtual antlrcpp::Any visitBoolBinaryOperators(TParser::BoolBinaryOperatorsContext* ctx) override;
        virtual antlrcpp::Any visitParam(TParser::ParamContext* ctx) override;
        virtual antlrcpp::Any visitBranch(TParser::BranchContext* ctx) override;

        virtual antlrcpp::Any visitFunction(TParser::FunctionContext* ctx) override;

        virtual antlrcpp::Any visitFunctionCall(TParser::FunctionCallContext* ctx) override;

        virtual antlrcpp::Any visitVariable(TParser::VariableContext* ctx) override;

        virtual antlrcpp::Any visitNamespaceBody(TParser::NamespaceBodyContext* ctx) override;

        virtual antlrcpp::Any visitForCycle(TParser::ForCycleContext* ctx) override;

        virtual antlrcpp::Any visitWhileCycle(TParser::WhileCycleContext* ctx) override;

        virtual antlrcpp::Any visitBody(TParser::BodyContext* ctx) override;
        virtual antlrcpp::Any visitCycleBody(TParser::CycleBodyContext* ctx) override;
        virtual antlrcpp::Any visitReturnState(TParser::ReturnStateContext* ctx) override;
        virtual antlrcpp::Any visitStop(TParser::StopContext* ctx) override;


        virtual antlrcpp::Any visitFloatValue(TParser::FloatValueContext* ctx) override;
        virtual antlrcpp::Any visitBoolValue(TParser::BoolValueContext* ctx) override;
        virtual antlrcpp::Any visitSetValue(TParser::SetValueContext* ctx) override;
        virtual antlrcpp::Any visitElement(TParser::ElementContext* ctx) override;


        virtual antlrcpp::Any visitExpr(TParser::ExprContext* ctx) override;
        virtual antlrcpp::Any visitCast(TParser::CastContext* ctx) override;
        antlrcpp::Any visitBodyPart(TParser::BodyPartContext* ctx) override;
        antlrcpp::Any visitCycleBodyPart(TParser::CycleBodyPartContext* ctx) override;
        antlrcpp::Any visitNumericalBoolOperators(TParser::NumericalBoolOperatorsContext* ctx) override;

        inline void SetTree()
        {
            m_Tree = std::make_shared<Baobab>();
        }
    private:
        const std::string m_FilePath = "Lang.cpp";
        std::ofstream stream;
        std::unique_ptr<Element> m_Current;
        std::shared_ptr<Baobab> m_Tree;
    };
}



