#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <string>
#include <vector>

  class Food{
    private:
      string name;
      string type;

    public:
      void print_ingredients();
      void set_item_name(string user_name);
      void set_type(string user_type);
      vector<string> ingredients;
			void set_ingredient(string ingredient_name);
			bool CompareToIngredients(vector<string> choices);
			string getName();
      Food(string food_name){ name = food_name; } // initializer
  };
  class Restaurant{
    private:
      string name;
      vector<Food> menu;

    public:
      void set_name(string user_name);
      void add_food(Food food_name);
			//void CheckMenu(vector<Food>& options, string& choices, vector<Food>& good_food);
      void CheckMenu(const vector<string>& choices, vector<Food>& good_food);
			string getName();
  };
#endif
