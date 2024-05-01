#include<iostream>
#include<algorithm>
using namespace std;
class node {
public:
 string key;
 string meaning;
 node* left;
 node* right;
 node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr) {}
};
class AVL {
private:
 node* root;
 int height(node* temp) {
 if (temp == nullptr)
 return -1;
 return max(height(temp->left), height(temp->right)) + 1;
 }
 node* LL(node* par) {
 node* temp = par->left;
 par->left = temp->right;
 temp->right = par;
 return temp;
 }
 node* RR(node* par) {
 node* temp = par->right;
 par->right = temp->left;
 temp->left = par;
 return temp;
 }
 node* LR(node* par) {
 par->left = RR(par->left);
 return LL(par);
 }
 node* RL(node* par) {
 par->right = LL(par->right);
 return RR(par);
 }
 int getBalance(node* temp) {
 if (temp == nullptr)
 return 0;
 return height(temp->left) - height(temp->right);
 }
 node* insert(node* cur, const string& key, const string& meaning) {
 if (cur == nullptr)
 return new node(key, meaning);
 if (key < cur->key)
 cur->left = insert(cur->left, key, meaning);
 else if (key > cur->key)
 cur->right = insert(cur->right, key, meaning);
 else // key already exists
 return cur;
 int balance = getBalance(cur);
 if (balance > 1) {
 if (key < cur->left->key)
 return LL(cur);
 else
 return LR(cur);
 }
 else if (balance < -1) {
 if (key > cur->right->key)
 return RR(cur);
 else
 return RL(cur);
 }
 return cur;
 }
 node* findMin(node* cur) {
 while (cur->left != nullptr)
 cur = cur->left;
 return cur;
 }
 node* deleteNode(node* cur, const string& key) {
 if (cur == nullptr)
 return cur;
 if (key < cur->key)
 cur->left = deleteNode(cur->left, key);
 else if (key > cur->key)
 cur->right = deleteNode(cur->right, key);
 else {
 if (cur->left == nullptr || cur->right == nullptr) {
 node* temp = (cur->left == nullptr) ? cur->right : cur->left;
 delete cur;
 return temp;
 }
 node* temp = findMin(cur->right);
 cur->key = temp->key;
 cur->meaning = temp->meaning;
 cur->right = deleteNode(cur->right, temp->key);
 }
 int balance = getBalance(cur);
 if (balance > 1) {
 if (getBalance(cur->left) >= 0)
 return LL(cur);
 else
 return LR(cur);
 }
 else if (balance < -1) {
 if (getBalance(cur->right) <= 0)
 return RR(cur);
 else
 return RL(cur);
 }
 return cur;
 }
 void inorderTraversal(node* temp) {
 if (temp == nullptr)
 return;
 inorderTraversal(temp->left);
 cout << temp->key << " : " << temp->meaning << endl;
 inorderTraversal(temp->right);
 }
public:
 AVL() : root(nullptr) {}
 void insert(const string& key, const string& meaning) {
 root = insert(root, key, meaning);
 }
 void remove(const string& key) {
 root = deleteNode(root, key);
 }
 void displayAscending() {
 inorderTraversal(root);
 }
 void displayDescending(node* temp) {
 if (temp == nullptr)
 return;
 displayDescending(temp->right);
 cout << temp->key << " : " << temp->meaning << endl;
 displayDescending(temp->left);
 }
 void displayDescending() {
 displayDescending(root);
 }
 bool search(const string& key) {
 node* cur = root;
 while (cur != nullptr) {
 if (cur->key == key)
 return true;
 else if (key < cur->key)
 cur = cur->left;
 else
 cur = cur->right;
 }
 return false;
 }
};
int main() {
 AVL dictionary;
 char choice;
 cout << "Menu:" << endl;
 cout << "1. Insert a keyword and meaning" << endl;
 cout << "2. Remove a keyword" << endl;
 cout << "3. Search for a keyword" << endl;
 cout << "4. Display keywords in ascending order" << endl;
 cout << "5. Display keywords in descending order" << endl;
 cout << "6. Exit" << endl;
 do {
 cout<<"------------------\n";
 cout << "Enter your choice: ";
 cin >> choice;
 switch (choice) {
 case '1': 
 cout<<"------------------\n";
 {
 string key, meaning;
 cout << "Enter keyword: ";
 cin >> key;
 cout << "Enter meaning: ";
 cin >> meaning;
 dictionary.insert(key, meaning);
 break;
 }
 case '2': 
 cout<<"------------------\n";{
 string key;
 cout << "Enter keyword to remove: ";
 cin >> key;
 dictionary.remove(key);
 break;
 }
 case '3':
 cout<<"------------------\n";
 {
 string key;
 cout << "Enter keyword to search: ";
 cin >> key;
 if (dictionary.search(key))
 cout << "Keyword found in dictionary." << endl;
 else
 cout << "Keyword not found in dictionary." << endl;
 break;
 }
 case '4':
 cout<<"------------------\n";
 cout << "Keywords in ascending order:" << endl;
 dictionary.displayAscending();
 break;
 case '5':
 cout<<"------------------\n";
 cout << "Keywords in descending order:" << endl;
 dictionary.displayDescending();
 break;
 case '6':
 cout<<"------------------\n";
 cout << "Exiting program...." << endl;
 break;
 default:
 cout << "Invalid choice." << endl;
 }
 } while (choice != '6');
 return 0;
}
