#include "pch.h"
#include "framework.h"
#include "PPSSPP_LAB_1.h"

static int getUniqueWordsCount(istream& inputStream)
{
    set<string> uniqueWords;
    string tempWord;

    while (inputStream >> tempWord)
    {
        uniqueWords.insert(tempWord);
    }

    return uniqueWords.size();
}

int getStringUniqueWordsCount(const string& source)
{
    stringstream stringStream(source);
    return getUniqueWordsCount(stringStream);
}

int getFileUniqueWordsCount(const string& filePath)
{
    fstream inputStream(filePath, fstream::in);
    return getUniqueWordsCount(inputStream);
}

