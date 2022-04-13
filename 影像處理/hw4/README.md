## 作業說明:
* 計算輸入圖的離散傅立葉轉換結果，並將頻譜大小與相位角度各以灰階256色圖像方式呈現出。
* 對圖像利用Gaussian Low-Pass filter處理，輸出平滑後圖像。
* 程式利用課本的frequency filter步驟者可得滿分，在網頁中將每個步驟結果呈現出。直接套用opencv函數得一半分數。
 
## 使用環境/語言:
 * Windows10
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 實作方法: 
 1. 輸入圖片路徑後，會檢查**是否可讀取到圖片內容**，若不行，則重新輸入圖片路徑。
 2. 輸入欲旋轉的角度。
 3. 會輸出**三種圖**:**原圖、整張圖像旋轉的圖、中心內切圓區域旋轉的圖**
 4. **整張圖像旋轉的圖**: 利用 **getRotationMatrix2D 求出旋轉矩陣** ， 再**利用 warpAffine 將圖片旋轉**。
 5. **中心內切圓區域旋轉的圖**: 利用**每個點座標與圓心之間的距離**，判斷是否屬於圓。**將所有屬於圓的點座標做成一張圖(a)**，**不屬於圓的點座標做成另外一張圖(b)**。
                              然後**圓形圖會根據輸入的角度作旋轉(c)**。旋轉完後，再**將(b)圖與(c)圖合併**。
 7. 印完圖像後，可讓使用者選擇**是否要繼續輸入旋轉角度，觀察同張圖片不同旋轉角度的效果**，若輸入^z，則回到**第二點的流程**。
 8. **第一點的流程**輸入0，則終止程式。

## 執行方式/畫面:

 * **原圖:**
        ![image](https://user-images.githubusercontent.com/82385589/155843112-12511b61-f6d2-4447-91d1-9269b9adcbd0.png)
 * **整張圖像旋轉的圖:**
        ![image](https://user-images.githubusercontent.com/82385589/155843124-fac961c0-21bc-4352-b911-f581afb4ab22.png)
 * **中心內切圓區域旋轉的圖:**
        ![image](https://user-images.githubusercontent.com/82385589/155843141-0c8a3584-cb9b-440d-8a00-19d2bf8e13b1.png)

## 參考資料:
* https://blog.csdn.net/cyf15238622067/article/details/87918125
* https://blog.csdn.net/yuandm819/article/details/79897868
* https://blog.csdn.net/jerwey/article/details/103991174
* https://www.twblogs.net/a/5c761cffbd9eee31cea509be
* https://www.twblogs.net/a/5b820dc82b71772165af693c
* https://iter01.com/541551.html
