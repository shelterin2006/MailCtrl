#include <iostream>
#include <vector>
#include <string>
#include <windows.h>    // Cần cho các API của Windows
#include <tlhelp32.h>   // Cần cho Tool Help API (CreateToolhelp32Snapshot, Process32First, Process32Next)
#include <iomanip>      // Để định dạng output

int main() {
    std::cout << "Danh sach cac tien trinh dang chay:" << std::endl;
    std::cout << std::setw(10) << "PID" << " | " << "Ten Tien Trinh" << std::endl;
    std::cout << "-----------|----------------------------------------" << std::endl;

    // Buoc 1: Tao mot snapshot cua tat ca cac tien trinh dang chay
    // TH32CS_SNAPPROCESS: Bao gom tat ca cac tien trinh
    // 0: Tham so thu hai khong su dung cho tien trinh
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // Khai bao su dung kieu PROCESSENTRY32W
    PROCESSENTRY32W pe32;
    // Thiet lap kich thuoc cho PROCESSENTRY32W - DONG NAY RAT QUAN TRONG VA PHAI O DAY
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    // Goi Process32FirstW
    if (!Process32FirstW(hSnapshot, &pe32)) {
        // ... Phan xu ly loi Process32FirstW that bai ...
        // Khi dwSize sai, loi o day thuong la ma loi 0
        std::cerr << "Loi khi lay thong tin tien trinh dau tien. Ma loi: " << GetLastError() << std::endl;
        CloseHandle(hSnapshot);
        return 1;
    }

    // Buoc 3: Lay thong tin cua tien trinh dau tien trong snapshot
    // Su dung Process32FirstW cho Unicode (khuyen khich tren Windows hien dai)
    if (!Process32FirstW(hSnapshot, &pe32)) {
        std::cerr << "Loi khi lay thong tin tien trinh dau tien. Ma loi: " << GetLastError() << std::endl;
        CloseHandle(hSnapshot); // Dong handle truoc khi thoat
        return 1;
    }

    // Buoc 4: Duyet qua cac tien trinh trong snapshot
    do {
        // pe32.th32ProcessID: PID cua tien trinh
        // pe32.szExeFile: Ten file thuc thi cua tien trinh (WCHAR string)

        // In PID va ten tien trinh
        // Su dung std::wcout cho WCHAR string
        std::wcout << std::setw(10) << pe32.th32ProcessID << " | " << pe32.szExeFile << std::endl;

    } while (Process32NextW(hSnapshot, &pe32)); // Lay thong tin tien trinh tiep theo

    // Buoc 5: Dong handle cua snapshot sau khi su dung xong
    CloseHandle(hSnapshot);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Hoan thanh liet ke tien trinh." << std::endl;

    return 0; // Thanh cong
}