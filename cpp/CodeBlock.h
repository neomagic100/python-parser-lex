#pragma once
#ifndef CODE_BLOCK_H
#define CODE_BLOCK_H

#include <string>
#include <vector>
#include <fstream>
#include "CodeLine.h"

class CodeBlock {
    private:
    std::vector<CodeLine> block;
    long unsigned int blockId;
    unsigned int findMaxTabs();
    unsigned int findMinTabs();
    CodeBlock* parent;
    std::vector<CodeBlock*> children;
    std::vector<CodeBlock*> siblings;
    std::ofstream fileStream;

    public:
    CodeBlock(std::vector<std::string> codeLines, long unsigned int id);
    ~CodeBlock() = default;
    
    unsigned int getHighestOrder();
    unsigned int getLowestOrder();

    void setParent(CodeBlock* parent);
    CodeBlock* getParent();
    bool hasParent();

    void addChild(CodeBlock* child);
    std::vector<CodeBlock*> getChildren();
    bool hasChildren();

    void printToFile();
    std::string toString();
    std::string toPyText();

    unsigned int getSize();

    void assignParent(std::vector<CodeBlock>& blocks);
    static std::vector<CodeLine> createCodeLines(const std::vector<std::string>& text);
    // static void assignParent(std::vector<CodeBlock>& blocks, CodeBlock& newBlock);
    static std::vector<long unsigned int> getSiblingIds(const std::vector<CodeBlock>& blocks, const CodeBlock& newBlock);
    long unsigned int getBlockID();

    // friend bool operator==(const CodeBlock& self, const CodeBlock& other);
    friend bool operator!=(const CodeBlock& self, const CodeBlock& other);
    friend bool operator>(const CodeBlock& self, const CodeBlock& other);
    friend bool operator<(const CodeBlock& self, const CodeBlock& other);
    friend bool operator>=(const CodeBlock& self, const CodeBlock& other);
    friend bool operator<=(const CodeBlock& self, const CodeBlock& other);
};

#endif // CODE_BLOCK_H