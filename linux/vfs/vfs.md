# 虚拟文件系统
虚拟文件系统（Virtual Filesystem, VFS）是内核的一个组件，用于处理与文件和文件系统相关的所有系统调用。VFS 是用户与特定文件系统之间的通用接口。这种抽象简化了文件系统的实现，并提供了更容易的多文件系统集成这样，文件系统的实现是通过使用 VFS 提供的 API 完成的，通用硬件和 I/O 子系统通信部分由 VFS 处理。

VFS的基本思想是提供一个可以表示来自任何文件系统的文件的文件模型。文件系统驱动程序负责底层操作。 这样，内核可以创建包含整个系统的单个目录结构。将有一个文件系统作为根，其余文件系统将安装在其各种目录中。

通用文件系统模型用 super_block 、inode、dentry 和 file 四个对象来表征任何文件系统。