#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;
void hangman();

int main()
{
    hangman();

    return 0;
}

void wordRandomize(string &randomWord, string &randomSave, string &randomHint)
{
    int generator;
    srand((unsigned) time(0));
    generator = rand() % 20 + 1;
  
    switch(generator){
        case 1:
        {
            randomWord = "M A R I O";
            randomSave = "M _ _ _ O";
            randomHint = "Character in 2D game";
            break;
        }
        case 2:
        {
            randomWord = "A B S U R D";
            randomSave = "A _ _ _ _ D";
            randomHint = "Synonym of 'illogical' ";
            break;
        }
        case 3:
        {
            randomWord = "M O U S E P A D";
            randomSave = "M _ _ _ _ _ _ D";
            randomHint = "PC peripheral";
            break;
        }
        case 4:
        {
            randomWord = "S U B W A Y";
            randomSave = "S _ _ _ _ Y";
            randomHint = "An underground tunnel... or a famous fast food chain";
            break;
        }
        case 5:
        {
            randomWord = "B A N J O";
            randomSave = "B _ _ _ O";
            randomHint = "A stringed musical instrument";
            break;
        }
        case 6:
        {
            randomWord = "B E A C H";
            randomSave = "B _ _ _ H";
            randomHint = "Coast of a sea/ocean";
            break;
        }
        case 7:
        {   
            randomWord = "G R A P H";
            randomSave = "G _ _ _ H";
            randomHint = "Diagram that shows multiple variables";
            break;
        }
        case 8:
        {
            randomWord = "C R Y S T A L";
            randomSave = "C _ _ _ _ _ L";
            randomHint = "Clear, transparent and beautiful rock";
            break;
        }
        case 9:
        {
            randomWord = "L U C K Y";
            randomSave = "L _ _ _ Y";
            randomHint = "Fortune";
            break;
        }
        case 10:
        {
            randomWord = "K E T C H U P";
            randomSave = "K _ _ _ _ _ P";
            randomHint = "";
            break;
        }
        case 11:
        {
            randomWord = "Z O M B I E";
            randomSave = "Z _ _ _ _ E";
            randomHint = "Dead character whose corpse was revived (movies / video games)";
            break;
        }
        case 12:
        {
            randomWord = "Z E B R A";
            randomSave = "Z _ _ _ A";
            randomHint = "African animal with black and white stripes";
            break;
        }
        case 13:
        {
            randomWord = "T I G E R";
            randomSave = "T _ _ _ R";
            randomHint = "Large wild animal with orange fur and black stripes";
            break;
        }
        case 14:
        {
            randomWord = "K E Y B O A R D";
            randomSave = "K _ _ _ _ _ _ D";
            randomHint = "PC Peripheral";
            break;
        }
        case 15:
        {
            randomWord = "D R A W E R";
            randomSave = "D _ _ _ _ R";
            randomHint = "Furniture meant to storage clothes";
            break;
        }
        case 16:
        {
            randomWord = "R A M E N";
            randomSave = "R _ _ _ N";
            randomHint = "Japanese soup with noodles";
            break;
        }
        case 17:
        {
            randomWord = "F R A N C E";
            randomSave = "F _ _ _ _ E";
            randomHint = "Country in West Europe";
            break;
        }
        case 18:
        {
            randomWord = "J O Y S T I C K";
            randomSave = "J _ _ _ _ _ _ K";
            randomHint = "Device meant to control devices such as a computer";
            break;
        }
        case 19:
        {
            randomWord = "M A C H I N E";
            randomSave = "M _ _ _ _ _ E";
            randomHint = "System that uses power and has several parts and structures";
            break;
        }
        case 20:
        {
            randomWord = "W A T E R";
            randomSave = "W _ _ _ R";
            randomHint = "Essential substance for life";
            break;
        }

    }
}


void hangman()
{
    string alph = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
    string word;
    string save;
    string hint;
    wordRandomize(word,save,hint);


    cout << endl;
    cout << "Available letters: " << endl
         << endl;
    cout << alph << endl
         << endl;

    int length = word.size();

    cout << "Your word is: " << endl << endl;
    cout << save << endl << endl;
    cout << " " << endl << endl;
    cout << " " << endl << endl;

    char a;
    int mistakes = 0;

    bool wordWasGuessed = false;

    for (int i = 0; mistakes != 5 && wordWasGuessed == false; i++)
    {
        cin >> a;

        size_t found = word.find(a);
        if (found != string::npos) // GUESSED
        {
            cout << a << " was one of the letters!" << endl
                 << endl;
            for (int i = 0; i <= length; i++)
            {
                if (i > 0 && i < length - 1 && word.at(i) != word.at(1))
                {
                    if (word.at(i) == word.at(found)) 
                    {
                        string aux = "";
                        aux+=a;
                        save.replace(found, 1, aux);
                        cout << endl << save << endl;
                    } 
                }
                if(word==save)
                {
                    wordWasGuessed = true;
                    break;
                }
            }
        }
        else // NOT GUESSED
        {
            cout << "The word does not contain " << a << endl
                 << endl;
            for (int i = 0; i <= length; i++)
            {
                if (i == 0)
                    cout << word.at(i) << " ";
                else if (i > 0 && i < length - 1 && word.at(i) != word.at(1))
                    cout << "_"
                         << " ";
                else if (i == length - 1)
                    cout << word.at(i) << " ";
            }
            mistakes++;
            if (mistakes == 4){

                cout<< endl << endl ;
                cout << "You have 1 try left.";
                cout << endl << endl << endl;
                cout << "Your hint is: " << endl << hint ;
                cout << endl;
            }
            else{
                cout << endl << endl;
                cout << "You have " << 5 - mistakes << " tries left." << endl << endl;
            }
        }
        replace(alph.begin(), alph.end(), a, ' ');
        cout << endl;
        cout << "Available letters: " << endl;
        cout << alph << endl << endl;
    }
    if(wordWasGuessed)
        cout<<endl<<"You have guessed the word "<<word<<" ! Game over.";
    else
    { 
        cout<<endl<<"You did not guess the word. Write AGAIN to try again for another word or MENU to go back to the menu.";
        char text[256];
        int n=1000;
        char comandaMENU[5] = {'M' , 'E' , 'N' , 'U' , '\0'};
        char comandaAGAIN[6] = {'A', 'G', 'A', 'I', 'N', '\0'};

        for(int i=0; i<n; i++)
        {
            cin>>text;
            if(strcmp(text, comandaAGAIN)==0)
                hangman();
            // if(strcmp(text, comandaMENU)==0)
            //     start();
        } 
    }
        
}

