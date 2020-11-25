/*	allegroHighScore Class v.1.1	FEB 19 2001
	Justin Todd 
    Features: Add and view records, auto-sort, simple to use.     
	Extended Features of allegroHighScore Class:
		AllegHS acts as a graphical frontend for HighScore Class in Allegro.
	Requirements: A C++ compiler
*/

#define MAX_RECORDS			10							//Maximum amount of high scores. WARNING!!!! Delete the current scores data file before changing this, or it won't work!
#define NAME_LENGTH			20							//Maxium amount of characters for name. WARNING!!!! Delete the current scores data file before changing this, or it won't work!
#define EMPTY_RECORD_NAME	"-Empty-\0"					//This is the name that is used for an emtpy record
#define FILE_NAME			"data/score.dat"				//Name of the binary file to save highscores

#include<allegro.h>
#include<string.h>
#include<stdio.h>

class HighScore{										//The HighScore class can add=remove records,sort highscores, find averages, write to files. and much more
private:
	FILE *DataFile;										//The binary file containing saved scores
	struct RecordStruct{								//A record to hold the name and score
		char Name[NAME_LENGTH];							//Character string to hold name
		int Score;
	};
	RecordStruct Record[MAX_RECORDS];
public:
	HighScore();										//Constructor
	~HighScore();										//Destructor

	int addRecord(char name[NAME_LENGTH], int score);	//adds a record in the apropriate spot based on its score size
	int viewRecordScore(int position);					//This method returns the score for the desired record
	char * viewRecordName(int position);				//This method returns the name for the desired record
	int findAverageScore();								//Finds the average score of all of the records
	void clearAllRecords();								//Resets the highscores
	int testRecord(int score);							//Finds out if the users score is high enough to enter the highscores
};

