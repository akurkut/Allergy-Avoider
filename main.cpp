#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <bits/stdc++.h>
#include "classes.h"
#include "businesses.h"
#include "json.hpp"
#include <fstream>

//Outline
using namespace std;
using json = nlohmann::json;

#include "crow.h"

// Attempt at connecting Back end to front end
// However, our exexperience got the best of us
int main(int argc, char* argv)
{
    crow::SimpleApp app;

		// Java call for User side
    CROW_ROUTE(app, "/client")([]() {
        return startClient();
    });

		// Java call for Business side
		CROW_ROUTE(app, "/business")([]() {
        return startClient();
    });

		// server side accepts request from this port number
    app.port(18080).multithreaded().run();

		return 0;
}

// client side returns a filtered search of Restaurants listed with compatible menu operations
// As well as the Food items' ingredients
json startClient(){
	//user side
	string user_pref; //User preferences
	vector<string> choices;
	int diet = 0;
	vector<Restauraunt> all_restaurants;

	DietType(diet);
	AllergyType(vector<Restaurant> all_restaurants);
	GetAllergiesFromUser(choices, diet);

	vector<pair<vector<Food>, Restaurant>> food_rest = CompareRestaurant(all_restaurants, choices);
	return OutputResultsJson(food_rest);
}

// Allows Businesses to input their information into the website for clients to access
int startBusiness(){
	return InputStoreInfo();
}

// gets the diet type from the user
void DietType(int& diet){ //choice string is shared pointer in used function
	string user_pref;
	cout << "Enter your meat prefrences: " << endl;
	cout << "Choose \"anything\",\"halal\", \"pescetarian\", \"vegan\", \"vegetarian\" " << endl;
	//Note: options must be spelled correctly for prototype version
	cin >> user_pref;

	ConvertStringLower(&user_pref);

	if(user_pref == "anything") {
		diet = 0;
	} else if(user_pref == "halal") {
		diet = 1;
	} else if(user_pref == "pescetarian") {
		diet = 2;
	} else if(user_pref == "vegan") {
		diet = 3;
	} else if(user_pref == "vegetarian") {
		diet = 4;
	} else {
		user_pref.clear()
		cout << "Try Again." << endl;
		DietType();
	}
}

// Shows user which allergies are filterable by the website
void AllergyType(vector<Restaurant> all_restaurants) {
	cout << "Enter your allergies: " << endl;
	cout << "We currently Support:" << Print_all_ingredients(&all_restaurants) << endl;  //have a set of ingredients to read off of. much easier
}

// prevents letter case sensitivity in input options
void ConvertStringLower(string& choice){
	transform(choice.begin(), choice.end(), choice.begin(),
    [](unsigned char c){ return tolower(c); });
	}
}

// allows user to input what allergies they have given the options
void GetAllergiesFromUser(vector<string>& choices, int diet){
	string maybe_choice;
	int i = 1;
  bool valid_word = true; // not whitespace

  cout << "Enter Allergies: ";
  while (cin >> maybe_choice){
    valid_word = true;
		ConvertStringLower(maybe_choice);
    for (string::size_type i = 0; i < maybe_choice.length(); ++i){ // checking for invalid input
      if (!isalpha(maybe_choice[i])){ // eats up whitespace
        valid_word = false;
      }
    }
		// diet types automatically add the following options to the "exculde list"
    if (valid_word){
      if(diet == 1) {
        // no pork, no beef
        choices.push_back("pork");
        choices.push_back("beef");
      } else if (diet == 2) {
        choices.push_back("pork");
        choices.push_back("beef");
        choices.push_back("chicken");
      } else if (diet == 3){
        choices.push_back("pork");
        choices.push_back("beef");
        choices.push_back("chicken");
        choices.push_back("fish");
        choices.push_back("milk");
        choices.push_back("egg");
        choices.push_back("eggs");
      } else if (diet == 4) {
        choices.push_back("pork");
        choices.push_back("beef");
        choices.push_back("chicken");
        choices.push_back("fish");
      }
    }
  }

	/*do {
		cout << "Enter Allergy " << i << ": ";
		cin >> maybe_choice;
		ConvertStringLower(maybe_choice);
		if (maybe_choice != "done") {
			choices.push_back(maybe_choice);
		}
		i++;
	} while (maybe_choice != "done");

	if(diet == 1) {
		// no pork, no beef
		choices.push_back("pork");
		choices.push_back("beef");
	} else if (diet == 2) {
		choices.push_back("pork");
		choices.push_back("beef");
		choices.push_back("chicken");
	} else if (diet == 3){
		choices.push_back("pork");
		choices.push_back("beef");
		choices.push_back("chicken");
		choices.push_back("fish");
		choices.push_back("milk");
		choices.push_back("egg");
		choices.push_back("eggs");
	} else if (diet == 4) {
		choices.push_back("pork");
		choices.push_back("beef");
		choices.push_back("chicken");
		choices.push_back("fish");
	}*/
}

