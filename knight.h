#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int MADBEAR = 1;
const int BANDIT = 2;
const int LordLupin = 3;
const int ELF = 4;
const int TROLL = 5;
const int SHAMAN = 6;
const int VAJSH = 7;
const int EXCALIBUR = 8;
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
struct Status
{
    int magic = -1;
    int frog = -1;
    bool Excal = false;
};

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

void checkStatus(knight &theKnight, Status &Knight, int level)
{
    if(Knight.magic > 0)
    {
        Knight.magic--;
        if(Knight.magic == 0) {
            theKnight.HP = theKnight.HP * 5;
            Knight.magic = -1;
        }
    }

    if(Knight.frog > 0)
    {
        Knight.frog--;
        if(Knight.frog == 0) {
            theKnight.level = level;
            Knight.frog = -1;
        }
    }
}
void checklevel0(knight &theKnight, Status &Knight, int theEvent, int i, int level, bool &process)
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
    checkStatus(theKnight, Knight,level);
}

void ShamanVajsh(knight &theKnight, Status &Knight, int i, int level, int maxHP, int *arrEvent, bool &process){
    if(Knight.magic > 0 || Knight.frog > 0)
    {
        checkStatus(theKnight, Knight, level);
    }
    else {
        i++;
        int b = i % 10;
        int levelO = i > 6 ? (b > 5 ? b : 5) : b;
        if (theKnight.level > levelO) {
            theKnight.level = theKnight.level + 2;
            theKnight.DF = theKnight.DF + 2;
            if (theKnight.level >= 10) {
                theKnight.level = 10;
            }
            if (theKnight.DF >= 20) {
                theKnight.DF = 20;
            }
        }
        else if (theKnight.level == levelO) {
            theKnight.level = theKnight.level;
            theKnight.DF = theKnight.DF;
        }
        else if (theKnight.level < levelO && arrEvent[i - 1] == 6)
        {
            Knight.magic = 3;
            theKnight.HP = theKnight.HP / 5;
            if (theKnight.remedy >= 1) {
                theKnight.remedy--;
                theKnight.HP = maxHP;
                Knight.magic = -1;
            } else {
                if (theKnight.HP < 5) {
                    theKnight.HP = 1;
                }
            }
        }
        else if (theKnight.level < levelO && arrEvent[i - 1] == 7)
        {
            Knight.frog = 3;
            theKnight.level = 1;
            if (theKnight.remedy >= 1) {
                theKnight.remedy--;
                theKnight.level = level;
                Knight.frog = -1;
            }
        }
    }
}

void checkExcal(knight &theKnight, Status &Knight, int theEvent, int i, int level, int maxHP, int *arrEvent, bool &process)
{
    if(Knight.Excal == true) {
        if (arrEvent[i] < 6) {
            int gold[6] = {0, 10, 20, 30, 40, 50};
            theKnight.level = theKnight.level + 1;
            theKnight.DF = theKnight.DF + 1;
            theKnight.gold = theKnight.gold + gold[theEvent];
            if (theKnight.level >= 10) {
                theKnight.level = 10;
            }
            if (theKnight.DF >= 20) {
                theKnight.DF = 20;
            }
            if (theKnight.gold >= 500) {
                theKnight.gold = 500;
            }
        } else if (arrEvent[i] == 6 || arrEvent[i] == 7) {
            ShamanVajsh(theKnight, Knight, i, level, maxHP, arrEvent, process);
        }
    }
    else
    {
        if(arrEvent[i] < 6)
        {
            checklevel0(theKnight, Knight, theEvent, i, level, process);
        }
        else if(arrEvent[i] == 6 || arrEvent[i] == 7)
        {
            ShamanVajsh(theKnight, Knight, i, level, maxHP, arrEvent, process);
        }
    }
}

int startJourney(knight theKnight, int nEvent, int *arrEvent){
    bool process = true;
    int result;
    Status Knight;
    int level = theKnight.level;
    int maxHP = theKnight.HP;
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
                checkExcal(theKnight, Knight, theEvent, i, level, maxHP, arrEvent, process);
                break;

            case BANDIT:
                checkExcal(theKnight, Knight, theEvent, i, level, maxHP, arrEvent, process);
                break;

            case LordLupin:
                checkExcal(theKnight, Knight, theEvent, i, level, maxHP, arrEvent, process);
                break;

            case ELF:
                checkExcal(theKnight, Knight, theEvent, i, level, maxHP, arrEvent, process);
                break;

            case TROLL:
                checkExcal(theKnight, Knight, theEvent, i, level, maxHP, arrEvent, process);
                break;

            case SHAMAN:
                checkExcal(theKnight, Knight, theEvent, i, level, maxHP, arrEvent, process);
                break;

            case VAJSH:
                checkExcal(theKnight, Knight, theEvent, i, level, maxHP, arrEvent, process);
                break;

            case EXCALIBUR:
                Knight.Excal = true;
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

