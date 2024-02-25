#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

class DHTNode {
private:
    std:: unordered_map<std::string, std::string> table;
    std:: string filename = "dht_data.txt";

    void saveToFile() {
        std::ofstream outFile(filename);
        for (const auto& pair : table) {
            outFile << pair.first << "," << pair.second << std::endl;
        }
        outFile.close();
    }

    void loadFromFile() {
        std::ifstream inFile(filename);
        std::string line;
        while (std::getline(inFile,line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, ',') && std::getline(iss, value)) {
                table[key] = value;
            }
        }
        inFile.close();
    }

public:

    DHTNode() {
        loadFromFile();
    }

    ~DHTNode() {
        saveToFile();
    }
    void store(const std::string& key, const std::string& value) {
        table[key] = value;
        saveToFile();
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

    void displayAll() {
        if (table.empty()) {
            std::cout << "The table is empty" <<std::endl;
        } else {
            std::cout << "All stored key-value pairs:" << std::endl;
            for (const auto& pair : table) {
                std::cout << pair.first << " - " << pair.second << std::endl;
            }
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
        std::cout << "3. Display all key-value pairs\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";
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
                node.displayAll();
                break;
            case '4':
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter 1, 2, 3 or 4.\n";
        }
    } while (choice != '4');

    return 0;
}