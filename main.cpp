#include <iostream>
#include <string>
typedef std::string itemType;
using namespace std;

enum Priority {
    Admin = 0,
    Teacher = 1,
    Student = 2
};

struct Node {
    Priority p;
    itemType data;
    Node* next;
};

class PriorityQueue {
private:
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    void insert(itemType item, Priority role);
    itemType remove();
    bool isEmpty();
    void Display();
};

void PriorityQueue::insert(itemType item, Priority role) {

    Node* newNode = new Node();
    newNode->data = item;
    newNode->p = role;
    newNode->next = nullptr;


    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }
    //if the priority of the role being inserted is less than the priority of the role at head
    //we will insert the newNode in front of head
    if (newNode->p < head->p) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* search = head;
    //we loop through the queue to find a suitable place to insert our newNode
    //if the search pointer points to a node whose role priority is <= newNode
    //we will move on to the next node
    while (search->next != nullptr && search->next->p <= newNode->p) {
        search = search->next;
    }
    //once we have found a suitable place we will insert it there
    newNode->next = search->next;
    search->next = newNode;
    if (newNode->next == nullptr) {
        tail = newNode;
    }
}

itemType PriorityQueue::remove() {
    if (isEmpty()) {
        cout << "QUEUE IS EMPTY\n";
        exit(1); 
    }
    //Store data of head incase we want to return it
    //Store address of head in a temporary pointer
    //make head point to the next node
    //delete the temporay pointer
    itemType data = head->data;
    Node* temp = head;
    head = head->next;
    delete temp;
    cout << "\nRemoved Successfully";
    return data;
}

bool PriorityQueue::isEmpty() {
    return head == nullptr;
}

void PriorityQueue::Display() {
    if (isEmpty()) {
        cout << "QUEUE IS EMPTY.\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        cout << "Data: " << current->data << ", Priority: " << current->p << "\n";
        current = current->next;
    }
}

int main() {
    PriorityQueue pq;
    itemType data;
    string choice;
    char con = 'y';

    do {
        cout << "Select role:\n";
        cout << "1. Admin\n2. Teacher\n3. Student\n4. Remove \n5. Display\n";
        cout << "Enter your choice: ";
        cin >> choice;
        Priority role;
        if (choice == "1") {
            role = Admin;
            cout << "\nEnter Admin username: ";
            cin.ignore();
            getline(cin, data);
            pq.insert(data, role);
        }
        else if (choice == "2") {
            role = Teacher;
            cout << "\nEnter Teacher username: ";
            cin.ignore();
            getline(cin, data);
            pq.insert(data, role);

        }
        else if (choice == "3") {
            role = Student;
            cout << "\nEnter Student username: ";
            cin.ignore();
            getline(cin, data);
            pq.insert(data, role);
        }
        else if (choice == "4") {
            pq.remove();
        }
        else if (choice == "5") {
            pq.Display();
        }
        else {
            cout << "Invalid choice";
        }
        cout << "\nWould you like to continue?(Y/N)";
        cin >> con;
        if (con == 'n' || con == 'N') {
            cout << "Exiting Program...";
        }
        else if (con == 'y' || con == 'Y') {}
        else {
            cout << "invalid input: enter Y/N";
            continue;
        }
    } while (con == 'y' || con == 'Y');
    return 0;
}