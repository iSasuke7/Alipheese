#include "ast/global/functiondeclaration.h"
#include "types/datatype.h"
#include "generator/brainfuck.h"
#include "common/util.h"

#include <iostream>

FunctionDeclaration::FunctionDeclaration(const std::string& name, FieldListNode* parameters, DataTypeBase* return_type, BlockNode* content):
    name(name), parameters(parameters), return_type(return_type), content(content) {}

FunctionDeclaration::~FunctionDeclaration()
{
    delete this->content;
    delete this->return_type;
    delete this->parameters;
}

void FunctionDeclaration::print(std::ostream& output, size_t level) const
{
    this->printIndent(output, level);
    output << "function declaration (" << this->name << ")" << std::endl;
    this->printIndent(output, level + 1);
    output << "return type: " << *this->return_type << std::endl;
    this->parameters->print(output, level + 1);
    output << std::endl;
    this->content->print(output, level + 1);
}

void FunctionDeclaration::declareGlobals(BrainfuckWriter& writer)
{
    this->scope = writer.declareFunction(this->name, this->parameters->getParameters(), this->return_type, this->content);
}

void FunctionDeclaration::checkTypes(BrainfuckWriter& writer)
{
    size_t old_scope = writer.getScope();
    writer.switchScope(this->scope);

    this->parameters->checkTypes(writer);
    for(Field& field : this->parameters->getParameters())
        writer.declareVariable(field.getName(), field.getType());

    this->content->checkTypes(writer);

    writer.switchScope(old_scope);
}

void FunctionDeclaration::generate(BrainfuckWriter& writer)
{
    UNUSED(writer);
}
