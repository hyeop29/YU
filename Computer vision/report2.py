# 주어진 RGB 칼라 영상을 YCbCr 로 변환하는 프로그램
# 변환된 YCbCr 을 다시 RGB 칼라 영상으로 변환하는 프로그램 작성
import cv2
import numpy as np

original = cv2.imread("21812248.jpg") # 윈도우 배경화면 사진 original에 저장 
cv2.imshow("original_img",original) # 원영상 출력

# cvtColor 함수 사용 변환
ycbcr_cvtColor = cv2.cvtColor(original, cv2.COLOR_BGR2YCR_CB) # cvtColor 함수를 이용하여 BGR 색상 공간 -> YCrCb 공간

cv2.imshow("YCbCr_cvtColor", ycbcr_cvtColor) # YCbCr 영상 출력

Y, Cr, Cb = cv2.split(ycbcr_cvtColor) # OpenCV에서는 YCbCr의 순서가 아닌 YCrCb의 순서로 인식
cv2.imshow("Y_cvtColor", Y) # Y 영상 출력

RGB_cvtColor = cv2.cvtColor(ycbcr_cvtColor, cv2.COLOR_YCrCb2BGR) # cvtColor 함수를 이용하여 YCrCb 색상 공간 -> BGR 공간 
cv2.imshow("RGB_cvtColor",RGB_cvtColor) # 복원된 RGB 영상 출력


# 수식을 이용하여 직접 구현
height, width, channel = original.shape
#원본 사진의 행, 열, 채널 값을 받아옴

# openCV는 B, G, R 순서로 불러온다
B = original[...,0]
G = original[...,1]
R = original[...,2]

# y, cb, cr의 값을 구하기 위해 빈 영상을 만들어준다.
Y = np.zeros((height, width), dtype=np.float)
Cr = np.zeros((height, width), dtype=np.float)
Cb = np.zeros((height, width), dtype=np.float)

# HD 모니터이므로 HDTV 공식 사용

for i in range(height):
    for j in range(width):      
        Y[i][j] = 0.183 * R[i][j] + 0.614 * G[i][j] + 0.062 * B[i][j] + 16
        Cb[i][j] = -0.101 * R[i][j] - 0.338 * G[i][j] + 0.439 * B[i][j] + 128
        Cr[i][j] = 0.439 * R[i][j] - 0.399 * G[i][j] - 0.040 * B[i][j] + 128

out = (np.dstack((Y, Cr, Cb))).astype(np.uint8) # 합쳐진 영상을 만든다

cv2.imshow("YCbCr_formula", out) # YCbCr 영상 출력

Y1, Cr2, Cb3 = cv2.split(out) # Y, Cr, Cb 구분
cv2.imshow("Y_formula", Y1) # Y 영상 출력

# R, G, B의 값을 구하기 위해 빈 영상을 만들어준다.
R = np.zeros((height, width), dtype=np.float)
G = np.zeros((height, width), dtype=np.float)
B = np.zeros((height, width), dtype=np.float)

for i in range(height):
    for j in range(width):
        R[i][j] = 1.164 * (Y[i][j] - 16) + 1.793 * (Cr[i][j] - 128)
        G[i][j] = 1.164 * (Y[i][j] - 16) - 0.534 * (Cr[i][j] - 128) - 0.213 * (Cb[i][j] - 128)
        B[i][j] = 1.164 * (Y[i][j] - 16) + 2.115 * (Cb[i][j] - 128)

out = (np.dstack((B, G, R))).astype(np.uint8) # 합쳐진 영상을 만든다

cv2.imshow("RGB_fromula", out) # 복원된 RGB 영상 출력

# 키입력 후 종료되도록
cv2.waitKey(0)
