#include <iostream>
#include <vector>
#include <map>
#include <regex>

std::map<std::string, std::vector<std::string>> analyzeCode(const std::string& code) {
    std::map<std::string, std::vector<std::string>> lexemes;

    // Регулярні вирази для розпізнавання різних лексем
    std::regex numberRegex("[0-9]+(\\.[0-9]+)?");
    std::regex stringRegex("\"[^\"]*\"|\'[^\']*\'");
    std::regex keywordRegex("\\b(if|else|for|while|def|import|from|return)\\b");
    std::regex operatorRegex("\\+|-|\\*|/|==|!=|<|>|<=|>=");
    std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");

    std::smatch match;

    // Розпізнавання чисел
    std::string tempCode = code;
    while (std::regex_search(tempCode, match, numberRegex)) {
        lexemes["numbers"].push_back(match.str());
        tempCode = match.suffix().str();
    }

    // Розпізнавання рядкових констант
    tempCode = code;
    while (std::regex_search(tempCode, match, stringRegex)) {
        lexemes["strings"].push_back(match.str());
        tempCode = match.suffix().str();
    }

    // Розпізнавання ключових слів
    tempCode = code;
    while (std::regex_search(tempCode, match, keywordRegex)) {
        lexemes["keywords"].push_back(match.str());
        tempCode = match.suffix().str();
    }

    // Розпізнавання операторів
    tempCode = code;
    while (std::regex_search(tempCode, match, operatorRegex)) {
        lexemes["operators"].push_back(match.str());
        tempCode = match.suffix().str();
    }

    // Розпізнавання ідентифікаторів
    tempCode = code;
    while (std::regex_search(tempCode, match, identifierRegex)) {
        if (lexemes["keywords"].end() == std::find(lexemes["keywords"].begin(), lexemes["keywords"].end(), match.str())) {
            lexemes["identifiers"].push_back(match.str());
        }
        tempCode = match.suffix().str();
    }

    return lexemes;
}

int main() {
    std::string code = "def greet(name):\n    \"\"\"This function greets the person passed as parameter\"\"\"\n    print(\"Hello, \" + name + \". Good morning!\")\n\n# Calling the function\ngreet(\"John\")\n\nx = 5\ny = 10.5\nz = x + y\n\nif z > 10:\n    print(\"Sum is greater than 10.\")\nelse:\n    print(\"Sum is less than or equal to 10.\")\n\n# This is a comment\n# Define a list\nfruits = ['apple', 'banana', 'cherry']\n\nfor fruit in fruits:\n    print(fruit)";

    auto lexemes = analyzeCode(code);

    for (const auto& pair : lexemes) {
        std::cout << pair.first << ":\n";
        for (const auto& lexeme : pair.second) {
            std::cout << "  " << lexeme << std::endl;
        }
    }

    return 0;
}
