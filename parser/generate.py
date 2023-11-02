#!/bin/python3
from xml.dom import minidom

grammar = minidom.parse(file="grammar.xml").documentElement;

print("Generating code...");

with open('symbols.h', 'w') as f:
    f.write("#ifndef MELT_PARSER_SYMBOLS_H\n");
    f.write("#define MELT_PARSER_SYMBOLS_H\n");
    f.write("#include <stdbool.h>\n\n");
    f.write("typedef enum {\n")
    counter = 0
    tokens = list(map(lambda n: n.getAttribute("name"), grammar.getElementsByTagName("token")))
    rules = list(map(lambda n: n.getAttribute("name"), grammar.getElementsByTagName("rule")))

    for token in tokens:
        f.write("  " + token.upper() + " = " + str(counter) + ",\n")
        counter+=1
    for rule in rules:
        f.write("  " + rule.upper() + " = " + str(counter) + ",\n")
        counter+=1
    f.write("} Symbol;\n\n")

    f.write("#define TOKEN_COUNT " + str(len(tokens)) + "\n")
    f.write("#define SYMBOL_COUNT " + str(counter) + "\n\n")

    f.write("#define is_token(sym) (sym < TOKEN_COUNT)\n\n")

    f.write("static const bool ALL_VALID[" + str(counter) + "] = { ")
    for i in range(0, counter):
            f.write("true, ")
    f.write("};\n\n")

    f.write("static const bool ALL_NOT_VALID[" + str(counter) + "] = { ")
    for i in range(0, counter):
            f.write("false, ")
    f.write("};\n\n")

    f.write("static const char *symbol_name[" + str(counter) + "] = { ")
    for token in tokens:
            f.write("\"" + token + "\", ")
    for rule in rules:
            f.write("\"" + rule + "\", ")
    f.write("};\n\n")

    f.write("#endif\n")

print("done");
