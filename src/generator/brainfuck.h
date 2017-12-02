#ifndef BRAINFUCK_HPP_INCLUDE
#define BRAINFUCK_HPP_INCLUDED

#include <iosfwd>
#include <map>
#include <vector>

#include "types/datatype.h"
#include "ast/node.h"

const size_t GLOBAL_SCOPE = 0;

class Scope
{
    private:
        std::vector<std::map<std::string, DataTypeBase*>> declarations;
        std::vector<std::map<std::string, size_t>> stack_locations;
    public:
        Scope() = default;
        Scope(const Scope&) = delete;
        Scope(Scope&&);
        ~Scope() = default;

        Scope& operator=(const Scope&) = delete;

        //Declares a variable in the currently active frame
        void declareVariable(const std::string&, DataTypeBase* datatype);
        void setVariableLocation(const std::string&, size_t);

        //Variable search
        DataTypeBase* findVariable(const std::string&);
        size_t findVariableLocation(const std::string&);

        //Checks
        bool hasVariable(const std::string&);
        bool hasFrameVariable(const std::string&);

        //Frame control
        void enterFrame();
        void exitFrame();

        //Scope fetch
        std::map<std::string, DataTypeBase*>& getFrameDeclarations();
};

class FunctionDefinition
{
    private:
        std::vector<std::pair<std::string, DataTypeBase*>> arguments;
        DataTypeBase* return_type;
        BlockNode* code;
    public:
        FunctionDefinition(const std::vector<std::pair<std::string, DataTypeBase*>>&, DataTypeBase*, BlockNode*);
        FunctionDefinition(FunctionDefinition&&);
        FunctionDefinition(const FunctionDefinition&) = delete;
        ~FunctionDefinition() = default;

        FunctionDefinition& operator=(const FunctionDefinition&) = delete;

        bool parametersEqual(const std::vector<DataTypeBase*>& arguments);
};

class StructureDefinition
{
    public:
        std::map<std::string, DataTypeBase*> fields;
    public:
        StructureDefinition(const std::map<std::string, DataTypeBase*>& fields);
        StructureDefinition(StructureDefinition&&);
        StructureDefinition(const StructureDefinition&) = delete;
        ~StructureDefinition() = default;

        StructureDefinition& operator=(const StructureDefinition&) = delete;
};

class BrainfuckWriter
{
	private:
		std::ostream& output;
        std::vector<Scope> scopes;
        std::multimap<std::string, FunctionDefinition> functions;
        std::map<std::string, StructureDefinition> structures;
        size_t current_scope;
	public:
		BrainfuckWriter(std::ostream&);
		~BrainfuckWriter() = default;

        //Declarations
	    size_t declareFunction(const std::string&, const std::vector<std::pair<std::string, DataTypeBase*>>&, DataTypeBase*, BlockNode*);
        void declareStructure(const std::string&, const std::map<std::string, DataTypeBase*>&);
        void declareVariable(const std::string&, DataTypeBase*);

        //Checks
        bool isFunctionDeclared(const std::string&, const std::vector<std::pair<std::string, DataTypeBase*>>&);
        bool isFunctionDeclared(const std::string&, const std::vector<DataTypeBase*>&);
        bool isStructureDeclared(const std::string&);

        //Controlling function-level scope
        void switchScope(size_t);
        size_t getScope();

        //Controlling statement-level frames
        void enterFrame();
        void exitFrame();
};

#endif
