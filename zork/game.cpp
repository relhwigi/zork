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
#include "takelistener.h"
#include "hurtlistener.h"
#include "attacklistener.h"

Game::Game() : player("Hero"), stationaryEnemy( "Witch", false ), roamingEnemy( "Zombie", true )
{
    srand(time(nullptr));

    // Commands
    EventManager::getInstance().listen("go",        new GoListener(this));
    EventManager::getInstance().listen("map",       new MapListener(this));
    EventManager::getInstance().listen("info",      new InfoListener(this));
    EventManager::getInstance().listen("restart",   new RestartListener(this));
    EventManager::getInstance().listen("teleport",  new TeleportListener(this));
    EventManager::getInstance().listen("exit",      new ExitListener(this));
    EventManager::getInstance().listen("take",      new TakeListener(this));
    EventManager::getInstance().listen("attack",    new AttackListener(this));

    // State changes
    EventManager::getInstance().listen("characterDeath", new CharacterDeathListener(this));
    EventManager::getInstance().listen("enterRoom",      new EnterRoomListener(this));
    EventManager::getInstance().listen("victory",        new VictoryListener(this));
    EventManager::getInstance().listen("defeat",         new DefeatListener(this));
    EventManager::getInstance().listen("hurt",         new HurtListener(this));

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

Game::~Game(){
    delete key;
    delete cursed;
    delete potion;
    delete locked;
    //found this workaround to free the memory taken by vector object. swap the vector with an empty vector (no memory allocated). this will de-allocate the memory taken by the vector and always guarenteed to work.
    vector<Room*>().swap(rooms);
    
    
}

void Game::reset(bool show_update)
{
    
    gameOver = false;
    
    for(int i = 0; i < rooms.size(); i++){
        if(rooms[i] -> hasItem()) rooms[i] -> setRoomItem(nullptr);
           }
    
    player.clearItems();
    distribute_items();
    lockRoom();
    enemies();
    player.setCurrentRoom(rooms[0]);
    player.setHealth(100);
    player.setStamina(100);
    stationaryEnemy.setHealth(100);
    stationaryEnemy.setStamina(100);
    roamingEnemy.setStamina(100);
    roamingEnemy.setHealth(100);
    
    cout << "\nWelcome to Zork!" << endl;
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
    cout << "Player -> [room name]\nEnemy  -> !room name!\n"<<endl;
    /****************** 6. Friends******************/
    cout << rooms[3]->getDescription(this) << " - " << rooms[4]->getDescription(this) << " - " << rooms[5]->getDescription(this);
    cout << "\n             |             \n";
    cout << rooms[1]->getDescription(this) << " - " << rooms[0]->getDescription(this) << " - " << rooms[2]->getDescription(this);
    cout << "\n             |             \n";
    cout << rooms[6]->getDescription(this) << " - " << rooms[7]->getDescription(this) << " - " << rooms[8]->getDescription(this);
    cout << "\n             |             \n";
    cout << "          " << rooms[9] -> getDescription(this) << "          ";
    
}

void Game::info()
{
    cout << "Available commands:" << endl;
    cout << " - go <direction>"   << endl;
    cout << " - teleport"         << endl;
    cout << " - map"              << endl;
    cout << " - info"             << endl;
    cout << " - take"             << endl;
    cout << " - attack"           << endl;
}

void Game::go(string direction)
{
    Room *next = player.getCurrentRoom()->getExit(direction);
    if(secondAttack) secondAttack = false;

        if (next != nullptr && next -> getName() == locked -> getName()) {
        player.setStamina(player.getStamina() - 1);
        if(player.hasTakenItem("key")){
            EventManager::getInstance().trigger("victory");
        }else{
            cout << "\nOh no this room is locked. You can find the key as an item in the other rooms.\n";
            EventManager::getInstance().trigger("enterRoom", player.getCurrentRoom());
        }
        } else if(next != nullptr){
            player.setCurrentRoom(next);
            player.setStamina(player.getStamina() - 1);
            EventManager::getInstance().trigger("enterRoom", next);
            roam();
        }else{
            cout << "You hit a wall" << endl;
        }
    
   
}

void Game::teleport()
{
    int selected = rand() % rooms.size();
    while(rooms[selected] ->getName() == locked ->getName()){
        selected = rand() % rooms.size();
    }
    player.setCurrentRoom(rooms[selected]);
    player.setStamina(player.getStamina() - 5);
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
        cout << "-------------------------------\n";
        cout << "You are in " << currentRoom->getName() << endl;

        cout << "Exits:";
        if (currentRoom->getExit("north") != nullptr) { cout << " north"; }
        if (currentRoom->getExit("east")  != nullptr) { cout << " east";  }
        if (currentRoom->getExit("south") != nullptr) { cout << " south"; }
        if (currentRoom->getExit("west")  != nullptr) { cout << " west";  }
        cout << endl;
        cout << "\n* Health and stamina stats *\n";
        /****************** 5. Binary operator overloading******************/
        cout << player;
        if(stationaryEnemy.getCurrentRoom() != nullptr){
            stationaryEnemy.getCurrentRoom()->setHasEnemy(true);
            if(currentRoom->getName() == stationaryEnemy.getCurrentRoom()->getName()){
                /****************** 5. Binary operator overloading******************/
                cout << stationaryEnemy;
            }
        }
        if(roamingEnemy.getCurrentRoom() != nullptr){
            roamingEnemy.getCurrentRoom()->setHasEnemy(true);
            if(currentRoom->getName() == roamingEnemy.getCurrentRoom()->getName()){
                /****************** 5. Binary operator overloading******************/
                cout << roamingEnemy;
            }
        }
        if(currentRoom ->getHasEnemy()) cout << "\n!!There is an enemy in this room!!.\n\n";
        
        if(currentRoom -> hasItem()){
            if(currentRoom->getHasEnemy()){
                cout << "\nThis room appears to have an item. But its being blocked. You can only \"take\" it if you defeat the enemy.\n";
            }else if(!currentRoom->getHasEnemy()){
                cout << "\nThis room appears to have an item. \"take\" it to have a closer look.\n";
            }
        }
        cout << "-------------------------------\n";
    }else {
        cout << "Type \"restart\" or \"exit\"." << endl;
    }
}


