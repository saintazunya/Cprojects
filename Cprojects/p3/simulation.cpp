#include"simulation.h"
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<iostream>
#include<cassert>

using namespace std;
bool initWorld(world_t &world, const string &speciesFile, const string &worldFile){
	//effect: init the world
	int i;//itr for reading species instructiosn
	string dictionary;
	dictionary=read_world(world,worldFile,speciesFile);//init

	//	check_species(world,speciesFile);	
	for(i=0;i<world.numSpecies;i++)
		{	
			read_in_instructions(dictionary,world.species[i]);
			
			}
	for (i=0;i<world.numCreatures;i++)//init each speceis programID to 1. 
		{
			world.creatures[i].programID=1;
			world.creatures[i].hillActive=true;//set init hill active to be true.
		}
	
	//***********************************************************************************
	//printGrid(world.grid);
	return true;
}

void fileopen(const string &file){
// effect: given file path, test if a file can be open or not. 
	ifstream File;
	File.open(file.c_str());
		if(!File)
		{	cout<<"Error: Cannot open file "<<file<<"!"<<endl;
			exit(0);
			}
	File.close();
	//
}
string read_world(world_t &world, const string &worldFile, const string &speciesFile){	
	//requries: world-file,species file exists
	//effect: read in world-file, species file		
		fileopen(speciesFile);
		fileopen(worldFile);
		ifstream worldfile;
		ifstream speciesfile;
		worldfile.open(worldFile.c_str());
		speciesfile.open(speciesFile.c_str());
		string dictionary;
		//read in species first.
		dictionary=read_species(world, speciesfile);
		
		worldfile>>world.grid.height;
		if(world.grid.height<1||world.grid.height>MAXHEIGHT){
			cout<<"Error: The grid height is illegal!"<<endl;
			exit(0);}
		worldfile>>world.grid.width;
		if(world.grid.width<1||world.grid.width>MAXWIDTH){
			cout<<"Error: The grid width is illegal!"<<endl;
			exit(0);}
		string temp_p;
		//int i,j;
		getline(worldfile,temp_p);//go to end of second line.
		read_terrain(world, worldfile);
		read_direction_ability(world, worldfile);
		//if(worldfile){
		//cout<<"Error: Accessing empty stream worldfile: should be empty. "<<worldfile<<endl;
		//exit(0);}
		return dictionary;
		
	
}
void read_terrain(world_t &world, ifstream &worldfile){
		//requires: world file opened, and passed into the function,terrain valid.
		//modifies: read in terrain information
		int i,j;//i ->height j->width
		string temp_p;
		for (i=0;i<world.grid.height;i++)
			{	getline(worldfile,temp_p);
			//cout<<temp_p<< " this is temp_p at ime 66"<<endl;
				for (j=0;j<world.grid.width;j++)																								
				{	
						if(temp_p.c_str()[j]=='P'){world.grid.terrain[i][j]=PLAIN;}
						else if(temp_p.c_str()[j]=='L'){world.grid.terrain[i][j]=LAKE;}
						else if(temp_p.c_str()[j]=='F'){world.grid.terrain[i][j]=FOREST;}
						else if(temp_p.c_str()[j]=='H'){world.grid.terrain[i][j]=HILL;}
						//TERRAIN_SIZE??
						//cout<<world.grid.terrain[i][j]<<" ";
						else {
						cout<<"Error: Terrain square ("<<temp_p.c_str()[j]<<" "<<i<<" "<<j<<") is invalid!"<<endl;
						exit(0);
						}
					}
					}
					// eniv created

}

