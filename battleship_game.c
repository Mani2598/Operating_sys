#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct playerInfo
{
    int id;
    char playerName[50];
    char date[10];
    int score;
    int hasPlayedtheGame;
    int isBoardPopulated;
    int isBoardViewed;
    int isBoardReinitialized;
    int isBoardInitialized;
};

void displayMenu();
void exitGame(char*,char*,char*,char*,char*,char*);
//This function displays the various menu options that the user can select from.
void displayMenu()
{
    printf("Please Select one option from the following menu Items:\n");
    printf("1. Enter Player Information.\n");
    printf("2. Initialize the Board.\n");
    printf("3. Populate the Board.\n");
    printf("4. Play the Game.\n");
    printf("5. Print the Board.\n");
    printf("6. Score Board.\n");
    printf("7. Exit\n");
}

//This function will take all the dynamically allocated parameters from the main function and releases their memory and exits the game.
void exitGame(char *board, char *carrierLocations, char *battleShipLocations, char *cruiserLocations, char *submarineLocations, char *destroyerLocations)
{
    //free dynamically allocated values.
    free(board);
    free(carrierLocations);
    free(battleShipLocations);
    free(cruiserLocations);
    free(submarineLocations);
    free(destroyerLocations);
    exit(0);
}

void savePlayerInfo(struct playerInfo *info);
//This Function saves the Player Information onto a file.
//Accepts pointer to struct of type playerInfo as an input parameter
void savePlayerInfo(struct playerInfo *info)
{
    FILE *fp = fopen("./shipProgramFile.txt", "a");
    if (!fp)
    {
        printf("some exception occured when trying to create a new file.\n");
        exit(0);
    }
    fprintf(fp, "%d %s %s %d\n", info->id, info->playerName, info->date, info->score);
    fclose(fp);
}

void playerInfo(struct playerInfo *info,int currentPlayerId);
//This Function will initialize the player with the user information from the stdinput/output.
//First Parameter is of type pointer to struct of type playerInfo.
//Second Parameter is an int with an ID to uniquely identify a player.
void playerInfo(struct playerInfo *info, int currentPlayerId)
{
    printf("Enter PlayerName:\n");
    scanf("%s", &info->playerName);
    printf("Enter Date:\n");
    scanf("%s", &info->date);
    info->id = currentPlayerId;
    info->score = 100;
    info->isBoardInitialized = 0;
    info->isBoardViewed = 0;
    info->isBoardReinitialized = 0;
    info->hasPlayedtheGame = 0;
    info->isBoardPopulated = 0;
    //savePlayerInfo(info);
}

void scoreBoard();
//This function will read from the file in which players information is saved and displays all the players information.
void scoreBoard()
{
    FILE *fp1 = fopen("./shipProgramFile.txt", "r");
    if (!fp1)
    {
        printf("some exception occured when trying to create a new file.\n");
        exit(0);
    }
    struct playerInfo *tempStore = (struct playerInfo *)malloc(sizeof(struct playerInfo));
    while ((fscanf(fp1, "%d %s %s %d\n", &tempStore->id, &tempStore->playerName, &tempStore->date, &tempStore->score)) > 0)
    {
        printf("Player Name: %s\nDate: %s\nScore: %d\n", tempStore->playerName, tempStore->date, tempStore->score);
    }
    fclose(fp1);
    free(tempStore);
}

void populateGameBoard(char *board,char *carrierLocations, char *battleShipLocations, char *cruiserLocations, char *submarineLocations, char *destroyerLocations);
//This function will initialize the gameboard with ships placed at random positions.
//First Parameter is a pointer to 2D array of the board.
//Second Parameter is a Pointer to 2D array to identify the location of carrier ship in the gameBoard.
//Third parameter to identify the location of battleShip in the gameboard.
//Fourth parameter to identify the location of CruiserShip in the gameboard.
//Fifth parameter to identify the location of subMarine in the gameboard.
//Sixth parameter to identify the location of destroyerShip in the gameboard.
void populateGameBoard(char *board, char *carrierLocations, char *battleShipLocations, char *cruiserLocations, char *submarineLocations, char *destroyerLocations)
{
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            *(board + row * 10 + col) = ' ';
        }
    }
    int orientation = rand() % 2;
    int value = rand() % 10;
    initializeShipLocation(board, carrierLocations, 5, orientation, value);
    initializeShipLocation(board, battleShipLocations, 4, orientation, (value + 1) % 10);
    initializeShipLocation(board, cruiserLocations, 3, orientation, (value + 2) % 10);
    initializeShipLocation(board, submarineLocations, 3, orientation, (value + 3) % 10);
    initializeShipLocation(board, destroyerLocations, 2, orientation, (value + 4) % 10);
}


