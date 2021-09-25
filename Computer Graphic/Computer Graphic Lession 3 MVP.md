# Computer Graphic Lession 3 MVP

#### How to take a photo(怎样拍一张照片)

* （找个好位置，把人聚集起来）Find a good place and arrange people(model transformation)

* （相机找个好角度）Find a good "angle" to put the camera(view transformation)

* （茄子！）Cheese!(projection transformation）



#### View/Camera Transformation

##### Define the Camera（定义一个相机）

* Position(位置)  <img src="D:\C++\Computer Graphic\picture\2021-08-13_141939.png" alt="img" style="zoom:50%;" />
* Look-at/gaze direction(朝向)<img src="D:\C++\Computer Graphic\picture\2021-08-13_141947.png" alt="img" style="zoom:50%;" />
* Up direction (上方向) <img src="D:\C++\Computer Graphic\picture\2021-08-13_141956.png" alt="img" style="zoom:50%;" />
  * assuming perp. to look-at(用来确定相机的旋转)

<img src="D:\C++\Computer Graphic\picture\2021-08-13_141532.png" alt="img" style="zoom:38%;" />

由于相片只与相机与物体的相对位置有关，不妨将相机的position变换到原点，Look-at direction 变换到看向-z，Up direction为y，让物体也做类似的变换，这就是View Transformation Matrix。

##### View Transformation Matrix

由定义可知矩阵的表达式为

<img src="D:\C++\Computer Graphic\picture\2021-08-13_143110.png" alt="img" style="zoom:50%;" />

即平移变换乘旋转变换

平移变换很简单，就是将相机移到原点，表达式为

<img src="D:\C++\Computer Graphic\picture\2021-08-13_143016.png" alt="img" style="zoom:50%;" />

有定义：

Look-at/gaze direction(朝向)<img src="D:\C++\Computer Graphic\picture\2021-08-13_141947.png" alt="img" style="zoom:50%;" />

Up direction (上方向) <img src="D:\C++\Computer Graphic\picture\2021-08-13_141956.png" alt="img" style="zoom:50%;" />

而直接考虑怎样把原来的Look-at direction转到-z方向来求旋转矩阵比较麻烦，不如换个思路，求-z方向转到Look-at direction的变换，再求逆矩阵。

有-z转向Look-at direction 矩阵为

<img src="D:\C++\Computer Graphic\picture\2021-08-13_143034.png" alt="img" style="zoom:50%;" />

逆矩阵为

<img src="D:\C++\Computer Graphic\picture\2021-08-13_143047.png" alt="img" style="zoom:50%;" />

再用

<img src="D:\C++\Computer Graphic\picture\2021-08-13_143110.png" alt="img" style="zoom:50%;" />

求出View Transformation

#### Projection Transformation

(Projection Transformation)投影变换，最最最核心，也是最难的变换，我们我们要将3D空间物体转换到2D平面内，就是利用投影。



有两种投影方式：

- 坐标投影(Orthographic projection)
- 透视投影(Perspective projection)

##### 坐标投影(Orthographic projection)

类似于从无限远处看向物体，即视线是平行线看向物体

<img src="D:\C++\Computer Graphic\picture\2021-08-13_145604.png" alt="img" style="zoom: 50%;" />

一般来说，我们做投影变换，将整个空间投射到一个正交规范的立方体中，即[-1,1] [-1,1] [-1,1]

<img src="D:\C++\Computer Graphic\picture\2021-08-13_145615.png" alt="img" style="zoom:50%;" />

很简单，对应的变换矩阵为

<img src="D:\C++\Computer Graphic\picture\2021-08-13_150048.png" alt="img" style="zoom:50%;" />

<img src="D:\C++\Computer Graphic\picture\2021-08-20_111654.png" alt="img" style="zoom:50%;" />

##### 透视投影（Perspective Projection）

一般来说，人眼所见都是透视投影，因此，透视投影看起来会更加真实，应用也会更加广泛。

辣么，我们要怎么做捏~

<img src="D:\C++\Computer Graphic\picture\2021-08-13_150614.png" alt="img" style="zoom:50%;" />

首先，我们可以看到，透视投影是个锥形，而我们成像的地方是这个锥形的截面，于是我们便可以考虑将这个台挤压成方形空间，再进行坐标投影。

<img src="D:\C++\Computer Graphic\picture\2021-08-13_151047.png" alt="img" style="zoom:50%;" />

辣么，要怎样挤压他捏~

先来画个截面

<img src="D:\C++\Computer Graphic\picture\2021-08-13_151209.png" alt="img" style="zoom:50%;" />

可以明显看出相似三角形的关系，得出结论 x,y与n/z 成正比，但是z的关系还是未知的，即

<img src="D:\C++\Computer Graphic\picture\2021-08-13_151529.png" alt="img" style="zoom: 50%;" />

可以先得出变换矩阵的部分参数

<img src="D:\C++\Computer Graphic\picture\2021-08-13_151707.png" alt="img" style="zoom:38%;" />

接下来找z的变换关系

###### 两条观察得出的结论

(Any point in the near plane will not change)任何近平面上的点都不变

<img src="D:\C++\Computer Graphic\picture\2021-08-13_152321.png" alt="img" style="zoom: 33%;" />

通过这条式子可以知道第三行前两个数必定为0，不妨设第三行为(0 0 A B)。

<img src="D:\C++\Computer Graphic\picture\2021-08-13_152528.png" alt="img" style="zoom: 33%;" />

(Any points in z will in the far plane will not change)任何远平面的Z轴上的点都不会变

<img src="D:\C++\Computer Graphic\picture\2021-08-13_152610.png" alt="img" style="zoom: 33%;" />

解方程：

<img src="D:\C++\Computer Graphic\picture\2021-08-13_152619.png" alt="img" style="zoom: 33%;" />

最后再来进行正交投影，就得出透视投影的变换

<img src="D:\C++\Computer Graphic\picture\2021-08-13_153136.png" alt="img" style="zoom:50%;" />

<img src="D:\C++\Computer Graphic\picture\2021-08-20_111727.png" alt="img" style="zoom:50%;" />





