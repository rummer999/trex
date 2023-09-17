#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"

class Sense
{
private:
    ConfigLoader *m_configLoader;
    Level *m_level;
    LocalPlayer *m_localPlayer;
    std::vector<Player *> *m_players;
    X11Utils *m_x11Utils;

public:
    Sense(ConfigLoader *configLoader,
          Level *level,
          LocalPlayer *localPlayer,
          std::vector<Player *> *players,
          X11Utils *x11Utils)
    {
        m_configLoader = configLoader;
        m_level = level;
        m_localPlayer = localPlayer;
        m_players = players;
        m_x11Utils = x11Utils;
    }
    void update()
    {
        if (!m_level->isPlayable())
            return;
        for (int i = 0; i < m_players->size(); i++)
        {
            Player *player = m_players->at(i);
            if (!player->isValid())
                continue;
            if (player->getTeamNumber() == m_localPlayer->getTeamNumber())
                continue;

            if (player->isVisible())
            {
                player->setGlowEnable(1);
                player->setGlowThroughWall(1);
                player->setGlowColorRed(50);
                player->setGlowColorGreen(0);
                player->setGlowColorBlue(0);
            }
            else
            {
                const int enemyShields = player->getShieldsValue();
                int r, g, b;
                if (enemyShields >= 120)
                {
                    r = 30;
                    g = 0;
                    b = 0;
                }
                else if (enemyShields >= 100)
                {
                    r = 15;
                    g = 0;
                    b = 15;
                }
                else if (enemyShields >= 75)
                {
                    r = 0;
                    g = 5;
                    b = 60;
                }
                else
                {
                    r = 0;
                    g = 17;
                    b = 0;
                }

                player->setGlowEnable(1);
                player->setGlowThroughWall(1);
                player->setGlowColorRed(r);
                player->setGlowColorGreen(g);
                player->setGlowColorBlue(b);
            }
        }
    }

};
