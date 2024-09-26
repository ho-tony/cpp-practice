#include <iostream>
#include <stdexcept>  // For std::runtime_error
#include <vector>
using namespace std;
template <typename keyType, typename valType>   
class OpenAddressingHashTable {
private: 
    struct Node {
        keyType key;
        valType val;
        bool isOccupied; 
        Node() : isOccupied(false) {}
        Node(keyType k, valType v, bool occupied) : key(k), val(v), isOccupied(occupied) {}
        
    };
    vector<Node> arr = vector<Node>(16);
    size_t num_elements = 0;
    const double LOAD_FACTOR = 0.7;

    void expand() {
        vector<Node> new_table(arr.size() * 2);
        for (int i = 0; i < arr.size(); ++i) {
            size_t hash = std::hash<keyType>{}(arr[i].key) % new_table.size();
            new_table[hash] = arr[i];
        }
        arr = new_table;
        
    }

public: 

    size_t get_hash(const keyType key) {
        return std::hash<keyType>{}(key) % arr.size();
    }

    bool insert(const keyType key, const valType val) {
        Node insert_node = Node(key, val, true);
        size_t ptr = get_hash(key);
        while (arr[ptr].isOccupied) {
            if (arr[ptr].key == key) {
                break;
            }
            ptr = (ptr + 1) % arr.size();
        
            
        }
        arr[ptr] = insert_node;
        num_elements++;
        if (num_elements > arr.size() * LOAD_FACTOR) {
            expand();
        }
        
        return true;
    }



    valType get(const keyType key) {
        size_t ptr = get_hash(key);
        while (arr[ptr].key != key) {
            ptr = (ptr + 1) % arr.size();
            if (!arr[ptr].isOccupied) {
                throw std::runtime_error("Element not found");
            }
        }
        if (!arr[ptr].isOccupied) {
            throw std::runtime_error("Element not found");
        }
        return arr[ptr].val;
    
    }
    size_t size() {
        return num_elements;
    }
    
    void toString() {
        for (uint i = 0; i < arr.size(); ++i) {
            cout << i << ":" << arr[i].key << ":" << arr[i].val << endl;
            
        }
    }

    bool remove(const keyType key) {
        size_t ptr = get_hash(key);
        while (arr[ptr].key != key) {
            ptr = (ptr + 1) % arr.size();
            if (!arr[ptr].isOccupied) {
                return false;
            }
        }
        arr[ptr].isOccupied = false;
        return true;
    }

    
};

int main() {
    OpenAddressingHashTable<string, string> test_table;
    test_table.insert("abc123", "hi");
    cout << endl;
    test_table.toString();
    test_table.insert("i will get", "a job");
    test_table.insert("i am the person", "tony");
    test_table.insert("hello", "world");
    test_table.insert("apple", "stock");
    test_table.insert("bloomberg", "pays");
    cout << endl;
    test_table.toString();
    test_table.insert("this is a", "string");
    test_table.insert("2k gaming", "has cool");
    test_table.insert("this is the", "man");
    test_table.insert("konosuba", "not bad");
    test_table.insert("you should watch", "frieren");
    test_table.insert("390", "something");
    test_table.insert("310948u3124812", "something2");
    test_table.insert("12893283", "something3");
    cout << endl;
    test_table.toString();
    test_table.insert("3194081248124", "something2319021");
    test_table.insert("123132ijhnjbkk", "something5");
    test_table.insert("abbbb", "abbbbbbbbbbbbbbb");
    test_table.insert("a very very very very very vepry very long sentence", "this is a very veyr very very long sentence");
    test_table.insert("...", "hihihiihihihihihihihihiih");
    cout << endl;
    test_table.toString();
    test_table.remove("abc123");
    try { 
        test_table.get("abc123");
    } catch (std::runtime_error ex){
        cout << "element removed\n";
    }

}
