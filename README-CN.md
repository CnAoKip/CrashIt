# CrashIt
Cak-Elib的第一个成员CrashIt——Ring3级系统蓝屏死机测试程序。


蒟蒻的笔者花了6个多月编了这个applet，测试您计算机的蓝屏效率（雾）

CrashIt 是一款可以让你的Windows系统蓝屏崩溃的软件。目前只有32位命令行、英文版本（英语这么差的蒟蒻，别说中国人了，外国人也看不懂）

我们可以保证，使用CrashIt 除了需要重启，对您的计算机不会有任何损害。此软件安全无毒。

## 命令行：

	CrashIt.exe [crash][checkcode][sysbug] code

		其中code是一个16进制的整数。

## 操作：

		'crash'：直接让CrashIt跑出bug并产生蓝屏。代码可以为下：

		```Shell
			0x01 Stack Overflow（栈溢出，俗称爆栈）
			0x02 Access Violation（非法访问）
			0x03 Buffer Overflow（缓冲区溢出，没错就是一种臭名昭著的攻击手段）
			0x04 Access Denied（拒绝访问）
			0x05 Invalid Handle（无效句柄）
			0x06 Integer Divided by Zero（整数除零）

		'checkcode'：指定蓝屏代码（爽！）但有局限性；代码必须在0xC0000000与0xCFFFFFFF之间。


		'sysbug': 内核bug。Code:

		```Shell
			0x01 Invalid Kernel Handle（无效内核句柄，只在Windows 2000/XP/Server 2003上起作用）
			0x02 Critical Object Termination（关键进程终止，需要管理员权限。Windows 8.1后，这些进程都受系统保护，故会失败）
			0x03 Critical Exit（CrashIt会自己设为关键进程并退出。目前只要有管理员权限都有效。）
