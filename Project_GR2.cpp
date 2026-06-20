#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <limits>
#include <sys/stat.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <sstream>
using namespace std;
void clearScreen(){
    system("cls");
}
void waitForKey(){
    cout << "\nPress any key to continue...";
    getch();
}
const int LINE_WIDTH = 70;
const string LINE(LINE_WIDTH, '-');
const string DOUBLE_LINE(LINE_WIDTH, '=');
const string ORDER_LINE = LINE;
void createDataFolder(){
    struct stat st;
    if(stat("data", &st) != 0){
        mkdir("data");
    }
    if(stat("data/receipts", &st) != 0){
        mkdir("data/receipts");
    }
    if(stat("data/sales", &st) != 0){
        mkdir("data/sales");
    }
    if(stat("data/reports", &st) != 0){
        mkdir("data/reports");
    }
}
void printPageTitle(const string& title){
    int boxWidth = 70;
    int titleLen = title.length();
    int leftSpaces = (boxWidth - titleLen) / 2;
    int rightSpaces = boxWidth - titleLen - leftSpaces;
    cout << "\n"
         << "  +" << string(boxWidth, '-') << "+\n"
         << "  |" << string(leftSpaces, ' ') << title << string(rightSpaces, ' ') << "|\n"
         << "  +" << string(boxWidth, '-') << "+\n\n";
}
void clearInput(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void printStoreBanner(){
    cout << "\n"
         << "            ***************************************************************\n"
         << "            *                                                             *\n"
         << "            *                 W E L C O M E   T O   O U R                 *\n"
         << "            *                 C L O T H I N G   S T O R E                 *\n"
         << "            *                                                             *\n"
         << "            *               >>  Online Shopping System  <<                *\n"
         << "            *                                                             *\n"
         << "            ***************************************************************\n\n";
}
void loadingAnimation(int seconds){
    const char symbols[] = {'|', '/', '-', '\\'};
    int count = 0;
    for(int i = 0; i < seconds * 10; i++){
        cout << "\rProcessing payment " << symbols[count % 4] << "   ";
        cout.flush();
        Sleep(100);
        count++;
    }
    cout << "\rPayment completed!          \n";
}
void printReceiptBox(const string& filename){
    ifstream in(filename.c_str());
    if(!in){
        return;
    }
    string line;
    cout << "\n"
         << "  .----------------------------------------------------------------------.\n"
         << "  |                           PAYMENT RECEIPT                            |\n"
         << "  +----------------------------------------------------------------------+\n";
    while(getline(in, line)){
        int pad = 68 - (int)line.length();
        if(pad < 0){
            pad = 0;
        }
        cout << "  | " << line << string(pad, ' ') << " |\n";
    }
    cout << "  '----------------------------------------------------------------------'\n\n";
}
string center(const string& s, int width){
    int len = s.length();
    if(len >= width){
        return s.substr(0, width);
    }
    int left = (width - len) / 2;
    int right = width - len - left;
    return string(left, ' ') + s + string(right, ' ');
}
string formatPrice(double price){
    ostringstream oss;
    oss << fixed << setprecision(2) << "RM" << price;
    return oss.str();
}
bool isValidUsername(const string& s){
    if(s.empty()){
        return false;
    }
    for(char c : s){
        if(!isalpha(c)){
            return false;
        }
    }
    return true;
}
bool isValidPassword(const string& s){
    return s.length() >= 6;
}
bool isValidName(const string& s){
    if(s.empty()){
        return false;
    }
    for(char c : s){
        if(!isalpha(c) && c != ' '){
            return false;
        }
    }
    return true;
}
bool isValidPhone(const string& s){
    if(s.length() != 10 && s.length() != 11){
        return false;
    }
    for(char c : s){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}
bool isValidNonEmpty(const string& s){
    return !s.empty();
}
bool isValidCVV(const string& s){
    if(s.length() != 3 && s.length() != 4){
        return false;
    }
    for(char c : s){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}
string getValidatedString(const string& prompt, bool (*validator)(const string&), const string& errorMsg){
    string input;
    while(true){
        cout << prompt;
        getline(cin, input);
        if(validator(input)){
            return input;
        }
        cout << errorMsg << endl << endl;
    }
}
int getIntInput(const string& prompt, int minVal, int maxVal){
    int value;
    while(true){
        cout << prompt;
        cin >> value;
        if(cin.fail()){
            cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n" << endl;
            clearInput();
        }
        else if(value < minVal || value > maxVal){
            cout << "Please enter a number between " << minVal << " and " << maxVal << ".\n" << endl;
            clearInput();
        }
        else{
            clearInput();
            return value;
        }
    }
}
int getPositiveInt(const string& prompt){
    int value;
    while(true){
        cout << prompt;
        cin >> value;
        if(cin.fail() || value <= 0){
            cout << "Invalid quantity. Please enter a positive integer.\n" << endl;
            clearInput();
        }
        else{
            clearInput();
            return value;
        }
    }
}
int getPositiveIntWithSkip(const string& prompt){
    while(true){
        cout << prompt;
        string input;
        getline(cin, input);
        if(input.empty()){
            return -1;
        }
        stringstream ss(input);
        int value;
        if(ss >> value && value > 0 && ss.eof()){
            return value;
        }
        cout << "Invalid quantity. Please enter a positive integer or press Enter to skip.\n" << endl;
    }
}
bool getYesNo(const string& prompt){
    string input;
    while(true){
        cout << prompt;
        cin >> input;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input. Please enter y or n.\n" << endl;
            continue;
        }
        clearInput();
        if(input == "y" || input == "Y"){
            return true;
        }
        if(input == "n" || input == "N"){
            return false;
        }
        cout << "Invalid input. Please enter y or n.\n" << endl;
    }
}
double getDoubleInput(const string& prompt){
    double value;
    while(true){
        cout << prompt;
        cin >> value;
        if(cin.fail()){
            cout << "Invalid input. Please enter a valid number.\n" << endl;
            clearInput();
        }
        else{
            clearInput();
            return value;
        }
    }
}
string getValidCardNumber(){
    string card;
    while(true){
        cout << "\nEnter card number (16 digits): ";
        cin >> card;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input. Please enter numbers only.\n" << endl;
            continue;
        }
        if(card.length() != 16){
            cout << "Card number must be exactly 16 digits. You entered " << card.length() << " digits.\n" << endl;
            continue;
        }
        bool allDigits = true;
        for(char c : card){
            if(!isdigit(c)){
                allDigits = false;
                break;
            }
        }
        if(!allDigits){
            cout << "Card number must contain only digits.\n" << endl;
            continue;
        }
        return card;
    }
}
bool getValidExpiry(int &month, int &year){
    time_t now = time(0);
    struct tm *local = localtime(&now);
    int currentYear = local->tm_year % 100;
    int currentMonth = local->tm_mon + 1;
    while(true){
        cout << "Enter expiry (MM YY) e.g., 10 26: ";
        cin >> month >> year;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input. Please enter two numbers (month and year).\n" << endl;
            continue;
        }
        clearInput();
        if(month < 1 || month > 12){
            cout << "Month must be between 1 and 12.\n" << endl;
            continue;
        }
        if(year < currentYear || (year == currentYear && month <= currentMonth)){
            cout << "Expiry date must be in the future (after current month/year).\n" << endl;
            continue;
        }
        if(year > 99){
            cout << "Year must be two digits (e.g., 26 for 2026).\n" << endl;
            continue;
        }
        return true;
    }
}
string toLower(string str){
    for(size_t i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}
int nextOrderId = 1;
struct Product{
    int prodID;
    string prodName;
    string category;
    double price;
    int stock;
    int rating;
    Product(int id = 0, string name = "", string cat = "", double p = 0.0, int s = 0, int r = 0){
        prodID = id;
        prodName = name;
        category = cat;
        price = p;
        stock = s;
        rating = r;
    }
    bool operator==(const Product& other) const{
        return prodID == other.prodID;
    }
    friend void displayProductDetails(const Product& p);
    friend void compareProductPrice(const Product& p1, const Product& p2);
};
struct OrderItem{
    int productId;
    string productName;
    int quantity;
    double subtotal;
    bool rated;
    int ratingValue;
    string comment;
};
struct CartItem{
    int productId;
    string productName;
    string size;
    int quantity;
    double price;
};
struct Node{
    Product data;
    Node* next;
};
class ADTqueue{
private:
    Node *front, *rear;
    int lastComparisons;
    int lastSwaps;
    double lastExecutionTime;
public:
    ADTqueue(){
        front = rear = NULL;
        lastComparisons = lastSwaps = 0;
        lastExecutionTime = 0;
    }
    ~ADTqueue(){
        while(!empty()){
            serve();
        }
    }
    bool empty(){
        return front == NULL;
    }
    void append(Product p){
        if(rear != NULL){
            rear->next = new Node;
            rear = rear->next;
            rear->data = p;
            rear->next = NULL;
        }
        else{
            front = rear = new Node;
            front->data = p;
            front->next = NULL;
        }
    }
    Product serve(){
        Product p;
        if(!empty()){
            p = front->data;
            Node* temp = front;
            front = front->next;
            delete temp;
            if(front == NULL){
                rear = NULL;
            }
        }
        return p;
    }
    void displaySortedById(){
        if(empty()){
            cout << "No product records found." << endl;
            return;
        }
        ADTqueue tempQueue;
        duplicateQueue(tempQueue);
        int size = tempQueue.getSize();
        for(int i=0; i<size-1; i++){
            for(int j=0; j<size-i-1; j++){
                Node* node1 = tempQueue.getNode(j);
                Node* node2 = tempQueue.getNode(j + 1);
                if(node1 && node2 && node1->data.prodID>node2->data.prodID){
                    Product temp = node1->data;
                    node1->data = node2->data;
                    node2->data = temp;
                }
            }
        }
        Node* temp = tempQueue.front;
        cout << "  " << center("Prod ID", 8)
             << center("Name", 25)
             << center("Category", 15)
             << center("Price", 10)
             << center("Stock", 8)
             << center("Rating", 8) << endl;
        cout << "  " << string(70, '-') << endl;
        while(temp != NULL){
            cout << "  " << center(to_string(temp->data.prodID), 8)
                 << center(temp->data.prodName, 25)
                 << center(temp->data.category, 15)
                 << center(formatPrice(temp->data.price), 10)
                 << center(to_string(temp->data.stock), 8)
                 << center(to_string(temp->data.rating), 8) << endl;
            temp = temp->next;
        }
    }
    void displayCurrentOrder(){
        if(empty()){
            cout << "No product records found." << endl;
            return;
        }
        Node* temp = front;
        cout << "  " << center("Prod ID", 8)
             << center("Name", 25)
             << center("Category", 15)
             << center("Price", 10)
             << center("Stock", 8)
             << center("Rating", 8) << endl;
        cout << "  " << string(70, '-') << endl;
        while(temp != NULL){
            cout << "  " << center(to_string(temp->data.prodID), 8)
                 << center(temp->data.prodName, 25)
                 << center(temp->data.category, 15)
                 << center(formatPrice(temp->data.price), 10)
                 << center(to_string(temp->data.stock), 8)
                 << center(to_string(temp->data.rating), 8) << endl;
            temp = temp->next;
        }
    }
    void duplicateQueue(ADTqueue &newQueue){
        Node* temp = front;
        while(temp != NULL){
            newQueue.append(temp->data);
            temp = temp->next;
        }
    }
    int getSize(){
        int count = 0;
        Node* temp = front;
        while(temp != NULL){
            count++;
            temp = temp->next;
        }
        return count;
    }
    Node* getNode(int index){
        Node* temp = front;
        int count = 0;
        while(temp != NULL && count<index){
            temp = temp->next;
            count++;
        }
        return temp;
    }
    void swapProd(Node* a, Node* b){
        Product temp = a->data;
        a->data = b->data;
        b->data = temp;
    }
    bool needSwap(Product a, Product b, int sortOption){
        switch (sortOption){
            case 1: return a.price > b.price;
            case 2: return a.rating > b.rating;
            case 3: return toLower(a.category) > toLower(b.category);
            case 4: return a.prodID > b.prodID;
            case 5: return a.stock > b.stock;
            default: return false;
        }
    }
    void quickSort(int sortOption){
        int size = getSize();
        if(size <= 1){
            return;
        }
        quickSortRec(0, size - 1, sortOption);
    }
private:
    void quickSortRec(int left, int right, int sortOption){
        if(left < right){
            int pivot = partition(left, right, sortOption);
            quickSortRec(left, pivot - 1, sortOption);
            quickSortRec(pivot + 1, right, sortOption);
        }
    }
    int partition(int left, int right, int sortOption){
        swapProd(getNode(left), getNode((left + right) / 2));
        Product pivotVal = getNode(left)->data;
        int lastSmall = left;
        for(int i = left + 1; i <= right; i++){
            bool shouldSwap = false;
            switch (sortOption){
                case 1: shouldSwap = getNode(i)->data.price < pivotVal.price; break;
                case 2: shouldSwap = getNode(i)->data.rating < pivotVal.rating; break;
                case 3: shouldSwap = toLower(getNode(i)->data.category) < toLower(pivotVal.category); break;
                case 4: shouldSwap = getNode(i)->data.prodID < pivotVal.prodID; break;
                case 5: shouldSwap = getNode(i)->data.stock < pivotVal.stock; break;
            }
            if(shouldSwap){
                lastSmall++;
                swapProd(getNode(lastSmall), getNode(i));
            }
        }
        swapProd(getNode(left), getNode(lastSmall));
        return lastSmall;
    }
public:
    int getLastComparisons(){
        return lastComparisons;
    }
    int getLastSwaps(){
        return lastSwaps;
    }
    double getLastExecutionTime(){
        return lastExecutionTime;
    }
    void searchByName(string keyword){
        if(empty()){
            cout << "No product records found." << endl;
            return;
        }
        int size = getSize();
        Product* arr = new Product[size];
        Node* temp = front;
        for(int i = 0; i < size; i++){
            arr[i] = temp->data;
            temp = temp->next;
        }
        string target = toLower(keyword);
        bool found = false;
        cout << endl;
        cout << "  " << center("Prod ID", 8)
             << center("Name", 25)
             << center("Category", 15)
             << center("Price", 10)
             << center("Stock", 8)
             << center("Rating", 8) << endl;
        cout << "  " << string(70, '-') << endl;
        for(int i = 0; i < size; i++){
            string lowerName = toLower(arr[i].prodName);
            if(lowerName.find(target) != string::npos){
                cout << "  " << center(to_string(arr[i].prodID), 8)
                     << center(arr[i].prodName, 25)
                     << center(arr[i].category, 15)
                     << center(formatPrice(arr[i].price), 10)
                     << center(to_string(arr[i].stock), 8)
                     << center(to_string(arr[i].rating), 8) << endl;
                found = true;
            }
        }
        if(!found){
            cout << "No product found matching \"" << keyword << "\"." << endl;
        }
        delete[] arr;
    }
    Product binarySearchById(int targetId){
        if(empty()){
            return Product();
        }
        int size = getSize();
        Product* arr = new Product[size];
        Node* temp = front;
        for(int i = 0; i < size; i++){
            arr[i] = temp->data;
            temp = temp->next;
        }
        int first = 0, last = size - 1;
        while(first <= last){
            int mid = (first + last) / 2;
            if(arr[mid].prodID == targetId){
                Product result = arr[mid];
                delete[] arr;
                return result;
            }
            else if(arr[mid].prodID < targetId){
                first = mid + 1;
            }
            else{
                last = mid - 1;
            }
        }
        delete[] arr;
        return Product();
    }
};
class Person{
protected:
    string fullName;
    string phone;
public:
    Person(string name = "", string tel = ""){
        fullName = name;
        phone = tel;
    }
    virtual ~Person(){}
    virtual void displayInfo() = 0;
    string getName() const{
        return fullName;
    }
    string getPhone() const{
        return phone;
    }
};
class Account : public Person{
protected:
    string username;
    string password;
    bool loggedIn;
public:
    Account(string user = "", string pass = "", string name = "", string tel = "")
        : Person(name, tel){
        username = user;
        password = pass;
        loggedIn = false;
    }
    virtual ~Account(){}
    bool login(string user, string pass){
        if(username == user && password == pass){
            loggedIn = true;
            return true;
        }
        return false;
    }
    bool login(int id, string pass){
        if(id == stoi(username) && password == pass){
            loggedIn = true;
            return true;
        }
        return false;
    }
    void logout(){
        loggedIn = false;
        cout << "Logging out... bye." << endl;
    }
    bool isLoggedIn() const{
        return loggedIn;
    }
    string getUsername() const{
        return username;
    }
    string getPassword() const{
        return password;
    }
    virtual void displayMenu() = 0;
    void displayInfo() override{
        cout << "User: " << username << ", Name: " << fullName << ", Phone: " << phone << endl;
    }
};
class Order{
private:
    int orderId;
    string customerName;
    OrderItem* items;
    int itemCount;
    double totalAmount;
    string status;
    string orderDate;
public:
    Order(int id = 0, string cust = ""){
        orderId = id;
        customerName = cust;
        items = NULL;
        itemCount = 0;
        totalAmount = 0.0;
        status = "pending payment";
        time_t now = time(0);
        struct tm *local = localtime(&now);
        char buffer[11];
        strftime(buffer, 11, "%Y-%m-%d", local);
        orderDate = buffer;
    }
    ~Order(){
        if(items != NULL){
            delete[] items;
            items = NULL;
        }
    }
    Order(const Order& other){
        orderId = other.orderId;
        customerName = other.customerName;
        itemCount = other.itemCount;
        totalAmount = other.totalAmount;
        status = other.status;
        orderDate = other.orderDate;
        if(itemCount > 0){
            items = new OrderItem[itemCount];
            for(int i = 0; i < itemCount; i++){
                items[i] = other.items[i];
            }
        }
        else{
            items = NULL;
        }
    }
    Order& operator=(const Order& other){
        if(this != &other){
            if(items != NULL){
                delete[] items;
                items = NULL;
            }
            orderId = other.orderId;
            customerName = other.customerName;
            itemCount = other.itemCount;
            totalAmount = other.totalAmount;
            status = other.status;
            orderDate = other.orderDate;
            if(itemCount > 0){
                items = new OrderItem[itemCount];
                for(int i = 0; i < itemCount; i++){
                    items[i] = other.items[i];
                }
            }
        }
        return *this;
    }
    void addItem(int prodId, string prodName, int qty, double price){
        OrderItem* newItems = new OrderItem[itemCount + 1];
        for(int i = 0; i < itemCount; i++){
            newItems[i] = items[i];
        }
        newItems[itemCount].productId = prodId;
        newItems[itemCount].productName = prodName;
        newItems[itemCount].quantity = qty;
        newItems[itemCount].subtotal = qty * price;
        totalAmount += newItems[itemCount].subtotal;
        if(items != NULL){
            delete[] items;
        }
        items = newItems;
        itemCount++;
    }
    int getOrderId() const{
        return orderId;
    }
    string getStatus() const{
        return status;
    }
    void setStatus(string s){
        status = s;
    }
    double getTotal() const{
        return totalAmount;
    }
    string getCustomerName() const{
        return customerName;
    }
    int getItemCount() const{
        return itemCount;
    }
    OrderItem* getItems() const{
        return items;
    }
    string getOrderDate() const{
        return orderDate;
    }
    void displaySummary() const{
        cout << "  " << center("Product ID", 12)
             << center("Product Name", 20)
             << center("Quantity", 10)
             << center("Subtotal", 12) << endl;
        cout << "  " << string(70, '-') << endl;
        for(int i = 0; i < itemCount; i++){
            cout << "  " << center(to_string(items[i].productId), 12)
                 << center(items[i].productName, 20)
                 << center(to_string(items[i].quantity), 10)
                 << center(formatPrice(items[i].subtotal), 12) << endl;
        }
        cout << "  " << string(70, '-') << endl;
        cout << "\nTotal Amount: RM" << fixed << setprecision(2) << totalAmount << endl;
    }
    friend void displayOrderSummary(const Order& o);
    friend void updateOrderStatus(Order& o, string newStatus);
};
class Customer : public Account{
        private:
            int customerId;
            Order* orderHistory;
            int orderCount;
            CartItem* cart;
            int cartCount;
            int cartCapacity;
public:
    Customer(string user = "", string pass = "", int id = 0, string name = "", string tel = "")
        : Account(user, pass, name, tel), customerId(id){
        orderHistory = NULL;
        orderCount = 0;
        cart = new CartItem[10];
        cartCount = 0;
        cartCapacity = 10;
    }
    ~Customer(){
        if(orderHistory != NULL){
            delete[] orderHistory;
            orderHistory = NULL;
        }
        if(cart != NULL){
            delete[] cart;
            cart = NULL;
        }
    }
    void addOrder(const Order& newOrder);
    void addOrderWithoutGlobal(const Order& newOrder);
    void viewOrders() const;
    void addToCart(bool showList = true, bool showTitle = true, bool isRoot = true);
    void viewCart();
    void checkout();
    void rateProducts();
    void displayMenu() override;
    void viewProducts();
    void searchProduct();
    void sortProducts();
    void generatePersonalReport();
    int getCustomerId() const{
        return customerId;
    }
    int getOrderCount() const{
        return orderCount;
    }
    Order* getOrderHistory(){
        return orderHistory;
    }
    const Order* getOrderHistory() const{
        return orderHistory;
    }
    void cartPushBack(const CartItem& item);
    void cartRemoveAt(int index);
    int cartFind(int productId);
    CartItem* getCartItem(int index);
    int getCartCount() const{
        return cartCount;
    }
    void clearCart();
};
class Admin : public Account{
public:
    Admin(string user = "", string pass = "", string name = "", string tel = "")
        : Account(user, pass, name, tel){
    }
    ~Admin(){}
    void displayMenu() override;
    void searchProductById();
    void addProduct();
    void editProduct();
    void deleteProduct();
    void viewProducts();
    void searchProduct();
    void sortProducts();
    void viewAllOrders();
    void updateOrderStatus();
    void generateSalesReport();
    void viewFeedback();
};
void displayProductDetails(const Product& p);
void compareProductPrice(const Product& p1, const Product& p2);
void displayOrderSummary(const Order& o);
void updateOrderStatus(Order& o, string newStatus);
ADTqueue allProducts;
const int MAX_CUSTOMERS = 50;
Customer allCustomers[MAX_CUSTOMERS];
int customerCount = 0;
const int MAX_ADMINS = 10;
Admin allAdmins[MAX_ADMINS];
int adminCount = 0;
Order* allOrders = NULL;
int allOrdersCount = 0;
int allOrdersCapacity = 0;
bool processPayment(double amount, const Order& order);
void saveProductsToFile();
void loadOrdersFromFile();
void saveOrdersToFile();
void loadFeedbacksFromFile();
void saveFeedbacksToFile();
void addToAllOrders(const Order& o);
void loadCustomersFromFile();
void saveCustomersToFile();
void loadAdminsFromFile();
void saveAdminsToFile();
void registerCustomer();
void registerAdmin();
void Customer::viewProducts(){
    printPageTitle("PRODUCT LIST");
    allProducts.displaySortedById();
    waitForKey();
}
void Customer::searchProduct(){
    printPageTitle("SEARCH PRODUCT");
    string keyword = getValidatedString("Enter product name keyword: ", isValidNonEmpty, "Keyword cannot be empty.");
    allProducts.searchByName(keyword);
    waitForKey();
}
void Customer::sortProducts(){
    printPageTitle("SORT PRODUCTS");
    cout << "Sort By:" << endl;
    cout << "1. Price" << endl;
    cout << "2. Rating" << endl;
    cout << "3. Category" << endl;
    cout << "4. Product ID" << endl;
    cout << "5. Stock" << endl;
    int opt = getIntInput("Option: ", 1, 5);
    ADTqueue temp;
    allProducts.duplicateQueue(temp);
    temp.quickSort(opt);
    cout << endl;
    temp.displayCurrentOrder();
    waitForKey();
}
void Customer::generatePersonalReport(){
    string filename = "data/reports/customer_report_" + username + ".txt";
    ofstream out(filename.c_str());
    if(!out){
        cerr << "Error: Cannot create report file.\n";
        waitForKey();
        return;
    }
    out << "  +" << string(70, '-') << "+\n";
    out << "  |" << center("Personal Report for " + username, 68) << "|\n";
    out << "  +" << string(70, '-') << "+\n\n";
    out << "  " << center("Order ID", 10)
        << center("Total Amount", 20)
        << center("Status", 12) << endl;
    out << "  " << string(70, '-') << endl;
    double totalSpent = 0;
    for(int i = 0; i < orderCount; i++){
        totalSpent += orderHistory[i].getTotal();
        out << "  " << center(to_string(orderHistory[i].getOrderId()), 10)
            << center(formatPrice(orderHistory[i].getTotal()), 20)
            << center(orderHistory[i].getStatus(), 12) << endl;
    }
    out << "  " << string(70, '-') << endl;
    out << "\nTotal Orders: " << orderCount << endl;
    out << "Total Spent: RM" << fixed << setprecision(2) << totalSpent << endl;
    out.close();
    ifstream in(filename.c_str());
    if(in){
        string line;
        while(getline(in, line)){
            cout << line << endl;
        }
        in.close();
    }
    waitForKey();
}
void Admin::addProduct(){
    printPageTitle("ADD PRODUCT");
    cout << "Current product list:\n\n";
    allProducts.displaySortedById();
    int maxId = 0;
    Node* temp = allProducts.getNode(0);
    while(temp != NULL){
        if(temp->data.prodID > maxId){
            maxId = temp->data.prodID;
        }
        temp = temp->next;
    }
    int newId = maxId + 1;
    cout << "\nAuto-generated Product ID: " << newId << endl;
    Product p;
    p.prodID = newId;
    bool validName = false;
    string name;
    while(!validName){
        cout << "Enter product name: ";
        getline(cin, name);
        if(!isValidNonEmpty(name)){
            cout << "Product name cannot be empty.\n" << endl;
            continue;
        }
        string lowerName = toLower(name);
        Node* check = allProducts.getNode(0);
        bool duplicate = false;
        while(check != NULL){
            if(toLower(check->data.prodName) == lowerName){
                duplicate = true;
                break;
            }
            check = check->next;
        }
        if(duplicate){
            cout << "Product name \"" << name << "\" already exists. Please enter a different name.\n" << endl;
        }
        else{
            validName = true;
            p.prodName = name;
        }
    }
    p.category = getValidatedString("Enter category: ", isValidNonEmpty, "Category cannot be empty.");
    p.price = getDoubleInput("Enter price: ");
    p.stock = getIntInput("Enter stock: ", 0, 999999);
    do{
        p.rating = getIntInput("Enter rating (1-5): ", 1, 5);
    }
    while(p.rating < 1 || p.rating > 5);
    allProducts.append(p);
    saveProductsToFile();
    cout << "Product added successfully!" << endl;
    allProducts.displaySortedById();
    waitForKey();
}
void Admin::editProduct(){
    printPageTitle("EDIT PRODUCT");
    cout << "Current product list:\n\n";
    allProducts.displaySortedById();
    int id = getIntInput("\nEnter product ID to edit: ", 1, 9999);
    Node* temp = allProducts.getNode(0);
    Node* target = NULL;
    while(temp != NULL){
        if(temp->data.prodID == id){
            target = temp;
            break;
        }
        temp = temp->next;
    }
    if(!target){
        cout << "Product not found!" << endl;
        waitForKey();
        return;
    }
    cout << "\nEditing product ID " << id << " - Current values:" << endl;
    cout << "  " << center("Prod ID", 8) << center("Name", 25) << center("Category", 15)
         << center("Price", 10) << center("Stock", 8) << center("Rating", 8) << endl;
    cout << "  " << string(70, '-') << endl;
    cout << "  " << center(to_string(target->data.prodID), 8)
         << center(target->data.prodName, 25)
         << center(target->data.category, 15)
         << center(formatPrice(target->data.price), 10)
         << center(to_string(target->data.stock), 8)
         << center(to_string(target->data.rating), 8) << endl;
    cout << "\nLeave blank to keep current value." << endl;
    string input;
    cout << "New name (" << target->data.prodName << "): ";
    getline(cin, input);
    if(!input.empty()){
        if(isValidNonEmpty(input)){
            string lowerInput = toLower(input);
            Node* check = allProducts.getNode(0);
            bool duplicate = false;
            while(check != NULL){
                if(check->data.prodID != target->data.prodID && toLower(check->data.prodName) == lowerInput){
                    duplicate = true;
                    break;
                }
                check = check->next;
            }
            if(duplicate){
                cout << "Product name \"" << input << "\" already exists. Keeping old value.\n";
            }
            else{
                target->data.prodName = input;
            }
        }
        else{
            cout << "Invalid name. Keeping old value.\n";
        }
    }
    cout << "New category (" << target->data.category << "): ";
    getline(cin, input);
    if(!input.empty()){
        if(isValidNonEmpty(input)){
            target->data.category = input;
        }
        else{
            cout << "Invalid category. Keeping old value.\n";
        }
    }
    cout << "New price (" << target->data.price << "): ";
    getline(cin, input);
    if(!input.empty()){
        stringstream ss(input);
        double val;
        if(ss >> val && val >= 0){
            target->data.price = val;
        }
        else{
            cout << "Invalid price. Keeping old value.\n";
        }
    }
    cout << "New stock (" << target->data.stock << "): ";
    getline(cin, input);
    if(!input.empty()){
        stringstream ss(input);
        int val;
        if(ss >> val && val >= 0){
            target->data.stock = val;
        }
        else{
            cout << "Invalid stock. Keeping old value.\n";
        }
    }
    cout << "New rating (1-5) (" << target->data.rating << "): ";
    getline(cin, input);
    if(!input.empty()){
        stringstream ss(input);
        int val;
        if(ss >> val && val >= 1 && val <= 5){
            target->data.rating = val;
        }
        else{
            cout << "Invalid rating (must be 1-5). Keeping old value.\n";
        }
    }
    saveProductsToFile();
    cout << "\nProduct updated! New record:" << endl;
    cout << "  " << center("Prod ID", 8) << center("Name", 25) << center("Category", 15)
         << center("Price", 10) << center("Stock", 8) << center("Rating", 8) << endl;
    cout << "  " << string(70, '-') << endl;
    cout << "  " << center(to_string(target->data.prodID), 8)
         << center(target->data.prodName, 25)
         << center(target->data.category, 15)
         << center(formatPrice(target->data.price), 10)
         << center(to_string(target->data.stock), 8)
         << center(to_string(target->data.rating), 8) << endl;
    waitForKey();
}
void Admin::deleteProduct(){
    printPageTitle("DELETE PRODUCT");
    cout << "Current product list: \n\n";
    allProducts.displaySortedById();
    int id = getIntInput("\nEnter product ID to delete: ", 1, 9999);
    if(!getYesNo("Are you sure you want to delete this product? (y/n): ")){
        cout << "Deletion cancelled." << endl;
        waitForKey();
        return;
    }
    ADTqueue temp;
    bool found = false;
    while(!allProducts.empty()){
        Product p = allProducts.serve();
        if(p.prodID == id){
            found = true;
        }
        else{
            temp.append(p);
        }
    }
    while(!temp.empty()){
        allProducts.append(temp.serve());
    }
    if(found){
        saveProductsToFile();
        cout << "Product deleted successfully!" << endl;
        allProducts.displaySortedById();
    }
    else{
        cout << "Product not found!" << endl;
    }
    waitForKey();
}
void Admin::viewProducts(){
    printPageTitle("PRODUCT LIST");
    allProducts.displaySortedById();
    waitForKey();
}
void Admin::searchProduct(){
    printPageTitle("SEARCH PRODUCT");
    string keyword = getValidatedString("Enter product name keyword: ", isValidNonEmpty, "Keyword cannot be empty.");
    allProducts.searchByName(keyword);
    waitForKey();
}
void Admin::sortProducts(){
    printPageTitle("SORT PRODUCTS");
    cout << "Sort By:" << endl;
    cout << "1. Price" << endl;
    cout << "2. Rating" << endl;
    cout << "3. Category" << endl;
    cout << "4. Product ID" << endl;
    cout << "5. Stock" << endl;
    int opt = getIntInput("Option: ", 1, 5);
    ADTqueue temp;
    allProducts.duplicateQueue(temp);
    temp.quickSort(opt);
    cout << endl;
    temp.displayCurrentOrder();
    waitForKey();
}
void Admin::viewAllOrders(){
    if(allOrdersCount == 0){
        cout << "\nNo orders found." << endl;
        waitForKey();
        return;
    }
    printPageTitle("ALL ORDERS");
    cout << "  " << center("Order ID", 10)
         << center("Customer", 14)
         << center("Item", 19)
         << center("Qty", 8)
         << center("Total", 10)
         << center("Status", 9) << endl;
    cout << "  " << string(70, '-') << endl;
    for(int i = 0; i < allOrdersCount; i++){
        const Order& ord = allOrders[i];
        int numItems = ord.getItemCount();
        for(int j = 0; j < numItems; j++){
            OrderItem* items = ord.getItems();
            if(j == 0){
                cout << "  " << center(to_string(ord.getOrderId()), 10)
                     << center(ord.getCustomerName(), 14)
                     << center(items[j].productName, 19)
                     << center(to_string(items[j].quantity), 8)
                     << center(formatPrice(items[j].subtotal), 10)
                     << center(ord.getStatus(), 9) << endl;
            }
            else{
                cout << "  " << center("", 10)
                     << center("", 14)
                     << center(items[j].productName, 19)
                     << center(to_string(items[j].quantity), 8)
                     << center(formatPrice(items[j].subtotal), 10)
                     << center("", 9) << endl;
            }
        }
        cout << "  " << string(70, '-') << endl;
    }
    waitForKey();
}
void Admin::updateOrderStatus(){
    if(allOrdersCount == 0){
        cout << "\nThere is no order currently." << endl;
        waitForKey();
        return;
    }
    viewAllOrders();
    int oid;
    bool found = false;
    while(!found){
        oid = getIntInput("\nEnter order ID to update: ", 1, 9999);
        for(int i = 0; i < allOrdersCount; i++){
            if(allOrders[i].getOrderId() == oid){
                found = true;
                cout << "\nCurrent status: " << allOrders[i].getStatus() << endl;
                cout << "Select new status:" << endl;
                cout << "1. To shipped" << endl;
                cout << "2. To received" << endl;
                int choice = getIntInput("Choice: ", 1, 2);
                string newStatus;
                switch (choice){
                    case 1: newStatus = "shipped"; break;
                    case 2: newStatus = "completed"; break;
                }
                allOrders[i].setStatus(newStatus);
                for(int c = 0; c < customerCount; c++){
                    Order* hist = allCustomers[c].getOrderHistory();
                    for(int j = 0; j < allCustomers[c].getOrderCount(); j++){
                        if(hist[j].getOrderId() == oid){
                            hist[j].setStatus(newStatus);
                            break;
                        }
                    }
                }
                saveOrdersToFile();
                cout << "Order status updated to " << newStatus << endl;
                break;
            }
        }
        if(!found){
            cout << "Order not found. Please try again.\n" << endl;
        }
    }
    waitForKey();
}
void Admin::generateSalesReport(){
    printPageTitle("SELECT MONTH TO GENERATE SALES ORDER");
    string monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    cout << "Select month:" << endl;
    for(int i = 0; i < 12; i++){
        cout << (i + 1) << ". " << monthNames[i] << endl;
    }
    int monthChoice = getIntInput("Choice (1-12): ", 1, 12);
    int month = monthChoice;
    string filename = "data/sales/sales_report_" + to_string(month) + ".txt";

    int filteredCount = 0;
    Order filteredOrders[100];
    for(int i = 0; i < allOrdersCount; i++){
        string date = allOrders[i].getOrderDate();
        int m = stoi(date.substr(5, 2));
        if(m == month){
            filteredOrders[filteredCount++] = allOrders[i];
        }
    }

    ofstream out(filename.c_str());
    if(!out){
        cout << "Error: Cannot create report file.\n";
        waitForKey();
        return;
    }
    out << "\n  +" << string(70, '-') << "+\n"
        << "  |" << center("SALES REPORT - " + monthNames[month-1], 68) << "|\n"
        << "  +" << string(70, '-') << "+\n\n";
    out << "  " << center("Order ID", 10)
        << center("Customer", 15)
        << center("Item", 20)
        << center("Qty", 8)
        << center("Total", 10) << endl;
    out << "  " << string(70, '-') << endl;
    double totalRevenue = 0;
    for(int i = 0; i < filteredCount; i++){
        const Order& ord = filteredOrders[i];
        int numItems = ord.getItemCount();
        for(int j = 0; j < numItems; j++){
            OrderItem* items = ord.getItems();
            if(j == 0){
                out << "  " << center(to_string(ord.getOrderId()), 10)
                    << center(ord.getCustomerName(), 15)
                    << center(items[j].productName, 20)
                    << center(to_string(items[j].quantity), 8)
                    << center(formatPrice(items[j].subtotal), 10) << endl;
            }
            else{
                out << "  " << center("", 10)
                    << center("", 15)
                    << center(items[j].productName, 20)
                    << center(to_string(items[j].quantity), 8)
                    << center(formatPrice(items[j].subtotal), 10) << endl;
            }
        }
        out << "  " << string(70, '-') << endl;
        totalRevenue += ord.getTotal();
    }
    out << "\nTotal Orders: " << filteredCount << endl;
    out << "Total Revenue: RM" << fixed << setprecision(2) << totalRevenue << endl;
    out.close();

    clearScreen();
    ifstream in(filename.c_str());
    string line;
    while(getline(in, line)){
        cout << line << endl;
    }
    in.close();
    waitForKey();
}
void Admin::viewFeedback(){
    printPageTitle("CUSTOMER RATINGS & FEEDBACK");
    cout << "  " << center("Customer", 20)
         << center("Product", 20)
         << center("Rating", 10)
         << "Comment" << endl;
    cout << "  " << string(70, '-') << endl;
    bool any = false;
    for(int i = 0; i < allOrdersCount; i++){
        for(int j = 0; j < allOrders[i].getItemCount(); j++){
            OrderItem* items = allOrders[i].getItems();
            if(items[j].rated){
                cout << "  " << center(allOrders[i].getCustomerName(), 20)
                     << center(items[j].productName, 20)
                     << center(to_string(items[j].ratingValue), 10)
                     << items[j].comment << endl;
                any = true;
            }
        }
    }
    if(!any){
        cout << "No ratings yet." << endl;
    }
    waitForKey();
}
void Admin::searchProductById(){
    printPageTitle("SEARCH PRODUCT BY ID");
    int id = getIntInput("Enter Product ID to search: ", 1, 9999);
    Product found = allProducts.binarySearchById(id);
    if(found.prodID != 0){
        cout << "\nProduct found:" << endl;
        cout << "  " << center("Prod ID", 8)
             << center("Name", 25)
             << center("Category", 15)
             << center("Price", 10)
             << center("Stock", 8)
             << center("Rating", 8) << endl;
        cout << "  " << string(70, '-') << endl;
        cout << "  " << center(to_string(found.prodID), 8)
             << center(found.prodName, 25)
             << center(found.category, 15)
             << center(formatPrice(found.price), 10)
             << center(to_string(found.stock), 8)
             << center(to_string(found.rating), 8) << endl;
    }
    else{
        cout << "Product with ID " << id << " not found." << endl;
    }
    waitForKey();
}
void Admin::displayMenu(){
    printPageTitle("ADMIN MENU");
    cout << "1. Add New Product" << endl;
    cout << "2. Edit Product" << endl;
    cout << "3. Delete Product" << endl;
    cout << "4. View All Products" << endl;
    cout << "5. Search Products by Name" << endl;
    cout << "6. Sort Products" << endl;
    cout << "7. View All Orders" << endl;
    cout << "8. Update Order Status" << endl;
    cout << "9. Generate Sales Report" << endl;
    cout << "10. View Customer Ratings & Feedback" << endl;
    cout << "11. Search Product by ID" << endl;
    cout << "12. Logout" << endl;
    cout << LINE << endl;
}
void displayProductDetails(const Product& p){
    cout << "  " << center(to_string(p.prodID), 8)
         << center(p.prodName, 25)
         << center(p.category, 15)
         << center(formatPrice(p.price), 10)
         << center(to_string(p.stock), 8)
         << center(to_string(p.rating), 8) << endl;
}
void compareProductPrice(const Product& p1, const Product& p2){
    if(p1.price < p2.price){
        cout << p1.prodName << " is cheaper than " << p2.prodName << endl;
    }
    else if(p1.price > p2.price){
        cout << p2.prodName << " is cheaper than " << p1.prodName << endl;
    }
    else{
        cout << p1.prodName << " and " << p2.prodName << " have same price." << endl;
    }
}
void displayOrderSummary(const Order& o){
    cout << "Order " << o.orderId << " by " << o.customerName
         << " - Total: RM" << fixed << setprecision(2) << o.totalAmount << " [" << o.status << "]" << endl;
}
void updateOrderStatus(Order& o, string newStatus){
    o.setStatus(newStatus);
    cout << "Order status updated to: " << newStatus << endl;
}
bool processPayment(double amount, const Order& order){
    int paymentMethod;
    clearScreen();
    printPageTitle("PAYMENT");
    cout << endl;
    order.displaySummary();
    cout << "Total amount to pay: RM" << fixed << setprecision(2) << amount << endl;
    cout << "\nSelect payment method:" << endl;
    cout << "1. Credit Card" << endl;
    cout << "2. Bank Transfer" << endl;
    cout << "3. TNG eWallet (QR Code)" << endl;
    paymentMethod = getIntInput("Choice: ", 1, 3);
    switch (paymentMethod){
        case 1:{
            string cardNo = getValidCardNumber();
            int expiryMonth, expiryYear;
            getValidExpiry(expiryMonth, expiryYear);
            string cvv;
            while(true){
                cout << "Enter CVV (3 or 4 digits): ";
                cin >> cvv;
                if(cin.fail()){
                    clearInput();
                    cout << "Invalid input.\n" << endl;
                    continue;
                }
                clearInput();
                if(isValidCVV(cvv)){
                    break;
                }
                cout << "CVV must be 3 or 4 digits.\n" << endl;
            }
            loadingAnimation(3);
            break;
        }
        case 2:{
            cout << "\nBank transfer instructions: Please transfer to Acc No: 1234-5678-90 (Maybank)." << endl;
            cout << "After transfer, press Enter to confirm...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
        case 3:{
            cout << "\n     Please scan the generated QR code below :\n" << endl;
            cout << "     $$$$$$$$$$$$$$$$$$$$$$$$" << endl;
            cout << "     $$$$$  $$$$$$$$$$$$$$$$" << endl;
            cout << "     $$$$$$$$$$$$$$$$$$$$$$$$" << endl;
            cout << "     $$$$$$$$$$ $ $$$  $$$$$$" << endl;
            cout << "     $$$$$$$$$$$$$$$$$$$$$$$$" << endl;
            cout << "     $$$$$  $$$$$$$$$$$$$$$$" << endl;
            cout << "     $$$$$$$$$$$$      $$$$$$" << endl;
            cout << "     $$$$$$$$$$$$$$$$$$$$$$$$" << endl;
            cout << "     $$$$$$$$$$$$$$$$$$$$$$$$" << endl;
            cout << "\nAfter scanning and payment confirmation, press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }
    }
    loadingAnimation(2);
    cout << "\nPayment successful! Thank you for your purchase.\n" << endl;
    return true;
}
void addToAllOrders(const Order& o){
    if(allOrdersCount >= allOrdersCapacity){
        allOrdersCapacity = (allOrdersCapacity == 0) ? 10 : allOrdersCapacity * 2;
        Order* newArr = new Order[allOrdersCapacity];
        for(int i = 0; i < allOrdersCount; i++){
            newArr[i] = allOrders[i];
        }
        if(allOrders != NULL){
            delete[] allOrders;
        }
        allOrders = newArr;
    }
    allOrders[allOrdersCount++] = o;
}
void loadProductsFromFile(){
    ifstream file("data/products.txt");
    if(!file.is_open()){
        Product products[50] = {
            Product(1, "Cotton T-shirt", "Men", 29.90, 50, 4),
            Product(2, "Denim Jeans", "Men", 89.90, 30, 4),
            Product(3, "Leather Jacket", "Men", 129.90, 20, 5),
            Product(4, "Running Shorts", "Men", 39.90, 35, 4),
            Product(5, "Polo Shirt", "Men", 49.90, 25, 4),
            Product(6, "Slim Joggers", "Men", 69.90, 20, 4),
            Product(7, "Cozy Sweater", "Men", 79.90, 15, 4),
            Product(8, "Classic Tuxedo", "Men", 349.90, 8, 5),
            Product(9, "Formal Suit", "Men", 299.90, 10, 5),
            Product(10, "Casual Blazer", "Men", 199.90, 12, 5),
            Product(11, "Sleeveless Vest", "Men", 19.90, 30, 3),
            Product(12, "Swim Trunks", "Men", 29.90, 35, 4),
            Product(13, "Leather Pants", "Men", 199.90, 12, 5),
            Product(14, "Rubber Shorts", "Men", 15.90, 40, 3),
            Product(15, "Analog Shirt", "Men", 89.90, 20, 4),
            Product(16, "Polarized Jacket", "Men", 59.90, 25, 4),
            Product(17, "SPF T-shirt", "Men", 19.90, 30, 4),
            Product(18, "Silk Shirt", "Men", 25.90, 20, 3),
            Product(19, "Leather Jacket", "Women", 129.90, 20, 5),
            Product(20, "Sports Shorts", "Women", 39.90, 60, 4),
            Product(21, "Casual Blouse", "Women", 49.90, 25, 5),
            Product(22, "Pleated Skirt", "Women", 45.00, 35, 4),
            Product(23, "Summer Dress", "Women", 99.90, 18, 5),
            Product(24, "Cropped Top", "Women", 29.90, 25, 4),
            Product(25, "Stretch Leggings", "Women", 39.90, 40, 4),
            Product(26, "Knitted Cardigan", "Women", 89.90, 15, 5),
            Product(27, "Soft Robe", "Women", 59.90, 20, 4),
            Product(28, "One-Piece Swimsuit", "Women", 49.90, 30, 4),
            Product(29, "Triangle Bikini", "Women", 39.90, 25, 4),
            Product(30, "Sport One-Piece", "Women", 59.90, 20, 4),
            Product(31, "Sheer Cover-Up", "Women", 34.90, 30, 4),
            Product(32, "Evening Gown", "Women", 399.90, 5, 5),
            Product(33, "Wedding Dress", "Women", 599.90, 3, 5),
            Product(34, "Japanese Kimono", "Women", 89.90, 15, 4),
            Product(35, "Silk Blouse", "Women", 24.90, 25, 4),
            Product(36, "Leather Skirt", "Women", 29.90, 20, 4),
            Product(37, "Leather Vest", "Women", 79.90, 15, 5),
            Product(38, "Straw Dress", "Women", 24.90, 18, 4),
            Product(39, "Gold Skirt", "Women", 29.90, 20, 4),
            Product(40, "Silver Blouse", "Women", 19.90, 25, 4),
            Product(41, "Velvet Dress", "Women", 22.90, 15, 4),
            Product(42, "Comfy Pants", "Women", 59.90, 20, 4),
            Product(43, "Warm Hoodie", "Kids", 59.90, 40, 4),
            Product(44, "School Backpack", "Kids", 49.90, 45, 4),
            Product(45, "Waterproof Raincoat", "Kids", 49.90, 10, 4),
            Product(46, "Kids Pajamas", "Kids", 39.90, 25, 4),
            Product(47, "Kids Shorts", "Kids", 12.90, 40, 3),
            Product(48, "Beach Shorts", "Kids", 29.90, 25, 4),
            Product(49, "Baseball Cap", "Accessories", 19.90, 100, 4),
            Product(50, "Silk Scarf", "Accessories", 24.90, 80, 4)
        };
        for(int i = 0; i < 50; i++){
            allProducts.append(products[i]);
        }
        return;
    }
    string skipLine;
    for(int i = 0; i < 6; i++){
        getline(file, skipLine);
    }
    int id, stock, rating;
    string name, cat;
    double price;
    while(file >> id){
        file.ignore();
        getline(file, name);
        getline(file, cat);
        file >> price >> stock >> rating;
        allProducts.append(Product(id, name, cat, price, stock, rating));
        string dummy;
        getline(file, dummy);
        if(file.peek() != EOF){
            getline(file, dummy);
            getline(file, dummy);
        }
    }
    file.close();
}
void saveProductsToFile(){
    try{
        ofstream file("data/products.txt");
        if(!file.is_open()){
            throw "Cannot open products.txt for writing!";
        }
        int size = allProducts.getSize();
        file << "    +" << string(70, '-') << "+\n";
        file << "    |" << center("PRODUCT LIST", 68) << "|\n";
        file << "    +" << string(70, '-') << "+\n\n";
        file << "    " << center("Prod ID", 8)
             << center("Name", 25)
             << center("Category", 15)
             << center("Price", 10)
             << center("Stock", 8)
             << center("Rating", 8) << endl;
        file << "    " << string(70, '-') << endl;
        for(int i = 0; i < size; i++){
            Node* node = allProducts.getNode(i);
            if(node){
                file << "    " << center(to_string(node->data.prodID), 8)
                     << center(node->data.prodName, 25)
                     << center(node->data.category, 15)
                     << center(formatPrice(node->data.price), 10)
                     << center(to_string(node->data.stock), 8)
                     << center(to_string(node->data.rating), 8) << endl;
                if(i < size - 1){
                    file << endl;
                }
            }
        }
        file << "    " << string(70, '-') << endl;
        file.close();
    }
    catch (const char* msg){
        cout << "Error: " << msg << endl;
    }
}
void loadOrdersFromFile(){
    ifstream file("data/orders.txt");
    if(!file.is_open()){
        return;
    }
    allOrdersCount = 0;
    allOrdersCapacity = 0;
    if(allOrders != NULL){
        delete[] allOrders;
        allOrders = NULL;
    }
    string skipLine;
    for(int i = 0; i < 4; i++){
        getline(file, skipLine);
    }
    int id, itemCnt;
    string cust, status, date;
    while(file >> id >> cust >> status >> date >> itemCnt){
        Order o(id, cust);
        o.setStatus(status);
        for(int i = 0; i < 7; i++){
            getline(file, skipLine);
        }
        for(int i = 0; i < itemCnt; i++){
            int pid, qty, rated, ratingVal;
            string pname;
            double price, subtotal;
            string comment;
            file >> pid >> pname >> qty >> price >> subtotal >> rated >> ratingVal;
            file.ignore();
            getline(file, comment);
            o.addItem(pid, pname, qty, price);
            OrderItem* items = o.getItems();
            items[i].rated = (rated == 1);
            items[i].ratingValue = ratingVal;
            items[i].comment = comment;
            if(i < itemCnt - 1){
                getline(file, skipLine);
            }
        }
        getline(file, skipLine);
        getline(file, skipLine);
        getline(file, skipLine);
        addToAllOrders(o);
        if(file.peek() != EOF){
            getline(file, skipLine);
            getline(file, skipLine);
            getline(file, skipLine);
        }
    }
    file.close();
}
void saveOrdersToFile(){
    try{
        ofstream file("data/orders.txt");
        if(!file.is_open()){
            throw "Cannot open orders.txt for writing!";
        }
        file << "    +" << string(70, '-') << "+\n";
        file << "    |" << center("ORDERS LIST", 68) << "|\n";
        file << "    +" << string(70, '-') << "+\n\n";
        for(int i = 0; i < allOrdersCount; i++){
            const Order& o = allOrders[i];
            file << "    " << center("Order ID: " + to_string(o.getOrderId()), 70) << endl;
            file << "    " << center("Customer: " + o.getCustomerName(), 70) << endl;
            file << "    " << center("Status: " + o.getStatus(), 70) << endl;
            file << "    " << center("Date: " + o.getOrderDate(), 70) << endl;
            file << "    " << string(70, '-') << endl;
            file << "    " << center("Product ID", 12)
                 << center("Product Name", 20)
                 << center("Quantity", 10)
                 << center("Subtotal", 12) << endl;
            file << "    " << string(70, '-') << endl;
            for(int j = 0; j < o.getItemCount(); j++){
                OrderItem* items = o.getItems();
                file << "    " << center(to_string(items[j].productId), 12)
                     << center(items[j].productName, 20)
                     << center(to_string(items[j].quantity), 10)
                     << center(formatPrice(items[j].subtotal), 12) << endl;
            }
            file << "    " << string(70, '-') << endl;
            file << "    " << center("Total: " + formatPrice(o.getTotal()), 70) << endl;
            if(i < allOrdersCount - 1){
                file << endl;
                file << "    " << string(70, '-') << endl;
                file << endl;
            }
        }
        file.close();
    }
    catch (const char* msg){
        cout << "Error: " << msg << endl;
    }
}
void loadCustomersFromFile(){
    ifstream file("data/customers_accounts.txt");
    if(!file.is_open()){
        customerCount = 1;
        allCustomers[0] = Customer("chelsea", "123456", 1003, "Chelsea Lee", "0198765432");
        return;
    }
    customerCount = 0;
    string user, pass, name, tel;
    int id;
    string skipLine;
    for(int i = 0; i < 6; i++){
        getline(file, skipLine);
    }
    while(file >> user >> pass >> id){
        file.ignore();
        getline(file, name);
        getline(file, tel);
        allCustomers[customerCount++] = Customer(user, pass, id, name, tel);
        string dummy;
        getline(file, dummy);
        if(file.peek() != EOF){
            getline(file, dummy);
            getline(file, dummy);
        }
    }
    file.close();
}
void saveCustomersToFile(){
    try{
        ofstream file("data/customers_accounts.txt");
        if(!file.is_open()){
            throw "Cannot open customers_accounts.txt for writing!";
        }
        file << "    +" << string(70, '-') << "+\n";
        file << "    |" << center("CUSTOMERS LIST", 68) << "|\n";
        file << "    +" << string(70, '-') << "+\n\n";
        file << "    " << center("Username", 15)
             << center("Customer ID", 15)
             << center("Name", 25)
             << center("Phone", 15) << endl;
        file << "    " << string(70, '-') << endl;
        for(int i = 0; i < customerCount; i++){
            file << "    " << center(allCustomers[i].getUsername(), 15)
                 << center(to_string(allCustomers[i].getCustomerId()), 15)
                 << center(allCustomers[i].getName(), 25)
                 << center(allCustomers[i].getPhone(), 15) << endl;
            if(i < customerCount - 1){
                file << endl;
            }
        }
        file << "    " << string(70, '-') << endl;
        file.close();
    }
    catch (const char* msg){
        cout << "Error: " << msg << endl;
    }
}
void loadAdminsFromFile(){
    ifstream file("data/admin_accounts.txt");
    if(!file.is_open()){
        adminCount = 1;
        allAdmins[0] = Admin("chengxi", "123456", "Cheng Xi", "0198765431");
        return;
    }
    adminCount = 0;
    string user, pass, name, tel;
    string skipLine;
    for(int i = 0; i < 6; i++){
        getline(file, skipLine);
    }
    while(file >> user >> pass){
        file.ignore();
        getline(file, name);
        getline(file, tel);
        allAdmins[adminCount++] = Admin(user, pass, name, tel);
        string dummy;
        getline(file, dummy);
        if(file.peek() != EOF){
            getline(file, dummy);
            getline(file, dummy);
        }
    }
    file.close();
}
void saveAdminsToFile(){
    try{
        ofstream file("data/admin_accounts.txt");
        if(!file.is_open()){
            throw "Cannot open admin_accounts.txt for writing!";
        }
        file << "    +" << string(70, '-') << "+\n";
        file << "    |" << center("ADMINS LIST", 68) << "|\n";
        file << "    +" << string(70, '-') << "+\n\n";
        file << "    " << center("Username", 15)
             << center("Name", 30)
             << center("Phone", 15) << endl;
        file << "    " << string(70, '-') << endl;
        for(int i = 0; i < adminCount; i++){
            file << "    " << center(allAdmins[i].getUsername(), 15)
                 << center(allAdmins[i].getName(), 30)
                 << center(allAdmins[i].getPhone(), 15) << endl;
            if(i < adminCount - 1){
                file << endl;
            }
        }
        file << "    " << string(70, '-') << endl;
        file.close();
    }
    catch (const char* msg){
        cout << "Error: " << msg << endl;
    }
}
void registerCustomer(){
    clearScreen();
    printPageTitle("REGISTER FORM");
    string user, pass, confirmPass, name, tel;
    while(true){
        cout << "Username (letters only): ";
        cin >> user;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input.\n" << endl;
            continue;
        }
        clearInput();
        if(!isValidUsername(user)){
            cout << "Username must contain only letters.\n" << endl;
            continue;
        }
        bool exists = false;
        for(int i = 0; i < customerCount; i++){
            if(allCustomers[i].getUsername() == user){
                exists = true;
                break;
            }
        }
        if(exists){
            cout << "Username \"" << user << "\" already exists. Please choose a different username.\n" << endl;
            continue;
        }
        break;
    }
    while(true){
        cout << "Password (minimum 6 characters): ";
        cin >> pass;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input.\n" << endl;
            continue;
        }
        clearInput();
        if(!isValidPassword(pass)){
            cout << "Password must be at least 6 characters.\n" << endl;
            continue;
        }
        break;
    }
    while(true){
        cout << "Confirm Password: ";
        cin >> confirmPass;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input.\n" << endl;
            continue;
        }
        clearInput();
        if(pass == confirmPass){
            break;
        }
        cout << "Passwords do not match. Please try again.\n" << endl;
    }
    while(true){
        cout << "Full Name (letters and spaces only): ";
        getline(cin, name);
        if(!isValidName(name)){
            cout << "Invalid name. Only letters and spaces allowed.\n" << endl;
            continue;
        }
        bool exists = false;
        string lowerName = toLower(name);
        for(int i = 0; i < customerCount; i++){
            if(toLower(allCustomers[i].getName()) == lowerName){
                exists = true;
                break;
            }
        }
        if(exists){
            cout << "Full Name \"" << name << "\" already exists. Please enter a different name.\n" << endl;
            continue;
        }
        break;
    }
    while(true){
        cout << "Phone Number (10 or 11 digits): ";
        getline(cin, tel);
        if(!isValidPhone(tel)){
            cout << "Invalid phone number. Must be exactly 10 or 11 digits.\n" << endl;
            continue;
        }
        bool exists = false;
        for(int i = 0; i < customerCount; i++){
            if(allCustomers[i].getPhone() == tel){
                exists = true;
                break;
            }
        }
        if(!exists){
            for(int i = 0; i < adminCount; i++){
                if(allAdmins[i].getPhone() == tel){
                    exists = true;
                    break;
                }
            }
        }
        if(exists){
            cout << "Phone number \"" << tel << "\" already registered by another user. Please enter a different phone number.\n" << endl;
            continue;
        }
        break;
    }
    int newId = 2001 + customerCount;
    allCustomers[customerCount++] = Customer(user, pass, newId, name, tel);
    saveCustomersToFile();
    cout << "\nRegister successfully! Welcome " << user << "!" << endl;
    cout << "Please login to continue." << endl;
    waitForKey();
}
void registerAdmin(){
    clearScreen();
    printPageTitle("ADMIN REGISTER FORM");
    string user, pass, confirmPass, name, tel;
    while(true){
        cout << "Username (letters only): ";
        cin >> user;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input.\n" << endl;
            continue;
        }
        clearInput();
        if(!isValidUsername(user)){
            cout << "Username must contain only letters.\n" << endl;
            continue;
        }
        bool exists = false;
        for(int i = 0; i < adminCount; i++){
            if(allAdmins[i].getUsername() == user){
                exists = true;
                break;
            }
        }
        if(exists){
            cout << "Admin username \"" << user << "\" already exists. Please choose a different username.\n" << endl;
            continue;
        }
        break;
    }
    while(true){
        cout << "Password (minimum 6 characters): ";
        cin >> pass;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input.\n" << endl;
            continue;
        }
        clearInput();
        if(!isValidPassword(pass)){
            cout << "Password must be at least 6 characters.\n" << endl;
            continue;
        }
        break;
    }
    while(true){
        cout << "Confirm Password: ";
        cin >> confirmPass;
        if(cin.fail()){
            clearInput();
            cout << "Invalid input.\n" << endl;
            continue;
        }
        clearInput();
        if(pass == confirmPass){
            break;
        }
        cout << "Passwords do not match. Please try again.\n" << endl;
    }
    while(true){
        cout << "Full Name (letters and spaces only): ";
        getline(cin, name);
        if(!isValidName(name)){
            cout << "Invalid name. Only letters and spaces allowed.\n" << endl;
            continue;
        }
        bool exists = false;
        string lowerName = toLower(name);
        for(int i = 0; i < adminCount; i++){
            if(toLower(allAdmins[i].getName()) == lowerName){
                exists = true;
                break;
            }
        }
        if(exists){
            cout << "Full Name \"" << name << "\" already exists. Please enter a different name.\n" << endl;
            continue;
        }
        break;
    }
    while(true){
        cout << "Phone Number (10 or 11 digits): ";
        getline(cin, tel);
        if(!isValidPhone(tel)){
            cout << "Invalid phone number. Must be exactly 10 or 11 digits.\n" << endl;
            continue;
        }
        bool exists = false;
        for(int i = 0; i < adminCount; i++){
            if(allAdmins[i].getPhone() == tel){
                exists = true;
                break;
            }
        }
        if(!exists){
            for(int i = 0; i < customerCount; i++){
                if(allCustomers[i].getPhone() == tel){
                    exists = true;
                    break;
                }
            }
        }
        if(exists){
            cout << "Phone number \"" << tel << "\" already registered by another user. Please enter a different phone number.\n" << endl;
            continue;
        }
        break;
    }
    allAdmins[adminCount++] = Admin(user, pass, name, tel);
    saveAdminsToFile();
    cout << "\nRegister successfully! Welcome " << user << "!" << endl;
    cout << "Please login to continue." << endl;
    waitForKey();
}
int main(){
    createDataFolder();
    srand(time(0));
    loadProductsFromFile();
    loadCustomersFromFile();
    loadAdminsFromFile();
    loadOrdersFromFile();
    for(int i = 0; i < allOrdersCount; i++){
        for(int c = 0; c < customerCount; c++){
            if(allCustomers[c].getUsername() == allOrders[i].getCustomerName()){
                allCustomers[c].addOrderWithoutGlobal(allOrders[i]);
                break;
            }
        }
    }
    int maxOrderId = 0;
    for(int i = 0; i < allOrdersCount; i++){
        if(allOrders[i].getOrderId() > maxOrderId){
            maxOrderId = allOrders[i].getOrderId();
        }
    }
    if(maxOrderId >= nextOrderId){
        nextOrderId = maxOrderId + 1;
    }
    int choice;
    string user, pass;
    bool exitProg = false;
    while(!exitProg){
        clearScreen();
        printStoreBanner();
        cout << "1. Customer Login" << endl;
        cout << "2. Admin Login" << endl;
        cout << "3. Register as Customer" << endl;
        cout << "4. Register as Admin" << endl;
        cout << "5. Exit" << endl;
        cout << DOUBLE_LINE << endl;
        choice = getIntInput("Choice: ", 1, 5);
        if(choice == 1){
            bool loginSuccess = false;
            while(!loginSuccess){
                clearScreen();
                printPageTitle("CUSTOMER LOGIN");
                cout << "Username: ";
                cin >> user;
                if(cin.fail()){
                    clearInput();
                    cout << "Invalid input.\n" << endl;
                    waitForKey();
                    continue;
                }
                clearInput();
                if(!isValidUsername(user)){
                    cout << "Invalid username format.\n" << endl;
                    waitForKey();
                    continue;
                }
                cout << "Password: ";
                cin >> pass;
                if(cin.fail()){
                    clearInput();
                    cout << "Invalid input.\n" << endl;
                    waitForKey();
                    continue;
                }
                clearInput();
                bool userExists = false;
                for(int i = 0; i < customerCount; i++){
                    if(allCustomers[i].getUsername() == user){
                        userExists = true;
                        break;
                    }
                }
                if(!userExists){
                    cout << "\nUser not found. Please register first." << endl;
                    waitForKey();
                    break;
                }
                for(int i = 0; i < customerCount; i++){
                    if(allCustomers[i].login(user, pass)){
                        Customer* logged = &allCustomers[i];
                        cout << "\nLogin successful! Welcome " << user << "!" << endl;
                        waitForKey();
                        int sub;
                        bool logout = false;
                        while(!logout){
                            clearScreen();
                            logged->displayMenu();
                            sub = getIntInput("Choice: ", 1, 9);
                            switch (sub){
                                case 1: clearScreen(); logged->viewProducts(); break;
                                case 2: clearScreen(); logged->searchProduct(); break;
                                case 3: clearScreen(); logged->sortProducts(); break;
                                case 4: clearScreen(); logged->addToCart(); break;
                                case 5: clearScreen(); logged->viewCart(); break;
                                case 6: clearScreen(); logged->viewOrders(); waitForKey(); break;
                                case 7: clearScreen(); logged->rateProducts(); break;
                                case 8: clearScreen(); logged->generatePersonalReport(); break;
                                case 9: logged->logout(); logout = true; break;
                                default: cout << "Invalid choice.\n"; waitForKey();
                            }
                        }
                        loginSuccess = true;
                        break;
                    }
                }
                if(!loginSuccess){
                    cout << "\nIncorrect password, please try again.\n" << endl;
                    waitForKey();
                }
            }
        }
        else if(choice == 2){
            bool loginSuccess = false;
            while(!loginSuccess){
                clearScreen();
                printPageTitle("ADMIN LOGIN");
                cout << "Username: ";
                cin >> user;
                if(cin.fail()){
                    clearInput();
                    cout << "Invalid input.\n" << endl;
                    waitForKey();
                    continue;
                }
                clearInput();
                if(!isValidUsername(user)){
                    cout << "Invalid username format.\n" << endl;
                    waitForKey();
                    continue;
                }
                cout << "Password: ";
                cin >> pass;
                if(cin.fail()){
                    clearInput();
                    cout << "Invalid input.\n" << endl;
                    waitForKey();
                    continue;
                }
                clearInput();
                bool userExists = false;
                for(int i = 0; i < adminCount; i++){
                    if(allAdmins[i].getUsername() == user){
                        userExists = true;
                        break;
                    }
                }
                if(!userExists){
                    cout << "\nAdmin user not found. Please register first.\n" << endl;
                    waitForKey();
                    break;
                }
                for(int i = 0; i < adminCount; i++){
                    if(allAdmins[i].login(user, pass)){
                        Admin* logged = &allAdmins[i];
                        cout << "\nLogin successful! Welcome " << user << "!" << endl;
                        waitForKey();
                        int sub;
                        bool logout = false;
                        while(!logout){
                            clearScreen();
                            logged->displayMenu();
                            sub = getIntInput("Choice: ", 1, 12);
                            switch (sub){
                                case 1: clearScreen(); logged->addProduct(); break;
                                case 2: clearScreen(); logged->editProduct(); break;
                                case 3: clearScreen(); logged->deleteProduct(); break;
                                case 4: clearScreen(); logged->viewProducts(); break;
                                case 5: clearScreen(); logged->searchProduct(); break;
                                case 6: clearScreen(); logged->sortProducts(); break;
                                case 7: clearScreen(); logged->viewAllOrders(); break;
                                case 8: clearScreen(); logged->updateOrderStatus(); break;
                                case 9: clearScreen(); logged->generateSalesReport(); break;
                                case 10: clearScreen(); logged->viewFeedback(); break;
                                case 11: clearScreen(); logged->searchProductById(); break;
                                case 12: logged->logout(); logout = true; break;
                                default: cout << "Invalid choice.\n"; waitForKey();
                            }
                        }
                        loginSuccess = true;
                        break;
                    }
                }
                if(!loginSuccess){
                    cout << "\nIncorrect password, please try again.\n" << endl;
                    waitForKey();
                }
            }
        }
        else if(choice == 3){
            registerCustomer();
        }
        else if(choice == 4){
            registerAdmin();
        }
        else if(choice == 5){
            exitProg = true;
            clearScreen();
            cout << "\n  +" << string(70, '-') << "+\n"
                 << "  |" << center("THANK YOU FOR VISITING OUR SHOP! HAVE A NICE DAY", 68) << "|\n"
                 << "  +" << string(70, '-') << "+\n";
            cout << "\nThank you for using our online clothing store!\n";
            waitForKey();
        }
        else{
            cout << "Invalid option.\n";
            waitForKey();
        }
    }
    saveProductsToFile();
    saveCustomersToFile();
    saveAdminsToFile();
    saveOrdersToFile();
    return 0;
}
void Customer::cartPushBack(const CartItem& item){
    if(cartCount >= cartCapacity){
        cartCapacity *= 2;
        CartItem* newCart = new CartItem[cartCapacity];
        for(int i = 0; i < cartCount; i++){
            newCart[i] = cart[i];
        }
        delete[] cart;
        cart = newCart;
    }
    cart[cartCount++] = item;
}
void Customer::cartRemoveAt(int index){
    if(index < 0 || index >= cartCount){
        return;
    }
    for(int i = index; i < cartCount - 1; i++){
        cart[i] = cart[i + 1];
    }
    cartCount--;
}
int Customer::cartFind(int productId){
    for(int i = 0; i < cartCount; i++){
        if(cart[i].productId == productId){
            return i;
        }
    }
    return -1;
}
CartItem* Customer::getCartItem(int index){
    if(index < 0 || index >= cartCount){
        return NULL;
    }
    return &cart[index];
}
void Customer::clearCart(){
    cartCount = 0;
}
void Customer::addOrder(const Order& newOrder){
    Order* newHistory = new Order[orderCount + 1];
    for(int i = 0; i < orderCount; i++){
        newHistory[i] = orderHistory[i];
    }
    newHistory[orderCount] = newOrder;
    if(orderHistory != NULL){
        delete[] orderHistory;
    }
    orderHistory = newHistory;
    orderCount++;
    addToAllOrders(newOrder);
}
void Customer::addOrderWithoutGlobal(const Order& newOrder){
    Order* newHistory = new Order[orderCount + 1];
    for(int i = 0; i < orderCount; i++){
        newHistory[i] = orderHistory[i];
    }
    newHistory[orderCount] = newOrder;
    if(orderHistory != NULL){
        delete[] orderHistory;
    }
    orderHistory = newHistory;
    orderCount++;
}
void Customer::viewOrders() const{
    printPageTitle("Order History for " + username);
    if(orderCount == 0){
        cout << "No orders placed yet." << endl;
        return;
    }
    cout << "  " << center("Order ID", 10)
         << center("Customer", 14)
         << center("Item", 19)
         << center("Qty", 8)
         << center("Total", 10)
         << center("Status", 9) << endl;
    cout << "  " << string(70, '-') << endl;
    for(int i = 0; i < orderCount; i++){
        const Order& ord = orderHistory[i];
        int numItems = ord.getItemCount();
        for(int j = 0; j < numItems; j++){
            OrderItem* items = ord.getItems();
            if(j == 0){
                cout << "  " << center(to_string(ord.getOrderId()), 10)
                     << center(ord.getCustomerName(), 14)
                     << center(items[j].productName, 19)
                     << center(to_string(items[j].quantity), 8)
                     << center(formatPrice(items[j].subtotal), 10)
                     << center(ord.getStatus(), 9) << endl;
            }
            else{
                cout << "  " << center("", 10)
                     << center("", 14)
                     << center(items[j].productName, 19)
                     << center(to_string(items[j].quantity), 8)
                     << center(formatPrice(items[j].subtotal), 10)
                     << center("", 9) << endl;
            }
        }
        cout << "  " << string(70, '-') << endl;
    }
}
void Customer::addToCart(bool showList, bool showTitle, bool isRoot){
    if(showTitle){
        printPageTitle("ADD TO CART");
    }
    if(showList){
        cout << "Current product list: \n\n";
        allProducts.displaySortedById();
    }
    int pid = 0;
    Product product;
    bool productFound = false;
    while(!productFound){
        pid = getIntInput("\nEnter product ID to add to cart: ", 1, 9999);
        Node* temp = allProducts.getNode(0);
        bool found = false;
        while(temp != NULL){
            if(temp->data.prodID == pid){
                product = temp->data;
                found = true;
                break;
            }
            temp = temp->next;
        }
        if(!found){
            cout << "Product ID " << pid << " not found. Please try again.\n" << endl;
        }
        else{
            productFound = true;
        }
    }
    if(product.stock <= 0){
        cout << "Sorry, product out of stock." << endl;
        if(isRoot){
            waitForKey();
        }
        return;
    }
    int qty;
    while(true){
        qty = getPositiveInt("Enter quantity: ");
        if(qty > product.stock){
            cout << "Insufficient stock. Only " << product.stock << " left. Please enter a smaller quantity.\n" << endl;
        }
        else{
            break;
        }
    }
    string size;
    bool validSize = false;
    while(!validSize){
        cout << "Select size (XS / S / M / L / XL): ";
        cin >> size;
        for(char& c : size){
            c = toupper(c);
        }
        if(size == "XS" || size == "S" || size == "M" || size == "L" || size == "XL"){
            validSize = true;
        }
        else{
            cout << "Invalid size, please enter the size ranging from XS to XL.\n\n";
        }
    }
    bool updated = false;
    for(int i = 0; i < cartCount; i++){
        if(cart[i].productId == pid && cart[i].size == size){
            cart[i].quantity += qty;
            updated = true;
            break;
        }
    }
    if(!updated){
        CartItem newItem;
        newItem.productId = pid;
        newItem.productName = product.prodName;
        newItem.size = size;
        newItem.quantity = qty;
        newItem.price = product.price;
        cartPushBack(newItem);
    }
    cout << product.prodName << " (Size: " << size << ") added to cart.\n";
    if(getYesNo("Add another product? (y/n): ")){
        addToCart(false, false, false);
    }
    if(isRoot){
        waitForKey();
    }
}
void Customer::viewCart(){
    while(true){
        if(cartCount == 0){
            printPageTitle("YOUR CART");
            cout << "Your cart is currently empty." << endl;
            waitForKey();
            return;
        }
        printPageTitle("YOUR CART");
        cout << "  " << center("ID", 10)
             << center("Name", 20)
             << center("Size", 8)
             << center("Qty", 10)
             << center("Price", 12)
             << center("Subtotal", 12) << endl;
        cout << "  " << string(70, '-') << endl;
        double total = 0;
        for(int i = 0; i < cartCount; i++){
            double subtotal = cart[i].quantity * cart[i].price;
            total += subtotal;
            cout << "  " << center(to_string(cart[i].productId), 10)
                 << center(cart[i].productName, 20)
                 << center(cart[i].size, 8)
                 << center(to_string(cart[i].quantity), 10)
                 << center(formatPrice(cart[i].price), 12)
                 << center(formatPrice(subtotal), 12) << endl;
        }
        cout << "  " << string(70, '-') << endl;
        cout << "\nTotal: RM" << fixed << setprecision(2) << total << endl;
        cout << "\nOptions:" << endl;
        cout << "1. Modify order details" << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Checkout" << endl;
        cout << "4. Back to menu" << endl;
        int opt = getIntInput("Choice: ", 1, 4);
        if(opt == 1){
            clearScreen();
            printPageTitle("MODIFY ORDER DETAILS");
            cout << "  " << center("ID", 10)
                 << center("Name", 20)
                 << center("Size", 8)
                 << center("Qty", 10)
                 << center("Price", 12)
                 << center("Subtotal", 12) << endl;
            cout << "  " << string(70, '-') << endl;
            for(int i = 0; i < cartCount; i++){
                double subtotal = cart[i].quantity * cart[i].price;
                cout << "  " << center(to_string(cart[i].productId), 10)
                     << center(cart[i].productName, 20)
                     << center(cart[i].size, 8)
                     << center(to_string(cart[i].quantity), 10)
                     << center(formatPrice(cart[i].price), 12)
                     << center(formatPrice(subtotal), 12) << endl;
            }
            cout << "  " << string(70, '-') << endl;
            bool validPid = false;
            while(!validPid){
                int pid = getIntInput("\nEnter product ID to modify: ", 1, 9999);
                int idx = cartFind(pid);
                if(idx != -1){
                    validPid = true;
                    cout << "Enter new quantity (press Enter to keep current: " << cart[idx].quantity << "): ";
                    int newQty = getPositiveIntWithSkip("");
                    if(newQty == -1){
                        cout << "Quantity kept as " << cart[idx].quantity << endl;
                    }
                    else{
                        if(newQty != cart[idx].quantity){
                            Node* temp = allProducts.getNode(0);
                            int stock = 0;
                            while(temp != NULL){
                                if(temp->data.prodID == pid){
                                    stock = temp->data.stock;
                                    break;
                                }
                                temp = temp->next;
                            }
                            if(newQty > stock){
                                cout << "Insufficient stock. Only " << stock << " left. Quantity not changed.\n";
                            }
                            else{
                                cart[idx].quantity = newQty;
                                cout << "Quantity updated to " << newQty << ".\n";
                            }
                        }
                        else{
                            cout << "Quantity kept as " << cart[idx].quantity << " (no change).\n";
                        }
                    }
                    string newSize;
                    while(true){
                        cout << "Enter new size (press Enter to keep current: " << cart[idx].size << "): ";
                        getline(cin, newSize);
                        if(newSize.empty()){
                            cout << "Size kept as " << cart[idx].size << ".\n\n";
                            break;
                        }
                        for(char& c : newSize){
                            c = toupper(c);
                        }
                        if(newSize == "XS" || newSize == "S" || newSize == "M" || newSize == "L" || newSize == "XL"){
                            cart[idx].size = newSize;
                            cout << "Size updated to " << newSize << ".\n\n";
                            break;
                        }
                        else{
                            cout << "Invalid size. Please enter size ranging from XS to XL.\n" << endl;
                        }
                    }
                    if(newQty == -1 && newSize.empty()){
                        cout << "No changes made.\n";
                    }
                }
                else{
                    cout << "Product ID not found in cart.\n" << endl;
                }
            }
        }
        else if(opt == 2){
            clearScreen();
            printPageTitle("REMOVE ITEM");
            cout << "  " << center("ID", 10)
                 << center("Name", 20)
                 << center("Size", 8)
                 << center("Qty", 10)
                 << center("Price", 12)
                 << center("Subtotal", 12) << endl;
            cout << "  " << string(70, '-') << endl;
            for(int i = 0; i < cartCount; i++){
                double subtotal = cart[i].quantity * cart[i].price;
                cout << "  " << center(to_string(cart[i].productId), 10)
                     << center(cart[i].productName, 20)
                     << center(cart[i].size, 8)
                     << center(to_string(cart[i].quantity), 10)
                     << center(formatPrice(cart[i].price), 12)
                     << center(formatPrice(subtotal), 12) << endl;
            }
            cout << "  " << string(70, '-') << endl;
            int pid = getIntInput("Enter product ID to remove: ", 1, 9999);
            int idx = cartFind(pid);
            if(idx != -1){
                cartRemoveAt(idx);
                cout << "Successfully removed item.\n\n";
            }
            else{
                cout << "Product ID not found in cart." << endl;
            }
        }
        else if(opt == 3){
            checkout();
            return;
        }
        else if(opt == 4){
            return;
        }
    }
}
void Customer::checkout(){
    clearScreen();
    if(cartCount == 0){
        cout << "\nCart is empty. Add items first." << endl;
        waitForKey();
        return;
    }
    bool stockOk = true;
    for(int i = 0; i < cartCount; i++){
        Node* temp = allProducts.getNode(0);
        int available = 0;
        while(temp != NULL){
            if(temp->data.prodID == cart[i].productId){
                available = temp->data.stock;
                break;
            }
            temp = temp->next;
        }
        if(cart[i].quantity > available){
            cout << "Sorry, product " << cart[i].productName << " (size " << cart[i].size << ") only has " << available << " left. Order cancelled." << endl;
            stockOk = false;
            break;
        }
    }
    if(!stockOk){
        waitForKey();
        return;
    }
    int orderId = nextOrderId++;
    Order newOrder(orderId, username);
    for(int i = 0; i < cartCount; i++){
        newOrder.addItem(cart[i].productId, cart[i].productName + " (" + cart[i].size + ")", cart[i].quantity, cart[i].price);
        Node* temp = allProducts.getNode(0);
        while(temp != NULL){
            if(temp->data.prodID == cart[i].productId){
                temp->data.stock -= cart[i].quantity;
                break;
            }
            temp = temp->next;
        }
    }
    saveProductsToFile();
    printPageTitle("ORDER SUMMARY");
    newOrder.displaySummary();
    if(!getYesNo("\nConfirm order? (y/n): ")){
        for(int i = 0; i < cartCount; i++){
            Node* temp = allProducts.getNode(0);
            while(temp != NULL){
                if(temp->data.prodID == cart[i].productId){
                    temp->data.stock += cart[i].quantity;
                    break;
                }
                temp = temp->next;
            }
        }
        saveProductsToFile();
        cout << "Order cancelled. Cart restored." << endl;
        waitForKey();
        return;
    }
    if(!processPayment(newOrder.getTotal(), newOrder)){
        for(int i = 0; i < cartCount; i++){
            Node* temp = allProducts.getNode(0);
            while(temp != NULL){
                if(temp->data.prodID == cart[i].productId){
                    temp->data.stock += cart[i].quantity;
                    break;
                }
                temp = temp->next;
            }
        }
        saveProductsToFile();
        cout << "Payment failed. Order cancelled." << endl;
        waitForKey();
        return;
    }
    newOrder.setStatus("paid");
    addOrder(newOrder);
    clearCart();
    cout << "Order placed successfully! Order ID: " << orderId << endl;
    string fname = "data/receipts/receipt_" + to_string(orderId) + ".txt";
    ofstream receipt(fname.c_str());
    receipt << "\n  ==========================================\n";
    receipt << "       PAYMENT RECEIPT\n";
    receipt << "  ==========================================\n\n";
    receipt << "Order ID: " << orderId << "\n";
    receipt << "Customer: " << username << "\n";
    receipt << "Date: " << __DATE__ << " " << __TIME__ << "\n";
    receipt << "\nItems:\n";
    for(int i = 0; i < newOrder.getItemCount(); i++){
        OrderItem* items = newOrder.getItems();
        receipt << "  " << items[i].quantity << " x " << items[i].productName
                << " = RM" << fixed << setprecision(2) << items[i].subtotal << "\n";
    }
    receipt << "\nTotal Amount: RM" << fixed << setprecision(2) << newOrder.getTotal() << "\n";
    receipt << "Status: PAID\n";
    receipt << "  ==========================================\n";
    receipt.close();
    clearScreen();
    printReceiptBox(fname);
    cout << endl;
    cout << "(Receipt saved to " << fname << ")" << endl;
    waitForKey();
}
void Customer::rateProducts(){
    bool hasPaidOrder = false;
    for(int i = 0; i < orderCount; i++){
        if(orderHistory[i].getStatus() == "paid" || orderHistory[i].getStatus() == "completed"){
            hasPaidOrder = true;
            break;
        }
    }
    if(!hasPaidOrder){
        printPageTitle("UNRATED PRODUCTS");
        cout << "Please proceed to payment first before rating." << endl;
        waitForKey();
        return;
    }
    int unratedCount = 0;
    int unratedIds[100];
    int unratedOrderIds[100];
    int unratedItemIndex[100];
    for(int i = 0; i < orderCount; i++){
        if(orderHistory[i].getStatus() == "paid" || orderHistory[i].getStatus() == "completed"){
            for(int j = 0; j < orderHistory[i].getItemCount(); j++){
                OrderItem* items = orderHistory[i].getItems();
                if(!items[j].rated){
                    unratedOrderIds[unratedCount] = orderHistory[i].getOrderId();
                    unratedItemIndex[unratedCount] = j;
                    unratedCount++;
                }
            }
        }
    }
    if(unratedCount == 0){
        printPageTitle("UNRATED PRODUCTS");
        cout << "\nNo unrated products found." << endl;
        waitForKey();
        return;
    }
    printPageTitle("UNRATED PRODUCTS");
    cout << "  " << center("Product ID", 12)
         << center("Product Name", 25)
         << center("Quantity", 10)
         << center("Subtotal", 12) << endl;
    cout << "  " << string(70, '-') << endl;
    for(int k = 0; k < unratedCount; k++){
        int oid = unratedOrderIds[k];
        int idx = unratedItemIndex[k];
        for(int i = 0; i < orderCount; i++){
            if(orderHistory[i].getOrderId() == oid){
                OrderItem* items = orderHistory[i].getItems();
                cout << "  " << center(to_string(items[idx].productId), 12)
                     << center(items[idx].productName, 25)
                     << center(to_string(items[idx].quantity), 10)
                     << center(formatPrice(items[idx].subtotal), 12) << endl;
                break;
            }
        }
    }
    int pid;
    bool validPid = false;
    int targetOrderId = -1;
    int targetIdx = -1;
    while(!validPid){
        pid = getIntInput("\nEnter Product ID to rate: ", 1, 9999);
        for(int k = 0; k < unratedCount; k++){
            int oid = unratedOrderIds[k];
            int idx = unratedItemIndex[k];
            for(int i = 0; i < orderCount; i++){
                if(orderHistory[i].getOrderId() == oid){
                    OrderItem* items = orderHistory[i].getItems();
                    if(items[idx].productId == pid){
                        targetOrderId = oid;
                        targetIdx = idx;
                        validPid = true;
                        break;
                    }
                }
            }
            if(validPid){
                break;
            }
        }
        if(!validPid){
            cout << "Product ID not found in unrated list. Please try again.\n";
        }
    }
    int rating = getIntInput("Enter rating (1 = worst, 5 = best): ", 1, 5);
    string comment;
    cout << "Enter comment (optional, press Enter to skip): ";
    getline(cin, comment);
    for(int i = 0; i < orderCount; i++){
        if(orderHistory[i].getOrderId() == targetOrderId){
            OrderItem* items = orderHistory[i].getItems();
            items[targetIdx].rated = true;
            items[targetIdx].ratingValue = rating;
            items[targetIdx].comment = comment;
            break;
        }
    }
    for(int i = 0; i < allOrdersCount; i++){
        if(allOrders[i].getOrderId() == targetOrderId){
            OrderItem* items = allOrders[i].getItems();
            for(int j = 0; j < allOrders[i].getItemCount(); j++){
                if(items[j].productId == pid){
                    items[j].rated = true;
                    items[j].ratingValue = rating;
                    items[j].comment = comment;
                    break;
                }
            }
            break;
        }
    }
    saveOrdersToFile();
    cout << "Thank you for your feedback! We appreciate it!" << endl;
    waitForKey();
}
void Customer::displayMenu(){
    printPageTitle("CUSTOMER MENU");
    cout << "1. View All Products" << endl;
    cout << "2. Search Products by Name" << endl;
    cout << "3. Sort Products" << endl;
    cout << "4. Add to Cart" << endl;
    cout << "5. View My Cart & Payment" << endl;
    cout << "6. View Order History" << endl;
    cout << "7. Rate Products" << endl;
    cout << "8. View Personal Report" << endl;
    cout << "9. Logout" << endl;
    cout << LINE << endl;
}