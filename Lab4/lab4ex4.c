#include <stdio.h>
#include <string.h>

typedef struct Recipe {
    char name[20];
    char ingredients[2][20];
} Recipe;

Recipe recipe1, recipe2, recipe3;

void pullRecipes () {
    // Omelette
    strcpy(recipe1.name, "French Omelette");
    strcpy(recipe1.ingredients[0], "2x Eggs");
    strcpy(recipe1.ingredients[1], "Salt & Pepper");

    // Egg Salad
    strcpy(recipe2.name, "Egg Salad");
    strcpy(recipe2.ingredients[0], "1x Egg");
    strcpy(recipe2.ingredients[1], "100g Lettuce");

    // Banana Bread
    strcpy(recipe3.name, "Banana Bread");
    strcpy(recipe3.ingredients[0], "2x Bananas");
    strcpy(recipe3.ingredients[1], "1x Loaf of Bread");
}

void printRecipeArray (Recipe* rb, int n) {
    for (int i=0; i < n; i++) {
        Recipe r = *rb;
        printf("----------- Recipe #%d: [ %s ] -----------\nWhat you need:\n", i+1, r.name);
        for (int j=0; j < 2; j++) {
            printf("%d) %s\n", j+1, r.ingredients[j]);
        }
        printf("\n\n");
        rb++;
    }
}

int main () {
    pullRecipes();
    Recipe Recipe_Book[] = {recipe1, recipe2, recipe3};
    printRecipeArray(Recipe_Book, 3);

    return 0;
}   