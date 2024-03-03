#include <iostream>
#include <chrono>
#include <thread>
#include "TableManager.h"

bool isRunning = false;

int main()
{
    TableManager table;
    table.PrintMessage("UNO - THE GAME\n");

    table.PrintMessage("ENABLE AUTOPLAY?\n[0] - NO \n[1] - YES");
    char autoPlay = false;
    std::cin >> autoPlay;
    table.SetToAuto(autoPlay);
    table.Init();
    isRunning = !isRunning;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    system("cls");
    while (isRunning)
    {
        table.NextPlayer();
        std::this_thread::sleep_for(std::chrono::seconds(1/10));
        isRunning = table.CheckRunStatus();
    }
    system("PAUSE");
    return 0;
}