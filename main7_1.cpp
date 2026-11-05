#include <iostream>
#include <string>
using namespace std;
struct Node {
    string city;   // город
    Node* left;    // левый потомок
    Node* right;   // правый потомок
    int height;    // высота
    Node(string value) {
        city = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// получить высоту
int getHeight(Node* root){
    if(root == nullptr){
        return 0;
    } else {
        return (root->height);
    }
}     

// обновить высоту
void updateHeight(Node* root)  {
    int right = getHeight(root->right);
    int left = getHeight(root->left);
    if ( right > left){
        right++;
        root->height = right;
    } else{
        left ++;
        root->height = left;
    }
}

// вычислить баланс
int getBalance(Node* root){
    if (root == nullptr){
        return 0;
    } else {
        int right = getHeight(root->right);
        int left = getHeight(root->left);
        int diff = left - right;
        return diff;
    }
    
}   

// левый поворот 
Node* rotateLeft(Node* root){
    Node* right = (root->right);
    Node* ne = right->left;
    right->left = root;
    root->right = ne;
    updateHeight(root);
    updateHeight(right);
    return right;
}    

// правый поворот
Node* rotateRight(Node* root) {
    Node* left = (root->left);
    Node* ne = left->right;
    left->right = root;
    root->left = ne;
    updateHeight(root);
    updateHeight(left);
    return left;
 
} 

// добавить город 
Node* insert(Node* current, string str){
    if(current == nullptr){
        Node* pow = new Node(str);
        return pow;
    }
    if ( str < current->city){
        current->left = insert(current->left, str);
    } else if (str > current->city){
        current-> right = insert(current->right, str);   
    } else {
        return current;
    }
    updateHeight(current);
    int balance = getBalance(current);
    if (balance>1 && str < current->left->city){
        return rotateRight(current);
    } else if (balance<-1 && str > current->right->city){
        return rotateLeft(current);
    } else if (balance>1 && str > current->left->city){
        current->left =rotateLeft(current->left);
        return rotateRight(current);
    }  else if (balance<-1 && str < current->right->city){
        current->right =rotateRight(current->right);
        return rotateLeft(current);
    }
    return current;
}        

// симметричный обход
void inorder( Node* root){

   if(root == nullptr){
    return;
   } 
   inorder(root->left);    
   cout << root->city + ' ';
   inorder(root->right);
}  

// обратный обход
void postorder(Node* root)  {
    if(root == nullptr){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->city + ' ';
}   

// длина пути
int pathLength(Node* root, string str) {
    int count = 0;

    while (root != nullptr) {
        if (str == root->city) {
            return count;
        } else if (str < root->city) {
            root = root->left;
        } else {
            root = root->right;
        }

        count++;
    }

    return -1;
}    
// очистить дерево
void clearTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    clearTree(root->left);
    clearTree(root->right);

    delete root;
}

int main() {
    Node* root = nullptr;
    int choice;

    do {
        cout << "\n1. Добавить город\n";
        cout << "2. Обратный обход\n";
        cout << "3. Симметричный обход\n";
        cout << "4. Найти длину пути\n";
        cout << "5. Найти высоту дерева\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        if (choice == 1) {
            string city;

            cout << "Введите город: ";
            cin >> city;

            root = insert(root, city);

            cout << "Город добавлен.\n";
        } else if (choice == 2) {
            cout << "Обратный обход: ";

            postorder(root);

            cout << "\n";
        } else if (choice == 3) {
            cout << "Симметричный обход: ";

            inorder(root);

            cout << "\n";
        } else if (choice == 4) {
            string city;

            cout << "Введите город: ";
            cin >> city;

            int result = pathLength(root, city);

            if (result == -1) {
                cout << "Город не найден.\n";
            } else {
                cout << "Длина пути: " << result << "\n";
            }
        } else if (choice == 5) {
            cout << "Высота дерева: "
                 << getHeight(root) << "\n";
        } else if (choice != 0) {
            cout << "Нет такого пункта.\n";
        }

    } while (choice != 0);

    clearTree(root);

    return 0;
}
