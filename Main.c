//Needed Libraries

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Required Constant Values

#define MIN_AGE 18
#define MAX_AGE 25
#define MAX_SALES 50
#define MAX_FEEDBACKS 100
#define MAX_FEEDBACK_LENGTH 201
#define TXT_FILE "sales.txt"


//Required Global Variables

int exit1 = 1;
int newPrice;
int discount;
unsigned short no_Sales = 0;
char customer_name[40];
unsigned short numFeedbacks;

//Required Arrays dealing with buying Cars, CarsInfo

int carprice[6] = {12000, 40000, 300000, 10000, 30000, 130000};
char *carModels[6] = {
        "ToyotaCorolla",
        "FordMustang",
        "TeslaModelS",
        "HyundaiAccent",
        "HondaCRV",
        "Porsche911"};
int carYear[6] = {1962, 1964, 2012, 1990, 1995, 1964};
int carStock[6] = {10, 12, 4, 3, 66, 7};


//Required Structs dealing with Sales info and Feedbacks

typedef struct {
    long long saleAmount;
    char carName[201];
    unsigned short discPersale;
    char name[201];
    int age;
    unsigned short carAm;
    time_t time;
} Customer;

Customer customer[MAX_SALES];

typedef struct {
    unsigned short rating;
    char feedback[MAX_FEEDBACK_LENGTH];
    time_t timestamp;
} Feedback;

Feedback feed[MAX_FEEDBACKS];


//Required Functions:


//Function for Clearing up Input Buffer

void getNchar() {
    int s;
    while ((s = getchar()) != '\n' && s != EOF);
}

//Function required to pause program wherever needed

void pressCont() {
    printf("Press enter to continue");
    getchar();
}

//Function Required for Greeting Customers

void menu_greetCustomer() {
    printf("Greetings, my friend! Welcome to STH Motors. What's your name?\n");
    fgets(&customer_name, sizeof(customer_name), stdin);
    printf("Pleasure to meet you, %s.Press Enter to proceed to the menu: ", &customer_name);
    getchar();
}

//Function Required to show Menu to customers

void menu_showMenu() {
    printf(" Menu:\n");
    printf(" a View Cars\n");
    printf(" b Buy Cars\n");
    printf(" c View Sales info\n");
    printf(" e Customer/Visitors Testimonials\n");
    printf(" f Exit\n");
    printf(" Your Choice: ");
}

// Function to swap two cars
void swapCars(int i, int j) {
    int tYear = carYear[i];
    carYear[i] = carYear[j];
    carYear[j] = tYear;

    int tempPrice = carprice[i];
    carprice[i] = carprice[j];
    carprice[j] = tempPrice;

    int tempStock = carStock[i];
    carStock[i] = carStock[j];
    carStock[j] = tempStock;

    char *tempModel = carModels[i];
    carModels[i] = carModels[j];
    carModels[j] = tempModel;
}

// Function to sort cars array in descending order based on manufacturing year using bubble sort

void bubSortCars() {
    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (carYear[j] < carYear[j + 1]) {
                swapCars(j, j + 1);
            }
        }
    }
}


//Function required to show cars

void menu_showCars() {
    bubSortCars();
    printf("------------------------------------------------\n");
    printf("| %-5s | %-15s | %-5s | %-10s | %-7s |\n", "Index", "Car Model", "Year", "Price($)", "Stock");
    printf("------------------------------------------------\n");

    for (int v = 0; v < 6; v++) {
        printf("| %-5d | %-15s | %-5d | $%-9d | %-7d |\n", v + 1, carModels[v], carYear[v], carprice[v], carStock[v]);
    }

    printf("------------------------------------------------\n");
}


//Function required to show cars for buying

void menu_buyCars() {
    printf("------------------------------------------------\n");
    printf("| %-5s | %-15s | %-5s | %-10s | %-7s |\n", "Index", "Car Model", "Year", "Price($)", "Stock");
    printf("------------------------------------------------\n");

    for (int v = 0; v < 6; v++) {
        printf("| %-5d | %-15s | %-5d | $%-9d | %-7d |\n", v + 1, carModels[v], carYear[v], carprice[v], carStock[v]);
    }

    printf("------------------------------------------------\n");
}


