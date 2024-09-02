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

void displayMenu() { cout << "DisplayMenu" << endl; }
void addToOrder() { cout << "addToOrder" << endl; }
void showOrderSummary() { cout << "showOrderSummary" << endl; }

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

  int itemCount = 10;

  int choice;

  do
  {
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
      displayMenu();
      break;

    case 2:
    {
      int itemIndex, quantity;

      cout << "Enter the item number to order: ";
      cin >> itemIndex;

      cout << "Enter the quantity: ";
      cin >> quantity;

      if (itemIndex > 0 && itemIndex <= itemCount && quantity > 0)
      {
        addToOrder();
        cout << "Item added to your order." << endl;
      }
      else
      {
        cout << "Invalid item number or quantity." << endl;
      }
      break;
    }

    case 3:
      showOrderSummary();

    case 4:
      cout << "Checking out..." << endl;
      showOrderSummary();
      cout << "Thank you for your order!";

    case 5:
      cout << "Thank you for visiting!" << endl;
      break;

    default:
      cout << "Invalid input, please try again." << endl;
      break;
    }

  } while (choice != 5);

  return 0;
}