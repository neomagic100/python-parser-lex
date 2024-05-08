#include <vector>
#include <string>
#include "CodeBlock.h"
#include <limits>

#define NEWLINE '\n'
#define UNDEFINED 1234567

CodeBlock::CodeBlock(std::vector<std::string> codeLines, long unsigned int id)
: blockId(id)
{
    this->block = CodeBlock::createCodeLines(codeLines);
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

std::string CodeBlock::toString()
{
    std::string s = "Block:\n";
    for (CodeLine& codeline: this->block)
    {
        s += (codeline.getString() + "\n");
    }
 
    return s;
}

std::string CodeBlock::toPyText()
{
    std::string s = "Block " + std::to_string(this->blockId) + ":\n";
    CodeBlock* p = this->getParent();
    long unsigned int parId = (p == nullptr) ? UNDEFINED : p->getBlockID();
    s += "Parent: " + std::to_string(parId) + "\n";
    s += "Children: \n"; //TODO
    s += "Siblings: \n"; //TODO
    for (CodeLine& codeline: this->block)
    {
        s += (codeline.toPyString() + "\n");
    }
 
    return s;
}

void CodeBlock::assignParent(std::vector<CodeBlock>& blocks)
{
    unsigned int numBlocks = blocks.size();
    if (numBlocks == 0) return;

    unsigned int numNewTabs = this->getHighestOrder();
    for (unsigned int i = numBlocks - 1; i > 0; --i)
    {
        if (numNewTabs == blocks[i].getHighestOrder()) continue;
        if (numNewTabs > blocks[i].getHighestOrder())
        {
            this->setParent(&blocks[i]);
            blocks[i].addChild(this);
            return;
        }
    }
}

CodeBlock* CodeBlock::getParent()
{
    return (this->hasParent()) ? this->parent : nullptr;
}

void CodeBlock::setParent(CodeBlock* b)
{
    this->parent = b;
}

long unsigned int CodeBlock::getBlockID()
{
   return this->blockId; 
}

bool CodeBlock::hasParent()
{
    return this->parent != nullptr && this->parent != NULL;
}

void CodeBlock::addChild(CodeBlock* c)
{
    this->children.push_back(c);
}

unsigned int CodeBlock::getHighestOrder()
{
   unsigned int leastTabs = std::numeric_limits<unsigned int>::max();
   for (CodeLine& line: block)
   {
       if (line.getTabsCount() < leastTabs)
       {
           leastTabs = line.getTabsCount();
       }
   }
   return leastTabs;
}
