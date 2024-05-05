TAB="\t"
TABSPACE3="   "
TABSPACE4="    "
TABSYMBOL="%#t"

class CodeLine:
    def __init__(self, text):
        self.rawtext = text
        self.tabsCount = 0
        self.textNoTabs = self.findNumTabs(self.rawtext)
        
    def findNumTabs(self, line):
        noTabs = str(line)
        while noTabs.startswith(TABSPACE4):
            self.tabsCount += 1
            noTabs = noTabs.replace(TABSPACE4, "", 1)
        while noTabs.startswith(TABSPACE3):
            self.tabsCount += 1
            noTabs = noTabs.replace(TABSPACE3, "", 1)
        while noTabs.startswith(TAB):
            self.tabsCount += 1
            noTabs = noTabs.replace(TAB, "", 1)
        return noTabs
    
    def getString(self):
        return "\\t * {}: {}".format(self.tabsCount, self.textNoTabs)
    
    def toPyString(self):
        s = ""
        s += ("\t" * self.tabsCount)
        s += self.textNoTabs
        return s
    
    def createCodeLines(text):
        codeLines = []
        for l in text:
            tempLine = l.replace("\n", "")
            if tempLine is None or len(tempLine.strip()) == 0 or CodeLine.isComment(tempLine):
                continue
            codeLines.append(CodeLine(tempLine))
        return codeLines
    
    def isComment(line):
        return line.strip().startswith("#")
    
    def __str__(self):
        return self.getString()
    
    def __repr__(self):
        return self.getString()