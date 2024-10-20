#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

// structre that hold information by priority
struct Person {
    string name;
    int priority; 
};


class PriorityQueue {
private:
    Person* arr;    // Dynamic array to hold person elements
    int maxSize;    // Maximum size of the queue
    int currentSize; // Current size of the queue

public:
    // in this constructre we pass size from main
    PriorityQueue(int s) {
        maxSize = s;
        arr = new Person[maxSize];
        currentSize = 0;
    }

    
    bool isFull() {
        return currentSize == maxSize;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    void enQueue(string name, int roleChoice) {
        if (isFull()) {
            cout << "\t*** Queue is full ***" << endl;
            return;
        }

        int priority = roleChoice; 

        int i;

        //The loop shifts people with lower priority one position to the right
        for (i = currentSize - 1; i >= 0 && arr[i].priority > priority; i--) {

            //If the person at arr[i] has lower priority than the new person (higher priority value), they are shifted to the right
            arr[i + 1] = arr[i];  

            //The loop starts at the last person currently in the queue;
            //makes sure that the loop doesn't go past the start of the queue;
            //This compares the priority of the person at position i with the priority of the new person;
        }

        // insert the new person
        arr[i + 1].name = name;
        arr[i + 1].priority = priority;


        currentSize++;

        //storing the values in getRoleName FUnction
        string role = getRoleName(roleChoice);
        
        cout << "\t*** " << name << " (" << role << ") added successfully ***" << endl;
    }

    
    void deQueue() {

        if (isEmpty()) {
            cout << "\t*** Queue is empty, cannot dequeue ***" << endl;
            return;
        }

        // deque the most priority person
        cout << "\t*** " << arr[0].name << " (" << getRoleName(arr[0].priority) << ") dequeued successfully ***" << endl;

        //used to shidt element to the left for dequing
        for (int i = 0; i < currentSize - 1; i++) {
            arr[i] = arr[i + 1]; // each element is replacing ti the left one position
        }

        currentSize--;
    }

    
    void peek() {
        if (isEmpty()) {
            cout << "\t*** Queue is empty, nothing to peek ***" << endl;
        }
        else {
            //printing the top element of the most priority
            cout << "\t*** Front Person: " << arr[0].name << " (" << getRoleName(arr[0].priority) << ") ***" << endl;
        }
    }


    void displaySize() {
        cout << "\t*** Current size of the queue: " << currentSize << " ***" << endl;
    }

    
    void displayQueue() {
        if (isEmpty()) {
            cout << "\t*** Queue is empty ***" << endl;
            return;
        }

        cout << "\n\t*** Displaying the Queue by Priority ***" << endl;
        for (int i = 0; i < currentSize; i++) {
            // this print the name of person in the i position and its priority in the i position
            cout << "\t" << arr[i].name << " (" << getRoleName(arr[i].priority) << ")" << endl;
        }
    }

   
    ~PriorityQueue() {
        delete[] arr;
    }

    // Input validation function to get a valid integer from the user
    int getValidatedInput() {
        string input;
        int result;

        while (true) {
            getline(cin, input); // Read the input as a string

            // Check if input is empty or just whitespace
            if (input.empty() || input.find_first_not_of(" \t\n\r") == string::npos) {
                cout << "\n\tEmpty input. Please enter a valid number: ";
                continue;
            }

            // Try to convert the string to an integer
            stringstream ss(input);
            if (ss >> result) {
                return result; // Return the valid integer
            }
            else {
                cout << "\n\tInvalid input. Please enter a valid number: ";
            }
        }
    }

    // Input validation function to get a valid string from the user
    string getValidatedString() {
        string input;

        while (true) {
            getline(cin, input); // Read the input as a string

            // Check if input is empty or just whitespace
            if (input.empty() || input.find_first_not_of(" \t\n\r") == string::npos) {
                cout << "\n\tEmpty input. Please enter a valid name: ";
                continue;
            }

            return input; // Return the valid string
        }
    }

    // Input validation function to get a valid role choice (1, 2, 3) from the user
    int getValidatedRole() {
        int role;

        while (true) {
            cout << "\n\tChoose the role (1. Administrator, 2. Faculty, 3. Student): ";
            role = getValidatedInput();
            if (role == 1 || role == 2 || role == 3) {
                return role; // Valid role choice
            }
            else {
                cout << "\n\tInvalid choice. Please enter 1, 2, or 3.";
            }
        }
    }

    // Get the role name based on the priority number
    string getRoleName(int priority) {
        if (priority == 1) return "Administrator";
        if (priority == 2) return "Faculty";
        return "Student";
    }
};

// Display the menu options to the user
void displayMenu() {
    cout << "\n\t\t\t*** Priority Queue Menu ***" << endl;
    cout << "\t1. Enqueue a person (Administrator, Faculty, Student)" << endl;
    cout << "\t2. Dequeue the highest priority person" << endl;
    cout << "\t3. Peek at the highest priority person" << endl;
    cout << "\t4. Display the size of the queue" << endl;
    cout << "\t5. Display entire queue by priority" << endl;
    cout << "\t6. Exit" << endl;
    cout << "\n\tEnter your choice: ";
}

int main() {
    int queueSize;

    // Get queue size from user with validation
    cout << "\n\t\t\t*** Welcome to the Priority Queue Program ***" << endl;
    cout << "\n\tEnter the size of the queue: ";
    queueSize = PriorityQueue(0).getValidatedInput(); // Get validated input for size

    PriorityQueue q(queueSize); // Initialize the queue with the correct size

    int choice;
    do {
        displayMenu();
        choice = q.getValidatedInput(); // Get validated input for menu choice

        switch (choice) {
        case 1: { // Enqueue operation
            cout << "\n\tEnter the name of the person: ";
            string name = q.getValidatedString(); // Get validated input for person's name

            int roleChoice = q.getValidatedRole(); // Get role choice (1, 2, or 3)

            q.enQueue(name, roleChoice);
            break;
        }
        case 2: // Dequeue operation
            q.deQueue();
            break;
        case 3: // Peek at the front (highest priority) person
            q.peek();
            break;
        case 4: // Display current size of the queue
            q.displaySize();
            break;
        case 5: // Display entire queue by priority
            q.displayQueue();
            break;
        case 6: // Exit
            cout << "\n\t*** Exiting the program... ***" << endl;
            break;
        default: // Handle invalid choices
            cout << "\n\tInvalid choice, please try again." << endl;
        }
    } while (choice != 6); // Keep running the program until the user chooses to exit

    return 0;
}
