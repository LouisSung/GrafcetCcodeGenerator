# generateGrafcetCcode
根據Grafcet圖形產生對應的Ccode架構
依照引導輸入Grafcet的各項數據

```
基本上為了降低code的複雜度，以及增加些許彈性，所以並沒有做太多防呆
因此請按照要求的輸入格式來回答問題
不要玩爆我的程式謝謝 Q_Q
```

```
關於輸入，大致上使用了RE，但是RE的*沒有辦法讓集合內元素不重複出現
注意輸入不要出現「重複的狀態」
ex: G0轉移到哪些狀態： 11 (1重複，可能會發生很可怕ㄉ事)
```

範例使用方式：
![image](https://github.com/LouisSung/generateGrafcetCcode/blob/master/generateGrafcetCcodeExample.png)
