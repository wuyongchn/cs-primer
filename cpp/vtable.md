# C++ 虚函数表实现
## vtable 位于何处
先定义两个基类 Base1 和 Base2
```
class Base1 {
 public:
  Base1() : value(1) {}
  virtual void vfn1() { std::cout << "Base1::vfn1" << std::endl; }
  virtual void vfn2() { std::cout << "Base1::vfn2" << std::endl; }
  long value;
};

class Base2 {
 public:
  Base2() : value(2) {}
  void fn1() { std::cout << "Base2::fn1" << std::endl; }
  void fn2() { std::cout << "Base2::fn2" << std::endl; }
  long value;
};
```
输出如下地址
```
int main() {
  Base1 base1;
  Base2 base2;

  long* base1_addr = (long*)&base1;
  long* base2_addr = (long*)&base2;

  std::cout << "&base1 = " << base1_addr << "\t&base1.value = " << &base1.value
            << std::endl;
  std::cout << "&base2 = " << base2_addr << "\t&base2.value = " << &base2.value
            << std::endl;
  return 0;
}
```
执行结果为
```
&base1 = 0x7fff0c115080 &base1.value = 0x7fff0c115088
&base2 = 0x7fff0c115068 &base2.value = 0x7fff0c115068
```
base1.value 的地址相对于 base1 偏移了 8 个字节（一个指针大小），但是 base2.value 的地址和 base2 的地址重合。base1 和 base2 两者唯一的差别是，base1 存在虚函数。由此推断，虚函数表 vtable 位于所有成员变量之前。

可以通过如下方式验证
```
int main() {
  Base1 base1;
  long** vtable = (long**)&base1;
  typedef void(*FNPtr)();
  auto vfn1_ptr = (FNPtr)(*vtable)[0];
  auto vfn2_ptr = (FNPtr)(*vtable)[1];
  vfn1_ptr();
  vfn2_ptr();
  return 0;
}
```
程序输出为
```
Base1::vfn1
Base1::vfn2
```
由此验证了我们的想法。TODO：插入图片

## 多态如何实现
先定义派生类 Derive1，其重写虚函数 vfn2
```
class Derive1 : public Base1 {
 public:
  void vfn1() override { std::cout << "Derive1::vfn1" << std::endl; }
};
```
然后输出虚函数表的内容
```
int main() {
  {
    std::cout << "----Base1----" << std::endl;
    Base1 base1;
    long** vtable = (long**)&base1;
    std::cout << "vfn1_ptr = " << (*vtable)[0] << std::endl;
    std::cout << "vfn2_ptr = " << (*vtable)[1] << std::endl;
  }
  {
    std::cout << "----Derive1----" << std::endl;
    Base1 *base1 = new Derive1;
    long** vtable = (long**)base1;
    typedef void (*FNPtr)();
    std::cout << "vfn1_ptr = " << (*vtable)[0] << std::endl;
    std::cout << "vfn2_ptr = " << (*vtable)[1] << std::endl;

    auto vfn1_ptr = (FNPtr)(*vtable)[0];
    vfn1_ptr();
    delete base1;
  }
  return 0;
}
```
结果为
```
----Base1----
vfn1_ptr = 94011309845860
vfn2_ptr = 94011309845916
----Derive1----
vfn1_ptr = 94011309845972
vfn2_ptr = 94011309845916
Derive1::vfn1
```
可以看到，Derive1 中，vfn1_ptr 的地址改变，并且指向了 Derive1::vfn1 函数实现，虚函数表未做更改（vfn1 和 vfn2 位于虚函数表的相对位置不变）

## 派生类添加虚函数
```
class Derive2 : public Base1 {
 public:
  void vfn1() override { std::cout << "Derive2::vfn1" << std::endl; }
  virtual void vfn3() { std::cout << "Derive2::vfn3" << std::endl; }
};
```
现在输出 Derive2 虚函数表内容
```
int main() {
  {
    std::cout << "----Base1----" << std::endl;
    Base1 base1;
    long** vtable = (long**)&base1;
    std::cout << "vfn1_ptr = " << (*vtable)[0] << std::endl;
    std::cout << "vfn2_ptr = " << (*vtable)[1] << std::endl;
  }
  {
    std::cout << "----Derive2----" << std::endl;
    Base1* base1 = new Derive2;
    long** vtable = (long**)base1;
    typedef void (*FNPtr)();
    std::cout << "vfn1_ptr = " << (*vtable)[0] << std::endl;
    std::cout << "vfn2_ptr = " << (*vtable)[1] << std::endl;
    std::cout << "vfn3_ptr = " << (*vtable)[2] << std::endl;

    auto vfn3_ptr = (FNPtr)(*vtable)[2];
    vfn3_ptr();
    delete base1;
  }
  return 0;
}
```
其结果为
```
----Base1----
vfn1_ptr = 94427161452192
vfn2_ptr = 94427161452248
----Derive2----
vfn1_ptr = 94427161452304
vfn2_ptr = 94427161452248
vfn3_ptr = 94427161452360
Derive2::vfn3
```
可以看到，Derive2 的虚函数表增加了一个条目，指向新增的虚函数。

