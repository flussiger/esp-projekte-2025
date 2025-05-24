//---------------------------------------------------------------------------------------------------------------------
// Cinema Program:
// In this program, you can choose between which movies to watch, which drinks, which popcorn to get, or to choose the
// recommender mode, where you can enter your budget and the system automatically calculates all possible combinations
// of movie, drink and popcorn you can get with your budget. Additionally, you are asked if you are a student or a 
// member, in which case you a get 30% or 15% discount on the movie. 
//
// Tutor: --
//
// Author: --
//---------------------------------------------------------------------------------------------------------------------
//

#include <stdio.h>
#include <string.h>

#define STUDENT_DISCOUNT 0.3
#define MEMBER_DISCOUNT 0.15



//movie struct
typedef struct _Movie_
{
  char name[100];
  double price;
} Movie;

//popcorn struct
typedef struct _Popcorn_
{
  char name[50];
  double price;
} Popcorn;

//drinks struct
typedef struct _Drink_
{
  char name[50];
  double price;
} Drink;

// Movie array sorted descending
Movie movies[] =
{
  {"Highway to Hell ESP Edition", 92.08},
  {"The Hitchhiker’s Guide to the Galaxy", 77.42},
  {"Flow", 59.74},
  {"The Place", 43.28},
  {"Interstate 60", 28.00},
  {"Truth seeking at TU Graz", 3.46}
};

// Popcorn array sorted descending
Popcorn popcorns[] =
{
  {"Spicy Popcorn", 9.99},
  {"Cheese Popcorn", 7.80},
  {"Caramel Popcorn", 5.50},
  {"Salted Popcorn", 3.50}
};

// Drinks array sorted descending
Drink drinks[] =
{
  {"Orange Juice", 2.95},
  {"Ice Tea", 2.60},
  {"Cola", 2.10},
  {"Sprite", 2.00},
  {"Water", 1.10}
};


//---------------------------------------------------------------------------------------------------------------------
/// The function gets a question when it is called, then asks for yes or no? and checks if the answer is either y or n
/// and if it isn't y or n, it repeats itself until it is y or n.
/// @param question question to ask
/// @return returns the answer

