#include "grafcet4.h"

static void action4(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

extern int x4 ;
int x40=1, x41=0, x42=0 ;

void grafcet4(){
/**D_AND**/
	if(x40==1/*&& (|__D-AND__G40→G41,G42其他條件__|)*/){x40=0; x41=1; x42=1 ;/*G4初始化內容*/}
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action4() ;
}

static void action4(){
	if(x41==1){/*|__G41動作__|*/}
	if(x42==1){/*|__G42動作__|*/}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("－G4狀態： _") ;
	if(x40==1){printf("_|x40|_") ;}if(x41==1){printf("_|x41|_") ;}if(x42==1){printf("_|x42|_") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