## Network Layer Function

- - -
transport segment from sending to receiving `host + router`, transport, application layer과는 다르다  
네트워크 레이어는 `forwarding(data plane)`, `routing(control plane)` 두 가지 기능을 제공한다.

## Two key network-layer functions

- - -

- data plane
	- 포워딩
	- local, per-router function
	- 라우터의 인풋 포트에서 어느 아웃풋 포트로 가야하는지를 결정한다
- control plane - network-wide logic
	- 데이터그램이 src->dst로 어떻게 가야 하는지를 결정
	- traditional routing algorithms
	- SDN (software-defined networking)

## Network Service Model

- - -

### Internet

- Best Effort
- No Guarantees
- No Congestion Feedback

### ATM

- C, V, A, U
- Guarantees available
- ABR only provide congestion feedback

# *Data plane*

- - -

## Router Architecture

- - -

### Input port Functions

- line termination physical layer: bit-level reception
- link layer protocol(receive)
  Ethernet
- lookup forwarding, queueing
	- 헤더의 값을 이용하여 인풋 메모리에 저장된 룩업 테이블을 보고 아웃풋 포트를 결정한다
	- 개빨라야됨
	- 포워딩 속도보다 데이터가 들어오는 속도가 빠를 수 있으므로 임시로 저장할곳이 필요하다, 요즘은 이 크기를 줄여서 타임아웃을 방지함
	- destination-based forwarding: 목적지 IP만으로 포워딩 가능해야됨
	- 헤더가 어떠한 값을 갖던 포워딩이 가능해야 한다

### Input Port Switching

- the longest prefix matching
	- 빠르게 하기 위해 TCAM (Ternary Content Addressable Memories)를 사용한다.
- Switching Fabrics
	- Memory: Speed limited by memory bandwidth (2 bus crossing per datagram)
	- Bus: via a shared bus, switching speed limited by bus bandwidth
	- Crossbar(Interconnection): fragmenting datagram into fixed length cells, switch cells through fabric

### Input Port Queueing

- Queueing delay and loss due to input buffer overflow
- HOL (Head Of the Line) blocking  
  queued datagram at front of queue prevents others in queue from moving forward

### Output Port Functions

- datagram buffer(queueing)
  datagram (packets) can be lost due to congestion, lack of buffers  
  `RTT * C / sqrt(N)  :  C = Link Capacity, N flows` 
- link layer protocol(send)
- line termination
- priority scheduling
	- FIFO: tail drop, priority, random
  	- Priority Scheduling
	- Round Robin: 
	- WFQ

# *IP (Internet Protocol)*
- - -
```
[transport layer: TCP, UDP]
[network layer][routing protocol: RIP, OSPF, BGP]
[network layer][ip protocol: addressing conventions, adtagram format, packet handling conventions]
[network layer][ICMP protocol: error reporting, router 'signal']
[link layer]
[physical layer]
```