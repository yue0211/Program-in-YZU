## 作業說明:
請撰寫一個程式，利用數學型態學影像處理運算(erode(), dilate()等函式)，計算出所附圖像(共三張)每張圖像中圍棋個數。
## 使用環境/語言:
 * Windows10
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 實作方法:
1. 輸入圖片路徑後，會檢查**是否可讀取到圖片內容**，若不行，則重新輸入圖片路徑。
2. 由於 **erode及dilate**，只能用於**經過二值化運算的灰階圖片**。因此**先將圖片轉成灰階圖**，並**利用threshold對圖片進行二值化運算**。
3. 將**經過二值化運算的灰階圖片**代入erode，如此能讓圖片去噪、細化影像和消除毛刺。
4. 由於 erode 會讓**圖片的輪廓**變細，因此需要利用 dilate 讓**圖片的輪廓**恢復正常大小，圖片會較清晰。
5. 利用 HoughCircles，偵測圖中的圓形個數，**圓形個數即為圍棋個數**。
6. 根據圓形的**圓心座標及圓半徑**畫圓，利用**circle函式**畫圓。
7. 使用迴圈，將偵測到的**所有圓形**畫在圖片上。
8. 印完圖片後，回到**第一點的流程**。
9. **第一點的流程**輸入0，則終止程式。 


## 執行方式/畫面:
### IMG_5702.JPG:(原圖:24顆圍棋，偵測:23顆圍棋)
![image](https://user-images.githubusercontent.com/82385589/171550627-8d1ddcf6-c30f-484a-8243-06c7d917332e.png)
![image](https://user-images.githubusercontent.com/82385589/171550575-49721978-d5e3-4a1a-b7f7-cf837605a784.png)

### IMG_5703.JPG:(原圖:31顆圍棋，偵測:30顆圍棋)
![image](https://user-images.githubusercontent.com/82385589/171550726-8122ca22-8249-4d43-9372-b8e9bab07fe6.png)
![image](https://user-images.githubusercontent.com/82385589/171550765-e337e9da-85e8-4f9c-97ba-3c23b4873286.png)

### IMG_5704.JPG:(原圖:31顆圍棋，偵測:31顆圍棋)
![image](https://user-images.githubusercontent.com/82385589/171550829-b2cb4f49-9dc1-46ae-a405-3e61df4d44aa.png)
![image](https://user-images.githubusercontent.com/82385589/171550870-fcab9dac-41c4-4fb6-9373-bc93ac48cc51.png)

## 參考資料:
* https://shengyu7697.github.io/python-opencv-erode-dilate/
* https://ithelp.ithome.com.tw/articles/10246270
* https://blog.csdn.net/u012566751/article/details/77046445
* https://docs.opencv.org/4.x/d3/de5/tutorial_js_houghcircles.html
* https://blog.csdn.net/zangle260/article/details/52980876
