# report3_이창협_21812248
# RGB (원본) 과 RGB 칼라 영상(복원) 의 PSNR 구하는 프로그램 작성
import cv2
import numpy as np
## RGB(원본) => YCbCr => RGB(복원)
original = cv2.imread("21812248.jpg") # 윈도우 배경화면 사진 original에 저장 
# cvtColor 함수 사용 변환
ycbcr_cvtColor = cv2.cvtColor(original, cv2.COLOR_BGR2YCR_CB) # cvtColor 함수를 이용하여 BGR 색상 공간 -> YCrCb 공간
RGB_cvtColor = cv2.cvtColor(ycbcr_cvtColor, cv2.COLOR_YCrCb2BGR) # cvtColor 함수를 이용하여 YCrCb 색상 공간 -> BGR 공간 ==> 복원
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
Y1, Cr2, Cb3 = cv2.split(out) # Y, Cr, Cb 구분
# R, G, B의 값을 구하기 위해 빈 영상을 만들어준다.
R = np.zeros((height, width), dtype=np.float)
G = np.zeros((height, width), dtype=np.float)
B = np.zeros((height, width), dtype=np.float)
for i in range(height):
    for j in range(width):
        R[i][j] = 1.164 * (Y[i][j] - 16) + 1.793 * (Cr[i][j] - 128)
        G[i][j] = 1.164 * (Y[i][j] - 16) - 0.534 * (Cr[i][j] - 128) - 0.213 * (Cb[i][j] - 128)
        B[i][j] = 1.164 * (Y[i][j] - 16) + 2.115 * (Cb[i][j] - 128)
RGB_fromula = (np.dstack((B, G, R))).astype(np.uint8) # 합쳐진 영상을 만든다
### PSNR 구하기
# 함수로 구하기
print("opencv 함수를 통한 복원값 PSNR")
PSNR_func = cv2.PSNR(original, RGB_cvtColor)
print("구현 1 :")
print("OpenCV PSNR 함수를 이용하여 구현 : {:0.4f}" .format(PSNR_func))
# 수식으로 구하기
MSEr = np.mean((original[:, :, 0] - RGB_cvtColor[:, :, 0]) ** 2)
MSEg = np.mean((original[:, :, 1] - RGB_cvtColor[:, :, 1]) ** 2)
MSEb = np.mean((original[:, :, 2] - RGB_cvtColor[:, :, 2]) ** 2)
MSE = (MSEr + MSEg + MSEb) / 3
if MSE == 0:   # MSE가 0인 특별한 경우 처리
    PSNER_formula = 100 # 원본 이미지와 복구 이밎가 완전히 동일할 때는 가능한 최대 PSNR 값인 100으로 정의
MAXi = 255
PSNR_formula = 20 * np.log10(MAXi) - 10 * np.log10(MSE)
print("구현 2 :")
print("앞에서 주어진 수식을 이용하여 각자의 PSNR 구하는 함수를 직접 구현 : {:0.4f}" .format(PSNR_formula))

# 함수로 구하기
print("수식을 통한 복원값 PSNR")
PSNR_func = cv2.PSNR(original, RGB_fromula)
print("구현 1 :")
print("OpenCV PSNR 함수를 이용하여 구현 : {:0.4f}" .format(PSNR_func))
# 수식으로 구하기
MSEr = np.mean((original[:, :, 0] - RGB_fromula[:, :, 0]) ** 2)
MSEg = np.mean((original[:, :, 1] - RGB_fromula[:, :, 1]) ** 2)
MSEb = np.mean((original[:, :, 2] - RGB_fromula[:, :, 2]) ** 2)
MSE = (MSEr + MSEg + MSEb) / 3
if MSE == 0:   # MSE가 0인 특별한 경우 처리
    PSNER_formula = 100 # 원본 이미지와 복구 이밎가 완전히 동일할 때는 가능한 최대 PSNR 값인 100으로 정의
MAXi = 255
PSNR_formula = 20 * np.log10(MAXi) - 10 * np.log10(MSE)
print("구현 2 :")
print("앞에서 주어진 수식을 이용하여 각자의 PSNR 구하는 함수를 직접 구현 : {:0.4f}" .format(PSNR_formula))
