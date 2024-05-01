#include <iostream>
#include <climits>
using namespace std;
class tree {
private:
 static const int MAX_VERTICES = 20;
 int a[MAX_VERTICES][MAX_VERTICES];
 int v, e;
 bool visited[MAX_VERTICES];
public:
 tree() {
 // Initialize variables
 v = 0;
 e = 0;
 for (int i = 0; i < MAX_VERTICES; i++) {
 visited[i] = false;
 for (int j = 0; j < MAX_VERTICES; j++) {
 a[i][j] = INT_MAX; // Use INT_MAX for infinity
 }
 }
 }
 void input();
 void display();
 void minimum();
};
void tree::input() {
 cout << "Enter the no. of branches: ";
 cin >> v;
 if (v <= 0 || v > MAX_VERTICES) {
 cout << "Invalid number of branches. Please enter a value between 1 and " << MAX_VERTICES << 
endl;
 return;
 }
 cout << "Enter the no. of connections: ";
 cin >> e;
 if (e < 0 || e > v * (v - 1) / 2) {
 cout << "Invalid number of connections. Please enter a value between 0 and " << v * (v - 1) / 2 << 
endl;
 return;
 }
 int l, u, w;
 for (int i = 0; i < e; i++) {
 cout << "Enter the end branches of connections: " << endl;
 cin >> l >> u;
 if (l < 1 || l > v || u < 1 || u > v || l == u) {
 cout << "Invalid vertices. Please enter valid vertices." << endl;
 i--; // Decrement i to re-enter the connection
 continue;
 }
 cout << "Enter the phone company charges for this connection: ";
 cin >> w;
 a[l - 1][u - 1] = a[u - 1][l - 1] = w;
 }
}
void tree::display() {
 cout << "\nAdjacency matrix:" << endl;
 for (int i = 0; i < v; i++) {
 for (int j = 0; j < v; j++) {
 if (a[i][j] == INT_MAX)
 cout << " 0 "<<" ";
 else
 cout << " " <<a[i][j] << " ";
 }
 cout << endl;
 }
}
void tree::minimum() {
 int total = 0;
 visited[0] = true;
 for (int count = 0; count < v - 1; count++) {
 int min = INT_MAX;
 int p, q;
 for (int i = 0; i < v; i++) {
 if (visited[i]) {
 for (int j = 0; j < v; j++) {
 if (!visited[j] && a[i][j] < min) {
 min = a[i][j];
 p = i;
 q = j;
 }
 }
 }
 }
 visited[q] = true;
 total += min;
 if (min != INT_MAX) {
 cout << "Minimum cost connection is " << (p + 1) << " -> " << (q + 1) << " with charge: " << min 
<< endl;
 // Mark reverse edge as visited to prevent repetition
 visited[p] = true;
 }
 }
 cout << "The minimum total cost of connections of all branches is: " << total << endl;
}
int main() {
 int ch;
 tree t;
 cout << "==========PRIM'S ALGORITHM=================" << endl;
 cout << "1.INPUT\n2.DISPLAY\n3.MINIMUM\n4.EXIT\n";
 do {
 cout << "------------------\n";
 cout << "Enter your choice: ";
 cin >> ch;
 switch (ch) {
 case 1:
 cout << "*******INPUT YOUR VALUES*******" << endl;
 t.input();
 break;
 case 2:
 cout << "*******DISPLAY THE CONTENTS********" << endl;
 t.display();
 break;
 case 3:
 cout << "*********MINIMUM************" << endl;
 t.minimum();
 break;
 case 4:
 cout << "Exiting..." << endl;
 break;
 default:
 cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
 }
 } while (ch != 4);
 return 0;
}
