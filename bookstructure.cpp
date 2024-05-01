#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
    string name;
    vector<Node*> children;

    Node(const string& n) : name(n) {}

    // Add a child node
    void addChild(Node* child) {
        children.push_back(child);
    }

    // Print the node and its children recursively
    void print() const {
        printRecursive(0);
    }

private:
    // Helper function for recursive printing
    void printRecursive(int depth) const {
        for (int i = 0; i < depth; ++i) {
            cout << "-";
        }
        cout << name << endl;
        for (Node* child : children) {
            child->printRecursive(depth + 1);
        }
    }
};

// Function to recursively build the book structure
Node* buildBook() {
    string name;
    cout << "Enter the name of the book: ";
    getline(cin, name);
    Node* book = new Node(name);

    while (true) {
        cout << "Enter the name of a chapter (or type 'done' to finish): ";
        getline(cin, name);
        if (name == "done") break;
        Node* chapter = new Node(name);
        book->addChild(chapter);

        while (true) {
            cout << "Enter the name of a section (or type 'done' to finish): ";
            getline(cin, name);
            if (name == "done") break;
            Node* section = new Node(name);
            chapter->addChild(section);

            while (true) {
                cout << "Enter the name of a subsection (or type 'done' to finish): ";
                getline(cin, name);
                if (name == "done") break;
                Node* subsection = new Node(name);
                section->addChild(subsection);
            }
        }
    }

    return book;
}

int main() {
    Node* book = buildBook();
    cout << "\nBook Structure:" << endl;
    book->print();

    // Cleanup - delete dynamically allocated nodes
    delete book;

    return 0;
}
