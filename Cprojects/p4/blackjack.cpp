#include "deck.h"
#include "player.h"
#include "rand.h"
#include "card.h"
#include "hand.h"
#include<iostream>
#include<cstdlib>
#include<cassert>
#include<fstream>
#include<sstream>
using namespace std;
void Announce_Hand(int thishand, const int bankroll){
	//Effects: Announce the start of a hand before starting.
	//modifies: cout
	cout << "# Hand " << thishand << " bankroll " << bankroll << endl;
}
void Shuffle_rand(Deck &gameDeck,Player *player_game){
	//Effects shuffle the deck by random method
	//modifies: deck, player cout
	int shuf_itr,rand;
	cout << "# Shuffling the deck\n";
	for (shuf_itr=1;shuf_itr<=7;shuf_itr++)
				{		
						rand=get_cut();
						gameDeck.shuffle(rand);
						cout << "cut at " << rand << endl;
				}
	player_game->shuffled();
}
void show_player_deal(Player *PLAYER,Hand &player, Deck &Deck,bool expose){
		//effect:Announcement player's deal
		//modifies: player, cout,deck,hand
		Card c=Deck.deal();
		player.addCard(c);
		cout<<"Player dealt "<<SpotNames[c.spot]<<" of "<<SuitNames[c.suit]<< endl;	
		//cout<<Deck.cardsLeft()<<endl;
		if(expose)
			PLAYER->expose(c);
}
Card show_dealer_deal(Player *PLAYER,Hand &dealer, Deck &Deck,bool expose){
		//effect:Announcement player's deal
		//modifies: player, cout,deck,hand
		Card c=Deck.deal();
		dealer.addCard(c);		
		//cout<<Deck.cardsLeft()<<endl;
		if(expose)
			{
				cout<<"Dealer dealt "<<SpotNames[c.spot]<<" of "<<SuitNames[c.suit]<< endl;
				PLAYER->expose(c);
			}
		return c;
}
void check_if_restore(Deck &Deck,Player *player_game){
	//effect check if needs restore the deck, if yes, restore it by random shuffle method
	//modifies: deck, player,cout
	if(Deck.cardsLeft()<20)
		{
			Shuffle_rand(Deck,player_game);
		}
	
}
void player_if_Bust(Hand & hand, int &Bankroll,int bet){
	
	if(hand.handValue().count > 21)
				{
					cout << "# Player busts\n";
					Bankroll-=bet;
					return;
				}
}
void Exe_oneHand(Hand &player, Hand &dealer, Deck &Deck, int &Bankroll, Player *player_game, const int minbet,int this_Hand_itr ){
			//effect execute one hand. 
			//modifies: player,dealer, hand of player, hand of dealer, bankroll, deck, 
			player.discardAll();
			dealer.discardAll();
			
			if(Bankroll<minbet)
				return;
			Announce_Hand(this_Hand_itr,Bankroll);
			check_if_restore(Deck,player_game);
			Card Bright,Dark,Later;
			int bet_thisHand=player_game->bet(Bankroll,minbet);
			cout << "# Player bets " <<  bet_thisHand<< endl;
			/*init*/
			bool expose=true;
			show_player_deal(player_game,player,Deck,expose);
			Bright=show_dealer_deal(player_game,dealer,Deck,expose);
			show_player_deal(player_game,player,Deck,expose);
			expose=false;
			Dark=show_dealer_deal(player_game,dealer,Deck,expose);
			expose=true;
			//cout<<"code at line 54 in blackjack"<<endl;
			/*-------------------*/
			bool init=true;
			while(1)
			{	
				if (player.handValue().count == 21&&init)
				{	
					cout << "# Player dealt natural 21\n";
					Bankroll+=(bet_thisHand*3/2);
					return; 
				}
				init=false;//natural only occurs on the first loop.
				if(player.handValue().count > 21)
				{	cout << "Player's total is " << player.handValue().count<< endl;
					player_if_Bust(player,Bankroll,bet_thisHand);
					return;
				}
				else 
					{	
						if(player_game->draw(Bright,player))
							{
								show_player_deal(player_game,player,Deck,expose);
							}
						
						else
							{
								break;
							}
					}
			}
			cout << "Player's total is " << player.handValue().count<< endl;
			player_if_Bust(player,Bankroll,bet_thisHand);
			/*---------------------dealer turn-----------------------------------*/
			cout<<"Dealer's hole card is "<<SpotNames[Dark.spot]<<" of "<<SuitNames[Dark.suit]<< endl;
			player_game->expose(Dark);//expose the hole card
			while(1)
				{	
					if(dealer.handValue().count<17)
						Later=show_dealer_deal(player_game,dealer,Deck,expose);
					else 
						break;
				}
				cout << "Dealer's total is " << dealer.handValue().count << endl;
				if(dealer.handValue().count>21)
					{		
							cout << "# Dealer busts\n";
							Bankroll+=bet_thisHand;
							return;
					}
				else 
					{
						if(dealer.handValue().count>player.handValue().count)
							{	
								Bankroll-=bet_thisHand;
								cout << "# Dealer wins\n";
								return;
							}
						else if (dealer.handValue().count<player.handValue().count)
							{	
								cout << "# Player wins\n";
								Bankroll+=bet_thisHand;
								return;
							}
						else
							{
								cout << "# Push\n";
								return;
							}
					}
								
}
int main(int argc,char* argv[]){
	//cout<<"<bankroll> <min-bet> <hands> <simple|counting> [<input_file_name>]"<<endl;
	int Bankroll=atoi(argv[1]);
	int gameHands=atoi(argv[3]);
	string player_T=argv[4];
	int minbet=atoi(argv[2]);
	int this_Hand_itr=1;
	//cout<<"debug line 170"<<endl;
	Deck gameDeck;
	Hand playerHand,dealerHand;	
	Player *player_game;// as a pointer
	if(player_T=="simple")
		{player_game=get_Simple();}
	else if(player_T=="counting")//{cout<<"line40 in blackjacj"<<endl;}
		{//cout<<"Error in line 176 blackjack"<<endl;
			player_game=get_Counting();}
		
	else{
		cout<<player_T<<endl;
		cout<<"Error in line40 blackjack"<<endl;
		assert(0);
		}
	//deckShuffle(gameDeck, player_game);
	//int shuf_itr;
	int rand;//used to shuffle from file 
	
	if(argc>5)
		{	//istringstream temp;
			cout << "# Shuffling the deck\n";
			string inst_name=argv[5];
			ifstream inst_file;
			inst_file.open(inst_name.c_str());	
			if(!inst_file)
				{	
					cout<<"Error: Cannot open file "<<inst_name<<"!"<<endl;
					exit(0);
				}
				//getline(inst_file,temp_str);
			while(inst_file>>rand)
				{
					gameDeck.shuffle(rand);
					cout << "cut at " << rand << endl;
					player_game->shuffled();
				}
		}
	
	else 
		{
			Shuffle_rand(gameDeck,player_game);
		}
	/*gamestart*/
	for (;this_Hand_itr<=gameHands;this_Hand_itr++)
		{	//cout<<"error before hand starts"<<endl;
			Exe_oneHand(playerHand, dealerHand, gameDeck, Bankroll,player_game, minbet,this_Hand_itr );	
			if(Bankroll<minbet)
				{	this_Hand_itr++;
					break;
				}
		}
	/*--------------output results---------------*/
	if(this_Hand_itr==2){this_Hand_itr--;}
	cout<<"# Player has "<<Bankroll<<" after "<<this_Hand_itr-1<<" hands"<<endl;
}
