#include "main.h"  
#include "bsp_uart.h"
#include "netconf.h"
#include "lwip/tcp.h"
#include "lwip/timeouts.h"
#include "hello_gigadevice.h"
#include "gd32f4xx_enet_eval.h"


int main(void)
{
	board_init();
	
	/* 串口初始化 波特率：115200 */
	bsp_uart_init();

	
/* setup ethernet system(GPIOs, clocks, MAC, DMA, systick) */
    enet_system_setup();

    /* initilaize the LwIP stack */
    lwip_stack_init();
	printf("init susccess\r\n");
    while(1) {

#ifndef USE_ENET_INTERRUPT
        /* check if any packet received */
        if(enet_rxframe_size_get()) {
            /* process received ethernet packet */
            lwip_pkt_handle();
        }
#endif /* USE_ENET_INTERRUPT */

        /* handle periodic timers for LwIP */
#ifdef TIMEOUT_CHECK_USE_LWIP
        sys_check_timeouts();

#ifdef USE_DHCP
        lwip_dhcp_process_handle();
#endif /* USE_DHCP */

#else
        lwip_periodic_handle(get_system_tick());
#endif /* TIMEOUT_CHECK_USE_LWIP */
    }
}





/*!
    \brief      after the netif is fully configured, it will be called to initialize the function of telnet, client and udp
    \param[in]  netif: the struct used for lwIP network interface
    \param[out] none
    \retval     none
*/
void lwip_netif_status_callback(struct netif *netif)
{
    if((netif->flags & NETIF_FLAG_UP) != 0) {
        /* initilaize the helloGigadevice module telnet 23 */
        hello_gigadevice_init();
    }
}

