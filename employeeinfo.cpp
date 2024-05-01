#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
class Set {
private:
    unordered_set<T> elements;

public:
    // Add new element to the set
    void add(const T& element) {
        elements.insert(element);
    }

    // Remove element from the set
    void remove(const T& element) {
        elements.erase(element);
    }

    // Check if element is in the set
    bool contains(const T& element) const {
        return elements.find(element) != elements.end();
    }

    // Return the number of elements in the set
    int size() const {
        return elements.size();
    }

    // Return an iterator to loop over the elements of the set
    typename unordered_set<T>::const_iterator iterator() const {
        return elements.begin();
    }

    // Intersection of two sets
    Set<T> intersection(const Set<T>& otherSet) const {
        Set<T> result;
        for (const T& element : elements) {
            if (otherSet.contains(element)) {
                result.add(element);
            }
        }
        return result;
    }

    // Union of two sets
    Set<T> unionSet(const Set<T>& otherSet) const {
        Set<T> result(*this);
        for (const T& element : otherSet.elements) {
            result.add(element);
        }
        return result;
    }

    // Difference between two sets
    Set<T> difference(const Set<T>& otherSet) const {
        Set<T> result(*this);
        for (const T& element : otherSet.elements) {
            result.remove(element);
        }
        return result;
    }

    // Check if the set is a subset of another set
    bool subset(const Set<T>& otherSet) const {
        for (const T& element : elements) {
            if (!otherSet.contains(element)) {
                return false;
            }
        }
        return true;
    }

    // Get the underlying unordered_set
    const unordered_set<T>& getElements() const {
        return elements;
    }
};

int main() {
    Set<int> set1, set2;
    int choice, element;

    cout << "Enter elements for Set 1 (Enter -1 to stop):\n";
    while (true) {
        cin >> element;
        if (element == -1) break;
        set1.add(element);
    }

    cout << "Enter elements for Set 2 (Enter -1 to stop):\n";
    while (true) {
        cin >> element;
        if (element == -1) break;
        set2.add(element);
    }

    cout << "Set 1 Size: " << set1.size() << endl;
    cout << "Set 2 Size: " << set2.size() << endl;

    cout << "Set 1 elements: ";
    for (auto it = set1.iterator(); it != set1.getElements().end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Set 2 elements: ";
    for (auto it = set2.iterator(); it != set2.getElements().end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Intersection of Set 1 and Set 2: ";
    Set<int> intersection = set1.intersection(set2);
    for (auto it = intersection.iterator(); it != intersection.getElements().end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Union of Set 1 and Set 2: ";
    Set<int> unionSet = set1.unionSet(set2);
    for (auto it = unionSet.iterator(); it != unionSet.getElements().end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Difference of Set 1 and Set 2: ";
    Set<int> difference = set1.difference(set2);
    for (auto it = difference.iterator(); it != difference.getElements().end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Is Set 1 a subset of Set 2? " << (set1.subset(set2) ? "Yes" : "No") << endl;

    return 0;
}
