//Ezzat Mohamadein | ComSc 210 | Midterm 2
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//create consts for each probability of an event happening
const int MIN = 1, MAX = 100, START = 5, HELP = 40, JOIN = 60, END_LEAVE = 20, LEAVE = 10, VIP = 10, PERIODS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

public:
    Node* head;
    Node* tail;

    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    //NEW
    //return data of node at pos
    string get_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return "";
        }
        Node* temp = head;
        for (int i = 1; i < pos && temp; i++) {
            temp = temp->next;
        }
        if (temp)
            return temp->data;
        else {
            cout << "Position doesn't exist." << endl;
            return "";
        }
    }
};

int main() {
    //initialize random seed
    srand(time(0));
    
    //define doubly linked list for the line of customers at the coffee shop
    DoublyLinkedList line;

    //initialize the line with START customers, suing names.txt randomly
    ifstream fin("names.txt");
    vector<string> names;
    string name;
    while (fin >> name) {
        names.push_back(name);
    }

    for (int i = 0; i < START; i++) {
        line.push_back(names[rand() % names.size()]);
    }

    //print initial line
    cout << "Initial line (Minute 1): " << endl;
    line.print();
    cout << endl;

    //Time periods 2-20
    for (int i = 2; i <= 20; i++) {
        cout << "Minute " << i << ": " << endl;
        //create new random seed for each minute
        srand(time(0) + i);
        //check if the first person orders (40%)
        if (rand() % 100 < HELP) {
            //print name of the person being helped and remove them from the line
            cout << line.head->data << " served" << endl;
            line.pop_front();
        }
        //check if a new person joins the line (60%)
        if (rand() % 100 < JOIN) {
            string newName = names[rand() % names.size()];
            line.push_back(newName);
            cout << newName << " joined the line" << endl;
        }
        //check if the last person leaves the line (20%)
        if (rand() % 100 < END_LEAVE) {
            cout << line.tail->data << " left the line" << endl;
            line.pop_back();
        }
        //check if a random person leaves the line (10%)
        if (rand() % 100 < LEAVE) {
            int pos = rand() % (START + i - 1) + 1;
            cout << line.get_pos(pos) << " left the line" << endl;
            line.delete_pos(pos);
        }
        //check if a VIP joins the line (10%)
        if (rand() % 100 < VIP) {
            string vipName = names[rand() % names.size()];
            line.push_front(vipName);
            cout << vipName << " (VIP) joined the front of the line" << endl;
        }
        //print the current line
        cout << "Current line: " << endl;
        line.print();
        cout << endl;
    }

    return 0;
}