# Editor Utility Widget 本地化切换指南

## 📋 概述

本指南说明如何在 Editor Utility Widget (EUW) 中实现编辑器语言切换时自动更新文本。

---

## 🔧 设置步骤

### 1️⃣ **创建本地化数据**

首先，你需要创建本地化表（Localization Table）：

#### 方法A：使用 CSV 文件（推荐）

1. 在 `Content/Localization/Game` 目录下创建 CSV 文件
2. 格式如下：

```csv
Key,SourceString,Comment,ru,fr,zh-Hans
"MainMenu_Title","Main Menu",标题文字,"Главное меню","Menu Principal","主菜单"
"Settings_Audio","Audio Settings",音频设置,"Настройки звука","Paramètres audio","音频设置"
"Button_Start","Start Game",开始游戏按钮,"Начать игру","Démarrer le jeu","开始游戏"
```

3. 在编辑器中导入 CSV：
   - 右键点击 Content Browser
   - 选择 "Import to /Game/..."
   - 选择你的 CSV 文件
   - 设置 Localization Target

#### 方法B：使用代码中的 NSLOCTEXT

在你的 C++ 代码中定义：

```cpp
#define LOCTEXT_NAMESPACE("MyEditorWidget")

// 定义本地化文本
FText TitleText = NSLOCTEXT("MyEditorWidget", "MainMenu_Title", "Main Menu");
FText ButtonText = NSLOCTEXT("MyEditorWidget", "Button_Start", "Start Game");

#undef LOCTEXT_NAMESPACE
```

---

### 2️⃣ **在 Blueprint 中使用**

#### **在 Editor Utility Widget 的 Event Construct 中：**

```
Event Construct
    │
    ├─► Register Editor Utility Widget For Localization (Self)
    │
    └─► [你的其他初始化逻辑]
```

#### **在 Event Destruct 中：**

```
Event Destruct
    │
    └─► Unregister Editor Utility Widget For Localization (Self)
```

#### **获取本地化文本：**

有两种方式：

**方式1：直接使用 FText 变量（推荐）**

1. 在 EUW 中创建 FText 类型的变量
2. 在细节面板中，你可以：
   - 直接输入文本（会自动成为本地化源文本）
   - 或者通过代码设置

**方式2：通过本地化表查找**

```
Event Construct
    │
    ├─► Get Localized Text
    │     ├─ Table ID: "Game"
    │     ├─ Key: "MainMenu_Title"
    │     └─ Namespace: "" (可选)
    │
    └─► Set Text (Your Text Block) → Return Value
```

---

### 3️⃣ **配置项目本地化**

编辑 `Config/DefaultGame.ini`：

```ini
[Internationalization]
; 设置默认文化
Culture=en

; 添加支持的语言
+SupportedCultures=en
+SupportedCultures=zh-Hans
+SupportedCultures=ja
+SupportedCultures=ko

; 本地化路径
+LocalizationPaths=%GAMEDIR%Content/Localization/Game
```

编辑 `Config/DefaultEditor.ini`：

```ini
[Internationalization]
; 编辑器也使用相同的本地化路径
+LocalizationPaths=%GAMEDIR%Content/Localization/Game
```

---

### 4️⃣ **生成和收集本地化文本**

#### **步骤1：收集需要本地化的文本**

1. 打开 **Window → Developers → Localization Dashboard**
2. 点击你的项目目标
3. 点击 **"Gather Text"** 按钮
4. 这会扫描所有 Blueprint 和 C++ 代码中的本地化文本

#### **步骤2：导出翻译**

1. 在 Localization Dashboard 中
2. 选择要翻译的语言（如 zh-Hans）
3. 点击 **"Export"** 生成 `.po` 文件
4. 将 `.po` 文件发送给翻译人员或使用翻译工具

#### **步骤3：导入翻译**

1. 翻译完成后，将 `.po` 文件放回原位置
2. 在 Localization Dashboard 中点击 **"Import"**
3. 点击 **"Compile"** 生成 `.locres` 文件

---

### 5️⃣ **测试语言切换**

#### **在编辑器中切换语言：**

1. **方法1：通过编辑器设置**
   - Edit → Editor Preferences
   - General → Region & Language
   - 更改 Language 选项
   - 重启编辑器

