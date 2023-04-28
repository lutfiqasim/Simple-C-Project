/*
****Lutfi Qasim
****Student_Num:1202064
****lecture section :6----------lab section: 11
*/
#include <stdio.h>
#include <string.h>
void calculateFINAL(double arr1[][5], double arr2[], size_t size);                                      //Calculate final Grade from scores
void Menu(int ID[], char Name[][50], double Score[][5], double Final_Grade[], size_t size);             //Dispaly Menu
void AscendingIDS(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size);     //Sorting by IDS score in asscending order
void AscendingNames(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size);   //Sorting by Names score in asscending order
void descendingscores(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size); //Sorting by final grade score in descending order
void searchbyID(int Id[], double Score[], size_t size);                                                 //Gets Scores by Id number
void searchbyname(char Name[][50], double score[], size_t size);                                        //Gets Scores by Names
void swap(int Id[], char Name[][50], double Score[][5], double Final_Grade[], int min, int i);          // swap values (Note you may not need to do two swapping functions make sure)
void printinfile(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size);      //if user wants to save his changes inside a file
void print(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size);            //write this function to display the new sorted array
int main()
{
    //parallel arrays where elements[Number]represent the same person informations for each array
    int const size = 1000;
    int IDs[size];
    char Names[size][50];
    double Scores[size][5];
    char File_Name[50];
    double Final_Grade[size];
    const char PrintInFile[50] = {"record for student.txt"};//name of the file that needs to be written in
    char FULL_Data[500];
    FILE *input;
    FILE *output;
    printf("\nEnter the name of the file which contains students data(note:with the \".txt\" extention):");
    gets(File_Name);
    input = fopen(File_Name, "r"); //open entered file text to be read from.
    while (input == NULL)          // Making the user decide if he wants to open a file or exit program to create a "file.txt"
    {
        printf("File wasn't found or (you have to add the \".txt\"extention to it),try again or type \"exit\" to close the program: ");
        gets(File_Name);
        if (strcmp(File_Name, "exit") == 0) // exit the program if "exit" was entered as the file name(Note:if exit.txt was entered it would keep going)
        {
            printf("%50s\n", "Exited the program");
            return 0;
        }
        else
            input = fopen((File_Name), "r"); //open entered file text to be read from.
    }
    output = fopen(PrintInFile, "w"); //openning required file"record for student.txt" and prepare it to be written in.
    int i, k = 0;
    char *tok;
    int EF = feof(input);
    for (i = 0; (!EF); i++)
    {
        fgets(FULL_Data,500,input);//gets the whole line for a student Note:expecting the line not to be more than 500 characters
            tok = strtok(FULL_Data, "$");// splites the line into IDs grades ETC... using the '$' character
            sscanf(tok, "%d", &IDs[i]);
            tok = strtok(NULL, "$");
            strcpy(Names[i],tok);
            tok = strtok(NULL, "$");
            k = 0;
            while (k < 5) //counting an only 5 grades to be entered as requiered
            //(1-Assignments 2- quizzes 3- Midterm 4- Practical exam 5-Final exam)grades
            {
                sscanf(tok, "%lf", &Scores[i][k]);
                k++;
                tok = strtok(NULL, "$");
            }
            EF = feof(input);// rechecking if the End of file is reached

    }
    fclose(input);
    int length = i;
    calculateFINAL(Scores, Final_Grade, length);
    fprintf(output, "ID\t\tSTUDENT.Name\tAssignments grade\t\tquizzes greade\tMidterm grade\tPractical exam grade\t Final exam grade\t Final Grade\n");
    fprintf(output, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int j = 0;
    for (i = 0; i < length; i++)
    {
        fprintf(output, "%d\t|%s\t", IDs[i], Names[i]);
        for (j = 0; j < 5; j++)
        {
            fprintf(output, "|");                           //prints"|" to divide each column in order to demonstrate it better
            fprintf(output, "\t%4.2f\t\t\t", Scores[i][j]); // printing the five grades inside of the record file+the Final grade
        }
        fprintf(output, "\t|%4.2f", Final_Grade[i]);//prints final score

        fprintf(output, "\n");
    }
    fclose(output);
    Menu(IDs, Names, Scores, Final_Grade, length);//calling the menu inorder to ask user to do some sorting-searching

    return 0;
}
void calculateFINAL(double arr1[][5], double arr2[], size_t size)// calculates final score using the given equation
{
    int k=0;
    for (int i = 0; i < size; i++)
    {
        k = 0;
        arr2[i] = ((arr1[i][k]) * .15) + (arr1[i][++k] * .15) + (arr1[i][++k] * .25) + (arr1[i][++k] * .1) + (arr1[i][++k] * .35);
    }
}
void Menu(int ID[], char Name[][50], double Score[][5], double Final_Grade[], size_t size)
{
    int userchoice;
    do
    {
        printf("\nPlease chose an option\n");
        printf("1-Sort data in ascending order according to students IDs and then display it.\n");
        printf("2-Sort data in ascending order according to students names and then display it.\n");
        printf("3-Sort data in descending order according to students scores and then display it.\n");
        printf("4-Ask the user to enter a student ID and display his score\n");
        printf("5-Ask the user to enter a student name and display his score\n");
        printf("6-Exit the program\n\n: ");
        scanf("%d", &userchoice);
        switch (userchoice)
        {
        case 1:
            AscendingIDS(ID, Name, Score, Final_Grade, size); //calling function to sort arrays according to IDS in an ascending order
            break;
        case 2:
            AscendingNames(ID, Name, Score, Final_Grade, size); //calling function to sort arrays according to NAMES in an ascending order
            break;
        case 3:
            descendingscores(ID, Name, Score, Final_Grade, size); //calling function to sort arrays according to FINAL SCORES in an descending order
            break;
        case 4:
            searchbyID(ID, Final_Grade, size); //FINDS the final score of a chosen student according to his ID NUMBER
            break;
        case 5:
            searchbyname(Name, Final_Grade, size); //FINDS the final score of a chosen student according to his NAME
            break;
        case 6:
            printf("\nTHANKS FOR USING THIS PROGRAM\n");
            break;
        default:
            printf("\nPlaese enter a valid choice Number or 6 to exit\n");
            break;
        }
    } while (userchoice != 6);
}
void swap(int Id[], char Name[][50], double Score[][5], double Final_Grade[], int min, int i)
{
    double temp3;
    //swapping the Id positions
    int temp1 = Id[i];
    Id[i] = Id[min];
    Id[min] = temp1;
    //swapping the Names
    char temp[50];
    strcpy(temp, Name[i]);
    strcpy(Name[i], Name[min]);
    strcpy(Name[min], temp);
    //swapping scores values for each column
    for (int j = 0; j < 5; j++)
    {
        temp3 = Score[i][j];
        Score[i][j] = Score[min][j];
        Score[min][j] = temp3;
    }
    //swapping Final Grades
    temp3 = Final_Grade[i];
    Final_Grade[i] = Final_Grade[min];
    Final_Grade[min] = temp3;
}
void AscendingIDS(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size)
{
    int min_index;
    for (int i = 0; i < size - 1; i++)
    {
        // selection sort assign the first id as smallest and then
        // go through the id array
        min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (Id[j] < Id[min_index]) // if any id is smaller than the assigned one assign it as smallest
            {
                min_index = j;
            }
        }
        swap(Id, Name, Score, Final_Grade, min_index, i);
    }
    print(Id, Name, Score, Final_Grade, size);
    int answer;
    printf("\nWould you like to save the result,if yes enter (1) else enter (0)");
    scanf("%d", &answer);
    if (answer == 1)
    {
        printinfile(Id, Name, Score, Final_Grade, size);
    }
}
void AscendingNames(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size)
{
    int min_index;
    for (int i = 0; i < size - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if ((strcmp(Name[j], Name[min_index])) == -1)
            {
                min_index = j;
            }
        }
        swap(Id, Name, Score, Final_Grade, min_index, i);
    }
    print(Id, Name, Score, Final_Grade, size);
    int answer;
    printf("\nWould you like to save the result,if yes enter (1) else enter (0)");
    scanf("%d", &answer);
    if (answer == 1)
    {
        printinfile(Id, Name, Score, Final_Grade, size);
    }
}
void descendingscores(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size)
{
    int max_index;
    for (int i = 0; i < size - 1; i++)
    {
        max_index = i; //sets maximum score to first score
        for (int k = i + 1; k < size; k++)
        {
            if (Final_Grade[k] > Final_Grade[max_index])
            {
                max_index = k; //if any score is greater than previous max set it to max score
            }
        }
        swap(Id, Name, Score, Final_Grade, max_index, i); //calling swap function
    }
    print(Id, Name, Score, Final_Grade, size); //calling printing function
    int answer;
    //asking user if he would like to save current result to a text file or not.
    printf("\nWould you like to save the result,if yes enter (1) else enter (0)");
    scanf("%d", &answer);
    if (answer == 1)
    {
        printinfile(Id, Name, Score, Final_Grade, size);
    }
}
void print(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size)
{
    printf("ID\t\tSTUDENT.Name\tAssignments grade\t\tquizzes greade\tMidterm grade\tPractical exam grade\t Final exam grade\t Final Grade\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d\t|%s\t", Id[i], Name[i]);
        for (int j = 0; j < 5; j++)
        {
            printf("|");
            printf("\t%4.2f\t\t\t", Score[i][j]);
        }
        printf("\t|%4.2f", Final_Grade[i]);
        printf("\n");
    }
}
void printinfile(int Id[], char Name[][50], double Score[][5], double Final_Grade[], size_t size)
{
    char filename[50];
    printf("Enter a name of a file you would like to save the result in with\".txt\": ");
    scanf("%s", filename); //gets file name from user
    FILE *output;
    output = fopen(filename, "w");
    fprintf(output, "ID\t\tSTUDENT.Name\tAssignments grade\t\tquizzes greade\t\tMidterm grade\tPractical exam grade\t Final exam grade\t Final Grade\n");
    fprintf(output, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        fprintf(output, "%d\t|%s\t", Id[i], Name[i]);
        for (j = 0; j < 5; j++)
        {
            fprintf(output, "|");                          //prints"|" to divide each column in order to demonstrate it better
            fprintf(output, "\t%4.2f\t\t\t", Score[i][j]); // printing the five grades inside of the record file+the Final grade
        }
        fprintf(output, "\t|%4.2f", Final_Grade[i]);

        fprintf(output, "\n");
    }
    fclose(output);
}
void searchbyID(int Id[], double Score[], size_t size)
{
    int ent_ID, found = 0, i = 0;
    printf("Please enter the Id of the student whom you want his scores to be displayed:");
    scanf("%d", &ent_ID);
    while (!found && i < size) //if !found is=1(which represents true) and i<size search for each name in the array
    {
        if (Id[i] == ent_ID)
            found = 1;
        else
            i++;
    }
    if (found == 1)
    {
        printf("\nThe score of student with IDnum:%d is :%4.2f\n\n", ent_ID, Score[i]);
    }
    else
        printf("\nThe entered Id was not found please check again\n");
}
void searchbyname(char Name[][50], double score[], size_t size)
{
    char Key[50];
    printf("Please enter the student name you would like to get the scores for:");
    getchar(); //gets The new line character in order for the gets function to skip it and ask for the user input
    gets(Key);
    int found = 0, i = 0;
    while ((!found) && i < size) // if !found is=1(which represents true) and i<size search for each name in the array
    {
        if ((strcmp(Key, Name[i])) == 0) // if an equal name is found but found =1, so that !found==0(false)
            found = 1;
        else
            i++;
    }
    if (found == 1)//when found the value turns into 1 so that the condition is applied
    {
        printf("\nThe score of student with Name:%s is :%4.2f\n\n", Key, score[i]);// prints the score value by value
    }
    else
        printf("\nThe entered Name was not found please check again\n\n");
}
