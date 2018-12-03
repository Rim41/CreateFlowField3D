# “三维矢量场生成程序” 开发文档

`时间：2018年11月23日` `版本：V2.0`

## 1 概述

本程序基于微软基础类库（MFC, Microsoft Foundation Classes)和 OpenGL，使用 Visual Studio 2015 开发，在本页面可以下载得到本程序的 Debug/Release 版本。使用下载得到的文件，并按照本文档操作指引，可以在本地搭建开发环境。



## 2 下载

### 2.1 直接下载

可以在[这里](https://github.com/Rim41/CreateFlowField3D/archive/master.zip)下载得到源代码的压缩文件。

### 2.2 使用 Git 下载

如果在 Windows 下已经安装了 Git，那么打开 Git Bash 或 Git CMD，跳转到合适的目录后输入：

`git clone https://github.com/Rim41/CreateFlowField3D.git`

稍等片刻，即可在这个目录下克隆得到源文件。



## 3 环境配置

由于本程序的开发涉及 OpenGL，因此在开发过程中需要 OpenGL 相关的库文件。在 2 中得到的文件寻找`Lib`文件夹，存放了开发所需要的 OpenGL 库文件。参考不同的 IDE 版本进行开发。

### 3.1 在 Visual Studio 2015 中配置 OpenGL 开发环境

#### 3.1.1 配置链接库

打开 Lib 文件夹中的 dll 文件夹，将下面的所有文件复制到`C:\Windows\SysWOW64`

#### 3.1.2 配置头文件

打开 Lib 文件夹中的 include 文件夹，将下面的所有文件（即一个名为 gl 的文件夹）复制到 Visual Studio 2015 的安装目录下，即为`C:\Program Files(x86)\Microsoft Visual Studio 14.0\VC\include` 

**注意：以文件夹为单位移动**

#### 3.1.3 配置库

打开 Lib 文件夹中的 library文件夹，将下面的所有文件复制到`C:\Program Files(x86)\Microsoft Visual Studio 14.0\VC\lib`

### 3.2 在 Visual Studio 2017 中配置 OpenGL 开发环境

在 Visual Studio 2017 中，IDE 的安装目录发生了改动，故配置开发环境的方式也发生了变化，在这里直接从 IDE 界面入手，进行相关配置。同样的 Visual Studio 2015 也可以参考这部分进行配置，在这里不再赘述。

1. 在解决方案资源管理器中，选中当前工程并右键，进入工程的属性页面
2. 配置属性 -> C/C++ -> 常规 -> 附加包含目录，将 2 中得到的 Lib\include 文件夹添加
3. 配置属性 -> 链接器 -> 常规 -> 附加库目录，将 2 中得到的 Lib\library 文件夹添加
4. 添加工程引用的 dll 动态库，将 2 中得到的 Lib\dll 的全部文件放到工程的可执行文件所在的目录下 ，即生成的 Debug 文件夹中



## 4 调试、运行

### 4.1 在 Visual Studio 2015 中调试运行

选中`SplitSDI.sln`，即项目的工程文件，右键选择打开方式`Visual Studio 2015`，稍等片刻，等待项目文件完整加载。

在解决方案资源管理器中，选中项目，右键打开项目的属性。选中 配置属性 -> 常规 -> 平台工具集，改为 Visual Studio 2015(v140)。

在上方的解决方案平台中将`x64`改为`x86`，点击`本地 Windows 调试器`，即可调试运行。

**注意**

如果遇到如下错误提示：`MSB600` “rc.exe”已退出，代码为5。那么可用的解决方案如下：

1. 在任务管理器搜索 rc.exe，等待搜索结果出现

2. 选择 x86 版本的 rc.exe，复制其路径

3. 打开系统环境变量设置，添加/编辑用户环境变量，变量名：PATH，变量值：`C:\Windows\System32;C:\Program Files(x86)\Windows Kits\8.0\bin\x86;`

   具体请根据找到的 rc.exe 的路径进行编辑

4. 重启 Visual Studio 2015，再次打开项目即可调试运行。




### 4.2 在 Visual Studio 2017 中调试运行

选中`SplitSDI.sln`，即项目的工程文件，右键选择打开方式`Visual Studio 2017`，稍等片刻，等待项目文件完整加载。

在上方的解决方案平台中将`x64`改为`x86`，点击`本地 Windows 调试器`，即可调试运行。

**注意**

如果出现错误，提示计算机中丢失 `glut32.dll`，请重复上文 3.2 中的第四步。



## 5 代码架构

本代码经过一次重构，详细的代码结构有待后续补充。



## 6  后记

本项目是本人第一个独立开发的项目，本文档描述的实践方法经过本人实践，如果后续有其他问题请及时联系本人。







