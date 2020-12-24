/*
       A program that fills an original matrix from a text file, the user is asked to enter the No of rows and the No of columns
       while the program defensively checks to ensure each of these numbers are between 1 and 10. Then  it finds the determinant
       of a 2x2sub matrix, with the user being asked to choose the starting row and column, once again checking that these numbers
       are within the limits of the original matrix and able to still produce a 2x2 matrix. A determinant value is calculated for
       the sub matrix which is then used to calculate the inverse matrix. For each new matrix the program asks for the user to
       enter a 1 character name, checking that the user hasn't entered a number. The program also includes detection of special
       cases such as a 1x1 original matrix and a determinant of 0.

       Created by: Jacob Lawson
       Date: 03/08/2020
*/

// required header files to sun code
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct matrix               // structures format of matrices
{
       float mat[10][10];   // to hold matrix of size up to 10x10
       int rows;            // to hold the number of rows in mat
       int cols;            // to hold the number of cols in mat
       char MatName         // to hold the one character length name of the matrix
};

// Declaration of functions
void inputMatrix(struct matrix *m1, FILE *fin);                                 // enters 1st matrix values from text file
void displayMatrix(struct matrix mat);                                          // displays the contents of matrix to the screen
float matrixDeterminant(struct matrix m1, struct matrix *m2, int *check);       // asks user for location of sub matrix and calculates its determinant
void matrixInverse(struct matrix m2, float determinant, struct matrix *m3);     // uses the determinant to calculate the inverse of the sub matrix

int main()
{
    struct matrix mat1;     // original matrix
    struct matrix mat2;     // sub matrix 2x2
    struct matrix mat3;     // inverse matrix
    int flag;               // checks type of inverse allowed by determinant
    float determinant;      // stores value of determinant
    char choice='Y';        // stores user repeat request

    do
    {
    FILE *fin;                              // pointer to file
    fin = fopen("Matrix2.txt","r");         // opens .txt file to read matrix data values from
    if (fin == NULL){                       // checks that the file exists
        printf("Error Reading File\n");
        exit (0);                           // exit code due to file failure
        }
    inputMatrix(&mat1, fin);    // calling input function
    displayMatrix(mat1);        // calling display function

    printf("\nCurrently finding the determinant\n");
            determinant = matrixDeterminant(mat1,&mat2,&flag);      // finding the determinant
            if (flag == 0){                                         // matrix condition check
                printf("The determinant is %.2f for matrix %c\n", determinant, ((mat2).MatName));
                displayMatrix(mat2);                                // displays sub matrix

                printf("\nCurrently finding the inverse\n");
                matrixInverse(mat2, determinant, &mat3);            //finding the inverse

                printf("The inverse of matrix %c is matrix %c:\n",((mat2).MatName), ((mat3).MatName));
                displayMatrix(mat3);                                // displays inverse matrix
            }
            else if (flag == 1){                                    // matrix condition check
                printf("The determinant and the inverse do not exist!\n\n");
            }

            else if (flag == 2){                                    // matrix condition check
                displayMatrix(mat2);                                // displays sub matrix
                printf("The determinant  = 0 and the inverse does not exist!\n\n");
            }

            fclose(fin);                                            // close file for reading

    fflush(stdin);
    printf("would you like to try again? Y/N\n");   // asks whether user wants to repeat the program
    choice=getchar();                               // user enters char variable

    }while(choice == 'Y' ||choice == 'y');                    // checks whether user wants to repeat the program
}

