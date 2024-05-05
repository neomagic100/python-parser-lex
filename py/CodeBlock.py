import CodeLine

class CodeBlock:
    
    def __init__(self, block, id) -> None:
        self.lines = block
        self.blockid = id
        self._parent = None
        self._children = []
        self._siblings = []
        self._findMaxTabs()
        self._findMinTabs()
        
    def assignParent(blocks, newBlock):
        numBlocks = len(blocks)
        
        if numBlocks == 0:
            return
        
        numNewTabs = newBlock.getHighestOrder()
        for i in range(numBlocks - 1, 0, -1):
            if numNewTabs == blocks[i].getHighestOrder():
                continue
            #     siblings.append(blocks[i])
            if numNewTabs > blocks[i].getHighestOrder():
                newBlock.setParent(blocks[i])
                blocks[i].addChild(newBlock)
                return
    
    def _findMaxTabs(self):
        self.tabsMax = 0
        for line in self.lines:
            if line.tabsCount > self.tabsMax:
                self.tabsMax = line.tabsCount
                
    def _findMinTabs(self):
        self.tabsMin = 2**15
        for line in self.lines:
            if line.tabsCount < self.tabsMin:
                self.tabsMin = line.tabsCount
    
    def getSiblingIds(blocks, block):
        sibs = []
        par = block.getParent()
        if par is None:
            return None
        for b in blocks:
            if b.getParent() and b.getParent() == block.getParent():
                sibs.append(b.blockid)
    
    def getHighestOrder(self):
        return self.tabsMin
    
    def getLowestOrder(self):
        return self.tabsMin
    
    def setParent(self, block):
        self._parent = block
    
    def getParent(self):
        return self._parent
    
    def hasParent(self):
        return self.getParent() is not None
    
    def addChild(self, block):
        self._children.append(block)
    
    def getChildren(self):
        return self._children
    
    def hasChildren(self):
        return len(self.getChildren) > 0
    
    def printToFile(self, fstr):
        try:
            fstr.write(self.toPyText())
        except Exception as e:
            e.with_traceback
    
    def toString(self):
        s = "Block:\n"
        for codeline in self.lines:
            s += (str(codeline) + "\n")
        return s

    def toPyText(self):
        s = "Block {}:\n".format(self.blockid)
        pstr = str(self.getParent().blockid) if self.getParent() is not None else "None"
        s += "Parent: {}\n".format(pstr)
        childs = [child.blockid for child in self.getChildren()] if len(self.getChildren()) > 0 else "[None]"
        s += "Children: {}\n".format(childs)
        s += "Siblings: {}\n".format(self._siblings)
        for codeline in self.lines:
            s += (codeline.toPyString() + "\n")
        s += "\n"
        return s
    
    def getSize(self):
        return len(self.lines)
    
    def __eq__(self, other):
        return self.blockid == other.blockid
    
    def __ne__(self, other):
        return not self == other
    
    def __gt__(self, other):
        return self.getHighestOrder() < other.getHighestOrder()
    
    def __ge__(self, other):
        return self > other or self.getHighestOrder() == other.getHighestOrder()
    
    def __lt__(self, other):
        return self.getHighestOrder() > other.getHighestOrder()
    
    def __le__(self, other):
        return self > other or self.getHighestOrder() == other.getHighestOrder()
    
    def __str__(self):
        return self.toString()
    
    def __repr__(self):
        return self.toString()