
#define ALLOCATE_EXTERN
#include <fx2regs.h>

#include <lights.h>

volatile xdata BYTE* bytes[] = { &D2ON, &D3ON, &D4ON, &D5ON, &D2OFF, &D3OFF, &D4OFF, &D5OFF };

void main(void)
{
	BYTE cur=0;

    // loop endlessly
    for(;;) {
       activate_light_delay(bytes[cur],20);
       cur = cur == 7 ? 0 : cur+1;
    }
}
