#include <iostream>
#include <string>

#define MAX_ITEM 10
#define CATEGORY_COUNT 3

using namespace std;

struct MenuItem
{
  string name;
  string description;
  double price;
};

void displayMenu(MenuItem menu[], int itemCount)
{
  cout << "\n--- Hotel Menu ---" << endl;

  for (int i = 0; i < itemCount; ++i)
  {
    {
      cout << i + 1 << ". " << menu[i].name << " - " << menu[i].description << " ($" << menu[i].price << ")" << endl;
    }
  }

  cin.get();
  cin.get();
}

void displayMenuByCategory(MenuItem menu[], int itemCount, const string categories[], int itemCategories[])
{
  cout << "\n--- Hotel Menu by Categories ---" << endl;

  for (int i = 0; i < CATEGORY_COUNT; ++i)
  {
    cout << endl
         << categories[i] << ":\n";

    for (int j = 0; j < itemCount; ++j)
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

void addToOrder(int order[], int itemIndex, int quantity)
{
  order[itemIndex] += quantity;
}

void modifyOrder(int order[], int itemIndex, int quantity)
{
  order[itemIndex] = quantity;
}

void showOrderSummary(MenuItem menu[], int order[], int itemCount)
{
  cout << "\n--- Order Summary ---" << endl;

  double total = 0.0;

  for (int i = 0; i < itemCount; i++)
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
  MenuItem menu[MAX_ITEM] = {
      {"Pizza", "Delicious cheese pizza", 9.99},
      {"Burger", "Juicy beef burger", 6.99},
      {"Ice Cream", "Vanilla ice cream", 3.99},
      {"Salad", "Fresh garden salad", 4.99},
      {"Pasta", "Creamy Alfredo pasta", 7.99},
      {"Coffee", "Hot brewed coffee", 2.99}};

  int order[MAX_ITEM] = {0};
  int itemCount = 6;

  string categories[CATEGORY_COUNT] = {"Main Course", "Desserts", "Beverages"};
  int itemCategories[MAX_ITEM] = {0, 0, 1, 0, 0, 2};

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
      displayMenu(menu, itemCount);
      break;

    case 2:
      system("@cls||clear");
      displayMenuByCategory(menu, itemCount, categories, itemCategories);
      break;

    case 3:
    {
      system("@cls||clear");
      int itemIndex, quantity;

      cout << "Enter the item number to order: ";
      cin >> itemIndex;

      cout << "Enter the quantity: ";
      cin >> quantity;

      if (itemIndex > 0 && itemIndex <= itemCount && quantity > 0)
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

      if (itemIndex > 0 && itemIndex <= itemCount && quantity >= 0)
      {
        modifyOrder(order, itemIndex - 1, quantity);
      }
      break;
    }

    case 5:
      system("@cls||clear");
      showOrderSummary(menu, order, itemCount);
      break;

    case 6:
      system("@cls||clear");
      cout << "Checking out..." << endl;
      showOrderSummary(menu, order, itemCount);
      cout << "Thank you for your order!";

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