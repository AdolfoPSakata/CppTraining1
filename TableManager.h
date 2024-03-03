#pragma once
#include <conio.h>
#include <string>
#include "DeckManager.h"
#include "Contestant.h"
#include "Player.h"
#include "Foe.h"

class TableManager
{
public:
    TableManager();
    ~TableManager();

    DeckManager* deckManager = new DeckManager;
    std::vector<Contestant>* playerOnTable = new std::vector<Contestant>();

    void SetToAuto(char isAutoInput);
    void Init();
    void CreateGameTable(int& foeCount);
    void AddPlayer();
    void AddFoe();
    void NextPlayer();
    int GetPlayersCount();
    void CheckTopCardSkill(Card discard);
    void CheckVictory(bool& calledUno, bool& isPlayer, int& handSize, int& playerIndex);
    Contestant& GetPlayerByIndex(int index);
    bool CheckRunStatus();
    void PrintMessage(std::string text);
private:
    int currentIndex = 0;
    bool isClockwise = true;
};