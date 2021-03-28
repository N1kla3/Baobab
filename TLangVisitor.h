//
// Created by kolya on 3/25/21.
//
#pragma once

#include "TParserBaseVisitor.h"

namespace antlrcpptest
{
    class TLangVisitor : public TParserBaseVisitor
    {
    public:
        virtual antlrcpp::Any visitMain(TParser::MainContext* ctx) override;

        virtual antlrcpp::Any visitStatement(TParser::StatementContext* ctx) override;

        virtual antlrcpp::Any visitFunction(TParser::FunctionContext* ctx) override;

        virtual antlrcpp::Any visitFunctionCall(TParser::FunctionCallContext* ctx) override;

        virtual antlrcpp::Any visitVariable(TParser::VariableContext* ctx) override;

        virtual antlrcpp::Any visitNamespaceBody(TParser::NamespaceBodyContext* ctx) override;

        virtual antlrcpp::Any visitBranch(TParser::BranchContext* ctx) override;

        virtual antlrcpp::Any visitForCycle(TParser::ForCycleContext* ctx) override;

        virtual antlrcpp::Any visitWhileCycle(TParser::WhileCycleContext* ctx) override;

        virtual antlrcpp::Any visitBody(TParser::BodyContext* ctx) override;

        virtual antlrcpp::Any visitType(TParser::TypeContext* ctx) override;

    private:
        const std::string m_FilePath = "Lang.cpp";
        std::ofstream stream;
    };
}



