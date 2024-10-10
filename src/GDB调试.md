要逐行调试 C++ 程序，通常需要使用一个调试工具。**GDB**（GNU Debugger）是一个常用的调试工具，支持在终端中逐行调试你的 C++ 程序。下面是使用 GDB 进行逐行调试的步骤。

### 1. **确保程序以调试模式编译**

在使用 GDB 调试之前，你需要确保你的程序以调试模式编译，这样编译器会生成额外的调试信息。为此，使用 `-g` 选项编译你的程序：

```bash
g++ -g -o dead_lock dead_lock.cpp -pthread
```

- `-g`：生成调试信息，这样 GDB 能够识别你的代码。
- `-o dead_lock`：生成可执行文件 `dead_lock`。

### 2. **启动 GDB**

编译完成后，使用以下命令启动 GDB：

```bash
gdb ./dead_lock
```

这会启动 GDB 并加载你的可执行文件 `dead_lock`。

### 3. **设置断点**

为了逐行调试，你可以在某些地方设置断点。一个断点可以让程序在某一行代码暂停运行，这样你可以查看程序的状态。以下是设置断点的方式：

- 在某个行号设置断点，例如在 `dead_lock.cpp` 的第 10 行：
  
  ```bash
  break dead_lock.cpp:10
  ```

- 在某个函数入口处设置断点，例如在 `transfer` 函数入口处设置断点：
  
  ```bash
  break transfer
  ```

### 4. **运行程序**

设置完断点后，输入 `run` 命令来运行程序，GDB 会在遇到断点时暂停程序的执行：

```bash
run
```

程序会从头开始执行，直到遇到第一个断点为止。

### 5. **逐行调试**

在程序暂停后，你可以逐行执行代码，并查看变量的值。以下是一些常用的命令：

- **`step` (简写 `s`)**：逐行执行代码，进入函数调用内部。
  
  ```bash
  step
  ```

- **`next` (简写 `n`)**：逐行执行代码，但不会进入函数内部，它会直接执行完函数。

  ```bash
  next
  ```

- **`continue` (简写 `c`)**：继续执行程序，直到遇到下一个断点。

  ```bash
  continue
  ```

- **`print`**：查看变量的值。比如要查看 `lhs.balance` 的值：

  ```bash
  print lhs.balance
  ```

- **`list`**：查看源代码的上下文。如果你想查看程序当前行的上下文，可以使用 `list` 命令。

  ```bash
  list
  ```

### 6. **查看变量和栈信息**

调试时，你可以查看当前变量的值和函数调用栈的信息：

- **查看当前函数调用栈**：
  
  ```bash
  backtrace
  ```

  这会显示函数调用的栈信息，包括当前函数和调用它的函数，方便查看程序的执行路径。

- **查看局部变量**：

  使用 `info locals` 命令可以查看当前函数的局部变量及其值。

  ```bash
  info locals
  ```

### 7. **结束调试**

- 在任何时候，你都可以通过输入 `quit` 退出 GDB 调试器：

  ```bash
  quit
  ```

### 示例：调试过程

假设你的 `dead_lock.cpp` 文件包含如下代码，并且你想要逐行调试 `transfer` 函数。

```cpp
#include <iostream>
#include <thread>
#include <mutex>

class Account {
public:
    int balance;
    std::mutex m;

    Account(int balance_) : balance(balance_) {}
};

void transfer(Account& lhs, Account& rhs, int amount) {
    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> lock_lhs(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_rhs(rhs.m, std::adopt_lock);

    if (lhs.balance >= amount) {
        lhs.balance -= amount;
        rhs.balance += amount;
        std::cout << "Transferred " << amount << std::endl;
    } else {
        std::cout << "Insufficient funds" << std::endl;
    }
}

int main() {
    Account accountA(100);
    Account accountB(50);

    std::thread t1(transfer, std::ref(accountA), std::ref(accountB), 10);
    std::thread t2(transfer, std::ref(accountB), std::ref(accountA), 20);

    t1.join();
    t2.join();

    std::cout << "Final balance A: " << accountA.balance << std::endl;
    std::cout << "Final balance B: " << accountB.balance << std::endl;

    return 0;
}
```

#### 逐行调试步骤：

1. **编译代码**：

   ```bash
   g++ -g -o dead_lock dead_lock.cpp -pthread
   ```

2. **启动 GDB**：

   ```bash
   gdb ./dead_lock
   ```

3. **在 `transfer` 函数中设置断点**：

   ```bash
   break transfer
   ```

4. **运行程序**：

   ```bash
   run
   ```

5. **逐行调试**：

   - 当 GDB 停止在 `transfer` 函数的断点处后，使用 `step` 或 `next` 来逐行执行代码。
   - 使用 `print` 来查看变量的值，例如查看 `lhs.balance` 和 `rhs.balance`。

6. **继续执行程序**：

   - 使用 `continue` 继续执行程序，直到程序结束或遇到下一个断点。

7. **退出调试**：

   当调试完成后，使用 `quit` 命令退出 GDB。

### 8. **总结**

- 使用 `g++ -g` 编译程序以生成调试信息。
- 使用 `gdb` 进行逐行调试，设置断点，使用 `step` 和 `next` 逐步执行代码。
- 使用 `print` 命令查看变量的值，并使用 `continue` 命令继续执行程序。

这样，你可以在终端中逐行调试程序，深入分析代码执行的细节，查看变量值并解决潜在问题。