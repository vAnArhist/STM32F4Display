#include "lwip/tcp.h"
#include "my_tcp.h"
#include <string.h>
#include "GUI.h"
#define MAX_BUFFER 32

const char NAK[3] = {0x4E,0x41,0x4B};
const int thrd=0x30;
const int ID=0xFF;
extern char transmitBuffer[32];
extern char receiveBuffer[32];
extern char rec[512];

struct inc_packet{
int length;  
char NAK[3];
int thrd;
int ID;
char bytes[MAX_BUFFER];
};


err_t MyTCP_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err);
err_t MyTCP_accept(void *arg, struct tcp_pcb *pcb, err_t err);
void  MyTCP_conn_err(void *arg, err_t err);

//Инициализация

void MyTCP_init()
{
  struct tcp_pcb *pcb;	            		
  
  /* Create a new TCP control block.*/
  pcb = tcp_new();	                		 	

  /* Assign to the new pcb a local IP address and a port number. 
Using IP_ADDR_ANY allow the pcb to be used by any local interface */
  tcp_bind(pcb, IP_ADDR_ANY, 10800); //открывает pcb.    

  /* Set the connection to the LISTEN state */
  pcb = tcp_listen(pcb);				

  /* Specify the function to be called when a connection is established */	
  tcp_accept(pcb, MyTCP_accept);
}

err_t MyTCP_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
 /* Tell LwIP to associate this structure with this connection. 
 Contiguously allocates enough space for count objects that are size bytes
 of memory each and returns a pointer to the allocated memory.*/
  tcp_arg(pcb, mem_calloc(sizeof(struct inc_packet), 5));//арг., который должен быть передан колбек-ф-и	
  
  /* Configure LwIP to use our call back functions. */
  tcp_err(pcb, MyTCP_conn_err);
  tcp_recv(pcb, MyTCP_recv);//функция, указывающая коллбэк на прием        
  
  /* Send out the first message */  
  tcp_write(pcb, "Connection Established", 22, 1); 

  return ERR_OK;
}

//освобождает память LWIP при сбое подключения
static void MyTCP_conn_err(void *arg, err_t err)
{
  struct inc_packet *inc_packet;
  inc_packet = (struct inc_packet *)arg;
  mem_free(inc_packet);
}

//Ф-я приема (проверки вх. пакета).

/*Протокол TCP определяет окно, которое говорит узлу отправки данных, сколько 
он сможет отправить на подключение. Размер окна для всех подключений определяется 
дефайном TCP_WND, который может быть переопределен в lwipopts.h. Приложение обработки 
входящих данных, должно вызвать функцию tcp_recved(), чтобы указать, что TCP 
может увеличить размер окна приема.
Custom memory pools для размещения буфера приема в своей переменной memp_std.h
LWIP_MALLOC_MEMPOOL(number_buffers, buffer_size). This is used to define pools for a mem_malloc (see next section). 
@file lwippools.h
 * Define three pools with sizes 256, 512, and 1512 bytes
LWIP_MALLOC_MEMPOOL_START
LWIP_MALLOC_MEMPOOL(50, 256)
LWIP_MALLOC_MEMPOOL(50, 512)
LWIP_MALLOC_MEMPOOL(50, 1512)
LWIP_MALLOC_MEMPOOL_END 

My sys_arch uses memory pools to allocate mbox and sems 
LWIP_MEMPOOL(SYS_MBOX, 22, sizeof(struct sys_mbox_struct), "SYS_MBOX")
LWIP_MEMPOOL(SYS_SEM, 12, sizeof(struct sys_sem_struct), "SYS_SEM")
*/
static err_t MyTCP_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  struct pbuf *q;//указатель на буфер
  struct inc_packet *inc_packet = (struct inc_packet *)arg;
  int *receive;  //pointer to the actual data in the buffer
  
  /* We perform here any necessary processing on the pbuf */
  if (p != NULL)
    {        
/* We call this function to tell the LwIp that we have processed the data */
/* This lets the stack advertise a larger window, so more data can be received*/
  tcp_recved(pcb, p->tot_len);
/* Check the inc_packet if NULL, no data passed, return withh illegal argument error */
  if(!inc_packet)
  {
  pbuf_free(p);//высвобождаем входной буфер
  return ERR_ARG;
  }
  uint16_t cnt=0;
  
  for(q=p; q != NULL; q = q->next)//next pbuf in singly linked pbuf chain(разбивание в памяти) 
{
  cnt++;
  receive = q->payload;//pointer to the actual data in the buffer
    if(*receive == 0xFF)// тот ID 
    {
    inc_packet->bytes[inc_packet->length++] = *receive;
    tcp_write(pcb, "\nHello, User\n", 13, 1);//ставит данные в очередь на посыл в буфер.
    tcp_write(pcb, transmitBuffer, 250, 1);// здесь код не работает (кидает только 1-ый бит с массива)
    tcp_write(pcb, receive, 250, 1);
    tcp_output(pcb);//пересылает все данные при пегеполнении вых. буфера
    }
} 

memcpy(rec, receive, p->len);//копирование с переменной ресив в массив рек
    GUI_GotoXY(20, 60);
    GUI_DispString(rec);
/* End of processing, we free the pbuf */
    pbuf_free(p);
  }  
  else if (err == ERR_OK) 
  {
    /* When the pbuf is NULL and the err is ERR_OK, the remote end is closing the connection. */
    /* We free the allocated memory and we close the connection */
    mem_free(inc_packet);
    return tcp_close(pcb);
  }
  return ERR_OK;
}

