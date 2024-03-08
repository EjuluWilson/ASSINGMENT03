// TextAnalysisBST.h
#ifndef TEXTANALYSISBST_H
#define TEXTANALYSISBST_H

#include <string>

// Define the structure of a BST node
struct Node
{
    std::string word; // Word stored in the node
    int frequency;    // Frequency of the word
    int level;        // The level of the node in the BST
    Node *left;       // Pointer to the left child
    Node *right;      // Pointer to the right child

    /**
     * Constructor to initialize a node with a word.
     * @param word The word to store in the node.
     */
    Node(std::string word) : word(word), frequency(1), level(0), left(nullptr), right(nullptr) {}
};

/**
 * Class representing a binary search tree (BST) for storing and analyzing words from text files.
 * Allows for insertion of words, computation of probes for finding words, and writing the analysis results to a file.
 */
class WordBST
{
public:
    WordBST();  // Constructor to initialize the BST
    ~WordBST(); // Destructor to clean up allocated resources and prevent memory leaks

    /**
     * Inserts a word into the BST. If the word already exists, its frequency is incremented.
     * @param word The word to insert into the BST.
     */
    void insert(const std::string &word); // Insert a word into the BST

    /**
     * Writes the contents of the BST (words and their frequencies) to a specified file.
     * The output includes the word, its frequency, and its level in the BST.
     * @param fileName The name of the file to which the BST contents will be written.
     */
    void writeToFile(const std::string &fileName); // Write the contents of the BST to a file

    /**
     * Computes the maximum and average number of probes required to find each word in the BST.
     * @param maxProbes A reference to an integer that will store the maximum number of probes encountered.
     * @param averageProbes A reference to a float that will store the average number of probes encountered.
     */
    void computeProbes(int &maxProbes, float &averageProbes); // Compute maximum and average probes

private:
    Node *root; // Root of the BST

    /**
     * Private helper function for recursive insertion of words into the BST.
     * @param node The current node being examined or inserted into.
     * @param word The word to insert.
     * @param currentLevel The current level in the BST, used for setting the level of inserted nodes.
     */
    void insertPrivate(Node *&node, const std::string &word, int currentLevel);

    /**
     * Recursively deallocates memory used by the BST, preventing memory leaks.
     * @param node The current node to destroy.
     */
    void destroyTree(Node *node);

    /**
     * Recursively writes the words stored in the BST in-order to a file, along with their frequency and level.
     * @param node The current node being written to the file.
     * @param outFile The output file stream to which the words are written.
     */
    void writeInOrder(Node *node, std::ofstream &outFile);

    /**
     * Private helper function to recursively compute the total and maximum probes required to find each word.
     * @param node The current node being examined.
     * @param totalProbes A reference to an integer accumulating the total number of probes.
     * @param maxProbes A reference to an integer storing the maximum number of probes encountered.
     * @param wordCount A reference to an integer counting the number of words processed.
     * @param currentProbe The current probe count for a given word.
     */
    void computeProbesPrivate(Node *node, int &totalProbes, int &maxProbes, int &wordCount, int currentProbe);
};

#endif // TEXTANALYSISBST_H