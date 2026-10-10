//COMSC-210 | Lab 21 | Eric-Giulio Hedes
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

//Set up the global constants
const int SIZE = 15, MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

//Set up the Goat class
class Goat
{
    //Private variables
    private:
        int age;
        string name, color;
        //NOTE: Didn't use replit for this! All of those came up from my imagination, just so you know.
        //Set up the name arrays
        string names[SIZE] = {
            "Billy", "Jimmy", "Bimmy", "Jilly", "Hox",
            "Walt", "Geott", "Hally", "Geoffrey", "Pinky",
            "Two-horned", "Maximus", "Brownie", "Donut", "Poodle"
        };
        //Set up the color arrays
        string colors[SIZE] = {
            "Blue", "Yellow", "Green", "Orange", "Red",
            "Turquoise", "Beige", "Black", "White", "Silver",
            "Golden", "Bronze", "Vantablack", "Chartreuse", "Pink"
        };
    //Public variables
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

//Set up the DoublyLinkedList
class DoublyLinkedList
{
    //Private variables
    private:
        //Set up a Node structure
        struct Node
        {
            int data; //Will be used for values
            int age; //Used for goat's age
            string name, color; //Used for goat's name & color
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

        //Set up head & tail nodes
        Node* head;
        Node* tail;

    public:
        //Set up an empty constructor
        DoublyLinkedList() { head = nullptr; tail = nullptr; }

        //Define push_back
        void push_back(int value) {
            //Set up a new node that'll be used for pushing the Goat elements back
            Node* newNode = new Node(value);
            if (!tail)  //If there's no tail, the list is empty
                head = tail = newNode;
            else { //Otherwise insert the new node to the tail
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        void push_front(int value) {
            //Set up a new node that'll be used for pushing the Goat elements front
            Node* newNode = new Node(value);
            if (!head)  //If there's no head, the list is empty
                head = tail = newNode;
            else { //Otherwise insert the new node to the head
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }

        //Define insert_after()
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

        //Define delete_node()
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

        //Define print()
        void print() {
            //Print out a message
            cout << "Forward: ";
            //Use a temporary node named current, starting from the head
            Node* current = head;
            //If the list is empty, print a messsage that is empty & abort the process
            if (!current)
            {
                cout << "List is empty." << endl;
                return;
            }
            //Otherwise print out the list as usual.
            while (current) {
                cout << endl << setw(10) << current->name << " (" << current->color << ", " << current->age << ")";
                current = current->next;
            }
            //Leave space for the next print entry
            cout << endl << endl;
        }

        //Define print_reverse()
        void print_reverse() {
            //Print out a message
            cout << "Backward: ";
            //Like last time, use a temporary node named current, starting from the head
            Node* current = tail;
            //If the list is empty, print a messsage that is empty & abort the process
            if (!current)
            {
                cout << "List is empty." << endl;
                return;
            }
            //Otherwise print out the list as usual.
            while (current) {
                cout << endl << setw(10) << current->name << " (" << current->color << ", " << current->age << ")";
                current = current->prev;
            }
            //Leave space for the next print entry
            cout << endl << endl;
        }

        //Destructor
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

    //Define the doubly linked list
    DoublyLinkedList list;
    //And the list's size
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    //Add up elements
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);

    //Print the list forwards
    list.print();

    //Print the list backwards
    list.print_reverse();

    //Delete the entire list
    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    //And print it
    list.print();

    return 0;
}
