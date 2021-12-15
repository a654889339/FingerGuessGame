#pragma once

/*
GamePlay部分的基础依赖
仅限Client和GameServer使用。

用 _CLIENT 宏表示仅服务端代码
用 _SERVER 宏表示仅服务端代码

class GamePlay 为入口，使用本工程的进程需要实例化一个class GamePlay，并在每帧调用GamePlay.Active
*/