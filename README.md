# ***Shinchan Adventure***
## **Introduction**
+ Họ và tên: Nguyễn Văn Khoa - K68N - UET

+ Mã sinh viên: 23020616

+ Bài tập lớn: Shinchan Adventure (2324II_INT2215_21 - Lập trình nâng cao) 
## **Description** 

### *Game description and instruction* 
- Shinchan Adventure là một tựa game hành động phiêu lưu được lấy cảm hứng từ game [Crayon Shinchan Phiêu Lưu (Cậu Bé Bút Chì)](https://gamevui.vn/crayon-shinchan-phieu-luu/game) trên trang game tuổi thơ [GameVui](gamevui.vn) nhằm mang lại cho người chơi những phút giây vui vẻ và những ký ức đáng nhớ về tuổi thơ, game này hứa hẹn đem lại những trải nghiệm tuyệt vời cho cả người hâm mộ lâu năm và những người mới biết đến cậu bé nghịch ngợm Shin-chan từ bộ truyện tranh và phim hoạt hình nổi tiếng "Crayon Shin-chan" của Nhật Bản.
- Game được thiết kế với đồ họa tươi sáng, sống động, giữ nguyên phong cách nghệ thuật đặc trưng của bộ truyện tranh gốc. Người chơi sẽ cảm thấy như mình đang bước vào thế giới đầy màu sắc của Shin-chan.
- Âm nhạc và hiệu ứng âm thanh trong game vui nhộn, gợi nhớ đến những giai điệu quen thuộc trong bộ phim hoạt hình, giúp tăng thêm phần hứng khởi và sống động cho người chơi.
- Shinchan Adventure đòi hỏi người chơi phải kết hợp giữa các nút điều khiển để né tránh chướng ngại vật, thu thập vật phẩm cho đến chiến đấu với các quái vật zombie.

### *Control* 

| Control | Mode 1   | Mode 2   | 
|---------|----------|----------|
| JUMP    |     ↑    |     w    |
| ATTACK  |     ↓    |     s    |
| LEFT    |     ←    |     a    |
| RIGHT   |     →    |     d    | 

### *Preview*
![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/menu_demo.png)
![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/instruction_demo.png)
![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/game_demo.png)

## **Setup**
- *Yêu cầu: sử dụng IDE CLion (mình đang dùng Version CLion 2023.1.5) và máy tính phải được cài đặt sẵn các thư viện SDL, SDL_image, SDL_mixer, SDL_ttf* 
  1. Khởi động Clion đặt tên và tạo project mới.
  2. Vào mục Terminal ở phía dưới chương trình và gõ lệnh:
   ```
     git clone https://github.com/NguyenKhoa311/Shin-Adventure
   ```
  3. Vào thư mục Shin-Adventure vừa clone về máy và chọn file CmakeLists.txt:
     
    ![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/step1.png)
  
    Copy nội dung từ file này và paste vào file CmakeLists.txt của project mới tạo:
  
    ![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/step2.png)
    ![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/step3.png)

    Sửa lại tên project thành tên project mới tạo tại các dòng project, add_executable, target_link_libraries. Sau đó ấn chọn mũi tên bên cạnh chữ Debug và chọn Edit Configurations...

    ![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/step4.png)

    Thêm vào Working Directory đường dẫn vào thư mục Shin-Adventure tại project mới vừa tạo :

    ![image](https://github.com/NguyenKhoa311/Shin-Adventure/blob/master/image/step5.png)

    Nhấn Ok vậy là bạn đã hoàn thành cài đặt game và có thể ấn Run (hình tam giác) để chạy game.
  
## **See also**  

### *Các kỹ thuật sử dụng*  
- Thư viện SDL2.0
- Sử dụng nhiều class, vector, tách file, ghi đè, ...
- Kĩ thuật tilemap
- Xử lý thời gian, thao tác chuột và bàn phím, âm thanh, hình ảnh, chữ. 
- Tạo menu

### *Nguồn tham khảo* 
- Cách xây dựng cấu trúc game, kĩ thuật Tile Map, tạo Menu game: tham khảo từ kênh youtube [PhátTriểnPhầnMềm123AZ](https://www.youtube.com/c/Ph%C3%A1tTri%E1%BB%83nPh%E1%BA%A7nM%E1%BB%81m123AZ/featured) và github [Snake Game](https://github.com/trongminh03/Snake-Game/blob/main/src/Menu.cpp)
  
- Sử dụng [Chat GPT](https://chatgpt.com/?oai-dm=1) để sửa lỗi, xây dựng 1 số hàm và optimize code.

- Cách sử dụng thư viện SDL2.0: thảo khảo trên trang [StudyPlan.dev](https://www.studyplan.dev/sdl-dev/sdl-setup-mac) và [lazyfoo.net](https://lazyfoo.net/tutorials/SDL/index.php)
  
- Hình ảnh: chụp cắt từ game [Crayon Shinchan Phiêu Lưu (Cậu Bé Bút Chì)](https://gamevui.vn/crayon-shinchan-phieu-luu/game) và tự tìm kiếm trên Google

- Âm thanh: từ các trang free âm thanh trên Google

### *Hướng phát triển*
- Cải thiện thêm menu game bật/tắt âm thanh, pause game.
  
- Thêm tính năng lưu điểm các lượt chơi, điểm cao nhất.
  
- Cập nhật thêm nhiều map chơi.
  

    

  
    
 






