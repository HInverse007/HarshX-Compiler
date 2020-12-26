#include<bits/stdc++.h>
//#include "ast.h"

using namespace std;
using namespace llvm;


class PostfixVisitor: public ASTvisitor{
	private:

    llvm::Module *module;
    llvm::IRBuilder<> *Builder;
    std::string id;
    llvm::LLVMContext MyGlobalContext;
    llvm::Function *mainFunc;
    map<string, Value *> symTableF; 
    map<Value *, map<string, Value *> > symTableV;
    string dect;
    string decv;
    Value* t1=NULL;
    Value* t2=NULL;
    map<Value*, int> mp;
    map<Value*, map<string,int> > symTableAr;
    map<Value*, pair<Value*,Value*> > checkArray;
	
	public:

	PostfixVisitor(std::string x) {
        id = x;
    }
	
	virtual llvm::Value * visit(ProgramASTnode& node) {
        module = new llvm::Module(id,MyGlobalContext);
        Builder = new llvm::IRBuilder<>(MyGlobalContext);
        llvm::FunctionType * pf = FunctionType::get(IntegerType::getInt32Ty(MyGlobalContext), PointerType::get(Type::getInt8Ty(MyGlobalContext), 0), true /* this is var arg func type*/);
        Function::Create(pf,llvm::Function::ExternalLinkage,"printf",module);
        Function::Create(pf,llvm::Function::ExternalLinkage,"scanf",module);
        llvm::FunctionType *funcType;
        funcType = llvm::FunctionType::get(Builder->getInt32Ty(),false);
        mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
        BasicBlock *current = BasicBlock::Create(MyGlobalContext, "entry", mainFunc);
        Builder->SetInsertPoint(current);
        symTableF.insert(pair<string, Value *>("main",mainFunc));
        map<string, Value *> temp;
        symTableV.insert(pair<Value *, map<string, Value *> >(mainFunc,temp));
        list<ASTnode*> *vec = new list<ASTnode*> ();
        vec = node.getVec();
        std::list<ASTnode*> :: iterator it;
        for(it = vec->begin(); it != vec->end(); ++it) {
            (*it)->accept(*this);
        }
        llvm::verifyFunction(*mainFunc);
        module->print(llvm::errs(), nullptr);
    }

    virtual llvm::Value * visit(CompoundASTnode& node) {
        list<ASTnode*> *vec = new list<ASTnode*> ();
        vec = node.getVec();
        std::list<ASTnode*> :: iterator it;
        for(it = vec->begin(); it != vec->end(); ++it) {
            (*it)->accept(*this);
        }
    }

    virtual llvm::Value * visit(FunctionCallASTnode& node) {
        list<ASTnode*> *vec = new list<ASTnode*> ();
        vec = node.getVec();
        std::list<ASTnode*> :: iterator it;
        Value * val;
        vector<Value *> parms;
        Function * callee = module->getFunction(node.getStrLit());
        int num = 0;
        if(callee==NULL) {
            cout<<"ERROR : Calling an undeclared function."<<endl;
            exit(1);
        }
        Function::arg_iterator AI, AE;
        for (AI = callee->arg_begin(), AE = callee->arg_end(); AI != AE; ++AI) {
            num++;
        }
        if(vec->size()!=num) {
            cout<<"ERROR : Invalid parameters."<<endl;
            exit(1);
        }
        AI = callee->arg_begin();
        for(it = vec->begin(); it != vec->end(); ++AI ) {
            val = (*it)->accept(*this);
            if(val->getType()->isPointerTy()) {
                val = Builder->CreateLoad(val, "tmp");
            }
            parms.push_back(val);
            ++it;
        }
        return Builder->CreateCall(callee,parms,"funccall");
    }

