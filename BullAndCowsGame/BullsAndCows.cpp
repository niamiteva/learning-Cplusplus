
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define MAX 5

//function that generates random digit
int generateRandomDigit()
{
	srand(time(NULL)); //unique word every time
	int num = rand() % 10;

	return num;
}
//function that generates number(type char*) with four different digits
void generateNumber(char* a)
{
	int digit;
	digit = generateRandomDigit();

	// the first digit can not be 0
	while(digit == 0)
        {
		digit = generateRandomDigit();
    	}
	//completing the first digit
    	a[0] = (char)(digit+48);

	//completing the other three
	for (int i = 1; i < 4;)
	{
		digit = generateRandomDigit();
		// check if the new digit is different from the other digits, if not generate new
		if ((char)(digit+48) != a[0] && (char)(digit+48)!=a[1] && (char)(digit+48)!=a[2] && (char)(digit+48)!=a[3])
		{
			a[i] = (char)(digit+48);
			//we continue after the digit is different from the other digits
			i++;
		}
		else digit = generateRandomDigit();
	}
}
// check if the input number is with 4 different digits
bool allDifferent(char* b)
{
    bool diff = true;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4;j++)
        {
            if(b[i] == b[j] && i!=j)
            {
                diff = false;
                break;
            }
        }
    }
    return diff;
}
// check if all chars in the input are numbers, not letters
bool allNums(char* b)
{
    bool isLetter = false;
    for(int i=0; i<4;i++)
    {
         if(b[i]<48 || b[i]> 57)
        {
            isLetter = true;
            break;
        }
    }
    return isLetter;

}
// searching for BULLS in the input number
int findBulls(char* a, char* b)
{
	int counter = 0;
	for (int i = 0; i < 4; i++)
	{
		if (a[i] == b[i]) counter++;
	}

	return counter;
}
//searching for Cows
int findCows(char* a, char* b)
{
	int counter = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i] == b[j]) counter++;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		// if we have bulls we have to substract their count from the cows' count
		if (a[i] == b[i]) counter--;
	}

	return counter;
}
//game play
void bullAndCows(char* a, char* b, int attempts)
{
	int bulls = findBulls(a, b);
	int cows = findCows(a, b);

	while (attempts > 1)
	{
		cout << "BULLS -> " << bulls << endl;
		cout << "COWS -> " << cows << endl;
		attempts--; cout << "Attempts left: " << attempts << endl<<endl;

		cout << "Make a guess: ";
		cin >> b;
		
		//conditions
		while(!allDifferent(b))
		{
		    cout << "Your number is not valid(all digits should be different).\nMake a new guess: ";
		    cin>>b;
		}
		while(allNums(b))
		{
		    cout << "Your number is not valid(you have letter in your number).\nMake a new guess: ";
		    cin>>b;
		}
		while(strlen(b) != 4)
		{
		    cout << "Your number is not valid(you have more or less than 4 digits).\nMake a new guess: ";
		    cin>>b;
		}


		bulls = findBulls(a, b);
		cows = findCows(a, b);
		//the user wins
		if (bulls == 4) break;
	}

	if (bulls == 4) cout << "Congratulations, you won the game!\n";
	else cout << "Sorry, you lost! The number was " << a << endl;
}

int main()
{
	cout << "RULES: Your mission is the guess the number generated from the program.\nThe number is with 4 different digits, so you will be asked to suggest only 4-digit numbers.\nIf you have in your number digit that is same as digit in the generated number means that you have 1 COW.\nIf the digit is the same and on the same place -> BULL.\n";
	cout << "\nChose a level: e(easy) -> 15 attempts, m(medium) -> 10 attempts, h(hard) -> 5 attempts\n";

	char level; cin >> level;

	int attempts = 0;
	if (level == 'e')	attempts = 15;
	else if (level == 'm')	attempts = 10;
	else if (level == 'h')	attempts = 5;

	char a[MAX] = "aaaa", b[MAX];

	generateNumber(a);

        cout << "Enter 4-(DIFFERENT)-digit number to make a guess: ";
        cin>>b;
	
	//conditions
        while(!allDifferent(b))
        {
		cout << "Your number is not valid(all digits should be different).\nMake a new guess: ";
		cin>>b;
        }
        while(allNums(b))
        {
		cout << "Your number is not valid(you have letter in your number).\nMake a new guess: ";
		cin>>b;
        }
        while(strlen(b) != 4)
        {
		cout << "Your number is not valid(you have more or less than 4 digits).\nMake a new guess: ";
		cin>>b;
        }
	
	//game function
	bullAndCows(a, b, attempts);

    return 0;
}

