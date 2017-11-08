#include "grafcet67.h"

static void action67(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

extern int x67 ;
int x670=1, x671=0, x672=0 ;

void grafcet67(){
/**D_AND**/
	if(x670==1/*&& (|__D-AND__G670→G671,G672其他條件__|)*/){x670=0; x671=1; x672=1 ;/*G67初始化內容*/}
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action67() ;
}

static void action67(){
	if(x671==1){/*|__G671動作__|*/}
	if(x672==1){/*|__G672動作__|*/}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("－G67狀態： _") ;
	if(x670==1){printf("_||x670||_") ;}if(x671==1){printf("_||x671||_") ;}if(x672==1){printf("_||x672||_") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