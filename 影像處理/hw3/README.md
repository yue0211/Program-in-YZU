## 作業說明:
撰寫一個程式，以灰階模式讀取一張圖像 imread(path, IMREAD_GRAYSCALE)
(a)利用 Sobel Operators 偵測並輸出邊緣成分圖
(b)設計一個類似素描線條的自畫像圖案。
 
## 使用環境/語言:
 * Windows11
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
        ![image](https://user-images.githubusercontent.com/82385589/155843112-12511b61-f6d2-4447-91d1-9269b9adcbd0.png)
 * **整張圖像旋轉的圖:**
        ![image](https://user-images.githubusercontent.com/82385589/155843124-fac961c0-21bc-4352-b911-f581afb4ab22.png)
 * **中心內切圓區域旋轉的圖:**
        ![image](https://user-images.githubusercontent.com/82385589/155843141-0c8a3584-cb9b-440d-8a00-19d2bf8e13b1.png)
     
## 參考資料:
 * https://blog.csdn.net/xingchenbingbuyu/article/details/50719569
 * https://docs.opencv.org/3.4/da/d6a/tutorial_trackbar.html
 
