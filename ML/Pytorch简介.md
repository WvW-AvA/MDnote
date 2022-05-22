### Pytorch简介

机器学习的过程可以大致分为几个部分

1. read data via MyDataset
2. put dataset into Dataloader
3. contruct model and move to device (cpu/gpu)
4. set loss function
5. set optimizer

其中这几个部分，pytorch都有相应的组件可以使用。

**Load Data：** 

```python
tourch.utils.data.Dataset
tourch.utils.data.Dataloader
```

**Define Neural Network,Loss Function,Optimizer:**

```python
torch.nn
torch.optim
```



#### Tensor

Tensor is hight-dimensional matrix.

**Data Type**

| data type                  | torch define | torch tenser      |
| -------------------------- | ------------ | ----------------- |
| 32-bit float point         | torch.float  | torch.FloatTensor |
| 64-bit float point(signed) | torch.long   | torch.LongTensor  |

**Tensor Operators**

* **Unsqueeze: **expend a new dimension.

```python
>>>x=torch.zeros([2,3])
>>>x.shape
torch.Size([2,3])
>>>x=x.Unsqueeze(1)
>>>x.shape
torch.Size([2,1,3])
```

* **Transpose: **transpose two specified dimensions.

```python
>>>x=torch.zeros([2,3])
>>>x.shape
torch.Size([2,3])
>>>x=x.transpose(0,1)
>>>x.shape
torch.Size([3,2])
```

* **cat: **concatenate mutiple tensors.

```python
>>> x = torch.zeros([2,1,3])
>>> y = torch.zeros([2,3,3])
>>> z = torch.zeros([2,2,3])
>>> w = torch.cat([x,y,z],dim=1)
>>>w.shape
torch.Size([2,6,3])
```

##### torch.nn

* Linear Layer(Full-connected Layer)，定义线性运算。

```python
nn.Linear(in_features,out_features)
```

举个例子，对于输入Tensor为* x 32，即任意行，32列。

经过

```python
nn.Linear(32,64)
```

输出Tensor为* x 64，即任意行，64列。

```python
>>>layer = torch.nn.Linear(32,64)
>>>layer.weight.shape
torch.Size([64,32])
>>>layer.bias.shape
torch.Size([64])
```

<img src="Picture\2022-01-20_192007.png" style="zoom:38%;" />

我们设W为64 * 32的矩阵，输出的y为1 * 64

##### torch.optim

* Optimization algorithms for neural networks (gradient descent)
* Stochastic Gradient Desent(SGD)

```python
torch.optim.SGD(params , lr , momentum = 0)
```