    virtual llvm::Value * visit(FunctionASTnode& node) {
        list<ASTnode*> *vec = new list<ASTnode*> ();
        vec = node.getVec();
        std::list<ASTnode*> :: iterator it;
        std::vector<Type *> args;
        string s;
        for(it = vec->begin(); it != vec->end(); ) {
            (*it)->accept(*this);
            s = dect;
            if(s=="int" || s=="uint") {
                args.push_back(Type::getInt32Ty(MyGlobalContext));
            } else if(s=="char") {
                args.push_back(Type::getInt8Ty(MyGlobalContext));
            } else if(s=="bool") {
                args.push_back(Type::getInt1Ty(MyGlobalContext));
            } else {
                args.push_back(Type::getVoidTy(MyGlobalContext));
            }
            ++it;
        }
        llvm::FunctionType *funcType;
        if(node.getStrLit1()=="int" || node.getStrLit1()=="uint") {
            funcType = llvm::FunctionType::get(Builder->getInt32Ty(), args, false);
        } else if(node.getStrLit1()=="char") {
            funcType = llvm::FunctionType::get(Builder->getInt8Ty(), args, false);
        } else if(node.getStrLit1()=="bool") {
            funcType = llvm::FunctionType::get(Builder->getInt1Ty(), args, false);
        } else {
            funcType = llvm::FunctionType::get(Builder->getVoidTy(), args, false);
        }
        map<string, Value *>::iterator itr;
        itr = symTableF.find(node.getStrLit2());
        if(itr!=symTableF.end()) {
            cout<<"ERROR : Multiple functions with same name."<<endl;
            exit(1);
        } 
        llvm::Function *fooFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, node.getStrLit2(), module);
        Function::arg_iterator AI, AE;
        it = vec->begin();
        for (AI = fooFunc->arg_begin(), AE = fooFunc->arg_end(); AI != AE; ++AI, ++it) {
            (*it)->accept(*this);
            s = decv;
            AI->setName(s);
        }
        symTableF.insert(pair<string, Value *>(node.getStrLit2(),fooFunc));
        map<string, Value *> temp;
        symTableV.insert(pair<Value *, map<string, Value *> >(fooFunc,temp));
        it = vec->begin();
        for (AI = fooFunc->arg_begin(), AE = fooFunc->arg_end(); AI != AE; ++AI, ++it) {
            (*it)->accept(*this);
            s = decv;
            itr = symTableV[fooFunc].find(s);
            if(itr!=symTableV[fooFunc].end()) {
                cout<<"ERROR : Multiple parameters with same name."<<endl;
                exit(1);
            }
            symTableV[fooFunc].insert(pair<string, Value *>(s,AI));
        }
        BasicBlock *entry = BasicBlock::Create(MyGlobalContext, "entry", fooFunc);
        BasicBlock *current = Builder->GetInsertBlock();
        Builder->SetInsertPoint(entry);
        node.getFirst()->accept(*this);
        llvm::verifyFunction(*fooFunc);
        Builder->SetInsertPoint(current);
    }

    virtual llvm::Value * visit(IntLitASTnode& node) {
        Value* val = Builder->getInt32(node.getIntLit());
        mp[val] = node.getIntLit();
        return val;
    }

    virtual llvm::Value * visit(BoolLitASTnode& node) {
        return Builder->getInt1(node.getIntLit());
    }

    virtual llvm::Value * visit(StrLitASTnode& node) {
        Function *F = Builder->GetInsertBlock()->getParent();
        Value * val = symTableV[F][node.getStrLit()];
        return val;
    }

    virtual llvm::Value * visit(Str1LitASTnode& node) {
        string s = node.getStrLit();
        return Builder->getInt8(s[0]);
    }

    virtual Value * visit(ExpressionASTnode& node) {
        Value * val = node.getFirst()->accept(*this);
        t1=NULL,t2=NULL;
        if(node.getSecond()) {
            t1 = node.getSecond()->accept(*this);
        }
        if(node.getThird()) {
            t2 = node.getThird()->accept(*this);
        }
        if(t1 == NULL)
        {
            return val;
        }
        else if(t1 !=NULL && t2 == NULL)
        {
            if(t1->getType() == Builder->getInt32Ty())
            {
                return Builder->CreateGEP(Builder->getInt32Ty(),val,Builder->getInt32(mp[t1]),"tmp");
            }
            else
            {
                Value* tmp = Builder->CreateLoad(t1,"tmp");
                return Builder->CreateGEP(Builder->getInt32Ty(),val,tmp,"tmp");
            }
        }
        else if(t1!=NULL && t2 != NULL)
        {
            if(t1->getType() == Builder->getInt32Ty())
            {
                Function *F = Builder->GetInsertBlock()->getParent();
                int t = mp[t1] + mp[t2];
                return Builder->CreateGEP(Builder->getInt32Ty(),val,Builder->getInt32(t),"tmp");
                //return Builder->CreateGEP(Builder->getInt32Ty(),val,Builder->getInt32(mp[t1]),"tmp");
            }
            else
            {
                Value* tmp1 = Builder->CreateLoad(t1,"tmp");
                Value* tmp2 = Builder->CreateLoad(t2,"tmp");
                return Builder->CreateGEP(Builder->getInt32Ty(),val,tmp1,"tmp");
            }
        }
    }

    virtual llvm::Value * visit(DeclaratorASTnode& node) {
        dect = node.getStrLit1();
        decv = node.getStrLit2();
        if(node.getArr()) {
        }
    }

    virtual llvm::Value * visit(DeclarationASTnode& node) {
        list<VariableASTnode*> *vec = new list<VariableASTnode*> ();
        vec = node.getVec();
        std::list<VariableASTnode*> :: iterator it; 
        Value *arraySize = 0;
        Type *ty;
        int align;
        std::map<string, Value *>::iterator itr; 
        Function *F = Builder->GetInsertBlock()->getParent();
        if(node.getStrLit()=="int" || node.getStrLit()=="uint") {
            ty = Builder->getInt32Ty();
            align = 4;
        } else if(node.getStrLit()=="bool") {
            ty = Builder->getInt1Ty();
            align = 1;
        } else if(node.getStrLit()=="char") {
            ty = Builder->getInt8Ty();
            align = 1;
        }
        for(it = vec->begin(); it != vec->end(); ++it) {
            itr = symTableV[F].find((*it)->getStrLit());
            if(itr!=symTableV[F].end()) {
                cout<<"ERROR : Multiple variables with same name."<<endl;
                exit(1);
            }
            if((*it)->getIntLit1() == 0)
            {
             arraySize = 0;
            }
            else if((*it)->getIntLit1() == 1)
            {
             arraySize =  llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyGlobalContext),(*it)->getIntLit2());
             symTableAr[F].insert(pair<string,int> ((*it)->getStrLit(),(*it)->getIntLit2()));
            }
            else if((*it)->getIntLit1() == 2)
            {
             arraySize = llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyGlobalContext),((*it)->getIntLit2() * (*it)->getIntLit3()));
             symTableAr[F].insert(pair<string,int> ((*it)->getStrLit(),(*it)->getIntLit3()));
            }
            AllocaInst *Alloca = Builder->CreateAlloca(ty, arraySize, (*it)->getStrLit());
            Alloca->setAlignment(align);
            symTableV[F].insert(pair<string, Value *>((*it)->getStrLit(),Alloca));
        }
    }

    virtual llvm::Value * visit(VariableASTnode& node) {
    }
    
    virtual llvm::Value * visit(listASTnode& node){
    }

    virtual llvm::Value * visit(InOutASTnode& node) { 
        vector<Value *> argsV;
        string s;
        Value * a = node.getFirst()->accept(*this);
        if(a->getType()->isPointerTy())
        {
            a = Builder->CreateLoad(a, "tmp");
        }
        if(node.getStrLit()=="return") {
            Builder->CreateRet(a);
        } else if(node.getStrLit()=="print") {
            if(a->getType()==Builder->getInt8Ty()) {
                s = "%c";
                a = Builder->CreateSExt(a,Builder->getInt32Ty(),"tmp");
            } else if(a->getType()==Builder->getInt1Ty()) {
                s = "%d";
                a = Builder->CreateZExt(a,Builder->getInt32Ty(),"tmp");
            } else {
                s = "%d";
            }
            Function *printFunc = module->getFunction("printf");
            s.push_back('\n');
            Value * val = Builder->CreateGlobalStringPtr(s.c_str(), "fmt");
            argsV.push_back(val);
            argsV.push_back(a);
            Builder->CreateCall(printFunc, argsV, "print");
        } else if(node.getStrLit()=="scan") {
            if(a->getType()==Builder->getInt8Ty()) {
                s = "%c";
            } else {
                s = "%d";
            }
            a = node.getFirst()->accept(*this);
            Function *printFunc = module->getFunction("scanf");
            Value * val = Builder->CreateGlobalStringPtr(s.c_str(), "fmt");
            argsV.push_back(val);
            argsV.push_back(a);
            Builder->CreateCall(printFunc, argsV, "print");
        }
        return NULL;
    }

    virtual llvm::Value * visit(BinaryASTnode& node) {
        Value * a = node.getFirst()->accept(*this);
        Value * b = node.getSecond()->accept(*this);
        if (!a || !b) {
            cout<<"ERROR : Variable not declared."<<endl;
            exit(1);
        }
        Value * val = a;
        if(a->getType()->isPointerTy())
        {
            a = Builder->CreateLoad(a, "tmp");
        }
        if(b->getType()->isPointerTy())
        {
            b = Builder->CreateLoad(b, "tmp");
        }
        if(a->getType() != b->getType()) {
            cout << "ERROR : Incompatible types." << endl;
            exit(1);
        }
        if(node.getStrLit()=="=") {
            val = Builder->CreateStore(b, val, false);
        } else if(node.getStrLit()=="+") {
            val = Builder->CreateAdd(a, b, "ADD");  
        } else if(node.getStrLit()=="-") {
            val = Builder->CreateSub(a, b, "SUB");
        } else if(node.getStrLit()=="*") {
            val = Builder->CreateMul(a, b, "MUL");
        } else if(node.getStrLit()=="/") {
            val = Builder->CreateUDiv(a, b, "DIV");
        } else if(node.getStrLit()=="%") {
            val = Builder->CreateURem(a, b, "MOD");
        } else if(node.getStrLit()=="&" || node.getStrLit()=="and") {
            val = Builder->CreateAnd(a, b, "AND");
        } else if(node.getStrLit()=="|" || node.getStrLit()=="or") {
            val = Builder->CreateOr(a, b, "OR");
        } else if(node.getStrLit()=="^") {
            val = Builder->CreateXor(a, b, "XOR");
        } else if(node.getStrLit()=="+=") {
            a = Builder->CreateAdd(a, b, "ADD");
            val = Builder->CreateStore(a, val, false);  
        } else if(node.getStrLit()=="-=") {
            a = Builder->CreateSub(a, b, "SUB");
            val = Builder->CreateStore(a, val, false);
        } else if(node.getStrLit()=="*=") {
            a = Builder->CreateMul(a, b, "MUL");
            val = Builder->CreateStore(a, val, false);
        } else if(node.getStrLit()=="/=") {
            a = Builder->CreateUDiv(a, b, "DIV");
            val = Builder->CreateStore(a, val, false);
        } else if(node.getStrLit()=="%=") {
            a = Builder->CreateURem(a, b, "MOD");
            val = Builder->CreateStore(a, val, false);
        } else if(node.getStrLit()=="&=") {
            a = Builder->CreateAnd(a, b, "AND");
            val = Builder->CreateStore(a, val, false);
        } else if(node.getStrLit()=="|=") {
            a = Builder->CreateOr(a, b, "OR");
            val = Builder->CreateStore(a, val, false);
        } else if(node.getStrLit()=="^=") {
            a = Builder->CreateXor(a, b, "XOR");
            val = Builder->CreateStore(a, val, false);
        } else if(node.getStrLit()=="==") {
            val = Builder->CreateICmpEQ(a, b, "EQ");  
        } else if(node.getStrLit()=="!=") {
            val = Builder->CreateICmpNE(a, b, "NE");  
        } else if(node.getStrLit()=="<") {
            val = Builder->CreateICmpSLT(a, b, "LT");  
        } else if(node.getStrLit()==">") {
            val = Builder->CreateICmpSGT(a, b, "GT");  
        } else if(node.getStrLit()=="<=") {
            val = Builder->CreateICmpSLE(a, b, "LEQ");  
        } else if(node.getStrLit()==">=") {
            val = Builder->CreateICmpSGE(a, b, "GEQ");  
        }
        return val;
    }

    virtual llvm::Value * visit(OptionASTnode& node) {
        Value * compare1 = node.getFirst()->accept(*this);
        Value * a = Builder->getInt32(0);
        Value * b = Builder->getInt32(1);
        Value * compare2 = Builder->CreateICmpEQ(a, b, "EQ");
        Value * condtn = Builder->CreateICmpNE(compare1, compare2, "ifcond");
        Function *F = Builder->GetInsertBlock()->getParent();
        BasicBlock * ThenBB = BasicBlock::Create(MyGlobalContext, "then", F);
        BasicBlock * ElseBB = BasicBlock::Create(MyGlobalContext, "else", F);
        BasicBlock * MergeBB = BasicBlock::Create(MyGlobalContext, "merge", F);
        Builder->CreateCondBr(condtn, ThenBB, ElseBB);
        Builder->SetInsertPoint(ThenBB);
        Value *ThenVal = node.getSecond()->accept(*this);
        Builder->CreateBr(MergeBB);
        Builder->SetInsertPoint(ElseBB);
        Value *ElseVal = node.getThird()->accept(*this);
        Builder->CreateBr(MergeBB);
        Builder->SetInsertPoint(MergeBB);
        unsigned PhiBBSize = 2;
        PHINode *Phi = Builder->CreatePHI(Type::getInt32Ty(MyGlobalContext),PhiBBSize, "iftmp");
        Phi->addIncoming(ThenVal, ThenBB);
        Phi->addIncoming(ElseVal, ElseBB);
        return Phi;
    }

    virtual llvm::Value * visit(WhileASTnode& node) {
        Function *F = Builder->GetInsertBlock()->getParent();
        Value * a = Builder->getInt32(0);
        Value * b = Builder->getInt32(1);
        Value * compare2 = Builder->CreateICmpEQ(a, b, "EQ");
        Value * condtn;
        if(node.getFirst()!=NULL) {
            Value * compare1 = node.getFirst()->accept(*this);
            condtn = Builder->CreateICmpNE(compare1, compare2, "whilecond");
        } else {
            condtn = Builder->CreateICmpEQ(compare2, compare2, "whilecond");
        }
        BasicBlock * LoopBB = BasicBlock::Create(MyGlobalContext, "loop", F);
        BasicBlock * AfterBB = BasicBlock::Create(MyGlobalContext, "after", F);
        Builder->CreateCondBr(condtn, LoopBB, AfterBB);
        Builder->SetInsertPoint(LoopBB);
        node.getSecond()->accept(*this);
        if(node.getFirst()!=NULL) {
            Value * compare1 = node.getFirst()->accept(*this);
            condtn = Builder->CreateICmpNE(compare1, compare2, "whilecond");
        } else {
            condtn = Builder->CreateICmpEQ(compare2, compare2, "whilecond");
        }
        Builder->CreateCondBr(condtn, LoopBB, AfterBB);
        Builder->SetInsertPoint(AfterBB);
    }

    virtual llvm::Value * visit(ConditionalASTnode& node) {
        Value * compare1 = node.getFirst()->accept(*this);
        Value * a = Builder->getInt32(0);
        Value * b = Builder->getInt32(1);
        Value * compare2 = Builder->CreateICmpEQ(a, b, "EQ");
        Value * condtn = Builder->CreateICmpNE(compare1, compare2, "ifcond");
        Function *F = Builder->GetInsertBlock()->getParent();
        BasicBlock * ThenBB = BasicBlock::Create(MyGlobalContext, "then", F);
        if(node.getThird()==NULL) {
            BasicBlock * MergeBB = BasicBlock::Create(MyGlobalContext, "merge", F);
            Builder->CreateCondBr(condtn, ThenBB, MergeBB);
            Builder->SetInsertPoint(ThenBB);
            node.getSecond()->accept(*this);
            Builder->CreateBr(MergeBB);
            Builder->SetInsertPoint(MergeBB);
        } else {
            BasicBlock * ElseBB = BasicBlock::Create(MyGlobalContext, "else", F);
            BasicBlock * MergeBB = BasicBlock::Create(MyGlobalContext, "merge", F);
            Builder->CreateCondBr(condtn, ThenBB, ElseBB);
            Builder->SetInsertPoint(ThenBB);
            node.getSecond()->accept(*this);
            Builder->CreateBr(MergeBB);
            Builder->SetInsertPoint(ElseBB);
            node.getThird()->accept(*this);
            Builder->CreateBr(MergeBB);
            Builder->SetInsertPoint(MergeBB);
        }
    }

    virtual llvm::Value * visit(ForASTnode& node) {
        Function *F = Builder->GetInsertBlock()->getParent();
        if(node.getFirst()!=NULL) {
            node.getFirst()->accept(*this);
        }
        Value * a = Builder->getInt32(0);
        Value * b = Builder->getInt32(1);
        Value * compare2 = Builder->CreateICmpEQ(a, b, "EQ");
        Value * condtn;
        if(node.getSecond()!=NULL) {
            Value * compare1 = node.getSecond()->accept(*this);
            condtn = Builder->CreateICmpNE(compare1, compare2, "forcond");
        } else {
            condtn = Builder->CreateICmpEQ(compare2, compare2, "forcond");
        }
        BasicBlock * LoopBB = BasicBlock::Create(MyGlobalContext, "loop", F);
        BasicBlock * AfterBB = BasicBlock::Create(MyGlobalContext, "after", F);
        Builder->CreateCondBr(condtn, LoopBB, AfterBB);
        Builder->SetInsertPoint(LoopBB);
        node.getFourth()->accept(*this);
        if(node.getThird()!=NULL) {
            node.getThird()->accept(*this);
        }
        if(node.getSecond()!=NULL) {
            Value * compare1 = node.getSecond()->accept(*this);
            condtn = Builder->CreateICmpNE(compare1, compare2, "forcond");
        } else {
            condtn = Builder->CreateICmpEQ(compare2, compare2, "forcond");
        }
        Builder->CreateCondBr(condtn, LoopBB, AfterBB);
        Builder->SetInsertPoint(AfterBB);
    }
};