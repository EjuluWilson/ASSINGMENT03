#ifndef TEXTANALYSISBST_H
#define TEXTANALYSISBST_H

#include <string>

// Define the structure of a BST node
struct Node {
    std::string word; // Word stored in the node
    int frequency; // Frequency of the word
    int level; // The level of the node in the BST
    Node* left; // Pointer to the left child
    Node* right; // Pointer to the right child

    Node(std::string word) : word(word), frequency(1), level(0), left(nullptr), right(nullptr) {}
};

class WordBST {
public:
    WordBST(); // Constructor
    ~WordBST(); // Destructor
    void insert(const std::string& word); // Insert a word into the BST
    void writeToFile(const std::string& fileName); // Write the contents of the BST to a file
    void computeProbes(int& maxProbes, float& averageProbes); // Compute maximum and average probes

private:
    Node* root; // Root of the BST
    void insertPrivate(Node*& node, const std::string& word, int currentLevel);
    void destroyTree(Node* node);
    void writeInOrder(Node* node, std::ofstream& outFile);
    void computeProbesPrivate(Node* node, int& totalProbes, int& maxProbes, int& wordCount, int currentProbe);
};

#endif
