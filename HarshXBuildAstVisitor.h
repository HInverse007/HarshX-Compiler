#include<bits/stdc++.h>
#include "ast.h"
#include "HarshXVisitor.h"

using namespace std;

class HarshXBuildAstVisitor : public HarshXVisitor
{
public:
    virtual antlrcpp::Any visitProgram(HarshXParser::ProgramContext *context)
    {
        //cout<<"In visitProgram"<<endl;
        
        listASTnode* vc = visit(context->call_start());
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        vc1 = vc->getVec();
        ProgramASTnode* node = new ProgramASTnode(vc1);
        //cout<<"Pass visitProgram"<<endl;
        //ProgramASTnode *node = new ProgramASTnode(vc);
        return (ProgramASTnode *) node;
    }
    virtual antlrcpp::Any visitCallstextDec(HarshXParser::CallstextDecContext *context)
    {
        //cout<<"In visitCallstextDec"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->externalDeclaration()));
        listASTnode* node = new listASTnode(vc);
        //ProgramASTnode *node = new ProgramASTnode(vc);
        //cout<<"pass visitCallstextDec"<<endl;
        return (listASTnode* )node;
    }
    virtual antlrcpp::Any visitCallstextDecCallst(HarshXParser::CallstextDecCallstContext *context)
    {
        //cout<<"In visitCallstextDecCallst"<<endl;
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        vc1->push_back(visit(context->externalDeclaration()));
        listASTnode* vc2 = visit(context->call_start());
        list<ASTnode*> *vc3 = new list<ASTnode*> ();
        vc3 = vc2->getVec();
        //list<ASTnode*>:: iterator it;
        for(auto it : *vc3)
        {
            vc1->push_back(it);
        }
        listASTnode* node = new listASTnode(vc1);
        //cout<<"pass visitCallstextDecCallst"<<endl;
        //ProgramASTnode *node = ProgramASTnode(vc1);
        return node;
    }
    virtual antlrcpp::Any visitExtdecDecaration(HarshXParser::ExtdecDecarationContext *context)
    {
        //cout<<"In visitExtdecDecaration"<<endl;
        ASTnode* node = visit(context->declaration());
        //cout<<"pass visitExtdecDecaration"<<endl;
        return node;
    }


