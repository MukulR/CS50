import string
from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    linesA = a.split("\n")
    linesB = b.split("\n")
    commonLines = set()

    for aline in linesA:
        for bline in linesB:
            if(aline == bline):
                commonLines.add(aline)
                break

    return list(commonLines)


def sentences(a, b):
    """Return sentences in both a and b"""
    sentA = sent_tokenize(a, language = 'english')
    sentB = sent_tokenize(b, language = 'english')

    commonSentences = set()

    for aline in sentA:
        for bline in sentB:
            if(aline == bline):
                commonSentences.add(aline)
                break

    return list(commonSentences)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substringsA = getSubstrings(a, n)
    substringsB = getSubstrings(b, n)
    commonSentences = set()

    for aSubstring in substringsA:
        for bSubstring in substringsB:
            if(aSubstring == bSubstring):
                commonSentences.add(aSubstring)
                break

    return list(commonSentences)


def getSubstrings(string, n):
    i = 0
    substrings = []
    while(i < len(string) - (n - 1)):
        substrings.append(string[i:(i + n)])
        i = i + 1

    return substrings