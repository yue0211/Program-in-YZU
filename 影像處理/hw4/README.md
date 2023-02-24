## 作業說明:
* 計算輸入圖的離散傅立葉轉換結果，並將頻譜大小與相位角度各以灰階256色圖像方式呈現出。
* 對圖像利用Gaussian Low-Pass filter處理，輸出平滑後圖像。
* 程式利用課本的frequency filter步驟者可得滿分，在網頁中將每個步驟結果呈現出。直接套用opencv函數得一半分數。
 
## 使用環境/語言:
 * Windows11
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 實作方法: 
 1. 輸入圖片路徑後，會檢查**是否可讀取到圖片內容**，若不行，則重新輸入圖片路徑。
 2. 輸入圖片欲模糊的程度。
 3. 讀取灰階圖片，並利用copyMakeBorder函式，將圖片的長、寬都調整為原圖兩倍。
 4. 將**新尺寸的圖片(padded image)** 的**型態換成CV_32FC1**，因為要對**圖片的每個像素乘上(-1)^(x+y)**，若沒轉型態的話會報錯，乘完後將**型態轉回CV_8UC1**，負數即會消失。
 5. 利用高斯低通濾波器的函數定義，求出高斯低通濾波器。
 6. 利用dft函式(傅立葉轉換函式)，算出**新尺寸的圖片(padded image)** 的複數值，然後**將複數值拆成實數和虛數**。
 7. 利用magnitude函式，**將第6點的實數和虛數轉成振幅值**，再將**振幅值轉成對數**，然後**利用normalize函式，將對數做歸一化**，如此**即可求出原圖的頻譜大小**。
 8. 利用Phase函式，**將第6點的實數和虛數轉成相位角度值**，然後**利用normalize函式，將相位角度值做歸一化**，如此**即可求出原圖的相位角度**。
 9. 利用multiply函式，將**第5點求出的高斯低通濾波器**與**第6點的實數和虛數** 互相做卷積，卷積完會得到新的實數和虛數，再**利用merge函式，將新的實數和虛數，組成一個新的複數**。
 10. 利用idft函式(反傅立葉轉換函式)，將**第9點的複數值**轉換成**新的複數值**，再利用split函式，將**新的複數值，拆成新的實數和虛數**。
 11. 利用magnitude函式，將**第10點的實數和虛數**轉換成**新的振幅值**，此部分**不需要將振幅值轉成對數**，因為此部分所用的實數和虛數是利用idft函式求得的值。
 12. 利用normalize函式，**將第11點的振幅值做歸一化**，然後**再將此部分求出的圖片，轉換成原圖片的尺寸**，如此**即可求出Gaussian Low-Pass filter處理後的，平滑圖像**。
 13. 印完圖像後，可讓使用者選擇是否要繼續輸入圖片欲模糊的程度，觀察同張圖片不同的模糊效果，若輸入^z，則回到**第一點的流程**。

## 執行方式/畫面:

### 原圖:
![image](https://user-images.githubusercontent.com/82385589/163253572-c2e548a0-b0fd-4565-b19a-b0dc10e4692a.png)
### 灰階圖:
![image](https://user-images.githubusercontent.com/82385589/163253661-63c0540d-88d9-46c9-8a2a-85cc528eb823.png)
### zero-padded image:
![image](https://user-images.githubusercontent.com/82385589/163251424-e0c8cd73-ab75-4420-b6f7-9682d0e5da41.png)
### zero-padded image multiply by (-1)^(x+y):
![image](https://user-images.githubusercontent.com/82385589/163251788-d9b65927-d687-4d32-9442-4c028aaa9dd1.png)
### 高斯濾波器函數:
![image](https://user-images.githubusercontent.com/82385589/163251848-e2d97f36-e5a9-467c-a648-be3afceb0da5.png)
### 原圖的頻譜大小:
![image](https://user-images.githubusercontent.com/82385589/163251886-ac5cbcf2-d0e7-4580-9036-cc5d57f3a743.png)
### 原圖的相位角度:
![image](https://user-images.githubusercontent.com/82385589/163252861-63687767-00c2-4201-b4c3-78a63173f1ce.png)
### 原圖與濾波器函數相乘的頻譜大小:
![image](https://user-images.githubusercontent.com/82385589/163252937-f3508656-76b5-4595-85c8-e0ed7b4d33f6.png)
### Gaussian filter(未調整為原尺寸):
![image](https://user-images.githubusercontent.com/82385589/163253139-8c62a21e-c6d3-4ed3-b946-bb6ce2fb641d.png)
### Gaussian filter(調整為原尺寸):
![image](https://user-images.githubusercontent.com/82385589/163253195-2b68be5f-7ea7-4a6f-9fd4-6aed7f5dbe4e.png)

## 參考資料:
* https://blog.csdn.net/cyf15238622067/article/details/87918125
* https://blog.csdn.net/yuandm819/article/details/79897868
* https://blog.csdn.net/jerwey/article/details/103991174
* https://www.twblogs.net/a/5c761cffbd9eee31cea509be
* https://www.twblogs.net/a/5b820dc82b71772165af693c
* https://iter01.com/541551.html
