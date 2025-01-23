#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "raylib.h"

using namespace std;

// Player class
class Player {
public:
    string name;
    int health;
    int attack;
    int defense;
    Vector2 position;

    Player(string name, int health, int attack, int defense) {
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        this->position = { 400, 300 }; // Initial position
    }

    void takeDamage(int damage) {
        int reducedDamage = damage - defense;
        if (reducedDamage > 0) {
            health -= reducedDamage;
            cout << name << " takes " << reducedDamage << " damage!" << endl;
        } else {
            cout << name << " blocks the attack!" << endl;
        }
    }

    int dealDamage() {
        return attack;
    }

    void draw() {
        DrawCircleV(position, 20, RED); // Draw the player as a red circle
    }
};

// Enemy class
class Enemy {
public:
    string name;
    int health;
    int attack;
    int defense;
    Vector2 position;

    Enemy(string name, int health, int attack, int defense, Vector2 position) {
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        this->position = position;
    }

    void takeDamage(int damage) {
        int reducedDamage = damage - defense;
        if (reducedDamage > 0) {
            health -= reducedDamage;
            cout << name << " takes " << reducedDamage << " damage!" << endl;
        } else {
            cout << name << " blocks the attack!" << endl;
        }
    }

    int dealDamage() {
        return attack;
    }

    void draw() {
        DrawCircleV(position, 20, BLUE); // Draw the enemy as a blue circle
    }
};

// Function to generate a random enemy
Enemy generateRandomEnemy() {
    vector<string> enemyNames = {"Goblin", "Skeleton", "Orc", "Wolf"};
    int randomIndex = rand() % enemyNames.size();
    string name = enemyNames[randomIndex];
    int health = rand() % 50 + 20;
    int attack = rand() % 15 + 5;
    int defense = rand() % 10 + 2;
    Vector2 position = { (float)(rand() % 700 + 50), (float)(rand() % 500 + 50) }; // Random position
    return Enemy(name, health, attack, defense, position);
}

int main() {
    // Initialize Raylib
    InitWindow(800, 600, "Simple RPG");
    SetTargetFPS(60);

    // Seed the random number generator
    srand(time(0));

    // Create the player
    cout << "Enter your name: ";
    string playerName;
    cin >> playerName;
    Player player(playerName, 100, 20, 5);

    // Create an enemy
    Enemy enemy = generateRandomEnemy();

    // Game loop
    bool playing = true;
    while (!WindowShouldClose() && playing) {
        // Update
        if (IsKeyDown(KEY_RIGHT)) player.position.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) player.position.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) player.position.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) player.position.y += 2.0f;

        // Check for collision with enemy (simple circle collision)
        float dist = sqrtf(powf(player.position.x - enemy.position.x, 2) + 
                          powf(player.position.y - enemy.position.y, 2));
        if (dist <= 40) { // 40 is the sum of the radii of the player and enemy circles
            // Battle logic (similar to your original code)
            cout << "\nYou encounter a " << enemy.name << "!" << endl;

            while (player.health > 0 && enemy.health > 0) {
                cout << "\nWhat do you want to do? (attack/run): ";
                string action;
                cin >> action;

                if (action == "attack") {
                    enemy.takeDamage(player.dealDamage());
                    if (enemy.health > 0) {
                        player.takeDamage(enemy.dealDamage());
                    }
                } else if (action == "run") {
                    cout << "You successfully escape!" << endl;
                    enemy = generateRandomEnemy(); // Generate a new enemy
                    break;
                } else {
                    cout << "Invalid action!" << endl;
                }
            }

            if (player.health <= 0) {
                cout << "\nYou have been defeated!" << endl;
                playing = false;
            } else if (enemy.health <= 0) {
                cout << "\nYou have defeated the " << enemy.name << "!" << endl;
                enemy = generateRandomEnemy(); // Generate a new enemy
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            player.draw();
            enemy.draw();
        EndDrawing();
    }

    CloseWindow();
    cout << "\nGame Over" << endl;
    return 0;
}
