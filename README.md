# c++ 程式作業

題目：
####
1. 可以接收並執行任意不帶參數的指令。舉例：
icheyneh@/home/OS>ls << 使用者輸入ls並按下 Enter
接著你便透過你的shell來建立一個新的ls程序，並將輸出導向標準輸出（於文字介面上輸出）

####
2. 可以接收並任何帶有參數的指令。舉例：
icheyneh@/home/OS>ls -al << 使用者輸入ls 並加上附加參數 "-al" 最後按下 Enter
接著你便透過你的shell來建立一個新的ls程序，執行時給與-al這個參數，並將最終輸出導向標準輸出
####

首先先進入命令提示字元，並且在提示字元的前面加上所在目錄的位置，再來我使用while迴圈，預設進入條件是true，就會一直在裡面，然後使用了getcwd函數來取得所在目錄的位置，再使用getline來讀取使用者所輸入的命令，並存入字串s，再將s內的資料傳到split函式，解析字串，split函式設立了一個for迴圈，迴圈次數是整個命令字元的數目，迴圈用意是將輸入的字串過濾掉空白，存入暫存區temp，再將temp的資料存入v1（s2），最後清除temp內容。
在process函式中，將指令切割為二維型態，argv[0]放置cd,exit,ls等指令，argv[1]放置路徑,-al等指令，因為cd指令不包含在exec（）家族內，因此使用chdir來更改路徑，如果使用者輸入cd，目前的工作目錄將改為v2[1]的內容；如果使用者輸入exit，印出ByeBye，並以正常狀態退出程式。
pid=fork()這一段，Pid是行程辨識元，讓OS Kernel辨識每個Process是Child還是Parent，用fork()產生Child Process，此時pid等於0，再執行execvp函數，agrv[0]表示要啟動的程序名稱，agrv表示啟動程序所帶的參數，若Pid不等於0的時候，就wait等待Process執行結束。

以下為結果：
<br>
![image](https://github.com/veryjimmy/OperatingSystem_hw2/blob/master/ex1.png)