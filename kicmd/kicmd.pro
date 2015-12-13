QT       += core
QT       -= gui

#模板类型
win32 {
TEMPLATE = vclib
}
unix
{
TEMPLATE = lib
}

#语言
LANGUAGE = C++

#源文件编码方式
CODECFORSRC = UTF-8

#指定rcc命令、moc命令、obj文件存放的目录
RCC_DIR += ./tmp
MOC_DIR += ./tmp
OBJECTS_DIR += ./tmp

#关于应用程序的配置信息
CONFIG += debug release warn_on qt	#qt是默认
release {
TARGET = bin/kicmd	#生成的目标名
OBJECTS_DIR = ./	#指定目标文件(obj)的存放目录
}
debug {
TARGET = debug/kicmd
OBJECTS_DIR = ./
}

#头文件包含路径
INCLUDEPATH += ./ ./tmp

#程序编译时依赖的相关路径
DEPENDPATH += include qrc sources

#工程中包含的资源文件
RESOURCES = kicmd.qrc

#引入的lib文件,用于引入动态链接库
LIBS += -L ./lib  					#-L：引入路径
LIBS += 
Release:LIBS += -L ./lib 		#release版引入的lib文件路径
Debug:LIBS += -L ./lib 			#Debug版引入的lib文件路径

#编译选项
DEFINES += DEBUG

SOURCES += $$files(*.cpp)
SOURCES += dir.cpp
HEADERS += dir.h
HEADERS += stable.h