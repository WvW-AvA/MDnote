# Computer Graphic Lecture 9 Ray Tracing (2)

### 辐照度量学的一些概念

**Radiant energy（辐射能量）Q [J]**

**Radiant flux （power辐射功率)单位[W] [lm]**
$$
Φ=dQ/dt
$$


**Radiant intensity (辐射强度) :power per unit solid angle单位体积角的辐射功率**
$$
I(ω)=dΦ/dω
$$
<img src="picture\2021-10-28_141525.png" style="zoom:80%;" />

Differential Solid Angles (微分体积角)：类比弧度
$$ {Differential Solid Angles}
dω=dA/r^2=sin\theta d\theta d\phi
$$ {Differential Solid Angles}

$$
Ω=A/r^2
$$

**Irradiance:（辐照度):The irradiance is the power per unit area incident on a surface point**
$$
E(X)=dΦ(x)/dA 
$$

$$
unit:[W/m^2][lm/m^2=lux]
$$



**Radiance(辐亮度):The radiance (luminance) is the power emitted,reflected ,transmitted or received by a surface ,**

**per unit solid angle,per projected unit area.**

![](picture\2021-10-28_144648.png)
$$
L(p,w)=d^2Φ(p,w)/dwdAcos\theta
$$

$$
unit:[W/sr*m^2][cd/m^2=lm/sr*m^2=nit]
$$



**Irradiance vs. Radiance**

Irradiance: total power received by area dA.

Radiance: Power received by area dA from "direction" dω(可看成某个方向上的irradiance)

<img src="picture\2021-10-28_150142.png" style="zoom:80%;" />
$$
dE(p,w)=L_i(p,w)cos\theta dw
$$

$$
E(p)=\int_{H^2} L_i(p,w)cos\theta dw
$$

### Bidirectional Reflectance Distribution Function(BRDF)（双向反射分布函数）

The Bidirectional Reflectance Distribution Function(BRDF) represents how much light is reflected into each outgoing direction from each incoming direction 

（就是一束光打到一块表面，然后会四面八方得反射出去，我们现在知道了入射光的irradiance 想要知道某一方向上的反射光的radiance ,就是由这个分布函数表示。）

![](picture\2021-10-28_151841.png)
$$
f_r(w_i\to w_r)=dL_r(w_r)/dE_r(w_i)=dL_r(w_r)/L_i(w_i)cos\theta _idw_i
$$

$$
unit: [1/sr]
$$

如果要求某一方向辐射出来的辐照度(Irradiance)只需对入射的辐照度乘以分布函数进行积分。
$$
L_r(p,w_r)=\int _{H^2} f_r(p,w_i\to w_r)L_i(p,w_i)cos\theta _idw_i
$$

### The Rendering Equation

Re-write the reflection equation:
$$
L_r(p,w_r)=\int _{H^2} f_r(p,w_i\to w_r)L_i(p,w_i)cos\theta _idw_i
$$
by adding an Emision term to make general!



The Rendering Equation
$$
L_o(p,w_o)=L_e(p,w_o)+\int _{Ω+} L_i(p,w_i)f_r(p,w_i,w_o)(n*w_i)dw_i
$$
渲染方程就是反射方程加上发光部分。H^2为半球。



#### 离散情形

考虑一个点光源

![](picture\2021-10-28_160810.png)

有方程

![](picture\2021-10-28_160755.png)

多个点光源只需要将各个点光源对该位置的反射光强进行求和就好

![](picture\2021-10-28_164503.png)

![](picture\2021-10-28_164515.png)

面光源即无数个点光源的集合，可以用积分表示

![](picture\2021-10-28_164535.png)

![](picture\2021-10-28_164548.png)



### Rendering Equation的简化形式

对于上述复杂的式子，我们可以看出其中只有L是未知的

![](picture\2021-10-28_165442.png)

可化简为
$$
l(u)=e(u)+\int l(v)K(u,v)dv
$$

$$
其中K(u,v)dv为Light Transport Operator(光线传播算子)
$$

于是式子就被简化成（有点神奇，积分方程直接转化为线性方程，不太理解）
$$
L=E+KL
$$
然后经过运算，可以解出
$$
L=(1-K)^{-1}E
$$
然后展开？？？

就得出了
$$
L=E+KE+K^2E+K^3E+...
$$
我们从物理的角度考虑这个式子，它可以解释成总的光强为

* 没有反射的光线
* 反射一次的光线
* 反射两次的光线
* ...
* 反射无数次光线

的叠加。
