1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The server will put the EOF character after completing the response so the client can start processing after receiving that EOF character. The way I handled my recv() is I keep looping to recv the bytes until it sees an EOF. That way we can handle partial reads or ensure complete message transmission.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

If we don't want to use the start and end techniques we used in our assignment, we can use structured headers to indicate start and end of messages. One of the challenge here is both the server and client should have predefined header agreement between them. You can implement the length byytes of the message or you can even create your own method for start and end of message. If this is not handled correctly, there would be instances where the messages is not fully received or the server/client keeps waiting for the message to finish.

3. Describe the general differences between stateful and stateless protocols.

Stateful Protocols: Maintain session information between requests as the server keeps track of the clients. If there is a disconnection, resumption is possible. TCP is a stateful protocol.
Stateless Protocols: Do not maintain session information between requests as every requent is treated independently. UDP is a stateless protocol.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

During our leture, the professor told us that TCP is more reliable but slower than UDP because it makes sure the message is fully received. However, when we are doing real-time communication where delays should not occur, UDP should be used. This gives us a convenient and understandable connection protocol where some lost bytes can be forgiven.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The operating system provides c ru time functions such as socket(), listen(), bind(), connect(), send(), recv(), close() to use network communications.