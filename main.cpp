#include <iostream>
#include <fstream>
#include <string>
#include "Recipe.h"

using namespace std;


void dataParsing();
void testZone(Recipe r);

int main() {

    dataParsing();

    return 0;
};



void dataParsing() {

    Recipe temp[10];

    int counter = 0;


    string na;
    int id;
    int mi;
    int numSt;
    int numIn;
    string ing;
    string nutrit;
    string ste;

    string line;
    ifstream theFile;
    theFile.open("Recipes.csv");
    getline(theFile, line);

    while (getline(theFile, line) && counter < 10) {

        na = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);

        id = stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1);

        mi = stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1);

        nutrit = line.substr(2, (line.find("]\",")-2));
        line = line.substr(line.find("]\",") + 3);

        numSt = stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1);

        ste = line.substr(2, (line.find("]\",")-2));
        line = line.substr(line.find("]\",") + 3);

        ing = line.substr(2, (line.find("]\",")-2));
        line = line.substr(line.find("]\",") + 3);

        numIn = stoi(line);



        counter++;
        temp[counter] = Recipe(na, id, mi, nutrit, numSt, numIn, ing, ste);
        testZone(temp[counter]);

    }


}



void testZone(Recipe r) {
    cout << "name: " << r.getName() << endl;
    cout << "ID: " << r.getUniqueID() << endl;
    cout << "Minutes: " << r.getMins() << endl;
    cout << "Nutrition: " << r.getNutrition() << endl;
    cout << "Number of Steps: " << r.getNumSteps() << endl;
    cout << "Number of Ingredients: " << r.getNumIngred() << endl;
    cout << "ingredients: " << r.getIngredients() << endl;
    cout << "Steps: " << r.getSteps() << endl;

}
