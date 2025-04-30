#include <iostream>
#include <string>

using namespace std;
struct stacknode {
    string stckdata;
    stacknode* next;
    stacknode(string data = "") {
        stckdata = data;
        next = NULL;
    }

};
struct Node {
    string data;
    Node* next;
    Node* prev;
    Node(const string& value) : data(value), next(nullptr), prev(nullptr) {}
};

// Stack implementation
class Stack {
private:
    stacknode* top;

public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (top) {
            stacknode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const string& value) {
        stacknode* newNode = new stacknode(value);
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (!top) return "";
        string value = top->stckdata;
        stacknode* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    string peek() const {
        return top ? top->stckdata : "";
    }

    bool isEmpty() const {
        return !top;
    }
};

// Linked List implementation
class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(const string& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display() const {
        Node* current = head;
        while (current) {
            cout << current->data << endl;
            current = current->next;
        }
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

// Modified BST implementation to store bookmark name and URL
struct BSTNode {
    string name;    // Bookmark name
    string url;     // Bookmark URL
    BSTNode* left;
    BSTNode* right;
    BSTNode(const string& bookmarkName, const string& bookmarkUrl)
        : name(bookmarkName), url(bookmarkUrl), left(nullptr), right(nullptr) {
    }
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, const string& name, const string& url) {
        if (!node) return new BSTNode(name, url);
        if (name < node->name) {
            node->left = insert(node->left, name, url);
        }
        else if (name > node->name) {
            node->right = insert(node->right, name, url);
        }
        else {
            // Update URL if bookmark name already exists
            node->url = url;
        }
        return node;
    }

    void inorder(BSTNode* node) const {
        if (node) {
            inorder(node->left);
            cout << "Name: " << node->name << " | URL: " << node->url << endl;
            inorder(node->right);
        }
    }

    BSTNode* find(BSTNode* node, const string& name) const {
        if (!node || node->name == name) return node;
        if (name < node->name) return find(node->left, name);
        return find(node->right, name);
    }

    BSTNode* deleteNode(BSTNode* node, const string& name) {
        if (!node) return nullptr;
        if (name < node->name) {
            node->left = deleteNode(node->left, name);
        }
        else if (name > node->name) {
            node->right = deleteNode(node->right, name);
        }
        else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode* minRight = findMin(node->right);
            node->name = minRight->name;
            node->url = minRight->url;
            node->right = deleteNode(node->right, minRight->name);
        }
        return node;
    }

    BSTNode* findMin(BSTNode* node) const {
        while (node->left) node = node->left;
        return node;
    }

    void clear(BSTNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const string& name, const string& url) {
        root = insert(root, name, url);
    }

    void display() const {
        inorder(root);
    }

    bool find(const string& name) const {
        return find(root, name) != nullptr;
    }

    string getUrl(const string& name) const {
        BSTNode* node = find(root, name);
        return node ? node->url : "";
    }

    void remove(const string& name) {
        root = deleteNode(root, name);
    }

    void clear() {
        clear(root);
        root = nullptr;
    }
};

// Browser History Manager
class BrowserHistoryManager {
private:
    Stack backwardStack;
    Stack forwardStack;
    LinkedList historyList;
    BST bookmarks;
    string currentPage;

public:
    BrowserHistoryManager() : currentPage("about:blank") {}

    void openPage(const string& url) {
        if (currentPage != "about:blank") {
            backwardStack.push(currentPage);
            while (!forwardStack.isEmpty()) {
                forwardStack.pop();
            }
        }
        currentPage = url;
        historyList.append(url);
        cout << "Opened: " << url << endl;
    }

    void goBack() {
        if (!backwardStack.isEmpty()) {
            forwardStack.push(currentPage);
            currentPage = backwardStack.pop();
            cout << "Went back to: " << currentPage << endl;
        }
        else {
            cout << "Cannot go back." << endl;
        }
    }

    void goForward() {
        if (!forwardStack.isEmpty()) {
            backwardStack.push(currentPage);
            currentPage = forwardStack.pop();
            cout << "Went forward to: " << currentPage << endl;
        }
        else {
            cout << "Cannot go forward." << endl;
        }
    }

    void viewHistory() const {
        cout << "Browsing History:" << endl;
        historyList.display();
    }

    void addBookmark(const string& name, const string& url) {
        bookmarks.insert(name, url);
        cout << "Added bookmark: " << name << " -> " << url << endl;
    }

    void viewBookmarks() const {
        cout << "Bookmarks:" << endl;
        bookmarks.display();
    }

    void openBookmark(const string& name) {
        string url = bookmarks.getUrl(name);
        if (!url.empty()) {
            openPage(url);
        }
        else {
            cout << "Bookmark not found." << endl;
        }
    }

    void clearHistory() {
        historyList.clear();
        cout << "History cleared." << endl;
    }

    void clearBookmarks() {
        bookmarks.clear();
        cout << "Bookmarks cleared." << endl;
    }
    void removeBookmark(const string& name) {
        if (bookmarks.find(name)) {
            bookmarks.remove(name);
            cout << "Bookmark deleted: " << name << endl;
        }
        else {
            cout << "Bookmark not found." << endl;
        }
    }

};

int main() {
    BrowserHistoryManager browser;
    int choice;
    string url;
    string input;

    while (true) {
        cout << "\nBrowser History Manager\n"
            << "1. Open a new page\n"
            << "2. Go back\n"
            << "3. Go forward\n"
            << "4. View browsing history\n"
            << "5. Add bookmark\n"
            << "6. View bookmarks\n"
            << "7. Open bookmark\n"
            << "8. Clear history\n"
            << "9. Clear bookmarks\n"
            << "10. Delete Bookmark\n"
            << "11. Exit\n"
            << "Enter your choice: ";

        getline(cin, input);
        choice = stoi(input);

        switch (choice) {
        case 1: {
            cout << "Enter URL: ";
            getline(cin, url);
            browser.openPage(url);

            // Ask if user wants to bookmark this page
            cout << "Do you want to bookmark this page? (y/n): ";
            getline(cin, input);
            if (input == "y" || input == "Y") {
                cout << "Enter bookmark name: ";
                string bookmarkName;
                getline(cin, bookmarkName);
                browser.addBookmark(bookmarkName, url);
            }
            break;
        }

        case 2:
            browser.goBack();
            break;

        case 3:
            browser.goForward();
            break;

        case 4:
            browser.viewHistory();
            break;

        case 5: {
            cout << "Enter bookmark name: ";
            string bookmarkName;
            getline(cin, bookmarkName);

            cout << "Enter URL: ";
            string bookmarkUrl;
            getline(cin, bookmarkUrl);

            browser.addBookmark(bookmarkName, bookmarkUrl);
            break;
        }

        case 6:
            browser.viewBookmarks();
            break;

        case 7: {
            cout << "Enter bookmark name: ";
            string bookmarkName;
            getline(cin, bookmarkName);
            browser.openBookmark(bookmarkName);
            break;
        }

        case 8:
            browser.clearHistory();
            break;

        case 9:
            browser.clearBookmarks();
            break;

        case 10: {
            cout << "Enter bookmark name to delete: ";
            string bookmarkName;
            getline(cin, bookmarkName);
            browser.removeBookmark(bookmarkName);
            break;
        }

        case 11: {
            cout << "Exiting...\n";
            return 0;
        }

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}