    virtual antlrcpp::Any visitExtdecstatement(HarshXParser::ExtdecstatementContext *context)
    {
        //cout<<"In visitExtdecstatement"<<endl;
        ASTnode* node = visit(context->statement());
        //cout<<"pass visitExtdecstatement"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitExtdecfunction(HarshXParser::ExtdecfunctionContext *context)
    {
       // cout<<"In visitExtdecfunction"<<endl;
        ASTnode* node = visit(context->function());
        //cout<<"pass visitExtdecfunction"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitListdeclist(HarshXParser::ListdeclistContext *context)
    {
        //cout<<"In visitListdeclist"<<endl;

        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->declaration()));
        listASTnode* n = visit(context->list());
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        vc1 = n->getVec();
        for(auto it : *vc1)
        {
            vc->push_back(it);
        }
        listASTnode* node = new listASTnode(vc);
        //cout<<"pass visitListdeclist"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitListstatementlist(HarshXParser::ListstatementlistContext *context)
    {
       // cout<<"In visitListstatementlist"<<endl;

        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->statement()));
        listASTnode* n = visit(context->list());
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        vc1 = n->getVec();
        for(auto it : *vc1)
        {
            vc->push_back(it);
        }
        listASTnode* node = new listASTnode(vc);
        //cout<<"pass visitListstatementlist"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitListstatement(HarshXParser::ListstatementContext *context)
    {
       // cout<<"In visitListstatement"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->statement()));
        listASTnode* node = new listASTnode(vc);
       // cout<<"pass visitListstatement"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitListdeclaration(HarshXParser::ListdeclarationContext *context)
    {
       // cout<<"In visitListdeclaration"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->declaration()));
        listASTnode* node = new listASTnode(vc);
       // cout<<"pass visitListdeclaration"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitFunc1(HarshXParser::Func1Context *context)
    {
       // cout<<"In visitFunc1"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        string s1 = visit(context->typeSpecifier());
        string s2 = context->ID()->getText();
        listASTnode* n = visit(context->declarationList());
        vc = n->getVec();
        ASTnode* m = visit(context->compoundStatement());
        FunctionASTnode* node = new FunctionASTnode(s1,s2,vc,m);
      //  cout<<"pass visitFunc1"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitFunc2(HarshXParser::Func2Context *context)
    {
     //   cout<<"In visitFunc1"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        string s1 = visit(context->typeSpecifier());
        string s2 = context->ID()->getText();
        ASTnode* m = visit(context->compoundStatement());
        FunctionASTnode* node = new FunctionASTnode(s1,s2,vc,m);
      //  cout<<"pass visitFunc1"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitDecllistdecl(HarshXParser::DecllistdeclContext *context)
    {
      //  cout<<"In visitDecllistdecl"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->declarator()));
        listASTnode* node = new listASTnode(vc);
       // cout<<"pass visitDecllistdecl"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitDecllistdecl2(HarshXParser::Decllistdecl2Context *context)
    {
       // cout<<"In visitDecllistdecl2"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->declarator()));
        listASTnode* n = visit(context->declarationList());
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        vc1 = n->getVec();
        for(auto it : *vc1)
        {
            vc->push_back(it);
        }
        listASTnode* node = new listASTnode(vc);
     //   cout<<"pass visitDecllistdecl2"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitDecltypespeci(HarshXParser::DecltypespeciContext *context)
    {
     //   cout<<"In visitDecltypespeci"<<endl;
        string s1 = visit(context->typeSpecifier());
        string s2 = context->ID()->getText();
        DeclaratorASTnode* node = new DeclaratorASTnode(s1,s2,false);
       // cout<<"pass visitDecltypespeci"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitDecltypespeci2(HarshXParser::Decltypespeci2Context *context)
    {
       // cout<<"In visitDecltypespeci2"<<endl;
        string s1 = visit(context->typeSpecifier());
        string s2 = context->ID()->getText();
        DeclaratorASTnode* node = new DeclaratorASTnode(s1,s2,true);
       // cout<<"pass visitDecltypespeci2"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitStateinput(HarshXParser::StateinputContext *context)
    {
       // cout<<"In visitStateinput"<<endl;
        ASTnode* node = visit(context->inputStatement());
       // cout<<"pass visitStateinput"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitStateprint(HarshXParser::StateprintContext *context)
    {
       // cout<<"In visitStateprint"<<endl;

        ASTnode* node = visit(context->printStatement());
       // cout<<"pass visitStateprint"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitStatereturn(HarshXParser::StatereturnContext *context)
    {
     //   cout<<"In visitStatereturn"<<endl;

        ASTnode* node = visit(context->returnStatement());
      //  cout<<"pass visitStatereturn"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitStateexpr(HarshXParser::StateexprContext *context)
    {
       // cout<<"In visitStateexpr"<<endl;

        ASTnode* node = visit(context->expressionStatement());
       // cout<<"pass visitStateexpr"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitStatecomp(HarshXParser::StatecompContext *context)
    {
      //  cout<<"In visitStatecomp"<<endl;

        ASTnode* node = visit(context->compoundStatement());
      //  cout<<"pass visitStatecomp"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitStatecont(HarshXParser::StatecontContext *context)
    {
      //  cout<<"In visitStatecont"<<endl;

        ASTnode* node = visit(context->controlStatement());
      //  cout<<"pass visitStatecont"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitStatefunc(HarshXParser::StatefuncContext *context)
    {
      //  cout<<"In visitStatefunc"<<endl;

        ASTnode* node = visit(context->functionCall());
      //  cout<<"pass visitStatefunc"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitStatestop(HarshXParser::StatestopContext *context)
    {
      //  cout<<"In visitStatestop"<<endl;
        string s = context->STOP()->getText();
        StrLitASTnode* node = new StrLitASTnode(s);
      //  cout<<"pass visitStatestop"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitCompstatelist(HarshXParser::CompstatelistContext *context)
    {
      //  cout<<"In visitCompstatelist"<<endl;
        listASTnode* n = visit(context->list());
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc = n->getVec();
        CompoundASTnode* node = new CompoundASTnode(vc);
      //  cout<<"pass visitCompstatelist"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitCompstateempty(HarshXParser::CompstateemptyContext *context)
    {
      //  cout<<"In visitCompstateempty"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        CompoundASTnode* node = new CompoundASTnode(vc);
      //  cout<<"Pass visitCompstateempty"<<endl;
        return (ASTnode*)node;
    }

    virtual antlrcpp::Any visitContstatecondition(HarshXParser::ContstateconditionContext *context)
    {
      //  cout<<"In visitContstatecondition"<<endl;
        ASTnode* node = visit(context->conditional());
      //  cout<<"pass visitContstatecondition"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitContstateloop(HarshXParser::ContstateloopContext *context)
    {
      //  cout<<"In visitContstateloop"<<endl;
        ASTnode* node = visit(context->loop());
      //  cout<<"pass visitContstateloop"<<endl;
        return node;   
    }

    virtual antlrcpp::Any visitFunctcall1(HarshXParser::Functcall1Context *context)
    {
      //  cout<<"In visitFunctcall1"<<endl;

        string s = context->ID()->getText();
        list<ASTnode*> *vc = new list<ASTnode*> ();
        listASTnode* m = visit(context->parameterList());
        vc = m->getVec();
        FunctionCallASTnode* node = new FunctionCallASTnode(s,vc);
       // cout<<"pass visitFunctcall1"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitFunctcall2(HarshXParser::Functcall2Context *context)
    {
     //   cout<<"In visitFunctcall2"<<endl;

        string s = context->ID()->getText();
        list<ASTnode*> *vc = new list<ASTnode*> ();
        FunctionCallASTnode* node = new FunctionCallASTnode(s,vc);
      //  cout<<"pass visitFunctcall2"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitParalistopexpr(HarshXParser::ParalistopexprContext *context)
    {
       // cout<<"In visitParalistopexpr"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->operationExpression()));
        listASTnode* node = new listASTnode(vc);
      //  cout<<"pass visitParalistopexpr"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitParalistopexpr2(HarshXParser::Paralistopexpr2Context *context)
    {
     //   cout<<"In visitParalistopexpr2"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->operationExpression()));
        listASTnode* m = visit(context->parameterList());
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        vc1 = m->getVec();
        for(auto it : * vc1)
        {
            vc->push_back(it);
        }
        listASTnode* node = new listASTnode(vc);
      //  cout<<"pass visitParalistopexpr2"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitDeclarationtypespeci(HarshXParser::DeclarationtypespeciContext *context)
    {
    //  cout<<"In visitDeclarationtypespeci"<<endl;
        string s = visit(context->typeSpecifier());
        listASTnode* vc = visit(context->iDlist());
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        vc1 = vc->getVec();
        list<VariableASTnode*> *vc2 = new list<VariableASTnode*> ();
        for(auto it : *vc1)
        {
            VariableASTnode* temp = (VariableASTnode*) it;
            vc2->push_back(temp);
        }
        //vc2 = (VariableASTnode*) vc1;
        DeclarationASTnode *node = new DeclarationASTnode(s,vc2);
      //  cout<<"pass visitDeclarationtypespeci"<<endl;
        return (ASTnode *) node;
    }

    virtual antlrcpp::Any visitInpstatescan(HarshXParser::InpstatescanContext *context)
    {
     //   cout<<"In visitInpstatescan"<<endl;

        string s = context->SCAN()->getText();
        ASTnode* vc = visit(context->expression());

        InOutASTnode* node = new InOutASTnode(s,vc);

       // cout<<"pass visitInpstatescan"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitPristateprint(HarshXParser::PristateprintContext *context)
    {
      //  cout<<"In visitPristateprint"<<endl;

        string s = context->PRINT()->getText();
        ASTnode* vc = visit(context->operationExpression());

        InOutASTnode* node = new InOutASTnode(s,vc);
       // cout<<"pass visitPristateprint"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitRetstateret(HarshXParser::RetstateretContext *context)
    {
      //  cout<<"In visitRetstateret"<<endl;

        string s = context->RETURN()->getText();
        ASTnode* vc = visit(context->operationExpression());

        InOutASTnode* node = new InOutASTnode(s,vc);
       // cout<<"pass visitRetstateret"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitExprstateassignexpr(HarshXParser::ExprstateassignexprContext *context)
    {
       // cout<<"In visitExprstateassignexpr"<<endl;

        ASTnode* node = visit(context->assignmentExpression());
       // cout<<"pass visitExprstateassignexpr"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitTypespeciint(HarshXParser::TypespeciintContext *context)
    {
    //  cout<<"In visitTypespeciint"<<endl;
        string s = context->INTEGER()->getText();
        //StrLitASTnode* node = new StrLitASTnode(s);
      //  cout<<"Pass visitTypespeciint"<<endl;
        return s;
    }
    virtual antlrcpp::Any visitTypespecibool(HarshXParser::TypespeciboolContext *context)
    {
        //cout<<"In visitTypespeciint"<<endl;
        string s = context->BOOLEAN()->getText();
        // StrLitASTnode* node = new StrLitASTnode(s);
        // return (StrLitASTnode* )node;
      //  cout<<"pass visitTypespeciint"<<endl;
        return s;
    }
    virtual antlrcpp::Any visitTypespecichar(HarshXParser::TypespecicharContext *context)
    {
    //  cout<<"In visitTypespecichar"<<endl;
        string s = context->CHARACTER()->getText();
        // StrLitASTnode* node = new StrLitASTnode(s);
        // return (StrLitASTnode* )node;
      //  cout<<"pass visitTypespecichar"<<endl;
        return s;
    }
    virtual antlrcpp::Any visitTypespeciuint(HarshXParser::TypespeciuintContext *context)
    {
    //  cout<<"In visitTypespeciuint"<<endl;
        string s = context->UINTEGER()->getText();
        // StrLitASTnode* node = new StrLitASTnode(s);
        // return (StrLitASTnode* )node;
      //  cout<<"In visitTypespeciuint"<<endl;
        return s;
    }
    virtual antlrcpp::Any visitIdlistvar(HarshXParser::IdlistvarContext *context)
    {
    //  cout<<"In visitIdlistvar"<<endl;
        list<ASTnode*> *vc = new list<ASTnode*> ();
        vc->push_back(visit(context->variable()));
        listASTnode* node = new listASTnode(vc);
      //  cout<<"pass visitIdlistvar"<<endl;
        return (listASTnode* )node;
        //return visit(context->variable());
    }
    virtual antlrcpp::Any visitIdlistvar2(HarshXParser::Idlistvar2Context *context)
    {
    //  cout<<"In visitIdlistvar2"<<endl;
        list<ASTnode*> *vc1 = new list<ASTnode*> ();
        list<ASTnode*> *vc3 = new list<ASTnode*> ();
        listASTnode* vc2;
        vc1->push_back(visit(context->variable()));
        vc2 = visit(context->iDlist());
        vc3 = vc2->getVec();
        for(auto it : *vc3)
        {
            vc1->push_back(it);
        }
        listASTnode* node = new listASTnode(vc1);
      //  cout<<"pass visitIdlistvar2"<<endl;
        return (listASTnode* ) node;
       // return visit(context->variable());
    }
    virtual antlrcpp::Any visitVar(HarshXParser::VarContext *context)
    {
    //  cout<<"In visitVar"<<endl;
        string s = context->ID()->getText();
        VariableASTnode* node = new VariableASTnode(s,0,0,0);
      //  cout<<"pass visitVar"<<endl;
        return (ASTnode *) node;
    }
    virtual antlrcpp::Any visitVar1darray(HarshXParser::Var1darrayContext *context)
    {
    //  cout<<"In visitVar1darray"<<endl;
        string s = context->ID()->getText();
        int n = stoi(context->NUMBER()->getText());
        VariableASTnode* node = new VariableASTnode(s,1,n,0);
       // cout<<"Pass visitVar1darray"<<endl;
        return (ASTnode *)node;
    }
    virtual antlrcpp::Any visitVar2darray(HarshXParser::Var2darrayContext *context)
    {
        //cout<<"In visitVar2darray";
        string s = context->ID()->getText();
        int n = stoi(context->NUMBER(0)->getText());
        int m = stoi(context->NUMBER(1)->getText());
        VariableASTnode* node = new VariableASTnode(s,2,n,m);
       // cout<<"pass visitVar2darray"<<endl;
        return (ASTnode *) node;
    }

    virtual antlrcpp::Any visitOpexpraritexpr(HarshXParser::OpexpraritexprContext *context)
    {
     //   cout<<"In visitOpexpraritexpr"<<endl;

        ASTnode* node = visit(context->arithmeticExpression());

      //  cout<<"pass visitOpexpraritexpr"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitOpexprexpr(HarshXParser::OpexprexprContext *context)
    {
      //  cout<<"In visitOpexprexpr"<<endl;

        ASTnode* node = visit(context->expression());

      //  cout<<"pass visitOpexprexpr"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitOpexprnum(HarshXParser::OpexprnumContext *context)
    {
      //  cout<<"In visitOpexprnum"<<endl;

        int val = stoi(context->NUMBER()->getText());
        IntLitASTnode* node = new IntLitASTnode(val);

       // cout<<"pass visitOpexprnum"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitOpexprtrue(HarshXParser::OpexprtrueContext *context)
    {
       // cout<<"In visitOpexprtrue"<<endl;
        BoolLitASTnode* node = new BoolLitASTnode(1);
       // cout<<"pass visitOpexprtrue"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitOpexprfalse(HarshXParser::OpexprfalseContext *context)
    {
       // cout<<"In visitOpexprfalse"<<endl;
        BoolLitASTnode* node = new BoolLitASTnode(0);
       // cout<<"pass visitOpexprfalse"<<endl;
        return (ASTnode* )node;   
    }

    virtual antlrcpp::Any visitOpexprboolexpr(HarshXParser::OpexprboolexprContext *context)
    {
       // cout<<"In visitOpexprboolexpr"<<endl;
        ASTnode* node = visit(context->booleanExpression());
       // cout<<"pass visitOpexprboolexpr"<<endl;
        return (ASTnode *) node;
    }

    virtual antlrcpp::Any visitOpexpropexpr(HarshXParser::OpexpropexprContext *context)
    {
      //  cout<<"In visitOpexpropexpr"<<endl;
        ASTnode* node = visit(context->optionExpression());
      //  cout<<"pass visitOpexpropexpr"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitAritexpr(HarshXParser::AritexprContext *context)
    {
       // cout<<"In visitAritexpr"<<endl;
        ASTnode* n = visit(context->operationExpression(0));
        ASTnode* m = visit(context->operationExpression(1));
        string s = visit(context->arithmeticOperator());

        BinaryASTnode* node = new BinaryASTnode(n,s,m);
       // cout<<"pass visitAritexpr"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitBoolexpr(HarshXParser::BoolexprContext *context)
    {
      //  cout<<"In visitBoolexpr"<<endl;
        ASTnode* n = visit(context->operationExpression(0));
        ASTnode* m = visit(context->operationExpression(1));
        string s = visit(context->booleanOperator());

        BinaryASTnode* node = new BinaryASTnode(n,s,m);
      //  cout<<"pass visitBoolexpr"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitOpexprter(HarshXParser::OpexprterContext *context)
    {
       // cout<<"In visitOpexprter"<<endl;
        ASTnode* n1 = visit(context->conditionalExpression());
        ASTnode* n2 = visit(context->operationExpression(0));
        ASTnode* n3 = visit(context->operationExpression(1));

        OptionASTnode* node = new OptionASTnode(n1,n2,n3);
       // cout<<"pass visitOpexprter"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitCondexprcond(HarshXParser::CondexprcondContext *context)
    {
      //  cout<<"In visitCondexprcond"<<endl;

        ASTnode* node = visit(context->condition());
      //  cout<<"pass visitCondexprcond"<<endl;
        return node;
    }

    virtual antlrcpp::Any visitCondexprcond2(HarshXParser::Condexprcond2Context *context)
    {
      //  cout<<"In visitCondexprcond2"<<endl;
        ASTnode* n1 = visit(context->conditionalExpression(0));
        ASTnode* n2 = visit(context->conditionalExpression(1));
        string s = visit(context->logicalOperator());

        BinaryASTnode* node = new BinaryASTnode(n1,s,n2);
      //  cout<<"pass visitCondexprcond2"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitAssignexpr1(HarshXParser::Assignexpr1Context *context)
    {
       // cout<<"In visitAssignexpr1"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        n1 = visit(context->expression());
        n2 = visit(context->operationExpression());
        string s = visit(context->assignmentOperator());
        BinaryASTnode* node = new BinaryASTnode(n1,s,n2);
       // cout<<"pass visitAssignexpr1"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitAssignexpr2(HarshXParser::Assignexpr2Context *context)
    {
      //  cout<<"In visitAssignexpr2"<<endl;
        ASTnode* n1 = visit(context->expression());
        string s = context->EQUAL()->getText();
        string s1 = context->ID()->getText();
        Str1LitASTnode* m = new Str1LitASTnode(s1);
        ASTnode* n2 = (ASTnode* )m;
        BinaryASTnode* node = new BinaryASTnode(n1,s,n2);
      //  cout<<"pass visitAssignexpr2"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitAssignexpr3(HarshXParser::Assignexpr3Context *context)
    {
      //  cout<<"In visitAssignexpr3"<<endl;
        ASTnode* n1 = visit(context->expression());
        string s = visit(context->assignmentOperator());
        ASTnode* n2 = visit(context->functionCall());
        BinaryASTnode* node = new BinaryASTnode(n1,s,n2);
      //  cout<<"pass visitAssignexpr3"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitCondopexprcom(HarshXParser::CondopexprcomContext *context)
    {
      //  cout<<"In visitCondopexprcom"<<endl;

        ASTnode* n1 = visit(context->operationExpression(0));
        ASTnode* n2 = visit(context->operationExpression(1));
        string s = visit(context->comparisonOperator());
        BinaryASTnode* node = new BinaryASTnode(n1,s,n2);
       // cout<<"pass visitCondopexprcom"<<endl;
        return (ASTnode* )node;
    }

    virtual antlrcpp::Any visitExpr(HarshXParser::ExprContext *context)
    {
      //  cout<<"In visitExpr"<<endl;
        string s = context->ID()->getText();
        StrLitASTnode* m = new StrLitASTnode(s);
        ExpressionASTnode* node =  new ExpressionASTnode(m,NULL,NULL);
      //  cout<<"pass visitExpr"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitExpr1darray(HarshXParser::Expr1darrayContext *context)
    {
      //  cout<<"In visitExpr1darray"<<endl;
        string s = context->ID()->getText();
        StrLitASTnode* m = new StrLitASTnode(s);
        ASTnode* n = visit(context->operationExpression());
        ExpressionASTnode* node =  new ExpressionASTnode(m,n,NULL);
      //  cout<<"pass visitExpr1darray"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitExpr2darray(HarshXParser::Expr2darrayContext *context)
    {
       // cout<<"In visitExpr2darray"<<endl;
        string s = context->ID()->getText();
        StrLitASTnode* m = new StrLitASTnode(s);
        ASTnode* n1 = visit(context->operationExpression(0));
        ASTnode* n2 = visit(context->operationExpression(1));
        ExpressionASTnode* node =  new ExpressionASTnode(m,n1,n2);
      //  cout<<"pass visitExpr2darray"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitCondif(HarshXParser::CondifContext *context)
    {
      //  cout<<"In visitCondif"<<endl;
        string s = context->IF()->getText();
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        n1 = visit(context->conditionalExpression());
        n2 = visit(context->compoundStatement());
        ConditionalASTnode* node = new ConditionalASTnode(s,n1,n2,"",NULL);
       // cout<<"pass visitCondif"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitCondifelse(HarshXParser::CondifelseContext *context)
    {
      //  cout<<"In visitCondifelse"<<endl;
        string s1 = context->IF()->getText();
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        n1 = visit(context->conditionalExpression());
        n2 = visit(context->compoundStatement());
        string s2 = context->ELSE()->getText();
        n3 = visit(context->conditional());
        ConditionalASTnode* node = new ConditionalASTnode(s1,n1,n2,s2,n3);
      //  cout<<"pass visitCondifelse"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitCondifelse2(HarshXParser::Condifelse2Context *context)
    {
      //  cout<<"In visitCondifelse2"<<endl;
        string s1 = context->IF()->getText();
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        n1 = visit(context->conditionalExpression());
        n2 = visit(context->compoundStatement(0));
        string s2 = context->ELSE()->getText();
        n3 = visit(context->compoundStatement(1));
        ConditionalASTnode* node = new ConditionalASTnode(s1,n1,n2,s2,n3);
     //   cout<<"pass visitCondifelse"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopwhile1(HarshXParser::Loopwhile1Context *context)
    {
      //  cout<<"In visitLoopwhile1"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        string s = context->WHILE()->getText();
        n1 = visit(context->conditionalExpression());
        n2 = visit(context->compoundStatement());
        WhileASTnode* node = new WhileASTnode(s,n1,n2);
      //  cout<<"pass visitLoopwhile1"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopwhile2(HarshXParser::Loopwhile2Context *context)
    {
      //  cout<<"In visitLoopwhile2"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        string s = context->WHILE()->getText();
        n1 = NULL;
        n2 = visit(context->compoundStatement());
        WhileASTnode* node = new WhileASTnode(s,n1,n2);
      //  cout<<"pass visitLoopwhile2"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor1(HarshXParser::Loopfor1Context *context)
    {
      //  cout<<"In visitLoopfor1"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = NULL;
        n2 = NULL;
        n3 = NULL;
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
      //  cout<<"pass visitLoopfor1"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor2(HarshXParser::Loopfor2Context *context)
    {
      //  cout<<"In visitLoopfor2"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = visit(context->assignmentExpression());
        n2 = NULL;
        n3 = NULL;
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
      //  cout<<"pass visitLoopfor2"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor3(HarshXParser::Loopfor3Context *context)
    {
       // cout<<"In visitLoopfor3"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = NULL;
        n2 = visit(context->conditionalExpression());
        n3 = NULL;
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
       // cout<<"pass visitLoopfor3"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor4(HarshXParser::Loopfor4Context *context)
    {
       // cout<<"In visitLoopfor4"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = NULL;
        n2 = NULL;
        n3 = visit(context->assignmentExpression());
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
       // cout<<"pass visitLoopfor4"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor5(HarshXParser::Loopfor5Context *context)
    {
      //  cout<<"In visitLoopfor5"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = visit(context->assignmentExpression());
        n2 = visit(context->conditionalExpression());
        n3 = NULL;
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
      //  cout<<"pass visitLoopfor5"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor6(HarshXParser::Loopfor6Context *context)
    {
     //   cout<<"In visitLoopfor6"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = visit(context->assignmentExpression(0));
        n2 = NULL;
        n3 = visit(context->assignmentExpression(1));
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
      //  cout<<"pass visitLoopfor6"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor7(HarshXParser::Loopfor7Context *context)
    {
      //  cout<<"In visitLoopfor7"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = NULL;
        n2 = visit(context->conditionalExpression());
        n3 = visit(context->assignmentExpression());
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
      //  cout<<"pass visitLoopfor7"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitLoopfor8(HarshXParser::Loopfor8Context *context)
    {
       // cout<<"In visitLoopfor8"<<endl;
        ASTnode* n1;
        ASTnode* n2;
        ASTnode* n3;
        ASTnode* n4;
        n1 = visit(context->assignmentExpression(0));
        n2 = visit(context->conditionalExpression());
        n3 = visit(context->assignmentExpression(1));
        n4 = visit(context->compoundStatement());
        string s = context->FOR()->getText();
        ForASTnode* node = new ForASTnode(s,n1,n2,n3,n4);
      //  cout<<"pass visitLoopfor8"<<endl;
        return (ASTnode*) node;
    }

    virtual antlrcpp::Any visitAritopplus(HarshXParser::AritopplusContext *context)
    {
     //   cout<<"In visitAritopplus"<<endl;

        string s = context->PLUS()->getText();
      //  cout<<"pass visitAritopplus"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitAritopminus(HarshXParser::AritopminusContext *context)
    {
       // cout<<"In visitAritopminus"<<endl;

        string s = context->MINUS()->getText();
       // cout<<"pass visitAritopminus"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitAritopmul(HarshXParser::AritopmulContext *context)
    {
      //  cout<<"In visitAritopmul"<<endl;

        string s = context->MUL()->getText();
      //  cout<<"pass visitAritopmul"<<endl;
        return s;   
    }

    virtual antlrcpp::Any visitAritopdiv(HarshXParser::AritopdivContext *context)
    {
       // cout<<"In visitAritopdiv"<<endl;

        string s = context->DIV()->getText();
       // cout<<"pass visitAritopdiv"<<endl;
        return s;   
    }

    virtual antlrcpp::Any visitAritopmod(HarshXParser::AritopmodContext *context)
    {
       // cout<<"In visitAritopmod"<<endl;

        string s = context->MOD()->getText();
       // cout<<"pass visitAritopmod"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitCompoplt(HarshXParser::CompopltContext *context)
    {
       // cout<<"In visitCompoplt"<<endl;

        string s = context->LT()->getText();
       // cout<<"pass visitCompoplt"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitCompopgt(HarshXParser::CompopgtContext *context)
    {
      //  cout<<"In visitCompopgt"<<endl;

        string s = context->GT()->getText();
      //  cout<<"pass visitCompopgt"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitCompopeq(HarshXParser::CompopeqContext *context)
    {
      //  cout<<"In visitCompopeq"<<endl;

        string s = context->EQ()->getText();
      //  cout<<"pass visitCompopeq"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitCompopnoteq(HarshXParser::CompopnoteqContext *context)
    {
      //  cout<<"In visitCompopnoteq"<<endl;

        string s = context->NOTEQ()->getText();
      //  cout<<"pass visitCompopnoteq"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitCompoplte(HarshXParser::CompoplteContext *context)
    {
      //  cout<<"In visitCompoplte"<<endl;

        string s = context->LTE()->getText();
      //  cout<<"pass visitCompoplte"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitCompopgte(HarshXParser::CompopgteContext *context)
    {
      //  cout<<"In visitCompopgte"<<endl;

        string s = context->GTE()->getText();
       // cout<<"pass visitCompopgte"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitBoolopand(HarshXParser::BoolopandContext *context)
    {
       // cout<<"In visitBoolopand"<<endl;

        string s = context->AND()->getText();
      //  cout<<"pass visitBoolopand"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitBoolopor(HarshXParser::BooloporContext *context)
    {
      //  cout<<"In visitBoolopor"<<endl;

        string s = context->OR()->getText();
       // cout<<"pass visitBoolopor"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitBoolopxor(HarshXParser::BoolopxorContext *context)
    {
      //  cout<<"In visitBoolopxor"<<endl;

        string s = context->XOR()->getText();
       // cout<<"pass visitBoolopxor"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitBooloplsft(HarshXParser::BooloplsftContext *context)
    {
      //  cout<<"In visitBooloplsft"<<endl;

        string s = context->LEFTSHIFT()->getText();
      //  cout<<"pass visitBooloplsft"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitBooloprsft(HarshXParser::BooloprsftContext *context)
    {
       // cout<<"In visitBooloprsft"<<endl;

        string s = context->RIGHTSHIFT()->getText();
      //  cout<<"pass visitBooloprsft"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitLogopandc(HarshXParser::LogopandcContext *context)
    {
       // cout<<"In visitLogopandc"<<endl;

        string s = context->ANDC()->getText();
       // cout<<"pass visitLogopandc"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitLogoporc(HarshXParser::LogoporcContext *context)
    {
       // cout<<"In visitLogoporc"<<endl;

        string s = context->ORC()->getText();
       // cout<<"pass visitLogoporc"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitAssignopeq(HarshXParser::AssignopeqContext *context)
    {
      //  cout<<"In visitAssignopeq"<<endl;
        string s = context->EQUAL()->getText();
      //  cout<<"pass visitAssignopeq"<<endl;;
        return s;
    }

    virtual antlrcpp::Any visitAssignoppl(HarshXParser::AssignopplContext *context)
    {
      //  cout<<"In visitAssignoppl"<<endl;
        string s = context->PLUSE()->getText();
      //  cout<<"pass visitAssignoppl"<<endl;
        return s;
    }

    virtual antlrcpp::Any visitAssignopmi(HarshXParser::AssignopmiContext *context)
    {
      //  cout<<"In visitAssignopmi"<<endl;
        string s = context->MINUSE()->getText();
      //  cout<<"pass visitAssignopmi";
        return s;
    }

    virtual antlrcpp::Any visitAssignopmu(HarshXParser::AssignopmuContext *context)
    {
      //  cout<<"In visitAssignopmu"<<endl;
        string s = context->MULE()->getText();
      //  cout<<"pass visitAssignopmu";
        return s;
    }

    virtual antlrcpp::Any visitAssignopdi(HarshXParser::AssignopdiContext *context)
    {
       // cout<<"In visitAssignopdi"<<endl;
        string s = context->DIVE()->getText();
       // cout<<"pass visitAssignopdi";
        return s;
    }

    virtual antlrcpp::Any visitAssignopmo(HarshXParser::AssignopmoContext *context)
    {
       // cout<<"In visitAssignopmo"<<endl;
        string s = context->MODE()->getText();
      //  cout<<"pass visitAssignopmo";
        return s;
    }

    virtual antlrcpp::Any visitAssignopande(HarshXParser::AssignopandeContext *context)
    {
       // cout<<"In visitAssignopande"<<endl;
        string s = context->ANDE()->getText();
       // cout<<"pass visitAssignopande";
        return s;
    }

    virtual antlrcpp::Any visitAssignopore(HarshXParser::AssignoporeContext *context)
    {
       // cout<<"In visitAssignopore"<<endl;
        string s = context->ORE()->getText();
       // cout<<"pass visitAssignopore";
        return s;
    }

    virtual antlrcpp::Any visitAssignopxore(HarshXParser::AssignopxoreContext *context)
    {
       // cout<<"In visitAssignopxore"<<endl;
        string s = context->XORE()->getText();
       // cout<<"pass visitAssignopxore";
        return s;
    }

    virtual antlrcpp::Any visitAssignoplsft(HarshXParser::AssignoplsftContext *context)
    {
      //  cout<<"In visitAssignoplsft"<<endl;
        string s = context->LEFTSHIFTE()->getText();
       // cout<<"pass visitAssignoplsft";
        return s;
    }

    virtual antlrcpp::Any visitAssignoprsft(HarshXParser::AssignoprsftContext *context)
    {
       // cout<<"In visitAssignoprsft"<<endl;
        string s = context->RIGHTSHIFTE()->getText();
       //   cout<<"pass visitAssignoprsft";
        return s;
    }
};