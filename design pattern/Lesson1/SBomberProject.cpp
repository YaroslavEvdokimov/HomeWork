
#include <conio.h>

#include "SBomber.h"
#include "MyTools.h"
#include "Time.h"

using namespace std;
using namespace MyTools;

//========================================================================================================================

int main(void)
{
    Timer time("OpenLogFile");
    LogSingletonProxy::getInstance()->OpenLogFile("log.txt");
    

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    Timer time1("OpenLogFile");
    LogSingletonProxy::getInstance()->CloseLogFile();
    return 0;
}
