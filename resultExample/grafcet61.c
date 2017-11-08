#include "grafcet61.h"

static void action61(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

extern int x61 ;
int x610=1, x611=0, x612=0, x613=0 ;

void grafcet61(){
/**SINGLE**/
	if(x610==1/*&& (|__SINGLE__G610→G611其他條件__|)*/){x610=0; x611=1 ;/*G61初始化內容*/}
	else if(x611==1/*&& (|__SINGLE__G611→G612其他條件__|)*/){x611=0; x612=1 ;}
	else if(x612==1/*&& (|__SINGLE__G612→G613其他條件__|)*/){x612=0; x613=1 ;}
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action61() ;
}

static void action61(){
	if(x611==1){/*|__G611動作__|*/}
	if(x612==1){/*|__G612動作__|*/}
	if(x613==1){/*|__G613動作__|*/}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("－G61狀態： _") ;
	if(x610==1){printf("_||x610||_") ;}if(x611==1){printf("_||x611||_") ;}if(x612==1){printf("_||x612||_") ;}if(x613==1){printf("_||x613||_") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