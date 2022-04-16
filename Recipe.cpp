#include <fstream>

#include "Recipe.h"
using namespace std;

Recipe::Recipe() {
	name = "";
	uniqueID = -1; 
	mins = -1; 
	nutrition = "";
	numSteps = -1; 
	numIngred = -1; 
	ingredients = "";
	steps = "";
}

Recipe::Recipe(string n, int id, int min, string nut, int numS, int numI, string ingred, string s) {
	name = n;
	uniqueID = id;
	mins = min;
	nutrition = nut;
	numSteps = numS;
	numIngred = numI;
	ingredients = ingred;
	steps = s;
}

string Recipe::getName() {
	return name;
}

int Recipe::getUniqueID() {
	return uniqueID;
}

int Recipe::getMins() {
	return mins;
}

int Recipe::getNumSteps() {
	return numSteps;
}

string Recipe::getSteps() {
	return steps;
}

int Recipe::getNumIngred() {
	return numIngred;
}

string Recipe::getIngredients() {
	return ingredients;
}

string Recipe::getNutrition() {
	return nutrition;
}
