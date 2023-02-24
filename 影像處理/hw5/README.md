## 作業說明:
1.撰寫一個程式將所附圖像flower.jpg的黃色花瓣區域擷顯示出來。
## 使用環境/語言:
 * Windows10
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 實作方法:
 1. 輸入圖片路徑後，會檢查**是否可讀取到圖片內容**，若不行，則重新輸入圖片路徑。
 2. 將圖像從**RGB color space**轉成**HSI color space**。如此做圖形處理時，較不會有太多雜訊。
 3. 設定要偵測的顏色的數值範圍(此部分是要設定黃色)
 4. 將第三點設定的數值，代入inRange函式。此操作可以**根據設定的顏色範圍，生成一張二值化的圖(此圖會將目標顏色的區域，設成白色)**
 5. 根據**二值化的圖**的**白色範圍**，重新設定**原圖的像素顏色**，如此即可獲得黃色花瓣。
 6. 印完圖像後，回到**第一點的流程**。
 7. **第一點的流程**輸入0，則終止程式。


## 執行方式/畫面:
![image](https://user-images.githubusercontent.com/82385589/167606748-052e0b0c-8538-4d73-aa71-ff2ab2ce1a69.png)
![image](https://user-images.githubusercontent.com/82385589/167606833-4cfca920-51ca-4a3f-8205-26ff745f2c43.png)
![image](https://user-images.githubusercontent.com/82385589/167607071-a88d16bc-5066-4868-9783-11e938ea61ad.png)
![image](https://user-images.githubusercontent.com/82385589/167607215-120f3be4-1e18-4255-a08a-2a76e7915b0c.png)
     
## 參考資料:
* https://bambovc.com/index.php/archives/43/
* https://cloud.tencent.com/developer/article/1471688
* https://stackoverflow.com/questions/10948589/choosing-the-correct-upper-and-lower-hsv-boundaries-for-color-detection-withcv
* https://stackoverflow.com/questions/23984191/resize-image-opencv
