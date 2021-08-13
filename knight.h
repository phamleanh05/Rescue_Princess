#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int MADBEAR = 1;
const int BANDIT = 2;
const int LL = 3;
const int ELF = 4;
const int TROLL = 5;
const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

struct knight
{
   int HP;
   int DF;
   int level;
   int remedy;
   int gold;
   int phoenixdown;
};

// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0
void checkHP(knight &theKnight, int maxHP, bool &process)
{
    if(theKnight.HP <= 0)
    {
        if(theKnight.phoenixdown == 0)
        {
            process = false;
        }
        else if(theKnight.phoenixdown > 0)
        {
            theKnight.phoenixdown--;
            theKnight.HP = maxHP;
        }
    }
}

void checklevel0(knight &theKnight, int theEvent, int i, bool &process)
{
    int maxHP = theKnight.HP;
    double base[6]= {0, 1, 2.5, 5.5, 7.5, 9.5};
    int gold[6] = {0, 10, 20, 30, 40, 50};
    i++;
    int b = i%10;
    int levelO = i>6? (b> 5? b : 5) : b;
    double baseDamage = base[theEvent];
    int damage = baseDamage * levelO * 10;
    if(theKnight.level > levelO)
    {
        theKnight.level = theKnight.level + 1;
        theKnight.DF = theKnight.DF + 1;
        theKnight.gold = theKnight.gold + gold[theEvent];
        if(theKnight.level >= 10)
        {
            theKnight.level = 10;
        }
        if(theKnight.DF >= 20)
        {
            theKnight.DF = 20;
        }
        if(theKnight.gold>= 500)
        {
            theKnight.gold = 500;
        }

    }
    else if(theKnight.level == levelO)
    {
        theKnight.level = theKnight.level;
        theKnight.DF = theKnight.DF;
    }
    else
    {
        if(damage > theKnight.DF)
        {
            theKnight.HP = theKnight.HP + theKnight.DF - damage;
            checkHP(theKnight,maxHP,process);
        }
        else{
            theKnight.HP -= damage;
            checkHP(theKnight,maxHP,process);
        }
    }
}
int startJourney(knight theKnight, int nEvent, int *arrEvent){
    bool process = true;
    int result;
    for (int i = 0; i < nEvent; i++)
    {
        int theEvent = arrEvent[i];
        switch (theEvent)
        {
            case 0:
                process = true;
                result = theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown;
                return result;
            case MADBEAR:
                checklevel0(theKnight,theEvent, i, process);
                break;

            case BANDIT:
                checklevel0(theKnight,theEvent, i, process);
                break;

            case LL:
                checklevel0(theKnight,theEvent, i, process);
                break;

            case ELF:
                checklevel0(theKnight,theEvent, i, process);
                break;

            case TROLL:
                checklevel0(theKnight,theEvent, i, process);
                break;

        }
    }
    if(process == false)
    {
        result = -1;
    }
    else
    {
        result = theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown;
    }
    return result;
}

