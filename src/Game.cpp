#include <iostream>
#include <string>
#include "game.hpp"
#include "rules.hpp"
#include "utils.hpp"
using namespace std;

static string colourName(int c) {
    static const char* names[4] = { "RED", "GREEN", "YELLOW", "BLUE" };
    return names[c % 4];
}

static bool onTrack(const Token& t) {
    return t.getState() == TokenState::ACTIVE && !t.isInHomeColumn();
}

Game::Game() {
    numPlayers = 4;
    turn = 0;
    players = new Player[numPlayers];
}

Game::Game(int n) {
    numPlayers = (n == 2) ? 2 : 4;
    turn = 0;
    players = new Player[numPlayers];
}

Game::~Game() {
    delete[] players;
}

void Game::setup() {
    for (int i = 0; i < numPlayers; i++) {
        int colour = i;
        if (numPlayers == 2 && i == 1) colour = YELLOW;   // opposite corners

        cout << "Name of player " << i + 1 << " (" << colourName(colour) << "): ";
        string name;
        getline(cin, name);
        if (name == "") name = "Player" + to_string(i + 1);

        int type = readInt("1 = human, 2 = bot: ", 1, 2);
        players[i] = Player(name, colour);
        players[i].setChooser(type == 2 ? botChoice : humanChoice);
    }
}

Player& Game::getPlayer(int i) {
    return players[i];
}

void Game::moveToken(Player& p, int idx, int roll) {
    Token& t = p[idx];

    if (t.getState() == TokenState::HOME) {
        t.leaveHome();
        cout << "Token " << idx + 1 << " comes out to cell " << t.getCell() << endl;
    } else {
        int from = t.getCell();
        t.move(roll);

        if (t.getState() == TokenState::FINISHED) {
            cout << "Token " << idx + 1 << " reached home!" << endl;
            p.tokenFinished();
        } else if (onTrack(t)) {
            cout << "Token " << idx + 1 << " goes " << from << " -> " << t.getCell() << endl;
        } else {
            cout << "Token " << idx + 1 << " is in the home column" << endl;
        }
    }

    if (onTrack(t))
        board.checkCapture(t, players, numPlayers);
}

void Game::showStatus() const {
    for (int i = 0; i < numPlayers; i++)
        cout << players[i] << endl;
}

void Game::run() {
    board.display(players, numPlayers);

    bool over = false;
    while (!over) {
        Player& cur = players[turn];
        cout << "\n" << cur.getName() << "'s turn (" << colourName(cur.getColour()) << ")" << endl;

        int roll = dice.roll();
        cout << "Rolled " << roll << endl;

        int idx = cur.chooseToken(roll);
        if (idx == -1) cout << "No token can move" << endl;
        else moveToken(cur, idx, roll);

        if (idx != -1) board.display(players, numPlayers);

        if (cur.hasWon()) over = true;
        else if (grantsExtraTurn(roll)) cout << "Got a 6, roll again" << endl;
        else turn = (turn + 1) % numPlayers;
    }

    declareWinner();
}

void Game::declareWinner() const {
    int scores[4];
    for (int i = 0; i < numPlayers; i++)
        scores[i] = players[i].getFinishedCount();

    int best = scores[0];
    for (int i = 1; i < numPlayers; i++)
        best = maxOf(best, scores[i]);

    int w = findIndex(scores, numPlayers, best);

    cout << "\nWinner: " << players[w].getName() << " (" << colourName(players[w].getColour()) << ")" << endl;
    cout << "Tokens home: ";
    printArray(scores, numPlayers);
}