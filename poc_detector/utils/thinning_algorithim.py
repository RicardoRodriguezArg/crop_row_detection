import cv2
import numpy as np

def neighbours_vec(image):
    return image[2:,1:-1], image[2:,2:], image[1:-1,2:], image[:-2,2:], image[:-2,1:-1],     image[:-2,:-2], image[1:-1,:-2], image[2:,:-2]

def transitions_vec(P2, P3, P4, P5, P6, P7, P8, P9):
    return ((P3-P2) > 0).astype(int) + ((P4-P3) > 0).astype(int) + \
    ((P5-P4) > 0).astype(int) + ((P6-P5) > 0).astype(int) + \
    ((P7-P6) > 0).astype(int) + ((P8-P7) > 0).astype(int) + \
    ((P9-P8) > 0).astype(int) + ((P2-P9) > 0).astype(int)

def zhangSuen_vec(image, iterations):
    for iter in range (1, iterations):
        print iter
        # step 1    
        P2,P3,P4,P5,P6,P7,P8,P9 = neighbours_vec(image)
        condition0 = image[1:-1,1:-1]
        condition4 = P4*P6*P8
        condition3 = P2*P4*P6
        condition2 = transitions_vec(P2, P3, P4, P5, P6, P7, P8, P9) == 1
        condition1 = (2 <= P2+P3+P4+P5+P6+P7+P8+P9) * (P2+P3+P4+P5+P6+P7+P8+P9 <= 6)
        cond = (condition0 == 1) * (condition4 == 0) * (condition3 == 0) * (condition2 == 1) * (condition1 == 1)
        changing1 = np.where(cond == 1)
        image[changing1[0]+1,changing1[1]+1] = 0
        # step 2
        P2,P3,P4,P5,P6,P7,P8,P9 = neighbours_vec(image)
        condition0 = image[1:-1,1:-1]
        condition4 = P2*P6*P8
        condition3 = P2*P4*P8
        condition2 = transitions_vec(P2, P3, P4, P5, P6, P7, P8, P9) == 1
        condition1 = (2 <= P2+P3+P4+P5+P6+P7+P8+P9) * (P2+P3+P4+P5+P6+P7+P8+P9 <= 6)
        cond = (condition0 == 1) * (condition4 == 0) * (condition3 == 0) * (condition2 == 1) * (condition1 == 1)
        changing2 = np.where(cond == 0)
        image[changing2[0]+1,changing2[1]+1] = 0
    return image

if __name__ == "__main__":
    image = cv2.imread("/home/operador/Documentos/_row_image_1_gimp.jpeg")
    #image = cv2.threshold(image, 100, 255, cv2.THRESH_BINARY)
    print image
    #image = cv2.bitwise_not(image)
    
    #se1 = cv2.getStructuringElement(cv2.MORPH_RECT, (2,2))
    #se2 = cv2.getStructuringElement(cv2.MORPH_RECT, (1,1))
    #mask = cv2.morphologyEx(image, cv2.MORPH_CLOSE, se1)
    #mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, se2)
    #image = image * mask
    
    #mask = np.dstack([mask, mask, mask]) / 255
    
    
    kernel = np.ones((4,4), np.uint8) 
    img_dilation = cv2.dilate(image, kernel, iterations=1)
    #img_dilation = zhangSuen_vec(image, 2)
    
    edges = cv2.Canny(img_dilation,20,30)
    minLineLength = 7
    maxLineGap = 5
    lines = cv2.HoughLinesP(edges,1,np.pi/180,2,np.array([]),minLineLength,maxLineGap)
    print lines[0]
    for line in lines:
        for x1,y1,x2,y2 in line:
            cv2.line(image,(x1,y1),(x2,y2),(0,255,0),1)
    
    cv2.imshow('thiing image',edges)
    cv2.imshow('image',image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()