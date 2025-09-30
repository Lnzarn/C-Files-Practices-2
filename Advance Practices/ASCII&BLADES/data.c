#include "headers.h"

const char *classes[] = {
    "Swordsman", "Archer", "Assassin", "Wizard"};

struct ClassesInfo
{
    char classname[10];
    int hp;
    int atk;
    int speed;
    struct Attack
    {
        char attackname[20];
        float multiplier;
    } attacks[2];
};

struct EnemyInfo
{
    char enemyname[20];
    int hp;
    int atk;
    int speed;
    int expdrop;
} currentEnemy;

struct ClassesInfo statclass[4] = {
    {"Swordsman", 120, 15, 20, {{"Slash", 1.0}, {"Heavy Slash", 1.2}}},
    {"Archer", 90, 22, 23, {{"Quick Shot", 1.0}, {"Power Shot", 1.3}}},
    {"Assassin", 80, 25, 26, {{"Stab", 1.0}, {"Backstab", 1.4}}},
    {"Wizard", 70, 28, 21, {{"Firebolt", 1.0}, {"Arcane Blast", 1.5}}}};

struct EnemyInfo LowEnemy[3] = {
    {"Cave Rat", 30, 5, 15, 100},
    {"Slime", 35, 6, 15, 100},
    {"Goblin Scout", 40, 8, 15, 100}};

struct EnemyInfo MidEnemy[3] = {
    {"Goblin Raider", 60, 12, 25, 100},
    {"Dire Wolf", 70, 14, 25, 100},
    {"Bandit", 65, 15, 20, 100}};

struct EnemyInfo HighEnemy[7] = {
    {"Jayvie Enorme", 90, 18, 26, 50},
    {"Ian Muyo", 110, 20, 21, 50},
    {"Vincent Jakosalem", 80, 25, 21, 50},
    {"Aethan Corpuz", 90, 18, 21, 50},
    {"Jed Plaza", 110, 20, 24, 50},
    {"Johnrex Borilla", 80, 25, 24, 50},
    {"Stan Magallon", 120, 20, 20, 50}};

struct EnemyInfo BossEnemy[2] = {
    {"Tasdas", 200, 20, 20, 100},
    {"Treeko", 150, 30, 25, 100}};