//Function Used to store Age of Customers

void ageStore() {
    strncpy(customer[no_Sales].name, &customer_name, sizeof(customer[no_Sales].name) - 1);
    printf("Alright, what is your age, %s? ", customer[no_Sales].name);

    //Loop which runs infinitely till user enters a correct value(Positive number) as age

    while (1) {
        if (scanf("%d", &customer[no_Sales].age) != 1 || customer[no_Sales].age < 0) {
            printf("Invalid input. Please enter a valid age (a positive number).\n");
            getNchar();
        } else {
            getNchar();
            break;
        }
    }
}


//Function Required to let users buy cars

void buyCar() {

    //Variables required throughout the function
    int i;
    int q;


    //If customer is under 18, they can't buy

    if (customer[no_Sales].age < MIN_AGE && customer[no_Sales].age > 0) {
        printf("You are not eligible to make a transaction.\n");
    }

    else{

        //Loop which lets runs itself till user chooses a correct option
        while (1) {
            printf("Choose your option: ");
            scanf("%d", &i);
            getNchar();

            q = i - 1;   //Adjusting index

            if (i >= 1 && i <= 6) {
                printf("You chose:\n");
                printf("Car: %s\n", carModels[q]);
                printf("Year: %d\n", carYear[q]);
                printf("Price: $%d\n", carprice[q]);
                printf("Stock: %d\n\n", carStock[q]);

                //Loop which runs itself till user gives a valid input

                while (1) {
                    printf("How many would you like: ");
                    scanf("%hu", &customer[no_Sales].carAm);
                    getNchar();

                    if (customer[no_Sales].carAm <= carStock[q] && customer[no_Sales].carAm > 0) {
                        printf("Press enter to proceed with your transaction: \n");
                        getchar();

                        //Capturing relevant info in required struct arrays
                        strncpy(customer[no_Sales].carName, carModels[q], sizeof(customer[no_Sales].carName) - 1);
                        customer[no_Sales].carName[sizeof(customer[no_Sales].carName) - 1] = '\0';
                        customer[no_Sales].saleAmount = carprice[q] * customer[no_Sales].carAm;
                        customer[no_Sales].discPersale = 0;


                        //Ensuring calculation of price depending upon the age of the user:


                        //If costumer gets discount

                        if (customer[no_Sales].age >= MIN_AGE && customer[no_Sales].age <= MAX_AGE) {
                            customer[no_Sales].time = time(NULL);

                            //calculating discount

                            discount = carprice[q] * customer[no_Sales].carAm * (customer[no_Sales].age / 100.0);
                            newPrice = carprice[q] * customer[no_Sales].carAm - discount;
                            customer[no_Sales].saleAmount = newPrice;

                            printf("Congrats, you are eligible for a %d%% discount\n", customer[no_Sales].age);
                            printf("So your total is $%d\n", newPrice);

                            //Deducting amount of cars left
                            carStock[q] -= customer[no_Sales].carAm;
                            customer[no_Sales].discPersale = customer[no_Sales].age;
                            printf("Now we have a total of %d of this model left\n", carStock[q]);
                            no_Sales++;
                            break;

                        }
                            //If Customer does not get a discount
                        else {
                            customer[no_Sales].time = time(NULL);

                            newPrice = carprice[q] * customer[no_Sales].carAm;
                            customer[no_Sales].saleAmount = newPrice;

                            printf("You are not eligible for a discount, so your total would be $%d\n", newPrice);

                            carStock[q] -= customer[no_Sales].carAm;
                            customer[no_Sales].discPersale = 0;  // Set discount to 0

                            printf("Now we have a total of %d of this model left\n", carStock[q]);
                            no_Sales++;
                            break;
                        }
                    } else {
                        printf("Invalid input, try again!\n");
                    }
                }
                break;
            } else {
                printf("Invalid input! try again.\n");
            }
        }
    }

}



