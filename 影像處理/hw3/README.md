## 作業說明:
撰寫一個程式，以**灰階模式讀取一張圖像** imread(path, IMREAD_GRAYSCALE)
1. 利用 Sobel Operators 偵測並輸出邊緣成分圖
2. 設計一個類似素描線條的自畫像圖案。
 
## 使用環境/語言:
 * Windows 11
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 實作方法: 
 1. 輸入圖片路徑後，會檢查**是否可讀取到圖片內容**，若不行，則重新輸入圖片路徑。
 2. 利用 **高斯模糊**，將照片的雜訊去除。
 3. 利用 **sobel operator**偵測圖片邊緣。
 4. 利用 **threshold 函數**，將(3)的圖片的**黑色部分轉成白色，白色部分轉成黑色**。
 7. 將(2)、(3)、(4)的圖像印出。
 8. **第一點的流程**輸入0，則終止程式。

## 執行方式/畫面:

 * **原圖:**
 
   ![image](https://user-images.githubusercontent.com/82385589/158057460-a3aeefe4-91fa-4d86-be03-156be504b374.png)
   
 * **灰階圖(高斯模糊處理過):**
 
   ![image](https://user-images.githubusercontent.com/82385589/158057482-b9af84bc-16c7-47e6-889f-cc9fd7202510.png)
   
 * **邊緣偵測的圖:**
 
   ![image](https://user-images.githubusercontent.com/82385589/158057497-6945b02b-781b-4228-a075-81c3fb341f76.png)
   
 * **素描圖:**    
 
   ![image](https://user-images.githubusercontent.com/82385589/158057591-49867b37-dd48-4060-aa2f-3ad282d01af2.png)

## 參考資料:
 * https://blog.csdn.net/u012566751/article/details/77046445
 * https://docs.opencv.org/4.2.0/d2/d2c/tutorial_sobel_derivatives.html
 
