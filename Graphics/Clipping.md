## Clipping
- - -
`Canonical Viewing Volume`밖에 있는 물체들을 제거하기, top, bottom, right, left 순서로 자른다.  
Vertices 수가 굉장히 많으면 모든 Vertex를 GPU로 보내는 것이 말이 안됨. 실제로 보면 유저의 `View Frustrum`에 있는 것만 살아남.  
이걸 보내기 전에 걸러서 보내주기 않는 것은 `Scene Graph`의 역할이다.  
전부 들어오면 accept, 전부 벗어나면 reject, 걸쳐있으면 detailed clipping을 시행한다.