void initializeShipLocation(char *board, char *shipType, int size, int orientation, int value);
//Function is used to place a ship at a particular location in the gameBoard
//First parameter is the pointer to 2D array of gameboard
//Second parameter is pointer to 2D array of a particular ship location
//Third parameter is the size of the ship
//Fourth parameter is the orientation whether to initialize the ship horizantally or dynamically
//Fifth parameter is an random starting int value
void initializeShipLocation(char *board, char *shipType, int size, int orientation, int value)
{
    if (orientation == 0)
    {
        int columnValue = rand() % (10 - size);
        int rowValue = value;
        for (int i = 0; i < size; i++)
        {
            *(board + rowValue * 10 + columnValue) = 'X';
            *(shipType + i * size + 0) = rowValue;
            *(shipType + i * size + 1) = columnValue;
            columnValue = columnValue + 1;
        }
    }
    else
    {
        int rowValue = rand() % (10 - size);
        int columnValue = value;
        for (int i = 0; i < size; i++)
        {
            *(board + rowValue * 10 + columnValue) = 'X';
            *(shipType + i * size + 0) = rowValue;
            *(shipType + i * size + 1) = columnValue;
            rowValue = rowValue + 1;
        }
    }
}

void displayBoard(char *board);
//Function used to display the gameboard to the user.
//Accepts the pointer to 2D array of gameboard to be displayed.
void displayBoard(char *board)
{
    printf("  ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", i);
    }
    int currentCharValue = 65;
    for (int row = 0; row < 10; row++)
    {
        printf("\n");
        printf("%c ", currentCharValue);
        for (int col = 0; col < 10; col++)
        {
            printf("%c ", *(board + row * 10 + col));
        }
        currentCharValue = currentCharValue + 1;
    }
    printf("\n");
}

void playGame(struct playerInfo *info, char *board, char *carrierLocations, char *battleShipLocations, char *cruiserLocations, char *submarineLocations, char *destroyerLocations);
//Function is used to play the game
//Accepts various input parameters like player info board info and various positions of each ship in the gameboard
void playGame(struct playerInfo *info, char *board, char *carrierLocations, char *battleShipLocations, char *cruiserLocations, char *submarineLocations, char *destroyerLocations)
{
    char *newArrayList = (char *)calloc(10 * 10, sizeof(char));
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            *(newArrayList + row * 10 + col) = ' ';
        }
    }
    int isCarrierKilled = 0;
    int isBattleShipKilled = 0;
    int isCruiserKilled = 0;
    int isSubMarineKilled = 0;
    int isDestroyerKilled = 0;
    int totalNoofShipsKilled = 0;
    while (totalNoofShipsKilled != 5)
    {
        printf("Enter your match:");
        int rowNumber;
        int columnNumber;
        char match[2];
        scanf("%s", &match);
        rowNumber = (int)match[0] - 65;
        columnNumber = (int)match[1] - 48;
        if (*(board + rowNumber * 10 + columnNumber) == ' ')
        {
            info->score -= 1;
            *(newArrayList + rowNumber * 10 + columnNumber) = 'M';
            displayBoard(newArrayList);
        }
        else
        {
            int isFound = 0;
            *(newArrayList + rowNumber * 10 + columnNumber) = 'H';
            if (isFound == 0 && isCarrierKilled == 0)
            {
                if (checkIfCurrentCarrierIsHit(carrierLocations, 5, rowNumber, columnNumber) == 1)
                {
                    isFound = 1;
                    if (checkIfShipIsSunk(carrierLocations, 5) == 1)
                    {
                        printf("Carrier ship is Sunk.\n");
                        totalNoofShipsKilled += 1;
                        isCarrierKilled = 1;
                    }
                    else
                    {
                        printf("You have hit a Carrier Ship.\n");
                    }
                }
            }
            if (isFound == 0 && isBattleShipKilled == 0)
            {
                if (checkIfCurrentCarrierIsHit(battleShipLocations, 4, rowNumber, columnNumber) == 1)
                {
                    isFound = 1;
                    if (checkIfShipIsSunk(battleShipLocations, 4) == 1)
                    {
                        printf("Battleship is Sunk.\n");
                        totalNoofShipsKilled += 1;
                        isBattleShipKilled = 1;
                    }
                    else
                    {
                        printf("You have hit a BattleShip.\n");
                    }
                }
            }
            if (isFound == 0 && isCruiserKilled == 0)
            {
                if (checkIfCurrentCarrierIsHit(cruiserLocations, 3, rowNumber, columnNumber) == 1)
                {
                    isFound = 1;
                    if (checkIfShipIsSunk(cruiserLocations, 3) == 1)
                    {
                        printf("Cruiser Ship is Sunk.\n");
                        totalNoofShipsKilled += 1;
                        isCruiserKilled = 1;
                    }
                    else
                    {
                        printf("You have hit a CruiserShip.\n");
                    }
                }
            }
            if (isFound == 0 && isSubMarineKilled == 0)
            {
                if (checkIfCurrentCarrierIsHit(submarineLocations, 3, rowNumber, columnNumber) == 1)
                {
                    isFound = 1;
                    if (checkIfShipIsSunk(submarineLocations, 3) == 1)
                    {
                        printf("Submarine is Sunk.\n");
                        totalNoofShipsKilled += 1;
                        isSubMarineKilled = 1;
                    }
                    else
                    {
                        printf("You have hit a Submarine.\n");
                    }
                }
            }
            if (isFound == 0 && isDestroyerKilled == 0)
            {
                if (checkIfCurrentCarrierIsHit(destroyerLocations, 2, rowNumber, columnNumber) == 1)
                {
                    isFound = 1;
                    if (checkIfShipIsSunk(destroyerLocations, 2) == 1)
                    {
                        printf("Destroyer Ship is Sunk.\n");
                        totalNoofShipsKilled += 1;
                        isDestroyerKilled = 1;
                    }
                    else
                    {
                        printf("You have hit a Destroyer.\n");
                    }
                }
            }
            displayBoard(newArrayList);
        }
    }
    printf("You have killed all the ships.\n");
    savePlayerInfo(info);
    free(newArrayList);
}

