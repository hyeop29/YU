# 영상 데이터를 불러와서 화면에 디스플레이하는 프로그램 작성
import numpy as np
import cv2

imgfile = '21812248.jpg'
img = cv2.imread(imgfile, cv2.IMREAD_COLOR)

cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
