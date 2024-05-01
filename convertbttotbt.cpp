#include <iostream>
#include <stack>

using namespace std;

// Node structure for binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    bool isThreaded; // Flag to indicate whether the right pointer is a thread
};

// Function to create a new node
Node* newNode(int data) {
    Node* temp = new Node();
    temp->data = data;
    temp->left = temp->right = nullptr;
    temp->isThreaded = false;
    return temp;
}

// Function to convert binary tree to threaded binary tree
void convertToThreaded(Node* root) {
    if (root == nullptr) return;

    // Create a stack to store the in-order traversal
    stack<Node*> stack;
    Node* curr = root; // Current node
    Node* prev = nullptr; // Previous node

    // Perform in-order traversal
    while (curr != nullptr || !stack.empty()) {
        // Push all left children to the stack
        while (curr != nullptr) {
            stack.push(curr);
            curr = curr->left;
        }

        // Pop the top node from stack
        curr = stack.top();
        stack.pop();

        // If previous node exists, make current node's right pointer point to it
        if (prev != nullptr && prev->right == nullptr) {
            curr->right = prev;
            curr->isThreaded = true;
        }

        // Update previous node
        prev = curr;

        // Move to the right child
        curr = curr->right;
    }
}

// Function to perform in-order traversal of threaded binary tree
void inOrderTraversal(Node* root) {
    if (root == nullptr) return;

    Node* curr = root;

    // Find the leftmost node
    while (curr->left != nullptr)
        curr = curr->left;

    // Traverse the threaded binary tree
    while (curr != nullptr) {
        cout << curr->data << " ";

        // If current node has a thread, move to its successor
        if (curr->isThreaded)
            curr = curr->right;
        else { // Otherwise, move to the leftmost node in its right subtree
            curr = curr->right;
            while (curr != nullptr && !curr->isThreaded)
                curr = curr->left;
        }
    }
}

// Main function
int main() {
    // Input binary tree from the user
    Node* root = nullptr;
    int value;
    char choice;
    cout << "Enter the root value of the binary tree: ";
    cin >> value;
    root = newNode(value);

    do {
        int parentValue, childValue;
        char direction;
        cout << "Enter the parent value and child value along with direction (L/R) for the child node: ";
        cin >> parentValue >> childValue >> direction;

        // Find the parent node
        Node* parent = nullptr;
        stack<Node*> stack;
        stack.push(root);
        while (!stack.empty()) {
            Node* curr = stack.top();
            stack.pop();
            if (curr->data == parentValue) {
                parent = curr;
                break;
            }
            if (curr->left != nullptr)
                stack.push(curr->left);
            if (curr->right != nullptr)
                stack.push(curr->right);
        }

        // Create the child node
        Node* child = newNode(childValue);

        // Attach the child node to the parent
        if (direction == 'L') {
            parent->left = child;
        } else if (direction == 'R') {
            parent->right = child;
        } else {
            cout << "Invalid direction! Please enter 'L' for left child or 'R' for right child." << endl;
            continue;
        }

        cout << "Do you want to add more nodes (Y/N)? ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    // Convert binary tree to threaded binary tree
    convertToThreaded(root);

    // Perform in-order traversal of threaded binary tree
    cout << "In-order traversal of threaded binary tree: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}