/************************************************************************************/
/* function to input the contents of the matrix from the pre set .txt file location */
/************************************************************************************/
void inputMatrix(struct matrix *m1, FILE *fin)
{
    int m,n = 0;                    // for loop incrementing row and column counters
    ((*m1).MatName) = '1';          // pointer to variable to store Matrix 1 name
    fflush(stdin);                  // clears stored variable value to allow user to re-run the program
    ((*m1).rows) = 0;               // pointer to variable to store Matrix 1 row count
    (m1->cols) = 0;                 // pointer to variable to store Matrix 1 column count

    // checks matrix name is entered correctly
    while((*m1).MatName >= '0' && (*m1).MatName <= '9'){
        printf("Enter a one character name of this matrix: ");          // enter matrix name
        scanf("%c",&((*m1).MatName));                                   // user enters matrix name
        if((*m1).MatName >= '0' && (*m1).MatName <= '9'){               // name checker
            fflush(stdin);                                              // clears stored variable value
            printf("Matrix Name must be A - Z and either capital or lower case \n");
        }
     }
    // checks row number was entered correctly
    while (((*m1).rows)<1 || ((*m1).rows)>10){
        printf("Please enter the number of rows in the matrix:  ");     // enter rows
        scanf("%d",&((*m1).rows));                                      // user enter number of rows
        if(((*m1).rows)<1 || ((*m1).rows)>10)                           // row checker
            printf("Matrix row count must be between 1 and 10 inclusive \n");
    }
    // checks column number was entered correctly
    while ((m1->cols)<1 || (m1->cols)>10){
        printf("Please enter the number of columns in the matrix:  ");  // enter columns
        scanf("%d",&(m1->cols));                                        // user enters number of columns
        if((m1->cols)<1 || (m1->cols)>10)                               // column checker
            printf("Matrix column count must be between 1 and 10 inclusive \n");
    }

    printf("Now entering the contents of the matrix, one row at a time\n");

    fin = fopen ("Matrix2.txt","r");
    for(m=0; m<(*m1).rows; m++)                                         // enter elements one row at a time
     {
        for(n=0; n<(*m1).cols; n++)                                     // enter elements one column at a time
            {

            fscanf(fin, "%f,",&((*m1).mat[m][n]));                      // reads from file and stores number in matrix
            }
    }
    fclose(fin);                                                        // close file for reading
}
/**************************************************/
/* function to display the contents of the matrix */
/**************************************************/
void displayMatrix(struct matrix mat)
{
    int m,n;                                        // for loop incrementing row and column counters
    int MatArea = (mat).rows * (mat.cols);          // stores area for matrix

    if (MatArea = 1){                               // checks for condition of a 1x1 matrix
        for(m=0; m<mat.rows; m++)                   // increments matrix row number
        {
            printf("Row %d:  ",m);                  // prints current row number
            for(n=0; n<mat.cols; n++)               // increments matrix column number
            {
                printf("\t%4.2f",mat.mat[m][n]);    // prints matrix to screen
            }
            printf("\n");
        }
    }
    else{
        for(m=0; m<mat.rows; m++)                   // increments matrix row number
        {
            printf("Row %d:  ",m);                  // prints current row number
            for(n=0; n<mat.cols; n++)               // increments matrix column number
            {
                printf("\t%8.2f",mat.mat[m][n]);    // prints matrix to screen
            }
            printf("\n");
        }
    }
}

