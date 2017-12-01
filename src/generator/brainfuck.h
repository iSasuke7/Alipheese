#ifndef BRAINFUCK_HPP_INCLUDE
#define BRAINFUCK_HPP_INCLUDED

#include <iosfwd>

#include "ast/datatype.h"

const size_t GLOBAL_SCOPE = 0;

class Scope
{
    private:

    public:
        Scope();
        Scope(const Scope&) = delete;
        Scope(Scope&&);
        ~Scope() = default;

        Scope& operator=(const Scope&) = delete;

        //Declares a variable in the currently active frame
        void declareVariable(const std::string&, DataTypeBase* datatype);
};

class FunctionDefinition
{
    private:
        std::map<std::string, DataTypeBase*> arguments;
        DataTypeBase* return_type;
        BlockNode* code;
    public:
        FunctionDefinition(const std::map<std::string, DataTypeBase*>&, DataTypeBase*, BlockNode*);
        FunctionDefinition(FunctionDefinition&&);
        FunctionDefinition(const FunctionDefinition&) = delete;
        ~FunctionDefinition() = default;

        FunctionDefinition& operator=(const FunctionDefinition&) = delete;
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

	    size_t declareFunction(const std::string&, const std::map<std::string, DataTypeBase*>&, DataTypeBase*, BlockNode*);
        size_t declareStructure(const std::string&, const std::map<std::string, DataTypeBase*>&);
        void declareVariable(const std::string&, DataTypeBase*);

        //Controlling function-level scope
        void switchScope(size_t);

        //Controlling statement-level frames
        void enterFrame();
        void exitFrame();
};

#endif
