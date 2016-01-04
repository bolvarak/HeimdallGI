HeimdallGI
==========

HeimdallGI is a simple, easy-to-use web MVC framework written in C++ using the Qt5 library.

Requirements
============
Qt >= 5.1
QCA >= 2.0.0

Ubuntu Installation (Requirements)
==================================
```sudo apt-get install qt5-default libqt5sql5 libqt5sql5-mysql libqt5sql5-odbc libqt5sql5-psql libqt5sql5-sqlite libqt5sql5-tds geoip-database-contrib libgeoip-dev``` 

ArchLinux Installation (Requirements)
=====================================
```sudo pacman -S qt5 geoip geoip-database postgresql-libs mariadb-clients```

Compiling
=========
```
	~:>cd /path/to/wherever
	~:>git clone https://bolvarak@bitbucket.org/bolvarak/heimdallgi.git HeimdallGI
	~:>cd HeimdallGI
	~:>cmake . ; make
	~:>./app.hgi
```

Optional
========
For optimal use behind apache, use the .htaccess file here (remember to change index.php to app.hgi):  https://github.com/bolvarak/Framsie/blob/master/public/.htaccess

