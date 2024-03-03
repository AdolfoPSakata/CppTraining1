#include "TableManager.h"

TableManager::TableManager() {}
TableManager::~TableManager(){}

int playerIndex = 0;
int drawCount = 0;
bool hasEnded = true;
bool isAuto = false;
bool isDrawed = true;

void TableManager::SetToAuto(char isAutoInput)
{
    if(isAutoInput == '1')
        isAuto = true;
}

void TableManager::Init()
{
    PrintMessage("ENTER THE NUMBER OF PLAYERS (MAX -> 10)");
    int index;
    std::cin >> index;

    if (index > 10)
        index = 10;
    else if (index < 2)
        index = 2;
  
    CreateGameTable(index);
    PrintMessage(" \n" + std::to_string(index) + " PLAYERS SET TO THE GAME ");

    deckManager->Init();
    int cards = 0;

    do
    {
        for (int i = 0; i < this->GetPlayersCount(); i++)
        {
            Card topCard = deckManager->DealCards();
             GetPlayerByIndex(i).hand->StoreCards(topCard);
        }
        cards++;

    } while (cards < deckManager->INITIAL_CARDS);

    deckManager->topCard = deckManager->FirstCard();
}

void TableManager::AddPlayer()
{
    Player* player = new Player(true);
    playerOnTable->emplace_back(*player);
}

void TableManager::AddFoe()
{
    Foe* foe = new Foe(false);
    playerOnTable->emplace_back(*foe);
}

void TableManager::CreateGameTable(int& foeCount)
{
    playerOnTable->reserve(foeCount);
    if (!isAuto)
    {
        AddPlayer();
        foeCount -= 1;
    }
    for (int foes = 0; foes < foeCount; foes++)
    {
        AddFoe();
    }
}

void TableManager::CheckTopCardSkill(Card discard)
{
    int discardValue = discard.number.GetNumberValue();

    if (discardValue == INVERT)
    {
        isClockwise = !isClockwise;
        deckManager->topCard.number.SetNumberValue();
    }
    else if (discardValue == DRAWTWO)
    {
        isDrawed = false;
        drawCount += 2;
    }
    else if (discardValue == BLOCK)
    {
        if (isClockwise)
            playerIndex++;
        else
            playerIndex--;

        deckManager->topCard.number.SetNumberValue();
    }
    else if (discardValue == DRAWFOUR)
    {
        drawCount += 4;
    }
}

