
# Assignment list
- 实现了castRay()函数，包含了路径追踪，对光源颜色的处理（白色），直接光照和间接光照的渲染方程，引入RR概率控制光线弹射等等。
- 在ray generation阶段使用了多线程，并对framebuffer进行锁控制

# Multi-Thread Result
normal：
- 8 SPP, 512\*512, time: 73s
- 16 SPP, 784\*784, time: 413s

multi-thread：
- 8 SPP, 512\*512, time: 89s
- 16 SPP, 784\*784, time: 362s

看起来采样点变多才能体现出多线程的优势。。。

