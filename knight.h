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
const int MYTHRIL = 9;
const int EXPOOR = 10;
const int MUSHMARIO = 11;
const int MUSHFIBO = 12;
const int MUSHGHOST = 13;
const int MUSHKNIGHT = 14;
const int Remedy = 15;
const int PhoenixDown = 16;
const int MERLIN = 17;
const int NINAdeRings = 18;
const int ABYSS = 19;
const int ODIN = 23;
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
    int Mythril = -1;
    int Physical = 7;
    int meetOdin = -1;
    bool Excal = false;
    bool Expoor = false;
};

void checkMax(knight &theKnight)
{
    if(theKnight.HP >= 999)
    {
        theKnight.HP = 999;
    }
    if(theKnight.level >= 10)
    {
        theKnight.level = 10;
    }
    if(theKnight.DF >= 20)
    {
        theKnight.DF = 20;
    }
    if(theKnight.gold >= 500)
    {
        theKnight.gold = 500;
    }
    if(theKnight.remedy >= 99)
    {
        theKnight.remedy = 99;
    }
    if(theKnight.phoenixdown >= 99)
    {
        theKnight.phoenixdown = 99;
    }
}
void checkHP(knight &theKnight, int MaxHP, bool &process) // MaxHP = Hp lúc đầu
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
            theKnight.HP = MaxHP;
        }
    }
}

bool checkFriend(int a, int b)
{
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i <= a; i++)
        if (a % i == 0)
            sum1 += i;
    for (int i = 1; i <= b; i++)
    {
        if (b % i == 0)
            sum2 += i;
    }
    return (sum1 / a) == (sum2 / b);
}

void checkStatus(knight &theKnight, Status &Knight,int MaxHP, int firstLevel)
{
    if(Knight.magic > 0)
    {
        Knight.magic--;
        if(Knight.magic == 0) {
            theKnight.HP = theKnight.HP * 5;
            Knight.magic = -1;
            if(theKnight.HP >= MaxHP)
            {
                theKnight.HP = MaxHP;
            }
        }
    }

    if(Knight.frog > 0)
    {
        Knight.frog--;
        if(Knight.frog == 0) {
            theKnight.level = firstLevel;
            Knight.frog = -1;
        }
    }
}

void checklevel0(knight &theKnight, Status &Knight, int theEvent, int i, int firstLevel, bool &process)
{
    int MaxHP = theKnight.HP;
    double base[6]= {0, 1, 2.5, 5.5, 7.5, 9.5};
    int gold[6] = {0, 10, 20, 30, 40, 50};
    i++;
    int b = i%10;
    int levelO = i>6? (b> 5? b : 5) : b;
    double baseDamage = base[theEvent];
    int damage = baseDamage * levelO * 10;
    if(Knight.meetOdin > 0)
    {
        Knight.meetOdin--;
        if (Knight.meetOdin == 0)
        {
            Knight.meetOdin = -2;
        }
        if(Knight.Mythril >0)
        {
            Knight.Mythril --;
            if (Knight.Mythril == 0) {
                Knight.Mythril = -1;
            }
        }
        theKnight.level = theKnight.level + 1;
        theKnight.DF = theKnight.DF + 1;
        theKnight.gold = theKnight.gold + gold[theEvent];
        checkMax(theKnight);
        checkStatus(theKnight,Knight,MaxHP,firstLevel);
    }
    else {
        if (Knight.Expoor == true) {
            if (Knight.Mythril > 0) {
                Knight.Mythril--;
                Knight.Physical--;
                theKnight.HP = theKnight.HP;
                if (Knight.Mythril == 0) {
                    Knight.Mythril = -1;
                }
            } else {
                if (damage > theKnight.DF) {
                    theKnight.HP = theKnight.HP + theKnight.DF - damage;
                    checkHP(theKnight, MaxHP, process);
                } else {
                    theKnight.HP -= damage;
                    checkHP(theKnight, MaxHP, process);
                }
            }
        } else {
            if (theKnight.level > levelO) {
                theKnight.level = theKnight.level + 1;
                theKnight.DF = theKnight.DF + 1;
                theKnight.gold = theKnight.gold + gold[theEvent];
                checkMax(theKnight);
            } else if (theKnight.level == levelO) {
                theKnight.level = theKnight.level;
                theKnight.DF = theKnight.DF;
            } else if (theKnight.level < levelO && 0 < Knight.Physical < 7) {
                if (Knight.Mythril > 0) {
                    Knight.Mythril--;
                    Knight.Physical--;
                    theKnight.HP = theKnight.HP;
                    if (Knight.Mythril == 0) {
                        Knight.Mythril = -1;
                    }
                } else {
                    if (damage > theKnight.DF) {
                        theKnight.HP = theKnight.HP + theKnight.DF - damage;
                        checkHP(theKnight, MaxHP, process);
                    } else {
                        theKnight.HP -= damage;
                        checkHP(theKnight, MaxHP, process);
                    }
                }
            }
        }
        checkStatus(theKnight, Knight, MaxHP, firstLevel);
    }
}

void ShamanVajsh(knight &theKnight, Status &Knight, int i, int firstLevel, int MaxHP, int *arrEvent, bool &process){
    i++;
    int b = i % 10;
    int levelO = i > 6 ? (b > 5 ? b : 5) : b;
    if(Knight.meetOdin > 0)
    {
        Knight.meetOdin--;
        if (Knight.meetOdin == 0)
        {
            Knight.meetOdin = -2;
        }
        theKnight.level = theKnight.level + 2;
        theKnight.DF = theKnight.DF + 2;
        checkMax(theKnight);
        checkStatus(theKnight, Knight, MaxHP, firstLevel);
    }
    else {
        if (Knight.magic > 0 || Knight.frog > 0) {
            checkStatus(theKnight, Knight, MaxHP, firstLevel);
        } else {
            if (Knight.Expoor == true) {
                if (theKnight.level < levelO && arrEvent[i - 1] == 6) {
                    Knight.magic = 3;
                    theKnight.HP = theKnight.HP / 5;
                    if (theKnight.remedy >= 1) {
                        theKnight.remedy--;
                        theKnight.HP = MaxHP;
                        Knight.magic = -1;
                    } else {
                        if (theKnight.HP < 5) {
                            theKnight.HP = 1;
                        }
                    }
                } else if (theKnight.level < levelO && arrEvent[i - 1] == 7) {
                    Knight.frog = 3;
                    theKnight.level = 1;
                    if (theKnight.remedy >= 1) {
                        theKnight.remedy--;
                        theKnight.level = firstLevel;
                        Knight.frog = -1;
                    }
                }
            } else {
                if (theKnight.level > levelO) {
                    theKnight.level = theKnight.level + 2;
                    theKnight.DF = theKnight.DF + 2;
                    checkMax(theKnight);
                } else if (theKnight.level == levelO) {
                    theKnight.level = theKnight.level;
                    theKnight.DF = theKnight.DF;
                } else if (theKnight.level < levelO && arrEvent[i - 1] == 6) {
                    Knight.magic = 3;
                    theKnight.HP = theKnight.HP / 5;
                    if (theKnight.remedy >= 1) {
                        theKnight.remedy--;
                        theKnight.HP = MaxHP;
                        Knight.magic = -1;
                    } else {
                        if (theKnight.HP < 5) {
                            theKnight.HP = 1;
                        }
                    }
                } else if (theKnight.level < levelO && arrEvent[i - 1] == 7) {
                    Knight.frog = 3;
                    theKnight.level = 1;
                    if (theKnight.remedy >= 1) {
                        theKnight.remedy--;
                        theKnight.level = firstLevel;
                        Knight.frog = -1;
                    }
                }
            }
        }
    }
}

void checkExcal(knight &theKnight, Status &Knight, int theEvent, int i, int firstLevel, int MaxHP, int *arrEvent, bool &process)
{
    if(Knight.meetOdin > 0 && arrEvent[i] < 6) {
        checklevel0(theKnight, Knight, theEvent, i, firstLevel, process);
    }
    else if(Knight.meetOdin > 0 && arrEvent[i] == 6 || arrEvent[i] == 7)
    {
        ShamanVajsh(theKnight, Knight, i, firstLevel, MaxHP, arrEvent, process);
    }
    else {
        if (Knight.Excal == true) {
            if (Knight.Expoor == true) {
                checklevel0(theKnight, Knight, theEvent, i, firstLevel, process);
            } else {
                if (arrEvent[i] < 6) {
                    int gold[6] = {0, 10, 20, 30, 40, 50};
                    theKnight.level = theKnight.level + 1;
                    theKnight.DF = theKnight.DF + 1;
                    theKnight.gold = theKnight.gold + gold[theEvent];
                    checkMax(theKnight);
                } else if (arrEvent[i] == 6 || arrEvent[i] == 7) {
                    ShamanVajsh(theKnight, Knight, i, firstLevel, MaxHP, arrEvent, process);
                }
            }
        } else {
            if (arrEvent[i] < 6) {
                checklevel0(theKnight, Knight, theEvent, i, firstLevel, process);
            } else if (arrEvent[i] == 6 || arrEvent[i] == 7) {
                ShamanVajsh(theKnight, Knight, i, firstLevel, MaxHP, arrEvent, process);
            }
        }
    }
}

