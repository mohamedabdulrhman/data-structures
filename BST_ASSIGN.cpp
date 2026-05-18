// ================= BST.h =================
#include <iostream>
using namespace std;

class appointment {
public:
    string name;
    int priority;
    string dep;
    appointment(string namex, int priorityx, string depx) {
        name = namex;
        priority = priorityx;
        dep = depx;
    }
};

class BST {
private:
    class node {
    public:
        appointment data;
        node* right;
        node* left;
        node(appointment a) : data(a), right(NULL), left(NULL) {};
    };

    node* root = NULL;

    node* findMin(node* temp) {
        while (temp != NULL && temp->left != NULL) {
            temp = temp->left;
        }
        return temp;
    }

    node* Delete(node* temp, int prio) {
        if (temp == NULL) {
            return NULL;
        }
        if (prio < temp->data.priority) {
            temp->left = Delete(temp->left, prio);
        }
        else if (prio > temp->data.priority) {
            temp->right = Delete(temp->right, prio);
        }
        else {
            if (temp->left == NULL && temp->right == NULL) {
                delete temp;
                return NULL;
            }
            else if (temp->left == NULL) {
                node* child = temp->right;
                delete temp;
                return child;
            }
            else if (temp->right == NULL) {
                node* child = temp->left;
                delete temp;
                return child;
            }
            else {
                node* minNode = findMin(temp->right);
                temp->data = minNode->data;
                temp->right = Delete(temp->right, minNode->data.priority);
                temp->left = Delete(temp->left, prio);
            }
        }
        return temp;
    }

    void inorder(node* current) {
        if (current == NULL) return;
        inorder(current->left);
        cout << "[" << current->data.name << ", " << current->data.priority << ", " << current->data.dep << "]" << endl;
        inorder(current->right);
    }

    void searchbypriority(node* current, int p) {
        if (current == NULL) return;
        searchbypriority(current->left, p);
        if (current->data.priority == p) {
            cout << "[" << current->data.name << ", " << current->data.priority << ", " << current->data.dep << "]" << endl;
        }
        searchbypriority(current->right, p);
    }

    void display_m_u(node* temp, int prio) {
        if (temp == NULL) return;
        display_m_u(temp->left, prio);
        if (temp->data.priority <= prio) {
            cout << "[" << temp->data.name << ", " << temp->data.priority << ", " << temp->data.dep << "]" << endl;
        }
        display_m_u(temp->right, prio);
    }

    void display_l_u(node* temp, int prio) {
        if (temp == NULL) return;
        display_l_u(temp->left, prio);
        if (temp->data.priority >= prio) {
            cout << "[" << temp->data.name << ", " << temp->data.priority << ", " << temp->data.dep << "]\n";
        }
        display_l_u(temp->right, prio);
    }

public:
    void schedule(string n, int p, string d) {
        appointment value(n, p, d);
        node* newnode = new node(value);

        if (root == NULL) {
            root = newnode;
            return;
        }

        node* temp = root;
        node* prev = NULL;

        while (temp != NULL) {
            prev = temp;
            if (value.priority <= temp->data.priority) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }

        if (value.priority <= prev->data.priority) {
            prev->left = newnode;
        }
        else {
            prev->right = newnode;
        }
    }

    void Cancel(int prio) {
        if (root == NULL) {
            cout << "No appointments found.\n";
            return;
        }
        root = Delete(root, prio);
        cout << "Appointment with priority " << prio << " canceled successfully.\n";
    }

    void display() {
        if (root == NULL) {
            cout << "No appointments found.\n";
            return;
        }
        inorder(root);
    }

    void displayByPriority(int p) {
        searchbypriority(root, p);
    }

    void displayMoreUrgent(int prio) {
        display_m_u(root, prio);
    }

    void displayLessUrgentThan(int prio) {
        display_l_u(root, prio);
    }
};


// ================= main.cpp =================
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    BST tree;

    ifstream inputFile("appointments.txt");
    if (!inputFile.is_open()) {
        cout << "Error: Could not open appointments.txt\n";
        return 1;
    }

    int n;
    inputFile >> n;
    inputFile.ignore();

    for (int i = 0; i < n; i++) {
        string name, dep;
        int priority;

        getline(inputFile, name);
        inputFile >> priority;
        inputFile.ignore();
        getline(inputFile, dep);

        tree.schedule(name, priority, dep);
    }
    inputFile.close();

    int choice;
    do {
        cout << "1. Schedule an appointment\n";
        cout << "2. Display all appointments\n";
        cout << "3. Search for an appointment\n";
        cout << "4. Cancel an appointment\n";
        cout << "5. Display more urgent than\n";
        cout << "6. Display less urgent than\n";
        cout << "Enter number of option: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name, dep;
            int priority;

            cout << "Enter patient name: ";
            getline(cin, name);

            cout << "Enter priority level: ";
            cin >> priority;
            cin.ignore();

            cout << "Enter department: ";
            getline(cin, dep);

            tree.schedule(name, priority, dep);
            cout << "Appointment scheduled.\n";
        }
        else if (choice == 2) {
            tree.display();
        }
        else if (choice == 3) {
            int priority;
            cout << "Enter the priority level: ";
            cin >> priority;
            cin.ignore();
            tree.displayByPriority(priority);
        }
        else if (choice == 4) {
            int priority;
            cout << "Enter the priority level: ";
            cin >> priority;
            cin.ignore();
            tree.Cancel(priority);
        }
        else if (choice == 5) {
            int priority;
            cout << "Display more urgent than: ";
            cin >> priority;
            cin.ignore();
            tree.displayMoreUrgent(priority);
        }
        else if (choice == 6) {
            int priority;
            cout << "Display less urgent than: ";
            cin >> priority;
            cin.ignore();
            tree.displayLessUrgentThan(priority);
        }

    } while (choice != 0);

    return 0;
}