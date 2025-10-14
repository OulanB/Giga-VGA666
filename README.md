Test of the LTDC part on the Arduino Giga with a passive VGA adapter
(SMT32H747 part with 8M SDRAM 16 bits, plus Usb host for keyboard input)

As the Giga Display is not very usefull (as a 480x800 display rotated 90°),
I started experiment on an external VGA display 

<img width="1280" height="647" alt="01" src="https://github.com/user-attachments/assets/d666bf81-4450-4e7a-a1fa-a87149b893cf" />

v0: 
- proof of concept is ok: 8 colors display at 800x600 with some resistors and cables
<img width="512" height="405" alt="03" src="https://github.com/user-attachments/assets/22bfc1e5-be17-4d43-ad45-be72c611c939" />
<img width="512" height="410" alt="04" src="https://github.com/user-attachments/assets/152a5c0a-d6fe-4c61-a26f-4dc147cb8410" />

- RGB565 mode and L8 mode tested (L8 used in an hp9816 emulator)
<img width="512" height="415" alt="02" src="https://github.com/user-attachments/assets/df4a6311-e9fe-456d-a190-879b7c1d420f" />

next:
- creating an add-on board (see wiki), similar to raspberrypi vga 666
- and there are enought IO on the connector to add if needed 2 DIN 6 connectors for a keyboard and a mouse in PS/2 ...

Feel free to use/modify all of these.