int checkIfCurrentCarrierIsHit(char *carrierLocations, int size, int rowNumber, int columnNumber);
//Function used to determine which type of ship the user has hit and if it is hit it mark that value as deleted.
//First parameter is the ship location on the gameboard
//Second parameter is the size of the ship we are trying to find if it is a hit or miss on the board
//Third and Fourth parameters are the rowNumber and columnNumber of the user entered value
//returns an int value to determine if its a hit or miss. 0 indicates miss and 1 indicates hit.
int checkIfCurrentCarrierIsHit(char *carrierLocations, int size, int rowNumber, int columnNumber)
{
    for (int i = 0; i < size; i++)
    {
        if (*(carrierLocations + i * size + 0) == rowNumber && *(carrierLocations + i * size + 1) == columnNumber)
        {
            *(carrierLocations + i * size + 0) = 10;
            *(carrierLocations + i * size + 1) = 10;
            return 1;
        }
    }
    return 0;
}

int checkIfShipIsSunk(char *shipLocations, int size);
//Function to check if a ship is completely destroyed.
//Accepts the ship positions on the board and size of the ship
//returns a int value to determine if a ship is completely destroyed or not.
int checkIfShipIsSunk(char *shipLocations, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (*(shipLocations + i * size + 0) != 10 || *(shipLocations + i * size + 1) != 10)
        {
            return 0;
        }
    }
    return 1;
}

void initializeBoard(struct playerInfo *info,char *board);
//Function used to initialize the game board with a 10*10 array.
//Accepts player info and the pointer to 2D array for the board
void initializeBoard(struct playerInfo *info, char *board)
{
    info->isBoardInitialized = 1;
    board = (char *)calloc(10 * 10, sizeof(char));
}

int main()
{
    int selectedMenuOption;
    int currentPlayerId = 0;
    struct playerInfo *player;
    char *gameBoard;
    char *carrierLocations;
    char *battleShipLocations;
    char *cruiserLocations;
    char *subMarineLocations;
    char *destroyerLocations;
    while (1 == 1)
    {
        displayMenu();
        scanf("%d", &selectedMenuOption);
        switch (selectedMenuOption)
        {
        case 1:
            player = (struct playerInfo *)calloc(1,sizeof(struct playerInfo));
            currentPlayerId = currentPlayerId + 1;
            playerInfo(player, currentPlayerId);
            break;
        case 2:
            initializeBoard(player, gameBoard);
            break;
        case 3:
            if (player->isBoardInitialized == 0)
            {
                printf("Please Initialize the board before populating it.\n");
            }
            else
            {
                carrierLocations = (char *)calloc(5 * 5, sizeof(char));
                battleShipLocations = (char *)calloc(4 * 4, sizeof(char));
                cruiserLocations = (char *)calloc(3 * 3, sizeof(char));
                subMarineLocations = (char *)calloc(3 * 3, sizeof(char));
                destroyerLocations = (char *)calloc(2 * 2, sizeof(char));
                populateGameBoard(gameBoard, carrierLocations, battleShipLocations, cruiserLocations, subMarineLocations, destroyerLocations);
                if (player->isBoardViewed == 1)
                {
                    player->isBoardViewed = 0;
                    player->isBoardReinitialized = 1;
                }
                else
                {
                    player->isBoardPopulated = 1;
                }
            }
            break;
        case 4:
            if (player->isBoardPopulated == 0)
            {
                printf("Please Populate the Board before starting to play.\n");
            }
            else if (player->isBoardViewed == 1 && player->isBoardReinitialized == 0)
            {
                printf("Please reinitialize the game Board as you cannot play after seeing the board.\n");
            }
            else
            {
                playGame(player, gameBoard, carrierLocations, battleShipLocations, cruiserLocations, subMarineLocations, destroyerLocations);
            }
            break;
        case 5:
            displayBoard(gameBoard);
            player->isBoardViewed = 1;
            break;
        case 6:
            scoreBoard();
            break;
        case 7:
            exitGame(gameBoard, carrierLocations, battleShipLocations, cruiserLocations, subMarineLocations, destroyerLocations);
            break;
        default:
            printf("Please select a valid option from the given Menu.\n");
            break;
        }
    }
    return 1;
}
