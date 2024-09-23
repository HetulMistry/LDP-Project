#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#define CATEGORY_COUNT 3

using namespace std;

struct MenuItem
{
  string name;
  string description;
  double price;
  int stock;
};

void displayMenu(const vector<MenuItem> &menu);
void displayMenuByCategory(const vector<MenuItem> &menu, const vector<int> &itemCategories, const vector<string> &categories);
void addToOrder(vector<int> &order, const vector<MenuItem> &menu, int itemIndex, int quantity);
void modifyOrder(vector<int> &order, int itemIndex, int quantity, const vector<MenuItem> &menu);
void showOrderSummary(const vector<MenuItem> &menu, const vector<int> &order);
void saveOrderToHistory(const vector<MenuItem> &menu, const vector<int> &order);
void loadOrderHistory();
void clearOrderHistory();
void restockInventory(vector<MenuItem> &menu);
void loadSpecificOrder(vector<int> &order, vector<MenuItem> &menu);

void displayMenu(const vector<MenuItem> &menu)
{
  cout << "\n--- Hotel Menu ---" << endl;

  for (size_t i = 0; i < menu.size(); ++i)
  {
    cout << i + 1 << ". " << menu[i].name << " - " << menu[i].description
         << " ($" << menu[i].price << ") [Stock: " << menu[i].stock << "]" << endl;
  }

  cin.get();
  cin.get();
}

void displayMenuByCategory(const vector<MenuItem> &menu, const vector<int> &itemCategories, const vector<string> &categories)
{
  cout << "\n--- Hotel Menu by Categories ---" << endl;

  for (int i = 0; i < CATEGORY_COUNT; ++i)
  {
    cout << endl
         << categories[i] << ":\n";

    for (size_t j = 0; j < menu.size(); ++j)
    {
      if (itemCategories[j] == i)
      {
        cout << j + 1 << ". " << menu[j].name << " - " << menu[j].description
             << "($" << menu[j].price << ") [Stock: " << menu[j].stock << "]" << endl;
      }
    }
  }

  cin.get();
  cin.get();
}

void addToOrder(vector<int> &order, const vector<MenuItem> &menu, int itemIndex, int quantity)
{
  if (menu[itemIndex].stock >= quantity)
  {
    order[itemIndex] += quantity;
    cout << "Added " << quantity << "x " << menu[itemIndex].name << " to your order." << endl;
  }
  else
  {
    cout << "Sorry, not enough stock available." << endl;
  }
}

void modifyOrder(vector<int> &order, int itemIndex, int quantity, const vector<MenuItem> &menu)
{
  if (menu[itemIndex].stock >= quantity)
  {
    order[itemIndex] = quantity;
    cout << "Order updated." << endl;
  }
  else
  {
    cout << "Sorry, not enough stock available." << endl;
  }
}

void showOrderSummary(const vector<MenuItem> &menu, const vector<int> &order)
{
  cout << "\n--- Order Summary ---" << endl;

  double total = 0.0;

  for (size_t i = 0; i < menu.size(); i++)
  {
    if (order[i] > 0)
    {
      cout << menu[i].name << " - " << "$" << menu[i].price << " x " << order[i] << " = $" << menu[i].price * order[i] << endl;
      total += menu[i].price * order[i];
    }
  }

  cout << "Total: $" << total << endl;

  cin.get();
  cin.get();
}

void saveOrderToHistory(const vector<MenuItem> &menu, const vector<int> &order)
{
  ofstream historyFile("order_history.txt", ios::app);

  historyFile << "--- New Order ---\n";

  double total = 0.0;

  for (size_t i = 0; i < menu.size(); ++i)
  {
    if (order[i] > 0)
    {
      historyFile << i + 1 << ". " << menu[i].name << " x " << order[i] << " = $" << menu[i].price * order[i] << "\n";
      total += menu[i].price * order[i];
    }
  }

  historyFile << "Total: $" << total << "\n\n";
  historyFile.close();

  cout << "Order saved to history.\n";
}

void loadOrderHistory()
{
  ifstream historyFile("order_history.txt");

  if (!historyFile.is_open())
  {
    cout << "No order history found.\n";
    return;
  }

  string line;

  while (getline(historyFile, line))
  {
    cout << line << endl;
  }

  historyFile.close();
}

void viewOrderHistory()
{
  ifstream historyFile("order_history.txt");

  if (!historyFile.is_open())
  {
    cout << "No order history found or the file could not be opened.\n";
    return;
  }

  string line;
  cout << "\n--- Order History ---\n";

  while (getline(historyFile, line))
  {
    cout << line << endl;
  }

  historyFile.close();
  cout << "\nEnd of Order History.\n";

  cin.get();
  cin.get();
}

void clearOrderHistory()
{
  ofstream historyFile("order_history.txt", ios::trunc);

  historyFile.close();

  cout << "Order history cleared.\n";
}

void restockInventory(vector<MenuItem> &menu)
{
  for (auto &item : menu)
  {
    cout << "Enter new stock for " << item.name << ": ";
    cin >> item.stock;
  }

  cout << "Inventory restocked.\n";
}

