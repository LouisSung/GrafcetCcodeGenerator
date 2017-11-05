//
//  main.c
//  generateGrafcetCcode
//
//  Created by LouisSung on 2017/11/1.
//  Copyright © 2017年 LS. All rights reserved.
//

#include <stdio.h>
#include "generateGrafcet0.h"
#include "generateSubGrafcet.h"
const char* EOL="\r\n" ;
const char outputPath[]="" ;
char grafcetID[5+1] ;			//_Grafcet最深層數(5層)+1

int main(int argc, const char * argv[]) {
	printf("要製作的Grafcet編號(0 | [1-9A-Z][0-9A-Z]*)： ") ;
	scanf("%s", grafcetID) ;
	if(grafcetID[0]=='0'){
		generateGrafcet0() ;}
	else{
		generateSubGrafcet() ;}
	return 0 ;
}
