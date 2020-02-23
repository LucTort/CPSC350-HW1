//https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
//http://www.cplusplus.com/doc/tutorial/files/
//https://stackoverflow.com/questions/46719183/c-using-ifstream-to-read-file
//https://stackoverflow.com/questions/2310939/remove-last-character-from-c-string
//https://stackoverflow.com/questions/2649717/c-function-for-picking-from-a-list-where-each-element-has-a-distinct-probabili
//https://stackoverflow.com/questions/7748071/same-random-numbers-every-time-i-run-the-program
//https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
//http://www.cplusplus.com/reference/cmath/log/

#include <iostream>
#include <fstream> //Needed to work with files
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

string getBigram(double probAA, double probAC, double probAT, double probAG, double probCA, double probCC, double probCT, double probCG,
                 double probTA, double probTC, double probTT, double probTG, double probGA, double probGC, double probGT, double probGG);

string getDnaString(double variance, double meanDnaLength, double probA, double probC, double probT, double probG,
                    double probAA, double probAC, double probAT, double probAG, double probCA, double probCC, double probCT, double probCG,
                    double probTA, double probTC, double probTT, double probTG, double probGA, double probGC, double probGT, double probGG);

int main(int argc, char **argv)
{

    srand(time(NULL)); //seeds random output

    const string OUTPUT_FILE = "lucasTorti.out"; //sets name for output file
    const int NUM_LINES_TO_PRINT = 1000;         //number of lines to output to file

    string stringOfLetters = "";
    string stringOfBigrams = "";

    unsigned int DNAlinesInDoc = 0;

    //for reading through file
    char currentChar = ' ';
    char previousChar = ' ';
    string bigram = "";
    int DNAstringLength = 0;
    double varianceNumerator = 0;

    double meanDnaPerLine = 0;
    double variance = 0;

    bool wasCharInLine = false;

    string userInput = "";  //sets up user inut variable

    //Arrays are for wimps. Real coders use copy & paste
    unsigned int numAA = 0;
    unsigned int numAC = 0;
    unsigned int numAT = 0;
    unsigned int numAG = 0;
    unsigned int numCA = 0;
    unsigned int numCC = 0;
    unsigned int numCT = 0;
    unsigned int numCG = 0;
    unsigned int numTA = 0;
    unsigned int numTC = 0;
    unsigned int numTT = 0;
    unsigned int numTG = 0;
    unsigned int numGA = 0;
    unsigned int numGC = 0;
    unsigned int numGT = 0;
    unsigned int numGG = 0;

    unsigned int numA = 0;
    unsigned int numC = 0;
    unsigned int numT = 0;
    unsigned int numG = 0;

    double probAA = 0;
    double probAC = 0;
    double probAT = 0;
    double probAG = 0;
    double probCA = 0;
    double probCC = 0;
    double probCT = 0;
    double probCG = 0;
    double probTA = 0;
    double probTC = 0;
    double probTT = 0;
    double probTG = 0;
    double probGA = 0;
    double probGC = 0;
    double probGT = 0;
    double probGG = 0;

    double probA = 0;
    double probC = 0;
    double probT = 0;
    double probG = 0;

    unsigned int totalDNA = 0;
    unsigned int totalBigrams = 0;

    string line = "";                             //sets up string to read from file


    //while is used to run program again and again
    ifstream inputFile; //takes file form command line
    

    while (userInput != "quit")//(!(tolower(userInput) == "quit"))
    {
        if (userInput == "")
        {
            inputFile.open(argv[1]);
        } else
        {
            inputFile.open(userInput);
        }
        
        

        if (!inputFile.is_open()) //makes sure file opens correctly
        {
            cout << "File didn't open properly" << endl;
            return 1;
        }

        //1st run through file
        while (inputFile.get(currentChar)) // loop getting single characters
        {

            currentChar = toupper(currentChar);

            if (currentChar == 'A' || currentChar == 'C' || currentChar == 'T' || currentChar == 'G')
            {
                stringOfLetters += currentChar;
                bigram += currentChar;
                wasCharInLine = true;
            }

            else
            {
                bigram = "";
                bigram = "";
                if (currentChar == '\n' && wasCharInLine == true) //This makes it so the program only counts lines with A,C, T, or G in them
                {
                    wasCharInLine = false;
                    DNAlinesInDoc++;
                }
            }

            if (bigram.length() == 2)
            {
                stringOfBigrams += bigram;
                bigram = "";
            }

            previousChar = currentChar;

        } //while

        //closes and opens file to reset position
        inputFile.close();
        ifstream anotherInputFile(argv[1]);

        //calculate mean DNA per line

        meanDnaPerLine = (stringOfLetters.length() / (double)DNAlinesInDoc);

        //2nd run through file
        while (anotherInputFile.get(currentChar)) // loop getting single characters
        {
            currentChar = toupper(currentChar);
            if (currentChar == 'A' || currentChar == 'C' || currentChar == 'T' || currentChar == 'G')
            {
                DNAstringLength++;
                // cout << currentChar << endl;

            } //if

            else if (currentChar == '\n')
            {
                varianceNumerator += pow((DNAstringLength - meanDnaPerLine), 2);

                // cout << "Variance calculation" << endl;

                // cout << pow((DNAstringLength - meanDnaPerLine), 2) << endl;

                DNAstringLength = 0;
            } //else  if

        } //while

        //Calculate variance
        variance = (varianceNumerator / (DNAlinesInDoc));

        //prints entire file

        //cout << endl << stringOfLetters << endl << stringOfBigrams << endl;

        ofstream outputFile(OUTPUT_FILE); //Creates output file

        //Counts number of each individual letter

        cout << "Counting letters" << endl;
        for (int i = 0; i < stringOfLetters.length(); ++i) //works
        {
            if (stringOfLetters.substr(i, 1) == "A")
                numA++;
            if (stringOfLetters.substr(i, 1) == "C")
                numC++;
            if (stringOfLetters.substr(i, 1) == "T")
                numT++;
            if (stringOfLetters.substr(i, 1) == "G")
                numG++;
        } //for

        //Counts number of each bigram

        cout << "Counting bigrams." << endl;
        for (int i = 0; i < stringOfBigrams.length(); ++++i)
        {
            if (stringOfBigrams.substr(i, 2) == "AA")
                numAA++;
            if (stringOfBigrams.substr(i, 2) == "AC")
                numAC++;
            if (stringOfBigrams.substr(i, 2) == "AT")
                numAT++;
            if (stringOfBigrams.substr(i, 2) == "AG")
                numAG++;
            if (stringOfBigrams.substr(i, 2) == "CA")
                numCA++;
            if (stringOfBigrams.substr(i, 2) == "CC")
                numCC++;
            if (stringOfBigrams.substr(i, 2) == "CT")
                numCT++;
            if (stringOfBigrams.substr(i, 2) == "CG")
                numCG++;
            if (stringOfBigrams.substr(i, 2) == "TA")
                numTA++;
            if (stringOfBigrams.substr(i, 2) == "TC")
                numTC++;
            if (stringOfBigrams.substr(i, 2) == "TT")
                numTT++;
            if (stringOfBigrams.substr(i, 2) == "TG")
                numTG++;
            if (stringOfBigrams.substr(i, 2) == "GA")
                numGA++;
            if (stringOfBigrams.substr(i, 2) == "GC")
                numGC++;
            if (stringOfBigrams.substr(i, 2) == "GT")
                numGT++;
            if (stringOfBigrams.substr(i, 2) == "GG")
                numGG++;
        } //for

        //Calculates probability of each combination

        //Gets total number of DNA letters and DNA bigrams

        totalDNA = stringOfLetters.length();
        totalBigrams = (stringOfBigrams.length() / 2);

        //Calculates actual probability

        probA = (numA / ((double)totalDNA));
        probC = (numC / ((double)totalDNA));
        probT = (numT / ((double)totalDNA));
        probG = (numG / ((double)totalDNA));

        //Calculates bigram probability
        probAA = (numAA / ((double)totalBigrams));
        probAC = (numAC / ((double)totalBigrams));
        probAT = (numAT / ((double)totalBigrams));
        probAG = (numAG / ((double)totalBigrams));
        probCA = (numCA / ((double)totalBigrams));
        probCC = (numCC / ((double)totalBigrams));
        probCT = (numCT / ((double)totalBigrams));
        probCG = (numCG / ((double)totalBigrams));
        probTA = (numTA / ((double)totalBigrams));
        probTC = (numTC / ((double)totalBigrams));
        probTT = (numTT / ((double)totalBigrams));
        probTG = (numTG / ((double)totalBigrams));
        probGA = (numGA / ((double)totalBigrams));
        probGC = (numGC / ((double)totalBigrams));
        probGT = (numGT / ((double)totalBigrams));
        probGG = (numGG / ((double)totalBigrams));

        //Hard coding is best coding
        cout << "Lucas Torti" << endl
            << endl;

        cout << "Number of A: " << numA << endl;
        cout << "Number of C: " << numC << endl;
        cout << "Number of T: " << numT << endl;
        cout << "Number of G: " << numG << endl
            << endl;

        cout << "AA combinations: " << numAA << endl;
        cout << "AC combinations: " << numAC << endl;
        cout << "AT combinations: " << numAT << endl;
        cout << "AG combinations: " << numAG << endl;
        cout << "CA combinations: " << numCA << endl;
        cout << "CC combinations: " << numCC << endl;
        cout << "CT combinations: " << numCT << endl;
        cout << "CG combinations: " << numCG << endl;
        cout << "TA combinations: " << numTA << endl;
        cout << "TC combinations: " << numTC << endl;
        cout << "TT combinations: " << numTT << endl;
        cout << "TG combinations: " << numTG << endl;
        cout << "GA combinations: " << numGA << endl;
        cout << "GC combinations: " << numGC << endl;
        cout << "GT combinations: " << numGT << endl;
        cout << "GG combinations: " << numGG << endl
            << endl;

        cout << "Probability of A: " << probA << endl;
        cout << "Probability of C: " << probC << endl;
        cout << "Probability of T: " << probT << endl;
        cout << "Probability of G: " << probG << endl
            << endl;

        cout << "Probability of AA: " << probAA << endl;
        cout << "Probability of AC: " << probAC << endl;
        cout << "Probability of AT: " << probAT << endl;
        cout << "Probability of AG: " << probAG << endl;
        cout << "Probability of CA: " << probCA << endl;
        cout << "Probability of CC: " << probCC << endl;
        cout << "Probability of CT: " << probCT << endl;
        cout << "Probability of CG: " << probCG << endl;
        cout << "Probability of TA: " << probTA << endl;
        cout << "Probability of TC: " << probTC << endl;
        cout << "Probability of TT: " << probTT << endl;
        cout << "Probability of TG: " << probTG << endl;
        cout << "Probability of GA: " << probGA << endl;
        cout << "Probability of GC: " << probGC << endl;
        cout << "Probability of GT: " << probGT << endl;
        cout << "Probability of GG: " << probGG << endl
            << endl;

        cout << endl
            << "Sum of DNA length: " << stringOfLetters.length() << endl;
        cout << "Lines containing DNA: " << DNAlinesInDoc << endl;
        cout << "Mean DNA per line: " << meanDnaPerLine << endl;
        cout << "Variance: " << variance << endl
            << endl;


        //cout << "Random value: " << selectedOutput << endl;
        cout << "Writing to file..." << endl;
        for (int i = 0; i < NUM_LINES_TO_PRINT; ++i)
        {
            outputFile << getDnaString(variance, meanDnaPerLine, probA, probC, probT, probG,
                                    probAA, probAC, probAT, probAG, probCA, probCC, probCT, probCG,
                                    probTA, probTC, probTT, probTG, probGA, probGC, probGT, probGG)
                    << endl;
        } //for

        cout << "Closing file." << endl;
        outputFile.close();

        cout << endl << "Enter another file to repeat the process, or type 'quit' to stop program: ";

        cin >> userInput;
    }      //while

    return 0;
} //main