int askYesNo(const char* question) //die Idee, const *char question in Funktionen zu benutzen hab ich von ChatGPT
//aber weiß was es macht und wie es funktioniert
{
  char answer[10];
  char yes[] = "y";
  char no[] = "n";
  printf("\n%s (enter y for \"Yes\", n for \"No\")\n", question);
  printf(" > ");

  do{
    scanf(" %s", answer);

    if (strcmp(answer, yes) == 0)
    {
      return 1;
    }
    else if (strcmp(answer, no) == 0)
    {
      return 0;
    }
    else
    {
    printf("Invalid input. Please enter either y for \"Yes\" or n for \"No\"\n > ");
    }
  } while (1);
    
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
/// The function gets a min and a max number when it is called, then scans if the input number is in that range.
/// and if it isn't, it repeats itself until it is.
/// @param min min number
/// @param max max number
/// @return returns the number

int askMenuNumber(int min, int max)
{
    char answer[10];
    int number;

    do
    {
        scanf(" %s", answer);

        if (sscanf(answer, "%d", &number) == 1) //ich weiß was das "sscanf" macht, aber kannte es
        //nicht und hab es von ChatGPT
        {
            if (number >= min && number <= max)
            {
                return number;
            }
        }

        printf("Invalid input. Please enter number in [%d, %d]!\n > ", min, max);
    } while (1);

    return 0;
}


//---------------------------------------------------------------------------------------------------------------------
/// The function gets a number min and a max number when it is called,
/// asks the question, then scans if the input number is in that range.
/// and if it isn't, it repeats itself until it is.
/// @param question question to ask
/// @param min min number
/// @param max max number
/// @return returns the number

int askNumber(const char* question, int min, int max)//die Idee, const *char question in Funktionen zu benutzen
//hab ich von ChatGPT aber weiß was es macht und wie es funktioniert
{
  printf("%s (%d-%d)\n", question, min, max);
  printf(" > ");
  int choice;
  int result;
  do
  {
    result = scanf("%d", &choice);

    if (result != 1)
    {
      printf("Invalid input. Please enter number in [%d, %d]!\n > ", min, max);
    }

    if (choice < min || choice > max)
    {
      printf("Invalid input. Please enter number in [%d, %d]!\n > ", min, max);
    }
  } while (choice < min || choice > max);
  
  return choice;
}

//---------------------------------------------------------------------------------------------------------------------
/// The function gets a question when it is called,
/// asks the question (budget), and saves the input(budget) as the budget
/// and if it isn't, it repeats itself until it is.
/// @param question question to ask
/// @return returns budget
double askBudget(const char* question) //die Idee, const *char question in Funktionen zu benutzen hab ich von ChatGPT
//aber weiß was es macht und wie es funktioniert
{
  double budget;
  printf("\n%s", question);
  printf(" > ");
  scanf("%lf", &budget);

  return budget;
}

//---------------------------------------------------------------------------------------------------------------------
/// The function asks wheter you're a student or a member or none.
/// @return either STUDENT_DISCOUNT or MEMBER_DISCOUNT == 0.3 or 0.15
double getDiscountStatus(void)
{
  if (askYesNo("Are you a student?"))
  {
    return STUDENT_DISCOUNT;
  }
  if (askYesNo("Do you have a membership card?"))
  {
    return MEMBER_DISCOUNT;
  }
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
/// The function gets a price and a discount  when it is called,
/// and applies the discount.
/// @param price movie price
/// @param discount applicable discount
/// @return returns the price with discount applied
double applyDiscount(double price, double discount)
{
  return price * (1 - discount);
}

//---------------------------------------------------------------------------------------------------------------------
/// The function gets the *popcorn_index when it is called
/// and asks if user would like popcorn by calling askYesNo. If yes: prints the flavors and scans the
/// the flavor the user chose by using askNumber and saving it as *popcorn_index. If no: returns 0 and sets 
/// *popcorn_index to -1 so no popcorn is shown in the receipt.
/// @param *popcorn_index pointer to integer that stores index selected popcorn
/// @return returns the price of the popcorn chosen
double choosePopcorn(int *popcorn_index)
{
  if (askYesNo("Would you like some popcorn?") == 1)
  {
    printf("\nOur popcorn flavors:\n");
    for (int i = 0; i < 4; i++)
    {
      printf("%d. %s - €%.2f\n", i + 1, popcorns[i].name, popcorns[i].price);
    }

    *popcorn_index = askNumber("Select an option", 1, 4);
    return popcorns[*popcorn_index - 1].price;
  }
  *popcorn_index = -1;
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
/// The function asks if user would like a drink by calling askYesNo. If yes: prints the flavors and scans the
/// the flavor the user chose by using askNumber and saving it as drink_index*. If no: returns 0 and sets 
/// *drink_index to -1 so no drink is shown in the receipt.
/// @param *drink_index pointer to integer that stores index selected drink
/// @return returns the price of the drink chosen
double chooseDrink(int *drink_index)
{
  if (askYesNo("Would you like a drink?") == 1)
  {
    printf("\nOur available drinks:\n");
    for (int i = 0; i < 5; i++)
    {
      printf("%d. %s - €%.2f\n", i + 1, drinks[i].name, drinks[i].price);
    }

    *drink_index = askNumber("Select an option", 1, 5);
    return drinks[*drink_index - 1].price;
  }
  *drink_index = -1;
  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
/// The function prints the welcome screen and "menu", and movies and asks what the user wants.
/// @return nothing as it is a void function
void printMovies(void)
{
  printf("\n=== Welcome to Cinema Booking System ===\n");
  printf("\nToday in our cinema:\n");
  
  for(int i = 0; i < 6; i++)
  {
    printf("%d. %s - €%.2f\n", i + 1, movies[i].name, movies[i].price);
  }
  
  printf("\nWhat do you want?:\n");
  printf("- leave (enter 0)\n");
  printf("- to proceed choosing a movie on your own (enter 1-6)\n");
  printf("- to be recommended some movie-treats-combos according to your budget (enter 7)\n");
  printf(" > ");

}

//---------------------------------------------------------------------------------------------------------------------
/// The function handles the complete process of a purchase. When its called, it gets the int movie_choice 
/// it initializes 2 integers popcorn and drink index and 4 doubles. the final_price, which is the movie price
/// the discount, which uses the discount function to ask if a discount is possible (student/member).
/// uses applyDiscount to change final_price if discount is applicable. and uses choose popcorn and drink
/// to get the selected popcorn and drink.
/// After that it prints the receipt with the correct items (movie, discount(if possible), selected popcorn and drink
/// (if chosen). and the Total is printed. 
/// @param movie_choice the movie choice.
/// @return nothing as it is a void function
void purchaseMode(int movie_choice)
{
  Movie selected_movie = movies[movie_choice - 1];
  double final_price = selected_movie.price;
  int popcorn_index;
  int drink_index;
  double discount = getDiscountStatus();
  final_price = applyDiscount(final_price, discount);
  double selected_popcorn = choosePopcorn(&popcorn_index);
  double selected_drink = chooseDrink(&drink_index);

  printf("\n=== Your Receipt ===\n");
  printf("Movie: %s\n", selected_movie.name);
  printf("Ticket price: €%.2f\n", selected_movie.price);
  
  if (discount > 0)
  {
    printf("Applicable discount: €-%.2f\n", selected_movie.price * discount);
  }

  if (popcorn_index >= 0)
  {
    printf("Popcorn (%s): €%.2f\n",popcorns[popcorn_index - 1].name, selected_popcorn);
    final_price += selected_popcorn;
  }

  if (drink_index >= 0)
  {
    printf("Drink (%s): €%.2f\n",drinks[drink_index - 1].name, selected_drink);
    final_price += selected_drink;
  }

  printf("Total: €%.8lf\n", final_price);
  printf("\nCongratulations on your purchase! Enjoy the movie!\n");
}

//---------------------------------------------------------------------------------------------------------------------
/// The function handles the complete process of the recommender mode if the user is unsure. 
/// It initalizes 2 doubles and 2 ints. Budget uses askBudget to enter a budget. Int student and member is set to 0 
/// in the beginning. Discount uses getDiscountStatus to ask if user can get discount. 
/// If user is member it sets member to 1, if user is student, it sets student to 1. 
/// combinationfound is int that is initialized that is set to 0, and set to 1 after a combination is found. 
/// the function basically checks every single combination of movies, drinks and popcorn and checks if it is under
/// the budget and if yes, it prints the combinations, while applying discount. If not, it prints that no combinations
/// were found
/// After that it prints the receipt with the correct items (movie, discount(if possible), selected popcorn and drink
/// (if chosen). and the Total is printed. 
/// @return 2 if a combination is found. if not, returns -1.
int recommenderSystem(void)
{
  double budget = askBudget("What's your budget in €?\n");

  int student = 0;
  int member = 0;
  double discount = getDiscountStatus();

  if (discount == MEMBER_DISCOUNT)
  {
    member = 1;
    student = 0;
  }
  
  if (discount == STUDENT_DISCOUNT)
  {
    student = 1;
    member = 0;
  }

  int combinationfound = 0;
  printf("\nRecommended movies within your budget (€%.2lf):\n", budget);

  for (int movie = 0; movie < 6; movie++)
  {
    double ticket_price = movies[movie].price;

    if (student == 1)
    {
      ticket_price *= 0.7;
    }

    if (member == 1)
    {
      ticket_price *= 0.85;
    }

    for (int popcorn = 0; popcorn < 4; popcorn++)
    {
      for (int drink = 0; drink < 5; drink++)
      {
        double total_price = ticket_price + popcorns[popcorn].price + drinks[drink].price;

        if (total_price <= budget)
        {
          combinationfound = 1;
          printf("- Movie \"%s\" + %s + %s (€%.8lf)\n", movies[movie].name, popcorns[popcorn].name, drinks[drink].name,
                  total_price);
        }
      }
    }
  }

  if (combinationfound == 0)
  {
    printf("Sorry, we have no offers within your budget (€%.2f)!\n", budget);
    return -1;
  }
  return 2;
}

//---------------------------------------------------------------------------------------------------------------------
/// It prints all movies in the cinema and uses askMenuNumber to ask for a number between min max, which it returns.
/// @param min number
/// @param max number
/// @return the menu choice
int getMenuChoice(int min, int max)
{
  printMovies();

  return askMenuNumber(min, max);
}

//---------------------------------------------------------------------------------------------------------------------
/// The main function gets a number from the getMenuChoice function min = 0, max = 7. then has if/else statements
/// if number is 0, it exits. if number is a movie (1-6), it prints the chosen movie and calls the purchase mode with
/// the chosen movie. If the number is 7, it calls the recommenderSystem to print recommendations. Sets the int result
/// to the return values and if returns 2, the main returns 2, if it returns -1 (no combis found) it returns -255 (as
/// required per testcase.)
/// @return 2 or 255 depending on if cominations were found or not.
int main(void)
{
  int menu_choice = getMenuChoice(0, 7);
  
  if (menu_choice == 0)
  {
    printf("Thanks for your visit! Looking forward to seeing you again!\n");
    return 0;
  }
  else if (menu_choice > 0 && menu_choice < 7)
  {
    printf("\nChosen Film: %s\n", movies[menu_choice - 1].name);
    purchaseMode(menu_choice);
  }
  else if (menu_choice == 7)
  {
    printf("\nWelcome to the recommender system!\n");
    int result = recommenderSystem();
    if (result == 2)
    {
      return 2;
    }

    if (result == -1)
    {
      return 255;
    }
  }
  
  return 1;
}
