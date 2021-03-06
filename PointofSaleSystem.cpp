#include <stdio.h> // For standard input/output operation
#include <stdlib.h> // To use functions like system();
#include <time.h> // To get system date and time  /* time_t, time, ctime */

#define TaxRate 0.07
#define gratuity1 0.08 
#define gratuity2 0.1 
#define gratuity3 0.12 

void welcome(); // To answer a question and  input your name
void firstmenu(); // To select the list
void beer(int l); // To select the item and select quantity
void clear(int l); // To clear everything = 0
void end();  // To view list and all costs
void datafile(); // Save list and all costs to a bill.txt
void file_welcome(); // Logo 
void file_witbier(); // Description witbier
void file_pale_ale(); // Description pale ale beer
void file_ipa(); // Description ipa beer
void file_stout(); // Description stout beer

size_t strftime(char* ptr, size_t maxsize, const char* format, const struct tm* timeptr);
time_t rawtime; //These are global variables to store system date and time
struct tm *timeinfo; //These are global variables to store system date and time
char buffer[80]; //These are global variables to store system date and time

char choice; 
char ans[3]; 
char name[17];
char ch = 'A';
double subtotal = 0.00;
float tax = 0.00;
float total = 0.00;
float gratuity01, gratuity02, gratuity03;
int num, quantity;
int i, j = 1;

struct bier // Structure for storing beer types 
    {
        char *biername;
    };
    struct bier bname[5] = {"WITBIER", "PALE ALE", "IPA", "STOUT", "EXIT"};

struct beverage // Structure for storing beer item
    {
          char *name;
          double price;
          int count;
    };
    struct beverage menu[99][99] = {
{{"Blanche De Chambly",2.99,0},{"Hoegaarden Original White Ale",2.03,0},{"Samuel Adams White Ale",2.95,0},{"St. Bernardus Witbier",2.10,0},{"Red & White",3.52,0}},

{{"Affligem Blond",2.59,0},{"Karma",2.99,0},{"Petrus Aged Pale",4.29,0},{"Rayon Vert",3.95,0},{"Spencer Trappist Ale",3.99,0}},

{{"A Little Sumpin Wild",2.75,0},{"Bitter Monk",2.95,0},{"Galaxy White IPA",3.52,0},{"Live A Rich Life",2.99,0},{"Muffin Top",4.99,0}},

{{"Belhaven Scottish Stout",2.50,0},{"Black Scottish Stout",2.34,0},{"Echigo Stout",8.95,0},{"Pearl Necklace Oyster Stout",5.52,0},{"Samuel Smith's Organic Stout",3.49,0}}
};

// ------------------------------------------------------------------------------
// Main Function
int main()
{
    time(&rawtime); // System date and time
    timeinfo = localtime(&rawtime); // System date and time
  
    welcome();
  
  return 0; 
} 
//End Main Function
// ------------------------------------------------------------------------------

void welcome()
{
    printf("\n\n");
    file_welcome(); 

    printf("\nAre you over 20? (yes/no) : ");
    scanf("%s",&ans);
 
      if(strcmp(ans,"yes") == 0) // strcmp : Comparing strings ans = yes?
      {
         printf("\nEnter your name : ");
         scanf("%s",&name);
         system("clear"); // Clears the screen

         firstmenu();
      }
} 


