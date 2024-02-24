#include <iostream>
#include <unordered_map>
#include <string>

class DHTNode {
private:
    std:: unordered_map<std::string, std::string> table;

public:
    void store(const std::string& key, const std::string& value) {
        table[key] = value;
        std::cout << "Stored key-value pair: " << key << " - " << value << std::endl;
    }

    std::string retrieve(const std::string& key) {
        auto it = table.find(key);
        if (it != table.end()) {
            return it->second;
        } else {
            return "Key not found";
        }
    }
};

int main() {
    DHTNode node;
    std::string key, value;
    char choice;

    do {
        std::cout << "\nDHT Node Menu:\n";
        std::cout << "1. Store key-value pair\n";
        std::cout << "2. Retrieve vaalue by key\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case '1':
                std::cout << "Enter key: ";
                std::getline(std::cin, key);
                std::cout << "Enter value: ";
                std::getline(std::cin, value);
                node.store(key, value);
                break;
            case '2':
                std::cout << "Enter key: ";
                std::getline(std::cin, key);
                value = node.retrieve(key);
                std::cout << "Retrieved value: " << value << std::endl;
                break;
            case '3':
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter 1, 2 or 3.\n";
        }
    } while (choice != '3');

    return 0;
}