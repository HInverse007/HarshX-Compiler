#include<bits/stdc++.h>

#include <list>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"


class ProgramASTnode;
class VariableASTnode;
class listASTnode;
class DeclarationASTnode;
class IntLitASTnode;
class BoolLitASTnode;
class StrLitASTnode;
class Str1LitASTnode;
class InOutASTnode;
class ExpressionASTnode;
class BinaryASTnode;
class OptionASTnode;
class FunctionCallASTnode;
class CompoundASTnode;
class ConditionalASTnode;
class WhileASTnode;
class ForASTnode;
class FunctionASTnode;
class DeclaratorASTnode;

class ASTvisitor {
  public:

    virtual llvm::Value * visit(VariableASTnode& node) = 0;
    virtual llvm::Value * visit(DeclarationASTnode& node) = 0;
    virtual llvm::Value * visit(ProgramASTnode& node) = 0;
    virtual llvm::Value * visit(IntLitASTnode& node) = 0;
    virtual llvm::Value * visit(BoolLitASTnode& node) = 0;
    virtual llvm::Value * visit(StrLitASTnode& node) = 0;
    virtual llvm::Value * visit(Str1LitASTnode& node) = 0;
    virtual llvm::Value * visit(listASTnode& node) = 0;
    virtual llvm::Value * visit(InOutASTnode& node) = 0;
    virtual llvm::Value * visit(ExpressionASTnode& node) = 0;
    virtual llvm::Value * visit(BinaryASTnode& node) = 0;
    virtual llvm::Value * visit(OptionASTnode& node) = 0;
    virtual llvm::Value * visit(FunctionCallASTnode& node) = 0;
    virtual llvm::Value * visit(CompoundASTnode& node) = 0;
    virtual llvm::Value * visit(ConditionalASTnode& node) = 0;
    virtual llvm::Value * visit(WhileASTnode& node) = 0;
    virtual llvm::Value * visit(ForASTnode& node) = 0;
    virtual llvm::Value * visit(FunctionASTnode& node) = 0;
    virtual llvm::Value * visit(DeclaratorASTnode& node) = 0;
};



class ASTnode {
     public :
     virtual ~ASTnode()
     {
     }
     virtual llvm::Value * accept(ASTvisitor& V) = 0;

};


