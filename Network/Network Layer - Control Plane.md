## Network Layer Function

- - -
transport segment from sending to receiving `host + router`, transport, application layer과는 다르다  
네트워크 레이어는 `forwarding(data plane)`, `routing(control plane)` 두 가지 기능을 제공한다.

- ### control plane
	- per-router control (traditional)  
	  모든 라우터에 라우팅 알고리즘이 존재하고, 서로 메세지를 주고받는다. (topology)  
	  상태 변화를 제대로 알려주지 못하면 `routing loop`같은 문제가 생길 수 있다  
	- logically centralized control (software defined network)      
	  논리적으로 하나의 컨트롤러라 존재하고, 하나의 컨트롤러가 모든 라우터의 요청을 처리한다. 라우터는 자신의 정보를 `remote controller`  
	  에게 알려준다. 이를 알려주는 것을 `control agent(CA)`라고 한다. cf) 테이블 자체를 여러개 있음
		- pros 하나의 topology로 forwarding table을 작성하기 때문에, 상태 변화를 처리하기 용이하다.
		- cons 전시에 불리하다.?
- - - 
- ### Routing Protocols
	- 네트워크를 그래프로 추상화하여 최단 비용, 최대 속도, 최소 혼잡 경로를 찾는다.
	- `global(link state algorithm)`, `decentralized(distance vector)` : static, dynamic으로 크게 구별 가능하다.
	- link-state algorithm(다익스트라 알고리즘)  
	  `link state boradcast(flooding)`를 통해 구현된다, 부정확한 정보가 미치는 영향이 상대적으로 제한적이다.  
	  oscillations possible -> link cost는 traffic에 비례해서는 안된다.
	- distance vector algorithm(Bellman-Ford Algorithm)  
	  라우터가 저장하고 있는 distance vector들을 이용하여 경로를 찾는다. -> 자기 자신과 이웃들이 가지고 있는 distance vector를 이용.  
	  각각의 node는 변경될 때문 dv를 다른 노드에 알려주기만 하면 된다. 뭔가 날아보면 dv 다시 계산하면 됨  
	  얼마나 빨리 수렴할까 --> `good news travels fast`, `count-to-infinity problem`  
	  부정확한 정보가 넓은 범위에 영향을 미침
- - -
- ### Making Routing Scalable
	- 라우터들을 묶은 것을 `autonomous system(AS) a.k.a. domain`라고 한다.  
	- intra-AS routing
	  - 모든 내부 라우터는 같은 intra-domain 프로토콜을 사용한다.
	  - gateway router: 다른 AS와 연결되는 router(s)
	  - 내부 모든 라우터에 `reachability`를 전달한다.
	- inter-AS routing (Gateway Router가 실행)
	  - known as `interior gateway protocols (IGP)`
	  - RIP (Routing Information Protocol)
	  - OSPF (Open Shortest Path First, IS-IS)
	  - IGPR (Interior Gateway Routing Protocol, Cisco proprietary)
	- OSPF (Internal AS Routing)
	  - Link-State Algorithm
	  - IP 바로 위에서 동작한다. (TCP/UDP에서 동작 안함;;)
	  - OSPF는 암호가 틀리면 메세지를 받을 수 없다
	  - 같은 코스트의 여러 path가 허용됨 --> 여러개의 output port로 나갈 수 있음
	  - TOS에 따라서 cost를 다르게 할 수 있다.
	  - 멀티캐스트 가능(여러 개의 dst로 전달, broadcast와는 다르다)
	  - 계층구조 적용 가능
	- BGP (Inter AS Routing)
	  - eBGP (obtain reachability information from neighboring AS)
	  - iBGP (propagate reachability information to all AS-internal router) (same as eBGP!)
	  - BGP Session (TCP, Semi-Permanent): path vector를 전달함 (AS들의 리스트)
	    - destination prefix + attributes = route ex) (AS3, X) -> (AS2 AS3, X)
		- AS-PATH (attribute): 지나온 경로
		- NEXT-TOP (attribute): internal-AS 라우터 지정
		- import policy, export policy가 존재한다.
	  - BGP Message
		- OPEN: TCP 연결 설정
		- UPDATE: 새로운 경로 알려줌
		- KEEPALIVE: TCP 안 끊어지게
		- NOTIFICATION: 에러 전달, 연결 종료
	  - BGP Route Selection
		- policy decision (local preference value attribute)
		- shortest AS-PATH
		- closest NEXT-HOP (hot potato: 목적지가 존재하지 않는 AS에 패킷이 오래 있을 이유가 없음)
		- additional criteria
	- Difference
		- intra-AS는 policy 적용 안됨, 성능을 최우선으로 생각함.
- - -
- ### SDN Control Plane
- - -
- ### ICMP: Internet Control Message Protocol
  - error reporting (unreachable host, network, port, protocol)
  - IP 위에서 동작한다, type, code + IP datagram의 처음 8바이트(, packet ID) 를 사용한다.
  - Traceroute and ICMP: TTL을 점점 증가시키는 방법 (11, 0: TTL expired)
- ### Network management and SNMP
  - Autonomous System은 정말 많은 하드웨어와 소프트웨어의 상호작용을 모니터링해야한다.
  - `MIB(Management Information Base)`가 Management Device에 전달된다.
  - SNMP(Simple Network Management Protocol): 전혀 simple 하지 않음
	- request mode
	- trap mode