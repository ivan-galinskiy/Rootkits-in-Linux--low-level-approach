c10b040c:	57                   	push   %edi
c10b040d:	b8 9c ff ff ff       	mov    $0xffffff9c,%eax
c10b0412:	56                   	push   %esi
c10b0413:	53                   	push   %ebx
c10b0414:	8b 7c 24 10          	mov    0x10(%esp),%edi
c10b0418:	8b 74 24 14          	mov    0x14(%esp),%esi
c10b041c:	8b 5c 24 18          	mov    0x18(%esp),%ebx
c10b0420:	89 fa                	mov    %edi,%edx
c10b0422:	89 f1                	mov    %esi,%ecx
c10b0424:	53                   	push   %ebx
c10b0425:	e8 dd fe ff ff       	call   0xc10b0307
c10b042a:	5a                   	pop    %edx
c10b042b:	5b                   	pop    %ebx
c10b042c:	5e                   	pop    %esi
c10b042d:	5f                   	pop    %edi
c10b042e:	c3                   	ret    