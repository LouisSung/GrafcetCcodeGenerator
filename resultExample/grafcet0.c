#include <stdio.h>
#include <stdlib.h>
#include "grafcet3.h"
#include "grafcet4.h"
#include "grafcet5.h"
#include "grafcet6.h"

void grafcet0(void) ;
static void action0(void) ;
//***輸出狀態用⇩
static void stateCheck(void) ;
//***輸出狀態用⇧

int x0=1, x1=0, x2=0, x3=0, x4=0, x5=0, x6=0, x7=0, x8=0 ;
extern int x30, x31, x32, x33 ;
extern int x40, x41, x42 ;
extern int x50, x51, x52 ;
extern int x60, x61, x62, x63, x64, x65, x66, x67, x68 ;

int main(){
	while(1){
		grafcet0() ;}
}

void grafcet0(){
/**SINGLE**/
	if(x0==1/*&& (|__SINGLE__G0→G1其他條件__|)*/){x0=0; x1=1 ;/*G0初始化內容*/}

/**D_AND**/
	else if(x1==1/*&& (|__D-AND__G1→G2,G3其他條件__|)*/){x1=0; x2=1; x3=1 ;}

/**D_OR**/
	//else if(x2==1/*&& (|__D-OR__G2→G4其他條件__|)*/){x2=0; x4=1 ;}
	//else if(x2==1/*&& (|__D-OR__G2→G5其他條件__|)*/){x2=0; x5=1 ;}
	else if(x2==1/*&& (|__D-OR__G2→G6其他條件__|)*/){x2=0; x6=1 ;}

/**C_OR**/
	else if(x4==1&&x42==1/*&& (|__C-OR__G4→G7其他條件__|)*/){x4=0; x42=0; x40=1; x7=1 ;}
	else if(x5==1&&x51==1/*&& (|__C-OR__G5→G7其他條件__|)*/){x5=0; x51=0; x50=1; x7=1 ;}
	/*手動加入"else if(x5==1&&x51==1)" ^^^ */
	else if(x5==1&&x52==1/*&& (|__C-OR__G5→G7其他條件__|)*/){x5=0; x52=0; x50=1; x7=1 ;}
	else if(x6==1&&x68==1/*&& (|__C-OR__G6→G7其他條件__|)*/){x6=0; x68=0; x60=1; x7=1 ;}

/**C_AND**/
	else if(x3==1&&x33==1&&x7==1/*&& (|__C-AND__G3,G7→G8其他條件__|)*/){x3=0; x33=0; x30=1; x7=0; x8=1 ;}

/**D_OR**/
	else if(x8==1/*&& (|__D-OR__G8→G0其他條件__|)*/){x8=0; x0=1 ;}
	else if(x8==1/*&& (|__D-OR__G8→G1其他條件__|)*/){x8=0; x1=1 ;}
//***輸出狀態用⇩
	stateCheck() ;
//***輸出狀態用⇧
	action0() ;
}

static void action0(){
	if(x1==1){/*|__G1動作__|*/}
	if(x2==1){/*|__G2動作__|*/}
	if(x3==1){grafcet3() ;}
	if(x4==1){grafcet4() ;}
	if(x5==1){grafcet5() ;}
	if(x6==1){grafcet6() ;}
	if(x7==1){/*|__G7動作__|*/}
	if(x8==1){/*|__G8動作__|*/}
}

//***輸出狀態用⇩
static void stateCheck(){
	printf("＊G0狀態： _") ;
	if(x0==1){printf("_x0_"); exit(35211) ;}if(x1==1){printf("_x1_") ;}if(x2==1){printf("_x2_") ;}if(x3==1){printf("_x3_") ;}if(x4==1){printf("_x4_") ;}if(x5==1){printf("_x5_") ;}if(x6==1){printf("_x6_") ;}if(x7==1){printf("_x7_") ;}if(x8==1){printf("_x8_") ;}
	if(x30==1){printf("_|x30|_") ;}if(x31==1){printf("_|x31|_") ;}if(x32==1){printf("_|x32|_") ;}if(x33==1){printf("_|x33|_") ;}
	if(x40==1){printf("_|x40|_") ;}if(x41==1){printf("_|x41|_") ;}if(x42==1){printf("_|x42|_") ;}
	if(x50==1){printf("_|x50|_") ;}if(x51==1){printf("_|x51|_") ;}if(x52==1){printf("_|x52|_") ;}
	if(x60==1){printf("_|x60|_") ;}if(x61==1){printf("_|x61|_") ;}if(x62==1){printf("_|x62|_") ;}if(x63==1){printf("_|x63|_") ;}if(x64==1){printf("_|x64|_") ;}if(x65==1){printf("_|x65|_") ;}if(x66==1){printf("_|x66|_") ;}if(x67==1){printf("_|x67|_") ;}if(x68==1){printf("_|x68|_") ;}
	printf("_\n") ;
}
//***輸出狀態用⇧
