#pragma once
#ifndef CODE_LINE_H
#define CODE_LINE_H

#include <vector>
#include <string>

class CodeLine
{
    private:
    std::string rawtext;
    unsigned int tabsCount;
    std::string textNoTabs;

    std::string findNumTabs(const std::string& line);

    public:
    CodeLine(const std::string& text);
    ~CodeLine() = default;
    
    std::string getString();
    std::string toPyString();
    std::string getTextNoTabs();

    static bool startsWith(const std::string searchToken, const std::string& text);
    static bool endsWith(const char searchChar, const std::string& text);
    static bool isComment(const std::string& line);
    static bool isControl(const char c);
    // static std::vector<CodeLine> createCodeLines(const std::vector<std::string>& text);
    static std::string trimWhitespace(const std::string& line);
};

#endif // !CODE_LINE_H