从0开始以c++尝试极朴素思路机器学习，闭门造车，暂时不看网课教材
以下是相关思考：
不借助其他参考信息，那么尝试编写人工智能的朴素思路应该是模拟人脑。
我管正在编写的小程序叫“小林”。
----------------------------------------------------------------------------------
我提取了一些简单的模块和步骤，类似程序三环节，接收信息、处理信息、输出信息。
接受信息首先是编码，这里只需要把汉字和英文等进行区分，随后对每一个字进行编码，用整型进行存储。这样一来，机器就可以不考虑其中具体字符内容，而仅仅处理不同id的组合。
编码后的问题是信息以什么形式进行存储，我这里的想法是使用键值对，维护一个字表，每个字有对应的其他每个字的联系表，这就是字与字的联系。我当然知道字与字之间的联系或许并不是简单的一维链接，但目前只想做一个最简单的，因此我仅仅使用距离来衡量一句话中两个字的联系。
----------------------------------------------------------------------------------
目前的进展是逻辑上大致没问题，但到对每个字联系表排序来组词这个步骤的优化中出现了问题，那就是似乎出现了内存泄露。输入1212，其中的排序结果子表中出现了空值。经过排查，map转vector过程中首末长度发生了异常改变。等等，我好像知道了。
我是sb，我在访问的时候没注意边界，让其越界访问，导致给map数组创造了没定义的空间。废了，这个问题改了我两小时，回去又得少打两小时王者。
收工，明天的计划是写注意力机制，如果有时间就准备生成了。
----------------------------------------------------------------------------------
1.13，今天写了注意力，思路是统计字出现的频率，出现最高的就是关键字。但实际上，根据运行结果，全部都是的的的我我我你你你在在在。我想这和婴儿一样，首先也是注意到某个词的频率特别突出，然后就可以先单独学习该词，就像牙牙学语时不断重复的“爸爸妈妈”。小孩子会对爸爸妈妈认错，因此需要不断矫正，这个过程中涉及到对提取的关键字的建模，那么我将再划一块叫做“理解”的区域给他存这些达到建模指标的东西。
![image](https://github.com/user-attachments/assets/3093f24f-7153-425a-8a6f-207c91390763)
----------------------------------------------------------------------------------
理解学习的地方先不写，我再好好想想。先把按字搜索句链的部分写了，现在勉强可以看作是在胡乱说着一些词，而不再是只能说几个词了。
