#include "grafcet68.h"

static void action68(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

extern int x68 ;
int x680=1, x681=0, x682=0 ;

void grafcet68(){
/**D_OR**/
	if(x680==1/*&& (|__D-OR__G680→G681其他條件__|)*/){x680=0; x681=1 ;/*G68初始化內容*/}
	else if(x680==1/*&& (|__D-OR__G680→G682其他條件__|)*/){x680=0; x682=1 ;/*G68初始化內容*/}

/**C_OR**/
	//else if(x681==1/*&& (|__C-OR__G681→G680其他條件__|)*/){x681=0; x680=1 ;}
	/*手動刪除這行 ^^^ */
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action68() ;
}

static void action68(){
	if(x681==1){/*|__G681動作__|*/}
	if(x682==1){/*|__G682動作__|*/}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("－G68狀態： _") ;
	if(x680==1){printf("_||x680||_") ;}if(x681==1){printf("_||x681||_") ;}if(x682==1){printf("_||x682||_") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧
