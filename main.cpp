
/*

Things to do:

quick sort implementation for all int - done
heap sort implementation for all int
search function
print


*/

/*
things finished

parsing
working quick sort for get min
working heap sort for get min
quick sort working for all 

*/



#include <iostream>
#include <fstream>
#include <string>
#include "Recipe.h"

using namespace std;


void dataParsing(Recipe r[]);
void testZone(Recipe r);

void quickSort(Recipe recipes[], int start, int end, string type);
int quickSortHelper(Recipe recipes[], int start, int end, string type);

void heapSort(Recipe recipes[], int size, string type);
void heapify(Recipe recipes[], int size, int index, string type);

void printMins(Recipe recipes[], int size);
void printSelected(Recipe recipes[], string type, int size);



int main() {
    int size; 

    Recipe temp[100000];


    dataParsing(temp);

    //size = sizeof(temp) / sizeof(temp[0]);

    //quickSort(temp, 0, 9, "mins");
   //heapSort(temp, size, "numSteps");

    //printSelected(temp, "numSteps", size);

     
    //cout << size << endl; 

    return 0;
};

void dataParsing(Recipe r[]) {

    int counter = 0;

    int tempSize = 1; 

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

    while (getline(theFile, line) && counter < 100000) {

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

        r[counter] = Recipe(na, id, mi, nutrit, numSt, numIn, ing, ste);

        //testZone(r[counter]);
        counter++;
        tempSize++;

    }


}



void quickSort(Recipe recipes[], int start, int end, string type) {

    int position; 

    if (start < end) {
        position = quickSortHelper(recipes, start, end, type);

        quickSort(recipes, start, position - 1, type);

        quickSort(recipes, position + 1, end, type);
    }
}

int quickSortHelper(Recipe recipes[], int start, int end, string type) {
    
    int pivot = recipes[start].valueGetter(type);
    int count = 0; 

    for (int i = start + 1; i <= end; i++) {
        if (recipes[i].valueGetter(type) <= pivot) {
            count++;
        }
    }

    int pivotIndex = start + count; 

    recipes[pivotIndex].swapRecipe(recipes[start]);

    int i = start;
    int j = end;


    while (i < pivotIndex && j > pivotIndex) { 
        while (recipes[i].valueGetter(type) <= pivot) {
            i++;
        }
        while (recipes[j].valueGetter(type) > pivot) {
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


void heapSort(Recipe recipes[], int size, string type) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(recipes, size, i, type);
    }

    for (int i = size - 1; i > 0; i--) {
        recipes[0].swapRecipe(recipes[i]);

        heapify(recipes, i, 0, type);
    }
}

void heapify(Recipe recipes[], int size, int index, string type) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < size && recipes[leftChild].valueGetter(type) > recipes[largest].valueGetter(type)) {
        largest = leftChild;
    }
    if (rightChild < size && recipes[rightChild].valueGetter(type) > recipes[largest].valueGetter(type)) {
        largest = rightChild;
    }

    if (largest != index) {
        recipes[largest].swapRecipe(recipes[index]);
        heapify(recipes, size, largest, type);
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
        cout << recipes[i].getName() << ": " << recipes[i].getNumSteps() << endl;
    }
}

void printSelected(Recipe recipes[], string type, int size) {
    cout << "size: " << size << endl;

    if (type == "all") {
        for (int i = 0; i < size; i++) {
            cout << "name: " << recipes[i].getName() << endl;
            cout << "ID: " << recipes[i].getUniqueID() << endl;
            cout << "Minutes: " << recipes[i].getMins() << endl;
            cout << "Nutrition: " << recipes[i].getNutrition() << endl;
            cout << "Number of Steps: " << recipes[i].getNumSteps() << endl;
            cout << "Number of Ingredients: " << recipes[i].getNumIngred() << endl;
            cout << "ingredients: " << recipes[i].getIngredients() << endl;
            cout << "Steps: " << recipes[i].getSteps() << endl;
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            cout << recipes[i].getName() << ": " << recipes[i].valueGetter(type) << endl;
        }

    }
}
