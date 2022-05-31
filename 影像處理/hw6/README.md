## 作業說明:
請設計一個基於Run-Length的壓縮法方，對圖檔作無失真壓縮後儲存成新檔案。
## 使用環境/語言:
 * Windows10
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 實作方法:
 1. 主要有兩個檔案紀錄圖片的資訊:**ColorDatabase.txt**、**ImageColor.txt**
 2. 程式會將**圖片出現過的顏色**記錄起來，而且**每種顏色都會對應到一組ID**，並將這些資訊存進**ColorDatabase.txt**。
 3. 程式會紀錄**圖片中的不同顏色出現的狀況**，並將值存到**ImageColor.txt**。
 4. 舉例:假設圖片第一列的pixes分別是:白白黑紅，由於**在ColorDatabase.txt中**，白色是代表0號，黑色代表1號，紅色代表2號，因此**在ImageColor.txt中**紀錄的格式會是:**0:2 1:1 2:2**，這代表在第一列中，白色連續出現2次，緊接著黑色出現1次，再來紅色會出現1次。
 5. 程式壓縮圖片時，會產生**ColorDatabase.txt 和 ImageColor.txt**紀錄圖片資訊。
 6. 程式解壓縮圖片時，會根據**ColorDatabase.txt 和 ImageColor.txt**，將圖片還原。

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
