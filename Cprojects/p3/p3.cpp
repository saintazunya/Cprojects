#include "simulation.h"
#include <fstream>
#include <iostream>
#include <sstream>
int main(int argc,char* argv[])
{ 	world_t world;
	//const int MAXSPECIES=20;
	//const int MAXPROGRAM=20;
	// error checking process
	if (argc<4)
	{   // check number of elements
		cout << "Error: Missing arguments!" << endl;
		cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
		return 0;
		
	}
	int round,crea_cont,round_itr;
	string strtemp;
	strtemp = argv[3];
	istringstream  Streamtemptemp;
	Streamtemptemp.str(strtemp);
	Streamtemptemp >> round;// use sstream to read in round as int
	if (round<0)//check if round is negative
		{	cout<<"Error: Number of simulation rounds is negative!"<<endl;
			Streamtemptemp.clear();// free the variable
			return 0;
			}
	const string worldFile=argv[2],speciesFile=argv[1];
	//end of counting species
	// instructions, left unsloved.
	
	//***********************************************************************************
	bool verbose=false;
	if (argc > 4)
		{
			string verbosestr;
			verbosestr=argv[4];//Transform the cahr* to a string.
			//cout<<"verbose"<<verbosestr<<endl;
			if (verbosestr=="v"||verbosestr=="verbose")
				{verbose=true;}
		}
	initWorld(world, speciesFile, worldFile);
	cout<<"Initial state"<<endl;
	printGrid(world.grid);
	//cout<<"test"<<endl;
	for(round_itr=1;round_itr<round+1;round_itr++)
	{	cout<<"Round "<<round_itr<<endl;
		for (crea_cont=0;crea_cont<world.numCreatures;crea_cont++)
			{	//cout<<"test2"<<endl;
				if(verbose)
					{
						simulateCreature(world.creatures[crea_cont],world.grid,verbose);
					}
			
				if(!verbose)//if not verbose, berbose=false;
				{
					simulateCreature(world.creatures[crea_cont],world.grid,verbose);
				}
			}
		if(!verbose){printGrid(world.grid);}
	}
	//cout<<world.creatures[world.numCreatures-1].species->name<<endl;
	//***********************************************************************************
	
/*
	initWorld(world, speciesFile, worldFile);
	cout<<"Initial state"<<endl;
	printGrid(world.grid);
	for (round_itr=1;round_itr<10;round_itr++){
		simulateCreature(world.creatures[0],world.grid,true);
		}
*/
return 0;}
