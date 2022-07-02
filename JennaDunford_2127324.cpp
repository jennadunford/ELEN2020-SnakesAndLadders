//<2127324>

//ELEN 2020 PROJECT, MAY 2021
//DYNAMICALLY CREATED GAMES OF SNAKES AND LADDERS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

string squareElem(string snakes, string ladders, int position) //This function determines what element is on a game square (empty, snake or ladder) and the index of where the value of the element is stored
{
    string outString; //An output string that the function returns
    int index; //An integer to store the index
    if (snakes.find(("-" + to_string(position)) + "-") != -1) //Checking if current position exists in the snake position string
    {
        index = snakes.find("-" + to_string(position) + "-");
        outString = "S-" + to_string(index);
    }
    else if (ladders.find(("-" + to_string(position)) + "-") != -1) //checking if the current position exists in the ladder position string
    {
        index = ladders.find("-" + to_string(position) + "-");
        outString = "L-" + to_string(index);
    }
    else //If the current position does not contain a snake or a ladder the default "D-" is used.
    {
        outString = "D-";
    }
    return outString; //Returns an output containing the element prefix and, if it exists, the index of where to find the value of the element (snake or ladder)
}

vector<string> CreateFileVector(string fileName) //This function creates the vector that holds all of the data from the initial file
{
    ifstream inputFile;
    string fileString;
    vector<string> outputVector;
    inputFile.open(fileName);
    while (!inputFile.eof())
    {
        getline(inputFile, fileString);
        if (!fileString.empty()) {
            outputVector.push_back(fileString); //Storing each line from the file into a string vector
        }
    }
    inputFile.close();
    return outputVector; //Outputting the vector
}

void ClearFile(string fileName) //A function to clear the input file
{
    ofstream file;
    file.open(fileName, std::ofstream::trunc); //Opens the file for truncation which clears the contents of the file
    file.close();
}

void SetRandom()
{
    srand(time(0)); //Initializes the random function
}

bool CheckIfLastGame(vector<string> fileVector, int GamesPlayed) //Boolean function that checks if this is the final game
{
    bool check;
    if (fileVector.size() == GamesPlayed)
    {
        check = true;
    }
    else
    {
        check = false;
    }
    return check;
}


vector<int>	InitializePlayer(vector<int> playerVector, int PlayerNum) //Function to initialize players for each game
{
    for (int i = 0; i <= 3; i++)
    {
        playerVector.push_back(0);
    }
    playerVector[1] = (PlayerNum);
    return playerVector;
}

int generateRandom(int start, int end) //Function to generate random numbers as needed
{
    return (start + rand() % end);
}


