#include <vector>
#include <string>
#include "CodeBlock.h"

#define NEWLINE '\n'

CodeBlock::CodeBlock(std::vector<CodeLine> codeLines, long unsigned int id)
: block(codeLines), blockId(id)
{
    CodeBlock::blockId++;
    this->parent = nullptr;
}

std::vector<CodeLine> CodeBlock::createCodeLines(const std::vector<std::string>& text)
{
    std::vector<CodeLine> codeLines;

    for (const std::string& line: text)
    {
        std::string tempLine{line};
        if (CodeLine::endsWith(NEWLINE, tempLine))
            tempLine.erase(tempLine.end() - 1);
        if (CodeLine::trimWhitespace(tempLine).length() == 0 ||
            CodeLine::isComment(tempLine)) continue;
        codeLines.push_back(tempLine);
    }
    return codeLines;
}
