# Git-and-GitHub 的用法教學

## 觀念:

    1. git 被創造的目的,是為了能多人編輯同一份專案

    2. Repositories 可被視為一個專案倉庫

    3. 每個 Repositories 內 都可以建立很多 branch,
       每個 branch 可以放很多資料

    4. branch是為了將修改記錄的整體流程分開儲存，讓分開的
       branch不受其他branch的影響，所以在同一個數據庫裡可
       以同時進行多個不同的修改。分開的branch還是可以和其他
       branch合併的。

## 指令教學:

    1.  git clone 網址
        網址的部分: 複製 Repositories 內的Code 的 https,就能將Repositories內的資料載入

    2.  當 Repositories內的資料,有任何更動時,輸入 git status 可觀察資料狀態

    3.  要完整更新github 上連動的資料 ,要按照以下步驟操作:

        (1)
            git add .  => (.代表所有更動過的資料,.可替換成其他更動過資料的資料名稱)

        (2)
            git commit -m "first" => (雙引號內的文字可以隨便打)

        (3)
            git push -u origin main  => 第一次指定完後,之後都能打( git push )
            (-u:把預設的remote設成origin,未來push如果不指定remote,都會推到origin)
            (main 代表branch的名稱)

    4.
        創造branch: git branch branch的名字
    5.
        切換分支: git checkout branch的名稱

    6. Repositories內 要創檔案時,檔案內一定要有東西