## 多重继承情况
```
class Base3 {
 public:
  Base3() : value(3) {}
  virtual void vfn4() { std::cout << "Base3::vfn4" << std::endl; }
  long value;
};

class Derive3 : public Base1, public Base3 {
};
```
首先输出 Derive3 两个成员变量的地址
```
int main() {
  Derive3 derive3;
  std::cout << "&derive3 = " << &derive3 << std::endl;
  std::cout << "&derive3.Base1::value = " << &derive3.Base1::value << std::endl;
  std::cout << "&derive3.Base3::value = " << &derive3.Base3::value << std::endl;
}
```
结果为
```
&derive3 = 0x7ffc8c326260
&derive3.Base1::value = 0x7ffc8c326268
&derive3.Base3::value = 0x7ffc8c326278
```
可以看到，Base1::value 的地址相对于 derive3 偏移了 8 个字节，而 Base3::value 的地址相对于 Base1::value 偏移了 16 个字节。因此，猜猜，Base1::value 和 Base3::value 前，插入了两个虚函数表指针。
```
int main() {
  Derive3 derive3;
  long* base_ptr = (long*)&derive3;
  typedef void (*FNPtr)();
  {
    long** vtable = (long**)base_ptr;
    auto vfn1_ptr = (FNPtr)(*vtable)[0];
    auto vfn2_ptr = (FNPtr)(*vtable)[1];
    vfn1_ptr();
    vfn2_ptr();
  }
  {
    long** vtable = (long**)(base_ptr + 2);
    auto vfn4_ptr = (FNPtr)(*vtable)[0];
    vfn4_ptr();
  }
  return 0;
}
```
结果为
```
Base1::vfn1
Base1::vfn2
Base3::vfn4
```
结果与我们的预期相符。

## 多重继承添加虚函数
```
class Derive4 : public Base1, public Base3 {
 public:
  virtual void vfn5() { std::cout << "Derive4:vfn5" << std::endl; }
};
```
是否需要修改两个虚函数表，通过如下方式验证
```
int main() {
  Derive4 derive4;
  long* base_ptr = (long*)&derive4;
  typedef void (*FNPtr)();
  {
    long** vtable = (long**)base_ptr;
    auto vfn1_ptr = (FNPtr)(*vtable)[0];
    auto vfn2_ptr = (FNPtr)(*vtable)[1];
    auto vfn5_ptr = (FNPtr)(*vtable)[2];
    vfn1_ptr();
    vfn2_ptr();
    vfn5_ptr();
  }
  {
    long** vtable = (long**)(base_ptr + 2);
    auto vfn4_ptr = (FNPtr)(*vtable)[0];
    auto vfn5_ptr = (FNPtr)(*vtable)[1];
    vfn4_ptr();
    vfn5_ptr();
  }
  return 0;
}
```
结果为
```
Base1::vfn1
Base1::vfn2
Derive4:vfn5
Base3:vfn4
Segmentation fault (core dumped)
```
可以看到，只修改第一个虚函数表

## 虚拟继承
```
class Derive5 : public virtual Base1 {};
class Derive6 : public virtual Base2 {};
```
输出成员变量的偏移
```
int main() {
  Derive5 derive5;
  std::cout << "&derive5 = " << &derive5
            << "\t&derive5.value = " << &derive5.value << std::endl;

  Derive6 derive6;
  std::cout << "&derive6 = " << &derive6
            << "\t&derive6.value = " << &derive6.value << std::endl;
  return 0;
}
```
结果为
```
&derive5 = 0x7ffc1bd89380       &derive5.value = 0x7ffc1bd89390
&derive6 = 0x7ffc1bd89370       &derive6.value = 0x7ffc1bd89378
```
和普通的继承相比，多出来 8 个字节。用 derive6 查看着 8 个字节的内容
```

```