### Tips of Gradient Descent

#### 1.Review

![img](https://github.com/kimojiaa/MDnote/raw/master/Picture/2021-07-19_150516.png)



#### Tip1:Turning your Learning Rate

If your Learning Rate is too small,It will cost a lot of time to get the suit model.

if your Learning Rate is too large,It couldn't get the suit model,and loop between two parameters,even fly out of boundary.

![img](https://github.com/kimojiaa/MDnote/raw/master/Picture/2021-07-19_150946.png)

So you can reduce your Learning Rate by some factor every few epochs.

At the beginning,we are far from the destination,so we use larger Learning Rate.

After serval epochs,we are near the destination,so we reduce the Learning Rate. 

##### Relative Arithmetic

###### 1.Adagrad

![img](https://github.com/kimojiaa/MDnote/raw/master/Picture/2021-07-19_152717.png)

![img](https://github.com/kimojiaa/MDnote/raw/master/Picture/2021-07-19_152810.png)

###### 2.RMS Prop

![img](https://github.com/kimojiaa/MDnote/raw/master/Picture/2021-07-19_171054.png)

### Tip2.Add Disturbance

Sometimes,The place whose the gradience equal to 0 isn't the minimum of the whole function.

It would be terrace or local minimum,So we can add some disturbance and let it keep going.

##### Relative Arithmetic

###### SDG with momentum

We can add the last movement as a parameter and calculate the next movement.

###### 



![img](https://github.com/kimojiaa/MDnote/raw/master/Picture/2021-07-19_164544.png)

![img](https://github.com/kimojiaa/MDnote/raw/master/Picture/2021-07-19_164647.png)

The result just like the movement of the date has inertance,like a ball roll down from the up of the mountain.