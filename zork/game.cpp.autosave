#include "game.h"

#include<ctime>
#include<iostream>

#include "eventmanager.h"
#include "room.h"

#include "golistener.h"
#include "maplistener.h"
#include "infolistener.h"
#include "restartlistener.h"
#include "teleportlistener.h"
#include "exitlistener.h"
#include "characterdeathlistener.h"
#include "enterroomlistener.h"
#include "victorylistener.h"
#include "defeatlistener.h"

Game::Game() :
    player("Hero")
{
    srand(time(nullptr
               ));

    // Commands
    EventManager::getInstance().listen("go",        new GoListener(this));
    EventManager::getInstance().listen("map",       new MapListener(this));
    EventManager::getInstance().listen("info",      new InfoListener(this));
    EventManager::getInstance().listen("restart",   new RestartListener(this));
    EventManager::getInstance().listen("teleport",  new TeleportListener(this));
    EventManager::getInstance().listen("exit",      new ExitListener(this));

    // State changes
    EventManager::getInstance().listen("characterDeath", new CharacterDeathListener(this));
    EventManager::getInstance().listen("enterRoom",      new EnterRoomListener(this));
    EventManager::getInstance().listen("victory",        new VictoryListener(this));
    EventManager::getInstance().listen("defeat",         new DefeatListener(this));

    rooms.push_back(new Room("A")); // 0
    rooms.push_back(new Room("B")); // 1
    rooms.push_back(new Room("C")); // 2
    rooms.push_back(new Room("D")); // 3
    rooms.push_back(new Room("E")); // 4
    rooms.push_back(new Room("F")); // 5
    rooms.push_back(new Room("G")); // 6
    rooms.push_back(new Room("H")); // 7
    rooms.push_back(new Room("I")); // 8
    rooms.push_back(new Room("J")); // 9

    //                 N         E         S         W
    rooms[0]->setExits(rooms[4], rooms[2], rooms[7], rooms[1]);
    rooms[1]->setExits(nullptr,  rooms[0], nullptr,  nullptr);
    rooms[2]->setExits(nullptr,  nullptr,  nullptr,  rooms[0]);
    rooms[3]->setExits(nullptr,  rooms[4], nullptr,  nullptr);
    rooms[4]->setExits(nullptr,  rooms[5], rooms[0], rooms[3]);
    rooms[5]->setExits(nullptr,  nullptr,  nullptr,  rooms[4]);
    rooms[6]->setExits(nullptr,  rooms[7], nullptr,  nullptr);
    rooms[7]->setExits(rooms[0], rooms[8], rooms[9], rooms[6]);
    rooms[8]->setExits(nullptr,  nullptr,  nullptr,  rooms[7]);
    rooms[9]->setExits(rooms[7], nullptr,  nullptr,  nullptr);

    reset();
}

void Game::reset(bool show_update)
{
    gameOver = false;

    player.setCurrentRoom(rooms[0]);
    player.setHealth(100);
    player.setStamina(100);

    cout << "Welcome to Zork!" << endl;
    if (show_update) {
        update_screen();
    }
}

void Game::setOver(bool over)
{
    this->gameOver = over;
}

void Game::map()
{
    cout << "D-E-F" << endl;
    cout << "  |  " << endl;
    cout << "B-A-C" << endl;
    cout << "  |  " << endl;
    cout << "G-H-I" << endl;
    cout << "  |  " << endl;
    cout << "  J  " << endl;
}

void Game::info()
{
    cout << "Available commands:" << endl;
    cout << " - go <direction>"   << endl;
    cout << " - teleport"         << endl;
    cout << " - map"              << endl;
    cout << " - info"             << endl;
}

void Game::go(string direction)
{
    Room *next = player.getCurrentRoom()->getExit(direction);

    if (next != nullptr) {
        player.setCurrentRoom(next);
        player.setStamina(player.getStamina() - 1);
        EventManager::getInstance().trigger("enterRoom", next);
    } else {
        cout << "You hit a wall" << endl;
    }
}

void Game::teleport()
{
    int selected = rand() % rooms.size();
    player.setCurrentRoom(rooms[selected]);
    player.setStamina(player.getStamina() - 50);
    EventManager::getInstance().trigger("enterRoom", rooms[selected]);
}

bool Game::is_over()
{
    return gameOver;
}

Character &Game::getPlayer()
{
    return player;
}

void Game::update_screen()
{
    if (!gameOver) {
        Room *currentRoom = player.getCurrentRoom();

        cout << endl;
        cout << "You are in " << currentRoom->getName() << endl;

        cout << "Exits:";
        if (currentRoom->getExit("north") != nullptr) { cout << " north"; }
        if (currentRoom->getExit("east")  != nullptr) { cout << " east";  }
        if (currentRoom->getExit("south") != nullptr) { cout << " south"; }
        if (currentRoom->getExit("west")  != nullptr) { cout << " west";  }
        cout << endl;

        cout << "HP: " << player.getHealth() << " ST: " << player.getStamina() << endl;
    } else {
        cout << "Type \"restart\" or \"exit\"." << endl;
    }
}
