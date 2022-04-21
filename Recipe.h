#pragma once

#include <iostream>
#include <string>

using namespace std;


class Recipe {
	// private variables
	string name;
	int uniqueID;
	int mins;
	string nutrition;
	int numSteps;
	int numIngred;
	string ingredients;
	string steps;


public:
	// constructors 
	Recipe();
	Recipe(string n, int id, int min, string nut, int numS, int numI, string ingred, string s);

	// getters
	string getName();
	int getUniqueID();
	int getMins();
	int getNumSteps();
	string getSteps();
	int getNumIngred();
	string getIngredients();
	string getNutrition();

	// helpers
	void swapRecipe(Recipe& other);
	int valueGetter(string var);

	// destructor
	~Recipe();
};
