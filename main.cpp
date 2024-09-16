#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define CATEGORY_COUNT 3

using namespace std;

struct MenuItem
{
  string name;
  string description;
  double price;
  int stock;
};

void displayMenu(const vector<MenuItem> &menu)
{
  cout << "\n--- Hotel Menu ---" << endl;
  for (size_t i = 0; i < menu.size(); ++i)
  {
    cout << i + 1 << ". " << menu[i].name << " - " << menu[i].description << " ($" << menu[i].price << ")"
         << " [Stock: " << menu[i].stock << "]" << endl;
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
        cout << j + 1 << ". " << menu[j].name << " - " << menu[j].description << " ($" << menu[j].price << ")"
             << " [Stock: " << menu[j].stock << "]" << endl;
      }
    }
  }
  cin.get();
  cin.get();
}

void addToOrder(vector<int> &order, vector<MenuItem> &menu, int itemIndex, int quantity)
{
  if (menu[itemIndex].stock >= quantity)
  {
    order[itemIndex] += quantity;
    menu[itemIndex].stock -= quantity;
    cout << "Item added to your order." << endl;
  }
  else
  {
    cout << "Sorry, we only have " << menu[itemIndex].stock << " units of " << menu[itemIndex].name << " in stock." << endl;
  }
}

void modifyOrder(vector<int> &order, int itemIndex, int quantity, vector<MenuItem> &menu)
{
  int currentQuantity = order[itemIndex];
  int difference = quantity - currentQuantity;

  if (difference > 0)
  {
    if (menu[itemIndex].stock >= difference)
    {
      order[itemIndex] = quantity;
      menu[itemIndex].stock -= difference;
    }
    else
    {
      cout << "Sorry, we only have " << menu[itemIndex].stock << " units of " << menu[itemIndex].name << " in stock." << endl;
    }
  }
  else
  {
    order[itemIndex] = quantity;
    menu[itemIndex].stock -= difference;
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

void restockInventory(vector<MenuItem> &menu)
{
  system("@cls||clear");
  int itemIndex, quantity;

  cout << "Enter the item number to restock: ";
  cin >> itemIndex;
  cout << "Enter the quantity to restock: ";
  cin >> quantity;

  if (itemIndex > 0 && itemIndex <= static_cast<int>(menu.size()) && quantity > 0)
  {
    menu[itemIndex - 1].stock += quantity; // Add stock to the item
    cout << "Restocked " << quantity << " units of " << menu[itemIndex - 1].name << "." << endl;
  }
  else
  {
    cout << "Invalid input." << endl;
  }
  cin.get();
  cin.get();
}

void saveOrderToFile(const vector<MenuItem> &menu, const vector<int> &order)
{
  ofstream orderFile("order.txt");
  if (orderFile.is_open())
  {
    for (size_t i = 0; i < menu.size(); ++i)
    {
      if (order[i] > 0)
      {
        orderFile << menu[i].name << " x " << order[i] << " = $" << menu[i].price * order[i] << "\n";
      }
    }
    orderFile.close();
    cout << "Order saved to file.\n";
  }
  else
  {
    cout << "Unable to save the order.\n";
  }
}

void loadOrderFromFile()
{
  ifstream orderFile("order.txt");
  string line;
  if (orderFile.is_open())
  {
    cout << "\n--- Loaded Order ---\n";
    while (getline(orderFile, line))
    {
      cout << line << endl;
    }
    orderFile.close();
  }
  else
  {
    cout << "No saved order found.\n";
  }
  cin.get();
  cin.get();
}

int main(void)
{
  vector<MenuItem> menu = {
      {"Pizza", "Delicious cheese pizza", 9.99, 10},
      {"Burger", "Juicy beef burger", 6.99, 8},
      {"Ice Cream", "Vanilla ice cream", 3.99, 5},
      {"Salad", "Fresh garden salad", 4.99, 12},
      {"Pasta", "Creamy Alfredo pasta", 7.99, 7},
      {"Coffee", "Hot brewed coffee", 2.99, 15}};

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
         << "6. Save Order to File" << endl
         << "7. Load Previous Order" << endl
         << "8. Restock Inventory" << endl
         << "9. Checkout" << endl
         << "10. Exit" << endl
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
      saveOrderToFile(menu, order);
      break;

    case 7:
      system("@cls||clear");
      loadOrderFromFile();
      break;

    case 8:
      system("@cls||clear");
      restockInventory(menu);
      break;

    case 9:
      system("@cls||clear");
      cout << "Checking out..." << endl;
      showOrderSummary(menu, order);
      cout << "Thank you for your order!" << endl;

    case 10:
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

  } while (choice != 10);

  return 0;
}