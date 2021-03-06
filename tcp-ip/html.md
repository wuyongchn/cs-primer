## 超文本传输协议（HyperText Markup Language, HTML）
HTTP 规定了在浏览器和服务器之间的请求和响应的格式和规则，定义了浏览器怎么向万维网服务器请求万维网文档，以及服务器怎样把文档传送给浏览器。

HTTP 的主要特点：
1. 无状态。无状态是指协议对于事务处理没有记忆能力，服务器不知道客户端是什么状态。即客户端发送 HTTP 请求后，服务器根据请求，会给我们发送数据，发送完后，不会记录信息。(使用 cookie 机制可以保持 session，解决无状态的问题)
2. 无连接。无连接的含义是限制每次连接只处理一个请求。服务器处理完客户的请求，并收到客户的应答后，即断开连接，采用这种方式可以节省传输时间。(当今多数服务器支持 Keep-Alive 功能，使用服务器支持长连接，解决无连接的问题)
3. 灵活。HTTP 协议允许客户端和服务器端传输任意类型任意格式的数据对象
4. 简单快速。当客户端向服务器端发送请求时，只是简单的填写请求路径和请求方法即可，然后就可以通过浏览器或其他方式将该请求发送就行了

HTTP1.1 的主要特点
1. 长连接。HTTP1.1 增加了一个 Connection 字段，通过设置 Keep-Alive 可以保持 HTTP 连接不断开，避免了每次客户端与服务器请求都要重复建立释放建立 TCP 连接，提高了网络的利用率。如果客户端想关闭 HTTP 连接，可以在请求头中携带 Connection:false 来告知服务器关闭请求。
2. 支持请求管道化（pipelining）。基于 HTTP1.1 的长连接，使得请求管线化成为可能。管线化使得请求能够“并行”传输。 HTTP 管道化可以让我们把先进先出队列从客户端（请求队列）迁移到服务端（响应队列）。
3. 支持缓存处理（强缓存和协商缓存）新的字段如 cache-control，支持断点传输，以及增加了 Host 字段（使得一个服务器能够用来创建多个 Web 站点）。

HTTP 请求报文与响应报文格式
- 请求报文包含三部分：
  - 请求行：包含请求方法、URI、HTTP 版本信息
  - 请求首部字段
  - 请求内容实体
- 响应报文包含三部分：
  - 状态行：包含 HTTP 版本、状态码、状态码的原因短语
  - 响应首部字段
  - 响应内容实体

HTTP请求报文中常用的方法

|  方法   | 意义                          |
| :-----: | :---------------------------- |
|   GET   | 请求读取有URL标识的信息       |
|  HEAD   | 请求读取由URL标识的信息的首部 |
|  POST   | 给服务器添加信息              |
| CONNECT | 用于代理服务器                |

GET和POST的区别

1. GET 重点在从服务器上获取资源，POST 重点在向服务器发送数据；
2. GET 传输数据是通过 URL 请求，以 field = value 的形式，置于 URL 后，并用"?"连接，多个请求数据间用"&"连接，如 `http://127.0.0.1/Test/login.action?name=admin&password=admin`，这个过程用户是可见的；POST 传输数据通过 HTTP 的 post 机制，将字段与对应值封存在请求实体中发送给服务器，这个过程对用户是不可见的；
3. GET 传输的数据量小，因为受 URL 长度限制，但效率较高；POST 可以传输大量数据，所以上传文件时只能用 POST 方式；
4. GET 是不安全的，因为 URL 是可见的，可能会泄露私密信息，如密码等；POST 较 GET 安全性较高；
5. GET 方式只能支持 ASCII 字符，向服务器传的中文字符可能会乱码。POST 支持标准字符集，可以正确传递中文字符。

HTTP常用状态码

| 状态码 | 含义                                                                                                           |
| :----: | :------------------------------------------------------------------------------------------------------------- |
|  200   | 请求被正常处理                                                                                                 |
|  204   | 请求被受理但没有资源可以返回                                                                                   |
|  206   | 客户端只是请求资源的一部分，服务器只对请求的部分资源执行 GET 方法，相应报文中通过 Content-Range 指定范围的资源 |
|  301   | 永久性重定向                                                                                                   |
|  302   | 临时重定向                                                                                                     |
|  303   | 与 302 状态码有相似功能，只是它希望客户端在请求一个 URL 的时候，能通过 GET 方法重定向到另一个 URL 上           |
|  304   | 发送附带条件的请求时，条件不满足时返回，与重定向无关                                                           |
|  307   | 临时重定向，与 302 类似，只是强制要求使用 POST 方法                                                            |
|  400   | 请求报文语法有误，服务器无法识别                                                                               |
|  401   | 请求需要认证                                                                                                   |
|  403   | 请求的对应资源禁止被访问                                                                                       |
|  404   | 服务器无法找到对应资源                                                                                         |
|  500   | 服务器内部错误                                                                                                 |
|  503   | 服务器正忙                                                                                                     |