void Mushghost(knight &theKnight)
{
    if(theKnight.HP < 51)
    {
        theKnight.HP = 1;
    }
    else if (theKnight.DF < 6)
    {
        theKnight.DF = 1;
    }
    else{
        theKnight.HP -= 50;
        theKnight.DF -= 5;
    }
}

void Merlin(knight &theKnight, Status &Knight, int MaxHP, int firstLevel){
    if(Knight.magic > 0 || Knight.frog >0)
    {
        Knight.magic = -1;
        if(Knight.magic == -1)
        {
            theKnight.HP = theKnight.HP * 5;
            if(theKnight.HP >= MaxHP)
            {
                theKnight.HP = MaxHP;
            }
        }

        Knight.frog = -1;
        if(Knight.frog == -1)
        {
            theKnight.level = firstLevel;
        }
        theKnight.level ++;
        checkMax(theKnight);
        theKnight.HP = MaxHP;
    }
    else{
        theKnight.level ++;
        checkMax(theKnight);
        theKnight.HP = MaxHP;
    }
}

void NINA(knight &theKnight, Status &Knight, int MaxHP, int firstLevel)
{
    bool checkfriend = checkFriend(theKnight.HP, theKnight.gold);
    if(checkfriend)
    {
        Knight.magic = -1;
        Knight.frog = -1;
        theKnight.HP = MaxHP;
        return;
    }
    else {
        if (theKnight.gold > 50) {
            if (Knight.magic > 0 || Knight.frog > 0) {
                theKnight.gold -= 50;
                Knight.magic = -1;
                if (Knight.magic == -1) {
                    theKnight.HP = theKnight.HP * 5;
                    if (theKnight.HP >= MaxHP) {
                        theKnight.HP = MaxHP;
                    }
                }

                Knight.frog = -1;
                if (Knight.frog == -1) {
                    theKnight.level = firstLevel;
                }

                if (theKnight.gold > 0 && theKnight.HP < MaxHP) {
                    theKnight.gold--;
                    theKnight.HP++;
                }
            } else {
                int a = MaxHP - theKnight.HP;
                if (a <= theKnight.gold) {
                    theKnight.HP = MaxHP;
                    theKnight.gold -= a;
                }
            }
        }
    }
}

void theAbyss()
{

}
int startJourney(knight theKnight, int nEvent, int *arrEvent){
    bool process = true;
    int result;
    Status Knight;
    int firstLevel = theKnight.level;
    int MaxHP = theKnight.HP;
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
                checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                break;

            case BANDIT:
                checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                break;

            case LordLupin:
                checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                break;

            case ELF:
                checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                break;

            case TROLL:
                checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                break;

            case SHAMAN:
                checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                break;

            case VAJSH:
                checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                break;

            case EXCALIBUR:
                Knight.Excal = true;
                break;

            case MYTHRIL:
                if(Knight.Physical == 7) {
                    Knight.Mythril = 5;
                    Knight.Physical--;
                    if(Knight.Physical == 0){
                        Knight.Physical = 7;
                    }
                }
                break;

            case EXPOOR:
                if(theKnight.level >= 5)
                {
                    Knight.Expoor = false;
                }
                else
                {
                    Knight.Expoor = true;
                }
                break;

            case MUSHMARIO:
                theKnight.HP += 50;
                if(theKnight.HP >= MaxHP)
                {
                    theKnight.HP = MaxHP;
                }
                break;

            case MUSHFIBO:
                break;

            case MUSHGHOST:
                Mushghost(theKnight);
                break;

            case MUSHKNIGHT:
                MaxHP += 50;
                theKnight.HP = MaxHP;
                checkMax(theKnight);
                break;

            case Remedy:
                theKnight.remedy ++;
                checkMax(theKnight);
                break;

            case PhoenixDown:
                theKnight.phoenixdown ++;
                checkMax(theKnight);
                break;

            case MERLIN:
                Merlin(theKnight, Knight, MaxHP, firstLevel);
                break;

            case NINAdeRings:
                NINA(theKnight, Knight, MaxHP, firstLevel);
                break;

            case ABYSS:
                if(theKnight.gold > 50)
                {
                    if(theKnight.level < 7)
                    {
                        theKnight.gold -= 50;
                    }
                }
                else
                {
                    theAbyss();
                }
                break;

            case ODIN:
                if(Knight.meetOdin == -1)
                {
                    Knight.meetOdin = 3;
                    checkExcal(theKnight, Knight, theEvent, i, firstLevel, MaxHP, arrEvent, process);
                }
                else if(Knight.meetOdin == -2)
                {
                    break;
                }
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