2. **方法2：通过命令行**
   ```bash
   UnrealEditor.exe -culture=zh-Hans
   ```

3. **方法3：动态切换（运行时）**
   ```cpp
   // 在 C++ 中
   FInternationalization::Get().SetCurrentCulture(TEXT("zh-Hans"));
   ```

当你切换语言后，所有注册的 Editor Utility Widget 应该自动更新文本！

---

## 💡 高级用法

### **自定义刷新逻辑**

如果你需要更精细的控制，可以在 EUW 中创建自定义事件：

```
Custom Event: RefreshLocalizedTexts
    │
    ├─► Get Localized Text ("MainMenu_Title") → Set Text (TitleBlock)
    ├─► Get Localized Text ("Button_Start") → Set Text (StartButton)
    └─► Get Localized Text ("Settings_Audio") → Set Text (AudioLabel)
```

然后在 C++ 中调用这个事件而不是重建整个 widget。

### **使用 DataTable 管理本地化键**

创建一个结构体：

```
Struct: FLocalizationKeyPair
    ├─ Key (FName)
    └─ Description (FText)
```

创建 DataTable，然后在 EUW 中通过 Key 查找对应的 FText。

---

## ⚠️ 常见问题

### Q1: 文本没有自动更新？

**检查清单：**
- ✅ 确认在 Event Construct 中调用了 Register
- ✅ 确认使用的是 FText 而不是 FString
- ✅ 确认 .locres 文件已正确编译
- ✅ 确认 Culture 名称正确（如 "zh-Hans" 而不是 "zh"）

### Q2: 如何查看当前加载的本地化资源？

在输出日志中搜索：
```
LogInternationalization: Display: Loading localization resources for culture: zh-Hans
```

### Q3: 编辑器重启后文本恢复为英文？

确保：
1. `.locres` 文件存在于正确的目录
2. `DefaultGame.ini` 中配置了正确的 Culture
3. 没有其他地方强制设置为英文

---

## 📁 文件结构示例

```
YourProject/
├── Config/
│   ├── DefaultGame.ini          # 包含 Internationalization 配置
│   └── DefaultEditor.ini        # 编辑器本地化配置
├── Content/
│   └── Localization/
│       └── Game/
│           ├── en/
│           │   └── Game.locres
│           ├── zh-Hans/
│           │   └── Game.locres
│           └── ja/
│               └── Game.locres
├── Source/
│   └── YourModule/
│       ├── Public/
│       │   └── EditorUtilityTextRefreshHelper.h
│       └── Private/
│           └── EditorUtilityTextRefreshHelper.cpp
└── ...
```

---

## 🎯 完整示例

### **Blueprint 节点连接示例：**

```
┌─────────────────────────────────────┐
│         Event Construct              │
└──────────────┬──────────────────────┘
               │
               ├──────────────────────────────┐
               │                              │
       ┌───────▼────────┐            ┌────────▼──────────┐
       │ Register EUW   │            │ Get Localized Text│
       │ For Loc (Self) │            │ Table: "Game"     │
       └────────────────┘            │ Key: "Title"      │
                                     └────────┬──────────┘
                                              │
                                     ┌────────▼──────────┐
                                     │ Set Text          │
                                     │ Target: TitleText │
                                     └───────────────────┘

┌─────────────────────────────────────┐
│          Event Destruct             │
└──────────────┬──────────────────────┘
               │
       ┌───────▼────────────────┐
       │ Unregister EUW For Loc │
       │ (Self)                 │
       └────────────────────────┘
```

---

## 🔗 相关资源

- [UE 官方文档 - 本地化](https://docs.unrealengine.com/en-US/localization/)
- [Localization Dashboard 教程](https://docs.unrealengine.com/en-US/localization-dashboard/)
- [FText vs FString](https://docs.unrealengine.com/en-US/text-localization-in-unreal-engine/)

---

## ✨ 总结

通过以上步骤，你的 Editor Utility Widget 现在可以：

✅ 在编辑器语言切换时自动更新文本  
✅ 支持多语言配置  
✅ 使用标准的 UE 本地化系统  
✅ 无需手动刷新或重启编辑器  

享受多语言编辑器开发吧！🎉