/*
    added three items: a cursed item, a key and a potion here.
 */

void Game::distribute_items(){
    cursed = new item("cursed item");
    key = new item("key");
    potion = new item("potion");
    
    int selected = rand() % rooms.size();
    rooms[selected] -> setRoomItem(cursed);
    
    selected = rand() % rooms.size();
    while(rooms[selected] -> hasItem()){ // so we only have one item per room
        selected = rand() % rooms.size();
    }
    rooms[selected] -> setRoomItem(key);
    keyIndex = selected;
    
    selected = rand() % rooms.size();
    while(rooms[selected] -> hasItem()){ // so we only have one item per room
        selected = rand() % rooms.size();
    }
    rooms[selected] -> setRoomItem(potion);
}

/*
    Locked a room here.
 */

void Game::lockRoom(){
    int selected = rand() % rooms.size();
    //can't lock a room that has exits east and west as it may stop the player from being able to retrieve a key.
    while(rooms[selected] -> hasItem() || (rooms[selected] -> getExit("east") != nullptr && rooms[selected] -> getExit("west") != nullptr ))
    { // so a room with an item isn't locked and rooms in the middle aren't locked
        selected = rand() % rooms.size();
    }
    locked = rooms[selected];
}

/*
    "take" command created here.
 */

void Game::take(){
    if(player.getCurrentRoom() -> hasItem() && !player.getCurrentRoom() -> getHasEnemy()){
        player.itemTaken(player.getCurrentRoom() -> getRoomItem());
        
        /*
            I check whether the player has taken and the cursed item here
         */
        
        if(player.getCurrentRoom() -> getRoomItem() -> getDescription() == "cursed item"){
            player.getCurrentRoom() -> setRoomItem(nullptr);
            /*
                I trigger the event hurt here.
             */
            cout << "\nOh no the item appears to be cursed.\n";
            EventManager::getInstance().trigger("hurt");
        } else if(player.getCurrentRoom() -> getRoomItem() -> getDescription() == "key"){
            player.getCurrentRoom() -> setRoomItem(nullptr);
            cout << "\nYou have found a key. This will come in handy to unlock a locked room you may encounter.\n";
        }else{
            player.getCurrentRoom() -> setRoomItem(nullptr);
            cout << "\nYou have found a potion. Hold on to that it may come in handy later.\n";
        }
    }
}

