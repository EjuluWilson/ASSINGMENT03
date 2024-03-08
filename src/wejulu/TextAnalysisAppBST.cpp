//TextAnalysisAppBST.cpp

#include "TextAnalysisBST.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstring>

// Helper function to process and clean each character, and then insert the word into the BST
void processCharacterAndWord(char currentChar, std::string& currentWord, WordBST& wordBST, bool& isWord) {
    if (std::isalnum(currentChar) || currentChar == '-') {
        currentWord += std::tolower(currentChar);
        isWord = true;
    } else if (isWord) {
        // Check for trailing 's in words and remove it
        if (currentWord.length() > 2 && currentWord.substr(currentWord.length() - 2) == "'s") {
            currentWord = currentWord.substr(0, currentWord.length() - 2);
        }
        wordBST.insert(currentWord);
        currentWord = ""; // Reset currentWord for the next word
        isWord = false;
    }
}

// Function to process each line of text and extract words
void splitAndProcessWords(const std::string& text, WordBST& wordBST) {
    std::string currentWord;
    bool isWord = false;
    for (char c : text) {
        processCharacterAndWord(c, currentWord, wordBST, isWord);
    }
    // Process the last word if the line ends with a word character
    if (isWord) {
        wordBST.insert(currentWord);
    }
}

int main() {
    std::ifstream inputFile("../data/input.txt");
    std::string outputFileName = "../data/output.txt";

    // Ensure outputFile is cleared at the beginning
    std::ofstream outputFile(outputFileName, std::ofstream::trunc);
    outputFile << "wejulu\n"; // Write ID to the output file
    outputFile.close(); // Close to allow append mode in writeToFile

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return -1;
    }

    std::string fileName;
    while (std::getline(inputFile, fileName)) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Failed to open " << fileName << std::endl;
            continue;
        }

        WordBST wordBST;
        std::string line;
        while (std::getline(file, line)) {
            splitAndProcessWords(line, wordBST);
        }

        file.close();

        // Open the output file in append mode and write file name
        std::ofstream outFile(outputFileName, std::ios::app);
        outFile << fileName << std::endl;
        outFile.close();

        // No need to manually compute probes or write them to the file here
        // The writeToFile method of wordBST will handle all the output operations
        wordBST.writeToFile(outputFileName);
    }

    return 0;
}
