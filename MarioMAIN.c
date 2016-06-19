#include<stdio.h>

int main(int argc,char * argv[])
{
    initscreen();
    loadresourcesfromlevel();
    initcamera();
    initializemario();
    rungame();
    return 0;
}
