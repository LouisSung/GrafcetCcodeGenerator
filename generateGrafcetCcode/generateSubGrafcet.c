//  ฅ• ω •ฅ 喵~
//  generateSubGrafcet.c
//  generateGrafcetCcode
//
//  Created by LouisSung on 2017/11/3.
//  Copyright © 2017年 LS. All rights reserved.
//
#include <string.h>
#include "generateSubGrafcet.h"
#define MAX_PATH_LENGTH (50)

static void getState(void) ;
static void genHeaderAndStateVariable(void), genGrafcet(void), genAction(void) ;//$
static void genHeaderFile(void) ;//+
//***輸出狀態用⇩
static void genStateCheck(const char* _EOLorEMPTY) ;
//***輸出狀態用⇧

extern const char* EOL ;
extern char grafcetID[6] ;//+
static const char state[36+1]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
static FILE *fptC=NULL ;
static FILE *fptH=NULL ;//+
static int howManyGrafcet=0 ;
static char subGrafcetList[36]={} ;
static int howManyStateOfSubGrafcet[36]={} ;

void generateSubGrafcet(void){//$
	extern const char outputPath[] ;
	char cFile[MAX_PATH_LENGTH], hFile[MAX_PATH_LENGTH] ;
	sprintf(cFile, "%sgrafcet%s.c", outputPath==NULL?"":outputPath, grafcetID) ;//$
	sprintf(hFile, "%sgrafcet%s.h", outputPath==NULL?"":outputPath, grafcetID) ;//$
	
	//==============================
	getState() ;
	fptC=fopen(cFile, "w") ;
	genHeaderAndStateVariable() ;
	genGrafcet() ;
	genAction() ;
	//***輸出狀態用⇩
	genStateCheck("") ;
	//***輸出狀態用⇧
	fclose(fptC) ;
	//==============================
	fptH=fopen(hFile, "w") ;//+
	genHeaderFile() ;//+
	fclose(fptH) ;//+
	//==============================
}

static void getState(){
	printf("G%s有幾個狀態？(2~36)： ", grafcetID) ;//$
	scanf("%d", &howManyGrafcet) ;
	printf("哪些狀態有subGrafcet？(狀態之間不需隔開)([1-9A-Z]+ | no)： ") ;
	scanf("%s", subGrafcetList) ;
	if(subGrafcetList[0]=='n' && subGrafcetList[1]=='o'){
		subGrafcetList[0]='\0' ;
		subGrafcetList[1]='\0' ;
	}
}

static void genHeaderAndStateVariable(){
	//---版權聲明
	fprintf(fptC, "//_auto created by LS' GrafcetCcodeGenerator ฅ• ω •ฅ%s", EOL) ;
	
	//---引入標頭檔
	fprintf(fptC, "#include \"grafcet%s.h\"%s", grafcetID, EOL) ;//$
	for(int i=0; i<strlen(subGrafcetList); ++i){			//_include"subSubGrafcets.h"
		fprintf(fptC, "#include \"grafcet%s%c.h\"%s", grafcetID, subGrafcetList[i], EOL) ;}//$
	
	//---函式宣告
	fprintf(fptC, "%s", EOL) ;			//_grafcet#()、action#()的原型宣告
	fprintf(fptC, "static void action%s(void) ;%s", grafcetID, EOL) ;//$
	
	//***輸出狀態用⇩
	fprintf(fptC, "//***輸出狀態用⇩%sstatic void stateCheck(void) ;%s//***輸出狀態用⇧%s", EOL, EOL, EOL) ;
	//***輸出狀態用⇧
	
	//---Grafcet#狀態變數宣告
	fprintf(fptC, "%s", EOL) ;
	fprintf(fptC, "extern int x%s ;%s", grafcetID, EOL) ;//+			//_引入自己的狀態變數
	fprintf(fptC, "int x%s0=1, ", grafcetID) ;//$			//_G#0狀態變數宣告
	for(int i=1; i<howManyGrafcet; ++i){			//_G#1~G#last狀態變數宣告
		fprintf(fptC, "x%s%c=0%s", grafcetID, state[i], i==howManyGrafcet-1?" ;":", ") ;}//$
	fprintf(fptC, "%s", EOL) ;
	
	//---subSubGrafcet狀態變數宣告
	if(strlen(subGrafcetList)!=0){
		printf("\n===\n") ;}
	for(int i=0; i<strlen(subGrafcetList); ++i){
		printf("G%s%c的subGrafcet有幾個狀態？(2~36)： ", grafcetID, subGrafcetList[i]) ;//$
		int indexOfSubGrafcet=0 ;
		if('0'<=subGrafcetList[i] && subGrafcetList[i]<='9'){			//_把subSubGrafcet的state換成編號
			indexOfSubGrafcet=subGrafcetList[i]-'0' ;}			//_'0'->0
		else if('A'<=subGrafcetList[i] && subGrafcetList[i]<='Z'){
			indexOfSubGrafcet=subGrafcetList[i]-'A'+10 ;}		//_'A'->10
		scanf("%d", &howManyStateOfSubGrafcet[indexOfSubGrafcet]) ;			//_紀錄哪些有subSubGrafcet
		fprintf(fptC, "extern int ") ;
		for(int j=0; j<howManyStateOfSubGrafcet[indexOfSubGrafcet]; ++j){
			fprintf(fptC, "x%s%c%c%s", grafcetID, state[indexOfSubGrafcet], state[j], j==howManyStateOfSubGrafcet[indexOfSubGrafcet]-1?" ;":", ") ;}//$
		fprintf(fptC, "%s", EOL) ;
	}
	fseek(fptC, -(strlen(EOL)), SEEK_END) ;			//_移除最後的空白行
}

