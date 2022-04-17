// print all ingredients in food item
Food::void print_ingredients(){
			cout << "Ingredients: ";
			for (int i = 0; i < ingredients.size() - 1; ++i){
				cout << ingredients[i] << ", "
			}
			cout << ingrdients[i + 1] << endl;
		}
// set the name of the food to Food object
Food::void set_item_name(string user_name){name = user_name;}

// set Type of food for diet
Food::void set_type(string user_type){type = user_type;}

// Append a single ingredient onto ingredient list
Food::void set_ingredient(string ingredient_name){
	ingredients.push_back(ingredient_name))
}

// retreive Food name
Food::string getName(){
	return name;
}

// Compare ingredients in a food to allergens reported by user
Food::bool CompareToIngredients(vector<string> choices){
	bool has_allergen = 0;
	for(int j = 0; j < choices.size() - 1; j++){
		string allergen = choices[j];
		for(int i = 0; i < ingredients.size() - 1; i++){
			if (allergen == ingredients[i]){
				has_allergen = 1;
			}
			if (has_allergen){
				break;
			}
				//Add food to output array?? Or should we just delete off of menu??
		}
		if(has_allergen){
			break;
		}
	}
	return has_allergen;
}

// Set name of restaurant
Restauraunt::void set_name(string user_name){ name = user_name;}

// Add food to restaurant menu
Restauraunt::void add_food(Food food_name){menu.push_back(food_name);}

// Check menu for potential allergens listed by the user
Restaurant::void CheckMenu(vector<Food> options, vector<string> choices, vector<Food> good_food){
	for(int i = 0; i < options.size() - 1; i++){
		bool is_allergen = rest_option.CompareToIngredients(rest_option, string* choices);
		if(!is_allergen) {
				good_food.append(rest_option);
		}
	}
}

// Check menu for potential allergens listed by the user (immutable reference version)
Restaurant::void CheckMenu(const vector<string>& choices, vector<Food>& good_food){
	for(int i = 0; i < (Restaurant::menu).size() - 1; i++){
		if(!((Restaurant::menu)[i].CompareToIngredients(choices))) { // current food does not have user's allergens
			good_food.push_back(Restaurant::menu)[i]);
		}
	}
}

// return name of restaurant
Restaurant::string getName(){
	return name;
}
