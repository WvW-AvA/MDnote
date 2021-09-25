# Computer Graphic Lecture 8 Ray Tracing 

  

#### 光线（Light Rays）

光线的三个宏观特性（Three ideas about light rays）

1. 光沿直线传播（Light travels in straight lines）
2. 光线相交的时候不会发生碰撞（Light rays don't collide with each other if they across）
3. 光线从光源出发，最后射向眼睛（Light rays travels from the light source to the eyes）

如果我们完全按照光线传播的路径进行模拟，计算量将会非常大，但是光线有一个特性，那就是光路可逆，逆向思维我们可以从眼睛中射出光线，模拟光线的传播路径。

那么具体要怎样从眼睛中射出光线呢？

#### 光线投射 Ray Casting

Appel 在1961年提出Ray Casting的概念

1. 每个像素投射出一根光线经过各种弹射，算出该像素的颜色，生成图片（Generate an image by casting one ray per pixel）
2. 射出光线指向光源判断是否位于阴影位置（Check for shadow by sending the rays to the light sources）

#### Pinhole Camera Model

<img src="picture\2021-09-04_164527.png" style="zoom: 67%;" />

<img src="picture\2021-09-04_164746.png" style="zoom:67%;" />

几个关键问题

1. 如何判断射线和是否相撞，怎么求出碰撞点
2. 光线的能量要怎么衰减，光路到底要怎么走，怎么反射折射
3. 物体材质对于光线的影响
4. 颜色要怎么算

#### 碰撞检测

##### 光线的数学定义

可以借用数学中射线的定义，即光线射出的原点o和方向d来定义

<img src="picture\2021-09-04_165607.png" style="zoom:67%;" />

r(t)=o+td  0<t<∞

其中o，d都是用向量表示

若d为单位向量，则t为光线上该点到原点的距离



##### 光线与隐式图形的碰撞

 光线与隐式图形<img src="picture\2021-09-04_165932.png" style="zoom:60%;" />的交点即<img src="picture\2021-09-04_165942.png" style="zoom:67%;" />的解。

若无实数解则意味着光线与图形无交点。

以球举例，球可以表示为

<img src="picture\2021-09-04_170356.png" style="zoom:67%;" />

将射线方程带入

<img src="picture\2021-09-04_170559.png" style="zoom:67%;" />

解出t

<img src="picture\2021-09-04_170648.png" style="zoom:67%;" />

若判别式小于零，t无解，意味着射线与圆相离，没有发生碰撞，

若判别式等于零，意味着射线与圆相切，

若判别式大于零，则t较小且大于零的那个为碰撞点。

##### 光线与显式图形的碰撞

显式图形的表示方式有很多种，其中最为普遍，用的最多的是三角形的表示方式，那么我们重点讨论与三角形的碰撞。

在之前的重心坐标我们得知三角形内的任意一点的重心坐标的表示方式

<img src="picture\2021-08-23_144451.png" style="zoom:50%;" />

其中

<img src="picture\2021-08-23_144600.png" style="zoom:50%;" />

于是我们可以和射线方程联立

<img src="picture\2021-09-04_172222.png" style="zoom:50%;" />

解得

<img src="picture\2021-09-01_100548.png" style="zoom:50%;" />

当t>0,b1>0,b2>0,(1-b1-b2)>0时表面射线与三角形相交。

求光线与一个由三角形组成的物体的交点，只需让光线与物体的所有三角形判断是否碰撞即可，然后取t最小的为碰撞点即可。

#### 碰撞检测的算法优化（Accelerating Ray-Surface Intersection）

若每根射线都与场景中的所有三角形求是否相交，当场景中物体的数量变多时，运算的消耗将越来越大，于是我们需要一些算法来加速。

##### 包围盒（Bounding Volumes）

包围盒将物体完全包裹住，如果射线连包围盒都撞不到，那么更不可能碰撞到物体本体。因此我们可以先让射线和物体的包围盒求交，若与包围盒有交点，则再与内部的物体求交。

不止可以单个物体判断求交，若场景中的物体数量非常多，为减少包围盒的数量，可以将几个物体放在一个包围盒内，保证每次光线交的数量不会膨胀，以下几种算法就是几种确定包围盒的方式。

为方便计算，我们约定包围盒的六个面会与对应的轴垂直

如图：

<img src="picture\2021-09-04_175816.png" style="zoom:50%;" />

称之为轴对齐包围盒（Axis-Aligned Bounding Box）即AABB包围盒。

##### 空间分割算法（Spatial Partition）

###### 八叉树（Oct-Tree）

将场景空间平均分为8份，并将空间内的物体存储在树的8个枝叶中，只有在射线与根节点所存储的空间的碰撞盒相撞时，才对空间内再进行八叉树细分，再检测碰撞，最后定位到物体。

<img src="picture\2021-09-04_181750.png" style="zoom:67%;" />

###### KD-Tree

八叉树分得太多，要考虑太多边界情况，我们想每次分割就砍一刀就好，于是就有了KD——Tree

<img src="D:\C++\Computer Graphic\picture\2021-09-04_183646.png" style="zoom:67%;" />

但是这些算法有些问题，如果一些物体同时处于两个空间内，要怎样划分物体的归属才能确保能搜寻到该物体。

所以说我们可以换个思路，与其划分空间，不如划分物体，对物体使用树状分割的算法。

##### Bounding Volumes Hierarchy

<img src="picture\2021-09-04_182149.png" style="zoom:67%;" />

###### 分割的两点注意事项

1. 为了使分割比较均匀，我们每次分割都从空间上较长的那个轴分割，这样能保证得到的碰撞盒的大小都比较均匀。
2. 确定好从那个轴分割后，我们可以取沿改轴排序为中间的物体为分界线，将所有物体划分为两部分。



