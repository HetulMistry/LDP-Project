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

  return 0;
}