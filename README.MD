
游戏名：
进击的坦克

平台：
Win32

工程：
VS2013

介绍：
这是一个横版瓦片地图式的坦克战斗游戏。除了一些Win32API相关代码，其他均为手写代码。画面为手绘风格，纯手工绘制，目前共有四关。这个游戏是本人大一（2013）的时候于暑期实训期间所做，获得过学院第一名。现在（2017）因为某些需要，重新拿出来进行了一些BUG修复、代码改进、地图重制等，并提供给需要的人。

警告：
本游戏年代久远，制作工具简陋，开发人员水平参差不齐，代码可读性极低，一切因为大量修改本游戏而造成的问题请自行承担，本人不提供维护或Debug指导 :p

注意事项：
SuperTank是游戏主体，TiledTransform是地图转换代码。本游戏地图使用Tiled制作并导出成json（见Maps文件夹），然后用TiledTransform工程进行转换，最后复制粘贴到SuperTank.cpp的数组中。


-------------------------

GameName:
Attack on Tank

Platform:
Win32

Project:
VS2013

Introduction:
This is a tank fighting game which has a style of tiledmap and side-scrolling. Except for some Win32API codes, all the codes are written by hand. The painting style is hand-drawn and all bmps are painted by hand. There are four stages at present. This game is made by me and my classmates when I was a freshman in university(2013) and it got the first prize in our college. Now(2017), because of some demand, I took it out from the corner of my disc, amended some bugs, modified some codes, rebuilt some maps and provide it to anyone in need.

Warning:
The codes are ancient, the technology is out of date, so the readability and maintainability is so bad that all bugs casued by modifying the codes are none of my business :p

Notes:
SuperTank is the main body of the game and TiledTransform is the project for transforming the map. The maps of this game are made by Tiled and exported into json(see the Maps directory). Then use the project TiledTransform to transform the numbers and copy it into the corresponding array in SuperTank.cpp.
