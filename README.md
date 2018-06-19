Can Your Seafood
=================
TODO
----
1. 把master pull下來，之後我會把allegro library從github上拿掉，一般來說這東東是不會上github的
1. 把codeblock設定好(linker, search dir)，或者你也可以直接用我丟上去的，不過之後.cbp專案檔也會拿掉
1. 之後要做任何更新(例如說把哪個Interface刻完)，請開一個新的branch，實做完沒有bug的時候再建立pull request
1. 大家加油RRRR
> 那些即將被拿掉的東西我會寫在`.gitignore`裡面，意思就是他不會被同步到github上

大架構
------
大架構很粗糙。目前實做完執行的模樣：點一下中間進入下一個Interface。依序為Opening -> Naming -> Gaming -> Ending。
每個Interface都還沒完成，每個Interface除了**美工**之外還差的東西如下：
- Opening：做個可愛的開頭
- Naming：跪求 @ricky 的Allegro鍵盤輸入文字的程式碼
- Gaming：選單和跟寵物互動
- Ending：開頭動畫

理論上我們應該還要一個Opening2，就是瘟腥的開頭動畫，不過那個我覺得看最後有沒有時間再說。

程式架構
--------
### 輸出debug訊息
除了各位已經熟知的cout跟printf之外，我多定義了一個巨集`dbg`，用法跟cout相同：
```c++
dbg << "My debug Message" << endl;
```
差別在他會連同這行debug訊息是從哪個檔案的哪一行冒出來的一併跟你講

### 每個物件怎麼運作
1. 從`run()`函式開始看，在讓一個物件(如Interface或是gameControl)執行統一都從`run()`函式開始。
1. `draw()`負責畫圖

### 有限狀態機
> 狀態都定意在`global.h`裡面的`enmu Stat`裡面
#### gameControl
他的狀態就是`STAT_XXX`那些，基本上就是一個stat結束跳下一個，跳到`STAT_EXIT`就把畫面卡掉。
#### Interface
每個Interface的運行建議也用有限狀態機實做，個人覺得這樣比較好維護。
`run()`這個Interface的主要執行函式，包括呼叫`process()`(event處理)跟`draw()`，
並且`run()`會回傳這個Interface的執行狀況，會傳的值有目前有三個(可以依照需求自行增加，定義在global.h的`Stat`裡面)
- INTER_DONE：這個Interface跑完了，該進入下個Interface了
- INTER_CONTINUE：這個Interface還沒跑完，等等繼續
- INTER_EXIT：終止遊戲，例如按叉叉
#### gameControl跟Interface的溝通
> 參見gameControl.cpp的`gameControl::run()`跟`gameControl::game_run()`
- `gameControl::run()`：整個遊戲的有限狀態機
- `gameControl::game_run()`：執行這個stat該運作的Interface(呼叫這個Interface的`run()`)，並且根據`Interface::run()`的回傳值決定下一個stat是誰


程式碼們
--------
### main.cpp
不解釋
### font.h
因為字型會被很多東西共用到，所以把字型獨立一個class。
### global.h
各種函識庫，還有自定義的巨集、enmu
### gameControl.h/.cpp
維護遊戲運作的有現狀態機
### Interface.h/.cpp
每個遊戲畫面都從Interface繼承出去，包括Opening, Naming, Gaming, Ending。
Interface裡面有一個`vector<Object*> vis_objs`，任何從Object繼承出來的需要在螢幕上顯示的都可以丟進去裡面，會由`Interface::draw()`統以畫出來。
### Circle.h/.cpp
跟mini2的差不多
### Button.h/.cpp
裡面的`ButtonRD`表示一個圓形按鈕
