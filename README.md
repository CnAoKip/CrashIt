# CrashIt
[中文](README-CN.md)

The first project of Cak-Elib: CrashIt Ring3 BSOD Testing Program.


I wrote a applet for 6 months, for testing your computer's BSOD efficiency (not)

CrashIt is a program that makes your Windows system crash. There has 32-bit command only and it's English (but Chinglish, you know)

It can't doing everything except you will restart the PC sometimes. It's safe.

## SYNOPSIS:

	CrashIt.exe [crash][checkcode][sysbug] code

		code is a hexadecimal integer。

## ARGUMENTS:

		'crash': Execute the program by using a loophole. It can be this:

		```Shell
			0x01 Stack Overflow
			0x02 Access Violation
			0x03 Buffer Overflow
			0x04 Access Denied
			0x05 Invalid Handle
			0x06 Integer Divided by Zero

		'checkcode': Custom BSOD code between 0xC0000000 to 0xCFFFFFFF.


		'sysbug': Loophole in kernel It can be this:

		```Shell
			0x01 Invalid Kernel Handle (Only for Windows 2000/XP/Server 2003)
			0x02 Critical Object Termination (Need Permission, after Windows 8.1, It's no effective)
			0x03 Critical Exit（CrashIt will set itself very "Critical" then exit itself, Need Permission.）
