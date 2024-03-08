//TextAnalysisImplBST.cpp

#include "TextAnalysisBST.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <iomanip>

// Transform the input string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr;
     // Iterate through each character and convert it to lowercase
    for (char c : str) {
        lowerStr += std::tolower(static_cast<unsigned char>(c));
    }
    return lowerStr;
}

// Initialize the BST with a null root
WordBST::WordBST() : root(nullptr) {}

// Ensure all nodes are deleted when the BST is destroyed
WordBST::~WordBST() {
    destroyTree(root);// Recursively delete all nodes to avoid memory leaks
}

// Private method to destroy the tree
void WordBST::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);// Delete left subtree
        destroyTree(node->right); // Delete right subtree
        delete node;// Delete the current node
    }
}

// Private method to insert a word into the BST
void WordBST::insertPrivate(Node*& node, const std::string& word, int currentLevel) {
    if (node == nullptr) {
        // If spot is found, insert new node
        node = new Node(word);
        node->level = currentLevel;
    } else if (toLowerCase(word) < toLowerCase(node->word)) {
        // Word should go to the left
        insertPrivate(node->left, word, currentLevel + 1);
    } else if (toLowerCase(word) > toLowerCase(node->word)) {
        // Word should go to the right
        insertPrivate(node->right, word, currentLevel + 1);
    } else {
        // Word already exists, increase its frequency
        node->frequency++;
    }
}

// Insert a word into the BST
void WordBST::insert(const std::string& word) {
    insertPrivate(root, word, 0);
}

// Private method to write the BST contents in-order to the output file
void WordBST::writeInOrder(Node* node, std::ofstream& outFile) {
    if (node != nullptr) {
        writeInOrder(node->left, outFile);
        // Write the current node's word, frequency, and level
        outFile << node->word << " " << node->frequency << " (" << node->level << ")\n";
        writeInOrder(node->right, outFile);
    }
}

// Private method to compute maximum and average probes
void WordBST::computeProbesPrivate(Node* node, int& totalProbes, int& maxProbes, int& wordCount, int currentProbe) {
    if (node != nullptr) {
        wordCount++;
        totalProbes += currentProbe;
        // Update maxProbes if currentProbe is larger
        if (currentProbe > maxProbes) {
            maxProbes = currentProbe;
        }
        // Continue to left and right children
        computeProbesPrivate(node->left, totalProbes, maxProbes, wordCount, currentProbe + 1);
        computeProbesPrivate(node->right, totalProbes, maxProbes, wordCount, currentProbe + 1);
    }
}

// Compute maximum and average probes
void WordBST::computeProbes(int& maxProbes, float& averageProbes) {
    int totalProbes = 0, wordCount = 0;
    maxProbes = 0; // Ensure these are reset before computation
    computeProbesPrivate(root, totalProbes, maxProbes, wordCount, 1);
    averageProbes = wordCount == 0 ? 0 : static_cast<float>(totalProbes) / wordCount;
}


// Write the contents of the BST to a file
void WordBST::writeToFile(const std::string& fileName) {
    std::ofstream outFile(fileName, std::ios::app); // Append mode
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the output file." << std::endl;
        return;
    }

    int maxProbes;
    float averageProbes;
    // Calculate probe statistics
    computeProbes(maxProbes, averageProbes);

    outFile << "Maximum number of probes: " << maxProbes << std::endl;
    outFile << std::fixed << std::setprecision(1); // Included using <iomanip>
    outFile << "Average number of probes: " << averageProbes << std::endl;

    writeInOrder(root, outFile);
    outFile << "--------------------\n";
    outFile.close();
}


