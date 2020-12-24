/* A program that asks the user for a line of characters and integers */
/* the program then writes this list to the file File1.txt */
/* then it reads the file and only prints the integers */
/* the program also counts the numbers along with finding the sum and mean */
/* when the program reaches the EOF it will then close the file and terminate */
/* written by Jacob Lawson, November 2019 */
#include <stdio.h>

float N(float a);   //function to count the number of numbers

float sum(float a,float b); //function to sum all of the numbers

float mean(float a,float b);    //function to find the mean of the numbers

main()  //beginning of main code
{
    FILE *myFile;   //address of file
    char c;         //character variable to be input by user
    int ic;         //integer variable of character in ACSII code
    myFile=fopen("File1.txt","w");       //opening of file for writing where the line of characters will be stored


    if (myFile != NULL) {       //check that the file exists
  }
    else {
    printf("Failed to create the file.\n"); //exit status for OS that an error occurred
    return -1;
  }
    printf("\nPlease input Chars on a line, no spaces:");   //request for input line of characters by user


    while(c!='\n'){                     //finish loop if character line ends
            scanf("%c",&c);             //scan each character one by one
               fprintf(myFile,"%c",c);  //input each character into the file
    }                                   //end of while loop
    fclose(myFile);                     //finish writing to the file and close it

    float No;       //count of numbers in file
    float Total;    //sum of numbers in file
    float Average;  //mean of numbers in file


    myFile=fopen("File1.txt","r");           //open the file for where the character line is stored for reading reading
    printf("\nNumbers found in the line:\n");   //statement telling user the program is about to output the integers
     while((c = fgetc(myFile)) != EOF)          //while loop that reads one char at a time from the stored file and puts that char through the following loop until the EOF is reached
      {int ic = c - '0';
            if(ic>=0 && ic<10)      //move onto the next char in the while loop if the converted integer value is more than or equal to 0 but less than 10
            {
                printf("%d\n",ic);      //print contents of ic to screen
                No = N(No);             //increment the number of numbers using function
                Total = sum(Total,ic);  //add current integer to the previous integers using function
            }
      }  // keep looking until c is input as EOF

    printf("sum is: %.1f\n", Total);        //statement telling the user the final sum of the numbers in the stored file
    printf("no of numbers is: %.1f\n", No);     //statement telling the user the final count of the numbers in the stored file
    Average = mean(Total, No);                  //finds the average of the numbers stored by using a function
    printf("the mean is: %.2f\n", Average);     //statement telling the user the average of the numbers in the stored file
    fclose(myFile);         //finish reading from the file and close it
    return 0;               //return 0 errors on program success
}

float N(float a){       //input to function

return (a+1);       //process of increasing count of numbers in file by 1
}

float sum(float a,float b){     //input to function

return (a=a+b);     //process of totalling the numbers in file
}

float mean(float a,float b){        //input to function

return (a / b);     //process of averaging the numbers in file
}
