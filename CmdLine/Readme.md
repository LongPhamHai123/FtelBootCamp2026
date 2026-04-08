# Command Line Parser – Table Pattern

## 1. Overview

Project này implement một **Command Line Interface (CLI)** đơn giản trong C theo **Table Pattern**.

### a. Table Pattern là gì?

**Table Pattern** là cách thiết kế trong đó:

- Các command được lưu trong một **bảng (table)**
- Mỗi command sẽ map tới một **function handler**

#### Structure

```c
typedef struct
{
    const int8_t *cmd;
    pf_cmd_func func;
    const int8_t *info;
} cmd_line_t;
```

Ví dụ:

```c
cmd_line_t cmd_table[] = {
    {(int8_t *)"help", cmd_help, (int8_t *)"Show help"},
    {(int8_t *)"led", cmd_led, (int8_t *)"Control LED"},
    {0, 0, 0}};
```

#### Cách hoạt động

1. Nhận input (ví dụ: `"led on"`)
2. Tách command (`"led"`)
3. So sánh với table
4. Gọi handler tương ứng


#### Các test case

| Test case                      | Cách thực hiện | Kết quả thực tế |
| ------------------------------ | -------------- | --------------- |
| Command hợp lệ (`help`)        | B1             | C1              |
| Command có argument (`led on`) | B2             | C2              |
| Command không tồn tại (`abc`)  | B3             | C3              |
| Command quá dài                | B1             | C1              |
| Table NULL                     | B2             | C2              |

#### Build & Run


- **Chạy demo main (thủ công)**

  ```bash
  gcc cmd_line.c main.c -o main
  main
  ```

<!-- > Lưu ý: Nhớ cài đặt MSYS2 sử dụng gcc/g++ để build & debug trên VSCode -->

### c. Demo input/output

#### Input

```text
help
led on
abc
```

#### Output

```text
CommandLineInterface (type 'exit' to quit)
> help
Available commands:
help: Show help
led: Control LED
> led on
LED command with arg: on
> hihi
Command not found
> exit
```