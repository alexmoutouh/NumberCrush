/**
* 
* @file NumberCrushStandardV2.cxx
*
* @author Julien M., Alexandre M., Stéphane N., Amélie L. 
*
* @bug
*
* @date 31/12/2014
*
* @brief Le jeu NumberCrush ; Mode standard
* 
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <utility>
#include <string> 
#include <fstream> 
#include <ctime>
#include <limits>



using namespace std;

/**
 * 
 * \namespace
 * 
 */
namespace 
{
	 
	
	
/** 
 * \typedef CVLine
 * \brief Vector that represent a line of a matrix 
 * 
 */ 
	typedef vector <unsigned> CVLine;
	
/**
 * \typedef CMat
 * \brief Matrix that represent the game grid
 *  
 */
	typedef vector <CVLine> CMat;
	
/**
 * \typedef CPosition 
 * \brief Spot of a number in the grid 
 * 
 */
	typedef pair <unsigned, unsigned> CPosition;
	
/**
 * \fn void ClearScreen()
 * \brief Clear the terminal's screen
 * 
 */	
	void ClearScreen ();

/**
 * \fn void Couleur (const string & coul)
 * \brief Change color of numbers or the background
 * 
 */
	void Couleur (const string & coul);
	
/**
 * \fn void DisplayLogo()
 * \brief Display the game logo from a file
 * 
 */
	void DisplayLogo ();

/**
 * \fn void DisplayGrid (const CMat & Grid)
 * \brief Display the Matrix 
 * 
 */
	void DisplayGrid (const CMat & Grid);
	
/**
 * \fn void InitGrid (CMat & Grid, unsigned Size, unsigned NbCandies)
 * \brief Initialize the Grid with random numbers
 * \param Grid The matrix
 * \param Size The size of the matrix
 * \param NbCandies The amount of candies, represented by numbers
 * 
 */
	void InitGrid (CMat & Grid, unsigned Size, unsigned NbCandies);
	
/**
 * \fn bool TestMove (CMat & Grid, const CPosition & Pos, char Direction)
 * \brief Verify if the move is possible
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of 
 *  number you want to move
 * \param Direction Char of the selected movement
 * 
 */	
	bool TestMove (CMat & Grid, const CPosition & Pos, char Direction);
	
/**
 * \fn void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction, 
 * 					   unsigned & NbMove, unsigned & Score)
 * \brief Move the chosen number by inserting a direction 
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of 
 *  number you want to move
 * \param Direction Char of the selected movement
 * \param NbMove Amount of move left
 * \param Score Amount of points you have
 * 
 */ 
	void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction, 
					unsigned & NbMove, unsigned & Score);
					
/**
 * \fn bool AtLeastThreeInAColumn (const CMat & Grid, CPosition & Pos,
 *  unsigned & HowMany)
 * \brief Return true if at least three same numbers are aligned in a column
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of 
 *  number you want to move
 * \param HowMany Represent the number of consecutive elements
 * 
 */
	bool AtLeastThreeInAColumn (const CMat & Grid, CPosition & Pos, 
								unsigned & HowMany);
	
/**
 * \fn bool AtLeastThreeInARow (const CMat & Grid, CPosition & Pos, 
 *  unsigned & HowMany)
 * \brief Return true if at least three same numbers are  aligned in a row
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of 
 *  number you want to move
 * \param HowMany Represent the number of consecutive elements
 * 
 */
	bool AtLeastThreeInARow (const CMat & Grid, CPosition & Pos, 
							 unsigned & HowMany); 

/**
 * \fn void RemovalInColumn (CMat & Grid, const CPosition & Pos, 
 * 							 unsigned  HowMany)
 * \brief When at least three same numbers are in a column
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of 
 *  number you want to move
 * \param HowMany Represent the number of consecutive elements 
 *  (at least three consecutive numbers)
 * 
 */
	void RemovalInColumn (CMat & Grid, const CPosition & Pos, 
						  unsigned  HowMany);
	
