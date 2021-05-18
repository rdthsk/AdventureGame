#include <string>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <synchapi.h>

using namespace std;

void HUD();
void Combat();
void CombatHUD();
void Moving();
void CreateEnemy();

string name = " ", race = " ", pronouns = " ";
int level = 0, xp = 0, health = 0, totalHealth = 0, maxHealth = 0, nextLevel = 0, heal = 0;
int enemyHealth = 0;
int enemyXp = 0;
int enemyLevel = 0;

string enemyName[] = {"Lucien", "Obann", "Avantika", "Lorenzo", "Trent", "Vokodo"};
int currEnemyNames = 5;
string currentEnemy = " ";

int main()
{
    level = 1;
    xp = 0;
    nextLevel = 76;
    health = 100;
    totalHealth = health;
    maxHealth = totalHealth;
    
    //Character Creation.
    cout << "Enter your character's name:";
    cin >> name;
    
    cout << "Enter your character's race:";
    cin >> race;
    
    cout << "Enter your character's pronouns:";
    cin >> pronouns;
    
    //Cool loading screen
    cout << "Creating Character...\n";
    Sleep(200);
    system("cls");
    
    cout << "Creating Character...\n";
    Sleep(200);
    system("cls");
    
    cout << "Creating Character...\n\n";
    Sleep(200);
    system("cls");
    
    HUD();
    Moving();
    
    return 0;
}

void HUD()
{
    Sleep(500);
    system("cls");
    cout << "Name: " << name << "      Health: " << totalHealth << "        \nRace: "
         << race << "\nPronouns: " << pronouns << "\nLevel: " << level << "\nExperience: "
         << xp << "\nExperience to Level: " << nextLevel << "\n" << endl;
    Moving();
}

void Moving()
{
    int choice;
    
    cout << "What would you like to do?\n";
    cout << "1. Move Forward\n";
    cout << "2. Relax\n";
    cout << "3. Move Backwards\n";
    
    cin >> choice;

    if (choice == 1)
    
    {
        int encouterChance = rand() % 100 + 1;
        cout << "You begin moving forward...\n";
        if (encouterChance >= 50)
        {
            //Enemy Encounter
            CreateEnemy();
            string tempName = enemyName[rand() % currEnemyNames];
            cout << tempName << " is engaging with you! Roll for Initiative!\n";
            currentEnemy = tempName;
            //Sleep(200);
            Combat();
        }
        cout << "You find nothing of interest and continue your jouney\n";
        //Sleep(1000);
        HUD();
    }
    else if(choice == 2)
    {
        cout << "You set up camp for the evening\n";

        if (totalHealth <= maxHealth - 1)
        {
            totalHealth += 10 * level;
        }
        cout << "You healed from resting! Your health is now " << totalHealth << endl;
        //Sleep(1000);
        HUD();
    }
    else if (choice == 3)
    {
        int encounterChance = rand() % 100 + 1;
        cout << "You begin moving backwards...\n";
        if (encounterChance >= 50)
        {
            //Enemy Encounter
            CreateEnemy();
            string tempName = enemyName[rand() % currEnemyNames];
            cout << tempName << " is engaging with you! Roll for Initiative!\n";
            currentEnemy = tempName;
            //Sleep(1000);
            Combat();
        }
        cout << "You find nothing of interest and continue your jouney\n";
        //Sleep(1000);
        HUD();
    }
    else
    {
        cout << "Invalid Input\n";
        //Sleep(500);
        Moving();
        
    }
}

void Combat()
{
    CombatHUD();
    int playerAttack;
    int playerDamage = 8 * level / 2;
    int enemyAttack = 6 * enemyLevel / 2;

    if (totalHealth >= 1 && enemyHealth >= 1)
    {
        cout << "\nWhat would you like to do?\n";
        cout << "1. Attack!\n";
        cout << "2. Block and Heal!\n";
        cout << "3. Run!\n";
        cin >> playerAttack;

        if (playerAttack == 1)
        {
            cout << "You roll for an attack...\n";
            int playerHitChance = rand() % 100 - 1;
            //Sleep(200);

            if (playerHitChance >= 50)
            {
                cout << "Your attack hits! You deal " << playerAttack << " points of damage to " << currentEnemy << "! Great Turn! Well Done!.\n" << endl;
                enemyHealth = enemyHealth - playerDamage;
                //Sleep(1000);
                CombatHUD();
            }
            else
            {
                cout << "Your attack just misses as " << currentEnemy << " blocks it! Better luck next turn!\n";
            }
            if (enemyHealth >= 1)
            {
                cout << currentEnemy << " is rolling for an attack...\n";
                int enemyHitChance = rand() % 100 - 1;
                //Sleep(200);
                
                if (enemyHitChance >= 50)
                {
                    totalHealth = totalHealth - enemyAttack;
                    cout << currentEnemy << "'s attack hits you and you suffer " << enemyAttack << " points of damage! Get ready for your next turn!\n";
                }
                else
                {
                    cout << currentEnemy << "'s attack just misses you as you side step it. Time to take advantage of this!\n";
                }

                if (totalHealth <= 0)
                {
                    totalHealth = 0;
                }
            }
            else if (enemyHealth <= 0)
            {
                enemyHealth = 0;
            }
            //Sleep(1000);
            Combat();
        }
        else if(playerAttack == 2)
        {
            cout << "You try an attack block to rest for a second...\n";
            int blockChance = rand() % 100 - 1;
            //Sleep(200);

            if (blockChance >= 50)
            {
                heal = level * 10 / 2;
                cout << "You successfully block the incoming attack and heal for " << heal << "points! Good call!/n";
                totalHealth += heal;
                //Sleep(1000);
                Combat();
            }
            else
            {
                cout << "You failed to block the incoming attack!\n";
                totalHealth -= enemyAttack;
                cout << "You suffer " << enemyAttack << " points of damage from " << currentEnemy << "'s attack!";
                //Sleep(1000);
                Combat();
            }
        }
        else if (playerAttack == 3)
        {
            cout << "You try to run away from the fight.../n";
            int runChance = rand() % 100 - 1;
            
            if (runChance >= 50)
            {
                cout << "You succssfully run away from " << currentEnemy << "!";
                HUD();
            }
            else
            {
                cout << "You failed to run away from " << currentEnemy << "! They attack...\n";
                int enemyOpHitChance = rand() % 100 - 1;

                if (enemyOpHitChance >= 50)
                {
                    totalHealth -= enemyAttack + 10;
                    cout << currentEnemy << " savagely hits you and you suffer " << enemyAttack + 10 << "!\n";
                    cout << "Your current health is " << totalHealth << "." << endl;
                    //Sleep(1000);
                    Combat();
                }
                else
                {
                    cout << currentEnemy << "'s oppertunity attack barely misses you. You seemed to have got very lucky here.\n";
                }
            }
        }
        else
        {
            cout << "Invalid Input\n";
            //Sleep(500);
            Combat();
        }
    }
}

void CombatHUD()
{
    Sleep(500);
    system("cls");
    cout << "Name: " << name << "       |       Enemy Name: " << currentEnemy << "\nHealth: "
         << totalHealth << "      |       Enemy Health: " << enemyHealth <<"\nLevel: " << level
         << "         |       Enemy Level: " << enemyLevel << endl;
}

void CreateEnemy()
{
    enemyHealth = 30;
    enemyLevel = (rand() % 3 + level);
    
    enemyHealth = (rand() % 30) * totalHealth;
    
    enemyXp = enemyHealth;

    if (enemyHealth == 0)
    {
        CreateEnemy();
    }
    if (enemyLevel == 0)
    {
        CreateEnemy();
    }
}
