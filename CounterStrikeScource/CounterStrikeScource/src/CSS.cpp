#include "pch.h"
#include "CSS.h"

namespace CounterStrikeSourceSE
{
    ent* getLocalEnt()
    {
        return *(ent**)(ClientEntList);
    }
    ent* getLocalEntServer()
    {
        eList* elist = *(eList**)(ClientEntList);
        return elist->clients[0].entPtr;
    }
    eList* getEntityList()
    {
        return *(eList**)(ClientEntList);
    }
    viewAngles* getViewAngles()
    {
        return *(viewAngles**)(ClientViewAngles);
    }
    int getNumberOfPlayersAlive()
    {
        return *(int*)(ServerNumberOfPlayers);
    }
    void testPrint(const char* text, ...)
    {
        char format[] = "%s:\f";
        csPrint(format, text);
    }
    bool isEntValid(ent* eEnt)
    {
        if (eEnt == nullptr)
        {
            return false;
        }
        if (eEnt->health < 2)
        {
            return false;
        }
        //if (!eEnt->teamNumber) // this was removed but not deleted because checking the teamnumber might be a good idea?? idk yet.
        //{
        //    return false;
        //}
        return true;
    }
    bool isOnTeam(ent* eEnt)
    {
        if (eEnt->teamNumber == getLocalEntServer()->teamNumber)
            return true;

        return false;
    }
    bool worldToScreen(m_Vector3 position, m_Vector2& screen, float vMatrix[16], int wWidth, int wHeight)
    {
        // i did not make this function, copied from youtube by a someone a lot smarter than I // https://youtu.be/jnUZT2gWWuE?si=T4idoaBny5VK8f1N
        m_Vector4 clipCoords;
        clipCoords.x = position.x * vMatrix[0] + position.y * vMatrix[1] + position.z * vMatrix[2] + vMatrix[3];
        clipCoords.y = position.x * vMatrix[4] + position.y * vMatrix[5] + position.z * vMatrix[6] + vMatrix[7];
        clipCoords.z = position.x * vMatrix[8] + position.y * vMatrix[9] + position.z * vMatrix[10] + vMatrix[11];
        clipCoords.w = position.x * vMatrix[12] + position.y * vMatrix[13] + position.z * vMatrix[14] + vMatrix[15];

        if (clipCoords.w < 0.1f)
            return false;

        m_Vector3 NDC;
        NDC.x = clipCoords.x / clipCoords.w;
        NDC.y = clipCoords.y / clipCoords.w;
        NDC.z = clipCoords.z / clipCoords.w;

        screen.x = (wWidth / 2 * NDC.x) + (NDC.x + wWidth / 2);
        screen.y = -(wHeight / 2 * NDC.y) + (NDC.y + wHeight / 2);
        return true;
    }


    void dumpEntitys()
    {
        eList* elist = *(eList**)(ClientEntList); // <-- client.dll added at #define
        if (elist != nullptr)
        {
            for (int i = 0; i < MaxEntsInList; i++)
            {
                if (isEntValid(elist->clients[i].entPtr))
                {
                    std::cout << "Entity[" << i << "] Health[" << elist->clients[i].entPtr->health << "] Team ID[" << elist->clients[i].entPtr->teamNumber << "]" << std::endl;
                }
            }
        }
    }
    float get3DDistance(m_Vector3 position_self, m_Vector3 position_ent)
    {
        return sqrt(pow(position_ent.x - position_self.x, 2.0) + 
                    pow(position_ent.y - position_self.y, 2.0) +    
                    pow(position_ent.z - position_self.z, 2.0));
    }
}