//Generate Gaussian distribution number
int getGaussianNum(double variance, double meanDnaPerLine)
{

    double a = ((double)rand() / (RAND_MAX));
    double b = ((double)rand() / (RAND_MAX));

    double C = sqrt(-2 * log(a)) * cos(2 * M_PI);

    double D = ( (sqrt(variance) * C) + meanDnaPerLine );

    return D;

} //getGaussianNum()

//generate random bigram based on probabilities

string getBigram(double probAA, double probAC, double probAT, double probAG, double probCA, double probCC, double probCT, double probCG,
                 double probTA, double probTC, double probTT, double probTG, double probGA, double probGC, double probGT, double probGG)

{

    double x = ((double)rand() / (RAND_MAX));
    int probabilityIndex = 0;
    double selectedProb = probAA;
    string bigramOutput = "AA";
    while (selectedProb < x)
    {
        //out << "In while" << endl;
        if (probabilityIndex == 0)
        {
            selectedProb += probAC;
            bigramOutput = "AC";
            probabilityIndex++;
        }
        else if (probabilityIndex == 1)
        {
            selectedProb += probAT;
            bigramOutput = "AT";
            probabilityIndex++;
        }
        else if (probabilityIndex == 2)
        {
            selectedProb += probAG;
            bigramOutput = "AG";
            probabilityIndex++;
        }
        else if (probabilityIndex == 3)
        {
            selectedProb += probCA;
            bigramOutput = "CA";
            probabilityIndex++;
        }
        else if (probabilityIndex == 4)
        {
            selectedProb += probCC;
            bigramOutput = "CC";
            probabilityIndex++;
        }
        else if (probabilityIndex == 5)
        {
            selectedProb += probCT;
            bigramOutput = "CT";
            probabilityIndex++;
        }
        else if (probabilityIndex == 6)
        {
            selectedProb += probCG;
            bigramOutput = "CG";
            probabilityIndex++;
        }
        else if (probabilityIndex == 7)
        {
            selectedProb += probTA;
            bigramOutput = "TA";
            probabilityIndex++;
        }
        else if (probabilityIndex == 8)
        {
            selectedProb += probTC;
            bigramOutput = "TC";
            probabilityIndex++;
        }
        else if (probabilityIndex == 9)
        {
            selectedProb += probTT;
            bigramOutput = "TT";
            probabilityIndex++;
        }
        else if (probabilityIndex == 10)
        {
            selectedProb += probTG;
            bigramOutput = "TG";
            probabilityIndex++;
        }
        else if (probabilityIndex == 11)
        {
            selectedProb += probGA;
            bigramOutput = "GA";
            probabilityIndex++;
        }
        else if (probabilityIndex == 12)
        {
            selectedProb += probGC;
            bigramOutput = "GC";
            probabilityIndex++;
        }
        else if (probabilityIndex == 13)
        {
            selectedProb += probGT;
            bigramOutput = "GT";
            probabilityIndex++;
        }
        else if (probabilityIndex == 14)
        {
            selectedProb += probGG;
            bigramOutput = "GG";
            probabilityIndex++;
        }

        else if (selectedProb == (1))
        {
            cout << endl << "There was a problem" << endl;
        }
    } //while


    return bigramOutput;

} //getBigram

