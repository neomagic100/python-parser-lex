import sys
from CodeLine import CodeLine
from CodeBlock import CodeBlock
# TAB="\t"
# TABSPACE3="   "
# TABSPACE4="    "
# TABSYMBOL="%#t"
filename = ""

def readFile(filename):
    try:
        with open(filename) as f:
            text = f.readlines()
    except Exception as e:
        e.with_traceback()
    
    return text
        
def determineBlock(nextLines, index, prevTabCount, prevLines):
    if not nextLines:
        return prevLines
    for i in range(index, len(nextLines)):
        if not nextLines or i + 1 >= len(nextLines):
            return prevTabCount, prevLines
        line = nextLines[i]
        if line.tabsCount == prevTabCount and prevLines == []: # main
            prevLines.append(line)
            return determineBlock(nextLines[1:], 0, prevTabCount, prevLines)
        if line.tabsCount >= prevTabCount:
            prevLines.append(line)
            return determineBlock(nextLines[1:], 0, line.tabsCount, prevLines)
        if line.tabsCount < prevTabCount or i + 1 >= len(nextLines):
            return line.tabsCount, prevLines

def findBlocks(text):
    lines = text
    blocks = []
    tabCount = 0
    count = 0
    while lines:
        tabCount, block = determineBlock(lines, 0, tabCount, [])
        b = CodeBlock(block, count)
        CodeBlock.assignParent(blocks, b)
        blockSize = b.getSize()
        if blockSize == 0:
            return blocks
        blocks.append(b)
        lines = lines[blockSize:]
        count += 1
        
    return blocks

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = "Account.py"
        
    lines = readFile(filename)
    
    codeLines = CodeLine.createCodeLines(lines)
    
    blocks = findBlocks(codeLines)
    
    for i, block in enumerate(blocks):
        sibs = CodeBlock.getSiblingIds(blocks, block)
        blocks[i]._siblings = sibs
    
    with open("blocksout.txt", "w") as f:
        for i, b in enumerate(blocks):
            print(b)
            b.printToFile(f)
    
