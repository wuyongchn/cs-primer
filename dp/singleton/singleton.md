## Singleton
### 动机
- 在软件系统中，经常有这样一些特殊的类，必须保证他们在系统中只存在一个实例，才能保证它们的逻辑正确性、以及良好的效率。
- 如何绕过常规的构造器，提供一种机制来保证一个类只有一个实例？
- 这应该是类设计者的责任，而不是使用者的责任。

### 模式定义
保证一个类仅有一个实例，并提供一个该实例的全局访问点

### 结构
<img src='../imgs/singleton.png'>

### 要点总结
- Singleton 模式中的实例构造器可以设置为 protected 以允许子类派生。
- Signleton 模式一般不要支持拷贝构造函数和 Clone 接口，因为这有可能导致多个对象实例，与 Singleton 模式的初衷违背。
- 如何实现多线程安全环境下的 Singleton？注意对双检查锁的正确实现。