class ProgramASTnode: public ASTnode {
    public:
    std::list<ASTnode *> *vec;
    ProgramASTnode(std::list<ASTnode*> *_vec):
    vec(_vec){}
    std::list<ASTnode*> *getVec() {
        return vec;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class listASTnode: public ASTnode{
    public:
    std::list<ASTnode*> *vec;
    listASTnode(std::list<ASTnode*> *_vec):
    vec(_vec){}
    std::list<ASTnode *> *getVec() {
        return vec;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class VariableASTnode: public ASTnode {
    public:
    std::string strlit;
    int intlit1;
    int intlit2;
    int intlit3;
    VariableASTnode (std::string _strlit, int _intlit1, int _intlit2, int _intlit3) :
    strlit(_strlit), intlit1(_intlit1), intlit2(_intlit2), intlit3(_intlit3){}
    std::string getStrLit() {
        return strlit;
    }
    int getIntLit1() {
        return intlit1;
    }
    int getIntLit2() {
        return intlit2;
    }
    int getIntLit3() {
        return intlit3;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class DeclarationASTnode: public ASTnode {
    public:
    std::list<VariableASTnode*> *vec;
    std::string strlit;
    DeclarationASTnode(std::string _strlit, std::list<VariableASTnode*> *_vec):
    strlit(_strlit), vec(_vec){}
    std::string getStrLit() {
        return strlit;
    }
    std::list<VariableASTnode*> *getVec() {
        return vec;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class IntLitASTnode: public ASTnode {
    public:
    int intlit;
    IntLitASTnode(int _intlit): 
    intlit(_intlit){}
    int getIntLit() {
        return intlit;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class BoolLitASTnode: public ASTnode {
    public:
    int intlit;
    BoolLitASTnode(int _intlit): 
    intlit(_intlit){}
    int getIntLit() {
        return intlit;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class StrLitASTnode: public ASTnode {
    public:
    std::string strlit;
    StrLitASTnode(std::string _strlit): 
    strlit(_strlit){}
    std::string getStrLit() {
        return strlit;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class Str1LitASTnode: public ASTnode {
    public:
    std::string strlit;
    Str1LitASTnode(std::string _strlit): 
    strlit(_strlit){}
    std::string getStrLit() {
        return strlit;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class InOutASTnode: public ASTnode {
    public:
    ASTnode *first;
    std::string strlit;
    InOutASTnode(std::string _strlit, ASTnode* _first):
    strlit(_strlit), first(_first){}
    std::string getStrLit() {
        return strlit;
    }
    ASTnode* getFirst() {
        return first;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class ExpressionASTnode: public ASTnode {
    public:
    ASTnode *first;
    ASTnode *second;
    ASTnode *third;
    ExpressionASTnode (ASTnode* _first, ASTnode* _second,ASTnode* _third) :
    first(_first), second(_second), third(_third){}
    ASTnode* getFirst() {
        return first;
    }
    ASTnode* getSecond() {
        return second;
    }
    ASTnode* getThird()
    {
        return third;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class BinaryASTnode: public ASTnode {
    public:
    ASTnode *first;
    ASTnode *second;
    std::string strlit;
    BinaryASTnode(ASTnode* _first, std::string _strlit, ASTnode* _second):
    first(_first), strlit(_strlit), second(_second){}
    ASTnode* getFirst() {
        return first;
    }
    ASTnode* getSecond() {
        return second;
    }
    std::string getStrLit() {
        return strlit;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};


class OptionASTnode: public ASTnode {
    public:
    ASTnode *first;
    ASTnode *second;
    ASTnode *third;
    OptionASTnode(ASTnode* _first, ASTnode* _second, ASTnode* _third):
    first(_first), second(_second), third(_third){}
    ASTnode* getFirst() {
        return first;
    }
    ASTnode* getSecond() {
        return second;
    }
    ASTnode* getThird() {
        return third;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};


class FunctionCallASTnode: public ASTnode {
    public:
    std::list<ASTnode*> *vec;
    std::string strlit;
    FunctionCallASTnode(std::string _strlit, std::list<ASTnode*> *_vec):
    strlit(_strlit), vec(_vec){}
    std::string getStrLit() {
        return strlit;
    }
    std::list<ASTnode*> *getVec() {
        return vec;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class CompoundASTnode: public ASTnode {
    public:
    std::list<ASTnode*> *vec;
    CompoundASTnode(std::list<ASTnode*> *_vec):
    vec(_vec){}
    std::list<ASTnode*> *getVec() {
        return vec;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class ConditionalASTnode: public ASTnode {
    public:
    ASTnode *first;
    ASTnode *second;
    ASTnode *third;
    std::string strlit1;
    std::string strlit2;
    ConditionalASTnode(std::string _strlit1, ASTnode* _first, ASTnode* _second, std::string _strlit2, ASTnode* _third):
    strlit1(_strlit1), first(_first), second(_second), strlit2(_strlit2), third(_third){}
    ASTnode* getFirst() {
        return first;
    }
    ASTnode* getSecond() {
        return second;
    }
    ASTnode* getThird() {
        return third;
    }
    std::string getStrLit1() {
        return strlit1;
    }
    std::string getStrLit2() {
        return strlit2;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class WhileASTnode: public ASTnode {
    public:
    ASTnode *first;
    ASTnode *second;
    std::string strlit;
    WhileASTnode(std::string _strlit, ASTnode* _first, ASTnode* _second):
    strlit(_strlit), first(_first), second(_second){}
    ASTnode* getFirst() {
        return first;
    }
    ASTnode* getSecond() {
        return second;
    }
    std::string getStrLit() {
        return strlit;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class ForASTnode: public ASTnode {
    public:
    ASTnode *first;
    ASTnode *second;
    ASTnode *third;
    ASTnode *fourth;
    std::string strlit;
    ForASTnode(std::string _strlit, ASTnode* _first, ASTnode* _second, ASTnode* _third, ASTnode* _fourth):
    strlit(_strlit), first(_first), second(_second), third(_third), fourth(_fourth){}
    ASTnode* getFirst() {
        return first;
    }
    ASTnode* getSecond() {
        return second;
    }
    ASTnode* getThird() {
        return third;
    }
    ASTnode* getFourth() {
        return fourth;
    }
    std::string getStrLit() {
        return strlit;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class FunctionASTnode: public ASTnode {
    public:
    std::list<ASTnode*> *vec;
    std::string strlit1;
    std::string strlit2;
    ASTnode *first;
    FunctionASTnode(std::string _strlit1, std::string _strlit2, std::list<ASTnode*> *_vec, ASTnode* _first):
    strlit1(_strlit1), strlit2(_strlit2), vec(_vec), first(_first){}
    std::string getStrLit1() {
        return strlit1;
    }
    std::string getStrLit2() {
        return strlit2;
    }
    std::list<ASTnode*> *getVec() {
        return vec;
    }
    ASTnode* getFirst() {
        return first;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class DeclaratorASTnode: public ASTnode {
    public:
    std::string strlit1;
    std::string strlit2;
    bool arr;
    DeclaratorASTnode (std::string _strlit1, std::string _strlit2, bool _arr) :
    strlit1(_strlit1), strlit2(_strlit2), arr(_arr) {}
    std::string getStrLit1() {
        return strlit1;
    }
    std::string getStrLit2() {
        return strlit2;
    }
    bool getArr() {
        return arr;
    }
    virtual llvm::Value * accept(ASTvisitor& v) {
      v.visit(*this);
    }
};

class ASTContext {
public:
    ASTnode *root;
    ~ASTContext() {
        clearAST();
    }

    void clearAST() {
        delete root;
    }
};