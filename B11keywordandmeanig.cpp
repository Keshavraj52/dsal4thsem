#include <iostream>
#include <string>
#include <queue>

using namespace std;

// Node class for BST
class Node {
public:
    string keyword;
    string meaning;
    Node* left;
    Node* right;

    Node(const string& key, const string& value) : keyword(key), meaning(value), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class Dictionary {
private:
    Node* root;

public:
    Dictionary() : root(nullptr) {}

    // Function to add a new keyword and its meaning
    void add(const string& keyword, const string& meaning) {
        root = insertRecursive(root, keyword, meaning);
    }

    // Function to delete a keyword and its meaning
    void remove(const string& keyword) {
        root = deleteRecursive(root, keyword);
    }

    // Function to update the meaning of a keyword
    void update(const string& keyword, const string& newMeaning) {
        root = deleteRecursive(root, keyword);
        root = insertRecursive(root, keyword, newMeaning);
    }

    // Function to display the data sorted in ascending order
    void displayAscending() const {
        inorderTraversal(root);
    }

    // Function to display the data sorted in descending order
    void displayDescending() const {
        reverseInorderTraversal(root);
    }

    // Function to find the maximum comparisons required for finding any keyword
    int maxComparisons(const string& keyword) const {
        return maxComparisonsRecursive(root, keyword, 0);
    }

private:
    // Recursive function to insert a new keyword and its meaning
    Node* insertRecursive(Node* node, const string& keyword, const string& meaning) {
        if (node == nullptr) {
            return new Node(keyword, meaning);
        }

        if (keyword < node->keyword) {
            node->left = insertRecursive(node->left, keyword, meaning);
        } else if (keyword > node->keyword) {
            node->right = insertRecursive(node->right, keyword, meaning);
        }

        return node;
    }

    // Recursive function to delete a keyword and its meaning
    Node* deleteRecursive(Node* node, const string& keyword) {
        if (node == nullptr) {
            return nullptr;
        }

        if (keyword < node->keyword) {
            node->left = deleteRecursive(node->left, keyword);
        } else if (keyword > node->keyword) {
            node->right = deleteRecursive(node->right, keyword);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->keyword = temp->keyword;
            node->meaning = temp->meaning;
            node->right = deleteRecursive(node->right, temp->keyword);
        }

        return node;
    }

    // Function to find the minimum node in a subtree
    Node* findMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Function for inorder traversal (sorted order)
    void inorderTraversal(Node* node) const {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->keyword << ": " << node->meaning << endl;
            inorderTraversal(node->right);
        }
    }

    // Function for reverse inorder traversal (sorted order)
    void reverseInorderTraversal(Node* node) const {
        if (node != nullptr) {
            reverseInorderTraversal(node->right);
            cout << node->keyword << ": " << node->meaning << endl;
            reverseInorderTraversal(node->left);
        }
    }

    // Recursive function to find the maximum comparisons required for finding any keyword
    int maxComparisonsRecursive(Node* node, const string& keyword, int count) const {
        if (node == nullptr) {
            return count;
        }

        if (keyword < node->keyword) {
            return maxComparisonsRecursive(node->left, keyword, count + 1);
        } else if (keyword > node->keyword) {
            return maxComparisonsRecursive(node->right, keyword, count + 1);
        } else {
            return count + 1;
        }
    }
};

int main() {
    Dictionary dictionary;

    cout << "Welcome to the Dictionary App!" << endl;
    char choice;
    do {
        cout << "\nChoose an operation:" << endl;
        cout << "1. Add a new keyword and its meaning" << endl;
        cout << "2. Delete a keyword" << endl;
        cout << "3. Update the meaning of a keyword" << endl;
        cout << "4. Display data sorted in ascending order" << endl;
        cout << "5. Display data sorted in descending order" << endl;
        cout << "6. Find the maximum comparisons for finding a keyword" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // to clear the input buffer

        switch (choice) {
            case '1': {
                string keyword, meaning;
                cout << "Enter the keyword: ";
                getline(cin, keyword);
                cout << "Enter the meaning: ";
                getline(cin, meaning);
                dictionary.add(keyword, meaning);
                cout << "Keyword added successfully!" << endl;
                break;
            }
            case '2': {
                string keyword;
                cout << "Enter the keyword to delete: ";
                getline(cin, keyword);
                dictionary.remove(keyword);
                cout << "Keyword deleted successfully!" << endl;
                break;
            }
            case '3': {
                string keyword, newMeaning;
                cout << "Enter the keyword to update: ";
                getline(cin, keyword);
                cout << "Enter the new meaning: ";
                getline(cin, newMeaning);
                dictionary.update(keyword, newMeaning);
                cout << "Meaning updated successfully!" << endl;
                break;
            }
            case '4': {
                cout << "Dictionary (Ascending Order):" << endl;
                dictionary.displayAscending();
                break;
            }
            case '5': {
                cout << "Dictionary (Descending Order):" << endl;
                dictionary.displayDescending();
                break;
            }
            case '6': {
                string keyword;
                cout << "Enter the keyword to find maximum comparisons: ";
                getline(cin, keyword);
                cout << "Maximum comparisons for finding '" << keyword << "': " << dictionary.maxComparisons(keyword) << endl;
                break;
            }
            case '7': {
                cout << "Exiting... Thank you!" << endl;
                break;
            }
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }

    } while (choice != '7');

    return 0;
}
