
/*

Things to do:

quick sort implementation for all int
heap sort implementation for all int
search function
print


*/

/*
things finished

parsing
working quick sort for get min
working heap sort for get min

*/



#include <iostream>
#include <fstream>
#include <string>
#include "Recipe.h"

using namespace std;


void dataParsing(Recipe r[]);
void testZone(Recipe r);

void quickSort(Recipe recipes[], int start, int end);
int quickSortHelper(Recipe recipes[], int start, int end);

void heapSort(Recipe recipes[], int size);
void heapify(Recipe recipes[], int size, int index);

//void swapObject(Recipe* a, Recipe b);
void printMins(Recipe recipes[], int size);



int main() {


    Recipe temp[10];

    dataParsing(temp);

    //delete[] temp; 

    //quickSort(temp, 0, 9);
   heapSort(temp, 10);



    printMins(temp,10);

    /*
    for (int i = 0; i < 10; i++) {
        testZone(temp[i]);
    }
    */

    return 0;
};



void dataParsing(Recipe r[]) {

    //Recipe temp[10];

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

        //r[counter] = new Recipe(na, id, mi, nutrit, numSt, numIn, ing, ste);
        r[counter] = Recipe(na, id, mi, nutrit, numSt, numIn, ing, ste);
        //Recipe theTemp = r[counter];

        testZone(r[counter]);
        counter++;

    }


}

void quickSort(Recipe recipes[], int start, int end) {

    int position; 

    if (start < end) {
        position = quickSortHelper(recipes, start, end);

        quickSort(recipes, start, position - 1);

        quickSort(recipes, position + 1, end);
    }
}

int quickSortHelper(Recipe recipes[], int start, int end) {
    cout << "reached here" << endl;
    
    int pivot = recipes[start].getMins();
    int count = 0; 

    for (int i = start + 1; i <= end; i++) {
        if (recipes[i].getMins() <= pivot) {
            count++;
        }
    }

    int pivotIndex = start + count; 

    recipes[pivotIndex].swapRecipe(recipes[start]);

    int i = start, j = end;


    while (i < pivotIndex && j > pivotIndex) { 
        while (recipes[i].getMins() <= pivot) {
            i++;
        }
        while (recipes[j].getMins() > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            recipes[i].swapRecipe(recipes[j]);
            i++;
            j++;
        }
    }
    return pivotIndex; 
}

void heapSort(Recipe recipes[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(recipes, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        recipes[0].swapRecipe(recipes[i]);

        heapify(recipes, i, 0);
    }
}

void heapify(Recipe recipes[], int size, int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < size && recipes[leftChild].getMins() > recipes[largest].getMins()) {
        largest = leftChild;
    }
    if (rightChild < size && recipes[rightChild].getMins() > recipes[largest].getMins()) {
        largest = rightChild;
    }

    if (largest != index) {
        recipes[largest].swapRecipe(recipes[index]);
        heapify(recipes, size, largest);
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


void printMins(Recipe recipes[], int size) {
    for (int i = 0; i < size; i++) {
        cout << recipes[i].getName() << ": " << recipes[i].getMins() << endl;
    }
}
