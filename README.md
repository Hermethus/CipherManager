# CipherManager

一个简单的密码管理软件

# 更新信息

2022/6/20

本软件使用Qt框架编写。由于我对Qt的使用还不太熟练，所以界面不太好看。在后续的更新中（如果有的话），我会对界面进行美化。

相比于早期的python版本（源码见Github），该版本添加了条目分组和备注的功能，如果你愿意，也可以将本软件作为一个加密记事本使用。

2022/7/7 

- 修复了部分导致崩溃的bug；

- 实现了文件的拖拽打开，现在将密文或者明文文件拖拽到程序上就能够直接打开，不需要走菜单栏了；

- 优化了保存文件的流程；

- 现在按下回车键即可进行搜索；

- 其他微小优化。

# 致谢

感谢bricke提供的基于Qt的加密库。
Thanks for the AES encryption library implemented in Qt provided by [brick](https://github.com/bricke/Qt-AES "brick").