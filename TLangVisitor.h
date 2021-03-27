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
    };
}