void loadSpecificOrder(vector<int> &order, vector<MenuItem> &menu)
{
  ifstream historyFile("order_history.txt");
  if (!historyFile.is_open())
  {
    cout << "No order history found or the file could not be opened.\n";
    return;
  }

  vector<string> orderLines;
  string line;
  int orderCount = 0;

  cout << "\n--- Available Orders ---\n";
  while (getline(historyFile, line))
  {
    if (line.find("Total") == string::npos)
    {
      cout << ++orderCount << ": " << line << endl;
      orderLines.push_back(line);
    }
  }

  if (orderCount == 0)
  {
    cout << "No previous orders found.\n";
    historyFile.close();
    return;
  }

  int selectedOrder;

  cout << "\nSelect an order to load (1 to " << orderCount << "): ";
  cin >> selectedOrder;

  if (selectedOrder < 1 || selectedOrder > orderCount)
  {
    cout << "Invalid selection.\n";
    historyFile.close();

    return;
  }

  string selectedOrderLine = orderLines[selectedOrder - 1];
  int itemIndex, quantity;

  sscanf(selectedOrderLine.c_str(), "%*s x %d", &quantity);

  itemIndex = selectedOrder - 1;

  if (itemIndex >= 0 && itemIndex < static_cast<int>(menu.size()))
  {
    order[itemIndex] = quantity;
    cout << "Order for " << menu[itemIndex].name << " loaded successfully.\n";
  }
  else
  {
    cout << "Error: Invalid item index.\n";
  }

  historyFile.close();
  cin.get();
  cin.get();
}

int main(void)
{
  vector<MenuItem> menu = {
      {"Pizza", "Delicious cheese pizza", 9.99, 10},
      {"Burger", "Juicy beef burger", 6.99, 10},
      {"Ice Cream", "Vanilla ice cream", 3.99, 10},
      {"Salad", "Fresh garden salad", 4.99, 10},
      {"Pasta", "Creamy Alfredo pasta", 7.99, 10},
      {"Coffee", "Hot brewed coffee", 2.99, 10}};

  vector<int> order(menu.size(), 0);

  vector<string> categories = {"Main Course", "Desserts", "Beverages"};
  vector<int> itemCategories = {0, 0, 1, 0, 0, 2};

  int choice;

  do
  {
    system("@cls||clear");
    cout << "Welcome to our Hotel Menu!" << endl
         << "1. Display Menu" << endl
         << "2. Display Menu by Category" << endl
         << "3. Add to Order" << endl
         << "4. Modify Order" << endl
         << "5. View Order Summary" << endl
         << "6. Save Order to History" << endl
         << "7. View Order History" << endl
         << "8. Clear Order History" << endl
         << "9. Restock Inventory" << endl
         << "10. Load Previous Order" << endl
         << "11. Checkout" << endl
         << "12. Exit" << endl
         << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      system("@cls||clear");
      displayMenu(menu);
      break;

    case 2:
      system("@cls||clear");
      displayMenuByCategory(menu, itemCategories, categories);
      break;

    case 3:
    {
      system("@cls||clear");
      int itemIndex, quantity;

      cout << "Enter the item number to order: ";
      cin >> itemIndex;

      cout << "Enter the quantity: ";
      cin >> quantity;

      if (itemIndex > 0 && itemIndex <= static_cast<int>(menu.size()) && quantity > 0)
      {
        addToOrder(order, menu, itemIndex - 1, quantity);
      }
      else
      {
        cout << "Invalid item number or quantity." << endl;
      }
      break;
    }

    case 4:
    {
      system("@cls||clear");
      int itemIndex, quantity;

      cout << "Enter the item number to modify: ";
      cin >> itemIndex;
      cout << "Enter the new quantity (enter 0 to remove): ";
      cin >> quantity;

      if (itemIndex > 0 && itemIndex <= static_cast<int>(menu.size()) && quantity >= 0)
      {
        modifyOrder(order, itemIndex - 1, quantity, menu);
      }
      break;
    }

    case 5:
      system("@cls||clear");
      showOrderSummary(menu, order);
      break;

    case 6:
      system("@cls||clear");
      saveOrderToHistory(menu, order);
      break;

    case 7:
      system("@cls||clear");
      viewOrderHistory();
      break;

    case 8:
      system("@cls||clear");
      clearOrderHistory();
      break;

    case 9:
      system("@cls||clear");
      restockInventory(menu);
      break;

    case 10:
      system("@cls||clear");
      loadSpecificOrder(order, menu);
      break;

    case 11:
      system("@cls||clear");
      cout << "Checking out..." << endl;
      showOrderSummary(menu, order);

      cout << "Thank you for your order!" << endl;

    case 12:
      system("@cls||clear");
      cout << "Thank you for visiting!" << endl;
      cin.get();
      cin.get();
      break;

    default:
      system("@cls||clear");
      cout << "Invalid input, please try again." << endl;
      cin.get();
      cin.get();
      break;
    }

  } while (choice != 12);

  return 0;
}