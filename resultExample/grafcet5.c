#include "grafcet5.h"

static void action5(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

extern int x5 ;
int x50=1, x51=0, x52=0 ;

void grafcet5(){
/**D_OR**/
	if(x50==1/*&& (|__D-OR__G50→G51其他條件__|)*/){x50=0; x51=1 ;/*G5初始化內容*/}
	else if(x50==1/*&& (|__D-OR__G50→G52其他條件__|)*/){x50=0; x52=1 ;/*G5初始化內容*/}

/**C_OR**/
	//else if(x51==1/*&& (|__C-OR__G51→G50其他條件__|)*/){x51=0; x50=1 ;}
	/*手動刪除這行 ^^^ */
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action5() ;
}

static void action5(){
	if(x51==1){/*|__G51動作__|*/}
	if(x52==1){/*|__G52動作__|*/}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("－G5狀態： _") ;
	if(x50==1){printf("_|x50|_") ;}if(x51==1){printf("_|x51|_") ;}if(x52==1){printf("_|x52|_") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧
