Redis6.0.0 设计与实现
1. [Redis 服务器启动](./redis-server-start.md)
1. [redisServer & client & connection 数据结构](./redisServer.md)
1. [redisCommand 数据结构](./redisComand.md)
1. [standardConfig 数据结构](./standardConfig.md)
1. [initServerConfig() & loadServerConfig() 函数实现](./initServerConfig.md)
1. [initServer() 函数实现](./initServer.md)
1. [InitServerLast() 函数实现](./InitServerLast.md)
1. [aeFileEvent & aeTimeEvent](./event.md)
1. [aeMain() 函数实现](./aeMain.md)
1. [时间事件 severCron()](./time-event-severCron.md)
1. [文件事件之 acceptTcpHandler()](./acceptTcpHandler.md)
1. [文件事件之 connSocketEventHandler()](./connSocketEventHandler.md)
1. [命令处理 processCommand()](./processCommand.md)
1. [哈希表 dict 设计与实现](./dict.md)
1. [redisObject 初探](./redisObject-basic.md)
1. [redisDb 数据库实现](./redisDb.md)
1. [RDB 持久化](./.md)(TODO)
1. [AOF 持久化](./.md)(TODO)
1. [主从复制之 SLAVEOF & PSYNC](./replication-slaveof-psync.md)
1. [主从复制之 replicationCron()](./replicationCron.md)
1. [主从复制之 connectWithMaster()](./connectWithMaster.md)
1. [主从复制之 PARTIAL-RESYNC](./partial-resync.md)
1. [主从复制之 FULL-RESYNC](./full-resync.md)
1. [主从复制之写操作传播](./write-propagate.md)
1. [发布与订阅](./pubsub.md)
1. [Sentinel 基础知识](./sentinel-basic.md)
1. [Sentinel 启动](./sentinel-start.md)
1. [sentinelRedisInstance 数据结构](./sentinelRedisInstance.md)
1. [sentinelHandleConfiguration() 函数实现](./sentinelHandleConfiguration.md)
1. [sentinelIsRunning() 函数实现](./sentinelIsRunning.md)
1. [sentinelTimer() 函数实现](./sentinelTimer.md)
1. [sentinelHandleRedisInstance() 之监视](./sentinelHandleRedisInstance-monitoring.md)
1. [sentinelHandleRedisInstance() 之故障检测](./sentinelHandleRedisInstance-acting.md)
1. [sentinelHandleRedisInstance() 之故障转移](./sentinelHandleRedisInstance-acting2.md)
1. [sentinelFailoverStateMachine() 实现](./sentinelFailoverStateMachine-impl.md)
1. [Cluster 启动](./cluster-start.md)(TODO)
1. [clusterCron() 定时任务](./clusterCron.md)(TODO)
1. [Cluster 命令执行之 getNodeByQuery()](./getNodeByQuery.md)(TODO)
1. [](./.md)
1. [](./.md)
1. [Module 设计与实现](./module.md)(TODO)
1. [对象结构 redisObject](./redisObject.md)
1. [基本数据结构之 sds](./sds.md)
1. [基本数据结构之 adlist](./adlist.md)
1. [基本数据结构之 dict](./dict.md)
1. [基本数据结构之 intset](./intset.md)
1. [基本数据结构之 ziplist](./ziplist.md)
1. [基本数据结构之 listpack](./listpack.md)
1. [基本数据结构之 quicklist](./quicklist.md)
1. [基本数据结构之 zipmap](./zipmap.md)
1. [基本数据结构之 zset](./zset.md)