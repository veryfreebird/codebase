import numpy as np
import cv2 as cv
# 创建一个黑色的图像
img = np.zeros((512,512,3), np.uint8)
# 画一条 5px 宽的蓝色对角线

cv.line(img,(0,0),(511,511),(255,0,0),5)
#cv.rectangle(img,(384,0),(510,128),(0,255,0),3)
#cv.circle(img,(447,63), 63, (0,0,255), -1)
#cv.ellipse(img,(256,256),(100,50),0,0,180,255,-1)
#pts = np.array([[10,5],[20,30],[70,20],[50,10]], np.int32)
#pts = pts.reshape((-1,1,2))
#cv.polylines(img,[pts],True,(0,255,255))