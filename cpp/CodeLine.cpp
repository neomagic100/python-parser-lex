#include <vector>
#include <string>
#include <iostream>
#include "CodeLine.h"

#define TAB "\t"
#define TABSPACE3 "   "
#define TABSPACE4 "    "
#define TABSYMBOL "\\#t"
#define FOURSPACE 4
#define THREESPACE 3
#define COMMENT '#'

CodeLine::CodeLine(const std::string& text) : rawtext(text)
{
    tabsCount = 0;
    textNoTabs = CodeLine::findNumTabs(rawtext);
}

std::string CodeLine::findNumTabs(const std::string& line)
{
    std::string textNoTabs{line};
    while (CodeLine::startsWith(TABSPACE4, textNoTabs))
    {
        this->tabsCount++;
        textNoTabs.erase(textNoTabs.begin(), textNoTabs.begin() + FOURSPACE);
    }
    while (CodeLine::startsWith(TABSPACE3, textNoTabs))
    {
        this->tabsCount++;
        textNoTabs.erase(textNoTabs.begin(), textNoTabs.begin() + THREESPACE);
    }
    while (CodeLine::startsWith(TAB, textNoTabs))
    {
        this->tabsCount++;
        textNoTabs.erase(textNoTabs.begin(), textNoTabs.begin() + THREESPACE);
    }

    return textNoTabs;
}

bool CodeLine::startsWith(const std::string searchToken, const std::string& text)
{
    if (text.empty()) return false;

    unsigned int size = searchToken.length();

    for (unsigned int i = 0; i < size; ++i)
    {
        if (text[i] != searchToken[i]) return false;
    }

    return true;
}

bool CodeLine::endsWith(const char searchChar, const std::string& text)
{
    if (text.empty()) return false;

    char lastChar = text.back();
    return lastChar == searchChar;
}

unsigned int CodeLine::getTabsCount()
{
    return this->tabsCount;
}

std::string CodeLine::getTextNoTabs()
{
    return this->textNoTabs;
}

std::string CodeLine::getString()
{
    std::string s = std::to_string(this->tabsCount);
    return "\\t * " + s + ": " + this->getTextNoTabs();
}

std::string CodeLine::toPyString()
{
    std::string s{""};
    for (unsigned int i = 0; i < this->tabsCount; ++i)
    {
        s += "\t";
    }
    s += this->getTextNoTabs();

    return s;
}

bool CodeLine::isComment(const std::string& line)
{
    for (unsigned int i = 0; i < line.length(); ++i)
    {
        if (std::isspace(static_cast<unsigned char>(line[i])))
            continue;
        return (line[i] == COMMENT);
    }
    return false;
}

std::string CodeLine::trimWhitespace(const std::string& line)
{
    // Remove front
    long unsigned int frontIter{0};
    long unsigned int backIter{line.length() - 1};

    while (CodeLine::isControl(line[frontIter]))
    {
        ++frontIter;
    }

    if (frontIter >= backIter) return "";

    // back
    while (CodeLine::isControl(line[backIter]))
    {
        --backIter;
    }

    if (backIter <= frontIter) return "";

    return line.substr(frontIter, backIter + 1); 
}

bool CodeLine::isControl(const char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}