//Function to store sales details in file



//Function to store sales details in file



void saveSalestoTxt() {
    FILE *file = fopen(TXT_FILE, "a");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the entire customer array info to the file
    fwrite(customer, sizeof(Customer), no_Sales, file);

    // Close the file
    fclose(file);
}




void readSalesFromTxt() {
    FILE *file = fopen(TXT_FILE, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the entire info from the file
    no_Sales = fread(customer, sizeof(Customer), MAX_SALES, file);

    // Close the file
    fclose(file);
}


//Function required to comparesale amounts so as to put info in a certain order

int compSales(const void *a, const void *b) {
    return ((Customer *)a)->saleAmount - ((Customer *)b)->saleAmount;
}

//Function required to show sales info

void salesInfo() {
    readSalesFromTxt();
    printf("Sales Information:\n");
    qsort(customer, no_Sales, sizeof(Customer), compSales);
    printf("Debug: no_Sales = %d\n", no_Sales); // Debug print

    for (int i = 0; i < no_Sales; i++) {
        printf("Debug: Reading sale info %d\n", i); // Debug print

        printf("Sale Index: %d | Sale Amount: %lld | Car Name: %s | Discount given: %hu%% | Customer Name: %s |\nPurchase Date: %s\n",
               i + 1, customer[i].saleAmount, customer[i].carName, customer[i].discPersale, customer[i].name, ctime(&customer[i].time));
    }

    if (no_Sales == 0) {
        printf("No sales information available.\n");
    }
}


//Function Required to store Customer Feedback

void getFeedback() {
    printf("Leave your feedback (rating out of 5): ");

    // Validate the rating
    while (1) {
        if (scanf("%hu", &feed[numFeedbacks].rating) != 1 || feed[numFeedbacks].rating < 1 || feed[numFeedbacks].rating > 5) {
            printf("Invalid rating. Please enter a rating between 1 and 5: ");
            getNchar();  // Clear input buffer
        } else {
            break;
        }
    }

    getNchar();  // Clear input buffer
    printf("Leave a short comment:\n");
    fgets(feed[numFeedbacks].feedback, MAX_FEEDBACK_LENGTH, stdin);
    feed[numFeedbacks].feedback[strcspn(feed[numFeedbacks].feedback, "\n")] = '\0';  // Removing newline character
    feed[numFeedbacks].timestamp = time(NULL);
    printf("Feedback stored successfully!\n");
    numFeedbacks++;
}


//Function Required to Show Feedbacks given by Customers

void showFeedbacks() {
    if (numFeedbacks == 0) {
        printf("No feedbacks available.\n");
        return;
    }

    printf("Feedbacks:\n");

    for (unsigned short i = 0; i < numFeedbacks; i++) {

        printf("%d. Rating: %hu/5 | Comment: %s | Timestamp: %s | Car: %s\n", i + 1, feed[i].rating, feed[i].feedback, ctime(&feed[i].timestamp), customer[i].carName);
    }
}



//Final Working of the Program

int main() {
    Feedback feedbacks[MAX_FEEDBACKS];
    char choice;
    menu_greetCustomer();
    while (exit1) {
        menu_showMenu();
        scanf(" %c", &choice);
        getchar();
        switch (choice) {
            case 'a':
                menu_showCars();
                pressCont();
                break;
            case 'b':
                ageStore();
                menu_buyCars();
                buyCar();
                if (customer[no_Sales].age < MIN_AGE && customer[no_Sales].age > 0){
                    printf("\n");
                } else{
                    getFeedback();
                }
                saveSalestoTxt();
                pressCont();
                break;
            case 'c':
                salesInfo();
                pressCont();
                break;
            case 'e':
                showFeedbacks(feedbacks, numFeedbacks);
                pressCont();
                break;
            case 'f':
                printf("Thanks for coming!\n");
                exit1 = 0;
                break;
            default:
                printf("Invalid Input, try again!\n");
                break;
        }
    }


    return 0;
}
