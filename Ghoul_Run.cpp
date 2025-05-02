#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

struct Entity {
    int x, y;
    char symbol;
    int speed;
    bool alive;
};

Entity player;
vector<Entity> enemies;
vector<Entity> bombs;
Entity powerup;

int ticks = 0;
int playerMoves = 0;
bool gameOver = false;
bool hasBomb = false;

bool powerupOnField = false;
bool speedBoostActive = false;
int speedBoostTurnsLeft = 0;

int ghoulSkip = 3;
int ghoulTurnCounter = 0;

void init() {
    srand(time(0));
    player.x = WIDTH / 2;
    player.y = HEIGHT / 2;
    player.symbol = 'V';
    player.speed = 1;
    player.alive = true;
}

void draw() {
    system("clear");

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            bool printed = false;

            if (player.x == x && player.y == y) {
                cout << player.symbol;
                printed = true;
            }

            for (auto& b : bombs) {
                if (b.x == x && b.y == y) {
                    cout << '0';
                    printed = true;
                }
            }

            for (auto& e : enemies) {
                if (e.alive && e.x == x && e.y == y) {
                    cout << e.symbol;
                    printed = true;
                }
            }

            if (powerupOnField && powerup.x == x && powerup.y == y) {
                cout << powerup.symbol;
                printed = true;
            }

            if (!printed) cout << '"';
        }
        cout << "\n";
    }

    cout << "Score: " << ticks << " | Ghouls skip: " << ghoulSkip << " turns\n";
    if (speedBoostActive) cout << "⚡ Speed Boost active! Moves left: " << speedBoostTurnsLeft << "\n";
    if (hasBomb) cout << "💣 Bomb ready! Press 'P' + Enter to place\n";
}

void movePlayer(char dir, int distance) {
    while (distance--) {
        if (dir == 'w' && player.y > 0) player.y--;
        if (dir == 's' && player.y < HEIGHT - 1) player.y++;
        if (dir == 'a' && player.x > 0) player.x--;
        if (dir == 'd' && player.x < WIDTH - 1) player.x++;
    }
}

void spawnEnemy(bool fast) {
    Entity e;
    e.symbol = fast ? 'X' : 'G';
    e.speed = fast ? 2 : 1;
    e.alive = true;

    int side = rand() % 4;
    if (side == 0) { e.x = 0; e.y = rand() % HEIGHT; }
    if (side == 1) { e.x = WIDTH - 1; e.y = rand() % HEIGHT; }
    if (side == 2) { e.x = rand() % WIDTH; e.y = 0; }
    if (side == 3) { e.x = rand() % WIDTH; e.y = HEIGHT - 1; }

    enemies.push_back(e);
}

void moveEnemies() {
    if (ghoulTurnCounter < ghoulSkip) {
        ghoulTurnCounter++;
        return;
    }
    ghoulTurnCounter = 0;

    for (auto& e : enemies) {
        if (!e.alive) continue;
        for (int i = 0; i < e.speed; ++i) {
            if (e.x < player.x) e.x++;
            else if (e.x > player.x) e.x--;
            if (e.y < player.y) e.y++;
            else if (e.y > player.y) e.y--;

            for (auto& b : bombs) {
                if (e.x == b.x && e.y == b.y) {
                    e.alive = false;
                    cout << "💥 A ghoul stepped on your bomb and exploded!\n";
                }
            }

            if (e.x == player.x && e.y == player.y && e.alive) {
                gameOver = true;
            }
        }
    }
}

void spawnPowerup() {
    powerup.x = rand() % WIDTH;
    powerup.y = rand() % HEIGHT;

    if (rand() % 2 == 0) {
        powerup.symbol = '+';
    } else {
        powerup.symbol = '0';
    }

    powerupOnField = true;
}

int main() {
    init();
    char input;

    while (!gameOver) {
        draw();

        cout << "Move (w/a/s/d or P to place bomb) + Enter: ";
        cin >> input;

        if (input == 'P' && hasBomb) {
            Entity bomb;
            bomb.x = player.x;
            bomb.y = player.y;
            bomb.symbol = '0';
            bombs.push_back(bomb);
            hasBomb = false;
            cout << "💣 Bomb placed at (" << bomb.x << ", " << bomb.y << ")\n";
            continue;
        }

        int moveDist = speedBoostActive ? 2 : 1;
        movePlayer(input, moveDist);

        playerMoves++;
        if (speedBoostActive) {
            speedBoostTurnsLeft--;
            if (speedBoostTurnsLeft <= 0) {
                speedBoostActive = false;
            }
        }

        if (powerupOnField && player.x == powerup.x && player.y == powerup.y) {
            if (powerup.symbol == '+') {
                speedBoostActive = true;
                speedBoostTurnsLeft = 5;
                cout << "⚡ Speed boost collected!\n";
            } else if (powerup.symbol == '0') {
                hasBomb = true;
                cout << "💣 Bomb power-up collected!\n";
            }
            powerupOnField = false;
        }

        if (playerMoves == 20) ghoulSkip = 2;
        if (playerMoves == 40) ghoulSkip = 1;

        if (ticks % 10 == 0) spawnEnemy(false);
        if (ticks % 20 == 0 && ticks > 0) spawnEnemy(true);
        if (ticks % 30 == 0 && !powerupOnField) spawnPowerup();

        moveEnemies();
        ticks++;

        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "\n💀 Game Over! Final Score: " << ticks << "\n";
    return 0;
}



