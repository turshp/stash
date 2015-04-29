# Hello, Markdown
-------

## 配置Sublime Text3
> * "ctrl+`"打开命令窗口，输入以下代码，安装Package Control：

    import urllib.request,os; pf = 'Package Control.sublime-package'; ipp = sublime.installed_packages_path(); urllib.request.install_opener( urllib.request.build_opener( urllib.request.ProxyHandler()) ); open(os.path.join(ipp, pf), 'wb').write(urllib.request.urlopen( 'http://sublime
    .wbond.net/' + pf.replace(' ','%20')).read())

> * `ctrl+shift+p`, 打开Package Control，输入`pci`，进入Package Control.
> * 安装Markdwon Preview和Markdown Editing。 