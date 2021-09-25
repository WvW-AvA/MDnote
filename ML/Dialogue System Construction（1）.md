# Dialogue System Construction（1）

对话框是游戏中重要的一环，特别是在RPG中，玩家一般通过操控玩家和世界进行交互推进游戏。

在对话过程中，玩家会做出不同的选择，导致出现不同的对话内容。

如果对于每个选项都制作相应的选项Button，再通过Button进行语句分支的判断，程序员的工作量就非常的巨大，更何况还有选项套选项的操作，更加增加对话的复杂程度。

于是懒惰的程序员决定把制造分支的工作交给文案，然后通过解析文案剧本自动生成对话内容树，自动进行对话选项的生成。

### 大致架构

要实现的功能包括

* 文案语法解析

* 生成对话树

* 字符串显示（打字机式）

* 动态生成Option

* 推进对话

  在Unity中实现分为Prefab（预制体）的搭建和Class（类）的编程。构思后设计出如下架构。

![Dialogue System](D:\Xmind\Dialogue System.png)

### 文案的语法定义

 * 分支对话编写的格式：
 * 使用“#+分支名称”为分支开始的关键语句，“#Option End”为分支结束的关键语句
 * 注意：“#+分支名称”与“#Option End”必须成对出现，否则会报错
 * 允许分支内嵌套分支,支持缩进和空行，例如：
 * #团长，不要停下来啊
 * Dialog 1
 * #Option End
 * #我不做人啦
 * Dialog 2
 * #Option End
 * 这样会显示两个选项：
 * 团长，不要停下来啊
 * 我不做人啦
 * 这样玩家就可以通过选择不同的选项显示Dialog 1 或 Dialog 2

### Prefab的搭建

按照大致架构，搭建出对应的Prefab。

![image-20210614114607086](C:\Users\86159\AppData\Roaming\Typora\typora-user-images\image-20210614114607086.png)

![image-20210614114743750](C:\Users\86159\AppData\Roaming\Typora\typora-user-images\image-20210614114743750.png)

![image-20210614115540923](C:\Users\86159\AppData\Roaming\Typora\typora-user-images\image-20210614115540923.png)

Option,Option Box,Dialog Box,name,Skip 是UGUI的Button，Character是空物体。

并分别创建三个脚本，按照逻辑图中的虚线给对应的Prefab安上。

### 程序实现

程序分为三部分，写在三个类中。

Option Property：选项配置类，这个类主要用于检测玩家选择。

Display Sentence：单句解析并显示类，这个类主要用于对一句话进行解析并执行相关操作。

Text Logic：整体调控类，功能包括段落文本的逻辑重排，对话树的生成，推进对话等。

#### Text Logic

###### 初始化

既然要来写树，那么就需要确立节点。

```c#
[System.Serializable]
public class TextNode
{
	public List<string> sentences;//节点存储的一段对话
	public List<TextNode> options;//节点存储的子支节点
    public TextNode parent;//节点的父节点
    public int pointer=0;、、
}
```

创建两个TextNode类型的变量，一个叫根节点（root），一个叫当前节点（current）。

一大段对话本质上就是一串超长的字符串，先将其按行分割成字符串类型的数组，字符串串？

```c#
    public string Talker;
	public TextAsset source;//从硬盘中读出的.txt类型的对话文本
	public TextNode root;
	private  string str;
    private string[] strs;
    public TextNode curr;
    public bool isSelect=true,isActive=false;
    public GameObject OptionPrefab;
    public  GameObject OptionBox;
    private  GameObject Option_Box;
```



遍历字符串串中的每个元素，以root为根节点生成对话树。

```c#
   private void textTransform()
    {
        for(int i=0;i<strs.Length;i++)
        {
            strs[i] = strs[i].Trim();
            if (strs[i] != string.Empty)
            {
                if (strs[i][0] == '#')
                {
                    if (!strs[i].Contains("#Option End"))
                    {
                        curr.sentences.Add(strs[i]);
                        curr.options.Add(new TextNode());// 新增子节点
                        curr.options[curr.options.Count - 1].parent = curr;//设置子节点的父节点
                        curr = curr.options[curr.options.Count - 1];//进入子节点
                        curr.sentences = new List<string>();
                        curr.options = new List<TextNode>();
                    }
                    else//跳出节点
                    {
                        if (curr.parent != null)
                            curr = curr.parent;
                        else
                        {
                            curr = root;
                        }
                    }
                }
                else
                {
                    curr.sentences.Add(strs[i]);
                }
            }
        }
    }
```

以上就是初始化的全部内容,	全部整合到一个方法中。

```c#
    public void reStart()
    {
        root.options = new List<TextNode>();
        root.sentences = new List<string>();
        root.pointer = 0;
        str = source.text;
        strs = str.Split('\n');
        curr = root;
        textTransform();
    }
```

到此为止，我们就完成了文本的逻辑重排和对话内容树的生成。 不过这才是刚刚开始，