// Allows Restauraunt food item ingredients to be compared with allergy list
vector<pair<vector<Food>, Restaurant>> CompareRestaurant(vector<Restaurant> all_restaurants, vector<string> choices){ // compares user allergies with menu items in all restaurants
	vector<pair<vector<Food>, Restaurant>> foods_and_rest;
	for(int i = 0; i < all_restaurants.size() - 1; i++){
		vector<Food> good_food;
		all_restaurants[i].CheckMenu(choices, &good_food);
		foods_and_rest.push_back(make_pair(good_food, all_restaurants[i]));
	}
	return foods_and_rest;
}

// Prints supported allergy checks for user to see
void Print_all_ingredients(vector<Restaurant> all_restaurants) {
	vector<string> all_ingredients;
	for(int i = 0; i < all_restaurants.size(); i++){
		for(int j = 0; j < all_restaurants[i].Restaurant::menu.size(); j++){
			for(int k = 0; k < all_restaurants[i].Restaurant::menu[j].Food::ingredients.size(); k++){
				if(all_ingredients.size() == 0){
					all_ingredients.append(all_restaurants[i].Restaurant::menu[j].Food::ingredients[k]);
				} else {
					for(int l = 0; l < all_ingredients.size(); ++l){
						if (all_restaurants[i].Restaurant::menu[j].Food::ingredients[k] != all_ingredients[l]) {
							all_ingredients.append(all_restaurants[i].Restaurant::menu[j].Food::ingredients[k]);
						}
					}
				}
			}
		}
	}
}

// Outputs results for C++ user/debugger
void OutputResults(vector<pair<vector<Food>, Restaurant>> foods_and_rest) {
	cout << "Here's what we found for you!" << endl << endl << endl;
	for(int i = 0; i < foods_and_rest.size(); i++) {
		cout << "Restaurant: " << endl;
		cout << foods_and_rest[i].second().getName() << endl << endl;
		cout << "Menu: " << endl
		for(int j = 0; j < foods_and_rest[i].first().size(); j++){
			cout << foods_and_rest[i].first()[j] << endl;
			cout << "Ingredients: "
			for (int k = 0; k < foods_and_rest[i].first()[j].Food::ingredients.size(); k++) {
				cout << foods_and_rest[i].first()[j].Food::ingredients[k];
				if (k != k < foods_and_rest[i].first()[j].Food::ingredients.size() - 1) {
					cout << ", ";
				} else {
					cout << endl;
				}
			}
		}
	}
}

// outputs results as a json file for the front end to unpack
json OutputResultsJson(vector<pair<vector<Food>, Restaurant>> foods_and_rest) {
	json j;
	for(int i = 0; i < foods_and_rest.size(); i++) {
		string Restaurant = "Restaurant" + str(i);  // json key names must be unique
		j[Restaurant] = foods_and_rest[i].second().getName();
		for(int j = 0; j < foods_and_rest[i].first().size(); j++) {
			string Menu = "Menu" + str(j);
			j[Restaurant][Menu] = foods_and_rest[i].first()[j];
			for (int k = 0; k < foods_and_rest[i].first()[j].Food::ingredients.size(); k++) {
				string Menu = "Ingredient" + str(j);
				j[Restaurant][Menu][Ingredient] = foods_and_rest[i].first()[j].Food::ingredients[k];
			}
		}
	}
	std::ofstream o("searchResults.json");
	o << std::setw(4) << j << std::endl;
	return o;
}
