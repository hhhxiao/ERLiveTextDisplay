# 法环直播文本信息展示(暂定名)

## 介绍

本 MOD 允许在 OBS 上展示玩家数据（目前仅支持死亡次数）。基本原理为定期扫描法环的内存然后读取需要的数据并写入到文本文件中。

## 使用教程

- 将 ERLiveDisplay.dll,er_live_text_display.json 放到任意目录（同一目录即可）
- 编辑 Modengine 的 config_eldenring.toml,在 external_dlls 内补上 ERLiveDisplay.dll 的完整路径
- 启动游戏并稍作等待，如果成果加载的话 dll 所在目录会生成一个文本文件`data.txt`
- 启动 OBS,添加文本(GDI+)数据源，选择从文件读取，然后选择 MOD 生成的 data.txt 即可。

## 配置

```txt
{
    "debug_mode": false, //是否开启调试模式（会生成黑窗）
    "fmt_string": "Death Count:{death_count}\nToday Death Count: {today_death_count}", //OBS内显示的文本格式（{}内的内容会被自动替换成实际的值，请勿修改）
    "refresh_cycle": 2, //内存查询频率，单位是s
    "data_file": "",//生成的文本文件的路径，默认在dll所在目录生成名为data.txt
    "correction": {
        "death": 0 //今日死亡次数修正值
    }
}
```
