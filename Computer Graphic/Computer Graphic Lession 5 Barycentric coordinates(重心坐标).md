# Computer Graphic Lession 5 Barycentric coordinates(重心坐标)

#### 定义

空间中任意一点的坐标都可以表示为三角形三个顶点坐标的线性组合。

即

<img src="D:\C++\Computer Graphic\picture\2021-08-23_144451.png" alt="img" style="zoom:67%;" />

且

<img src="D:\C++\Computer Graphic\picture\2021-08-23_144600.png" alt="img" style="zoom:67%;" />

若该点在三角形内，即α，β，γ均大于零，则称（α，β，γ）为该点在三角形ABC的重心坐标。

#### 求法

​					<img src="D:\C++\Computer Graphic\picture\2021-08-23_145407.png" alt="img" style="zoom:38%;" />								<img src="D:\C++\Computer Graphic\picture\2021-08-23_145440.png" alt="img" style="zoom:50%;" />   



我们可以让三角形三个顶点显示不同的颜色，然后通过重心坐标插值出三角形内每个点的颜色，得出这么一张图：

<img src="D:\C++\Computer Graphic\picture\2021-08-23_150012.png" alt="img" style="zoom: 50%;" />

由此可见，从另一种角度看，重心坐标实际上表示的是三角形内的点受三角形三个顶点的影响的加权平均，利用这个特性，我们可以通过三角形顶点的属性，插值出三角形内任意一点的属性。

#### 透视矫正插值

然而，在图形学中，我们在屏幕空间下的通过重心坐标插值出来的值不能直接用，需要转换到三维实际坐标中，可以通过投影逆变换来实现。

##### z坐标的插值

<img src="D:\C++\Computer Graphic\picture\2021-08-27_082037.png" alt="img" style="zoom:50%;" />

##### 任意属性的插值

<img src="D:\C++\Computer Graphic\picture\2021-08-27_082053.png" alt="img" style="zoom:50%;" />

既然是任意属性都可以套用这种公式，很自然的就可以联想到利用C++模板函数来实现。

```c++
template <typename T1>
T1 lerp(const T1 *origin,float z_value,Vector3f weight, const std::array<Eigen::Vector3f,3>&view_pos)
{
    return ((weight.x()*origin[0]/view_pos[0].z()+
            weight.y()*origin[1]/view_pos[1].z()+
            weight.z()*origin[2]/view_pos[2].z())*z_value);
}
```

