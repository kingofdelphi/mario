#include<stdio.h>
void initscreen();
void loadresourcesfromlevel();
void initcamera();
void initializemario();
void rungame();

int main(int argc,char * argv[])
{
    initscreen();
    loadresourcesfromlevel();
    initcamera();
    initializemario();
    rungame();
    return 0;
}
