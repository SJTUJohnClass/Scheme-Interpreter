# Extensions

选择写 extension 之前请跟 TA 联系。

此外， 对于你所写的 extension,  应当在最终提交的文件中附上关于 extension 的说明。

## Multi-thread
> 感谢 Wang Yuxuan 提出的建议。

多线程需要对你的 `shared.hpp` 进行一些修改。

首先， 在你的 `shared.hpp` 前加上

```
#ifndef PARALLEL_OPTIMIZE
typedef int count_type;
#else
typedef std::atomic<int> count_type;
#endif
```

然后把 `shared.hpp` 中用到的跟 `ref_count` 有关的 `int` 全部改为 `count_type`。

开启多线程优化的全局编译控制符为 PARALLEL_OPTIMIZE。