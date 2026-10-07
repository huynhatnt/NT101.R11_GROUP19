\# Lab 01: Mật mã học cổ điển (Classical Cryptography)



\##1. Mục tiêu

\- Làm quen với các khái niệm và kỹ thuật của hệ mật mã cổ điển (mật mã thay thế, hoán vị).

\- Trực tiếp cài đặt các chương trình mã hóa và giải mã.

\- Hiểu và lập trình được các công cụ thám mã (phá mã) cơ bản bằng phương pháp thống kê và thuật toán tối ưu.



\## 2. Nội dung chính

Thư mục này chứa mã nguồn C++ giải quyết các nhiệm vụ trong Lab 01:

\- Task 2.1: Mã hóa, giải mã và brute-force Caesar Cipher.

\- \*\*Task 2.2 \& 2.3:\*\* Phân tích tần suất thủ công và lập trình tool tự động giải mã Mono-alphabetic Substitution Cipher (sử dụng Hill-Climbing).

\- \*\*Task 2.4:\*\* Mã hóa và giải mã Playfair Cipher xử lý ma trận 5x5.

\- \*\*Task 2.5 \& 2.6:\*\* Mã hóa, giải mã và phá mã tự động Vigenère Cipher.

\- \*\*Task 2.7 (Mở rộng):\*\* Lập trình mã hóa/giải mã thuật toán.



\## 3. Hướng dẫn chạy chương trình

\- \*\*Môi trường:\*\* Mã nguồn được viết bằng C++ và biên dịch tốt nhất trên Visual Studio.

\- \*\*Cách chạy:\*\*

&#x20; 1. Mở file mã nguồn (`.cpp`) tương ứng với từng Task.

&#x20; 2. Đối với các Task có đọc dữ liệu (như Task 2.3, 2.6), cần đảm bảo các file text như `english\_quadgrams.txt` hoặc `ciphertext.txt` được đặt cùng cấp thư mục với file mã nguồn. Và nên để chế độ build \*\*Release\*\* để có tốc độ tối đa.