void read_direction_ability(world_t &world, ifstream &worldfile){
		//requires: world file opened and passed into the funciton
		//effect: read in the species of creatures and its direction, init location, ability.
		//requires: species, direction, ability, initial location valid
	string temp_p,creaturespecies;
		int i=0,k=0;
		istringstream istemp; 
		//k for species checking 
		//i for creature iterating.
		//cout<<worldfile<<endl;
		//cout<<temp_p<<"this is temp_p"<<endl;
		while (getline(worldfile,temp_p))
		{	/*if(temp_p.compare(" ")==0)
			{	cout<<"test"<<endl;
				break;
			}*/
			istemp.str(temp_p);
			istemp>>creaturespecies;
			//cout<<temp_p<<" this is temp_p line 115"<<endl;
			bool judge=false;
			for (k=0;k<world.numSpecies;k++)
				{	if (creaturespecies.compare(world.species[k].name)==0)
						{
							world.creatures[i].species=&world.species[k];
							judge=true;
							break;
						}
				}
			
			if(!judge){cout<<"Error: Species "<<creaturespecies<<" not found!"<<endl;
						exit(0);}
			if(!istemp){break;}
			istemp>>temp_p;
			if(worldfile)
			{
				if (temp_p=="east")
					{
						world.creatures[i].direction=EAST;
					}
				else if (temp_p=="south")
					{
						world.creatures[i].direction=SOUTH;
						
					}
				else if (temp_p=="north")
					{
						world.creatures[i].direction=NORTH;
						
					}
				else if (temp_p=="west")
					{
						world.creatures[i].direction=WEST;
						
					}
				else
					{
					cout<<"Error: Direction " <<temp_p<< " is not recognized!"<<endl;
					exit(0);
					
					}
			}
		world.numCreatures=i;
		if(world.numCreatures>MAXCREATURES){
			cout<<"Error: Too many creatures!"<<endl;
			cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
			exit(0);}
		istemp>>world.creatures[i].location.r>>world.creatures[i].location.c;//row, colum;
		//cout<<world.creatures[i].location.r<<"  "<<world.creatures[i].location.c<<"this is locations"<<endl;
		if(world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c])//check overlap before assign creature to a location
			{		creature_t crea_temp;
					crea_temp=*getCreature(world.grid,world.creatures[i].location);
					cout<<"Error: ";
					cout<<"Creature ("<<world.creatures[i].species->name<<" "<<directName[world.creatures[i].direction]<<" "<<world.creatures[i].location.r<< " ";
					cout<<world.creatures[i].location.c<<") overlaps with creature ";
					cout<<"("<<crea_temp.species->name<<" "<<directName[crea_temp.direction]<<" "<<crea_temp.location.r<< " ";
					cout<<crea_temp.location.c<<")!"<<endl;
					exit(0);
					//cout<<"creature 1 "<<getCreature(world.grid,world.creatures[i].location)->species->name<<endl;
					//cout<<"creature 2 "<<world.creatures[i].species->name<<endl;
			}
		world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c]=&world.creatures[i];			
		while(istemp>>temp_p)
		{//read in ability
			//cout<<temp_p<<" this is check ability before assign to creature, line 197"<<"creature species: "<<world.creatures[i].species->name<<endl;
			if(temp_p.c_str()[1])
				{
					cout<<"Error: Creature (";
					cout<<world.creatures[i].species->name<<" "<< directName[world.creatures[i].direction]<<" "<<world.creatures[i].location.r<<" ";
					cout<<world.creatures[i].location.c;
					cout<<") has an invalid ability ";
					cout<<temp_p<<"!"<<endl;
					exit(0);
				}
			switch (temp_p.c_str()[0])
			{
				case 'f':
				world.creatures[i].ability[0]=true;
				break;
				case 'a':
				world.creatures[i].ability[1]=true;
				break;
				default: 
				cout<<"Error: Creature (";
				cout<<world.creatures[i].species->name<<" "<< directName[world.creatures[i].direction]<<" "<<world.creatures[i].location.r<<" ";
				cout<<world.creatures[i].location.c;
				cout<<") has an invalid ability ";
				cout<<temp_p<<"!"<<endl;
				exit(0);
				break;
			}
		}
				
		if(world.creatures[i].location.r>world.grid.height-1||world.creatures[i].location.c>world.grid.width-1)//check if in boundary
			{cout<<"Error: Creature (";
			cout<<world.species[i].name<<" "<< directName[world.creatures[i].direction]<<" "<<world.creatures[i].location.r<<" ";
			cout<<world.creatures[i].location.c;
			cout<<") is out of bound!"<<endl;
			cout<<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<"."<<endl;
			exit(0);
				}
		if(world.grid.terrain[world.creatures[i].location.r][world.creatures[i].location.c]==LAKE&&!world.creatures[i].ability[0])
			{	creature_t crea_temp;
				crea_temp=world.creatures[i];
				cout<<"Error: ";
				cout<<"Creature ("<<crea_temp.species->name<<" "<<directName[crea_temp.direction]<<" "<<crea_temp.location.r<< " ";
				cout<<crea_temp.location.c<<") is in a lake square!"<<endl;
				cout<<"The creature cannot fly! "<<endl;
				exit(0);
			
			}
		//cout<<"istemp is not used up"<<istemp<<endl;
		i++;
		istemp.clear();//clean it .
		temp_p="";
		}//while end
		worldfile.close();
		world.numCreatures=i;
		//cout<<"num of creatures "<<world.numCreatures<<endl;
		if(world.numCreatures>MAXCREATURES)
			{
					cout<<"Error: Too many creatures!"<<endl;
					cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
			}
		//cout<<endl;
}//function end 

