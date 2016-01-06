#include "platcomm.h"
#include "tcplistener.h"
#include "termioManager.h"
#include "gateCmdHandler.h"
#include "testTcpListener.h"
#include "testTermioManager.h"
#include "testGateCmdHandler.h"

int main(int argc, char* argv[])
{
    if (initSocket())
        return -1;

    if (initObj())
        return -1;

   /* 
    CTestTermioManager tester;
    tester.test();   
    */
   /*
    CTestGateCmdHandler tester;
    tester.test();
*/

    /*
    CTermManager manager;
    manager.init();
*/  

    while (1) {
        platSleep(1);
    }

    deinitSocket();

    return 0;
}