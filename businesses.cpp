#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include <bits/stdc++.h>
#include "businesses.h"
#include "classes.h"

// Main function for businesses calling for info entering
json InputStoreInfo(){
	Restaurant new_restaurant;
	InputName(new_restaurant);
	InputMenu(new_restaurant);
	OutputMenuJson(new_restaurantt)
}

// Input restaurant name request into object
void InputName(vector<Restaurant>& all_restaurants){
	string rest_name;
	bool is_new_restaurant;
	cout << "What is your Restaurant name?" << endl;
	cin >> rest_name;
	for (i = 0; i < all_restaurants.size(); ++i){
		if (rest_name == all_restaurants[i].getName()){
			//
			break;
		}else{
			Restaurant(rest_name);
			all_restaurants.push_back(rest_name);
		}
	}
	InputDish(all_restaurants, rest_name);
}

// Requests the information for a single food item
void InputDish(vector<Restaurant>& all_restaurants, string rest_name){
	Food cur_food_item;
	string cur_food_name;
	int i = 0;
	cout << "Enter your Dish: "; //<< "Enter DONE to finish" << endl;
	cin >> cur_food_name;
	ConvertStringLower(cur_food_name);
	cur_food_item.set_item_name(cur_food_item);
	InputIngredients(cur_food_item);
	for (i = 0; i < all_restaurants.size(); ++i){ // input Food (with ingredients) into restaurant
		if (rest_name == all_restaurants[i].getName()){
			all_restaurants[i].add_food(rest_name);
			break;
		}
}

// Input all ingredients for a single food item
// we use "enter done/finish" to end due to time restrictions
void InputIngredients(Food& cur_food_item) {
	int i = 0;
	string cur_ingredient;
	cout << "Input ingredients." << endl; //<< "Enter FINISH to stop. " << endl;
	cout << "Enter Ingredients: ";
	bool valid_word = true;
  while (cin >> cur_ingredient){
    valid_word = true;
		ConvertStringLower(cur_ingredient);
    for (string::size_type i = 0; i < cur_ingredient.length(); ++i){ // checking for invalid input
      if (!isalpha(cur_ingredient[i])){ // eats up whitespace
        valid_word = false;
      }
		}
  }
    if (valid_word){
      cur_food_item.set_ingredient(cur_ingredient);
    }
}

// Output menu for coder debugging purposes in C++ section
void OutputMenu(Restaurant new_restaurant){
	cout << new_restaurant.getName() << endl;
	cout << "Menu: " << endl;
	for(int j = 0; j < new_restaurant.Restaurant::menu.size(); j++){
		cout << new_restaurant.Restaurant::menu[j].getName() << endl;
		cout << "Ingredients: "
		for (int k = 0; k < new_restaurant.Restaurant::menu[j].Food::ingredients.size(); k++) {
			cout << new_restaurant.Restaurant::menu[j].Food::ingredients[k];
			if (k != k < new_restaurant.Restaurant::menu[j].Food::ingredients.size() - 1) {
				cout << ", ";
			} else {
				cout << endl;
			}
		}
	}
}

// Output information entered by business into formatable Json file for front end
json OutputMenuJson(Restaurant new_restaurantt) {
	json j;
	string Restaurant = "Restaurant";  // json key names must be unique
	j[Restaurant] = new_restaurant.getName();
	for(int j = 0; j < new_restaurant.Restaurant::menu.size(); j++) {
		string Menu = "Menu" + str(j);
		j[Restaurant][Menu] = new_restaurant.Restaurant::menu[j].getName();
		for (int k = 0; k < new_restaurant.Restaurant::menu[j].Food::ingredients.size(); k++) {
			string Menu = "Ingredient" + str(j);
			j[Restaurant][Menu][Ingredient] = new_restaurant.Restaurant::menu[j].Food::ingredients[k];
		}
	}
}
	std::ofstream b("BusiResults.json");
	b << std::setw(4) << j << std::endl;
	return o;
}