//generate random letter values based on probabilities

string getSingleDna(double probA, double probC, double probT, double probG)
{
    double x = ((double)rand() / (RAND_MAX)); //makes random number from 0.0 to 1.0
    //cout << x << endl;
    int probabilityIndex = 0;
    double selectedProb = probA;
    string selectedOutput = "A";
    while (selectedProb < x)
    {
        if (probabilityIndex == 0)
        {
            selectedProb += probC;
            selectedOutput = "C";
            probabilityIndex++;
        }
        else if (probabilityIndex == 1)
        {
            selectedProb += probT;
            selectedOutput = "T";
            probabilityIndex++;
        }
        else if (probabilityIndex == 2)
        {
            selectedProb += probG;
            selectedOutput = "G";
            probabilityIndex++;
        }
        else if (probabilityIndex == 3)
        {
            cout << endl
                 << "There was a problem" << endl;
        }
    } //while
    return selectedOutput;
} //getDnaChar()

string getDnaString(double variance, double meanDnaLength, double probA, double probC, double probT, double probG,
                    double probAA, double probAC, double probAT, double probAG, double probCA, double probCC, double probCT, double probCG,
                    double probTA, double probTC, double probTT, double probTG, double probGA, double probGC, double probGT, double probGG)
{
    int dnaLength = getGaussianNum(variance, meanDnaLength);
    //cout << "dnaLength: " << dnaLength << endl;
    string dnaString = "";
    int DnaLengthLeftToGenerate = 0;

    while (dnaString.length() < dnaLength)
    {
        dnaString.append(getBigram(probAA, probAC, probAT, probAG, probCA, probCC, probCT, probCG,
                                       probTA, probTC, probTT, probTG, probGA, probGC, probGT, probGG));

        if ( ((dnaLength) - dnaString.length()) == 1) //As suggested by Chris Chang
        {
            dnaString.append(getSingleDna(probA, probC, probT, probG));
        }

    } //while
    //cout << "dnaString: " << dnaString << endl;

    return dnaString;
} //getDnaString()
