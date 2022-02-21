## 作業說明:
 1. 撰寫一個程式讀取 1 張圖片，將圖像中每一個點像素的值各加上一個數值。
 2. 如果輸入圖像是灰階圖像，改變每個像素的灰階值。
 3. 如果輸入圖像是全彩圖像(RGB)，則只改變每個像素的 R 值。
 4. 修改後的像素值仍然要介於 0 ~ 255 (注意!!數值不要溢位)
 
## 使用環境/語言:
 * Windows10
 * Visual Studio 2019
 * Opencv-4.3.0
 * C++
 
## 特殊程式片段註解/實作方法:
 
## 執行方式/畫面:

 * **輸入灰階圖:**
     * **將每個像素的灰階值，加上100(像素變成255會變全白)。**
        ![image](https://user-images.githubusercontent.com/82385589/154868450-9a432518-131e-4b95-a6c4-b89f27bf0c90.png)
     * **將每個像素的灰階值，減掉100(像素變成0會變全黑)。**
        ![image](https://user-images.githubusercontent.com/82385589/154872194-def38bcd-3c89-4c5e-b22a-2368513277aa.png)
 * **輸入全彩圖:**
     * **將每個像素的R值，變成 255。(輸入255)**
        ![image](https://user-images.githubusercontent.com/82385589/154866699-4a97216a-c73b-4048-a559-81d8097553ec.png)
     * **將每個像素的R值，變成 0。(輸入-255)**
        ![image](https://user-images.githubusercontent.com/82385589/154866886-54f1cccd-bd89-41e9-953a-f7c65f03baa2.png)

       
## 參考資料:
 * https://answers.opencv.org/question/36288/how-to-know-grayscale-or-color-img-loaded/
 * https://openweather.blogspot.com/2019/09/opencv-clonecopyto-opencvclonecopyto.html
 * https://cloud.tencent.com/developer/article/1470529
 * http://yzucs362.blogspot.com
