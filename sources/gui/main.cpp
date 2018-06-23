#include "bootprintsqt.h"
#include <signal.h>

void signalHandler(int sig)
{
    printf("Operating system sent a signal:%d (%s)\n",sig,strsignal(sig));
    BootPrintsQt::instance()->quit(-sig);
}

int main(int argc, char *argv[])
{
    SCOPE_SENTINEL
    signal(SIGINT,signalHandler);
    signal(SIGTERM,signalHandler);
    signal(SIGKILL,signalHandler);
    return BootPrintsQt::start(argc,argv);
}
