#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;

int CS=0,IS=0,DS=0,AI=0,IT=0; // global variables to be used in counting students in each department

struct node
{
    int id;
    double gpa;
    string name;
    string department;
    node *left;
    node *right;
    node(int ID, double GPA, string Name, string Department)
    {
        id = ID;
        gpa = GPA;
        name = Name;
        department = Department;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    node *root;
public:
    BST()
    {
        root = nullptr;
    }
    void insert(int ID, double GPA, string Name, string Department);
    void search(int ID);
    void remove(int ID);
    void printAll(node *n);
    void loadFile();
    void run();
    node *getRoot();
    void printReport();
};

void BST::loadFile()
{
    string filename = "students.txt";
    fstream file(filename);
    if(!file.is_open())
    {
        cout << "File could not be found\n";
        cout << "--------------------------------------------\n";
    }
    else
    {
        string n;
        getline(file, n);
        int l = stoi(n);
        while(l--)
        {
            string id,name,gpa,department;
            getline(file, id);
            getline(file, name);
            getline(file, gpa);
            getline(file, department);
            int ID = stoi(id);
            double GPA = stod(gpa);
            this->insert(ID, GPA, name, department);
        }
    }
}

void BST::insert(int ID, double GPA, string Name, string Department)
{
    node *newStudent = new node(ID, GPA, Name, Department);
    if(root == nullptr)
    {
        root = newStudent;
        return;
    }

    node *current = root;
    node *parent = nullptr;
    while(current != nullptr)
    {
        parent = current;
        if(ID == current->id)
        {
            cout << "A student with the same ID already exists!\n";
            return;
        }

        if(ID < current->id)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if(ID < parent->id)
    {
        parent->left = newStudent;
    }
    else
    {
        parent->right = newStudent;
    }
}


void BST::search(int ID)
{
    node *current = root;
    while(current != nullptr)
    {
        if(current->id == ID)
        {
            cout << "Student was found\n";
            cout << "[" << current->id << ", " << current->name << ", " << current->gpa << ", " << current->department << "]\n";
            cout << "--------------------------------------------\n";
            return;
        }

        if(current->id > ID)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    cout << "Student does not exist!\n";
    cout << "--------------------------------------------\n";
}

void BST::remove(int ID)
{
    node *current = root;
    node *parent = nullptr;
    while(current != nullptr && current->id != ID)
    {
        parent = current;
        if(current->id > ID)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if(current == nullptr)
    {
        cout << "Student does not exist!\n";
        cout << "--------------------------------------------\n";
        return;
    }
    //The node has no children
    if(current->left == nullptr && current->right == nullptr)
    {
        if(current == root)
        {
            root = nullptr;
        }
        else if(parent->left == current)
        {
            parent->left = nullptr;
        }
        else if(parent->right == current)
        {
            parent->right = nullptr;
        }
        delete current;
    }
    // if the node has one child
    else if(current->left == nullptr || current->right == nullptr)
    {
        node *child;
        if(current->left != nullptr)
        {
            child = current->left;
        }
        else
        {
            child = current->right;
        }
        // attaching the child to the parent of the node
        if(current == root)
        {
            root = child;
        }
        else if(parent->left == current)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
    }
    //if the node has two children
    else
    {
        // the predecessor is the node with the largest value in the left subtree
        node *predecessor = current->left;
        while(predecessor->right != nullptr)
        {
            parent = predecessor;
            predecessor = predecessor->right;
        }

        if(parent == current)
        {
            parent->left = predecessor->left;
        }
        else
        {
            parent->right = predecessor->left;
        }

        if(current == root)
        {
            root = predecessor;
        }
        else if(parent->left == current)
        {
            parent->left = predecessor;
        }
        else
        {
            parent->right = predecessor;
        }

        predecessor->left = current->left;
        predecessor->right = current->right;
    }
}

node *BST::getRoot()
{
    return root;
}

void BST::printAll(node *n)
{
    if(n != nullptr)
    {
        if(n->department == "CS")
        {
            CS++;
        }
        else if(n->department == "IS")
        {
            IS++;
        }
        else if(n->department == "AI")
        {
            AI++;
        }
        else if(n->department == "IT")
        {
            IT++;
        }
        else if(n->department == "DS")
        {
            DS++;
        }
        printAll(n->left);
        cout << "[" << n->id << ", " << n->name << ", " << n->gpa << ", " << n->department << "]\n";
        printAll(n->right);
    }
}

void BST::printReport()
{
    cout << "Students per department:\n";
    cout << "CS : " << CS << " Students\n";
    cout << "IS : " << IS << " Students\n";
    cout << "AI : " << AI << " Students\n";
    cout << "DS : " << DS << " Students\n";
    cout << "IT : " << IT << " Students\n";
    cout << "--------------------------------------------\n";
    CS=0,AI=0,IT=0,DS=0,IS=0;
}

void BST::run()
{
    this->loadFile();
    int f=1;
    while(f)
    {
        cout << "Choose one of the following options:\n";
        cout << "1- Add student\n";
        cout << "2- Remove student\n";
        cout << "3- Search student\n";
        cout << "4- Print All\n";
        cout << "5- Return to main menu\n";
        cout << "Option: ";
        string name,department;
        int ID;
        double GPA;
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "ID: ";
                cin >> ID;
                cout << "Name: ";
                cin.ignore();
                getline(cin,name);
                cout << "GPA: ";
                cin >> GPA;
                cout << "Department: ";
                cin >> department;
                this->insert(ID,GPA,name,department);
                break;
            case 2:
                cout << "ID: ";
                cin >> ID;
                this->remove(ID);
                break;
            case 3:
                cout << "ID: ";
                cin >> ID;
                this->search(ID);
                break;
            case 4:
                this->printAll(this->getRoot());
                this->printReport();
                break;
            case 5:
                f=0;
                break;
        }
    }
}

int main()
{
    BST students;
    students.run();
}