/***********************************************************/
/* function to find the determinant of a subset 2x2 matrix */
/***********************************************************/
float matrixDeterminant(struct matrix m1, struct matrix *m2, int *check)
{
    int m,n,x,y = 0;                        // Matrix dimension limiter variables
    int MatCondition = 0;                   // stores condition of Matrix variable
    int MatArea = 0;                        // stores area for matrix
    float DetXMat;                          // stores sub matrix determinant
    ((*m2).MatName) = '1';                  // pointer to variable to store Matrix 2 name
    fflush(stdin);                          // clears stored variable value to allow user to re-run the program
    ((*m2).rows) = 2;                       // pointer to variable to store Matrix 2 row count
    (m2->cols) = 2;                         // pointer to variable to store Matrix 2 column count

        MatArea = (m1).rows * (m1.cols);                                    // calculates area of Matrix 1

        // checks matrix name is entered correctly
        while((*m2).MatName >= '0' && (*m2).MatName <= '9'){
            printf("Enter a one character name of this matrix: ");          // enter matrix name
            scanf("%c",&((*m2).MatName));                                   // user enters matrix name
            if((*m2).MatName >= '0' && (*m2).MatName <= '9'){               // user enters matrix name
                fflush(stdin);                                              // clears stored variable value
                printf("Matrix Name must be A - Z and either capital or lower case \n");
            }
        }
        if (MatArea == 1)                                                   // checks for 1x1 Matrix 1 condition
        {
            ((*m2).rows) = 1;                                               // set Matrix 2 row count to 1
            (m2->cols) = 1;                                                 // set Matrix 2 column count to 1
            MatCondition = 0;
            *check = MatCondition;                                          // pointer to variable to store Matrix condition
            DetXMat = m1.mat[0][0];
            (*m2).mat[0][0] = m1.mat[0][0];                                 // calculates determinant of Matrix
            printf("DetXMat is %.2f\n", DetXMat);
        }
        if ((MatArea > 1 && MatArea < 4 )||((m1.cols) == 1 && MatArea > 4))
        {
            MatCondition = 1;                                               // sets condition of Matrix
            *check = MatCondition;                                          // pointer to variable to store Matrix condition
        }
        if (MatArea >= 4)
        {
            ((*m2).rows) = 2;                                               // set Matrix 2 row count to 2
            (m2->cols) = 2;                                                 // set Matrix 2 row count to 2
            MatCondition = 0;                                               // sets condition of Matrix
            *check = MatCondition;                                          // pointer to variable to store Matrix condition
            m = -1;                                                         // ensures row position while loop
            n = -1;                                                         // ensures column position while loop
            x = (m1).rows - 2;                                              // row limits for sub matrix
            y = (m1).cols - 2;                                              // column limits for sub matrix

            // checks row number was entered correctly
            while (m<0 || m>x){
                printf("Please enter the row starting location of the sub matrix between 0 and %d \n", x);
                scanf("%d",&m);         // enter rows
                if(m<0 || m>x)          // row checker
                    printf("Sub matrix row start point must be between 0 and %d \n", x);
            }
            printf("Row starting position is: %4.d \n", m);

            // checks column number was entered correctly
            while (n<0 || n>y){
                printf("Please enter the column starting location of the sub matrix between 0 and %d \n", y);
                scanf("%d",&n);         // enter columns
                if(n<0 || n>y)          // column checker
                    printf("Sub matrix column start point must be between 0 and %d \n", y);
            }
            printf("Column starting position is: %4.d \n", n);

            printf("\nEntering the 4 elements of matrix %c \n", ((*m2).MatName));
            // fills contents of 2x2 sub matrix
            (*m2).mat[0][0] = m1.mat[m][n];
            (*m2).mat[0][1] = m1.mat[m][n+1];
            (*m2).mat[1][0] = m1.mat[m+1][n];
            (*m2).mat[1][1] = m1.mat[m+1][n+1];

            DetXMat = ((*m2).mat[0][0]*(*m2).mat[1][1] - (*m2).mat[1][0]*(*m2).mat[0][1]);  // calculates determinant of Matrix

            if (DetXMat = 0){                                                               // determinant special condition checker
                MatCondition = 2;                                                           // sets condition of Matrix
                *check = MatCondition;                                                      // pointer to variable to store Matrix condition
                return ((*m2).mat[0][0]*(*m2).mat[1][1] - (*m2).mat[1][0]*(*m2).mat[0][1]); // calculates determinant of Matrix and returns it to main
            }
            else {
                MatCondition = 0;                                                           // sets condition of Matrix
                *check = MatCondition;                                                      // pointer to variable to store Matrix condition
                return ((*m2).mat[0][0]*(*m2).mat[1][1] - (*m2).mat[1][0]*(*m2).mat[0][1]); // calculates determinant of Matrix and returns it to main
            }
        }
return DetXMat;                 // returns value of the determinant to main
}
/*********************************************************/
/* function to find the inverse of the subset 2x2 matrix */
/*********************************************************/
void matrixInverse(struct matrix m2, float determinant, struct matrix *m3)
{

    float m31D = (1 / determinant);             // calculates 1/determinant modifier
    int m2Area = (m2).rows * (m2.cols);         // calculates area of Matrix 2
    fflush(stdin);                              // clears stored variable value to allow user to re-run the program
    ((*m3).MatName) = '1';                      // pointer to variable to store Matrix 3 name

    // checks matrix name is entered correctly
    while((*m3).MatName >= '0' && (*m3).MatName <= '9'){
        printf("Enter a one character name of this matrix: ");          // enter matrix name
        scanf("%c",&((*m3).MatName));                                   // user enters matrix name
        if((*m3).MatName >= '0' && (*m3).MatName <= '9'){               // user enters matrix name
            fflush(stdin);                                              // clears stored variable value
            printf("Matrix Name must be A - Z and either capital or lower case \n");
        }
     }
    if (m2Area == 1){                                                   // checks for 1x1 Matrix 2 condition
            ((*m3).rows) = 1;                                           // set Matrix 3 row count to 1
            (m3->cols) = 1;                                             // set Matrix 3 column count to 1
            (*m3).mat[0][0] = (m2).mat[0][0] *m31D;                     // calculates inverse matrix
    }
    else {
            ((*m3).rows) = 2;                                           // set Matrix 3 row count to 2
            (m3->cols) = 2;                                             // set Matrix 3 column count to 2
            // calculates inverse matrix
            (*m3).mat[0][0] = (m2).mat[1][1] * +1 *  m31D;
            (*m3).mat[0][1] = (m2).mat[0][1] * -1 *  m31D;
            (*m3).mat[1][0] = (m2).mat[1][0] * -1 *  m31D;
            (*m3).mat[1][1] = (m2).mat[0][0] * +1 *  m31D;

            printf("\n");
    }
}