static void genGrafcet(){
	//_Gi=現在狀態, Gj=下一狀態, Gk=其他個別狀態, Gns=上下多狀態, []*t=[動作]做t次
	//---產生grafcet()
	fprintf(fptC, "%s%s", EOL, EOL) ;
	fprintf(fptC, "void grafcet%s(){%s", grafcetID, EOL) ;//$
	
	//---產生狀態轉移條件
	enum translationType{SINGLE=1, D_AND, D_OR, C_AND, C_OR}previousType=0, currentType=0 ;
	const char tType[6][7]={"","SINGLE", "D_AND", "D_OR", "C_AND", "C_OR"} ;			//`enum->string
	char translationTo[36]={} ;
	char cAndList[36][36]={} ;
	unsigned char remindConvergenceFlag=0 ;
	printf("\n===\n") ;
	for(int i=0; i<howManyGrafcet; ++i){
		//---C_AND:多個Gn收斂至Gi
		if(strlen(cAndList[i])!=0){
			currentType=C_AND ;
			if(currentType!=previousType){
				fprintf(fptC, "%s/**%s**/%s", i==0?"":EOL, tType[currentType], EOL) ;}			//`分隔不同類型區塊
			fprintf(fptC, "\t%s(", i==0?"if":"else if") ;			//_第一行if, 其他行else if
			for(int j=0; j<strlen(cAndList[i]); ++j){				//_if(xi==1&&xns==1...)
				fprintf(fptC, "x%s%c==1%s", grafcetID, cAndList[i][j], j==strlen(cAndList[i])-1?"":"&&") ;//$
				int indexOfCAndList=(cAndList[i][j]<='9'?cAndList[i][j]-'0':cAndList[i][j]-'A'+10) ;
				if(howManyStateOfSubGrafcet[indexOfCAndList]!=0){			//_下層subGrafcet完成後, 上層才轉移
					fprintf(fptC, "%sx%s%c%c==1%s", j==strlen(cAndList[i])-1?"&&":"", grafcetID,  state[indexOfCAndList], state[howManyStateOfSubGrafcet[indexOfCAndList]-1], j==strlen(cAndList[i])-1?"":"&&") ;}
			}
			fprintf(fptC, "/*&& (|__C-AND__") ;
			printf("C_AND：") ;
			for(int j=0; j<strlen(cAndList[i]); ++j){
				fprintf(fptC, "G%s%c%s", grafcetID, cAndList[i][j], j==strlen(cAndList[i])-1?"":",") ;//$
				printf("G%s%c%s", grafcetID, cAndList[i][j], j==strlen(cAndList[i])-1?"":",") ;//$
			}
			fprintf(fptC, "→G%s%c其他條件__|)*/){", grafcetID, state[i]) ;//$				//_Gns...->Gi
			printf("收斂到G%s%c\n", grafcetID, state[i]) ;//$
			for(int j=0; j<strlen(cAndList[i]); ++j){			//_{xns=0...,xi=1}
				fprintf(fptC, "x%s%c=0; ", grafcetID, cAndList[i][j]) ;//$
				int indexOfCAndList=(cAndList[i][j]<='9'?cAndList[i][j]-'0':cAndList[i][j]-'A'+10) ;
				if(howManyStateOfSubGrafcet[indexOfCAndList]!=0){			//_上層Grafcet控制下層轉移
					fprintf(fptC, "x%s%c%c=0; x%s%c0=1; ", grafcetID, state[indexOfCAndList], state[howManyStateOfSubGrafcet[indexOfCAndList]-1], grafcetID, state[indexOfCAndList]) ;}//$
			}
			fprintf(fptC, "x%s%c=1 ;%s%s%s}%s", grafcetID, state[i], i==0?"/*G":"", i==0?grafcetID:"", i==0?"初始化內容*/":"", EOL) ;//$
		}
		
		//---確認Gi狀態(SINGLE/D_AND/D_OR/C_AND/C_OR)
		printf("G%s%c會轉移到哪些狀態？(狀態之間不需隔開)(%s[0-9A-Z]+)： ", grafcetID, state[i], remindConvergenceFlag==0?"":"(and|or)?") ;//$			//_曾出現D_AND或D_OR, 新增前綴選項可供輸入
		scanf("%s", translationTo) ;
		char divergenceType[4]={} ;			//_用來記錄是D_AND或D_OR
		if(strlen(translationTo)>1){
			if(strncmp(translationTo, "and", 3)!=0 && strncmp(translationTo, "or", 2)!=0){			//_無and/or前綴
				if(remindConvergenceFlag==0){			//_第一次出現D_AND或D_OR時, 提醒使用者
					printf("\n＊＊＊ 想要Convergence時請在轉移狀態加上and/or前綴(ex:or5會C_OR到G5)\n\n") ;
					remindConvergenceFlag=1 ;
				}
				printf("G%s%c Divergence到多個狀態是D_AND還是D_OR？(and|or)： ", grafcetID, state[i]) ;
				scanf("%s", divergenceType) ;
			}}
		
		//---最後一個狀態須由上層控制器來轉移至初始狀態(Gxlast→Gx0)//+
		if(i==howManyGrafcet-1 && translationTo[0]=='0'){//+
			if(strlen(translationTo)==1){
				break ;}			//不轉移到Gx0
			else{
				memmove(translationTo, translationTo+1, strlen(translationTo));}}			//_移除轉移到Gx0
		else if(i==howManyGrafcet-1 && strcmp(translationTo, "or0")==0){//+
			break ;}			//_判斷是否為or0
		
		//---D_AND:Gi發散至多個Gn
		if(strcmp(divergenceType, "and")==0){
			currentType=D_AND ;
			if(currentType!=previousType){
				fprintf(fptC, "%s/**%s**/%s", i==0?"":EOL, tType[currentType], EOL) ;}		//`^
			fprintf(fptC, "\t%s", i==0?"if":"else if") ;		//_if(xi==1)
			fprintf(fptC, "(x%s%c==1", grafcetID, state[i]) ;
			if(howManyStateOfSubGrafcet[i]!=0){//^
				fprintf(fptC, "&&x%s%c%c==1",grafcetID , state[i], state[howManyStateOfSubGrafcet[i]-1]) ;}//$
			fprintf(fptC, "/*&& (|__D-AND__G%s%c→", grafcetID, state[i]) ;//$
			for(int j=0; j<strlen(translationTo); ++j){		//_Gi->Gns...
				fprintf(fptC, "G%s%c%s", grafcetID, translationTo[j], j==strlen(translationTo)-1?"":",") ;}//$
			fprintf(fptC, "其他條件__|)*/){x%s%c=0; ", grafcetID, state[i]) ;//$
			if(howManyStateOfSubGrafcet[i]!=0){			//^
				fprintf(fptC, "x%s%c%c=0; x%s%c0=1; ", grafcetID, state[i], state[howManyStateOfSubGrafcet[i]-1], grafcetID, state[i]) ;}//$
			for(int j=0; j<strlen(translationTo); ++j){			//_{xi=0, xns=1...}
				fprintf(fptC, "x%s%c=1%s", grafcetID, translationTo[j], j==strlen(translationTo)-1?" ;":"; ") ;}//$
			fprintf(fptC, "%s%s%s}%s", i==0?"/*G":"", i==0?grafcetID:"", i==0?"初始化內容*/":"", EOL) ;
		}
		
		//---D_OR:Gi發散至多個Gns
		else if(strcmp(divergenceType, "or")==0){
			currentType=D_OR ;
			if(currentType!=previousType){
				fprintf(fptC, "%s/**%s**/%s", i==0?"":EOL, tType[currentType], EOL) ;}			//`^
			for(int j=0; j<strlen(translationTo); ++j){			//_if(xi==1)
				fprintf(fptC, "\t%s", i==0&&j==0?"if":"else if") ;			//_[Gi->Gj]*t
				fprintf(fptC, "(x%s%c==1", grafcetID, state[i]) ;//$
				if(howManyStateOfSubGrafcet[i]!=0){//^
					fprintf(fptC, "&&x%s%c%c==1",grafcetID , state[i], state[howManyStateOfSubGrafcet[i]-1]) ;}//$
				fprintf(fptC, "/*&& (|__D-OR__G%s%c→G%s%c其他條件__|)*/){x%s%c=0; ", grafcetID, state[i], grafcetID, translationTo[j], grafcetID, state[i]) ;//$
				if(howManyStateOfSubGrafcet[i]!=0){			//^
					fprintf(fptC, "x%s%c%c=0; x%s%c0=1; ", grafcetID, state[i], state[howManyStateOfSubGrafcet[i]-1], grafcetID, state[i]) ;}//$
				fprintf(fptC, "x%s%c=1 ;%s%s%s}%s", grafcetID, translationTo[j], i==0?"/*G":"", i==0?grafcetID:"", i==0?"初始化內容*/":"", EOL) ;//$			//_[{xi=0; xj=1}]*t
			}
		}
		
		//---C_OR:多個Gns收斂至Gi
		else if(remindConvergenceFlag==1 && strncmp(translationTo, "or", 2)==0){			//_if(xj==1)
			currentType=C_OR ;
			if(currentType!=previousType){
				fprintf(fptC, "%s/**%s**/%s", i==0?"":EOL, tType[currentType], EOL) ;}			//`^
			fprintf(fptC, "\t%s", i==0?"if":"else if") ;			//_Gj->Gi
			fprintf(fptC, "(x%s%c==1", grafcetID, state[i]) ;//$
			if(howManyStateOfSubGrafcet[i]!=0){//^
				fprintf(fptC, "&&x%s%c%c==1",grafcetID , state[i], state[howManyStateOfSubGrafcet[i]-1]) ;}//$
			fprintf(fptC, "/*&& (|__C-OR__G%s%c→G%s%c其他條件__|)*/){x%s%c=0; ", grafcetID, state[i], grafcetID, translationTo[2], grafcetID, state[i]) ;//$
			if(howManyStateOfSubGrafcet[i]!=0){			//^
				fprintf(fptC, "x%s%c%c=0; x%s%c0=1; ", grafcetID, state[i], state[howManyStateOfSubGrafcet[i]-1], grafcetID, state[i]) ;}//$
			fprintf(fptC, "x%s%c=1 ;%s%s%s}%s", grafcetID, translationTo[2], i==0?"/*G":"", i==0?grafcetID:"", i==0?"初始化內容*/":"", EOL) ;//$			//_{xj=0, xi=1}
		}
		
		//---紀錄C_AND:(僅建表)多個Gns收斂至Gi
		else if(remindConvergenceFlag==1 && strncmp(translationTo, "and", 3)==0){
			int indexOfTranslation=0 ;
			if(translationTo[3]<='9'){			//_把轉移目標的state換成編號
				indexOfTranslation=translationTo[3]-'0' ;}
			else if(translationTo[3]<='Z'){
				indexOfTranslation=translationTo[3]-'A'+10 ;}
			cAndList[indexOfTranslation][strlen(cAndList[indexOfTranslation])]=state[i] ;			//_Gi收斂到Gk, 紀錄在Gk的表中, 最後Gk的表會紀錄有狀態Gi,Gns...收斂到他
		}
		
		//---SINGLE:普通的單線轉移Gi->Gj
		else{			//_if(xi==1)
			currentType=SINGLE ;
			if(currentType!=previousType){
				fprintf(fptC, "%s/**%s**/%s", i==0?"":EOL, tType[currentType], EOL) ;}			//`^
			fprintf(fptC, "\t%s", i==0?"if":"else if") ;		//_Gi->Gj
			fprintf(fptC, "(x%s%c==1", grafcetID, state[i]) ;//$
			if(howManyStateOfSubGrafcet[i]!=0){//^
				fprintf(fptC, "&&x%s%c%c==1",grafcetID , state[i], state[howManyStateOfSubGrafcet[i]-1]) ;}//$
			fprintf(fptC, "/*&& (|__SINGLE__G%s%c→G%s%c其他條件__|)*/){x%s%c=0; ", grafcetID, state[i], grafcetID, translationTo[0], grafcetID, state[i]) ;//$
			if(howManyStateOfSubGrafcet[i]!=0){			//^
				fprintf(fptC, "x%s%c%c=0; x%s%c0=1; ", grafcetID, state[i], state[howManyStateOfSubGrafcet[i]-1], grafcetID, state[i]) ;}//$
			fprintf(fptC, "x%s%c=1 ;%s%s%s}%s", grafcetID, translationTo[0], i==0?"/*G":"", i==0?grafcetID:"", i==0?"初始化內容*/":"", EOL) ;//$			//_{xi=0, xj=1}
		}
		previousType=currentType ;
	}
	
	//-移除特殊C_AND:Gxns→Gx0//-
	
	//***輸出狀態用⇩
	fprintf(fptC, "//***輸出狀態用⇩%s\tstateCheck() ;%s//***輸出狀態用⇧", EOL, EOL) ;
	//***輸出狀態用⇧
	
	//---產生ActionFunctionCall
	fprintf(fptC, "%s\taction%s() ;%s}", EOL, grafcetID, EOL) ;//$
}