string read_species(world_t &world, ifstream &speciesfile){
	//modifies: read in all the name of species given in the species file
	//requires: species file open and passed into the function
	string temp_p,dictionary;
	int speciesNum=0,speciesindex;
	getline(speciesfile,dictionary);//get out the first line 
	while(getline(speciesfile,temp_p))//if we can get the next line, loop.
	{	speciesNum++;
		speciesindex=speciesNum-1;//index of species in world array
		//cout<<speciesNum<<" "<<temp_p<<endl;
		if(speciesNum>MAXSPECIES)
			{	//cout<<speciesNum<<endl;
				cout<<"Error: Too many species!"<<endl;
				cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
				exit(0);
			}
		world.species[speciesindex].name=temp_p;
		//cout<<world.species[speciesNum-1].name<<endl;
		
	}
	//cout<<"test1"<<endl;
	world.numSpecies=speciesNum;	
	speciesfile.close();
	//cout<<dictionary<<" this is dictionary in read_species "<<endl;
	return dictionary;
}
void printGrid(const grid_t &grid){
	//modifies: print out the condition of world, including its creatures;
	//requries: world initialized. 
	int h,w;
	string temp_p;
	//cout<<grid.height<<endl;
	//cout<<grid.width<<endl;
	for (h=0;h<grid.height;h++){	
		for(w=0;w<grid.width;w++){
			if (grid.squares[h][w]){
			creature_t temp_c=(*grid.squares[h][w]);
			temp_p=temp_c.species->name;
			cout<<temp_p[0]<<temp_p[1]<<"_"<<directShortName[grid.squares[h][w]->direction]<<" ";
			}
			else{
					cout<<"____ ";
						}
			
			}
			cout<<endl;
		}
	
	
}//end function

direction_t leftFrom(direction_t dir){
// EFFECTS: Returns the direction that results from turning
// left from the given direction "dir".
	direction_t left_dir;
	switch (dir)
	{
		case NORTH:
			left_dir=WEST;
			break;
		case WEST:
			left_dir=SOUTH;
			break;
		case SOUTH:
			left_dir=EAST;
			break;
		case EAST:
			left_dir=NORTH;
			break;
		default:
			assert(0);
			break;
	}
	return left_dir;
}
direction_t rightFrom(direction_t dir){
// EFFECTS: Returns the direction that results from turning
// left from the given direction "dir".
	direction_t right_dir;
	switch (dir)
	{
		case NORTH:
			right_dir=EAST;
			break;
		case WEST:
			right_dir=NORTH;
			break;
		case SOUTH:
			right_dir=WEST;
			break;
		case EAST:
			right_dir=SOUTH;
			break;
		default:
			assert(0);
			break;
	}
	return right_dir;
}
void read_in_instructions(string dictionary,species_t &species){
//requires: instruction of the species exits.
//modifies: read in the instructions given a single species
//need for loop to read in all the species' instructions
//for instructions don't have a address, assign 0 to it.
	ifstream iFile;
	string temp,file;//file: path of file and file name
	int programsize=0;//different from creature programID!!
	//int j;//itr all possible input of instructions total 9 instrcutions
	istringstream temp_s;
	//cout<<dictionary<<" this is dictionary in read in instructions "<<endl;
	dictionary+="/";
	dictionary+=species.name;
	//dictionary.append(species.name);
	file=dictionary;
	//cout<<dictionary<<" this is dictionary in read in instructions "<<endl;
	iFile.open(file.c_str());
	if(!iFile)
		{	cout<<"Error: Cannot open file "<<file<<"!"<<endl;
			exit(0);
			}
	while(getline(iFile,temp)){
		if (temp==""){break;}
		temp_s.str(temp);
		temp_s>>temp;
		//cout<<species.name<<" this is the instruction "<<temp<<" id is "<<programsize<<endl;
		if(temp=="hop") 
				{species.program[programsize].op=HOP;}
		else if(temp=="left")
				{species.program[programsize].op=LEFT;}
		else if(temp=="right")
				{species.program[programsize].op=RIGHT;}
		else if(temp=="infect")
				{species.program[programsize].op=INFECT;}	
		else if(temp=="ifempty")
				{species.program[programsize].op=IFEMPTY;}
		else if(temp=="ifenemy")
				{species.program[programsize].op=IFENEMY;}	
		else if(temp=="ifsame")
				{species.program[programsize].op=IFSAME;}
		else if(temp=="ifwall")
				{species.program[programsize].op=IFWALL;}	
		else if(temp=="go")
				{species.program[programsize].op=GO;}	
		else
			{	cout<<"Error: Instruction "<<temp<< " is not recognized!"<<endl;
				exit(0);} 
		//cout<<"this is instruction of "<<species.name<<"  "<<opName[species.program[programsize].op]<<endl;
		if (temp_s){
			temp_s>>species.program[programsize].address;
			//cout<<species.program[programsize].address<<" this is address of program id "<<programsize<<endl;	
			//cout<<endl;
			}
			
		
		temp_s.clear();
		programsize++;
	}
	
	species.programSize=programsize;
	if(programsize>MAXPROGRAM)
		{
			cout<<"Error: Too many instructions for species "<<species.name<<"!"<<endl;
			cout<<"Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
			exit(0);
		}
	iFile.close();
	
}
instruction_t getInstruction(const creature_t &creature){
// EFFECTS: Returns the current instruction of "creature".	
	
	return creature.species->program[creature.programID-1];	//program id starts from 0;
	
}//end of function

