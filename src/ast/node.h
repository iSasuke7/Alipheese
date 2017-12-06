#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <iosfwd>
#include <string>
#include <vector>
#include <map>
#include "types/datatype.h"
#include "common/field.h"

/*
 * Node type:
 * 
 * Function Declaration
 *
 * Global Namespace
 * Statement List
 * Block
 * Global declaration
 * Structure type definition
 *
 * Expression Statement
 * Declaration Statement
 * Assignment Statement
 * While Statement
 * If Statement
 * If Else Statement
 * Assembly Statement
 * Return Statement
 *
 * Expression
 * Add Expression
 * Sub Expression
 * Mul Expression
 * Div Expression
 * Mod Expression
 * Negate Expression
 * Bitwise Complement Expression
 * Bitwise And Expression
 * Bitwise Or Expression
 * Bitwise Xor Expression
 * Bitwise Left Shift Expression
 * Bitwise Right Shift Expression
 * Constant Expression
 * Variable Expression
 * Function Call Expression
 * Cast Expression
 */

class BrainfuckWriter;
class DataTypeBase;

class StatementNode;
class ExpressionNode;
class BlockNode;
class FunctionParameters;
class FunctionArguments;
class GlobalElementNode;
class VariableNode;

class Node
{
    protected:
        void printIndent(std::ostream&, size_t) const;
    public:
        virtual ~Node() = default;
        
        virtual void print(std::ostream&, size_t) const = 0;
        virtual void generate(BrainfuckWriter&) = 0;
        virtual void declareGlobals(BrainfuckWriter&) const;
        virtual void checkTypes(BrainfuckWriter&) = 0;
};

class GlobalNode : public Node
{
    private:
        std::vector<GlobalElementNode*> elements;
    public:
        GlobalNode(const std::vector<GlobalElementNode*>&);
        virtual ~GlobalNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void declareGlobals(BrainfuckWriter&) const;
        virtual void checkTypes(BrainfuckWriter&);
};

class GlobalElementNode : public Node
{
    public:
        virtual ~GlobalElementNode() = default;
};

class GlobalExpressionNode : public GlobalElementNode
{
    private:
        ExpressionNode* expression;
    public:
        GlobalExpressionNode(ExpressionNode*);
        virtual ~GlobalExpressionNode();
    
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void declareGlobals(BrainfuckWriter&) const;
        virtual void checkTypes(BrainfuckWriter&);
};

class FunctionDeclaration : public GlobalElementNode
{
    private:
        VariableNode* name;
        FunctionParameters* parameters;
        DataTypeBase* return_type;
        BlockNode* content;
    public:
        FunctionDeclaration(VariableNode*, FunctionParameters*, DataTypeBase*, BlockNode*);
        virtual ~FunctionDeclaration();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void declareGlobals(BrainfuckWriter&) const;
        virtual void checkTypes(BrainfuckWriter&);
};

class FunctionParameters : public Node
{
    private:
        std::vector<Field> arguments;
    public:
        FunctionParameters(const std::vector<Field>&);
        virtual ~FunctionParameters();

        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);

        std::vector<Field>& getParameters();
};

class StructureDefinitionNode : public GlobalElementNode
{
    private:
        VariableNode* name;
        std::vector<Field> members;
        DataType<DataTypeClass::STRUCT_FORWARD>* type;
    public:
        StructureDefinitionNode(VariableNode*, const std::vector<Field>&);
        ~StructureDefinitionNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void declareGlobals(BrainfuckWriter&) const;
        virtual void checkTypes(BrainfuckWriter&);
};

class StatementNode : public Node
{
    public:
        virtual ~StatementNode() = default;
};

