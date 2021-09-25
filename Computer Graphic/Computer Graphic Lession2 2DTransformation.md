# Computer Graphic Lession2 Transformation

### 2D transformations: rotation, scale, translation



##### scale

![img](D:\C++\Computer Graphic\picture\2021-08-13_101035.png)

我们可以用矩阵表示这个变换过程

<img src="D:\C++\Computer Graphic\picture\2021-08-13_095854.png" alt="img" style="zoom:40%;" />

一般的Scale有

![img](D:\C++\Computer Graphic\picture\2021-08-13_100007.png)

我们可以用矩阵表示这个变换过程

<img src="D:\C++\Computer Graphic\picture\2021-08-13_095813.png" alt="img" style="zoom:50%;" />

##### rotate

![img](D:\C++\Computer Graphic\picture\2021-08-13_100026.png)

##### translation

![img](D:\C++\Computer Graphic\picture\2021-08-13_100101.png)

那么怎么用矩阵运算来表示捏？

好像不能简单地用2*2矩阵相乘来表示，必须引入加法



于是二维空间内的所有变换可以这样表示

<img src="D:\C++\Computer Graphic\picture\2021-08-13_100116.png" alt="img" style="zoom:38%;" />

这就是仿射变换的表示方式。



但是这样的话不够整洁，要是能用乘法表示二维空间内的所有变换的话，就完美了。

于是为了将translation 统一到到矩阵乘法中，我们引入齐次坐标（Homogeneous Coordinates）的概念

#### Homogeneous Coordinates

说白就是多加一个维度，用三维矩阵的乘法就可以表示所有的二维空间内的变换。让我们来看看他是怎么做到的吧！

在齐次坐标中，2D的点可以表示为(x,y,1),	2D的向量表示为(x,y,0)。

<img src="D:\C++\Computer Graphic\picture\2021-08-13_100134.png" alt="img" style="zoom:50%;" />

也就是说，齐次坐标中(x,y,w)表示为2D中的点(x/w,y/w)。



其实只要解决了用矩阵乘法表示translation 的问题，问题就迎刃而解了。

<img src="D:\C++\Computer Graphic\picture\2021-08-13_100145.png" alt="img" style="zoom:38%;" />



可以看出，translation的向量就是变换矩阵的第三列。



于是，我们就可以得出二维空间通用的变换矩阵：

<img src="D:\C++\Computer Graphic\picture\2021-08-13_100315.png" alt="img" style="zoom:50%;" />

其中，a,b,c,d为rotation,scale的变换的二维矩阵表达形式，tx,ty表示translation。



### 3D Transformations

类比2D transformations,我们同样可以用齐次坐标表示3D transformations，用四维矩阵表示。

<img src="D:\C++\Computer Graphic\picture\2021-08-13_105007.png" alt="img" style="zoom:50%;" />

scale,translation的定义方式和2D的相同，不再赘述，3D的rotation就比较麻烦。

##### 3D rotation

首先，任意的3D旋转都可以分解为绕x轴，y轴，z轴旋转表示。

（想象一下飞机的旋转方式）

<img src="D:\C++\Computer Graphic\picture\2021-08-13_105518.png" alt="img" style="zoom:50%;" />

<img src="D:\C++\Computer Graphic\picture\2021-08-13_105528.png" alt="img" style="zoom:50%;" />

我们叫他们欧拉角。

而绕x,y,z轴旋转的矩阵就是2D旋转的过程，可得：

<img src="D:\C++\Computer Graphic\picture\2021-08-13_105903.png" alt="img" style="zoom:50%;" />

而我们更常使用的绕轴旋转的矩阵可以用Rodrigues' Rotation Formula表示。

<img src="D:\C++\Computer Graphic\picture\2021-08-13_110150.png" alt="img" style="zoom:50%;" />

