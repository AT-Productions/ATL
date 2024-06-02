#include "funcs.hpp"
#include "../compiler.hpp"
#include <vector>
#include <memory>
#include <iostream>

//forward declarations
void print_factor(const Parse_Factor& factor, int depth);
void print_term(const Parse_Term& term, int depth);
void print_expression(const Parse_Expression& expression, int depth);

// Function to print Parse_Factor
void print_factor(const Parse_Factor& factor, int depth) {
    std::string indent(depth * 2, ' ');
    if (factor.type == Expression_Types::Literal) {
        std::cout << indent << "Factor (Literal): " << factor.value << std::endl;
    } else if (factor.type == Expression_Types::Expression && factor.subexpression) {
        std::cout << indent << "Factor (Subexpression):" << std::endl;
        print_expression(*factor.subexpression, depth + 1);
    }
}

// Function to print Parse_Term
void print_term(const Parse_Term& term, int depth) {
    std::string indent(depth * 2, ' ');
    for (size_t i = 0; i < term.factors.size(); ++i) {
        print_factor(term.factors[i], depth + 1);
        if (i < term.operators.size()) {
            std::cout << indent << "Operator: " << term.operators[i] << std::endl;
        }
    }
}

// Function to print Parse_Expression
void print_expression(const Parse_Expression& expression, int depth) {
    std::string indent(depth * 2, ' ');
    for (size_t i = 0; i < expression.terms.size(); ++i) {
        print_term(expression.terms[i], depth + 1);
        if (i < expression.operators.size()) {
            std::cout << indent << "Operator: " << expression.operators[i] << std::endl;
        }
    }
}

// Function to print the parse tree
void print_parsed_tree(const std::shared_ptr<Parsed_Token>& node, int depth = 0) {
    if (!node) return;

    std::string indent(depth * 2, ' ');
    std::cout << indent << "Node: " << node->name << ", Value: " << node->value << ", Type: " << static_cast<int>(node->type) << std::endl;

    if (node->args) {
        std::cout << indent << "  Arguments:" << std::endl;
        for (const auto& arg : *(node->args)) {
            print_expression(*arg, depth + 1);
        }
    }

    for (const auto& child : node->children) {
        print_parsed_tree(child, depth + 1);
    }
}