/**
 * \fn void RemovalInRow (CMat & Grid, const CPosition & Pos, 
 * 						  unsigned  HowMany)
 * \brief When at least three same numbers are in a row
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of 
 *  number you want to move
 * \param HowMany Represent the number of consecutive elements 
 *  (at least three consecutive numbers)
 * 
 */
	void RemovalInRow (CMat & Grid, const CPosition & Pos, 
					   unsigned HowMany);
					   
/**
 * \fn bool FullColumn (CMat & Grid, CPosition & Pos)
 * \brief Return true if a column is full of zeros
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of
 *  number you want to move
 * 
 */
	bool FullColumn (CMat & Grid, CPosition & Pos);
	
/**
 * \fn void RemovalFullColumn (CMat & Grid, const CPosition & Pos)
 * \brief Move to the right the full column
 * \param Grid The matrix
 * \param Pos It's a pair of unsigned numbers, represent the position of 
 *  number you want to move
 * 
 */
	void RemovalFullColumn (CMat & Grid, const CPosition & Pos);
	
/**
 * \fn void CalculScore (unsigned & Score, unsigned HowMany) 
 * \brief Calcul the player's score
 * \param Score Current points earn by the player
 * \param HowMany Represent the number of following elements 
 *  (at least three following numbers)
 * 
 */
	void CalculScore (unsigned & Score, unsigned HowMany); 
	
/**
 * \fn bool NombreCombiRestante (unsigned & CptTot, CMat Grid)
 * \brief Calcul the player's score
 * \param Grid The matrix
 * \param CptTot Amount of possible combinations remaining
 * 
 */
	bool NombreCombiRestante (unsigned & CptTot, CMat Grid);
	
/**
 * \fn void NumberCrushV1 (string Language, string Difficulty)
 * \brief Regroup all fonctions
 * \param Language Chosen language
 * \param Difficulty Chosen difficulty
 * 
 */
	void NumberCrushV1(string Language, string Difficulty); 

/**
 * \fn void GameOptions (string & Language, string & Difficulty); 
 * \brief Regroup all the games option. 
 * \param Language Chosen language
 * \param Difficulty Chosen difficulty
 * 
 */	
	void GameOptions (string & Language, string & Difficulty); 

/**
 * \fn void Help (string Language)
 * \brief Display the help 
 * \param Language Chosen language
 * 
 */
	void Help (string Language); 
	
/**
 * \fn void StartMenu ()
 * \brief Display the game menu
 * 
 */
	void StartMenu ();
	 
/**
 * \fn void ScoreBoard (unsigned & Score)
 * \brief Function used to show the scoreboard
 *  edit a file which shows the best score
 * \param Score Player's score
 * 
 */	
	void ScoreBoard (unsigned & Score);
	
