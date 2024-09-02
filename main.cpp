#include <iostream>
#include <string>

#define MAX_ITEM 10

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

void addToOrder(int order[], int itemIndex, int quantity)
{
  order[itemIndex] += quantity;
}

void showOrderSummary(MenuItem menu[], int order[], int itemCount)
{
  cout << "\n--- Order Summary ---" << endl;

  double total = 0.0;

  for (int i = 0; i < itemCount; i++)
  {
    if (order[i] > 0)
    {
      cout << menu[i].name << " - " << menu[i].price << " x " << "$" << order[i] << " = $" << menu[i].price * order[i] << endl;
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
      {"Burger", "Juicy ham burger", 8.99},
      {"Fries", "Crispy fries", 2.99},
      {"Soda", "Cold soda", 1.99},
      {"Salad", "Fresh green salad", 4.99},
      {"Sandwich", "Delicious sandwich", 7.99},
      {"Pizza", "Hot pizza", 9.99},
      {"Chicken", "Grilled chicken", 6.99},
      {"Ice Cream", "Vanilla ice cream", 3.99},
      {"Cake", "Moist chocolate cake", 5.99},
      {"Bread", "Freshly baked bread", 1.99}};

  int order[MAX_ITEM] = {0};
  int itemCount = 10;

  int choice;

  do
  {
    system("@cls||clear");
    cout << "Welcome to our Hotel Menu!" << endl
         << "1. Display Menu" << endl
         << "2. Add to Order" << endl
         << "3. View Order Summary" << endl
         << "4. Checkout" << endl
         << "5. Exit" << endl
         << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      system("@cls||clear");
      displayMenu(menu, itemCount);
      break;

    case 2:
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

    case 3:
      system("@cls||clear");
      showOrderSummary(menu, order, itemCount);
      break;

    case 4:
      system("@cls||clear");
      cout << "Checking out..." << endl;
      showOrderSummary(menu, order, itemCount);
      cout << "Thank you for your order!";
      break;

    case 5:
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

  } while (choice != 5);

  return 0;
}