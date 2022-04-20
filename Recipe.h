#pragma once

#include <iostream>
#include <string>

using namespace std;


class Recipe {

	string name;
	int uniqueID;
	int mins;
	string nutrition;
	int numSteps;
	int numIngred;
	string ingredients;
	string steps;


public:
	Recipe();
	Recipe(string n, int id, int min, string nut, int numS, int numI, string ingred, string s);
	string getName();
	int getUniqueID();
	int getMins();
	int getNumSteps();
	string getSteps();
	int getNumIngred();
	string getIngredients();
	string getNutrition();


	void swapRecipe(Recipe& other);
};