Room* Game::getLockedRoom(){
    return locked;
}

void Game::enemies(){
    int selected = rand() % rooms.size();
    // no point putting an enemy in the locked room since entering the locked room triggers victory
    while(rooms[selected]->getName() == locked->getName() || selected == keyIndex){
        selected = rand() % rooms.size();
    }
    roamingEnemy.setCurrentRoom(rooms[selected]);
    rooms[selected] -> setHasEnemy(true);
    stationaryEnemy.setCurrentRoom(rooms[keyIndex]);
    rooms[keyIndex] -> setHasEnemy(true);
    //same room as key so the player must attack to win the game;
}

void Game::roam(){
    
    if(roamingEnemy.getCurrentRoom() != nullptr){
    vector<string> directions = roamingEnemy.getCurrentRoom()->possibleDirections();
    int selected = rand() % directions.size();
    Room *next = roamingEnemy.getCurrentRoom() -> getExit(directions[selected]);
    roamingEnemy.getCurrentRoom() -> setHasEnemy(false);
    next->setHasEnemy(true);
    roamingEnemy.setCurrentRoom(next);
    roamingEnemy.setStamina(roamingEnemy.getStamina()-1);
    }
    if(roamingEnemy.getStamina() == 0){
        roamingEnemy.setCurrentRoom(nullptr);
    }
}

void Game::attack(){
    //if player attacks roaming enemy its up to chance who loses some health. either player kills enemy from first attack, or enemy hurts player, or enemy is wounded and player should attack again, at a higher stamina expense, to kill enemy.
    //if player attacks stationary enemy they will continue to lose unless they have the potion
    if(stationaryEnemy.getCurrentRoom() == player.getCurrentRoom()){
        if(player.hasTakenItem("potion")){
            cout << "\nYou have deafeated the " << stationaryEnemy.getName() << "!" << endl;
            stationaryEnemy.getCurrentRoom() -> setHasEnemy(false);
            stationaryEnemy.setCurrentRoom(nullptr);
        }else{
            cout << "\nYou have been wounded by the " << stationaryEnemy.getName() << "!" << endl;
            EventManager::getInstance().trigger("hurt");
            cout << "\nYou can only defeat the " << stationaryEnemy.getName() << " when you have the potion." << endl;
        }
        player.setStamina(player.getStamina()-5);
        stationaryEnemy.setStamina(stationaryEnemy.getStamina()-5);
    }else if(roamingEnemy.getCurrentRoom() == player.getCurrentRoom()){
        if(!secondAttack){
            int winner = rand()%3; //1 player wins, 0 enemy wins, 3 enemy is wounded attack once more to kill.
            if(winner == 1){
                cout << "\nYou have defeated the " << roamingEnemy.getName() << "!" << endl;
                roamingEnemy.getCurrentRoom() -> setHasEnemy(false);
                roamingEnemy.setCurrentRoom(nullptr);
            } else if(winner == 0) {
                cout << "\nYou have been wounded by the " << roamingEnemy.getName() << "!" <<   endl;
                EventManager::getInstance().trigger("hurt");
            } else {
                cout << "\nYou have wounded the " << roamingEnemy.getName() << "! this your chance to attack again to kill the " << roamingEnemy.getName() << ". But it'll be at a higher stamina expense.\n";
                roamingEnemy.setHealth(roamingEnemy.getHealth()-50);
                if(roamingEnemy.getHealth() == 0){
                    cout << "\nYou have defeated the " << roamingEnemy.getName() << "!" << endl;
                    roamingEnemy.getCurrentRoom()->setHasEnemy(false);
                    roamingEnemy.setCurrentRoom(nullptr);
                    secondAttack = false;
                }else{
                secondAttack = true;
                }
            }
            player.setStamina(player.getStamina()-5);
            roamingEnemy.setStamina(roamingEnemy.getStamina()-5);
        }else{
            cout << "\nYou have defeated the " << roamingEnemy.getName() << "!" << endl;
            roamingEnemy.getCurrentRoom()->setHasEnemy(false);
            roamingEnemy.setCurrentRoom(nullptr);
            player.setStamina(player.getStamina()-15);
            secondAttack = false;
        }
    }else{
        cout << "\nNo enemy in this room to attack\n";
    }
}
