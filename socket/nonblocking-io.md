## 概述
套接字的默认状态是阻塞的，当发出一个不能立即完成的套接字调用时，其进程将被投入睡眠，等待相应操作完成

1. 输入操作，包括 read()、readv()、recv()、 recvfrom()、recvmsg()
2. 输出操作，包括 write() 、writev()、send()、sendmsg()
3. 接受外来连接，即 accept() 函数
4. 发起外出连接，及用于 TCP 的 connect() 函数

## 非阻塞 connect() 
当一个非阻塞的 TCP 套接字调用 connect() 时，connect() 将立即返回一个 EINPROGRESS 错误，不过已经发起的 TCP 三路握手继续进行。接着使用 select() 检测这个连接或成功或失败的已建立条件。非阻塞 connect() 有三个用途：
- 把三路握手叠加在其他处理上
- 同时建立多个连接
- 既然使用 select() 等待连接的建立，可以给 select() 指定一个时间限制，使得能够缩短 connect() 的超时

## 非阻塞 accept()
服务器繁忙时，它无法在 select() 返回监听套接字的可读条件后马上调用accept()。通常情况下服务器的这种迟钝不成问题，但是结合上连接建立之后到达的来自客户的 RST （这个已完成连接被服务器 TCP 驱除已完成队列），问题就出现了。

服务器会一直阻塞在 accept() 调用上，直到其他某个客户建立一个连接为止。但是在此期间，服务器单纯阻塞在 accept() 调用上，无法处理任何其他已就绪的描述符（可读或可写）

解决办法如下：
- 当使用 select() 获悉某个监听套接字上何时有已完成连接准备好被 accept() 时，总是把这个监听套接字设置为非阻塞。
- 在后续的 accept() 调用中忽略以下错误： EWOULDBLOCK（源自Kerkeley 的实现，客户中止连接时）、ECONNABORTED（POSIX 实现，客户中止连接时）、 EPROTO SVR4 实现，客户中止连接时）和 EINTR（如果有信号被捕获）