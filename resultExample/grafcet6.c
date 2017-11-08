#include "grafcet6.h"
#include "grafcet61.h"
#include "grafcet67.h"
#include "grafcet68.h"

static void action6(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

extern int x6 ;
int x60=1, x61=0, x62=0, x63=0, x64=0, x65=0, x66=0, x67=0, x68=0 ;
extern int x610, x611, x612, x613 ;
extern int x670, x671, x672 ;
extern int x680, x681, x682 ;

void grafcet6(){
/**SINGLE**/
	if(x60==1/*&& (|__SINGLE__G60→G61其他條件__|)*/){x60=0; x61=1 ;/*G6初始化內容*/}

/**D_AND**/
	else if(x61==1&&x613==1/*&& (|__D-AND__G61→G62,G63其他條件__|)*/){x61=0; x613=0; x610=1; x62=1; x63=1 ;}

/**D_OR**/
	else if(x62==1/*&& (|__D-OR__G62→G64其他條件__|)*/){x62=0; x64=1 ;}
	else if(x62==1/*&& (|__D-OR__G62→G65其他條件__|)*/){x62=0; x65=1 ;}
	else if(x62==1/*&& (|__D-OR__G62→G66其他條件__|)*/){x62=0; x66=1 ;}

/**C_OR**/
	else if(x64==1/*&& (|__C-OR__G64→G67其他條件__|)*/){x64=0; x67=1 ;}
	else if(x65==1/*&& (|__C-OR__G65→G67其他條件__|)*/){x65=0; x67=1 ;}
	else if(x66==1/*&& (|__C-OR__G66→G67其他條件__|)*/){x66=0; x67=1 ;}

/**C_AND**/
	else if(x63==1&&x67==1&&x671==1&&x672==1/*&& (|__C-AND__G63,G67→G68其他條件__|)*/){x63=0; x67=0; x671=0; x672=0; x670=1; x68=1 ;}
	/*手動加入"&&x671==1" 和 "x671=0;" ^^^ */

/**D_OR**/
	else if(x68==1&&x682==1/*&& (|__D-OR__G68→G61其他條件__|)*/){x68=0; x682=0; x680=1; x61=1 ;}
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action6() ;
}

static void action6(){
	if(x61==1){grafcet61() ;}
	if(x62==1){/*|__G62動作__|*/}
	if(x63==1){/*|__G63動作__|*/}
	if(x64==1){/*|__G64動作__|*/}
	if(x65==1){/*|__G65動作__|*/}
	if(x66==1){/*|__G66動作__|*/}
	if(x67==1){grafcet67() ;}
	if(x68==1){grafcet68() ;}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("－G6狀態： _") ;
	if(x60==1){printf("_|x60|_") ;}if(x61==1){printf("_|x61|_") ;}if(x62==1){printf("_|x62|_") ;}if(x63==1){printf("_|x63|_") ;}if(x64==1){printf("_|x64|_") ;}if(x65==1){printf("_|x65|_") ;}if(x66==1){printf("_|x66|_") ;}if(x67==1){printf("_|x67|_") ;}if(x68==1){printf("_|x68|_") ;}
	if(x610==1){printf("_||x610_||") ;}if(x611==1){printf("_||x611_||") ;}if(x612==1){printf("_||x612_||") ;}if(x613==1){printf("_||x613_||") ;}
	if(x670==1){printf("_||x670_||") ;}if(x671==1){printf("_||x671_||") ;}if(x672==1){printf("_||x672_||") ;}
	if(x680==1){printf("_||x680_||") ;}if(x681==1){printf("_||x681_||") ;}if(x682==1){printf("_||x682_||") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧
