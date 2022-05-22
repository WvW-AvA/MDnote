## Classification

#### Description

<img src="Picture/2021-07-19_184405.png" alt="img" style="zoom:50%;" />

<img src="Picture/2021-07-19_184731.png" alt="img" style="zoom:50%;" />

There are two ways to define your function. Logistic Regression and Generation.

#### Bayes Probability 

As for binary classification problem,The key to knowing which class the target belongs to is calculating its Bayes Probability between two class.

The fallowing picture show the Bayes Formula.

<img src="Picture/2021-07-19_184756.png" alt="img" style="zoom:50%;" />

<img src="Picture/2021-07-19_184818.png" alt="img" style="zoom:50%;" />

However, There are some problems about how to calculate the probability that pick x from C1.(P(x|C1)).

Because the C1 isn't a continuous area,so we have to find a method to get a area form discrete date.

#### Gaussian Distribution



<img src="Picture/2021-07-19_184933.png" alt="img" style="zoom:50%;" />

<img src="Picture/2021-07-19_185016.png" alt="img" style="zoom:50%;" />

##### Combine Bayes Probability and Gaussian Distribution

<img src="Picture/2021-07-20_230042.png" alt="img" style="zoom:50%;" />

#### Optimization

We can try to let two classes share the same covariance,because the covariance is the square of the variance,Sometimes it will seems too large and effect the result.

The new covariance is the weighted overage between two covariance.

<img src="Picture/2021-07-20_233321.png" alt="img" style="zoom:50%;" />

 Now we can simplify our function.

##### Mathematical derivation

<img src="Picture/2021-07-20_233706.png" alt="img" style="zoom:50%;" />

<img src="Picture/2021-07-20_233725.png" alt="img" style="zoom:50%;" />

<img src="Picture/2021-07-20_233746.png" alt="(img)" style="zoom:50%;" />

<img src="Picture/2021-07-20_233858.png" alt="img" style="zoom:50%;" />

Now we get our finally function,It is interesting that the result seems like a linear model.

So that we can writer out our finally function as fallow.

<img src="Picture/2021-07-20_233945.png" alt="img" style="zoom: 50%;" />

#### The difference between Logistic Regression and Generative

Now there are two ways to training our model,

we can calculate it as a linear mode and train w and b directly, it was named Logistic Regression

Another way is calculate it as a model whose parameters is <img src="Picture/2021-07-20_235657.png" alt="img" style="zoom: 35%;" /> ,It was called Generative.

