#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Level.cpp"
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Sense.cpp"
#include "NoRecoil.cpp"
#include "Aimbot.cpp"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"
#include "item.cpp"

int main(int argc, char *argv[])
{
    ConfigLoader *configLoader = new ConfigLoader();
    if (getuid())
    {
        printf("MUST RUN AS ROOT!\n");
        return -1;
    }
    if (mem::GetPID() == 0)
    {
        printf("GAME NOT FOUND. EXITING!\n");
        return -1;
    }
    Level *level = new Level();
    LocalPlayer *localPlayer = new LocalPlayer();
    X11Utils *x11Utils = new X11Utils();
    std::vector<Player *> players;

    for (int i = 0; i < 60; i++)
    {
        players.push_back(new Player(i));
    }

    Sense *sense = new Sense(configLoader, level, localPlayer, &players, x11Utils);
    NoRecoil *noRecoil = new NoRecoil(configLoader, level, localPlayer, &players, x11Utils);
    Aimbot *aimbot = new Aimbot(configLoader, level, localPlayer, &players, x11Utils);
    item itemInstance(level, localPlayer, &players, x11Utils); // Создаем экземпляр класса item

    // Main loop
    printf("MYAPEX STARTING MAIN LOOP\n");
    int counter = 0;
    while (1)
    {
        try
        {
            if (counter % 200 == 0)
                configLoader->reloadFile(); // Попытка перезагрузить конфигурацию, если были какие-либо обновления

            // Разрешаем указатели
            localPlayer->markForPointerResolution();
            for (Player *player : players)
            {
                player->markForPointerResolution();
            }

            // Запускаем функции
            if (configLoader->isAimbotOn())
                aimbot->update();

            if (configLoader->isNorecoilOn())
                noRecoil->update();

            if (configLoader->isSenseOn())
                sense->update();

            itemInstance.item_glow__pagedown(counter); // Вызываем метод через экземпляр класса item

            // Все прошло успешно
            if (counter % 1000 == 0)
                printf("UPDATE[%d] OK. \n", counter);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        catch (...)
        {
            printf("UPDATE[%d] ERROR (LOADING SCREEN?). SLEEPING FOR 10 SECONDS\n", counter);
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
        counter++;
        if (counter > 1000)
            counter = 0;
    }

    // Освобождение памяти
    delete configLoader;
    delete level;
    delete localPlayer;
    delete x11Utils;
    for (Player *player : players)
    {
        delete player;
    }
    delete sense;
    delete noRecoil;
    delete aimbot;

    return 0;
}

