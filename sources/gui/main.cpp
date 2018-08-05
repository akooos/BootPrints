#include "bootprintsqt.h"
#include <signal.h>
#include <sys/utsname.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
void signalHandler(int sig)
{
    printf("Operating system sent a signal:%d (%s)\n",sig,strsignal(sig));
    BootPrintsQt::instance()->quit(-sig);
}


int main(int argc, char *argv[])
{
    utsname utsName;
    uname(&utsName);
    char hostnam[HOST_NAME_MAX+1];
    size_t len = HOST_NAME_MAX+1;
    gethostname(hostnam,len);

    std::cout << "Hostname " << hostnam << " len" << len << std::endl;
    std::cout <<"Marchine "<<  utsName.machine << std::endl;
    std::cout <<"Release "<<  utsName.release << std::endl;
    std::cout <<"Version "<<  utsName.version << std::endl;
    std::cout <<"sysname "<<  utsName.sysname << std::endl;
    std::cout << "domainname " << utsName.domainname << std::endl;
    std::cout << "nodename " << utsName.nodename << std::endl;

    SCOPE_SENTINEL
    signal(SIGINT,signalHandler);
    signal(SIGTERM,signalHandler);
    signal(SIGKILL,signalHandler);
    return BootPrintsQt::start(argc,argv);
}
