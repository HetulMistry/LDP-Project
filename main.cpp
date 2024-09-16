#include <iostream>
#include <string>
#include <vector>

#define CATEGORY_COUNT 3

using namespace std;

struct MenuItem
{
  string name;
  string description;
  double price;
};

void displayMenu(const vector<MenuItem> &menu)
{
  cout << "\n--- Hotel Menu ---" << endl;

  for (size_t i = 0; i < menu.size(); ++i)
  {
    cout << i + 1 << ". " << menu[i].name << " - " << menu[i].description << " ($" << menu[i].price << ")" << endl;
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
        cout << j + 1 << ". " << menu[j].name << " - " << menu[j].description << "($" << menu[j].price << ")" << endl;
      }
    }
  }

  cin.get();
  cin.get();
}

void addToOrder(vector<int> &order, int itemIndex, int quantity)
{
  order[itemIndex] += quantity;
}

void modifyOrder(vector<int> &order, int itemIndex, int quantity)
{
  order[itemIndex] = quantity;
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

int main(void)
{
  vector<MenuItem> menu = {
      {"Pizza", "Delicious cheese pizza", 9.99},
      {"Burger", "Juicy beef burger", 6.99},
      {"Ice Cream", "Vanilla ice cream", 3.99},
      {"Salad", "Fresh garden salad", 4.99},
      {"Pasta", "Creamy Alfredo pasta", 7.99},
      {"Coffee", "Hot brewed coffee", 2.99}};

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
         << "6. Checkout" << endl
         << "7. Exit" << endl
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
        addToOrder(order, itemIndex - 1, quantity);
        cout << "Item added to your order." << endl;
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
        modifyOrder(order, itemIndex - 1, quantity);
      }
      break;
    }

    case 5:
      system("@cls||clear");
      showOrderSummary(menu, order);
      break;

    case 6:
      system("@cls||clear");
      cout << "Checking out..." << endl;
      showOrderSummary(menu, order);
      cout << "Thank you for your order!" << endl;
      break;

    case 7:
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

  } while (choice != 7);

  return 0;
}