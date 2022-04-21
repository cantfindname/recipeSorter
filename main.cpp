
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "Recipe.h"

using namespace std;
using namespace std::chrono; 

// function initialization 
vector<Recipe*> dataParsing(vector<Recipe*> recipes);

    // quick sort
void quickSort(vector<Recipe*> recipes, int start, int end, string type);
int quickSortHelper(vector<Recipe*> recipes, int start, int end, string type);

    // heap sort
void heapSort(vector<Recipe*> recipes, int size, string type);
void heapify(vector<Recipe*> recipes, int size, int index, string type);

    // print the recipe and related data
void printSelected(vector<Recipe*> recipes, string type, int size);
    
    // search for recipe according to user input
void searchData(vector<Recipe*> recipes, string keyword, string sortBy);


// ----------- getting user input and calling functions -----------
int main() {
    auto start = high_resolution_clock::now(); 

    string keyword;
    string sortItBy;
    bool validCin = false; 

    // user interface and input
    cout << "=======================================" << endl; 
    cout << "what type of food are you looking for?" << endl; 
    cout << "please enter one keyword, such as coffee, salad, cake" << endl; 
    cin >> keyword; 
    cout << "how would you like to sort it by? Enter either numberOfIngredients, numberOfSteps, or timeItTakes" << endl;
    cin >> sortItBy; 

    // initialize the recipes vector and add Recipe object into the vector 
    vector<Recipe*> recipes; 
    recipes = dataParsing(recipes);

    // check for valid user input
    if (sortItBy == "numberOfIngredients") {
        sortItBy = "numIngred";
        validCin = true; 
    }
    else if (sortItBy == "numberOfSteps") {
        sortItBy = "numSteps";
        validCin = true;
    }
    else if (sortItBy == "timeItTakes") {
        sortItBy = "mins";
        validCin = true;
    }
    else {
        cout << "invalid command, try again" << endl;
    }

    if (validCin) {
        searchData(recipes, keyword, sortItBy);
    }
     
    // Record the time it takes to run the program
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl; 

    return 0;
};
// ----------------------------------------------------------------

// function delcaration 
vector<Recipe*> dataParsing(vector<Recipe*> recipes) {

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

    //parsing data line by line
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
        
        ste = line.substr(2, (line.find("]\",") - 2));
        line = line.substr(line.find("]\",") + 3);

        ing = line.substr(2, (line.find("]\",")-2));
        line = line.substr(line.find("]\",") + 3);

        numIn = stoi(line);

        // construct a new object and add to the vector
        recipes.push_back(new Recipe(na, id, mi, nutrit, numSt, numIn, ing, ste));
        counter++;
    }
    return recipes; 
}

    //quick Sort
void quickSort(vector<Recipe*> recipes, int start, int end, string type) {
    int position; 

    if (start < end) {
        position = quickSortHelper(recipes, start, end, type);

        //sort the left portion of the vector
        quickSort(recipes, start, position - 1, type);

        //sort the right portion of the vector
        quickSort(recipes, position + 1, end, type);
    }
}

int quickSortHelper(vector<Recipe*> recipes, int start, int end, string type) {
    
    int pivot = recipes[start]->valueGetter(type);
    int count = 0; 

    for (int i = start + 1; i <= end; i++) {
        if (recipes[i]->valueGetter(type) <= pivot) {
            count++;
        }
    }

    int pivotIndex = start + count; 

    recipes[pivotIndex]->swapRecipe(*recipes[start]);

    int i = start;
    int j = end;

    while (i < pivotIndex && j > pivotIndex) { 
        while (recipes[i]->valueGetter(type) <= pivot) {
            i++;
        }
        while (recipes[j]->valueGetter(type) > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            recipes[i]->swapRecipe(*recipes[j]);
            i++;
            j--;
        }
    }
    return pivotIndex; 
}

    // heap Sort
void heapSort(vector<Recipe*> recipes, int size, string type) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(recipes, size, i, type);
    }

    for (int i = size - 1; i > 0; i--) {
        recipes[0]->swapRecipe(*recipes[i]);

        heapify(recipes, i, 0, type);
    }
}

void heapify(vector<Recipe*> recipes, int size, int index, string type) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < size && recipes[leftChild]->valueGetter(type) > recipes[largest]->valueGetter(type)) {
        largest = leftChild;
    }
    if (rightChild < size && recipes[rightChild]->valueGetter(type) > recipes[largest]->valueGetter(type)) {
        largest = rightChild;
    }
    if (largest != index) {
        recipes[largest]->swapRecipe(*recipes[index]);
        heapify(recipes, size, largest, type);
    }
}

    // print
void printSelected(vector<Recipe*> recipes, string type, int size) {
    // print all information of each recipe
    if (type == "all") {
        for (int i = 0; i < size; i++) {
            cout << "name: " << recipes[i]->getName() << endl;
            cout << "Time it takes to prepare: " << recipes[i]->getMins() << " minutes" << endl;
            cout << "Number of Steps in recipe: " << recipes[i]->getNumSteps() << endl;
            cout << "Number of Ingredients needed: " << recipes[i]->getNumIngred() << endl;
            cout << "ingredients: " << recipes[i]->getIngredients() << endl;
            cout << "Steps: " << recipes[i]->getSteps() << endl;
            cout << endl; 
        }
    }

    // print the name of each recipe 
    else if (type == "name") {
        for (int i = 0; i < size; i++) {
            cout << recipes[i]->getName() << endl;
        }
    }

    // print the name and the value that it's sorted by
    else {
        for (int i = 0; i < size; i++) {
            cout << recipes[i]->getName() << ": " << recipes[i]->valueGetter(type) << endl;
        }
    }

    cout << "There are in total " << size << " entries" << endl;

}

    // search 
void searchData(vector<Recipe*> recipes, string keyword, string sortBy) {
    
    vector<Recipe*> result; 

    for (int i = 0; i < recipes.size(); i++) {
        if (recipes[i]->getName().find(keyword) != -1) {
            result.push_back(recipes[i]);
        }
    }

    heapSort(result, result.size(), sortBy);
    printSelected(result, "all", result.size());
}
