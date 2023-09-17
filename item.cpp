#pragma once
#include <cfloat>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "X11Utils.cpp"

class item
{
private:
    Level *m_level;
    LocalPlayer *m_localPlayer;
    std::vector<Player *> *m_players;
    X11Utils *m_x11Utils;
    
    long tmp_counter2;
    bool item_glow_flag;
    
public:
    item(
        Level *level,
        LocalPlayer *localPlayer,
        std::vector<Player *> *players,
        X11Utils *x11Utils)
    {
        m_level = level;
        m_localPlayer = localPlayer;
        m_players = players;
        m_x11Utils = x11Utils;
        
        tmp_counter2 = 0;
        item_glow_flag = true;
    }
    
    void item_glow__pagedown(int counter)
    {
        if (m_x11Utils->keyDown(0xff56) == true) // PAGE_DOWN
        {
            if (tmp_counter2 == 0)
            {
                item_glow_flag = !item_glow_flag;
            }
            tmp_counter2++;
        }
        else
        {
            tmp_counter2 = 0;
        }
    
        if (m_level->isPlayable() == true)
        {
            for (size_t i = 0; i < 15; i++)
            {
                int index = (counter * 15) + i;
                long ent_base = mem::ReadLong(offsets::REGION + offsets::ENTITY_LIST + ((index + 1) << 5));
                
                if (ent_base == 0)
                {
                    continue;
                }
                
                std::string class_name = mem::get_client_class_name(ent_base);
                
                if (class_name != "CPropSurvival" && class_name != "CWeaponX")
                {
                    continue;
                }
                
                int itemID = mem::ReadInt(ent_base + 0x1668);
                
                switch (itemID)
                {
                    //case 139:   // Lite
                        //if (item_glow_flag == true)
                        //{
                            // Устанавливаем оранжевый цвет для объекта 139
                            //int orangeColor = 255 << 16 | 165 << 8 | 0;
                            //mem::WriteInt(ent_base + 0x02f0, orangeColor);
                        //}
                        //else
                        //{
                           // mem::WriteInt(ent_base + 0x02f0, 0);
                        //}
                        //break;
                        
                   case 28:   // Flatline
                        //if (item_glow_flag == true)
                        //{
                            // Устанавливаем оранжевый цвет для объекта 139
                            //int customColor = 130 << 16 | 60 << 8 | 0;
                            //mem::WriteInt(ent_base + 0x02f0, customColor);
                        //}
                        //else
                        //{
                            //mem::WriteInt(ent_base + 0x02f0, 0);
                        //}
                        //break;
                    case 200:   // Evo Shield 4", Rarity::Armor
                    case 199:   // Evo Shield 3", Rarity:Armor
                    case 190:   // Helmet 4
                    case 189:   // Helmet 3
                    case 185:   // Shield Battery
                    case 44:    // Alternator
                    case 80:    // R301
                    case 142:   // Heavy
                    case 257:   // турбозарядник
                    case 208:   // сумка 3
                    case 209:   // сумка 4
                    case 207:   // сумка 2
                    case 219:   // прицел х3
                    case 220:   // прицел х2-4
                    case 218:   // прицел золотой
                    case 217:   // прицел
                    case 216:   // прицел
                    case 215:   // прицел
                    case 214:   // прицел
                    case 234:   // магазин лайт 4
                    case 233:   // плайт маг 3
                    case 237:   // хеви магазин 3
                    case 238:   // хеви магазин 4
                    case 260:   // пробивные боеприпасы
                        if (item_glow_flag == true)
                        {
                            mem::WriteInt(ent_base + 0x02f0, 1363184265); // Светится белым цветом
                        }
                        else
                        {
                            mem::WriteInt(ent_base + 0x02f0, 0);
                        }
                        break;
                }
            }
        }
    }
};

