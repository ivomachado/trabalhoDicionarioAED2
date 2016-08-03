typedef struct arraydinamico TArrayDinamico;

typedef void* (*TAcessarAD)(TArrayDinamico*, int pos);
typedef void (*TAtualizarAD)(TArrayDinamico*, int pos, void* elemento);
typedef int (*TTamanhoAD)(TArrayDinamico*);
TArrayDinamico* criarArrayDinamico(int tam);

struct arraydinamico {
	void *dado;
	TAcessarAD acessar;
	TAtualizarAD atualizar;
	TTamanhoAD tamanho;
};