creature_t *getCreature(const grid_t &grid, const point_t& location){
	//return pointer to a creature in a given grid
		
	return grid.squares[location.r][location.c];

}//end of function

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose){
	//simulate signle creature
	//cout<<"test 3 "<<creature.species->name<<endl;
	instruction_t inst_temp;
	bool ifnotact=true;
	//int i=0;
	int inst_itr=1;
	ifcanact(creature,grid);
		//update the condition in the hill.
		if(!creature.hillActive)
			{
			//cout<<"Creature "<< creature.species->name<<" is in hill and this is idle turn."<<endl;
			return;
			}
		//cout<<"test 4 "<<creature.species->name<<endl;
		//cout<<"test 4 "<<directName[creature.direction];
		//used for debug
		//cout<<"this is creature species "<<creature.species->name<<endl;
		//cout<<"this is program size "<<creature.species->programSize<<endl;
		//cout<<"this is current creature.programID "<<creature.programID<<endl;
		else
		{		
				cout<<"Creature ("<<creature.species->name<<" "<<directName[creature.direction]<<" "<<creature.location.r<< " ";
				cout<<creature.location.c;
				cout<<") takes action:";
				
				while(ifnotact)
				{	inst_itr=creature.programID;
					inst_temp=getInstruction(creature);
					switch(inst_temp.op)
					{
							case HOP:
								exehop(creature,grid,inst_temp);
								ifnotact=false;
								break;
							case LEFT:
								exeleft(creature, inst_temp);
								ifnotact=false;
								break;
							case RIGHT:
								exeright(creature,inst_temp);
								ifnotact=false;
								break;
							case INFECT:
								exeinfect(creature,grid,inst_temp);
								ifnotact=false;
								break;
							case IFEMPTY:
								exeifempty(creature,grid,inst_temp);
								break;
							case IFENEMY:
								exeifenemy(creature,grid,inst_temp);
								break;
							case IFSAME:
								exeifsame(creature,grid,inst_temp);
								break;
							case IFWALL:
								exeifwall(creature,grid,inst_temp);
								break;
							case GO:
								exego(creature,inst_temp);
								break;
							default:
								cout<<"Instruction "<<opName[inst_temp.op]<<" is not recognized! "<<endl;
								exit(0);
								break;	
					}
					if(verbose)
						{	cout<<endl;
							cout<<"Instruction "<<inst_itr<<": "<<opName[inst_temp.op];
							if(inst_temp.address!=0){cout<<" "<<inst_temp.address;}
							else{cout<<endl;}
							//inst_itr++;
							
						}
					
				}	
				if(verbose){
				printGrid(grid);
				}
				//cout<<opName[inst_temp.op]<<endl;
				else
					{
						cout<<" "<<opName[inst_temp.op]<<endl;
					}
				
					

		}
		
	
}

