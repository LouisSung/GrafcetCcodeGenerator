## 　**這是自動生成Grafcet架構Ccode的程式，適用於[MIAT方法論](http://ccy.dd.ncu.edu.tw/~chen/resource/MIAT%A4%E8%AAk%BD%D7%C2%B2%A4%B6.pdf)**  
## 　**如果你不知道那是什麼，這個程式可能不是你正在找的東西**  

---

程式運作流程：  
先繪製Grafcet圖形  
而後依照引導輸入Grafcet圖形的各項數據  
產生對應的Ccode架構 (每一張圖都要執行一次這個程式)  

---

```
基本上為了降低code的複雜度，以及增加些許彈性，所以並沒有做太多防呆  
因此請按照要求的輸入格式來回答問題  
不要玩爆我的程式謝謝 Q_Q  
```

```
關於輸入，大致上使用了RE，但是RE的'+'和'*'沒有辦法讓集合內元素不重複出現  
請注意輸入不要出現「重複的狀態」  
ex: G0轉移到哪些狀態： 1123AB (1重複，可能會發生很可怕ㄉ事)  
```
---

### 使用方式： (程式碼可在/resultExample/內找到)  
範例程式：有8張圖的Grafcet  
![image](https://github.com/LouisSung/generateGrafcetCcode/blob/master/resultExample/grafcetExample.png)  
  
看圖回答問題：
![image](https://github.com/LouisSung/generateGrafcetCcode/blob/master/resultExample/fromGrafcetToCcode.png)  

---

### 最後：  
Grafcet有很多眉角需要留意  
雖然我已經認識Grafcet有好一些時日  
但是並不是每種極端/特殊的狀況都可以遇到  
如果只有single path，大概只需要10行左右就可以完成  
剩下的200行左右都是處理Divergence、Convergence的各種條件  
  
　　　＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  
所以　＊　請不要過度依賴自動生成工具　＊  
　　　＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  
  
在開始實做action之前，先確認架構與流程是否都正確  
下面會舉一個需要手動修改的例子  
這是這個程式設計上的限制，而不是bug  
  
  
舉個栗子🌰：  
這裡可以看到671並沒有隨著67轉移到68而變成0  
理由是因為67的結束是一個Convergence AND  
而這個程式只會處理Grafcet67的最後一個狀態(672)  
將672轉移到670，而不是671&672一起轉到670  
(事實上你在Grafcet6裡面，他只詢問你67有幾個狀態(3個))  
(他只在乎有「幾個狀態」，而不在乎那些「狀態之間是如何轉移的」)  
(紀錄幾個狀態主要是用來生成extern int用的)  
如果你不想處理這個問題(嚴格上來說也稱不上是問題XD)  
就讓最後的狀態是SINGLE的即可  
至於要怎麼做到呢？  

> ## 請善用「空狀態」吧  

![image](https://github.com/LouisSung/generateGrafcetCcode/blob/master/resultExample/somethingMustDoneByYourself.png)  

---

```
註：  
可以自行修改實作的部分  
- main.c  
scanf("%s", outputPath) ;		//預設是直接輸出在執行檔所在的目錄，如果想要更換可以自行scanf路徑，路徑長度定義在MAX_PATH_LENGTH，預設是50(包含grafcet檔名長度)  
EOL		//可根據OS不同，修改換行符，預設是"\r\n"  
MAX_SUBGRAFCET_LAYER+1			//可以實作到幾層的subGrafcet，預設是5層  
```
