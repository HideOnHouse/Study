## Rasterization
- - -
`primitive`를 어떻게 `Pixel Set`으로 바꿀 것인가에 대한 내용  
`fragment`가 만들어 질 때는 `screen space`, `primitive`는 `clipping space`  
`primitive`에서 `fragment`를 만드는게 `rasterizer`가 할 일이며, `interpolation`으로 진행한다.  
## Interpolation
- - -
- Line Rasterization
    - DDA Algorithm  
    두점 사이의 기울기를 이용하여 그림, 1증가하면 y = m * 1 부분을 칠함 --> 기울기 크면 구멍뚫림 (역함수를 이용)
    - Bresenham's Line Algorithm-->요즘 쓰는 기법
- Polygon Rasterization
    - Bilinear Interpolation
    선의 픽셀 컬러(모든 vertex의 속성)를 채우고`r = (1 - t)p + tq`, `scan line`을 이용하여 나머지를 채운다  
    `SSAA` --> 픽셀 뻥튀기해서 그림   
      
## Hidden Surface Removal (Z-buffer Algorithm)
- - -
위와 똑같은 `interpolation`을 이용하여 depth 또한 계산할 수 있다.  
먼저 그린 depth보다 depth보다 클 경우 그 값을 덮어씌우지 않고 거른다. (색상 등을)
물체끼리의 depth 값이 일치할 경우 GL 설정을 통해 결정할 수 있다.
  - Combine shading and hidden surface removal through scan line algorithm
 
투명한 경우 계산하지 않고, `painter's algorithm`을 사용한다. 이때, Z 값의 sorting이 필요하다.  

## Hidden Surface Removal (Back-Face Removal)
- - -
-90 < theta < 90의 범위를 벗어나는 물체는 면이 보일리가 없다. (normal과 이루는 값)