#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Client {
    string name;
    string phoneNumber;
};

class HashTableSeparateChaining {
private:
    vector<list<Client>> table;
    size_t size;

    // Hash function
    size_t hash(const string& key) {
        size_t hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % size;
        }
        return hashValue;
    }

public:
    HashTableSeparateChaining(size_t tableSize) : size(tableSize) {
        table.resize(size);
    }

    void insert(const string& name, const string& phoneNumber) {
        Client client{name, phoneNumber};
        size_t index = hash(name);
        table[index].push_back(client);
    }

    string search(const string& name) {
        size_t index = hash(name);
        for (const Client& client : table[index]) {
            if (client.name == name) {
                return client.phoneNumber;
            }
        }
        return "Not found";
    }
};

class HashTableLinearProbing {
private:
    vector<Client> table;
    size_t size;

    // Hash function
    size_t hash(const string& key) {
        size_t hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % size;
        }
        return hashValue;
    }

public:
    HashTableLinearProbing(size_t tableSize) : size(tableSize) {
        table.resize(size);
    }

    void insert(const string& name, const string& phoneNumber) {
        Client client{name, phoneNumber};
        size_t index = hash(name);
        while (!table[index].name.empty()) {
            index = (index + 1) % size;
        }
        table[index] = client;
    }

    string search(const string& name) {
        size_t index = hash(name);
        size_t originalIndex = index;
        while (!table[index].name.empty()) {
            if (table[index].name == name) {
                return table[index].phoneNumber;
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                break;
            }
        }
        return "Not found";
    }
};

int main() {
    HashTableSeparateChaining htSeparateChaining(1000);
    HashTableLinearProbing htLinearProbing(1000);

    string name, phoneNumber;
    cout << "Enter client details (name and phone number), type 'done' to stop:\n";
    while (true) {
        cout << "Name: ";
        getline(cin, name);
        if (name == "done") break;
        cout << "Phone Number: ";
        getline(cin, phoneNumber);
        htSeparateChaining.insert(name, phoneNumber);
        htLinearProbing.insert(name, phoneNumber);
    }

    cout << "\nEnter client name to search for their phone number:\n";
    while (true) {
        cout << "Name: ";
        getline(cin, name);
        if (name == "done") break;
        cout << "Searching for " << name << "'s number using Separate Chaining: " << htSeparateChaining.search(name) << endl;
        cout << "Searching for " << name << "'s number using Linear Probing: " << htLinearProbing.search(name) << endl;
    }

    return 0;
}