bool ifoutboundary(const grid_t &grid, const point_t& pt){
	//effect: judge if a point is out of boundary
	if (pt.r==-1||pt.c==-1||pt.r==grid.height||pt.c==grid.width)
		{return true;}
	else
		{return false;}
}
bool isempty(const grid_t &grid, const point_t& pt){
	//judge if the adjacent point is really empty, do not depend on terrain or creature ability.
	//cout<<"test for line 338"<<endl;
	if(ifoutboundary(grid,pt)){return false;}
	if (grid.squares[pt.r][pt.c])
		{//cout<<"test for line 341"<<endl;
		return false;}
	else
		{return true;}
}
bool ifisenemy(const creature_t &creature, const grid_t &grid,point_t point){
// given a point, judge if the point has an empty in it, do not depend on terrain or creature ability. 
// REAL CASE!! nomatter with ability a or not 
// for default, point=creature.point, in ability 'a' iteration, it can be any point.
// modifies: none
		point_t pt;
		pt=point;
		//cout<<"test for line 349"<<endl;	
		if(ifoutboundary(grid,pt)){return false;}
		else if(isempty(grid,pt)){return false;}
		else 
			{	//cout<<"test for line 350"<<endl;	
				/*if(!creature.ability[1])
					{
						if(grid.terrain[pt.r][pt.c]==FOREST){return false;}
					}*/
					//cout<<"test for line 354"<<endl;	
				if(grid.squares[pt.r][pt.c])
					{
						if(!(grid.squares[pt.r][pt.c]->species->name==creature.species->name)){return true;}
						
					}
				else{return false;}
				//world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c]=&world.creatures[i];
			}
			
}
point_t adjacentPoint(point_t pt, direction_t dir){
//return the adjacentpoint given creature direction and location
		point_t target_pt;
		target_pt=pt;
		switch(dir)
		{
				case EAST:	
					target_pt.c++;
					break;
				case WEST:
					target_pt.c--;
					break;
				case SOUTH:
					target_pt.r++;
					break;
				case NORTH:
					target_pt.r--;	
					break;
				default:
				assert(0);
		}
		//cout<<"target point location: "<<target_pt.r<<"  "<<target_pt.c<<endl;
	return target_pt;
}
bool ifcanhop(const creature_t &creature, const grid_t &grid,const direction_t &direction){
	//judge if a creature can hop forward based on current location of creature
	// modifies: none
	bool judge=false;
	point_t target_pt;
	target_pt=adjacentPoint(creature.location,direction);
	if(!ifoutboundary(grid,target_pt))
	{	if(!isempty(grid,target_pt)){judge=false;}
		else
		{
			if(creature.ability[0])
			{
				judge=true;
			}
			else{
					if(grid.terrain[target_pt.r][target_pt.c]==LAKE)
						{judge=false;}
					else{judge=true;}
				}
		}		
	}	
	return judge;
}
void hop(creature_t & creature, grid_t &grid){
	//move forward
	//cout<<"before ifcanhop"<<endl;
	//if(creature.species->name=="rrover"){cout<<"creature rrover"<<endl;}
	// modifies: creature.location
	if( ifcanhop(creature,grid,creature.direction) )
		{	//cout<<"can hop"<<endl;
				switch(creature.direction)
			{
					case EAST:	
						grid.squares[creature.location.r][creature.location.c]=NULL;
						creature.location.c+=1;
						grid.squares[creature.location.r][creature.location.c]=&creature;
						//world.grid.squares[world.creatures[i].location.r][world.creatures[i].location.c]=&world.creatures[i];
						break;
					case WEST:
						grid.squares[creature.location.r][creature.location.c]=NULL;
						creature.location.c-=1;
						grid.squares[creature.location.r][creature.location.c]=&creature;
						break;
					case SOUTH:
						grid.squares[creature.location.r][creature.location.c]=NULL;
						creature.location.r+=1;
						grid.squares[creature.location.r][creature.location.c]=&creature;
						break;
					case NORTH:
						grid.squares[creature.location.r][creature.location.c]=NULL;
						creature.location.r-=1;	
						grid.squares[creature.location.r][creature.location.c]=&creature;
						break;
					default: 
					cout<<"error"<<endl;
					assert(0);
		
			}
			//cout<<"creature: "<<creature.species->name<<endl;
			//cout<<"hop success"<<endl;
		}
	else{
		//cout<<"Error can not hop creature "<<creature.species->name<<endl; 
		}
}
void turn_left(creature_t &creature){//carry out instruction left
		creature.direction=leftFrom(creature.direction);
}
void turn_right(creature_t &creature){//carry out instruction right
		creature.direction=rightFrom(creature.direction);
}
void infect(creature_t &creature , grid_t &grid){
	// modifies: world
	// effect: carry out the instruction infect
	// only execute the instruction, but DO NOT update program id.
	point_t target_pt;
	target_pt=creature.location;//init 
	creature_t *infect_crea;
	//cout<<"this is line is used to test original location "<<creature.location.r <<" "<<creature.location.c<<endl;
	if (!creature.ability[1])
	{	target_pt=adjacentPoint(creature.location,creature.direction);
		//cout<<"target point location: "<<target_pt.r<<"  "<<target_pt.c<<endl;
		if(ifoutboundary(grid,target_pt)){return;}
		if(grid.terrain[target_pt.r][target_pt.c]==FOREST){return;}
		if(ifisenemy(creature,grid,target_pt))
		{	//cout<<"this is line is used to test line 453"<<endl;
			//grid.squares[target_pt.r][target_pt.c]->species=creature.species;
			infect_crea=getCreature( grid, target_pt);
			infect_crea->species=creature.species;
			infect_crea->programID=1;
		}
	}
	else if(creature.ability[1])
		{	//cout<<"target point location: "<<target_pt.r<<"  "<<target_pt.c<<endl;
			while(1)
				{	target_pt=adjacentPoint(target_pt,creature.direction);
					if(ifoutboundary(grid,target_pt)){break;}
					//cout<<"creature direction "<<creature.direction<<endl;
					//cout<<"target point location: "<<target_pt.r<<"  "<<target_pt.c<<endl;
					//exit(0);
					//cout<<ifisenemy(creature,grid,target_pt)<<endl;
					if(ifisenemy(creature,grid,target_pt))
						{	//cout<<"there is an enemy in location"<<target_pt.r<<"  "<<target_pt.c<<endl;
							//grid.squares[target_pt.r][target_pt.c]->species=creature.species;
							infect_crea=getCreature( grid, target_pt);
							infect_crea->species=creature.species;
							infect_crea->programID=1;
							break;
						}
					
				}
				
		}
		
}//end of function
void exeifempty(creature_t &creature, const grid_t &grid,instruction_t &instruction){ 
	// execute the command ifempty
	// modifies: program id.
	if(instruction.op!=IFEMPTY){
		cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be IFEMPTY"<<endl;
		assert(0);}
	point_t target_pt=adjacentPoint(creature.location,creature.direction);
		if(instruction.address==0)
		{
			cout<<"error address"<<endl;
			exit(0);
		}
	/*if(isforsest(grid,target_pt)){
		creature.programID++;
		return;}*/
	if(isempty(grid,target_pt))
		{
			creature.programID=instruction.address;
			return;
		}

	else {creature.programID++;
	return;}
}
bool ifenemy(const creature_t &creature, const grid_t &grid){
//effect: return the vale used to carry out insturctions, dfferent from each terrain.
//modifies: none
	point_t target_pt=adjacentPoint(creature.location,creature.direction);
	/*if(creature.ability[1])
		{
			return ifisenemy(creature,grid,target_pt); 
		}
	else 
		{*/
			if(grid.terrain[target_pt.r][target_pt.c]==FOREST)
				{
					return false;					
				}
			else 
				{
						return ifisenemy(creature,grid,target_pt); 
				}
		/*}*/
}//end of function
bool ifsame(const creature_t &creature, const grid_t &grid){
	//effect: return the vale used to carry out insturctions, dfferent from each terrain.
	//modifies: none
	point_t target_pt=adjacentPoint(creature.location,creature.direction);
			if(ifoutboundary(grid,target_pt)){return false;}
			if(grid.terrain[target_pt.r][target_pt.c]==FOREST)
				{
					return false;					
				}
			else 
				{	if(isempty(grid,target_pt))
					{
						return false;
					}
					else {return !ifisenemy(creature,grid,target_pt);}
						
				}

}//end of function
void exeifenemy(creature_t &creature, const grid_t &grid, instruction_t &instruction){
	//execute ifenemy
	if(instruction.op!=IFENEMY)
		{
			cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be IFENEMY"<<endl;
			assert(0);
		}
	//point_t target_pt=adjacentPoint(creature.location,creature.direction);
		if(instruction.address==0)
		{
			cout<<"error address"<<endl;
			exit(0);
		}
	/*if(isforest(grid,target_pt)){creature.programID++;
	return;}*/
	else if(ifenemy(creature,grid))
		{
			creature.programID=instruction.address;
		}

	else {creature.programID++;}
	
	
}//end of function
void exeifsame(creature_t &creature, const grid_t &grid, instruction_t &instruction){
	//execute ifsame
	if(instruction.op!=IFSAME)
		{
			cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be IFSAME"<<endl;
			assert(0);
		}
			if(instruction.address==0)
		{
			cout<<"error address"<<endl;
			exit(0);
		}
	//point_t target_pt=adjacentPoint(creature.location,creature.direction);
	/*if(isforest(grid,target_pt)){creature.programID++;
	return;}*/
	if(ifsame(creature,grid))
		{
			creature.programID=instruction.address;
		}

	else {creature.programID++;}
	
	
}//end of function
void exeifwall(creature_t &creature, const grid_t grid, instruction_t &instruction){
	//execute ifwall
	if(instruction.op!=IFWALL){
		cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be IFWALL"<<endl;
		assert(0);}	
	point_t target_pt;
	target_pt=adjacentPoint(creature.location,creature.direction);
	if(instruction.address==0)
		{
			cout<<"error address"<<endl;
			exit(0);
		}
	if (ifoutboundary(grid,target_pt))
		{
				creature.programID=instruction.address;
		}
	else if(grid.terrain[target_pt.r][target_pt.c]==LAKE)
		{	if(!creature.ability[0])
				{
					creature.programID=instruction.address;
				}
			else {creature.programID++;}
		}//if target is lake
	else {creature.programID++;}
}//end of function.
void exego(creature_t &creature, instruction_t &instruction){
	//execute go
	if(instruction.op!=GO){
		cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be GO"<<endl;
		assert(0);}	
	if(instruction.address==0)
		{
			cout<<"error address"<<endl;
			exit(0);
		}
	creature.programID=instruction.address;
	
}//end of function
void exehop(creature_t &creature, grid_t &grid, instruction_t &instruction){
	//execute hop
	if(instruction.address!=0)
	{
		cout<<"error address"<<endl;
		exit(0);
	}
	if(instruction.op!=HOP){
		cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be HOP"<<endl;
		assert(0);}	
	hop(creature,grid);
	creature.programID++;
}//end of function
void exeinfect(creature_t &creature, grid_t &grid, instruction_t &instruction){
	//execute infect
	if(instruction.address!=0)
	{
		cout<<"error address"<<endl;
		exit(0);
	}
	if(instruction.op!=INFECT)
	{
		cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be INFECT"<<endl;
		assert(0);
	}	
	infect(creature,grid);	
	creature.programID++;
}
void exeleft(creature_t &creature, instruction_t &instruction){
	//execute left
		if(instruction.address!=0)
	{
		cout<<"error address"<<endl;
		exit(0);
	}
	if(instruction.op!=LEFT)
	{
		cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be LEFT"<<endl;
		assert(0);
	}
	turn_left(creature);	
	creature.programID++;
}
void exeright(creature_t &creature, instruction_t &instruction){
	//execute right 
		if(instruction.address!=0)
	{
		cout<<"error address"<<endl;
		exit(0);
	}
	if(instruction.op!=RIGHT)
	{
		cout<<"Error: wrong instruction "<<opName[instruction.op]<<" instruction should be RIGHT"<<endl;
		assert(0);
	}
	turn_right(creature);	
	creature.programID++;
}//end of function
void ifcanact(creature_t &creature,const grid_t &grid){
	//effect:judge whether a creature can act this turn or not
	//modifies: none
	if(creature.ability[0])
		{	
			creature.hillActive=true;
			
		}
	else if(!creature.ability[0]&&grid.terrain[creature.location.r][creature.location.c]==HILL)
		{
			
			creature.hillActive=!creature.hillActive;
		}
	else {creature.hillActive=true;}
}
bool isforest(const grid_t &grid, const point_t &pt){
	//return if terrain of a grid is forest
	//modifies: none
		return grid.terrain[pt.r][pt.c]==FOREST;
}


