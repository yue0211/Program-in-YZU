## 作業說明:
請撰寫一個程式，利用數學型態學影像處理運算(erode(), dilate()等函式)，計算出所附圖像(共三張)每張圖像中圍棋個數。
## 使用環境/語言:
 * Windows10
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 實作方法:
1. 輸入圖片路徑後，會檢查**是否可讀取到圖片內容**，若不行，則重新輸入圖片路徑。
2. 由於 **erode()及dilate()**，只能用於**經過二值化運算的灰階圖片**。因此**先將圖片轉成灰階圖**，並**利用threshold對圖片進行二值化運算**。
3. 


## 執行方式/畫面:

     
## 參考資料:
* https://shengyu7697.github.io/python-opencv-erode-dilate/
* https://ithelp.ithome.com.tw/articles/10246270
* https://blog.csdn.net/u012566751/article/details/77046445
* https://docs.opencv.org/4.x/d3/de5/tutorial_js_houghcircles.html
* https://blog.csdn.net/zangle260/article/details/52980876
