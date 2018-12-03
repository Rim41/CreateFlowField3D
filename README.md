# “三维矢量场生成程序” 开发文档

`时间：2018年12月3日` `版本：V2.1`

## 0 引言

本程序是北京理工大学计算机学院下属可视化与医学成像课题组的研究成果。

课题组主页：http://iitlab.bit.edu.cn/mcislab/~zhangwenyao/index.htm

如有疑问，请联系张文耀老师（zhwenyao@bit.edu.cn）。

## 1 概述

本程序实现了三维空间中的电荷放置与调整。给定空间范围，可以在程序中看到网格，并在网格空间中任意放置正负电荷。放置完成后，可以通过界面控制输出数据文件。

本程序基于微软基础类库（MFC, Microsoft Foundation Classes)和 OpenGL，使用 Visual Studio 2015 开发，在本页面可以下载得到本程序的 Debug/Release 版本。使用下载得到的文件，并按照本文档操作指引，可以在本地搭建开发环境。



## 2 下载

### 2.1 直接下载

可以在[这里](https://github.com/Rim41/CreateFlowField3D/archive/master.zip)下载得到源代码的压缩文件。

### 2.2 使用 Git 下载

如果在 Windows 下已经安装了 Git，那么打开 Git Bash 或 Git CMD，跳转到合适的目录后输入：

`git clone https://github.com/Rim41/CreateFlowField3D.git`

稍等片刻，即可在这个目录下克隆得到源文件。



## 3 环境配置

本程序是 64 位程序，涉及 64 位程序下 OpenGL 环境的搭建。开发过程中所需的 OpenGL 相关的库文件，存放在步骤 2 中下载得到的`Lib`文件夹中。

本程序开发基于 Visual Studio 2015，不同的 IDE 版本开发存在部分差异。此处以 VS2015 为例。

### 3.1 在 Visual Studio 2015 中配置 64 位 OpenGL 开发环境

#### 3.1.1 找到安装位置

首先找到 Visual Studio 2015 的安装目录。

![1.png](https://github.com/Rim41/CreateFlowField3D/Figure/1.png)

#### 3.1.2 配置库

1. 64 位 OpenGL 程序的库目录，在`~\Microsoft Visual Studio 14.0\VC\lib\amd64`（目录1）

2. 将`~\Lib\glew-2.1.0\lib\Release\x64`下的两个文件放入目录1
3. 将`~\Library\glut-3.7.6-bin-32and64\glut-3.7.6-bin`下的`glut64.lib`放入目录1

#### 3.1.3 配置头文件

1. 打开`~\Microsoft Visual Studio14.0\VC\include`，新建文件夹，命名为“GL”，进入该文件夹（目录2）
2. 将`~\Library\glew-2.1.0\include\GL`下的四个文件放入目录2
3. 将`~\Library\glut-3.7.6-bin-32and64\glut-3.7.6-bin`下的`glut.h`放入目录2

#### 3.1.4 配置链接库

1. 进入`C:\Windows\System32`（目录3）
2. 将`~\Library\glew-2.1.0\bin\Release\x64`下的`glew32.dll`文件放到目录3中
3. 将`~\Library\glut-3.7.6-bin-32and64\glut-3.7.6-bin`下的两个文件放到目录3中

#### 3.1.5 确认stdafx.h

64 位的 OpenGL 程序需要如下头文件，请确保头文件`stdafx.h`按如下顺序引用 OpenGL 库。

```c++
#include <GL/glew.h>  
#include <GL/glut.h>  
#pragma comment(lib,"opengl32.lib")  
#pragma comment(lib,"glu32.lib")  
#pragma comment(lib,"glew32.lib")  
#pragma comment( lib, "glut64.lib" )  
```

### 3.2 其他版本的 64 位 OpenGL 环境配置

参考 3.1 节，打开项目后，在项目->属性->VC++目录中查看库目录、包含目录的位置，并且把 32 位的 DLL 文件放到`C:\Windows\SysWOW64`，把 64 位的 DLL 文件放到`C:\Windows\System32`即可（注意，32 位的放到“64”，64 位的放到“32”）。











