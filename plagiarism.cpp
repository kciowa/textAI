#include <iostream>
#include <string>
#include <cstring> 
#include "md5.cpp"

using namespace std;

const int N = 256;

double antiPlagiarism(string text, string fragment);
int getNewArrSize(string* mas, string text);
bool isSeparator(char c);
bool isConjunction(string word);
char toLowerPtr(char p);

double antiPlagiarism(string text, string fragment)
{
    string masWordText[N];
    string masWordFragment[N];

    int textSize = getNewArrSize(masWordText, text);
    int fragmentSize = getNewArrSize(masWordFragment, fragment);

    int overlapCounter = 0;

    for (int i = 0; i < fragmentSize - 2; i++)
    {
        string fragmentSelection = masWordFragment[i] + masWordFragment[i + 1] + masWordFragment[i + 2];
        for (int k = 0; k < textSize - 2; k++)
        {
            string textSelection = masWordText[k] + masWordText[k + 1] + masWordText[k + 2];
            if (md5(textSelection) == md5(fragmentSelection))
            {
                overlapCounter++;
            }
        }
    }
    double uniquenessPercentage = 100 - (round(((double)overlapCounter / (fragmentSize - 2) * 100) * 100) / 100);
    return uniquenessPercentage;
}

int getNewArrSize(string* mas, string text)
{
    char word[N] = "\0";

    int wordIterator = 0;
    int sizeCounter = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isSeparator(text[i]))
        {
            word[wordIterator] = toLowerPtr(text[i]);
            wordIterator++;
            if (isSeparator(text[i + 1]) or text[i + 1] == '\0')
            {
                word[wordIterator] = '\0';
                if (!isConjunction(word))
                {
                    mas[sizeCounter] = word;
                    sizeCounter++;
                }
                wordIterator = 0;
            }
        }
    }
    return sizeCounter;
}

bool isSeparator(char c)
{
    char separatorArr[] = " .,!?;:-+{}()[]*@%$^&#`~_=<>/|'\"\\“”";

    for (int i = 0; separatorArr[i] != '\0'; i++)
    {
        if (separatorArr[i] == c)
            return true;
    }
    return false;
}

bool isConjunction(string word)
{
    string conjunctions[15] = { "and", "as", "or", "then", "but", "if", "till", "how", "so", "because", "unless", "until", "although", "however", "whenever" };

    for (int i = 0; i < 15; i++)
    {
        if (conjunctions[i] == word)
        {
            return true;
        }
    }
    return false;
}

char toLowerPtr(char p)
{
    switch (p)
    {
    case 'A': p = 'a'; return p;
    case 'B': p = 'b'; return p;
    case 'C': p = 'c'; return p;
    case 'D': p = 'd'; return p;
    case 'E': p = 'e'; return p;
    case 'F': p = 'f'; return p;
    case 'G': p = 'g'; return p;
    case 'H': p = 'h'; return p;
    case 'I': p = 'i'; return p;
    case 'J': p = 'j'; return p;
    case 'K': p = 'k'; return p;
    case 'L': p = 'l'; return p;
    case 'M': p = 'm'; return p;
    case 'N': p = 'n'; return p;
    case 'O': p = 'o'; return p;
    case 'P': p = 'p'; return p;
    case 'Q': p = 'q'; return p;
    case 'R': p = 'r'; return p;
    case 'S': p = 's'; return p;
    case 'T': p = 't'; return p;
    case 'U': p = 'u'; return p;
    case 'V': p = 'v'; return p;
    case 'W': p = 'w'; return p;
    case 'X': p = 'x'; return p;
    case 'Y': p = 'y'; return p;
    case 'Z': p = 'z'; return p;
    };
    return p;
}
