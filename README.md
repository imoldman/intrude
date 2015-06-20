# intrude

## 什么是intrude

由于各种原因，iOS越狱现状越来越满足不了实际需求。但有时候我们又想研究某第三方`App`的实现，因此如何在一个非越狱`iOS`设备上实现这个目的就变成了一个需要解决的需求。`intrude`的设计初衷就是用来做这个事情的。

`intrude`是一个小巧的工具，其作用是在未越狱机器上给一个`iOS App`嵌入一个或多个`dylib`。

## 如何使用

1. 首先该工具只能运行在`Mac OS X`系统上，因此你得准备一台`Mac`。

1. 将目标`App`从目标设备上导出，成`ipa`文件。

1. 使用如下命令将`/path/to/bar.dylib`嵌入到`/path/to/foo.ipa`中
	
		./intrude --ipa       "/path/to/foo.ipa" \
	              --dylib     "/path/to/bar.dylib" \
	              --bundle    "li.oldman.test"
	              --sign      "iPhone Developer: Oldman Li (QNRMA23W53)" \
	              --provision "/path/to/li.oldman.test.mobileprovision"
	
	其中，`bundle`, `sign`, `privision` 为嵌入过程所必须的重签名参数，这三者必须互相对应
	
1. 上步骤会生成一个ipa文件`/path/to/foo.ipa.modified.ipa`，此`ipa`文件即包含了`bar.dylib`, 将其重新导入设备即可。

## 已知问题

1. 注意，原始`ipa`中可执行二进制文件必须为无加密版本（即俗称的砸壳版本）。

1. 简易起见，目前本工具重新生成`ipa`文件时未将`Plugins`目录包含在内。


## 实现原理
如果你对实现原理感兴趣，这里的简短说明可以作为参考。

本质上，一个二进制文件需要依赖哪些`dylib`，这些信息是记录在`Mach O`结构中的。而`intrude`便是改写了`Mach O`结构，增加了一条加载`dylib`的指令，使之能够在运行时即加载它。这部分实现可参阅[这里](https://github.com/imoldman/intrude/tree/master/src/insert_dylib_to_macho/insert_dylib_to_macho)。
