#ifndef BUSINESSES_H
#define BUSINESSES_H

void InputName(new_restaurant);
void InputName(Restaurant& new_restaurant);
void InputMenu(Restaurant& new_restaurant);
void InputIngredients(Food cur_food_item);
void OutputMenu(Restaurant new_restaurant);
void OutputResults(vector<pair<vector<Food>, Restaurant>> foods_and_rest);

#endif