static void genAction() {
	//---產生action()
	fprintf(fptC, "%s%s", EOL, EOL) ;
	fprintf(fptC, "static void action%s(){%s", grafcetID, EOL) ;//$
	for(int i=1; i<howManyGrafcet; ++i){
		fprintf(fptC, "\tif(x%s%c==1){", grafcetID, state[i]) ;
		if(howManyStateOfSubGrafcet[i]!=0){			//_呼叫subGrafcet
			fprintf(fptC, "grafcet%s%c() ;", grafcetID, state[i]) ;}
		else{
			fprintf(fptC, "/*|__G%s%c動作__|*/", grafcetID, state[i]) ;}
		fprintf(fptC, "}%s", EOL) ;
	}
	fprintf(fptC, "}") ;
}

//***輸出狀態用⇩
static void genStateCheck(const char* EOLorEMPTY){
	//---產生stateCheck()
	unsigned char eolFlag=!strcmp(EOLorEMPTY, EOL) ;			//_紀錄換行與否
	fprintf(fptC, "%s%s", EOL, EOL) ;
	fprintf(fptC, "//***輸出狀態用⇩%sstatic void stateCheck(){%s\tprintf(\"－G%s狀態： _\") ;%s", EOL, EOL, grafcetID, EOL) ;//$
	for(int i=0; i<howManyGrafcet; ++i){			//_G0各狀態
		if(eolFlag==1 || i==0){			//_(第一行/不換行時各if之間)的空白
			fprintf(fptC, "\t") ;}
		fprintf(fptC, "if(x%s%c==1){printf(\"_", grafcetID, state[i]) ;//$
		for(int j=0; j<strlen(grafcetID); ++j){//+
			fprintf(fptC,"|") ;}
		fprintf(fptC, "x%s%c", grafcetID, state[i]) ;//$
		for(int j=0; j<strlen(grafcetID); ++j){//+
			fprintf(fptC,"|") ;}
		fprintf(fptC, "_\") ;}%s", EOLorEMPTY) ;//$
	}
	fprintf(fptC, "%s", EOL);			//_每一組之間換行
	for(int i=0; i<strlen(subGrafcetList); ++i){		//_subGrafcet各狀態
		if(eolFlag==0){
			fprintf(fptC, "\t") ;}		//_換行時的空白
		int numOfSG=subGrafcetList[i]<='9'?subGrafcetList[i]-'0':subGrafcetList[i]-'A'+10 ;
		for(int j=0; j<howManyStateOfSubGrafcet[numOfSG]; ++j){
			if(eolFlag==1){
				fprintf(fptC, "\t") ;}
			fprintf(fptC, "if(x%s%c%c==1){printf(\"_", grafcetID, subGrafcetList[i], state[j]) ;//$
			for(int j=0; j<strlen(grafcetID)+1; ++j){//+
				fprintf(fptC,"|") ;}
			fprintf(fptC, "x%s%c%c_", grafcetID, subGrafcetList[i], state[j]) ;//$
			for(int j=0; j<strlen(grafcetID)+1; ++j){//+
				fprintf(fptC,"|") ;}
			fprintf(fptC,"\") ;}%s", EOLorEMPTY) ;//$
		}
		fprintf(fptC, "%s", EOL) ;
	}
	if(eolFlag==1){
		fseek(fptC, -(strlen(EOL)), SEEK_END) ;}		//_移除多餘的空白行
	fprintf(fptC, "\tprintf(\"_\\n\") ;%s}%s//***輸出狀態用⇧", EOL, EOL) ;
}
//***輸出狀態用⇧

void genHeaderFile(void){//+
	fprintf(fptH, "#ifndef grafcet%s_h%s#define grafcet%s_h%s%s#include <stdio.h>%svoid grafcet%s(void) ;%s%s#endif /* grafcet%s_h */", grafcetID, EOL, grafcetID, EOL, EOL, EOL, grafcetID, EOL, EOL, grafcetID) ;//+
}
