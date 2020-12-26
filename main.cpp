#include <bits/stdc++.h>
#include "antlr4-runtime.h"
#include "HarshXLexer.cpp"
#include "HarshXParser.cpp"

#include "HarshXBuildAstVisitor.h"

#include "PostfixVisitor.h"
//#include "ast.h"

using namespace std;
using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::ifstream stream;

    cout << "Processing input file " << argv[1] << endl;
    stream.open(argv[1]);
    
    ANTLRInputStream input(stream);

    HarshXLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    HarshXParser parser(&tokens);    

    HarshXParser::ProgramContext *ctx = parser.program();

    HarshXVisitor *visitor = new HarshXBuildAstVisitor();

    ProgramASTnode *program_root = visitor->visitProgram(ctx);
    std::string s = argv[1];
    PostfixVisitor *pv = new PostfixVisitor(s);
    pv->visit(*program_root);
    return 0;
}