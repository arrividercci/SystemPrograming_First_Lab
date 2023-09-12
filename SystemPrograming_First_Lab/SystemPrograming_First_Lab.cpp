#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

const string fileName = "words.txt";

const string consonantLetters = "bcdfghjklmnpqrstvwxyz";    
int maxConsonantCount = 0;
vector<string> words;

char letterToLowerCase(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + 32;   
    }

    return ch;
}


void removeDuplicates()
{
    sort(words.begin(), words.end());

    words.erase(unique(words.begin(),words.end()), words.end());
}

void clearCharArray(char* arr)
{
    int size = strlen(arr);
    for (int i = 0; i < size; i++)
    {
        arr[i] = '\0';
    }
}

void printResult()
{
    if (words.empty())
    {
        cout << "File is empty or doesn't have words with consonant letters.";
        return;
    }

    cout << "max consonant substring has size: " << maxConsonantCount << endl;
    for(string word : words)
    {
        cout << word << " ";
    }
    cout << endl;
}

int main()
{
    ifstream fin;
    fin.open(fileName);
    if (!fin.is_open())
    {
        cout << "Mistake during file opening." << endl;
    }
    else
    {
        int index = 0;
        int currentWordMaxConsonant = 0;
        int consonantCounter = 0;
        char word[31] = {'\0'};
        bool previousIsConsonant = false;
        char ch;
        while (fin.get(ch))
        {
            if (index > 30)
            {
                cout << "Some words in file have lenth longer than 30." << endl;
                cout << "Check your file and try again.";
                return 0;
            }
            if (ch == ' ' || ch == '\n')
            {
                if (previousIsConsonant && consonantCounter > currentWordMaxConsonant)
                {
                    currentWordMaxConsonant = consonantCounter;
                }

                if (strlen(word) <= 0)
                {
                    index = 0;
                    continue;
                }
                else
                {
                    if (currentWordMaxConsonant > maxConsonantCount)
                    {
                        maxConsonantCount = currentWordMaxConsonant;

                        words.clear();
                        
                        string newWord = string(word);
                        
                        clearCharArray(word);

                        words.push_back(newWord);

                    }
                    else if(currentWordMaxConsonant == maxConsonantCount)
                    {
                        string newWord = string(word);
                        
                        words.push_back(newWord);

                        clearCharArray(word);
                    }
                    else
                    {
                        clearCharArray(word);
                    }

                    currentWordMaxConsonant = 0;

                    previousIsConsonant = false;
                    
                    consonantCounter = 0;
                    
                    index = 0;
                }
            }
            else if (consonantLetters.find(letterToLowerCase(ch)) < consonantLetters.length())
            {
                word[index] = ch;
                previousIsConsonant = true;
                consonantCounter++;
                index++;
            }
            else
            {
                if (previousIsConsonant && consonantCounter > currentWordMaxConsonant)
                {
                    currentWordMaxConsonant = consonantCounter;    
                }
                
                word[index] = ch;
                consonantCounter = 0;
                previousIsConsonant = false;
                index++;
            }
        }
        if (strlen(word) > 0)
        {
            if (previousIsConsonant && consonantCounter > currentWordMaxConsonant)
            {
                currentWordMaxConsonant = consonantCounter;
            }
            if (currentWordMaxConsonant > maxConsonantCount)
            {
                maxConsonantCount = currentWordMaxConsonant;

                words.clear();

                string newWord = string(word);

                clearCharArray(word);

                words.push_back(newWord);

            }
            else if (currentWordMaxConsonant == maxConsonantCount)
            {
                string newWord = string(word);

                words.push_back(newWord);

                clearCharArray(word);
            }
            else
            {
                clearCharArray(word);
            }
        }
    }
    fin.close();
    
    removeDuplicates();

    printResult();
    return 0;
}
