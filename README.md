HeimdallGI
==========

HeimdallGI is a simple, easy-to-use web MVC framework written in C++ using the Qt5 library.

Requirements
============
Qt >= 5.0.2 http://qt-project.org/


Compiling
=========

1.  ```~:> git clone https://bolvarak@bitbucket.org/bolvarak/heimdallgi.git && cd HeimdallGI```, just for all you beginners.
2.  ```~:> nano Application.ini``` or vi, your choice, but you should change ```basePath``` and ```templatePath``` under ```Paths``` before you continue or your views will not process and no content will display.
3.  ```~:> qmake HeimdallGI.pro```
4.  ```~:> make```
5.  ```~:> ./Application.hgi``` or move the binary under your cgi-bin or designated directory with ExecCGI in Apache.
6.  Add the following .htaccess file for full effect:  https://github.com/bolvarak/Framsie/blob/master/public/.htaccess.