void TableManager::NextPlayer()
{
    CheckTopCardSkill(deckManager->topCard);

    if (deckManager->allCards->size() <= 0)
    {
        PrintMessage("EVERYBODY FAIL, NO MORE CARDS!");
        hasEnded = false;
        return;
    }

    if (isDrawed)
    {
        int i = rand() % 4;
        deckManager->topCard.color.SetCharColor(*deckManager->GetSuit(i));
        deckManager->topCard.color.name = deckManager->topCard.color.SetName();
        deckManager->topCard.number.SetNumberValue();
    }

    PrintMessage("\n----------------------------------------------");
    PrintMessage("TOP CARD: " + deckManager->topCard.number.GetNumberString() + " " +deckManager->topCard.color.GetColorName());
    PrintMessage("----------------------------------------------");
    
    if (isClockwise)
    {
        playerIndex++;
        if (playerOnTable->size() - 1 < playerIndex)
            playerIndex = 0;
    }
    else
    {
        playerIndex--;
        if (0 > playerIndex)
            playerIndex = playerOnTable->size() - 1;
    }

    Contestant* currentPlayer = &GetPlayerByIndex(playerIndex);
    Hand* playerHand = currentPlayer->hand;
    int count = currentPlayer->hand->playerHand.size();
    bool isPlayer = currentPlayer->GetPlayerStatus();
    bool calledUno = false;
    
    std::vector<Card>& currentPlayerCards = currentPlayer->hand->playerHand;

    if (!isPlayer)
    {
        FoeBehavior* foe = reinterpret_cast <Foe*>(currentPlayer)->behavior;

        foe->EvaluateCards(currentPlayerCards, deckManager->topCard.color, deckManager->topCard.number);
        int cardIndex = foe->ChooseAvailableCard();

        PrintMessage("FOE " + std::to_string(playerIndex) + " TURN: " + std::to_string(count) + " CARDS");

        if (cardIndex >= 0)
        {
            Card discard = playerHand->Discard(cardIndex);
            
            if (isDrawed && discard.number.GetNumberValue() == DRAWFOUR)
            {
                isDrawed = false;
            }

            int luck = rand() % 100;
            if (count == 2 && luck < 70)
            {
                PrintMessage("\n!!!!!!!!!UNO!!!!!!!!!!");
                calledUno = true;
            }
            else if (count <= 2 && luck > 70)
            {
                for (int cards = 0; cards < 2; cards++)
                {
                    playerHand->Draw(deckManager->DealCards());
                }
            }

            deckManager->SendToDiscard(discard);
            deckManager->topCard = *deckManager->GetLastDiscard();
            
            
           if (discard.color.GetCharColor() == BLACK && isDrawed)
           {
               int i = rand() % 4;
               deckManager->topCard.color.SetCharColor(*deckManager->GetSuit(i));
               deckManager->topCard.color.name = deckManager->topCard.color.SetName();
               deckManager->topCard.number.SetNumberValue();
           }

            CheckVictory(calledUno, isPlayer, count, currentIndex);

            if (count - 1 < 1 && !calledUno)
            {
                for (int cards = 0; cards < 2; cards++)
                {
                    playerHand->Draw(deckManager->DealCards());
                    isDrawed = true;
                }
            }
            reinterpret_cast <Foe*>(currentPlayer)->behavior->ClearEvaluatedCards();
        }
        else
        {
            if (drawCount == 0)
                drawCount = 1;
            else
                deckManager->topCard.number.SetNumberValue();

            for (int cards = 0; cards < drawCount; cards++)
            {
               playerHand->Draw(deckManager->DealCards());
               isDrawed = true;
            }
            PrintMessage(std::to_string(drawCount) +" CARDS DRAWN");
            drawCount = 0;
        }
    }
    else
    {
        PrintMessage("PLAYER'S TURN");
        bool acceptedInput = false;
        do
        {
            PrintMessage("\n[-2] - UNO!");
            PrintMessage("[-1] - DRAW CARD\n");

            for (int i = 0; i < count; i++)
            {
                currentPlayerCards.at(i).Debug(i);
            }

            int input = reinterpret_cast <Player*>(currentPlayer)->GetPlayerInput();
            
            if (input == -2)
            {
                PrintMessage("\n!!!!!!!!!UNO!!!!!!!!!!");
                if (count > 2)
                {
                    input = -1;

                    for (int cards = 0; cards < 2; cards++)
                    {
                        playerHand->Draw(deckManager->DealCards());
                        isDrawed = true;
                    }

                    acceptedInput = true;
                }
                else
                    calledUno = true;
            }
            else if(input == -1)
            {
                if (drawCount == 0)
                    drawCount = 1;
                else
                    deckManager->topCard.number.SetNumberValue();

                for (int cards = 0; cards < drawCount; cards++)
                {
                    playerHand->Draw(deckManager->DealCards());
                    isDrawed = true;
                }

                PrintMessage(std::to_string(drawCount) + " CARDS DRAWN");
                drawCount = 0;
                acceptedInput = true;
            }
            else if (input < currentPlayerCards.size())
            {
                Card discardCandidate = playerHand->PeekCard(input);

                acceptedInput = reinterpret_cast <Player*>(currentPlayer)->
                    EvaluateInput(discardCandidate, deckManager->topCard.color, deckManager->topCard.number);
                
                if (!acceptedInput)
                {
                    PrintMessage("YOU CANNOT DISCARD THIS CARD");
                    PrintMessage("\nTOP CARD: " + deckManager->topCard.color.GetColorName() + " " + deckManager->topCard.number.GetNumberString());
                    continue;
                }

                Card discard = playerHand->Discard(input);
                deckManager->SendToDiscard(discard);
                deckManager->topCard = *deckManager->GetLastDiscard();
                CheckVictory(calledUno, isPlayer, count, currentIndex);
               
                if (count - 1 < 1 && !calledUno)
                {
                    for (int cards = 0; cards < 2; cards++)
                    {
                        playerHand->Draw(deckManager->DealCards());
                        isDrawed = true;
                    }
                }

                if (discard.color.GetCharColor() == 'n')
                {
                    PrintMessage("SELECT A NEW COLOR:\n[0] -> RED\n[1] -> GREEN\n[2] -> BLUE\n[3] -> YELLOW");
                   
                    char input = _getch();
                    deckManager->topCard.color.SetCharColor(*deckManager->GetSuit(input - '0'));
                    deckManager->topCard.color.name = deckManager->topCard.color.SetName();
                    deckManager->topCard.number.SetNumberValue();
                }
            }

        } while (!acceptedInput);
    }
}

void TableManager::CheckVictory(bool& calledUno, bool& isPlayer, int& handSize, int& playerIndex)
{
    if (calledUno && handSize < 2)
    {
        if (isPlayer)
            PrintMessage("YOU WON!");
        else
            PrintMessage("FOE " + std::to_string(playerIndex) + " WON!");

        hasEnded = false;
    }
}

bool TableManager::CheckRunStatus()
{
    return hasEnded;
}

int TableManager::GetPlayersCount()
{
    return playerOnTable->size();
}

Contestant& TableManager::GetPlayerByIndex(int index)
{
    Contestant tempContestant = playerOnTable->at(index);
    return tempContestant;
}

void TableManager::PrintMessage(std::string text)
{
    printf("%s\n", text.c_str());
}
