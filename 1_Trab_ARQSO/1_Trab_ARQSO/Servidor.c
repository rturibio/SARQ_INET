#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <pthread.h>

void *conect(void *arg);

pthread_mutex_t mutex;

int main(int argc, char **argv)
{
	pthread_mutex_init(&mutex,NULL);
	int sock_fd, sock_len, sock_novo, num;
	socklen_t nock_novo_len;
	struct sockaddr_in sock_ser, sock_cli;
	char msg[100];

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		printf("Erro ao criar o Socket \n");
			exit(0);
	}



	bzero((char*)&sock_ser, sizeof(sock_ser));
	sock_ser.sin_family = AF_INET;
	

	sock_ser.sin_port=htons(9002);
	sock_ser.sin_addr.s_addr=INADDR_ANY;

	if (bind(sock_fd, (struct sockaddr*)&sock_ser, sizeof sock_ser) < 0)
	{
		printf("Erro ao associar o nome ao socket \n");
		exit(0);
	}

	listen(sock_fd, 5);

	
	pthread_t conexao;

	while (1)
	{
		int sock_novo_len = sizeof(sock_cli);
		sock_novo = accept(sock_fd, (struct sockaddr*)&sock_cli, &sock_novo_len);

		if (sock_novo < 0)
		{
			printf("Erro ao conectar com o cliente \n");
			exit(0);
		}
		else printf("\nConectado ao Servidor !\n\n");
		pthread_create(&conexao,NULL,conect,&sock_novo);
              
                printf("Trabalho Arq_Sis_Op\n");
 		printf("Comandos executados:\n");
 		printf("1- criar (sub)diretório / mkdir -p\n");
 		printf("2- remover (sub)diretório / rm -rf\n");
 		printf("3- entrar em (sub)diretório / cd\n");
 		printf("4- mostrar conteúdo do diretório / ls \n");
 		printf("5- criar arquivo / nano\n");
 		printf("6- remover arquivo / rm\n");
 		printf("7- escrever um sequência de caracteres em um arquivo / \n");
 		printf("8- mostrar conteúdo do arquivo / more\n\n");
	}
}

void *conect(void *arg)
{
	pthread_mutex_lock(&mutex);
	int save_sockt = *((int*) arg);

	 char msg[255];

	memset(&msg,'\0', sizeof(msg));
 
	while (1)
	{
		printf("*********************************************\n");
		printf("\nExecute seu Comando:\n");
		read(save_sockt,&msg,255);
		printf("\nSeu comando foi: ");
  
		printf("%s",msg);
		printf("\n");
		system(msg);
		pthread_mutex_unlock(&mutex);
		printf("\n");
	}

}

