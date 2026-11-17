import cv2
import numpy as np
import os
import sys


def sobel_x_convolution(image_path):
    """
    使用指定的 Sobel X 模板对灰度图像进行卷积操作。
    """
    # 检查文件是否存在
    if not os.path.exists(image_path):
        print(f"错误：找不到文件路径 '{image_path}'。请确保文件存在。")
        sys.exit(1)

    # 1. 以灰度模式加载图像
    # cv2.IMREAD_GRAYSCALE 确保图像是单通道（灰度图）
    src_image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

    if src_image is None:
        print(f"错误：无法加载图像 '{image_path}'。")
        print("这可能由文件损坏、路径问题或 OpenCV 解码器问题引起。")
        sys.exit(1)

    # --- 卷积核心部分 ---

    # 2. 定义作业中给出的模板（Sobel X 算子）
    # 在 numpy/OpenCV 中，模板通常定义为浮点型
    kernel = np.array([
        [-1, 0, 1],
        [-2, 0, 2],
        [-1, 0, 1]
    ], dtype=np.float32)

    # 3. 执行模板运算 (2D 卷积)
    # cv2.filter2D() 执行卷积操作
    # cv2.CV_16S (或 -1) 指定输出深度。使用 CV_16S 以保留负梯度值。
    grad_x = cv2.filter2D(src_image, cv2.CV_16S, kernel)

    # 4. 输出结果图像（可视化处理）
    # 由于梯度包含负值，需要取绝对值并转换回 8 位整数 (0-255) 才能正确显示
    abs_grad_x = cv2.convertScaleAbs(grad_x)

    # --- 显示和保存 ---

    output_filename = "result_sobel_x.png"
    cv2.imwrite(output_filename, abs_grad_x)

    print(f"卷积完成！结果已保存为 '{output_filename}'")

    # 显示图像
    cv2.imshow("Original Grayscale Image", src_image)
    cv2.imshow("Convolution Result (Sobel X - Vertical Edges)", abs_grad_x)

    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    image_file = "test_clean.jpg"

    print(f"正在尝试使用模板运算处理图像：{image_file}")
    sobel_x_convolution(image_file)