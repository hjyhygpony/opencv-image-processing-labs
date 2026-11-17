# OpenCV Image Processing Labs

数字图像处理课程实验：使用 Sobel X 卷积核提取灰度图像的水平边缘。

提供 Python/OpenCV 和 C++/OpenCV 两个版本。

## 实验内容

Sobel X 卷积核：

```text
[-1  0  1]
[-2  0  2]
[-1  0  1]
```

处理流程：

1. 以灰度模式读取图像；
2. 使用 `cv2.filter2D` 执行二维卷积；
3. 使用 `CV_16S` 保存负梯度；
4. 取绝对值并转换为 `CV_8U` 用于显示；
5. 保存结果并显示原图与边缘图。

## 目录

```text
opencv-image-processing-labs/
├─ python/
│  ├─ convolution_sobel.py
│  ├─ test_clean.jpg
│  └─ result_sobel_x.png
├─ cpp/
│  ├─ sobel_convolution.cpp
│  └─ Project1.sln
└─ README.md
```

## Python 运行

```powershell
python -m venv .venv
.\.venv\Scripts\Activate.ps1
pip install -r requirements.txt
cd python
python convolution_sobel.py
```

## C++ 运行

1. 安装 Visual Studio 2022 和 OpenCV。
2. 配置 OpenCV 的 include/lib 路径。
3. 打开 `cpp\Project1.sln` 编译。
4. 将 `test_clean.png` 放到程序工作目录。

## 结果

`python/result_sobel_x.png` 是已经生成的 Sobel X 处理结果。

## 说明

- 仓库不包含 OpenCV 安装包、虚拟环境、VS 缓存或实验报告。
- 图像只作为课程实验样例使用。
- 如果要处理透明 PNG，建议先转为灰度图或自行处理 alpha 通道。
