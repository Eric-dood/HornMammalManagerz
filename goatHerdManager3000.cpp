//COMSC-210 | Lab 21 | Eric-Giulio Hedes
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 15, MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Goat
{
    private:
        int age;
        string name, color;
        //Didn't use replit for this! All of those came up from my imagination, just so you know.
        string names[SIZE] = {
            "Billy", "Jimmy", "Bimmy", "Jilly", "Hox",
            "Walt", "Geott", "Hally", "Geoffrey", "Pinky",
            "Two-horned", "Maximus", "Brownie", "Donut", "Poodle"
        };
        string colors[SIZE] = {
            "Blue", "Yellow", "Green", "Orange", "Red",
            "Turquoise", "Beige", "Black", "White", "Silver",
            "Golden", "Bronze", "Vantablack", "Chartreuse", "Pink"
        };
    public:
        //Setters
        void setAge(int a) { age = a; }
        void setName(string n) { name = n; }
        void setColor(string c) { color = c; }
        //Getters
        int getAge() { return age; }
        string getName() { return name; }
        string getColor() { return color; }
        //Empty constructor
        Goat() {
            age = rand() % 20 + 1; //Set random age from 1 to 20
            name = names[rand() % SIZE]; //Pick a random name
            color = colors[rand() % SIZE]; //Pick a random color
        }
        //Partial constructor
        Goat(int a) //Age parameter
        {
            age = a; //Set age to a
            name = names[rand() % SIZE]; //Pick a random name
            color = colors[rand() % SIZE]; //Pick a random color
        }
        Goat(int a, string n) //Age & name parameter
        {
            age = a; //Set age to a
            name = n; //Set name to n
            color = colors[rand() % SIZE]; //Pick a random color
        }
        //Full constructor
        Goat(int a, string n, string c) {
            age = a; //Set age to a
            name = n; //Set name to n
            color = c; //Set color to c
        }
};

class DoublyLinkedList
{
    private:
        struct Node {
            int data;
            int age;
            string name, color;
            Node* prev;
            Node* next;
            Node(int val, Goat myGoat = Goat(), Node* p = nullptr, Node* n = nullptr) {
                data = val;
                age = myGoat.getAge();
                name = myGoat.getName();
                color = myGoat.getColor();
                prev = p;
                next = n;
            }
        };

        Node* head;
        Node* tail;

    public:
        // constructor
        DoublyLinkedList() { head = nullptr; tail = nullptr; }

        void push_back(Goat value) {
            Node* newNode = new Node(value);
            if (!tail)  // if there's no tail, the list is empty
                head = tail = newNode;
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        void push_front(Goat value) {
            Node* newNode = new Node(value);
            if (!head)  // if there's no head, the list is empty
                head = tail = newNode;
            else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }

        void insert_after(int value, int position) {
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
                tail = newNode; // Inserting at the end
            temp->next = newNode;
        }

        void delete_node(int value) {
            if (!head) return; // Empty list

            Node* temp = head;
            while (temp && temp->data != value)
                temp = temp->next;

            if (!temp) return; // Value not found

            if (temp->prev) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next; // Deleting the head
            }

            if (temp->next) {
                temp->next->prev = temp->prev;
            } else {
                tail = temp->prev; // Deleting the tail
            }

            delete temp;
        }

        void print() {
            cout << "Forward:" << endl;
            Node* current = head;
            if (!current) return;
            while (current) {
                cout << setw(10) << current->name << " (" << current->color << ", " << current_age << ")" << endl;
                current = current->next;
            }
            cout << endl;
        }

        void print_reverse() {
            cout << "Backward:" << endl;
            Node* current = tail;
            if (!current) return;
            while (current) {
                cout << setw(10) << current->name << " (" << current->color << ", " << current_age << ")" << endl;
                current = current->prev;
            }
            cout << endl;
        }

        ~DoublyLinkedList() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};

//Start of main()
int main()
{
    //Random seed generator
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
