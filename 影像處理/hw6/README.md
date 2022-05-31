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
 4. 舉例:假設圖片第一列的pixes分別是:白白黑紅，由於**在ColorDatabase.txt中**，白色是代表0號，黑色代表1號，紅色代表2號，因此**在ImageColor.txt中**紀錄的格式會是:**0:2 1:1 2:1**，這代表在第一列中，白色連續出現2次，緊接著黑色出現1次，再來紅色會出現1次。
 5. 程式壓縮圖片時，會產生**ColorDatabase.txt 和 ImageColor.txt**紀錄圖片資訊。
 6. 圖片壓縮率的計算方式:**(圖片byte數) / [(ColorDatabase.txt 的byte數)+(ImageColor.txt的byte數)]**

## 執行方式/畫面:

### 壓縮率:
![image](https://user-images.githubusercontent.com/82385589/171224846-e8cf18f2-f315-4fc5-aac1-9a04289d8360.png)
![image](https://user-images.githubusercontent.com/82385589/171225205-28c4fb1f-b595-43be-8f77-7b92c796b9ef.png)
![image](https://user-images.githubusercontent.com/82385589/171225479-ac7756ca-621f-4e85-8690-11d627394134.png)
![image](https://user-images.githubusercontent.com/82385589/171225614-b6206c9a-b184-4211-bd6a-c85a1e4c2911.png)

### 解壓縮的結果:(非原圖比例，原圖太大)
![image](https://user-images.githubusercontent.com/82385589/171223046-a425de26-43fa-477b-8646-49b7837aa84d.png)
![image](https://user-images.githubusercontent.com/82385589/171223324-8a54f040-cd9e-4728-af3f-10fbf0e028bf.png)
![image](https://user-images.githubusercontent.com/82385589/171223509-3721b7ef-d026-46fc-86b0-aab11d03328a.png)

### 檔案資訊:
![image](https://user-images.githubusercontent.com/82385589/171226014-6cc332d3-7d0a-4d3e-8e30-fd196704b752.png)
![image](https://user-images.githubusercontent.com/82385589/171226066-c4ebcd71-a962-45d4-9367-60b063403865.png)
![image](https://user-images.githubusercontent.com/82385589/171226161-8ea2befb-d408-44d1-ab47-c5fe24809be2.png)
![image](https://user-images.githubusercontent.com/82385589/171226654-9e9dbf44-df06-4198-b3ef-0eaef93b3f6b.png)
![image](https://user-images.githubusercontent.com/82385589/171226765-7466ea99-b31a-4218-aeee-705b9675caaf.png)

     