class StatementListNode : public StatementNode
{
    private:
        StatementNode* first;
        StatementNode* second;
    public:
        StatementListNode(StatementNode*, StatementNode*);
        virtual ~StatementListNode();

        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class BlockNode : public StatementNode
{
    private:
        StatementNode* content;
    public:
        BlockNode(StatementNode*);
        virtual ~BlockNode();
    
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class ExpressionStatementNode : public StatementNode
{
    private:
        ExpressionNode* content;
    public:
        ExpressionStatementNode(ExpressionNode*);
        virtual ~ExpressionStatementNode();
    
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class WhileNode : public StatementNode
{
    private:
        ExpressionNode* conditional;
        StatementNode* statement;
    public:
        WhileNode(ExpressionNode*, StatementNode*);
        virtual ~WhileNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class IfNode : public StatementNode
{
    private:
        ExpressionNode* conditional;
        StatementNode* statement;
    public:
        IfNode(ExpressionNode*, StatementNode*);
        virtual ~IfNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class IfElseNode : public StatementNode
{
    private:
        ExpressionNode* conditional;
        StatementNode* statement;
        StatementNode* else_statement;
    public:
        IfElseNode(ExpressionNode*, StatementNode*, StatementNode*);
        virtual ~IfElseNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class AssemblyNode : public StatementNode
{
    private:
        std::string assembly;
    public:
        AssemblyNode(const std::string&);
        virtual ~AssemblyNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class ReturnNode : public StatementNode
{
    private:
        ExpressionNode* retval;
    public:
        ReturnNode(ExpressionNode*);
        virtual ~ReturnNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class ExpressionNode : public Node
{
    public:
        virtual ~ExpressionNode() = default;

        virtual DataTypeBase* getType() = 0;
};

class AssignmentNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        AssignmentNode(ExpressionNode*, ExpressionNode*);
        virtual ~AssignmentNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class AddNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        AddNode(ExpressionNode*, ExpressionNode*);
        virtual ~AddNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class SubNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        SubNode(ExpressionNode*, ExpressionNode*);
        virtual ~SubNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class MulNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        MulNode(ExpressionNode*, ExpressionNode*);
        virtual ~MulNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class DivNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        DivNode(ExpressionNode*, ExpressionNode*);
        virtual ~DivNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class ModNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        ModNode(ExpressionNode*, ExpressionNode*);
        virtual ~ModNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class NegateNode : public ExpressionNode
{
    private:
        ExpressionNode* op;
    public:
        NegateNode(ExpressionNode*);
        virtual ~NegateNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class ComplementNode : public ExpressionNode
{
    private:
        ExpressionNode* op;
    public:
        ComplementNode(ExpressionNode*);
        virtual ~ComplementNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class BitwiseAndNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        BitwiseAndNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitwiseAndNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class BitwiseOrNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        BitwiseOrNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitwiseOrNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class BitwiseXorNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        BitwiseXorNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitwiseXorNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class BitwiseLeftShiftNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        BitwiseLeftShiftNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitwiseLeftShiftNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class BitwiseRightShiftNode : public ExpressionNode
{
    private:
        ExpressionNode* lop;
        ExpressionNode* rop;
    public:
        BitwiseRightShiftNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitwiseRightShiftNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class U8ConstantNode : public ExpressionNode
{
    private:
        uint8_t value;
    public:
        U8ConstantNode(uint8_t);
        virtual ~U8ConstantNode();

        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class DeclarationNode: public ExpressionNode
{
    private:
        DataTypeBase* datatype;
        VariableNode* variable;
    public:
        DeclarationNode(DataTypeBase*, VariableNode*);
        virtual ~DeclarationNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class VariableNode : public ExpressionNode
{
    private:
        std::string variable;
    public:
        VariableNode(const std::string&);
        virtual ~VariableNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class FunctionCallNode : public ExpressionNode
{
    private:
        VariableNode* function_name;
        FunctionArguments* arguments;
    public:
        FunctionCallNode(VariableNode*, FunctionArguments* arguments);
        virtual ~FunctionCallNode();
        
        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

class FunctionArguments : public Node
{
    private:
        std::vector<ExpressionNode*> arguments;
    public:
        FunctionArguments(const std::vector<ExpressionNode*>& arguments);
        virtual ~FunctionArguments();

        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void declareGlobals(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
};

class CastExpression : public ExpressionNode
{
    private:
        ExpressionNode* expression;
        DataTypeBase* desired_type;
    public:
        CastExpression(ExpressionNode*, DataTypeBase*);
        virtual ~CastExpression();

        virtual void print(std::ostream&, size_t) const;
        virtual void generate(BrainfuckWriter&);
        virtual void checkTypes(BrainfuckWriter&);
        virtual DataTypeBase* getType();
};

#endif
