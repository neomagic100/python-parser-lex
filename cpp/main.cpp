#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "CodeLine.h"
#include "CodeBlock.h"

std::vector<std::string> readFile(std::string filename)
{
    std::vector<std::string> lines;
    return lines;
}

std::map<unsigned int, std::vector<std::string>> determineBlock(
    std::vector<std::string> nextLines, 
    unsigned int index, 
    unsigned int previousTabCount, 
    std::vector<std::string> prevLines)
{
    std::map<unsigned int, std::vector<std::string>> temp;
    return temp;
}

int main(int argc, char *argv[])
{
    std::string filename;
    if (argc > 1) filename = argv[1];
    else          filename = "Account.py";
    
    std::string test{"        self.textNoTabs = self.findNumTabs(self.rawtext)\n"};
    std::string test2{"            return prevTabCount, prevLines\n"};
    CodeLine line{test};
    std::vector<std::string> lines;
    lines.push_back(test);
    lines.push_back(test2);

    // std::cout << line.getString() << std::endl;
    // std::cout << line.toPyString() << std::endl;
    

    std::vector<CodeLine> codeLines = CodeBlock::createCodeLines(lines);

    // for (CodeLine cl: codeLines)
    // {
    //     std::cout << cl.getString() << std::endl;
    // }

    CodeBlock block{lines, 0};

    std::cout << block.toPyText() << std::endl;
    std::cout << block.hasParent() << std::endl;
   
}