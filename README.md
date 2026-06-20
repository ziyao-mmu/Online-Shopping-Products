CLOTHING STORE ONLINE SHOPPING SYSTEM

# How to Run the Program
1. Open Dev-C++ or any C++ compiler.
2. Open the file named `Project_GR2.cpp`.
3. Click **Compile & Run**.
4. The program will start and show the main menu.

The program will automatically create a folder called 'data' in the same directory. This folder stores all files such as products, orders, customer accounts, admin accounts, receipts, sales reports, and personal reports.

------------------------------------------------------------------------------------------------------------------------------------------

# How to Login
Use existing account to login
The system consists of 2 accounts for testing purposes.
1. Customer Login
- Username: chelsea
- Password: 123456

2. Admin Login
- Username: chengxi
- Password: 123456

Register a new account
- Select **Option 3 (Register as Customer)** or **Option 4 (Register as Admin)**

------------------------------------------------------------------------------------------------------------------------------------------

# System Overview
This is an **online clothing store system** built in C++.

The system has **2** main modules:
1. Customer Module
For regular users to shop, manage orders, and provide feedback

2. Admin Module
For staff to manage products, orders, and generate reports

------------------------------------------------------------------------------------------------------------------------------------------

# Main Features
## Customer Features (9 options)
Option 1: View All Products
- Display a complete list of all available products in the store.
- Show Product ID, Name, Category, Price, Stock, and Rating.
- Product are sorted by Product ID by default.

Option 2: Search Products by Name
- Search for products by name using **partial keyword matching** 
e.g., searching "shirt" will show all products containing "shirt" in the name
- The system will display all matching products.

Option 3: Sort Products
- Sort products by: Price, Rating, Category, Product ID, Stock.
- Use **Quick Sort** algorithm

Option 4: Add to Cart
- Add products to the shopping cart.
- Select a product ID, quantity, and size (XS/S/M/L/XL).
- The product will be added to the cart.
- Choose "y" to add another product, or "n" to return.

Option 5: View My Cart & Payment
- Displays all items currently in shopping cart.
- Shows ID, Name, Size, Quantity, Price, and Subtotal for each item.
- Customer can also:
  - **Modify order details** (change quantity or size)
  - **Remove item** from cart
  - **Checkout** and proceed to payment
    1. From the cart, select **3. Checkout**.
    2. The system will check stock availability.
    3. View the order summary.
    4. Confirm the order (y/n).
    5. Choose a payment method:
    - **1. Credit Card** – enter card number, expiry date, and CVV
    - **2. Bank Transfer** – follow the transfer instructions
    - **3. TNG eWallet** – scan the QR code displayed
    6. After successful payment, a receipt will be generated and displayed.
    7. The receipt is saved in the `data/receipts/` folder.

  - **Back to menu** return back to main page

Option 6: View Order History
- Displays all past orders placed by the customer.
- Shows Order ID, Customer, Item, Quantity, Total, and Status.

Option 7: Rate Products
- Allows customers to rate products they have purchased (paid orders only).
- Customers can provide a rating from 1 (worst) to 5 (best) and an optional comment.

Option 8: View Personal Report
- Generates a personal spending report for the customer.
- Shows total orders, each order with amount, total spent, and status.
- The report is saved as a `.txt` file in the `data/reports/` folder.

Option 9: Logout
- Logs out the current customer and returns to the main menu.

------------------------------------------------------------------------------------------------------------------------------------------

## Admin Features (12 options)
Option 1: Add New Product
- Allows the admin to add a new product to the store.
- The Product ID is auto-generated.
- Fill in the details like product's name, category, price, stock, rating
- The product will be added and saved to `data/products.txt`.

Option 2: Edit Product
- Allows the admin to edit an existing product's details.
- The admin can leave fields blank to keep the current value.
- The product will be updated and saved to `data/products.txt`.

Option 3: Delete Product
- Allows the admin to delete a product from the store.
- A confirmation prompt is shown before deletion.

Option 4: View All Products
- Displays a complete list of all available products in the store.
- Same as the customer's view all products feature.

Option 5: Search Products by Name
- Searches for products by name using partial keyword matching.
- Same as the customer's search feature.

Option 6: Sort Products
- Sorts products by one of five criteria using Quick Sort.
- Same as the customer's sort feature.

Option 7: View All Orders
- Displays all orders placed by all customers.
- Shows Order ID, Customer, Item, Quantity, Total, and Status.

Option 8: Update Order Status
- Allows the admin to update the status of an existing order.
- Status options: **shipped** or **completed**.
- The order status will be updated and saved to `data/orders.txt`.

Option 9: Generate Sales Report
- Generates a monthly sales report for a selected month.
- Shows all orders placed in that month with details and total revenue.

Option 10: View Customer Ratings & Feedback
- Displays all ratings and comments provided by customers.
- Shows Customer name, Product name, Rating, and Comment

Option 11: Search Product by ID
- Searches for a product by its ID using **Binary Search**

Option 12: Logout
- Logs out the current admin and returns to the main menu.

------------------------------------------------------------------------------------------------------------------------------------------

## 5. File Storage
All data is stored in the **`data`** folder, which is automatically created when the program runs:
`data/products.txt`: Stores all product records (ID, name, category, price, stock, rating) 
`data/orders.txt`: Stores all customer orders (order ID, customer, items, status, date) |
`data/customers_accounts.txt`: Stores customer accounts (username, password, ID, name, phone) 
`data/admin_accounts.txt`: Stores admin accounts (username, password, name, phone) 
`data/receipts/`: Stores payment receipts for each order 
`data/sales/`: Stores monthly sales reports generated by admin
`data/reports/`: Stores personal reports generated by customer

------------------------------------------------------------------------------------------------------------------------------------------

## 6. Algorithms Used
**Linked Queue (ADTqueue)**: Stores and manages product data in memory using a linked list-based queue | `class ADTqueue`
**Quick Sort**: Sorts products by price, rating, category, ID, or stock | `ADTqueue::quickSort()` |
**Binary Search**: Searches for a product by its ID (used by admin) | `ADTqueue::binarySearchById()` |
**Linear Search**: Searches for products by name using partial keyword matching | `ADTqueue::searchByName()` |

------------------------------------------------------------------------------------------------------------------------------------------

## 7. Notes
- The program automatically creates the `data` folder if it does not exist.
- All input fields have validation (e.g., username must contain only letters, password must be at least 6 characters).
- Product names must be unique.
- Payment methods supported: Credit Card, Bank Transfer, and TNG eWallet.
- Receipts are automatically saved as `.txt` files in the `data/receipts/` folder.