int main()
{
    class gameData //A class to store data for the game
    {
    public:
        void getBoardSize(string size) //Function to obtain board size
        {
            _BoardSize = stoi(size);
        }

        void getPlayers(string numPlayers) //Function to obtain number of players
        {
            _PlayerNum = stoi(numPlayers);
        }

        void getStNum(string stNumber) //Function to obtain student number
        {
            _StudentNum = stoi(stNumber);
        }

        void getBinary(vector<int> vBinary) //function to obtain binary values
        {
            _BinaryVals = vBinary;
        }


        int _BoardSize, _PlayerNum, _StudentNum; //Declaration of class variables, integers
        vector<int> _BinaryVals; //Declaration of vector class variable
    };

    //Below are the variables used in the main code
    ifstream inputF; //Variable for the input file to read from it
    ofstream appinputF; //Variable to append to the input file
    ofstream resultsF; //Variable to append the results file
    string inputStr; //String to store the input string line from the file
    string binString; //String to store binary values
    gameData game; //Creating gameData variable named game
    vector<int> binV; //Creating a vector of integers to store the binary Values
    int numSnakes = 0; //Creating an integer to store the number of snakes
    int numLadders = 0; //Creating an integer to store the number of ladders
    vector<vector<int>> vSnakes; //A 2D Vector to store vectors of snakes positions and values
    vector<vector<int>> vLadders; //A 2D Vector to store vectors of ladders positions and values
    vector<vector<int>> vPlayers; //A 2D Vector to store vectors of players game data
    vector<int> tempVec; //A temporary vector of integers to be used as needed
    vector<int> usedSquares; //A vector which indicates which board squares have already been used
    int randSquare; //An integer to store a randomly generated square value for a snake or ladder
    int randLength; //An integer to store a randomly generated length value for a snake or ladder
    bool playing = true; //Boolean variable flag to check if game is being played or not
    bool initialized = false; //Boolean variable flag to check if players have been initialized
    int diceRoll = 0; //Integer variable to store the dice roll
    int Rounds = 0; //Integer variable to store the number of rounds
    int arrPositions[9] = { 1 }; //An array with positions of players (game can support up to 9 players)
    int boardSize; //Integer to store the size of the board
    int endIndex; //Integer to store the end index of a string
    int startIndex; //Integer to store the start index of a string
    string strsnakesSP; //String to store Snakes Positions
    string strsnakesSV; //String to store Snakes Values
    string strladdsSP; //String to store ladders Positions
    string strladdsSV; //String to store ladders Values
    string sqElem; //String to obtain the element string from the function
    string winner; //String to output who the winner is
    vector<string> fileVec; //A vector to store the lines from the input file
    string fileLine; //A string to store the file lines
    int gamesPlayed = 0; //A counter integer to count how many games have been played
    string strElement; //An element string to output either D- S- or L- in the output file

    fileVec = CreateFileVector("input.txt");
    ClearFile("input.txt");
Setup:
    SetRandom(); //Initializing the random number generator
    int b = 0; //Initializing two integers, b and c
    int c = 0;
    if (CheckIfLastGame(fileVec, gamesPlayed)) {
        goto stop;
    }
    for (int pos = 0; pos < 8; pos++)
    {
        arrPositions[pos] = 0; //Filling position array with 0 as each player starts outside the board.
    }
    inputStr = fileVec[gamesPlayed]; //Gets first line for input file

    for (int a = 0; a < inputStr.length() - 1; a++)
    {
        if (isblank(inputStr[a]) && (gamesPlayed == 0))
        {
            switch (b) //Switch statements which store the game data if this is the first game being played
            {
            case 0:
                game.getBoardSize(inputStr.substr(0, (a)));
                b++;
                break;
            case 1:
                game.getPlayers(inputStr.substr((a - 1), 1));
                b++;
                c = a;
                break;
            case 2:
                game.getStNum(inputStr.substr((c + 1), (a - c - 1)));
                b++;
                break;
            }
        }
        if (!(isblank(inputStr[a])) && b == 3 && gamesPlayed == 0) //If and case statements used to generate the number of snakes and ladders based on the binary value
        {
            binString = binString + inputStr[a];
            binV.push_back((inputStr[a]) - '0');
            switch ((inputStr[a]))
            {
            case '0':
                numSnakes++;
                break;
            case '1':
                numLadders++;
                break;
            }
        }
    }
    if (gamesPlayed > 0) //If this is not the first game being played, game data is obtained differently
    {
        int tempA = inputStr.find(" ");
        game.getBoardSize(inputStr.substr(0, tempA));
        game.getPlayers(inputStr.substr(tempA + 1, 1));
    }
    if (gamesPlayed == 0)
    {
        game.getBinary(binV);
    }
    else //If this is not the first game being played, the number of snakes and ladders are determined with a random function
    {

        numSnakes = 6 + generateRandom(1, 6);
        numLadders = 6 + generateRandom(1, 6);
    }

    for (int s = 0; s <= numSnakes - 1; s++) //For loop to generate the snakes values and positions
    {
    generateS:
        randSquare = generateRandom(1, (game._BoardSize - 1));
        randLength = generateRandom(1, 50);
        if ((find(usedSquares.begin(), usedSquares.end(), randSquare) != usedSquares.end())) //Checking if square position is already taken
        {
            goto generateS;
        }
        else
        {
            if ((randSquare - randLength) > 0) //Checking that the square position is not less than the length
            {   //Below: filling vectors with position and length values for snakes
                usedSquares.push_back(randSquare);
                tempVec.push_back(randSquare);
                tempVec.push_back(randLength);
                vSnakes.push_back(tempVec);
                tempVec.clear();
            }
            else
            {
                goto generateS;
            }
        }
    }
    for (int l = 0; l <= numLadders; l++) //For loop to generate positions and lengths for ladders
    {
    generateL:
        randSquare = generateRandom(1, (game._BoardSize - 1));
        randLength = generateRandom(1, 50);
        if ((find(usedSquares.begin(), usedSquares.end(), randSquare) != usedSquares.end())) //Checking if square position is already used
        {
            goto generateL;
        }
        else
        {
            if (((randSquare + randLength) < (game._BoardSize))) //Checking that ladder does not go off the game board
            {   //Below: filling vectors with position and length values for ladders
                usedSquares.push_back(randSquare);
                tempVec.push_back(randSquare);
                tempVec.push_back(randLength);
                vLadders.push_back(tempVec);
                tempVec.clear();
            }
            else
                goto generateL;
        }
    }
    appinputF.open("input.txt", std::ios_base::app); //Open the input file for appending
    appinputF << fileVec[gamesPlayed] << "\n"; //Adding first line with the board and player data
    for (int q = 0; q < numSnakes; q++)
    {
        appinputF << "S " << vSnakes[q][0] << "-" << vSnakes[q][1] << "\n"; //Appending file with Snake values
    }
    for (int z = 0; z < numLadders; z++)
    {
        appinputF << "L " << vLadders[z][0] << "-" << vLadders[z][1] << "\n"; //Appending file with Ladder values
    }
    appinputF << "\n"; //Leaving a line
    appinputF.close(); //Closing the input file
    //Below: clearing snake and ladder value and position strings;
    strsnakesSP.clear();
    strsnakesSV.clear();
    strladdsSP.clear();
    strladdsSV.clear();

    //Below: filling strings with snake and ladder values and positions
    for (int iq = 0; iq < numSnakes; iq++)
    {
        strsnakesSP = strsnakesSP + "-" + to_string(vSnakes[iq][0]);
        strsnakesSV = strsnakesSV + "-" + to_string(vSnakes[iq][1]);
    }
    for (int iv = 0; iv < numLadders; iv++)
    {
        strladdsSP = strladdsSP + "-" + to_string(vLadders[iv][0]);
        strladdsSV = strladdsSV + "-" + to_string(vLadders[iv][1]);
    }
    boardSize = game._BoardSize; //Setting the boardSize

        //Actual game
    initialized = false; //Making sure initialization is set to false to begin with
    resultsF.open("results.txt", std::ios_base::app); //Opening the results file for appending
    if (gamesPlayed == 0) //Checking if this is the first game
    {
        resultsF << boardSize << " " << game._StudentNum << " " << binString << "\n"; //Writing applicable first line for the first game
    }
    else
    {
        resultsF << boardSize << "\n"; //Writing applicable first line for subsequent games
    }
    while (playing) //The game play occurs while the playing boolean is true
    {
        strElement = " D-"; //The default square element is " D-" for output purposes
        if (!initialized) //If players have not been initialized, initialization routine occurs
        {
            for (int r = 0; r < game._PlayerNum; r++) //Below for loop initializes each player for the current game
            {
                tempVec.clear();
                tempVec = InitializePlayer(tempVec, (r + 1));
                vPlayers.push_back(tempVec);
                resultsF << "R-" << vPlayers[r][0] << " P-" << vPlayers[r][1] << " D-" << vPlayers[r][2] << " M-" << vPlayers[r][3] << "\n";
            }
            initialized = true; //Sets initialization to true
        }
        Rounds++; //Increases number of rounds by 1
        for (int pg = 0; pg < game._PlayerNum; pg++) //For loop so that every player has a turn each round
        {
            tempVec = vPlayers[pg]; //getting the player's data vector
            tempVec[1] = pg + 1; //Setting players name (example: P-1)
            tempVec[0] = Rounds; //Setting number of rounds
            tempVec[2] = 0;

        rollAgain: //Roll again routine in case a player rolls a 6
            diceRoll = generateRandom(1, 6);
            if ((arrPositions[pg] + diceRoll) > game._BoardSize) //If dice roll takes player off the board player misses their turn
            {
                strElement = " D-";
                tempVec[2] = tempVec[2] + diceRoll;
                tempVec[3] = arrPositions[pg];
                goto missTurn;
            }
            tempVec[2] = diceRoll; //Stores dice roll in temporary Vector
            arrPositions[pg] = arrPositions[pg] + diceRoll; //Updates player positions array
            tempVec[3] = arrPositions[pg]; //Storing player position
            if (diceRoll == 6) //If the dice roll was 6, the player rolls again
            {
                goto rollAgain;
            }
            sqElem = squareElem(strsnakesSP, strladdsSP, arrPositions[pg]); //Checking which element the player has landed on

            if ((sqElem.substr(0, 2)) == "D-") //If player has landed on an empty quare
            {
                if (tempVec[3] == boardSize) //Checking if player has landed on the final square
                {
                    strElement = " D-"; //String element is D- by default
                    playing = false; //Play has ended
                    winner = "WP-" + to_string(tempVec[1]); //Updating the winner string
                    goto endGame; //Jumps to the end of the game
                }

            }
            else if ((sqElem.substr(0, 2) == "S-")) //Checking if player has landed on a snake
            {
                startIndex = sqElem.find("-") + 1;//Finding start index of index value;
                endIndex = strsnakesSV.find(startIndex, '-') - 1; //Finding end index of index value
                tempVec[2] = tempVec[2] - stoi(strsnakesSV.substr(startIndex, endIndex - startIndex)); //Getting the snake length value
                tempVec[3] = arrPositions[pg] - tempVec[2]; //Updating player position
                strElement = " S-"; //Updating element value
            }
            else if ((sqElem.substr(0, 2)) == "L-") //Checking if player landed on a ladder
            {
                startIndex = sqElem.find("-") + 1;//Finding start index of index value
                endIndex = strladdsSV.find(startIndex, '-') - 1; //Finding end index of index value
                tempVec[2] = tempVec[2] + stoi(strladdsSV.substr(startIndex, endIndex - startIndex)); //Updating player position
                strElement = " L-"; //Updating element value
                if ((arrPositions[pg] + diceRoll) > game._BoardSize) //Checking if player went over the board
                {
                    tempVec[3] = arrPositions[pg]; //Updating position data
                    goto missTurn; //Missing a turn
                }
                tempVec[3] = arrPositions[pg] + tempVec[2]; //Updating position data
                if (tempVec[3] == boardSize) //Checking if player has won
                {
                    playing = false; //Stop playing
                    winner = "WP-" + to_string(tempVec[1]); //Storing winner string
                    goto endGame; //Going to the end game
                }
            }
        missTurn: //Miss turn routine for if a player misses a turn
            if (tempVec[2] < 0)
            {
                tempVec[2] = tempVec[2] * -1; //Small effort to make sure rare chance of negative numbers does not affect output data
            }
            if (tempVec[3] < 0)
            {
                tempVec[3] = tempVec[3] * -1; //Small effort to make sure rare chance of negative numbers does not affect output data
            }
            resultsF << "R-" << tempVec[0] << " P-" << tempVec[1] << strElement << tempVec[2] << " M-" << tempVec[3] << "\n"; //Outputting round results
        }
    endGame:
        if (!playing)
        {
            resultsF << "R-" << tempVec[0] << " P-" << tempVec[1] << strElement << tempVec[2] << " M-" << tempVec[3] << "\n"; //Outputting winner results
        }

    }
    resultsF << winner; //Outputs the winner string
    resultsF << "\n"; //Leaves two lines in the output file
    resultsF << "\n";
    resultsF.close(); //Closes the output file
    vSnakes.clear();
    vLadders.clear();
    usedSquares.clear();
    gamesPlayed++;
    playing = true;
    Rounds = 0;

    goto Setup; //Jumps up to the setup of the game

stop:
    return(0);

}