void firstmenu()
{     
    char choice = ' ';

    printf("\n");
    file_welcome();

    printf("\n\t\tPlease select the beer types that you would like.  \n");
    printf("  \t\t>  >  BEER TYPES  <  <\n\n");
      for(i=0;i<5;i++)
    printf(" \t\t[%c]\t --\t%-8s\n\n",ch+i,bname[i].biername);

    
    do
    {
        printf("\nSELECT MENU (A-E) : ");
        scanf("%s", &choice);
        printf("\n");

        if(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E') 
        // when no records are found choice != A,B,C,D,E 
        {
 	     printf("   *** UNLISTED ***\n");
             printf("Please select menu again");
        }   
    }while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E');
     // terminates do... while loop if record found
    system("clear"); // Clears the screen

  switch(choice)
  {
      case 'A':  file_witbier();
		 beer(0);

              break;

      case 'B':  file_pale_ale();
		 beer(1);

              break;

      case 'C':	 file_ipa();
		 beer(2);

              break;

      case 'D':  file_stout();
		 beer(3);

              break;

      case 'E':	 end();

              break;
  } 
} 


void beer(int l)
{

    while(num = getchar())
    {
        printf("\nPlease select the beer that you would like. \n\n");
        printf("  %-10s%-34s%-14s%-10s\n","NUM", "NAME", "PRICE", "QUANTITY");
          for(i=0;i<=4;i++)
        printf("  % -10d%-34s%-17.2f%-10d\n",j+i,menu[l][i].name,menu[l][i].price,menu[l][i].count);
        printf("\n[SELECT LIST (1-5), (6)-BACK TO MAIN MENU, (7)-RESET, (8)-CHECK & EXIT]\n");

    do
    {
        printf("Enter list : ");
        scanf("%d", &num); 
 
          if(num < 1 || num > 8)
          {
	      printf("\n   *** UNLISTED ***\n");
              printf("Please select menu again\n");
          }   
    }while(num < 1 || num > 8);

  switch(num)
      {
      case 1: case 2: case 3: case 4: case 5:
              do
              {
                  printf("Enter quantity(1-17) : ");
                  scanf("%d",&quantity);
                  printf("\n");

                    if(quantity < 1 || quantity > 17)
                    {
             	        printf("Please select quantity(1-17) \n");
                    }   
              }while(quantity < 1 || quantity > 17);
               system("clear"); 

               menu[l][num-1].count+=quantity; // Calculation of total quantity
               subtotal += menu[l][num-1].price*quantity; // Calculation of subtotal
               tax = TaxRate * subtotal; // Calculation of tax
               total = tax + subtotal; // Calculation of total balance
            break;

      case 6:  system("clear");  
               firstmenu();
            break;


      case 7:  num = subtotal = 0.00;
	       system("clear"); 
	       clear(l);
            break;

       
      case 8:  system("clear"); 
               end();

      } 
  } 
} 


void clear(int l)
{
  int i;
 
  for (i = 0; i <= 5; i++){
  for (l = 0; l <= 5; l++){
    menu[i][l].count = 0;
  }
  }
} 


void end(int l)
{
    system("clear");
    datafile();

    printf("\n\t\t     WELCOME TO McSORLEY'S HOUSE");
    printf("\n--------------------------------------------------------------------\n");
    printf("  %-10s%-34s%-14s%-10s\n","NUM", "NAME", "PRICE", "QUANTITY");
        for(l=0;l<=3;l++){
        for(i=0;i<=4;i++){
    printf("  % -10d%-34s%-17.2f%-10d\n",j+i,menu[l][i].name,menu[l][i].price,menu[l][i].count);
    }
    printf("\n");
    }

    menu[l][num-1].count+=quantity; 
    tax = TaxRate * subtotal; 
    total = tax + subtotal; 

    gratuity01 = gratuity1 * subtotal; // Calculation of  8% gratuity 
    gratuity02 = gratuity2 * subtotal; // Calculation of  10% gratuity
    gratuity03 = gratuity3 * subtotal; // Calculation of  12% gratuity

    strftime(buffer,80,"\t\t\t\t\t%D   %r  \n", timeinfo);
    puts(buffer);

    printf("\t\t\t\t\t[%s]", name);
    printf("\n\t\t\t\t\t______________________");
    printf("\n\t\t\t\t\tSubtotal         $%.2f", subtotal);
    printf("\n\t\t\t\t\tTax              $%.2f\n", tax);
    printf("\n\t\t\t\t\tTotal            $%.2f\n", total);

    printf("\n\t\t\t For your convenience");
    printf("\n\t\t\t  8%, Gratuity = %.2f", gratuity01);
    printf("\n\t\t\t 10%, Gratuity = %.2f", gratuity02);
    printf("\n\t\t\t 12%, Gratuity = %.2f", gratuity03);
    printf("\n\n     ************************ THANK YOU ************************\n\n");
  
    exit(0);
} 

// ------------------------------------------------------------------------------
// File Function

void datafile(int l)
{
   FILE *file; // File pointers

   file = fopen("bill.txt", "a"); 

    fprintf(file,"\n\t\t     WELCOME TO McSORLEY'S HOUSE");
    fprintf(file,"\n--------------------------------------------------------------------\n");
    fprintf(file,"  %-10s%-34s%-14s%-10s\n","NUM", "NAME", "PRICE", "QUANTITY");
        for(l=0;l<=3;l++){
        for(i=0;i<=4;i++){
    fprintf(file,"  % -10d%-34s%-17.2f%-10d\n",j+i,menu[l][i].name,menu[l][i].price,menu[l][i].count);
    }
    fprintf(file,"\n");
    }

    fprintf(file,"\t\t\t\t\t[%s]", name);
    fprintf(file,"\n\t\t\t\t\tSubtotal     $%.2f", subtotal);
    fprintf(file,"\n\t\t\t\t\tTax          $%.2f\n", tax);
    fprintf(file,"\n\t\t\t\t\tTotal        $%.2f\n", total);

    fclose(file);
}


void file_witbier()
{
	FILE *myfile; 
	char text;
        int result;

	myfile = fopen("witbier.dat", "r");
	result = fscanf(myfile, "%c", &text);
	  while(result != EOF){
	    fprintf(stdout,"%c", text);
	    result = fscanf(myfile,"%c", &text);
	  }
    fclose(myfile);
}


void file_pale_ale()
{
	FILE *myfile;
	char text;
        int result;

	myfile = fopen("pale_ale.dat", "r");
	result = fscanf(myfile, "%c", &text);
	  while(result != EOF){
	    fprintf(stdout,"%c", text);
	    result = fscanf(myfile,"%c", &text);
	  }
    fclose(myfile);
}


void file_ipa()
{
	FILE *myfile;
	char text;
        int result;

	myfile = fopen("ipa.dat", "r");
	result = fscanf(myfile, "%c", &text);
	  while(result != EOF){
	    fprintf(stdout,"%c", text);
	    result = fscanf(myfile,"%c", &text);
	  }
    fclose(myfile);
}


void file_stout()
{
	FILE *myfile;
	char text;
        int result;

	myfile = fopen("stout.dat", "r");
	result = fscanf(myfile, "%c", &text);
       	  while(result != EOF){
	    fprintf(stdout,"%c", text);
	    result = fscanf(myfile,"%c", &text);
	  }
    fclose(myfile);
}


void file_welcome()
{
	FILE *myfile;
	char text;
        int result;

	myfile = fopen("welcome.dat", "r");
	result = fscanf(myfile, "%c", &text);
       	  while(result != EOF){
	    fprintf(stdout,"%c", text);
	    result = fscanf(myfile,"%c", &text);
	  }
    fclose(myfile);
}

