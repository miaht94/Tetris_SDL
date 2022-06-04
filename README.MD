# Tetris SDL 2
*Project game giữa kỳ môn Lập Trình Nâng Cao INT 2215_22 K64-UET-VNU*\
\
<img src="https://github.com/miaht94/Tetris_SDL/blob/master/tetris_image.png?raw=true"/>
## Plugins
*Thư viện SDL 2 bao gồm:*
* [SDL2 ](https://www.libsdl.org/download-2.0.php)
* [SDL2_Image ](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_Ttf](https://www.libsdl.org/projects/SDL_ttf/) 
* [SDL2_Mixer](https://www.libsdl.org/projects/SDL_mixer/)
## How to build
*Làm theo những hướng dẫn sau để setup thư viện vào Visual studio code :*
* [SDL2 ](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
* [SDL2_Image](http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php) 
* SDL2_Mixer , SDL_Ttf cài đặt tương tự như SDL2_Image.
## Materials
* Tất cả Assets được lấy từ [tetris.com](https://tetris.com/sanrio).
* Ý tưởng về effect trong game cũng được lấy từ [tetris.com](https://tetris.com/sanrio).
## How to play
Rule :
* Các khối gach được sinh ra ngẫu nhiên và rơi xuống 1 hàng mỗi 1s (thời gian tuỳ theo độ khó của game).
* Luật chơi khá đơn giản và quen thuộc lấp đầy các hàng để clear hàng đó và kiếm điểm.
* Với mỗi hàng clear sẽ được 100 điểm.
* Game kết thúc khi có 1 viên gạch chạm nóc.

Điều khiển :
* Dùng các phím mũi tên sang trái sang phải để điều khiển khối gạch sang trái sang phải
* Dùng phím mũi tên lên trên để xoay khối gạch
* Dùng phím mũi tên xuống dưới để viên gạch rơi xuống nhanh hơn
* Khi gạch rơi xuống vị trí tối đa bạn vẫn có thể điều chỉnh sang trái phải hoặc xoay (nếu có vị trí trống có thể chèn vào) trong 1 khoảng thời gian ngắn
* Dùng phím Space để viên gạch rơi xuống ngay lập tức

