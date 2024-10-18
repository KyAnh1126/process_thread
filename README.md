# process_thread

1. process.cpp
- đưa ra ví dụ về fork(), tạo một tiến trình con từ tiến trình gọi fork() (tiến trình cha)
- các tiến trình có các bộ nhớ khác nhau (ngoại trừ text section), ở đây là biến cục bộ test
- tiến trình cha có process id được cấp bởi hệ điều hành, tiến trình con luôn có process id = 0
- các tiến trình được lập lịch bởi kernel, nên thứ tự thực thi lệnh có thể khác nhau mỗi lần chạy chương trình
- wait(NULL) được gọi ở hàm cha để đợi tiến trình con thực thi xong mới kết thúc chương trình

2. thread.cpp
- file chỉ ra ví dụ về lập trình multi-thread, một tiến trình được chia thành nhiều luồng, thực thi một nhiệm vụ riêng
- các luồng có chung một bộ nhớ (ở đây là mảng array, threads, data và pthread_sum)
- các luồng được chia ra để tính tổng một phần của mảng
- đoạn cuối sẽ so sánh tổng được tính bởi multi-thread so với single-thread
