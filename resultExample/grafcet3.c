#include "grafcet3.h"

static void action3(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

extern int x3 ;
int x30=1, x31=0, x32=0, x33=0 ;

void grafcet3(){
/**SINGLE**/
	if(x30==1/*&& (|__SINGLE__G30→G31其他條件__|)*/){x30=0; x31=1 ;/*G3初始化內容*/}
	else if(x31==1/*&& (|__SINGLE__G31→G32其他條件__|)*/){x31=0; x32=1 ;}
	else if(x32==1/*&& (|__SINGLE__G32→G33其他條件__|)*/){x32=0; x33=1 ;}
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action3() ;
}

static void action3(){
	if(x31==1){/*|__G31動作__|*/}
	if(x32==1){/*|__G32動作__|*/}
	if(x33==1){/*|__G33動作__|*/}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("－G3狀態： _") ;
	if(x30==1){printf("_|x30|_") ;}if(x31==1){printf("_|x31|_") ;}if(x32==1){printf("_|x32|_") ;}if(x33==1){printf("_|x33|_") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