/**
 * \fn void ChangeMode ()
 * \brief allow to change between standard mode and chrono mode
 * 
 */		
	void ChangeMode(); 
	
	const string KReset   ("0");
	const string KNoir    ("30");
	const string KRouge   ("31");
	const string KVert    ("32");
	const string KJaune   ("33");
	const string KBleu    ("34");
	const string KMAgenta ("35");
	const string KCyan    ("36");
	
	const string KRougeF  ("41");
	
   
	void ClearScreen ()
	{
		cout << "\033[H\033[2J";
	} //ClearScreen
	
	void Couleur (const string & coul)
	{
		cout << "\033[" << coul <<"m";
	} //Couleur
	
	void DisplayLogo ()
	{
		vector<string> VLogo; 
		ifstream ifs; 
		ifs.open ("logo"); //mettre le fichier logo dans le même 
						  //répertoire que le fichier source

		string LineFile; 

		while (getline (ifs, LineFile))
			VLogo.push_back (LineFile); 

		ifs.close (); 

		for(unsigned i = 0; i < VLogo.size (); ++i)
			cout << VLogo[i] << endl; 		
	} //DisplayLogo 
	
	void  DisplayGrid (const CMat & Grid)
	{
		Couleur (KReset);
		ClearScreen ();
		DisplayLogo ();
		cout << "   ";
		for (unsigned i (0); i < Grid.size (); ++i)
			cout << setw (4) << i + 1; 

		cout << endl; 
			
		cout << "   "; 
		for (unsigned i (0); i < Grid.size (); ++i)
			cout << "----";

		cout << endl;

		for (unsigned i (0); i < Grid.size (); ++i)
		{
			cout << setw (2) << i + 1 << '|';
			for (unsigned j (0); j < Grid[i].size (); ++j)
			{
				Couleur (KReset);
				if (Grid[i][j]==1)
				{
					Couleur (KReset);
					cout << setw (4) << Grid[i][j];
				}	
				else if (Grid[i][j]==2)
				{
					Couleur (KNoir);
					cout << setw (4) << Grid[i][j];
				}
				else if (Grid[i][j]==3)
				{
					Couleur (KRouge);
					cout << setw (4) << Grid[i][j];
				}
				else if (Grid[i][j]==4)
				{
					Couleur (KVert);
					cout << setw (4) << Grid[i][j];
				}
				else if (Grid[i][j]==5)
				{
					Couleur (KJaune);
					cout << setw (4) << Grid[i][j];
				}
				else if (Grid[i][j]==6)
				{
					Couleur (KBleu);
					cout << setw (4) << Grid[i][j];
				}
				else if (Grid[i][j]==7)
				{
					Couleur (KMAgenta);
					cout << setw (4) << Grid[i][j];
				}
				else if (Grid[i][j]==8)
				{
					Couleur (KCyan);
					cout << setw (4) << Grid[i][j];
				}
				else 
				{
					Couleur (KRougeF);
					cout << setw (4) << Grid[i][j];
				}
			}
			Couleur (KReset);
			cout << endl;	
		}
	} //DisplayGrid
	
	void InitGrid (CMat & Grid, unsigned Size, unsigned NbCandies)
	{
		Grid.resize (Size);
		for (unsigned i (0); i < Grid.size(); ++i)
			Grid[i].resize (Size);
		for (unsigned i (0); i < Grid.size (); ++i)	
			for (unsigned j (0); j < Grid[i].size (); ++j)
				Grid[i][j] = rand () % NbCandies + 1;			
	} //InitGrid
	
	bool TestMove (CMat & Grid, const CPosition & Pos, char Direction)
	{
		for ( unsigned i = 0; i < Grid.size () - 1; ++i)
		{
			for (unsigned j = 0; j < Grid.size () - 1; ++j)
			{
				if (j == Grid.size() - 1 || j == Grid.size() || 
					i == Grid.size() - 1 || i == Grid.size()) 
					return false;
			}
		}
		return true;
	} //TestMove
	
	void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction,
					unsigned & NbMove, unsigned & Score)
	{
			switch (Direction)
			{
			  case 'A':
			  case 'a':
				if (0 == Pos.second || Grid[Pos.first][Pos.second - 1]
					== 0 || Grid[Pos.first][Pos.second] == 0)
				{
					cout << "Impossible" << endl;
				}
				else
				{
					swap (Grid[Pos.first][Pos.second],
						  Grid[Pos.first][Pos.second - 1]);
					--NbMove;
				}
					break;
			  case 'Z':
			  case 'z':
				if(Pos.first == 0 || Grid[Pos.first - 1][Pos.second]
				   == 0 || Grid[Pos.first][Pos.second] == 0) 
				{
					cout << "Impossible" << endl;
				}
				else
				{
					swap (Grid[Pos.first][Pos.second],
						  Grid[Pos.first - 1][Pos.second]);
					--NbMove;
				}
					break;
			  case 'E':
			  case 'e':
				if (Pos.second == Grid.size() - 1 || 
					Grid[Pos.first][Pos.second + 1] == 0 ||
					Grid[Pos.first][Pos.second] == 0)
				{
					cout << "Impossible" << endl;
				}
				else
				{
					swap (Grid[Pos.first][Pos.second],
						  Grid[Pos.first][Pos.second + 1]);
					--NbMove;
				}
					break;
			  case 'S':
			  case 's':
				if (Pos.first == Grid.size() - 1 || Grid[Pos.first + 1]
					[Pos.second] == 0 || Grid[Pos.first][Pos.second] == 0)
				{
					cout << "Impossible" << endl;
				}
				else
				{
					swap (Grid[Pos.first][Pos.second], Grid[Pos.first + 1]
						  [Pos.second]);
					--NbMove;
				}
					break;
			  case 'q':
			  case 'Q':
					Score = 0;
					break;
			  default:		
				cout << "Retry" << endl; 
				cin.ignore (numeric_limits<streamsize>::max(), '\n');
			}
	} //MakeAMove
	
	bool AtLeastThreeInAColumn (const CMat & Grid, CPosition & Pos,
								unsigned & HowMany) 
	{
		HowMany = 0;
		unsigned i = 1;
		for (; (i < Grid.size ()) && (HowMany < 2); ++i)
		{
			if (Grid[i - 1][Pos.second] == 0 || Grid[i - 1][Pos.second]
				!= Grid[i][Pos.second])
			{
				HowMany = 0;
				continue;
			}
			++HowMany;
		}
		if (2 == HowMany) 
		{
			HowMany = 1;
			i -= 3;
			Pos = make_pair (i, Pos.second);
			for (; (i < Grid.size () - 1) && (Grid[i + 1][Pos.second]
				 == Grid[i][Pos.second]); ++i)
				++HowMany;
			return true;
		}
		else
			return false;
	} //AtLeastThreeInAColumn()

	bool AtLeastThreeInARow (const CMat & Grid, CPosition & Pos,
							 unsigned & HowMany)
	{
		HowMany = 0;
		unsigned i = 1;
		for (; (i < Grid.size ()) && (HowMany < 2); ++i)
		{
			if (Grid[Pos.first][i - 1] == 0 || Grid[Pos.first][i - 1] !=
				Grid[Pos.first][i])
			{
				HowMany = 0;
				continue;
			}
			++HowMany;
		}
		if (2 == HowMany) 
		{
			HowMany = 1;
			i -= 3;
			Pos = make_pair (Pos.first, i);
			for (; (i < Grid.size () - 1) && (Grid[Pos.first][i] == 
				 Grid[Pos.first][i + 1]); ++i)
				++HowMany;
			return true;
		}
		else
			return false;
	} //AtLeastThreeInARow	

	void RemovalInColumn (CMat & Grid, const CPosition & Pos,
						  unsigned  HowMany)
	{
    	unsigned i = Pos.first;
		for (; (i < Grid.size () - 1) && 
				(Grid[i + 1][Pos.second] == Grid[i][Pos.second]); ++i)
			Grid[i][Pos.second] = 0;
		Grid[i][Pos.second] = 0;
		unsigned Cpt = 0;
		for (unsigned j = i; Cpt < HowMany; --j)
		{
			for (unsigned k = j; k < Grid.size() - 1; ++k)
				swap (Grid[k][Pos.second], Grid[k+1][Pos.second]);
			++Cpt;
		} 
	} //RemovalInColumn

    void RemovalInRow (CMat & Grid, const CPosition & Pos, 
					   unsigned  HowMany)
    {
		unsigned i = Pos.second;
		for (; (i < Grid.size () - 1) && 
				(Grid[Pos.first][i + 1] == Grid[Pos.first][i]); ++i)
			Grid[Pos.first][i] = 0;
		Grid[Pos.first][i]= 0;
		unsigned Cpt = 0;
		for (unsigned j = Pos.second; Cpt < HowMany; ++j)
		{
			for (unsigned k = Pos.first; k < Grid.size () - 1; ++k)
				swap (Grid[k][j],Grid[k+1][j]);
			++Cpt;
		}
    } //RemovalInRow

	bool FullColumn (CMat & Grid, CPosition & Pos)
	{
		for (unsigned i = 0; i < Grid.size (); ++i)
			if (Grid[0][i] == 0)
			{
				Pos = make_pair (0, i);
				return true;
			}
		return false;
	} //FullColumn
	
	void RemovalFullColumn (CMat & Grid, const CPosition & Pos)
    {
		for (unsigned i = Pos.second; i < Grid.size ()-1; ++i)
		{
			for (unsigned k = 0; k < Grid.size (); ++k)
				swap (Grid[k][i], Grid[k][i + 1]);
			
		}
    } //RemovalFullColumn

    void CalculScore (unsigned & Score, unsigned HowMany)
	{
		if (HowMany == 3)
			Score = Score + 3;
		else if (HowMany == 4)
			Score = Score + 6;
		else if (HowMany >= 5)
			Score = Score + 9;
	} //CalculScore
	
	bool NombreCombiRestante (unsigned & CptTot, CMat Grid)
	{
		unsigned Cpt1 = 0;
		unsigned Cpt2 = 0;
		unsigned Cpt3 = 0;
		unsigned Cpt4 = 0;
		unsigned Cpt5 = 0;
		unsigned Cpt6 = 0;
		unsigned Cpt7 = 0;
		unsigned Cpt8 = 0;
		for (unsigned Li = 0; Li < Grid.size(); ++Li)
		{
			for (unsigned Col = 0; Col < Grid.size() ; ++Col)
			{
				if (Grid[Li][Col] == 1)
					++Cpt1;
				else if (Grid[Li][Col] == 2)
					++Cpt2;
				else if (Grid[Li][Col] == 3)
					++Cpt3;
				else if (Grid[Li][Col] == 4)
					++Cpt4;
				else if (Grid[Li][Col] == 5)
					++Cpt5;
				else if (Grid[Li][Col] == 6)
					++Cpt6;		
				else if (Grid[Li][Col] == 7)
					++Cpt7;	
				else if (Grid[Li][Col] == 8)
					++Cpt8;
				CptTot = Cpt1/3 + Cpt2/3 + Cpt3/3 + Cpt4/3 + Cpt5/3 + 
						 Cpt6/3 + Cpt7/3 + Cpt8/3;
			}
		}
		if (CptTot == 0) return false;
		return true;
	} //NombreCombiRestante
	
	void NumberCrushV1 (string Language, string Difficulty)
	{
		srand(time(NULL));
		unsigned Size = 0;
		unsigned NbCandies = 0; 
		unsigned NbMove = 0; 
		unsigned Score = 0; 
		unsigned CptTot = 0;

		if(Difficulty == "Easy")
		{
			Size = 10; 
			NbCandies = 4; 
			NbMove = 40; 
		}
		else if(Difficulty == "Medium")
		{
			Size = 10;
			NbCandies = 6;  
			NbMove = 35; 
			Score += 500;
		}
		else
		{
			Size = 10; 
			NbCandies = 8; 
			NbMove = 30; 
			Score += 1000;
		}

		CMat Grid;
		CPosition Pos;
		unsigned HowMany = 0; 
		InitGrid (Grid, Size, NbCandies);

		time_t Debut, Arrive, Ecart;
		time (&Debut); 

		char Direction; 

		for (; NbMove != 0 && Direction != 'q' ;)
		{
			HowMany = 0; 
			CPosition Deb;
			for (unsigned j = 0; j <= 3; ++j)
			{ 
				for (unsigned i = 0; i < Grid.size (); ++i)
				{
					Deb = make_pair (i, 0);
					while (AtLeastThreeInARow (Grid, Deb, HowMany))
					{
						CalculScore (Score, HowMany);
						RemovalInRow (Grid, Deb, HowMany);
					}
				}
				if (FullColumn (Grid, Deb))
					RemovalFullColumn (Grid, Deb);
				for (unsigned i = 0; i < Grid.size (); ++i)
				{
					Deb = make_pair (0, i);
					while (AtLeastThreeInAColumn (Grid, Deb, HowMany))
					{
						CalculScore (Score, HowMany);
						RemovalInColumn (Grid, Deb, HowMany);
					}
				}
			}

			DisplayGrid (Grid);
			NombreCombiRestante (CptTot, Grid);
			if (!NombreCombiRestante (CptTot, Grid)) break;
			Language == "Fr" ? cout << "Il reste : " << CptTot
									<< " combinaisons possible" << endl : 
							   cout << CptTot << " combo remaining" << endl;
			Language == "Fr" ? cout << "Il reste : " << NbMove
									<< " deplacements" << endl : 
							   cout << NbMove << " moves remaining" << endl;

			Language == "Fr" ? cout << "Quelle est la position du nombre"
										" que vous souhaitez déplacer ?" 
									<< endl : cout 
									<< "Where is located the number "
										"you want to move ?" << endl; 

			Language == "Fr" ? cout << "Numéro de la ligne : " : 
							   cout << "Spot of the line : " ; 
			
			
			cin >> Pos.first; 
			
			for (; Pos.first > Grid.size() || cin.fail ();) 
			{
				cin.clear ();
				cin.ignore (numeric_limits<streamsize>::max(), '\n');
				Language == "Fr" ? cout << "C'est un numéro : " : cout 
								   << "Enter unsigned : " ; 
				cin >> Pos.first; 
			}
			
			--Pos.first;
	
			Language == "Fr" ? cout << "Numéro de la colonne : " : cout 
							   << "Spot of the column : "; 
			cin.ignore (numeric_limits<streamsize>::max(), '\n');
			cin >> Pos.second; 
			
			for (; Pos.second > Grid.size() || cin.fail();) 
			{
				cin.clear ();
				cin.ignore (numeric_limits<streamsize>::max(), '\n');	
				Language == "Fr" ? cout << "C'est un numéro : " : cout
										<< "Enter unsigned : "; 
				cin >> Pos.second;
			}
			
			--Pos.second;

			Language == "Fr" ? cout << "Déplacements disponibles :" << endl
									<< "A - Gauche" << endl
									<< "Z - Haut" << endl
									<< "E - Droite" << endl
									<< "S - Bas" << endl
							 : cout << "Move available :" << endl
							 		<< "A - Left " << endl
							 		<< "Z - Top" << endl
							 		<< "E - Right" << endl
							 		<< "S - Bottom" << endl; 
			cin >> Direction;
			
			if (TestMove (Grid, Pos, Direction))
			{
				MakeAMove (Grid, Pos, Direction, NbMove, Score);
			}
		}

		Language == "Fr" ? cout << "Fin de partie" << endl : 
						   cout << "End of game" << endl; 

		time (&Arrive);
		Ecart = Arrive - Debut;
		Score = (Score * 10000) / (NbMove + (Ecart/10));
		ScoreBoard (Score);
	} //NumberCrushV1

	void GameOptions (string & Language, string & Difficulty)
	{
		char ModOptions; 
		for (char Choice; Choice != 'q' && Choice != 'Q';)
		{
			/* Affichage du menu de modification des options en Français
			 *  ou en Anglais (tout dépend de la valeur 
			 * du paramètre Language)*/ 			
			ClearScreen ();
			DisplayLogo (); 
			Language == "Fr" ? cout << endl
									<< "D - Modifier la difficulté" << endl
									<< "L - Modifier le langage "
									   "( 1 : Fr / 2 : En )" << endl
									<< "Q - Retour au menu" << endl
							 : cout << endl
							   		<< "D - Change difficulty" << endl
							   		<< "L - Change language "
									   "( 1 : Fr / 2 : En )" << endl
							   		<< "Q - Exit options" << endl; 
			cin >> Choice; 

			// Choix de modification d'une option
			switch (Choice)
			{
			  case 'L':
			  case 'l': 
				cin >> ModOptions; 
				ModOptions == '1' ? Language ="Fr" : Language = "En"; 
				break; 

			  case 'D':
			  case 'd': 
				cout << endl; 
				Language == "Fr" ? cout << " Modifier la difficulté : " 
									    << endl 
										<< " E - Facile" << endl
										<< " M - Moyen" << endl
										<< " H - Difficile" << endl
							     : cout << " Change difficulty : " << endl
										<< " E - Easy" << endl 
										<< " M - Medium" << endl 
										<< " H - Hard" << endl; 
				cin >> ModOptions; 
				switch(ModOptions)
				{
				  case 'E':
				  case 'e': 
					Difficulty = "Easy";
					cout << endl; 
					break; 

				  case 'M':
				  case 'm': 
					Difficulty = "Medium";
					cout << endl;
					break; 

				  case 'H':
				  case 'h':
					Difficulty = "Hard"; 
					cout << endl; 
					break; 

				  default: 
					Language == "Fr" ? cerr << "Saisie incorrecte" << endl
									 : cerr << "Invalid entry" << endl; 
				}

			  case 'Q':
			  case 'q': 
				break;

			  default:
				Language == "Fr" ? cerr << "Saisie incorrecte" << endl
								 : cerr << "Invalid entry" << endl; 
			}
		}
	} //GameOptions

	void Help (string Language)
	{	
		vector <string> VHelp; 
		ifstream ifs; 
		Language == "Fr" ? ifs.open ("aide.txt") : ifs.open ("help.txt"); 
		/* mettre les fichiers text dans le même répertoire 
		   que le fichier source*/

		string LineFile; 

		while (getline (ifs, LineFile))
			VHelp.push_back (LineFile); 

		ifs.close (); 

		for (unsigned i = 0; i < VHelp.size (); ++i)
			cout << VHelp[i] << endl; 		
	
	} //Help

	void StartMenu () 
	{
		string Lang = "Fr"; 
		string Difficulty = "Easy";

		ClearScreen (); 
		DisplayLogo (); 

		char Choice;
		while (Choice != 'q' || Choice != 'Q')
		{ 
			Lang == "Fr" ? cout << endl
						   	    << "S - Commencer une partie" << endl
						   	    << "C - Changer en mode chrono" << endl 
						  		<< "O - Personnaliser les options" << endl
						   		<< "H - Aide" << endl
						   		<< "Q - Quitter" << endl
						 : cout << endl
						   		<< "S - Start a game" << endl
						   		<< "C - Change for time mode" << endl
						   		<< "O - Change settings" << endl
						   		<< "H - Help" << endl 
						   		<< "Q - Leave the game" << endl; 

			cin >> Choice; 

			switch (Choice) 
			{
			  case 's':
			  case 'S': 
				NumberCrushV1 (Lang, Difficulty);  
				break; 

			  case 'o':
			  case 'O':
				GameOptions (Lang, Difficulty);
				break;  

			  case 'h': 
			  case 'H': 
				Help (Lang); 
				break; 

			  case 'q':
			  case 'Q': 
				cout << "A bientôt! / Good bye!" << endl; 
				break; 
			  case 'c':
			  case 'C': 
				ChangeMode ();  
				break;
			  default: 
				cout << "Choix incorrect / Unkown command" << endl; 
			}
			if (Choice == 'Q' || Choice == 'q') break;
		}
	} //StartMenu
	void ScoreBoard (unsigned & Score)
	{
		string Pseudo;
		cout << "Entrez votre pseudo / Enter Player id : " << endl;
		cin >> Pseudo;
		ClearScreen();
		vector <string> VScore;
		ofstream ofs;
		ofs.open ("score.txt");
		ofs << setw (10)  <<  Pseudo << endl <<  "---------------" 
			<< endl << setw (9) << Score << endl << "---------------" 
			<< endl;
		ofs.close ();
		ifstream ifs; 
		ifs.open ("score.txt"); 
		string LineFile;
		while (getline (ifs, LineFile))
			VScore.push_back (LineFile); 
		ifs.close (); 

		for (unsigned i = 0; i < VScore.size (); ++i)
			cout << VScore[i] << endl; 		
	} //ScoreBoard
	void ChangeMode ()
	{
		system ("g++ -std=c++11 -Wall NumberCrushChronoV1.cxx -o Chrono");
		system ("./Chrono");
	} //ChangeMode
} //namespace

int main ()
{
	ClearScreen ();
	cout << endl; 
	StartMenu (); 
	cout << endl; 

	return 0; 
} //main
