#ifndef SIMULATION_H
#define SIMULATION_H
#include "world_type.h"
bool initWorld(world_t &world, const string &speciesFile, const string &worldFile);
//effect: init the world
void fileopen(const string &file);
// effect: given file path, test if a file can be open or not. 
void read_terrain(world_t &world, ifstream &worldfile);
//requries: world-file,species file exists
//effect: read in world-file, species file	
string read_world(world_t &world, const string &worldFile, const string &speciesFile);
//requires: world file opened, and passed into the function,terrain valid.
//modifies: read in terrain information
void read_direction_ability(world_t &world, ifstream &worldfile);
//requires: world file opened and passed into the funciton
//effect: read in the species of creatures and its direction, initial location, ability.
//requires: species, direction, ability, init location valid
string read_species(world_t &world, ifstream &speciesfile);
//modifies: read in all the name of species given in the species file
//requires: species file open and passed into the function
point_t adjacentPoint(point_t pt, direction_t dir);
//return the adjacentpoint given creature direction and location
direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// left from the given direction "dir".
direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// left from the given direction "dir".
creature_t *getCreature(const grid_t &grid, const point_t& location);
//return pointer to a creature in a given grid
void printGrid(const grid_t &grid);
//modifies: print out the condition of world, including its creatures;
//requries: world initialized. 
void read_in_instructions(string dictionary,species_t &species);
//requires: instruction of the species exits.
//modifies: read in the instructions given a single species
//need for loop to read in all the species' instructions
//for instructions don't have a address, assign 0 to it.
instruction_t getInstruction(const creature_t &creature);
// EFFECTS: Returns the current instruction of "creature".
creature_t *getCreature(const grid_t &grid, const point_t& location);
void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
//simulate signle creature
//cout<<"test 3 "<<creature.species->name<<endl;
bool ifoutboundary(const grid_t &grid, const point_t& pt);
//effect: judge if a point is out of boundary
bool isempty(const grid_t &grid, const point_t& pt);
//judge if the adjacent point is really empty, do not depend on terrain or creature ability.
bool ifisenemy(const creature_t creature, const grid_t &grid);
// given a point, judge if the point has an empty in it, do not depend on terrain or creature ability. 
// REAL CASE!! nomatter with ability a or not 
// for default, point=creature.point, in ability 'a' iteration, it can be any point.
// modifies: none
bool ifcanhop(const creature_t &creature, const grid_t &grid,const direction_t &direction);
//judge if a creature can hop forward based on current location of creature
// modifies: none
void hop(creature_t & creature, grid_t &grid);
//move forward
//cout<<"before ifcanhop"<<endl;
//if(creature.species->name=="rrover"){cout<<"creature rrover"<<endl;}
// modifies: creature.location
void turn_left(creature_t &creature);
//carry out instruction left
void turn_right(creature_t &creature);
//carry out instruction right
void infect(creature_t &creature , grid_t &grid);
// modifies: world
// effect: carry out the instruction infect
// only execute the instruction, but DO NOT update program id.
void exeifempty(creature_t &creature, const grid_t &grid,instruction_t &instruction);
// execute the command ifempty
// modifies: program id.
bool ifenemy(const creature_t &creature, const grid_t &grid);
//effect: return the vale used to carry out insturctions, dfferent from each terrain.
//modifies: none
bool ifsame(const creature_t &creature, const grid_t &grid);
//effect: return the vale used to carry out insturctions, dfferent from each terrain.
//modifies: none
void exeifenemy(creature_t &creature, const grid_t &grid, instruction_t &instruction);
//execute ifenemy
void exeifsame(creature_t &creature, const grid_t &grid, instruction_t &instruction);
//execute ifsame
void exeifwall(creature_t &creature, const grid_t grid, instruction_t &instruction);
//execute ifwall
void exego(creature_t &creature, instruction_t &instruction);
//execute go
void exehop(creature_t &creature, grid_t &grid, instruction_t &instruction);
//execute hop
void exeinfect(creature_t &creature, grid_t &grid, instruction_t &instruction);
//execute infect
void exeleft(creature_t &creature, instruction_t &instruction);
//execute left
void exeright(creature_t &creature, instruction_t &instruction);
//execute right
void ifcanact(creature_t &creature,const grid_t &grid);
//effect:judge whether a creature can act this turn or not
//modifies: none
bool isforest(const grid_t &grid, const point_t &pt);
//return if terrain of a grid is forest
//modifies: none
#endif

