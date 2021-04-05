# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)
project(demo)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 17)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE /home/kolya/CLionProjects/malbolgepp/antlr-4.9.1-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(SampleGrammarLexer /home/kolya/CLionProjects/malbolgepp/TLexer.g4 LEXER
        PACKAGE antlrcpptest
        )
antlr_target(SampleGrammarParser /home/kolya/CLionProjects/malbolgepp/TParser.g4 PARSER VISITOR
        PACKAGE antlrcpptest
        )


# include generated files in project environment
include_directories(${ANTLR_SampleGrammarLexer_OUTPUT_DIR})
include_directories(${ANTLR_SampleGrammarParser_OUTPUT_DIR})
message(${ANTLR_SampleGrammarLexer_OUTPUT_DIR})
message(${ANTLR_SampleGrammarParser_OUTPUT_DIR})

# add generated grammar to demo binary target
add_executable(demo main.cpp
        ${ANTLR_SampleGrammarLexer_CXX_OUTPUTS}
        ${ANTLR_SampleGrammarParser_CXX_OUTPUTS} TLangVisitor.cpp TLangVisitor.h Elements/Baobab.cpp Elements/Baobab.h Elements/Element.cpp Elements/Element.h Elements/MainElement.cpp Elements/MainElement.h Elements/StatementElement.cpp Elements/StatementElement.h)
target_link_libraries(demo antlr4_static)
message(${ANTLR_SampleGrammarLexer_CXX_OUTPUTS})
message(${ANTLR_SampleGrammarParser_CXX_OUTPUTS})