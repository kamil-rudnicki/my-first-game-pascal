#include "naglowki.h"

HighScore::HighScore(){									//the constructor
	int x;												//a counter
	for(x=0;x<MAX_RECORDS;x++){							//Loop which initializes the record structure
		Record[x].Score=0;								//Initializes the scores
		strcpy(Record[x].Name,EMPTY_RECORD_NAME);		//Initializes the strings by putting the "empty" message for a name
	}
	DataFile=fopen(FILE_NAME,"rb");						//Open file for reading
	if(DataFile){										//If the file exists, copy the saved highscores from the file into the Record structure
		fread(&Record,sizeof(struct RecordStruct),\
			MAX_RECORDS,DataFile);						//Read the file into the highscore structure
		fclose(DataFile);								//Close the file
	}
}

HighScore::~HighScore(){
	DataFile=fopen(FILE_NAME,"wb");						//Open the datafile for writing				
	fwrite(&Record,sizeof(struct RecordStruct),\
		MAX_RECORDS,DataFile);							//Write the updated highscores to file
	fclose(DataFile);									//Close the file
}

int HighScore::addRecord(char name[NAME_LENGTH], int score){	//This method adds a record (if it even qualifies) in the appropriate location (sorted from great to least)
	int x,y;													//x and y are simply integer counters
	for(x=0;x<MAX_RECORDS;x++){									//a loop to go through the entire highscore list
		if(score>Record[x].Score){								//If the score trying to get into the highscore list is greater than the current score in the list, (Record[x].Score) then...
			for(y=(MAX_RECORDS-1);y>x;y--){						//...begin a loop that will move the list down to make room for it.  Note: the last score in the list will be disregarded
				Record[y].Score=Record[y-1].Score;				//"Move this score down one"
				strcpy(Record[y].Name,Record[y-1].Name);		//"Move this name down one"
			}
			Record[x].Score=score;								//Now that we've made an empty spot for the new score, lets fill it up
			strcpy(Record[x].Name,name);						//Place the users name into the record
			return 1;											//If 1 is returned, it means that the record made the highscore list and was successfully entered
		}
	}
	return 0;													//If 0 is returned, it means that this record did not make the highscore list
}

int HighScore::viewRecordScore(int position){					//This method returns the score for the desired record
	return Record[position].Score;
}

char * HighScore::viewRecordName(int position){					//This method returns the name for the desired record
	return Record[position].Name;
}

int HighScore::findAverageScore(){			//This method finds the average score of the entire list
	int sum,numRecords,x;					//numRecords keeps a count of non-zero records
	sum=numRecords=x=0;						//Sets the integers to zero
	for(x=0;x<MAX_RECORDS;x++){				//Go through all records
		if(Record[x].Score>0){				//If record has no value, disregard it
			sum+=Record[x].Score;			//Add this score to the current sum of scores
			numRecords++;					//Incremt numRecords
		}
	}
	return sum/numRecords;					//Return the average score
}

void HighScore::clearAllRecords(){						//Resets the highscores
	int x;
	for(x=0;x<MAX_RECORDS;x++){							//for loop to loop through entire Record structure
		Record[x].Score=0;								//Deletes score
		strcpy(Record[x].Name,EMPTY_RECORD_NAME);		//Deletes name
	}
}

int HighScore::testRecord(int score){					//Tests to see if the given score is enough to get into the highscores
	int x;												//Counter
	for(x=0;x<MAX_RECORDS;x++)							//Loops through the highscores...
		if(score>Record[x].Score) return 1;				//and if the given score is bigger than any score currently in the highscores, then return 0
	return 0;											//score wasn't high enough
}
